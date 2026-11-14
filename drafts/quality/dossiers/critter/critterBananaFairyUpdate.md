# critterBananaFairyUpdate (critter, src/critter/3340.c)
## Sites
- critter:80027448:other:29956a: RESOLVED as ORIG. The case-10 empty `if (func_806FB418() < requiredCount) {}` is code the target executes.
## Attempts
- rounds 22-23 (opus:low): remove / cond / classify / diagnose / permute (600 s); see history.
- 2026-11-14 U HackcritterBananaFairyUpdate opus:high (variants.py try full=):
  - empty `{} else {}`: 0; empty `;`: 0
  - count local shared with case 0: 61
  - call only: 86
## Untried ideas
- none: the construct is ORIG.
## Evidence
- 0x5ec `jal func_806FB418`, with `sb zero,341(t4)` (unk155 = 0) in the delay slot
- 0x5f4 `lw t5,100(sp)` (requiredCount)
- 0x5f8 `slt at,v0,t5`
- 0x5fc `beqz at,0x994` and 0x604 `b 0x994`: both arms go to the case merge
