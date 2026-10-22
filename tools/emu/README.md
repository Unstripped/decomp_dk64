# Donkey Kong 64 Emulator & Save-State Guide

This guide explains how to play Donkey Kong 64 inside our instrumented emulator environment, create save states for decompilation research, warp across maps, and inspect running code.

The emulator runs **ares-64** inside a Docker container with an embedded GDB server, virtual display (Xvfb), and VNC server (`x11vnc`), allowing both interactive human gameplay and headless automated analysis by decompilation agents.

---

## 1. Playing the Game

### One-Time Setup

Before starting a session, ensure your workspace and container image are prepared:

1. **Docker Desktop**: Confirm Docker is running on your machine (`docker info`).
2. **Build Toolchain & Baserom**: Ensure `baserom.us.z64` exists from the initial setup:
   ```sh
   tools/dk make setup
   ```
3. **Build the ELF Binaries**: Compile matching ELF images so debug symbols are available:
   ```sh
   tools/dk make
   ```
4. **Build the Emulator Image**: Build the `dk64-emu` Docker container:
   ```sh
   python3 tools/emu/emu.py build
   ```

### Starting the Session

Launch the default emulator session:

```sh
python3 tools/emu/emu.py start
```

This starts a Docker container named `dk64-emu-main`, runs ares-64 with an expansion pak enabled, opens the GDB server on internal port `9123`, and exposes VNC on port `5900`.

### Connecting via VNC

On macOS, open the Screen Sharing client:

```sh
open vnc://127.0.0.1:5900
```

When prompted for the password, enter:
```
dk64
```

> **Important**: Click inside the Screen Sharing window so it captures keyboard focus!

### Controller Key Map

The container maps your host keyboard directly to N64 Controller Port 1:

| N64 Control | Keyboard Key | Description |
|---|---|---|
| **Analog Stick** | `W` / `A` / `S` / `D` | Up / Left / Down / Right |
| **A Button** | `K` | Jump, accept, swim, flutter |
| **B Button** | `J` | Attack, cancel, dive |
| **Z Trigger** | `Space` | Crouch, ground pound |
| **L Shoulder** | `Q` | Zoom camera / L-trigger |
| **R Shoulder** | `E` | Center camera / first-person view |
| **Start** | `Return` (Enter) | Pause menu |
| **C-Up** | `Up Arrow` | First-person look / camera up |
| **C-Down** | `Down Arrow` | Zoom camera in / out |
| **C-Left** | `Left Arrow` | Rotate camera left |
| **C-Right** | `Right Arrow` | Rotate camera right |
| **D-Pad** | `1` / `2` / `3` / `4` | D-Pad Up / Down / Left / Right |
| **Quick Save State** | `F5` | Saves emulator state to current slot |
| **Quick Load State** | `F7` | Loads emulator state from current slot |
| **Previous Slot** | `F6` | Select previous save slot (1–9) |
| **Next Slot** | `F8` | Select next save slot (1–9) |

### Play Experience Notes

- **No Gamepad Passthrough**: Ares runs headless under Xvfb inside Docker; controller inputs are forwarded over VNC as X11 keyboard events. Physical gamepads are not supported over VNC.
- **Latency**: Expect a small amount of network and display latency over VNC. The gameplay is fully playable for traversal and setup, though tight timing minigames can feel sluggish.
- **No Sound**: The container does not export an audio sink, so there is no game audio during VNC play.

### Stopping the Session

When you are finished playing, stop the container to release ports and resources:

```sh
python3 tools/emu/emu.py stop
```

---

## 2. Making Save States

Save states are essential for decompilation: they allow subagents to test hypotheses against specific game scenes, measure function execution coverage, and inspect live function parameters without replaying the entire game.

### (a) The Recommended Way: Direct Terminal Command

While playing in VNC, leave the game running at the moment you want to capture, switch to a host terminal, and run:

```sh
python3 tools/emu/states.py save <label> --note "Description of game state"
```

For example:
```sh
python3 tools/emu/states.py save japes_lanky_tag_barrel --note "Lanky standing next to tag barrel in Jungle Japes main area"
```

