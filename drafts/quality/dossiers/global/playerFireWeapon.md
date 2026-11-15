# playerFireWeapon (global, src/global/E4090.c)

## Sites
- global:806E225C:other:13c383 (retired). It was `ang2 = camZ; // FAKE`. The camZ argument of projectileSetTargetCoords was routed through the pitch-angle temp ang2.

## Attempts
**2026-11-14, U HackE4090InputB, opus:high.** I scored each form with `variants.py try`.

| Form | Diff lines |
|---|---|
| camZ passed directly | 3 |
| Typed `PlayerStruct *slot` snapshot for the whole first-person block (Q0601), at block top or function top | 174 |
| Index snapshot `s32 p` | 173 |
| Block-scoped `f32 camZ` | 69 |
| dz/dx computed before the call | 127 |
| Separate `f32 z` at each of the 13 declaration positions | 41-69 |
| Same, with the unk8F clamp as `unk8F = unk8F + 1` | 0 at the last position |
| Same, with the unk8F clamp as a ternary | 0 at the last position |
| z also reused for `dz = focusZ - z` | 30-76 |

- For the 41-69 rows, the frame grows by 8 because of the block-scoped `s32 v` clamp temp.
- With `++`, the clamp scores 230.

**Applied:** `f32 z;` declared before hasFlag, with `z = camZ; // ORIG: …` and the ternary clamp. fdiff 0.

## Untried ideas
None for this site.

## Evidence
- Target at 0x33b8: `lwc1 $f0,536(v0)` (camZ), then `mfc1 a2,$f0` at 0x33c4 before `jal projectileSetTargetCoords`. The value passes through an FPR, which is what an f32 local does. A direct argument compiles to `lw a2,536(v0)`.
- After the call, camZ is reloaded from memory at 0x33fc, so the local is used once.
- Callee prototype: `projectileSetTargetCoords(f32, f32, f32)` (936B0.h). There is no type mismatch, so no conversion is involved.
