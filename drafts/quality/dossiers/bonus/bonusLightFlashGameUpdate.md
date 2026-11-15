# bonusLightFlashGameUpdate (bonus, src/bonus/2690.c)

## Sites
- bonus:80029364:other:c02f22: `((s16 *)&D_8002D8F4)[2] = j` stores D_8002D8F8 through D_8002D8F4's base so lh 0x3028 (lui v1) and sh 0x3044 (lui at) keep separate lui/%lo pairs instead of one hoisted lui/addiu base.
- bonus:80029364:other:190d09: `((s16 *)&D_8002D8F4)[4] = d`, same for D_8002D8FC: lh 0x3088 (lui v0) / sh 0x309c (lui at).
- bonus:80029364:dead-if:e5ec5b: `if (gCurrentActor->state && ...) {} if (j == 9) {}` make j a coloured candidate so the draw is `andi v1,v0,3` / `addiu t4,v1,2` at 0x3070 (else andi t3 / addiu t4).
- bonus:80029364:dead-if:300787: `d = -100; if (d) {} D_8002D8FC = d | 0` gives `li v0,-100` hoisted above bc1f at 0x3108 (else li t2).
- bonus:80029364:dead-if:b1a373: `j = 1; if (j) {} D_8002D8F8 = j | 0` gives `li v1,1` at 0x310c (else li t2,1 and t-reg shifts after 0x3130).

## Attempts
- 2026-11-10..2026-11-14 (rounds 8-36, OwnerMinecartTrackPoints, OwnerPadInputStateViews2, Polish*): remove/cond/classify per site and together (fdiff 1), permuter runs (best 960/685/215/30, no natural form), LightFlashTimers struct view of 0x8002D8F4 (timer lh/sh share a base), --/++ and plain stores (one lda web), natural-body reconstructs (fdiff 1).
- 2026-11-15 HackbonusLightFlashGameUpdate2 anthropic/claude-opus-5-5:high: lever b `D_8002D8FC = d = -100` (full=82), `= (d = -100)` (82), `D_8002D8F8 = j = 1` (82), both (112), shared tail `d = 0/-100; D_8002D8FC = d` (8); lever c timer in r (6) or d (4), with draw plain/j/r/i (2..10): no zero.
- 2026-11-15 HackbonusLightFlashGameUpdate2 anthropic/claude-opus-5-5:high: D_8002D8F4/F8/FC as function-local statics with a fully plain body: whole file TEXT OK (fdiff exit 3, own .data only). With all 2690 data 0x98C0-0x990F defined in C (carve_2690.c) the built .data is byte-identical to the ROM range. Blocked only on the yaml carve (header-request.md).
- 2026-11-15 same: D_8002D904 as a static local of bonusPerilPathPanicGameUpdate with plain `= 1 - n` (d61c1f): +2 instructions, not a fix.

## Untried ideas
- After the carve: fdiff the carve copy to 0 and re-run the sweep; consider the same function-local-static test for other bonus/race Q0332 sites (func_8002A398 d61c1f needs more than a static: +2 instrs).

## Evidence
- 0x3010-0x3044: `lui v1,%hi(D_8002D8F8)` before bc1f, `lh v1,0(v1)` at 0x3028, separate `lui at` + `sh t9` at 0x302c/0x3044.
- 0x3084-0x309c: `lui v0; lh v0` then separate `lui at; sh t6` for D_8002D8FC.
- 0x3100-0x312c: `lui at,%hi(D_8002D8FC)` above the branch, `li v0,-100; li v1,1` hoisted; second `lui at` in the zero arm; stores `sh zero`/`sh v0` in the arms and `sh v1` to D_8002D8F8 after the join.
- Data: asm/bonus/data/0.data.s 0x98F4 `.byte 0x32` + pad, 0x98F8/0x98FC s16 zero + pad: IDO's +0/+4/+8 static layout.
- Q0761 (function-local static = native S variable, own lui/%lo per access), Q0564, Q0332, Q0520.
