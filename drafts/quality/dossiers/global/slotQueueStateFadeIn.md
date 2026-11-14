# slotQueueStateFadeIn (global, src/global/FCCD0.c)
## Sites
- global:806FA5A4:dead-if:533782 `if (gSlotQueue == 0) {}`: callee-saved homes. Target: slot s6, gfx s7, 0x400 s5, 1 s4. Without it: slot s7, gfx s4, 0x400 s6, 1 s5 (19 r, 0x2620-0x2754).
## Attempts
- 2026-11-14 U (first diagnose):
  - while loop, no else, timer--: 19 each
  - early return: 25
  - variants scan: 19
  - `slot == 8 || slot == 9` matches (kept as a review fix)
## Untried ideas
- a uopt -l 6 priority dump to find what the dead global read changes (gSlotQueue base candidate vs slot/gfx priorities)
## Evidence
- frame 0x58
- slot*0x30 spilled at 64(sp)
- gSlotQueue reloaded at 0x2760/0x2790
