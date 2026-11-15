# mapNodeAssetParse (global, src/global/55B20.c)
## Sites
- f01450 (removed): the clear loop is `for (i = 0; i < 32; i++) gMapZones[i] = NULL;`.
  - Evidence: `&gMapCellBoxes + 1` is gMapZones (0x807F70B8), and D_807F7138 is gMapZones + 0x80.
  - fdiff `--reloc-ok`: RELOC-EQUIV OK. Raw words differ only in the LO16 immediates at 0x7b44 and 0x7b48.
- 0240a2 (kept): the integer-typed slot.
## Attempts (2026-11-14, Hack55B20TypedMembers)
- **Clear loop:**

  | form | result |
  |---|---|
  | statements on separate lines | text=2 |
  | `gMapZones` / `&gMapZones[0]` bounds | text 49-50 |
  | index loop | RELOC-EQUIV OK |

- **Slot**, measured after the clear-loop fix:

  | form | text |
  |---|---|
  | typed slot, plain, void *, block-scoped | 36 (s0/s1 swap of p and slot) |
  | MapZone * snapshot | 70 |
  | s16 *p | 44 |

## Untried ideas
- Permuter on the typed-slot body with the new clear loop.
