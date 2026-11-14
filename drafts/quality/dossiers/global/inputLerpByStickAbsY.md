# inputLerpByStickAbsY (global, src/global/E4090.c)
## Sites
global:806E0454:other:816f04 other: re-read of stickAbsY after the zero test; gave the variable a second def so the u8-to-int widening became a separate v1 candidate (move v1,v0 in the bnez delay slot) (FIXED)
## Attempts
2026-11-09..13 CleanE4090 / ReReview / Rev16J / CleanGlobalE4090 (low, xhigh): plain/diagnose/permute nohit; diagnosis: without the re-read move v1,v0 hoists and the sub.s order swaps
2026-11-14 HackinputLerpByStickAbsX opus-5-5:high: field tested directly + local loaded inside (5), ?: clamp (3), s32 local (3), int copy local in/after the test (3), clamp to int 70 then convert (17), bare if (stickAbs) without the re-read (0, applied)
## Untried ideas
none (fixed)
## Evidence
One lbu of the field (0x105c in X); beqz v0 / slti at,v0,71 (delay); bnez at with move v1,v0 in the delay slot (0x106c); mtc1 v1,$f4 / cvt.s.w; sub.s f2 (0x109c) before sub.s f10 = to - from (0x10a0). uopt -zdbug:5: bare test uses uneq{253}{0} on the variable; the ucvt {504} widening is its own candidate (reg 2, v1).
