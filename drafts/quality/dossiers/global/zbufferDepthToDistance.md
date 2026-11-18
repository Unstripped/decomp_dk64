# zbufferDepthToDistance (global, src/global/103AB0.c)
## Sites
global:807009F4:other:c99c9b other: `mid = -1;` between `lo = 0` and `hi = 0x1FE`, read by `if (depth == mid)`: makes mid (M -6) uopt candidate bit 3, ahead of hi (M -4, bit 6), so colouring gives lo=v0 mid=v1 hi=a1 (plain: hi bit 3 -> v1, mid bit 13 -> a1; 15 lines). OPEN (kept FAKE).
## Attempts
2026-11-09..2026-11-13 (rounds 3, 10, 16, 17, 20, 26, 34, 36): plain literal -1 (15 reg diffs); mid = depth reuse; permuter from the plain early-return body (several 600-900 s runs): every zero re-inserts the preassign, a dead `mid = (lo + hi) / 2` before hi is set (uninit hi), `mid = 1; depth == -mid`, or `lo = mid` (Q0706); uopt_trace base vs removal (candidate 3 vs 6).
2026-11-17 2026-11-17: cleanup CleanzbufferReadDepth CleanzbufferReadDepth anthropic/claude-opus-5-5: 336 variants (s16/s32 per lo/hi/mid, 3 declaration orders, guard before/after the inits, do/while/for(;;)/for-init, >= vs <=) best 15; guard spellings 15-37; block-scoped mid 15; table pointer local at 5 positions 21-30 (between lo and hi: hi -> a1 as in the target, but the pointer holds v1 across the loop and mid -> a2); early-return result variable 15-40; single-exit `dist = 0` default 8 (exact loop colours; -1 path and tail differ); permuter 900 s from the single-exit base 876 -> 490, no zero.
## Untried ideas
A pre-loop variable that first appears between `lo = 0` and `hi = 0x1FE`, is dead across the loop (so mid can share v1) and still allows the -1 path's own `jr ra`: only constant-valued locals found so far (steers). (CleanzbufferReadDepth diagnosis)
## Evidence
Target 0x1c44-0x1c70: sw a0,0(sp); sll/sra a0 (s16 param); li at,-1; move v0,zero (lo); bne a0,at,0x1c68; li a1,510 (hi, delay slot); jr ra; move v0,zero; lui/lw a3 = D_8076A0A0 (hoisted); addu a2,v0,a1.
Loop: mid in v1 (sll v1,t8,16; sra t9,v1,16; move v1,t9 at 0x1c98-0x1ca8), hi = mid - 1 in a1 (0x1cac), lo = mid + 1 in v0 (0x1cbc), found: addiu v0,v1,8 + jr ra (0x1cf0). Tail 0x1d0c: addiu v0,a0,-31771 (dist in v0); ternary temp in v1; sll/sra to s16.
The -1 is never stored to mid's register: the preassign is a dead store, so it cannot become `// ORIG`.
D_8076A0A0 is `s16 *` defined in src/global/450.c (assetLoad(0x13, ...)), not an array.
