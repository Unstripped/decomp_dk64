---
name: emulator
description: Run Donkey Kong 64 under an instrumented ares-64 container to inspect live execution, trace function calls and arguments, find gameplay triggers via coverage breakpoints, and warp across maps. Use when understanding or naming an unknown function, checking which game situations execute code, warping to scenes, or measuring dynamic coverage.
---

# DK64 Emulator & Dynamic Analysis Skill

Use this skill to execute, inspect, and trace Donkey Kong 64 inside the Docker-based ares-64 emulator.
Driving the emulator provides ground-truth runtime evidence (register arguments, struct layouts, return values, caller sites, and execution triggers) to confirm function names and data structures in the decompilation.

## 0. Session Isolation Rules

Every agent MUST run in its own isolated container session:
- Specify `--name <unique_agent_id>` on every command.
- Specify a unique `--vnc-port <port>` (range 5910–5960; port 5900 is reserved for human play).
- All runtime output MUST stay under `emu/` (gitignored). Temporary probes stay in `.scratch/`.
- Always stop your container session when your task completes.

```sh
# Start isolated agent session
python3 tools/emu/emu.py start --name study-act --vnc-port 5925

# Stop session when finished
python3 tools/emu/emu.py stop --name study-act
```

---

## 1. Session Lifecycle CLI

Manage Docker containers (`dk64-emu-<name>`) running ares-64, Xvfb, x11vnc, and the GDB server:

```sh
# Build emulator Docker image (if not already built)
python3 tools/emu/emu.py build

# Start session
python3 tools/emu/emu.py start [--name NAME] [--vnc-port PORT] [--slot SLOT] [--state STATE]

# Inspect session status (container health, uptime, forwarded ports)
python3 tools/emu/emu.py status [--name NAME]

# List all active and stopped sessions
python3 tools/emu/emu.py list

# Stop session container
python3 tools/emu/emu.py stop [--name NAME]
```

### Direct Input & Memory Commands

```sh
# Send controller inputs
python3 tools/emu/emu.py press [--name NAME] [--ms MS] buttons
python3 tools/emu/emu.py hold [--name NAME] buttons
python3 tools/emu/emu.py release [--name NAME] [buttons]

# Capture virtual screen
python3 tools/emu/emu.py screenshot <output.png> [--name NAME]

# Read/write RDRAM
python3 tools/emu/emu.py read <addr> [len] [--name NAME]
python3 tools/emu/emu.py read32 <addr> [--name NAME]
python3 tools/emu/emu.py write <addr> <hexbytes> [--name NAME]
```

---

## 2. Save-State Library vs. Session Slots

The emulator provides two separate state mechanisms:

### (a) Per-Session Slots (Ephemeral)
Each session container has its own private state directory at `emu/sessions/<name>/states/`. Sessions never share slot files.
```sh
# Save/load slot 1-9 in active session
python3 tools/emu/emu.py savestate --name study-act --slot 1
python3 tools/emu/emu.py loadstate --name study-act --slot 1
```

### (b) Save-State Library (Persistent & Shared)
Stored at `emu/states/library/<label>.{bs,json,png}`. Contains known, labeled gameplay moments with recorded map IDs and active overlays.
```sh
# List all states in the library
python3 tools/emu/states.py list

# Save current session into library
python3 tools/emu/states.py save <label> [--name NAME] [--note NOTE]

# Load library state into running session (or boot a new session into it)
python3 tools/emu/states.py load <label> [--name NAME] [--vnc-port PORT]

# Import an existing slot into library
python3 tools/emu/states.py import <label> --slot SLOT [--name NAME] [--note NOTE]

# Remove state from library
python3 tools/emu/states.py rm <label>
```

**Key Library State**: `training_grounds` (map `0xB0`, playable Donkey Kong on Training Grounds). Use this as the default baseline for global function study.

---

## 3. Dynamic Function Coverage Workflow (`coverage.py`)

Measure which functions execute during specific gameplay sequences using GDB breakpoints.

### Coverage Commands

```sh
# 1. Run coverage collection on a saved state (default 20 seconds)
python3 tools/emu/coverage.py run <label> [--seconds S] [--inputs FILE] [--name NAME] [--batch-size B]

# 2. Re-index coverage runs into emu/coverage/index.json
python3 tools/emu/coverage.py index

# 3. Find which states execute a specific function
python3 tools/emu/coverage.py where <func_or_addr>

# 4. Compare coverage between two states (e.g. isolate action triggers)
python3 tools/emu/coverage.py diff <label_a> <label_b>

# 5. Display coverage summary
python3 tools/emu/coverage.py summary [--label LABEL]
```