What `states.py save` does automatically:
1. Freezes the running session and saves the ares-64 state to `emu/states/library/<label>.bs`.
2. Reads memory address `0x8076A0A8` to record the active map ID.
3. Inspects memory to identify the active overlay (`boss`, `race`, `bonus`, `menu`, etc.).
4. Captures a visual snapshot of the screen to `emu/states/library/<label>.png`.
5. Writes full metadata to `emu/states/library/<label>.json`.

**Naming Labels**: Use short, lowercase, descriptive labels indicating the world, kong, and action (e.g. `isles_dk_start`, `japes_diddy_mountain`, `aztec_tiny_temple`, `factory_chunky_crusher`, `helm_krool_fight`).

### (b) The In-Game Hotkey Way: Save Slot Import

If you prefer playing uninterrupted:
1. Press `F5` in the game window whenever you reach a good moment (saves to current slot, default slot 1).
2. Use `F6` and `F8` to switch between slots 1 through 9.
3. Press `F7` if you want to quickly reload a slot.
4. When you finish your play session, import any slot into the permanent library:
   ```sh
   python3 tools/emu/states.py import <label> --slot 1 --note "Lanky in front of Mad Jack arena"
   ```

### Managing the Library

- **List All Saved States**:
  ```sh
  python3 tools/emu/states.py list
  ```
  Displays each saved state, its recorded map ID, active overlay, timestamp, and notes.

- **Load a Saved State**:
  ```sh
  python3 tools/emu/states.py load <label>
  ```
  If the session is already running, this immediately switches it to the saved state. If no session is running, it starts a fresh emulator container loaded directly into that state!

- **Delete a Saved State**:
  ```sh
  python3 tools/emu/states.py rm <label>
  ```

### Which Moments Make Useful States?

Automated decompilation agents benefit from maximum variety across the entire game engine. The best save states capture:

- **Every Level**: DK Isles hub, Jungle Japes, Angry Aztec, Frantic Factory, Gloomy Galleon, Fungi Forest, Crystal Caves, Creepy Castle, and Hideout Helm.
- **Every Kong**: States controlling DK, Diddy, Lanky, Tiny, and Chunky, especially right before activating character-specific abilities (Simian Slam, OrangStand, Mini-Monkey, Hunky Chunky, Jetpack).
- **Vendor Shops**: Outside and inside Cranky's Lab, Funky's Armory, Candy's Music Shop, and Snide's H.Q.
- **Boss Fights**: Army Dillo, Dogadon, Mad Jack, Puftoss, King Kut-Out, and each round of King K. Rool.
- **Bonus Minigames**: Right before jumping into bonus barrels (Minecart Mayhem, Stealthy Snoop, Beaver Bother, Speedy Swing-Sort, Batty Barrel Bandit, etc.).
- **Arcade Games**: Playing the retro Donkey Kong arcade cabinet or Jetpac machine.
- **Action Triggers**: Moments *just before* an action occurs (stepping on a pad, entering a portal, opening a door, initiating a cutscene).

### Storage & Emulator Version Compatibility

- All library states are stored under `emu/states/library/` (this directory is gitignored and will never be committed to git).
- Ares save states are architecture- and version-specific: they work with the exact Docker emulator image. If the pinned ares-64 commit in `tools/emu/Dockerfile` is updated, older `.bs` state files may become invalid.

---

## 3. Warping to Maps

The warp tool lets you jump directly to any map ID by triggering the game's internal transition function `func_805FF378(map, exit)` at a safe point in the main game loop (`controllerUpdate`).

### Warping to a Map ID or Name

Warp by hexadecimal ID:
```sh
python3 tools/emu/warp.py 0x22
```

Warp by decimal ID:
```sh
python3 tools/emu/warp.py 34
```

Warp by map name (case-insensitive, substrings allowed; looked up in `tools/emu/maps.tsv`):
```sh
python3 tools/emu/warp.py "Cranky's Lab"
```

