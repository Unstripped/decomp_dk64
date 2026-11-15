# bossMadJackStep (boss, src/boss/52B0.c)
## Sites
- boss:80029468:goto:ua30a4 -> u2103c `goto attackSequence;` (was `block_28`), goto-hand kept (Q0591): states 0x28/0x2A
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
## Untried ideas
- none structured: every form adds a state compare the target lacks (Q0844/Q0845 need compared case values)
## Evidence
- Outer switch: `lbu v1,340(s0)` 0x2b8; jtbl .rodata+0x58 indexed by state-0x1E (0x2c0-0x2dc).
- .rodata+0x80/+0x88 (0x28/0x2A) -> 0x83c; .rodata+0xf8 (0x46) -> 0x858 (re-read 2026-11-15 from expected/ relocs).
- 0x83c-0x854: `li a0,20; jal actorTurnTowardActorYaw; sw t0,76(sp)` / `b 0x8e8; lw t0,76(sp)`. No state compare.
- 0x858-0x8e4: yaw += unk2E; mathAngleSignedDistance; both clamp arms `b 0x8e8` (0x8ac/0x8b4/0x8d4/0x8dc).
- 0x8e8: `lw s0,0(s1); lbu t4,341(s0)`; unk155 jtbl at .rodata+0x148; layout continues with the other outer
  cases (0x37 etc.) after it, so the tail cannot sit after the outer switch (the outer break target is 0xf3c).
