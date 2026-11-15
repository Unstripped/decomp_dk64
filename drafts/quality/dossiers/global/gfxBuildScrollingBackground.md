# gfxBuildScrollingBackground (global, src/global/109660.c)
## Sites
global:80706F90:other:1c23c5 other: REMOVED. Was `*(s16 *)((u8 *)gTintKeyframes + 0x18) = scroll;` (gBgScrollX store through a neighbour's base so it kept its own `lui at; sh t7,0x18(at)` at 0x2d00/0x2d04 instead of joining the {551|1} lda web in v1).
global:80706F90:other:3a2970 other: REMOVED. Was `*(s16 *)((u8 *)gSkyQuadColors + 0x78) = 0;` (the wrap store; target `lui at; sh zero,0x78(at)` at 0x2d14/0x2d18).
## Attempts
- Rounds 10, 16, 17, 20 and 2026-11-14 Hack109660BgScroll / Owner109660DataToC: see drafts/quality/dossiers/global/gfxBuildScrollingBackground.md (static + `scroll = X + 4` tail: text 31; `+=` tail with extern globals: text 40; struct/array views 28 rows).
- 2026-11-15 HackgfxBuildScrollingBackground2 anthropic/claude-opus-5-5:high: function-local `static s16` X/Y (Q0761) combined with each tail shape, variants.py try text rows: `sX += 4; sY += 4;` + two clamps 5 (all 5 rows are LO16 addend-only), sY first 15, assign-in-compare 15, `(sX = scroll) >= 0x200` 15, re-read compare 15, X store first 28, plain `scroll = sX + 4` 31, `sY = sY + 4` 31; extern plain 15.
- Applied `+=` tail with statics sBgScrollX/sBgScrollY, file-scope definitions removed -> fdiff --reloc-ok RELOC-EQUIV OK (exit 0); plain fdiff TEXT OK; .data and .rodata bytes identical.
## Untried ideas
none (function clean: 0 FAKE).
## Evidence
- Target tail 0x2cd8-0x2d38: X `lui v0; lh v0,%lo` and Y `lui t8; lh t8,%lo` (0x2cd8-0x2ce4); Y+4 stored `sh t6` at 0x2cf8; X+4 narrowed `sll t9,v0,16; sra t7,t9,16` (0x2cf4/0x2cfc), stored at 0x2d04 and compared `slti at,t7,512` at 0x2d08; conditional zero store 0x2d18; Y reloaded `lh t9` at 0x2d1c and compared, zero store at 0x2d38. Every access has its own lui: S-variables (Q0761), not an lda web (Q0255).
- Built copy: statics have no symbol; relocations are `.data+0x290` (X) and `.data+0x294` (Y), equal to gBgScrollX/gBgScrollY's expected offsets (gTintKeyframes 0x278 + 0x18, gSkyQuadColors 0x218 + 0x78). Raw-word proof: `.scratch/HackgfxBuildScrollingBackground2/rawword_109660.diff` (only LO16 immediates differ, each resolving to the same .data offset).
- IDO lays the function-local statics after all file-scope initialised data, in declaration order.
