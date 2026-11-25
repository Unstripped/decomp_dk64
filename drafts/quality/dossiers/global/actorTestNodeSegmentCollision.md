# actorTestNodeSegmentCollision (global, src/global/E4090_player_input.c)
## Sites
global:806E2B20:do-while0:e9a088 do-while0 (REMOVED 2026-11-25): `do { x = x1; y = y1; z = z1; } while (0);` ended the copy block so uopt copy propagation could not fold the copies into the lerps; x/y/z stayed candidates ($f2/$f16/$f18, x1 lwc1 $f2 at 0x3834, y1 lwc1 $f16 at 0x383c, z1 lwc1 $f18 at 0x3848). Replaced by per-axis endpoint arrays `f32 segX[2], segY[2], segZ[2]` (index 0 = node 4, index 1 = node 0xA) and textbook lerps `x = segX[0] + ((segX[1] - segX[0]) * t);`: fdiff 0, uninit 0, cfe warnings 0.
global:806E2B20:dead-store:8abab6 dead-store (REMOVED 2026-11-16): `z = ((z2 - z1) * t) + z` inside the collisionTestSphere argument, replaced by real per-axis statements on x/y/z.
## Attempts
2026-11-09..15 CleanE4090/ReReview/Rev16F/Rev16J/Rev26A/CleanGlobalE4090/PolishglobalE4090 (see quality history): do-while removal, permuter (best=0 only via if (1) {}, dead if (hit) {}, duplicate assignment), bare {} block (21 rows), plain z = z1 (fdiff 21 rows), cond/copy sweeps.
2026-11-16 HackactorTestNodeSegmentCollision anthropic/claude-opus-5-5:high: natural scalar bodies 14-19 rows; the do/while(0) copy block -> fdiff 0 (kept); loop shapes 19-67; permuter 900 s best 115 (dead-test/alias steers only).
2026-11-25 LeverScout26 (read-only scout): per-axis `f32 px[2], py[2], pz[2]` endpoint arrays with `x = px[0]; x = ((px[1] - px[0]) * t) + x;` -> fdiff 0 for the function and the file, uninit 0.
2026-11-25 continue CleaninputRemapButtons anthropic/claude-opus-5-5: scout patch applied with real names (segX/segY/segZ) -> fdiff 0; natural lerp spellings scored with variants.py try: `x = segX[0] + ((segX[1] - segX[0]) * t);` full=0 (KEPT, the in-place copy pair dropped), `x = ((segX[1] - segX[0]) * t) + segX[0];` full=3, `x = segX[0]; x += (segX[1] - segX[0]) * t;` full=3. Final copy fdiff 0, clint uninit 0, cwarn 0.
## Untried ideas
- none open: the function has no hack site left.
## Evidence
- endpoint homes per axis, 8-aligned pairs: segZ sp+104/108, segY sp+112/116, segX sp+120/124, written by the two actorGetNodePos calls (0x37a8-0x37f4)
- 0x3834-0x3848 reloads each iteration: lwc1 $f2,120(sp) [segX[0]], $f6,124(sp) [segX[1]], $f16,112(sp) [segY[0]], $f4,116(sp) [segY[1]], $f18,104(sp) [segZ[0]]; segZ[1] at 108(sp) loaded late at 0x3870 into $f10
- array elements are non-vreg (Q0562): never forwarded, so the endpoint loads stay per iteration like the target; the top-level `+` of an array-element expression compiles operands swapped (Q0562 (3), Q1454), so `segX[0] + (...)` gives the target's `(...) + x` order
- 0x3880 add.s $f0 (z) -> mfc1 a2; x/y computed straight into $f12/$f14
- 0x38b0 beqzl v1 back to 0x3838 with the segX[0] reload in the delay slot
- frame 144 bytes: x/y/z/t + three f32[2] + 2 s16 + u8 hit at sp+0x63
