# /// script
# requires-python = ">=3.12"
# dependencies = ["libclang==18.1.1"]
# ///
"""Remaining-work ("debt") ledger for continue units: one weighted score over every decompilation and
cleanup task, per stream and per src file, so a unit spends its slots where the most debt retires.

    uv run tools/debt.py [--from REPORT.json] [--progress PROGRESS.json] [--limit N] [--stream S] [--json]
    uv run tools/debt.py names [--limit N] [--seg SEG]

Without --from it runs `uv run tools/quality.py report --json` (~5 min); `bash autoresearch.sh` leaves
both inputs in .scratch/autoresearch/ (quality.json, progress.json), so pass those to reuse a fresh run.
--progress adds unmatched functions / asm data (segment-level, from `tools/progress.py --json`).

`names` is the names stream's queue (libclang, every non-libultra src file): unkXX field references
grouped by the record that declares them (with that declaration's file), D_ globals by name space
(an address in overlay VRAM 0x80024000-0x805FB300 belongs to the referencing overlay; any other address is
one boot/global symbol, its refs summed over every segment, renamed with `rename.py global global`) and func_
definitions per segment, highest reference count first: one rename retires all of its references.

Streams and the procedure that retires each:
  decomp   unmatched functions, asm data         -> skill://decomp-unit (§1-3) / data.md
  hack     FAKE, goto, LAYOUT, proto-type, open ladder sites -> cleanup-unit hack workers (brief-hack.md)
  polish   unreviewed functions, cfe/uninit warnings, prototype mismatches -> polish workers / TypesOwner
  names    func_ definitions, m2c names, unkXX fields, D_ refs -> names workers (continue-unit names.md)

The weights must equal the ones in autoresearch.sh (the benchmark the continue-unit campaign is scored by).
"""
import argparse
import collections
import json
import multiprocessing
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from shadow import posix  # noqa: E402

# quality.py report row -> (metric key, weight, stream)
ROWS = {
    "FAKE": ("fake", 20, "hack"),
    "goto": ("goto", 20, "hack"),
    "LAYOUT": ("layout", 10, "hack"),
    "proto-type": ("proto_type", 10, "hack"),
    "sites open": ("sites_open", 5, "hack"),
    "cfe warnings": ("cfe_warnings", 5, "polish"),
    "protos mismatch": ("protos_mismatch", 5, "polish"),
    "uninit warnings": ("uninit_warnings", 2, "polish"),
    "func_ defs": ("func_defs", 2, "names"),
    "m2c names": ("m2c_names", 2, "names"),
    "unk fields": ("unk_fields", 1, "names"),
    "D_ refs": ("d_refs", 1, "names"),
}
UNREVIEWED_W = 5  # functions - reviewed, stream polish
UNMATCHED_W, ASM_DATA_W = 100, 0.25  # progress.py, stream decomp
STREAMS = ("decomp", "hack", "polish", "names")


def score(counts):
    """{metric: n}, {stream: debt} for one report row dict (file, segment or total)."""
    m, s = {}, dict.fromkeys(STREAMS, 0)
    for row, (key, w, stream) in ROWS.items():
        m[key] = counts.get(row, 0)
        s[stream] += w * m[key]
    m["unreviewed"] = counts.get("functions", 0) - counts.get("reviewed", 0)
    s["polish"] += UNREVIEWED_W * m["unreviewed"]
    return m, s


def cmd_rank(a):
    if a.src:
        rep = json.load(open(a.src))
    else:
        out = subprocess.run(["uv", "run", "tools/quality.py", "report", "--json"], cwd=ROOT, check=True,
                             capture_output=True, text=True).stdout
        rep = json.loads(out)
    if "files" not in rep:
        sys.exit("debt: report has no per-file counts; rerun `uv run tools/quality.py report --json`")

    _, streams = score(rep["total"])
    decomp_segs = None
    if a.progress:
        prog = json.load(open(a.progress))
        t = prog["total"]
        streams["decomp"] = UNMATCHED_W * (t["total_funcs"] - t["matched_funcs"]) + ASM_DATA_W * t["data_asm_bytes"]
        decomp_segs = {seg: v["total_funcs"] - v["matched_funcs"] for seg, v in prog.items()
                       if seg != "total" and v["total_funcs"] != v["matched_funcs"]}

    rows = []
    for path, counts in rep["files"].items():
        m, s = score(counts)
        d = s[a.stream] if a.stream else sum(s.values())
        if d:
            rows.append((d, path, s, m))
    rows.sort(key=lambda r: (-r[0], r[1]))

    if a.json:
        print(json.dumps({"debt": sum(streams.values()), "streams": streams, "unmatched_by_seg": decomp_segs,
                          "files": [{"path": p, "debt": d, "streams": s, "metrics": m}
                                    for d, p, s, m in rows[:a.limit]]}, indent=1))
        return
    print(f"debt {sum(streams.values()):g}  " + "  ".join(f"{k} {v:g}" for k, v in streams.items())
          + ("" if a.progress else "  (decomp: pass --progress)"))
    if decomp_segs:
        print("unmatched: " + ", ".join(f"{k} {v}" for k, v in decomp_segs.items()))
    print(f"\n{'debt':>6}  {'file':<34} {'hack':>5} {'polish':>6} {'names':>6}  top items")
    for d, path, s, m in rows[:a.limit]:
        top = sorted(((w * m[k], k, m[k]) for k, w, _ in ROWS.values() if m[k]), reverse=True)[:3]
        if m["unreviewed"]:
            top.append((UNREVIEWED_W * m["unreviewed"], "unreviewed", m["unreviewed"]))
        print(f"{d:>6g}  {path:<34} {s['hack']:>5g} {s['polish']:>6g} {s['names']:>6g}  "
              + ", ".join(f"{k} {n}" for _, k, n in top))


