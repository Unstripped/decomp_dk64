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
## Untried ideas
- an expression whose copy-forward exceeds uoptcopy's 10-variable-leaf limit (nz's right side has 4 variable leaves; no natural spelling found)
## Evidence
- 0x4178 cvt.d.s $f2 (dz02), 0x4150 cvt.d.s $f0 (dz01): both free once ny is computed (0x4198). d: add.d $f0 0x41dc, neg.d $f0 0x41e4, home 0x108(sp) via sdc1/ldc1 at 0x4254, 0x4290, 0x42c8, 0x430c, 0x4318, 0x4320.
- Every `mtc1 zero` pair (0x426c, 0x42e0, 0x4360) feeds the `0.0 - x` sub.d of val; there is no zero store to any stack slot.
