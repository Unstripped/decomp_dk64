#!/usr/bin/env python3
"""DK64 Save-State Library Manager.

Manage named save states for emulator sessions, bookmarks, and automated runs.
Storage layout:
  emu/states/library/<LABEL>.bs    - State snapshot binary
  emu/states/library/<LABEL>.json  - Metadata (map, overlay, timestamp, commit, note)
  emu/states/library/<LABEL>.png   - Screenshot captured at save time
"""

import argparse
from datetime import datetime
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time
from typing import Any, Dict, List, Optional, Tuple

SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
LIBRARY_DIR = REPO_ROOT / "emu" / "states" / "library"

ARES_COMMIT = "6b65e1beacf8b2af66aaee72541ab154382b7e6a"
CURRENT_MAP_ADDR = 0x8076A0A8
OVERLAY_BASE_ADDR = 0x80024000
OVERLAY_PROBE_SIZE = 512

# Ensure library dir exists
LIBRARY_DIR.mkdir(parents=True, exist_ok=True)

# Add tools/emu to import path
sys.path.insert(0, str(SCRIPT_DIR))
import emu
import symbols


def get_session_state_dirs(session: str = "main") -> List[Path]:
    """Return all directories where ares might save/load state files for a session."""
    return [emu.get_session_states_dir(session)]


def get_state_dirs(session: str = "main") -> List[Path]:
    """Return all directories where ares might save/load state files for a session."""
    return get_session_state_dirs(session)


def find_slot_file(slot: int, session: str = "main") -> Optional[Path]:
    """Find state file for a given slot in the session's state directory."""
    for d in get_session_state_dirs(session):
        for prefix in ["baserom.us", "dk64.us"]:
            candidate = d / f"{prefix}.bs{slot}"
            if candidate.exists():
                return candidate
    return None


def find_latest_state_file(session: str = "main") -> Optional[Path]:
    """Find the most recently modified state file for a session."""
    latest: Optional[Path] = None
    latest_mtime: float = -1.0
    for d in get_session_state_dirs(session):
        if not d.exists():
            continue
        for candidate in d.glob("*.bs*"):
            if candidate.is_file() and not candidate.is_symlink():
                mtime = candidate.stat().st_mtime
                if mtime > latest_mtime:
                    latest_mtime = mtime
                    latest = candidate
    return latest


def stage_state_to_slot(state_file: Path, slot: int = 1, session: str = "main") -> None:
    """Copy a library state file into the session's state directory for slot N."""
    for d in get_session_state_dirs(session):
        d.mkdir(parents=True, exist_ok=True)
        for prefix in ["baserom.us", "dk64.us"]:
            target = d / f"{prefix}.bs{slot}"
            shutil.copyfile(state_file, target)

def query_session_map(session: str) -> Optional[int]:
    """Read current map ID (0x8076A0A8) from running session."""
    c_name = emu.container_name(session)
    if not emu.is_container_running(c_name):
        return None
    try:
        res = subprocess.run(
            [
                "docker", "exec",
                "-e", f"GDB_PORT={emu.GDB_PORT}",
                "-e", "GDB_ACTION=read32",
                "-e", f"GDB_ADDR={hex(CURRENT_MAP_ADDR)}",
                c_name,
                "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
            ],
            capture_output=True,
            text=True,
            timeout=5,
        )
        for line in res.stdout.splitlines():
            line = line.strip()
            if "in ?? ()" in line or "warning:" in line.lower():
                continue
            if line.startswith("0x"):
                parts = line.split()
                return int(parts[0], 16)
    except Exception:
        pass
    return None


def query_session_overlay(session: str) -> Optional[str]:
    """Detect active overlay in running session."""
    c_name = emu.container_name(session)
    if not emu.is_container_running(c_name):
        return None

    def read_mem(addr: int, n: int) -> bytes:
        res = subprocess.run(
            [
                "docker", "exec",
                "-e", f"GDB_PORT={emu.GDB_PORT}",
                "-e", "GDB_ACTION=read",
                "-e", f"GDB_ADDR={hex(addr)}",
                "-e", f"GDB_LEN={n}",
                c_name,
                "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
            ],
            capture_output=True,
            text=True,
            timeout=5,
        )
        bytes_list = []
        for line in res.stdout.splitlines():
            if ":" in line and "|" in line:
                hex_part = line.split(":")[1].split("|")[0].strip()
                bytes_list.extend(int(b, 16) for b in hex_part.split())
        return bytes(bytes_list)
    try:
        return symbols.detect_overlay(read_mem, REPO_ROOT)
    except Exception:
        return None


