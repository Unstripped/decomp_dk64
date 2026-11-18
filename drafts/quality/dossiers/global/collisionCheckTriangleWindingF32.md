# collisionCheckTriangleWindingF32 (global, src/global/6AD90.c)
## Sites
global:80669930:other:27898a other: `f32 cross[1]` keeps the cross product memory-resident so ugen emits its home store `swc1 $f4,4(sp)` at 0x3910 (never reloaded; the c.le.d reads the cvt of $f4). A plain scalar takes the same home word but is coloured, so the store vanishes.
## Attempts
2026-11-16 Polishglobal6AD90 opus:high: CrossProductStack struct of locals retired into plain v1[3]/v0[3] arrays; one-element cross tagged.
2026-11-17 HackcollisionTestStaticMeshFloor3 gpt-6.1-terra: two-element XZ edges and three-element normal cross[1] score 9; best adjacent declaration swap scores 7.
2026-11-18 CleancollisionCheckTriangleWinding opus: `f32 cross[3]` with the Y component `cross[1]`: v1,v0,cross order keeps frame 0x20 but stores at 0(sp) (score 1); the other 5 orders 9-11. cross[3] idx2 fdiff 0 (Y formula in the Z slot: index steer). Vec3f normal struct 16 (scalar-replaced, frame 0x18), Vec3f edges+normal 34, `f32 edge[2][3]` + cross[3] idx1 1. -> kept (nohit).
## Untried ideas
none natural: same frame mechanism as collisionCheckTriangleWindingS16 (only the last element of the array declared after v0 reaches sp+4).
## Evidence
Frame 0x20 (leaf). v1[0] 0x14 (0x38b8), v1[2] 0x1c (0x38c8, reloaded 0x38d8), v0[0] 0x8 (0x38dc, reloaded 0x38e8), v0[2] 0x10 (0x38fc, reloaded 0x3900); v1[0] reloaded 0x38f4. Cross stored swc1 $f4,4(sp) at 0x3910, c.le.d at 0x3914.
