# raceOpponentRacerBehaviorUpdate (race, src/race/52B0.c)
## Sites
race:8002A0AC:other:d19aac other: s32 raceResult first held target->participant so ugen emitted the a1 load before move a0,s0 (jal delay slot order at 0x11ac/0x11b4) (FIXED)
## Attempts
2026-11-11 r16 CleanRace7BD0 / Rev16E opus-5-5:low: separate RaceParticipant * locals, inline argument (fdiff 1), shared chased local, permute (second pointer copy only)
2026-11-14 HackraceOpponentRacerBehaviorUpdate opus-5-5:high: inline argument (4 rows: move a0 / lw a1 delay-slot swap, confirmed in ugen with as1probe keep), function-scope rival local (2: raceResult slot sp+40 instead of sp+44), reuse of chased (35), arguments split over lines (4 rows), block-scoped RaceParticipant *rival in the case-3 if block (0, applied)
## Untried ideas
none (fixed)
## Evidence
Case 1: lw t3,4(t2); sw t3,52(sp) (chased home); move a0,s0; jal; lw a1,52(sp) (0x1124-0x1138). Case 3: lw a1,4(t2) at 0x11ac, jal raceGetFinishCutsceneCam with move a0,s0 in the delay slot, sw v0,44(sp) / lw t3,44(sp) (raceResult home). raceGetFinishCutsceneCam is defined in this file and returns s32.
