# mpDrawPlayerViewportHud (multiplayer, src/multiplayer/0.c)
## Sites
- multiplayer:80024CA4:other:348fe0 `Gfx *gfx2`: FIXED.
  - The reset packet is now `gDPSetColor(curGlist++, G_SETPRIMCOLOR, (alpha & 0xFF) | 0xFFFFFF00)`.
  - The macro's block `_g` takes gfx2's slot.
- multiplayer:80024CA4:other:d23002 w1-before-w0 stores: FIXED as a `// LAYOUT:` line join.
  - Evidence: as1probe `delete .loc` -> full=0.
## Attempts
- round 22/30 (opus): diagnose, permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - all-gDPSetPrimColor: 13 (stack shift by 4)
  - gDPSetPrimColor on a single packet: 79-90 (breaks the alpha & 0xFF CSE)
  - gDPSetColor reset packet: 0 (applied)
  - w0-first on two lines: 2
  - w0-first on one line: 0 (applied)
## Evidence
- copy.diff
