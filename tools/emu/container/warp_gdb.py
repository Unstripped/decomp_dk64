"""GDB Python helper for DK64 transition observation and warping.

Runs inside gdb-multiarch in the container via:
  gdb-multiarch -batch -x /dk64/tools/emu/container/warp_gdb.py
Controlled by environment variables:
  WARP_ACTION: "observe" or "warp"
  WARP_TARGET_MAP: map id (for warp)
  WARP_TARGET_EXIT: exit id (for warp, default 0)
"""

import json
import os
import subprocess
import sys
import time

try:
    import gdb
except ImportError:
    print("Error: must run inside gdb-multiarch", file=sys.stderr)
    sys.exit(1)

# Add tools/emu to sys.path so we can import symbols
sys.path.insert(0, "/dk64/tools/emu")
try:
    import symbols
    sym_db = symbols.load("/dk64")
except Exception as e:
    sym_db = None

ADDR_FUNC_805FF378 = 0x805FF378  # func_805FF378(map, exit)
ADDR_FUNC_805FF4D8 = 0x805FF4D8  # func_805FF4D8(map, exit)
ADDR_FUNC_80712F10 = 0x80712F10  # func_80712F10(&map, &exit)
ADDR_RET_80712F10  = 0x805FF3B8  # Return address of func_80712F10 in func_805FF378
ADDR_SAFE_POINT    = 0x8060AC7C  # controllerUpdate entry (per-frame safe point)

ADDR_D_807444EC = 0x807444EC  # u8 mode/gate
ADDR_D_80755314 = 0x80755314  # u8 for func_80712798
ADDR_D_80755318 = 0x80755318  # u8 for func_80712798
ADDR_D_8076A0A8 = 0x8076A0A8  # s32 current map
ADDR_D_807444E4 = 0x807444E4  # s32 next map
ADDR_D_807444E8 = 0x807444E8  # s32 exit
ADDR_D_8076A0B1 = 0x8076A0B1  # u8 flags
ADDR_D_8076A0B2 = 0x8076A0B2  # u8 flags
ADDR_MODE_BYTE  = 0x8074450C  # u8 mode byte (0x8074450C)

LOG_FILE = "/dk64/emu/natural_transitions.jsonl"
SCREENSHOT_DIR = "/dk64/emu/screenshots"

def read_u8(inf, addr):
    try:
        data = inf.read_memory(addr & 0xFFFFFFFF, 1).tobytes()
        return data[0]
    except Exception:
        return None

def read_s32(inf, addr):
    try:
        data = inf.read_memory(addr & 0xFFFFFFFF, 4).tobytes()
        return int.from_bytes(data, byteorder="big", signed=True)
    except Exception:
        return None

def read_u32(inf, addr):
    try:
        data = inf.read_memory(addr & 0xFFFFFFFF, 4).tobytes()
        return int.from_bytes(data, byteorder="big", signed=False)
    except Exception:
        return None

def symbolize(addr):
    addr_u = addr & 0xFFFFFFFF
    if sym_db:
        for seg in ["global", "boot"]:
            res = sym_db.function_at(addr_u, seg)
            if res:
                fn_name, start, size, segment = res
                offset = addr_u - start
                return f"{fn_name}+0x{offset:X}" if offset > 0 else fn_name
    try:
        out = gdb.execute(f"info symbol {hex(addr_u)}", to_string=True).strip()
        if "in section" in out:
            return out.split("in section")[0].strip()
        return out
    except Exception:
        return hex(addr_u)

def take_screenshot(out_path):
    try:
        env = os.environ.copy()
        env["DISPLAY"] = ":99"
        subprocess.run(["import", "-window", "root", out_path], env=env, check=False)
    except Exception as e:
        print(f"Error taking screenshot: {e}", file=sys.stderr)

