# playerWeaponSpawnProjectile (global, src/global/F56F0.c)
## Sites
global:806F1EB0:dead-if:8a271c dead-if (FIXED 2026-11-17f): `if (k == 0) {}` after loop 1 in the `active == 0` arm. Class 1 block split (`if (1) {}` there matches). The 2 extra blocks raise index's (`*count`, sp-20 web) live-block count n 36 -> 38, so its divisor ((n-2)>>2)+2 goes 10 -> 11 and its adjsave (savings 203) drops 20.30 -> 18.45, below the 20.0 webs &angle1 (sp+196), &angle0 (sp+200) and const 8 (savings 100, n=15, divisor 5). Those then take s4/s5/s6 and index takes s7. Without the blocks, index takes s4 (`lw s4,0(a2)`, `sll t0,s4,3`).

## Attempts
2026-11-09 round 3 CleanF56F0 opus:low: remove/cond nohit, classify kept (class 1)
2026-11-10 round 6 ReReview opus:xhigh: diagnose nohit (removal: uopt colouring identical 31/31, full=10); permute best=0 only inserts do { } while (0)
2026-11-11 round 16 Rev16E opus:low: diagnose nohit (without the test the count load colours s4 instead of s7, same 255 insns); permute output-0-1 = do-while0 steer
2026-11-17 CleanplayerWeaponSpawnProjectile anthropic/claude-opus-5-5: positions of `if (1) {}` in the removal body: before loop 1, inside loop 1, after the holdTimer if, before `if (active == 0)`, at the else-arm start, after `index = *count`, before `*count = index` all give 0. Inside the holdTimer then-arm and after the trajectory25 call (end of the else arm) give 10. Loop 2 as `for (k = 0; k != 2; k++, cur++)` alone: index n=37 (still divisor 10), 10. Inner loop as `for (i = 0; i != 8; i++)` alone: 10. Both together, with the preheader join `slot = slots; slot += index; for (...)`: 0. Hoisting `slot = slots + index` / `&slots[index]` instead: 1 (addu s1,t0,s2 at 0x16a4). Separate preheader lines: 2-3. FIX: both loops as constant-trip `for` and `slots[index].f` written inside the inner loop (sibling style of playerWeaponAimTarget/playerWeaponInitCrosshair), with the slot local dropped. Final: index n=39, divisor 11, s7; webs n=17, divisor 5, s4-s6. fdiff 0. Both `// LAYOUT:` joins are gone. The unused slot declaration is still needed for the frame (33 diffs without it). It became the dedicated `f32 target` (anim weight target, which was `newvel` reused), fdiff 0.
2026-11-17 CleanplayerWeaponSpawnProjectile review: `y` (height, then |turn|) split, so pos[k][1] is read directly and the |turn| local is `turnSpeed`: 0. `s8 value` without the `(s8)` cast: 0 (sibling style). `(ret > 0)` order: 0. `ret = 0.0f`: 14 (Q1045 zero class, so `= 0` stays). `state[k]` in loop 1 instead of `cur[k]`: 8 (SR pointers v0/v1 swap at 0x1594-0x15b8). Moving `cur = state` to loop 2: 71. Dropping the `(s32)` rotY/rotZ casts: 73. Extra decl `f32 turn` at the end: 37 (frame).

## Untried ideas
none open: the site is fixed and the body has no other hack sites

## Evidence
0x1510 lw s7,0(a2): index lives in s7 for the whole function; 0x1800 addiu s7,s7,1 in the inner loop; 0x186c sw s7,0(t1)
0x1524 sw s0,148(sp): state is stored to cur's home sp+148 before the trajectory26 call (cur = state at the top is a separate variable); 0x184c-0x185c lw/addiu 316/sw cur at sp+148 per outer iteration
0x15a4-0x15b8: loop 1 is LFTR'd (pos walk v0 += 12 until sp+188, chain walk v1 += 316), and k is not read after it
0x169c sll t0,s7,3 / 0x16a4 addu s1,s2,t0: strength-reduced slots[index] pointer with base first (Q0667)
0x16ac sw zero,204(sp) / 0x1848-0x1864: the outer counter k lives in memory at sp+204
0x16b0-0x16b8 li s6,8 / addiu s5,sp,196 / addiu s4,sp,200: hoisted webs in the outer-loop preheader
