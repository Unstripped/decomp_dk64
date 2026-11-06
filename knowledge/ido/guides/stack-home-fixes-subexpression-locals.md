---
title: "Fixing stack-home offsets: named subexpression locals and hoisted conditional assignments"
description: "Two ways to move IDO 5.3 -O2 stack homes when a function's asm matches instruction-for-instruction but local slots are off by 4: extract a repeated subexpression into a named local at the right declaration position (replaces a compiler-temp home), and hoist a conditional pointer assignment to before the if (moves a spill slot). Learned matching func_80026354 (race 1770.c)."
origin: "ok-fine dk64/notes/stack-home-fixes-subexpression-locals"
---
# Fixing stack-home offsets: named subexpression locals and hoisted conditional assignments

When a function's compiled asm matches the target instruction-for-instruction but a block of locals sits 4 bytes too high and a spill slot 4 bytes too low (frame size unchanged), the cause is usually home-allocation, not codegen. Two fixes from the `func_80026354` match (race `1770.c`, frame 0xA0):

- **Extract a repeated subexpression into a named local at the declaration position where the missing gap belongs.** The `sqrtf` distance inside `func_806CC190(..., (s16)(s32)(func_80611BB4(..., sqrtf(...)) * 2048.0 / pi), ...)` generated two compiler-temp homes below the last local (unused → gaps at `0x48`/`0x44`). Declaring `f32 dist;` between `spd` and `flag` and assigning `dist = sqrtf(...)` before the statement replaced one temp home with a named home at `0x58`, shifting `flag`/`sp54`/`hx`/`hy`/`hz` down 4 to the target slots with no frame growth.
- **Hoist a conditional pointer assignment to before the `if` and delete the in-branch assignment.** `nxt = LR3NXT;` inside `if (!(unk60 & 0x10))` plus a repeat after the if spilled at `0x3C`; hoisting the first assignment to right after `nxt2 = LR3PT(next2);` (keeping the post-if one) moved the spill to `0x40`. The compiled instructions stay identical (the value is recomputed in both places as before).
- **Unprototyped callee with two arities in one TU:** `func_806CC10C` was `(s16, s16, void *)` for `func_800261E0` (3 args) but the new function calls it with 2. Declaring `s16 func_806CC10C();` (unprototyped) compiles both, but the 3-arg call lost its `sll/sra` arg narrowing; an explicit `(s16)` cast on that argument in `func_800261E0` restored the exact instructions.

Both changes were necessary together; either alone left some slots off. Verify with `tools/fdiff.sh` (no `s` marks in the function) and the full ROM gate. [^commit] [^target]

[^commit]: `src/race/1770.c` at the cited commit.

[^target]: `asm/race/nonmatchings/1770/func_80026354.s`.
