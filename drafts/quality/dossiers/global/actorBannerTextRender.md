# actorBannerTextRender (global, src/global/A2F10.c)

## Sites
- 0c76ca: `switch (sel ^ 0)`. KEPT.
  - The target dispatches on a v0 copy of sel (`move v0,a3` in the blez delay slot) while blez and the case bodies use a3.

## Attempts
- 2026-11-14 U HackactorBannerTextRender: selector casts and widths, field selector, extra local, line joins, as1probe scan; see the ledger for line counts.
  - Nearest form: `(u8)sel` at 2 lines, where blez uses v0 instead of a3.

## Untried ideas
- None found natural.

## Evidence
- Target 0x1948 `lbu a3,351(t8)`; 0x1950 `blez a3`; 0x1954 `move v0,a3`; 0x1958 `addiu t9,v0,-30`.
