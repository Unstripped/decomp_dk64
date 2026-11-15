# raceUpdateWaypointActivation (race, src/race/A960.c)

## Sites
race:8002F950:other:714c8a other (FIXED): `dz = 302500.0f; farAway |= dist > dz;` reassigned dz after `dist = dz*dz + (dx*dx + dy*dy)`, so dist's definition was no longer available at the compare and uopt kept `dist` (vreg -28) as its own coloured web ($f14). That is the 8th FP web; it pushes the hoisted constant to callee-saved $f22 and z/x/y cvts to $f16/$f18/$f20 (frame 0x50, sdc1 $f22,32(sp) + sdc1 $f20,24(sp)). With a literal compare dist is copy-propagated into the compare: 7 webs, frame 0x48.

## Attempts
2026-11-11 r16 CleanRaceB opus-5-5:low: literal compare -> fdiff 1 (frame 0x50 -> 0x48); permute best=0 only by re-adding dz.
2026-11-11 r16 Rev16G opus-5-5:low: permute best=0 reloads the constant through dy (same pattern).
2026-11-12 r33 CleanRaceA960 opus-5-5:low: uopt_trace; constant lives in $f22 only with dz=302500.
2026-11-14 HackraceUpdateWaypointActivation opus-5-5:high: variants.py try (full scores): literal 33; `dist = dx*dx+dy*dy; dist = dz*dz + dist;` 33; `dist += dz*dz` 33; `550.0f * 550.0f` 33; `if (dist > K) farAway = 1;` 69; `?: 1 : 0` 60; dz inlined, dx/dy temps 15; dy inlined 7; dx inlined 9; flat `z² + (x² + y²)` 15; flat `x² + y² + z²` with no temps **0 (fdiff exit 0)**; same without `dist` 42; same with `gPlayerSlots[j].camX` (no p) 12; same with `PlayerStruct *p` 20 (target pre-adds 0x210: `addiu a1,a1,528` at 0x10a8, so `f32 *p = &...camX` is real).

## Untried ideas
none needed; site fixed.

## Evidence
0x1050 `lwc1 $f22,8(at)` constant hoisted above the outer loop; 0x108c-0x10b4 lh z(4)/x(0)/y(2) + cvt.s.w into $f16/$f18/$f20 hoisted out of the inner loop; 0x10a8 `addiu a1,a1,528` (&camX base, stride 0x2f0 at 0x10d8); 0x10c4-0x10f0 dx $f2, dy $f12, dz $f0, `add.s $f4,$f8,$f10` (x²+y²), `add.s $f14,$f6,$f4` (z² + that) into dist's $f14; 0x10f4 `c.lt.s $f22,$f14`. Mechanism: uoptcopy.c find_replacements refuses copy propagation when the assigned value holds an ilod (Q0510/Q0553/Q0559); the flat no-temp sum (Q0065) gives dist ilods, so dist stays a variable, and the three CSEd differences colour $f0/$f2/$f12.
