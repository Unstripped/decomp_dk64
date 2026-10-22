#!/usr/bin/env python3
"""DK64 Function Study Tool.

Traces function execution in the emulator, inspecting incoming register arguments ($a0-$a3),
callers ($ra), stack ($sp), dereferencing RDRAM pointer arguments (0x80 bytes),
capturing return values ($v0, $v1, $f0), watching memory mutations, and capturing screenshots.

Usage:
  study.py FUNC_OR_ADDR [--state LABEL] [--hits K] [--segment S] [--watch ADDR[:LEN]] [--name N]
Outputs:
  emu/study/<FUNC>/report.md
  emu/study/<FUNC>/screenshot.png
  emu/study/<FUNC>/data.json
"""

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import time
from typing import Any, Dict, List, Optional, Tuple

SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
STUDY_DIR = REPO_ROOT / "emu" / "study"
STUDY_DIR.mkdir(parents=True, exist_ok=True)

sys.path.insert(0, str(SCRIPT_DIR))
import emu
import states
import symbols


def resolve_target(func_or_addr: str, segment: Optional[str] = None) -> Tuple[str, int, str]:
    """Resolve target name, entry address, and segment."""
    syms = symbols.load(REPO_ROOT)
    
    # Check if hex address
    if func_or_addr.startswith("0x") or func_or_addr.startswith("0X"):
        addr = int(func_or_addr, 16)
        fn_info = syms.function_at(addr, segment=segment)
        if not fn_info:
            raise ValueError(f"No known function at address 0x{addr:08x} (segment={segment or 'auto'})")
        name, start_addr, size, seg = fn_info
        return name, start_addr, seg

    # Look up by symbol name
    name = func_or_addr
    lookup_res = syms.lookup(name, segment=segment)
    if not lookup_res:
        raise ValueError(f"Unknown symbol '{name}' (segment={segment or 'auto'})")
    entry_addr, seg = lookup_res
    return name, entry_addr, seg


def pick_state_for_func(func_name: str) -> Optional[str]:
    """Choose a state from coverage index where func_name was hit."""
    idx_file = REPO_ROOT / "emu" / "coverage" / "index.json"
    if idx_file.exists():
        try:
            with open(idx_file, "r") as f:
                data = json.load(f)
            funcs_map = data.get("functions", {})
            if func_name in funcs_map and funcs_map[func_name]:
                return funcs_map[func_name][0]
        except Exception:
            pass

    # Fallback to checking library states
    lib_dir = states.LIBRARY_DIR
    if (lib_dir / "title.bs").exists():
        return "title"
    if (lib_dir / "intro.bs").exists():
        return "intro"
    
    # Pick any available state
    bs_files = list(lib_dir.glob("*.bs"))
    if bs_files:
        return bs_files[0].stem
    return None


