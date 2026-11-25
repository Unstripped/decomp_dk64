# vehicleUpdateMotion (global, src/global/936B0_projectile.c)

K&R definition at line 311 (was func_8068F72C; u8 params applyBuoyancy/tilt). Frame 0x60; s0 = cached
gCurrentActor, s1 = &gCurrentActor, s2 = vehicle. Locals (frame-top offsets): turnScale (s32, was tmpA) -4 (0x5c),
kongState -8 (0x58), drag -12, turnRate -16, speedGain -20 (was tmpB; never stored), tiltRoll -22 (0x4a, sh at
0x1120), tiltPitch -24 (0x48, sh at 0x1138), u8 inWater -25 (0x47), u8 onGround -26 (0x46), velX -32, velZ -36,
thrust -40, slopeAngle -42 (never stored), slopeRange -44, pl -48 (never stored); cfe temps -52 (5000/10000
select, $f12) and -56 (0x28: (f32)slopeRange spilled across mathSinF, swc1 $f2 at
0x1110). 2026-11-16 (HackvehicleUpdateMotion3): the reused temps are respelled
(5000/10000 divisor inline ternary, buoyancy y/waterY/|speedY| and terminalSpeedY as field reads, speedXZ clamp
without velX, slope factor straight from slopeRange); the 0x5c slot freed from tmpA holds the s32 turn factor.

## Sites
global:8068F72C:other:54eada FIXED 2026-11-16 (HackvehicleUpdateMotion5): two plain `u8 inWater; u8 onGround;`
  scalars (homes -25 = 0x47, -26 = 0x46, sb at 0xe08/0xe10 and 0xe1c, lbu reloads at 0xef0, 0xf90, 0x10ac,
  0x11a4, 0x11ac, 0x1424, 0x1428, 0x1528) match once every test of them is a bare truth test (`if (inWater)`,
  `if (onGround)`, `inWater || onGround`). The earlier 186 runs kept `!= 0`: both `!= 0` 186, inWater `!= 0`
  only 183, onGround `!= 0` only 146 (the `!= 0` compare is what grows the frame 0x60 -> 0x70). Template:
  raceUpdateRacerMotion (race/6650.c) `u8 onGround` at sb 83(sp) with three lbu reloads.
global:8068F72C:dead-if:cc13db FIXED 2026-11-16: the turn factor (li v0,-40/-30 at 0x12f0/0x12f8, mtc1 v0 at
  0x130c) is its own `s32 turnScale` in the 0x5c slot; with it the dead tiltRoll guard is unneeded (fdiff 0).
global:8068F72C:other:17cf50 FIXED 2026-11-16 (HackvehicleUpdateMotion5): the air arm spells the 2.0 factor as
  an int literal like raceUpdateRacerMotion (`thrust = throttle * 2; drag = ... + 2`, Q0041/Q0270/Q0421): one
  lui 0x4000/mtc1 $f0 per arm (0xf94-0xfa4, 0xfe0) shared by mul.s and add.s, so the 0x4c home is a dedicated
  `f32 speedGain` (sub.s $f0 at 0x12d0). 2.0f literal 131 (strength-reduced add.s x,x), 2.0 150.
