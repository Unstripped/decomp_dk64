# mpDrawScoreGlyphs (multiplayer, src/multiplayer/0.c)

## Sites
- multiplayer:800246EC:other:5df330 other (FIXED 2026-11-17): the early `alpha = gPlayerSlots[i].actor->alpha & 0xFF;` was a dead store (both clamp arms overwrite it). It killed alpha's loop-top 0xFF, so the `>= 0x100` arm kept its own `li v1,255` (0x844) and alpha stayed in v1 with the lh in a0. Without it, uopt dropped that li (Q0840) because alpha already held 0xFF from the loop-top li. alpha moved to a0 and the branch became `beqzl at`.
- No sites remain.

## Attempts
**2026-11-14 HackSmallLeftovers (claude-opus-5-5):** Actor.alpha is s16 at 0x128, so the `& 0xFF` is a real andi.

| form | text |
|---|---|
| removal / ternary / `> 0xFF` / `< 0x100` first / u32 alpha | 11 |
| override without else | 22 |
| if/else on unk2EA | 18 |
| `unk2EA == 0 \|\| alpha >= 0x100` | 17 |
| `unk2EA && alpha < 0x100` (and its ternary) | 7 (registers right; branch polarity flipped, beqz at + nop) |
| s16/s32 alpha snapshot | 16 |
| Actor * snapshot | 66 |
| load-once `alpha &= 0xFF` | 70 |
| u8 alpha | 51 |

**2026-11-17 cleanup CleanmpDrawScoreGlyphs (claude-opus-5-5):** fixed, fdiff 0. The raw field is loaded into alpha itself, the test is written on alpha, and the else arm reads the field again:
```c
alpha = 0xFF;
if (gPlayerSlots[i].unk2EA != 0) {
    alpha = gPlayerSlots[i].actor->alpha;
    if (alpha >= 0x100) {
        alpha = 0xFF;
    } else {
        alpha = gPlayerSlots[i].actor->alpha & 0xFF;
    }
}
```
The live raw store is the killing store Q0840 needs. The else re-read CSEs to the one `lh a0`, so `andi v1,a0,0xff` lands in the bnez delay slot. This is the 13980 schedStartTask copy-then-read-again lever. Scores (variants.py try, full):

| form | full |
|---|---|
| the fix above; also with `> 0xFF`, a ternary else, or a `(u8)` else | 0 |
| else `alpha &= 0xFF` (lh into alpha's register) | 70 |
| separate `s32 a` for the test, else re-read | 39 |
| `Actor *actor` local for both reads | 61 |
| `PlayerStruct *slot` local for every access | 70 |
| `if (unk2EA == 0) alpha = 0xFF; else if (>= 0x100) ... else ...` | 25 |
| `unk2EA == 0 \|\| clamp` | 17 |
| if/else of unk2EA, `< 0x100` arm first | 19 |
| `alpha = 0xFF; if (unk2EA != 0 && field < 0x100) alpha = field & 0xFF;` | 32 |
| F1 scan (alpha &= 0xFF form): u8/u16 alpha 45, s16 64 | |

Review: dropped the `(s16)`/`(f32)` casts of the split-screen glyphX. They are implicit conversions, and fdiff passes without them.

## Untried ideas
- None open. The `alpha &= 0xFF` load-once spelling of the else arm stays 70; only a lead ruling on the else re-read could reopen the site.

## Evidence
- 0x818 `li v1,255`; 0x824 `beqzl t9,0x84c` with `lbu t2` in its delay slot.
- 0x830 `lh a0,0x128(t1)`; 0x834 `slti at,a0,256`; 0x838 `bnez at,0x848` with `andi v1,a0,0xff` in its delay slot.
- 0x840 `b 0x848` with `li v1,255` in its delay slot. This is the then-arm of a real if/else whose else falls through to the join at 0x848.
- 0x8cc-0x8f0: `mtc1/cvt.s.w/mul.s/cvt.d.s/sub.d/trunc.w.d` is `(i + 1) * spacing - 20.0` in double. It is the same with or without the explicit casts.
