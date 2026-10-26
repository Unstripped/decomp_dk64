#!/usr/bin/env python3
"""Permuter tooling for Donkey Kong 64 matching decompilation.

METHODOLOGY AND SAFETY POLICY:
Permuter mutations are NOT semantics-preserving (upstream randomizer.py has
perm_reorder_stmts "Move a statement to another random place", perm_randomize_*_type,
perm_remove_ast deleting if statements without else, *_zero passes), and its scorer
compares disassembly only (stack offsets only with --stack-diffs; it does not check
relocations or data). A result is a search hint: rewrite the idea into readable C
that keeps the asm's behaviour, then the normal gates apply (fdiff/objdiff OK or
TEXT OK, then full ROM `build/dk64.us.z64: OK`). Never paste permuter output into
src unreviewed.

Subcommands:
  setup  Build permuter input directory (.scratch/permuter/<seg>_<FUNC>/)
  run    Run permuter with --stack-diffs and optional wall-clock limit
  best   List best outputs and print diff against base.c
"""

import argparse
import difflib
import glob
import os
import re
import shutil
import signal
import subprocess
import sys
from pathlib import Path
from typing import List, Optional, Tuple

ROOT = Path(__file__).resolve().parent.parent

# ---------------------------------------------------------------------------
# Container re-exec when running on host without /opt/decomp-permuter
# ---------------------------------------------------------------------------
if not os.path.exists("/opt/decomp-permuter"):
    dk_image = os.environ.get("DK_IMAGE")
    if dk_image:
        cmd = ["docker", "run", "--rm"]
        if sys.stdin.isatty() and sys.stdout.isatty():
            cmd.append("-it")
        cmd.extend(["-v", f"{ROOT}:/dk64", "-w", "/dk64", dk_image, "python3", "tools/permute.py"] + sys.argv[1:])
    else:
        dk_script = ROOT / "tools" / "dk"
        if dk_script.exists():
            cmd = [str(dk_script), "python3", "tools/permute.py"] + sys.argv[1:]
        else:
            sys.exit("error: /opt/decomp-permuter not found and tools/dk not found")
    sys.exit(subprocess.call(cmd))


# ---------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------
def locate_asm(seg: str, func: str) -> Path:
    """Find asm file for func in segment."""
    patterns = []
    if seg == "boot":
        patterns.extend([
            f"asm/nonmatchings/*/{func}.s",
            f"asm/boot/nonmatchings/*/{func}.s",
        ])
    else:
        patterns.append(f"asm/{seg}/nonmatchings/*/{func}.s")
    patterns.append(f"asm/**/{func}.s")

    for pat in patterns:
        hits = list(ROOT.glob(pat))
        if hits:
            return hits[0]
    sys.exit(f"error: assembly file for '{func}' in segment '{seg}' not found")


def deduce_src(asm_path: Path, seg: str, func: str) -> Path:
    """Deduce src C file from asm path or pragma lookup."""
    try:
        rel = asm_path.relative_to(ROOT / "asm")
    except ValueError:
        rel = asm_path

    parts = rel.parts
    candidate = None
    if len(parts) >= 3 and parts[1] == "nonmatchings":
        seg_dir = parts[0]
        subpath = Path(*parts[2:-1])
        candidate = ROOT / "src" / seg_dir / f"{subpath}.c"
    elif len(parts) >= 2 and parts[0] == "nonmatchings":
        subpath = Path(*parts[1:-1])
        c1 = ROOT / "src" / "boot" / f"{subpath}.c"
        c2 = ROOT / "src" / f"{subpath}.c"
        candidate = c1 if c1.exists() else c2

    if candidate and candidate.exists():
        return candidate

    # Search src/ for GLOBAL_ASM referencing func.s
    for c_file in (ROOT / "src").glob("**/*.c"):
        try:
            content = c_file.read_text(encoding="utf-8", errors="ignore")
            if f"{func}.s" in content:
                return c_file
        except Exception:
            pass

    if candidate:
        return candidate
    sys.exit(f"error: could not determine src C file for '{func}'")