global:8068F72C:dead-if:6c8d63 (was ebb5e5) dead-if: `if (inWater) {}` inside the buoyancy `y < waterY` arm. BLOCK SPLIT
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
2026-11-16 HackvehicleUpdateMotion4 opus:high (copy unchanged, fdiff 0; sweep 0 hits):
  54eada: per-flag signedness: u8 inWater + s8 onGround 146, s8 inWater + u8 onGround 183. Trace of the 146 body:
    cand 21 (-25vreg) and 32 (-26vreg) are both "not colored (-ve save)", yet the widened lbu of inWater (v0 at
    0xef0) is PRE-saved to a fresh temp (sw v0,0x2c(sp)), growing the frame 0x60 -> 0x70. So an uncoloured u8
    vreg still costs a widening temp (Q0957 holds for locals too); only non-vreg bytes (array/address-taken)
    avoid it. `struct { u8 v[2]; }` wrapper: word-aligned like the bare array (0x44/0x45, 12); (u8) casts on
    s8 scalars 177.
  17cf50: no free word in the frame (homes 0x5c..0x30 from the top, 0x28 = cfe temp of (f32)slopeRange at
    0x1110). A separate f32 speedGain declared last / after pl / in tmpB's place: 59 each (frame 0x68, every
    home +8). Trading turnScale for an inline ternary to make room (speedGain, or airDrag with tmpB as gain):
    79/84. drag as the 2.0f base with literal 2.0f thrust: `drag += ...` 105, `... + drag` 131; only
    `thrust = throttle * drag` (pun) is 0.
  ebb5e5: permuter 900 s from the current body with only ebb5e5 removed (base 115, fdiff 20), 19957 iterations:
    both zeros insert an empty if (`if (!gCurrentActor) {}` in the late floor-snap arm,
    `if (!gCurrentActor->terminalSpeedY) {}` in the buoyancy arm): the known block split, nohit.
  9b1ca1: kongState tail uses re-read through pl->actorType (Q0589 lever): jump only 62, turn + jump 61.
    Merged single guard re-measured 3 (kongState == 0 and == 2).
2026-11-16 HackvehicleUpdateMotion5 opus:high (copy fdiff 0, FAKE 4 -> 2):
  17cf50 FIXED: air arm with int literal 2 (`throttle * 2`, `... + 2`), as raceUpdateRacerMotion spells it;
    the 0x4c local is a dedicated speedGain. 2.0f 131, 2.0 150.
  54eada FIXED: `u8 inWater; u8 onGround;` scalars with bare truth tests only (`!= 0` on either: 146-186).
  6c8d63 (was ebb5e5): on the new body removal 20; grids all >= 20 with it removed: compound assignments,
    `&&` forms of the buoyancy/floor-snap ifs, applyBuoyancy/tilt `!= 0`/`== 0` (both applyBuoyancy forms
    grow the frame), inWater init ternary/if-else 29, if-set 168, negated 115, each 0.0f as 0/0.0 (20-175),
    each float literal as an int literal (20), turnScale ternary/default and jump switch (20).
  9b1ca1: removal 45; one `if (kongState) {}` at the top of the buoyancy `y < waterY` arm replacing both
    guards = 7 (only the v1/a0 colours of kongState and the constant 2 swap at 0x12cc/0x12ec/0x1434);
    guard expression grid all 7, one line lower 14, other lines up to actorStepPhysics 20-47; variants scan
    on that body: no zero.
  permuter 900 s from the new body with both dead ifs removed (base 487, 6280 iterations): best 450 only
    inserts `if (!gCurrentActor) {}` in the tilt else-arm, nohit.
2026-11-16 HackvehicleUpdateMotion6 opus:high (copy unchanged, fdiff 0; sweep 47 checks 0 hits):
  review nohit: fresh top-to-bottom read, body unchanged, FAKE 2 kept (6c8d63, 9b1ca1). No site retry: the
    stale causes (Q1066 bare truth tests, Q1114 int literal 2) are already in this body and Motion5's rungs
    were measured on it. Target re-read: kongState a0 / constant 2 v1 live with no call from 0x12cc to
    0x1434; onGround lbu t5,70(sp) is hoisted to 0x1428 above the inWater branch; the dead use must reach
    the 0x148c/0x14b0 clamp-join block feeding `move a0,s0` for actorStepPhysics. Natural respellings
    considered (inWater && kongState == 2 chain, jump-clear after the arms, != 2 drag ternary) are either
    behaviour/shape changes or already covered by variants scans.
  gGlobalOverlayFlags: per-file extern (s32 in 22 files, u32 in 5, twice in 936B0.c at 307/747).
