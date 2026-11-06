---
title: "IDO uopt: statics, constant live ranges and temps in large functions"
description: "How IDO 5.3 uopt treats function-local statics vs globals, constant coloring live ranges, live-range splitting, store forwarding and temp frame slots, and how ugen's LRU scratch allocation plus as1 deletions hide register-numbering diffs; learned matching func_806057F8 and func_80622B24."
origin: "ok-fine dk64/notes/ido-uopt-statics-and-live-ranges"
---
Facts established while matching the 2892-instruction `func_806057F8` (now `sfxUpdateSourceGroups`) in `src/global/7130.c` (stage 3 draft to ROM match); the live-range splitting section comes from the parked camera update `func_80622B24` (now `camComputeEyeFocus`). Each was confirmed by micro-tests with the project `cc` flags and by the final build.[^f7130][^yaml] Related: IDO matching quirks, large functions runbook (guide large-functions-and-near-misses: python3 tools/quirks.py get large-functions-and-near-misses), audio units (ok-fine dk64 architecture/audio-fog-lights).

## Globals vs statics

- **Extern globals are never uopt register candidates;** only locals (`M`) and statics (`S`) appear as `isvar` in the `uopt_trace.sh -l 5` candidate table. A global that the target keeps in an FP register across a region, with redundant `swc1 reg, %lo(G)` stores at block entries and a reload in one branch, is a **function-local `static`**. A file-scope static or a plain definition does not reproduce it (calls to same-file functions kill it). Check first that only this function references the symbol.
- Such a static needs its TU to own the bss at the right address: IDO lays out `.bss` in definition order, objects ≥ 8 bytes 8-aligned, function statics after the file-scope definitions that precede the function, section size rounded to 16. With `SUBALIGN(16)` the TU's `.bss` must start at a 16-aligned object, so define the neighbouring vars too and split the asm bss in the yaml (`{type: .bss, name: <tu>}` between two named `bss` pieces).
- **Store-to-load forwarding:** int/pointer stores to an extern are forwarded to the next load of it; float stores are not (`swc1` then `lwc1`). An int global stored and immediately reloaded with separate `lui at`/`lui tN` pairs means `&G` was not a colored constant candidate: a codeless `if (G != NULL) {}` before the function's main loop extends that address constant's live range over the loop so it stays uncolored.

## Constants and expressions

- **Constants are coloring candidates with loop-spanning live ranges** (`const------>` blocks in the `-l 5` trace; `not colored (-ve save)` in `-l 6`). Uses of the same constant value/type anywhere in a loop body join one live range; single-use sites (`x + 2.0f`) drag a two-use site (`x * 2.0f + 2.0f`, target shares one `$f0`) into an uncolorable range. Fix by changing the literal type at single-use sites (`2.0f` → `2.0` for adds; ints `2` and `2.0f` are the same constant). A double literal multiplier (`* 2.0`) strength-reduces to `add.d x, x`; float/int literals keep `mul.d`.
- `x *= y` and `x = x * y` order `mul.d` operands differently; the draft-style `(f32)((f64)x * y)` gave the swapped form.
- Clamps that store then reload the value (`swc1; bc1fl ...; lwc1`) are ternaries `X = (X > 1.0f) ? 1.0f : X`; `if` clamps compare the computed register.
- `if (t-- <= 0.0f)` on a float counter emits `c.le.s` + `sub.s` + a `v0` boolean before the store; `if (t > 0.0f) c += (b - c) / t--;` divides by the old value and stores `t` first.

## Temps and frame

- uopt temporaries (CSE/PRE values such as `i*4`, `&arr[i]`, a re-read `arr[i]` after calls) get frame slots below the declared locals, numbered from the top of that area in creation order. Writing those values as named locals (m2c style `sp98 = &D[i]`) makes them declared locals and breaks the layout; write the array accesses directly. One missing temp shows up as every temp slot 4 bytes low; an unused declared local at the bottom restores the frame without fixing the temps.
- Block-scoped locals get slots too; m2c's `s16 ent = ...` temps both grow the frame and pin values in `$s` registers the target reloads.

## ugen temp registers

