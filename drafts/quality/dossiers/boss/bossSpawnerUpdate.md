# bossSpawnerUpdate (boss, src/boss/DAA0.c)

## Sites
- proto-steer fe0889/59a070 (sfxAllocateChannel K&R): FIXED. Shared `void sfxAllocateChannel(s32, f32)` with `1.0` (double literal): built per call `lui a1,0x3f80`; `1.0f` joins the function 1.0f FP web and is passed `mfc1 a1,$f2`.
- proto-steer 4c08f3/3cd67a (sfxPlayOnFreeSlot K&R): FIXED. Shared `s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8)` with `63.0, 1.0`: per-call `lui a2,0x427c` / `lui a3,0x3f80`. `63, 1` (int) and `63.0f, 1.0` also match; any `1.0f` fails (Q0354/Q0421). bossFollowerActorUpdate's two calls changed with it.
- other 9b9b60/df676c: see the 2026-11-18b attempts (light position inline isolates the case-1 colouring: 9 lines).
- other a0a7fe (dx reused for randomFloat): FIXED. `f32 r` own local; frame room comes from the old `s32 pad` slot (0x78) plus sharing one x/z float pair between case 1 (player offset) and the light block.
- other 82a569 (cutsceneId as light level): FIXED. `s32 level` in the old pad slot, used for raw level and the `(i << 4) & 0xFF` intensity.
- dead-if f9b7c2 (`if (D_80035B68 == 0) {}` case 1): FIXED via Q0498: D_80035B68/D_80035B6C become function-local statics (only user). Object differs only in relocations (.data+0x68/+0x6c instead of the two global symbols); `fdiff --reloc-ok` RELOC-EQUIV OK, raw words equal except LO16 addends, .data/.rodata bytes identical.
- dead-if 3e88fe (was 0e256f, `if (level && level) {}`): KEPT tagged. The guard splits the block after `level = (i << 4) & 0xFF`, so the first lightAdd's `(u8)level` args are a global copy-propagation product with a late candidate bit (base trace: `ucvtl{and}` bit 443 after `ucvtl{level}` bit 427). spilltemps then gives the call-crossing intensity temp the second slot 0x44 (`sw v0,68(sp)` at 0xeec, `lw v0,68(sp)` at 0xf3c); 0x48 is held by the lower bit. Without the guard same-block forwarding (Q0499) substitutes the expression into the args (double `andi`, v0 home 0x48).
- other 39fa37 (`s32 i`, tagged 2026-11-18, pre-existing): loop counter (t0, home 0x70 spills 0xb8/0xd4, 0x2ec/0x2f4), case 0/1 step threshold (li t0 0x640/0x664/0x770/0x784/0x798) and light magnitude (move t0,v0 0xe60) share one uopt range in t0; never stored to the home outside the loops.
- other 926eea (`s16 j`, tagged 2026-11-18, pre-existing): case 7 loop counter (a1, home 0x52 at 0xc60/0xc6c) and case 0 repeat limit (li a1 0x650/0x668, slt at,t3,a1 0x6a0): merged bit 227 adjsave 14.67 forbidden [1 3] -> $a1; a split limit (adjsave 1.5) takes $v0.
- other 9b9b60 / df676c (`f32 x`/`f32 z`, tagged 2026-11-18, pre-existing; the 2026-11-14 a0a7fe fix made them shared): case 1 player offset ($f12/$f0 at 0x3f0/0x3f4) and light position; a dx/dz split grows the frame 0x80 -> 0x88 and recolours the offsets to $f2/$f12.

## Attempts (2026-11-14, HackbossSpawnerUpdate, anthropic/claude-opus-5-5:high)
- int / double literal args for prototyped f32 params -> fdiff 0 (all four proto sites)
- split local replacing the pad (b1: level, b2: r) -> fdiff 0 each; both together need a 4-byte slot: freed by x/z sharing (g2) -> fdiff 0
- both splits with j/r declaration permutations (240 variants) -> j home 0x52 moves (d_10_15 closest)
- block-scoped r / level -> spill homes -4
- k or i as the level variable -> recolouring of k (v0 vs a1)
- function-local statics D_80035B68 (+B6C) without the case-1 dead test -> RELOC-EQUIV OK
- 3e88fe removal: level types u8..u32, spellings i<<4 / i*16 / (u8), statement moves, u8 intensity local in the 3-byte hole -> nonzero (+1..+3 insns)
- permuter on the 3e88fe-removed base: see ledger

