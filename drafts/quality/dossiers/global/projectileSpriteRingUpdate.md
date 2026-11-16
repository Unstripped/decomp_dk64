# projectileSpriteRingUpdate (global, src/global/9BF30.c)
## Sites
global:80697988:other:d61aae other: REMOVED 2026-11-16. Was `kind = sub->ringType;  // FAKE` before the `sub->ringType != 0` test, with `switch (kind)`; it kept the dispatch byte in $a0 (lbu a0,17(v1) at 0x77c/0x844, beqzl a0 at 0x84c, bne a0,at at 0x854) instead of $v0.
## Attempts
2026-11-14 HackSentinelSwitchChains opus:high: sentinel switch: switch (ringType) with case 1 then case 0 (old else arm) = 4 diff lines (v0 vs a0 only); case 0 first = 178; with a default = 4; switch (kind) with kind kept as the selector (u8/s32/u32/s16/u16, declared first) = 4-13; (s32)/(u8) selector casts = 4; if/else-if chains on ringType or kind = 65-223; if (ringType == 0) ... else switch = 180
2026-11-16 HackprojectileSpriteRingUpdate2 anthropic/claude-opus-5-5:high: plain (switch (sub->ringType) in the branch) = 4 (v0 for a0); init-block one-case switch + outer one-case or two-case switch on the field (cfe shared selector temp with two defs, Q0944) = 6; one local reused for the init `== 1` read and the dispatch (if/switch init x if-on-kind/if-on-field/two-case outer x u8/s32/s16/u16/u32) = 17-50; one local for both test and switch (`kind != 0`, `(kind = ...) != 0`, `if (kind = ...)`, `if (kind)`, all widths, decl first/last) = 4-13; variants.py scan of the plain and two-case forms = no variant below 4; **`if (sub->ringType != 0) { s32 kind = sub->ringType; switch (kind) ... }` = 0 (fdiff exit 0)**; same with u32 = 0, u8/u16 = 3, s16/s8 = 36, with `> 0` test = 1-3; with the one-case switch replaced by `if (kind == 1)` = 61
## Untried ideas
none open (site removed)
## Evidence
- the target tests one lbu of ringType (lbu a0,17(v1) at 0x77c in the bnezl delay slot and 0x844 on the init path, PRE re-insertion per path) with beqzl a0 at 0x84c (to the ringType == 0 block at 0x938) then bne a0,1 at 0x854.
- uopt (fixed form): kind is cand 22 (-20vreg, adjsave 2.0, live bb8 only) and is coloured $v0 before the ringType ucvt cand 17 (adjsave 1.5, live bb7-8, interferes with 22 in bb8), which takes $a0; ugen then emits the lbu straight into a0. Plain form: cand 17 alone, coloured $v0.
- old hack form: the raw uilod (cand 16, bb7) took $v0 and the u8 kind (cand 20, bb7-8) took $a0 — same register outcome, different candidate.