### Input Script Format
Pass scripted inputs via `--inputs <file>`:
```
# Format: action [param] [buttons]
wait 1.5
press start 100
press a 150
hold stick_up
wait 2.0
release stick_up
```

### Performance & Overlay Mechanics
- **Breakpoint Scaling**: GDB must run with `set breakpoint always-inserted on`. Without this, GDB removes and re-inserts breakpoints on every stop, creating 10–15s pauses per stop. With `always-inserted on`, stop latency drops to 15–40 ms.
- **Insertion Rate**: Inserting all ~3,860 functions takes ~15 seconds.
- **Monotonic Cost Drop**: Breakpoints are removed upon first hit; stop overhead decreases as functions execute.
- **Overlay Flushing**: All 9 overlays share VRAM `0x80024000`. The coverage script hooks `loadOverlay` (`0x80610350`) to flush old overlay breakpoints and re-registers the new overlay via `symbols.detect_overlay`.

---

## 4. Function Study Workflow (`study.py`)

Trace function execution, inspect arguments, dereference pointers, and verify return values.

### Command
```sh
python3 tools/emu/study.py <FUNC_OR_ADDR> [--state STATE] [--hits HITS] [--segment SEG] [--watch ADDR[:LEN]] [--name NAME]
```

### Options
- `FUNC_OR_ADDR`: Function symbol name (e.g. `controllerUpdate`) or hex address (`0x8060AC7C`).
- `--state STATE`: Library state label to load. If omitted, `study.py` automatically selects a state from `emu/coverage/index.json` where the function was hit.
- `--hits HITS`: Maximum invocation stops to trace (default: 3).
- `--segment SEG`: Explicit segment (`boot`, `global`, or overlay name) when an address is ambiguous.
- `--watch ADDR[:LEN]`: Memory address and length to watch for mutations (e.g. `0x8076A0A8:4`).
- `--name NAME`: Session name (default: `main`).

### Output Dossier (`emu/study/<FUNC>/`)
- `report.md`: Markdown report with:
  - Invocation count and CPU cycles.
  - Return address `$ra` and resolved caller symbol.
  - Input registers: `$a0`–`$a3` and floating-point `$f12`–`$f14`.
  - Stack pointer `$sp` and frame memory.
  - Automatic pointer dereferencing: 0x80-byte memory dumps for any register containing an RDRAM address (`0x80XXXXXX`).
  - Return values `$v0`, `$v1`, and `$f0` captured upon function exit.
  - Memory watch diffs (before vs after execution).
- `screenshot.png`: Screen state at the instant of invocation.
- `data.json`: Machine-readable dump of all captured register and memory states.

---

## 5. Map Warping & Sweeps (`warp.py`)

Warp the running game to any map ID by calling `func_805FF378(map, exit)` at the main loop safe point (`controllerUpdate`).

### Warping to a Map
```sh
python3 tools/emu/warp.py --name NAME 0x22 [EXIT] [--timeout S] [--settle S]
python3 tools/emu/warp.py --name NAME "Cranky's Lab"   # name/substring from tools/emu/maps.tsv
```
- Waits up to `--timeout` (20 s) for `D_8076A0A8` to change; a `hang` needs the map register AND the frame/VI counters to stall. Then waits `--settle` (4.5 s) for the iris wipe before re-reading the map, overlay and taking the screenshot.
- Run at most 2 warp/sweep sessions at once: under 4 concurrent sessions, transitions took 6.5–8.5 s wall and the old 6 s timeout produced false hangs.
- `tools/emu/maps.tsv`: all 224 ids `0x00`–`0xDF` (the per-map byte table `D_807445E0` is 0xE0 long), measured from `training_grounds`: 215 load as requested, `0xB3` is rewritten to `0x1E`, `0xD8`–`0xDF` change the map register and then fault the game thread (`__osFaultedThread`). Names are visual descriptions from one settled frame, not verified titles; fix one when you can tell better.
- `warp.py` checks `__osFaultedThread` and the frame counter after settling too: the map register changes before a map finishes loading, so a register change alone is not success.
- Warping from `training_grounds` works for ids `0x00`–`0xD7`; story flags still come from that save, so late-game maps can look empty.

