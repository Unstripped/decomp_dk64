# raceRenderCoinHud (race, src/race/7BD0_manager.c)
## Sites
race:8002C2E8:other:a3016e other (REMOVED 2026-11-25): same delayed `dl = next` in the second sprite loop; kept move s2,v0 in the bnez delay slot after count++ and xOffset += 0x18. Gone with the plain for loops below.
## Attempts
2026-11-09..12 Clean7BD0 / CleanRace7BD0 / Rev22A opus-5-5:low: diagnose (count/xOffset past the jal), permute (both sites together; round 22 no output in 600 s)
2026-11-14 HackraceRenderSpeedBoostHud opus-5-5:high: direct dl assignment with count += 1 / count++ and both increment orders (2 rows each)
2026-11-17 cleanup CleanraceRenderCoinHud: direct assignment with both increments in for header scores 2; preheader count initialization moves before blez instead of its slot; guarded form scores 18, split initialization scores 2.
2026-11-17 as1probe scan of for-header form: 2100 single edits, none closes score 2; deleting record 228 (count zero) or 229 (xOffset zero) scores 1 but leaves an initialized loop variable undefined.
2026-11-17 named call result retained but dl=next moved immediately after call: score 2, ugen move $18,$2 precedes the count and xOffset increments; late assignment scores 0. The result-local classification remains a question for the lead under Q0601/Q1159.
2026-11-17 cleanup CleanraceRenderCoinHud: hack-free-weights permuter from direct assignment, 900s, setup baseline 120, best 120; no output directories or zero-score output.
2026-11-25 continue CleanraceRenderCoinHud opus-5-5: FIXED. Both sprite loops as `for (i = 0; i < 5; i++)` / `for (i = 0; i < 5 - tracker->gateMissesLeft; i++)` with `xOffset = i * 0x18;` (f32 local) and direct `dl = renderRotatedSprite(...)`, one shared `i` (s32 xOffset, count, next locals dropped), `s32 pad[2]` kept -> variants try full=0, fdiff 0 (whole object). Variants: only loop 2 converted (loop 1 kept as `xOffset += 0x18` for) 9; without pad[2] 2 (frame); separate counters per loop 11 / 9 with pad; xOffset inline without the f32 local 2 (add.s operand order, Q0023).
## Untried ideas
Frame: a natural local that replaces s32 pad[2] (0x80 vs 0x88 without it) (Q0691, Q1227).
## Evidence
Loop 1: 0x968 addiu s0,s0,24, 0x96c slti at,s0,120: uopt LFTR of i < 5 onto the i * 0x18 IV (no separate counter). Loop 2: 0x9a0 move s1,zero (i = 0) in the blez slot, 0x9a4 move s0,zero after the blez = strength-reduced i * 0x18 IV started in the guarded preheader (Q1616/Q0489). Tail: 0x9f4 jal, 0x9fc lbu t3,68(s5), 0xa00 addiu s1,1, 0xa04 addiu s0,24, 0xa10 bnez, 0xa14 move s2,v0.
