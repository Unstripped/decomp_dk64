# playerStateWaypointAimUpdate (global, src/global/F56F0_player_weapon.c)

## Sites
global:806F3E0C:dead-if:8092af  `if (gWaypointIndex && gWaypointIndex) {}` at the top of the `if (eq)` arm:
keeps the gWaypointIndex load (lh 0x3534, uses 0x3540/0x35f4) the higher-priority uopt candidate so it
takes $v0 and eq {M -40vreg} takes $v1 (without it eq, live in one block, adjsave 2.0, beats the load's 1.5).
global:806F3E0C:other:543a88 (copy-only, tagged 2026-11-25 as pre-existing) `next = gWaypointCursor + 1;` re-reads the global
while cur holds it. The target loads gWaypointCursor once (`lw t0,0(a3)` 0x3438), and next is a variable in t1
(`addiu t1,t0,18` 0x3460, spilled to 56(sp)). The ilod blocks copy propagation (Q0510). `cur + 1` is propagated into cur
offsets (`lh t7,18(t0)`) and the frame grows 0x50 -> 0x70 (full=156).
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
2026-11-17 2026-11-17: cleanup HackplayerStateWaypointAimUpdate4 HackplayerStateWaypointAimUpdate4 anthropic/claude-opus-5-5:high:
- 8092af reduction: single `if (gWaypointIndex) {}` (and `!= 0`, `== gWaypointIndex`) at every line from
  `starting =` to `control->button = 0` -> best 3 (never 0); `if (1) {}` 3; removal 3; triple 0; `||` two-term 0.
  uopt -l5 (single guard in the then-arm): eq {1597} LR 60 and index load {536} LR 64 both adjsave 2.0; the tie
  goes to eq (lower LR; eq's store numbers the var before both compare operands: 60 eq, 62/63 count loads,
  64 index load), so eq takes v0. Each then-arm block holding a same-value read adds 0.5 (1.5 -> 2.0 -> 2.5):
  two blocks are needed to beat eq, one only ties.
- classify (hand): unrelated two-term guards `cur && cur`, `close && close`, `eq && eq` 3, `tgt && tgt` 14,
  `gWaypointIndex && tgt` 14 -> availability/same-value class (Q0908 class 2, Q1030 term count).
- tie-breakers with the single guard: `register s32 eq` 3, block-scope `s32 eq =` 3, if-assign eq 3, swapped
  compare 24, `eq = idx + 2; eq = eq == count` 66, `eq = ... != ...; if (!eq)` 3.
- natural bodies without a guard: eq u8 69, s8/s16 70, u16 69, u32 3; no eq 9 (index load v0 OK, but
  &gWaypointIndex then takes the free v1 instead of a0, so `lui a0,%hi(gWaypointCallbackId)` fills the delay
  slot and bnel becomes bne); `count == idx + 2` no eq 29; local idx2 = idx + 2 66 (s16 84); count local 67;
  else-arm `++x`/`x = x + 1`/`x += 1` 3, cursor before index 7; decl order of eq 3/43/61.
- variants scan (swap/float/width/declswap) on the guard-free body (base 3) and the no-eq body (base 9): no zero.
- permuter (900 s, -j 2, base 15) on the single-guard body: best=0 three times, each only adding a second dead
  guard in the gGameMode == 0 arm (`!idx && !idx && !idx` or `if (!eq) {}`): no natural hint.
Result: no change (fdiff 0, 1 FAKE + 1 ORIG).
2026-11-18 "2026-11-18: cleanup CleanplayerWeaponCalculateTrajectory22" CleanplayerWeaponCalculateTrajectory22 opus
(variants.py try full=):
- guard-free uopt -l5/-l6: eq {1597} cand 60 adjsave 2.0 (bb3 only, firstisstr), gWaypointIndex load {536} cand 64
  1.5 (bb3 + bb10), &gWaypointIndex const {52} cand 218 0.5 (bb3 + bb10); all constrained, priority order puts
  60 (reg 1, $v0) before 64 (reg 2, $v1). With the guard, 64 colours before 40 and 60 (reg 1), 60 gets reg 2.
  A natural target order needs eq below 1.5 (def and use in two blocks) or the load above 2.0.
- eq hoisted above `if (close)` (two-block eq range): 16; the lh/lw loads move before the beqzl t2 at 0x3524.
- no eq, `if (gWaypointIndex + 2 != count)` with the advance arm first: 42 (block order inverted).
- pointer local `s16 *index = &gWaypointIndex;` for both the read and `(*index)++`: 75.
Result: no change.
2026-11-20 "2026-11-20: cleanup CleanbonusControllerUpdated" CleanbonusControllerUpdated claude-opus-5-5
(re-measure at 3da6b8de after TypesOwner14 batch_15 part D2, `extern u8 gDemoPlaybackState`, was s8):
- guard removed 3 (gWaypointIndex in v1 at 0x3534/0x3540/0x35f4), single `if (gWaypointIndex) {}` 3, two-term 0;
  variants scan of the guard-free body (49) best 3, no zero.
- uopt -l5/-l6 guard-free: eq {1047|0} bit 60 adjsave 2.0 -> $v0, load {1055|0} bit 64 1.5 -> $v1,
  &gWaypointIndex {1121} bit 218 -> $a0; with the guard the load is 2.5 ($v0), eq 2.0 ($v1). Same bits and
  savings as 2026-11-18 (only the uopt hashes renumbered). gDemoPlaybackState is only stored here
  (`sb zero` 0x3554), so the D2 width change adds no candidate.
Result: no change.

2026-11-25 "2026-11-25c continue" CleanplayerWeaponCalculateTrajectory22 claude-opus-5-5 (base 7fb29a74; variants.py try full=):
- Q1593 switch respellings of tests the target already has, guard removed:
  `switch (gGameMode) { case 0: ...; break; }` in the eq arm 3; `switch (gWaypointActor->state) { case 0x4F: ...;
  break; default: ...; break; }` 3; both 3. Each is the same diff: `lh v1,0(a0)` 0x3534, `addiu t9,v1,2` 0x3540,
  `addiu t6,v1,1` 0x35f4. The added switch blocks lie outside both ranges (eq: bb3 only; the gWaypointIndex
  load: bb3 + else arm), so neither priority moves.
- Q1602/Q1599: the then-arm 0x354c-0x35ec has no gWaypointIndex access. a0 is reloaded with `lui a0,%hi(gWaypointCallbackId)`
  at 0x355c and $v0 is reused for &gScreenRenderFlags 0x3560 and &gGlobalPauseFlags 0x35b8. No target instruction exists for a
  real use to take, and a code-free use is dropped before counting.
- No-eq body, uopt -l5/-l6: the load {1055} is bit 62, 1.5, and takes reg 1 ($v0). &gWaypointIndex {1121} is bit 213, adjsave 0.5,
  forbidden [1 6 7 8 10], interfering with 212 211 207 206 62 54 12 4 0. It takes reg 2 ($v1); the target has a0.
  So the target needs a reg-2 occupant live in bb3 or the else arm that emits no code: eq's compare fused into `bnel` 0x3544.
- variants scan of the guard-free body (all four sites removed in one copy; 73 variants incl. truth/swap/width/float/branch): best 3, no zero.
Result: no change.

## Untried ideas
- a real (code-free) then-arm use of gWaypointIndex to replace the 8092af guard; none found.
- a natural way to number the gWaypointIndex load before eq (then one same-value read would win the 2.0 tie);
  eq's own store always numbers it first in `eq = idx + 2 == count` (HackplayerStateWaypointAimUpdate4).
- a v1 occupant other than eq for the no-eq body (needs an invisible candidate live in bb3/else with
  adjsave between 0.5 and 1.5) (HackplayerStateWaypointAimUpdate4).
- 543a88: a natural def of next that copy propagation keeps as its own variable without the global re-read.
  Measured 156 each: `cur + 1`, `&cur[1]`, `next = cur; next++;`, cur assigned just before next.

## Evidence
target 0x3500 `sltiu a1,a2,1`, 0x3504 `andi t4,a1,0x1`, 0x3508 `beqz t4`: the flag is a coloured variable (a1)
masked again. 0x3534 `lh v0,0(a0)` (gWaypointIndex), 0x3540 `addiu t9,v0,2`, 0x3544 `bnel t8,t9`, 0x35f4
`addiu t6,v0,1`. 0x35a0 `jal playerStateQueueCallback` sets a0/a1/a2 only.
v1 is not used in the target between 0x341c and 0x3ac8 (first use: `lb v1,3(a1)` at 0x3ac8, stick_y blend):
in the close arm it is held by an invisible candidate (the fused eq compare), coloured after the index load
(v0) and before &gWaypointIndex (a0, adjsave 0.5).
gDemoPlaybackState (u8 since 3da6b8de, the definition's type): `lui at` 0x3550 + `sb zero,0(at)` 0x3554 in the
eq arm, its only access in this function. `(u32)cur->speed`: `lbu t6,9(t0)` 0x3450, `bgez t6` 0x3464 and the
2^32 `add.d` fixup 0x346c-0x3478 are the cast's own unsigned conversion (kept cast).
