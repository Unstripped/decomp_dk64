# hudPauseMenuRender (global, src/global/ACDC0.c)

## Sites
- **6bd641/01af71 proto-steer** (kept; not this unit's): a local `renderRotatedSprite` declaration with a u8 `siz` keeps the constant-2 web in $s8, so case 0 passes `move a3,s8`. The shared 90D80 prototype gives `li a3,2` at 0x1638/0x16b8. Owner 90D80 is blocked (pending.md round 29).
- **fc512f dead-store** (FIXED): `fadeInput0` must be the first float candidate so that it gets $f2 and `fadeInput4` gets $f12. Case 2 at 0x1d9c/0x1da0 and case 3 at 0x1eec/0x1ef0 load `lwc1 $f12,4` then `lwc1 $f2,0` (Q0584).
- **4cca45 value-named constant** (FIXED): `li t3,320` at 0x13ec is converted by `mtc1 t3,$f6` (0x13f8) + `cvt.s.w $f8,$f6` (0x142c). An integer 320 reaches uopt as a non-literal.
- **744852 raw SetPrimColor** (FIXED): the macro's block `_g` costs one frame word (0x1A0 -> 0x1A8, Q0663).
- **1c9898 actor reuse** (FIXED): a separate s32 for `slideY[i] * 4` costs one frame word.
- **f38e4a/eb1c3c byte-offset entry + s64 pair** (OPEN): the ugen scratch ring in loop 1 (0x12e8-0x13c4). Target: `sll t4,s0,2` (0x1324), `mfc1 t5,$f10` (0x1344), `addu s0,t4,t5` (0x134c), `mul.s $f8,$f0,$f6` (0x131c), `addu t8,s0,t7` (0x1364) (Q0583/Q0588).
- **b371d1 dead-if** (OPEN): `list` is homed at 0x13C(sp). `sw v0,0x13c(sp)` at 0x126c, `lw a0,0x13c(sp)` at 0x1278. Without it, list goes to $s0 (`move s0,v0`) (Q0585).
- **498f25 dead-if** (OPEN): the dead `D_80750530` test makes uopt colour $t2 (the case-2 `gPlayerInventoryTable` address at 0x1408/0x1cec/0x1d30/0x1e44). Without it, $t2 joins the ugen ring: 384 differing lines starting at 0x12b0 (Q0583).

## Attempts
- **2026-11-14 HackhudPauseMenuRender (claude-opus-5-5, strong retry; copy from HEAD eeeab600)**
  - **4cca45:** `y0 = 0xA0; y0 -= (s16)(y0 * 2 * hud->fade);` -> fdiff OK.
    - `y0 = y0 - (s16)(y0 * 2 * fade)` also full=0.
    - `(s16)(hud->fade * (y0 * 2))` scores full=62 (operand order).
  - **744852 + 1c9898 + frame budget:**
    - `gDPSetPrimColor` macro alone: full=47.
    - Macro + one shadowing case-1 `f32 fc` deleted: 0.
    - Macro + both case-1 shadows deleted + a block-scoped `s32 slide`: 0, fdiff OK.
    - Other single deletions: case-3 `fb` 5, case-0 `fc` 13, case-0 `off` 33, case-0 `fa` 82, case-0 `s16 y` 0 (macro only; 2 with `slide`).
  - **fc512f:**
    - Removed with case 2/3 in their original order: 14.
    - Case-3 ternary (case-1 spelling): 7, only case 2 swapped.
    - Case 2 written fade-first: 2 (load order 0x1d9c/0x1da0 swapped).
    - Block-scoped fade locals, fa/fb/fc reuse, max form, case 1 with the fade locals: 6-428.
    - `fadeInput0 = 0.0f;` at the top, or as the declaration initialiser `f32 fadeInput0 = 0.0f;`: 0, fdiff OK. Kept the declaration initialiser.
  - **f38e4a/eb1c3c:**
    - 140 natural loop-1 bodies, scored on both the stage-3 and the final copy: `it[j]` / `(it + j)` / byte-offset spellings × x-forms (s32/s16/u16/pe/`(f32)`), y-forms, offsetX-forms (`(u32)`, plain, u16, `+=`) and statement orders.
    - Best natural: `it[j]`, `off = off * 4 + (s32)(fa * it[j].flyX);`, full=4. The four lines: `mul.s $f8,$f6,$f0` at 0x131c, `sll t5`/`mfc1 t4` swapped at 0x1324/0x1344, `addu t8,t7,s0` at 0x1364.
    - `variants.py scan` of that body (192 one-edit variants): none below 4.
    - Permuter on it: base 30, best 30, ~23.3k iterations, 1200 s.
  - **b371d1:** removal on the final body: full=5 (list in $s0).
  - **498f25:** removal: full ~350, shape 47 ($t2 joins the ring, case 2 address in $t1).

## Untried ideas
- An s64-free GPR even/odd pair source in loop 1. Q0583 says pairs come only from 64-bit values and struct copies. A struct copy of the `HudTextEntry` x/y halfwords?
- A `list` home through a real later use. A debug-print macro that leaves `if (list == NULL) {}` would be ORIG, but no target evidence (the dead test emits nothing).
- An address reference to D_80750530 in case 1 that keeps the case-2 address out of $t2. The case-1 read at 0x1b10/0x1b5c is the only executed use.

## Evidence
- The prologue saves s0-s8 and $f20-$f30. Frame 0x1A0. Homes: hubWorld 0x138, list 0x13C, ret 0x140, tab 0x144, i 0x158, hud 0x15C, buf 0xA8.
- Case 0: `li t7,160` (0x1434), `subu s4,t7,t6` (0x147c), then `sll/sra` to s16 (0x1480/0x1488).
- Case 1 ternary on fields: `lwc1 $f12,4(a0)` / `lwc1 $f2,0(a0)` at 0x1bc8/0x1bcc. These are temps; their colours move with fc512f.