2026-11-17 HackvehicleUpdateMotion7 anthropic/claude-opus-5-5 (copy unchanged, fdiff 0; sweep 47 checks 0 hits; base bbc1ab11, after
  TypesOwner batch_8 F made gGlobalOverlayFlags the one common.h extern):
  9b1ca1 diagnose nohit: uopt -l5 piece map (with the test: kongState piece 323 = bbs 44/58/66, one load at 0x12cc,
    adjsave 0.286, a0 after the constant-2 piece 329 takes v1; without: piece 321 grows back over bb 19 and bb 6,
    the call blocks, reloads at both, adjsave 0.0, uncoloured -> 45). Dedicated alias `u8/u16/s16 kong = kongState;`
    (frame hole after onGround) for the turn select + jump compare: 3/3/5 at every assignment position; its ucvt
    candidate 195 is coloured whole to v1 before the constant-2 piece (a0), so only the a0/v1 pair swaps
    (lbu v1,0x5b(sp) at 0x12cc). s32 alias: copy-propagated (Q0510) = removal + frame 0x68 (81-97 over all 16
    declaration slots); alias in pl's slot / pl inlined (Q0510 ilod init) 146-149; flattened
    `inWater && kongState == 2` jump chain 31 (with) / 50 (removed); one-case switches on the new body = 45.
  6c8d63 diagnose nohit: abs clamp as if/else into a block-scope absSpeedY 73 (frame +8), `|| -speedY > 20` 27,
    ternary-of-compares condition 121; u8 alias with both tests removed 23 = 20 + 3 (sites independent).
  review nohit: body unchanged, FAKE 2 kept.
- 2026-11-17 HackvehicleUpdateMotion8 opus:high (copy unchanged, fdiff 0; sweep 47 checks 0 hits):
  9b1ca1 diagnose nohit: piece arithmetic at base 08f85115 (Q0998 formula (uses - reload blocks) / blocks):
    without the test kongState {205} splits 10 {bb 0..5} -> 317 {bb 8..14, 18; 1 use, adjsave -0.33} -> 321
    {bb 6, 7, 15..17, 19..58; uses bb 44 (lw 0x58(sp) at 0x12cc) + bb 58 (0x1434); reload blocks bb 6 and bb 19}
    = 2 - 2 = adjsave 0.0, dropped without a further split. With the bb 66 test the same range is 3 - 2 > 0, so it is
    split again into 323 {bb 44..66, one reload at 44, adjsave 0.286} -> a0 and 331 {6, 7, 15..17, 19..43} (-0.22).
    A natural fix must drop one reload block (bb 6 or bb 19) from that range or add a real use; the target has
    neither (0x58(sp) is read only at 0xf10, 0x12cc). Entry-shape respellings measured on the removal copy:
    motion-arm `else { if (onGround) }` -> `else if (onGround)` 45 (identical IR), inWater-arm drag increment
    as `drag += throttle != 0.0f ? 30.0f : 3.0f` 219, kongState assignment moved after onGround 61 / after
    tiltPitch 51, tiltRoll = 0 before pl 47.
  review nohit: fresh top-to-bottom read at 08f85115, body unchanged, FAKE 2 kept.
- 2026-11-17 U HackvehicleUpdateMotion9 anthropic/claude-opus-5-5 (copy unchanged apart from the two FAKE comments, fdiff 0; sweep 47 checks 0 hits; uopt -l5 on c5578e18):
  6c8d63 diagnose nohit (fresh, the old diagnose was stale): waterY is ONE FP candidate (cand 24 {895|0}) over the
    buoyancy pair (compare bb 48, use bb 49) and the late floor-snap pair (bb 70/71), numerator 12 (4 uses, 2 reload
    blocks): 12/4 = 3.0 without the guard ties the abs-block speedY candidate (cand 216 {895|12}, 15/5 over bb 49..53)
    and wins on number -> $f0; the guard adds bb 49/50 -> 12/6 = 2.0 and speedY colours first. Removal 20. Late arm
    written speedY = accelY before y = waterY: 9 rows (the speedY store forces a waterY reload, the late region leaves
    cand 24, the buoyancy and early code then match; only the late arm differs): the late-region reuse (swc1 $f2,0x80
    at 0x1500) is what ties the numerator. Force as `15.0f + depth * 3.0f` 33, `3.0f * depth + 15.0f` 21, register u8 inWater 20.
  9b1ca1 diagnose nohit: pieces with the guard 10 (bb 0..5), 319 (bb 8..14,18, -0.33), 323 (bb 44..66, 0.2857 -> a0),
    331 (bb 6,7,15..17,19..43, -0.22); without it bb 6..58 is 2 uses - 2 reloads = 0, dropped unsplit (Q1179): 45. Dead-use
    position probe BEFORE the turnScale select (tail guard removed): after velZ 97, after the thrust adds 50, after moveYaw
    45, after turnRate 9, before speedGain 7 and after the heading mask 7 (kongState coloured v1, constant 2 in a0: the
    alias order). register s32 kongState 45; register on kongState/inWater/onGround with both guards removed 65.
  review nohit; FAKE comments rewritten in register terms.
