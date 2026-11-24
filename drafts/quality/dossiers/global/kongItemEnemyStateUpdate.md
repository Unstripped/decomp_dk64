# kongItemEnemyStateUpdate (global, src/global/B5EC0_kong_item_enemy.c)

## Sites
global:806B13B4:proto-steer:72fa9a proto-steer: `#define PROTO_SKIP_actorTrackBoneTowardTarget` + K&R `void actorTrackBoneTowardTarget();`
so the case 2/3/7/0x35 call can pass a spare 2nd argument `sel` (owner 1295B0 reads only a0: `andi a1,a0,0xff`
at 0x5a0 writes a1 before any read). The spare use keeps `sel` (uopt cand bit 14, -4vreg, colour 4 = $a1) itself live into
the case block (uopt bb122), so the `sel == 0x35` test reads $a1 (`bne a1,at` at 0x9c8). The K&R form also
needs the two `(u8)` casts at the calls of lines 207/214 (`andi a0,v1,0xff` at 0x980/0x9dc), conversions the
target executes (untagged, R1). Ruling RQ3 (2026-11-20): TERMINAL, the FAKE is kept.

## Attempts
2026-11-14 Hackfunc_806B13B4 anthropic/claude-opus-5-5:high
- consolidate (key 72fa9a, first time on this key): drop define + K&R decl so include/proto/global/1295B0.h
  `void actorTrackBoneTowardTarget(u8)` applies; the 2-arg call is a cfe arity error, so the spare `sel` goes too.
  With the casts kept (t1) and without them (t2) the object is identical: fdiff 1, 5 instruction lines differ:
  `move v0,a1` takes the delay slot of the jump-table range test (`beqz at,default` at +0x240, the target slot holds
  `addiu t0,..gBehaviourWorkState`, which moves above; function grows by 4), the 0x35 test becomes `bne v0,at`
  (+0x7d8, target `bne a1,at` +0x7d4); one as1 order swap (`lui a0` vs `lui gCurrentActor`, target +0x5d4). Callers at lines 131/205 are unaffected by the shared prototype.
- diagnose (uopt -l5/-l6 on base vs t1): t1 adds candidate bit 54 `{120|0} uadd{1360|0}{0|0}` (the switch-temp
  copy of `sel`), computed in bb29 (dispatch) and used in bb122 (case 2/3/7/0x35), adjsave 1.5, coloured 1 = $v0.
  In base bb122 lists `{1360|0}` (sel itself, $a1) because the spare argument reads sel there; bit 54 never
  becomes active. So the steer is not callee width (casts/prototype give the same andi) but an extra read of
  `sel` in bb122.
- natural respellings under the shared prototype (all fdiff 1, instruction-line diff vs target in brackets):
  `gCurrentActor->state == 0x35` in the call [36], plus `switch (gCurrentActor->state)` [99, also without casts],
  `sel = ...; switch (gCurrentActor->state)` [38], separate `state` local for the first switch [77], for the second
  switch [58], second switch on `gCurrentActor->state` [58], u8 `bone` via if/else [13], s32 `bone` ternary [14],
  `sel != 0x35 ? 3 : 2` [9], `register s32 sel` [5], `case 0x35:` first in its group [5], `patrolPathStep(sel, 1)` [92].
  `variants.py scan` of the consolidated copy (45 recipes: swap/float/width/declswap): best full=4 = baseline.
- permute (consolidated copy t1, -j 2, 900 s, base 364): zero after 11 s (output-0-1, output-0-2), both the same
  copy temp: `sel = gCurrentActor->state; new_var = sel; switch (new_var)` with the 0x35 test on `new_var`
  (reproduced as t/pz.c, fdiff 0). `sel` there is only a store feeding the copy; a direct selector local
  (`state = gCurrentActor->state`, t/pw.c, b1.c) gives 77 differing lines. Copy temp = steer swap: not applied.
