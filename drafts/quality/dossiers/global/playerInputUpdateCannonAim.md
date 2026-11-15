# playerInputUpdateCannonAim (global, src/global/E4090.c)

## Sites
- **global:806E36B4:dead-if:9bdc6b**, `if (!gCurrentActor && !gCurrentActor) {}`, inside the do/while(0) e9a088. It makes &gCurrentActor an entry-block web, so `lui/addiu a3,gCurrentActor` sit at 0x4350/0x4360, ahead of the pad branch.
- **global:806E36B4:other:bdc230**, `p = gCurrentActor; p->state = 0x4C`. This one-use pointer web takes v1 (`lw v1,0(a3)` at 0x43a4, `sb t6,340(v1)` at 0x43b0).
- **global:806E36B4:other:acd1db**, `sel ^= 0`. It keeps the switch selector in its own web: v0 (`lw v0,88(t2)` at 0x43e8, `sltiu at,v0,86`).

## Attempts
**2026-11-14, U HackE4090InputB, opus:high.** All scored with `variants.py try`.

| Grid or variant | Diff lines |
|---|---|
| Entry {none, do/while dead test, bare dead test} x state {direct, p} x selector {direct, sel, sel^0, Actor *held local, held hoisted}, 30 bodies | 0 only with all four current steers |
| Fake-free natural body | 49 |
| Best without the entry dead test | 10 (p + ^0) |
| sel declared as u32/s32/u16/s16/u8, both declaration orders, no ^0 | 6-7 (v0/v1 swap of p and sel) |
| `(u32)` cast switch | 6 |
| `Actor *held` snapshot | 17-29 |
| p reused for the held actor | 17 |
| Block-scoped p/sel | 6 |
| Block-scope extern redeclarations of the three globals, all 6 orders | no change (49 / 16) |
| Early return instead of the outer if | 10 |
| do/while(0) around the pad branch | 27 |
| `if (gCurrentActor) {}` without the wrapper | 28 |

## Untried ideas
- A permuter run on the fake-free body (`seconds>=600`).
- The SchedStruct field `unk280` is already u32 (`sched.h:41`), and Actor.actorType is u32 (0x58), so those widths are not levers.

## Evidence
- Target: &gActivePlayerState is rematerialised in a2 inside the pad branch (0x4364) and again after it (0x437c), and after both calls (0x4438, 0x4450).
- &gCurrentActor sits in a3 from the entry.
- The sibling playerInputHandleAButtonSub5A, which has the same shape, hoists &gActivePlayerState to v1 instead.
