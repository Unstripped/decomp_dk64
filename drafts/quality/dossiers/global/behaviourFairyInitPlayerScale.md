# behaviourFairyInitPlayerScale (global, src/global/BDEE0.c)
## Sites
global:806BB400:goto:ud4ecc `default: gCurrentActor->unk155 = 1; goto join; join: case 1:` in the 0x23 state's unk155 switch: kept (Q0591 shared tail, Q0160), re-verified at base 5c8c62b7.
## Attempts
2026-11-11 round 11 CleanGlobalBDEE0: goto-hand kept (Q0591), permute zero only with `if (0) {}`.
2026-11-14 HackbehaviourFairyInitPlayerScale opus:high: plain fallthrough in four arm orders: default directly before case 1 after case 0 (1 region / 45 lines: orphan sb at 0x238c, +4 shift), case 0/case 2/default/case 1 (same), default + case 1 first (21), case 1 first and default last with a fallthrough comment (27).
2026-11-15 HackbehaviourFairyInitPlayerScale2 opus:high: goto-hand kept Q0591. variants.py try (full=): plain fallthrough c0/default/c1/c2 and c2/c0/default/c1 1 (re-measured); source-order if-chain with a reload per compare 13; if-chain `==0` then `==1 || !=2` 16; nested `==0 {A; break}` / `!=1 { ==2 break; store }` / B 13; flag local set in arms, tail tested once after the switch 15 (store+flag+break in default 16); `for (;;) switch` with `default: store; continue;` 20 (default first 20); sentinel `default:` arm holding `if (!=1) store` + case-1 body 18; `case 1: default:` shared arm 10; `default: if (==2) break; store;` falling into case 1 12; `default: if (!=1) store;` falling into case 1 12.
## Untried ideas
none: the target's default block (store) ends in a forward jump over case 0 into a reload-only block that falls into case 1; plain fallthrough keeps the store in its own block at 0x238c, and every structured form tried moves bodies or compares.
## Evidence
0x2340 lbu v0,341(s0); beqzl -> case 0 (0x236c); beq v0,1 -> 0x2390; beq v0,2 -> 0x23f8; li t2,1; b 0x238c; sb t2,341(s0) (delay). 0x238c lw s0,0(s1) (default path only), 0x2390 case 1 head (lw t3,4(s0)). Plain fallthrough: same chain but `b 0x2390` with sb copied into the delay slot and the original sb left at 0x238c (+4 from there on).