## Attempts (2026-11-15, HackbossSpawnerUpdate2, anthropic/claude-opus-5-5:high)
- review: case 0 `i = 5;` default moved into the `phase == 2` branch (both forms fdiff 0; kept the plain if/else form).
- 3e88fe, deadsweep scores vs target (full): plain removal 23; intensity inline per call (`i << 4`, `i * 16`, `(u8)(i << 4)`) 22, `(i << 4) & 0xFF` inline 39; `u8 c = i << 4` local at three declaration positions 22/80/57; `(u8)level` args 23; ternary abs 26; clamp folded into the intensity ternary 52; `level = 0xF0` / `(i << 4) & 0xFF` if/else 9 (extra `b` + `li 240`); `level = i << 4; level &= 0xFF` 23; `i <<= 4; level = i & 0xFF` 5; `i = (i << 4) & 0xFF` passed as i 33; `level = (level << 4) & 0xFF` with roles of i/level swapped 56.
- local `PROTO_SKIP_lightAdd` + s32 colour params (diagnostic only): 22, same as inline; the caller-side u8 narrowing is not the cause.
- `i <<= 4` (or `i *= 16`, `i = i << 4`, `(u8)i` args, `k = state->side` after the shift) with `i` passed to both calls: full 2. Only difference: the call-crossing intensity temp spills to 0x48 (`sw v0,72(sp)` / `lw v0,72(sp)`) instead of 0x44. `level = i << 4; i = level` and `i <<= 4; level = i` also 2. variants.py scan (120 + width/declswap 67) around it: no zero.
- permuter 900 s from the `i <<= 4` copy (perm_t3, base 8, 35838 iterations): the only 0 re-inserts `if (gCurrentActor) {}` right after `i <<= 4` (another dead guard: confirms a block boundary after the intensity def is what the target needs); no natural output below 8.

## Attempts (2026-11-17, CleanbossFollowerActorUpdate, strength-3, base 2cbbc1af)
- spilltemps emulation (dossier untried idea 2) from `uopt_trace.sh -l 4` node regions: in the target the light-block nodes carry only bit 406 (`(i << 4) & 0xFF`, region from its def through the guard nodes to the call-block entry) and bit 443 (ucvtl{and}, call-block entry to the second lightAdd); they share one node, so 406 holds the first slot 0x48 and 443 takes 0x44. In the `i <<= 4` body (full 2) those nodes carry only bit 424 (ucvtl{i}, live bb169 + bb173), so it takes 0x48. The target therefore needs a second, lower-bit region item in the light block, which only exists when the masked intensity crosses a block boundary before its cvtl use; no other region item (gCurrentActor bit 2, umpy{k}{2} bit 407, the x/z loads) reaches those nodes.
- natural block-end candidates (untried idea 1), deadsweep full: if/else abs + `i <<= 4` 5; x/z moved ahead of `i <<= 4` 18; if/else abs + masked level 26; x/z moved ahead of the masked level def 23; abs spelled `if (i < 0) i = -i` + `i <<= 4` 2. variants.py scan of the `i <<= 4` copy: 195 variants, best 2. sweep: 0 hits (classify class 2).

## Attempts (2026-11-18, CleanbossFollowerActorUpdateb, strength-3, base 2291c741)
- 3e88fe: mask at the u8 call arguments (`i <<= 4` + `i & 0xFF` args 32; `level = i << 4` + `level & 0xFF` args 39); plain removal 23.
- review found the register-only reuses of i (loop counter / step threshold / magnitude), j (repeat limit / loop counter) and x/z (case 1 offset / light position); tagged. Splits with the guard kept: stepLimit s16 (0x64 hole) 411, s32 427; magnitude s8/s16 418, u8 417, s32 438; repeatLimit s8/s16 in the 0x64 hole 8 (a1 -> v0), variants.py scan of it 200 variants best 8; dx/dz 56-58 (frame 0x88).
- reconstruct (all role locals, no guard): s32 locals 134 (frame 0x90), narrow locals packed 152.

