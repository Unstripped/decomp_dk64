# tagBarrelIsSpecial (global, src/global/80150.c)
## Sites
global:8067B450:proto-steer:c1a42b proto-steer: `#define PROTO_SKIP_flagGet` — skipped the shared `u8 flagGet(s16, u8)` so tagBarrelCheckKongFlag compiled against s32. REMOVED (this session).
global:8067B450:proto-steer:b5496b proto-steer: local `s32 flagGet(s16, s32);` — same steer. REMOVED (this session).
global:8067B450:other:60b7c8 other: `s32 count = 4;` value-named constant local; target `li a2,4` before the actorListFindIdByActor call, `sw a2,28(sp)` in its delay slot, frame 0x20. EXHAUSTED, kept.
## Attempts
2026-11-09..14 (rounds 0-36, OwnerFlagGetWidthPlan; claude-opus-5-5 low/xhigh/high): consolidate/diagnose with the shared u8 proto -> only tagBarrelCheckKongFlag differs (full=11, t0/t9/t1 -> t1/t0/t2 at 0x7f48); owner-width redesign closed (A/B/C/D shadow protos over 48 callers). 60b7c8: plain/recipe/permute nohit; literal 4 natural for/do-while full=20 (frame 0x18, no a2 spill).
2026-11-16 HacktagBarrelIsSpecial anthropic/claude-opus-5-5:high: KongFlagInfo.isSet s32 -> u32 in tagBarrelCheckKongFlag -> fdiff 0 with both steers removed. Tried and failed (full=11): bare `!info.isSet`, `setFlag && !info.isSet`, `p->isSet =`, `(s32)flagGet(...)`, comma-embedded assignment, `int` field, `(s16)info.value`. 60b7c8: call in for-init 30/20, u32 i 20, u32 listId 20.
## Untried ideas
60b7c8: none credible; the bound must be a candidate live across the call (a local or a parameter-like value).
## Evidence
tagBarrelCheckKongFlag 0x7f0c `sw v0,0x24(sp)` stores flagGet's result unconverted; uopt_trace (s32 field): `ucvt{flagGet}` then `ustr{isSet}{ucvt}`; (u32 field): `ustr{isSet}{flagGet}` with no ucvt — the ucvt temp is the extra ugen ring register.
