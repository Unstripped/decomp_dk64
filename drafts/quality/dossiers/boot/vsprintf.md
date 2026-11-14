# vsprintf (boot, src/boot/3D20.c)
## Sites
boot:8000320C:dead-if:2829ec (295) zero-pad loop `if (width == 0) {}`: second loop block keeps the '0' constant uncoloured (li t7,48 per iteration at 0x88c); removed, li v0,48 is hoisted and the ring shifts (59).
boot:8000320C:dead-if:u8169d (412) `if (space && space) {}` in the exp-sign else: leaves an ugen sne record at the else head so the exp/10, exp%10 PRE insertion precedes the '+' store (li t9,43 / mfhi t7 at 0xccc/0xcd8); removed, t7/t9 swap (4).
boot:8000320C:dead-if:e415e5 / other:69d5aa / dead-if:7dcd26 (373-379) coupled e-arm zero-pad steer.
boot:8000320C:dead-if:7dcd26#2 (418), noop-arith:9bc6c1 (101), gotos u01010/u01010#2/u860d7/u860d7#2: unchanged (EXHAUSTED; gotos Q0591).
## Attempts
2026-11-12 round 27 CleanBoot3D20 opus:medium: all sweep rungs, diagnoses, permutes, reconstruct, goto-hand kept.
2026-11-14 Hackvsprintf opus:high: 2829ec loop shapes (59-66; trailing continue 0 = steer); u8169d count/arm/ternary/switch/bound forms (4-108), as1probe ugen stream diff; e-arm coupled rewrites (154-392).
## Untried ideas
A real second statement in the zero-pad loop body (none exists in the target).
## Evidence
0x88c li t7,48 / sb t7 in the zero-pad loop; 0xcc4-0xcf0 else-arm: div exp/10, li t9,43, sb, div, mfhi t7.
