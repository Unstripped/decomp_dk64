#!/usr/bin/env python3
"""DK64 function probe: what does one function do to the game?

Stops the emulator at a natural call of FUNC (real caller, arguments, stack and
registers), saves that instant as an ares save state while GDB holds the CPU, then
replays experiments from it:

  baseline   run unchanged to FUNC's return, then --frames game frames
  control    baseline again: bytes that differ between the two are run-to-run noise
  skip       return immediately from FUNC ($v0 = --ret), then --frames frames
  args       overwrite $a0-$a3 (--arg a0=0x10 ...), run to return, then --frames frames

and reports
  - the call's own effect: RAM changed between entry and return (baseline), with data
    symbols, plus return values and (--callees) every function first entered during it;
  - the knock-out / argument effect: RAM and screen differences against the baseline
    after --frames frames, minus control noise, and whether the game faulted or stalled.

Arguments are only what is valid at a function entry: the checkpoint is the real call,
so pointers in $a0-$a3 are live; --arg replaces scalars. Nothing builds a synthetic call
frame. Slot 9 of the session is reserved for the checkpoint.

Usage:
  probe.py FUNC... [--list FILE] [--segment S] [--state LABEL] [--hit K] [--wait S] [--return-timeout S]
           [--frames N] [--ret V] [--arg aN=VAL ...] [--no-skip] [--callees] [--summary PATH] [--name SESSION]
Outputs:
  emu/probe/<seg>_<FUNC>/report.md, data.json, <experiment>/{after.png,result.json,...}
  emu/probe/summary.{md,json} for two or more functions (one row each; errors do not stop the batch)
"""

import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys
import time
from typing import Dict, List, Optional, Set, Tuple

SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
PROBE_DIR = REPO_ROOT / "emu" / "probe"
CHECKPOINT_SLOT = 9
RDRAM_BASE = 0x80000000
PAGE = 4096
STACK_WINDOW = 0x8000  # bytes below the caller's $sp treated as dead callee frames

sys.path.insert(0, str(SCRIPT_DIR))
import emu
import states
import symbols
from study import pick_state_for_func, resolve_target


def container_path(p: Path) -> str:
    return "/dk64/" + str(p.relative_to(REPO_ROOT))


def slot_file(session: str) -> Path:
    return emu.get_session_states_dir(session) / f"baserom.us.bs{CHECKPOINT_SLOT}"


def run_phase(session: str, env: Dict[str, str], out_dir: Path, host_action, wait_ready: float) -> dict:
    """Run one probe_gdb.py phase; perform host_action (save/load slot) at the handshake."""
    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True)
    cmd = ["docker", "exec", "-e", f"GDB_PORT={emu.GDB_PORT}", "-e", f"PROBE_DIR={container_path(out_dir)}"]
    for k, v in env.items():
        cmd += ["-e", f"{k}={v}"]
    cmd += [emu.container_name(session), "gdb-multiarch", "-batch", "-x", "/dk64/tools/emu/container/probe_gdb.py"]
    log = open(out_dir / "gdb.log", "w")
    proc = subprocess.Popen(cmd, stdout=log, stderr=subprocess.STDOUT, text=True)
    ready = out_dir / "ready.flag"
    deadline = time.time() + wait_ready
    while not ready.exists() and proc.poll() is None and time.time() < deadline:
        time.sleep(0.05)
    if ready.exists():
        host_action()
        (out_dir / "go.flag").write_text("1")
    else:
        proc.kill()
    proc.wait()
    log.close()
    result_file = out_dir / "result.json"
    if not result_file.exists():
        return {"status": "error", "error": f"no result (see {out_dir / 'gdb.log'})"}
    return json.loads(result_file.read_text())


def save_checkpoint(session: str):
    target = slot_file(session)
    before = target.stat().st_mtime if target.exists() else 0
    emu.cmd_savestate(argparse.Namespace(name=session, slot=CHECKPOINT_SLOT))
    deadline = time.time() + 10
    while time.time() < deadline:
        if target.exists() and target.stat().st_mtime > before:
            time.sleep(0.5)  # let ares finish writing
            return
        time.sleep(0.1)
    raise RuntimeError(f"ares did not write {target}")


