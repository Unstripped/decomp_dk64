# slotQueueAddValue (global, src/global/FCCD0.c)
## Sites
global:806F91B4:other:78fc23 other (copy-only, final copy): `slotQueueGetAddress((u32)player)`: the unsigned arg to the K&R callee is the raw u8 load, so one post-call `lbu a0,87(sp)` (0x1208) feeds the 0x306 index and the call; plain `player` promotes through the (int) ucvt candidate shared with the playerGetResolvedKongId/slotQueueGetMaxValue args and the call takes `lw a0,0x28(sp)` from its spill.
Base sites (all removed in the final copy):
global:806F91B4:other:ccffb3 other: `pa = &player` makes the u8 param address-taken, so every block reloads `lbu a0,87(sp)` (calls kill it); without it the (int)player cvt candidate spans blocks and the slotQueueGetAddress K&R arg comes from its spill (`lw a0,0x28(sp)`) instead of the shared post-call `lbu a0,87(sp)`.
global:806F91B4:other:5d0eea other: s32 copy of player homed at sp+0x28 (last declared local): `sw a0,40(sp)` in the playerGetResolvedKongId delay slot, `lw a1,40(sp)` into slotQueueGetMaxValue.
global:806F91B4:dead-if:1606fa dead-if: keeps `slots` live past `counter = entry->value`; without it entry moves a0 -> v1 and counter v1 -> v0 (uopt cand 28 entry / 46 counter recoloured).
global:806F91B4:other:dbac2d other: `slots + slot*0x30` recomputed into a2 (`addu a2,t0,t2` at 0x12ac) and spilled `sw a2,32(sp)` across slotQueueGetMaxValue, instead of reusing entry (a0).
global:806F91B4:other:ad98d7 other: post-call re-read through a2 (`lw a2,32(sp); lw v1,0(a2)` at 0x12f0).
global:806F91B4:other:57a90d other: world index shares `value`'s slot (sp+0x34); a separate local adds a declared word and shifts the sp+0x24/0x20 uopt spills.
global:806F91B4:other:daef12 other: flag index reuses `slots`; passing flagGridIndex() straight to flagSet adds a cfe hidden temp word.
global:806F91B4:dead-if:2d3b87 dead-if: `if (playerIdx) {}` at the end of the slot!=10/12 block; without it slot*0x30 (t2) is spilled at its definition (`sw t2,0x24(sp)` at 0x126c) instead of on the two call paths (0x12c8, 0x12e0).

## Attempts
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: frame census: target = 10 word locals sp+0x28..0x4f (kongInv 0x48, flag 0x3c, total 0x38, s32 player 0x28) + uopt spills t2 0x24, a2 0x20.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: separate world local in counter's slot (counter dropped) -> variants full=7; dropping counter alone -> 7 (counter named temp matters for entry/counter colours).
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: kong id passed inline into the inventory index (frees `value`) -> 33 (player load before the call).
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: K&R definition of slotQueueAddValue (base body) -> 0, natural body -> unchanged 71/75: K&R vs ANSI definition is irrelevant here.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: natural body N3 (no pa, no playerIdx, no dead ifs, typed SlotQueueSlot *slots, separate kong/world, flagGridIndex passed directly; 8 declared locals) -> 71: frame 0x50 right and the player cvt spill lands at sp+0x28 by itself (uopt spill, not a declared local).
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: N3 with `slotQueueGetAddress((u32)player)` -> 40: the whole entry/first two blocks match (shared post-call lbu a0,87(sp) for the 0x306 index and the K&R arg, sw a0,0x28 / lw a1,0x28 for kong/max); left: t2 spill at definition and entry in v1 (same as removing 2d3b87 / 1606fa).
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: ANSI `s32 slotQueueGetAddress(u8)` definition+declaration (base bodies) -> slotQueueInit (+move at 0x488) and slotQueueSetShownValue (& 0xFF double andi) break: no.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: base with kong call taking playerIdx -> 0 (pa kept), without pa -> 78.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: `(unsigned)`/`(u32)` arg -> 40; `(u8)`, `(unsigned char)`, `(u16)`, `(s32)`, `(int)` -> 71 (only an unsigned-int widening skips the ucvt).
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: + dead `if (player) {}` at the end of the slot!=10/12 block -> 7 (entry v1 not a0); + `if (slots) {}`, `slots + slot`, swapped add, `!x` forms, nested ifs, named flag index -> 7; counter temp with entry -> frame +1 word.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: s32 slots + cast spellings fix `addu a0,v0,t2` operand order but not the register -> 7.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: NO entry variable, `u16 *counter = slots[slot].value` -> fdiff 0 (typed or s32 slots): block 1 uses the copy-propagated v0 (a0), later blocks the slots variable (a2 = t0 + t2).
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: dead `if (player) {}` replaced by `switch (slot) { case 0xA: case 0xC: break; default: ... }` -> fdiff 0 (Q0844 pattern); `||`-inverted and nested-if forms -> 40.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: plain GetAddress arg with the switch body -> 56; reordered slots/kongInv -> 80; (s32)/(u32) kong arg, (u8) max arg -> 56; variants scan (swap/float/width/declswap, 44 each) on the plain-arg and no-dead forms: no gain.
2026-11-15 HackslotQueueAddValue anthropic/claude-opus-5-5:high: ANSI `s32 slotQueueGetAddress(u8)` (PROTO_SKIP stand-in) + plain arg + slotQueueSetShownValue without `& 0xFF`: slotQueueAddValue matches, only slotQueueInit differs (+4 bytes, 0x750 -> 0x754).
FINAL: fdiff 0, fake 8 -> 1 (78fc23).

## Untried ideas
Retype slotQueueGetAddress to ANSI `s32 slotQueueGetAddress(u8 player)` and re-match slotQueueInit's call (its s32 `player` local holding (u8)i narrows under the u8 prototype, +1 insn) and drop slotQueueSetShownValue's `& 0xFF`: would retire 78fc23 and likely slotQueueGetValue's `pa = &player` pin (same K&R-arg pattern). Needs those functions' owners (this unit).
Return type `SlotQueueSlot *` for slotQueueGetAddress (drops the `(SlotQueueSlot *)` casts at every caller; untested).

## Evidence
0x11e4 frame 0x50; a1 homed 0x54 (u8 at 0x57), a2 homed 0x58 (s16 lh 0x5a per use), slot a3 homed 0x50 and reloaded after slotQueueGetAddress.
0x1204 `sw a0,40(sp)` in the playerGetResolvedKongId delay slot; 0x12ec `lw a1,40(sp)` for slotQueueGetMaxValue.
0x1208 one `lbu a0,87(sp)` feeds both the 0x306 multiply and the slotQueueGetAddress K&R argument.
0x126c entry = v0 + t2 in a0; 0x12ac second `addu a2,t0,t2` from the slots variable (t0), spilled 0x12e4.
0x1314/0x1348 slot == 8 / slot == 0 compiled as t2 == 0x180 / t2 != 0 on the spilled slot*0x30.
0x13ac flag index: `sll a0,v0,16; sra t7,a0,16; move a0,t7` (s32 variable narrowed to the s16 flagSet param).
