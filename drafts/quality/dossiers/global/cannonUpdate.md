# cannonUpdate (global, src/global/80150.c)
## Sites
global:806822FC:other:9f7928 other: x/y reused for the focus-camera dz/dx (fixed: own dz/dx locals).
global:806822FC:other:2c0b1c other: y reused for the cosine term (fixed: own cosV local).
## Attempts
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: block-scoped dz/dx + block cosV (V5) -> 6 (only y/z FPR swap at 0x70a0-0x70c4 and cos product $f14 vs $f2 at 0x7504)
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: + `y = gCurrentActor->y + D_8074E7FC;` assigned before `z = gCurrentActor->z;` (W3) -> 0
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: same order with function-scope `f32 dz, dx, cosV` (F1) -> 0, fdiff OK (applied)
2026-11-15 HackthrowableBarrelUpdate HackthrowableBarrelUpdate anthropic/claude-opus-5-5:high: cos inline as the projectileSpawnNodeEntry argument -> 16/14; z field read directly in camSetFixedView -> 84/87; declaration reorders of x/y/z -> 6/10
## Untried ideas
none (both sites removed).
## Evidence
0x70a0 add.s $f2 = actor y + D_8074E7FC (y), 0x70a4 lwc1 $f14 = actor z: y is the earlier FP candidate once its statement precedes z (Q0468); 0x7504 mul.s $f2 cos product, swc1 $f2,16(sp) at 0x7520. No x/y/dz/dx/cosV stack homes (frame 0x60 unchanged).