class Observer:
    def __init__(self):
        self.hit_count = 0
        self.saved_a0_ptr = None
        self.saved_a1_ptr = None
        self.saved_before_map = None
        self.saved_before_exit = None
        os.makedirs(SCREENSHOT_DIR, exist_ok=True)
        with open(LOG_FILE, "w") as f:
            pass

    def on_hit(self, point_name, bp_addr):
        self.hit_count += 1
        inf = gdb.selected_inferior()
        frame = gdb.selected_frame()

        pc = int(frame.read_register("pc")) & 0xFFFFFFFF
        ra = int(frame.read_register("ra")) & 0xFFFFFFFF
        a0 = int(frame.read_register("a0")) & 0xFFFFFFFF
        a1 = int(frame.read_register("a1")) & 0xFFFFFFFF

        d_807444ec = read_u8(inf, ADDR_D_807444EC)
        v_5314 = read_u8(inf, ADDR_D_80755314)
        v_5318 = read_u8(inf, ADDR_D_80755318)
        func_80712798_res = 0 if (v_5314 is not None and v_5318 is not None and v_5314 == v_5318) else 1
        d_8076a0a8 = read_s32(inf, ADDR_D_8076A0A8)
        d_807444e4 = read_s32(inf, ADDR_D_807444E4)
        d_807444e8 = read_s32(inf, ADDR_D_807444E8)
        d_8076a0b1 = read_u8(inf, ADDR_D_8076A0B1)
        d_8076a0b2 = read_u8(inf, ADDR_D_8076A0B2)
        mode_byte  = read_u8(inf, ADDR_MODE_BYTE)

        shot_name = f"obs_hit_{self.hit_count:02d}_{point_name}.png"
        shot_path = os.path.join(SCREENSHOT_DIR, shot_name)
        take_screenshot(shot_path)

        data = {
            "hit": self.hit_count,
            "point": point_name,
            "pc": f"0x{pc:08X}",
            "ra": f"0x{ra:08X}",
            "ra_sym": symbolize(ra),
            "a0": f"0x{a0:08X}",
            "a1": f"0x{a1:08X}",
            "D_807444EC": d_807444ec,
            "func_80712798_result": func_80712798_res,
            "D_80755314": v_5314,
            "D_80755318": v_5318,
            "D_8076A0A8_current_map": d_8076a0a8,
            "D_807444E4_next_map": d_807444e4,
            "D_807444E8_exit": d_807444e8,
            "D_8076A0B1": d_8076a0b1,
            "D_8076A0B2": d_8076a0b2,
            "mode_byte_8074450C": mode_byte,
            "screenshot": shot_path,
        }

        if point_name == "func_80712F10":
            self.saved_a0_ptr = a0
            self.saved_a1_ptr = a1
            val_a0 = read_s32(inf, a0) if a0 != 0 else None
            val_a1 = read_s32(inf, a1) if a1 != 0 else None
            self.saved_before_map = val_a0
            self.saved_before_exit = val_a1
            data["pointed_map_before"] = val_a0
            data["pointed_exit_before"] = val_a1

        elif point_name == "ret_func_80712F10":
            val_a0_after = read_s32(inf, self.saved_a0_ptr) if self.saved_a0_ptr else None
            val_a1_after = read_s32(inf, self.saved_a1_ptr) if self.saved_a1_ptr else None
            data["pointed_map_before"] = self.saved_before_map
            data["pointed_exit_before"] = self.saved_before_exit
            data["pointed_map_after"] = val_a0_after
            data["pointed_exit_after"] = val_a1_after
            data["rewritten"] = (
                (self.saved_before_map != val_a0_after) or
                (self.saved_before_exit != val_a1_after)
            )

        print(f"[OBSERVER HIT {self.hit_count}] {point_name}: {json.dumps(data)}")
        with open(LOG_FILE, "a") as f:
            f.write(json.dumps(data) + "\n")

class ObsBreakpoint(gdb.Breakpoint):
    def __init__(self, addr, name, observer):
        super().__init__(f"*{hex(addr)}", type=gdb.BP_BREAKPOINT, internal=False)
        self.name = name
        self.addr = addr
        self.observer = observer

    def stop(self):
        try:
            self.observer.on_hit(self.name, self.addr)
        except Exception as e:
            print(f"Error in on_hit: {e}", file=sys.stderr)
        return False

def run_observe():
    print("[warp_gdb] Starting observation session...")
    obs = Observer()

    bp1 = ObsBreakpoint(ADDR_FUNC_805FF378, "func_805FF378", obs)
    bp2 = ObsBreakpoint(ADDR_FUNC_805FF4D8, "func_805FF4D8", obs)
    bp3 = ObsBreakpoint(ADDR_FUNC_80712F10, "func_80712F10", obs)
    bp4 = ObsBreakpoint(ADDR_RET_80712F10,  "ret_func_80712F10", obs)

    print("[warp_gdb] Breakpoints set. Continuing execution...")
    try:
        gdb.execute("continue")
    except KeyboardInterrupt:
        print("[warp_gdb] Interrupted by user.")
    except Exception as e:
        print(f"[warp_gdb] Execution ended: {e}")
    finally:
        bp1.delete()
        bp2.delete()
        bp3.delete()
        bp4.delete()
        try:
            gdb.execute("detach")
        except Exception:
            pass

