# seqUpdateVolumeFades (global, src/global/7130.c)
## Sites
global:8060A500:do-while0:e9a088 do-while0: FIXED (2026-11-17f CleansfxStartAreaAmbient). An empty `do {} while (0);` between `D_80770568[i] = curr + (target - curr) * 0.075;` and `curr = D_80770568[i];` split the block so the reload lwc1 $f0,0(v1) at 0x8158 stayed; without it uopt forwarded the stored cvt.s.d value into curr (text 8). Fixed by the compound store on the arrays with direct reads (no curr/target locals): the stored expression contains the ilod the swc1 kills, so it cannot be forwarded (Q1012).
## Attempts
2026-11-09..2026-11-13 (pilot, rounds 12/16/36): removal (reload becomes mov.s, .text -4), += and `curr = D_80770568[i] = ...` with the curr local (reload lost), permuter outputs = do {} while (0) / if (1) {} re-inserted -> nohit.
2026-11-18 2026-11-17: cleanup CleansfxStartAreaAmbient CleansfxStartAreaAmbient opus-5-5: on the carved body: removal 8; outer loop as pre-tested while 10, as do-while 10, `for (; i < 4; i++)` with an initialised i 10; `if (!D_80770598[i]) continue;` 8; ternary diff 8; target local read before curr 21; pointer local `f32 *vol = &D_80770568[i]` 19; scan of the removal copy (swap/width) no gain.
2026-11-18 CleansfxStartAreaAmbient: Q1012 compound store + direct reads: with a target local read first 13 (text 5: lui s2/s3 order and sub.s/cvt.d.s at 0x813c swap); `x = x + (t - x) * 0.075` with no locals 9; no curr/target locals, `D_80770568[i] += (D_80770578[i] - D_80770568[i]) * 0.075;` and direct reads in the compare/diff/clamp -> 0 (also 0 on the pre-carve body 08e85d18^) -> applied.
## Untried ideas
None (fixed).
## Evidence
Target 7130.o 0x80d0-0x81d8: s1/s2/s3 = &D_80770598/&D_80770568/&D_80770578 (lui 0x80f8/0x80fc/0x8100); per i: a0 = s1+i (flag), v1 = s2+i*4, t7 = s3+i*4; lwc1 $f0,0(v1) 0x8134, lwc1 $f2,0(t7) 0x8138, cvt.d.s $f4,$f0 0x813c before sub.s $f6,$f2,$f0 0x8140, mul.d by 0.075 ($f20), swc1 $f18,0(v1) 0x8154, reload lwc1 $f0,0(v1) 0x8158, c.lt.s $f0,$f2 0x815c, sub.s $f12,$f2,$f0 in both arms (0x8168/0x8170/0x8174), neg.s 0x8178, c.lt.d with 0.05 ($f22) 0x8180, swc1 $f2,0(v1) / sb zero,0(a0) 0x8190/0x8194, jal seqUpdateVolume 0x8198.
