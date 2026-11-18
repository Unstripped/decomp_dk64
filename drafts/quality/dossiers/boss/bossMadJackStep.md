# bossMadJackStep (boss, src/boss/52B0.c)
## Sites
- boss:80029468:goto:ua30a4 -> u2103c `goto attackSequence;` (was `block_28`), goto-hand kept (Q0591, Q0953): states 0x28/0x2A
  jump-table entry 0x83c runs `jal actorTurnTowardActorYaw` (0x848) then `b 0x8e8` (0x850, delay `lw t0,76(sp)`
  reloads the spilled scriptState) over the 0x46 yaw block (0x858-0x8e4) into the shared unk155 switch at 0x8e8.
## Attempts
- Rev16I/Rev17M (opus:low): goto-hand kept; merged `state != 0x46` (fdiff 1).
- 2026-11-14 HackbossMadJackStep (opus:high), scored with variants.py try (full=):
  - fall-through with a selector guard: 14-16
  - merged `== 0x46` if/else or inner switch: 24
  - flag local: 249
- 2026-11-15 U HackbossMadJackStep2 (opus:high), variants.py try (full=), goto-hand kept (Q0591):
  - sentinel inner switch (case 0x46 yaw, default turn call): 24
  - inner switch (case 0x28/0x2A turn, default yaw): 10
  - source-order if-chain `state == 0x28 || state == 0x2A` turn else yaw: 14
  - arm order `!= 0x28 && != 0x2A` yaw first: 24
  - case 0x46 first, fall-through into guarded turn: 27
  - tail as a state-gated block after the outer switch: 736
  - duplicated tail in both cases: 520
  - review: dropped 6 redundant (f64) casts in case 7 (fdiff 0); label block_28 -> attackSequence
- 2026-11-17 U HackbossMadJackStep3 (opus-5-5, strength-3 dispatch), goto-hand kept (Q0591, Q0953):
  - Duff forms (case 0x46 label inside a block the 0x28/0x2A path skips), variants.py try: `if (0) { case 0x46: yaw }` 0,
    `if (1) { turn } else { case 0x46: yaw }` 0, `do { turn; break; case 0x46: yaw } while (0);` 0 (fdiff OK on the
    if (0) copy). All three give the target's `b 0x8e8` at 0x850 over 0x858-0x8e4; each is a constant-condition
    construct (dead if / do-while(0)), so a hack swap: rejected (Q0953).
  - merged `case 0x28: case 0x2A: case 0x46: if (state != 0x46) turn else yaw` re-measured in register terms (full=10):
    +16 bytes = `lbu a0,0x154(s0)` + `move v1,a0` at 0x2b8/0x2c0 (the outer selector stays live in a0 for the merged
    compare) and `li at,0x46; beq a0,at,yaw` at 0x840/0x844 (yaw `lui t7` hoisted into the beq delay slot), jtbl
    .rodata+0xf8 retargeted to the merged entry; every other instruction identical. The extra compare is the only cost.
  - permuter (hack-free weights, -j 2, 900 s) from the merged form: baseline 456, best 335 (an unreachable
    `turnSpeed = state != 0x46;` before the case labels, then `if (turnSpeed)`: semantics broken); no zero, nohit.
  - review: `turnSpeed >= -0x31` -> `turnSpeed > -0x32` (mirrors the `< 0x32` arm; fdiff 0, same `slti at,v1,-49`).
## Untried ideas
- none structured left: the join is reachable without a compare only through an unconditional jump over the case 0x46
  entry, i.e. a goto or a case label inside a constant-condition block (measured 2026-11-17, Q0953); IDO does not thread
  value-known branches (Q1156), so every compare-carrying form keeps its compare.
## Evidence
- Outer switch: `lbu v1,340(s0)` 0x2b8; jtbl .rodata+0x58 indexed by state-0x1E (0x2c0-0x2dc).
- .rodata+0x80/+0x88 (0x28/0x2A) -> 0x83c; .rodata+0xf8 (0x46) -> 0x858 (re-read 2026-11-17 from expected/ objdump -drz).
- 0x83c-0x854: `lui/lw a1 gBehaviourTargetActor; li a0,20; jal actorTurnTowardActorYaw; sw t0,76(sp)` / `b 0x8e8; lw t0,76(sp)`.
  No state compare.
- 0x858-0x8e4: yaw += unk2E; mathAngleSignedDistance (jal 0x87c, `sw t0,76(sp)` delay, `lw t0,76(sp)` in the blez delay
  0x888); clamp arms `b 0x8e8` (0x8ac/0x8b4/0x8dc), `bnezl 0x8e8` 0x8d4; 0x8e4 `sh t3,46(v0)` falls into 0x8e8.
- 0x8e8: `lw s0,0(s1); lbu t4,341(s0)`; unk155 jtbl at .rodata+0x148; layout continues with the other outer
  cases (0x37 etc.) after it, so the tail cannot sit after the outer switch (the outer break target is 0xf3c).
- uopt -l6 (2026-11-17): scriptState = candidate bit 0 `{1392|0} isvar M -4vreg` (home sp+0x4C), colored first among
  the locals to uopt 7 = $t0 (caller-saved), so every jal is bracketed by `sw t0,0x4c(sp)` (jal delay) and
  `lw t0,0x4c(sp)`. The 0x854 delay-slot reload is that post-call restore, moved by as1 into the `b` delay slot; the
  merged and Duff forms reproduce it unchanged (merged: 0x85c/0x864), so it does not constrain the form.