def get_compile_flags(src_file: Path) -> tuple[str, str]:
    """Determine the IDO compiler and CFLAGS make uses for this src file."""
    rel_src = src_file.relative_to(ROOT)
    rel_obj = Path("build") / rel_src.with_suffix(".o")

    cmd = ["make", "-n", "-W", str(rel_src), str(rel_obj)]
    res = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)

    cc = "/opt/ido5.3/cc"
    cflags = ""
    for line in res.stdout.splitlines():
        m_cc = re.search(r"/opt/ido[0-9.]+/cc", line)
        if m_cc or "asm-processor" in line:
            if m_cc:
                cc = m_cc.group(0)
            if "--" in line:
                # asm-processor format: ... /opt/idoX/cc -- <as flags> -- <cflags> -o <obj> <src>
                parts = line.split("--")
                cflags = parts[-1].strip()
                cflags = cflags.split("-o")[0].strip()
            else:
                # direct cc format: /opt/idoX/cc <cflags> -o <obj> <src>
                m = re.search(r"/opt/ido[0-9.]+/cc\s+(.*?)\s+-o", line)
                if m:
                    cflags = m.group(1).strip()

    if not cflags:
        # Fallback default flags
        cflags = (
            "-c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -signed -woff 649,654,838,807 "
            "-I include -D_FINALROM -DF3DEX_GBI_2 -DTARGET_N64 -D_MIPS_SZLONG=32 -O2 -mips2"
        )
    return cc, cflags


def extract_func_definition(source: str, func_name: str) -> str:
    """Extract a single function definition from C source text."""
    # Find start of function header
    pat = re.compile(rf"(^|\n)([^\n;{{}}]*?\b{re.escape(func_name)}\s*\([^;{{}}]*\)\s*\{{)", re.MULTILINE)
    m = pat.search(source)
    if not m:
        # Retry with multiline parameter list
        pat2 = re.compile(rf"(^|\n)([^\n;{{}}]*?\b{re.escape(func_name)}\s*\([^{{}}]*?\)\s*\{{)", re.DOTALL)
        m = pat2.search(source)
    if not m:
        raise ValueError(f"function '{func_name}' definition not found in source")

    start_idx = m.start(2)
    brace_idx = source.find('{', start_idx)
    level = 1
    i = brace_idx + 1
    n = len(source)
    while i < n:
        if source[i] == '{':
            level += 1
        elif source[i] == '}':
            level -= 1
            if level == 0:
                return source[start_idx : i + 1].strip()
        i += 1
    raise ValueError(f"unclosed brace for function '{func_name}'")


def strip_other_fns(source: str, keep_fn: str) -> str:
    """Turn all function bodies except keep_fn into forward declarations."""
    result = ""
    remain = source
    fn_regex = re.compile(r"^([a-zA-Z0-9_* \t\n]+?)\b(\w+)\s*\(([^;]*?)\)\s*\{", re.M)
    while True:
        m = fn_regex.search(remain)
        if not m:
            result += remain
            break
        fn_name = m.group(2)
        start_idx = m.end() - 1
        level = 1
        i = start_idx + 1
        n = len(remain)
        while i < n and level > 0:
            if remain[i] == "{":
                level += 1
            elif remain[i] == "}":
                level -= 1
            i += 1
        if fn_name == keep_fn or fn_name.startswith("PERM"):
            result += remain[:i]
        else:
            proto = remain[:start_idx].rstrip() + ";"
            result += proto + "\n"
        remain = remain[i:]
    return result