`maps.tsv` lists all 224 map ids (`0x00`–`0xDF`) with what loaded, the overlay and a short name. The names were given by agents looking at one screenshot taken right after each warp, so treat them as descriptions, not official titles; `unknown` means the frame showed nothing recognisable (`0xD8`–`0xDF` load but stay black). Correct a name whenever you recognise a place better.

Specify an optional exit index (defaults to 0), and `--name` to warp a session other than `main`:
```sh
python3 tools/emu/warp.py --name play 0x22 1
```

A warp waits up to `--timeout` seconds (default 20) for the map to change, then `--settle` seconds (default 4.5) for the iris wipe to open before it takes the screenshot.

### Story-Progress Flags vs. Map Location

**Important**: Warping sets the destination map and executes the engine's loading sequence, but it **does not** automatically set story progression, inventory, or Kong unlock flags.

If you warp to a late-game map (such as Hideout Helm or K. Rool's ship) from a fresh boot, doors may be locked, puzzle objects may not spawn, or Kongs may not be switchable. For accurate behavior analysis of late-game code, naturally played save states are preferred over cold warps.

### Automated Map Sweeps

To probe maps sequentially and record reachability and screenshots:

```sh
python3 tools/emu/warp.py sweep --name sweep1 --state training_grounds --from 0 --to 0xDF --out emu/maps/sweep.tsv --vnc-port 5970
```

Before each warp attempt, this restores the specified library state (e.g. `training_grounds`), attempts the transition, verifies whether the map loaded into `D_8076A0A8`, identifies the loaded overlay via memory inspection, saves a screenshot to `emu/maps/map_0xNN.png`, and writes the results to the TSV file.

---

## 4. What Agents Do With Your Save States

Decompilation subagents use your save states to automate function identification, matching, and documentation:

### 1. Dynamic Coverage Collection (`coverage.py`)

Agents measure which functions execute during specific gameplay sequences by inserting thousands of temporary breakpoints:

```sh
python3 tools/emu/coverage.py run japes_lanky --seconds 20
```

Agents can then query where an unknown function executes:
```sh
python3 tools/emu/coverage.py where func_80677D80
```
Or compare coverage between two states to isolate the function responsible for a specific mechanic:
```sh
python3 tools/emu/coverage.py diff japes_standing japes_jumping
```

### 2. Live Function Tracing (`study.py`)

When reverse-engineering an unidentified function, agents use `study.py` to inspect runtime behavior:

```sh
python3 tools/emu/study.py func_8060AC7C --state training_grounds --hits 3
```

This intercepts the function on live execution, recording:
- Input arguments in `$a0`–`$a3` and floating-point registers.
- Caller return addresses in `$ra`.
- Stack pointer `$sp` and local frame contents.
- Automatic dereferencing of RDRAM pointer arguments (inspecting struct payloads).
- Return values in `$v0`, `$v1`, and `$f0`.
- Memory mutations at watched addresses (`--watch 0x8076A0A8:4`).

The resulting report is saved to `emu/study/<FUNC>/report.md` along with a screenshot, providing verifiable behavioral evidence for renaming functions in the decompilation.

---

## 5. Troubleshooting & Session Management

### Port Already in Use

If default VNC port `5900` is already in use by macOS Screen Sharing or another process, launch your session with a custom port:

```sh
python3 tools/emu/emu.py start --name play --vnc-port 5905
open vnc://127.0.0.1:5905
```

### Black Screen on Startup

Ares initializes hardware and executes the boot sequence before displaying graphics. The initial boot takes approximately 10 to 15 seconds before the Rareware logo or copyright screen appears. If the screen is black immediately after `start`, wait 15 seconds.

### Inspecting Running Sessions

To list all running and stopped emulator sessions:
```sh
python3 tools/emu/emu.py list
```

To view detailed status (container health, uptime, forwarded VNC/GDB ports):
```sh
python3 tools/emu/emu.py status
```
Or for a specific named session:
```sh
python3 tools/emu/emu.py status --name play
```

### Stopping Sessions

Always stop unused sessions to prevent container build-up:
```sh
python3 tools/emu/emu.py stop
python3 tools/emu/emu.py stop --name play
```
