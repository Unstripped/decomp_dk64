# raceRenderSpeedBoostHud (race, src/race/7BD0.c)
## Sites
race:8002C14C:other:a3016e other: `Gfx *next = renderRotatedSprite(...); i++; offset += 0x10; dl = next;` puts ugen's move s2,v0 after the two increments so as1 fills the bnez delay slot with it (0x6c0)
## Attempts
2026-11-09..13 Clean7BD0 / CleanRace7BD0 / Rev16J / Rev22A opus-5-5:low: direct dl assignment (2 rows), traces, permute (round 22 best=0 dl += 0; round 33 hit output-0-1)
2026-11-14 HackraceRenderSpeedBoostHud opus-5-5:high: round-33 hit reviewed: dl++; dl--; (noop-arith), full=0 confirmed, rejected; increments before the call (13), offset bump before (11), offset/i order after (2), offset as i * 0x10 (2); as1probe scan of the direct form, records 100-122: no single edit improves
2026-11-17 cleanup CleanraceRenderCoinHud: direct assignment with both increments in for header scores 2; move s1,zero moves before addiu t0,t0,-34 rather than into the positive-ammo path; guarded form scores 3, split initialization scores 2.
2026-11-17 as1probe scan of for-header form: 1020 single edits, none closes score 2; deleting record 58 (offset zero) scores 1 but leaves offset uninitialized.
2026-11-17 named call result retained but dl=next moved immediately after call: score 2, ugen move $18,$2 precedes both i and offset increments; late assignment scores 0. The result-local classification remains a question for the lead under Q0601/Q1159.
2026-11-17 cleanup CleanraceRenderCoinHud: hack-free-weights permuter from direct assignment, 900s, setup baseline 120, best 120; no output directories or zero-score output.
## Untried ideas
Investigate a natural preheader that initializes offset only on the positive-ammo path while retaining the direct-assignment for loop.
## Evidence
0x6a4 jal renderRotatedSprite (sw t8,24(sp) in the slot), 0x6ac lbu v1,42(s3), 0x6b0 addiu s0 (i), 0x6b4 addiu s1,16 (offset), 0x6bc bnez with move s2,v0 in the slot (0x6c0). ugen (direct form): move $18,$2 right after jal.
Direct for form ugen records jal, move $18,$2, .loc, addu $16,1, addu $17,16, lbu, blt; nevertheless as1 fills the target branch slot with move $18,$2. The remaining score 2 is the offset initialization in the preheader.
