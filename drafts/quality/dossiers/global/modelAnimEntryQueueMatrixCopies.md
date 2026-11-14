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

## Attempts (HackmodelAnimEntryQueueMatrixCopies2, anthropic/claude-opus-5-5:high, after the ModelAnimEntry retype 52539211)
- 72-body grid: p as u8/u32/s32 *, p's first assignment (before stride / after stride / after the bases), while vs for, bases as u32 or u8 * locals with the cast only at the global stores, dst temp or none. All full=10.
- 48-body grid: a named u32 offset local (first/last/none), base+offset vs offset+base, p via node + 1 or sizeof(ModelAnimNodeHeader), p in the for header. Best 10.
- NULL/0 initialisers (Q0199) on p/node/dst/srcBase/dstBase/stride, singly and in pairs; early return on matrixCount == 0; guarded do-while. All 10.

## Evidence
- The 10 differing words are all in the prologue:
  - gGfxBufferIndex `lbu` in v1 (target) vs v0 at 0x630/0x65c/0x678;
  - the D_807F6BE0/E4 address temps in a2/a3 (target) vs v1/a2 at 0x670-0x6a0.
- The loop (0x6bc-0x6ec) matches in every variant. The dead `!p` test's extra block (Q0523) gives an early short range v0, which pushes gGfxBufferIndex to v1.

## Untried ideas
- A natural statement that adds one prologue basic block without a dead test. None found: guards, early returns and do-while guards all compile to the same blocks as the plain loop.
