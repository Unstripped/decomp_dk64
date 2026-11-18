# raceRenderCoinHud (race, src/race/7BD0.c)
## Sites
race:8002C2E8:other:a3016e other: same delayed `dl = next` in the second sprite loop; keeps move s2,v0 in the bnez delay slot after count++ and xOffset += 0x18
## Attempts
2026-11-09..12 Clean7BD0 / CleanRace7BD0 / Rev22A opus-5-5:low: diagnose (count/xOffset past the jal), permute (both sites together; round 22 no output in 600 s)
2026-11-14 HackraceRenderSpeedBoostHud opus-5-5:high: direct dl assignment with count += 1 / count++ and both increment orders (2 rows each)
2026-11-17 cleanup CleanraceRenderCoinHud: direct assignment with both increments in for header scores 2; preheader count initialization moves before blez instead of its slot; guarded form scores 18, split initialization scores 2.
2026-11-17 as1probe scan of for-header form: 2100 single edits, none closes score 2; deleting record 228 (count zero) or 229 (xOffset zero) scores 1 but leaves an initialized loop variable undefined.
2026-11-17 named call result retained but dl=next moved immediately after call: score 2, ugen move $18,$2 precedes the count and xOffset increments; late assignment scores 0. The result-local classification remains a question for the lead under Q0601/Q1159.
2026-11-17 cleanup CleanraceRenderCoinHud: hack-free-weights permuter from direct assignment, 900s, setup baseline 120, best 120; no output directories or zero-score output.
## Untried ideas
Investigate a natural preheader that initializes count in the blez delay slot while retaining the direct-assignment for loop.
## Evidence
Loop tail as in the twin: move s2,v0 is the bnez delay-slot instruction after addiu s0,s0,0x18 and the count increment.
At 0x9f4 jal renderRotatedSprite; 0xa00 count increment, 0xa04 xOffset increment, 0xa10 bnez, 0xa14 move s2,v0. The direct for form emits ugen move before increments but as1 still fills this slot; its separate preheader is the mismatch.
