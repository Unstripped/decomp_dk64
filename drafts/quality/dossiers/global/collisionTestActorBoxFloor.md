# collisionTestActorBoxFloor (global, src/global/6AD90.c)
## Sites
- global:8066A08C:dead-store:ff3fab `dy02 = 0.0;`: the dead-store kill described in ido-levers-revisit-7 (Coll entry) and Q0499 (floats have no no-code kill). It stops uopt forwarding nz's expression into d. Target: d in $f0 at 0x41dc-0x41e4, spilled to its home 0x108(sp) around every call. Not ORIG: the target never stores 0.0 for dy02.
## Attempts
- CleanD5E10, Rev16G, Rev17L (opus:low): remove/cond/diagnose/permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - plain removal: 11
  - d operand orders: 11-122
  - nx/ny/nz statement orders: 19-46+
  - casts all/none: 11
  - block-scoped temporaries: 20
  - d/nz inside the ny test: 305+
  - nz inlined into d: 12
  - variants scan of the removal: 11 at best
- 2026-11-15 HackcollisionTestActorBoxFloor2 (opus:high), base a04efaed, diagnose nohit:
  - plain removal re-measured: 11 (d only: $f2 for $f0)
  - zdbug:6 trace: without the kill, nz's usub (candidate 110) has 2 uses (nz store + d), is the first FP candidate coloured and takes $24=f0; it interferes with d (112), so d gets $25=f2. With the kill only the nz var exists and d (113) takes $24 after dz01.
  - nz as `nz = a; nz -= b;`, and all three normals so: 11 (forwarded after the merge)
  - d accumulated in steps (`d = nx*x1 + ny*y1; d = -(nz*z1 + d)`, `d += ...; d = -d`): 145; `d = ...; d = -d`: 198
  - normal from tri fields without delta locals: 243; nz alone from fields: 286
  - ray-direction reuse dx02/dy02/dz02 = 0, 2000, 0 with the full dot-product denominator: 175 (IDO keeps nx*0.0)
  - ray-span reuse `dy02 = 2000.0;` before d, feeding `ny * dy02` and `dy02 * val`: 0, but a reused-temp steer in place of the dead store; not applied
  - frame census: pad words 0x90..0xB4 untouched except hitY 0xAC; nx/ny/nz live in $f30/$f20/$f22; 0x78..0x8C are uopt temps for the tri x1/y1/z1 loads. A memory-homed aggregate for the normal would add loads and stores.
- 2026-11-15 HackcollisionTestActorBoxFloor3 (opus:high), base f9b2e9c7, diagnose nohit (variants.py try):
  - plain removal 11; variants scan of it best 11
  - operand map of the kill: `dy01 = 0.0` or `dy02 = 0.0` after nz -> 0; `dx01`/`dx02`/`dz01 = 0.0` -> 298
  - Q0908 block-split test: `if (j) {}` 311, `if (hit) {}` 321, `goto split; split:` 321, bare label 11 (a split also breaks the tri->x1/y1/z1 CSE temps)
  - nz assigned inside d's expression 12; nz before nx/ny 295; named f32 x1/y1/z1 locals 362
  - d flat sum 128; d partial before nz then `d = -(nz*z1 + d)` 128; `d = nz*z1; d += ...; d = -d` 141; `d = -(...); d -= nz*z1` 152
  - 10-leaf limit test: deltas through `((CollisionBoxTri *)actor->collision->triangles)[j]` 357 (y-deltas only 312); nz with field deltas 152. Same-block uses are substituted at input (Q0559), so uoptcopy's leaf limit is not the lever.
  - ray-span reuse confined to `dy02 * val` (denominator keeps the literal) 0: still a reused-temp steer, not applied
  - permuter on the plain removal (hack-free weights, 900 s, base 60): six zeros, all a y-delta reused for a literal between nz and d (dy01 = 0.01 / 2000.0; dy02 = 2000.0 / -1000.0 / -0.01); reused-temp steers, not applied
## Untried ideas
- (tried 2026-11-15, unit 3: not applicable in-block) an expression exceeding uoptcopy's 10-variable-leaf limit
- a natural source role for a y-delta (dy01/dy02) after the normal: the only zero-scoring family; needs a reading of the ray maths where a y-delta variable really is the ray span (none found that is not a reused temp)
## Evidence
- rodata: 0x128 2000.0 unreferenced (Q0086); 0x130 0.01, 0x138/0x140 2000.0 (the two ny tests), 0x148 -0.01, 0x150 2000.0 loaded once into $f26 at 0x421c and used for every den and `2000.0 * val` in all three blocks, then per-use -1000.0/1000.0 pairs at 0x158..0x180.
- tri->x1 is loaded once (0x4108) and parked in two uopt temps 0x8C(sp) and 0x78(sp) (reload 0x41ac for d); y1 0x84, z1 0x80.
- 0x4178 cvt.d.s $f2 (dz02), 0x4150 cvt.d.s $f0 (dz01): both free once ny is computed (0x4198). d: add.d $f0 0x41dc, neg.d $f0 0x41e4, home 0x108(sp) via sdc1/ldc1 at 0x4254, 0x4290, 0x42c8, 0x430c, 0x4318, 0x4320.
- Every `mtc1 zero` pair (0x426c, 0x42e0, 0x4360) feeds the `0.0 - x` sub.d of val; there is no zero store to any stack slot.
