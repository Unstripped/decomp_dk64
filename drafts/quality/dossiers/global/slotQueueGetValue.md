# slotQueueGetValue (global, src/global/FCCD0.c)
## Sites
- global:806F8AD4:other:ccffb3 `pa = &player;`: keeps player memory-only, so it is reloaded with lbu 0x2f(sp) at 0xb14/0xb64. Without it: andi a0,a1,0xff at entry, a spill at 0x18, frame 0x30.
- global:806F8AD4:dead-if:4ccde5: slot->value colours v1 (0xb44-0xb74). Without it, v0.
## Attempts
- round 3 (opus:low): diagnose/permute both.
- 2026-11-14 U:
  - K&R definition: identical to ANSI
  - `player & 0xFF`: extra code
  - index spelling: no change
  - valuePtr local: same 4 r
## Untried ideas
- why index (also lbu 0x2b from its home in both) stays uncoloured while player is coloured: a uopt -l 6 priority dump of the removed copy
## Evidence
- frame 0x28
- value homed at 0x26(sp) (sh/lhu)
- world spilled at 0x1c
