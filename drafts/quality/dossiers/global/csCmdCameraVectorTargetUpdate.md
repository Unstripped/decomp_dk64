# csCmdCameraVectorTargetUpdate (global, src/global/478F0.c)

## Sites
- global:806496B0:dead-if:a7ed7a (kept; re-keyed abbd3b by the 2026-11-17f local renames xs/zo/xo -> startX/startY/startZ):
  `if (&startX == 0 || &px == 0 || &startY == 0 || &py == 0 || &startZ == 0 || &pz == 0) {}`.
  - Address-taking keeps the six floats in declaration-order stack homes: startX 0xa8, px 0xa4, startY 0xa0, py 0x9c, startZ 0x98, pz 0x94 (frame 0xd8).
  - Removed, uopt colours them: frame 0xe0, 179 lines. Each single term dropped: startX 95, px 102, startY 92, py 109, startZ 93, pz 97.
  - FIX FOUND, blocked on a header (2026-11-18): per-axis local arrays plus PlayerState 0x220 as `f32 unk220[3]`, fdiff 0
    under a shadow actor.h. Copy `.scratch/CleancsCmdCameraVectorTargetUpdateb/fix/478F0.c` (with D5E10/E4090 user copies and
    `header-request.md`); queued for the next TypesOwner batch. The merged copy keeps the guard until then.

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
- 2026-11-18 CleancsCmdCameraVectorTargetUpdateb anthropic/claude-opus-5-5 (cleanup session 2026-11-18):
  - Per-axis arrays `f32 x[2], y[2], z[2]` ([0] the cutscene point, [1] the spark start), guard removed:
    - `ex = p->unk220 * 50.0 + x[0]`, `ez` alike, `y[1] = mathSinF(ang) * 100.0 + y[0]`: 47 (the earlier array form).
    - Base-first adds with the scalar field (`ex = x[0] + p->unk220 * 50.0`, `y[1] = y[0] + mathSinF(ang) * 100.0`): 45.
      The y line now matches (the call product on the right goes first, Q1222: add.d $f10,$f18,$f6 at 0x6e44); ex/ez still
      load x[0]/z[0] first (add.d $f16,$f4,$f10 for $f16,$f8,$f10 at 0x6d68, pz reload hoisted), the loop only FP-renamed.
    - The 0x220 vector read as an array element on the right, `ex = x[0] + (&p->unk220)[0] * 50.0`,
      `ez = z[0] + (&p->unk220)[2] * 50.0`: 0 (Q1069/Q1051: a right operand holding a subscript goes first). The same with
      every 0x220/0x224/0x228 access as `[0]/[1]/[2]` and with a real `f32 unk220[3]` field (shadow actor.h): 0.
    - Operand orders are load-bearing: ex/ez reversed 45, the y line reversed 4; x/y/z[0] stores split from the LAYOUT line 4.
    - Users of the field compile and match with `[k]`: D5E10 playerInputHandleBButtonPunch, func_806DF280,
      E4090 playerInputCheckBButtonTarget (shadow fdiff 0 each, cfe warnings 0).
  - Permuter 900 s -j 2 (hack-free weights) from the scalar-field array body: base 925, best 175, no zero.

## Untried ideas
- None for the guard itself once the header lands; until then the guard stays (lead ruling 2026-11-18: a PlayerState field
  type change is TypesOwner-only, with a stale-cost measurement first).

## Evidence
- Homes: swc1 148/164/156(sp) 0x6d24-0x6d30 (pz px py), startX 168 0x6e18, startZ 152 0x6e20, startY 160 0x6e50; `lw a2,164(sp)`/`lw a3,156(sp)` pass px/py at 0x6edc.
- 0x6d34 lwc1 $f18,544(s0); 0x6d3c lwc1 $f6,164(sp); 0x6d68 add.d $f16,$f8,$f10 (product first); pz reload 0x6d6c lwc1 $f10,148(sp).
- Every float is re-read from its home after `swc1` stores through q (s0) in the same block: 168(sp) at 0x6f4c and 0x6f64,
  160 at 0x6f54/0x6f74, 152 at 0x6f5c/0x6f84 (aliased memory objects, as arrays or address-taken scalars are);
  the unaliased uncoloured sinA/ex/ez homes 184/180/176 are each read once per iteration (0x6de4, 0x6dec, 0x6e00).
- 0x220 and 0x228 are each loaded twice from s0 (544(s0) at 0x6d00 and 0x6d34, 552(s0) at 0x6d04 and 0x6d8c): the ex/ez
  field re-reads are real loads.
- 0x220..0x228 is one 3-float vector elsewhere: E4090 copies gActorGlobalState.unk4/unk8/unkC into it, D5E10 uses 0x220/0x228
  as a point X/Z and as x/z offsets; PlayerState already has `targetScale[3]`/`currentScale[3]`.
