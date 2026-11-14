# behaviourFairyInitPlayerScale (global, src/global/BDEE0.c)
## Sites
global:806BB400:goto:ud4ecc `default: gCurrentActor->unk155 = 1; goto join; join: case 1:` in the 0x23 state's unk155 switch: kept (Q0591 shared tail, Q0160).
## Attempts
2026-11-11 round 11 CleanGlobalBDEE0: goto-hand kept (Q0591), permute zero only with `if (0) {}`.
2026-11-14 HackbehaviourFairyInitPlayerScale opus:high: plain fallthrough in four arm orders: default directly before case 1 after case 0 (1 region / 45 lines: orphan sb at 0x238c, +4 shift), case 0/case 2/default/case 1 (same), default + case 1 first (21), case 1 first and default last with a fallthrough comment (27).
## Untried ideas
none: the target's default block ends in a jump to a reload-then-case-1 tail, which only a goto (or an equivalent jump) produces.
## Evidence
0x2340 lbu v0,341(s0); beqzl -> case 0 (0x236c); beq v0,1 -> 0x2390; beq v0,2 -> 0x23f8; li t2,1; b 0x238c; sb t2,341(s0) (delay). 0x238c lw s0,0(s1) (default path only), 0x2390 case 1 head (lw t3,4(s0)).
