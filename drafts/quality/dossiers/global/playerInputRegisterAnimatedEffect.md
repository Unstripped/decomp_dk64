# playerInputRegisterAnimatedEffect (global, src/global/E4090.c)

## Sites
- **global:806E8244:noop-arith:2a4e3a** (fixed 2026-11-17), arm 1: `pad = &gPlayerPadState[gCurrentPlayerIndex ^ 0]`. The xor gave the arm's second stride-0x34 multiply a constant web of its own, so ugen expanded it as shifts (0x8f5c-0x8f6c) instead of `multu t5,a2`. Removed together with the whole `pad` pointer.

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

**2026-11-17, U CleanplayerInputRegisterAnimatedEffect (session 2026-11-17f).** FIXED, FAKE 1 -> 0, fdiff exit 0.

| Form (scored with `variants.py try`) | Diff lines |
|---|---|
| Plain index (re-measured) | 6 |
| Arm 1 `pad = &a[i]; st->stickInput = pad->stickX;` | 84 |
| Arm 1 `pad = &a[i]; st->stickInput = a[i].stickX;` | 84 |
| Arm 1 without pad, arms 2-4 pad, tail element read | 155 |
| Arm 1 pad, arms 2-4 pad, tail element read | 155 |
| Arm 1 without pad, arms 2-4 element access, tail `pad->` | 152 |
| **No pad pointer: element access in all arms and the tail** | **0** |

- `variants.py scan` on the fixed body: every comparison swap and width variant (yaw s32, t s16/s32/u32) also scores 0; kept as written.

## Untried ideas
- None for the site (fixed).

## Evidence
- In each arm, `li a2,52` is local to the arm.
- Arm 1: `multu t1,a2` at 0x8f40 for stickX, `sh t4,2(a3)` at 0x8f54, index reloaded `lbu t5,0(a1)` at 0x8f58, then the address is computed with sll/subu/sll/addu/sll at 0x8f5c-0x8f6c into v0 (`addu v0,a0,t6` at 0x8f74) for the tail `lb v1,46(v0)` at 0x909c. Arm 1 never writes the pad.
- Arms 2-4: both multiplies use `multu …,a2` (0x8f9c/0x8fb8, 0x8ffc/0x901c, 0x9058/0x9078).
- Fixed source, uopt `-zdbug:5`: candidates `umpy{idx}{52}` (bit 21) and `uixa{gPlayerPadState}{umpy}` (bit 22); the const web `{52|0}` (a2) counts 1 use in bb 6 (arm 1) and 2 in bbs 9/12/13 (arms 2-4). The tail's element address is therefore a second, uncoloured-constant computation in arm 1 (inferred: code motion inserts the tail's partially redundant address in arm 1, where the `sh` through `st` killed the index; arms 2-4 already hold it in v0 after their post-store reload).
- Q0681: index casts and `^ 0` split the stride-constant web. Plain pointer addition and `(u32)`/`(u16)` casts do not. A `pad` pointer local (`uadd{umpy}{base}`) is a different expression from the element read (`uixa{base}{umpy}`, Q0776/Q0175); with no pointer, every access is the same uixa expression.
