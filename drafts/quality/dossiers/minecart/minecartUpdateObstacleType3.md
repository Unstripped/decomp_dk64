# minecartUpdateObstacleType3 (minecart, src/minecart/25F0.c)
## Sites
minecart:800286EC:goto:u6bb91 goto: case 0 then-arm `goto case_1` (KEPT, Q0591 shared tail / Q0613): the extra edge splits LR &gCurrentActor so it lives in t0 (0x2240) through dispatch and case 0 only; without it the address colours whole to a saved register (sw s1,0x30(sp); lw s0,0(s1) per use)
## Attempts
2026-11-11 r11 CleanMinecart25F0 opus-5-5 (low): uopt_trace goto vs fall-through (LR127 &gCurrentActor to reg15), permute best=0 only via dummy goto, fall-through 4269 / inverted early return 5224
2026-11-14 HackminecartUpdateObstacleType3 opus-5-5:high: fall-through 163, early-return-first 214, route if-chain 178 (goto and fall), for(;;) re-dispatch 243, state re-test 16 (rejected steer)
2026-11-15 HackminecartUpdateObstacleType32 opus-5-5:high: re-measured at 5c8c62b7: fall-through 163, else-first fall-through 214; case-1 body as a block after the switch (`case 1: break;`, then-arm `break`) 88, then-arm falling into `case 1: break;` 87: reload/colouring right (lw s0,0(t0) in the then-arm b delay slot), but case 2/default bodies precede the case-1 body, temps renumbered
## Untried ideas
none structured: every semantics-preserving form (goto, fall-through, tail after switch, loop re-dispatch, re-test) measured; layout needs the case-1 body between case 0 and case 2, and only the goto gives both that and the t0 split
## Evidence
0x2240-0x2248 lui/addiu t0 = &gCurrentActor, lw s0,0(t0); 0x2254 lbu v1,340(s0) single state load; 0x225c beqz v1,0x227c (case 0); 0x2264 beq v1,at,0x2320 (case 1 dispatch); 0x226c beq v1,at,0x2554 (case 2); 0x2284 beqzl t9,0x230c (else); 0x2300 b 0x231c (then-arm, delay sb t2,340(s0) = state++); 0x2308-0x2318 else arm (actorUpdateModelMatrix, b 0x2590); 0x231c lw s0,0(t0) (goto-only reload of gCurrentActor); 0x2320 case-1 body (lw v0,0(v0) gPrimaryPlayerActor hi from 0x2258)
