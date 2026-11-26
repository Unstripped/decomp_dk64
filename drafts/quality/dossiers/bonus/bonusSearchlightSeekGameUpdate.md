# bonusSearchlightSeekGameUpdate (bonus, src/bonus/2690_minigames.c)

## Sites
bonus:8002BF98:other:2818d5 other: aim point for projectileSetTargetCoords written into the 3rd/4th/5th declared f32 locals so aimX/aimY spill to homes 124(sp)/120(sp) across mathCosF; now `// ORIG:` (own-home rule), no longer a site.
bonus:8002BF98:other:60fd8d other: offset clamp reads offsetX/offsetZ into the same 3rd/5th locals so they spill to 124(sp)/116(sp) across sqrtf; the distance reused cosYaw. Now `// ORIG:`; distance is its own `f32 dist` in the former `s32 pad` word.
bonus:8002BF98:other:9b1a7c other: case-0 velZ pre-read held in x. FIXED (HackbonusSearchlightSeekGameUpdate3): own `f32 velZ` declared after `s16 spawnAngle`.
bonus:8002BF98:other:5a458f other: clamp scale 110.0f / dist held in y. FIXED (HackbonusSearchlightSeekGameUpdate3): own `f32 scale` declared after `s16 spawnAngle`.
bonus:8002BF98:other:83418a other (re-keyed from noop-arith:83418a by 73393b44): case-0 stick_x * 0.06f held in z (aim/clamp z home): the z web 602|1 scores 4.5 and takes $f2 (mul.s at 0x5e18) ahead of the velX error var (4.0); an honest stickX is 3.0 in bb43. Needed only because d3c36c holds 4.0. Still FAKE: Q1666 census part 1 fails (2026-11-26, below).
bonus:8002BF98:other:d3c36c other: velX also holds the x velocity error (`velX = ... - velX`, $f12 vs pre-read $f14): the counted pre-read def (Q1049) lifts the var to 4.0 over the subExt->velX load (3.0); a separate errX on this body is copy-propagated into the update (error in a $f6 temp, load in $f12). Still FAKE: Q1666 census part 1 fails (2026-11-26, below); comment refreshed.
bonus:8002BF98:other:b25205 other (copy-only, 2026-11-26 hidden-reuse sweep, pre-existing, now tagged): z also holds the aim point z (line 2024, $f2 add.s 0x5f90 -> mfc1 a2 0x5f94, never stored to z's home 116(sp)); that block keeps z one web over the stick, aim and clamp roles, so the stick role (83418a) and the clamp z keep $f2. Q1666 census parts 1 and 2 fail (below).

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
2026-11-16d HackbonusSearchlightSeekGameUpdate5 anthropic/claude-opus-5-5 (variants.py try, full= lines, on the shared `void func_806FDAB8(s16, f32)` prototype):
- honest trailing `f32 stickX` 10 (same as before the prototype change, so the stale cause did not move this site); `register f32 stickX` 10 (keyword ignored).
- stick_x into a trailing `s8 sx`/`s32 sx` with `sx * 0.06f` written in both products (a CSE expression temp instead of a variable) 80, `(sx * 0.06f)` 80; unscaled `f32 sx` with `sx * 0.06f` twice 134.
- d3c36c not retried (no new idea).
- Final: no change to this function, fdiff 0, clint uninit 0.
2026-11-17 cleanup HackbonusSearchlightSeekGameUpdate6 anthropic/claude-opus-5-5 (base 8b129890; variants.py try full= lines; whole-function bodies):
- Re-measured at 8b129890: inline error term `subExt->velX + (t - velX) * 0.155f` 101 (also `+=`); `velX + (t - velX) * 0.155f` 88; honest `errX` local in each of the 14 declaration slots and first 99-112 (99 trailing); with `subExt->velX = velX + errX * 0.155f` 88-100.
- New: honest `errX = t - velX; errX *= 0.155f; subExt->velX = subExt->velX + errX;` 99-112 (same as one-step: the mul def is propagated); `errX = t; errX -= velX;` same; block-scoped errX (top of the case-0 block, or an inner `{ f32 errX = ...; }`) 88-99; `register f32 errX` 99 (keyword ignored).
- New: velX refined in place with a real store (`velX += (t - velX) * 0.155f; subExt->velX = velX;`) 95: velX outranks z and takes $f2 (lwc1 $f2,0x14(s5) at 0x5e08), the stored local is forwarded into the offsetX add (no lwc1 $f6,0x14(s5) reload at 0x5e78), the error is a $f10 temp, the cosYaw reload hoists to 0x5e00. Both axes so 91; ilod store `velX = subExt->velX + (t - velX) * 0.155f; subExt->velX = velX;` 88; chain `velX = t - velX; velX = subExt->velX + velX * 0.155f; subExt->velX = velX;` 102 (both axes 116).
- Respawn loop: `for (i = 0; i < 1; i++)` / `i != 1` 2 lines (adds the entry guard); `do ... while (i < 1)` 0. The do-while is real control flow; no change.
- uopt -l 5 at 8b129890: bb43 adjsave and order unchanged, bits +2 (see Evidence). quality.py sweep: 0 hits.
- Final: no change to this function, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line).
2026-11-17 cleanup HackbonusSearchlightSeekGameUpdate7 anthropic/claude-opus-5-5:high (base 49aa0365, measured at c67b81d2; variants.py try full= lines; whole-function bodies):
- uopt -l 5 re-scored: bb43 unchanged from 8b129890 (error var 538|0 bit 150 4.0 -> $f12, velX load 1252|6 bit 152 3.0 -> $f14, z web 602|1 bit 158 4.5 -> $f2, stickY 474|0 bit 165 -> $f18). The z web's 4.5 comes from one live range over bb43 (stick), bb55 (aim z), bb74/bb76 (clamp z); an honest stickX only lives in bb43.
- Fully honest body (trailing `f32 stickX; f32 errX;`) 101: errX 538|1 bit 150 2.0 -> $f18, velX load 3.0 -> $f2, velZ load -> $f12, stickX 1581|0 bit 158 3.0 -> $f14, stickY -> $f16.
- New: three-step `errX = z * cosYaw; errX -= stickY * sinYaw; errX -= velX;` 99 (z FAKE kept) / 101 (stickX honest); negated first def `errX = -velX; errX += t;` 99; `OSContPad *pad = gCurrentContPad;` for both stick reads with honest stickX 10 (velX FAKE kept) / 101 (errX honest).
- New: one same-role error local `d` shared by both axes (`d = tx - velX; subExt->velX = subExt->velX + d * 0.155f; d = tz - velZ; ...`, also `+=`) 112/114 (108/110 text): the velZ pre-read spills to 0x5c(sp) and the frame grows 0x88 -> 0x90.
- Permuter 900 s (-j 2, hack-free weights) on the fully honest body: baseline 780, best 55, and both 55s put a hack back (errX merged into velX = d3c36c, or the error stored into stickX, which changes the velZ term). quality.py sweep: 0 hits.
- Final: no change to this function, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line).
2026-11-17 cleanup HackbonusSearchlightSeekGameUpdate8 anthropic/claude-opus-5-5 (base ba499c04; variants.py try, full= lines; whole-function bodies):
- Rank-chain derivation (uopt -l 5/6 at ba499c04, see Evidence): the five case-0 FP values all live only in bb43 (after the mathCosF call), so they interfere pairwise and only the colouring order decides the target: stickX > error > velX load > velZ load > stickY. Honest refs give stickX 3.0, error 2.0, both loads 3.0, stickY 3.0. The error's real def needs stickY, whose bit must follow the velZ load's, which must follow the velX load's, so the error can never win a 3.0 tie against the velX load: it needs > 3.0 on adjsave alone (2 counted refs without code), and stickX must then outrank it (> 4.0, or 4.0 with a lower bit). Adjsave follows Q0163 (refs minus reloads, divided by ((nlive-2)>>2)+2): the z web has 9 refs over 5 blocks (bb43/55/74/75/76) / 2 = 4.5 (int 222|0: 20 refs over 10 blocks / 4 = 5.0), single-block ranges divide by 1 (velX error 4.0, stickY 3.0); an honest stickX lives only in bb43, so it stays at 3.0, and spreading it over 2 blocks would only halve it.
- New: `s32 rawX = stick_x; stickX = rawX; stickX *= 0.06f;` (velX FAKE kept) 79: the int->float first def has no ilod, so it is copy-propagated; stickX 1581|0 drops out of the candidates and `(f32)rawX * 0.06f` becomes CSE expression 1369|1 (3.0 -> $f16) while the error var (4.0) takes $f2.
- New: stick axes as one aggregate local `f32 stick[2]` (velX FAKE kept) 203: frame 0x88 -> 0x98 and both scaled axes go through the stack (swc1 at 0x5e10, swc1 $f8,0x5c(sp) at 0x5e38), never a colour candidate.
- New: sign-flipped error `errX = velX - t; subExt->velX = subExt->velX - errX * 0.155f;` (z FAKE kept) 99: the error becomes a $f6 temp (sub.s $f6,$f12,$f10 at 0x5e48), the velX load takes $f12, the update is sub.s at 0x5e50. The error assigned inside the update `subExt->velX = subExt->velX + (errX = t - velX) * 0.155f;` 99: errX is dead after it, so the error is a $f6 temp and the velZ load/stickY move up to $f14/$f16.
- variants.py scan of the copy (82 variants): only comparison swaps and spelling-neutral float suffixes are zero; `= 0.0` -> `0.0f` in the init block (`subExt->velX/velZ/offsetX/offsetZ = 0.0;`) is 3 lines each (Q0333 constant webs), so those double literals are load-bearing natural spellings.
- Permuter 900 s (-j 2, hack-free weights, 25410 iterations) on a new base: z steer kept, error honest (trailing `f32 errX; errX = t - velX; subExt->velX = subExt->velX + errX * 0.155f;`): baseline 765, best 0. The 0 deletes errX and writes `velX = t - velX` back (d3c36c itself); 8 is the same load copy on errX (`errX = subExt->velX; errX = t - errX;`); 55 stores the error into z; 60/90 add a redundant velX alias or reuse velX for `errX * 0.155f`. Every sub-100 output re-inserts a reuse steer (nohit by the session's best=0 ruling).
- quality.py sweep: 0 hits. Final: no change to this function, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line), cwarn 0.

