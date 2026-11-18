# mapBspPlaneDistanceCheck (global, src/global/2F550.c)
## Sites
global:8062EBB8:other:3a0961 other: byte-offset corner reads `*(f32 *)((u8 *)D_807F5E20 + i * 12)` (+4, +8) and the `< sViewPlane` loop bound. FIXED 2026-11-18: file-scope `extern f32 D_807F5E20[4][3];`, `D_807F5E20[i][k]` reads, `while (i < 4)`.
global:8062EBB8:dead-if:5d2f3f dead-if: `if (dot && dot) {}` after sqrtf. Needed only because the 4b7f43 guard adds a use of dx; with 4b7f43 removed it changes nothing (both removed 16 = dx guard removed 16; dot guard alone removed 35: dot (M-72) split, part $f24).
global:8062EBB8:dead-if:4b7f43 dead-if: `if (dx) {}` after dz. Class 1 block split (sweep says class 2: it only tries int locals): with BOTH guards removed one no-code split after dz or after d (`if (1) {}`, `if (0) {}`, `while (0) {}`, `switch (i) {}`) scores 3 = the reloc-only bound diff; a guard on any live local (dx, dy, dz, d, nx, x, dot) adds a use and needs the dot guard back (35-54).
## Attempts
2026-11-09 CleanD5E10 opus:low: both guards plus byte-offset removed: blocks 26/18, D_807F5E20[i * 3] addu order.
2026-11-10 Rev10E opus:xhigh: uopt_trace per site; permute best 30 (aliasing node local + if (!node)); reconstruct corner pointer walk 5211.
2026-11-11 Rev17N opus:low: D_807F5E20[i * 3 + k] 1 diff (sll/subu, i home store after sqrtf); permute 989.
2026-11-12 Rev20C/Rev26B opus:low: dx guard removed -> dx $f0, dy $f2; permute zeros only via empty do-while / goto-label split (steer swaps, Q0695).
2026-11-13 CleanGlobal55B20 opus:low: rc_dist_a (corner pointer loop) 32 bytes short; rc_dist_b (D_807F5E20[i * 3]) 33 lines; permute zeros steer swaps.
2026-11-18 2026-11-17f CleanmapBspPlaneSideTest opus: 3a0961 fixed (typed f32[4][3] corners + i < 4, RELOC-EQUIV); dead guards re-measured on the fixed body (see Sites); natural block-split candidates all 16: for (; i < 4; i++), while (i < 4), while (++i < 4), continue on !(d > 0.01 || d < -0.01), assignment in the test, nested t tests, per-iteration f32 *corner = D_807F5E20[i], fields read in the loop without nx/ny/nz locals (uopt hoists them; 3 with the guards kept), `;`/`{}`/`{;}` after dz; d <= 0.01 && d >= -0.01 forms 24 (c.le compares); permuter hack-free 900 s from the both-removed body (perm_dist_rm, base 75): zeros only re-insert a dead guard after dz/d (node, sViewPlane, D_807F5E20 operands) or alias d through f64 *new_var = &d: steer swaps.
## Untried ideas
A real construct in the original loop body that leaves a no-code uopt label between the dz load and the d test (debug print under a constant flag compiled to `if (0)`? not derivable from the asm) (this session).
A file-scope Vec3f D_807F5E20[4] spelling (same i*12 row; f32[4][3] chosen because frustumOrientPolyNormals takes f32 *) (this session).
## Evidence
Frame 0x88: f20-f30 saved 16..63, ra 68, i home 76 (`sw zero,76(sp)` 0x4394 before sqrtf, `lw t6,76(sp)` 0x43fc), pad[14] 80..135.
Corner address: `sll t7,t6,2; subu t7,t7,t6; sll t7,t7,2; addu v0,t7,t8` (0x4408-0x4424) = one i*12 (12-byte row) offset-first (Q0175).
Loop end: `lui/addiu v1 sViewPlane` (0x4414/0x4420) = D_807F5E20+0x30: IVE/LFTR of i < 4 (Q0741, Q0264).
Loop colours: d sum $f0, dx $f2, dy $f12, dz $f14, t $f2 (0x44ac-0x44f8); dot $f30; constants 0.01 $f24, -0.01 $f26, 1.0 $f28, 0.0 $f16.
uopt -l5 both guards removed: dx 63, dy 71, dz 77, d expression 89 all adjsave 40 -> candidate order gives dx $f0 (Q0900); with the dx guard: dx 30, dy/dz 20, d 40, t 30 -> d first.
