# bonusSearchlightSeekGameUpdate (bonus, src/bonus/2690.c)

## Sites
bonus:8002BF98:other:2818d5 other: aim point for projectileSetTargetCoords written into the 3rd/4th/5th declared f32 locals so aimX/aimY spill to homes 124(sp)/120(sp) across mathCosF; now `// ORIG:` (own-home rule), no longer a site.
bonus:8002BF98:other:60fd8d other: offset clamp reads offsetX/offsetZ into the same 3rd/5th locals so they spill to 124(sp)/116(sp) across sqrtf; the distance reused cosYaw. Now `// ORIG:`; distance is its own `f32 dist` in the former `s32 pad` word.
bonus:8002BF98:other:9b1a7c other: case-0 velZ pre-read held in x. FIXED (HackbonusSearchlightSeekGameUpdate3): own `f32 velZ` declared after `s16 spawnAngle`.
bonus:8002BF98:other:5a458f other: clamp scale 110.0f / dist held in y. FIXED (HackbonusSearchlightSeekGameUpdate3): own `f32 scale` declared after `s16 spawnAngle`.
bonus:8002BF98:noop-arith:83418a noop-arith: case-0 stick_x * 0.06f held in z (aim/clamp z home); stickX must be coloured $f2 before velX/velZ/stickY. Still FAKE.
bonus:8002BF98:other:d3c36c other (copy-only, new tag): velX also holds the x velocity error (`velX = ... - velX`, $f12 vs pre-read $f14). Pre-existing, now tagged FAKE.

## Attempts
2026-11-10 cleanup round 8 CleanBonus2690 anthropic/claude-opus-5-5:low: views (PlayerState camActor, PlayerStruct camX/Y/Z, heldButtonsPtr), sinYaw/cosYaw names swapped -> fdiff 0
2026-11-10 cleanup round 9 CleanGlobal36880 anthropic/claude-opus-5-5:low: projectile chain last param Actor * retype -> fixed
2026-11-13 cleanup round 36 CleanBonus2690 anthropic/claude-opus-5-5:xhigh: D_807ECDEC as OSContPad *, LargeB4Sub field names; velX/velZ pre-reads needed (rev/v_e14.c, v_e15.c) -> fdiff 0
2026-11-14 PolishBonus2690Names anthropic/claude-opus-5-5:high: SearchlightGameState/SearchlightTargetState names -> fdiff 0 via standin
2026-11-14 RereviewSmallFiles1 anthropic/claude-opus-5-5:high: reuse tagged FAKE; separate aimX/aimY/aimZ 77 diff lines, separate ox/oz/dist 85 diff lines
2026-11-15 Polishbonus2690 anthropic/claude-opus-5-5:high: parens, 1.0 -> 1.0f for f32 args -> fdiff 0
2026-11-15 HackbonusSearchlightSeekGameUpdate2 HackbonusSearchlightSeekGameUpdate2 anthropic/claude-opus-5-5:high (variants.py try, full= lines):
- aimX/aimY/aimZ after stickY 77 (shape 16); same with s32 pad dropped 75; aim locals declared first, pad dropped 75
- offX/offZ/dist/clampScale after stickY 83 (shape 12); aim + clamp separate, pad dropped 78
- `f32 dist` in the s32 pad word for the clamp distance (cosYaw no longer reused) 0 -> kept
- `f32 velZ` in the pad word for the case-0 velZ pre-read 0 (but the pad word can hold only one of dist/velZ); dist + velZ as a 13th word 15 (shape 15)
- case-0 stick_x in its own pad-word local 10; in the 4th var 13; case-0 3rd/5th roles swapped 10 (stick_x must share the 5th var: Q0739 merged live range)
- case-0 velZ pre-read in the 4th var (with dist in pad) 0
- clamp scale inline `x * (110.0f / dist)` 2 (mul.s operands swapped at 0x60e0/0x60e8), `(110.0f / dist) * x` 2, `x * 110.0f / dist` 48; `dist = 110.0f / dist` 0 (register-only reuse, not kept)
- final: dist in the pad word, targetOffsetZ/scale/targetOffsetX -> x/y/z, both FAKE -> ORIG with offsets -> fdiff 0, clint uninit 0, cwarn 0
2026-11-15 HackbonusSearchlightSeekGameUpdate3 anthropic/claude-opus-5-5:high (variants.py try, full= lines):
- Frame probe: `s32 pad;` or `s32 pad[2];` declared AFTER `s16 spawnAngle` -> fdiff 0 (frame stays 0x88); one extra word declared before spawnAngle (after dist) or before sinYaw -> 0x90 (only the two addiu sp lines differ). So the frame has 3 spare trailing words; "exactly 12 words" was wrong.
- velZ pre-read as an inline `subExt->velZ` temp 6 (velZ $f18 / stickY $f16 swapped, a CSE temp ranks below a variable); own `f32 velZ` after spawnAngle 0 -> fixed
- scale inline in all 4 operand orders 2 (CSE temp canonicalised to scale*x); own `f32 scale` after spawnAngle 0 -> fixed
- stickX own local after spawnAngle (any of the 6 trailing orders, with velZ/scale) 10; swapped into each register-only declaration slot 10; stickY/stickX statement order 14; both before velX 13; before sinYaw 218; `f32 stickX, stickY;` 25; unparenthesised delta 10; inline temp 187 (stick_x reloaded after the velX store)
- velX error term: inline like the velZ line 101 (4 spellings), `velX + (...) * 0.155f` 88, accelX local (trailing) 88-101
- uopt_trace -l 6 (stickX vs z): the z web (bit 156, -20 vreg) is coloured before velX (148) and gets the first free FP reg ($f2); an honest stickX web ranks after velX/velZ/stickY and lands in $f16.
- permuter 905 s (-j 2, hack-free weights) on the honest-stickX body: baseline 55, best 0, but every zero puts stick_x back into z (a `stickX = z;` alias copy or stickX deleted): no new idea.
- Final: velZ and scale own trailing locals (2 FAKE removed), z-holds-stick_x kept, velX-holds-error tagged (pre-existing) -> fdiff 0, clint uninit 0
2026-11-16 HackbonusSearchlightSeekGameUpdate4 anthropic/claude-opus-5-5:high (uopt_trace -l 5 adjsave/bit per variant, variants.py try full= lines):
- Model: in bb43 FP candidates colour by adjsave desc, then candidate bit asc (first appearance, LHS before RHS), first-fit 25=$f2 26=$f12 27=$f14 28=$f16 29=$f18. Target order: stickX > velX error > subExt->velX load (CSE) > subExt->velZ load > stickY.
- Honest stickX 3.0 (1 def 2 uses) vs hack error 4.0 (2 defs 2 uses, both phantom refs of `velX = subExt->velX`): 10. stickX line first (bit 148 < error 155): 5, stickX/error swapped $f12/$f2.
- `stickX = stick_x; stickX = stickX * 0.06f;` 5.0: all five FP values coloured right, but the cvt lands in $f2 (`mul.s $f2,$f2,$f10`): 108. Block-scoped stickX in case 0 10; `stickX = 0.06f; stickX *= stick_x` 66 (constant def not counted); `sens = 0.06f` local 10.
- Error: the bit order needs velX load < velZ load < stickY, and the error is defined from stickY, so it must outrank the 3.0 velX load on adjsave alone (2 defs + 2 uses with no emitted code). `dx = t; dx -= subExt->velX` 13 (first def propagated, 2.0); dead `velX = subExt->velX;` before `velX = t - subExt->velX` 10 (removed, 2.0); `velX *= 0.155f; subExt->velX += velX` 96/103 (4.0, but a real `mul.s $f2,$f2,$f6`); accX `*=` two-step 88.
- Final: no change, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line).

