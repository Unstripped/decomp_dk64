# playerStartPickupApproach (global, src/global/CEAE0.c)

## Sites
- (fixed 2026-11-18 CleanplayerUpdateCommonb) global:806CEC04:other:a2dc63: was `s32 frames = 15; // FAKE: int constant local steers regalloc (literal 15.0f: one sub.s fewer)`.
  - The target converts the int at run time: `li t5,15` at 0x5020, `mtc1 t5,$f6` at 0x5024, `cvt.s.w $f0,$f6` at 0x5034. $f0 is the divisor of both `div.s` (0x5044, 0x506c), and the value is never stored to a home.
  - cfe folds every literal spelling to `lui 0x4170` and drops those three instructions. So only an int variable that reaches uopt reproduces the target (Q0814).
  - Lead ruling 2026-11-18 (9CE20 `maxAmplitude` precedent): ordinary C. The local stays untagged under its role name.
- (earlier) global:806CEC04:other:c99f21: the same local under its m2c name `div`, renamed `frames` 2026-11-10.

## Attempts
- 2026-11-09 .. 2026-11-12 (CleanArcade0, CleanCEAE0, ReReview, Rev16G, Batch16, Rev26B): see `uv run tools/quality.py history playerStartPickupApproach`. Every attempt was the `15.0f` literal (fdiff 1, full=25), plus sweeps and permuter runs (nohit).
- 2026-11-18 cleanup CleanplayerUpdateCommonb (anthropic/claude-opus-5-5):
  - Divisor spellings scored with `variants.py try`:
    - `/ 15` (an int literal in float arithmetic): full=25.
    - `/ (f32)15`: 25.
    - `/ 15.0f`: 25.
    - `/ frames` (no cast): 0.
  - FAKE tag dropped on the lead ruling. fdiff OK, uninit exit 0, sweep: the site is gone.

## Untried ideas
- none for hacks (no site left).
- Names, cross-file:
  - `D_807532A8` (s16 per-kong table, read by `lh` at 0x4e98) -> `gKongPickupApproachRadius`.
  - PlayerState `unk78`/`unk7C` (f32 per-frame x/z step, added to the actor's x/z each frame in D5E10.c:3174/3180) -> `approachStepX`/`approachStepZ`.
  - PlayerState `unk80` (s16 yaw, copied to actor yaw in D5E10.c:3176/3182) -> `approachYaw`.

## Evidence
- Frame 0x88: mtx at sp+64, offsetX/Y/Z at sp+60/56/52, radius spilled to sp+132 across the calls (0x4f2c, 0x4fc8).
- 0x4f30-0x4f64: `sll`/`sra` 16 on each of the four mathAngleBetweenPointsDeg arguments (the (s16) casts are real truncations to the s32 parameters).
- 0x4e98-0x4ea4: `lh` of D_807532A8[gCurrentCharacterIndex], then `mtc1` + `cvt.s.w` (s16 table converted to f32 radius).
- 0x5020-0x5034: run-time int 15 -> f32 conversion shared by both divisions.
