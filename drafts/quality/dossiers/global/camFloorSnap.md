# camFloorSnap (global, src/global/201B0.c)

## Sites
global:8061B9B0:other:6c7f1e `if (1) {}` after `ret = 0;` (FAKE, kept): gives the floorActor def (`lw t2,0(a1)` at 0x520) a uopt basic block (bb0) that holds no call. That keeps LR0 (floorActor, -4vreg, home sp+0x7c) colourable in t2 (uopt 9), with saves and reloads around every jal (0x578/0x59c, 0x784/0x7c0, 0x7e4/0x804, 0x974/0x9a0, 0xa10/0xa1c).

## Attempts
2026-11-14 HackcamFloorSnap anthropic/claude-opus-5-5:high: diagnose nohit. Hack-free body = 141 (`lw t6,0(a1)` hoists to 0x51c, `sw t6,124(sp)` home, every t2 save and reload missing). Placement probe: the boundary matches (0) before `ret = 0`, after `unkFA = 0` or right before the call; at the function end or in the else arm it gives 141. A bare `{ }` compound statement produces no ugen label (141). Natural respellings all score 141: else-if for the cutscene arm, merged `if (snapMode)` blocks, initialisers at declaration, ternary ceilMargin. An s32 `hit` temp scores 177. Variants scan of the hack-free body: best 121 (`cnt` as s8). review fixed: dropped `s32 pad3` (redundant frame pad; dropping pad2 too gives 69).
2026-11-17 HackcamFloorSnap2 anthropic/claude-opus-5-5: diagnose nohit. Re-traced at f2fddb55 after TypesOwner batches 3/8F: LR0 facts unchanged (boundary: reg 9, adjsave 0.28, bb0 needregsave=false; plain 141, bb0 needregsave=true, split 279/282/285). New probes: an unreferenced C label `entry:` before `ceilY = -32768.0f` scores 141 (cfe drops it, no ugen label); floorActor declared in a nested block over the body (Q1060 home order) 179; inverted arms (`if (!collisionCheckActorFloor(...))`, cutscene arm first) 239; an empty `switch (snapMode) {}` in place of the `if (1)` matches (0) but is the same dead no-code label (hack-for-hack, not applied). names fixed: params `targetDist`/`stepFactor` renamed `posX`/`posZ` (collisionCheckActorFloor takes x, y, z; callers pass `*outX`/`*outZ` and `*eyeX`/`*eyeZ`). review fixed.

## Untried ideas
- A natural construct that leaves a uopt label but emits no code between the decls and the first jal, for example a compiled-out debug macro. Every such construct found so far (`if (1) {}`, empty `switch (snapMode) {}`, `do {} while (0)`) is a dead test (Q0502) and stays FAKE; an unreferenced C label and a bare `{ }` leave no label.
- More savings for LR0: a natural extra floorActor occurrence in its own block that emits the same code. The target's only floorActor reads are speedY/state at 0x92c-0x958, state at 0xb08-0xb9c and yaw at 0xc30.

## Evidence
- uopt -zdbug:5, with the boundary: `>>>active<<<{925|0} 0 9`, adjsave 0.28, forbidden [1..8,14], bb0 `firstisstr=true needregsave=false`.
- Without the boundary: LR0 is split (279, 282, 285) and no piece is coloured. The bb0 piece has adjsave 0.0 and `needregsave=true`.
- Target 0x500-0x568 is one straight-line block (ret sb 0x73, ceilY 0x74, floorY 0x78, unkFA, cnt 0x6a, jal at 0x55c), so the label must not emit any code.
