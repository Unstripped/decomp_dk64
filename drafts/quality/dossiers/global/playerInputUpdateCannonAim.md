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

**2026-11-17, HackplayerTurnByStickX5, anthropic/claude-opus-5-5:high.** Base 4d0df275 (carve merged), `variants.py try`, full lines, site c17942 only:

| Variant | Diff lines |
|---|---|
| c17942 removed (no guard) | 42 (shape 0) |
| `sel = heldActor->actorType` hoisted above the state store (Q0199 first-appearance order) | 57 |
| `&& gCurrentActor` folded into the jumpTimer test (a real use, extra beqz) | 33 |
| switch directly on `gActivePlayerState->heldActor->actorType`, no sel (Q1148) | 42 |
| one-use `Actor *actor` for the state store only (= bdc230) | 6 |
| `variants.py scan`: guard-free copy | best 29 (sel u8/u16) |
| `variants.py scan`: actor-local copy | best 6 (declswap, widths) |

**2026-11-19, unit "2026-11-18c: cleanup CleanplayerInputUpdateMoveTargetClampedb", CleanplayerInputUpdateMoveTargetClampedb, anthropic/claude-opus-5-5.** Base 9de100e7 (merged carve), site c17942 only, `variants.py try` full lines:

| Variant | Diff lines |
|---|---|
| c17942 removed (if form) | 42 (shape 0) |
| `if (1) {}` in its place (Q0908) | 33 (class 2; sweep classify class 2) |
| guard-return entry `if (T >= 0xF) return;` (Q1368/Q1375 file idiom), no guard | 42 |
| guard-return entry with the guard | 0 (the entry form is no lever) |
| default-first actorType switch (M9 ebd16c6f), no guard / with guard | 57 (shape 4) / 4 |
| invented one-case switch on the button bit (R3 shape), case 0x8000 / default first | 48 / 50 (shape 10-11) |
| switch directly on `heldActor->actorType`, guard-return form | 42 |
| Q0601 `held = gActivePlayerState->heldActor; switch (held->actorType)`, if or return form | 19 |
| held + `sel = held->actorType` (either declaration order) | 19 |
| held + the guard | 17 |
| held read hoisted above the state store | 49 |
| pad local for the button test | 73 |
| `actor` local for both state and unk155 stores | 32 |
| `variants.py scan`: removal copy / held copy | best 29 (sel u8/u16) / no variants |
| permuter perm_ca, 905 s, `-j 2`, base 300 | 4 zeros, all re-insert `if (gCurrentActor) {}` / `if (!gCurrentActor) {}` (perm_refer_to_var is not in HACK_PASSES); best non-zero are one-use Actor aliases or other dead ifs |

- Removal diff: &gCurrentActor a3 -> a2 (0x4350/0x4360), &gActivePlayerState a2 -> v1 (0x4364/0x437c and every `lw x,0(a2)`), the state-store load `lw v1,0(a3)` 0x43a4 -> ring t7.
- uopt -l 6: with the guard, web 15 (`uilod` of &gCurrentActor, const 916) spans the guard block and the store block and is coloured reg 2 (v1); sel web 24 reg 1 (v0); &gActivePlayerState web 46 reg 5 (a2); &gCurrentActor web 48 reg 6 (a3). Without it web 15 is no candidate and 46/48 take regs 2/5. The held local gives two low webs too, but the wrong ones: held (web 24) v0 and the switch temp (web 28) v1.
- R3 does not hold: the function has no if/else on a selector byte. Its only tests are `andi 0x8000`/`beqz` 0x4358-0x435c and `sltiu 15`/`beqzl` 0x4398-0x439c; actorType (`lw v0,88(t2)` 0x43e8, `sltiu 86` / `li 130`) is already a switch.
- Result: c17942 stays FAKE (diagnose nohit, permute nohit). The copy is unchanged.

## Untried ideas
- Permuter on the carve fake-free body: done 2026-11-15 (stand-in) and 2026-11-19 (merged TU); every zero re-inserts the dead read.
- None found that reach the target state codelessly: it needs the gCurrentActor load (web 15) available in a block ahead of the state store, and only a dead read of gCurrentActor at the jump-block head supplies that. A held-actor local (19) fixes both address registers; a natural change that then moves held/the switch temp off v0/v1 (e.g. a reason for the 0x43a4 load to be a web) is the only open direction.
- The SchedStruct field `unk280` is already u32 (`sched.h:41`), and Actor.actorType is u32 (0x58), so those widths are not levers.

## Evidence
- Target: &gActivePlayerState is rematerialised in a2 inside the pad branch (0x4364) and again after it (0x437c), and after both calls (0x4438, 0x4450).
- &gCurrentActor sits in a3 from the entry.
- The sibling playerInputHandleAButtonSub5A, which has the same shape, hoists &gActivePlayerState to v1 instead.

2026-11-15 Lead2 (merge b15f1d44): E4090 .data carve applied; e9a088/9bdc6b/bdc230/acd1db FIXED, c17942 tagged guard remains (net 4 -> 1).
