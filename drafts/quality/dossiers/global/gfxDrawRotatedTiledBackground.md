# gfxDrawRotatedTiledBackground (global, src/global/109660.c)
## Sites
global:807069A4:other:5432c9 other: KEPT (FAKE). `inv` holds the roll angle (`cvt.s.w $f0,$f8; mul.s $f0,$f0,$f10` at 0x2108/0x211c, `mfc1 a1,$f0`) and later `1.0f / scale` (`div.s $f14,$f0,$f8` at 0x237c). A separate f32 adds a vreg home below the named locals: frame 0x1B0 -> 0x1B8.
## Attempts
- Rounds 10, 16, 17, 29 and 2026-11-14 Hack109660BgScroll: see drafts/quality/dossiers/global/gfxDrawRotatedTiledBackground.md (separate angle 61, inline roll 84, `* 360.0f / 4096.0f` 16, scrollU/scrollV reuse 33/6, playerState/playerActor/scale drops 167/147/80).
- 2026-11-15 HackgfxBuildScrollingBackground2 anthropic/claude-opus-5-5:high, variants.py try (text rows):
  - frame census: separate `f32 roll` declared first, last, after count, b, mtxB, spans, i: 61 at every position (identical diffs, so the extra home is not a declaration-order slot).
  - reading 1.0f/scale in place (inv deleted, `roll` the only named f32 at inv's place): 27 rows. Constant-first and inverse-first operand spellings both 27; one-statement `roll = (...) * 0.087890625f` 78; roll declared last 37, first 40; -70 store split into two statements 27; `-(x * 70.0f)` 29; -70 line moved first 61, moved above the while loops 80.
  - s16/u16 integer roll in the 0x128 alignment gap below count, f32 multiply in the guRotateF argument: s16 229, u16 81.
  - variants.py scan of the in-place copy (72 one-edit variants): nothing below 27.
## Untried ideas
- Reading 1.0f/scale in place leaves only Q0304 value-number operand order (three mul.s) plus the sp+0x68 chained-store reload; a natural spelling that gives the CSE temp a lower value number than the 460/380/-70 constants without a no-op would retire the reuse (Q0304 lists only hack shapes).
## Evidence
- Target 0x20e4-0x2120: 0.087890625 in $f10, zero in $f2, the roll converted and multiplied in $f0, then `mfc1 a1,$f0`.
- Target 0x23d8/0x2404/0x2440: `mul.s $f4,$f6,$f14`, `mul.s $f8,$f4,$f14`, `mul.s $f8,$f4,$f14` (constant first, inv in $f14 second). With 1.0f/scale read in place the built copy emits `$f14` first in all three.
- Target 0x2444-0x2450: `-70 * inv` stored to sp+0x68 (chained-assignment temp) and straight from $f8 to spans[0].v[2][0]/[1] (0x13c/0x140); the in-place copy reloads sp+0x68 into $f6 (+1 insn) and the FP ring rotates through 0x25ec.
- Named homes: scale 0x94, r/g/b 0x99-0x9B, mtxB 0x9C, mtxA 0xDC, count 0x12B, spans 0x12C; vreg/temp area 0x60-0x93.
