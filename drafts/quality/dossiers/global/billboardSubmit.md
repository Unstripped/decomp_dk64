# billboardSubmit (global, src/global/61AA0.c)
## Sites
global:8065D254:dead-if:95b7e4 dead-if (FIXED 2026-11-17f): `if ((u32)gBillboardCache[i].lastUsedFrame == 0xFFFFFFFF) {}` before loop 2 opened a u32 -1 web (lr 200, $a0) with needreglod at bb15, putting `li a0,-1` in the `bnez v0,0x638` slot at 0x590 ahead of the loop-2 IV setup (`sll t4,zero,2` at 0x594).
global:8065D254:other:53d71a other (FIXED 2026-11-17f): `(u32)... == 0xFFFFFFFF` in loop 2 split the -1 constant into an s32 web (loop 1, lr 199) and a u32 web (loop 2, lr 200) so $a0 is reloaded at 0x590.
global:8065D254:other:7eeb4a other (FIXED 2026-11-17f): `gBillboardCache[i * 1]` kept the lastUsedFrame store address (`sw t9,%lo(gBillboardCache)(at)` at 0x670, i*12 recomputed from $t0 at 0x63c) apart from the $v1 IV / sp+0x2c address.
global:8065D254:other:dba036 (untagged, r38): `found = FALSE;` re-init in the `!found` block is real: `move v0,zero` at 0x5ac; dropping it scores 4.
All three were stand-ins for one thing: loop 1 written as a do-while instead of a pre-tested `while`.
## Attempts
2026-11-09..11-13 (rounds 9, 14, 17, 20, 30, 38; see `quality.py history billboardSubmit`): dead-read/u32/i*1 removals, signed and unsigned compares, for/break and natural rewrites with loop 1 a do-while, permuter runs (best 60/100/460, only no-op `^ 0` outputs) -> fdiff 1.
2026-11-17 "2026-11-17: cleanup CleanbillboardSubmit" CleanbillboardSubmit anthropic/claude-opus-5-5: loop 1 `do {...} while ((i < 4) && !found);` -> `while ((i < 4) && !found) {...}`, dead read dropped, loop-2 compare `== -1`, plain `[i]` -> variants.py full=0, fdiff 0 (FIXED, FAKE 3 -> 0).
Measured on the way (variants.py try full=): do-while loop 1 + all three removed 185; do-while + only i*1 removed 184; do-while + only dead read removed 2; do-while + signed compare, no dead read, i*1 kept 1; while loop 1 + dead read and u32 kept, plain [i] 0; while loop 1 + u32 compare without dead read 2; while loop 1 + loop 2 as do-while 171; while loop 1 without the `found = FALSE` re-init 4.
## Untried ideas
none open: function has no hack sites.
## Evidence
- Entry block: `move v0,zero` 0x4e4 (found), `move t0,zero` 0x4ec (i): inits before the early returns; loop-1 IV init from $t0 at 0x520-0x53c, loop-2 IV init from $zero at 0x594-0x5b0 (Q0093 shape).
- Loop 1 0x54c-0x588: `li a0,-1` at 0x54c (preheader), `beql a0,t2` / `bnel a1,t3`, found path `b 0x578; li v0,1`, exit test `slti at,t0,4; beqz at` then `beqzl v0` (while (i < 4 && !found), if/else i++).
- `bnez v0,0x638` at 0x58c with `li a0,-1` in its slot (0x590): second reglod of the one s32 -1 web; uopt -l5 (final copy): web lr 192 reg 3 needreglod at bb9 and bb16, bb16 = `if (!found)` block with preds bb6/bb7 (folded while entry test) besides the loop-1 exits; do-while form: web lr 190, single needreglod at bb7.
- Merge 0x638-0x670: `sll t2,t0,2; subu; sll` then `sw t9,%lo(gBillboardCache)(at)` (address recomputed, not the $v1 IV), then `sb t0,0x102(v0)` cacheIndex, `sb t5,0x106(v0)` alpha.
- !found block 0x5ec-0x634: `&gBillboardCache[i]` in $v1 saved at sp+0x2c across `assetLoad`, i saved at sp+0xd0.
