# slotQueueInit (global, src/global/FCCD0.c)

## Sites
- da5663 / 06d21a (proto-steer): the mapGetHubWorldIndex PROTO_SKIP define plus the K&R extern. KEPT, not ORIG. The
  shared u8 prototype matches only if the bitfield helpers pass `map` rather than `map & 0xFF`; then only
  slotQueueAddValue differs (addu v1/a0 at 0x1368). pending.md (closed): u8 mapGetHubWorldIndex(u8, u8) stays because
  func_806BE09C uses v0 unmasked; never retype the 3C10 owner.
- ab9e8a: dead `player && player`. FIXED: `s32 player = (u8)i` (word home of a byte value, Q0808).
- 0930b5: kongInv two-step (byte offset parked in kongInv, then `(u8 *)inv + (s32)kongInv`). KEPT (addu operand
  order at 0x494 + frame size). The kongInv pun is not a reused-local ORIG: the offset (t8) never reaches kongInv's home
  (only the sum is stored, sw t9,132(sp)).
- (review 2026-11-15) hidden no-op mask `if (flag & 0xFF)` removed: `if (base[j].locked)` re-reads the u8 just stored,
  which is the target's `andi t8,s7,0xff` beside `sb s7,45(s0)` (0x9dc).
- (review 2026-11-15) the 15 one-line `base[j].x = ..; base[j].y = ..;` pairs are load-bearing as1 layout (each split
  costs 2 lines: target stores y at +12 before x at +8; y-first on separate lines or one line costs 60): tagged
  `// LAYOUT:` (not sites).

## Attempts
- 2026-11-15 HackslotQueueInit2 anthropic/claude-opus-5-5:high: diagnose 0930b5 nohit. With the s32 player local,
  every two-statement natural form gets `addu t9,s8,t8` but a 4-byte compiler temp grows the frame 160 -> 168
  (41 lines, every sp offset +8): s32 kongId local + `&inv->kong[kongId]`, s32/u32 byte-offset local (any declaration
  position, or block-scoped), `kongInv = inv->kong; kongInv += id`, `(KongInventory *)inv` then `+=`,
  `&(*inv).kong[id]`. Single-expression forms keep 160 but give `addu t9,t8,s8` (1 line): `(u8 *)inv + sizeof * id`,
  `id * sizeof + (u8 *)inv`, `(s32)inv + ...` both orders, `kongInv = inv->kong; kongInv = &kongInv[id]`,
  `kongInv = (KongInventory *)inv; kongInv = kongInv + id`. `kongInv = (KongInventory *)id; kongInv =
  &inv->kong[(s32)kongInv]` matches (same pun). No kongInv (s32/u8/u32/s16/u16 kong index, `inv->kong[kong].field`): 265.
  No inv (`gPlayerInventoryTable[i].`): 280-358. s16/u16 offset local: 389/182.
- 2026-11-15 same: WITHOUT the player local (`slotQueueGetAddress((u8)i)`, `func_806F8278((u8)i)` or `(i)`), every
  natural form (`&inv->kong[id]`, kongId local, `+=`, `&(*inv).kong[id]`) keeps frame 160 and `addu t9,s8,t8`;
  residual 4 lines: `lbu v1,155(sp)` scheduled inside the multiply + `move a0,v1` + `sw v1,120(sp)` vs target
  `lbu a0,155(sp)` / `sw a0,120(sp)` (the (u8)i CSE temp takes the 120 slot). variants scan of that body: no zero
  (69 variants, best 4). u8 player local: 43.
- 2026-11-15 same: outer loop as `for (i = 0; i < gPlayerCount; i++)`: 8 with the inner do-while, 178-181 with the inner
  for; kept the if/do-while.
- 2026-11-15 same: permute nohit (900 s, base 199 -> best 0) on the no-player-local body. Zeros only swap steers:
  `slotQueueGetAddress((unsigned long)(u8)i)` (variants try: `(u32)(u8)i` full=0 with `func_806F8278(i)` or `((u8)i)`;
  `(s32)(u8)i` 4), `flag = (u8)i; func_806F8278(flag)`, `j = (u8)i; slotQueueGetAddress(j)`. The u32-typed argument
  lets the (u8)i CSE temp load straight into a0 (`lbu a0,155(sp)`, `sw a0,120(sp)`), but the target callee narrows
  its K&R u8 param (`andi t6,a0,0xff` at 0x0) and has no other callers, so a u32 prototype is not natural: a cast steer
  in place of the kongInv pun is a swap, not a removal.

## Untried ideas
- From the no-player-local body (np: natural `&inv->kong[id]`, 4 lines): find what puts the (u8)i reload straight into
  a0 (ugen register choice for the CSE temp) - uopt_trace -l 6 on that body to see the temp's live range vs a0.
- da5663/06d21a: nothing new beyond pending.md.

## Evidence
- 0x48c `lbu a0,155(sp)`; 0x4a0 `sw a0,120(sp)`; 0xa24 `lbu a0,123(sp)` (func_806F8278 arg from player's home).
- 0x494 `addu t9,s8,t8`; 0x498 `sw t9,132(sp)` (kongInv home); 0xa44 `addiu s8,s8,774` (inv++).
- 0x36c frame `addiu sp,sp,-160`.
- 0x534-0x53c `sw value,0(s0)`, `sw y,12(s0)`, `sw x,8(s0)` (one-line layout).
- 0x9dc `andi t8,s7,0xff` / 0x9e4 `sb s7,45(s0)` (locked store + test).
- 0x1428/0x1468/0x14ac `andi a0,a1,0xff` before the jal (bitfield helpers).