- 2026-11-17 Hackfunc_806B13B42 anthropic/claude-opus-5-5 diagnose nohit (base b1e83349). `protos.py consolidate`
  prints `PROTO actorTrackBoneTowardTarget` (the 2-arg call is a cfe arity error under the u8 header). With the spare
  argument dropped as well (t1), the result is full=4: `move v0,a1` in the beqz delay slot at +0x240 and `bne v0,at` at +0x7d4.
  cfe t.B: NO switch temp for an s32 or a u32 `sel` (`xjp` loads the -4 home directly; -8vreg is the ternary temp).
  uopt t.O: `add(lod a1,0)` -> $v0 is the xjp operand (cand uadd{1360|0}, bit 54 s32 / 53 u32), and copy
  propagation turns the case-0x35 `equ` into `lod v0`. Measured: u32 sel 4 (same diff), u8/u16 27, s16 199;
  `sel = gCurrentActor->state; sel == 1` in the 1/0x10/0x23 block 25; per-role locals 43 (first switch;
  u32 57) / 34 (second switch) / 34 (phase checks). The B2CE0 func_806AE588 snapshot
  (`entryState = sel; switch (sel)` with the 0x35 test on `entryState`) gives full=0 for s32 and u32 and 18 for u8, but
  here sel is never reassigned, so the snapshot is a redundant alias. CleanupLead-2 ruled it a steer swap
  (1 -> 1), so the proto-steer stays.
- 2026-11-17 Hackfunc_806B13B43 anthropic/claude-opus-5-5:high diagnose nohit (base db35e1fb). Lead question
  (does the target load a1 for the call?): no. a1 = sel only by residence: `move a1,a0` after `lbu a0,0x154(s0)` on
  every path into the dispatch (last 0x424, 0x628), no a1 write between `jr t9` (0x450) and the jal at 0x9d8; the
  same residence holds at the default `jal behaviourUpdateContactAndState` (0xb2c). Tried the B2CE0/BB300 ORIG form
  instead (shared u8 `actorTrackBoneTowardTarget`, K&R `behaviourUpdateContactAndState(0x203, sel)` in default):
  full=4, same `move v0,a1` (0x43c) / `bne v0,at` (0x9cc). Grid {switch(sel) | sel snapshot + switch(field)} x
  {sel redefined in the 1/0x10/0x23 block as in B2CE0 func_806AFB58} x {default spare arg}: 4/4, 25/25, 22/22,
  43/43 — the default-arm spare argument is object-neutral here (unlike B2CE0, Q0649).

2026-11-17 Cleanfunc_806B13B4 anthropic/claude-opus-5-5 (unit "2026-11-17: cleanup Cleanfunc_806B13B4", base d09e1e2a)
- diagnose nohit, lever (a) which use keeps bit 54 `uadd{1360|0}{0|0}` alive: the 0x35 equ, not the xjp. uopt wraps a
  bare-variable selector: t.O dispatch is `lod a1; ldc 0; add; xjp` in the base (copy never stored) and
  `lod a1; ldc 0; add; str v0; lod v0; xjp` in t1, whose case block reads `lod v0; ldc 53; equ`. With the 0x35 test
  removed (`actorTrackBoneTowardTarget(3)`) the dispatch is `add; xjp` again and no `move v0,a1` is emitted, so the
  xjp itself always reads $a1 (`addiu t9,a1,-1` at +0x234). Selector spellings: `switch (sel = gCurrentActor->state)` 4
  (also with the second switch the same way 4), `switch ((s32)sel)` 4, `(u32)sel == 0x35` 4, `0x35 == sel` 4 (no-op
  conversions and the assignment fold like the bare variable). Only a selector that is already a non-folding
  expression escapes the wrap: `switch (sel ^ 0)` gives `lod a1; ldc 0; xor; xjp`, the equ reads $a1 and fdiff exits 0
  (t/w_s3.c), but it is a no-op-arithmetic FAKE in place of the proto-steer (1 -> 1): not applied.
