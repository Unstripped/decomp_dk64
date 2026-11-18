# collisionCheckTriangleWindingS16 (global, src/global/6AD90.c)
## Sites
global:8066893C:other:27898a other: `f32 cross[1]` keeps the cross product memory-resident so ugen emits its home store `swc1 $f10,4(sp)` at 0x293c (never reloaded; the c.le.d reads the cached $f10). A plain scalar has the same home (uopt candidate `isvar M -28`, = sp+4 in frame 0x20) but is coloured (adjsave 2.0), so the store vanishes.
## Attempts
2026-11-16 Polishglobal6AD90 opus:high: CrossProductStack struct of locals retired into plain v1[3]/v0[3] arrays; one-element cross tagged.
2026-11-17 HackcollisionTestStaticMeshFloor3 gpt-6.1-terra: two-element XZ edges and three-element normal cross[1] score 6; best adjacent declaration swap scores 4.
2026-11-18 CleancollisionCheckTriangleWinding opus: `f32 cross[3]` with the Y component `cross[1]` (the vector math of collisionStoreTriangleNormalAnglesS16): v1,v0,cross order keeps frame 0x20 but stores at 0(sp) (score 1); the other 5 orders 5-7. Per-index probes (v1,v0,cross order): cross[2] idx0 1 (0(sp)), idx1 0; cross[3] idx0 6 (frame 0x28), idx2 0; cross[4] idx0 7, idx1 6 (frame 0x28), idx2 1 (0(sp)), idx3 0. Vec3f normal struct 13 (scalar-replaced, frame 0x18), Vec3f edges+normal 53, `f32 edge[2][3]` + cross[3] idx1 1. uopt_trace -l5 of the plain scalar: home -28 vreg, coloured. -> kept (nohit).
## Untried ideas
none natural: the array declared after v0 starts at v0 - 4N and the frame bottom is its deepest referenced element, so only its LAST element reaches sp+4 (cross[1] of [1], [1] of [2], [2] of [3]); a 3-vector holding the Y formula stores at sp+0. Only a non-array memory-resident scalar could be natural, and IDO colours every such scalar here (Q1041: address-take/volatile are no stand-ins).
## Evidence
Frame 0x20 (leaf). Edge stores: v1[0] 0x14 (0x28cc), v1[2] 0x1c (0x28e8), v0[0] 0x8 (0x2908), v0[2] 0x10 (0x2930), none reloaded. Cross: sub.s $f10 at 0x2934, cvt.d.s $f8,$f10 at 0x2938, swc1 $f10,4(sp) at 0x293c, c.le.d $f8,$f18 at 0x2940. Element k of an array f32 a[N] declared after v0 lands at sp+0x8-4N+4k; a negative address grows the frame by 8 (0x28).
