# arcadeDrawStage3Background (arcade, src/arcade/0.c)
## Sites
- arcade:800275E8:other:1489cd (kept): the `(s32)` end pointer keeps `addiu s1,s0,84` (end derived from the walker, 0x3884).
## Attempts
- 2026-11-14 opus:high (full=):
  - sized extern [21] with sizeof bound: 18; for walker: 20
  - index loops: 21-22
  - end local in the pad slot: 18-20
- 2026-11-16 U HackarcadeUpdateBouncingBarrel2 opus:high (full=):
  - `!=` ends: `(s32)` + `!=` 2; `pt != D_8004A7C8 + 21` (do / while / for) 5: end recomputed inside the loop as `addiu t8,s1,0x54` off the CSE'd lda in s1
  - `<` ends `D_8004A7C8 + 21` / `&[21]` / mirrored `>` 16-18; `<= + 20` 18-20; `(u8 *)` byte offset 18; pointer difference `pt - D_8004A7C8 < 21` 18
  - counted i loop + `pt++` 21 (counter kept, `slti s2,0x15`, no LFTR onto pt); counted j loop 166; `(u32)` round trip 0 (same steer)
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawStage4Background2 HackarcadeDrawStage4Background2 anthropic/claude-opus-5-5:
  - index loop `for (i = 0; i < 21; i++)` over `D_8004A7C8[i]` (the lift loop's `i = 0` is a later definition, so the exit keeps `sltu`) + `s32 pad2` after glist (frame 0xa0 kept): 20 (text 16): LFTR end `lui s1,%hi / addiu s1,s1,%lo(D_8004A7C8+0x54)`
  - `pt = &D_8004A7C8[i]` in that index loop 20; counter i + `pt++` 21
  - D_8004A7C8 defined in this TU (0x26790 .data carve copy, see arcadeDrawHud): `&D_8004A7C8[sizeof / sizeof]` still folds to `%lo(D_8004A7C8+0x54)`
  - the outer `(s32)` casts on the s16 rectangle args are not needed (implicit conversion, fdiff 0): dropped
## Untried ideas
- none left from the local asm: every compile-time end folds (Q0811), LFTR-built ends too (they fold the IV's constant init); a non-constant natural end (a table length read from data) has no counterpart in the target.
## Evidence
- target: `lui t8,%hi(D_8004A7C8)` / `addiu s0,t8,%lo` at 0x387c/0x3880, `addiu s1,s0,84` at 0x3884, `sltu at,s0,s1` at 0x38a0.
- first j loop keeps `slti at,s0,160` (0x3770: the second loop redefines j), the second has `li s1,160; bnel s0,s1` (0x37d4).
- D_8004A7C8: 21 x 4 bytes, next label D_8004A81C.
- `<` ends are hoisted as loop invariants and fold to `addiu s1,%lo(D_8004A7C8+0x54)`; `!=` ends stay in the loop but keep the base + 0x54 add (lda shared in s1).
