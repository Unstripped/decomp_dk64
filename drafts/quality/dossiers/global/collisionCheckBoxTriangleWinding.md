# collisionCheckBoxTriangleWinding (global, src/global/6AD90.c)
## Sites
global:8066AC10:other:27898a `f32 cross[1];`: the one-element array keeps the cross product a dead store to 4(sp) (swc1 f4,4(sp) at 0x4bf0, never reloaded). A scalar stays in a register.
## Attempts
2026-11-16 Polishglobal6AD90 opus:high: CrossProductStack struct retired into plain arrays; one-element cross tagged.
2026-11-16 HackcollisionCheckBoxTriangleContainsPointXZ opus:high: `f32 cross[3]` written to cross[1] (the y normal component, as collisionStoreBoxTriangleNormalAngles) 1 line (store at 0(sp)); the other 5 declaration orders 9-11; cross[3] index 0 10; scalar 16; inline test 19; `f32 cross[2]` index 1 fdiff 0 but is the same memory-only aggregate.
2026-11-17 HackcollisionTestStaticMeshFloor3 gpt-6.1-terra: two-component XZ edge arrays plus a three-component cross[1] scores 9, with frame 0x18 vs 0x20 and cross store sp+0 vs sp+4 at 0x4bf0; best declaration swap scores 7.
2026-11-18 CleancollisionCheckTriangleWinding opus: cross[3] idx2 fdiff 0 (Y formula in the Z slot: index steer); Vec3f normal struct 16 (scalar-replaced, frame 0x18), Vec3f edges+normal 34, `f32 edge[2][3]` + cross[3] idx1 1; mechanism (S16 probes): the array declared after v0 starts at v0 - 4N and the frame bottom is its deepest referenced element, so cross[3] sits at sp-4 (cross[1] at 0(sp)) and only the last element reaches sp+4. -> kept (nohit).
## Untried ideas
none: with v1[0] at 0x14 and v0[0] at 0x8 fixed, the stored value must be the last element of the array declared right after v0; no natural vector puts the Y formula there.
## Evidence
Frame 0x20. v1[0] 0x14, v1[2] 0x1c, v0[0] 0x8, v0[2] 0x10 (each stored and reloaded); cross stored at 0x4 at 0x4bf0, then cvt.d.s + c.le.d against 0.0. Element k of f32 a[N] declared after v0 lands at sp+0x8-4N+4k; below sp it grows the frame to 0x28 only when referenced.
