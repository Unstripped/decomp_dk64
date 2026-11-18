# playerStateApproachVelocity (global, src/global/D5E10.c)
## Sites
global:806D4758:dead-if:fd202c dead-if: `if (mathAngleDistance(moveYaw, approachYaw)) {}` in case 0 is a class-1 block split: it ends the basic block at the jal mathAngleDistance (0x3698), so the gActivePlayerState value candidate {849|0} piece in that block stops at the call and $v0 is not forbidden ([3 4 5]); with the plain call statement the piece spans the call, $v0 is forbidden ([1 3 4 5]) and every gActivePlayerState access in cases 0/1 moves v0 -> v1 (26 lines, lui moves from the switch head 0x3660 into case 0).
## Attempts
2026-11-09..11-14 rounds 1-36 (CleanD5E10, CleanOrch, CleanGlobalD5E10, ReReview, Rev16F, Rev17M; opus-5-5 low/xhigh): remove/cond/classify (no local), plain call, (void) cast, s16/s32 result locals, uopt traces (forbidden [1 3 4 5] -> [3 4 5], Q0738), permuter runs: best=0 only with `if (1) {}` / `do {} while (0)` around the call or the approach statements (block-boundary steers, Q0720).
2026-11-17 cleanup CleanplayerStateApproachVelocity (CleanplayerStateApproachVelocity): hand class-1 classification: plain call + `if (1) {}`, + `if (gCurrentActor) {}`, + goto label all full=0; same-value `if (approachYaw) {}` 26, empty `;` 26, `(s32)`/`(u16)` cast statements 26, block-scope `s16 d = call;` 26. Natural shapes on the plain call: bare approachTimer test 26, `-= 1` 26, case-0 inner switch 26, if/else-if chain for the unk155 switch 48; variants scan (swap/float) 26. Hack-free permuter run 900 s from the plain-call body (base 624, best 0): every zero re-inserts an empty guard after the call (if (gCurrentActor) {}, if (gCurrentActor->speedXZ) {}, if (gCurrentActor->moveYaw) {}, if (gPlayerCharacterId) {}, && chains) -> nohit. Tag reworded to the block-split mechanism; `maxSpeed *= 0.63` in cases 0/1 (fdiff 0).
## Untried ideas
- A real construct that ends a uopt basic block right after a call statement without code (Q0698: an empty statement at the end of an arm; a two-case switch in actorCollisionProcessHit) has no plausible position here: the approach step after the call runs unconditionally.
- The sibling playerStateBackflip (same file, not this function) keeps the same tagged dead if in case 1 with the plain call in case 0 (Q0738 shows the opposite direction there): a shared helper/macro for the timed approach step does not change blocks.
## Evidence
- 0x3660: lui v0,%hi(gActivePlayerState) in the switch head (before beqz v1).
- 0x3684-0x369c: lw v0 gActivePlayerState; lh t6,0x3e(v0) approachTimer; lh a0,0xee(a2) moveYaw; jal mathAngleDistance; lh a1,0x40(v0) approachYaw.
- 0x36a0: lui v0 immediately after the call: the s16 result is never read (no ORIG: the target performs no test).
- 0x36a8-0x36b4: playerApproachVelocity(approachYaw, 50.0f in a1, targetSpeed lw 0x38).
- mathAngleDistance (CEAE0.c:752) returns s16, matching include/proto/global/CEAE0.h: no prototype item.