def deduplicate_externs(source: str, func_name: str) -> str:
    """Deduplicate extern variable declarations.

    Keeps, per symbol, the last declaration before func_name's definition (the one the
    kept function compiles against), or the first one when all follow it.
    """
    lines = source.splitlines()
    func_pat = re.compile(rf"\b{re.escape(func_name)}\s*\([^;]*$|\b{re.escape(func_name)}\s*\([^;]*\)\s*\{{")
    func_line = next((i for i, l in enumerate(lines) if func_pat.search(l) and not l.lstrip().startswith("extern")), len(lines))
    decl_re = re.compile(r"extern\s+[a-zA-Z0-9_* \t]+\b([A-Za-z0-9_]+)\s*(?:\[[^\]]*\])*\s*;")
    keep = {}
    for i, l in enumerate(lines):
        m = decl_re.search(l)
        if m:
            sym = m.group(1)
            if sym not in keep or i < func_line:
                keep[sym] = i

    new_lines = []
    for i, l in enumerate(lines):
        m = decl_re.search(l)
        if m and keep[m.group(1)] != i:
            continue
        new_lines.append(l)
    return "\n".join(new_lines)


def wrap_multi_statement_lines(source: str, func_name: str) -> str:
    """Wrap lines with multiple statements inside func_name in PERM_FORCE_SAMELINE."""
    pat = re.compile(rf"(^|\n)([^\n;{{}}]*?\b{re.escape(func_name)}\s*\([^;{{}}]*\)\s*\{{)", re.MULTILINE)
    m = pat.search(source)
    if not m:
        return source
    start_idx = m.start(2)
    brace_idx = source.find("{", start_idx)
    level = 1
    i = brace_idx + 1
    n = len(source)
    while i < n and level > 0:
        if source[i] == "{":
            level += 1
        elif source[i] == "}":
            level -= 1
        i += 1
    func_text = source[start_idx:i]

    lines = func_text.splitlines()
    new_lines = []
    for idx, line in enumerate(lines):
        if idx == 0 or idx == len(lines) - 1:
            new_lines.append(line)
            continue
        s = line.strip()
        if not s or s.startswith("//") or s.startswith("/*") or s.startswith("#"):
            new_lines.append(line)
            continue
        if "PERM_" in s:
            new_lines.append(line)
            continue
        if re.match(r"^\s*for\s*\(", line):
            paren_depth = 0
            open_idx = line.find("(")
            close_idx = -1
            for j in range(open_idx, len(line)):
                if line[j] == "(":
                    paren_depth += 1
                elif line[j] == ")":
                    paren_depth -= 1
                    if paren_depth == 0:
                        close_idx = j
                        break
            if close_idx != -1:
                after_for = line[close_idx + 1:]
                if after_for.count(";") <= 1:
                    new_lines.append(line)
                    continue
        if s.count(";") > 1:
            indent = line[:len(line) - len(line.lstrip())]
            new_lines.append(f"{indent}PERM_FORCE_SAMELINE({s})")
        else:
            new_lines.append(line)

    new_func_text = "\n".join(new_lines)
    return source[:start_idx] + new_func_text + source[i:]


def preprocess_whole_source(source_text: str, extra_flags: List[str]) -> str:
    """Preprocess a complete assembled source file with cpp, expanding macros."""
    cpp_bin = shutil.which("mips-linux-gnu-cpp") or shutil.which("cpp") or "cpp"
    cmd = [
        cpp_bin,
        "-E",
        "-P",
        "-D_LANGUAGE_C",
        "-D_FINALROM",
        "-DF3DEX_GBI_2",
        "-DTARGET_N64",
        "-D_MIPS_SZLONG=32",
        "-D_Static_assert(x, y)=",
        "-D__attribute__(x)=",
        "-D__extension__=",
        "-I",
        "include",
    ]
    for flag in extra_flags:
        if flag.startswith("-I") or flag.startswith("-D"):
            if flag not in cmd:
                cmd.append(flag)

    res = subprocess.run(cmd, cwd=ROOT, input=source_text, capture_output=True, text=True)
    if res.returncode != 0:
        sys.exit(f"error preprocessing source ({cpp_bin}):\n{res.stderr}")

    defines = (
        "#ifndef NULL\n#define NULL 0\n#endif\n"
        "#ifndef TRUE\n#define TRUE 1\n#endif\n"
        "#ifndef FALSE\n#define FALSE 0\n#endif\n"
    )
    return res.stdout + "\n" + defines


