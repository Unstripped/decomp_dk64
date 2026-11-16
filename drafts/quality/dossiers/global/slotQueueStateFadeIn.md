# slotQueueStateFadeIn (global, src/global/FCCD0.c)
## Sites
- global:806FA5A4:dead-if:533782 `if (gSlotQueue == 0) {}`: FIXED (2026-11-16, HackslotQueueStateFadeIn2).
  - Block split (Q0908 class 1): `if (1) {}` also matches, but only at the end of the done arm or in the timer else arm.
  - uopt -l5: without it gfx (cand 27) has adjsave 25/10 = 2.50 > slot 17/7 = 2.43, so gfx is coloured first (gfx s4, 1 s5, 0x400 s6, slot s7). The extra block makes it 25/11 = 2.27, below slot and the constants (1 s4, 0x400 s5, slot s6, gfx s7).
  - Fix: the node == NULL switch uses `break` and one `return gfx;` after it, no `else` around the loop, loop as `while (node != NULL)`: fdiff 0.
## Attempts
- 2026-11-14 U (first diagnose):
  - while loop, no else, timer--: 19 each
  - early return: 25
  - variants scan: 19
  - `slot == 8 || slot == 9` matches (kept as a review fix)
- 2026-11-16 U HackslotQueueStateFadeIn2 (anthropic/claude-opus-5-5:high):
  - classify: `if (1) {}` 0; `;` 19; `if (1) {}` elsewhere (before state = 2, after the done block, loop end, function top) 111.
  - switch for the timer 28; state store first 42; `return gfx` inside the done arm 21.
  - NULL-arm switch with `return` per case: 19 (with or without else); with `break` + else kept: 4; else-if chain with one final return: 14-19; `break` + shared return, no else: 0 (applied).
  - `fade += 102.4f`, `> 0x400`, `++`/`--`: 0 (applied).
## Untried ideas
- none (no hack left)
## Evidence
- frame 0x58
- slot*0x30 spilled at 64(sp)
- gSlotQueue reloaded at 0x2760/0x2790
