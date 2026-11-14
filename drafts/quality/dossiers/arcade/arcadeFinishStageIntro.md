# arcadeFinishStageIntro (arcade, src/arcade/0.c)
## Sites
- arcade:800257D8:other:3593b5 / 44f5dd: REMOVED. The offset-symbol walk (D_8004BCD4 - 4 .. D_8004C6D4 - 4) is now `for (i = 0; i < 80; i++) D_8004BCD0[i].type = 0;`.
## Attempts
- 2026-11-14 U HackarcadeUpdateDonkeyKongStage1 opus:high (variants.py try full=):
  - index loop: 1 (reloc only; RELOC-EQUIV OK)
  - `i != 80`: 3; `i < 80U`: 10
  - pointer for / do-while to &D_8004BCD0[80]: 21-22
  - pointer to &D_8004C6D0: 22-48
## Evidence
- Target 0x17dc-0x1810: v0 = 0x8004BCD0, v1 = 0x8004C6D0; `addiu v0,v0,32` / `sltu` / `bnez`, with `sb zero,-8(v0)` in the delay slot.
- Raw words equal except the LO16 immediates (-4 vs 0 / 0xa00), which resolve to the same addresses.
