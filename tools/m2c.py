#!/usr/bin/env python3
"""m2c helper: produce starter C for a function using m2c.

Usage:
  tools/dk python3 tools/m2c.py [-s SEGMENT] FUNC [extra m2c args]
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import List, Optional, Set

VALID_SEGMENTS = [
    "boot",
    "global",
    "multiplayer",
    "minecart",
    "bonus",
    "race",
    "critter",
    "boss",
    "arcade",
    "jetpac",
    "menu",
]

M2C_DEFAULT_PATH = "/opt/m2c/m2c.py"


def strip_unsupported_c(text: str) -> str:
    """Strip attributes and pragmas that m2c's parser may reject."""
    result = []
    i = 0
    n = len(text)
    while i < n:
        if text.startswith("__attribute__", i):
            j = i + len("__attribute__")
            while j < n and text[j].isspace():
                j += 1
            if j < n and text[j] == "(":
                paren_depth = 0
                while j < n:
                    if text[j] == "(":
                        paren_depth += 1
                    elif text[j] == ")":
                        paren_depth -= 1
                        if paren_depth == 0:
                            j += 1
                            break
                    j += 1
                i = j
                continue
        elif text.startswith("__asm__", i) or text.startswith("__asm", i):
            prefix = "__asm__" if text.startswith("__asm__", i) else "__asm"
            j = i + len(prefix)
            while j < n and text[j].isspace():
                j += 1
            if j < n and text[j] == "(":
                paren_depth = 0
                while j < n:
                    if text[j] == "(":
                        paren_depth += 1
                    elif text[j] == ")":
                        paren_depth -= 1
                        if paren_depth == 0:
                            j += 1
                            break
                    j += 1
                i = j
                continue
        result.append(text[i])
        i += 1

    cleaned = "".join(result)
    cleaned = re.sub(r"\b__extension__\b", "", cleaned)
    lines = []
    for line in cleaned.splitlines():
        stripped = line.strip()
        if stripped.startswith("#"):
            continue
        lines.append(line)
    return "\n".join(lines) + "\n"


def generate_context() -> Path:
    """Build an m2c context from include/common.h and write build/m2c_ctx.c."""
    header = Path("include/common.h")
    if not header.exists():
        sys.exit(f"error: header '{header}' not found")

    ctx_path = Path("build/m2c_ctx.c")
    ctx_path.parent.mkdir(parents=True, exist_ok=True)

    cpp_bin = shutil.which("mips-linux-gnu-cpp") or shutil.which("cpp") or "cpp"
    cmd = [
        cpp_bin,
        "-E",
        "-P",
        "-D_LANGUAGE_C",
        "-DM2CTX",
        "-D_FINALROM",
        "-DF3DEX_GBI_2",
        "-DTARGET_N64",
        "-I",
        "include",
        str(header),
    ]

    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode != 0:
        sys.exit(f"error running C preprocessor ({cpp_bin}):\n{res.stderr}")

    cleaned = strip_unsupported_c(res.stdout)
    ctx_path.write_text(cleaned)
    return ctx_path


def extract_function_asm(file_text: str, func_name: str) -> str:
    """Extract assembly lines for func_name from an asm file."""
    lines = file_text.splitlines()
    in_func = False
    func_lines = []

    glabel_re = re.compile(rf"^\s*glabel\s+{re.escape(func_name)}\b")
    endlabel_re = re.compile(rf"^\s*endlabel\s+{re.escape(func_name)}\b")
    other_glabel_re = re.compile(r"^\s*glabel\s+")

    for line in lines:
        if not in_func:
            if glabel_re.match(line):
                in_func = True
                func_lines.append(line)
        else:
            if endlabel_re.match(line):
                func_lines.append(line)
                break
            if other_glabel_re.match(line):
                break
            func_lines.append(line)

    return "\n".join(func_lines)