### Automated Map Sweeps
```sh
python3 tools/emu/warp.py sweep --name NAME --state LABEL --from A --to B --out FILE.tsv [--vnc-port P] [--timeout S] [--settle S]
```
- Restores library state `--state` before every warp, writes ONLY to `--out` (columns `id	name	loaded	overlay	status	notes`, `name` left empty for a human or agent to fill from the screenshot), screenshots to `emu/maps/map_0xNN.png`.
- Restarts the session on `--vnc-port` only after a real crash or hang.

---

## 6. Symbolizer CLI (`symbols.py`)

Resolve addresses to function names and query overlay boundaries from symbol files:

```sh
# Resolve address to symbol
python3 tools/emu/symbols.py addr 0x805FF378
python3 tools/emu/symbols.py addr 0x80024000 --segment menu

# Look up address by function name
python3 tools/emu/symbols.py name controllerUpdate

# List all functions in a segment
python3 tools/emu/symbols.py list global

# Report function counts per segment
python3 tools/emu/symbols.py stats
```

---

## 7. Raw GDB & Low-Level Debugging

For manual inspection or custom scripting:

```sh
# Run GDB command batch against session
python3 tools/emu/emu.py gdb --name <name> "x/8x 0x8076A0A8"

# Load overlay symbols and inspect
python3 tools/emu/emu.py gdb --name <name> --overlay boss "info symbol 0x80024000"

# Interactive GDB shell
python3 tools/emu/emu.py gdb --name <name>
```

---

## 8. Critical Gotchas

1. **Always `break *0xADDR`**: Setting a breakpoint by function name (`break funcname`) causes GDB to inspect MIPS instructions and skip the prologue. This corrupts argument inspection because `$a0`–`$a3` may already be overwritten. Always break on the exact entry address using `break *0x<hex>`.
2. **Never warp by writing globals directly**: `func_805FF378` (`src/global/3C10.c`) gates the transition (`D_807444EC == 6 || func_80712798() == 0`), lets `func_80712F10` rewrite or cancel the target, records the old map and runs the transition setup calls. Writing `D_807444E4`/`D_807444E8`/`D_8076A0B2` skips all of that. Always warp through `warp.py`, which calls the function at the `controllerUpdate` safe point.
3. **Overlays share VRAM `0x80024000`**: All 9 overlays load at the same address, so any address from `0x80024000` up to the global segment (`0x805FB300`) is ambiguous. Resolve it with `symbols.py addr ADDR --segment S` only after `symbols.detect_overlay` confirms which overlay is loaded.
4. **ELF load order in GDB**: Always load `file build/dk64.us.elf` *before* `target remote 127.0.0.1:9123`. If GDB connects before loading a 32-bit ELF, it defaults to 64-bit MIPS registers, sign-extending addresses to `0xffffffff80xxxxxx` and failing breakpoint insertions.
5. **Clean up containers**: Always run `python3 tools/emu/emu.py stop --name <name>` when finished. Unstopped containers hold network ports and system RAM.
6. **Naming evidence**: Names follow the AGENTS.md conventions: behaviour confirmed from the matched C. A `study.py` report (caller, arguments, return value, screenshot) is supporting evidence that makes a name stronger; record what it showed in the commit message. Never name a function from a screenshot or a guess alone.

---

## 9. Feeding Study Results into Decompilation

When a function is studied via `study.py <FUNC>`:
1. Review `emu/study/<FUNC>/report.md` for argument structures, pointer dereferences, and caller return addresses.
2. Confirm the behavioral purpose of the function against the decompiled C in `src/`.
3. Rename the symbol in `symbol_addrs.us.txt` (or `symbol_addrs.<overlay>.us.txt`):
   ```
   controllerUpdate = 0x8060AC7C; // type:func
   ```
4. Update header prototypes (e.g. `include/actor.h` or `include/common.h`).
5. Re-run `tools/dk make split` to regenerate asm references with the new name.
6. Check matching build with `tools/dk make`.

---

## 10. Improve This Skill

Update this skill file (`.omp/skills/emulator/SKILL.md`) whenever an emulator workflow or GDB procedure is improved, or when new breakpoint or overlay gotchas are discovered.
