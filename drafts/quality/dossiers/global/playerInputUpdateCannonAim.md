# playerInputUpdateCannonAim (global, src/global/E4090.c)

## Sites
- **global:806E36B4:do-while0:e9a088**, the `do { ... } while (0);` around 9bdc6b. **The E4090 .data carve fixes it** (see below).
- **global:806E36B4:dead-if:9bdc6b**, `if (!gCurrentActor && !gCurrentActor) {}`, inside the do/while(0) e9a088. It makes &gCurrentActor an entry-block web, so `lui/addiu a3,gCurrentActor` sit at 0x4350/0x4360, ahead of the pad branch. **The E4090 .data carve fixes it.**
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

**2026-11-15, HackplayerTurnByStickX2, opus-5-5:high (E4090 .data carve, Q0552).** Stand-in `.scratch/HackplayerTurnByStickX2/carve_E4090.c` defines E4090's whole .data (`gButtonRemapTable`, `D_80750FF4`..`D_80751000`, `gPlayerInputHandlers[107]`, 0x80750FF0-0x80752C70, generated from the asm). The table names this function, so as1 links the switch `jr t4` (0x4424) to the entry block. All 16 removal subsets of the four sites were measured with `objdump -drz -j .text`:

| Removed (carve) | Diff lines |
|---|---|
| e9a088 + 9bdc6b, or 9bdc6b alone | **0** |
| e9a088 alone (bare dead test left) | 6 |
| subsets with acd1db, without bdc230 | 12 (18 when only e9a088 goes with it) |
| any subset with bdc230 | 84-88 |

- In the plain copy (extern table) the same e9a088 + 9bdc6b removal differs 50 lines: `lui a2,gActivePlayerState` takes 0x4350 and the a3 web starts after the pad branch (0x438c/0x4390).
- With the entry steers gone under the carve, bdc230 and acd1db are pure uopt colouring. Their removal objects are md5-identical carve vs plain. `variants.py scan` on the carve copies: acd1db-free best full=6, both-free best full=29 (u8/u16 sel).
- Permuter (900 s, `-j 2`, base = carve copy with all four steers removed, score 300): 8 zero outputs. Every one adds a dead `if (gCurrentActor) {}` or `if (!gCurrentActor) {}` at the jump-block head, with no p and no `^ 0`. That single test, tagged as new site `global:806E36B4:dead-if:c17942`, is objdump-identical in `carve_E4090.c`. The function goes from **4 tags to 1**.
- uopt -l 6 trace: with the test, web 15 (the `uilod` of gCurrentActor feeding the state and unk155 stores) is coloured to reg 2 ($v1), and sel (web 24) keeps reg 1 ($v0). Without it, web 15 is not a candidate, and 46/48 take regs 2/5.
- In the plain copy (extern table), the same single-test body differs by 50 lines. The a3 placement is the as1 problem again.
- The landing needs the yaml carve: `.scratch/HackplayerTurnByStickX2/header-request.md`.

## Untried ideas
- Permuter on the carve fake-free body: done 2026-11-15 (see the ledger permute line).
- The SchedStruct field `unk280` is already u32 (`sched.h:41`), and Actor.actorType is u32 (0x58), so those widths are not levers.

## Evidence
- Target: &gActivePlayerState is rematerialised in a2 inside the pad branch (0x4364) and again after it (0x437c), and after both calls (0x4438, 0x4450).
- &gCurrentActor sits in a3 from the entry.
- The sibling playerInputHandleAButtonSub5A, which has the same shape, hoists &gActivePlayerState to v1 instead.
