# gfxDrawRotatedTiledBackground (global, src/global/109660.c)
## Sites
global:807069A4:other:901863 (was 5432c9 until 2026-11-17 dropped the redundant `(f32)` cast on the line) other: KEPT (FAKE). `inv` holds the roll angle (`cvt.s.w $f0,$f8; mul.s $f0,$f0,$f10` at 0x2108/0x211c, `mfc1 a1,$f0`) and later `1.0f / scale` (`div.s $f14,$f0,$f8` at 0x237c). A separate f32 roll gives identical instructions but takes one 4-byte declaration slot; the raw frame is exactly 0x1B0, so it rounds to 0x1B8.
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
## Untried ideas
none in natural C. The target has six word slots (0x11C-0x127 and 0x1A4-0x1AF) for seven word-sized values (scrollU, scrollV, i, playerActor, playerState, inv, roll); every one of them must be a variable (loops, values held across calls), and per Q0488 (corrected) cfe emits the heavier operand of an FP multiply first, so `1.0f / scale` read in place always lands first in the three mul.s: inv must be a variable, so the roll must share it.
## Evidence
- Target 0x20e4-0x2120: 0.087890625 in $f10, zero in $f2, the roll converted and multiplied in $f0, then `mfc1 a1,$f0`.
- Target 0x23d8/0x2404/0x2440: `mul.s $f4,$f6,$f14`, `mul.s $f8,$f4,$f14`, `mul.s $f8,$f4,$f14` (constant first, inv in $f14 second). With 1.0f/scale read in place the built copy emits `$f14` first in all three.
- Target 0x2444-0x2450: `-70 * inv` stored to sp+0x68 (chained-assignment temp) and straight from $f8 to spans[0].v[2][0]/[1] (0x13c/0x140); the in-place copy reloads sp+0x68 into $f6 (+1 insn) and the FP ring rotates through 0x25ec.
- Named homes: scale 0x94, b/g/r 0x99-0x9B, mtxB 0x9C, mtxA 0xDC, count 0x12B, spans 0x12C; unaccessed declaration slots 0x11C-0x127 (playerActor/playerState/inv) and 0x1A4-0x1AF (scrollU/scrollV/i); vreg/temp area 0x60-0x93.
