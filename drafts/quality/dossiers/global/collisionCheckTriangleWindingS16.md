# collisionCheckTriangleWindingS16 (global, src/global/6AD90.c)
## Sites
global:8066893C:other:27898a `f32 cross[1]` forces a dead store of the cross product at sp+4.
## Attempts
2026-11-17 HackcollisionTestStaticMeshFloor3 opus: two-element XZ edges and three-element normal cross[1] score 6; best adjacent declaration swap scores 4.
## Untried ideas
Find a natural representation that preserves the original 3D edge array offsets while giving the cross product a non-vreg home at sp+4.
## Evidence
At 0x293c target stores cross to sp+4; trial stores to sp+0. Target frame 0x20, trial 0x18; target edge slots 0x14/0x1c and 0x8/0x10, trial 0x10/0x14 and 0x8/0xc.
