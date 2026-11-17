# playerStateWaypointAimUpdate (global, src/global/F56F0.c)

## Sites
global:806F3E0C:dead-if:8092af  `if (gWaypointIndex && gWaypointIndex) {}` at the top of the `if (eq)` arm:
keeps the gWaypointIndex load (lh 0x3534, uses 0x3540/0x35f4) the higher-priority uopt candidate so it
takes $v0 and eq {M -40vreg} takes $v1 (without it eq, live in one block, adjsave 2.0, beats the load's 1.5).
ORIG (not a site): `if (starting & 1)` = target `andi t4,a1,0x1` at 0x3504 on the sltiu a1 result.
Fixed 2026-11-17 (were 1ea72b f7b1c1 bc0c83 e7e05f 23f09e 2797cb 69b9dd 718e35, 2223db, 523ab5, proto-type 14204c).

## Attempts
2026-11-15 HackplayerStateWaypointAimUpdate2 anthropic/claude-opus-5-5:high (types phase):
- shared 3-arg prototype on the old body: fdiff 1 (full=11); 4-param/variadic local prototypes 0; EFDC0
  callee variadic/4-param: fdiff 1 -> views blocked (owner EFDC0).
2026-11-17 HackplayerStateWaypointAimUpdate3 anthropic/claude-opus-5-5:
- close = inline squared distance over gWaypointActor->x/z and next->x/z (dx/dz locals dropped): the
  ilods block copy propagation (Q0510), so close is evaluated before the gWaypointFlags load without
  `if (close) {}`. All-removed body 110 -> 80; with `(flags == 0) & 1` 77, block shape 0; &gWaypointCursor
  stays in a3 with a 3-arg call.
- flags test: `u8 flags = !gWaypointFlags; if (flags)` 4 (andi 0xff), u16 4, `s32 starting = !gWaypointFlags;
  if (starting & 1)` 3 (the remaining diff is only gWaypointIndex in v1 instead of v0).
- eq/index: eq if-assign 18, ternary 17, `;` 3, reuse var 3, s16 idx local 24-29, WaypointPath local 69-74,
  no eq 9, `if (!eq)` swap 40, block-split guard before `if (eq)` 11. Permuter (900 s, base 15) best=0 =
  a triple same-value gWaypointIndex read at the top of the then-arm; the two-term form is enough (fdiff 0).
- shared prototype (PROTO_SKIP + K&R decl deleted): fdiff 0.
Result: fdiff 0, 10 FAKE + 1 PROTO -> 1 FAKE + 1 ORIG.

## Untried ideas
- a real (code-free) then-arm use of gWaypointIndex to replace the 8092af guard; none found.

## Evidence
target 0x3500 `sltiu a1,a2,1`, 0x3504 `andi t4,a1,0x1`, 0x3508 `beqz t4`: the flag is a coloured variable (a1)
masked again. 0x3534 `lh v0,0(a0)` (gWaypointIndex), 0x3540 `addiu t9,v0,2`, 0x3544 `bnel t8,t9`, 0x35f4
`addiu t6,v0,1`. 0x35a0 `jal playerStateQueueCallback` sets a0/a1/a2 only.
