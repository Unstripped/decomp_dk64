# actorMapModelsSetup (global, src/global/8D3E0.c)
## Sites
global:806886E0:other:c3f815 (other, FIXED 2026-11-15): `s32 modelAsset` was reused as the asset id and as the `D_8076A160[mapIndex]` colour cursor (`modelAsset = (s32)&D_8076A160[mapIndex]`, `((u8 *)modelAsset)[0x24..0x26]`, `modelAsset += 3`). Steered nothing: the cursor is uopt's strength-reduced induction variable in s0.
LAYOUT (not a site): `flag = 0; do { lightSetColor(` on one line steers as1 order of the hoisted `ldc1 $f20` vs `addu s0` (0x17c-0x184).
## Attempts
2026-11-09 Clean8D3E0 claude-opus-5-5:low: names nohit; review fixed casts=15.
2026-11-11 Rev16G/Batch16 claude-opus-5-5:low: subtables/records -> u8 *; ModelAssetEntry160.unk1C -> s32; modelAsset param as u8 * blocked (loadMode andi s2 lost).
2026-11-12 CleanGlobal8D3E0 claude-opus-5-5: u8 * param retype kept (m1-m6), ModelAssetEntry178 view folded into D_8076A160[i].modelData.
2026-11-14 OwnerWarnings450Chain claude-opus-5-5:high: param retyped (u8 *modelData), s32 modelAsset local in the old pad slot (Q0836); colour-walker reuse tagged FAKE; separate walker local at two declaration positions grows the frame.
2026-11-15 HackactorMapModelsSetup2 claude-opus-5-5:high: in-place `D_8076A160[mapIndex].rgb[flag][0..2]` with flag as counter -> full=0, fdiff 0 (FIXED). modelData param as walker (`modelData = D_8076A160[mapIndex].rgb[0]` or `(u8 *)&D_8076A160[mapIndex]` + 0x24) full=46; ternary for the asset id + `u8 *rgb` walker local full=46. LAYOUT probes: init and `do {` on separate lines full=4, `for (flag = 0; flag < gMapChunkCount; flag++)` without the outer if full=3, `flag = 0; do {` on one line with the call on the next line full=0 (equivalent to current).
## Untried ideas
`if (gMapChunkCount > 0) { for (flag = 0; ...) }` with the init on the `if`/`for` line, to retire the LAYOUT (source: this session's L2 full=3).
## Evidence
Frame 0x60: s0-s2 at 40/44/48, ra 52, $f20 at 32; subtables 92, records 88, mapIndex 84 (spilled, reloaded 0x118/0x150), preMapModelCount 78 (sh/lhu). s0 = modelData (0x14), then asset id (0xcc zero / 0xd8 v0), then rgb cursor (0x184 addu s0,t1,t2; lbu 36/37/38(s0)). s1 = flag then loop counter. u8 channel -> double via u32 (bgez + 0x41f00000 adjust at 0x194).