def generate_markdown_report(data: Dict[str, Any], report_path: Path) -> str:
    """Generate Markdown report from study JSON data."""
    target_name = data.get("target_name")
    target_addr = data.get("target_address")
    target_seg = data.get("target_segment")
    hits = data.get("hits", [])
    has_screenshot = (report_path.parent / "screenshot.png").exists()

    md = []
    md.append(f"# Function Study: `{target_name}`\n")
    md.append(f"- **Address:** `{target_addr}`")
    md.append(f"- **Segment:** `{target_seg}`")
    md.append(f"- **Recorded Hits:** {len(hits)}")
    md.append(f"- **Timestamp:** {time.strftime('%Y-%m-%d %H:%M:%S UTC', time.gmtime())}\n")

    if has_screenshot:
        md.append("## Screen at First Invocation\n")
        md.append("![Screen at first hit](screenshot.png)\n")

    md.append("## Invocation Summary\n")
    md.append("| Hit | Time | Caller ($ra) | Arguments ($a0-$a3) | Return Value ($v0) |")
    md.append("|---|---|---|---|---|")
    for h in hits:
        hit_num = h["hit"]
        t = f"{h['time_offset']}s"
        caller = h["caller"]["symbol"]
        regs = h["registers"]
        args_str = f"`{regs['a0']}`, `{regs['a1']}`, `{regs['a2']}`, `{regs['a3']}`"
        ret = h.get("return_value", {})
        ret_v0 = ret.get("v0") or "-"
        if ret.get("f0") is not None:
            ret_str = f"`{ret_v0}` (float `$f0`: `{ret['f0']}`)"
        else:
            ret_str = f"`{ret_v0}`"
            if ret.get("v0_dec") is not None:
                ret_str += f" ({ret['v0_dec']})"
        md.append(f"| #{hit_num} | {t} | `{caller}` | {args_str} | {ret_str} |")
    md.append("")

    md.append("## Detailed Call Traces\n")
    for h in hits:
        hit_num = h["hit"]
        regs = h["registers"]
        ret = h.get("return_value", {})
        md.append(f"### Hit #{hit_num} (at +{h['time_offset']}s)\n")
        md.append(f"- **Caller:** `{h['caller']['symbol']}` (`{h['caller']['address']}`)")
        md.append(f"- **Stack Pointer:** `{regs['sp']}`")
        md.append(f"- **Return Value:** `$v0` = `{ret.get('v0')}` ({ret.get('v0_dec')}), `$v1` = `{ret.get('v1')}`")
        if ret.get("f0") is not None:
            md.append(f"- **Float Return ($f0):** `{ret.get('f0')}`")

        # Pointer dumps
        ptrs = h.get("rdram_pointers", {})
        if ptrs:
            md.append("\n#### Dereferenced Pointer Arguments (0x80 bytes):\n")
            for arg_k, pinfo in ptrs.items():
                paddr = pinfo.get("pointer")
                md.append(f"**Argument `${arg_k}`** (`{paddr}`):\n")
                if "hex_dump" in pinfo:
                    md.append("```text")
                    md.append(pinfo["hex_dump"])
                    md.append("```\n")
                elif "error" in pinfo:
                    md.append(f"*Error reading memory:* `{pinfo['error']}`\n")

        # Memory Watch
        watch = h.get("watch")
        if watch:
            wb = watch.get("before")
            wa = watch.get("after")
            changed = watch.get("changed", False)
            md.append(f"\n#### Watched Memory Mutation ({'MODIFIED' if changed else 'UNCHANGED'}):\n")
            if wb and "hex_dump" in wb:
                md.append("**Before Call:**")
                md.append("```text")
                md.append(wb["hex_dump"])
                md.append("```")
            if wa and "hex_dump" in wa:
                md.append("**After Call:**")
                md.append("```text")
                md.append(wa["hex_dump"])
                md.append("```\n")

        md.append("")

    content = "\n".join(md)
    with open(report_path, "w") as f:
        f.write(content)
    return content