def cmd_save(args: argparse.Namespace) -> int:
    """Trigger save state on running session and archive it to library."""
    c_name = emu.container_name(args.name)
    if not emu.is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    label = args.label
    bs_target = LIBRARY_DIR / f"{label}.bs"
    json_target = LIBRARY_DIR / f"{label}.json"
    png_target = LIBRARY_DIR / f"{label}.png"

    current_slot = emu.get_current_slot(args.name)
    t_before = time.time()

    # Trigger save hotkey (F5)
    emu.cmd_press(argparse.Namespace(name=args.name, buttons="save", ms=100))
    time.sleep(0.6)

    # Find the newly saved file
    slot_file = find_slot_file(current_slot, session=args.name)
    if not slot_file or slot_file.stat().st_mtime < (t_before - 2.0):
        slot_file = find_latest_state_file(session=args.name)

    if not slot_file or not slot_file.exists():
        print(f"Error: Could not locate saved state file on disk", file=sys.stderr)
        return 1

    # Copy state to library
    shutil.copyfile(slot_file, bs_target)

    # Query current map & overlay
    current_map = query_session_map(args.name)
    overlay = query_session_overlay(args.name)

    # Capture screenshot
    try:
        emu.cmd_screenshot(argparse.Namespace(name=args.name, output=str(png_target)))
    except Exception:
        pass

    metadata = {
        "label": label,
        "note": args.note or "",
        "map_id": current_map,
        "map_hex": f"0x{current_map:08x}" if current_map is not None else None,
        "overlay": overlay,
        "timestamp": datetime.now().isoformat(),
        "ares_commit": ARES_COMMIT,
        "size_bytes": bs_target.stat().st_size,
    }
    with open(json_target, "w") as f:
        json.dump(metadata, f, indent=2)

    map_display = f"{metadata['map_hex']} ({current_map})" if current_map is not None else "unknown"
    print(f"Saved state '{label}' to library:")
    print(f"  State:     {bs_target} ({metadata['size_bytes']:,} bytes)")
    print(f"  Map:       {map_display}")
    print(f"  Overlay:   {overlay or 'none'}")
    if png_target.exists():
        print(f"  Picture:   {png_target}")
    if args.note:
        print(f"  Note:      {args.note}")
    return 0


def cmd_import(args: argparse.Namespace) -> int:
    """Import an existing slot file (e.g. from in-emulator F5 hotkey) into the library."""
    slot = args.slot
    label = args.label
    session_name = args.name if args.name else emu.DEFAULT_SESSION
    slot_file = find_slot_file(slot, session=session_name)
    if not slot_file:
        print(f"Error: Slot {slot} file not found in state directories", file=sys.stderr)
        return 1

    bs_target = LIBRARY_DIR / f"{label}.bs"
    json_target = LIBRARY_DIR / f"{label}.json"
    png_target = LIBRARY_DIR / f"{label}.png"

    shutil.copyfile(slot_file, bs_target)

    current_map = query_session_map(args.name) if args.name else None
    overlay = query_session_overlay(args.name) if args.name else None

    if args.name and emu.is_container_running(emu.container_name(args.name)):
        try:
            emu.cmd_screenshot(argparse.Namespace(name=args.name, output=str(png_target)))
        except Exception:
            pass

    metadata = {
        "label": label,
        "note": args.note or "",
        "map_id": current_map,
        "map_hex": f"0x{current_map:08x}" if current_map is not None else None,
        "overlay": overlay,
        "timestamp": datetime.now().isoformat(),
        "ares_commit": ARES_COMMIT,
        "size_bytes": bs_target.stat().st_size,
    }
    with open(json_target, "w") as f:
        json.dump(metadata, f, indent=2)

    print(f"Imported slot {slot} as '{label}' in library:")
    print(f"  State:  {bs_target}")
    return 0


