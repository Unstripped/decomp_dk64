# textGetCharAdvance (global, src/global/100180.c)
## Sites
- global:806FD7A8:other:67d8c8 other: REMOVED (2026-11-16). `f = font;` s32 copy kept the extended font in a2 (sll a2,a0,0x10 at 0x2328) apart from the a0 argument, with the call re-extension sll a0,a2,16/sra t6,a0,16 at 0x23a4.
## Attempts
- rounds 10-16 (CleanGlobal100180, Rev16B/D/I): see quality history (s32 f copy, font ^ 0 / (s32)font in the call, dead store info= hoist).
- 2026-11-16 U HacktextDrawStringVtx5 anthropic/claude-opus-5-5:high (variants.py try full scores, gca/v1..v6):
  - v1 `font ^= 0x80; info = &gTextFonts[font]; advance = info->fixedWidth;`: 9.
  - v2 `info = &gTextFonts[(s16)(font ^ 0x80)]` without reassigning font: 37.
  - v3/v5 `font ^= 0x80; advance = gTextFonts[font].fixedWidth; info = &gTextFonts[font];` (v5: the same advance-then-info order in all three branches): 0, fdiff 0. Kept v5.
  - v4/v6 `return advance + info->spacing;`: 40.
## Untried ideas
- none (site removed).
## Evidence
- Entry: sll a2,a0,0x10; sra t6,a2,0x10; ... move a2,t6 (delay slot of beqz t7 at 0x2344).
- 0x80 branch: xori t8,t6,0x80; sll/sra (font ^= 0x80 truncation) at 0x234c-0x2354; lbu v1,5(a0) fixedWidth.
- Call branch: sll a0,a2,0x10; sra t6,a0,0x10; move a0,t6 at 0x23a4-0x23ac; font saved with sh a2,26(sp) in the jal delay slot, reloaded lh a2,26(sp) at 0x23bc.