# ---------------------------------------------------------------------------
# Subcommand: setup
# ---------------------------------------------------------------------------
def cmd_setup(args: argparse.Namespace) -> None:
    seg = args.seg
    func = args.func

    # 1. Locate asm and src files
    asm_path = locate_asm(seg, func)
    if args.src:
        src_path = Path(args.src)
        if not src_path.is_absolute():
            src_path = ROOT / src_path
    else:
        src_path = deduce_src(asm_path, seg, func)

    if not src_path.exists():
        sys.exit(f"error: src file '{src_path}' not found")

    out_dir = ROOT / ".scratch" / "permuter" / f"{seg}_{func}"
    out_dir.mkdir(parents=True, exist_ok=True)

    # 2. Build target.o
    # Assemble with project prelude and VR4300 flags
    target_o = out_dir / "target.o"
    as_bin = shutil.which("mips-linux-gnu-as") or "mips-linux-gnu-as"
    as_cmd = [
        as_bin,
        "-EB",
        "-march=vr4300",
        "-mabi=32",
        "-mgp32",
        "-mfp32",
        "-I",
        "include",
        "include/asm_prelude.inc",
        str(asm_path),
        "-o",
        str(target_o),
    ]
    res_as = subprocess.run(as_cmd, cwd=ROOT, capture_output=True, text=True)
    if res_as.returncode != 0:
        sys.exit(f"error assembling target.o:\n{res_as.stderr}")

    # 3. Build compile.sh
    cc, cflags = get_compile_flags(src_file=src_path)
    compile_sh = out_dir / "compile.sh"
    sh_content = f"""#!/bin/bash
{cc} {cflags} "$1" -o "$3"
"""
    compile_sh.write_text(sh_content, encoding="utf-8")
    compile_sh.chmod(0o755)

    # 4. Build settings.toml
    settings_toml = out_dir / "settings.toml"
    settings_content = f"""func_name = "{func}"
compiler_type = "ido"
"""
    settings_toml.write_text(settings_content, encoding="utf-8")

    src_text = src_path.read_text(encoding="utf-8", errors="ignore")

    # 5. Build base.c
    if args.from_file:
        from_path = Path(args.from_file)
        if not from_path.is_absolute():
            from_path = ROOT / from_path
        if not from_path.exists():
            sys.exit(f"error: input file '{from_path}' not found")
        from_text = from_path.read_text(encoding="utf-8", errors="ignore")
    else:
        # Check if func is parked inside #ifdef NON_MATCHING in src_text
        pat_parked = rf"#if(?:def|\s+defined\s*\()\s*NON_MATCHING[\s\S]*?\b{re.escape(func)}\s*\([^;]*\)\s*\{{"
        if re.search(pat_parked, src_text):
            from_path = src_path
            from_text = src_text
        else:
            # A function already written as C in the given --src (e.g. a private copy) is
            # taken from there; otherwise fall back to the stored draft.
            src_has_c = re.search(rf"^[^\n;#]*\b{re.escape(func)}\s*\([^;]*\)\s*\{{", src_text, re.M) and not re.search(
                rf"#pragma\s+GLOBAL_ASM\(\"[^\"]*/{re.escape(func)}\.s\"\)", src_text
            )
            if src_has_c:
                from_path = src_path
                from_text = src_text
            else:
                from_path = ROOT / "drafts" / seg / f"{func}.c"
                if not from_path.exists():
                    sys.exit(f"error: input file '{from_path}' not found (provide a draft or --from FILE.c)")
                from_text = from_path.read_text(encoding="utf-8", errors="ignore")

    # Determine if NON_MATCHING should be enabled
    use_non_matching = bool(args.non_matching)
    if not use_non_matching:
        pat_nm = rf"#if(?:def|\s+defined\s*\()\s*NON_MATCHING[\s\S]*?\b{re.escape(func)}\b[\s\S]*?#endif"
        if re.search(pat_nm, from_text) or re.search(pat_nm, src_text):
            use_non_matching = True

    # Check whether from_path is a whole file (e.g. private copy of src/ with GLOBAL_ASM / other functions)
    is_whole_file = False
    if from_path == src_path or args.from_file:
        if re.search(r"#pragma\s+GLOBAL_ASM", from_text):
            is_whole_file = True
        else:
            top_fns = re.findall(r"^(?:[a-zA-Z0-9_*]+\s+)+(\w+)\s*\([^;]*\)\s*\{", from_text, re.MULTILINE)
            top_fns = [f for f in top_fns if f not in ("if", "while", "for", "switch", "catch")]
            if len(top_fns) > 1:
                is_whole_file = True

    if is_whole_file:
        combined = from_text
    else:
        # Stored draft or single function snippet
        draft_lines = []
        for line in from_text.splitlines():
            s = line.strip()
            if s.startswith("//"):
                continue
            if s.startswith("#include"):
                inc = s.split()[1] if len(s.split()) > 1 else ""
                if inc in src_text:
                    continue
            draft_lines.append(line)
        draft_text = "\n".join(draft_lines).strip()

        # Replace target GLOBAL_ASM with draft_text, or append if pragma absent
        target_pragma = re.compile(rf"#pragma\s+GLOBAL_ASM\(\"[^\"]*{re.escape(func)}\.s\"\)")
        if target_pragma.search(src_text):
            combined = target_pragma.sub(lambda _: draft_text, src_text, count=1)
        else:
            combined = src_text + "\n\n" + draft_text

    combined = deduplicate_externs(combined, func)
    combined = strip_other_fns(combined, func)
    combined = re.sub(r"#pragma\s+GLOBAL_ASM\([^\)]*\)", "", combined)

    extra_flags = [tok for tok in cflags.split() if tok.startswith("-I") or tok.startswith("-D")]
    if use_non_matching and "-DNON_MATCHING" not in extra_flags:
        extra_flags.append("-DNON_MATCHING")

    base_c_content = preprocess_whole_source(combined, extra_flags)
    base_c_content = wrap_multi_statement_lines(base_c_content, func)
    base_c = out_dir / "base.c"
    base_c.write_text(base_c_content, encoding="utf-8")

    # 6. Verify compilation and compute starting score
    base_o = out_dir / "base.o"
    if "PERM_" in base_c_content:
        sys.path.insert(0, "/opt/decomp-permuter")
        from src.perm.eval import perm_evaluate_one
        from src.perm.parse import perm_parse
        perms = perm_parse(base_c_content)
        test_c_content, _ = perm_evaluate_one(perms)
        test_c_file = out_dir / "test_base.c"
        test_c_file.write_text(test_c_content, encoding="utf-8")
        comp_file = test_c_file
    else:
        comp_file = base_c

    comp_res = subprocess.run(
        [str(compile_sh), str(comp_file), "-o", str(base_o)],
        cwd=out_dir,
        capture_output=True,
        text=True,
    )
    if "PERM_" in base_c_content and comp_file.exists():
        comp_file.unlink()

    if comp_res.returncode != 0:
        print(f"Compilation error in {base_c}:", file=sys.stderr)
        print(comp_res.stderr or comp_res.stdout, file=sys.stderr)
        sys.exit(1)

    # Score base.o vs target.o and compute permuter baseline score
    sys.path.insert(0, "/opt/decomp-permuter")
    try:
        from src.scorer import Scorer
        from src.preprocess import preprocess
        from src.perm.parse import perm_parse
        from src.perm.eval import perm_evaluate_one
        from src.candidate import Candidate
        from src.helpers import get_default_randomization_weights

        scorer = Scorer(
            str(target_o),
            stack_differences=True,
            algorithm="difflib",
            debug_mode=False,
            ign_branch_targets=False,
            objdump_command=None,
        )
        direct_score, _ = scorer.score(str(base_o))

        # Evaluate through decomp-permuter pipeline as run will
        c_source = preprocess(str(base_c))
        weights = get_default_randomization_weights("ido")
        perms = perm_parse(c_source)
        base_source, eval_state = perm_evaluate_one(perms)
        cand = Candidate.from_source(base_source, eval_state, func, weights, rng_seed=0)
        cand_c = out_dir / "cand_base.c"
        cand_o = out_dir / "cand_base.o"
        cand_c.write_text(cand.get_source(), encoding="utf-8")
        cand_comp = subprocess.run(
            [str(compile_sh), str(cand_c), "-o", str(cand_o)],
            cwd=out_dir,
            capture_output=True,
            text=True,
        )
        if cand_c.exists():
            cand_c.unlink()
        cand_score = None
        if cand_comp.returncode == 0:
            cand_score, _ = scorer.score(str(cand_o))
            if cand_o.exists():
                cand_o.unlink()

        print(f"Permuter setup complete: {out_dir}")
        print(f"Starting score (direct compile): {direct_score}")
        if cand_score is not None:
            print(f"Starting score (permuter baseline): {cand_score}")
            if cand_score != direct_score:
                print(
                    f"WARNING: Direct compile score ({direct_score}) and permuter baseline score ({cand_score}) differ!\n"
                    f"IDO 5.3 is sensitive to same-line statements and formatting.\n"
                    f"The permuter will search relative to the baseline score ({cand_score})."
                )
    except Exception as e:
        print(f"Permuter setup complete: {out_dir}")
        print(f"(Scorer check warning: {e})")

