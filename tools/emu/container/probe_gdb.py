"""In-container GDB script for one probe phase of a function (see tools/emu/probe.py).

Every experiment restarts from one checkpoint: the emulator halted at the target's
natural entry (its real caller, arguments, stack frame and every register), saved as an
ares save state while GDB holds the CPU. The host drives ares save/load hotkeys while
this script waits on handshake files, so both happen with the CPU halted.

Phases (PROBE_PHASE):
  checkpoint  continue to the PROBE_HIT-th entry hit, dump entry RAM/registers, signal
              ready, wait for the host to save the checkpoint slot.
  experiment  attach (halted), signal ready, wait for the host to load the checkpoint,
              verify pc/sp/ra equal the checkpoint, apply PROBE_MODE, run to the
              function's return (observe/args) and then PROBE_FRAMES frames.

Interventions are limited to what is valid at a function entry under the o32 ABI:
  observe  nothing.
  args     overwrite $a0-$a3 (PROBE_ARGS="a0=0x1,a2=5"); the caller's frame is untouched.
  skip     return immediately: $v0/$v1 = PROBE_RET, $pc = $ra. No prologue has run, so
           $sp and the callee-saved registers already hold the caller's values.

Environment:
  GDB_PORT, PROBE_PHASE, PROBE_ADDR, PROBE_SEG, PROBE_HIT, PROBE_MODE, PROBE_ARGS,
  PROBE_RET, PROBE_FRAMES, PROBE_CALLEES (1 = record functions first entered during the
  call), PROBE_RETURN_TIMEOUT, PROBE_FRAME_TIMEOUT, PROBE_DIR (container path of the
  experiment output directory; handshake files ready.flag / go.flag live there).
"""

import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import threading
import time

try:
    import gdb
except ImportError:
    print("Error: must be run inside gdb-multiarch", file=sys.stderr)
    sys.exit(1)

sys.path.insert(0, "/dk64/tools/emu")
import symbols

REPO_ROOT = Path("/dk64")
RDRAM_BASE = 0x80000000
RDRAM_SIZE = 0x800000
ADDR_SAFE_POINT = 0x8060AC7C  # controllerUpdate entry, once per game frame
ADDR_FRAME_COUNTER = 0x80767CC4
ADDR_FAULTED_THREAD = 0x800100F4  # __osFaultedThread
LOAD_OVERLAY_ADDR = 0x80610350
HANDSHAKE_TIMEOUT = 60.0


def u32(v):
    return int(v) & 0xFFFFFFFF


def reg(name):
    return u32(gdb.parse_and_eval(f"${name}"))


def read_mem(addr, length):
    return gdb.selected_inferior().read_memory(addr, length).tobytes()


def read_u32(addr):
    return int.from_bytes(read_mem(addr, 4), "big")


def dump_ram(path):
    Path(path).write_bytes(read_mem(RDRAM_BASE, RDRAM_SIZE))


def screenshot(path):
    subprocess.run(["import", "-window", "root", "-display", ":99", str(path)],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=10)


def handshake(out_dir):
    """Tell the host the CPU is halted, then wait until it has saved/loaded the slot."""
    (out_dir / "ready.flag").write_text("1")
    deadline = time.time() + HANDSHAKE_TIMEOUT
    while not (out_dir / "go.flag").exists():
        if time.time() > deadline:
            raise RuntimeError("host did not answer the handshake")
        time.sleep(0.05)


def continue_until(stop_test, timeout):
    """`continue` until stop_test(pc) is true. Returns pc, or None on timeout.

    A timer interrupts the target so a function that never returns (or a game that
    stalls) cannot block forever, as in coverage_gdb.py.
    """
    fired = []

    def interrupt():
        fired.append(True)
        os.kill(os.getpid(), signal.SIGINT)

    timer = threading.Timer(timeout, interrupt)
    timer.daemon = True
    timer.start()
    try:
        while True:
            try:
                gdb.execute("continue", to_string=True)
            except (gdb.error, KeyboardInterrupt):
                return None
            if fired:
                return None
            pc = reg("pc")
            if stop_test(pc):
                return pc
    finally:
        timer.cancel()


def entry_regs():
    names = ["pc", "ra", "sp", "a0", "a1", "a2", "a3", "s0", "s1", "s2", "s3", "s4",
             "s5", "s6", "s7", "fp", "gp"]
    out = {n: f"0x{reg(n):08x}" for n in names}
    for f in ("f12", "f14"):
        try:
            out[f] = float(gdb.parse_and_eval(f"${f}"))
        except Exception:
            out[f] = None
    return out


