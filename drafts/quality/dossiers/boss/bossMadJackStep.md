# bossMadJackStep (boss, src/boss/52B0.c)
## Sites
- boss:80029468:goto:ua30a4 `goto block_28;`: goto-hand kept (Q0591 shared tail).
## Evidence
- jtbl:
  - .rodata+0x80/+0x88 (0x28/0x2A) -> 0x83c: jal actorTurnTowardActorYaw (0x848), then b 0x8e8 (0x850)
  - .rodata+0xf8 (0x46) -> 0x858: the yaw block; every arm branches to 0x8e8
- No state test between either entry and the tail.
## Attempts
- Rev16I/Rev17M (opus:low): goto-hand kept; merged `state != 0x46` (fdiff 1).
- 2026-11-14 U, scored with variants.py try (full=):
  - fall-through with a selector guard: 14-16
  - merged `== 0x46` if/else or inner switch: 24
  - flag local: 249
