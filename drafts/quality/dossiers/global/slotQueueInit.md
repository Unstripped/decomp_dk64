# slotQueueInit (global, src/global/FCCD0.c)

## Sites
- da5663 / 06d21a (proto-steer): the mapGetHubWorldIndex PROTO_SKIP define plus the K&R extern. FIXED 2026-11-15
  (HackslotQueueInit3, consolidate): both dropped so proto/global/3C10.h `u8 mapGetHubWorldIndex(u8, u8)` applies,
  and bitfieldSet/Clear/HasMappedFlag pass `map` instead of `map & 0xFF` (the u8 parameter emits the target's
  `andi a0,a1,0xff`). Whole-object fdiff 0 once slotQueueAddValue had been reconstructed (its 0x1368 residual is gone).
  Owner width untouched (pending.md ruling stands: the 3C10 owner stays u8).
- ab9e8a: dead `player && player`. FIXED earlier (`s32 player = (u8)i`); the player local itself is now gone too (below).
- 0930b5: kongInv two-step (byte offset parked in kongInv, then `(u8 *)inv + (s32)kongInv`). FIXED 2026-11-15
  (HackslotQueueInit3): `kongInv = &inv->kong[playerGetResolvedKongId(i)]; base = slotQueueGetAddress(i); ...
  func_806F8278(i);` with no player local. With the ANSI u8 slotQueueGetAddress (Q0925) the caller converts i itself,
  so the (u8)i CSE temp is loaded straight into a0 and spilled to sp+120; the pun and the s32 player local were both
  steers coupled to the old K&R callee (Q0902).
- (review 2026-11-15) hidden no-op mask `if (flag & 0xFF)` removed: `if (base[j].locked)` re-reads the u8 just stored,
  which is the target's `andi t8,s7,0xff` beside `sb s7,45(s0)` (0x9dc).
- (review 2026-11-15) the 15 one-line `base[j].x = ..; base[j].y = ..;` pairs are load-bearing as1 layout (target
  stores y at +12 before x at +8): tagged `// LAYOUT:` (not sites). Re-measured on the hack-free body: all split
  x-first 32, all split y-first 60, a single split 2.

## Attempts
- 2026-11-15 HackslotQueueInit2 anthropic/claude-opus-5-5:high: diagnose 0930b5 nohit. With the s32 player local,
  every two-statement natural form gets `addu t9,s8,t8` but a 4-byte compiler temp grows the frame 160 -> 168
  (41 lines, every sp offset +8): s32 kongId local + `&inv->kong[kongId]`, s32/u32 byte-offset local (any declaration
  position, or block-scoped), `kongInv = inv->kong; kongInv += id`, `(KongInventory *)inv` then `+=`,
  `&(*inv).kong[id]`. Single-expression forms keep 160 but give `addu t9,t8,s8` (1 line). No kongInv: 265. No inv:
  280-358. s16/u16 offset local: 389/182.
- 2026-11-15 same: WITHOUT the player local (K&R slotQueueGetAddress), every natural form keeps frame 160 and
  `addu t9,s8,t8`; residual 4 lines (`lbu v1,155(sp)` + `move a0,v1` + `sw v1,120(sp)` vs target `lbu a0` /
  `sw a0`). variants scan of that body: no zero (69 variants, best 4). u8 player local: 43.
- 2026-11-15 same: outer loop as `for`: 8 with the inner do-while, 178-181 with the inner for; kept the if/do-while.
- 2026-11-15 same: permute nohit (900 s, base 199 -> best 0) on the no-player-local body; zeros only swap steers.
- 2026-11-15 HackslotQueueInit3 anthropic/claude-opus-5-5:high (base 88434bd1, slotQueueGetAddress already ANSI u8):
  natural no-player-local body (`&inv->kong[playerGetResolvedKongId(i)]`, `slotQueueGetAddress(i)`,
  `func_806F8278(i)`) -> full=0, fdiff 0. Same with `u8 player = i` kept and the natural kongInv: 41; player
  assigned before kongInv: 39.
- 2026-11-15 same: consolidate (drop define + extern) alone -> fdiff 1 (+16 bytes text: bitfield helpers' extra
  andi/move copies); plus helpers passing `map` -> fdiff 0.
- 2026-11-15 same: variants scan of the final body: 69 variants, baseline 0 (comparison swaps all 0).

## Untried ideas
- None left for this function (0 FAKE sites; only the 15 LAYOUT lines, which are as1 line-order layout).

## Evidence
- 0x48c `lbu a0,155(sp)`; 0x4a0 `sw a0,120(sp)` (delay slot of the slotQueueGetAddress jal at 0x49c);
  0xa24 `lbu a0,123(sp)` (func_806F8278 arg, low byte of the 0x78 spill).
- 0x494 `addu t9,s8,t8`; 0x498 `sw t9,132(sp)` (kongInv home); 0xa44 `addiu s8,s8,774` (inv++).
- 0x36c frame `addiu sp,sp,-160`.
- 0x534-0x53c `sw value,0(s0)`, `sw y,12(s0)`, `sw x,8(s0)` (one-line layout).
- 0x9dc `andi t8,s7,0xff` / 0x9e4 `sb s7,45(s0)` (locked store + test).
- 0x1428/0x1468/0x14ac `andi a0,a1,0xff` before the mapGetHubWorldIndex jal (bitfield helpers); 0x143c
  `sllv t8,t7,v0` uses the u8 return unmasked.
