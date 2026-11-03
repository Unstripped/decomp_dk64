# Donkey Kong 64 decompilation

A matching decompilation of **Donkey Kong 64** (N64, USA, `NDOE`). The C sources here compile with the original toolchain (IDO 5.3, libultra 2.0J) to a ROM that is byte-identical to the retail game:

```
SHA-1 cf806ff2603640a748fca5026ded28802f1f4a50  dk64.us.z64
```

This repository contains no game data. You need your own copy of the ROM to build it.

## Progress

Percentages are matched C function bytes out of all function bytes in each code segment. Assets (textures, models, text) are not counted; see [ROADMAP.md](ROADMAP.md).

<!-- progress:start -->
**Overall: 94.53%** of code bytes matched (1,642,592 / 1,737,724 bytes, 4,367 / 4,499 functions)

`██████████████████████████████████████░░`

| Segment | Contents | Progress | Bytes | Functions |
|---|---|---|--:|--:|
| `boot` | boot, libultra, inflate | `████████████████░░░░` 79.6% | 42,820 / 53,796 | 191 / 229 |
| `global` | main game code | `███████████████████░` 94.5% | 1,250,832 / 1,323,472 | 3,516 / 3,601 |
| `multiplayer` | `ovl02`, multiplayer modes | `████████████████████` 100.0% | 12,132 / 12,132 | 31 / 31 |
| `minecart` | `ovl03`, minecart rides | `████████████████████` 100.0% | 19,332 / 19,332 | 25 / 25 |
| `bonus` | `ovl04`, bonus barrels | `███████████████████░` 94.6% | 36,868 / 38,972 | 46 / 47 |
| `race` | `ovl05`, races | `████████████████████` 100.0% | 47,836 / 47,836 | 113 / 113 |
| `critter` | `ovl06`, critter minigames | `████████████████████` 100.0% | 22,496 / 22,496 | 55 / 55 |
| `boss` | `ovl07`, boss fights | `████████████████████` 97.9% | 70,304 / 71,784 | 78 / 79 |
| `arcade` | `ovl08`, Donkey Kong arcade | `███████████████████░` 95.4% | 55,244 / 57,880 | 96 / 98 |
| `jetpac` | `ovl09`, Jetpac | `███████████████████░` 96.0% | 27,636 / 28,788 | 107 / 108 |
| `menu` | `ovl10`, main menu / file select | `███████████████████░` 93.2% | 57,092 / 61,236 | 109 / 113 |
| **Total** |  | `███████████████████░` 94.5% | 1,642,592 / 1,737,724 | 4,367 / 4,499 |
<!-- progress:end -->

Refresh after a matching build with `tools/dk python3 tools/progress.py --readme`.

## Building

Requirements: Docker and a Donkey Kong 64 (USA) ROM in any byte order (`.z64`, `.n64` or `.v64`). Every build tool runs inside the `dk64-decomp` container through `tools/dk`; the host needs no MIPS toolchain.

```sh
docker compose build                                # build the toolchain image
tools/dk make setup BASEROM=donkey-kong.n64        # verify + extract the ROM, split with splat
tools/dk make                                       # build build/dk64.us.z64 and check its SHA-1
tools/dk make progress                              # per-segment progress table
```

A successful build ends with `build/dk64.us.z64: OK`.

## How the ROM is organised

| Segment | Load address | Contents |
|---|---|---|
| boot | `0x80000450` | uncompressed: entry, threads, libultra, gzip inflate |
| global | `0x805FB300` | main game code and data (gzip compressed) |
| 9 overlays | `0x80024000` | one per game mode: multiplayer, minecart, bonus, race, critter, boss, arcade, jetpac, menu |
| assets | — | ~8.7k gzip streams of textures, models, text and sound |

Each code segment has its own splat config (`dk64.us.yaml`, `dk64.global.us.yaml`, `dk64.<overlay>.us.yaml`) and expected hashes (`*.sha1`). The full ROM map is in [ROADMAP.md](ROADMAP.md).

## Contributing

The workflow for decompiling a function, compiler notes and repository conventions are in [AGENTS.md](AGENTS.md). In short:

1. Pick a `#pragma GLOBAL_ASM(...)` function in `src/`; `tools/dk python3 tools/m2c.py [-s SEGMENT] FUNC` gives starter C.
2. Build and compare: `tools/dk make`, then `tools/dk ./diff.sh [-s SEGMENT] FUNC` on mismatch.
3. Name confirmed symbols in `symbol_addrs.us.txt` (boot/global) or `symbol_addrs.<overlay>.us.txt`.

Never commit ROMs, extracted binaries (`bin/`, `assets/`) or generated asm (`asm/`), and never commit a non-matching build.
