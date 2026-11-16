# mapChunksApplyLights (global, src/global/55B20.c)
## Sites
global:80655410:other:7b1ec5 (final copy key 3304af after the obj -> lightCount rename) other: `(Vtx *)(s32)gMapChunks[i].litVtx[gGfxBufferIndex]` as lightApplyToVertices' first argument. The ucvt keeps the shared litVtx load at 0x4be4 in v0 (`lw v0,0x60(t9)`), so the target emits `move a0,v0` at 0x4c0c and `addu a1,t1,v0` at 0x4c14. Without the conversion, uopt coalesces the temp into a0.
## Attempts
2026-11-09..14 Clean55B20/CleanGlobal55B20/Rev10E/Rev16H/Rev17M/OwnerAsmLightProjProto: void * args, truthful Vtx * prototype, plain litVtx, (Vtx *)litVtx, block-scoped Vtx */u8 */s32 snapshot, + vtxSize / 16, permuter 600 s x3 -> fdiff 1 each (see history)
2026-11-15 HackmapChunksApplyLights anthropic/claude-opus-5-5:high: plain call (no casts) -> 3 rows (lw a0 / no move / addu a1,t1,a0)
2026-11-15 HackmapChunksApplyLights: Vtx *vtx declared LAST at function scope, assigned inside the 0x10 arm, end (u8 *)vtx + size or size + (u8 *)vtx -> 39 (same a0 coalescing, block shift)
2026-11-15 HackmapChunksApplyLights: same local assigned before the 0x10 test (FCCD0 contrast) -> 189
2026-11-15 HackmapChunksApplyLights: block-scoped Vtx *vtx / u8 *vtx, both end orders -> 39; block-scoped start+end pair -> 31; function-scope start+end declared last -> 31; end-first local -> 39; s32 size local -> 50
2026-11-15 HackmapChunksApplyLights: cellVtx reuse -> 3; src reuse (u8 *) -> 19; &((u8 *)litVtx)[vtxSize] -> 3; (Vtx *)litVtx first -> 3; size + (u8 *)litVtx -> 3
2026-11-15 HackmapChunksApplyLights: field retype u8 *litVtx[2] with (Vtx *)litVtx / (Vtx *)(litVtx + size) -> same 3 rows; u32 litVtx[2] (diagnostic only) -> this function matches but mapChunkFreeIdleBuffers' heapFree gains lw v0 + move a0,v0 (0x4d58/0x4d68)
2026-11-15 HackmapChunksApplyLights: variants.py scan of the plain form -> 97 variants, best 3 (= baseline)
2026-11-15 HackmapChunksApplyLights: names: obj -> lightCount (fdiff 0)
## Untried ideas
none with evidence. The target needs a ucvt on exactly this one use of the litVtx value, and only pointer<->integer conversions supply it. Field-level integer typing is ruled out by mapChunkFreeIdleBuffers.
## Evidence
0x4be4 lw v0,0x60(t9) (litVtx[gGfxBufferIndex]); 0x4be8 lw t1,0x5c(s2) (vtxSize); 0x4c0c move a0,v0; 0x4c14 addu a1,t1,v0 (delay slot of jal lightApplyToVertices).
Cell path 0x498c lw a0,0x14(t5) / 0x4a0c addu a1,t7,a0: a plain Vtx * argument coalesces into a0 there, as the target expects.
mapChunkFreeIdleBuffers 0x4d58: target loads litVtx straight into a0 for heapFree, so the field is a pointer.