## Untried ideas
stickX (83418a) / velX error (d3c36c): each needs one more counted ref that emits no code (stickX >= 4.0 with a lower bit than the error, error > 3.0). Only the reuse of a load-copied local (`v = p->f; v = e - v;`) produces such refs. No natural spelling found; Q0771-style constant-propagated refs land on the constant local, not on stickX.

## Evidence
- Frame 0x88: saves s0-s6 at 56..80(sp), ra 84(sp), 12 declared local words 88..135(sp) highest-first: sinYaw 132 (spilled at 0x5dc4), cosYaw 128, x 124, y 120, z 116, velX 112, stickY 108, subExt 104, spawnExt 100, i 96, dist 92, spawnAngle 88.
- Aim: swc1 $f6,124(sp) 0x5f5c (x), swc1 $f10,120(sp) 0x5f68 (y), reloaded into $f12/$f14 at 0x5f80/0x5f8c, z in $f2 -> mfc1 a2 at 0x5f94.
- Clamp: swc1 $f0,124(sp) 0x60a8 (x), swc1 $f2,116(sp) 0x60ac (z), reloads at 0x60c4/0x60dc after sqrtf; scale div.s $f12,$f14,$f0 at 0x60d8; mul.s $f4,$f6,$f12 / $f8,$f2,$f12 at 0x60e0/0x60e8 (x * scale order).
- Case 0 keeps x (velZ pre-read), z (stick_x*0.06f), velX, stickY in registers ($f16, $f2, $f14, $f18).
- bb43 adjsave (uopt -l 5, hacked base): error var 538|1 bit 148 4.0 -> 26 ($f12); velX load 1252|6 bit 150 3.0 -> 27 ($f14); velZ load 1252|7 bit 154 3.0 -> 28 ($f16); z web 602|1 bit 156 4.5 (4 blocks) -> 25 ($f2); stickY 474|0 bit 163 3.0 -> 29 ($f18).
