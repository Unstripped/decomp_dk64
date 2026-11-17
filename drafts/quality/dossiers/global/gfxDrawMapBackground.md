# gfxDrawMapBackground (global, src/global/109660.c)
## Sites
global:80707980:goto:u8a880 / u8a880#2 (`goto fill;` in cases 0xD0 / 0x36): KEPT, Q0591 shared tail (re-verified 2026-11-17 at cfcf2ce7 on the current body).
## Attempts
- round 10 (opus): nested-switch fill colour (fdiff 1, +4 insns), permute (no zero).
- 2026-11-14 HackgfxDrawSkySprite (opus), variants.py try (lines off): if/else-if colour chain in the default arm 204; colour local with a sentinel-guarded fill block after the switch 322.
- 2026-11-15 HackgfxBuildScrollingBackground2 (anthropic/claude-opus-5-5:high), variants.py try (text rows): merged `case 0xD0: case 0x36: default:` group with the colour as a ternary chain on gCurrentMap 81; the same group with an inner switch on gCurrentMap selecting the colour 204.
- 2026-11-17 HackgfxDrawMapBackground, variants.py try (full rows): `s32 fill` flag set beside each in-arm `gDPSetFillColor` with the fill tail after the switch under `if (fill)` 267 (declared first or last alike); the fill tail written out in all three colour arms 351. Case 0x4/0xB0 merged into one group: 16 bytes short (the target keeps two copies).
## Untried ideas
none in structured C. Each colour case is its own jump-table target with constant stores and a branch into the single tail; case 0x50's code sits between the colour arms and the default, so any goto-free form needs either a second dispatch (compares, inner switch, flag test: Q1156 says IDO never threads value-known branches) or a tail copy (Q0591: IDO never tail-merges). The only other matching spelling is the Duff `if (0) { case ...: }` form, a dead-if hack (Q0953).
## Evidence
- 0x382C: case 0xD0 sw F7000000/FFFFFFFF, then b 0x38F0 (0x3840).
- 0x3848: case 0x36 sw F7000000/FFC1FFC1, then b 0x38F0 (0x3860).
- 0x3868-0x38D0: case 0x50 (lensFlareAddFromAngle, gfxDrawBackgroundQuad, gfxDrawSkySprite), b 0x39D0.
- 0x38D4: default sw F7000000/0x10001, falling into 0x38F0, the one copy of the fill tail (E200001C SetOtherMode 0x38F4, E3000A01 cycle type 0x3900/0x3910, FillRectangle from the player rect 0x3920-0x39a0, PipeSync, cycle type).
- Fill-flag variant: flag homed at sp+0x3C (frame 0x40 -> 0x50), `sw zero,0x3c(sp)` before the switch, `li t8,1; sw t8,0x3c(sp)` in each colour arm, every arm branches to the post-switch test at 0x38F8.
