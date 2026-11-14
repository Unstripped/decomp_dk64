#!/usr/bin/env python3
"""Host-side: merge one cleanup worker's private copies and record its ledger in one command.

  python3 tools/merge_record.py --agent A --unit U --base BASE --model SEL --ledger FILE [--copy-only FILE]
         [--keymap FILE] [--stage PATH]... [--message MSG] [--copy-dir DIR] [--dry-run] src/<seg>/<f>.c...

--copy-dir defaults to .scratch/<A>, --message to `<seg>: clean <file stems> (<A>)`. Every step prints
`== <step>` and echoes its command's output; the first failure prints `MERGE_RECORD_FAIL: <step>` and
exits 1; success prints `MERGE_RECORD_OK merge=<sha|none> ledger=<sha|unchanged>`. --dry-run prints
the commands and runs none.

Steps:
  1. ledger-only check: every <copy-dir>/<basename> equal to BASE's src file means nothing to merge:
     record (--base BASE), carry --rev BASE, dossiers, commit.
  2. gate: tools/merge_gate.sh --commit MSG [--stage P]... <copy-dir> BASE <srcs> (GATE_OK and COMMITTED);
     MERGE = HEAD
  3. record --base BASE --model SEL --batch <ledger>
  4. tools/dk make expected
  5. quality.py sweep <srcs> -j 4 --record --unit U
  6. re-record at the merge commit: <ledger> with --keymap's `<old> -> <new>` keys applied, written to
     <copy-dir>/ledger_at_merge.txt, recorded --base MERGE --skip-missing (sites the merge fixed are gone)
  7. --copy-only lines (keys that exist only in the copy): record --base MERGE
  8. quality.py carry --rev MERGE^ --unit U <srcs>
  9. dossiers: <copy-dir>/dossier_<seg>_<FUNC>.md -> drafts/quality/dossiers/<seg>/<FUNC>.md
 10. git commit -- drafts/quality (`quality: <U> <A> record`)
"""
import argparse
import glob
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
QUALITY = ["uv", "run", "tools/quality.py"]
DOSSIER = re.compile(r"dossier_(\w+?)_(\w+)\.md$")


class Fail(Exception):
    pass


def parse_keymap(text):
    """{old key: new key} of a keymap file: `<old> -> <new>` lines, blank and `#` lines ignored."""
    out = {}
    for n, line in enumerate(text.split("\n"), 1):
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        m = re.fullmatch(r"(\S+)\s+->\s+(\S+)", s)
        if not m:
            raise ValueError(f"keymap line {n}: expected `<old> -> <new>`, got {s!r}")
        out[m.group(1)] = m.group(2)
    return out


def apply_keymap(lines, mapping):
    """LINES with each record line's first token (its key) replaced through MAPPING."""
    out = []
    for line in lines:
        toks = line.split(None, 1)
        if toks and toks[0] in mapping:
            lead = line[:len(line) - len(line.lstrip())]
            line = lead + mapping[toks[0]] + (" " + toks[1] if len(toks) > 1 else "")
        out.append(line)
    return out


class Runner:
    def __init__(self, dry):
        self.dry = dry

    def step(self, name):
        print(f"== {name}", flush=True)
        self.name = name

    def run(self, cmd, ok=lambda out: True):
        """Run CMD in ROOT echoing its output; Fail on a non-zero exit or when OK(output) is false."""
        print("$ " + " ".join(cmd), flush=True)
        if self.dry:
            return ""
        p = subprocess.Popen(cmd, cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        out = []
        for line in p.stdout:
            sys.stdout.write(line)
            sys.stdout.flush()
            out.append(line)
        text = "".join(out)
        if p.wait() != 0 or not ok(text):
            raise Fail(self.name)
        return text

    def git(self, *args):
        return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True).stdout.strip()


