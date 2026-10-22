#!/usr/bin/env python3
"""DK64 Map Warp Tool - warp to any map ID by calling game transition functions.

Warp mechanism:
  1. Stops emulator at safe point (controllerUpdate entry at 0x8060AC7C).
  2. Verifies gate conditions (D_807444EC == 6 or func_80712798() == 0).
  3. Calls func_805FF378(map, exit) via in-container GDB infcall (with manual fallback).
  4. Detaches GDB and waits for transition to complete (polling D_8076A0A8).
  5. Identifies active overlay and captures screenshot to emu/maps/.

Usage:
  python3 tools/emu/warp.py [--name main] 0x22 [EXIT] [--timeout S] [--settle S]
  python3 tools/emu/warp.py [--name main] "Cranky's Lab"
  python3 tools/emu/warp.py sweep --name N --state LABEL --from A --to B --out FILE.tsv [--vnc-port P] [--timeout S] [--settle S]
"""

import argparse
import json
import os
import subprocess
import sys
import time
from pathlib import Path

# Repo root detection
SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]

# Add tools/emu to sys.path
sys.path.insert(0, str(SCRIPT_DIR))
import emu
import states
import symbols

DEFAULT_SESSION = emu.DEFAULT_SESSION
DEFAULT_SLOT = 1
MAPS_TSV = SCRIPT_DIR / "maps.tsv"
MAPS_DIR = REPO_ROOT / "emu" / "maps"

# Memory constants
ADDR_CURRENT_MAP = "0x8076A0A8"
ADDR_FAULTED_THREAD = "0x800100F4"
ADDR_FRAME_COUNTER = "0x80767CC4"
ADDR_VI_COUNTER = "0x80014FEC"
DEFAULT_TIMEOUT = 20.0
DEFAULT_SETTLE = 4.5
def load_maps_tsv():
    """Load name -> id mapping from maps.tsv if available."""
    name_to_id = {}
    id_to_name = {}
    if MAPS_TSV.exists():
        with open(MAPS_TSV, "r") as f:
            for line in f:
                parts = line.strip().split("\t")
                if len(parts) >= 2 and parts[0] != "id":
                    try:
                        m_id = int(parts[0], 0)
                        m_name = parts[1]
                        name_to_id[m_name.lower()] = m_id
                        id_to_name[m_id] = m_name
                    except ValueError:
                        pass
    return name_to_id, id_to_name

def parse_map_target(map_arg):
    """Parse map ID from hex, dec, or name in maps.tsv."""
    try:
        return int(map_arg, 0)
    except ValueError:
        pass
    name_to_id, _ = load_maps_tsv()
    key = map_arg.strip().lower()
    if key in name_to_id:
        return name_to_id[key]
    # Substring / partial match fallback
    for m_name, m_id in name_to_id.items():
        if key in m_name:
            return m_id
    raise ValueError(f"Unknown map name or invalid ID: '{map_arg}'")
def read_u32(session, addr_str, retries=1):
    """Read a 32-bit big-endian word via emu.py read32 with retry."""
    c_name = emu.container_name(session)
    cmd = [
        "docker", "exec",
        "-e", "GDB_ACTION=read32",
        "-e", f"GDB_ADDR={addr_str}",
        c_name,
        "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
    ]
    for attempt in range(retries + 1):
        try:
            res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=5)
            if res.returncode == 0:
                for line in res.stdout.splitlines():
                    line = line.strip()
                    if line.startswith("0x") and "in ??" not in line:
                        val_str = line.split()[0]
                        try:
                            return int(val_str, 16)
                        except ValueError:
                            pass
        except Exception:
            pass
        if attempt < retries:
            time.sleep(0.3)
    return None

def check_crash(session):
    """Check if __osFaultedThread is non-null."""
    fault = read_u32(session, ADDR_FAULTED_THREAD, retries=1)
    return fault is not None and fault != 0

def check_game_stuck(session):
    """Check if the game appears frozen/deadlocked."""
    fc1 = read_u32(session, ADDR_FRAME_COUNTER, retries=1)
    time.sleep(0.8)
    fc2 = read_u32(session, ADDR_FRAME_COUNTER, retries=1)
    if fc1 is not None and fc2 is not None:
        if fc2 > fc1:
            return False
        return True
    vi1 = read_u32(session, ADDR_VI_COUNTER, retries=1)
    time.sleep(0.8)
    vi2 = read_u32(session, ADDR_VI_COUNTER, retries=1)
    if vi1 is not None and vi2 is not None:
        if vi2 > vi1:
            return False
        return True
    return False

