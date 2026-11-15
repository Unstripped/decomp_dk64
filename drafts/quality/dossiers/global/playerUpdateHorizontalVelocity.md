# playerUpdateHorizontalVelocity (global, src/global/CEAE0.c)
## Sites
global:806CCC54:other:b36919 other: `lateral = mathAtan2(vx, vz)` reused the f32 lateral (home 72) for the heading so no 9th named local word grows the 0x50 frame. FIXED: `ang = (mathAtan2(vx, vz) * 4096.0) / 6.2831855f; ... moveYaw = ang;`
global:806CCC54:other:f73438 other: `forward = mathSinF(ang) * speed` in the default arm stores to forward home 76(sp). ORIG (slot evidence below).
## Attempts
2026-11-14 PolishglobalCEAE0 opus-5-5:high: separate f32 heading local -> frame 0x58 (fdiff 1); vx = sin*speed + sin*slope, vx = sin*speed; vx += sin*slope -> fail
2026-11-14 U HackplayerUpdateHorizontalVelocity anthropic/claude-opus-5-5:high: b36919 block-scoped `{ f32 heading }` -> full=80 (frame 0x58); function-scope heading -> full=80; heading as the s16 ang (`ang = (s32)(atan2*4096.0/2pi)`, `moveYaw = ang`) -> full=0, fdiff 0 (FIXED)
2026-11-14 U HackplayerUpdateHorizontalVelocity anthropic/claude-opus-5-5:high: f73438 vx = sin*speed + sin*slope -> full=249; vx = sin*speed; vx += sin*slope -> full=158; new f32 local t / block-scoped t -> full=123, frame 0x58; forward + X, X + forward, forward + slope*f, (X) parenthesised, vx = X; vx = vx + forward -> full=1 per axis (add.s operand order $f10,$f14 vs target $f14,$f10 at 0x3550); forward += X; vx = forward -> full=22; only `vx = X; vx = forward + vx;` gives the target order. Converted to ORIG.
2026-11-14 U review: (s16)(s32) on the mathSinF arg, (s32) on both atan2 conversions, inner `return;` after playerApplyDeceleration and the case `return;` (-> break) all removed, fdiff 0; local m -> yawDiff.
## Untried ideas
none for the sites (both closed). Names: D_807FD586 (flag cleared by both arms, gates the moveYaw snap in default) and PlayerState.unkC2 need cross-file evidence.
## Evidence
- frame 0x50; named homes 76 forward, 72 lateral, 68 vx, 64 vz, 60 speed, 56 slope, 54 ang, 52 m (register-only), 48 tracker; compiler spill 24(sp) (m in v1, 0x30f0/0x3144).
- 0x3108 swc1 $f14,76(sp): case-arm stick forward spilled to its home across mathSinF.
- 0x3530 swc1 $f14,76(sp) / 0x3538 reload: default-arm sin(ang)*speed in the same home; 0x3574 same for cos(ang)*speed.
- 0x3550 add.s $f18,$f14,$f10: forward operand first (matches `vx = forward + vx`).
- 0x3384 jal mathAtan2, result in $f0 never stored; 0x338c lbu apply 83(sp), 0x3398 beqzl; conversion 0x33a8-0x33d8 and sh moveYaw 0x33e0 inside the apply arm (uopt sinks the s16 ang assignment, Q0324).
