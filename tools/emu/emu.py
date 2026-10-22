#!/usr/bin/env python3
"""DK64 Emulator CLI - Dockerized ares emulator with GDB remote server.

Provides headless execution of Donkey Kong 64 (USA) with:
  - angrylion CPU video renderer (pixel-accurate, no GPU required)
  - GDB remote server on port 9123 for breakpoints, memory inspection & warping
  - x11vnc for interactive viewing over VNC (port 5900)
  - xdotool for button inputs, holds, and save states
  - gdb-multiarch inside the container for symbol lookup and debugging

Usage:
  python3 tools/emu/emu.py build
  python3 tools/emu/emu.py start [--name main] [--vnc-port 5900]
  python3 tools/emu/emu.py status
  python3 tools/emu/emu.py screenshot out.png
  python3 tools/emu/emu.py press start
  python3 tools/emu/emu.py read 0x8000DCC4 16
  python3 tools/emu/emu.py read32 0x80767A40
  python3 tools/emu/emu.py write 0x80746A30 deadbeef
  python3 tools/emu/emu.py gdb -- 'break controllerUpdate' 'continue' 'info registers pc'
  python3 tools/emu/emu.py savestate --slot 1
  python3 tools/emu/emu.py loadstate --slot 1
  python3 tools/emu/emu.py stop
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

# Repo root detection
SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]

# Default constants
IMAGE_NAME = "dk64-emu"
DEFAULT_SESSION = "main"
CONTAINER_PREFIX = "dk64-emu-"
DEFAULT_VNC_PORT = 5900
GDB_PORT = 9123

# Keyboard mapping: Button name -> xdotool key symbol
# Configured in ares via default_settings.bml
BUTTON_MAP = {
    # N64 action buttons
    "start": "Return",
    "enter": "Return",
    "return": "Return",
    "a": "k",
    "b": "j",
    "z": "space",
    "space": "space",
    "l": "q",
    "r": "e",
    # Analog stick (WASD)
    "up": "w",
    "down": "s",
    "left": "a",
    "right": "d",
    "stick_up": "w",
    "stick_down": "s",
    "stick_left": "a",
    "stick_right": "d",
    "stick-up": "w",
    "stick-down": "s",
    "stick-left": "a",
    "stick-right": "d",
    # C-Buttons (Arrow keys)
    "c-up": "Up",
    "c-down": "Down",
    "c-left": "Left",
    "c-right": "Right",
    "cup": "Up",
    "cdown": "Down",
    "cleft": "Left",
    "cright": "Right",
    "c_up": "Up",
    "c_down": "Down",
    "c_left": "Left",
    "c_right": "Right",
    # D-Pad (Numbers 1-4)
    "d-up": "1",
    "d-down": "2",
    "d-left": "3",
    "d-right": "4",
    "dup": "1",
    "ddown": "2",
    "dleft": "3",
    "dright": "4",
    # Emulator Hotkeys
    "save": "F5",
    "load": "F7",
    "slot_dec": "F6",
    "slot_inc": "F8",
}


def container_name(session: str) -> str:
    return f"{CONTAINER_PREFIX}{session}"

def get_session_states_dir(session: str) -> Path:
    """Return the save-state directory for a session."""
    d = REPO_ROOT / "emu" / "sessions" / session / "states"
    d.mkdir(parents=True, exist_ok=True)
    sym = d / "Nintendo 64"
    if not sym.exists() and not sym.is_symlink():
        try:
            sym.symlink_to(".")
        except OSError:
            pass
    return d



def get_slot_tracker_path(session: str) -> Path:
    tracker_dir = REPO_ROOT / "emu"
    tracker_dir.mkdir(parents=True, exist_ok=True)
    return tracker_dir / f".slot_{session}"


def get_current_slot(session: str) -> int:
    p = get_slot_tracker_path(session)
    if p.exists():
        try:
            return int(p.read_text().strip())
        except Exception:
            pass
    return 1


def set_current_slot(session: str, slot: int):
    p = get_slot_tracker_path(session)
    p.write_text(str(slot))


def run_cmd(cmd, check=True, capture=False, text=True):
    if capture:
        return subprocess.run(cmd, check=check, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=text)
    return subprocess.run(cmd, check=check)


def is_container_running(c_name: str) -> bool:
    res = subprocess.run(
        ["docker", "inspect", "-f", "{{.State.Running}}", c_name],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    return res.returncode == 0 and res.stdout.strip() == "true"


def cmd_build(args):
    """Build the docker emulator image."""
    dockerfile = SCRIPT_DIR / "Dockerfile"
    if not dockerfile.exists():
        print(f"Error: Dockerfile not found at {dockerfile}", file=sys.stderr)
        return 1

    cmd = ["docker", "build", "-t", IMAGE_NAME, "-f", str(dockerfile), str(REPO_ROOT)]
    if getattr(args, "no_cache", False):
        cmd.append("--no-cache")

    print(f"Building Docker image '{IMAGE_NAME}' from {dockerfile}...")
    res = run_cmd(cmd, check=False)
    if res.returncode != 0:
        print("Docker build failed", file=sys.stderr)
        return res.returncode
    print(f"Successfully built image '{IMAGE_NAME}'.")
    return 0


def cmd_start(args):
    """Start an emulator session container."""
    c_name = container_name(args.name)

    if is_container_running(c_name):
        print(f"Session '{args.name}' ({c_name}) is already running.")
        cmd_status(args)
        return 0

    # Clean up stale stopped container if present
    subprocess.run(["docker", "rm", "-f", c_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Determine ROM path inside container
    rom = args.rom
    if not rom:
        if (REPO_ROOT / "baserom.us.z64").exists():
            rom = "/dk64/baserom.us.z64"
        elif (REPO_ROOT / "build/dk64.us.z64").exists():
            rom = "/dk64/build/dk64.us.z64"
        else:
            print("Error: No ROM found at baserom.us.z64 or build/dk64.us.z64", file=sys.stderr)
            return 1
    elif not rom.startswith("/"):
        rom = f"/dk64/{rom}"

    # Determine VNC port
    vnc_port = args.vnc_port
    if vnc_port is None:
        if args.name == DEFAULT_SESSION:
            vnc_port = DEFAULT_VNC_PORT
        else:
            # Assign an unused port starting from 5901
            for p in range(5901, 5950):
                res = subprocess.run(["nc", "-z", "127.0.0.1", str(p)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                if res.returncode != 0:
                    vnc_port = p
                    break
            if vnc_port is None:
                vnc_port = 5901

    # Prepare save state if --state or --slot specified
    session_states_dir = get_session_states_dir(args.name)
    slot_arg = None
    if args.slot:
        slot_arg = str(args.slot)
        set_current_slot(args.name, args.slot)
    elif args.state:
        state_file = Path(args.state).resolve()
        if not state_file.exists():
            print(f"Error: Save state file not found: {state_file}", file=sys.stderr)
            return 1
        # Copy to slot 1 in session states dir
        for prefix in ["baserom.us", "dk64.us"]:
            shutil.copyfile(state_file, session_states_dir / f"{prefix}.bs1")
        slot_arg = "1"
        set_current_slot(args.name, 1)

    # Ensure host directories exist
    (REPO_ROOT / "emu" / "screenshots").mkdir(parents=True, exist_ok=True)
    (REPO_ROOT / "emu" / "logs").mkdir(parents=True, exist_ok=True)

    docker_args = [
        "docker", "run", "-d",
        "--name", c_name,
        "-v", f"{REPO_ROOT}:/dk64",
        "-p", f"127.0.0.1:{vnc_port}:5900",
        IMAGE_NAME,
        "--name", args.name,
        "--save-path", f"/dk64/emu/sessions/{args.name}/states/",
        rom,
    ]
    if slot_arg:
        docker_args.extend(["--slot", slot_arg])

    print(f"Starting emulator session '{args.name}' ({c_name})...")
    res = subprocess.run(docker_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if res.returncode != 0:
        print(f"Failed to start container: {res.stderr.strip()}", file=sys.stderr)
        return res.returncode

    # Wait until GDB server is up inside container
    print("Waiting for emulator to boot and GDB remote server to listen...")
    gdb_ready = False
    for _ in range(60):
        probe = subprocess.run(
            ["docker", "exec", c_name, "nc", "-z", "127.0.0.1", str(GDB_PORT)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        if probe.returncode == 0:
            gdb_ready = True
            break
        time.sleep(0.5)

    if not gdb_ready:
        print("Warning: GDB remote port 9123 did not respond within 30s. Checking logs...", file=sys.stderr)
        subprocess.run(["docker", "logs", "--tail", "20", c_name])
        return 1

    print(f"Emulator '{args.name}' is up and running!")
    print(f"  VNC Display:   open vnc://127.0.0.1:{vnc_port}")
    print(f"  VNC Password:  dk64")
    print(f"  GDB Remote:    internal port {GDB_PORT} (use 'python3 tools/emu/emu.py gdb')")
    return 0


def cmd_stop(args):
    """Stop and remove an emulator session container."""
    c_name = container_name(args.name)
    print(f"Stopping session '{args.name}' ({c_name})...")
    res = subprocess.run(["docker", "stop", "-t", "2", c_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    subprocess.run(["docker", "rm", "-f", c_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if res.returncode == 0:
        print(f"Session '{args.name}' stopped.")
    else:
        print(f"Session '{args.name}' was not running.")
    return 0


def cmd_status(args):
    """Show status of an emulator session."""
    c_name = container_name(args.name)
    res = subprocess.run(
        ["docker", "inspect", c_name],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if res.returncode != 0:
        print(f"Session '{args.name}' ({c_name}): NOT RUNNING")
        return 1

    running = is_container_running(c_name)
    state_str = "RUNNING" if running else "STOPPED"
    print(f"Session '{args.name}' ({c_name}): {state_str}")

    if running:
        # Check port mappings
        p_res = subprocess.run(
            ["docker", "port", c_name, "5900"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
        vnc_mapped = p_res.stdout.strip()
        print(f"  VNC Host Port: {vnc_mapped}")

        # Check GDB reachability inside container
        gdb_check = subprocess.run(
            ["docker", "exec", c_name, "nc", "-z", "127.0.0.1", str(GDB_PORT)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        gdb_status = "OK (port 9123)" if gdb_check.returncode == 0 else "OFFLINE"
        print(f"  GDB Server:    {gdb_status}")
    return 0


def cmd_list(args):
    """List all emulator containers."""
    res = subprocess.run(
        ["docker", "ps", "-a", "--filter", f"name={CONTAINER_PREFIX}", "--format", "table {{.Names}}\t{{.Status}}\t{{.Ports}}"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    print(res.stdout)
    return 0


def cmd_screenshot(args):
    """Capture a PNG screenshot of the emulator virtual display."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    out_path = Path(args.output).resolve()
    out_path.parent.mkdir(parents=True, exist_ok=True)

    # Capture directly to stdout from xwd / import
    res = subprocess.run(
        ["docker", "exec", "-e", "DISPLAY=:99", c_name, "import", "-window", "root", "png:-"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    if res.returncode != 0:
        print(f"Failed to capture screenshot: {res.stderr.decode()}", file=sys.stderr)
        return res.returncode

    out_path.write_bytes(res.stdout)
    print(f"Screenshot saved to {out_path} ({len(res.stdout)} bytes)")
    return 0


def translate_buttons(buttons_str: str):
    """Parse comma-separated or space-separated button names to xdotool keys."""
    raw = [b.strip().lower() for b in re.split(r"[,+\s]+", buttons_str) if b.strip()]
    keys = []
    for b in raw:
        if b in BUTTON_MAP:
            keys.append(BUTTON_MAP[b])
        else:
            # Pass verbatim if unrecognized (e.g. Return, space, F5)
            keys.append(b)
    return keys


def cmd_press(args):
    """Press buttons via xdotool."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    keys = translate_buttons(args.buttons)
    if not keys:
        print("No valid buttons specified", file=sys.stderr)
        return 1

    ms = args.ms if args.ms is not None else 100
    sec = ms / 1000.0

    # Build atomic xdotool command: keydown k1 keydown k2 sleep 0.1 keyup k1 keyup k2
    xdo = []
    for k in keys:
        xdo.extend(["keydown", k])
    xdo.extend(["sleep", str(sec)])
    for k in keys:
        xdo.extend(["keyup", k])

    cmd = ["docker", "exec", "-e", "DISPLAY=:99", c_name, "xdotool"] + xdo
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if res.returncode != 0:
        print(f"Error sending input: {res.stderr.strip()}", file=sys.stderr)
        return res.returncode
    return 0


def cmd_hold(args):
    """Hold buttons down."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    keys = translate_buttons(args.buttons)
    xdo = []
    for k in keys:
        xdo.extend(["keydown", k])

    cmd = ["docker", "exec", "-e", "DISPLAY=:99", c_name, "xdotool"] + xdo
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return res.returncode


def cmd_release(args):
    """Release buttons."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    keys = translate_buttons(args.buttons)
    xdo = []
    for k in keys:
        xdo.extend(["keyup", k])

    cmd = ["docker", "exec", "-e", "DISPLAY=:99", c_name, "xdotool"] + xdo
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return res.returncode


def cmd_read(args):
    """Hex dump memory from emulator via GDB."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    cmd = [
        "docker", "exec",
        "-e", "GDB_ACTION=read",
        "-e", f"GDB_ADDR={args.addr}",
        "-e", f"GDB_LEN={args.len}",
        c_name,
        "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
    ]
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if res.returncode != 0:
        print(res.stderr, file=sys.stderr)
        return res.returncode
    clean_lines = [l for l in res.stdout.splitlines() if "in ?? ()" not in l and not l.startswith("warning:")]
    print("\n".join(clean_lines))
    return 0


def cmd_read32(args):
    """Read a 32-bit big-endian word from emulator memory."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    cmd = [
        "docker", "exec",
        "-e", "GDB_ACTION=read32",
        "-e", f"GDB_ADDR={args.addr}",
        c_name,
        "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
    ]
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if res.returncode != 0:
        print(res.stderr, file=sys.stderr)
        return res.returncode
    clean_lines = [l for l in res.stdout.splitlines() if "in ?? ()" not in l and not l.startswith("warning:")]
    print("\n".join(clean_lines).strip())
    return 0


def cmd_write(args):
    """Write hex bytes to emulator memory."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    cmd = [
        "docker", "exec",
        "-e", "GDB_ACTION=write",
        "-e", f"GDB_ADDR={args.addr}",
        "-e", f"GDB_DATA={args.hexbytes}",
        c_name,
        "gdb-multiarch", "-batch", "-x", "/opt/emu/gdb_helper.py",
    ]
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if res.returncode != 0:
        print(res.stderr, file=sys.stderr)
        return res.returncode
    clean_lines = [l for l in res.stdout.splitlines() if "in ?? ()" not in l and not l.startswith("warning:")]
    print("\n".join(clean_lines).strip())
    return 0


