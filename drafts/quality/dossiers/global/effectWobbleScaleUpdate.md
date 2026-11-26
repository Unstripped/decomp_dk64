# effectWobbleScaleUpdate (global, src/global/11BC10_effect_update.c)
## Sites
(untagged, removed 2026-11-25c) `wave` reuse (ReviewTypes21 2026-11-25, drafts/cleanup/pending.md "split or tag"): role 1 = cosApprox(speed * 2) z drift (base lines 884/887), role 2 = sinApprox(frame * 0.2267) scaleY wobble (base lines 891/893); both roles stay in $f0, neither reaches wave's home sp+0x30. Now two locals: `driftZ` (role 1) and `wobbleY` (role 2); the unused `s32 pad` (sp+0x28) is gone, its word taken by the new local (Q0644).
## Attempts
2026-11-25 continue 2026-11-25c CleaneffectWobbleRiseUpdate anthropic/claude-opus-5-5: natural split, declarations `mtx, pad2, wobbleX, wobbleY, driftX, driftZ` (`s32 pad` dropped: the split local takes its word, every home unchanged: wobbleX sp+0x34, driftX sp+0x2c, frame 0xB8) -> fdiff 0 (v/S1.c, then the copy). Census not needed (split matches).
2026-11-25 continue 2026-11-25c CleaneffectWobbleRiseUpdate anthropic/claude-opus-5-5: no-local spellings generated for the record only (v/S_inline1.c `effect->z -= (f32)((f64)cosApprox(...) * 0.2)`, v/S_inline2.c sinApprox inline in the scaleY product); not needed after the split matched, not scored.
## Untried ideas
- none for the reuse (fixed). The 12 `(WobbleScaleState *)` allocation views stay (ReviewTypes21: views=ok, file-local state struct on the polymorphic allocation member).
## Evidence
- frame 0xB8 (addiu sp,sp,-184 at 0x28a4); s0 = effect, ra/s0 saved at sp+0x1c/0x18.
- base declaration-order homes: mtx sp+0x78 (addiu a0,sp,120 at 0x2a44/0x2acc), pad2 sp+0x38, wobbleX sp+0x34 (swc1 $f0,52(sp) 0x29e8 across jal sinApprox 0x2a0c, lwc1 $f4,52(sp) 0x2a1c), wave sp+0x30 (never accessed), driftX sp+0x2c (swc1 $f8,44(sp) 0x294c across jal cosApprox 0x295c, lwc1 $f18,44(sp) 0x2968), pad sp+0x28 (never accessed); sp+0x20..0x27 below the homes.
- role 1: cosApprox(speed * 2) returns in $f0 (jal 0x295c), consumed in $f0 by cvt.d.s $f4,$f0 at 0x298c (mul.d by 0.2 at 0x29a8, sub.s into effect->z 0x29b0/0x29b4); no store to sp+0x30.
- role 2: sinApprox(frame * 0.2267) returns in $f0 (jal 0x2a0c), consumed by cvt.d.s $f18,$f0 at 0x2a58 (mul.d 0x2a5c, scaleY store 0x2a74); no store to sp+0x30.
- live regions: role 1 lines 884-887 (asm 0x2950-0x29b4), role 2 lines 891-893 (asm 0x29ec-0x2a74): disjoint, same type f32. Neither role has a home access, so a split local in the pad word is unobservable: the reuse was never evidenced.
- quirks: Q0644 (pad word taken by the split local), Q1122/Q1035/Q0986 (split census background), R-oildrum census rule (rulings.md).
