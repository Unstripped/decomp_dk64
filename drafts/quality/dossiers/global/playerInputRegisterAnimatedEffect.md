# playerInputRegisterAnimatedEffect (global, src/global/E4090.c)

## Sites
- **global:806E8244:noop-arith:2a4e3a**, arm 1: `pad = &gPlayerPadState[gCurrentPlayerIndex ^ 0]`. The xor gives the arm's second stride-0x34 multiply a constant web of its own, so ugen expands it as shifts (0x8f5c-0x8f6c) instead of `multu t5,a2`.

## Attempts
**2026-11-14, U HackE4090InputB, opus:high.**

| Form (scored with `variants.py try`) | Diff lines |
|---|---|
| Plain index | 6 |
| pad set once before the if chain | 6 |
| `gPlayerPadState + idx` | 6 |
| sizeof-scaled byte address | 6 |
| Arm 1 without pad, pad set before the chain or before the yaw load | 124-178 |
| Nested `else { if … }` shape | 6 |
| yaw as s32 | 6 |
| yaw as u16 | 10 |
| Arm 1 pad assigned before the stickX read | 84 |

- **Permuter:** 900 s on the fake-free body with hack passes weighted 0. Base 829, best 0. All four zero outputs swap the `^ 0` for an `(int)` or `(long)` cast on the index, which is the Q0681 split, a hidden steer. Not used.

## Untried ideas
- A different source shape for arm 1's st->stickInput read that would not be a reload: there is none, because the target reloads the index after the `sh` at 0x8f54.

## Evidence
- In each arm, `li a2,52` is local to the arm.
- Arm 1: `multu t1,a2` at 0x8f40 for stickX, then pad is computed with sll/subu/sll/addu/sll at 0x8f5c-0x8f6c.
- Arms 2-4: both multiplies use `multu …,a2` (0x8f9c/0x8fb8, 0x8ffc/0x901c, 0x9058/0x9078).
- Q0681: index casts and `^ 0` split the stride-constant web. Plain pointer addition and `(u32)`/`(u16)` casts do not.