def run_warp(target_map, target_exit):
    inf = gdb.selected_inferior()

    # 1. Break at safe point
    gdb.execute(f"break *{hex(ADDR_SAFE_POINT)}", to_string=True)
    gdb.execute("continue", to_string=True)
    gdb.execute("delete", to_string=True)

    # 2. Verify gate conditions
    d_807444ec = read_u8(inf, ADDR_D_807444EC)
    v_5314 = read_u8(inf, ADDR_D_80755314)
    v_5318 = read_u8(inf, ADDR_D_80755318)
    func_80712798_res = 0 if (v_5314 is not None and v_5318 is not None and v_5314 == v_5318) else 1

    gate_open = (d_807444ec == 6) or (func_80712798_res == 0)
    current_map = read_s32(inf, ADDR_D_8076A0A8)

    if not gate_open:
        res = {
            "status": "refused",
            "error": f"Gate refused: D_807444EC={d_807444ec} != 6 and func_80712798()={func_80712798_res} (0x80755314={v_5314} != 0x80755318={v_5318})",
            "current_map": current_map,
            "target_map": target_map,
            "target_exit": target_exit,
        }
        print(f"WARP_RESULT:{json.dumps(res)}")
        try:
            gdb.execute("detach", to_string=True)
        except Exception:
            pass
        return

    # 3. Call func_805FF378(map, exit)
    call_success = False
    try:
        gdb.execute(f"call (void)func_805FF378({target_map}, {target_exit})", to_string=True)
        call_success = True
    except Exception as e:
        # Fallback to manual call frame setup
        try:
            frame = gdb.selected_frame()
            orig_ra = int(frame.read_register("ra")) & 0xFFFFFFFF
            orig_a0 = int(frame.read_register("a0")) & 0xFFFFFFFF
            orig_a1 = int(frame.read_register("a1")) & 0xFFFFFFFF

            bp_ret = gdb.Breakpoint(f"*{hex(ADDR_SAFE_POINT)}", type=gdb.BP_BREAKPOINT, internal=False)
            gdb.execute(f"set $a0 = {target_map}")
            gdb.execute(f"set $a1 = {target_exit}")
            gdb.execute(f"set $ra = {ADDR_SAFE_POINT}")
            gdb.execute(f"set $pc = {ADDR_FUNC_805FF378}")
            gdb.execute("continue", to_string=True)
            bp_ret.delete()

            gdb.execute(f"set $ra = {orig_ra}")
            gdb.execute(f"set $a0 = {orig_a0}")
            gdb.execute(f"set $a1 = {orig_a1}")
            call_success = True
        except Exception as e2:
            res = {
                "status": "error",
                "error": f"Call failed: infcall ({e}), manual ({e2})",
                "current_map": current_map,
                "target_map": target_map,
            }
            print(f"WARP_RESULT:{json.dumps(res)}")
            try:
                gdb.execute("detach", to_string=True)
            except Exception:
                pass
            return

    # 4. Check if func_80712F10 rewrote or cancelled
    next_map = read_s32(inf, ADDR_D_807444E4)
    next_exit = read_s32(inf, ADDR_D_807444E8)

    rewritten = (next_map != target_map) or (next_exit != target_exit)
    cancelled = (next_map == -1)

    res = {
        "status": "initiated",
        "current_map": current_map,
        "target_map": target_map,
        "target_exit": target_exit,
        "next_map": next_map,
        "next_exit": next_exit,
        "rewritten": rewritten,
        "cancelled": cancelled,
    }
    print(f"WARP_RESULT:{json.dumps(res)}")
    try:
        gdb.execute("detach", to_string=True)
    except Exception:
        pass
def main():
    action = os.environ.get("WARP_ACTION", "observe")
    gdb.execute("set architecture mips:4000", to_string=True)
    if os.path.exists("/dk64/build/dk64.us.elf"):
        gdb.execute("file /dk64/build/dk64.us.elf", to_string=True)
    if os.path.exists("/dk64/build/global.elf"):
        gdb.execute("add-symbol-file /dk64/build/global.elf", to_string=True)

    gdb.execute("target remote 127.0.0.1:9123", to_string=True)

    if action == "observe":
        run_observe()
    elif action == "warp":
        t_map = int(os.environ.get("WARP_TARGET_MAP", "0"), 0)
        t_exit = int(os.environ.get("WARP_TARGET_EXIT", "0"), 0)
        run_warp(t_map, t_exit)
    else:
        print(f"Unknown action: {action}", file=sys.stderr)

if __name__ == "__main__":
    main()
