# meshComputeVertexRanges (global, src/global/10E1D0.c)
## Sites
global:80709ACC:dead-store:3cbe71 dead-store: min = 0 at entry gave min the first candidate bit (v0) (FIXED)
global:80709ACC:dead-store:1565d1 dead-store: pre-loop v2 = e->v2 gave the vertex local its bit ahead of max (a2 vs a3) (FIXED)
global:80709ACC:other:9a6177 other: byte offset off + per-column (MeshCell *)((u8 *)cells + off) (FIXED: cell index form)
## Attempts
2026-11-11 r11 CleanGlobal10E1D0 opus-5-5:low: remove/cond/diagnose/permute (best only dead re-spellings)
2026-11-11 r17 CleanGlobal2DE90 / Rev17L opus-5-5:low: diagnose 1565d1 (v2 bit ahead of max), permute (dead re-spellings)
2026-11-14 PolishGlobal10E1D0Views opus-5-5:high: views unified; e = &cells[off] + e++ and single walker fdiff 1; tagged 9a6177
2026-11-14 HackmeshComputeVertexRanges opus-5-5:high: one vertex local v with the pointer form -> 26-39 (register permutation); cell index form j1 -> shape 0, 45; min/max init forms: min = max = x 45, max = min = x 44, v = x; min = v; max = v 22, min = x; max = x -> 0. Applied, fdiff 0.
## Untried ideas
none (fixed)
## Evidence
0x600 move v1,zero (cell offset), 0x620 addu a1,t7,v1 (column cell pointer), 0x624 lw a3,0(a1) (max), 0x62c move v0,a3 (min), 0x630/0x660/0x688 lw a2,0/4/8(a1) (one vertex register), 0x638 addiu v1,v1,28, 0x6b8 addiu a1,a1,28.
uopt -zdbug:5 (base copy): candidates coloured in bit order, lowest free register: min {1264} -> 1 (v0), off {1200} -> 2 (v1), e {1392} -> 4 (a1), v2 {1328} -> 5 (a2), max {1136} -> 6 (a3).
