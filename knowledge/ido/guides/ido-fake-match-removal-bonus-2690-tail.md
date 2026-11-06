---
title: "IDO fake-match removal findings (src/bonus/2690.c tail: func_8002AAA4..func_8002CC08)"
description: "Which fake-match constructs in the bonus-overlay actor/large-game functions at the end of 2690.c were removable and which change IDO output."
origin: "ok-fine dk64/notes/ido-fake-match-removal-bonus-2690-tail"
---
Established while removing fake matches in the tail of `src/bonus/2690.c` (func_8002AAA4 through func_8002CC08; each change gated by a full-ROM match).

**Removable (output unchanged):**
- Hand-rolled `WRITE_GFX(pkt, 0xE7000000, 0)` display-list macro in func_8002CC08: use `gDPPipeSync`, `gDPSetCombineMode(G_CC_DECALRGBA, ...)`, `gDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2)`, `gSPDisplayList`, `gSPMatrix(..., G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION/MODELVIEW)` (same sequence as bonusRenderCrosshair).
- `*((u8 *)p + 0x21)` where 0x20 is an `s16`: write `(u8)p->unk20` (IDO emits `lbu` at +1).
- Byte-pointer loops `p = (s8 *)s; ... p[0x2A]`: use the array field `s->unk2A[i]`. The init loop only matches as `i = 0; do { s->unk2A[i] = 1; i++; } while (i != 1);` (a `for (i = 0; i < 1; i++)` moves the pointer increment before the store). The old `s8 *p` local still reserves a 4-byte stack slot, keep it as `s32 pad;`.
- `*(void **)temp = actor` into an untyped first field: type the field.
- `(f32 *)*D_807F5FD4 + 9` is `Point3f *p = *D_807F5FD4 + 3; p->x` (dropping the `p` local changes regalloc).
- `x &= 0xFFFF7FFF` to `x &= ~0x8000`; `(&arr[i])->f` to `arr[i].f`; `(s16)`/`(u16)` casts where the callee parameter is already `s16`/`u16`.

**NOT removable:**
- `do { } while (0)` in the empty `case 7:` of func_8002CC08: a plain `break;`, `return arg0;`, or dropping the case changes the spill-slot layout (a 4-byte ghost slot) or the epilogue.
- `new_var` alias in func_8002AAA4 (`new_var = (T *)a->unk174; new_var->unk4 = 8;`): direct `a->unk174->unk4 = 8` flips the loop-count register.
- `var_v0 = 1` as loop exit in func_8002B920/func_8002C8EC: a real `break` grows the text by 16 bytes.
- The dead `unkC = 2;` before `unkC = ...` in func_8002BF98 (IDO keeps the store).
- The six dead `e1..e3`/`d1..d3` s32 locals in func_8002C8EC (frame 0x50 vs 0x48).
- `(f32)(sp80 * 4.0)` when truncating to s16 in func_8002CC08 (double multiply then `cvt.s.d`); `sp80 * 4.0f` is 16 bytes shorter.
