# actorTargetCourseHostUpdate (global, src/global/C2A90.c)
## Sites
global:806BE8BC:other:9a2e3b other: FIXED 2026-11-25. Was `s32 sel` holding the subState inner-switch selector (cases 0x1F, 0x28) and reused as the 0x303/0x304 anim id for actorScriptStart, pulling every selector use into $a1 (Q0162). Removed: switch directly on gCurrentActor->subState in both cases, inline ternary argument.
## Attempts
2026-11-12 Rev20C: switch on unk155 alone (sel kept for the anim id) -> fdiff 1 (history)
2026-11-14 RereviewW2Global: switch (gCurrentActor->unk155) direct -> recorded in review (history)
2026-11-18b Polishglobal126260: tagged sel reuse FAKE; a separate anim local gives v0 (diagnose nohit, history)
2026-11-25 continue CleanactorTargetCourseHostUpdate anthropic/claude-opus-5-5: both halves together (switch on field x2 + inline `(gFrameCounter & 1) ? 0x303 : 0x304`, sel deleted; lever from scout LeverScout26) -> fdiff exit 0 whole file, clint uninit 0, cwarn total 0
## Untried ideas
none open (function has no sites left)
## Evidence
- expected C2A90.o: frame `addiu sp,sp,-56` at 0xb2c; sel has no stack home.
- 0x1F switch: 0xd18 `lbu a1,341(s0)`, 0xd20 `beqz a1`, 0xd28 `beq a1,at` (at=1).
- 0x28 switch: 0xf40 `lbu a1,341(s0)`, 0xf4c `beqz a1`, 0xf54 `beq a1,at`.
- anim id: 0x12c0 `li a1,772`, 0x12c4 `andi t7,t6,1`, 0x12c8 `beqz t7`, 0x12d0 `b`, 0x12d4 `li a1,771` (delay slot), 0x12d8 `jal actorScriptStart`.
- uopt trace of the clean copy: cfe shared switch temp -12vreg (candidate 39) is stored from the subState cvt (bit 43) and from both ternary results 771/772 (bits 144/145); coloured uopt 4 = $a1. The a1 sharing is cfe reusing its switch temp for a later `?:` result (Q1303, Q1318), not a user local (corrects Q0162 for this function).
