# seqLoadAndPlay (global, src/global/7130.c)
## Sites
global:8060A1B0:other:93926d `tries = (s32)heapAlloc(0x8000);` (retry counter reused as the buffer): REMOVED. The buffer is a separate `void *buf`; the block computes `addr = D_8076D200[seqId] + D_8000DDCC` and `len = D_8076D200[seqId + 1] - D_8076D200[seqId]` without a `base` local, which keeps the declared-local count and so the seqIndex*4 spill temp at sp+0x44 (Q0331).
## Attempts
2026-11-09 pilot / rounds 12, 13, 16, 17 (opus): separate buf at function or block scope, declared first or later (home 0x40), permutes (no zero in 606 s).
2026-11-14 HackseqLoadAndPlay opus:high: block-scoped tries + function-scope buf (6), buf = NULL first/second (6), u8 *buf (6), addr folded instead of base (28), base folded (0).
## Untried ideas
none.
## Evidence
0x7dbc sw v0,68(sp) (seqIndex << 2 spill), 0x7eb4 move s0,v0 (heapAlloc result), 0x7eb8/0x7ec8 sw a1,72(sp) (len), 0x7ee8 addiu a2,sp,72 (&len), 0x7ef8 sw s0,24(sp) (buf argument).