def load_checkpoint(session: str):
    emu.cmd_loadstate(argparse.Namespace(name=session, slot=CHECKPOINT_SLOT))
    time.sleep(1.0)  # the load is applied by ares's UI loop, not synchronously


def diff_offsets(a: bytes, b: bytes) -> Set[int]:
    out = set()
    for off in range(0, len(a), PAGE):
        if a[off:off + PAGE] != b[off:off + PAGE]:
            out.update(j for j in range(off, off + PAGE) if a[j] != b[j])
    return out


def to_ranges(offsets: Set[int], gap: int = 8) -> List[Tuple[int, int]]:
    """Merge byte offsets into [start, end) ranges, joining gaps up to `gap` bytes."""
    ranges: List[List[int]] = []
    for o in sorted(offsets):
        if ranges and o - ranges[-1][1] <= gap:
            ranges[-1][1] = o + 1
        else:
            ranges.append([o, o + 1])
    return [(s, e) for s, e in ranges]


def describe(ranges, before: bytes, after: bytes, syms, seg: Optional[str], limit: int) -> List[dict]:
    rows = []
    for s, e in sorted(ranges, key=lambda r: r[0] - r[1])[:limit]:
        addr = RDRAM_BASE + s
        data_seg = seg if symbols.OVERLAY_VRAM_START <= addr < symbols.GLOBAL_VRAM_START else None
        d = syms.data_at(addr, segment=data_seg)
        row = {"address": f"0x{addr:08x}", "size": e - s,
               "symbol": f"{d[0]}+0x{d[2]:x}" if d else None}
        if e - s <= 16:
            row["before"] = before[s:e].hex()
            row["after"] = after[s:e].hex()
        rows.append(row)
    return sorted(rows, key=lambda r: r["address"])


