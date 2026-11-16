# mapNodeAssetParse (global, src/global/55B20.c)
## Sites
- f01450 (removed 2026-11-14): the clear loop is `for (i = 0; i < 32; i++) gMapZones[i] = NULL;`.
  - Evidence: `&gMapCellBoxes + 1` is gMapZones (0x807F70B8), and D_807F7138 is gMapZones + 0x80.
  - fdiff `--reloc-ok`: RELOC-EQUIV OK. Raw words differ only in the LO16 immediates at 0x7b44 and 0x7b48.
- 0240a2 (removed 2026-11-16, HackmapChunksApplyLights2): the integer-typed `s32 slot` and its `MAP_ZONE_SLOT` macro are gone.
  - The fix is an `s16 *p` stream reader with one `*p++` per field: `n = *p++`, `idx = *p++`, `vertCount = *p++`,
    `height = *p++`, `exitCount = *p++`, then `p += 16` after each 0x20-byte cell copy and `p += 8` after the links.
  - Every zone access is spelled `gMapZones[idx]->...`. No slot or zone local remains. fdiff 0.
## Attempts
- **Clear loop** (2026-11-14, Hack55B20TypedMembers):

  | form | result |
  |---|---|
  | statements on separate lines | text=2 |
  | `gMapZones` / `&gMapZones[0]` bounds | text 49-50 |
  | index loop | RELOC-EQUIV OK |

- **Slot**, measured after the clear-loop fix (2026-11-14):

  | form | text |
  |---|---|
  | typed slot, plain, void *, block-scoped | 36 (s0/s1 swap of p and slot) |
  | MapZone * snapshot | 70 |
  | s16 *p | 44 |

- **Slot** (2026-11-16, HackmapChunksApplyLights2, anthropic/claude-opus-5-5:high). Bodies are typed slot unless the row says plain:

  | form | full |
  |---|---|
  | typed slot (`MapZone **slot`) | 34 |
  | permuter 900 s on the typed slot | best 0, but all 15 zeros insert `perm_refer_to_var` dead guards (`if (p && p && p) {}`, `if (!idx) {}`); see Q0695 |
  | data parameter as the cursor | 39 (s1 = data from the prologue) |
  | `zone->` for the first stores | 34 to 53 |
  | chained `*slot = zone = heapAlloc()`, no zone local, slot before heapAlloc | 34 |
  | `if (data != NULL)` wrap, while loop | 34 |
  | `s16 *p` with `p[1]` / `p[16]` reads and `p += 2` / `p += 17` advances | 34 |
  | `*p++` reads for height and exitCount only | 34 |
  | `p += 16; enterCount = *p++` only | 34 |
  | `*p++` for every field and `p += 16` / `p += 8` after the copies | 0 |
  | the same in the plain `gMapZones[idx]` spelling | 0 |
  | plain spelling without pad[2] | 2 |
  | plain spelling with pad[1] | 4 |

## Untried ideas
none (no hack site left).
## Evidence
- `uopt -l5` (try/trace5_*.txt): p is cand 18 at adjsave 60.25 in every form.
  - Base: the ucvt slot is cand 38 at 55.0, so p is coloured first into reg 14 ($s0).
  - Typed slot: the uixa slot is cand 38 at 75.0, so the slot is coloured first and takes $s0.
  - With a block split (`if (1) {}`), the uixa slot drops to 50.0.
- Final body, `uopt -l5` (try/trace5_final.txt): p is cand 18 at adjsave 75.25 and `&gMapZones[idx]` is cand 31 at 75.0. p is coloured first, so s0 = p and s1 = the slot address.
  - The separate `*p++` reads and advances raise p from 60.25 to 75.25. The merged `p[16]` / `p += 17` spelling lacks those p uses.
  - The margin is 0.25, so any edit to the walker can flip it again.
- The `p += vertCount * 6 / sizeof(s16)` advance explains the target's `srl t7,t6,1; sll t8,t7,1` at 0x7c20-0x7c24: an unsigned byte count is converted to s16 elements and scaled back to bytes.
