# raceGetRoute (race, src/race/A960.c)
## Sites
race:8002E960:other:3626c5 early `e = &D_8002FCF0->items[idx]` at the declaration: REMOVED; replaced by a defensive `e = NULL` initialiser. The entry def of e (never executed: copy-prop removes it) makes e a candidate live from entry, coloured v1, so the D_8002FCF0 load takes a1 as in the target.
## Attempts
2026-11-11 round 16 CleanRaceB / Rev16G: tagged, sweep plain, diagnose (e in $3, global in $5), permute best=0 only by re-adding the early def. 2026-11-12 round 33 CleanRaceA960: uopt_trace diagnose.
2026-11-14 HackraceGetRoute opus:high: direct return / table local / items local / two ifs / u32 or s32 idx / swapped compare / init then return e / init then direct return / init with else: 6-18; NULL result joined at the end 19; init-then-nullify 21; ternary 19; e = NULL at the declaration with return NULL then e = &...; return e: 0.
## Untried ideas
none.
## Evidence
lui/lw a1 (D_8002FCF0) at 0x0/0x4; beqz a1; lbu/lhu count; bnezl with lw t8,4(a1) (items) in the delay slot; result addu v0,t8,t9.
