# modelSlotFreeAssetTextures (global, src/global/36880.c)
## Sites
global:80636210:dead-if:208f26 dead-if `if (base) {}` (copy-propagated to a ucg1 of asset): with the triple guard it lifts asset (uopt bit 5) above i (bit 13) so asset takes s1 and i s2; alone neither guard does it (i s1, asset s2).
global:80636210:dead-if:d53555 dead-if `if (base && base && base) {}`: same mechanism, three more ucg1 uses of asset inside the second free.
`base = asset;` (copy-only, tagged 2026-11-15) other: redundant alias of the parameter; base (bit 10) is the s3 candidate that carries quadCount (lbu 32(s3)); without it (guards on asset) full=16.
## Attempts
2026-11-15 HackmodelSlotReplaceSegment6Commands anthropic/claude-opus-5-5:high: void **p walk (p[9]/p[13]) -> for loop over asset->textures[i]/asset->palettes[i] with guards kept -> fdiff 0 (applied; cast retired). Same with base->textures[i] -> 8.
2026-11-15 same: single guard grid (positions loop top, before palettes load, inside each free, after loop/after loop body; 1-4 uses; on asset or base) on both the do-while and for forms -> best 3 (i s1 / phantom s2); f2 merged 4-use guard 5, 5-use 7.
2026-11-15 same: guard-free natural forms: array-indexed for/do-while without base (h1-h4) 19, base for condition + asset indexed (m1/m4) 14, base assigned before the type test (o1/o2) 19, precheck on asset (o3) 14, p from base (o4) 14, statement order (o5/o6) 15, NULL/!= 0 spellings (o7) 15; variants scan on the guard-free copy: best 14.
2026-11-21 continue unit 2 Lever36880 anthropic/claude-opus-5-5 (levers Q1588/Q1590, base fd085ca0):
- Q1588 dead initialisers are inert here: 240 bodies (alias/guard configs x initialiser subsets of base = NULL / i = 0 / q = NULL x 6 declaration orders) score one value per config: alias + `if (base) {}` 3, alias + triple guard 3, alias alone 14, triple guard on asset without alias 16, single guard on asset 19, no alias/guards 19.
- uopt -l5 priorities (adjsave): base body asset (bit 5) 8.8 > i (bit 13) 6.2 (asset s1, i s2, base s3); alias + triple guard asset 6.8 < i 7.75; alias + single guard 3.5 < 7.75; alias alone asset 2.0 / i 10.33. Not a tie: asset (the parameter, bit 5) already has the lower candidate number, so renumbering cannot reorder it; it loses on adjsave by 0.95+ without both guards.
- Q1590 extra def/use: `base = asset` re-defined at the loop top each iteration with single guard 8, triple guard 8, alone 19; with the palettes arm as `if (q == NULL) continue;` + triple guard 5, + single guard 11; `(base = asset)->quadCount` as the loop bound with any guard combination 16-19; continue-form palettes arm on the current body 25.
- reconstruct (natural): direct field reads without q 19, early return 19, nested type/texAnims ifs 19, continue-form palettes arm 27, per-element pointer locals (&asset->textures[i], &asset->palettes[i]) 27. Without base the quadCount reload goes through the asset register itself (no s3 copy) and the phantom s1 is missing; the guard-free alias body (14) differs only by the missing phantom (Q1005).
## Untried ideas
A natural source of an emitted-nothing live range for asset (compiled-out debug macro such as an assert on asset): unverifiable from the asm.
## Evidence
- guard-free alias body (full=14): identical instruction stream except register numbers: s0 pointer, s1 i, s2 base, 3 saves (no phantom).
0x46a8 sw s1,24(sp) / 0x4730 lw s1,24(sp): s1 saved and restored but never read or written in the body (phantom live range of asset). 0x46c8 move s3,a0 (base), 0x46cc move s2,zero (i), 0x46d4 move s0,a0 (strength-reduced &asset->textures[i]); 0x4710 lbu t9,32(s3) quadCount reload; 0x4714 addiu s2,s2,1.