def names_scan(path):
    """(path, Counter((record, field, decl file)), Counter(D_ symbol), [func_ definitions]) for one src file."""
    import clint
    from clang.cindex import CursorKind
    tu = clint.parse(path)
    me = os.path.abspath(os.path.join(ROOT, path))
    fields, drefs, funcs = collections.Counter(), collections.Counter(), []
    for top in tu.cursor.get_children():
        # function bodies only, as clint.function_metrics counts them (the scored metric)
        if (top.kind != CursorKind.FUNCTION_DECL or not top.is_definition() or top.location.file is None
                or os.path.abspath(top.location.file.name) != me):
            continue
        if top.spelling.startswith("func_"):
            funcs.append(top.spelling)
        for c in clint.walk(top):
            if c.kind == CursorKind.MEMBER_REF_EXPR and clint.UNK_FIELD.match(c.spelling):
                rec = c.referenced.semantic_parent if c.referenced else None
                name = (rec.type.spelling or rec.spelling) if rec else "?"
                decl = posix(os.path.relpath(rec.location.file.name, ROOT)) if rec and rec.location.file else "?"
                fields[(name, c.spelling, decl)] += 1
            elif c.kind == CursorKind.DECL_REF_EXPR and clint.D_REF.match(c.spelling):
                drefs[c.spelling] += 1
    return path, fields, drefs, funcs


def cmd_names(a):
    import clint
    files = [p for p in clint.src_files() if not a.seg or p.startswith(f"src/{a.seg}/")]
    with multiprocessing.get_context("spawn").Pool(os.cpu_count() or 4) as pool:
        res = pool.map(names_scan, files, chunksize=4)
    fields, fields_files = collections.Counter(), collections.defaultdict(set)
    drefs, drefs_files = collections.Counter(), collections.defaultdict(set)
    funcs = collections.Counter()
    for path, f, d, fn in res:
        seg = path.split("/")[1]
        for k, n in f.items():
            fields[k] += n
            fields_files[k].add(path)
        for k, n in d.items():
            # overlays share VRAM 0x80024000-0x805FB300 (each its own name space); any other address is a
            # boot/global symbol (one name space, `rename.py global global ...`) whichever segment references it
            key = (seg if 0x80024000 <= int(k[2:], 16) < 0x805FB300 else "global", k)
            drefs[key] += n
            drefs_files[key].add(path)
        funcs[seg] += len(fn)
    print(f"unk fields {sum(fields.values())} refs / {len(fields)} fields; D_ refs {sum(drefs.values())} refs / "
          f"{len(drefs)} symbols; func_ definitions "
          + (", ".join(f"{s} {n}" for s, n in funcs.most_common() if n) or "0"))
    by_rec = collections.Counter()
    for (rec, _, decl), n in fields.items():
        by_rec[rec, decl] += n
    print(f"\n{'refs':>5}  record (declared in): top fields  -- one names worker per record or two related ones")
    for (rec, decl), n in by_rec.most_common(a.limit // 2):
        top = sorted(((m, f) for (r, f, d), m in fields.items() if (r, d) == (rec, decl)), reverse=True)[:6]
        print(f"{n:>5}  {rec} ({decl}): " + " ".join(f"{f} {m}" for m, f in top))
    print(f"\n{'refs':>5} {'files':>5}  field (declared in)")
    for (rec, fld, decl), n in fields.most_common(a.limit):
        print(f"{n:>5} {len(fields_files[rec, fld, decl]):>5}  {rec}.{fld} ({decl})")
    print(f"\n{'refs':>5} {'files':>5}  global (segment)")
    for (seg, sym), n in drefs.most_common(a.limit):
        print(f"{n:>5} {len(drefs_files[seg, sym]):>5}  {sym} ({seg})")
    per_file = collections.Counter()
    for path, _, d, _ in res:
        per_file[path] = sum(d.values())
    print(f"\n{'refs':>5}  file (D_ refs in function bodies)  -- D_ workers take neighbouring files")
    for path, n in per_file.most_common(a.limit):
        if n:
            print(f"{n:>5}  {path}")


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--from", dest="src", help="quality.py report --json output")
    p.add_argument("--progress", help="tools/progress.py --json output")
    p.add_argument("--limit", type=int, default=30)
    p.add_argument("--stream", choices=STREAMS, help="rank files by this stream's debt only")
    p.add_argument("--json", action="store_true")
    s = p.add_subparsers(dest="cmd")
    n = s.add_parser("names", help="names-stream queue: unkXX fields and D_ globals by reference count")
    n.add_argument("--limit", type=int, default=40)
    n.add_argument("--seg", help="only src/<seg>/ files")
    a = p.parse_args(argv)
    (cmd_names if a.cmd == "names" else cmd_rank)(a)


if __name__ == "__main__":
    main()
