# hudPauseMenuRender (global, src/global/ACDC0.c)

## Sites
- **6bd641/01af71 proto-steer** (kept; not this unit's): a local `renderRotatedSprite` declaration with a u8 `siz` keeps the constant-2 web in $s8, so case 0 passes `move a3,s8`. The shared 90D80 prototype gives `li a3,2` at 0x1638/0x16b8. Owner 90D80 is blocked (pending.md round 29).
- **f38e4a byte-offset entry** (FIXED 2026-11-15): `sPauseTextLists` is `HudTextList *[2]` (`HudTextList { HudTextEntry entries[10]; }`, the 0x1E0 buffer split at +10 entries); `(it->entries + j)->f` gives base-first `addu v0,s2,t7` at 0x12f8 for all eight loop-1 reads. `it->entries[j]`/`&it->entries[j]` stay index-first (272).
- **e1b0a2 -> 766e68 s64 pair** (OPEN): `(u16)(off * 4) + (s16)(s64)(s32)(fa * flyX)`. The (u16) mask on off*4 is a deleted no-op that moves off*4 from the ring front t3 to t4 (Q0374); with the s64 conversion the trunc result lands t5. Target: `sll t4,s0,2` (0x1324), `mfc1 t5,$f10` (0x1344), `addu s0,t4,t5` (0x134c), `mul.s $f8,$f0,$f6` (0x131c).
- **5ed6ef -> a87eed (u16) y steer** (OPEN): `y += (u16)(s32)(fa * flyY)` with s16 `y`; without the `(u16)` the flyY mfc1 lands t3 not t4 at 0x1350 (116-358).
- **fa96af -> c4e347 (u32)off steer** (OPEN): `off = (s16)((u32)off + offsetX * 4)`; without `(u32)` the addu at 0x1364 becomes `addu t8,t7,s0` (full=1).
- **b371d1 dead-if** (OPEN): `list` is homed at 0x13C(sp) (`sw v0,0x13c(sp)` at 0x126c, `lw a0,0x13c(sp)` at 0x1278). Without it, list goes to $s0 (`move s0,v0`) (Q0585).
- **498f25 dead-if** (EXHAUSTED, class 1): the dead `D_80750530` test keeps $t2 coloured by uopt (case-2 table address at 0x1408/0x1cec/0x1d30/0x1e44) (Q0583).
- FIXED earlier: fc512f, 4cca45, 744852, 1c9898.

## Attempts
- **2026-11-14** HackhudPauseMenuRender (claude-opus-5-5, two sessions): see drafts dossier (140 entry spellings, s64/u16/u32 probes, permuter 1200 s, b371d1 role swaps/positions).
- **2026-11-15 U HackhudPauseMenuRender3 claude-opus-5-5:high** (base 63c0bd1c):
  - f38e4a deep-base census (Q0813): `(&it[0] + j)` 0 (Q0813 steer), `HudTextList *it` with `(it->entries + j)` 0, `&it->entries[j]` 272, `HudTextEntry (*it)[10]` with `&(*it)[j]` 272, `void *it` with `(HudTextEntry *)it + j` 0 (cast steer) / `&((HudTextEntry *)it)[j]` 272, `&sPauseTextLists[i][j]` 264. Applied the HudTextList retype (extern, `+ 1` in hudPauseMenuUpdate, `->entries` in hudPauseMenuAddCounter): fdiff OK.
  - e1b0a2/5ed6ef/fa96af statement-shape census on the HudTextList base (179 + 72 bodies): best natural `off = (s32)(fa * flyX) + off * 4` full=3 (trunc scratch t3, mfc1 t4, sll t5; mul.s operands flipped); `(flyX * fa)`, `4 * off` the same 3; all 20 interleavings of the six x/y statements x {x5, (s16)(s32) first, (s16)(off*4)} x {(u32), plain} 3-17. Without the y (u16): best 116. Without (u32): 1. as1probe scan of the full=3 body: 0 improving single edits (operand order comes from uopt, not ugen).
  - b371d1: list reused in a later web (case-3 nested hudDrawScaledText via list; `list = dl` before gSPEndDisplayList) 5 each; list as loop-1 cursor then `dl = list` 517.
  - reconstruct (HudTextList reads, trunc-first x, plain y, no u32, no dead test): 316 (311 with the dead test).
- **2026-11-15 U HackhudPauseMenuRender4 anthropic/claude-opus-5-5:high** (base 1a9860aa):
  - 6bd641/01af71 consolidate re-measured (no PROTO_SKIP, no local declaration, shared 90D80 s32 siz) after the HudTextList retype, Carve56 statics and 114aeeb1: full=400, only `li a3,2` vs target `move a3,s8` at 0x1638/0x16b8 (s8 = `li s8,2` at 0x12a0). Unchanged; pair stays FAKE per the pending.md ruling.
  - Call-site `(u8)2` under the s32 prototype (first, second or both calls): cfe folds it to the literal, full=400 each.
  - Entry pointer local `HudTextEntry *e = it->entries + j` (and `&it->entries[j]`) for all eight loop-1 reads: e takes a frame word (0x1A0 -> 0x1A8) and the `style == 2` compare loads `li at,2` (0x12e4) instead of using s8: full=385. On that body: no (s64) 320, no y (u16) 379, no (u32) 385, all three casts dropped 389, trunc-first x 395.
  - Removal measurements on the base: d4f3b3 (function-end dead test) full=6012 (.rodata/reloc mismatches too), b371d1 full=615.
- **2026-11-16 U HackhudPauseMenuRender5 anthropic/claude-opus-5-5:high** (base 22f598c3):
  - Removal on this base: b371d1 full=5 (only the list home: `move s0,v0`, `sw s0,4(v0)`, `move a0,s0`). uopt -l6: with the test list (cand 19, M -100) splits 19 -> 666, 666 gets reg 3 ($a0), 19 not coloured; without it 19 takes $s0 whole. `list = dl` at the switch head (dead store, dropped) 5; list declared before ret 6.
  - Untried idea 3 tested: `HudTextEntry *e = it->entries + j` with the frame word paid by deleting the case-3 block `f32 fb` shadow (frame back to 0x1A0; the deletion alone is 7, only the 0xA8 spill moves to 0xAC): full=371. i leaves 0x158(sp) for $s8 (`move s8,zero` at 0x129c) and the constant-2 web loses $s8 (`li at,2` before the style bnel). e at function scope 371, e except the style read 371, + case-0 `s16 y` shadow deleted 366, + case-0 `f32 fd` shadow deleted 399, + all three loop-1 casts dropped 377.
  - Dedicated loop-1 x local (Q0601 role split) instead of reusing off, frame paid by the case-3 shadow deletion, 90 bodies (s16/s32/u16, block/function scope, 5 x forms x 3 offsetX forms): best 71 (s32 x, base cast expressions). x leaves $s0 (`lh v1,8(v0)`), list colours $s8, the 2-web moves to $s5: off's case-1/case-2 webs (one candidate per variable) are what keep x in $s0.
  - variants.py scan (197): zeros only for cosmetic swaps/float/width/declswap; `off` as u32 25 but makes the case-2 slide compares unsigned. quality sweep: 0 hits.
- **2026-11-16 U HackhudPauseMenuRender6 anthropic/claude-opus-5-5:high** (base a543051e):
  - Consolidate re-measured (no PROTO_SKIP, no local declaration): full=2 on this base (only `li a3,2` vs `move a3,s8` at 0x1638/0x16b8); 8 on the dy body below. b371d1 removal 5 on the base, 11 on the dy body.
  - a87eed: function-scope `s16 dy; ... dy = fa * flyY; y += dy;` (named s16 temp, ordinary C) gives the t3 -> t4 ring advance through its deleted store narrowing (mfc1 t4 at 0x1350 matches): full=6 with every other steer kept. Left: uopt colours dy (cand 86, M -76) $v1 at -zdbug:6, so hud's loop-1 piece (cand 3 -> 659) takes $a0 (`lw a0,0x15C(sp)` at 0x12d8/0x12ec, target v1), and the standalone product swaps `mul.s $f18` operands (0x1328, Q0966). dy only adjacent to y in the declarations (positions 4-7: 6; elsewhere 8-51); block scope (loop/if/for-i) 51; 105 statement orders and 24 use positions 6-19; `y = e->y * 4` combined 6; `y = y * 4 + dy` 314. Without a local: (s16)(f) 308, (u16)(f) 56, (s16)(y + ...) 311, y as s32/u16 180-525, `y = fa * flyY; y += e->y * 4` 312.
  - x on the dy body: plain forms re-run: `off = (s32)(fa * flyX) + off * 4` with `(s16)(off + offsetX * 4)` 10 (with the dead test), `off * 4 + (s32)(...)` 106, `off *= 4; off += ...` 17; s16/u16 `dx` named temps (`dx = e->x * 4`, `dx = off * 4`, `dx = fa * flyX`) 62-374; dedicated x local with dy 102-422.
  - b371d1 (Q1055 one-candidate hypothesis): `void *list` reused as the loop-1 table pointer (it role): 13 (list colours $s4 and is never homed; it moves s2 -> s4).
  - Reconstruct (natural loop 1: `(s32)(fa * flyX) + off * 4`, s16 dy, `(s16)(off + offsetX * 4)`, no u16/u32/s64, no dead test, shared s32 prototype): full=17 (15 under the local u8 declaration, 10 with the b371d1 test). Left: list home, hud $a0, both mul.s orders, x ring t4/t5, `addu t8,t7,s0`. With the y (u16) kept instead of dy: 4 (x mul.s order, sll/mfc1 t5/t4, addu order).
  - Permuter 900 s (-j 2) each: dy body base 35 -> 20 only via a new dead `if (!hubWorld) {}` before the dy statement; natural reconstruct base 65 -> 65.
  - Review: case-1 `j = tab->kong[...].goldenBananas[...]` reuse is load-bearing (inline 98, via cnt 340); not tagged (reused-local style, Q1055).

## Untried ideas
- A narrowing source for y that is not a uopt candidate in loop 1's last block (dy takes $v1 from hud's piece), or that keeps the `A + (s32)(f)` evaluation order (fa-first mul.s, Q0966) (Q0374).
- A natural source for the t3 -> t4 ring advance before the x trunc that also keeps `A + (s32)(f)` order: every named-temp form tried flips mul.s or loses the ring (Q0374, Q0966).
- Making list live through loop 1 with a use that emits no code (Q0585); none found in the target.