## Attempts (2026-11-18, 2026-11-18b: cleanup CleanbossSpawnerUpdate, CleanbossSpawnerUpdate, anthropic/claude-opus-5-5, base f0eac003)
- body since e42248f8 changed by renames only (e495654c); copy renames k -> side, cutsceneId -> kong (fdiff 0, site keys unchanged). sweep: 0 hits.
- x/z (9b9b60/df676c): light position inline (CSE'd `gBossSideOffsetX[side] * 0.33 + gCurrentActor->x`, no x/z locals in the light block): light block 0xe80-0xfec and frame 0x80 match, only case 1 recolours: 9 lines (sub.s $f2/$f12, cvt.d.s $f0; target $f12/$f0, $f2). uopt -l5: x bit 138 adjsave 4.0 -> 2.0, z bit 143 4.0 -> 1.0, so ucvt{x} bit 148 (3.0) colours first and takes $f0; the shared range's light-block use (first f32 arg, cvt.s.d $f12 at 0xefc/0xfc8) is what gives x $f12 and both pieces their rank. Same body: z/x declaration swap 9, x/z declared first 54, case-1 dx/dz block-scoped 11 (pad[2] for the freed words 58), case-1 offsets inline 144, two-step defs (`x = p->x; x -= a->x`) 133-185; variants.py scan 195 variants best 9.
- i (39fa37): loop-counter split (both loops on a new `s32 n`, i keeps threshold + magnitude) 438 (424 with n in r's slot and randomFloat() inline): n adjsave 27.3 forbidden [1-5] -> $a3 (target merged i 13.43, forbidden [1-6] -> $t0), i 3.0 -> $v0; threshold in r's freed slot (`s32 limit`) 423: i 17.4 -> $a3, limit 2.33 -> $v0; magnitude in r's slot 424. randomFloat() inline with `s32 pad` in r's slot alone 14.
- j (926eea): `s16 limit` re-measured 8 (also `s8 limit` beside the s8 locals 8); limit defaulted before the phase if (`limit = 4; if (phase == 2) limit = 0xC`) 11; ternary repeat limit in the compare 32.
- 3e88fe: guard removed on the inline-light body 32; `i <<= 4` + guard removed on it 11 = the 9 case-1 lines + the 0x44 -> 0x48 spill (`sw/lw v0` at 0xeec/0xf3c), so the CSE'd light-position temps add no lower-bit region item.
- reconstruct: natural per-role body (LIGHT_X/LIGHT_Z macros for the light position, dx/dz in case 1, stepLimit/repeatLimit/mag role locals, i and j loop counters only, no guard): 134, frame 0x88.
- permuter perm_xzinl from the inline-light body (9 lines), 905 s, 26885 iterations, base 65: best 40 (output-40-1) only adds a case-1 copy temp (`z = p->x - a->x; x = z;`); no zero.

## Untried ideas
- none left in straight-line C: the 0xe80-0xf24 block has no branch, and a block boundary there without emitted code is a dead guard (or label/loop steer) by construction.
- repeatLimit split is 8 lines (v0 for a1 only): a natural use that forbids v0 across 0x650-0x6a0 in case 0 (none found).
- x/z: a natural case-1 spelling that gives x adjsave >= 3.0 and a $f12 preference without the light block (none found; two-step defs recolour widely).

## Evidence
- D_80035B38 (u8) is compared with -1 in case 0 (`lbu t6` 0x24c, `li at,-1` 0x224, `bnel t6,at` 0x250): the target performs the always-false compare, so `D_80035B38 == -1` is original code, not a steer.
- frame 0x80: s0/s1/ra 0x34/0x38/0x3c, spills v1 0x48 / v0 0x44, j 0x52, cutsceneId 0x5c (lh 0x5e), s8 locals 0x67-0x6b, i 0x70; unaddressed 4-byte locals fill 0x7c,0x78,0x74,0x6c,0x60,0x58,0x54
- light block: `addiu v0,t9,-16; move t0,v0; bgez v0` (level separate from i), `sll t2,t0,4; andi v0,t2,0xff; sw v0,0x44(sp)` and v0 passed straight to the u8 args
- 0xec8 `sll t2,t0,0x4` (t2 is a uopt-coloured temp, the x/z table loads take ring t3/t4 at 0xe80/0xe8c), 0xecc `andi v0,t2,0xff`, 0xeec `sw v0,68(sp)`, 0xf3c `lw v0,68(sp)`; slot 0x44 is also the &D_80035B44[i] induction temp's spill (0x2e4/0x300), 0x48 holds v1/a3 spills (0x54, 0xac, 0x1d8, ...)