def phase_checkpoint(addr, seg, hit, out_dir):
    bp = gdb.Breakpoint(f"*{hex(addr)}", type=gdb.BP_BREAKPOINT, internal=True)
    seen = 0

    def is_hit(pc):
        nonlocal seen
        if pc != addr:
            return False
        if seg not in ("boot", "global") and symbols.detect_overlay(read_mem, REPO_ROOT) != seg:
            return False  # another overlay's code at the same address
        seen += 1
        return seen >= hit

    pc = continue_until(is_hit, float(os.environ.get("PROBE_HIT_TIMEOUT", "60")))
    bp.delete()
    if pc is None:
        return {"status": "no_hit", "hits_seen": seen}
    syms = symbols.load(REPO_ROOT)
    ra = reg("ra")
    overlay = symbols.detect_overlay(read_mem, REPO_ROOT)
    in_overlay = symbols.OVERLAY_VRAM_START <= ra < symbols.GLOBAL_VRAM_START
    caller = syms.function_at(ra, segment=overlay) if in_overlay else syms.function_at(ra)
    result = {
        "status": "ok",
        "hit": hit,
        "registers": entry_regs(),
        "caller": f"{caller[0]}+0x{ra - caller[1]:x}" if caller else f"0x{ra:08x}",
        "frame_counter": read_u32(ADDR_FRAME_COUNTER),
        "overlay": overlay,
    }
    dump_ram(out_dir / "entry.bin")
    screenshot(out_dir / "entry.png")
    handshake(out_dir)  # host saves the checkpoint slot now
    return result


def run_call(entry_addr, entry_sp, ra, record_callees, seg):
    """Run from entry to the matching return; optionally record callees entered first.

    The target itself is not armed: the first `continue` would report the entry the
    CPU is halted on. Recursive calls of the target are therefore not recorded.
    """
    callee_bps = {}
    if record_callees:
        syms = symbols.load(REPO_ROOT)
        segs = ["boot", "global"] + ([seg] if seg not in ("boot", "global") else [])
        overlay = symbols.detect_overlay(read_mem, REPO_ROOT)
        if overlay and overlay not in segs:
            segs.append(overlay)
        for s in segs:
            skip = {a for _, a in syms.fallthrough_entries(s)}  # breakpoints there wedge ares
            for name, a, _ in syms.functions(s):
                if a in skip or a in (LOAD_OVERLAY_ADDR, entry_addr) or a in callee_bps:
                    continue
                try:
                    callee_bps[a] = (gdb.Breakpoint(f"*{hex(a)}", type=gdb.BP_BREAKPOINT, internal=True), name, s)
                except Exception:
                    pass
    ret_bp = gdb.Breakpoint(f"*{hex(ra)}", type=gdb.BP_BREAKPOINT, internal=True)
    callees = []

    def returned(pc):
        if pc == ra and reg("sp") == entry_sp:  # a recursive inner return has a lower $sp
            return True
        if pc in callee_bps:
            bp, name, s = callee_bps.pop(pc)
            callees.append({"name": name, "segment": s, "address": f"0x{pc:08x}"})
            bp.delete()
        return False

    t0 = time.time()
    pc = continue_until(returned, float(os.environ.get("PROBE_RETURN_TIMEOUT", "30")))
    elapsed = time.time() - t0
    ret_bp.delete()
    for bp, _, _ in callee_bps.values():
        bp.delete()
    return pc is not None, callees, elapsed


def run_frames(frames):
    """Run `frames` game frames (controllerUpdate entries); report crash/stall."""
    fc0 = read_u32(ADDR_FRAME_COUNTER)
    bp = gdb.Breakpoint(f"*{hex(ADDR_SAFE_POINT)}", type=gdb.BP_BREAKPOINT, internal=True)
    count = 0

    def frame(pc):
        nonlocal count
        if pc == ADDR_SAFE_POINT:
            count += 1
        return count >= frames

    pc = continue_until(frame, float(os.environ.get("PROBE_FRAME_TIMEOUT", "60")))
    bp.delete()
    return {
        "frames_requested": frames,
        "frames_run": count,
        "completed": pc is not None,
        "frame_counter_start": fc0,
        "frame_counter_end": read_u32(ADDR_FRAME_COUNTER),
        "faulted_thread": f"0x{read_u32(ADDR_FAULTED_THREAD):08x}",
    }


