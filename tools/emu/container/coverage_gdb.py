"""In-container GDB script for function coverage collection.

Runs inside gdb-multiarch inside the emulator container:
  gdb-multiarch -batch -x /dk64/tools/emu/container/coverage_gdb.py
Configured via environment variables:
  GDB_PORT      - Remote port (default: 9123)
  COV_LABEL     - Label of the state being analyzed
  COV_DURATION  - Duration in seconds to run (default: 20.0)
  COV_OUTPUT    - Host-mounted output path for coverage JSON
  COV_OVERLAY   - Expected overlay or "auto"
  COV_BATCH_MIN - Optional lower index for function batching
  COV_BATCH_MAX - Optional upper index for function batching
"""

import json
import os
from pathlib import Path
import sys
import time

try:
    import gdb
except ImportError:
    print("Error: must be run inside gdb-multiarch", file=sys.stderr)
    sys.exit(1)

sys.path.insert(0, "/dk64/tools/emu")
import symbols

REPO_ROOT = Path("/dk64")
OVERLAY_BASE_ADDR = 0x80024000
GLOBAL_BASE_ADDR = 0x805FB300
LOAD_OVERLAY_ADDR = 0x80610350


def read_inferior_mem(addr: int, length: int) -> bytes:
    inf = gdb.selected_inferior()
    return inf.read_memory(addr, length).tobytes()


