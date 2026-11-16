# heapRegisterSurvivor (global, src/global/15050.c)
## Sites
- 6c7f1e other: `if (1) { ... }` around the body after `b = b - 1`.
  - It is a block split: the handle param (cand 2) spans two blocks, so its adjsave drops 2.0 -> 1.0.
  - &gHeapSurvivorCount (cand 19, 2.0) is then coloured first and takes a0. The handle moves to a1 (target 0x1264-0x1270).
  - Without the block both candidates are 2.0, and the param wins the lowest-bit tie: handle stays in a0 and &count takes a1.
## Attempts
- 2026-11-10..14 rounds 6/19/24/36 (low, unlevelled, xhigh): uopt traces and permuter runs. best=0 only through steer swaps (do-while(0), if (!handle) {}, copy temps).
- 2026-11-16 cleanup HackloadOverlay2 anthropic/claude-opus-5-5:high, scored with variants.py try (full=):
  - plain removal: 11
  - `if (1) {}` position sweep: 0 only after `b = *handle` or `b = b - 1`, before the tag store. Every other position: 7-12.
  - one-line b: 6
  - initialised b: 6
  - `b = (HeapBlock *)(*handle - 0x10)`: 6
  - `&((HeapBlock *)*handle)[-1]`: 6
  - `u8 *b` with `b -= 0x10`: 11
  - `u8 *b = *handle - 0x10`: 6
  - `u8 *ptr` with `ptr[-5]`: 8
  - `(*handle)[-5]`: 14
  - list store with post- or pre-increment: 11
  - count local n: 6
  - `if (b != NULL)`: 15
  - `if (handle) {}`: 12
  - b decrement after the tag store, or at the end: 8
## Untried ideas
- A natural second block between the *handle load and the tag store. Nothing in the target asm shows one (straight-line code up to the 0x20 test).
- A `void **` or `HeapBlock **` handle parameter. This needs a prototype bundle across the callers.
## Evidence
- target 0x1258-0x12c0:
  - `lw v1,0(a0)` and `move a1,a0` at 0x1260/0x1264
  - `lui/addiu a0,gHeapSurvivorCount` at 0x1268/0x1270
  - `sb t6,-5(v1)` at 0x1274
  - a dead `addiu v1,v1,-16` (b) at 0x1280
- traces: .scratch/HackloadOverlay2/tr5_hr_keep.txt and tr5_hr_oneline.txt