- diagnose nohit, lever (b) block position vs liveness: the copy replaces a case-block read of sel exactly when sel is
  dead after that read. `sel == 0x35 ? 2 : sel` (a later sel read on the else path) puts the equ back on $a1 with no
  `move v0,a1`: fdiff 1, the only differing line is +0x7d8 (`move v1,a1` vs target `li v1,3`). A sel read BEFORE the test
  does not help (`behaviourFadeOutWithinZone(sel)` / `actorSetTargetSpeed(gCurrentActor, sel)` before the call: the par
  reads $a1, the equ still reads v0, spilled to sp+44 across the inserted jal). Two equ reads in successive blocks
  (`sel == 0x35 ? 2 : sel == 0x36 ? 4 : 3`) both read v0, so the dispatch-block vs later-block position is not what stops
  it. Between the test and the jal at +0x7e4 the only zero-cost read of sel is a call argument already resident in
  $a1, i.e. the spare argument itself. Also measured: inner `switch (sel) { case 0x35: ... default: ... }` with two calls
  20, with a `bone` local 8; `u8 bone = 3; if (sel == 0x35) bone = 2;` 8; sel re-read at the end of each phase arm
  (the first if-chain's style, mirroring the per-path reloads at 0x39c/0x3cc/0x420) 32, still `move v0,a1`/`bne v0,at`.
- diagnose nohit, lever (c) callee evidence: all 37 `jal actorTrackBoneTowardTarget` sites in the expected objects of
  boss/9C60, global/12E800, B1F60, B2CE0, B5EC0, BB300, C2A90, C4620, C8C10 and minecart/25F0 read a1 only by
  residence: a previous call's delay-slot argument (9C60 0x2a0 `li a1,1`, 0x660; 12E800 0x2364; BB300 0xb50, 0xc04,
  0xc88), a value from another path (12E800 0x2b48, minecart 0x1c50), or the caller's own selector home (B2CE0
  `lbu a1,340(t2)` at 0xba0/0x20e4 read by `bne a1,at`; B5EC0 `move a1,a0`). No caller sets a1 for the call, so a
  2-parameter owner prototype is not data-proven (owner +0x8 `andi a1,a0,0xff`).
- variants.py scan of the assignment-in-switch copy (t/p_s1.c, 45 recipes): best 4 = baseline, no zero.
- permute (start body t/p_s1.c: shared u8 prototype, no spare argument, `switch (sel = gCurrentActor->state)`; -j 2,
  900 s, 13466 iterations; setup direct score 364, run base 165): best 165, no output below base.
- review nohit: fake=1/0 goto=0 casts=2 kept (the K&R (u8) arguments) protos=1 steer uninit=0 warn=0.

2026-11-20 Cleanfunc_806B13B4b anthropic/claude-opus-5-5 (unit "2026-11-20: cleanup Cleanfunc_806B13B4b", base 827913fc)
- diagnose nohit, re-measurement under director ruling RQ3 (terminal like D1) after the file-scope edit 2fcc4355
  (D_80750600 .data definition moved into the TU, extern dropped; body unchanged since d09e1e2a). Throwaway t/t1.c
  (PROTO_SKIP define + K&R decl + spare sel dropped, shared u8 header): fdiff 1, the same 3 lines: target `beqz at`
  0x434 with `addiu t0,%lo(gBehaviourWorkState)` in its slot vs t1 `addiu t0` 0x434 / `beqz` 0x438 / `move v0,a1`
  0x43c; target `bne a1,at` 0x9c8 vs t1 `bne v0,at` 0x9cc; function grows 4 (the trailing pad nop absorbs it).
  uopt -l5/-l6: sel is now ucode id 1376 (was 1360); bit 54 `uadd{120|0}` of sel active only in t1, adjsave 1.5,
  live bb29 -> bb122, colour 1 = $v0, in sel interference list; sel cand bit 14 colour 4 = $a1 (forbidden 1 2 3 14)
  reaches bb122 only in the base (adjsave 2.23 base, 2.45 t1). `variants.py scan` of t1: 45 variants, best full=4 =
  baseline. Owner 1295B0 +0x8 (0x5a0) `andi a1,a0,0xff` unchanged. PROTO_SKIP + K&R decl kept.
- 2026-11-24 CleankongItemEnemyStateUpdate (unit "2026-11-24: cleanup CleankongItemEnemyStateUpdate", base b9a69764,
  file text unchanged since the rename) diagnose nohit, re-measure after the 50304ca5 knowledge corrections
  (Q0639/Q1167 corrected, Q1607 added: B2CE0 one-argument calls match; B5EC0 named as a real spare argument).
  Plain form t/plain.c (skip + K&R decl + spare sel dropped, shared u8 header): fdiff 1, full=4 text=3, the same
  3 lines (beqz 0x438 + `move v0,a1` 0x43c vs target beqz 0x434; `bne v0,at` 0x9cc vs `bne a1,at` 0x9c8); uopt -l6:
  bit 54 `uadd{1376|0}{0}` assigned colour 1 = v0 (unassigned in the base). Owner (u8, s32) stand-in (skip + local
  `void actorTrackBoneTowardTarget(u8, s32);`, sel passed at 0x62c/0x97c/0x9d8, t/owner1.c): full=10, frame
  0x28 -> 0x30, a1 spilled to sp+0x2c across kongItemEnemyTryGroundSlam/TryAttack; `gCurrentActor->state` as the
  0x97c spare (t/owner2.c): full=21 (`lbu a1,0x154(t3)` at 0x968 for `lbu t4`). B2CE0 behaviourMeleePatrolEnemyUpdate
  (func_806AE588) one-argument form transplanted whole: `switch (gCurrentActor->state)` + `(gCurrentActor->state
  == 0x35) ? 2 : 3` full=53 (t/b1.c, `(u8)` cast t/b2.c the same: sel moves a1 -> v1 at the pre-switch
  `move a1,a0` 0x28c/0x2a4/0x2c4 plus a v0 copy); the field test alone under `switch (sel)` full=21 (t/b4.c:
  `move v0,a0` beside those three, gActorGlobalState base v1 -> a3). `variants.py scan` of t/plain.c: 54 variants,
  best full=4 = baseline. `quality.py sweep` of the copy: 1 site, 0 hits. PROTO_SKIP + K&R decl kept (RQ3).