- **ugen allocates GPR scratch (`t3`–`t9`; uopt colors only `v0`–`t2` = ids 1–9 plus `s` regs) by least-recently-used:** every def or use of a temp refreshes it, a temp is free after its last use in ugen's own expression order, all temps are free after `jal`, and the initial order is `t6 t7 t8 t9 t3 t4 t5`. A simulator over the `cc -S` listing (temps `$11`–`$15`,`$24`,`$25`; fresh def = allocation; busy until the last later use before redefinition or `jal`) predicted 342/342 allocations in `func_80622B24`; the initial order is inferred from the first seven allocations, not documented. FP scratch (`$f4`–`$f18` minus uopt colors) behaves the same way.
- **as1 deletes ugen instructions, so the final asm hides allocator state.** `cc -S` (same flags, `-S` instead of `-c -o`) prints ugen's output before as1: home-slot reloads of params that as1 forwards from `a0`–`a3`, `sll/sra` sign-extension of a callee result stored into an `s16`, `move` chains. A diff that is only scratch-register numbering from one point on means the *deleted* instructions differ there. Compare the `-S` listing with the target's registers at the first divergence, not the scheduled asm.
- Three sources of such invisible temps found in `func_80622B24`: (1) a callee declared `s32` whose `s16` result feeds arithmetic emits `sll/sra` temps (declare it `s16`: `s16 func_806CC284(s16, s16, f32)`); (2) an `f32` local holding a one-use quotient became a uopt candidate colored `$f12` where the target had a ugen `$f18` (the original is a `f64` local in an unexplained 8-byte frame gap, with the `f32` slot left unused); (3) `*arg1 + call() * dist` vs `call() * dist + *arg1` changes which operand is evaluated first (deeper subtree first; on a tie the right operand).
- A `cc -S` listing also shows the macro `CAM_LERP(sqrtf(A), sqrtf(B), t)` evaluating `sqrtf(A)` twice, exactly as the ROM does: the original used a two-evaluation macro.
- `t`-register choice carries across blocks; one extra or missing uopt candidate early in a function (e.g. a `u8` local for an index the target keeps in `$v0`) renumbers every later `t` register. Fix divergences top-down; most of 1300 `r` diff lines vanished from three such fixes.
- Statement placement on the same source line can change scheduling (decomp-permuter found `...; break;` on one line); check before trusting it.
- **Visible ring registers can force an allocation ORDER, not just a count (`enemyGridStateStep`, matched 2026-11-05).** Under the allocation-order model below (which reproduced this function's listing), extra burns only rotate the phase. The model pointed to one ordering for the target's `t4` (dx's `sll`), `t3` (the `(u16)(v >> 2)` operand) and `t6` (dy's `sll`), and that ordering matched: the dy operand's two temps allocated before dx's narrowing. An `s16` variable narrows at its own store, so that narrowing cannot move. What worked: declare `dx`/`dy` `s32`, cast every store `(s16)(...)`, and add `dx = (s16)dx; dy = (s16)dy;` after both subtractions. Separate `s32` temporaries (`tx = ...; dx = tx;`, or reusing `j`) got their own colours (`v1`/`t1`) and extra moves: the narrowed variable itself must hold the unnarrowed value.[^c0ee0]
- Wider types must still fit the frame. Homes are top-down in declaration order with natural alignment, and `s16`/`s8` homes pack (retyping two `s16` locals to `s32` grew the frame from 0x88 to 0x90). Count the free bytes between the homes the target exposes (here 0x70, 0x64, 0x54, 0x44, 0x40/0x42). Reordering declarations and holding the chosen cell in `adx` (dead after its loop) instead of a separate `s8 v` kept 0x88.[^c0ee0]
- On that function's `as1probe keep` listing, LRU by allocation time (uses do not refresh) reproduced every integer allocation; with use refresh, four more mismatched. A crude corpus-wide run (373 functions, about 67% for both models) did not separate them, so the use-refresh rule above is unconfirmed either way.

## Live-range splitting (func_80622B24)

Learned on the 1941-insn camera path update (matched 2026-10-25).[^c201b0]

- **A `u8` local spills to a word uopt temp, not its home:** `u8 type = p->unk1;` used by several compares makes the `ucvt` CSE value the candidate; when uncolored it is stored once (`sw` in a branch delay slot) and reloaded with `lw` from a temp slot below the cfe temps. An `s32` local spills to its own home slot instead. The declaration position of the `u8` local shifts the cfe temp slots (switch/sqrt temps) by one word.
- **`-l 6` piece arithmetic:** a range spanning calls is split; each piece's priority is `(uses - reload points) / blocks`. A piece entered from several call-containing predecessors through ONE join block counts one reload; routing those exits through distinct join blocks (extra labels/gotos) adds reload points and can drive the piece to `not colored (-ve save)`. Brute-force label placements by grepping the piece lines of the `-l 6` trace before diffing.
- **Global coupling:** adding code at the end of a function moves `t`-register choices hundreds of instructions earlier; a C structure that fixes uopt coloring with artificial gotos can still diverge in ugen scratch numbering, so an identical opcode stream is not yet a match (see the ugen section below for how that was resolved).
- The two consecutive labels (`look_set:`/`look_done:` after the switch) are required: every single-label or label-free shape, including moving the look computation after the switch with `goto`s and a `default: goto`, re-colors `type` (1945–1947 insns).
- `x == 0` vs `!x` on a global byte also passed to a call changes whether the loaded value is reused as the argument register (`lbu v0; bnez v0; move a1,v0`).
- `if (G != 1U)` avoids CSE of the constant `1` with an earlier `== 1` test of the same global; `(u32)type == 7` makes the cast a separate expression (the other uses spill fully, but the compare itself changes).
[^c0ee0]: `src/global/C0EE0.c` `enemyGridStateStep`, matched in commit `893aee2f`; experiments under `.scratch/me_egs/`.

## Sources

[^f7130]: src/global/7130.c @ a9ca3062c87b
[^yaml]: dk64.global.us.yaml @ a9ca3062c87b
[^c201b0]: src/global/201B0.c @ a9ca3062c87b
