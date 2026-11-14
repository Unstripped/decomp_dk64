# raceGetNextWaypointIndex (race, src/race/1770.c)
## Sites
race:80025770:other:b83936: kept; see Evidence.
## Attempts
2026-11-11/12 rounds 16, 17, 22, 23 (opus:low): plain, diagnose, as1probe, permute (see history).
2026-11-14 HackraceApplyPositionOffset opus:high: no next local (3: compare in t6, recompute in the delay slot), ternary with/without next (4/7), compare reversed and == 0-first forms (5-6), next reset to 0 then returned (5), curWaypoint incremented in place or ++ in the test (6-7), result local initialised 0 with or without next (5-7), return in an else (4), >= bound (6)
## Untried ideas
none recorded.
## Evidence
target 0x0-0x10: addiu v1,a1,1; beq a0,v1; move v0,zero (delay); jr ra / move v0,v1: next lives in v1 and the returned value is a copy. Returning next colours next into v0 (return-register preference) and the compare becomes beql a0,v0 with move v0,zero duplicated (4 lines); the recomputed curWaypoint + 1 is CSE'd into next's v1 and copied
