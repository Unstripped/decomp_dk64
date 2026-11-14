# actorConfigLookup (global, src/global/8F050.c)
## Sites
- global:8068A3A0:do-while0:5c6932: REMOVED. It is an as1 line join (`i = 0; do {`), now tagged `// LAYOUT:`.
- global:8068A3A0:dead-if:fdc560 `if (actorType && actorType && actorType) {}`:
  - The dead test makes actorType candidate bit 0, so it keeps a0. Without it, actorType is bit 16, next takes a0, and actorType gets `move a2,a0`.
## Attempts
- rounds 15/16 (opus:low): diagnose/permute both (the permuter only re-adds dead uses / re-joins the line).
- 2026-11-14 U HackactorConfigLookup:
  - as1probe scan on the split copy: the only full=0 edits are the line join
  - init orders: 10; for/break: 14
  - fdc560: uopt -l 6 bit comparison
  - 10 body shapes, including early continue and one-case switch: 8-20
  - variants scan: 8
## Untried ideas
- fdc560: any natural code-free first mention of actorType before `cfg = D_80750100`. The target has no early-out, and every real use emits code.
## Evidence
- leaf; table base a3 (lui at 0x50, addiu at 0x5c)
- move v0,zero at 0x60
- stride 20 via multu
- outIndex stored in the bnel delay slot
