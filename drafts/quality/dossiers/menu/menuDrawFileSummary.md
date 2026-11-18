# menuDrawFileSummary (menu, src/menu/3E10.c)
## Sites
menu:800291CC:other:2cc85d other: `four = 4.0f` value-named constant local. It kept 85 x 4.0 as a run-time `mul.s $f14,$f6,$f26` at 0x1718, because cfe folds `85 * 4.0f` to 340.0. It also took one frame word above posX. FIXED 2026-11-17: removed.
menu:800291CC:other:93ed43 other: `x = 0.5f`, the loop x reused as the sprite scale in $f20, which saved one frame word. FIXED 2026-11-17: now a dedicated `scale`.
menu:800291CC:other:83437e other: `i = gFrameCounter % 360U`, the loop counter reused as the sprite angle in s0, which saved one frame word. FIXED 2026-11-17: now a dedicated `angle`.
(35c61d `py = (s32)((f32)py + 40.0f)` was fixed in 2026-11-12 round 22.)
## Attempts
2026-11-09..11-14: rounds 9, 16, 17, 22, 34 and 37, PolishMenu3E10Names (opus-5-5 low/xhigh). Separate scale and spin locals gave identical codegen with frame 248/256 (full=2/19). A 4.0f literal at all 7 uses gave full=87/74; those runs folded `85 * 4.0f` to 340.0. Dropping state or p gave 43/158 rows, inlining ang gave 64 rows, and narrowing ang gave >=64 rows. The perm2/perm3 permuter runs reached best=10/66 (posX = 4.0f reuse).
2026-11-17 2026-11-17: cleanup CleanmenuDrawFileSummary, CleanmenuDrawFileSummary, anthropic/claude-opus-5-5: rewrote the function with these changes:
- `four` removed, with a 4.0f literal at every use.
- `posX = 85; posX *= 4.0f`.
- Dedicated `scale`, `scaleY` (no sc reuse) and `angle` locals.
- `strBuf[0x20]` shrunk to `[0x18]` (Q0986), with `scale` declared before posX.
- `(s32)` casts on the sprite x/y args dropped.
- Renamed iconX, iconScale, iconFlag, textX, textY.

Result: fdiff 0. Measurements:
- Literals with posX refined in place: full=17, all sp offsets from four's lost word.
- `85 * 4.0f`: full=74.
- `posX = 85.0f`: full=35 (joins the loop 85.0f web).
- `posX = 85.0`: full=0.
- Block-scoped `{ f32 scale; s32 angle; }`: full=19 (sibling blocks do not share homes).
- An unused pad after strBuf: full=19 (no frame slack).
## Untried ideas
None left for the sites. A possible extra name: `bob`/`ang` could become `bobScale`/`bobAngle` (naming only).
## Evidence
- Frame 240 (0x13bc). Address-taken homes: posX sp+208 (0x1440 `addiu s5,sp,208`), posY sp+204 (0x1444) and strBuf sp+164 (0x1544). Declared locals plus five `_g` gDP words fill sp+144..240 exactly (Q0400).
- 4.0 is loaded once into $f26 at 0x152c/0x1530 and used at 0x1540, 0x1718, 0x1720, 0x1728, 0x1730, 0x18e0 and 0x18ec.
- 0.5 web in $f28 (0x165c): `+ 0.5f` at 0x16d4, `scale = 0.5f` with `*= 4.0f` at 0x1720, and `scaleY * 0.5f` at 0x17bc.
- iconScale 3.0f is in $f22. It is converted at run time (`cvt.d.s` at 0x1484) for the double 0.85 `mul.d` at 0x148c (Q0814).
- The sprite angle is in s0 (`mfhi` at 0x1798 and 0x1828). `scale *= 0.75f` is at 0x1790 and `scaleY = -scale` (`neg.s $f24`) at 0x17b4.
