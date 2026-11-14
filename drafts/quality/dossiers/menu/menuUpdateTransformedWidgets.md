# menuUpdateTransformedWidgets (menu, src/menu/1AF0.c)

## Sites
- **menu:80027988:other:3285e9** (base line 1053): REMOVED.
  - Case 2's fade-out step was computed into `lineHeight`, the font-height local. Writing it to `fadeStep` swapped v1/a0 in case 1's step at 0x2240-0x2254, because the shared `fadeStep` web took a0.

## Attempts
**2026-11-14 U HackmenuUpdateTransformedWidgets.** `variants.py try`, function scores (full):

| Variant | full |
|---|---|
| direct2: case 2 `widget->alpha -= (alpha > 0x10) ? 0x10 : alpha` | 0 |
| bothdirect: both cases direct, fadeStep deleted | 0 (kept) |
| fade2: fadeStep in case 2, also with decl swap, `>= 0x11`, if/else | 5 |
| fade2 with u8 fadeStep | 6 |
| MIN direct | 7 |
| MIN / `<` into fadeStep | 12 |
| fadeStep declared first | 48 |
| block-scoped `s32 step` per case | 49 |
| block-scoped `u8 step` | 50 |

## Untried ideas
- none left; the site is gone.

## Evidence
**Target 0x2234-0x2280:**
- Case 1: `lbu v0,8(t1)`; `subu v1,t6,v0`; the clamp result is in a0 (`move a0,v1` / `li a0,16`); `addu t7,v0,a0`; `sb`.
- Case 2: the clamp result is in v1 (`move v1,v0` / `li v1,16`).

**Mechanism:** with no named step local in either case, uopt colours each case's expression temp independently and reproduces a0 in case 1 and v1 in case 2.
