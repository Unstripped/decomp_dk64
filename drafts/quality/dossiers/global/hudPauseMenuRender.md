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

## Untried ideas
- A natural source for the t3 -> t4 ring advance before the x trunc (a deleted narrowing on off*4 that is ordinary C, e.g. an s16 intermediate already in the frame) (Q0374).
- Making list live through loop 1 with a use that emits no code (Q0585); none found in the target.
- Entry pointer local `e` with its frame word paid elsewhere (only the e slot and the lost s8 CSE of `style == 2` separate it from the matching register flow; untested whether the s8 reuse returns once the frame matches).

## Evidence
- Frame 0x1A0. Homes: hubWorld 0x138, list 0x13C, ret 0x140, tab 0x144, i 0x158, hud 0x15C, buf 0xA8.
- Loop 1: `li s5,24` (0x12a4) + `multu s3,s5` (0x12e8), entry address `addu v0,s2,t7` (0x12f8) shared by all eight reads; s4 = &sPauseTextCounts[i] (0x12c4), s6 = hud + i*2 (0x12e4).
- ugen (as1probe dis) for the x statement in the matching body: off*4 mul, (u16) and, l.s, `mul.s $f8,$f0,$f6`, `trunc.w.s $f10,$f8,$13`, mfc1, s64 moves/sra, `addu $16,$12,$13`; trunc-first form: `trunc.w.s $f10,$f8,$11`, mfc1, mul, `addu $16,$12,$13` with the operands reversed.
- sPauseTextLists[0] = heapAlloc(0x1E0); sPauseTextLists[1] = sPauseTextLists[0] + 10 entries (hudPauseMenuUpdate).

## Lead ruling (Lead5, 2026-11-15)
f38e4a -> a97e00: the (u8 *) byte-offset pun is retired by the HudTextList retype, but `(it->entries + j)->f` is chosen for codegen (it->entries[j] 272), so it stays tagged per the Q0816 precedent (pun retired, tag kept).