def locate_function_asm(segment: str, func: str) -> tuple[Path, bool]:
    """Locate assembly for func in the given segment.

    Returns (path_to_asm_file, is_nonmatching).
    """
    if segment == "boot":
        nonmatching_dir = Path("asm/nonmatchings")
        asm_dir = Path("asm")
    else:
        nonmatching_dir = Path(f"asm/{segment}/nonmatchings")
        asm_dir = Path(f"asm/{segment}")

    # 1. Search nonmatchings
    if nonmatching_dir.is_dir():
        matches = list(nonmatching_dir.glob(f"**/{func}.s"))
        if matches:
            return matches[0], True

    # 2. Search whole-file .s in asm_dir (non-recursive)
    if asm_dir.is_dir():
        pattern = re.compile(rf"^\s*glabel\s+{re.escape(func)}\b", re.MULTILINE)
        for p in sorted(asm_dir.glob("*.s")):
            if p.is_file():
                text = p.read_text(errors="replace")
                if pattern.search(text):
                    return p, False

    sys.exit(f"error: function '{func}' not found in segment '{segment}'")


def find_referenced_rodata(segment: str, func_asm: str) -> list[Path]:
    """Find any .rodata.s files in the segment referenced by func_asm."""
    if segment == "boot":
        rodata_dir = Path("asm/data")
    else:
        rodata_dir = Path(f"asm/{segment}/data")

    if not rodata_dir.is_dir():
        return []

    func_tokens = set(re.findall(r"\b\w+\b", func_asm))
    matching_rodata = []

    for rodata_file in sorted(rodata_dir.glob("*.rodata.s")):
        rodata_text = rodata_file.read_text(errors="replace")
        rodata_labels = set(re.findall(r"\bdlabel\s+(\w+)\b", rodata_text))
        if rodata_labels & func_tokens:
            matching_rodata.append(rodata_file)

    return matching_rodata


def main() -> None:
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        usage="tools/dk python3 tools/m2c.py [-s SEGMENT] FUNC [extra m2c args]",
    )
    parser.add_argument(
        "-s",
        "--segment",
        default="boot",
        help=f"Segment name: boot (default), global, or overlay ({', '.join(VALID_SEGMENTS[2:])})",
    )
    parser.add_argument("func", metavar="FUNC", help="Function name to decompile")

    args, extra_m2c_args = parser.parse_known_args()
    segment = args.segment.lower()
    if segment not in VALID_SEGMENTS:
        sys.exit(
            f"error: unknown segment '{args.segment}'. Valid segments: {', '.join(VALID_SEGMENTS)}"
        )

    # Resolve m2c binary
    m2c_path = os.environ.get("M2C_PATH", M2C_DEFAULT_PATH)
    m2c_bin = shutil.which(m2c_path) or (Path(m2c_path) if Path(m2c_path).exists() else None)
    if not m2c_bin:
        m2c_bin = shutil.which("m2c.py") or shutil.which("m2c")
    if not m2c_bin:
        sys.exit(
            f"error: m2c not found at {m2c_path}. Run via tools/dk or set M2C_PATH."
        )

    # Locate asm file
    target_asm, is_nonmatching = locate_function_asm(segment, args.func)

    # Extract function asm for rodata checking
    if is_nonmatching:
        func_asm = target_asm.read_text(errors="replace")
    else:
        whole_text = target_asm.read_text(errors="replace")
        func_asm = extract_function_asm(whole_text, args.func)

    # Check for rodata references
    rodata_files = find_referenced_rodata(segment, func_asm)

    # Generate C context
    ctx_path = generate_context()

    # Build m2c command
    cmd: list[str] = [
        sys.executable,
        str(m2c_bin),
        "--target",
        "mips-ido-c",
        "--context",
        str(ctx_path),
    ]

    has_function_arg = any(arg in ("-f", "--function") or arg.startswith("--function=") for arg in extra_m2c_args)
    if not is_nonmatching and not has_function_arg:
        cmd.extend(["--function", args.func])

    cmd.append(str(target_asm))
    cmd.extend(str(p) for p in rodata_files)
    cmd.extend(extra_m2c_args)

    proc = subprocess.run(cmd)
    sys.exit(proc.returncode)


if __name__ == "__main__":
    main()
