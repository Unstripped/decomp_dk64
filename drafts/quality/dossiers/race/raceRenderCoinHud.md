# raceRenderCoinHud (race, src/race/7BD0.c)
## Sites
race:8002C2E8:other:a3016e other: same delayed `dl = next` in the second sprite loop; keeps move s2,v0 in the bnez delay slot after count++ and xOffset += 0x18
## Attempts
2026-11-09..12 Clean7BD0 / CleanRace7BD0 / Rev22A opus-5-5:low: diagnose (count/xOffset past the jal), permute (both sites together; round 22 no output in 600 s)
2026-11-14 HackraceRenderSpeedBoostHud opus-5-5:high: direct dl assignment with count += 1 / count++ and both increment orders (2 rows each)
## Untried ideas
none natural (same cause as raceRenderSpeedBoostHud)
## Evidence
Loop tail as in the twin: move s2,v0 is the bnez delay-slot instruction after addiu s0,s0,0x18 and the count increment.
