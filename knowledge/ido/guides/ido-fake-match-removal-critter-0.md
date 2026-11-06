---
title: "IDO fake-match removal findings (src/critter/0.c struct conversion)"
description: "What changed codegen when raw-offset code in critter/0.c became CritterObj/CritterGroup/CritterZone struct accesses."
origin: "ok-fine dk64/notes/ido-fake-match-removal-critter-0"
---
Established converting `src/critter/0.c` from `*(f32 *)(arg0 + 0x28)` to struct fields (full-ROM gate on each commit).

**Removable (output unchanged):** `goto end` in a zone pick (plain if); unused `u8 pad` local in func_80024F28; `(f64)(u32)x`, `(s16)(s32)`, `(s32)arg[2]`, `(u32)` casts; redundant `{ }` block; `(0, col)` comma plus manual Gfx word build (use `gDPSetPrimColor`); `var_s3 = NULL` pre-init before a switch with default.

**Struct access changes commutative-operand order.** IDO orders commutative operands of + and * by operand shape; `obj->field` loads rank differently from `*(T *)(p + off)`, so identical source can swap register/scheduling. Fix by commuting the source (`+ (f32)off->x` first, `obj->x += spd * f()` instead of `obj->x = spd * f() + obj->x`, `(f64)obj->anim + 200.0 * ...`, `obj->frame != D_807444FC`, `obj->zone != leader->zone`).

**NOT removable:** `*(volatile f32 *)&obj->speed` in the steer function (needed for the reload after the store); `(u8)use_y`; unused `s32 col;` local in the render group function (frame padding); parked func_8002601C needs `obj->homeZone->...` re-read each use (no zone local) to keep its NON_MATCHING object identical.

**Typed params:** a K&R-defined or unprototyped callee passes an s32 unmasked, while a prototyped `u8` param adds an `andi`; `critterGetZone(grp, u8 idx)` with `u8 idx` local in the caller matches.
