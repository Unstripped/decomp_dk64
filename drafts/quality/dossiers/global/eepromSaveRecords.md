# eepromSaveRecords (global, src/global/104F0.c)
## Sites (all kept)
- 77df56: the laundered q makes the first poll test a full la + lbu 0(t2) (0x1dcc-0x1dd4) instead of a folded lbu %lo.
- 6b7e71: dead `a` test in the CRC loop (colouring of the narrowed index temp).
- 575291: dead `offset = 0` keeps b a variable for the CRC slot index.
- 081ad7: dead D_807ECEA0 read across osWritebackDCacheAll.
- a1ca65: dead unsigned -64 use keeps `li at,-64` uncoloured.
- 3c3a54: dead read of sector keeps the variable in s1 above its widening in s4 (`move s4,s1` at 0x1dc8).
## Attempts
- rounds 5/13 (opus:low): per-site diagnose/permute, all-removed, two reconstructs; see history.
- 2026-11-14 U HackeepromSaveRecords opus:high (variants.py try full=):
  - poll as while/for, or an if on the global plus do-while: 39 (only the folded first read differs)
  - p moved next to the poll: 220-223
  - CRC loop with a running offset: 245/247
  - a/b order: 173
  - offset = 0 removed: 125
  - size local: 149-267
  - single removals: 081ad7 46, a1ca65 118, 3c3a54 117
## Untried ideas
- A real type for D_807ECD08 that makes the first poll read an unfolded address: it is declared `u8 []` here; a pointer-typed extern would change every use.
## Evidence
- See the offsets above. The target loop reloads p from 92(sp) into s0 (0x1de8).
