# frustumOrientPolyNormals (global, src/global/2F550.c)
## Sites
global:8062AD28:dead-if:649e56 dead-if (REMOVED 2026-11-16): dead duplicate `if (poly->d + (sum) < (0, 0.0)) {}` gave the plane-distance expression a second use, so uopt CSE'd it as candidate 154 coloured $f0 (add.d $f0,$f6,$f10 at 0x8e8) with an 8-byte home (frame 0x90) and kept tree order d + ((a*x + b*y) + c*z), which fixes the LFTR pointer order s2=xs(sp+0x78) s3=ys(sp+0x64) s1=zs(sp+0x50), loop end s4=sp+0x64.
## Attempts
2026-11-09 CleanD5E10 opus:low: guard removed -> frame 0x90->0x88, 9 colouring lines differ
2026-11-10 CleanGlobal55B20 opus:low: classify/cond/remove nohit; permute best 10
2026-11-11 Rev17N opus:low: removal -> frame 144 vs 136; permute best 10
2026-11-13 CleanGlobal55B20 opus:low: permute best output-105-1 (0.0 as a double local); comma removed from real compare
2026-11-13 CleanGlobal103AB0 opus:xhigh: uopt_trace: removal reassociates the sum to ((c*z + (a*x+b*y)) + d), no candidate
2026-11-16 HackfrustumOrientPolyNormals anthropic/claude-opus-5-5:high: ~70 bodies via variants.py try:
  - plain removal: full 32; f64 d local at decl positions 0..5: best position 4 (after zs) full 13, frame back to 0x90
  - poly->d spellings (d + S, S + d, regroupings, product swaps): full 11-55 (uopt commutes to (cz + ab) + d / x*a products)
  - d = poly->d; d += S: full 3 (d is an isvar coloured $f0 from the ldc1, load scheduled first)
  - planes[i] / poly = &planes[i] loops: full 99-118 (index-reduced pointer, extra $s regs)
  - S + poly[0].d or S + (*poly).d with d local at position 4: full 0
  - FIX: file macro PLANE_DIST(plane,x,y,z) ((((plane).a*(x) + (plane).b*(y)) + (plane).c*(z)) + (plane).d), d = PLANE_DIST(*poly, xs[i], ys[i], zs[i]); same macro for mapBspBoxInFrustum's two sums (planes[i], identical expansion) -> fdiff 0
## Untried ideas
none open: site fixed. Header request: move PLANE_DIST beside PlanePoly in include/render.h and use it in 55B20.c:2489 (gFrustumPlanes[planeIdx] sum, same expansion).
## Evidence
0x8a4-0x91c loop: s0 poly (+64), s2 xs, s3 ys, s1 zs (+4 each), bne s1,s4; d loaded ldc1 $f6,56(s0) after the c*z cvt; add.d $f0,$f6,$f10; c.lt.d $f0,$f20 with $f20 = mtc1 zero hoisted (0x898). Frame 0x90: f20 at 0x18, s0-s4 0x20-0x30, ra 0x34, zs 0x50, ys 0x64, xs 0x78.
