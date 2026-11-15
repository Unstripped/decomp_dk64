# mpDrawScoreGlyphs

## Sites
- **5df330 (line 241):** the early `alpha = gPlayerSlots[i].actor->alpha & 0xFF;`. It kills alpha's loop-top 0xFF, so the `>= 0x100` arm keeps its own `li v1,255` (0x844), and it keeps alpha in v1 and the lh in a0.
- Without it, uopt drops that li because alpha is already 0xFF from the loop-top li. alpha moves to a0 and the branch becomes `beqzl at`.

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

## Untried ideas
- Permuter from the `&&` chain body (7): look for a spelling that restores the target polarity (bnez at + andi delay).

## Evidence
- 0x81c `li v1,255`; 0x824 `beqzl t9,0x84c` with `lbu t2` in its delay slot.
- 0x830 `lh a0,0x128(t1)`; 0x838 `bnez at,0x848` with `andi v1,a0,0xff` in its delay slot.
- 0x840 `b 0x848` with `li v1,255` in its delay slot.