def phase_experiment(seg, out_dir, checkpoint):
    handshake(out_dir)  # host loads the checkpoint slot now
    gdb.execute("flushregs", to_string=True)
    want = checkpoint["registers"]
    got = {n: f"0x{reg(n):08x}" for n in ("pc", "sp", "ra")}
    if any(got[n] != want[n] for n in got):
        return {"status": "restore_failed", "expected": {n: want[n] for n in got}, "got": got}

    mode = os.environ.get("PROBE_MODE", "observe")
    entry_sp = int(want["sp"], 16)
    ra = int(want["ra"], 16)
    result = {"status": "ok", "mode": mode}

    overrides = {}
    for item in filter(None, os.environ.get("PROBE_ARGS", "").split(",")):
        name, val = item.split("=", 1)
        overrides[name.strip()] = int(val, 0) & 0xFFFFFFFF
    for name, val in overrides.items():
        gdb.execute(f"set ${name} = {val}", to_string=True)
    if overrides:
        result["args"] = {n: f"0x{v:08x}" for n, v in overrides.items()}

    if mode == "skip":
        ret = int(os.environ.get("PROBE_RET", "0"), 0) & 0xFFFFFFFF
        gdb.execute(f"set $v0 = {ret}", to_string=True)
        gdb.execute(f"set $v1 = 0", to_string=True)
        gdb.execute(f"set $pc = {ra}", to_string=True)
        result["skip_return"] = f"0x{ret:08x}"
    else:
        done, callees, elapsed = run_call(int(want["pc"], 16), entry_sp, ra, os.environ.get("PROBE_CALLEES") == "1", seg)
        result["returned"] = done
        result["call_seconds"] = round(elapsed, 3)
        if os.environ.get("PROBE_CALLEES") == "1":
            result["callees"] = callees
        if not done:
            return result
        result["return"] = {"v0": f"0x{reg('v0'):08x}", "v1": f"0x{reg('v1'):08x}"}
        try:
            result["return"]["f0"] = float(gdb.parse_and_eval("$f0"))
        except Exception:
            result["return"]["f0"] = None
        dump_ram(out_dir / "ret.bin")

    result["after"] = run_frames(int(os.environ.get("PROBE_FRAMES", "30")))
    dump_ram(out_dir / "after.bin")
    screenshot(out_dir / "after.png")
    return result


def main():
    port = os.environ.get("GDB_PORT", "9123")
    phase = os.environ["PROBE_PHASE"]
    addr = int(os.environ["PROBE_ADDR"], 0)
    seg = os.environ.get("PROBE_SEG", "global")
    out_dir = Path(os.environ["PROBE_DIR"])
    out_dir.mkdir(parents=True, exist_ok=True)

    gdb.execute("set architecture mips:4000", to_string=True)
    gdb.execute("set pagination off", to_string=True)
    gdb.execute("set breakpoint always-inserted on", to_string=True)
    # 32-bit ELF before connecting, otherwise GDB treats the target as 64-bit.
    gdb.execute(f"file {REPO_ROOT / 'build' / 'dk64.us.elf'}", to_string=True)
    gdb.execute(f"add-symbol-file {REPO_ROOT / 'build' / 'global.elf'}", to_string=True)

    try:
        # ares's stub once reset a connection made right after the previous client
        # detached (1 in ~80 connects); retry before failing the phase.
        for attempt in range(5):
            try:
                gdb.execute(f"target remote 127.0.0.1:{port}", to_string=True)
                break
            except gdb.error:
                if attempt == 4:
                    raise
                time.sleep(1.0)
        if phase == "checkpoint":
            result = phase_checkpoint(addr, seg, int(os.environ.get("PROBE_HIT", "1")), out_dir)
        else:
            checkpoint = json.loads((out_dir.parent / "checkpoint.json").read_text())
            result = phase_experiment(seg, out_dir, checkpoint)
    except Exception as e:
        result = {"status": "error", "error": str(e)}
    finally:
        try:
            gdb.execute("delete", to_string=True)
            gdb.execute("detach", to_string=True)
        except Exception:
            pass
    (out_dir / "result.json").write_text(json.dumps(result, indent=2))
    print(f"PROBE_RESULT:{json.dumps({'status': result.get('status')})}")


main()