def main() -> int:
    parser = argparse.ArgumentParser(description="DK64 Function Study Tool", prog="tools/emu/study.py")
    parser.add_argument("func", help="Function symbol name or hex entry address (e.g. controllerUpdate or 0x8060AC7C)")
    parser.add_argument("--state", default=None, help="State label to load (chosen from coverage index if omitted)")
    parser.add_argument("--hits", type=int, default=3, help="Max invocation hits to capture (default: 3)")
    parser.add_argument("--segment", default=None, help="Optional segment disambiguation (boot, global, or overlay)")
    parser.add_argument("--watch", default=None, help="Optional address[:length] to watch for memory mutation (e.g. 0x8076A0A8:4)")
    parser.add_argument("--name", default=emu.DEFAULT_SESSION, help="Session name (default: main)")

    args = parser.parse_args()

    # 1. Resolve function
    try:
        fn_name, entry_addr, seg = resolve_target(args.func, segment=args.segment)
    except Exception as e:
        print(f"Error resolving target: {e}", file=sys.stderr)
        return 1

    print(f"Target function: {fn_name} (0x{entry_addr:08x}) in {seg}")
    if entry_addr in {a for _, a in symbols.load(REPO_ROOT).fallthrough_entries(seg)}:
        print(f"Error: {fn_name} is a fall-through split (the previous function runs into it), not a call "
              "target; a breakpoint there wedges ares's GDB stub. Study the function before it.", file=sys.stderr)
        return 1

    # 2. Resolve state
    state_label = args.state
    if not state_label:
        index_key = fn_name if seg in ("boot", "global") else f"{seg}:{fn_name}"  # matches coverage.hit_key
        state_label = pick_state_for_func(index_key)
        if not state_label:
            print(f"Error: Function '{fn_name}' not found in coverage index and no --state given.", file=sys.stderr)
            print("Please specify --state <LABEL> explicitly.", file=sys.stderr)
            return 1
        print(f"Selected state from coverage index: '{state_label}'")

    bs_file = states.LIBRARY_DIR / f"{state_label}.bs"
    if not bs_file.exists():
        print(f"Error: State '{state_label}' not found in library ({bs_file})", file=sys.stderr)
        return 1

    # 3. Parse watch parameter
    watch_addr_str = None
    watch_len = 16
    if args.watch:
        if ":" in args.watch:
            parts = args.watch.split(":", 1)
            watch_addr_str = parts[0]
            watch_len = int(parts[1], 0)
        else:
            watch_addr_str = args.watch

    # 4. Prepare target directory
    target_study_dir = STUDY_DIR / fn_name
    target_study_dir.mkdir(parents=True, exist_ok=True)
    out_json = target_study_dir / "data.json"
    screenshot_file = target_study_dir / "screenshot.png"
    report_file = target_study_dir / "report.md"

    container_json = f"/dk64/emu/study/{fn_name}/data.json"
    container_screenshot = f"/dk64/emu/study/{fn_name}/screenshot.png"

    # 5. Load or start session at target state
    session = args.name
    c_name = emu.container_name(session)
    if not emu.is_container_running(c_name):
        print(f"Starting session '{session}' at state '{state_label}'...")
        res = states.cmd_load(argparse.Namespace(label=state_label, name=session, vnc_port=None))
        if res != 0:
            return res
    else:
        print(f"Loading state '{state_label}' into running session '{session}'...")
        res = states.cmd_load(argparse.Namespace(label=state_label, name=session, vnc_port=None))
        if res != 0:
            return res

    time.sleep(0.5)

    # 6. Run study_gdb.py inside container
    print(f"Running GDB function study on {fn_name} for up to {args.hits} hits...")
    gdb_cmd = [
        "docker", "exec",
        "-e", f"GDB_PORT={emu.GDB_PORT}",
        "-e", f"STUDY_TARGET_ADDR={hex(entry_addr)}",
        "-e", f"STUDY_TARGET_NAME={fn_name}",
        "-e", f"STUDY_TARGET_SEG={seg}",
        "-e", f"STUDY_MAX_HITS={args.hits}",
        "-e", f"STUDY_OUTPUT_JSON={container_json}",
        "-e", f"STUDY_SCREENSHOT={container_screenshot}",
    ]
    if watch_addr_str:
        gdb_cmd.extend([
            "-e", f"STUDY_WATCH_ADDR={watch_addr_str}",
            "-e", f"STUDY_WATCH_LEN={watch_len}",
        ])

    gdb_cmd.extend([
        c_name,
        "gdb-multiarch", "-batch",
        "-x", "/dk64/tools/emu/container/study_gdb.py",
    ])

    proc = subprocess.run(gdb_cmd, text=True)
    if proc.returncode != 0:
        print(f"Error running study script (exit {proc.returncode})", file=sys.stderr)
        return proc.returncode

    if not out_json.exists():
        print(f"Error: Study data JSON not created at {out_json}", file=sys.stderr)
        return 1

    with open(out_json, "r") as f:
        study_data = json.load(f)

    # 7. Generate markdown report
    generate_markdown_report(study_data, report_file)
    print("\n" + "=" * 60)
    print(f"STUDY REPORT GENERATED: {fn_name}")
    print("=" * 60)
    print(f"  Target:     {fn_name} (0x{entry_addr:08x}) [{seg}]")
    print(f"  State:      {state_label}")
    print(f"  Hits:       {len(study_data.get('hits', []))}")
    print(f"  Report:     {report_file}")
    if screenshot_file.exists():
        print(f"  Screenshot: {screenshot_file}")
    print("=" * 60)
    return 0


if __name__ == "__main__":
    sys.exit(main())
