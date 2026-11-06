---
title: "IDO fake-match removal findings (src/minecart/25F0.c)"
description: "Struct unification, redundant casts and natural forms that still match in minecart/25F0.c; constructs that must stay."
origin: "ok-fine dk64/notes/ido-fake-match-removal-minecart-25f0"
---
Established while removing cast views and fake constructs from `src/minecart/25F0.c` (each batch gated by full-ROM match).

- One `Actor_25F0` (current/last-spawned/player/neighbour actor), one `PlayerState_25F0` (`D_807FD580`: unk88 actor, unk104, unk1F0) and one `MinecartCart` (track cursor) replace ~12 per-use cast views and the CB/CD/C4C/MC macros; `unk174` stays `void *` because its pointee differs per actor type. Retyping is codegen-neutral.
- Float args: prototype `func_806CC190(s16, s16, f32)`, `func_80714C08(void *, f32, ...)` replace `0x41000000`-style hex constants; `sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8)` makes the `(s16)(s32)` cast on the 4th arg redundant; `D_8074E880` is `void *[]`, `D_80720120` `u8[]`.
- Redundant `(f64)`, `(f32)`, `(s16)(s32)`, `(u8)(u32)` casts all drop (implicit conversions give identical code). Track tables `D_80028C34/40/48`, `D_80028BD0` are `u8 []`; `AllocSub` becomes `u8 *` (`unk34--`).
- A duplicated clamp (`t4 = t2 > 45 ? t2 : 45; if (t4 < 90) { t5 = (same) ...`) is `MIN(MAX(t2, 45.0), 90.0)` with the ultra-header MIN/MAX macros (double evaluation is the original shape); `-(t1 > 0.0 ? t1 : -t1)` replaces the abs if/else; `MAX(0, a)`, `MIN(1.0, d)` also match. Removing the then-unused f64 temps is required for the frame.
- Comma-expression conditions (`dx = ..., dz = ..., dx*dx+dz*dz < N`) match as the plain expanded expression without dx/dy/dz locals; `--x == 0` replaces `(x--, x == 0)`.
- Must stay: `goto case_1` and `s32 pad` in func_800286EC, `s32 pad0..2` in func_8002835C, `padA..C` and `v` (read-modify-write of sp68->unk2C) in minecartFollowerChildBehaviour, and `s32 minecartSetTargetAheadOfPlayer` with no return (void changes the caller's register allocation).
- `+=` is codegen-neutral only for the unk80 blends; for unk7C/unk84 the `x = e * 0.3 + x` order matters.