# ---------------------------------------------------------------------------
# Subcommand: run
# ---------------------------------------------------------------------------
def cmd_run(args: argparse.Namespace, extra_args: List[str]) -> None:
    target_dir = Path(args.dir)
    if not target_dir.is_absolute():
        target_dir = ROOT / target_dir

    if not target_dir.exists():
        sys.exit(f"error: directory '{target_dir}' does not exist")

    for req in ["base.c", "target.o", "compile.sh"]:
        if not (target_dir / req).exists():
            sys.exit(f"error: missing '{req}' in {target_dir}")

    threads = args.threads
    if threads is None or threads <= 0:
        cpu_cnt = os.cpu_count() or 2
        threads = max(1, cpu_cnt // 2)

    permuter_py = Path("/opt/decomp-permuter/permuter.py")
    if not permuter_py.exists():
        sys.exit("error: /opt/decomp-permuter/permuter.py not found")

    cmd = [
        sys.executable,
        str(permuter_py),
        str(target_dir),
        "--stack-diffs",
        "--stop-on-zero",
        "-j",
        str(threads),
    ] + extra_args

    print(f"Running permuter on {target_dir} ({threads} threads, --stack-diffs, stop-on-zero)...")
    if args.seconds is not None and args.seconds > 0:
        proc = subprocess.Popen(cmd)
        try:
            ret = proc.wait(timeout=args.seconds)
            sys.exit(ret)
        except subprocess.TimeoutExpired:
            print(f"\nWall-clock limit reached ({args.seconds}s). Stopping permuter.")
            proc.send_signal(signal.SIGINT)
            try:
                proc.wait(timeout=5)
            except subprocess.TimeoutExpired:
                proc.kill()
            sys.exit(0)
    else:
        ret = subprocess.call(cmd)
        sys.exit(ret)


# ---------------------------------------------------------------------------
# Subcommand: best
# ---------------------------------------------------------------------------
def cmd_best(args: argparse.Namespace) -> None:
    target_dir = Path(args.dir)
    if not target_dir.is_absolute():
        target_dir = ROOT / target_dir

    if not target_dir.exists():
        sys.exit(f"error: directory '{target_dir}' does not exist")

    output_dirs = []
    for d in target_dir.iterdir():
        if d.is_dir() and d.name.startswith("output-"):
            score = None
            score_file = d / "score.txt"
            if score_file.exists():
                try:
                    score = int(score_file.read_text().strip())
                except ValueError:
                    pass
            if score is None:
                parts = d.name.split("-")
                if len(parts) >= 2:
                    try:
                        score = int(parts[1])
                    except ValueError:
                        score = 999999
            output_dirs.append((score, d))

    if not output_dirs:
        print(f"No output directories found in {target_dir}")
        return

    output_dirs.sort(key=lambda x: (x[0] if x[0] is not None else 999999, x[1].name))

    print(f"Outputs in {target_dir} ({len(output_dirs)} total, sorted by score):")
    for score, d in output_dirs:
        rel = d.relative_to(ROOT) if d.is_relative_to(ROOT) else d
        print(f"  score: {score:<6d} path: {rel}")

    best_score, best_d = output_dirs[0]
    rel_best = best_d.relative_to(ROOT) if best_d.is_relative_to(ROOT) else best_d
    print(f"\n=== Best result: score {best_score} in {rel_best} ===")

    diff_file = best_d / "diff.txt"
    if diff_file.exists() and diff_file.stat().st_size > 0:
        print(diff_file.read_text(encoding="utf-8", errors="ignore"))
    else:
        # Fallback to computing unified diff between base.c and source.c
        base_c = target_dir / "base.c"
        source_c = best_d / "source.c"
        if base_c.exists() and source_c.exists():
            base_lines = base_c.read_text(encoding="utf-8", errors="ignore").splitlines()
            source_lines = source_c.read_text(encoding="utf-8", errors="ignore").splitlines()
            udiff = list(difflib.unified_diff(base_lines, source_lines, fromfile="base.c", tofile="source.c", lineterm=""))
            print("\n".join(udiff))


# ---------------------------------------------------------------------------
# CLI Entrypoint
# ---------------------------------------------------------------------------
def main() -> None:
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    sub = parser.add_subparsers(dest="subcommand", required=True)

    # setup
    p_setup = sub.add_parser("setup", help="Set up a permuter input directory")
    p_setup.add_argument("seg", help="Segment name (boot, global, boss, ...)")
    p_setup.add_argument("func", help="Function name (e.g. func_80663BE8)")
    p_setup.add_argument("--from", dest="from_file", help="Input C file (default: drafts/<seg>/<func>.c)")
    p_setup.add_argument("--src", help="Path to original C file in src/ (default: auto-detected)")
    p_setup.add_argument("--non-matching", action="store_true", help="Enable NON_MATCHING define for parked function definitions")

    # run
    p_run = sub.add_parser("run", help="Run permuter on an input directory")
    p_run.add_argument("dir", help="Permuter input directory")
    p_run.add_argument("-j", "--threads", type=int, default=None, help="Number of threads (default: half CPUs)")
    p_run.add_argument("--seconds", type=int, default=None, help="Wall-clock limit in seconds")

    # best
    p_best = sub.add_parser("best", help="List best outputs and show diff")
    p_best.add_argument("dir", help="Permuter input directory")

    # Parse known args so trailing permuter args can be forwarded to run
    args, extra = parser.parse_known_args()

    if args.subcommand == "setup":
        if extra:
            sys.exit(f"error: unrecognized arguments: {' '.join(extra)}")
        cmd_setup(args)
    elif args.subcommand == "run":
        cmd_run(args, extra)
    elif args.subcommand == "best":
        if extra:
            sys.exit(f"error: unrecognized arguments: {' '.join(extra)}")
        cmd_best(args)


if __name__ == "__main__":
    main()
