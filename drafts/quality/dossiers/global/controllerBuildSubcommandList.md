# controllerBuildSubcommandList (global, src/global/17B90.c)
## Sites
global:8061324C:dead-if:b57e8a dead-if: made `cmd0 >> 24` a cross-block CSE candidate coloured v0 (op), so the word took v1 at 0x400 (FIXED)
global:8061324C:dead-if:efb90c dead-if: made `(cmd0 >> 16) & 0xFF` a cross-block candidate so `srl a0,v1,0x10` sits before `bne v0,s6` at 0x408 (FIXED)
global:8061324C:dead-if:a6e6f0 dead-if: extended op's range past the id sll/srl (0x428/0x430) so op outranks the word (v0 vs v1) (FIXED)
## Attempts
2026-11-11 r12 CleanGlobal17B90 opus-5-5:low: trace, permuter (do-while(0) wraps), for-loop reconstruct -> 1065
2026-11-11 r16 Rev16E opus-5-5:low: nested do-while reconstruct 285; permuter best reuses cmd0 = 4 as shift count
2026-11-12 r23 Rev23A opus-5-5:low: if (sub) {} removal alone (score 120); for-loop reconstruct 1065
2026-11-14 HackcontrollerBuildSubcommandList opus-5-5:high: GBI spellings (`(x >> 24) & 0xFF`, u8 casts, byte reads, `(cmd0 >> 16) == 0xDE01`), s32/u8 op/sub, switch forms, continue form, hi-halfword local, index inner loop (Q0489), cmd0/op reuse with a cmd0 word -> full 15..40 (variants.py units); op/sub assigned straight from `curr->unk0` (Q0510 has_ilod) -> 5 (only v0/v1 swapped); plus op reused as the inner opcode `op = search->unk0 >> 24` -> 0. Applied as for + while loops, fdiff 0.
## Untried ideas
none (fixed)
## Evidence
0x400 lw v1,0(s3); 0x404 srl v0,v1,0x18 (op); 0x408 srl a0,v1,0x10; 0x40c bne v0,s6; 0x410 andi t6,a0,0xff (delay slot); 0x41c lw s1,4(s3); 0x428/0x430 sll t7,s1,4 / srl s1,t7,0x1c (SEGMENT_NUMBER id); inner 0x434 lw v0,0(s0) shares op's v0; found flag v1 (0x424 move v1,zero, 0x454 li v1,1).
uopt -zdbug:5 without reuse (op/sub from curr->unk0): lw CSE {1181} adjsave 30 coloured first (v0), op var adjsave 20 -> v1. With op reused in the inner loop op outranks it.
