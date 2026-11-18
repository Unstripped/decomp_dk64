# mapChunksApplyLights (global, src/global/55B20.c)
## Sites
global:80655410:other:3304af other: `(Vtx *)(s32)gMapChunks[i].litVtx[gGfxBufferIndex]` as lightApplyToVertices' first argument. The ucvt keeps the shared litVtx load at 0x4be4 in v0 (`lw v0,0x60(t9)`), so the target emits `move a0,v0` at 0x4c0c and `addu a1,t1,v0` at 0x4c14. Without the conversion, uopt coalesces the temp into a0 (Q1023). (Earlier key 7b1ec5 before the obj -> lightCount rename.)
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
2026-11-16 HackmapChunksApplyLights2 anthropic/claude-opus-5-5:high: (u32) on both arguments `(Vtx *)(u32)litVtx, (Vtx *)((u32)litVtx + vtxSize)` -> 0. It is the same first-argument round trip, so not kept
2026-11-16 HackmapChunksApplyLights2: (u32) or (s32) on the end argument only, plain first argument -> 3; u32/s32 addr local, block- or function-scoped -> 39
2026-11-17 CleanmapChunksApplyLights anthropic/claude-opus-5-5: read 61690.s (handwritten): start/end compared with signed `slt a0,a1` (0x61714), stepped by `stride << 4` bytes (0x61700, 0x61A44 `addu a0,a0,a2`), Vtx fields at 0/2/4 and 0xC-0xE.
2026-11-17 CleanmapChunksApplyLights: integer prototype `(s32|u32 start, s32|u32 end, ...)` measured with a renamed-symbol stand-in (text only) on all three callers:
  - arm `((T)litVtx, (T)litVtx + vtxSize)` -> text 3 (the shared (T)litVtx cvt coalesces into a0 again: lw a0,0x60(t9) / no move / addu a1,t1,a0); `(T)(vtxSize + (u8 *)litVtx)` -> text 1
  - arm `((T)litVtx, (T)((u8 *)litVtx + vtxSize))` with cell call `((T)cellVtx, (T)(cellVtx + vtxCount[j]))` -> text 0 (s32 and u32)
  - 63EC0 effectWaterApplyLights `((s32)vtxBuffer, (s32)(vtxBuffer + node->vtxCount))` -> text 0
  - real shadow header (include/ copy with render.h `s32 start, s32 end`, make's compile with `-I include` swapped): 55B20 stand-in objdiff OK, 63EC0 stand-in objdiff OK; cfe warnings 0 -> 0 (55B20), 1 -> 1 (63EC0, pre-existing W709 line 255)
  -> header request (render.h.patch), FAKE removable once it lands
2026-11-17 CleanmapChunksApplyLights: uopt -l 6: cand 167 (uilod of litVtx[gGfxBufferIndex]) is reg 1 ($v0) with the ucvt (cand 168), reg 3 ($a0) without
2026-11-17 CleanmapChunksApplyLights: variants.py scan of the plain copy: 97 variants, best 3 (= baseline)
2026-11-17 CleanmapChunksApplyLights: permuter 900 s from the plain body, hack-free weights: setup baseline 117 (permuter base 110), no output below it (about 26k iterations)
## Untried ideas
none: the remaining fix is the integer prototype header request (header-request.md); under the Vtx * prototype only a pointer<->integer round trip on the first argument separates the litVtx temp (Q1023).
## Evidence
0x4be4 lw v0,0x60(t9) (litVtx[gGfxBufferIndex]); 0x4be8 lw t1,0x5c(s2) (vtxSize); 0x4c0c move a0,v0; 0x4c14 addu a1,t1,v0 (delay slot of jal lightApplyToVertices).
Cell path 0x498c lw a0,0x14(t5) / 0x49f0 sll t7,t6,0x4 / 0x4a0c addu a1,t7,a0: a plain Vtx * argument coalesces into a0 there; `(s32)cellVtx, (s32)(cellVtx + n)` keeps it (cellVtx is a variable preferenced to a0, the no-op cvt changes nothing).
mapChunkFreeIdleBuffers 0x4d58: target loads litVtx straight into a0 for heapFree, so the field is a pointer.
Callee asm/global/61690.s (handwritten, 0x8065C990): 0x61700 sll a2,a2,4; 0x61714 slt at,a0,a1 (signed compare of start/end, a C pointer compare would be sltu); 0x61730-0x61738 lh 0/2/4(a0); 0x61994.. lbu/sb 0xC-0xE(a0); 0x61A44 addu a0,a0,a2.
