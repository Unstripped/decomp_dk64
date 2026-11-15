# raceOpponentBehaviourUpdate (race, src/race/0.c)

## Sites
race:80024690:other:bcda7c other: u16 `angU` copy preserves the atan truncation in ring temp $t3, stores it at sp+0x66, and doubles it as `addu t4,t3,t3` without an sll/sra sign-extension chain. KEPT.
race:80024690:dead-if:4456a3: dead phase test steered the first `unk35` copy into $a0. FIXED (removed).
race:80024690:dead-if:9cd7d5: dead phaseCopy test steered the switch copy into $v0. FIXED (removed).
race:80024690:other:fdc010 copy-only: `selector = phaseCopy` is the single remaining selector-copy steer after consolidating the two dead tests. KEPT.
race:80024690:other:5c6e36: `value = gCurrentActor->y` reused the f32 `value` as the actor height. FIXED: the height test and both dist branches read `gCurrentActor->y` in place (uopt CSEs them into the one lwc1 $f2,128(s0) at 0xbe4).
race:80024690:other:f88a4d: `stateValue` reused for the D_8002FB94 path id. FIXED: case 5 switches on `controller->unk35` directly (case 1 stores `controller->unk35 + 1`), so the local only holds the path id and is renamed `pathId`.
race:80024690:other:26120e (copy-only key): case-10 `selector = gCurrentActor->unk155` shares the u32 selector with the raceStatus-0 switch. Pre-existing, now tagged; part of the fdc010 knot. KEPT.

## Attempts
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: removed each/both dead tests -> same 14-line v0/v1 swap at target 0xc0c-0xc50.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: switch forms tried: direct controller->unk35; phase; phaseCopy; chained and sequential assignments; switch assignment expressions; s32/u32/u16/s16/u8 selector and phase widths; declaration orders; case-0 increment through phase or phaseCopy. Best natural forms were 4 lines (copy scheduling only) or 10-14 lines (v0/v1); none zero.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: Q0330 exact analog from raceOpponentCarBehaviorUpdate: phase=unk35; phaseCopy=unk35; selector=phaseCopy; switch(selector) -> fdiff 0. This replaces two dead-if sites with one tagged selector copy (net -1 hack).
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: angU removal: ang16+ang16 (signed) -> mfc1 v0, sh v0,0x66(sp), sll/sra before addition (186 lines); one u16 ang16 with `(u16)ang16 * 2` -> only target addu becomes sll (2 lines); u16 addition adds `andi v1,v0,0xffff` and shifts the later t ring (718 lines); u32/s32 raw copy colours v0 (580 lines); u8/s16 widths 178/186 lines. Coupled removal with both dead tests: best 16 lines.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: names: tmp->stateValue, e->pad, fv1->value, sel->phaseCopy, x->selector, y->phase. ang16/angU retained to keep the base site key stable.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: hack-free permuter on the coupled no-dead-test body, 900 seconds: base 40, best 10. Best hint was `phase = (phaseCopy = controller->unk35)`, corresponding to the already-tested 4-disassembly-line move-schedule miss; no zero.
2026-11-15 HackraceOpponentBehaviourUpdate2 anthropic/claude-opus-5-5:high: 5c6e36 fixed by reading gCurrentActor->y in place (no local); a separate actorY local measured 6-90 lines by declaration slot.
2026-11-15 HackraceOpponentBehaviourUpdate2 anthropic/claude-opus-5-5:high: f88a4d fixed by dropping the case-5 switch local (switch on controller->unk35, case 1 stores controller->unk35 + 1); separate pathId with the case-5 stateValue kept: 4 lines (case-5 load in v0), inline path id 110, separate lap-index local 15-194.
2026-11-15 HackraceOpponentBehaviourUpdate2 anthropic/claude-opus-5-5:high: bcda7c (after the two fixes): single u16 with ang16 * 2, 2 * ang16 or << 1 -> 1 line (sll t4,t3,1 for addu); single u16 sums in any order 312; single s16 (plain, without (s32), assignment expression) 6 (sll/sra); s32/u32 temp chain/sep 311, temp only 355.
2026-11-15 HackraceOpponentBehaviourUpdate2 anthropic/claude-opus-5-5:high: fdc010: 9 assignment forms x selector widths x phase widths x case-10 selector shared/direct (313 variants) plus 9 case-0 increment spellings: best 2 (u8 phase adds andi a0) and 4 (`sel = unk35; phase = sel` or `phase = sel = unk35`: right registers, phase/selector moves in the other order); `phase = unk35; sel = unk35` 7 (v0/v1 swap). Case-10 switch on its own local or on unk155 directly with the current chain: 11 lines.
2026-11-15 HackraceOpponentBehaviourUpdate2 anthropic/claude-opus-5-5:high: fdc010 hack-free permuter from the 4-line `sel = unk35; phase = sel` body, 905 seconds: base 10, best 10 (no improvement).
2026-11-15 HackraceOpponentBehaviourUpdate2 anthropic/claude-opus-5-5:high: review: five redundant value casts dropped ((f32) on the yaw differences, (s32)/(f32) on the timer updates); the (s32) on the atan angle stays (without it the chain measures 46).

## Untried ideas
none with new evidence; angU and the selector copy/sharing remain after ucode, trace and statement-order diagnosis.

## Evidence
0xd10-0xd48: target mfc1 $t3; sh $t3,0x66(sp); addu $t4,$t3,$t3; later lh $a1,0x66(sp). uopt ucode: the chain forwards cvt s32(cvtl u16(cvt u32(cvt s32 f64))) as one candidate and ugen folds the cvtl into the trunc; a single u16 home var keeps cvt u32 X and re-applies cvtl u16 at each use (andi). A single s16 creates sign extension.
0xc0c-0xc24 (object 0x129c-0x12b4): target lbu $v1,0x35(controller); move $a0,$v1; beqz $v1; delay-slot move $v0,$v1; cases 1/2 compare $v0. ugen emits move a0 (phase) then move v0 (selector) and as1 puts the second in the delay slot. uopt level 5: selector (shared with case 10) adjsave 2.67 > load expression 2.0 > phase 1.25.
0xc4c: case 0 increments from the original $v1 value; case arms after calls reload `unk35` before assigning phase.
