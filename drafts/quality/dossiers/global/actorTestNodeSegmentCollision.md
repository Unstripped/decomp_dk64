# actorTestNodeSegmentCollision (global, src/global/E4090.c)
## Sites
global:806E2B20:do-while0:e9a088 do-while0: `do { x = x1; y = y1; z = z1; } while (0);` ends the copy block, so uopt copy propagation cannot fold the copies into the lerp statements of the next block; x/y/z stay register candidates and take $f2/$f16/$f18 (x1 lwc1 $f2 at 0x3834, y1 lwc1 $f16 at 0x383c, z1 lwc1 $f18 at 0x3848; beqzl delay-slot reload of x1 into $f2 at 0x38b4). Without it (k4 form) x/y/z are folded to stores of uadd trees, the x1/y1/z1 loads are the candidates and colour $f0/$f2/$f16 (19 rows, 0x3834-0x3884 and 0x3890 add.d $f6).
global:806E2B20:dead-store:8abab6 dead-store (REMOVED 2026-11-16): `z = ((z2 - z1) * t) + z` inside the collisionTestSphere argument. Replaced by real per-axis statements `x = ((x2 - x1) * t) + x; y = ...; z = ...;` and `collisionTestSphere(x, y, z, ...)`: the pads pad1/pad2 became the real x/y locals (same 144-byte frame).
## Attempts
2026-11-09..15 CleanE4090/ReReview/Rev16F/Rev16J/Rev26A/CleanGlobalE4090/PolishglobalE4090 (see quality history): do-while removal, permuter (best=0 only via if (1) {}, dead if (hit) {}, duplicate assignment), bare {} block (21 rows), plain z = z1 (fdiff 21 rows), cond/copy sweeps.
2026-11-16 HackactorTestNodeSegmentCollision anthropic/claude-opus-5-5:high:
- natural bodies (one-statement lerps, args inline, z first, z +=, dz temp): 14-19 rows
- `x = x1; y = y1; z = z1;` in a do/while(0) block, then three lerp statements and a call on x, y, z -> fdiff 0 (KEPT; dead-store 8abab6 removed, 2 FAKE -> 1)
- same without the block (k4) -> 19; bare {} -> 19; switch(0) default -> 19; `goto lerp; lerp:` -> 0 (hack swap, not taken); if (1) {} -> 0 (hack swap)
- `+=` lerps inside the do/while(0) form -> 3; without the block -> 19; `x + (...)` order -> 19; `t * (x2 - x1)` -> 20
- loop shapes: while with t += at end -> 19; copies in preheader + latch -> 60; for-init/step comma copies -> 67; n-and-a-half while(TRUE) with break -> 57; guarded `if (t <= 1.0) do {} while` -> 24; `for (; t <= 1.0;)` + `if (hit) break` -> 35; `if (t > 0.0f)` lerp guard -> 67
- z = 0.0f before the loop / z = t = 0.0f / dead z use after loop (theory: z needs a second web) -> 14
- permuter 900 s -j 2 from the natural `z = ((z2 - z1) * t) + z1;` body (hack-free weights): base 722 best 115, only dead if (x2 && x2) {}, &y1 re-read, &x1 alias steers
## Untried ideas
- a vector struct or f32[3] local for the start point (frame must stay 144 bytes; an array would stay in memory, unlike the target x/y/z registers)
- an inline-expanded macro shared with a sibling segment test (search other files for the same 0.2 step loop)
## Evidence
- 0x3834-0x3848: lwc1 $f2,120(sp) [x1], $f6,124(sp) [x2], $f16,112(sp) [y1], $f4,116(sp) [y2], $f18,104(sp) [z1]; z2 at 108(sp) loaded late at 0x3870 into $f10
- 0x3880 add.s $f0 (z) -> mfc1 a2; x/y computed straight into $f12/$f14
- 0x38b0 beqzl v1 back to 0x3838 with x1 reload in the delay slot
- frame 144 bytes: 10 f32 locals + 2 s16 + u8 hit at sp+0x63
