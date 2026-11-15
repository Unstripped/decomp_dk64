# gfxDrawRotatedTiledBackground

## Sites
- global:807069A4:other:5432c9 (line 372): the roll angle is computed in `inv`, which is later reused for `1.0f / scale`. Target: `cvt.s.w $f0,$f8; mul.s $f0,$f0,$f10` at 0x2108/0x211c, frame 0x1B0. A separate f32 adds a home (frame 0x1B8) and moves every home and the a0-a2 slots by 8.

## Attempts
- Rounds 10, 16, 17, 29: separate angle, permute, uopt_trace (see the history file).
- 2026-11 Hack109660BgScroll (claude-opus-5-5), variants text rows:
  - disjoint sibling-block locals for roll and inv: 61 (separate homes).
  - roll inline in the guRotateF argument: 84 (frame kept, FP temp ring shifted).
  - `* 360.0f / 4096.0f` inline: 16 (two muls).
  - block roll: 61. Angle declared first/last: 61; at inv's place: 143.
  - s16 pitch snapshot: 234. camActor snapshot: 239.
  - angle plus dropping playerState / playerActor / scale: 167 / 147 / 80.
  - roll held in scrollU: 33; in scrollV: 6.
- sweep: plain and recipe nohit. scan of the separate-angle copy: nothing below the baseline (61).

## Untried ideas
- None that keeps the local count. The 0x1B0 frame fixes 14 locals, so the original reused one of them. Reusing inv is the only spelling that matches.

## Evidence
- Target 0x20e4-0x2120: the 0.087890625 constant is loaded into $f10 and zero into $f2 (both 0 args). The roll is converted and multiplied in $f0, then `mfc1 a1,$f0`.