- 2026-11-21 continue unit 2 Lever936B0 anthropic/claude-opus-5-5 (copy unchanged, fdiff 0; sweep 47 checks 0 hits; uopt -l5 at 18884cf4):
  6c8d63 diagnose nohit, new lever Q1590 (extra natural def/use breaks an exact tie) + Q1588 (candidate number):
    removal body waterY cand 24 {48,49,70,71} 3.0 ties speedY cand 216 {49,50,51,53x2,52} 3.0, bit 24 wins $f0 (full 20).
    18 bodies respelling the speedY reads in bb 49..53: code identical to the removal (216 stays 3.0): divide arm `-=`,
    `-(x / 12.0f) + x`, `x / 12`, `20.0f < abs`; extra or moved reads emit code: abs arm `0.0f - x` (sub.s $f0,$f14,$f2 for
    neg.s at 0x13c8/0x13d4, full 20), `(x * 12.0f - x) / 12.0f` 22,
    conditional store `x = abs > 20.0f ? x - x / 12.0f : x` 23 (216: 6 uses over 6 blocks, 2.33), `x - x * (1.0f / 12.0f)` 24,
    `x - (x + x) / 24.0f` 27, `x > 20.0f || -x > 20.0f` 27, `x * x > 400.0f` 40, `x + -x / 12.0f` 43, if/else-if pair 43,
    `x > 20.0f || x < -20.0f` 47, `-=` ternary of 0.0f 110, split compare ternary 121; hack-shaped probes 45/25.
    Every counted use is an instruction operand (c.lt.s 0x13bc, mov.s 0x13d0, neg.s 0x13d4, div.s/sub.s 0x13f0/0x13f4).
    A speedY local stays a real var (ilod locals are not forwarded) and the frame has no free word. Q1588: speedY is
    bit 216 (first read = bb 49 reload), waterY bit 24 (line-339 inWater read): no natural order numbers speedY first.
  9b1ca1: Q1590 does not apply (no tie: piece 321 is 2 uses - 2 reload blocks = 0); nothing recorded.
  review nohit: fresh read at 18884cf4, body unchanged, FAKE 2 kept.
- 2026-11-21 continue unit 2 Lever936B0 follow-up (base 48370a9c, 936B0.c unchanged; copy fdiff 0, uninit 0, no cwarn):
  9b1ca1 diagnose nohit re-checked against Q1599/Q1593/Q1602: removal piece 321 {19/6 reload, uses 44, 58} 0.0; the target
    has no kongState read after 0x1434 (a0 = s0 at 0x14b0); switch respellings of both kongState == 2 branches (turnScale
    select, jump block; case-first and default-first, alone and both, 8 bodies) add blocks (77 -> 79), no use: 45 each.
