# hudPauseMenuIconUpdate (global, src/global/ACDC0.c)
## Sites
global:806AC07C:other:37222f other: s16 five = 5 used for the compare and subtract on the kong index (KEPT)
## Attempts
2026-11-10..12 (low, medium): literal 5 (90), pad (30), permutes
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: %=5 (115), > 4 (90), ?: (90), range switch (122), i s16/u32 (127/94); same local renamed kongCount (0, not applied: needs a ruling)
## Untried ideas
decision owed: is an s16 kongCount = 5 used for both the bound and the subtraction an accepted real-quantity local
## Evidence
literal 5 shrinks the frame 0x58 -> 0x50 and moves the sp+0x54 reloads.