2026-11-17f cleanup CleanbonusSearchlightSeekGameUpdate anthropic/claude-opus-5-5 (base b5e2166e; variants.py try full= lines; whole-function bodies; uopt -l 5 per variant):
- New template from the sibling bonusBigBugBashGameUpdate (2690.c:1649-1656, same stick/velocity code): no velX/velZ pre-read locals, `stickX = stick_x * 0.06f; stickY = stick_y * 0.06f; errX = (stickX * cosYaw - stickY * sinYaw) - subExt->velX; subExt->velX += errX * 0.155f; subExt->velZ += ((stickX * sinYaw + stickY * cosYaw) - subExt->velZ) * 0.25f; subExt->offsetX += subExt->velX; subExt->offsetZ -= subExt->velZ;` (BB1, both FAKEs gone) 5: stickX 1581|0 bit 150 3.0 -> $f2 (mul.s at 0x5e18), velX load 1252|6 bit 168 -> $f14, velZ load 1252|7 bit 174 -> $f16 all as in the target; only stickY 474|0 bit 157 3.0 takes $f12 and errX 1517|0 bit 163 2.0 takes $f18 (target: error $f12 at 0x5e48, stickY $f18 at 0x5e28). Same 5 with `=` instead of `+=`, with stickX/errX in the velX/velZ declaration slots, with errX named velX (diffDelta style), with stickY block-scoped (7). variants.py scan of the BB1 copy (84 variants): no zero.
- Rank chain for BB1: without pre-reads the loads are numbered inside the error statement, after stickY, so stickY must fall below 3.0 and errX rise to exactly 3.0 (its bit 163 already precedes the velX load). stickX and stickY have one liveness (both defined before the error, last used in the velZ line), so no natural ref change lowers stickY without stickX: two adjsave changes, as in the pre-read structure (z web 4.5, velX load copy 4.0).
- Pre-read locals by position (lever b, named local reverses load numbering): velX/velZ pre-reads in all 15 orders around the stick lines, loads used in the updates 97-103 (the velX var is a 2.0 phantom candidate that takes a register), velZ pre-read only 10-13; pre-read vars also used in the updates (Q0601 one field read for use) 87-109.
- Line-order layouts (lever a: stick lines on one line, stickY + error on one line, error + update on one line) 5 each; statement reorders: stickY first 9, velZ update before velX update 34, velZ term operands swapped 62, constant-first products 7.
- One dead test as a compound for both sites (lever e: `if (stickX) {}`, `if (errX) {}`, `if (stickX && errX) {}`, `if (errX && stickX) {}` after each case-0 statement, 22 bodies) 91-129: every split halves stickX together with stickY.
- One-reuse checks in BB1: stickX in z 5 (stickX is already first), stickY in the aim y 12 (y's bb43 range stays single-block 3.0), velX load-copy error with stickX first 13 (error var 4.0 outranks stickX 3.0), errX in the dist/scale local (BugBash diffDelta) 15, plus stickX in x 15; errX refined in place (`errX *= 0.155f; subExt->velX += errX;`) 98; stickX refined in place 108.
- Permuter 905 s (-j 2, hack-free weights, 20854 iterations) on the BB1 template (both sites honest, no pre-reads): baseline 25, best 25 (no output below the baseline). quality.py sweep: 0 hits. Final: no change to this function, copy byte-identical to the base, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line), cwarn 0.
2026-11-18 cleanup CleanbonusSearchlightSeekGameUpdateb anthropic/claude-opus-5-5 (base a1d5bac2; variants.py try, full= lines; uopt -l 5/6):
- Re-measured at a1d5bac2: velX var 538|0 bit 150 4.0 -> $f12, velX load 1252|6 bit 152 3.0 -> $f14, velZ load 1252|7 bit 156 3.0 -> $f16, z web 602|1 bit 158 4.5 -> $f2, stickY 474|0 bit 165 3.0 -> $f18 (unchanged from 8b129890).
- New: rotated-stick target-velocity locals (targetVelX = stickX * cosYaw - stickY * sinYaw; targetVelZ = stickX * sinYaw + stickY * cosYaw), both sites honest. Inline lerps `subExt->velX = subExt->velX + (targetVelX - subExt->velX) * 0.155f` (tv1), `+=` forms (tv2), the targetVel locals in the 6th/7th declaration slots (tv3), block-scoped targetVel locals (tv6): 101 each (targetVel copy-propagated, the error becomes a $f10 temp). velX pre-read + targetVelX (tv4) 91. targetVelX + errX (tv5) 5, the same as BB1: uopt -l 5 stickX 538|1 bit 150 3.0 -> $f2, stickY 474|0 bit 157 3.0 -> $f12, targetVelX 90|0 bit 163 copy-propagated (no candidate), errX 26|1 bit 169 2.0 -> $f18, velX load 1252|6 bit 171 -> $f14, velZ load 1252|7 bit 177 -> $f16. variants.py scan of tv5 (83 variants): no zero.
- New: stickX first, then a velZ pre-read, then stickY, honest errX (sv1, the dossier's "stickY defined after the velZ load is first numbered" idea): 104.
- Single-read argument: the target reads the error register $f12 once (mul.s $f4,$f12,$f6 at 0x5e4c; next $f12 write at 0x5f80), so an honest error local has 1 def + 1 use = 2.0, below the five other bb43 candidates' 3.0 in every statement and declaration order; only a counted first def from the CSE'd subExt->velX load (Q1049, i.e. d3c36c) lifts it above the load. With d3c36c at 4.0, stickX needs > 4.0 (or 4.0 with a lower bit), which only the z web (83418a) or a two-def stickX that moves the cvt into $f2 (Q1250, 108) gives. The two FAKEs are the minimum under the uopt priority model (Q0163).
- Permuter 900 s (-j 2, hack-free weights, 15535 iterations) on the tv5 body (both sites honest, targetVelX feeding errX): baseline 25, no output below it (1028 compile errors).
- Review: empty case-0 braces (no declarations) dropped, both FAKE comments rewritten in adjsave/register terms, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line). quality.py sweep: 0 hits.
2026-11-18c cleanup CleanbonusSearchlightSeekGameUpdatec anthropic/claude-opus-5-5 (base a05ab709; variants.py try, full= lines; uopt -l 5/6):
- Re-scored at a05ab709 (after the static-data campaign f960a16f..4e14b5c5 and the 18b renames 7a1f8709): bb43 unchanged (velX var 538|0 bit 150 4.0 -> $f12, velX load 1252|6 bit 152 3.0 -> $f14, velZ load 1252|7 bit 156 3.0 -> $f16, z web 602|1 bit 158 4.5 -> $f2, stickY 474|0 bit 165 3.0 -> $f18; -l 6 colours 158, 150, 152, 156, 165 in that order, all constrained). Re-measured: honest trailing stickX 10, honest errX (z kept) 99, fully honest 101, BB1 5 (stickX 90|0 bit 150 3.0 -> $f2, stickY 474|0 bit 157 3.0 -> $f12, errX 538|0 bit 163 2.0 -> $f18, loads bits 168/174 -> $f14/$f16). quality.py sweep: 0 hits.
- New, second-block divisor lever (Q0163) for stickY, the one competitor BB1 must lower below 3.0: stickY defined between the mathSinF and mathCosF calls 192 on BB1 and 192 on the hacked base. stickY then crosses mathCosF and is homed instead of coloured (swc1 $f6,108(sp) at 0x5df4, lwc1 $f8,108(sp) at 0x5e2c and for the velZ term; .text +16 bytes). Both stick lines there (BB1) 186: both homed (swc1 $f8,116(sp) / $f18,92(sp) at 0x5e00/0x5e08), frame 0x88 -> 0x90. The only reachable second block is across the call, and there the value goes uncoloured instead of moving down the bb43 order.
- Final: no change to this function, copy byte-identical to the base, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line).
2026-11-21 continue unit 2 LeverBonus2690 anthropic/claude-opus-5-5 (base 18884cf4; lever Q1590; variants.py try, full= lines; uopt -l 5):
- Re-scored at 18884cf4: bb43 unchanged (538|0 bit 150 4.0 -> $f12, 1252|6 bit 152 -> $f14, 1252|7 bit 156 -> $f16, z web 602|1 bit 158 4.5 -> $f2, stickY 474|0 bit 165 -> $f18). quality.py sweep: 0 hits.
- Lever precondition: honest stickX with its line first (before the velX/velZ pre-reads), velX FAKE kept, 5 lines: stickX 1581|0 bit 150 3.0 -> $f12, error var 538|1 bit 157 4.0 -> $f2, loads 159/163 -> $f14/$f16, stickY 165 -> $f18. So stickX already has the lower bit and would win an exact 4.0 tie (Q1590/Q1551); it lacks one counted ref. variants.py scan of that copy (87 variants): best 5, no zero.
- Code-free extra refs after the mul are all dropped before counting (stickX stays 1581|0 3.0, 5 lines each): `stickX *= 1.0f;`, `stickX = stickX;`, `+ (stickX - stickX)` in the velZ term, a dead copy `x = stickX;` (x redefined before any read), and a redundant recompute `stickX = stick_x * 0.06f;` after the stickY line (14: the first def becomes dead, stickX moves to bit 165).
- A real second def after the velX update, `stickX = stickX * sinYaw + stickY * cosYaw;` feeding `(stickX - velZ) * 0.25f` (an unrelated-role reuse), counts: 1581|0 5.0 -> $f2 with all five bb43 colours right, but the velZ target is then held in stickX: `add.s $f2,$f6,$f4` instead of `add.s $f8,$f6,$f4` at 0x5e68 and every later temp shifts: 80.
- Final: no change to this function, copy byte-identical to the base, fdiff 0, clint uninit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line).
2026-11-21 continue unit 2 LeverBonus2690 follow-up anthropic/claude-opus-5-5 (base 48370a9c, fresh copy .scratch/LeverBonus2690/f/2690.c; Q1599 re-check of d3c36c; variants.py try, uopt -l 5):
- Honest trailing `f32 errX` with the z steer and both pre-reads kept: 99. errX (1581|0 bit 171) is copy-propagated into the velX update and has no live range; the pre-read velX var 538|1 is a 2.0 phantom -> $f18, the velX load 1252|6 3.0 -> $f12, the velZ load -> $f14. Q1599 code-free uses of errX (`errX *= 1.0f;`, `errX = errX;`, `+ (errX - errX)`, dead copy `x = errX;`): 99 each, all five bb43 records unchanged.
- Q1599 real-code condition: in bb43 the target writes $f12 only at 0x5e48 (sub.s $f12,$f10,$f14) and reads it only at 0x5e4c (mul.s $f4,$f12,$f6); the partial sum (0x5e44) and the product go to $f10/$f4 temps, so no target instruction can take a third counted ref of the error. Q1596/Q1597 need a tie (split error 2.0 vs 3.0 loads); Q1601/Q1602 concern call-crossing or spilled values (the error is single-block). No change, fdiff 0, clint uninit 0, cwarn 0.
2026-11-26 cleanup CleanbonusSearchlightSeekGameUpdate anthropic/claude-opus-5-5 (base d366ec4e; R-oildrum three-part census, Q1666; bodies in .scratch/CleanbonusSearchlightSeekGameUpdate/census/{b,n,h}/, scores `variants.py try` (try1-4.txt), stack facts from `deadsweep.py score --diff` per body (d/*.diff, summarised by census/analyze.py into part1_summary.txt / part2_summary.txt / hidden_summary.txt)):
- Census on 83418a (stick role of z) and d3c36c (error role of velX), each split alone and both together, 114 part-1 bodies + 22 no-local bodies: no body matches; both FAKEs stay (part 1 fails for each, see `## Census (Q1666)`). d3c36c's comment refreshed (it described the BB1 template's 2.0/$f18 error; on this body a separate errX is copy-propagated).
- Hidden-reuse sweep of every local: z's aim-point role (line 2024) is an untagged unrelated-role reuse whose census fails (21 bodies): tagged `// FAKE` (pre-existing, now tagged, copy-only key).
- variants.py scan --max 0 (135 variants each) of the stickX-split copy (trailing f32 stickX, base 10): best 10, every variant ties the base (truth/swap/switch respellings), no zero; of the errX-split copy (trailing f32 errX, base 99): best 69 (`110.0f` -> `110.0`, a value-changing double literal), then `0.25f` -> `0.25` 73, `errX * 0.155f` operands swapped 76, other float suffixes 81-89; no zero (census/scan/*.txt).
- fakehunt pass-1 zero (83418a output-0-1) not re-run (the lead's reading: it re-merges stick_x into z). d3c36c's as1 hints (99 -> 93 by deleting record 542 `add.s $f8,$f6,$f4` or swapping it with its `s.s`, i.e. the offsetX update's add in records 540-543 `l.s l.s add.s s.s`) drop the add or store before computing it; no C spelling follows from them.
- Final: two comment-only edits (d3c36c refreshed, line 2024 tagged), fdiff exit 0, clint uninit exit 0 (only the pre-existing bonusBigBugBashGameUpdate diffDelta line), cwarn 0.

## Census (Q1666)
Target stack (expected object): frame 0x88 (`addiu sp,sp,-136` 0x5908); named homes used: sinYaw 132 (swc1 0x5dc4, lwc1 0x5e20/0x5e58), x 124 (aim 0x5f5c/0x5f80, clamp 0x60a8/0x60dc), y 120 (0x5f68/0x5f8c), z 116 (clamp 0x60ac/0x60c4), spawnAngle 90 (sh 0x5c34, lh 0x5c48); outgoing args 16..40. Locals declared after spawnAngle (velZ, scale) never take a home and do not size the frame.
Positions: function scope F00 (first) and after each of sinYaw cosYaw x y z velX stickY subExt spawnExt i dist spawnAngle velZ scale (F01-F14); block scope: `case 0: { ... }` block (Bcase), bare block over the role's lines (Bbare), bare block with the initialised declaration (Binit); `register` at F00, F07, F14, Bcase, Bbare (each identical to the plain body). Type f32 only: both values are floats (no narrow width applies).
### Part 1, 83418a: `f32 stickX` for the scaled stick_x (velX FAKE kept)
| positions | full | frame | what moved |
|---|---|---|---|
| F00-F11 (before spawnAngle, 12 slots + register) | 25 | 0x88 -> 0x90 | every home shifts: below the new slot +4, above it +8 (e.g. F00: sinYaw 132->136, x 124->128, y 120->124, z 116->120, spawnAngle 90->94); bb43 recoloured as below |
| F12-F14 (after spawnAngle/velZ/scale) + register | 10 | 0x88 kept | NO stack change: every home and offset identical; only bb43 colours: stickX $f16 (mul.s 0x5e18), velX load $f12, velZ load $f14, error $f2 |
| Bcase, Bbare, Binit + register | 10 | 0x88 kept | as F12-F14 (register-only) |
Result: FAILS (frame-keeping, home-keeping split at 3 function slots and every block scope: register-only, 12E800 `near` ruling).
### Part 1, d3c36c: `f32 errX` for the x velocity error (z FAKE kept)
| positions | full | frame | what moved |
|---|---|---|---|
| F00-F03 | 112 | 0x88 -> 0x90 | homes +4/+8 as above; errX copy-propagated (below) |
| F04-F11 | 110 | 0x88 -> 0x90 | homes +4/+8 |
| F12-F14 + register | 99 | 0x88 kept | NO stack change; errX copy-propagated into the update: `sub.s $f6,$f10,$f12` (error a $f6 temp), velX load $f12, velZ load $f14, stickY $f16, the sub.s hoisted above the 0.155f load, every later FP temp rotated |
| Bcase, Bbare, Binit + register | 99 | 0x88 kept | as F12-F14 |
Result: FAILS (register/schedule-only at the frame-keeping positions).
### Part 1, both splits together
| positions | full | frame | what moved |
|---|---|---|---|
| both at F00 (both orders, register) | 103 | 0x90 | frame only (homes keep their sp offsets: the two new words sit on top) |
| both at F01/F02 | 105 | 0x90 | sinYaw 132->140 |
| both at F03 / F04 | 107 / 108 | 0x90 | x/y homes move |
| both at F05-F11 | 110 | 0x90 | sinYaw/x/y/z homes move |
| both at F12-F14 (both orders, register), Bcase, Bbare, Binit | 101 | 0x88 kept | NO stack change (register-only) |
| one local at F14, the other at F00-F11 | 112-114 | 0x90 | homes move |
| one local at F14, the other at F12-F14 | 101 | 0x88 kept | NO stack change |
### Part 2, no-local spellings
| role | spelling | full | stack |
|---|---|---|---|
| stick | `gCurrentContPad->stick_x * 0.06f` inline at both uses (also parenthesised) | 187 | stick_x read twice (`lb t1,3`/`lb t2,2`, then `lb t3,2(t4)` after the velX store); the target reads it once (`lb t1,2(v0)` 0x5dec), so this re-read would be a steer anyway |
| stick | `OSContPad *pad` local (trailing, assigned at the stick line or before the pre-reads; stick_y through pad too) | 185 | frame kept |
| stick | `OSContPad *pad` declared first | 199 | frame 0x90 |
| stick | `static f32 stickX` | 21 | .bss store + reload (R HI16/LO16 .bss) |
| stick | direct field/array write | n/a | no field holds the scaled stick (only an arithmetic operand of two products) |
| error | inline in the update `subExt->velX = subExt->velX + (t - velX) * 0.155f` / `+=` | 101 | sinYaw reload 132 dropped |
| error | inline with the pre-read as the base `subExt->velX = velX + (t - velX) * 0.155f` | 88 | 681 lines |
| error | field re-read, no pre-read (`... - subExt->velX`, `=` and `+=`) | 101 | |
| error | error first stored to the field (`subExt->velX = t - velX; subExt->velX = velX + subExt->velX * 0.155f`) | 88 | an extra store the target lacks |
| error | `f32 *pv = &subExt->velX` (with and without the pre-read through pv) | 101 | |
| error | `static f32 errX` | 107 | .bss store |
| both | both inline (stick inline + error inline / re-read / `+=`) | 174 | |
| both | both static | 126 | |
Result: FAILS for both roles (best 21 stick static, 88 error).
### Part 3, roles
- z: f32 throughout. Stick role lines 2004-2008, $f2 `mul.s $f2,$f10,$f4` 0x5e18, reads 0x5e30/0x5e5c; aim z lines 2024-2025, `add.s $f2,$f4,$f8` 0x5f90 -> `mfc1 a2,$f2` 0x5f94; clamp z lines 2056-2061, `lwc1 $f2,16(s5)` 0x60a0, home `swc1 $f2,116(sp)` 0x60ac / `lwc1 $f2,116(sp)` 0x60c4, `mul.s` 0x60e8. Disjoint (case-0 arm, then the fire block, then after the switch); one colour ($f2) for the whole web. Plausibility of the stick role in `z`: weak (an x-axis stick value in the z coordinate scratch). Holds as a disjointness fact; moot after part 1.
- velX: f32. Pre-read line 2002 (`lwc1 $f14,20(s5)` 0x5e00), last read by the error statement (sub.s 0x5e48; the add.s 0x5e50 reads the CSE'd field load in the same register); error lines 2006-2007 (`sub.s $f12,$f10,$f14` 0x5e48, `mul.s $f4,$f12,$f6` 0x5e4c). Disjoint: the error starts where the pre-read dies. Moot after part 1.
### Hidden-reuse sweep (every local)
| local | values (lines) | target | outcome |
|---|---|---|---|
| sinYaw | sin(camYaw) (2000) | home 132 across mathCosF | one role |
| cosYaw | cos(camYaw) (2001) | copy-propagated into $f0 | one role |
| x | aim x (2022), clamp offsetX (2055) | both stored to home 124 (0x5f5c, 0x60a8) | ORIG (two values spill to one home), lines 2022/2055 |
| y | aim y (2023) | home 120 (0x5f68) | one role |
| z | stick (2004, FAKE 83418a), aim z (2024), clamp z (2056, home 116) | aim z never stored | aim role: census below, FAILS -> tagged |
| velX | pre-read (2002), error (2006, FAKE d3c36c) | | censused above |
| stickY | stick_y * 0.06f (2005) | $f18 | one role |
| subExt, spawnExt | customState pointers (1914, 1972) | s5 / s0 | one role each |
| i | respawnTimers index in the init do-while (1962) and the respawn for loop (1968) | | same role, each loop reinitialises (R7) |
| dist, spawnAngle, velZ, scale | one assignment each (2057, 1978, 2003, 2059) | | one role |
z's aim role census (bodies h/, `f32 aimZ` for line 2024-2025, z keeps stick + clamp):
| positions | full | frame | what moved |
|---|---|---|---|
| F00-F11 | 29 | 0x88 -> 0x90 | homes +4/+8 |
| F12-F14, the fire if-block, bare block, initialised block | 16 | 0x88 kept | NO stack change: the z web loses the aim block; stick role $f2 -> $f14 (mul.s 0x5e18), error $f12 -> $f2, velX load $f14 -> $f12, clamp z $f2 -> $f14 (0x60a0-0x60e8), clamp scale $f12 -> $f2 |
| aimZ and stickX both split, trailing | 19 | 0x88 kept | register-only |
No-local: the aim z inline as the projectileSetTargetCoords argument 67 (frame kept); `static f32 aimZ` 21 (.bss store). Part 3: f32, aim 0x5f90-0x5f94 vs clamp 0x60a0-0x60e8, disjoint. Result: parts 1 and 2 FAIL -> line 2024 tagged `// FAKE` (pre-existing, now tagged). x's ORIG does not extend to z: x's aim value reaches x's home (0x5f5c), z's never does, and a separate aimZ keeps the frame.
## Untried ideas
stickX (83418a) / velX error (d3c36c): closed under the uopt model by the 2026-11-18 single-read argument (Attempts): an extra natural use of the error needs a second read of $f12 that the target does not have, and stickY's position cannot help while the honest error stays at 2.0. A second block for stickY is only reachable across the mathCosF call, which homes it (2026-11-18c). The Q1590 tie lever (2026-11-21) is closed too: a code-free extra ref after the mul is not counted, and a counted in-block def holds its value in stickX's register. The Q1666 census (2026-11-26) fails at part 1 for both and for z's aim role (register-only splits after spawnAngle and in blocks). Left only: a new uopt counting mechanism (another code-free counted ref besides Q1049's CSE-load first def) found in another function, then retried here; the three z roles and the velX roles are coupled (one z web over 5 blocks), so any lever must move all of them together.

## Evidence
- Frame 0x88: saves s0-s6 at 56..80(sp), ra 84(sp), 12 declared local words 88..135(sp) highest-first: sinYaw 132 (spilled at 0x5dc4), cosYaw 128, x 124, y 120, z 116, velX 112, stickY 108, subExt 104, spawnExt 100, i 96, dist 92, spawnAngle 88.
- Aim: swc1 $f6,124(sp) 0x5f5c (x), swc1 $f10,120(sp) 0x5f68 (y), reloaded into $f12/$f14 at 0x5f80/0x5f8c, z in $f2 -> mfc1 a2 at 0x5f94.
- Clamp: swc1 $f0,124(sp) 0x60a8 (x), swc1 $f2,116(sp) 0x60ac (z), reloads at 0x60c4/0x60dc after sqrtf; scale div.s $f12,$f14,$f0 at 0x60d8; mul.s $f4,$f6,$f12 / $f8,$f2,$f12 at 0x60e0/0x60e8 (x * scale order).
- Case 0 keeps z (stick_x*0.06f), velX pre-read, velZ pre-read, stickY in registers ($f2, $f14, $f16, $f18); the velX error is $f12 (sub.s $f12,$f10,$f14 at 0x5e48), the new velX is stored at 0x5e54 and reloaded at 0x5e78 for the offsetX add.
- bb43 adjsave (uopt -l 5, hacked base, 8b129890): error var 538|0 bit 150 4.0 -> 26 ($f12); velX load 1252|6 bit 152 3.0 -> 27 ($f14); velZ load 1252|7 bit 156 3.0 -> 28 ($f16); z web 602|1 bit 158 4.5 -> 25 ($f2); stickY 474|0 bit 165 3.0 -> 29 ($f18). (At the 2026-11-16 base the same records sat at bits 148/150/154/156/163.)
- Block structure at ba499c04: calls end uopt blocks here. sinYaw's def is in bb42 and its 2 uses in bb43 (it crosses the mathCosF call, so it is spilled to 132(sp) and reloaded at 0x5e20/0x5e58); bb43 runs from the mathCosF return to the `bnez` at 0x5e9c, so every case-0 FP value except sinYaw is single-block. cosYaw is copy-propagated into the FP return-register candidate 346|1 (2 uses in bb43), so $f0 (24) is forbidden to all of them.
- BB1 template (no pre-reads, uopt -l 5 at b5e2166e): stickX 1581|0 bit 150 3.0 -> 25 ($f2), stickY 474|0 bit 157 3.0 -> 26 ($f12), errX 1517|0 bit 163 2.0 -> 29 ($f18), velX load 1252|6 bit 168 3.0 -> 27 ($f14), velZ load 1252|7 bit 174 3.0 -> 28 ($f16); all single-block in bb43; target needs the 26/29 pair swapped. With a velX pre-read named local the var 538|1 (bit 150, 2.0) stays a phantom candidate that takes a register without code.
- Error register: $f12 is written by sub.s $f12,$f10,$f14 at 0x5e48 and read only by mul.s $f4,$f12,$f6 at 0x5e4c; the next $f12 access is the aim reload lwc1 $f12,124(sp) at 0x5f80.
- tv5 template (uopt -l 5 at a1d5bac2): targetVelX's def `ustr{90|0}{1571|0}` is copy-propagated; the error def is `ustr{26|1}{usub{1571|0}{1252|6}}`, and every one of the five FP candidates interferes with the other four (one bb43 interference list).
- Re-score at a05ab709: the five bb43 records, bits, scores and colours above are unchanged (uopt -l 5/-l 6 of the base copy).
- Lever check at 18884cf4 (uopt -l 5): with the honest stickX line first, stickX 1581|0 sits at bit 150 below the error var 538|1 (bit 157), so an exact 4.0 tie would give it $f2; refs that emit no code (`*= 1.0f`, self-copy, `(s - s)`, a dead copy, a redundant recompute) are removed before adjsave counting, and a counted second def is computed into the variable's own colour ($f2 at 0x5e68).
