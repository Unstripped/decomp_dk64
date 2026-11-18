# arcadeDrawStage3Background (arcade, src/arcade/0.c)
## Sites
- arcade:800275E8:other:e89353 (was 1489cd): kept // FAKE 2026-11-17 (CleanarcadeDrawHud, lead ruling Q0816): `count = sizeof(D_8004A7C8) / sizeof(D_8004A7C8[0]);`
  (Q0780 ARRAY_COUNT bound local, data-proven length) and `for (pt = D_8004A7C8; pt < D_8004A7C8 + count; pt++)` keep the
  end derived from the walker (`addiu s1,s0,84`, 0x3884); `count` takes the old `pad[1]` slot. Was: `(s32)` end pointer.
  A constant-valued local whose assignment position steers (initialised at its declaration: 69), so a steer per SKILL §5.6.
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
  - index loop `for (i = 0; i < 21; i++)` over `D_8004A7C8[i]` + `s32 pad2` after glist (frame 0xa0 kept): 20 (text 16): LFTR end `lui s1,%hi / addiu s1,s1,%lo(D_8004A7C8+0x54)`
  - `pt = &D_8004A7C8[i]` in that index loop 20; counter i + `pt++` 21
  - D_8004A7C8 defined in this TU (0x26790 .data carve copy): `&D_8004A7C8[sizeof / sizeof]` still folds to `%lo(D_8004A7C8+0x54)`
  - the outer `(s32)` casts on the s16 rectangle args are not needed (implicit conversion, fdiff 0): dropped
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawHud HackarcadeDrawHud anthropic/claude-opus-5-5 (carve body cff1dc07, D_8004A7C8 TU-defined):
  - `&D_8004A7C8[21]`, `D_8004A7C8 + sizeof / sizeof`, `end = pt + 21` / `&pt[21]` (after pt, in the pad slot): 18 (text 16);
    the end now relocates as `%lo(D_8004A81C)` (next symbol) in its own `lui s1`
  - `ARRLEN(D_8004A7C8)` 21; `for (pt = D_8004A7C8; pt < &D_8004A7C8[21]; pt++)` 20; end local first / without pad 20
  - `pt != D_8004A7C8 + 21` / `!= &D_8004A7C8[21]` 5 (unchanged, Q1071); `!=` end local 20; for with comma init 22
  - permuter 900 s -j 2 from the `!=` body: base 615, best 300 (adds a constant local `new_var = 21` for the end: a value-named constant steer), no zero
- 2026-11-17 2026-11-17: cleanup CleanarcadeDrawHud CleanarcadeDrawHud anthropic/claude-opus-5-5 (base 87ed9ed8, Q1224 re-measure):
  - girder index loop on i (the lift loop `for (i = 0; ...)` is the later definition, Q1224): exit stays `<`
    (`sltu at,s0,s1` / `bnezl` as in the target, no EQ_INEQ `!=`) but LFTR folds the end: `lui s1,%hi` +
    `addiu s1,s1,%lo(D_8004A7C8+0x54)` at 0x3880/0x3884 vs target `addiu s1,s0,0x54` off the walker lda: 25 with
    pad[1] only (frame 0x98, glist 0x88), 22 with `s32 pad[2]` before or after glist (glist 0x94), 20 (text 16) with
    pad[1] + `s32 pad2` after glist (frame 0xa0, glist 0x90): the end and the following t-register renames only.
  - `pt = &D_8004A7C8[i]` inside the i loop 20 (text 16); `for (pt = D_8004A7C8; pt < &D_8004A7C8[21]; pt++)` 20 (text 16).
  - girder index loop on j 138: the second j loop (0x37d4) then keeps `slti at,s0,0xa0` / `bnezl` (target `li s1,0xa0` /
    `bnel`), exactly Q1224, and the girder exit becomes `bnel s0,s1`: j is not the girder counter.
  - permuter 900 s -j 2 from that i index-loop body (pad[2], literal 21): base 215, best 10: only a constant-valued local
    bound (`new_var = 21; i < new_var`), after which LFTR builds the end as `addiu s2,s0,0x54` off the walker.
  - FIX from that hint: an ARRAY_COUNT bound local (Q0780; D_8004A7C8 TU-defined, 21 entries, next label at +0x54):
    `count = sizeof / sizeof` right before `for (pt = D_8004A7C8; pt < D_8004A7C8 + count; pt++)`, count declared in the
    pad[1] slot (i, j, count, glist, pt): fdiff 0. Same local in the do/while form 0; `&D_8004A7C8[count]` 18;
    `i < count` index loop 2 (LFTR end off the walker but coloured s2, target s1); `s32 count = ...` initialised at its
    declaration 69 (the assignment moves to the function entry); `n = 21` in place of sizeof/sizeof also 2 in the index loop.
## Untried ideas
- an untagged natural end that matches without the constant-valued local: measured `&D_8004A7C8[count]` 18, `&D_8004A7C8[21]` 16,
  `D_8004A7C8 + sizeof/sizeof` inline 18-20; none so far.
## Evidence
- target: `lui t8,%hi(D_8004A7C8)` / `addiu s0,t8,%lo` at 0x387c/0x3880, `addiu s1,s0,84` at 0x3884, `sltu at,s0,s1` at 0x38a0, `bnezl` 0x38a4.
- first j loop keeps `slti at,s0,160` (0x3770: the second loop redefines j), the second has `li s1,160; bnel s0,s1` (0x37d4).
- D_8004A7C8: 21 x 4 bytes at .data+0x38, next label D_8004A81C (.data+0x8c).
- `<` ends are hoisted as loop invariants and fold to `addiu s1,%lo(D_8004A7C8+0x54)`; `!=` ends stay in the loop but keep the base + 0x54 add (lda shared in s1).
- a non-literal bound (a local holding the count) keeps the end off the walker: the pointer walk `pt < D_8004A7C8 + count`
  gives the target `addiu s1,s0,84` exactly; a literal bound folds (Q0811).