- 2026-11-25 continue CleanmountedBarrelUpdate anthropic/claude-opus-5-5 (base 9d5aabb3; copy unchanged, fdiff 0, uninit 0,
  cwarn 0; sweep 47 checks 0 hits):
  6c8d63 diagnose nohit: uncapped variants scan of the removal body (all 11 recipes, --max 2000): 182 variants, best 20.
    The sweep's recipe rung scans with --max 120, so the 62 later float/width/declswap variants had never been scored.
  9b1ca1 diagnose nohit: uncapped scans of the removal (181 variants, best 45) and of the both-removed body (180 variants,
    best 65); speedGain clamp as `speedGain = speedGain < 0.0f ? 0.0f : speedGain` and the heading update as `+=` / `&=`:
    45 each (same code as the removal).
  review nohit: fresh read at 9d5aabb3, body unchanged, FAKE 2 kept.

## Untried ideas
- 6c8d63: a natural construct adding a block between a waterY compare and its use (bb 48->49 or bb 70->71) with no
  code; the late-arm reuse of waterY must stay (store-order probe). (One more speedY use in bb 49..53: tried 2026-11-21, nohit.)
- 9b1ca1: one more kongState use AFTER the bb 58 compare (0x1434) with no code: ruled out by Q1599 (code-free uses are not
  counted; the target has no later read). Aliases stay redundant-alias steers. Remaining structural lever: drop one of the
  two reload blocks (bb 6 after the first call, bb 19 at the motion-arm join) from the tail range with the def still at
  0xdcc-0xde0 and the 0xf10 reload kept; no spelling found (2026-11-17 entry shapes, 2026-11-25 speedGain/heading forms).

## Evidence
0xdf8-0xe1c: `move t1,zero; c.le.s; bc1fl; sb t1,71(sp); li t1,1; sb t1,71(sp)` then `andi t3,t2,1; sb t3,70(sp)`.
uopt table at base 6fe2a3af: fl[3]/fl[2] were `isvar M 58 -25/-26` without `vreg`; the u8 scalars inWater/onGround
(same homes) are vreg candidates left uncoloured (-ve save) and, tested bare, add no widening temp.
0x12e0/0x12e8: `li v1,2` (constant web kept in v1 to 0x1434 `bne a0,v1`).
0x12cc: kongState reload `lw a0,0x58(sp)` live to 0x1434 (piece 339, adjsave +0.25 with the dead use).
0x12f0/0x12f8: turn factor `li v0,-40` / `li v0,-30` (tiltRoll piece 332, adjsave 1.0, v0), never stored to 0x48.
0x136c/0x1370: buoyancy y in $f12 (tmpA colour), waterY in $f2; 0x14e8: late block waterY in $f2 (cand 24) before y ($f4).
0x12cc (u8 alias body): `lbu v1,0x5b(sp)`, 0x12e0/0x12e8 `li a0,2`, all else equal (full 3); cand 195 = ucvt{194 ucvtl{kongState}}.
uopt -l5 at 08f85115 (removal copy): kongState piece 321 `live bb 19/6 needreglod`, `44 1`, `58 1 deadout`, adjsave
0.00000000e+00, no split; base piece 323 `44 1 needreglod`, `58 1`, `66 1 deadout`, adjsave 2.857e-01, a0 (uopt 3).
uopt -l5 at c5578e18: waterY cand 24 live bb 48, 49..50, 51, 72, 73 (with guard, adjsave 2.0, $f2) vs 48, 49, 70, 71
(without, 3.0, $f0); speedY cand 217/216 adjsave 3.0 both ways.
uopt -l5 at 18884cf4 (removal body): cand 24 `48 1 1 0`, `49 1 0 0`, `70 1 1 0`, `71 1 0 0` 3.0 (reg 24); cand 216
`49 1 1 0`, `50 1`, `53 2 deadout`, `51 1`, default [52], 3.0 (reg 25). Conditional-store body: 216 adds `54 1`, 2.33.
Target at 9d5aabb3: kongState `lw t0,88(v0)` 0xdcc / `sw t0,88(sp)` 0xde0, reloads only `lw t1,88(sp)` 0xf10 (5000/10000 select)
and `lw a0,88(sp)` 0x12cc (kept to `bne a0,v1` 0x12ec and 0x1434); waterY `lwc1 $f2,172(s0)` 0x1370 and 0x14e8, speedY `lwc1 $f0` 0x13b8.
