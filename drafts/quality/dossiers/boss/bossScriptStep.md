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
## Untried ideas
none that can keep the layout: the target places the tail once at the 0x42 source slot and 4 separate arms later each branch back to it
## Evidence
0x59c-0x60c: case 0x42 tail, lw gBehaviourWorkState, li a0,0x42, actorMoveWithinZone jal 0x5d8, patrolPathStep jal 0x5f0 (a0 = lbu 340(gCurrentActor)), bnez v0 -> 0xbd0 / move t1,zero
0x970-0x99c 0x67: bossPickRandomWaypoint; li 0x42; move t1,zero; sb 340; b 0x59c; sb zero,341 (delay)
0x9a0-0x9cc 0x4C: bossPickFarthestWaypoint; same stores; b 0x59c
0x9d0-0xa40 0x4B: waypointIndex++ (lbu/sb 37(v1)), compare script[pos+1]; scriptPos+=2; same stores; b 0x59c
0xa44-0xa88 0x41: waypointIndex=script[pos]; scriptPos++; same stores; b 0x59c
Case blocks are in source order (0x42 between 0x5A and 0x69); arms not adjacent to 0x42 -> Q0591 shared tail
```