def cmd_load(args: argparse.Namespace) -> int:
    """Load a state into a running session, or start a new session at that state."""
    label = args.label
    bs_target = LIBRARY_DIR / f"{label}.bs"
    if not bs_target.exists():
        print(f"Error: State '{label}' not found in library ({bs_target})", file=sys.stderr)
        return 1

    c_name = emu.container_name(args.name)
    if emu.is_container_running(c_name):
        current_slot = emu.get_current_slot(args.name)
        # Stage to active slot
        stage_state_to_slot(bs_target, current_slot, session=args.name)
        time.sleep(0.1)
        # Press load (F7)
        emu.cmd_press(argparse.Namespace(name=args.name, buttons="load", ms=100))
        time.sleep(0.5)
        print(f"Loaded '{label}' into running session '{args.name}' (slot {current_slot})")
    else:
        # Session is not running; stage to slot 1 and start
        stage_state_to_slot(bs_target, 1, session=args.name)
        start_args = argparse.Namespace(
            name=args.name,
            rom=None,
            state=str(bs_target),
            slot=1,
            vnc_port=args.vnc_port,
        )
        print(f"Starting session '{args.name}' with state '{label}'...")
        res = emu.cmd_start(start_args)
        if res != 0:
            return res
        print(f"Session '{args.name}' started and loaded with '{label}'.")
    return 0


def cmd_list(args: argparse.Namespace) -> int:
    """List all states in library."""
    json_files = sorted(LIBRARY_DIR.glob("*.json"))
    if not json_files:
        print("Save state library is empty.")
        return 0

    print(f"{'Label':<16} {'Map':<14} {'Overlay':<12} {'Size':<10} {'Timestamp':<20} Note")
    print("-" * 85)
    for jf in json_files:
        try:
            with open(jf, "r") as f:
                meta = json.load(f)
        except Exception:
            continue
        label = meta.get("label", jf.stem)
        map_hex = meta.get("map_hex") or "-"
        map_id = meta.get("map_id")
        map_str = f"{map_hex}" + (f" ({map_id})" if map_id is not None else "")
        overlay = meta.get("overlay") or "none"
        size_bytes = meta.get("size_bytes", 0)
        size_str = f"{size_bytes / (1024*1024):.1f} MB" if size_bytes else "-"
        ts = meta.get("timestamp", "")[:19].replace("T", " ")
        note = meta.get("note", "")
        print(f"{label:<16} {map_str:<14} {overlay:<12} {size_str:<10} {ts:<20} {note}")
    return 0


def cmd_rm(args: argparse.Namespace) -> int:
    """Remove a state from library."""
    label = args.label
    bs_target = LIBRARY_DIR / f"{label}.bs"
    json_target = LIBRARY_DIR / f"{label}.json"
    png_target = LIBRARY_DIR / f"{label}.png"

    deleted = 0
    for p in [bs_target, json_target, png_target]:
        if p.exists():
            p.unlink()
            deleted += 1

    if deleted > 0:
        print(f"Removed state '{label}' from library.")
        return 0
    else:
        print(f"State '{label}' not found in library.", file=sys.stderr)
        return 1


def main() -> int:
    parser = argparse.ArgumentParser(description="DK64 Save-State Library", prog="tools/emu/states.py")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # save
    p_save = subparsers.add_parser("save", help="Save running session to library")
    p_save.add_argument("label", help="State label name (e.g. title, krool_cutscene)")
    p_save.add_argument("--name", default=emu.DEFAULT_SESSION, help="Session name (default: main)")
    p_save.add_argument("--note", default="", help="Note or description for this state")
    p_save.set_defaults(func=cmd_save)

    # list
    p_list = subparsers.add_parser("list", help="List all saved states in library")
    p_list.set_defaults(func=cmd_list)

    # load
    p_load = subparsers.add_parser("load", help="Load library state into running session or start session")
    p_load.add_argument("label", help="State label to load")
    p_load.add_argument("--name", default=emu.DEFAULT_SESSION, help="Session name (default: main)")
    p_load.add_argument("--vnc-port", type=int, default=None, help="VNC port if starting a new session")
    p_load.set_defaults(func=cmd_load)

    # rm
    p_rm = subparsers.add_parser("rm", help="Remove state from library")
    p_rm.add_argument("label", help="State label to delete")
    p_rm.set_defaults(func=cmd_rm)

    # import
    p_import = subparsers.add_parser("import", help="Import an existing slot file into library")
    p_import.add_argument("label", help="State label to save as")
    p_import.add_argument("--slot", type=int, required=True, help="Slot number (1-9)")
    p_import.add_argument("--name", default=None, help="Running session name to query map/overlay/screenshot")
    p_import.add_argument("--note", default="", help="Note or description")
    p_import.set_defaults(func=cmd_import)

    args = parser.parse_args()
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