def same_as_base(copy_dir, base, srcs):
    for src in srcs:
        copy = os.path.join(ROOT, copy_dir, os.path.basename(src))
        if not os.path.exists(copy):
            return False
        r = subprocess.run(["git", "show", f"{base}:{src}"], cwd=ROOT, capture_output=True)
        if r.returncode != 0 or open(copy, "rb").read() != r.stdout:
            return False
    return True


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--agent", required=True)
    p.add_argument("--unit", required=True)
    p.add_argument("--base", required=True)
    p.add_argument("--model", required=True, help="worker selector provider/model[:level]")
    p.add_argument("--ledger", required=True, help="the worker's LEDGER block (record lines)")
    p.add_argument("--copy-only", help="record lines whose keys exist only in the copy")
    p.add_argument("--keymap", help="`<old key> -> <new key>` lines for the re-record at the merge commit")
    p.add_argument("--stage", action="append", default=[])
    p.add_argument("--message")
    p.add_argument("--copy-dir")
    p.add_argument("--dry-run", action="store_true")
    p.add_argument("srcs", nargs="+")
    a = p.parse_args(argv)
    copy_dir = a.copy_dir or os.path.join(".scratch", a.agent)
    segs = sorted({s.split("/")[1] for s in a.srcs if s.count("/") >= 2})
    msg = a.message or f"{'/'.join(segs)}: clean {' '.join(os.path.splitext(os.path.basename(s))[0] for s in a.srcs)} ({a.agent})"
    who = ["--unit", a.unit, "--agent", a.agent]
    r = Runner(a.dry_run)
    merge = None
    try:
        keymap = parse_keymap(open(os.path.join(ROOT, a.keymap)).read()) if a.keymap else {}
        if same_as_base(copy_dir, a.base, a.srcs):
            r.step("ledger-only (copies equal BASE): record")
            r.run(QUALITY + ["record", *who, "--base", a.base, "--model", a.model, "--batch", a.ledger])
            r.step("carry")
            r.run(QUALITY + ["carry", "--rev", a.base, "--unit", a.unit, *a.srcs])
        else:
            r.step("gate")
            stage = [x for s in a.stage for x in ("--stage", s)]
            r.run(["tools/merge_gate.sh", "--commit", msg, *stage, copy_dir, a.base, *a.srcs],
                  ok=lambda out: re.search(r"(?m)^GATE_OK$", out) and re.search(r"(?m)^COMMITTED ", out))
            merge = "<MERGE>" if a.dry_run else r.git("rev-parse", "HEAD")
            r.step("record at base")
            r.run(QUALITY + ["record", *who, "--base", a.base, "--model", a.model, "--batch", a.ledger])
            r.step("make expected")
            r.run(["tools/dk", "make", "expected"])
            r.step("sweep")
            r.run(QUALITY + ["sweep", *a.srcs, "-j", "4", "--record", "--unit", a.unit])
            r.step("re-record at merge")
            at_merge = os.path.join(copy_dir, "ledger_at_merge.txt")
            lines = apply_keymap(open(os.path.join(ROOT, a.ledger)).read().split("\n"), keymap)
            if a.dry_run:
                print(f"(write {at_merge})")
            else:
                open(os.path.join(ROOT, at_merge), "w").write("\n".join(lines))
            r.run(QUALITY + ["record", *who, "--base", merge, "--model", a.model, "--skip-missing",
                             "--batch", at_merge])
            if a.copy_only:
                r.step("copy-only lines")
                r.run(QUALITY + ["record", *who, "--base", merge, "--model", a.model, "--batch", a.copy_only])
            r.step("carry")
            r.run(QUALITY + ["carry", "--rev", f"{merge}^", "--unit", a.unit, *a.srcs])
        r.step("dossiers")
        for path in sorted(glob.glob(os.path.join(ROOT, copy_dir, "dossier_*.md"))):
            m = DOSSIER.search(os.path.basename(path))
            if not m:
                continue
            dest = os.path.join("drafts", "quality", "dossiers", m.group(1), m.group(2) + ".md")
            print(f"{os.path.relpath(path, ROOT)} -> {dest}")
            if not a.dry_run:
                os.makedirs(os.path.dirname(os.path.join(ROOT, dest)), exist_ok=True)
                shutil.copyfile(path, os.path.join(ROOT, dest))
        r.step("commit")
        r.run(["git", "add", "drafts/quality"])
        staged = a.dry_run or subprocess.run(["git", "diff", "--cached", "--quiet", "--", "drafts/quality"],
                                             cwd=ROOT).returncode != 0
        ledger = "unchanged"
        if staged:
            r.run(["git", "commit", "-q", "-m", f"quality: {a.unit} {a.agent} record", "--", "drafts/quality"])
            ledger = "<LEDGER>" if a.dry_run else r.git("rev-parse", "--short", "HEAD")
    except (Fail, OSError, ValueError) as ex:
        name = ex.args[0] if isinstance(ex, Fail) else f"{getattr(r, 'name', 'setup')}: {ex}"
        print(f"MERGE_RECORD_FAIL: {name}", flush=True)
        return 1
    short = merge if merge in (None, "<MERGE>") else merge[:8]
    print(f"MERGE_RECORD_OK merge={short or 'none'} ledger={ledger}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