def main():
    port = os.environ.get("GDB_PORT", "9123")
    label = os.environ.get("COV_LABEL", "unknown")
    duration = float(os.environ.get("COV_DURATION", "20.0"))
    out_path = os.environ.get("COV_OUTPUT", f"/dk64/emu/coverage/{label}.json")
    batch_min_str = os.environ.get("COV_BATCH_MIN")
    batch_max_str = os.environ.get("COV_BATCH_MAX")

    print(f"[coverage_gdb] Initializing coverage collection for '{label}' ({duration}s)...")

    # 1. Setup GDB architecture & base symbols
    gdb.execute("set architecture mips:4000", to_string=True)
    gdb.execute("set pagination off", to_string=True)
    # Crucial for scaling: prevents GDB from deleting & reinserting thousands of breakpoints on every stop
    gdb.execute("set breakpoint always-inserted on", to_string=True)

    elf_boot = REPO_ROOT / "build" / "dk64.us.elf"
    elf_global = REPO_ROOT / "build" / "global.elf"

    if elf_boot.exists():
        gdb.execute(f"file {elf_boot}", to_string=True)
    if elf_global.exists():
        gdb.execute(f"add-symbol-file {elf_global}", to_string=True)

    # 2. Connect to ares GDB server
    print(f"[coverage_gdb] Connecting to 127.0.0.1:{port}...")
    gdb.execute(f"target remote 127.0.0.1:{port}", to_string=True)

    # 3. Detect initial overlay
    active_overlay = symbols.detect_overlay(read_inferior_mem, REPO_ROOT)
    print(f"[coverage_gdb] Active overlay at start: {active_overlay or 'none'}")
    if active_overlay:
        ovl_elf = REPO_ROOT / "build" / f"{active_overlay}.elf"
        if ovl_elf.exists():
            try:
                gdb.execute(f"add-symbol-file {ovl_elf}", to_string=True)
            except Exception as e:
                print(f"[coverage_gdb] Warning loading overlay symbols: {e}")

    # 4. Gather function candidates
    syms = symbols.load(REPO_ROOT)
    candidates = []

    # Boot functions
    for fn, addr, sz in syms.functions("boot"):
        candidates.append((fn, addr, sz, "boot"))

    # Global functions
    for fn, addr, sz in syms.functions("global"):
        candidates.append((fn, addr, sz, "global"))

    # Active overlay functions
    if active_overlay:
        try:
            for fn, addr, sz in syms.functions(active_overlay):
                candidates.append((fn, addr, sz, active_overlay))
        except Exception:
            pass

    # Apply batch slicing if requested
    total_candidates_all = len(candidates)
    if batch_min_str is not None and batch_max_str is not None:
        b_min = int(batch_min_str)
        b_max = int(batch_max_str)
        candidates = candidates[b_min:b_max]
        print(f"[coverage_gdb] Batching: functions [{b_min}:{b_max}] of {total_candidates_all}")
    else:
        print(f"[coverage_gdb] Monitoring all {len(candidates)} functions across boot, global, and overlay")

    # Map address to (name, segment, size)
    addr_map = {}
    for fn, addr, sz, seg in candidates:
        addr_map[addr] = (fn, seg, sz)

    # 5. Set breakpoints on all candidate function entries
    t_bp_start = time.time()
    active_bps = {}
    bp_errors = 0
    for fn, addr, sz, seg in candidates:
        try:
            bp = gdb.Breakpoint(f"*{hex(addr)}", type=gdb.BP_BREAKPOINT, internal=True)
            active_bps[addr] = bp
        except Exception:
            bp_errors += 1

    t_bp_set = time.time() - t_bp_start
    print(f"[coverage_gdb] Successfully set {len(active_bps)} breakpoints in {t_bp_set:.3f}s ({t_bp_set/len(candidates)*1000:.2f} ms/bp)")

    # Also hook loadOverlay so we can invalidate overlay breakpoints when overlay changes
    try:
        load_ovl_bp = gdb.Breakpoint(f"*{hex(LOAD_OVERLAY_ADDR)}", type=gdb.BP_BREAKPOINT, internal=True)
    except Exception:
        load_ovl_bp = None

    # 6. Execute and collect hits
    hits = []
    seen_addresses = set()
    overlay_transitions = []
    current_ovl_state = active_overlay

    t_start = time.time()
    t_end = t_start + duration
    stops = 0

    print(f"[coverage_gdb] Starting execution loop for {duration} seconds...")
    try:
        while time.time() < t_end:
            try:
                gdb.execute("continue", to_string=True)
            except gdb.error as e:
                # Execution error or remote disconnect
                print(f"[coverage_gdb] Breakpoint stop / continue error: {e}")
                break

            stops += 1
            now_offset = time.time() - t_start

            # Read current PC
            try:
                pc_raw = int(gdb.parse_and_eval("$pc"))
                pc = pc_raw & 0xFFFFFFFF
            except Exception:
                continue

            # Check if this stop was loadOverlay
            if pc == LOAD_OVERLAY_ADDR:
                # The game is switching overlays!
                # Overlay memory 0x80024000..0x805FB300 is about to be overwritten.
                # Remove all remaining overlay breakpoints to avoid invalid hits.
                ovl_removed = 0
                for a in list(active_bps.keys()):
                    if OVERLAY_BASE_ADDR <= a < GLOBAL_BASE_ADDR:
                        try:
                            active_bps[a].delete()
                        except Exception:
                            pass
                        del active_bps[a]
                        if a in addr_map:
                            del addr_map[a]
                        ovl_removed += 1
                overlay_transitions.append({
                    "time": round(now_offset, 4),
                    "previous_overlay": current_ovl_state,
                    "removed_breakpoints": ovl_removed,
                })
                # We can't know the new overlay until after it loads, so continue
                continue

            # Normal function entry hit
            if pc in addr_map:
                fn_name, seg, sz = addr_map[pc]

                # If this was an overlay function, verify the overlay is still active
                if seg not in ("boot", "global"):
                    current_detected = symbols.detect_overlay(read_inferior_mem, REPO_ROOT)
                    if current_detected != seg:
                        # Overwritten by another overlay: remove stale breakpoint and skip hit
                        if pc in active_bps:
                            try:
                                active_bps[pc].delete()
                            except Exception:
                                pass
                            del active_bps[pc]
                        continue

                # Record hit
                if pc not in seen_addresses:
                    seen_addresses.add(pc)
                    hits.append({
                        "name": fn_name,
                        "address": f"0x{pc:08x}",
                        "segment": seg,
                        "time": round(now_offset, 4),
                        "order": len(hits) + 1,
                    })

                # Delete breakpoint on first hit so cost drops over time!
                if pc in active_bps:
                    try:
                        active_bps[pc].delete()
                    except Exception:
                        pass
                    del active_bps[pc]

    finally:
        t_total_run = time.time() - t_start
        print(f"[coverage_gdb] Run finished in {t_total_run:.2f}s: {len(hits)} functions hit ({stops} stops)")

        # Clean up all remaining breakpoints
        print(f"[coverage_gdb] Cleaning up {len(active_bps)} remaining breakpoints...")
        for bp in list(active_bps.values()):
            try:
                bp.delete()
            except Exception:
                pass
        if load_ovl_bp:
            try:
                load_ovl_bp.delete()
            except Exception:
                pass

        # Detach cleanly so emulator continues running smoothly
        try:
            gdb.execute("detach", to_string=True)
            print("[coverage_gdb] Detached from emulator cleanly.")
        except Exception:
            pass

    # 7. Write output JSON
    out_dir = Path(out_path).parent
    out_dir.mkdir(parents=True, exist_ok=True)

    result_data = {
        "label": label,
        "duration_seconds": duration,
        "actual_run_seconds": round(t_total_run, 3),
        "total_monitored": len(candidates),
        "total_hits": len(hits),
        "initial_overlay": active_overlay,
        "overlay_transitions": overlay_transitions,
        "performance": {
            "breakpoint_set_seconds": round(t_bp_set, 3),
            "ms_per_breakpoint_set": round((t_bp_set / len(candidates) * 1000) if candidates else 0, 2),
            "stops": stops,
            "stops_per_second": round(stops / t_total_run if t_total_run > 0 else 0, 2),
        },
        "hits": hits,
    }

    with open(out_path, "w") as f:
        json.dump(result_data, f, indent=2)

    print(f"[coverage_gdb] Coverage data written to {out_path}")


if __name__ == "__main__":
    main()
