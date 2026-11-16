# vehicleUpdateMotion (global, src/global/936B0.c)

K&R definition at line 311 (was func_8068F72C; u8 params applyBuoyancy/tilt). Frame 0x60; s0 = cached
gCurrentActor, s1 = &gCurrentActor, s2 = vehicle. Locals (frame-top offsets): turnScale (s32, was tmpA) -4 (0x5c),
kongState -8 (0x58), drag -12, turnRate -16, tmpB -20, tiltPitch -22 (0x4a), tiltRoll -24 (0x48), fl[3] -25
(0x47), fl[2] -26 (0x46), velX -32, velZ -36, thrust -40, slopeAngle -42, slopeRange -44, pl -48; cfe temp -52
(0x2c, store of an f0 call result). 2026-11-16 (HackvehicleUpdateMotion3): the reused temps are respelled
(5000/10000 divisor inline ternary, buoyancy y/waterY/|speedY| and terminalSpeedY as field reads, speedXZ clamp
without velX, slope factor straight from slopeRange); the 0x5c slot freed from tmpA holds the s32 turn factor.

## Sites
global:8068F72C:other:54eada other: `u8 fl[4]` keeps fl[2]/fl[3] as non-vreg isvars (uopt table `isvar M 58 -25/-26`
  without `vreg`): sb at 0xe08/0xe10 (0x47) and 0xe1c (0x46), lbu reloads at 0xef0, 0xf90, 0x10ac, 0x11a4, 0x11ac,
  0x1424, 0x1428, 0x151c/0x1528. Two u8 scalars become vreg candidates, get coloured (t0 etc.) and add spill
  temps: frame 0x60 -> 0x70, full=186.
global:8068F72C:dead-if:cc13db FIXED 2026-11-16: the turn factor (li v0,-40/-30 at 0x12f0/0x12f8, mtc1 v0 at
  0x130c) is its own `s32 turnScale` in the 0x5c slot; with it the dead tiltRoll guard is unneeded (fdiff 0).
global:8068F72C:other:17cf50 other (copy-only, pre-existing now tagged): tmpB holds the 2.0f air constant
  (lui 0x4000/mtc1 $f0 at 0xf94-0xfa4) and the clamped speed gain ($f0 at 0x12d0). A separate f32 local shifts
  every home (59); speed gain inline 96 or in drag 174; literal 2.0f 131; drag = 2.0f base (0) is a pun.
global:8068F72C:dead-if:ebb5e5 dead-if: `if (fl[3] != 0) {}` inside the buoyancy `y < waterY` arm. BLOCK SPLIT
  (guard on 1/vehicle/fl[2]/tilt/motion all 0). On the new body only cand 24 (waterY uilod 172) moves: its live
  blocks are the buoyancy compare/use (bb 48,51) and the late !applyBuoyancy floor-snap compare/use (bb 72,73,
  0x14e8/0x1500); n 4->6 = divisor 2->3, adjsave 3.0->2.0. Without it waterY takes $f0 at 0x1370 and the
  5000/10000 select and throttle swap $f12/$f0 at 0xf0c-0xf5c (full=20 on the new body, 38 at base).
global:8068F72C:dead-if:9b1ca1 dead-if: `if (kongState == 0) {}` before actorStepPhysics. USE class (only a
  guard on kongState matches). With it the kongState tail range [bb 44,58,66] splits off (adjsave 0.29) and
  takes a0 (lw a0,0x58(sp) at 0x12cc feeds 0x12ec and 0x1434); without it the tail merges with the bb 19/6
  range (adjsave 0.0, not coloured) and kongState is reloaded twice (t4 at 0x12cc, t3 at 0x1428) (full=45).

## Attempts
(see .scratch/briefs/HackvehicleUpdateMotion2-history-vehicleUpdateMotion.txt for the 105 earlier events:
rounds 2-30 opus:low, Hackfunc_8068F72C opus:high 2026-11-14, PermBatch1114c)
2026-11-10..14 earlier units: two u8 register flags, flag struct, u8 fl[2], fl[4] with every dead test removed (56),
  separate turn-factor local, switch/?: on kongState, typed kongState snapshots, one-case switch grid (Q0523),
  variants scans, removal-combination matrix, permuter batches (cc13db, 9b1ca1, 54eada) -> no 0.
2026-11-15 cleanup HackvehicleUpdateMotion2 opus:high:
  sweep (copy-of src) -> 0 hits; removals alone: no1(cc13db)=55, no2(ebb5e5)=38, no3(9b1ca1)=45, all=56.
  variants scan on each single removal and on the all-removal -> no zero.
  cc13db: inline ternary in the heading expression (79/116 with 9b1ca1), `tiltRoll = kongState == 2 ? -0x1E : -0x28`
    (55), `tiltRoll = -0x28; if (kongState == 2) tiltRoll = -0x1E` (54), `kongState != 2` arms (55),
    turn factor in tiltPitch (55) / slopeAngle (11, reuse of an unrelated local) / slopeRange (21).
  54eada: `u8 inWater; u8 onGround;` with and without `u8 pad[2]` before/after (186 each, frame 0x70).
  ebb5e5 (dead test removed): buoyancy respellings of y/waterY caching: field reads only (`r2`, 30),
    drag only (`drag = waterY; if (y < drag) (drag - y)`, 7), tmpA+drag with field compare (6), etc.;
    fl[3] compare operand order (no effect); abs block with field re-reads (no effect); `&&`-merged
    buoyancy/late conditions (no effect); late block through a local: field reads in buoyancy +
    `tmpB = waterY; if (y < tmpB) y = tmpB;` in the !applyBuoyancy block -> 3 (only the late block's waterY
    is $f0 instead of $f2). Full 154 x 58 buoyancy/late grid (8932 bodies) and abs/terminalSpeedY clamp
    respellings: floor 3. uopt -l5 adjsave: base 67 2.67 > 101 tmpB 2.6 > 83 tmpA 2.25 > 24 waterY 2.0;
    no test: 24 3.0, 83 3.0. 24 must keep its late uses (late $f2) yet rank below tmpA, which needs the
    extra blocks only the dead test supplies. Permuter 900 s on the 3-line body (base 15, best 15).
  9b1ca1: kongState reload piece 339 adjsave +0.25 with the test, -0.25 without; removal on the ebb5e5
    near-miss body 48; with cc13db respellings 56.
  reconstruct (no dead tests, field-read buoyancy, late tmpB, inline-ternary factor): 118 with fl[4],
    206 with u8 scalars.
