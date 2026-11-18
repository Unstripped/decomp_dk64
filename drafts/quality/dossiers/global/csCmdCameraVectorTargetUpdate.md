# csCmdCameraVectorTargetUpdate (global, src/global/478F0.c)

## Sites
- global:806496B0:dead-if:a7ed7a (kept; re-keyed abbd3b by the 2026-11-17f local renames xs/zo/xo -> startX/startY/startZ):
  `if (&startX == 0 || &px == 0 || &startY == 0 || &py == 0 || &startZ == 0 || &pz == 0) {}`.
  - Address-taking keeps the six floats in declaration-order stack homes: startX 0xa8, px 0xa4, startY 0xa0, py 0x9c, startZ 0x98, pz 0x94 (frame 0xd8).
  - Removed, uopt colours them: frame 0xe0, 179 lines. Each single term dropped: startX 95, px 102, startY 92, py 109, startZ 93, pz 97.

## Attempts
- 2026-11-09..12, Clean478F0 / ReReview / Rev16K / Rev17L / CleanGlobal478F0 (opus low/xhigh): remove/cond/classify (class 2), Vec3 struct layouts, permuter (best adds `f32 *new_var = &px`). nohit.
- 2026-11-16 HackcsCmdStepSequenceProgress3 anthropic/claude-opus-5-5:high:
  - Local arrays `f32 x[2], y[2], z[2]` ([0] = px/py/pz, [1] = start x/y/z) in place of the address test: frame 0xd8 and all six homes match; 47 lines.
    - `f32 v[3][2]`, `*x` for `x[0]`, all 1680 orderings of the setup statements, operand swaps of ex/ez, a `(f64)` cast: 47 or worse.
    - as1probe ucode: uopt output equals the base except three `add` operand orders (ex at 0x6d68, ez, `y[1] = sin * 100.0 + y[0]`).
    - Cause: cfe emits the subscripted right operand of `+` first (Q0860 holds for `+`), also when the left product reads `(*p).f`, `p[0].f`, `(&p->unk220)[0]` or `x[1]`.
  - Local structs (`{f32 pos, start;}` per axis, `pr[3]`, one 6-field struct): uopt scalar-replaces them, 179 like the removal.
  - `cb` local (38 without) and `flag` (55 with `c == 0` in the loop) are load-bearing; ordinary named locals.
- 2026-11-17f CleancsCmdCameraVectorTargetUpdate (cfe hidden-temp lever of ACDC0/2690/109660):
  - Census (`uopt_trace -l 5`, base): named homes p -4 .. cb -72; four cfe hidden temps: -84/-80/-76 = the three
    `randomFloat()` results (`ustr` from $f0) in the c == 2 `effectCreateAtPosition` arguments, -88 = the loop's
    `randomNonNegative()` result (v0) in the `D_8074E880[...]` index. `q = obj->allocation = heapAlloc(0x28)` has no temp.
  - Without the address test: per-role locals for the randoms (`f32 rx, ry, rz` last) and the index (`s32 model`) are
    word-neutral (frame 0xe0, 179); splitting the chained store gives 181 (q first) / 179 (field first). A measurement-only
    probe reusing startX/startY/startZ for the three randoms (an unrelated reuse) drops three temps: frame 0xd0, 181, the
    six floats still coloured (cand 110 -> 30, 115 -> 31, 120 -> 32, 72 -> 35, py/pz split). Frame words do not decide
    the layout; the colouring does.
  - A dedicated `s16 heading` for the first `ang` use: 12 (before or after `ang`); `ang` stays one local.
  - Permuter (900 s, -j 2, hack-free weights) from the un-nested removal body (rx/ry/rz/model): base 10876, best 7251,
    which overwrites ex with 0.033333335f inside the loop for q->rate (semantics change); nohit.

## Untried ideas
- An array spelling whose `+` operands are emitted in source order (the left product would need to be a subscript itself).
- A natural callee that took the floats' addresses in the original (none in the target asm).

## Evidence
- Homes: swc1 148/164/156(sp) 0x6d24-0x6d30 (pz px py), startX 168 0x6e18, startZ 152 0x6e20, startY 160 0x6e50; `lw a2,164(sp)`/`lw a3,156(sp)` pass px/py at 0x6edc.
- 0x6d34 lwc1 $f18,544(s0); 0x6d3c lwc1 $f6,164(sp); 0x6d68 add.d $f16,$f8,$f10 (product first); pz reload 0x6d6c lwc1 $f10,148(sp).
- Every float is re-read from its home after `swc1` stores through q (s0) in the same block: 168(sp) at 0x6f4c and 0x6f64,
  160 at 0x6f54/0x6f74, 152 at 0x6f5c/0x6f84 (aliased memory objects, as arrays or address-taken scalars are);
  the unaliased uncoloured sinA/ex/ez homes 184/180/176 are each read once per iteration (0x6de4, 0x6dec, 0x6e00).
