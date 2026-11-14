# effectActorOrbitFollowUpdate / effectArcAroundActorUpdate / effectPuffRiseUpdate (global, src/global/11BC10.c)

## Sites
- 4c1bb4, cacc56 (OrbitFollow) and 39fab2, 515501 (ArcAround): the extra `& 0xFFFF` masks were folded by the compiler and only stepped the ugen int temp ring. The target executes a single `andi 0xfff` per wrap. REMOVED.
  - The replacement is the s16 angle narrowing `(f32)((s16)(s32)x & 0xFFF)`, the same idiom these functions use for mathSinF/mathCosF.
- 8d261d, 3e6015 (PuffRise): the file-wide `PROTO_SKIP_lightAdd` plus a local s32-parameter declaration. With the header's u8 colour parameters, only effectFadeRatioStepUpdate differed (its redundant `& 0xFF`). REMOVED.

## Attempts
- 2026-11-14 U HackeffectActorOrbitFollowUpdate:
  - Mask sites: `(s16)` narrowing inside gives fdiff 0. Other spellings: u16 inside 26 lines, u16 outside 151, s32/s16 local 26, u16 local 99, u32 133.
  - Proto sites: with the header prototype, a per-function asm compare over all 12 lightAdd callers showed only effectFadeRatioStepUpdate differing (10 lines). `u8 intensity = (u32)(...)` without the mask gives fdiff 0.

## Untried ideas
- None for these sites.

## Evidence
- Target effectActorOrbitFollowUpdate: `mfc1 t0; andi t1,t0,0xfff` (0x6fa0/0x6fa8) and `mfc1 t5; andi t6,t5,0xfff` (0x6fc8/0x6fd0). The plain form uses t8/t9 and t1/t2 (two ring steps short per site).
- uopt -l6 assignment lists are identical between the plain and fixed forms (candidate numbers shift by one).
- Target effectFadeRatioStepUpdate: one `andi t0,v0,0xff`, then three `sw t0` argument stores.