def pixel_diff(session: str, a: Path, b: Path, diff: Optional[Path] = None) -> Optional[int]:
    """Changed-pixel count between two screenshots; `diff` gets a red-on-white change map."""
    if not (a.exists() and b.exists()):
        return None
    res = subprocess.run(["docker", "exec", emu.container_name(session), "compare", "-metric", "AE",
                          "-compose", "src", "-highlight-color", "red",
                          container_path(a), container_path(b), container_path(diff) if diff else "null:"],
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    try:
        return int(float(res.stderr.strip().split()[0]))
    except (ValueError, IndexError):
        return None


def table(rows: List[dict]) -> List[str]:
    md = ["| Address | Size | Symbol | Before | After |", "|---|---|---|---|---|"]
    for r in rows:
        md.append(f"| `{r['address']}` | {r['size']} | {('`' + r['symbol'] + '`') if r['symbol'] else ''} "
                  f"| {('`' + r['before'] + '`') if 'before' in r else ''} | {('`' + r['after'] + '`') if 'after' in r else ''} |")
    return md


class ProbeError(Exception):
    pass


def probe_one(func: str, args: argparse.Namespace) -> dict:
    """Checkpoint, experiments, comparison and report for one function; returns a summary row."""
    try:
        name, addr, seg = resolve_target(func, segment=args.segment)
    except ValueError as e:
        raise ProbeError(str(e))
    syms = symbols.load(REPO_ROOT)
    if addr in {a for _, a in syms.fallthrough_entries(seg)}:
        raise ProbeError(f"{name} is a fall-through split, not a call target; probe the function before it")

    state = args.state or pick_state_for_func(name if seg in ("boot", "global") else f"{seg}:{name}")
    if not state or not (states.LIBRARY_DIR / f"{state}.bs").exists():
        raise ProbeError("no library state; pass --state LABEL")

    out = PROBE_DIR / f"{seg}_{name}"
    out.mkdir(parents=True, exist_ok=True)
    print(f"Probing {name} (0x{addr:08x}, {seg}) from state '{state}', call #{args.hit}, {args.frames} frames after")

    session = args.name
    if states.cmd_load(argparse.Namespace(label=state, name=session, vnc_port=None)) != 0:
        raise ProbeError(f"could not load state '{state}'")
    time.sleep(1.0)

    base_env = {"PROBE_ADDR": hex(addr), "PROBE_SEG": seg, "PROBE_FRAMES": str(args.frames),
                "PROBE_RETURN_TIMEOUT": str(args.return_timeout)}

    # 1. Checkpoint at the natural entry.
    cp = run_phase(session, {**base_env, "PROBE_PHASE": "checkpoint", "PROBE_HIT": str(args.hit),
                             "PROBE_HIT_TIMEOUT": str(args.wait)},
                   out / "checkpoint", lambda: save_checkpoint(session), wait_ready=args.wait + 60)
    if cp.get("status") != "ok":
        raise ProbeError(f"checkpoint failed: {cp}")
    (out / "checkpoint.json").write_text(json.dumps(cp, indent=2))
    regs = cp["registers"]
    print(f"  checkpoint: caller {cp['caller']}, a0-a3 {regs['a0']} {regs['a1']} {regs['a2']} {regs['a3']}")

    # 2. Experiments, each restarted from the checkpoint.
    experiments = [("baseline", {"PROBE_MODE": "observe", "PROBE_CALLEES": "1" if args.callees else "0"}),
                   ("control", {"PROBE_MODE": "observe"})]
    if not args.no_skip:
        experiments.append(("skip", {"PROBE_MODE": "skip", "PROBE_RET": args.ret}))
    if args.arg:
        experiments.append(("args", {"PROBE_MODE": "args", "PROBE_ARGS": ",".join(args.arg)}))

    results = {}
    for label, env in experiments:
        print(f"  running {label}...")
        results[label] = run_phase(session, {**base_env, "PROBE_PHASE": "experiment", **env},
                                   out / label, lambda: load_checkpoint(session), wait_ready=30)
        if results[label].get("status") != "ok":
            raise ProbeError(f"{label} failed: {results[label]}")
        if results[label].get("returned") is False:
            # No return within PROBE_RETURN_TIMEOUT: no ret.bin/after.bin to compare.
            (out / "data.json").write_text(json.dumps({"function": name, "checkpoint": cp, "experiments": results}, indent=2))
            raise ProbeError(f"{label}: {name} did not return within the timeout "
                             f"(callees so far: {len(results[label].get('callees', []))}); see {out / 'data.json'}")

    # 3. Compare.
    ram = lambda label, f: (out / label / f).read_bytes()
    entry = (out / "checkpoint" / "entry.bin").read_bytes()
    ovl = cp.get("overlay")
    report = {"function": name, "address": f"0x{addr:08x}", "segment": seg, "state": state,
              "hit": args.hit, "frames": args.frames, "checkpoint": cp, "experiments": results}

    base = results["baseline"]
    if base.get("returned"):
        # Below the caller's $sp lie only the dead frames of FUNC and its callees.
        sp = int(regs["sp"], 16) - RDRAM_BASE
        dead = range(sp - STACK_WINDOW, sp)
        call_all = diff_offsets(entry, ram("baseline", "ret.bin"))
        call_changes = {o for o in call_all if o not in dead}
        # Same bytes at return and same return registers in the control replay.
        deterministic = (ram("baseline", "ret.bin") == ram("control", "ret.bin")
                         and base["return"] == results["control"]["return"])
        report["call_effect"] = {
            "bytes": len(call_changes),
            "dead_stack_bytes": len(call_all) - len(call_changes),
            "deterministic": deterministic,
            "ranges": describe(to_ranges(call_changes), entry, ram("baseline", "ret.bin"), syms, ovl, args.limit),
        }
    after_base = ram("baseline", "after.bin")
    noise = diff_offsets(after_base, ram("control", "after.bin"))
    report["noise_bytes"] = len(noise)
    report["noise_pixels"] = pixel_diff(session, out / "baseline" / "after.png", out / "control" / "after.png")
    for label in ("skip", "args"):
        if label not in results:
            continue
        changed = diff_offsets(after_base, ram(label, "after.bin")) - noise
        report[f"{label}_effect"] = {
            "bytes": len(changed),
            "pixels": pixel_diff(session, out / "baseline" / "after.png", out / label / "after.png", out / label / "diff.png"),
            "ranges": describe(to_ranges(changed), after_base, ram(label, "after.bin"), syms, ovl, args.limit),
        }

    (out / "data.json").write_text(json.dumps(report, indent=2))

    # 4. Markdown report.
    md = [f"# Probe: `{name}` (`0x{addr:08x}`, {seg})", "",
          f"State `{state}`, call #{args.hit}; caller `{cp['caller']}`; frame counter {cp['frame_counter']}; "
          f"overlay {ovl or 'none'}.", "",
          "## Entry registers", "",
          "| " + " | ".join(["a0", "a1", "a2", "a3", "sp", "ra", "f12", "f14"]) + " |",
          "|" + "---|" * 8,
          "| " + " | ".join(f"`{regs[r]}`" for r in ["a0", "a1", "a2", "a3", "sp", "ra", "f12", "f14"]) + " |", ""]
    if "call_effect" in report:
        ce = report["call_effect"]
        r = base["return"]
        md += ["## Call effect (entry → return, baseline)", "",
               f"Returned `$v0={r['v0']}` `$v1={r['v1']}` `$f0={r['f0']}` in {base['call_seconds']} s wall; "
               f"{ce['bytes']} bytes changed (plus {ce['dead_stack_bytes']} in dead stack frames below the caller's "
               f"`$sp`, not listed); same in control run: {ce['deterministic']}.", ""]
        md += table(ce["ranges"]) + [""]
        if "callees" in base:
            md += [f"Functions first entered during the call ({len(base['callees'])}): "
                   + ", ".join(f"`{c['name']}`" for c in base["callees"]), ""]
    else:
        md += ["## Call effect", "", f"Did not return within the timeout (baseline: {base}).", ""]
    md += [f"## After {args.frames} frames", "",
           f"Run-to-run noise (baseline vs control): {report['noise_bytes']} bytes, {report['noise_pixels']} pixels.", ""]
    md += ["| Experiment | Frames run | Faulted thread | Changed bytes (minus noise) | Changed pixels |",
           "|---|---|---|---|---|"]
    for label in [l for l, _ in experiments]:
        a = results[label]["after"]
        eff = report.get(f"{label}_effect", {})
        md.append(f"| {label} | {a['frames_run']}/{a['frames_requested']} | `{a['faulted_thread']}` "
                  f"| {eff.get('bytes', '')} | {eff.get('pixels', '')} |")
    md.append("")
    for label in ("skip", "args"):
        if f"{label}_effect" in report:
            extra = f" (`$v0={args.ret}`)" if label == "skip" else f" ({', '.join(args.arg)})"
            md += [f"### {label}{extra}: RAM differences vs baseline", ""] + table(report[f"{label}_effect"]["ranges"]) + [""]
    md += ["Screens: " + ", ".join(f"`{l}/after.png`" for l, _ in experiments) + ", `checkpoint/entry.png`; "
           "change maps vs baseline: " + ", ".join(f"`{l}/diff.png`" for l in ("skip", "args") if l in results) + ".",
           "", "A skipped or altered call also shifts later random-number draws, so particles and other "
           "random effects can differ without being this function's work: check where `diff.png` is red.", ""]
    (out / "report.md").write_text("\n".join(md))

    print(f"Report: {out / 'report.md'}")
    ce = report.get("call_effect", {})
    sk = report.get("skip_effect", {})
    return {"function": name, "segment": seg, "status": "ok", "caller": cp["caller"],
            "returned": base.get("returned"), "call_bytes": ce.get("bytes"),
            "callees": len(base["callees"]) if "callees" in base else None,
            "noise_bytes": report["noise_bytes"], "skip_bytes": sk.get("bytes"), "skip_pixels": sk.get("pixels"),
            "skip_faulted": results["skip"]["after"]["faulted_thread"] != "0x00000000" if "skip" in results else None,
            "skip_stalled": not results["skip"]["after"]["completed"] if "skip" in results else None,
            "report": str(out.relative_to(REPO_ROOT) / "report.md")}


def main() -> int:
    ap = argparse.ArgumentParser(description="DK64 function probe", prog="tools/emu/probe.py")
    ap.add_argument("func", nargs="*", help="Function symbols or hex entry addresses")
    ap.add_argument("--list", default=None, help="File with one function per line (# comments allowed)")
    ap.add_argument("--segment", default=None, help="boot, global or overlay name (overlay functions)")
    ap.add_argument("--state", default=None, help="Library state (default: one where coverage saw FUNC)")
    ap.add_argument("--hit", type=int, default=1, help="Use the K-th call after the state loads (default 1)")
    ap.add_argument("--wait", type=float, default=60, help="Seconds to wait for the K-th call (default 60)")
    ap.add_argument("--return-timeout", type=float, default=30,
                    help="Seconds (wall) for the call to return before the function is reported as not returning (default 30)")
    ap.add_argument("--frames", type=int, default=30, help="Game frames to run after the call (default 30)")
    ap.add_argument("--ret", default="0", help="$v0 for the skip experiment (default 0)")
    ap.add_argument("--arg", action="append", default=[], help="Argument override aN=VAL for an 'args' experiment (repeatable)")
    ap.add_argument("--no-skip", action="store_true", help="Do not run the skip experiment")
    ap.add_argument("--callees", action="store_true", help="Record functions first entered during the call (~20 s to arm)")
    ap.add_argument("--limit", type=int, default=40, help="Largest changed ranges listed per comparison (default 40)")
    ap.add_argument("--summary", default=None, help="Batch summary path (default emu/probe/summary.md for 2+ functions)")
    ap.add_argument("--name", default=emu.DEFAULT_SESSION, help="Session name (default: main)")
    args = ap.parse_args()

    for a in args.arg:
        if "=" not in a or a.split("=", 1)[0] not in ("a0", "a1", "a2", "a3"):
            print(f"Error: --arg takes a0..a3=VALUE, got '{a}'", file=sys.stderr)
            return 1
    funcs = list(args.func)
    if args.list:
        for line in Path(args.list).read_text().splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                funcs.append(line)
    if not funcs:
        print("Error: give at least one function (or --list FILE)", file=sys.stderr)
        return 1

    rows = []
    for func in funcs:
        try:
            rows.append(probe_one(func, args))
        except ProbeError as e:
            print(f"Error: {func}: {e}", file=sys.stderr)
            rows.append({"function": func, "status": f"error: {e}"})
        except Exception as e:  # one broken target must not end the batch
            print(f"Error: {func}: {type(e).__name__}: {e}", file=sys.stderr)
            rows.append({"function": func, "status": f"error: {type(e).__name__}: {e}"})
    if len(funcs) == 1:
        return 0 if rows[0]["status"] == "ok" else 1

    summary = Path(args.summary) if args.summary else PROBE_DIR / "summary.md"
    md = [f"# Probe batch ({len(funcs)} functions, state {args.state or 'auto'}, call #{args.hit}, {args.frames} frames)", "",
          "| Function | Caller | Call bytes | Callees | Skip: bytes | Skip: pixels | Skip: fault/stall | Report |",
          "|---|---|---|---|---|---|---|---|"]
    for r in rows:
        if r["status"] != "ok":
            md.append(f"| `{r['function']}` | {r['status']} | | | | | | |")
            continue
        fs = "fault" if r["skip_faulted"] else ("stall" if r["skip_stalled"] else "")
        md.append(f"| `{r['function']}` | `{r['caller']}` | {r['call_bytes'] if r['returned'] else 'no return'} "
                  f"| {'' if r['callees'] is None else r['callees']} | {'' if r['skip_bytes'] is None else r['skip_bytes']} "
                  f"| {'' if r['skip_pixels'] is None else r['skip_pixels']} | {fs} | `{r['report']}` |")
    summary.write_text("\n".join(md) + "\n")
    (summary.with_suffix(".json")).write_text(json.dumps(rows, indent=2))
    print(f"Summary: {summary}")
    return 0 if all(r["status"] == "ok" for r in rows) else 1


if __name__ == "__main__":
    sys.exit(main())
