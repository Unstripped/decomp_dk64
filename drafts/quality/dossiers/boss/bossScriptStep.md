```
# bossScriptStep (boss, src/boss/3840.c)
## Sites
boss:80027BA8:goto:u2634e   goto  case 0x67 arm -> patrol (target b 0x59c at 0x998)
boss:80027BA8:goto:u2634e#2 goto  case 0x4C arm -> patrol (target b 0x59c at 0x9c8)
boss:80027BA8:goto:u2634e#3 goto  case 0x4B arm -> patrol (target b 0x59c at 0xa3c)
boss:80027BA8:goto:u2634e#4 goto  case 0x41 arm -> patrol (target b 0x59c at 0xa84)
## Attempts
2026-11-09 CleanBoss / 2026-11-10 QualityTools / 2026-11-12 Rev24: copy case 0x42 tail into the four arms -> .text 6768->7104 (+336), fdiff 1
2026-11-14 HackbossScriptStep opus-5-5:high: for(;;){switch} with `continue` after state=0x42 (re-dispatch via jump table) -> variants full=574 text=762
2026-11-14 HackbossScriptStep opus-5-5:high: u8 patrolNow flag, case 0x42 and the 4 arms set it, tail after the switch -> full=500 text=418
2026-11-14 HackbossScriptStep opus-5-5:high: 4 arms grouped `case 0x67: case 0x4C: case 0x4B: case 0x41:` nested switch + common state/unk155 stores, fallthrough into case 0x42 -> full=594 text=522
2026-11-16 HackbossScriptStep2 opus-5-5:high: Duff loop: `case 0x42: for (;;) { <tail>; break; case 0x69: ... case 0x41: ...; continue; } break;` (for/while(1)/do-while(1), last arm falling off the end too) -> full=10 text=8; loop closing after `default:` -> full=9 text=7. Arms/tail layout match (b 0x59c at 0x998/0x9c8/0xa3c/0xa84); the only miss is case 0x4B 0x9d0: target `lui a1; addiu a1` + `lw v1,0(a1)` x2, Duff gives `lui v1; lw v1,%lo(v1)` (one instruction short)
2026-11-16 HackbossScriptStep2: variants scan on the Duff body (31 swap/width/declswap) -> best full=9; permuter 900s on it (hack-free weights, base 467) -> best 200 = dead `if (!gBehaviourWorkState) {}` in case 0x4C + `5 * (6 * x)`, no natural hint
2026-11-17 HackbossScriptStep3 opus-5-5:high: tail after the switch behind `if (BOSS_ACTOR->base.state == 0x42)` (no flag local; case 0x42 and the arms `break`) -> full=485 text=497. All 30 case exits branch to the `li at,66; bne` test at 0xc34; arms b 0xc34 at 0x9cc/0xa04/0xa80/0xacc; tail at 0xc40-0xca8
2026-11-17 HackbossScriptStep3: `u8 op` selector, `for (;;) { switch (op) { ... arm: state = op = 0x42; continue; } break; }` (does uopt thread a known selector?) -> full=577 text=569. No: arms set s0=66 and b 0x3c8 (slti/jr dispatch) at 0x904/0x938/0x9a0/0x9dc; the loop moves op/script/advanceScript/&gCurrentActor into s0-s4, frame 56->72
2026-11-17 HackbossScriptStep3 (reconstruct): two-switch dispatch, a pre-switch holding the 4 waypoint arms, then the main switch -> full=677 text=629. The 4-case pre-switch becomes a beq chain at 0x3b0-0x4e8, arms b 0x540 into the main dispatch, jr moves 0x3d0 -> 0x564
## Untried ideas
none. In emission order the arm blocks (0x970-0xa88) come after the tail (0x59c), so the target `b 0x59c` is a backward jump. Only a goto or a loop headed at 0x59c gives that. A loop headed at 0x59c inside the switch is the Duff loop (Q0953 class, a hack even at full=0). A loop around the switch re-dispatches through the jump table (574/577). Code after the switch lands at the end (485/500). Sibling bossMadJackStep (52B0.c u2103c) keeps the same case-to-shared-tail goto, so this is the overlay authors' style
## Evidence
0x59c-0x60c: case 0x42 tail, lw gBehaviourWorkState, li a0,0x42, actorMoveWithinZone jal 0x5d8, patrolPathStep jal 0x5f0 (a0 = lbu 340(gCurrentActor)), bnez v0 -> 0xbd0 / move t1,zero
0x970-0x99c 0x67: bossPickRandomWaypoint; li 0x42; move t1,zero; sb 340; b 0x59c; sb zero,341 (delay)
0x9a0-0x9cc 0x4C: bossPickFarthestWaypoint; same stores; b 0x59c
0x9d0-0xa40 0x4B: waypointIndex++ (lbu/sb 37(v1)), compare script[pos+1]; scriptPos+=2; same stores; b 0x59c
0xa44-0xa88 0x41: waypointIndex=script[pos]; scriptPos++; same stores; b 0x59c
Case blocks are in source order (0x42 between 0x5A and 0x69); arms not adjacent to 0x42 -> Q0591 shared tail
uopt (-zdbug:6): &gBehaviourWorkState is LR 201, split into 8 pieces; at base the 0x4B piece (222) is assigned reg 4 (a1) and the 0x41 piece reg 9 (t2). In the Duff loop the param LR 77 (turnSpeed) and LR 10 (advanceScript) are split before 201 (loop-depth weight raises their priority) and the 0x4B piece becomes `not colored (-ve save)`
```
