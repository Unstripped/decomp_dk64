# mapGetVoidHeightForCharacter (global, src/global/F93B0.c)
## Sites
- global:806F46B0:other:4a6510 other: REMOVED. `lim = 13` value-named bound local kept 13 in v0 (`li v0,13` at 0x18, `slt at,v1,v0` at 0x78).
## Attempts
- PolishGlobalF93B0 (opus:high): plain nohit (while (i < 13) folds to slti and shifts registers by one).
- 2026-11-14 U HackmapGetVoidHeightForCharacter anthropic/claude-opus-5-5:high (variants.py try full=):
  - Literal bound:
    - <, >, <=, >= forms: 23
    - != forms: 25
    - `!(i >= 13)` 23, `i - 13 < 0` 24, `13 - i > 0` 25
    - s32 i: 95
    - variants scan on the literal body: nothing below 23
  - lim kept, with lim s16 or declared last: 0
  - Split layout:
    - fully split: 6
    - other statement orders: 6-16
    - for-loop: 14
  - Joins:
    - `i = 0; map = gCurrentMap; do {`: 0
    - also joining `e = ...`: 0
    - `i = 0;` alone, then `map...; do {`: 2
    - `i = 0; map = ...;` with `do {` on the next line: 4
    - `map ...; i = 0; do {`: 11
  - Count local:
    - `extern MapVoidHeight D_80753EA0[13]` with `count = sizeof(D_80753EA0) / sizeof(D_80753EA0[0])`, s32 or s16, under the original or the short join: 0 (applied: s32, short join)
    - fully split: 6
## Untried ideas
- none: site removed. The short LAYOUT join stays (see Evidence).
## Evidence
- Target 0x00-0x90:
  - `li v0,13` at 0x18; `move v1,zero` at 0x24, after `lw a1,gCurrentMap` at 0x20
  - `multu v1,t1` (t1 = 6)
  - s16 i via `sll`/`sra` at 0x70/0x74
  - `slt at,v1,v0` at 0x78
- uopt trace with a literal bound: `ules {976 i} {13}`, folded to `slti`.
- Data (asm/global/data/14C9E0.data.s): D_80753EA0 holds 13 six-byte entries, 0x80753EA0-0x80753EED.
  - maps 0x1E, 0x1E, 0x26, 0xCC, 0xC9, 0x22, 0x30 x5, 0x48, 0x57
  - then 2 bytes of 0, then D_80753EF0
- as1probe scan on the fully split body (6 -> 2): swap or delete the `.loc` between `move $3,$0` and `lw $5,gCurrentMap`, i.e. a line join.
