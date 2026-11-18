# menuDrawBlinkingPromptText (global, src/global/117190.c)

## Sites
global:807135B4:dead-if:dc3c6c dead-if (FIXED 2026-11-17): `if (&D_80755370 && &D_80755370 && &D_80755370) {}` at the
head of the post-early-return block ($33). ugen emitted `beq $4,0,$34` (conditional jump-to-next) as the first record
of $33; as1's branch-likely conversion cannot copy a branch into the delay slot, so the state check after
`lw t5,gCurrentMap` stayed `bne t5,at,0x11dc; nop` (0x11cc). Without it as1 emitted `bnel t5,at` with
`lwc1 $f16,52(sp)` (x reload, first instruction of 0x11dc) in the slot. It stood in for `textIndex = 1;` written as
its own statement after the early-return test (see Attempts 2026-11-17).

## Attempts
2026-11-15 menuDrawBlinkingPromptText HackmenuDrawBlinkingPromptText anthropic/claude-opus-5-5:high:
- as1probe try on the FAKE's t.G: deleting both hoisted `la $4,D_80755370` (records 57, 68) keeps full 0;
  deleting only the `beq $4,0,$34` (record 80) gives full 2. The block-head conditional branch alone is the steer.
- as1probe scan of the guard-less body (977 single edits incl. noop/bnext/alias/label/live): 0 improve.
- Local aggregate initialiser (Q0802): block-scoped `TextIdPair textIds = D_80755370;` with textIndex at
  function scope and/or x/y block-scoped (4 orderings) -> fdiff 2 (only the bnel); textIds first in a block
  that also declares textIndex/x/y -> 6..13 (slots move: block locals are allocated after function-scope
  ones); copy declared after x/y -> 59; function-scope initialiser (copy before the elapsed test) -> 56.
- Real initialiser `{ 3, 23 }` (block scope): text identical to the D_80755370 copy (same bnel), reloc 2
  (.data instead of D_80755370); no text gain, so no carve request.
- Early-return test: separate statements / if-else / else-if / single-case switch on gCurrentMap / switch on
  menuIsTransitionType3Or4() -> 5 (two return blocks, beqz->bnez); negated condition around the draw
  (`if (!(...)) {draw}` and De Morgan) -> 9 (beql to the shared epilogue); ternary forms 32/55;
  `if (...) return dl; else {draw}` -> 2.
- x spellings `(f32)(0.5 * (f64)x)`, `0.5 * x`, `x *= 0.5`, `x = x * 0.5`, `x / 2.0` -> 2 (uopt
  canonicalises; $33 still starts with `l.s $f16,52($sp)`).
- Dead stores inside an `if` (`if (textIndex != 0) { elapsed = 0; }`, `if (dl != NULL) { elapsed = 1; }`) and
  nested empty ifs at the site: uopt removes the whole test -> 2 (no surviving block-head branch).
- permute (905 s, from the block-scoped initialiser body, base 400): every zero is the same triple dead test
  on `dl`/`!dl`/`!textIndex` at the site: steer swap, rejected.
- review: dropped no-op casts (`x = x * 0.5`, `(s16)` without `(s32)` twice, `(s32)` on the s32 id); fdiff 0;
  FAKE removal re-measured after it: still 2.
2026-11-17 2026-11-17: cleanup CleanmenuDrawBlinkingPromptText CleanmenuDrawBlinkingPromptText anthropic/claude-opus-5-5:
- sweep re-run at the base (remove/cond/classify/recipe): no hit (class 2).
- FIX: `if (gControllerConnectedMask != 0) { if ((menuIsTransitionType3Or4() == 0) || (gCurrentMap == 0x4C)) { return dl; }
  textIndex = 1; }` (assignment after the map test, no comma) -> whole-object fdiff 0 without the dead test.
- as1probe swap on the guard-less t.G: `li.d $f4,0.5` moved ahead of `l.s $f16,52($sp)` at the head of the draw
  block -> still bnel + lwc1 (as1 schedules the target block before choosing the likely-slot copy; a multi-record
  macro as the first record does not block it).
- nested ifs with `textIndex = 1;` before the map test -> 5; inner `if (...) {textIndex = 1; if (map) return;} else
  return;` -> 4; else-if textIndex selection (`== 0` / `else if (... && map != 0x4C) textIndex = 1; else return`) -> 10,
  inner if/else selection -> 5; bare truth tests with the comma -> 2.
- review: dropped 5 redundant conversion casts (fdiff 0); permuter run from the guard-less body cancelled once fixed.

## Untried ideas
- none: the function has no hack site left.

## Evidence
- target 0x11b8 `beqz v0,0x11d4`; 0x11c0 `lw t5,gCurrentMap`; 0x11c4 `li at,76`; 0x11c8 `li v1,1`;
  0x11cc `bne t5,at,0x11dc`; 0x11d0 `nop`; 0x11d4 `b 0x12b8; move v0,s0`; 0x11dc `lwc1 $f16,52(sp)`.
- fixed ugen: `beq $2,0,$32; lw $13,gCurrentMap; bne $13,76,$33; $32: move $2,$16; b $36; $33: li $3,1; $34: l.s ...`;
  as1 hoists `li $3,1` (one-predecessor $33, v1 dead on $32) into the lw stall, leaving the bne target empty.
- Stack: textIds 56(sp), textIndex 64(sp) (sw zero / reload into v1 around textGetFontHeight), x 52, y 48.
