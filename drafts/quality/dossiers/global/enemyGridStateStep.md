# enemyGridStateStep (global, src/global/C0EE0.c)

## Sites
- global:806BC1E0:other:3f4254 other: `for (j = 0; &D_807FC8C0[j] < &D_807FC8C0[16]; j++)` keeps the strength-reduced pointer compare `sltu at,v1,a0` + `bnezl at` at 0x4dc/0x508 (v1 = walk pointer, a0 = D_807FC8C0+16); `j < 16` gives LFTR `bnel v1,a0`.
- global:806BC1E0:other:92ac80 other: `(u16)(cell >> 2)` gives the cell >> 2 chain a second ugen record (`sra $25` + `and $11,0xffff`), so cell >> 2 lands in t3 at 0x750 and the dx sll in t4 at 0x74c.
- global:806BC1E0:other:cc75db / 047f57 other: s32 dx/dy with `dx = (s16)dx; dy = (s16)dy;` after both subtractions puts the dx narrowing (sll t4 at 0x74c) after cell >> 2 in ugen order (Q0758 / ido-uopt-statics-and-live-ranges#6).
- global:806BC1E0:dead-if:716d92 dead-if: `if (ones == 0) {}` in the dx < -1 block reloads `ones` (lh $7,66($sp), deleted by as1) so the ones web (cand 105, a3) interferes with the gridX/gridY CSE webs (cand 169/176); with 85e7fb they take t0/t1 (0x718/0x724) instead of v1/a3. Reads `ones` uninitialised on this path (clint UNINIT line 237).
- global:806BC1E0:dead-if:85e7fb dead-if: `if (cell & 3) {}` in the dy < -1 block makes `cell & 3` (cand 235, uand) a coloured web in v1 (adjsave 1.0 > gridX's 0.75) live to the dy clamp; it blocks v1 for gridX and moves the col narrowing to sll $15/sra $24 (andi t8 at 0x744).

## Attempts
- 2026-11-15 HackenemyGridStateStep2 anthropic/claude-opus-5-5:high: sweep 27 checks 0 hits (classify 85e7fb class 1, 716d92 class 2).
- 3f4254: `s8 *p` walk `for (p = D_807FC8C0; p < D_807FC8C0 + 16; p++)` in j's home 13 rows (D_807FC8C0 %hi becomes one coloured web shared with the i loop: lui t1 + addiu v1,t1 at 0x4bc, i-loop base t1 / -1 in t0 at 0x5e8/0x604); p at each of the 20 declaration slots 13-31; `&D_807FC8C0[16]`/`&D_807FC8C0[0]` 13; `!=` 285; while 13; do-while 27; end-pointer local 31; j+p dual counter 42-45; `*p++` 79; index bounds `j < 16`, `j != 16`, `j <= 15`, `(u32)j < 16`, `sizeof`, u32 j: 2 rows (bnel v1,a0 at 0x508).
- 92ac80/cc75db/047f57: drop u16 only 92; drop both deferred narrowings (s16 casts in the subtractions) 4 (dx sll t9 at 0x74c, cell >> 2 t5 at 0x750); s16 dx/dy 13; one narrowing at a time 4; 85-variant grid (row local s8/u8/s16/u16/s32 before/after dx, dy first, dx/dy s16/s32, cast/none, `x -= a`) best 9 only without narrowing (semantics differ); `dx = col; dy = (u16)(cell >> 2); dx -= st->gridX; dy -= st->gridY;` + deferred narrowing = 0 (respelling only, same hacks).
- 716d92+85e7fb with dx/dy reshaped (Q0602): `col = cell & 3; dx = col; dy = cell >> 2; dx -= st->gridX; dy -= st->gridY;` + deferred narrowing, no u16, no dead tests: 8 rows (only andi t9 for t8 at 0x744 and gridX/gridY v1/a3 for t0/t1); the ones test alone changes nothing there, the cell test alone 91-101; col s8/u8/u16/s32, `(s16)` inits: 8-43.
- 716d92/85e7fb merges: best/zeros/n/cell renamed into ones/zeros/i/best/n/col (12 pairs x 3 dead-test states) best 3 (cell -> i: v1 for v0), none drops a dead test below 7.
- Loop 2 guard as early `continue` (Q0773) and `if (dist <= 0) continue;`: dead tests still needed (0 only with both kept, 79-94 otherwise).
- Clamp shapes (else-if, `> 1`, `<= -2`, reversed order, ternaries) without dead tests 94-152.
- reconstruct: natural body (p walk, `col = cell & 3; dx = (s16)(col - st->gridX); dy = (s16)((cell >> 2) - st->gridY);`, no dead tests) 24 rows; same with the j-index loop hack kept 11 rows (vs round 38's 95): gridX/gridY v1/a3 for t0/t1 and ugen ring t9/t3/t5 for t8/t4/t3. variants.py scan of that body (162 variants) no improvement.
- permute (perm_F1j): 11-row natural body with all five removed, -j 2, 900 s, 29458 iterations, base 65 best 65, no output below baseline.

## Untried ideas
- A natural second use of `cell & 3` live through the dy clamp (the v1 blocker) together with an a3 blocker that leaves no instruction: no candidate found; a debug-print macro compiled out inside the clamp blocks would explain both dead tests but reads `ones` uninitialised.
- A file-owned definition of D_807FC8C0 (4x4 `s8 [4][4]` grid) for the pointer walk: needs a .bss carve (address 0x807FC8C0 not owned by this TU); no evidence it changes the shared %hi web.

## Evidence
- Target 0x4bc-0x508: lui v1/lui a0 (D_807FC8C0, +16), loop sltu at,v1,a0 / bnezl at; ones a3 spilled at 66(sp), zeros t0 at 64(sp) around flagSet (0x51c-0x53c).
- Target 0x5e8-0x6fc: i loop base t0 = D_807FC8C0, -1 in t1, i v1, best a3, n a2, &cand t2.
- Target 0x708-0x7a8: n spilled 84(sp) around randomFloat; gridX lb t0 0x718, gridY lb t1 0x724; andi t8 0x744, sll t4 0x74c, sra t3 0x750, sll t6 0x75c; clamps slti/li; addu t8/t9 + sb 0x7a4/0x7a8.
- uopt trace (base): cand 235 (uand cell,3) v1 adjsave 1.0, cand 169/176 (gridX/gridY uilod) adjsave 0.75 forbidden [1 2 3 4 5 6 9 14] -> 7/8; without dead tests adjsave 1.0, forbidden [1 3 4 5 9 14] -> 2/6. Cand 105 (ones, -70vreg) a3 interferes with 169/176.
