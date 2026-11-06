---
title: "IDO fake-match removal findings (src/bonus/2690.c target/popup game)"
description: "What was removable vs not in bonusTargetGameUpdate/bonusPopupGameUpdate/render HUD functions of the bonus overlay."
origin: "ok-fine dk64/notes/ido-fake-match-removal-bonus-2690"
---
Established while removing fake matches in `src/bonus/2690.c` (each change gated by a full-ROM match).

**Removable (output unchanged):** `*(void **)((u8 *)D_807FD580 + 0x104)` (file-local `struct { char pad0[0x104]; void *unk104; }` plus a macro cast of the `void *` global); `((u8 *)e->unk174)[0x1C]` (add `unk1C` to the target sub struct); `(Struct_71B4 *)t0` call cast and `(Actor_74A0 *)arg1` crosshair casts (merge the partial struct views of the same memory into one type; give the actor an `unk178` of type `void *` so typed locals take it by implicit conversion); K&R forward declaration `Gfx *f();`; `(f32)` casts on assignments/args; `(u32)` on a float stored to u8; `ang2 = ang` copy local (`ang -= 8.0f`); `r`/`idx` pair collapsed into `idx = (... % 0xFF) % 8`; `(s16)`/`(u16)` casts at a call whose prototype took `s32` (narrow the local prototype to `u16`/`s16` and drop the casts).

**NOT removable:** `s32 pad` in bonusRenderCrosshair (frame 0x68 vs 0x70); the `pad1[4]/pad2[6]/pad3[4]` arrays around `sp64/sp48/sp34` in bonusRenderTargetGameHud (frame 0x48 vs 0x80); collapsing the `temp_v0 -> temp_v1 -> temp_s1` single-use chain in bonusRenderPopupGameHud (regalloc v0/v1 become t2/t3); hoisting `step = (x ? 2 : 1)` above the compare in bonusTargetUpdate (text shrinks): the else branch needs its own `step = (sub->unk8 != 0) ? 2 : 1;` ternary assignment (if/else assigning step also matches, a bare ternary in `-=` does not).
