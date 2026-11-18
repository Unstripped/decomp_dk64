# modelSlotUpdateFacingTrigger (global, src/global/70FD0.c)
## Sites
global:8066FE08:dead-store:414c65 dead-store (case 1, `yaw = 0;` after `angle = ...`): kills copy propagation of angle's rhs cvt.s.d(mpy(div(cvt(yaw), 4095.0), 2pi)) into the sinApprox/cosApprox args, so angle (M-308) stays a candidate and is spilled to its own home sp+0x44 across the sinApprox jal (swc1/lwc1 $f12 at 0x3cb4/0x3cbc); without it the value goes to the temp slot sp+0x3c. Only remaining site.
Removed 2026-11-17e (actorYaw local dropped, gCurrentActor->yaw read inline): other:e9755c (case-1 `yaw = (1 | inArc) ? yaw : yaw + 1`), dead-if:0b27f0 / 0b27f0#2 (`if (yawDiff) {}` per case), dead-store:414c65#2 (case-2 `yaw = 0`). Earlier keys of the same steers: other:c71681, dead-if:f836b3(#2), dead-store:0cacc2(#2); other:50f97e (kind guard) fixed 2026-11-11 as `case 0: break;`.
## Attempts
2026-11-10 r2 Clean70FD0 opus-5-5:low: permute/reconstruct with all five removed (ABS/ternary +48 bytes) -> nohit
2026-11-10 r6 ReReview opus-5-5:xhigh: natural rewrite without redefinition/dead tests/dead stores full=66 -> nohit
2026-11-11 r10 Rev10F opus-5-5:xhigh: early-return guard + switch reconstruct fdiff=1 (70 rows); trace_var diagnoses; permute 696 -> nohit; sp144 -> f32 yOffset retype fixed
2026-11-11 r11 Rev11D opus-5-5:low: kind guard -> case 0 fixed; cases 1/2 merged around one yaw block 12620 -> nohit
2026-11-11/12 opus-5-5:low: s32 yawDiff 42 rows; permute 266 -> 206; FAKE-free 391 -> 791; ABS of the s16 difference 5190 -> nohit
2026-11-13 r34/r35/r37 opus-5-5:low/xhigh: uopt_trace colouring (yaw reg2 $v1, yawDiff reg3 $a0, actorYaw reg4 $a1, arcMax reg5 $a2, arcMin reg1 $v0); permutes (best=0 outputs only re-insert dead tests / if (1) blocks); reconstruct t_fe_r0..r6 (42-167 rows) -> nohit
2026-11-17 TypesOwner10 r10 opus-5-5:xhigh: CsStateFull view -> CsState (views fixed)
2026-11-17 2026-11-17: cleanup HackmodelSlotUpdateFacingTrigger HackmodelSlotUpdateFacingTrigger opus-5-5: re-measure on the 11134d9a body (alone removed: e9755c 6, 0b27f0 46, 0b27f0#2 68, 414c65 2, 414c65#2 39, all 66); new body without the actorYaw local (gCurrentActor->yaw read inline in the yawDiff subtraction and the four arc compares per case): all five removed full=2, with 414c65 kept fdiff exit 0 -> 4 sites fixed; 26 redundant casts dropped, fdiff 0. 414c65 alone on the new body: assignment inside the sinApprox argument 2, angle computed before the arc test / before the if 2 (uopt sinks it back), cast spellings 2, declaration position 2, expression in both calls without an angle local 89, variants.py scan no zero; permute 900 s from the actorYaw-free body (base 16, best 16, 24817 iterations) -> nohit
## Untried ideas
- A file-scope `static const f64` for 2pi or 4095.0 (an ilod in angle's rhs would stop the forward, Q0558) - needs .rodata order evidence and is a constant-variable steer unless the asm shows a symbol load (it shows .rodata+216/+224 literals) (this unit)
- angle consumed by another statement the target really performs: none found in the asm (this unit)
## Evidence
- 0x3bf4 `lh a1,0xe6(t8)` loads gCurrentActor->yaw once per case; 0x3bf8 `subu a0,v1,a1`, 0x3bfc/0x3c00 `sll t9,a0,16; sra t1,t9,16`, 0x3c04 `bgez t1` with `move a0,t1` in the delay slot: the sign test reads yawDiff's single sign-extension (case 2 the same at 0x3d1c-0x3d30).
- Arc compares read $a1 (the one actor-yaw load) at 0x3c40/0x3c48/0x3c5c/0x3c64 with arcMax $a2 (lh 0x8a(t0)) and arcMin $v0 (lh 0x88(t0)).
- 0x3c88 `mtc1 v1,$f4` converts yaw ($v1) for the angle; 0x3cac `cvt.s.d $f12`; 0x3cb4 `swc1 $f12,0x44(sp)` in the sinApprox delay slot and 0x3cbc `lwc1 $f12,0x44(sp)`: angle lives in its home M-308 = sp+0x44, sub spilled to its home sp+0x168 (M-16).
- 0x3b90 `beqzl v0` is the explicit case 0 compare of sub->unk50 (lbu v0,0x50(v1) at 0x3b84).
- Literals 4095.0 and 2pi are .rodata+216 / +224 (R_MIPS_HI16/LO16 .rodata), not symbol loads.
