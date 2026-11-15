# arcadeInsertHighScore (arcade, src/arcade/0.c)

## Sites
- e03dfc, 2190b9, 718d93, 286c69, 2190b9#2: REMOVED 2026-11-15 (HackarcadeInsertHighScore2). They emulated a memory-resident
  byte at sp+0xC (u16[2] address-taken array + `[i % 1]` reads + dead guards placing its single reload).
- Remaining: one `// LAYOUT` (fill loop body on the `for` line): as1 line order puts `sb a0,0(v1)` before `bne` and
  `addiu v1,v1,1` in the delay slot (0xaf0-0xaf8); multi-line for/while/do forms give `addiu v1; bne; sb a0,-1(v1)` (full=2).
  `for (i = 0; i < 3;) { D_8004A778[rank][i++] = ...; }` also matches without joining (same line-order steer, untagged).

## Attempts
- 2026-11-14 U HackarcadeInsertHighScore: aggregate and row-pointer forms 38-45. Invariant variable index 13 (still a steer).
- 2026-11-15 HackarcadeInsertHighScore2 anthropic/claude-opus-5-5:high: natural u8/s32 local 43; constant-index local
  arrays u8[1..4], char[4], 1-byte struct field 43 (uopt promotes them); `u8 initial[1] = {' '}` 4 (only the .data reloc
  and fill-loop order differ); struct copy `Blank b = *(Blank *)&D_8004A794` 2; + one-line fill for -> 0; final:
  `extern ArcadeBlankInitial D_8004A794; ArcadeBlankInitial blank = D_8004A794;` fdiff OK, 0 FAKE.

## Untried ideas
- Remove the LAYOUT: only line-order spellings found (one-line for, `i++` in the subscript of a for without increment).

## Evidence
- 0xa54/0xa68 `lbu t6; sb t6,12(sp)` at entry; a single reload `lbu a0,12(sp)` at 0xae0 before the fill loop.
- D_8004A794 in asm/arcade/data/0.data.s is `.byte 0x20` + 3 zero pad bytes, between D_8004A790 (arcadeMain data) and
  D_8004A798 (ArcadeTitleBitmap, the template a later function copies into `titleBitmap`): compiler-emitted templates of
  local aggregate initialisers in function order. A `umov` block copy keeps the local a non-candidate memory var (Q0802).
