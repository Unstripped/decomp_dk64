# modelAnimEntryQueueMatrixCopies (global, src/global/54150.c)
## Sites
- global:8064FA7C:dead-if:02baa4 `if (!p) {}`: its own short live range (LR8) takes uopt reg 1 ($v0) in the prologue. That pushes the gGfxBufferIndex load (LR19) to $v1 and the D_807F6BE0/E4 address temps to a2/a3.
## Attempts
- rounds 7/11 (opus:low): two dead gGfxBufferIndex tests merged into this one by the permuter; remove/cond/classify/diagnose/permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - 288-body structural grid: 10 at best
  - snapshot-local grid: 10 at best
  - snapshot for the ^1 index only: 2 (a mixed spelling, a steer)
## Untried ideas
- a natural value with a short prologue live range that takes $v0 before the gGfxBufferIndex load (the target's v0 is only the loop's matrix offset load)
## Evidence
- target 0x630-0x6a0: lui/lbu v1 gGfxBufferIndex, xori t9,v1,1
- a2/a3 hold the global addresses
- blez entry guard on matrixCount (0x6b8)
- p in s0 = node + 60