def cmd_gdb(args):
    """Run gdb-multiarch inside the container connected to the emulator."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    gdb_args = [
        "gdb-multiarch",
        "-ex", "set architecture mips:4000",
    ]

    # Load base symbols
    if (REPO_ROOT / "build/dk64.us.elf").exists():
        gdb_args.extend(["-ex", "file /dk64/build/dk64.us.elf"])
    if (REPO_ROOT / "build/global.elf").exists():
        gdb_args.extend(["-ex", "add-symbol-file /dk64/build/global.elf"])

    # Load overlay symbol file if requested
    if args.overlay:
        ovl_elf = f"/dk64/build/{args.overlay}.elf"
        gdb_args.extend(["-ex", f"add-symbol-file {ovl_elf}"])

    # Connect to target
    gdb_args.extend(["-ex", f"target remote 127.0.0.1:{GDB_PORT}"])

    if args.script:
        script_path = Path(args.script).resolve()
        try:
            rel = script_path.relative_to(REPO_ROOT)
            container_script = f"/dk64/{rel}"
        except ValueError:
            container_script = f"/tmp/{script_path.name}"
            subprocess.run(["docker", "cp", str(script_path), f"{c_name}:{container_script}"], check=True)
        gdb_args.extend(["-x", container_script])
        cmd = ["docker", "exec", c_name] + gdb_args
        return subprocess.run(cmd).returncode

    if args.cmds:
        # Non-interactive batch commands
        batch_gdb = ["gdb-multiarch", "-batch"] + gdb_args[1:]
        for c in args.cmds:
            batch_gdb.extend(["-ex", c])
        # Ensure clean detach and quit so emulator keeps running
        batch_gdb.extend(["-ex", "detach", "-ex", "quit"])
        cmd = ["docker", "exec", c_name] + batch_gdb
        res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        print(res.stdout, end="")
        if res.stderr:
            # Filter non-critical GDB noise
            filtered = "\n".join(l for l in res.stderr.splitlines() if "warning:" not in l.lower() and "quit anyway" not in l.lower())
            if filtered:
                print(filtered, file=sys.stderr)
        return res.returncode

    # Interactive GDB session
    cmd = ["docker", "exec", "-it", c_name] + gdb_args
    return subprocess.run(cmd).returncode


def cmd_savestate(args):
    """Save emulator state."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    current = get_current_slot(args.name)
    target = args.slot if args.slot is not None else current

    # Cycle slot if needed
    if target != current:
        steps = (target - current) % 9
        for _ in range(steps):
            cmd_press(argparse.Namespace(name=args.name, buttons="slot_inc", ms=50))
            time.sleep(0.05)
        set_current_slot(args.name, target)

    # Press F5 (Save State)
    cmd_press(argparse.Namespace(name=args.name, buttons="save", ms=100))
    time.sleep(0.5)

    session_states_dir = get_session_states_dir(args.name)
    state_file = None
    for name_prefix in ["baserom.us", "dk64.us"]:
        candidate = session_states_dir / f"{name_prefix}.bs{target}"
        if candidate.exists():
            state_file = candidate
            break

    if state_file and state_file.exists():
        print(f"Saved state slot {target} to {state_file} ({state_file.stat().st_size} bytes)")
    else:
        print(f"Saved state to slot {target} (directory: {session_states_dir})")
    return 0


