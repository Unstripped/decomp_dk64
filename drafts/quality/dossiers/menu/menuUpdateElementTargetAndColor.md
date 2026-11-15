# menuUpdateElementTargetAndColor (menu, src/menu/3E10.c)

## Sites
All seven fixed on 2026-11-15 (HackmenuUpdateElementTargetAndColor2); none left.
- menu:80030C14:dead-if:787316 dead-if: `if (elemActor && elemActor && elemActor) {}` in inner case 3. Its extra blocks lowered idx (-36vreg) adjsave from 3.0 to 2.0, so the D_80033804 phantom (2.33) was coloured first.
- menu:80030C14:dead-if:da4772 dead-if: `if (D_80033804 && D_80033804) {}` in inner case 10. First read of the D_80033804 load candidate (uilod{1335}, bit 266).
- menu:80030C14:dead-if:eed27b dead-if: `if (D_80033804 == 0) {}` after `t = (s16)idx`. Second read: it makes bit 266 live from case 10 through the join (bbs 97/98/103-108, adjsave 2.33). Bit 266 interferes with idx and is coloured v1 but emits no code, because ugen deletes the guards. idx then has v0/v1/a0 forbidden and gets a1.
- menu:80030C14:dead-if:ac6bed dead-if: `if (outFlag != 0) {}` between scaleX and scaleY in case 15. It split case 15, which dropped the D_80033F68/F80/F98 uixa address candidates from 3.0 to 1.5, below idx.
- menu:80030C14:other:ac50a9 / 8cc650 / 888422: byte puns `*((u8 *)D_800337DC + (idx << 2) + k)`, now `(D_800337DC + idx)->r/.g/.b`.

## Attempts
- 2026-11-09..14: 175 events (CleanE4090, CleanMenu3E10 rounds 9/16/17/22/28/34/35/37, Polish*): sweeps, permute 600 s+ (best 85 / 210), reconstructs (fdiff=1), and diagnoses on the old keys 659799/0a8f58/c145d3. Those diagnoses found that with D_800337DC[idx].r/.g/.b, idx<<2 goes to v1 instead of v0 and the base register changes from t5 to t3.
- 2026-11-15 HackmenuUpdateElementTargetAndColor2 opus-5-5:high: `(D_800337DC + idx)->r/g/b` scores full=0 and fdiff is OK. `D_800337DC[idx].r` and `(&D_800337DC[idx])->r` score full=22. A named `MenuUiRgba *color = &D_800337DC[idx]` scores 77; `= D_800337DC + idx` scores 8.
- same: with the pointer-add form and any subset of the four dead ifs removed, the score is 13-16. With all four removed, idx gets v1 instead of a1 (mfc1 at 0x9490 and 0x967c).
- same, with all four removed: the inner switch as an if/else chain scored 94. Putting the case-15 index in `slot` scored 17 and in `t` scored 21; putting the case 2/3/10 index in `slot` scored 13. Renaming idx everywhere to slot/t/offsetY/splineStep scored 17/64/20/78. Moving the idx declaration scored 16-49, respelling the angle arithmetic scored 16-58, and assigning idx after the inner switch scored 60. A variants scan found nothing better than 16. A deadsweep with one dead statement reached 10 at best.
- same: the permuter (base = all four removed, score 90; cancelled before 900 s at the lead's request) produced a zero whose only semantic change was `idx = (s32)target->spawnX >> 2;` before the menuEvaluateSelectorSpline call in case 6/7/18. Rewritten by hand: all 7 FAKEs are gone and fdiff is OK.

## Untried ideas
- `*(&D_80033804 + idx)` reads a scalar extern as an array. It is untagged. Retyping it as `extern s8 D_80033804[]` would edit file scope plus other functions' bodies (`D_80033804 = 1`, `s8 *p = &D_80033804`), so it was left alone.

## Evidence
- Target: idx is a1 in both arms (mfc1 a1 at 0x9490 and 0x967c), and nothing writes v1 in the case 2/3/10 code. In case 15: v0 = idx*4, v1 = &D_80033F68[idx] (0x968c), a0 = &D_80033F80[idx], a2 = &D_80033F98[idx], v0 = D_800337DC + idx<<2 (0x96dc), lbu 0/1/2(v0) at 0x96e8-0x96f8.
- uopt with all four dead ifs removed: idx is bit 239, adjsave 3.0. It ties the uixas 295/298/301 (all 3.0) and wins on candidate number, so it takes v1. Order F68 > idx >= F98 is impossible, because the F68 load..store range contains both F98 loads.
- Fixed body: idx is candidate 33 (its first appearance is now in case 6/7/18), adjsave 3.5, forbidden [v0 a0 a2 a3] by the menuEvaluateSelectorSpline call, and assigned uopt 4 = a1. The uixas then take v1/a0/a2 as in the target.
