#!/usr/bin/env python3
"""DK64 Emulator Function Coverage Tool.

Measures dynamic function execution coverage using GDB breakpoints.
Subcommands:
  run LABEL [--seconds S] [--inputs FILE] [--name N] [--batch-size B]
  index
  where FUNC
  diff LABEL_A LABEL_B
  summary [--label LABEL]
"""

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import threading
import time
from typing import Any, Dict, List, Optional, Set, Tuple

SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
COVERAGE_DIR = REPO_ROOT / "emu" / "coverage"
COVERAGE_DIR.mkdir(parents=True, exist_ok=True)

sys.path.insert(0, str(SCRIPT_DIR))
import emu
import states
import symbols


def parse_inputs_file(path: Path) -> List[Tuple[str, float, str]]:
    """Parse a simple input script file.
    Lines can be:
      wait <seconds>
      press <buttons> [ms]
      hold <buttons>
      release <buttons>
    Returns list of (action, param_float_or_ms, buttons_str).
    """
    commands = []
    with open(path, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split(maxsplit=2)
            cmd = parts[0].lower()
            if cmd == "wait":
                sec = float(parts[1]) if len(parts) > 1 else 1.0
                commands.append(("wait", sec, ""))
            elif cmd == "press":
                btns = parts[1] if len(parts) > 1 else "start"
                ms = int(parts[2]) if len(parts) > 2 else 100
                commands.append(("press", float(ms), btns))
            elif cmd == "hold":
                btns = parts[1] if len(parts) > 1 else ""
                commands.append(("hold", 0.0, btns))
            elif cmd == "release":
                btns = parts[1] if len(parts) > 1 else ""
                commands.append(("release", 0.0, btns))
    return commands


def run_input_worker(session: str, commands: List[Tuple[str, float, str]], stop_event: threading.Event):
    """Worker thread that dispatches inputs while coverage runs."""
    for action, val, btns in commands:
        if stop_event.is_set():
            break
        try:
            if action == "wait":
                # Sleep in short increments to respond to stop_event
                deadline = time.time() + val
                while time.time() < deadline:
                    if stop_event.is_set():
                        return
                    time.sleep(0.05)
            elif action == "press":
                emu.cmd_press(argparse.Namespace(name=session, buttons=btns, ms=int(val)))
            elif action == "hold":
                emu.cmd_hold(argparse.Namespace(name=session, buttons=btns))
            elif action == "release":
                emu.cmd_release(argparse.Namespace(name=session, buttons=btns))
        except Exception:
            pass


def cmd_run(args: argparse.Namespace) -> int:
    """Run coverage collection on a given state."""
    label = args.label
    duration = float(args.seconds)
    session = args.name
    batch_size = getattr(args, "batch_size", 0)

    # 1. Ensure state exists
    bs_file = states.LIBRARY_DIR / f"{label}.bs"
    if not bs_file.exists():
        print(f"Error: State '{label}' not found in library ({bs_file})", file=sys.stderr)
        return 1

    c_name = emu.container_name(session)

    # 2. Start or load session at state
    if not emu.is_container_running(c_name):
        print(f"Starting session '{session}' at state '{label}'...")
        res = states.cmd_load(argparse.Namespace(label=label, name=session, vnc_port=None))
        if res != 0:
            return res
    else:
        print(f"Loading state '{label}' into running session '{session}'...")
        res = states.cmd_load(argparse.Namespace(label=label, name=session, vnc_port=None))
        if res != 0:
            return res

    time.sleep(0.5)

    # 3. Setup optional input script runner
    input_thread = None
    stop_event = threading.Event()
    if args.inputs:
        inputs_path = Path(args.inputs).resolve()
        if not inputs_path.exists():
            print(f"Error: Inputs file not found: {inputs_path}", file=sys.stderr)
            return 1
        commands = parse_inputs_file(inputs_path)
        print(f"Loaded {len(commands)} input script actions from {inputs_path}")
        input_thread = threading.Thread(
            target=run_input_worker,
            args=(session, commands, stop_event),
            daemon=True
        )
        input_thread.start()

    # 4. Run in-container coverage script via gdb-multiarch
    out_json = COVERAGE_DIR / f"{label}.json"
    container_out = f"/dk64/emu/coverage/{label}.json"

    print(f"Running GDB coverage collector ({duration}s, batch_size={batch_size})...")
    gdb_cmd = [
        "docker", "exec",
        "-e", f"GDB_PORT={emu.GDB_PORT}",
        "-e", f"COV_LABEL={label}",
        "-e", f"COV_DURATION={duration}",
        "-e", f"COV_OUTPUT={container_out}",
    ]
    if batch_size > 0:
        gdb_cmd.extend([
            "-e", "COV_BATCH_MIN=0",
            "-e", f"COV_BATCH_MAX={batch_size}",
        ])

    gdb_cmd.extend([
        c_name,
        "gdb-multiarch", "-batch",
        "-x", "/dk64/tools/emu/container/coverage_gdb.py"
    ])

    t0 = time.time()
    try:
        proc = subprocess.run(gdb_cmd, text=True)
    finally:
        stop_event.set()
        if input_thread:
            input_thread.join(timeout=1.0)

    t_wall = time.time() - t0
    if proc.returncode != 0:
        print(f"Error running coverage collector (exit {proc.returncode})", file=sys.stderr)
        return proc.returncode

    if not out_json.exists():
        print(f"Error: Coverage output JSON was not produced at {out_json}", file=sys.stderr)
        return 1

    # Load and display summary
    with open(out_json, "r") as f:
        data = json.load(f)

    hits = data.get("hits", [])
    perf = data.get("performance", {})
    print("\n" + "=" * 60)
    print(f"COVERAGE RUN RESULTS: '{label}'")
    print("=" * 60)
    print(f"  Wall time:           {t_wall:.2f}s (emulated test: {duration}s)")
    print(f"  Functions monitored: {data.get('total_monitored')}")
    print(f"  Functions hit:       {len(hits)}")
    print(f"  Breakpoint set time: {perf.get('breakpoint_set_seconds')}s ({perf.get('ms_per_breakpoint_set')} ms/bp)")
    print(f"  Stops per second:    {perf.get('stops_per_second')}")

    # Breakdown by segment
    seg_counts: Dict[str, int] = {}
    named_count = 0
    func_count = 0
    for h in hits:
        seg = h.get("segment", "unknown")
        seg_counts[seg] = seg_counts.get(seg, 0) + 1
        name = h.get("name", "")
        if name.startswith("func_"):
            func_count += 1
        else:
            named_count += 1

    print("\nSegment Breakdown:")
    for seg, cnt in sorted(seg_counts.items()):
        print(f"  {seg:<15} {cnt:>5} hits")
    print(f"\nSymbol Breakdown:")
    print(f"  Named symbols:    {named_count:>5}")
    print(f"  func_* symbols:   {func_count:>5}")
    print(f"\nCoverage report saved to: {out_json}")
    return 0


def cmd_index(args: argparse.Namespace) -> int:
    """Build emu/coverage/index.json mapping function names to state labels."""
    index: Dict[str, List[str]] = {}
    label_summaries: Dict[str, Dict[str, Any]] = {}

    coverage_files = sorted(COVERAGE_DIR.glob("*.json"))
    coverage_files = [f for f in coverage_files if f.name != "index.json"]

    if not coverage_files:
        print("No coverage runs found in emu/coverage/.", file=sys.stderr)
        return 1

    for fpath in coverage_files:
        try:
            with open(fpath, "r") as f:
                data = json.load(f)
        except Exception:
            continue
        label = data.get("label", fpath.stem)
        hits = data.get("hits", [])
        label_summaries[label] = {
            "total_hits": len(hits),
            "initial_overlay": data.get("initial_overlay"),
            "duration_seconds": data.get("duration_seconds"),
        }
        for h in hits:
            name = h.get("name")
            if not name:
                continue
            if name not in index:
                index[name] = []
            if label not in index[name]:
                index[name].append(label)

    index_data = {
        "updated_at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "total_functions": len(index),
        "labels": label_summaries,
        "functions": index,
    }

    out_file = COVERAGE_DIR / "index.json"
    with open(out_file, "w") as f:
        json.dump(index_data, f, indent=2)

    print(f"Built coverage index at {out_file}:")
    print(f"  Total unique functions indexed: {len(index)}")
    print(f"  Runs indexed: {len(label_summaries)} ({', '.join(label_summaries.keys())})")
    return 0


def cmd_where(args: argparse.Namespace) -> int:
    """List states/labels that hit FUNC."""
    func_target = args.func
    index_file = COVERAGE_DIR / "index.json"

    if not index_file.exists():
        print("Coverage index not found. Building index...")
        cmd_index(argparse.Namespace())

    if not index_file.exists():
        print("Error: Could not load or build coverage index.", file=sys.stderr)
        return 1

    with open(index_file, "r") as f:
        index_data = json.load(f)

    funcs_map = index_data.get("functions", {})

    # If target is a hex address, resolve name
    matched_name = None
    if func_target.startswith("0x") or func_target.startswith("0X"):
        try:
            addr = int(func_target, 16)
            syms = symbols.load(REPO_ROOT)
            fn_info = syms.function_at(addr)
            if fn_info:
                matched_name = fn_info[0]
        except Exception:
            pass
    if not matched_name:
        matched_name = func_target

    matched_labels = funcs_map.get(matched_name)
    if not matched_labels:
        print(f"Function '{matched_name}' was NOT hit in any indexed coverage run.")
        return 0

    print(f"Function '{matched_name}' was hit in {len(matched_labels)} state(s):")
    # Show hit order & timing for each state
    for label in matched_labels:
        cov_file = COVERAGE_DIR / f"{label}.json"
        hit_info = ""
        if cov_file.exists():
            try:
                with open(cov_file, "r") as f:
                    cdata = json.load(f)
                for h in cdata.get("hits", []):
                    if h.get("name") == matched_name:
                        hit_info = f" (hit #{h.get('order')} at {h.get('time')}s in {h.get('segment')})"
                        break
            except Exception:
                pass
        print(f"  - {label}{hit_info}")
    return 0


def cmd_diff(args: argparse.Namespace) -> int:
    """Compare functions hit in LABEL_A vs LABEL_B."""
    file_a = COVERAGE_DIR / f"{args.label_a}.json"
    file_b = COVERAGE_DIR / f"{args.label_b}.json"

    if not file_a.exists():
        print(f"Error: Coverage file for '{args.label_a}' not found: {file_a}", file=sys.stderr)
        return 1
    if not file_b.exists():
        print(f"Error: Coverage file for '{args.label_b}' not found: {file_b}", file=sys.stderr)
        return 1

    with open(file_a, "r") as f:
        data_a = json.load(f)
    with open(file_b, "r") as f:
        data_b = json.load(f)

    hits_a = {h["name"]: h for h in data_a.get("hits", [])}
    hits_b = {h["name"]: h for h in data_b.get("hits", [])}

    names_a = set(hits_a.keys())
    names_b = set(hits_b.keys())

    both = sorted(names_a & names_b)
    only_a = sorted(names_a - names_b)
    only_b = sorted(names_b - names_a)

    print(f"Coverage Diff: '{args.label_a}' ({len(names_a)} hits) vs '{args.label_b}' ({len(names_b)} hits)")
    print("-" * 70)
    print(f"  Common to both:       {len(both):>5}")
    print(f"  Only in '{args.label_a}': {len(only_a):>5}")
    print(f"  Only in '{args.label_b}': {len(only_b):>5}")
    print("-" * 70)

    if only_a:
        print(f"\nFunctions only in '{args.label_a}' (first 25):")
        for fn in only_a[:25]:
            h = hits_a[fn]
            print(f"  {fn:<30} ({h.get('segment')}) at {h.get('time')}s")
        if len(only_a) > 25:
            print(f"  ... and {len(only_a) - 25} more")

    if only_b:
        print(f"\nFunctions only in '{args.label_b}' (first 25):")
        for fn in only_b[:25]:
            h = hits_b[fn]
            print(f"  {fn:<30} ({h.get('segment')}) at {h.get('time')}s")
        if len(only_b) > 25:
            print(f"  ... and {len(only_b) - 25} more")

    return 0


def cmd_summary(args: argparse.Namespace) -> int:
    """Print coverage summary by segment and named vs splat functions."""
    syms = symbols.load(REPO_ROOT)
    total_funcs_by_seg: Dict[str, int] = {}
    for seg in symbols.SEGMENTS:
        try:
            total_funcs_by_seg[seg] = len(syms.functions(seg))
        except Exception:
            pass

    if args.label:
        # Summary for a single label
        cov_file = COVERAGE_DIR / f"{args.label}.json"
        if not cov_file.exists():
            print(f"Error: Coverage file '{cov_file}' not found.", file=sys.stderr)
            return 1
        with open(cov_file, "r") as f:
            runs_data = [json.load(f)]
        title = f"Coverage Summary for '{args.label}'"
    else:
        # Aggregate across all runs
        files = [f for f in COVERAGE_DIR.glob("*.json") if f.name != "index.json"]
        if not files:
            print("No coverage runs found.", file=sys.stderr)
            return 1
        runs_data = []
        for fpath in files:
            try:
                with open(fpath, "r") as f:
                    runs_data.append(json.load(f))
            except Exception:
                pass
        title = f"Overall Aggregate Coverage ({len(runs_data)} runs)"

    # Aggregate hits
    unique_hits: Dict[str, Dict[str, Any]] = {}
    for r in runs_data:
        for h in r.get("hits", []):
            name = h.get("name")
            if name and name not in unique_hits:
                unique_hits[name] = h

    seg_hits: Dict[str, int] = {}
    named_hits = 0
    func_hits = 0

    for name, h in unique_hits.items():
        seg = h.get("segment", "unknown")
        seg_hits[seg] = seg_hits.get(seg, 0) + 1
        if name.startswith("func_"):
            func_hits += 1
        else:
            named_hits += 1

    print("\n" + "=" * 65)
    print(title)
    print("=" * 65)
    print(f"{'Segment':<16} {'Hits':<10} {'Total':<10} {'Coverage %':<12}")
    print("-" * 65)

    all_segs = sorted(set(list(total_funcs_by_seg.keys()) + list(seg_hits.keys())))
    total_hit_all = 0
    total_funcs_all = 0

    for seg in all_segs:
        hits_cnt = seg_hits.get(seg, 0)
        tot = total_funcs_by_seg.get(seg, 0)
        total_hit_all += hits_cnt
        total_funcs_all += tot
        pct_str = f"{(hits_cnt / tot * 100):.1f}%" if tot > 0 else "-"
        print(f"{seg:<16} {hits_cnt:<10} {tot:<10} {pct_str:<12}")

    print("-" * 65)
    pct_total = f"{(total_hit_all / total_funcs_all * 100):.1f}%" if total_funcs_all > 0 else "-"
    print(f"{'Total':<16} {total_hit_all:<10} {total_funcs_all:<10} {pct_total:<12}")

    print("\nSymbol Breakdown:")
    print(f"  Named C functions:    {named_hits:>5} ({named_hits/(named_hits+func_hits)*100:.1f}%)" if (named_hits+func_hits) else "  Named C functions: 0")
    print(f"  Unmatched func_*:     {func_hits:>5} ({func_hits/(named_hits+func_hits)*100:.1f}%)" if (named_hits+func_hits) else "  Unmatched func_*: 0")
    print("=" * 65)
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description="DK64 Emulator Function Coverage Tool", prog="tools/emu/coverage.py")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # run
    p_run = subparsers.add_parser("run", help="Run coverage collection on a saved state")
    p_run.add_argument("label", help="State label to run coverage on")
    p_run.add_argument("--seconds", type=float, default=20.0, help="Run duration in seconds (default: 20)")
    p_run.add_argument("--inputs", default=None, help="Path to scripted input file")
    p_run.add_argument("--name", default=emu.DEFAULT_SESSION, help="Session name (default: main)")
    p_run.add_argument("--batch-size", type=int, default=0, help="Optional batch size (0 = all at once)")
    p_run.set_defaults(handler=cmd_run)

    # index
    p_idx = subparsers.add_parser("index", help="Build function-to-state coverage index")
    p_idx.set_defaults(handler=cmd_index)

    # where
    p_where = subparsers.add_parser("where", help="List states where a function was hit")
    p_where.add_argument("func", help="Function name (or hex address)")
    p_where.set_defaults(handler=cmd_where)

    # diff
    p_diff = subparsers.add_parser("diff", help="Diff coverage between two states")
    p_diff.add_argument("label_a", help="First state label")
    p_diff.add_argument("label_b", help="Second state label")
    p_diff.set_defaults(handler=cmd_diff)

    # summary
    p_sum = subparsers.add_parser("summary", help="Show coverage statistics")
    p_sum.add_argument("--label", default=None, help="Optional state label to summarize (default: all)")
    p_sum.set_defaults(handler=cmd_summary)

    args = parser.parse_args()
    return args.handler(args)


if __name__ == "__main__":
    sys.exit(main())
