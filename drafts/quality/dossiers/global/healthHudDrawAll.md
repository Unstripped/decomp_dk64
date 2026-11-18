# healthHudDrawAll (global, src/global/10D2D0.c)
## Sites
global:80709344:noop-arith:98a549 noop-arith: FIXED (2026-11-17, CleanhealthHudDrawAll). The base call
`healthHudUpdateDraw(glist, (s16)(playerIndex + 0), (slotOffset ^ 0) + (s32)gPlayerSlots, (s32)gPlayerSlots)` did
three jobs: `(s16)(... + 0)` made the caller narrow (sll a1,s0,16 / sra t2,a1,16 / move a1,t2 at 0xe0c); `^ 0` made
the third argument its own candidate (uxor{slotOffset}{0}) so it was recomputed as addu a2,t0,a3 at 0xe20 instead of
CSE'd with the slot address; the extra 4th argument gave the gPlayerSlots ucvt candidate a second use with an a3
preference (adjsave 10.0 vs the product's 7.5) so it took a3 (lw a3,0(s2) at 0xdbc) and the product t0.
Fixed form: ANSI `Gfx *healthHudUpdateDraw(Gfx *glist, s16 playerIndex, PlayerStruct *hudState)` definition, slot line
`slot = (PlayerStruct *)((s32)gPlayerSlots + playerIndex * 0x2F0)`, call `healthHudUpdateDraw(glist, playerIndex,
&gPlayerSlots[playerIndex])`.
global:80709344:other:01dbfe other: FIXED (2026-11-17, CleanhealthHudDrawAllInline). The lead-tagged
integer-address slot line `slot = (PlayerStruct *)((s32)gPlayerSlots + playerIndex * 0x2F0)` gave the slot address
the base-first addu (addu v0,a3,t0 at 0xdc4) while staying a different tree from the call's `&gPlayerSlots[i]`.
Fixed form: no slot pointer; element reads `gPlayerSlots[playerIndex].active` / `.unk2E2` (into the u16 flags local) /
`.unk2E4`, call argument `&gPlayerSlots[playerIndex]`. No casts left in the function.

## Attempts
2026-11-11..12 rounds 14/16/17/21 (opus low): plain, diagnose, permutes; K&R best 230, ANSI-prototype lane best 10
(constant temp). Round 21: ANSI definition reproduces the narrowing; a3/t0 swap remained.
2026-11-14 HackhealthRefill (opus high): classified the callee as K&R per Q0486; s32 counter + (s16) wrap with ^0
matches; (u32)slotOffset breaks CSE; &gPlayerSlots[i] with 4 args 11 lines.
2026-11-17 2026-11-17: cleanup CleanhealthHudDrawAll CleanhealthHudDrawAll anthropic/claude-opus-5-5 (selector per
harness): measured with the K&R callee: 3 args + both no-ops 4 (a3/t0 swap); 3 args, `(s16)(playerIndex + 0)`,
`&gPlayerSlots[playerIndex]` 4 (same swap); same with the multiply folded into the slot line (no slotOffset local) 0;
then ANSI s16 definition + plain playerIndex 0 (whole object, warn 0); K&R definition + ANSI prototype before or
after it also 0 but adds cfe Warning 642 (rejected). Slot-form scan under ANSI: `&gPlayerSlots[i]` / `gPlayerSlots + i`
slot 26, `(u8 *)gPlayerSlots + i * 0x2F0` 22, `* sizeof(PlayerStruct)` (u32 multiply) 30, `(s32)&gPlayerSlots[i]` 26,
slotOffset local kept 4; `(PlayerStruct *)((s32)gPlayerSlots + i * 0x2F0)` pointer local 0, also as a for loop with
bare truth tests and no (s32) casts on gPlayerCount 0 -> final. fdiff 0, uninit 0, warn 0, sweep: no sites.
2026-11-17 CleanupLead17f: tagged the integer-address slot line (01dbfe) per director ruling turn 37.
2026-11-17 2026-11-17: cleanup CleanhealthHudDrawAllInline CleanhealthHudDrawAllInline anthropic/claude-opus-5-5
(selector per harness): no slot pointer, element reads + `&gPlayerSlots[playerIndex]` call argument (variants.py try):
active test first with the u16 flags local 0; flags inline at every use 0; the 0x20 test as a nested if 0; flags copied
before the active test 3. Final: active first + flags local, whole-object fdiff 0, clint uninit 0, cfe warnings 0,
sweep: no sites. FAKE 1 -> 0.

## Untried ideas
none needed: the function has no hack site left.

## Evidence
- 0xdbc lw a3,0(s2) / 0xdc0 mflo t0 / 0xdc4 addu v0,a3,t0: element address base-first (the reads' uixa{base}{umpy}).
- 0xdc8 lbu t6,0(v0) (active), 0xdd4 lhu v1,738(v0) (unk2E2 -> flags), 0xde4 lbu t8,740(v0) (unk2E4): all three reads
  off the one v0 address, so the reads share one candidate.
- 0xe0c-0xe14 sll a1,s0,16 / sra t2,a1,16 / move a1,t2: call-site narrowing of an s16 variable = s16 prototype in
  scope (Q0666, Q1117); a K&R/unprototyped call passes move a1,s0.
- 0xe20 addu a2,t0,a3 (jal delay slot): third argument recomputed product-first = typed `&gPlayerSlots[i]` (uadd), not
  CSE'd with the reads' address.
- Callee 0x7e4 sw a1,76(sp), 0x7f0/0x7f4 lh a0,78(sp) / lh t6,78(sp): identical for a K&R `s16` and an ANSI `s16`
  parameter that lives across a call, so it does not prove K&R.
- uopt -l5 on the final copy: candidates 7 uilod{1482} (gPlayerSlots load, adjsave 7.5, reg 6 a3), 8 umpy{1600}{752}
  (playerIndex * 0x2F0, 7.5, reg 7 t0), 9 uixa{158}{436} (adjsave 20.0, reg 1 v0) used by uilod{1188} x3; the call
  argument is candidate 24 uadd{436}{158}, a separate tree (no CSE with the reads).
- uopt -l5 control (slot = &gPlayerSlots[i] pointer local): umpy bit 9 before the load bit 10, slot = uadd{436}{158}
  bit 11, and the call argument is the same uadd tree, so it CSEs with the slot (no separate recompute): why every
  typed slot pointer failed.
