# gfxDrawMapBackground (global, src/global/109660.c)
## Sites
global:80707980:goto:u8a880 / u8a880#2 (`goto fill;` in cases 0xD0 / 0x36): KEPT, Q0591 shared tail (re-verified 2026-11-15 on the current body).
## Attempts
- round 10 (opus): nested-switch fill colour (fdiff 1, +4 insns), permute (no zero).
- 2026-11-14 HackgfxDrawSkySprite (opus), variants.py try (lines off): if/else-if colour chain in the default arm 204; colour local with a sentinel-guarded fill block after the switch 322.
- 2026-11-15 HackgfxBuildScrollingBackground2 (anthropic/claude-opus-5-5:high), variants.py try (text rows): merged `case 0xD0: case 0x36: default:` group with the colour as a ternary chain on gCurrentMap 81; the same group with an inner switch on gCurrentMap selecting the colour 204.
## Untried ideas
none in structured C. Each colour case is its own jump-table target with constant stores and a branch into the single tail.
## Evidence
- 0x382C: case 0xD0 sw F7000000/FFFFFFFF, then b 0x38F0 (0x3840).
- 0x3848: case 0x36 sw F7000000/FFC1FFC1, then b 0x38F0 (0x3860).
- 0x38D4: default sw F7000000/0x10001, falling into 0x38F0, the one copy of the fill tail (E200001C SetOtherMode 0x38F4, E3000A01 cycle type 0x3900/0x3910, FillRectangle from the player rect 0x3920-0x39a0, PipeSync, cycle type).