2026-11-16 HackvehicleUpdateMotion3 opus:high: refined Q0908 classify (cc13db use class on a dead tiltRoll,
  ebb5e5 block split, 9b1ca1 use class on kongState). De-reuse reconstruct fixed cc13db (tmpA slot -> s32
  turnScale); tagged the remaining tmpB reuse (17cf50). ebb5e5: an if (vehicle) {} inside the late floor-snap
  then-arm also matches (cand 24 spans both regions); unused label / `;` add no uopt block (38); compare swaps,
  merged conditions, else-if late block all 20. 9b1ca1: ternary jump speed / turnScale, != 2 flips, bare flag
  tests: 45-58. 54eada: two u8 scalars 186 on the new body.
2026-11-16 HackvehicleUpdateMotion opus:high (copy unchanged, fdiff 0):
  54eada re-diagnosed on the turnScale frame: u8/u8 186, u16 186, anonymous `struct { u8 onGround; u8 inWater; }`
    186 (fields promoted like scalars), u8 fl[2] 12 (local arrays are word-aligned: bytes land at 0x44/0x45, not
    0x46/0x47), s8/s8 scalars 9 (both stay memory-resident at 0x46/0x47, only the 9 reloads are lb instead of
    lbu), s16 12, s32 59 (memory-resident, frame +8). Mixed u8/s8 146/183. u8 trace: onGround (cand 32,
    -26vreg) adjsave 0.6 -> t0; s8: 0.0, not coloured. onGround def respellings (`!= 0`, `?1:0`, if/else)
    160-182. variants scan on the s8 body: no edit beats 9 (Q0957/Q0927: only unsigned narrow locals get a
    coloured widening candidate).
  17cf50: speed gain and/or the 2.0f in nested `{ f32 x; }` block scopes: 59 each; IDO gives block-scope locals
    their own slots (no overlay of sibling blocks), frame 0x60 -> 0x68.
  9b1ca1 + ebb5e5: ONE `if (kongState == 0) {}` at the top of the late floor-snap then-arm (both removed) -> 3:
    it supplies ebb5e5's waterY-range blocks and the kongState tail use, but the kongState piece then reaches
    actorStepPhysics's a0 setup, so it is coloured a3 (uopt 6) not a0 (3) at 0x12cc/0x12ec/0x1434. Grid of 4
    guard forms x every statement position from the jump block to the end: only that position reaches 3 (others
    20-36). variants scan on that body: nothing below 3. Permuter 900 s on it (base 15, best 15).
  reconstruct: s8 flag scalars + that single guard + tmpB kept 12 (9 lb + a3/a0); s8 without dead tests 70;
    plus separate airDrag/speedGain 117.
  review: tiltRoll -> Actor 0xE8 `roll`, tiltPitch -> 0xE4 `pitch` as named (no local rename); the physical
    roles hint actor.h's 0xE4/0xE8 names are swapped (bonus/2690.c:342 eases an elevation into ->roll).

## Untried ideas
- ebb5e5: needs two zero-code uopt blocks inside either waterY compare/use pair (buoyancy or late floor-snap
  arm); no natural statement found that does that.
- 17cf50: a third role-free slot for the speed gain or the 2.0f constant (pl cannot be inlined: 144).
- 54eada: s8 scalars already give the target's memory homes (9 lb/lbu lines); open: an unsigned byte
  local whose widening candidate is not coloured (Q0957), or an s8 local whose reloads come out lbu.
- 9b1ca1/ebb5e5: merging both guards needs the kongState piece kept off a0's argument setup at 0x14a4/0x14b0
  while the use sits in the late floor-snap arm (single-guard body: 3 off, a3 vs a0); no spelling found.
- lever (b) (aggregate initialiser from a .data template) does not apply: fl bytes are computed stores.

## Evidence
0xdf8-0xe1c: `move t1,zero; c.le.s; bc1fl; sb t1,71(sp); li t1,1; sb t1,71(sp)` then `andi t3,t2,1; sb t3,70(sp)`.
uopt table: fl[3]/fl[2] are `isvar M 58 -25/-26` without `vreg` (memory-only candidates).
0x12e0/0x12e8: `li v1,2` (constant web kept in v1 to 0x1434 `bne a0,v1`).
0x12cc: kongState reload `lw a0,0x58(sp)` live to 0x1434 (piece 339, adjsave +0.25 with the dead use).
0x12f0/0x12f8: turn factor `li v0,-40` / `li v0,-30` (tiltRoll piece 332, adjsave 1.0, v0), never stored to 0x48.
0x136c/0x1370: buoyancy y in $f12 (tmpA colour), waterY in $f2; 0x14e8: late block waterY in $f2 (cand 24) before y ($f4).
