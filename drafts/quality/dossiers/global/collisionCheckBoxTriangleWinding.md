# collisionCheckBoxTriangleWinding (global, src/global/6AD90.c)
## Sites
global:8066AC10:other:27898a `f32 cross[1];`: the one-element array keeps the cross product a dead store to 4(sp) (swc1 f4,4(sp) at 0x4bf0, never reloaded). A scalar stays in a register.
## Attempts
2026-11-16 Polishglobal6AD90 opus:high: CrossProductStack struct retired into plain arrays; one-element cross tagged.
2026-11-16 HackcollisionCheckBoxTriangleContainsPointXZ opus:high: `f32 cross[3]` written to cross[1] (the y normal component, as collisionStoreBoxTriangleNormalAngles) 1 line (store at 0(sp)); the other 5 declaration orders 9-11; cross[3] index 0 10; scalar 16; inline test 19; `f32 cross[2]` index 1 fdiff 0 but is the same memory-only aggregate.
## Untried ideas
none: with v1[0] at 0x14 and v0[0] at 0x8 fixed, the aggregate must start at 0(sp) and span at most 8 bytes.
## Evidence
Frame 0x20. v1[0] 0x14, v1[2] 0x1c, v0[0] 0x8, v0[2] 0x10 (each stored and reloaded); cross stored at 0x4 at 0x4bf0, then cvt.d.s + c.le.d against 0.0.
