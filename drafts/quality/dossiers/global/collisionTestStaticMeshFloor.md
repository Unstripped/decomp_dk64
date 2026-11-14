# collisionTestStaticMeshFloor (global, src/global/6AD90.c)
## Sites
global:806679BC:other:3172c6 `h2 = (f64)(M * 6.0f);` before `h2 = <formula> + h2;`: REMOVED (2026-11-14). It only made the offset a named leaf so the add keeps the formula first (add.d f24,f20,f6 at 0x1e34).
global:806679BC:other:af4d3a (copy-only, pre-existing, now tagged) `h2 = <full height formula> + offset;`: recomputes the formula instead of reusing val; `(2000.0 * val) - 1000.0 + offset` or `h2 += offset` changes 86-337 lines.
global:806679BC:other:356775 `struct { u8 pad[3]; u8 cb; f32 cc; } spS;`: makes the address-taken &spS.cc alias cb, so the final `cb |= collisionTestHardcodedFloorPlane(&spS.cc, ...)` reloads lbu t5,203(sp) after the call.
## Attempts
2026-11-09 CleanD5E10 opus:low: separate locals (frame 0x158 vs 0x150), h2 += M*6, f32/f64 offset locals, reversed operands, permute.
2026-11-10 QualityTools: review. 2026-11-11 Rev16G / Rev17L: sweep, diagnose (single expression swaps add.d), permute.
2026-11-14 HackcollisionBstSortFlatItems opus:high:
- 3172c6: `f32 offset` declared in the padTop slot (first local, padTop removed) + `offset = M * 6.0f; h2 = <formula> + offset;` -> fdiff 0. Other placements: block-scoped f32 5 lines (spill homes of ix/iz 148/152 vs 152/156), with a pad word removed 0 for padTop/padH/padB/padC variants at several positions; f64 offset 27-56; h2 += offset 86; val-based formula 337; if/else forms 272-378.
- 356775: `f32 floorY; u8 hit;` (reverse order) puts the homes at 203/204(sp) exactly; 24 lines left: hit kept in s0 across the final call instead of reloaded. hit = call | hit / hit = hit | call: 74.
## Untried ideas
A real reason for cb to be aliased by the call (no callee writes it; collisionTestHardcodedFloorPlane only reads *arg0).
## Evidence
Target: sb zero,203(sp) / swc1 f4,204(sp) at 0x19ac/0x19b0; addiu a0,sp,204 at 0x1acc/0x1b70/0x242c; final lbu t5,203(sp) at 0x2440 after jal at 0x2438; add.d f24,f20,f6 at 0x1e34.
