# particleFindPathIndices (global, src/global/699B0.c)
## Sites
global:80664CB0:other:3dca20 other: `limit = 13;` bound local. It keeps the trip count non-constant during uopt loop analysis (vreg {1008}, loop test `ules i, limit`), so the scan is not unrolled. The bound is then materialised as `li v0,13` (0x1c) and compared with `slt at,v1,v0` (0x5c).
## Attempts
2026-11-14 cleanup PolishGlobal699B0 opus:high: literal 13 bound -> peels iteration 0 and unrolls (fdiff 1); indexing D_80748BA0[i].level -> fdiff 1 (plain nohit, recipe nohit)
2026-11-14 U HackparticleFindPathIndices opus: diagnose. Scores are variants.py try full=:
  - literal bound written as for, while, do-while, `i <= 12`, `i != 13` and `(u32)i < 13`: all full=75 (unrolled, 70 insns)
  - `for (;;)` with `if (i >= 13) break`: full=25 (no unroll, but `bne v0,t1` instead of `slt`)
  - `ptr < &D_80748BA0[13]`: full=25 (`sltu` against an end pointer, D_80748BA0+0x1a0 in t1)
  - `extern D_80748BA0[13]` with a `(s32)(sizeof/sizeof)` bound: folded to the literal (70 insns, fdiff 1)
  - `D_807F9448 != 8` compared first, literal bound: 68 insns, fdiff 1
  - variants scan: 15 one-edit variants; the 6 zeros all keep `limit`
## Untried ideas
- none natural left. A count global is ruled out because the target uses `li` with no load. sizeof is folded by cfe. Every literal spelling either unrolls or gets the `<`->`!=` / LFTR end-pointer test (Q0257, Q0582, Q0607).
- The permuter (optional): it can only find another bound-variable spelling.
## Evidence
0x1c `li v0,13` (hoisted before the loop); 0x2c `move v1,zero` (i); 0x30 `li t0,8`; loop 0x34-0x64: `lbu t8,0(a1)` / `bnel a0,t8` / `lw a2,0(a3)` (D_807F9448 re-read each pass) / `beq t0,a2` / `sb v1,0(t9)` / `sw t2,0(a3)`; 0x5c `slt at,v1,v0`; 0x60 `bnez at,0x34`; 0x64 `addiu a1,a1,0x20` in the delay slot; 28 instructions, no entry guard.
uopt trace (copy): `ustr {1008} 13` ... `ules {880} {1008}`.
Same pattern as the tagged bound locals in 135D30.c (Q0263, Q0582).
