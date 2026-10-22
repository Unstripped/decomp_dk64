"""In-container GDB script for detailed function study.

Records arguments, caller ($ra), stack ($sp), dereferences RDRAM pointer args,
steps to $ra to capture return values ($v0, $v1, $f0), optionally watches memory,
and captures a screenshot at first hit.

Runs inside gdb-multiarch:
  gdb-multiarch -batch -x /dk64/tools/emu/container/study_gdb.py
"""

import json
import os
from pathlib import Path
import subprocess
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
RDRAM_START = 0x80000000
RDRAM_END = 0x80800000  # 8MB RDRAM


def format_hex_dump(data: bytes, base_addr: int) -> str:
    """Format bytes as standard 16-byte hex dump."""
    lines = []
    for off in range(0, len(data), 16):
        chunk = data[off:off + 16]
        hex_str = " ".join(f"{b:02x}" for b in chunk)
        ascii_str = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
        lines.append(f"0x{base_addr + off:08x}:  {hex_str:<48}  |{ascii_str}|")
    return "\n".join(lines)


def main():
    port = os.environ.get("GDB_PORT", "9123")
    target_addr_str = os.environ.get("STUDY_TARGET_ADDR")
    target_name = os.environ.get("STUDY_TARGET_NAME", "unknown")
    target_seg = os.environ.get("STUDY_TARGET_SEG", "global")
    max_hits = int(os.environ.get("STUDY_MAX_HITS", "3"))
    out_json = os.environ.get("STUDY_OUTPUT_JSON", f"/dk64/emu/study/{target_name}/data.json")
    screenshot_path = os.environ.get("STUDY_SCREENSHOT", f"/dk64/emu/study/{target_name}/screenshot.png")

    watch_addr_str = os.environ.get("STUDY_WATCH_ADDR")
    watch_addr = int(watch_addr_str, 0) if watch_addr_str else None
    watch_len = int(os.environ.get("STUDY_WATCH_LEN", "16"))

    if not target_addr_str:
        print("Error: STUDY_TARGET_ADDR must be specified", file=sys.stderr)
        sys.exit(1)

    entry_addr = int(target_addr_str, 0)

    print(f"[study_gdb] Target: {target_name} at 0x{entry_addr:08x} in {target_seg} (max {max_hits} hits)")

    # 1. Setup GDB
    gdb.execute("set architecture mips:4000", to_string=True)
    gdb.execute("set pagination off", to_string=True)

    elf_boot = REPO_ROOT / "build" / "dk64.us.elf"
    elf_global = REPO_ROOT / "build" / "global.elf"
    if elf_boot.exists():
        gdb.execute(f"file {elf_boot}", to_string=True)
    if elf_global.exists():
        gdb.execute(f"add-symbol-file {elf_global}", to_string=True)

    # If overlay segment, load overlay symbols
    if target_seg not in ("boot", "global"):
        ovl_elf = REPO_ROOT / "build" / f"{target_seg}.elf"
        if ovl_elf.exists():
            gdb.execute(f"add-symbol-file {ovl_elf}", to_string=True)

    # 2. Connect
    print(f"[study_gdb] Connecting to target 127.0.0.1:{port}...")
    gdb.execute(f"target remote 127.0.0.1:{port}", to_string=True)
    inf = gdb.selected_inferior()
    syms = symbols.load(REPO_ROOT)

    # 3. Set entry breakpoint (*entry_addr)
    # Must use *0xADDR to avoid prologue skipping
    bp_entry = gdb.Breakpoint(f"*{hex(entry_addr)}", type=gdb.BP_BREAKPOINT, internal=True)

    hits_data = []
    t_start = time.time()

    try:
        for hit_idx in range(1, max_hits + 1):
            print(f"[study_gdb] Waiting for hit #{hit_idx}...")
            try:
                gdb.execute("continue", to_string=True)
            except gdb.error as e:
                print(f"[study_gdb] Breakpoint error: {e}")
                break

            now = time.time() - t_start
            pc = int(gdb.parse_and_eval("$pc")) & 0xFFFFFFFF
            if pc != entry_addr:
                # Unexpected stop
                print(f"[study_gdb] Stopped at unexpected PC 0x{pc:08x}, expected 0x{entry_addr:08x}")
                continue

            # Read arguments & registers
            a0 = int(gdb.parse_and_eval("$a0")) & 0xFFFFFFFF
            a1 = int(gdb.parse_and_eval("$a1")) & 0xFFFFFFFF
            a2 = int(gdb.parse_and_eval("$a2")) & 0xFFFFFFFF
            a3 = int(gdb.parse_and_eval("$a3")) & 0xFFFFFFFF
            sp = int(gdb.parse_and_eval("$sp")) & 0xFFFFFFFF
            ra = int(gdb.parse_and_eval("$ra")) & 0xFFFFFFFF

            # Symbolize caller
            caller_sym = syms.function_at(ra)
            if caller_sym:
                caller_str = f"{caller_sym[0]}+0x{ra - caller_sym[1]:x} ({caller_sym[3]})"
            else:
                caller_str = f"0x{ra:08x} (unknown)"

            # Capture screenshot on first hit
            if hit_idx == 1 and screenshot_path:
                try:
                    Path(screenshot_path).parent.mkdir(parents=True, exist_ok=True)
                    subprocess.run(
                        ["import", "-window", "root", "-display", ":99", screenshot_path],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        timeout=5
                    )
                    print(f"[study_gdb] Captured first-hit screenshot to {screenshot_path}")
                except Exception as ex:
                    print(f"[study_gdb] Warning: failed to capture screenshot: {ex}")

            # Inspect RDRAM pointers in $a0-$a3 (0x80 bytes each)
            arg_dumps = {}
            for arg_name, arg_val in [("a0", a0), ("a1", a1), ("a2", a2), ("a3", a3)]:
                if RDRAM_START <= arg_val < RDRAM_END:
                    try:
                        mem_bytes = inf.read_memory(arg_val, 128).tobytes()
                        arg_dumps[arg_name] = {
                            "pointer": f"0x{arg_val:08x}",
                            "hex_dump": format_hex_dump(mem_bytes, arg_val),
                            "raw_hex": mem_bytes.hex(),
                        }
                    except Exception as e:
                        arg_dumps[arg_name] = {
                            "pointer": f"0x{arg_val:08x}",
                            "error": str(e),
                        }

            # Inspect watched memory before call
            watch_before = None
            if watch_addr is not None:
                try:
                    wb_bytes = inf.read_memory(watch_addr, watch_len).tobytes()
                    watch_before = {
                        "address": f"0x{watch_addr:08x}",
                        "length": watch_len,
                        "hex_dump": format_hex_dump(wb_bytes, watch_addr),
                        "raw_hex": wb_bytes.hex(),
                    }
                except Exception as e:
                    watch_before = {"error": str(e)}

            # Now capture return value: temporarily disable entry bp, set temp bp at $ra
            bp_entry.enabled = False
            bp_ret = None
            ret_v0 = None
            ret_v1 = None
            ret_f0 = None
            try:
                bp_ret = gdb.Breakpoint(f"*{hex(ra)}", type=gdb.BP_BREAKPOINT, temporary=True)
                gdb.execute("continue", to_string=True)
                ret_pc = int(gdb.parse_and_eval("$pc")) & 0xFFFFFFFF
                if ret_pc == ra:
                    ret_v0 = int(gdb.parse_and_eval("$v0")) & 0xFFFFFFFF
                    ret_v1 = int(gdb.parse_and_eval("$v1")) & 0xFFFFFFFF
                    try:
                        # Try reading $f0 float register
                        ret_f0_val = float(gdb.parse_and_eval("$f0"))
                        ret_f0 = round(ret_f0_val, 6)
                    except Exception:
                        ret_f0 = None
            except Exception as e:
                print(f"[study_gdb] Error waiting for return: {e}")
            finally:
                if bp_ret:
                    try:
                        bp_ret.delete()
                    except Exception:
                        pass
                bp_entry.enabled = True

            # Inspect watched memory after call
            watch_after = None
            watch_changed = False
            if watch_addr is not None:
                try:
                    wa_bytes = inf.read_memory(watch_addr, watch_len).tobytes()
                    watch_after = {
                        "address": f"0x{watch_addr:08x}",
                        "length": watch_len,
                        "hex_dump": format_hex_dump(wa_bytes, watch_addr),
                        "raw_hex": wa_bytes.hex(),
                    }
                    if watch_before and "raw_hex" in watch_before:
                        watch_changed = (watch_before["raw_hex"] != wa_bytes.hex())
                except Exception as e:
                    watch_after = {"error": str(e)}

            hit_record = {
                "hit": hit_idx,
                "time_offset": round(now, 4),
                "pc": f"0x{pc:08x}",
                "registers": {
                    "a0": f"0x{a0:08x}",
                    "a1": f"0x{a1:08x}",
                    "a2": f"0x{a2:08x}",
                    "a3": f"0x{a3:08x}",
                    "sp": f"0x{sp:08x}",
                    "ra": f"0x{ra:08x}",
                },
                "caller": {
                    "address": f"0x{ra:08x}",
                    "symbol": caller_str,
                },
                "rdram_pointers": arg_dumps,
                "return_value": {
                    "v0": f"0x{ret_v0:08x}" if ret_v0 is not None else None,
                    "v0_dec": ret_v0,
                    "v1": f"0x{ret_v1:08x}" if ret_v1 is not None else None,
                    "f0": ret_f0,
                },
                "watch": {
                    "before": watch_before,
                    "after": watch_after,
                    "changed": watch_changed,
                } if watch_addr is not None else None,
            }
            hits_data.append(hit_record)

    finally:
        # Delete entry breakpoint
        try:
            bp_entry.delete()
        except Exception:
            pass

        # Detach cleanly so emulator keeps running
        try:
            gdb.execute("detach", to_string=True)
            print("[study_gdb] Detached cleanly; emulator continues.")
        except Exception:
            pass

    # Save output JSON
    out_dir = Path(out_json).parent
    out_dir.mkdir(parents=True, exist_ok=True)

    result_payload = {
        "target_name": target_name,
        "target_address": f"0x{entry_addr:08x}",
        "target_segment": target_seg,
        "max_hits_requested": max_hits,
        "actual_hits": len(hits_data),
        "screenshot": screenshot_path,
        "hits": hits_data,
    }

    with open(out_json, "w") as f:
        json.dump(result_payload, f, indent=2)

    print(f"[study_gdb] Study complete: {len(hits_data)} hits recorded to {out_json}")


if __name__ == "__main__":
    main()