- review nohit: fake=1/0 goto=0 casts=2 kept (andi-executing `(u8)` conversions) protos=1 steer uninit=0 warn=0.

## Untried ideas
- none natural left (re-confirmed 2026-11-17 Cleanfunc_806B13B4: the copy is avoided only by a later read of sel
  before the jal, i.e. the spare argument, or by a non-folding selector expression such as `^ 0`). Every form that restores $a1 in bb122 adds a read of the selector (the spare argument) or
  an alias of it: the permuter copy temp, or the entryState snapshot (both ruled steer swaps). It would need a
  callee-side change (owner 1295B0, one real u8 parameter) that nobody has evidence for.

## Evidence
- target +0x234..+0x244 (object 0x428..0x438): `addiu t9,a1,-1` / `sltiu at,t9,0x40` / `beqz at,+0x938` with
  `addiu t0,..gBehaviourWorkState` in the delay slot (no copy of sel); every path in sets a1 by `move a1,a0`.
- target +0x7d0..+0x7e8 (object 0x9c4..0x9dc): `li at,0x35; bne a1,at; li v1,3; b; li v1,2; jal actorTrackBoneTowardTarget; andi a0,v1,0xff`.
- owner 1295B0 actorTrackBoneTowardTarget +0x8: `andi a1,a0,0xff` (a1 written before read): one real parameter.
- target 0x95c..0x970 (1/0x10/0x23 block): `lbu t4,0x154(t3)`; `bne t4,at` — the field, not a redefined sel, so the
  func_806AFB58 route (its 0x23-block `state = gCurrentActor->state`) is excluded.
- sibling B2CE0 func_806AFB58 0x2144..0x215c has the same call-block code (`bne a1,at`) with no spare argument.
- uopt t.O (t1 = consolidated): dispatch `lod a1; ldc 0; add; str v0; lod v0; xjp 1-64`, case block `lod v0; ldc 53; equ`;
  base: `lod a1; ldc 0; add; xjp`, case block `lod a1; ldc 53; equ`. `switch (sel ^ 0)`: `xor` instead of `add`, no copy.
- no caller of actorTrackBoneTowardTarget loads a1 for the call (37 jal sites, 10 objects).
- base 827913fc (after 2fcc4355): func at .text 0x1f4; dispatch `lbu a0,340(s0)` 0x420, `move a1,a0` 0x424, other
  path `lbu a0,340(s0)` 0x9b8 / `b` / `move a1,a0` 0x9c0; case block 0x9c4..0x9dc, `jal actorTrackBoneTowardTarget` 0x9d8.
- B2CE0 behaviourMeleePatrolEnemyUpdate (func_806AE588) 0xbf8..0xc10: `lbu a0,340(s0)` / `b` / `move a1,a0`, then
  `li at,53; bne a1,at` at 0xc04/0xc08: its C reads `gCurrentActor->state` in both the switch and the test, with no
  sel local in a pre-switch if-chain. Transplanted into B5EC0, whose if-chain (0x27c..0x2c4) keeps sel in a1 via
  `move a1,a0`, that spelling moves sel to v1 there (full=53, t/b1.c): measured, the sibling form does not transfer.
- base b9a69764: same offsets as 827913fc; owner 1295B0 `actorTrackBoneTowardTarget` at .text 0x598, `andi a1,a0,0xff` 0x5a0.
