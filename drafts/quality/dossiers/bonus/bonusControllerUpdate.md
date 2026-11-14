# bonusControllerUpdate (bonus, src/bonus/0.c)
## Sites
- bonus:80024158:goto:uef380 goto: case 15 (0x314-0x35c) jumps back with `b 0x2f8` into the single textTableGetString(0x1A,2,1) jal at 0x2fc (case 14 -> 0/4/13 tail).
- bonus:80024158:goto:u4da95 / u4da95#2 goto: the render block at 0x950 has the single jal renderCallbacksRegister at 0x968. It is entered by:
  - the case 2 fall-through,
  - `b 0x950` at 0x83c (cases 7/8),
  - `beql v1,t9,0x950` at 0x900 (cases 0/4/11/13/14/15).
- bonus:80024158:other:31a06c other: `pv = &challengeType` makes challengeType aliased, so every use reloads sp+0x6F. Without it, uopt hoists one load (lbu v0,0x77 at 0x9b4) across resQueueSetValue, with a spill slot at 0x3c, and the frame grows from 0x78 to 0x80.
## Attempts
- rounds 9/14/20 (opus:low):
  - goto-hand kept x3 (duplicate tails fdiff 1)
  - pv: plain/recipe nohit; direct challengeType == 3 gives 0x80/sp+0x77; permute best=0 re-takes the address
  - guide ido-fake-match-removal-bonus-0-12A0-9010#1: pre-switch if and duplicate tails change dispatch; a 2-element array changes text size
- 2026-11-14 U HackbonusControllerUpdate (opus:high), scored with variants.py try (full=):
  - merged case 14/15 with if/else in front of the tail: 81
  - doRender flag local tested after the switch: 103
  - struct local { u8 targetCount; u8 type; }: identical to plain u8 (frame 0x80, 49 r + 60 s diffs)
  - u8 params[2]: .text 4752 vs 4768
  - uopt -l 6 trace of the pv-removed copy: challengeType (bit 5, -9vreg) is never coloured, so the frame growth comes from the hoisted-load spill slot at 0x3c
## Untried ideas
- A natural statement in the late region (after `switch (s->unk0)`) that stops uopt hoisting the challengeType load above the `D_8076AEF2 == 0x11` test (0x9b4). Candidates: rewriting the D_8002D863[challengeType << 2] index expression, or moving the resQueueSetValue condition. Each must keep the target's reloads at 0x9cc/0x9d8.
- Per-type actor view `{ Actor base; LB3bState *unk178; }` for the `(u8 *)gCurrentActor + 0x178` cast: a file-scope edit shared with the function at line 44.
## Evidence
- frame `addiu sp,sp,-120` (0x78)
- challengeType: sb at 0x190; lbu 0x6f(sp) at 0x28c, 0x488, 0x78c, 0x9cc, 0x9d8, 0xa8c, 0xaa8, 0xab4, 0xb20
- targetCount sp+0x6E, also memory-resident
- no `addiu aN,sp,0x6f` anywhere
- first switch jump table at 0x29c
- tail jal at 0x2fc; render jal at 0x968
