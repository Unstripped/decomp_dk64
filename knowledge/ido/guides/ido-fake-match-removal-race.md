---
title: "IDO fake-match removal findings (src/race/*.c)"
description: "Natural-C replacements for codegen hacks in the race overlay that still match under IDO 5.3, and the ones that must stay."
origin: "ok-fine dk64/notes/ido-fake-match-removal-race"
---
Established while removing fake matches in `src/race/*.c` (each change gated by full-ROM match).

**Replacements that matched**
- `if (a != 0) {} else {X}` -> `if (!a) {X}` (A960 func_8002F784); `==0`, `<=0`, `0 ==` forms do NOT match, `!a` does.
- `if (p == NULL) {} else {..}` + `goto next` in a loop -> `for` + `continue` on both skip conditions (7BD0 func_8002CBEC); null and bad-kind paths both `b` to the step with the bound already in v1.
- Self-assign clamp `if (x < c) x = x; else x = c;` -> `x = (x < c) ? x : c;` (the plain `if (x >= c) x = c` form does not match).
- `goto tail` out of the first `default:` of a switch -> put `default:` last and fall through from the preceding case (52B0 func_8002A0AC); recomputing the field read is fine.
- `goto end` ret-assign pattern -> single-exit if/else-if chain with one `return ret;` (early returns change the ret register v1->v0).
- Empty `do {} while (0)` plus reused argument -> separate local; plain `while (cur != end)` matches the guarded do-while.
- Pointer-to-s32 locals, `(&p->f)[k]`, `(u8 *)p + n` accesses -> typed fields / `f32 f[3]`; `D_807FBB40` position fields are f32 (an s32 declaration only existed to force `lw`).
- Constant temps like `s32 a = 0xBE;` as call args can be inlined if the pointer-chain temps stay (6650 func_8002B610).
- Uninitialised-read probe (`ret = sp38;` with sp38 unset) plus pad slot disappears when `ret` is declared in the order `u8 i; f32 ret; s32 found;` (7BD0 func_8002DDA0).

**Still needed (removal breaks the match)**
- 6650 func_8002B180: `if (BBV->unk7C) {}`, `if (var_fv1) {}` and `f32 sp54[1]` (stack home); needs a human.
- 7BD0 func_8002D778: `if (!t->unk1C && ...) {}` guard and the `(u32)t->unk1C +/- 1` casts (they pick v1 for the lhu temp); `(s32)temp_v1 + arg1 * 8` operand order in func_8002BC2C/BCB0.
- multiplayer func_80025654: `volatile` pointer local (forces the stack home; plain local goes to s0).
- xor-swap in A960 func_8002F784 is in the target asm.
- Most `pad`/frame locals: removal changes the frame (all tested once per function). Many pads only vanish once an adjacent hack is fixed, so retry after fixing the neighbours.
- Code under `#ifdef NON_MATCHING` is not compiled and cannot be verified by fdiff.
