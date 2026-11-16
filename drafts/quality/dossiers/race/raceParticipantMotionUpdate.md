# raceParticipantMotionUpdate (race, src/race/6650.c)
## Sites
race:8002AE9C:proto-steer:8cc620 proto-steer: K&R `void playerStateQueueCallback();` kept the third argument (s32 playerIdx from lbu 0x28(s3)) unmasked in a2; the shared u8 parameter added `andi a2,v0,0xff` at 0x898. REMOVED (2026-11-16).
race:8002AE9C:proto-steer:3db41f proto-steer: file-scope `s32 sfxStopSlotSound(Actor *, u8);` vs the real void return; only raceHandlePostRaceFinished (0x1178) moved, and only while playerStateQueueCallback was the K&R void decl. REMOVED (2026-11-16).
## Attempts
2026-11-09 bootstrap orchestrator: protos.py consolidate 8cc620 -> STEER (no shared header in scope)
2026-11-10 round 4 QualityTools opus:xhigh: shared protos for both -> MISMATCH (return width)
2026-11-11 round 16 CleanRace7BD0 opus:low: EFDC0.h proto, also u8 playerIdx local, also racerState->playerIdx passed directly -> fdiff 1; 7130.h void sfx alone -> fdiff 1 (0x1178 &gCurrentActor a3->v1)
2026-11-11 round 16 Rev16G opus:low: protos.py consolidate -> STEER (both)
2026-11-12 round 28 CleanRace6650 opus:medium: protos.py consolidate -> STEER; void sfx alone fdiff 1
2026-11-16 HackraceParticipantMotionUpdate opus:high: EFDC0.h + 7130.h included, both decls deleted, `u8 playerIdx` declared second (racerState; u8 playerIdx; s32 i; u8 colorMode; u32 flags) -> fdiff 0 (whole object). u8 playerIdx in the base declaration order: code matches but frame 0x48 (colorMode sp+0x3e, offset spill sp+0x30): the two u8 locals packed into one word. 120 declaration orders swept: 12 match, natural one kept. void sfx alone (base otherwise) still fails at raceHandlePostRaceFinished; with EFDC0's s32 return in scope it matches with either sfx return width.
## Untried ideas
none left: function has 0 FAKE / 0 goto.
## Evidence
0x84c addiu sp,sp,-0x50 (frame 0x50); 0x87c lbu a2,0x28(s3) before the flags&0x10 branch, passed unmasked at jal 0x894 (delay slot move a1,s1); colorMode sb at sp+0x43; sfx loop offset temp spilled at sp+0x34 across jal sfxStopSlotSound (0xa20/0xa24).
