# raceRenderSpeedBoostHud (race, src/race/7BD0_manager.c)
## Sites
race:8002C14C:other:a3016e other (REMOVED 2026-11-25): `Gfx *next = renderRotatedSprite(...); i++; offset += 0x10; dl = next;` put ugen's move s2,v0 after the two increments so as1 filled the bnez delay slot with it (0x6c0). Gone with the plain for loop below.
## Attempts
2026-11-09..13 Clean7BD0 / CleanRace7BD0 / Rev16J / Rev22A opus-5-5:low: direct dl assignment (2 rows), traces, permute (round 22 best=0 dl += 0; round 33 hit output-0-1)
2026-11-14 HackraceRenderSpeedBoostHud opus-5-5:high: round-33 hit reviewed: dl++; dl--; (noop-arith), full=0 confirmed, rejected; increments before the call (13), offset bump before (11), offset/i order after (2), offset as i * 0x10 (2); as1probe scan of the direct form, records 100-122: no single edit improves
2026-11-17 cleanup CleanraceRenderCoinHud: direct assignment with both increments in for header scores 2; move s1,zero moves before addiu t0,t0,-34 rather than into the positive-ammo path; guarded form scores 3, split initialization scores 2.
2026-11-17 as1probe scan of for-header form: 1020 single edits, none closes score 2; deleting record 58 (offset zero) scores 1 but leaves offset uninitialized.
2026-11-17 named call result retained but dl=next moved immediately after call: score 2, ugen move $18,$2 precedes both i and offset increments; late assignment scores 0. The result-local classification remains a question for the lead under Q0601/Q1159.
2026-11-17 cleanup CleanraceRenderCoinHud: hack-free-weights permuter from direct assignment, 900s, setup baseline 120, best 120; no output directories or zero-score output.
2026-11-25 continue CleanraceRenderCoinHud opus-5-5: FIXED. Plain `for (i = 0; i < tracker->projectileAmmo; i++) { xOffset = i * 0x10; dl = renderRotatedSprite(..., (s32)((doubleX + xOffset) * 4.0f), scaledY, ...); }` with doubleX/scaledY assigned before the for (offset, f_offset, next locals dropped) -> variants try full=0, fdiff 0 (whole object). Also full=0: everything inline (`(f32)(i * 0x10)` without a local; `screenX * 2.0f` for the doubled terms). Hand-rotated do-while with `f_offset = i * 0x10` (no for) -> full=2.
## Untried ideas
none open (site removed).
## Evidence
0x5ec move s0,zero (i = 0) before the blez 0x5fc; 0x628 move s1,zero inside the guarded preheader = uopt strength-reduced IV for i * 0x10 (Q1616/Q0489), never a source local initialised before the test. Loop tail 0x6a4 jal renderRotatedSprite, 0x6ac lbu v1,42(s3), 0x6b0 addiu s0,1, 0x6b4 addiu s1,16, 0x6bc bnez, 0x6c0 move s2,v0.
doubleX/scaledY assigned before the for still compute after blez (0x604..0x654): uopt moves them into the preheader since only the loop uses them.
