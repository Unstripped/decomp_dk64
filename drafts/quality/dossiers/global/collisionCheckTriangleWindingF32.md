# collisionCheckTriangleWindingF32 (global, src/global/6AD90.c)
## Sites
global:80669930:other:27898a `f32 cross[1]` forces a dead store of the cross product at sp+4.
## Attempts
2026-11-17 HackcollisionTestStaticMeshFloor3 opus: two-element XZ edges and three-element normal cross[1] score 9; best adjacent declaration swap scores 7.
## Untried ideas
Find a natural representation that preserves the original 3D edge array offsets while giving the cross product a non-vreg home at sp+4.
## Evidence
Target frame 0x20, trial 0x18; target cross stored at sp+4, trial sp+0; target edge slots 0x14/0x1c and 0x8/0x10, trial 0x10/0x14 and 0x8/0xc.
