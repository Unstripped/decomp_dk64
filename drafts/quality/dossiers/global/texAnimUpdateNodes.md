# texAnimUpdateNodes (global, src/global/36880.c)
## Sites
global:80639968:other:a3e028 other: function-scope `s32 *dst` holding &texCmd->tileSizeW0 for both 0xF2000000 (G_SETTILESIZE w0) stores; v0 holds the address (addiu v0,v0,0x30) and the store is sw t9,0(v0) / sw t2,0(v0). Now `// ORIG` (removed as a site).
## Attempts
2026-11-11 Rev10C claude-opus-5-5:xhigh: diagnose dst = isvar coloured v0; permute without dst best 645 -> nohit
2026-11-11 Rev16E claude-opus-5-5:low: direct node->cmdsA[i].texCmd->tileSizeW0 stores, 167 vs 168 insns; permute best 645 -> nohit
2026-11-11 Rev17M claude-opus-5-5:low: direct stores, index lbu t1 vs t0, second store recomputes multu/addu; permute best 645 (mask steer) -> nohit
2026-11-13 CleanGlobal36880 claude-opus-5-5:xhigh: permP16 direct stores, dl-object locals vT1-vT7 best full=4 -> nohit
2026-11-14 HacktexAnimUpdateNodes claude-opus-5-5:high: variants scan (47 variants, no new zero beyond baseline); block-scoped `s32 *dst` per branch (with/without initialiser) full=18; `*&...->tileSizeW0 =` full=105; `((s32 *)texCmd)[12] =` full=105; value temp `w0` + field store full=24; no `pad` full=16 (pad is frame size). Diagnosis: the address materialisation is the original object behaviour -> FAKE replaced by `// ORIG` citing 0x7eb8/0x7f18; fdiff 0.
## Untried ideas
Retype TexImageCmdSpan as a Gfx command array (Gfx[0] G_SETTIMG w1 = texAddr at 0x4, Gfx[6] G_SETTILESIZE w0 at 0x30) with a GBI-macro-shaped `Gfx *` pointer (file-scope change, touches dlFindTextureCommands/dlResolveNodeTextures casts) (this unit)
## Evidence
0x7eb8 addiu v0,v0,48; 0x7ebc sw t9,0(v0) (cmdsA); 0x7f18 addiu v0,v0,48; 0x7f1c sw t2,0(v0) (cmdsB). Every field-store spelling folds 0x30 into `sw x,48(v0)` (one instruction fewer per store).
gGfxBufferIndex*12 uses multu with s2=12 in the texCmd blocks and sll/subu/sll in the dualTex blocks (0x7fcc-0x8024).
Frame 0x68 needs `s32 pad` (without: full=16).