## Evidence
- Frame 0x1A0. Homes: hubWorld 0x138, list 0x13C, ret 0x140, tab 0x144, i 0x158, hud 0x15C, buf 0x160 (`addiu s0,sp,352` at 0x1920); 0xA8 is a case-0 f32 spill (`swc1 $f6,0xA8(sp)` at 0x14b0, `lwc1 $f18` at 0x15d4).
- The constant-2 web in $s8 (`li s8,2` at 0x12a0) feeds the loop-1 `style == 2` bnel (0x1300), the switch `case 2` beq (0x1404) and, under the u8 local prototype, both case-0 renderRotatedSprite 4th args.
- Loop 1: `li s5,24` (0x12a4) + `multu s3,s5` (0x12e8), entry address `addu v0,s2,t7` (0x12f8) shared by all eight reads; s4 = &sPauseTextCounts[i] (0x12c4), s6 = hud + i*2 (0x12e4).
- ugen (as1probe dis) for the x statement in the matching body: off*4 mul, (u16) and, l.s, `mul.s $f8,$f0,$f6`, `trunc.w.s $f10,$f8,$13`, mfc1, s64 moves/sra, `addu $16,$12,$13`; trunc-first form: `trunc.w.s $f10,$f8,$11`, mfc1, mul, `addu $16,$12,$13` with the operands reversed.
- sPauseTextLists[0] = heapAlloc(0x1E0); sPauseTextLists[1] = sPauseTextLists[0] + 10 entries (hudPauseMenuUpdate).

## Lead ruling (Lead5, 2026-11-15)
f38e4a -> a97e00: the (u8 *) byte-offset pun is retired by the HudTextList retype, but `(it->entries + j)->f` is chosen for codegen (it->entries[j] 272), so it stays tagged per the Q0816 precedent (pun retired, tag kept).
