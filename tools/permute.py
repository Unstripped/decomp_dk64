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


def get_compile_flags(src_file: Path) -> str:
    """Determine IDO 5.3 CFLAGS used by make for this src file."""
    rel_src = src_file.relative_to(ROOT)
    rel_obj = Path("build") / rel_src.with_suffix(".o")

    cmd = ["make", "-n", "-W", str(rel_src), str(rel_obj)]
    res = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)

    cflags = ""
    for line in res.stdout.splitlines():
        if "ido5.3/cc" in line or "asm-processor" in line:
            if "--" in line:
                # asm-processor format: ... /opt/ido5.3/cc -- <as flags> -- <cflags> -o <obj> <src>
                parts = line.split("--")
                cflags = parts[-1].strip()
                cflags = cflags.split("-o")[0].strip()
            else:
                # direct cc format: /opt/ido5.3/cc <cflags> -o <obj> <src>
                m = re.search(r"/opt/ido5.3/cc\s+(.*?)\s+-o", line)
                if m:
                    cflags = m.group(1).strip()

    if not cflags:
        # Fallback default flags
        cflags = (
            "-c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -signed -woff 649,654,838,807 "
            "-I include -D_FINALROM -DF3DEX_GBI_2 -DTARGET_N64 -D_MIPS_SZLONG=32 -O2 -mips2"
        )
    return cflags


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


def preprocess_includes(include_lines: List[str], extra_flags: List[str]) -> str:
    """Preprocess #include lines to produce a self-contained type context."""
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
        "-I",
        "include",
    ]
    # Pass through any additional -I or -D flags from the compile flags
    for flag in extra_flags:
        if flag.startswith("-I") or flag.startswith("-D"):
            if flag not in cmd:
                cmd.append(flag)

    input_text = "\n".join(include_lines) + "\n"
    res = subprocess.run(cmd, cwd=ROOT, input=input_text, capture_output=True, text=True)
    if res.returncode != 0:
        sys.exit(f"error preprocessing includes ({cpp_bin}):\n{res.stderr}")
    return res.stdout


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
    cflags = get_compile_flags(src_file=src_path)
    compile_sh = out_dir / "compile.sh"
    sh_content = f"""#!/bin/bash
/opt/ido5.3/cc {cflags} "$1" -o "$3"
"""
    compile_sh.write_text(sh_content, encoding="utf-8")
    compile_sh.chmod(0o755)

    # 4. Build settings.toml
    settings_toml = out_dir / "settings.toml"
    settings_content = f"""func_name = "{func}"
compiler_type = "ido"
"""
    settings_toml.write_text(settings_content, encoding="utf-8")

    # 5. Build base.c
    if args.from_file:
        from_path = Path(args.from_file)
        if not from_path.is_absolute():
            from_path = ROOT / from_path
    else:
        from_path = ROOT / "drafts" / seg / f"{func}.c"

    if not from_path.exists():
        sys.exit(f"error: input file '{from_path}' not found (provide a draft or --from FILE.c)")

    from_text = from_path.read_text(encoding="utf-8", errors="ignore")
    src_text = src_path.read_text(encoding="utf-8", errors="ignore")

    # Gather #include lines
    include_lines = []
    for line in src_text.splitlines():
        if line.strip().startswith("#include"):
            include_lines.append(line.strip())
    for line in from_text.splitlines():
        if line.strip().startswith("#include"):
            inc = line.strip()
            if inc not in include_lines:
                include_lines.append(inc)

    # Extract compile flags for cpp
    extra_flags = [tok for tok in cflags.split() if tok.startswith("-I") or tok.startswith("-D")]
    ctx_text = preprocess_includes(include_lines, extra_flags)

    # Standard defines for boolean/pointer constants
    defines = (
        "#ifndef NULL\n#define NULL 0\n#endif\n"
        "#ifndef TRUE\n#define TRUE 1\n#endif\n"
        "#ifndef FALSE\n#define FALSE 0\n#endif\n"
    )
    # Check whether from_path is a whole file (e.g. private copy of src/ with GLOBAL_ASM / other functions)
    is_whole_file = False
    if args.from_file:
        if re.search(r"#pragma\s+GLOBAL_ASM", from_text):
            is_whole_file = True
        else:
            top_fns = re.findall(r"^(?:[a-zA-Z0-9_*]+\s+)+(\w+)\s*\([^;]*\)\s*\{", from_text, re.MULTILINE)
            top_fns = [f for f in top_fns if f not in ("if", "while", "for", "switch", "catch")]
            if len(top_fns) > 1:
                is_whole_file = True

    if is_whole_file:
        # Extract just FUNC from private copy
        func_body = extract_func_definition(from_text, func)
        # Top-level declarations come from from_path (or src_path) before the first function
        m_first = re.search(r"^(?:[a-zA-Z0-9_*]+\s+)+(\w+)\s*\([^;]*\)\s*\{", from_text, re.MULTILINE)
        first_decl_text = from_text[:m_first.start()] if m_first else ""
        decl_lines = [
            l for l in first_decl_text.splitlines()
            if not l.strip().startswith("#include") and not l.strip().startswith("#pragma")
        ]
        base_c_content = f"{ctx_text}\n{defines}\n" + "\n".join(decl_lines) + f"\n\n{func_body}\n"
    else:
        # Stored draft or single function snippet
        draft_lines = []
        for line in from_text.splitlines():
            s = line.strip()
            if s.startswith("//") or s.startswith("#include"):
                continue
            draft_lines.append(line)
        draft_body = "\n".join(draft_lines).strip()

        # Extract top-level declarations from src file before first function
        m_first = re.search(r"^(?:[a-zA-Z0-9_*]+\s+)+(\w+)\s*\([^;]*\)\s*\{", src_text, re.MULTILINE)
        src_decls = src_text[:m_first.start()] if m_first else ""
        filtered_decls = []
        for l in src_decls.splitlines():
            s = l.strip()
            if s.startswith("#include") or s.startswith("#pragma"):
                continue
            # Avoid redeclaration conflict if symbol already defined/declared in draft
            m_sym = re.search(r"\b(D_[0-9A-Fa-f]+)\b", s)
            if m_sym and m_sym.group(1) in draft_body:
                continue
            filtered_decls.append(l)

        base_c_content = f"{ctx_text}\n{defines}\n" + "\n".join(filtered_decls) + f"\n\n{draft_body}\n"
    base_c = out_dir / "base.c"
    base_c.write_text(base_c_content, encoding="utf-8")

    # 6. Verify compilation and compute starting score
    base_o = out_dir / "base.o"
    comp_res = subprocess.run(
        [str(compile_sh), str(base_c), "-o", str(base_o)],
        cwd=out_dir,
        capture_output=True,
        text=True,
    )
    if comp_res.returncode != 0:
        print(f"Compilation error in {base_c}:", file=sys.stderr)
        print(comp_res.stderr or comp_res.stdout, file=sys.stderr)
        sys.exit(1)

    # Score base.o vs target.o
    sys.path.insert(0, "/opt/decomp-permuter")
    try:
        from src.scorer import Scorer
        scorer = Scorer(
            str(target_o),
            stack_differences=True,
            algorithm="difflib",
            debug_mode=False,
            ign_branch_targets=False,
            objdump_command=None,
        )
        score, _ = scorer.score(str(base_o))
        print(f"Permuter setup complete: {out_dir}")
        print(f"Starting score: {score}")
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
