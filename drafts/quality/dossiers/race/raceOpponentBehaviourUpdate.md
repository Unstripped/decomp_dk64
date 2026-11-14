# raceOpponentBehaviourUpdate (race, src/race/0.c)

## Sites
race:80024690:other:bcda7c other: u16 `angU` copy preserves the atan truncation in ring temp $t3, stores it at sp+0x66, and doubles it as `addu t4,t3,t3` without an sll/sra sign-extension chain. KEPT.
race:80024690:dead-if:4456a3: dead phase test steered the first `unk35` copy into $a0. FIXED (removed).
race:80024690:dead-if:9cd7d5: dead phaseCopy test steered the switch copy into $v0. FIXED (removed).
race:80024690:other:fdc010 copy-only: `selector = phaseCopy` is the single remaining selector-copy steer after consolidating the two dead tests. KEPT.

## Attempts
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: removed each/both dead tests -> same 14-line v0/v1 swap at target 0xc0c-0xc50.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: switch forms tried: direct controller->unk35; phase; phaseCopy; chained and sequential assignments; switch assignment expressions; s32/u32/u16/s16/u8 selector and phase widths; declaration orders; case-0 increment through phase or phaseCopy. Best natural forms were 4 lines (copy scheduling only) or 10-14 lines (v0/v1); none zero.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: Q0330 exact analog from raceOpponentCarBehaviorUpdate: phase=unk35; phaseCopy=unk35; selector=phaseCopy; switch(selector) -> fdiff 0. This replaces two dead-if sites with one tagged selector copy (net -1 hack).
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: angU removal: ang16+ang16 (signed) -> mfc1 v0, sh v0,0x66(sp), sll/sra before addition (186 lines); one u16 ang16 with `(u16)ang16 * 2` -> only target addu becomes sll (2 lines); u16 addition adds `andi v1,v0,0xffff` and shifts the later t ring (718 lines); u32/s32 raw copy colours v0 (580 lines); u8/s16 widths 178/186 lines. Coupled removal with both dead tests: best 16 lines.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: names: tmp->stateValue, e->pad, fv1->value, sel->phaseCopy, x->selector, y->phase. ang16/angU retained to keep the base site key stable.
2026-11-14 HackraceOpponentBehaviourUpdate openai-codex/gpt-5.6-sol: hack-free permuter on the coupled no-dead-test body, 900 seconds: base 40, best 10. Best hint was `phase = (phaseCopy = controller->unk35)`, corresponding to the already-tested 4-disassembly-line move-schedule miss; no zero.

## Untried ideas
none with new evidence; angU and selector copy remain after uopt/ring diagnosis and the 900-second hack-free permuter retry.

## Evidence
0xd10-0xd48: target mfc1 $t3; sh $t3,0x66(sp); addu $t4,$t3,$t3; later lh $a1,0x66(sp). A single s16 creates mfc1 $v0 and sign-extension; a single u16 double uses sll or retains an `andi`.
0xc0c-0xc24: target lbu $v1,0x35(controller); move $a0,$v1; beqz $v1; delay-slot move $v0,$v1; cases 1/2 compare $v0. Q0330's exact three-copy chain reproduces this sequence.
0xc4c: case 0 increments from the original $v1 value; case arms after calls reload `unk35` before assigning phase.
