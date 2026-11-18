# gfxDrawRotatedTiledBackground (global, src/global/109660.c)
## Sites
global:807069A4:other:901863 (was 5432c9 until 2026-11-17 dropped the redundant `(f32)` cast on the line) other: FIXED 2026-11-17 (CleangfxDrawRotatedTiledBackground). `inv` held the roll angle (`cvt.s.w $f0,$f8; mul.s $f0,$f0,$f10` at 0x2108/0x211c, `mfc1 a1,$f0`) and later `1.0f / scale` (`div.s $f14,$f0,$f8` at 0x237c). A separate f32 roll gives identical instructions but takes one 4-byte declaration slot; the raw frame is exactly 0x1B0. The word it needs was the cfe temp home (-324vreg, sp+0x6C) of the chained `spans[0].v[2][1] = spans[0].v[2][0] = -70.0f * inv;`: two statements free it, and `f32 roll` declared last (after scale) takes -288vreg (sp+0x90) with every accessed home unchanged.
## Attempts
- Rounds 10, 16, 17, 29 and 2026-11-14 Hack109660BgScroll (history): separate angle 61, inline roll 84, `* 360.0f / 4096.0f` 16, scrollU/scrollV reuse 33/6, playerState/playerActor/scale drops 167/147/80.
- 2026-11-15 HackgfxBuildScrollingBackground2 anthropic/claude-opus-5-5:high, variants.py try (text rows):
  - frame census: separate `f32 roll` declared first, last, after count, b, mtxB, spans, i: 61 at every position.
  - reading 1.0f/scale in place (inv deleted, `roll` the only named f32 at inv's place): 27 rows. Constant-first and inverse-first operand spellings both 27; one-statement `roll = (...) * 0.087890625f` 78; roll declared last 37, first 40; -70 store split into two statements 27; `-(x * 70.0f)` 29; -70 line moved first 61, moved above the while loops 80.
  - s16/u16 integer roll in the 0x128 alignment gap below count, f32 multiply in the guRotateF argument: s16 229, u16 81.
  - variants.py scan of the in-place copy (72 one-edit variants): nothing below 27.
- 2026-11-17 HackgfxDrawMapBackground, variants.py try (full rows):
  - freeing a slot without a new local: scrollU dropped with rotX refined in place into the U scroll 155, scrollV dropped with rotY refined 147 (the refined parameter is promoted to callee-saved $f20: `mtc1 a1/a2,$f20`, `sdc1 $f20,0x40(sp)`, frame still 0x1B8), both dropped 169 ($f20/$f22, frame 0x1C0).
  - `scale = 1.0f / scale` (scale refined into its reciprocal, roll at inv's slot): 126, scale moves to $f20.
  - `register f32 roll`: identical to a plain separate roll (61).
  - layout census: a separate roll declared first moves every named home +4, declared last +8 (the 8-byte rounding pad sits below the named homes); one unused `f32 dummy` does the same (61); two unused dummies declared first give frame 0x1B8 with the named homes unchanged. So the raw frame is exactly 0x1B0 with no slack.
  - `i` narrowed (u8/s8/u16/s16) into the 3-byte gap below count with the roll in i's word slot: 206/207 (&gBgRotatedScale takes a new s6, frame 0x1B8).
  - the `(f32)` cast on the FAKE line is redundant (fdiff 0 without it): dropped.
  - permuter on the in-place body (inv deleted, roll at inv's slot, 1.0f/scale read in place), perm_rtb, -j 2, 900 s, ~4220 iterations: nothing below its own base score 265 (setup baseline 277).
- 2026-11-17 "2026-11-17: cleanup CleangfxDrawRotatedTiledBackground" CleangfxDrawRotatedTiledBackground anthropic/claude-opus-5-5, `uopt_trace -l 5` census plus variants.py try (full rows):
  - census at the base: -288..-320vreg are the 9 GBI `_g` homes (each `ustr{_g}{glist}`), -324vreg (sp+0x6C) is cfe's temp for the chained -70 store (`ustr{310}{umpy -70*inv}` only: never reloaded, no store emitted). The sp+0x68 store at 0x2444 is the spill of the CSE'd `-70*inv` and stays with two statements.
  - separate roll + inv kept + chain split into two statements: roll declared after inv 10 (frame 0x1B0 but mtxA/mtxB/r/g/b/scale all -4), roll declared first 22, roll declared last (after scale) 0 -> fdiff 0. Reverse store order (`[1]` first) with roll after inv 12. Chain kept, roll last: 61 (history).
  - roll forms with the fix: `roll *= 360.0f / 4096.0f;` 0 (kept: degrees per 4096-unit angle), `roll *= 0.087890625f;` 0, one statement `roll = (...) * 0.087890625f` or `* (360.0f / 4096.0f)` 88.
  - `inv` renamed `invScale` (only `1.0f / scale` now); GBI literals 3/20 spelled `G_MDSFT_RENDERMODE` and `gDPSetCycleType(glist++, G_CYC_1CYCLE)` as elsewhere in the file: fdiff 0.
## Untried ideas
none: the site is fixed. Possible readability only: `0x200004` as `G_SHADE | G_SHADING_SMOOTH` (the file's other uses stay literal; check which gbi.h branch is active), `guRotateF(mtxB, roll, 0, 0, 1)` with float literals.
## Evidence
- Target 0x20e4-0x2120: 0.087890625 in $f10, zero in $f2, the roll converted and multiplied in $f0, then `mfc1 a1,$f0`.
- Target 0x23d8/0x2404/0x2440: `mul.s $f4,$f6,$f14`, `mul.s $f8,$f4,$f14`, `mul.s $f8,$f4,$f14` (constant first, inv in $f14 second). With 1.0f/scale read in place the built copy emits `$f14` first in all three.
- Target 0x2444-0x2450: `-70 * inv` stored to sp+0x68 (spill item of the CSE'd product, not the chain temp: it stays with the two-statement form) and straight from $f8 to spans[0].v[2][0]/[1] (0x13c/0x140); the in-place copy reloads sp+0x68 into $f6 (+1 insn) and the FP ring rotates through 0x25ec.
- Named homes: scale 0x94, b/g/r 0x99-0x9B, mtxB 0x9C, mtxA 0xDC, count 0x12B, spans 0x12C; unaccessed declaration slots 0x11C-0x127 (playerActor/playerState/invScale) and 0x1A4-0x1AF (scrollU/scrollV/i); vregs 0x6C-0x93 (fixed copy: roll 0x90, 9 `_g` homes 0x6C-0x8C; base: 9 `_g` homes 0x70-0x90 and the chain temp 0x6C); spill 0x68.
- spans[5]: gfxWrapRectSpan fills at most 4 (1 -> 2 -> 4; its own `RectSpan temp[4]`); the 5th element is never accessed but the frame needs it (by the declaration-order layout, spans[4] would move every home declared after it by 0x18; not compiled).
