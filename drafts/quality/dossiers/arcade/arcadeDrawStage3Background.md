# arcadeDrawStage3Background (arcade, src/arcade/0.c)
## Sites
- arcade:800275E8:other:317c79 (was e89353, 1489cd; re-keyed by the gArcadeStage3Girders rename): kept // FAKE 2026-11-17 (CleanarcadeDrawHud, lead ruling Q0816): `count = sizeof(D_8004A7C8) / sizeof(D_8004A7C8[0]);`
  (Q0780 ARRAY_COUNT bound local, data-proven length) and `for (pt = D_8004A7C8; pt < D_8004A7C8 + count; pt++)` keep the
  end derived from the walker (`addiu s1,s0,84`, 0x3884); `count` takes the old `pad[1]` slot. Was: `(s32)` end pointer.
  A constant-valued local whose assignment position steers (initialised at its declaration: 69), so a steer per SKILL §5.6.
  2026-11-18 (director ruling: a sizeof count local is ordinary only if the target keeps the bound): the target has no
  home for 21 (no `li`/`sw` of 0x15 in the function); the bound exists only as the immediate of `addiu s1,s0,84` at
  0x3884, a register-only end, so the count stays `// FAKE` (re-checked by CleanarcadeDrawStage3Background).
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
- 2026-11-18 2026-11-18: cleanup CleanarcadeDrawStage3Background CleanarcadeDrawStage3Background anthropic/claude-opus-5-5 (base 2291c741):
  - a pointer local to the table for every access (`spans = D_8004A7C8; for (pt = spans; pt < spans + 21; pt++)`,
    spans in the count slot): 18 (text 16); `spans + sizeof/sizeof` 18; `spans[i]` index loop 20. uopt -l5: the end
    reaches the candidate table as `uadd{spans}{84}` (literal offset, cand 52) and after copy propagation folds to its own
    `lui s1` + `addiu s1,s1,%lo(D_8004A7C8+0x54)` (copy 0x3880/0x3888). Only the count local keeps the offset as
    `ushl{count}{2}` (cands 52-53: `uadd{lda}{ushl}`), which ugen adds to the walker s0 (target 0x3884).
  - countdown counters next to the walker (`for (pt = D_8004A7C8, n = 21; n != 0 / n > 0; n--, pt++)`, the
    sizeof/sizeof start, `do {} while (--n)`, `while (n--)`): 19-20; the counter stays in s1 (`li s1,0x14` at 0x3884,
    `bnez s1` / `addiu s1,s1,-1`): no LFTR onto the pointer, no end register.
  - `{ s32 count = sizeof/sizeof; for (...) }` (block-scoped initialiser at the loop) with the outer slot as `s32 pad`: 0;
    without the pad 3 (frame). The 69 is only the function-entry position of a top-level initialiser. Still the same
    constant-valued bound local with a register-only bound: a respelling of the steer plus a pad, not kept.
  - permuter 900 s -j 2 (hack-free weights) from the spans pointer-local body: base 192, best 75 only by inserting a dead
    `if (D_8004C719 && D_8004C719) {}` before the loop (a dead guard: steer), no zero.
- 2026-11-19 2026-11-18c: cleanup CleanarcadeDrawStage3Backgroundb CleanarcadeDrawStage3Backgroundb anthropic/claude-opus-5-5 (base a3d0ef71, renamed body):
  - re-run: literal `pt < gArcadeStage3Girders + 21` + `s32 pad` 18 (text 16); `ARRLEN(...)` bound and the `i < 21` index loop fold too;
    count initialised at its declaration 69. uopt -l5: base cand 52 `ushl{count}{2}`, 53 `uadd{lda}{ushl}` (ugen adds it to the walker,
    `addiu s1,s0,0x54` 0x3884); literal: `ules{pt}{const}` (cand 49) folded to `lui s1` / `addiu s1,%lo(+0x54)`.
  - NEW: the table as a function-local static (`static ArcadeGirderSpan sGirders[]` inside the function, Q1125; only this
    function reads it): with the count local RELOC-EQUIV OK (data placement unchanged); with the literal bound the end still
    folds to `lui s1,%hi(.data)` / `addiu s1,%lo(.data+0x8c)` (fdiff 1). Static vs global makes no difference to the fold.
## Untried ideas
- none from the local asm: every hack-free end with a literal offset (sized array, sizeof, pointer local, end local,
  byte offset, pointer difference, index loop, function-local static table) folds to `%lo(D_8004A7C8+0x54)`; only a variable count gives the scaled
  `ushl` that ugen adds to the walker, and no real variable holds 21 there (i is unset, j is 20 after the second loop).
## Evidence
- target: `lui t8,%hi(D_8004A7C8)` / `addiu s0,t8,%lo` at 0x387c/0x3880, `addiu s1,s0,84` at 0x3884, `sltu at,s0,s1` at 0x38a0, `bnezl` 0x38a4.
- first j loop keeps `slti at,s0,160` (0x3770: the second loop redefines j), the second has `li s1,160; bnel s0,s1` (0x37d4).
- D_8004A7C8: 21 x 4 bytes at .data+0x38, next label D_8004A81C (.data+0x8c).
- `<` ends are hoisted as loop invariants and fold to `addiu s1,%lo(D_8004A7C8+0x54)`; `!=` ends stay in the loop but keep the base + 0x54 add (lda shared in s1).
- a non-literal bound (a local holding the count) keeps the end off the walker: the pointer walk `pt < D_8004A7C8 + count`
  gives the target `addiu s1,s0,84` exactly; a literal bound folds (Q0811).
- target 0x35e8-0x3a34: no `li` or `sw` of 21 anywhere; the count survives only as the 84 immediate at 0x3884.
- ruling question (2026-11-18c): rulings.md ordinary C lists a constant-valued local the target uses at run time in a way no
  literal reproduces (Q0814); here the end is built at run time off the walker (0x3884) and every literal folds, but the
  2026-11-18 director ruling (no home or li of 21) keeps the FAKE until re-ruled.
