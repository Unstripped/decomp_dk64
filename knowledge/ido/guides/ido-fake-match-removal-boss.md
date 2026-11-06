---
title: "IDO fake-match removal findings (src/boss)"
description: "Which suspected codegen hacks in the boss overlay were safely removable and which genuinely affect IDO 5.3 output."
origin: "ok-fine dk64/notes/ido-fake-match-removal-boss"
---
Established while removing fake matches in `src/boss/*.c` (each change gated by a full-ROM match).

**Removable (output unchanged):** `register` on a local; an unused loop temp assigned in a do-while condition; `(u8 *)D_807FDC90 + 0x28` byte offsets (add a `u8 unk28[4]` field and pass `D_807FDC90->unk28`); `(s16)(s32)` / `(f64)(u32)` double casts; `U` literal suffixes; `(u8)` casts on u8 stores; block-local `tbl` temp vs reusing the function-level pointer; an unused `s32 pad[1]` in one function; an f32 `zero` local used as an argument; `goto done` ladders in a small function (rewrite as if/else).

**NOT removable (changes codegen):** `(void *)(s32)&sym` int cast around an address (relocation form changes); a repeated `sp20 = sin(...)` recompute; a dead `unk155 = 0` store before `unk155 = 1`; most pad locals (frame/slot shift even when frame size is equal); a struct-copy local in a loop; `(f32)(f64)x` round trips on float args; `sinVal`/`fArg1` temps ordering call evaluation; an empty `if (x == 0) {}` after a switch case (emits lbu/bnezl); pointer temps loaded from a struct field before calls (inlining them reloads after the call); shared-tail `goto` into another case body (52B0 `block_28`, 3840 `block_16`).

File-local pad locals are therefore not a reliable fake-match signal; check by removing once.