def cmd_loadstate(args):
    """Load emulator state."""
    c_name = container_name(args.name)
    if not is_container_running(c_name):
        print(f"Error: Session '{args.name}' is not running", file=sys.stderr)
        return 1

    target = args.slot
    current = get_current_slot(args.name)

    # Cycle slot if needed
    if target != current:
        steps = (target - current) % 9
        for _ in range(steps):
            cmd_press(argparse.Namespace(name=args.name, buttons="slot_inc", ms=50))
            time.sleep(0.05)
        set_current_slot(args.name, target)

    # Press F7 (Load State)
    cmd_press(argparse.Namespace(name=args.name, buttons="load", ms=100))
    time.sleep(0.5)
    print(f"Loaded state slot {target}")
    return 0


def main():
    parser = argparse.ArgumentParser(description="DK64 Emulator Tooling CLI", prog="tools/emu/emu.py")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # build
    p_build = subparsers.add_parser("build", help="Build the emulator Docker image")
    p_build.add_argument("--no-cache", action="store_true", help="Build without docker cache")
    p_build.set_defaults(func=cmd_build)

    # start
    p_start = subparsers.add_parser("start", help="Start an emulator session container")
    p_start.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_start.add_argument("--rom", help="ROM path (default: baserom.us.z64 or build/dk64.us.z64)")
    p_start.add_argument("--state", help="Path to a save state file to load on start")
    p_start.add_argument("--slot", type=int, choices=range(1, 10), help="Save state slot (1-9)")
    p_start.add_argument("--vnc-port", type=int, help="Host port for VNC (default 5900 for main)")
    p_start.set_defaults(func=cmd_start)

    # stop
    p_stop = subparsers.add_parser("stop", help="Stop an emulator session")
    p_stop.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_stop.set_defaults(func=cmd_stop)

    # status
    p_status = subparsers.add_parser("status", help="Show emulator session status")
    p_status.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_status.set_defaults(func=cmd_status)

    # list
    p_list = subparsers.add_parser("list", help="List all emulator sessions")
    p_list.set_defaults(func=cmd_list)

    # screenshot
    p_ss = subparsers.add_parser("screenshot", help="Capture a screenshot of the virtual display")
    p_ss.add_argument("output", help="Output PNG path")
    p_ss.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_ss.set_defaults(func=cmd_screenshot)

    # press
    p_press = subparsers.add_parser("press", help="Press buttons/keys on controller 1")
    p_press.add_argument("buttons", help="Buttons (comma-separated, e.g. start, a, b, stick_up, c-down)")
    p_press.add_argument("--ms", type=int, default=100, help="Press duration in milliseconds")
    p_press.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_press.set_defaults(func=cmd_press)

    # hold
    p_hold = subparsers.add_parser("hold", help="Hold buttons down")
    p_hold.add_argument("buttons", help="Buttons to hold")
    p_hold.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_hold.set_defaults(func=cmd_hold)

    # release
    p_rel = subparsers.add_parser("release", help="Release buttons")
    p_rel.add_argument("buttons", help="Buttons to release")
    p_rel.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_rel.set_defaults(func=cmd_release)

    # read
    p_read = subparsers.add_parser("read", help="Hex dump memory at address")
    p_read.add_argument("addr", help="Memory address (e.g. 0x8000DCC4)")
    p_read.add_argument("len", nargs="?", default="16", help="Length in bytes (default: 16)")
    p_read.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_read.set_defaults(func=cmd_read)

    # read32
    p_read32 = subparsers.add_parser("read32", help="Read 32-bit word at address")
    p_read32.add_argument("addr", help="Memory address (e.g. 0x80767A40)")
    p_read32.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_read32.set_defaults(func=cmd_read32)

    # write
    p_write = subparsers.add_parser("write", help="Write hex bytes to memory address")
    p_write.add_argument("addr", help="Memory address (e.g. 0x80746A30)")
    p_write.add_argument("hexbytes", help="Hex string to write (e.g. deadbeef)")
    p_write.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_write.set_defaults(func=cmd_write)

    # gdb
    p_gdb = subparsers.add_parser("gdb", help="Run gdb-multiarch connected to emulator")
    p_gdb.add_argument("--overlay", help="Overlay name to load symbols for (e.g. boss)")
    p_gdb.add_argument("--script", help="GDB Python script to run")
    p_gdb.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_gdb.add_argument("cmds", nargs="*", help="GDB commands to execute in batch mode")
    p_gdb.set_defaults(func=cmd_gdb)

    # savestate
    p_save = subparsers.add_parser("savestate", help="Save emulator state to a slot")
    p_save.add_argument("--slot", type=int, choices=range(1, 10), default=1, help="Slot number 1-9 (default: 1)")
    p_save.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_save.set_defaults(func=cmd_savestate)

    # loadstate
    p_load = subparsers.add_parser("loadstate", help="Load emulator state from a slot")
    p_load.add_argument("--slot", type=int, choices=range(1, 10), default=1, help="Slot number 1-9 (default: 1)")
    p_load.add_argument("--name", default=DEFAULT_SESSION, help="Session name (default: main)")
    p_load.set_defaults(func=cmd_loadstate)

    # Parse and execute
    # Support '--' separation for GDB commands
    if "gdb" in sys.argv:
        gdb_idx = sys.argv.index("gdb")
        if "--" in sys.argv[gdb_idx:]:
            dash_idx = sys.argv.index("--", gdb_idx)
            gdb_before = sys.argv[:dash_idx]
            cmds = sys.argv[dash_idx + 1:]
            parsed = parser.parse_args(gdb_before[1:] + cmds)
            return parsed.func(parsed)

    parsed = parser.parse_args()
    return parsed.func(parsed)


if __name__ == "__main__":
    sys.exit(main())
