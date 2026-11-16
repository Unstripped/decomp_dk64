# modelSlotFreeAssetTextures (global, src/global/36880.c)
## Sites
global:80636210:dead-if:208f26 dead-if `if (base) {}` (copy-propagated to a ucg1 of asset): with the triple guard it lifts asset (uopt bit 5) above i (bit 13) so asset takes s1 and i s2; alone neither guard does it (i s1, asset s2).
global:80636210:dead-if:d53555 dead-if `if (base && base && base) {}`: same mechanism, three more ucg1 uses of asset inside the second free.
`base = asset;` (copy-only, tagged 2026-11-15) other: redundant alias of the parameter; base (bit 10) is the s3 candidate that carries quadCount (lbu 32(s3)); without it (guards on asset) full=16.
## Attempts
2026-11-15 HackmodelSlotReplaceSegment6Commands anthropic/claude-opus-5-5:high: void **p walk (p[9]/p[13]) -> for loop over asset->textures[i]/asset->palettes[i] with guards kept -> fdiff 0 (applied; cast retired). Same with base->textures[i] -> 8.
2026-11-15 same: single guard grid (positions loop top, before palettes load, inside each free, after loop/after loop body; 1-4 uses; on asset or base) on both the do-while and for forms -> best 3 (i s1 / phantom s2); f2 merged 4-use guard 5, 5-use 7.
2026-11-15 same: guard-free natural forms: array-indexed for/do-while without base (h1-h4) 19, base for condition + asset indexed (m1/m4) 14, base assigned before the type test (o1/o2) 19, precheck on asset (o3) 14, p from base (o4) 14, statement order (o5/o6) 15, NULL/!= 0 spellings (o7) 15; variants scan on the guard-free copy: best 14.
## Untried ideas
A natural source of an emitted-nothing live range for asset (compiled-out debug macro such as an assert on asset): unverifiable from the asm.
## Evidence
0x46a8 sw s1,24(sp) / 0x4730 lw s1,24(sp): s1 saved and restored but never read or written in the body (phantom live range of asset). 0x46c8 move s3,a0 (base), 0x46cc move s2,zero (i), 0x46d4 move s0,a0 (strength-reduced &asset->textures[i]); 0x4710 lbu t9,32(s3) quadCount reload; 0x4714 addiu s2,s2,1.
