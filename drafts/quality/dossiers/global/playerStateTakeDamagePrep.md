# playerStateTakeDamagePrep (global, src/global/EFDC0.c)
## Sites
- global:806EB744:dead-if:398172 `if (gPlayerSlots && gPlayerSlots) {}`: its live range colours ahead of type/speed. Without it:
  - type v1 (target v0)
  - speed a1 (target v1)
  - 8 r at 0x6a8-0x6d8
## Attempts
- CleanEFDC0 (opus:low): remove/cond/classify/diagnose; permute 0 only via a do-while(0).
- 2026-11-14 U, scored with variants.py try (full=):
  - extra blocks: speed `?:` 91, if/else 21, one-case switch on type/kind 8
  - declaration orders: 8-11
  - widths: 8
  - camActor reuse: worse
  - slot pointer early 101, late 69
  - scan of the plain removal: 8
## Untried ideas
- an unrelated early read of gPlayerSlots (e.g. the slot fields read before the camera block)
## Evidence
- try/trace_base.txt, try/trace_plain.txt (uopt -l 6)
- try/plain.diff
