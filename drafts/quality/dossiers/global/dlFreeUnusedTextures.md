# dlFreeUnusedTextures (global, src/global/36880.c)

## Sites
global:80636784:dead-if:acad4c (removed): `if (restore != 0) {}` before the do-while hoisted restore (lbu s2,0x63(sp)) and kept tail uncoloured; without it tail took $s5 (andi s5,a3,0xff), 0xfd took $s7, frame 0x58.

## Attempts
2026-11-09..13 (Clean36880, Rev16E, Rev21B, CleanGlobal36880 permP6): removal 35 lines; while/early-return/for outer-loop shapes 35-48; permuter best=0 only with do-while(0)/(long long) hacks. See history.
2026-11-15 HackmodelSlotsStepSegmentCommands anthropic/claude-opus-5-5:high: removal + bare `if (restore)` 25; ANSI u8 definition (PROTO_SKIP stand-in) same as K&R; node walk as `while (node != NULL && found == 0)` 20, + bare restore 12; `while (found == 0 && node != NULL)` / `for (node = nodes; found == 0 && node != NULL; node = node->next)` + bare restore 0; same with `restore != 0` 7; outer `for (; start != end; start++)` 0 (kept). Dropping the w local: 37.

## Untried ideas
(none open)

## Evidence
Target 0x4c34 lbu s2,0x63(sp) (restore) and 0x4c38 li s1,1 in the preheader; 0x4c5c lbu a0,0x5f(sp) (tail reloaded per node); 0x4cfc bnez v1 (found) before 0x4d00 lw v0,0xd4(v0) / 0x4d04 bnez v0 (node): found is tested before node. Q0596, Q0494, Q0196.
