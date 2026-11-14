# minecartUpdateObstacleType3 (minecart, src/minecart/25F0.c)
## Sites
minecart:800286EC:goto:u6bb91 goto: case 0 then-arm goto case_1 (KEPT, Q0591 shared tail)
## Attempts
2026-11-11 r11 CleanMinecart25F0 opus-5-5 (low): uopt_trace goto vs fall-through (LR127 &gCurrentActor to reg15), permute best=0 only via dummy goto, fall-through 4269 / inverted early return 5224
2026-11-14 HackminecartUpdateObstacleType3 opus-5-5:high: fall-through 163, early-return-first 214, route if-chain 178 (goto and fall), for(;;) re-dispatch 243, state re-test 16 (rejected steer)
## Untried ideas
none structured; the then-arm path has its own block (0x231c) ahead of the case-1 entry
## Evidence
0x2264 beq v1,at,0x2320 (case 1 dispatch); 0x2300 b 0x231c (then-arm, delay sb state++); 0x2308-0x2314 else arm; 0x231c lw s0,0(t0) (goto-only reload of gCurrentActor); 0x2320 case-1 body.