def detect_current_overlay(session):
    """Detect active overlay in emulator memory with disagreement retry."""
    c_name = emu.container_name(session)

    def read_mem(addr, length):
        cmd = [
            "docker", "exec",
            "-e", "GDB_ACTION=read",
            "-e", f"GDB_ADDR={hex(addr)}",
            "-e", f"GDB_LEN={length}",
            c_name,
            "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
        ]
        for attempt in range(2):
            try:
                res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=5)
                bytes_list = []
                for line in res.stdout.splitlines():
                    if ": " in line:
                        parts = line.split(": ")[1].split(" |")[0].split()
                        bytes_list.extend([int(b, 16) for b in parts])
                if bytes_list:
                    return bytes(bytes_list)
            except Exception:
                pass
            if attempt == 0:
                time.sleep(0.3)
        return b""

    try:
        ovl, diag = symbols.detect_overlay(read_mem, REPO_ROOT, return_details=True)
    except Exception:
        ovl, diag = None, None

    # If disagreement, retry once after 1 s before reporting None
    if diag and ovl is None:
        time.sleep(1.0)
        try:
            ovl2, diag2 = symbols.detect_overlay(read_mem, REPO_ROOT, return_details=True)
            if ovl2 is not None:
                return ovl2, None
            return None, diag2 or diag
        except Exception:
            return None, diag

    return ovl, diag
def take_screenshot(session, out_path):
    """Capture a screenshot to out_path."""
    c_name = emu.container_name(session)
    path_obj = Path(out_path).resolve()
    path_obj.parent.mkdir(parents=True, exist_ok=True)
    try:
        rel = path_obj.relative_to(REPO_ROOT)
        container_path = f"/dk64/{rel}"
    except ValueError:
        container_path = str(path_obj)
    cmd = ["docker", "exec", "-e", "DISPLAY=:99", c_name, "import", "-window", "root", container_path]
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return res.returncode == 0

