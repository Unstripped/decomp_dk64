# renderActorEntryBuildDisplayList (global, src/global/35000.c)
## Sites
global:80630DCC:dead-if:939bb2 dead-if: `if (dy) {}` after `dy = actor->z - eyeZ`; extra use lifted dy's adjsave to 4.5 so the z delta took $f2 and scaleY (dz) $f14. REMOVED.
global:80630DCC:other:01f267 other: `if (dxb > 0.5f) { dy = dy * dy; }` dead block + dead store; lowered dxb's adjsave so the x delta took $f12 and kept load order lwc1 0x84(s0) before 0x224(v0). REMOVED.
## Attempts
2026-11-10..12 rounds 10/13/16/20 (claude-opus-5-5 low/xhigh): removal of either/both, dy/dz swap ($f2/$f14), separate dzb local (158 lines), dead dy store moved into dxb block, `if (!dy) {}` in the clamp, permuter 600s (best 20/355/3215), reconstruct with nested if/MIN -> no match.
2026-11-16 HackrenderActorEntryBuildDisplayList claude-opus-5-5:high: per-role locals in the second block -> v1 dz/dx reuse + dy scale 142; block-scoped zDist/xDist/scale 158; xDist-first block locals 158; dx/dz reuse x-first 142; no hacks with dy/dxb 130; inline z-first expression 5 (load order swap only); inline x-first `(x-eyeX)*(x-eyeX) + (z-eyeZ)*(z-eyeZ)` + dz reuse for scale 0; same with a dedicated `scale` local in dxb's declaration slot -> fdiff OK (kept). Also dropped `(s32)`/`(f64)` casts on distSq -> fdiff OK. SQ() macro form 67.
## Untried ideas
none open (function is hack-free).
## Evidence
0x1178/0x118c lwc1 $f16,0x84(s0) (actor->z), 0x1190 lwc1 $f18,0x224(v0) (eyeZ), 0x1194 lwc1 $f10,0x7c(s0), 0x1198 lwc1 $f8,0x21c(v0); 0x119c sub.s $f2 (z delta), 0x11a8 sub.s $f12 (x delta), 0x11ac/0x11b8 mul.s squares, 0x11c8 add.s $f16,$f4,$f6, 0x11cc trunc.w.s -> v1 distSq; 0x11b0 lwc1 $f14,0x38(t3) scaleY, 0x11dc reload 0.01f into $f14 on the clamp path.
First block (0xb8c-0xbdc): dx $f0, dy $f2, dz $f14 (squared in place), sqrtf arg $f12.
