# textBlitGlyph (global, src/global/100180.c)
## Sites
- global:806FB490:other:ef13cf other: REMOVED (2026-11-16). `(u32)width` in the return gave the return its own width conversion, so the loop bound kept the int widening (andi t3,a0,0xff at 0x78, move a0,t3 at 0x88) and width stayed in a0.
## Attempts
- rounds 10-32 (CleanGlobal100180, Rev16B): see quality history (no (u32): width in v1; permuter only re-adds the widening).
- 2026-11-16 U HacktextDrawStringVtx5 anthropic/claude-opus-5-5:high (variants.py try full scores, tbg/):
  - plain `+ width` at the base: 49; return order respellings 49; `dst += width; return bool + dst` 50; if-forms 182; j as s32/u8/u16 83, u32 223.
  - dst/return as u32: 49.
  - dst as `u8 *` (return type `u8 *`, `dstRow = dst + pitch * 16 + pitch * row`), plain return: 0 in every operand order. Kept.
  - sheet as `u8 *` too: 1 (`addu t1,t9,a2` offset-first at 0x50, Q0813; `&sheet[i]` and `src + i` also 1). sheet stays s32 with `(u8 *)sheet`.
## Untried ideas
- none (site removed). sheet's `(u8 *)` casts and the callers' `(s32)gTextFontSheets[...]` stay (base-first addu needs the conversion on the base, Q0813).
## Evidence
- 0x4c `andi t3,a0,0xff` (width param), 0x68 `srl a0,t3,1`, 0x78 `andi t3,a0,0xff`, 0x88 `move a0,t3`: width in a0, its int widening in t3 (`blez t3` at 0x9c).
- Return: 0x268 `beqz v0` / `move a2,v0` / `move a2,v1` (phaseBit && oddBit), 0x274 `addu t7,a2,a1` (+ dst), 0x290 `addu v0,t7,a0` (+ width).
