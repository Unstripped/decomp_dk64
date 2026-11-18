# collisionCheckTriangleWindingS16 (global, src/global/6AD90.c)
## Sites
global:8066893C:other:27898a other (now `// ORIG`, no site): `f32 cross[1]` is a non-vreg memory local, so ugen emits its home store `swc1 $f10,4(sp)` at 0x293c and the compare converts the cached register (`cvt.d.s $f8,$f10` at 0x2938). A plain scalar has the same home (uopt candidate `isvar M -28`, = sp+4 in frame 0x20) but is coloured (adjsave 2.0), so the store vanishes.
## Attempts
2026-11-16 Polishglobal6AD90 opus:high: CrossProductStack struct of locals retired into plain v1[3]/v0[3] arrays; one-element cross tagged.
2026-11-17 HackcollisionTestStaticMeshFloor3 gpt-6.1-terra: two-element XZ edges and three-element normal cross[1] score 6; best adjacent declaration swap scores 4.
2026-11-18 CleancollisionCheckTriangleWinding opus: `f32 cross[3]` with the Y component `cross[1]` (the vector math of collisionStoreTriangleNormalAnglesS16): v1,v0,cross order keeps frame 0x20 but stores at 0(sp) (score 1); the other 5 orders 5-7. Per-index probes (v1,v0,cross order): cross[2] idx0 1 (0(sp)), idx1 0; cross[3] idx0 6 (frame 0x28), idx2 0; cross[4] idx0 7, idx1 6 (frame 0x28), idx2 1 (0(sp)), idx3 0. Vec3f normal struct 13 (scalar-replaced, frame 0x18), Vec3f edges+normal 53, `f32 edge[2][3]` + cross[3] idx1 1. uopt_trace -l5 of the plain scalar: home -28 vreg, coloured. -> kept (nohit).
2026-11-18 "2026-11-18: cleanup CleancollisionCheckTriangleWindingF32" CleancollisionCheckTriangleWindingF32 opus: ORIG check: the target executes the store to the variable own home (swc1 at 0x293c, fp-28, right below v0 at sp+8) and never reloads it. Plain scalar 13; `f32 cross; f32 *out = &cross;` with every access through `*out` fdiff 0 (address-taken scalar stays non-vreg like the array; a redundant alias, so the array is kept). -> FAKE retagged `// ORIG` citing 0x293c (diagnose fixed).
## Untried ideas
none: the construct is the target behaviour (executed store at 0x293c).
## Evidence
Frame 0x20 (leaf). Edge stores: v1[0] 0x14 (0x28cc), v1[2] 0x1c (0x28e8), v0[0] 0x8 (0x2908), v0[2] 0x10 (0x2930), none reloaded. Cross: sub.s $f10 at 0x2934, cvt.d.s $f8,$f10 at 0x2938, swc1 $f10,4(sp) at 0x293c, c.le.d $f8,$f18 at 0x2940; no lwc1 of 4(sp). Element k of an array f32 a[N] declared after v0 lands at sp+0x8-4N+4k; a negative address grows the frame by 8 (0x28).
