# actorBannerTextRender (global, src/global/A2F10.c)

## Sites
- 0c76ca noop-arith: `switch (sel ^ 0)`. KEPT (FAKE).
  - The target dispatches on a v0 copy of sel (`move v0,a3` in the blez delay slot) while blez and the case bodies use a3.
  - Property `^ 0` supplies (2026-11-17f census): cfe emits the switch temp (vreg -200, `str s32 Mmt -200`) in BOTH `switch (sel)` and `switch (sel ^ 0)`; the only cfe difference is `ldc 0; xor`. uopt copy-propagates the temp away in the plain form (`les`/`xjp`/`equ` read `$a3`, Mmt len 212), but with `^ 0` it substitutes the unfolded expression `uxor{sel}{0}` (candidate bit 69, sel = bit 62/-172vreg), which is coloured uopt reg 1 (`$v0`; sel `$a3`). ugen lowers the xor as `move $2,$7; ble $2,0,$36`, and as1 fills the blez delay slot with that move and rewrites the branch operand to `$7` (0x1950/0x1954).

## Attempts
- 2026-11-10 round 8 CleanA2F10: switch(sel), switch(arg1->unk15F), u8 sel, switch(sel = ...); diagnose; permuter best=0 = `^ 0` itself.
- 2026-11-11 round 16 Rev16K: plain switch(sel) (case range test `addiu t9,a3,-0x1e`); permuter best=0 restores `^ 0` (Q0634).
- 2026-11-14 HackactorBannerTextRender: selector casts and widths, field selector, extra local, line joins, as1probe scan; see the ledger for line counts.
  - Nearest form: `(u8)sel` at 2 lines, where blez uses v0 instead of a3.
- 2026-11-17 cleanup CleanactorBannerTextRender (anthropic/claude-opus-5-5): cfe/uopt census (above) -> fdiff 1, 3 lines for the plain form.
  - Copy-propagation is per use: a second store to the shared temp (diagnostic 2-label `switch (centered)`, 8 refs to -200) still leaves the first dispatch on `$a3` (3 lines + 29 from the new switch); a second definition of sel in the default arm (`sel = 0xA - (sel & 0x3F)` before `_sprintf`) does not keep the temp either (7 lines).
  - A no-op conversion is folded like a copy: `u32 sel; switch ((s32)sel)` = 3 lines (same as plain).
  - Narrowing casts survive but ugen emits `and $2,$7,255` (not `move`): as1 does not forward it into the delay slot (it rewrites it to `move v0,a3` after scheduling), so `blez v0` (the 2-line `(u8)sel`).
  - Natural selector sources (all 0 hacks): `u32 sel` + `switch (actor->unk15F)` 5; `switch (sel = actor->unk15F)` 3; sel only as selector with bodies re-reading the field 3; s32 sel + field selector 5 (three registers: load v0, sel a3, temp v1); no local, all field reads 49 (frame +8, load v1, promoted a3, temp v0); u8 sel 5 (two registers but swapped: load v0, promoted copy a3 for dispatch+default); u8/u16 sel with `u` masks 50-58; u32 sel plain 4 (`beqz`, unsigned).
  - variants.py scan on the plain form: 38 variants, best 3 (no zero).
  - permuter 900 s -j 2 from `(u8)sel` with hack-free weights (33.5k iterations, base 200, best 30, no zero): best = `u8 sel` (fdiff 5: load v0, copy a3, colours swapped); 39/64 = u8 copy-alias chains (steers).
  - Review: dropped m2c conversion casts (`(f64)` on f32 fields/width, `(f32)` on assignments, `(s16)` on textDrawStringVtx arguments); fdiff OK.

## Untried ideas
- None natural left: every expression uopt keeps as its own candidate and ugen lowers to `move` is a no-op operator (`^ 0`, `| 0`); conversions are folded (`(s32)` of u32) or lowered to `and` (`(u8)`).

## Evidence
- Target 0x1948 `lbu a3,351(t8)`; 0x1950 `blez a3`; 0x1954 `move v0,a3`; 0x1958 `addiu t9,v0,-30`; 0x197c `bnez v0`; bodies use a3 (0x1998 `sll t1,a3,2`, 0x19c0 `andi t2,a3,0x80`, 0x1a70 `move a2,a3`).
- ugen (hack): `lbu $7,351($24); move $2,$7; ble $2,0,$36; addu $25,$2,-30` -> as1 output `blez a3; move v0,a3`.
- ugen (`(u8)sel`): `and $2,$7,255; ble $2,0,$36` -> as1 output `move v0,a3; blez v0; addiu t9,v0,-30`.
