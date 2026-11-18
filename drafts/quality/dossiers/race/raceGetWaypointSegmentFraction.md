# raceGetWaypointSegmentFraction (race, src/race/36B0.c)

## Sites
- 85cf24 (other): the embedded store `sqrtf((e2 = sum) / d2)`. KEPT (FAKE, lead ruling: steer).
  - The tagged line's own operations are the target's 0x1b0 `swc1 $f10,76(sp)` (sum into e2's home) and 0x1b4 `lwc1 $f4,76(sp)` (read back for `div.s $f12,$f4,$f6` at 0x1bc).
  - Mechanism (2026-11-17): cfe ucode of the embedded form and of a separate `e2 = sum; return sqrtf(e2 / d2);` differ only in where `mst` sits. Embedded: the `str e2` is inside sqrtf's argument evaluation (after `mst`).
    - uopt then keeps the e2 difference temps off $f12/$f14: z $f16, x $f18, y homed at 60(sp) (0x190/0x194). [INFERENCE] the float argument registers are reserved inside the argument region.
    - ugen reloads a variable stored inside the argument evaluation (0x1b4), but forwards one stored before `mst` (d2, stored at 0x188 and divided from $f6; e2 in the separate-statement form).

## Attempts
- 2026-11-11 round 16 CleanRaceB / Rev16F, round 17 Rev17N: plain/recipe nohit; diagnose of the store/reload; permute (best re-creates the embedded store; without e2: best 63).
- 2026-11-14 HackraceGetWaypointSegmentFraction: dx/dy/dz locals 50/47/60, `f32 dist[2]` 54, decl order 3, no e2 13, `e2 /= d2` 18, ratio local 18, f64 e2 43, x+y+z order 19, out - cur 18.
- 2026-11-17 CleanraceGetWaypointSegmentFraction (anthropic/claude-opus-5-5):
  - Sum inline in the sqrtf argument, `f32 e2;` declared and unused: full=3. The only difference is the missing 0x1b0/0x1b4 store/reload (div from $f10).
  - Separate statement, also on one line (no `loc` between): 18. `f32 e2[1]` (non-vreg) separate statement: 18. `e2 = sqrtf(e2 / d2); return e2;`: 18.
  - In-place refinement: `e2 = x+y; e2 = z + e2;` 38, `e2 = x+y; e2 += z;` 40, `e2 = x; e2 += y; e2 = z + e2;` 36.
  - Partial sum outside the call: `e2 = x+y; sqrtf((z + e2) / d2)` 37, `e2 = z; sqrtf((e2 + (x+y)) / d2)` 17.
  - variants.py scan around the hack-free inline body: 18 variants, best 3 (no zero).
  - Hack-free-weights permuter from the inline body (-j 2, 900 s): base 205, best 74. It re-inserts `e2 = sum` inside the sqrtf argument, plus a volatile pad and a copy local.

## Untried ideas
- None in plain C: the store/reload needs the assignment inside sqrtf's argument evaluation. The other spelling that does this is a comma expression, which is also a hack.
- Lead decision (director ruling turn 112, applied by CleanupLead17f in the merge): ORIG with the 0x1b0/0x1b4 offsets. The lead checked both in the expected object. The target stores into e2's own home slot: removing the declaration shifts the temp homes 0x4c->0x48, 0x44->0x40 and 0x3c->0x38. Apart from the div.s source register, the hack-free no-store body differs only by those two instructions.

## Evidence
- Target 0x188 `swc1 $f6,80(sp)` (d2 home, divided from $f6, never reloaded). 0x1b0/0x1b4 `swc1 $f10,76(sp)` / `lwc1 $f4,76(sp)`. 0x190/0x194 y-term store/reload at 60(sp).
- cfe ucode (as1probe `ucode --cfe`): base `mst; ... str f32 Mmt -44; lod f32 Mmt -44; lod f32 Mmt -40; div; par; cup`. Separate statement: `str f32 Mmt -44; loc 75; mst; lod -44; ...`. Otherwise identical.