def warp(session, target_map, target_exit=0, timeout=DEFAULT_TIMEOUT, settle=DEFAULT_SETTLE):
    """Execute warp by calling func_805FF378(target_map, target_exit)."""
    c_name = emu.container_name(session)
    if not emu.is_container_running(c_name):
        return {"status": "error", "error": f"Session '{session}' is not running"}

    initial_map = read_u32(session, ADDR_CURRENT_MAP)

    # 1. Execute in-container GDB warp script (with retry on transient gdb errors)
    cmd = [
        "docker", "exec",
        "-e", "WARP_ACTION=warp",
        "-e", f"WARP_TARGET_MAP={target_map}",
        "-e", f"WARP_TARGET_EXIT={target_exit}",
        c_name,
        "gdb-multiarch", "-batch", "-x", "/dk64/tools/emu/container/warp_gdb.py",
    ]
    warp_result = None
    last_err = ""
    for attempt in range(2):
        try:
            res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=timeout)
            if res.returncode == 0:
                for line in res.stdout.splitlines():
                    if line.startswith("WARP_RESULT:"):
                        try:
                            warp_result = json.loads(line[len("WARP_RESULT:"):])
                        except Exception:
                            pass
                if warp_result:
                    break
            last_err = res.stderr.strip() or res.stdout.strip()
        except subprocess.TimeoutExpired:
            subprocess.run(["docker", "exec", c_name, "pkill", "-9", "gdb-multiarch"])
            last_err = "Timeout waiting for safe point or call"
        if attempt == 0:
            subprocess.run(["docker", "exec", c_name, "pkill", "-9", "gdb-multiarch"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            time.sleep(1.0)
    shot_path = MAPS_DIR / f"map_0x{target_map:02X}.png"

    if not warp_result:
        take_screenshot(session, shot_path)
        return {
            "status": "error",
            "error": f"GDB script failed or returned no result: {last_err}",
            "initial_map": initial_map,
            "target_map": target_map,
            "loaded_map": initial_map,
            "screenshot": str(shot_path),
        }

    if warp_result.get("status") == "refused":
        take_screenshot(session, shot_path)
        return {
            "status": "refused",
            "error": warp_result.get("error", "Gate refused"),
            "initial_map": initial_map,
            "target_map": target_map,
            "loaded_map": initial_map,
            "screenshot": str(shot_path),
        }

    if warp_result.get("cancelled"):
        take_screenshot(session, shot_path)
        return {
            "status": "refused",
            "error": "Transition cancelled by func_80712F10 (map set to -1)",
            "initial_map": initial_map,
            "target_map": target_map,
            "loaded_map": initial_map,
            "screenshot": str(shot_path),
        }

    rewritten_to = None
    if warp_result.get("rewritten"):
        rewritten_to = (warp_result.get("next_map"), warp_result.get("next_exit"))

    # 2. Wait for transition to complete (poll ONE memory read per iteration)
    start_time = time.time()
    final_map = initial_map
    completed = False

    while (time.time() - start_time) < timeout:
        time.sleep(0.5)
        current = read_u32(session, ADDR_CURRENT_MAP)
        if current is not None:
            if target_map != initial_map and current != initial_map:
                final_map = current
                completed = True
                break
            elif target_map == initial_map and (time.time() - start_time) >= 2.0:
                final_map = current
                completed = True
                break

    if completed:
        if settle > 0:
            time.sleep(settle)
        settled_map = read_u32(session, ADDR_CURRENT_MAP)
        if settled_map is not None:
            final_map = settled_map
        take_screenshot(session, shot_path)
        ovl, diag = detect_current_overlay(session)
        status = "success" if final_map == target_map else "rewritten"
        return {
            "status": status,
            "initial_map": initial_map,
            "target_map": target_map,
            "target_exit": target_exit,
            "loaded_map": final_map,
            "rewritten_to": rewritten_to,
            "overlay": ovl,
            "disagreement": diag,
            "screenshot": str(shot_path),
        }
    else:
        # Timeout without map register changing
        if check_crash(session):
            take_screenshot(session, shot_path)
            return {
                "status": "crash",
                "error": "Game thread faulted during transition",
                "initial_map": initial_map,
                "target_map": target_map,
                "loaded_map": initial_map,
                "screenshot": str(shot_path),
            }
        is_stuck = check_game_stuck(session)
        take_screenshot(session, shot_path)
        ovl, diag = detect_current_overlay(session)
        if is_stuck:
            return {
                "status": "hang",
                "error": "Transition timed out and game loop is stuck",
                "initial_map": initial_map,
                "target_map": target_map,
                "loaded_map": initial_map,
                "overlay": ovl,
                "disagreement": diag,
                "screenshot": str(shot_path),
            }
        else:
            return {
                "status": "refused",
                "error": f"Transition did not occur (game remained on 0x{initial_map:02X})",
                "initial_map": initial_map,
                "target_map": target_map,
                "loaded_map": initial_map,
                "overlay": ovl,
                "disagreement": diag,
                "screenshot": str(shot_path),
            }
def cmd_warp(args):
    target_map = parse_map_target(args.map)
    target_exit = args.exit if args.exit is not None else 0
    session = args.name
    timeout = getattr(args, "timeout", DEFAULT_TIMEOUT)
    settle = getattr(args, "settle", DEFAULT_SETTLE)

    print(f"Warping session '{session}' to map 0x{target_map:02X} ({target_map}), exit {target_exit} (timeout={timeout}s, settle={settle}s)...")
    res = warp(session, target_map, target_exit, timeout=timeout, settle=settle)

    status = res.get("status")
    if status in ("success", "rewritten"):
        loaded = res.get("loaded_map")
        ovl = res.get("overlay") or "none"
        shot = res.get("screenshot")
        diag = res.get("disagreement")
        print(f"Success: Loaded map 0x{loaded:02X} ({loaded})")
        if res.get("rewritten_to"):
            r_map, r_exit = res.get("rewritten_to")
            print(f"  Note: func_80712F10 rewrote target to map 0x{r_map:02X}, exit {r_exit}")
        print(f"  Overlay:    {ovl}")
        if diag:
            print(f"  Overlay Note: {diag}")
        print(f"  Screenshot: {shot}")
        return 0
    elif status == "refused":
        print(f"Gate Refused: {res.get('error')}", file=sys.stderr)
        return 1
    elif status == "crash":
        print(f"Crash: {res.get('error')}", file=sys.stderr)
        return 2
    elif status == "hang":
        print(f"Hang: {res.get('error')}. Loaded map: 0x{res.get('loaded_map', 0):02X}", file=sys.stderr)
        return 3
    else:
        print(f"Error: {res.get('error')}", file=sys.stderr)
        return 4

def get_session_vnc_port(session):
    """Discover host VNC port for a running container."""
    c_name = emu.container_name(session)
    res = subprocess.run(["docker", "port", c_name, "5900/tcp"], capture_output=True, text=True)
    if res.returncode == 0 and res.stdout.strip():
        try:
            return int(res.stdout.strip().split(":")[-1])
        except Exception:
            pass
    return None

def restart_sweep_session(session, state_label, vnc_port=None):
    """Restart a session into the given library state during sweep recovery."""
    print(f"  [recovery] Restarting {session} into state '{state_label}'...")
    emu.cmd_stop(argparse.Namespace(name=session))
    time.sleep(1.0)
    states.cmd_load(argparse.Namespace(label=state_label, name=session, vnc_port=vnc_port))
    time.sleep(2.0)

def cmd_sweep(args):
    session = args.name
    state_label = args.state
    vnc_port = args.vnc_port
    timeout = getattr(args, "timeout", DEFAULT_TIMEOUT)
    settle = getattr(args, "settle", DEFAULT_SETTLE)

    from_id = int(args.from_id, 0)
    to_id = int(args.to_id, 0)

    bs_file = states.LIBRARY_DIR / f"{state_label}.bs"
    if not bs_file.exists():
        sys.exit(f"Error: State '{state_label}' not found in library ({bs_file})")

    out_path = Path(args.out).resolve()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    MAPS_DIR.mkdir(parents=True, exist_ok=True)

    c_name = emu.container_name(session)
    if not emu.is_container_running(c_name):
        print(f"Starting session '{session}' with state '{state_label}'...")
        res = states.cmd_load(argparse.Namespace(label=state_label, name=session, vnc_port=vnc_port))
        if res != 0:
            sys.exit(f"Failed to start session '{session}'")
        time.sleep(2.0)

    if vnc_port is None:
        vnc_port = get_session_vnc_port(session)

    print(f"Starting map sweep from 0x{from_id:02X} to 0x{to_id:02X} using state '{state_label}' (timeout={timeout}s, settle={settle}s)...")

    entries = []

    for m_id in range(from_id, to_id + 1):
        # 1. Restore library state before each warp
        load_res = states.cmd_load(argparse.Namespace(label=state_label, name=session, vnc_port=vnc_port))
        if load_res != 0 or not emu.is_container_running(c_name):
            restart_sweep_session(session, state_label, vnc_port)
        else:
            time.sleep(0.8)
            curr = read_u32(session, ADDR_CURRENT_MAP)
            if state_label == "training_grounds" and curr != 0xB0:
                emu.cmd_press(argparse.Namespace(name=session, buttons="load", ms=150))
                time.sleep(1.0)
                curr = read_u32(session, ADDR_CURRENT_MAP)
                if curr != 0xB0:
                    restart_sweep_session(session, state_label, vnc_port)
        res = warp(session, m_id, target_exit=0, timeout=timeout, settle=settle)
        raw_status = res.get("status")
        loaded_val = res.get("loaded_map")
        ovl = res.get("overlay") or "none"
        diag = res.get("disagreement")
        notes_parts = []

        if raw_status == "success":
            status = "success"
            if res.get("rewritten_to"):
                r_map, r_exit = res.get("rewritten_to")
                notes_parts.append(f"rewritten to 0x{r_map:02X}")
        elif raw_status == "rewritten":
            status = "rewritten"
            notes_parts.append(f"loaded 0x{loaded_val:02X} instead of 0x{m_id:02X}")
        elif raw_status == "hang":
            status = "hang"
            notes_parts.append(res.get("error", "timeout waiting for transition"))
        elif raw_status == "crash":
            status = "crash"
            notes_parts.append(res.get("error", "thread faulted"))
        elif raw_status == "refused":
            status = "refused"
            notes_parts.append(res.get("error", "gate refused"))
        else:
            status = "crash" if raw_status == "error" else (raw_status or "hang")
            if res.get("error"):
                notes_parts.append(res.get("error"))

        if diag:
            notes_parts.append(f"overlay disagreement: {diag}")

        notes = "; ".join(notes_parts).replace("\n", " ").replace("\r", " ").strip()
        print(f"[{m_id:3d}/0x{m_id:02X}] {status.upper()} -> loaded {loaded_str}, overlay: {ovl}" + (f" ({notes})" if notes else ""))

        entries.append({
            "id": f"0x{m_id:02X}",
            "name": "",
            "loaded": loaded_str,
            "overlay": ovl,
            "status": status,
            "notes": notes,
        })

        # Restart session container ONLY for real hangs or crashes
        if status in ("crash", "hang") or not emu.is_container_running(c_name):
            restart_sweep_session(session, state_label, vnc_port)

    # Write ONLY to args.out (never write tools/emu/maps.tsv)
    with open(out_path, "w") as f:
        f.write("id\tname\tloaded\toverlay\tstatus\tnotes\n")
        for e in entries:
            f.write(f"{e['id']}\t{e['name']}\t{e['loaded']}\t{e['overlay']}\t{e['status']}\t{e['notes']}\n")

    print(f"Wrote {len(entries)} entries to {out_path}")
def main():
    parser = argparse.ArgumentParser(description="DK64 Map Warp Tool")
    parser.add_argument("--name", default=DEFAULT_SESSION, help=f"Session name (default: {DEFAULT_SESSION})")

    subparsers = parser.add_subparsers(dest="subcommand")

    p_sweep = subparsers.add_parser("sweep", help="Sweep map ID range")
    p_sweep.add_argument("--name", default=DEFAULT_SESSION, help=f"Session name (default: {DEFAULT_SESSION})")
    p_sweep.add_argument("--state", required=True, help="Library save state label to restore before each warp")
    p_sweep.add_argument("--from", dest="from_id", required=True, help="Start map ID (hex or dec, e.g. 0x22)")
    p_sweep.add_argument("--to", dest="to_id", required=True, help="End map ID (hex or dec, e.g. 0x24)")
    p_sweep.add_argument("--out", required=True, help="Output TSV file path")
    p_sweep.add_argument("--vnc-port", type=int, default=None, help="VNC port for session / recovery")
    p_sweep.add_argument("--timeout", type=float, default=DEFAULT_TIMEOUT, help=f"Timeout waiting for transition in seconds (default: {DEFAULT_TIMEOUT})")
    p_sweep.add_argument("--settle", type=float, default=DEFAULT_SETTLE, help=f"Settle delay after transition in seconds (default: {DEFAULT_SETTLE})")
    p_warp = subparsers.add_parser("warp", help="Warp to a map")
    p_warp.add_argument("--name", default=DEFAULT_SESSION, help=f"Session name (default: {DEFAULT_SESSION})")
    p_warp.add_argument("--timeout", type=float, default=DEFAULT_TIMEOUT, help=f"Timeout waiting for transition in seconds (default: {DEFAULT_TIMEOUT})")
    p_warp.add_argument("--settle", type=float, default=DEFAULT_SETTLE, help=f"Settle delay after transition in seconds (default: {DEFAULT_SETTLE})")
    p_warp.add_argument("map", help="Target map ID (hex e.g. 0x22, dec, or name)")
    p_warp.add_argument("exit", nargs="?", type=int, default=0, help="Target exit ID (default: 0)")
    args_list = sys.argv[1:]
    if args_list and args_list[0] not in ["sweep", "warp", "-h", "--help"]:
        if "--name" in args_list:
            idx = args_list.index("--name")
            name_val = args_list[idx + 1]
            remaining = [a for i, a in enumerate(args_list) if i not in (idx, idx + 1)]
            args_list = ["warp", "--name", name_val] + remaining
        else:
            args_list = ["warp"] + args_list

    args = parser.parse_args(args_list)

    if args.subcommand == "sweep":
        cmd_sweep(args)
    elif args.subcommand == "warp":
        sys.exit(cmd_warp(args))
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
