---
title: "IDO fake-match removal findings (src/multiplayer/0.c)"
description: "Struct unification of raw offsets in multiplayer/0.c and which hacks IDO 5.3 still needs."
origin: "ok-fine dk64/notes/ido-fake-match-removal-multiplayer-0"
---
Established while converting raw offsets in `src/multiplayer/0.c` (each batch gated by full-ROM match).

- Retyping externs (`MpPlayer *D_807FC924` stride 0x2F0, `MpScore D_807FC950[]` stride 0x306, `MpControllerActor *D_807FBB40`) is codegen-neutral; the old per-function cast-and-pad structs unify into one actor/kong-state/controller-state view.
- `D_807FCC4B + i*0x306` is `D_807FC950[i].unk2FB` (symbol differs in the .o reloc, ROM identical).
- Passing an f32 actor field to a prototype with f32 params in a0..a3 still compiles to `lw`, so one actor struct with f32 pos works for `actorSpawnNodeEntryScaled`.
- Needed hacks: `void *temp` in mpDrawPlayerScores (viewport and Gfx* share one local: separate locals add a saved reg and change the frame, `glistp = f()` flips the move order); `p = (void *)(s32)&D_8071F3C0` in mpUpdateScoreEffects (plain `&sym` loses the hoisted register); `flag` + switch fallthrough in mpUpdate; double store `unkC = x; unkC = unkC * 60`; mpDrawHud's `t0`/`cond` early-load locals; `ctrl` pointer local in the slot of `pad1` in mpDropItemsOnHit.
- mpCalcKillScore: `arg0->unk2FE[arg1]` strength-reduces compares to `arg1<<1`; `*(u16 *)((u8 *)arg0->unk2FE + (arg1 << 1))` matches.
- Removable: redundant `(s16)(s32)` float casts, `(s32)` before u8 `D_807FC928` and `randomNonNegative() >> 15`, nested braces and assignment-in-condition in func_80025654.
