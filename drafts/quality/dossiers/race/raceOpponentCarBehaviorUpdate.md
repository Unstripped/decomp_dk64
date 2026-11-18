# raceOpponentCarBehaviorUpdate (race, src/race/36B0.c)

## Sites
- race:80028440:other:f726c6 (`cursorVal = statePhase;`, first `switch (cursorVal)` on raceStatus 0):
  steered uopt colouring of the dispatch `lbu v1,53(s1); move a0,v1; beqz v1; move v0,v1`
  (load/cvt in v1, phase in a0, selector in v0). REMOVED 2026-11-17 (see Attempts): there is no
  phase or selector local at all; `switch (state->unk35)` with `state->unk35++` in every arm and
  `if (state->unk35 < 3)` gives cfe's shared switch temp v0, the load v1 and the end-test value a0.
- race:80028440:other:1dd5de (byte-offset iterator `*(s16 *)((u8 *)soundSlots + audioSlot)`):
  REMOVED 2026-11-16 (see Attempts).
- No hack sites left.

## Attempts
- 2026-11-16 HackraceOpponentCarBehaviorUpdate anthropic/claude-opus-5-5:high
  - 1dd5de fixed: `gCurrentActor->soundSlots[idx]` (uopt builds the byte IV in v1 and spills
    it at 52(sp), the spill slot sits 16 below the lowest named home), plus the layout:
    named homes must be exactly 11 words (lowest home 68) under `pad70[2]`. Done by dropping
    audioSlot, pad38[1], pad30, inlining f32 unclampedVal (`cursorVal > 10.0f`, the u32->f32
    conversion is the same) and letting statePhase also be the raceStatus 5 selector
    (`statePhase = state->unk35; switch (statePhase)`, endPhase gone). fdiff 0 (whole file OK).
    Dropping cam/count/endPhase-into-`switch (state->unk35)` instead changes codegen.
  - f726c6 tried (all fdiff 1, scores = variants.py try full):
    `phase = F; switch (state->unk35)` 7 (v0/v1 swapped: cvt v0, selector v1);
    `phase = F; sel = F; switch (sel)` (sel = cursorVal, endPhase, statePhase or a dedicated
    function/block-scope u32/s32/u8/u16 local) 7-31 (same swap, or frame/spill shift for a new local);
    `sel = F; phase = sel; switch (sel)` and `phase = sel = F` 4 (colouring right, but ugen emits
    the selector move before the phase move: `move v0,v1; beqz v1; move a0,v1` delay slot);
    phase u8/u16 in that form 2 (`andi a0,v1,0xff` in the delay slot);
    `phase = F; sel = phase` 9 (phase and selector coalesce); no phase local, post-switch
    `if (state->unk35 < 3)` 9 (PRE reuses the load register v1, no `move a0,v1`);
    case 0 `phase = state->unk35 = state->unk35 + 1` 3 (colours right, case 0 computes into v0
    with `andi a0` before the `sb`); `++`/`+=` spellings of the arms 7-14.
  - as1probe scan on the `sel = F; phase = sel` form: only `delete` of the phase move helps;
    no C-emittable single edit.
  - permute (v3 base: soundSlots[idx], no statePhase, `switch (state->unk35)`): see ledger.

- 2026-11-16d HackraceOpponentCarBehaviorUpdate2 anthropic/claude-opus-5-5
  - Re-scored on the u16 gTextNumberArg declaration (TypesOwner batch_6 part A): every
    form above scores the same (switch(F) 7, `phase = statePhase = F` / `statePhase = F;
    phase = statePhase` 4 order-only, `phase = F; statePhase = F; switch (statePhase)` 7
    colour-swap, `phase = F; switch (phase)` 9); statePhase/phase widths u8/u16 2-10.
  - f726c6 fixed: `u32 sel` used as the selector of BOTH switches (`sel = statePhase;
    switch (sel)` on raceStatus 0, `sel = state->unk35; switch (sel)` on raceStatus 5).
    uopt -l 5: a u32 selector needs no cfe switch temp; sel adjsave 3.0 (two switches) >
    load cvt {210} 2.0, so sel takes v0 and the cvt v1. Frame: sel declared second under a
    one-word pad (`s32 pad74; u32 sel;`): pad70[2] -> pad74 keeps the homes (flagPtr 0x6c)
    and the IV spill at 52(sp). Needs the s32 statePhase single-def copy (`statePhase = F;
    sel = statePhase`, or `switch (sel = statePhase)`): `sel = F` gets its own u8->u32 cvt
    (16), `sel = phase` 9 (phase multi-def). Declaring sel beside statePhase shifts homes (11).
    stunTimer local (was cursorVal) renamed. fdiff 0, whole-file OK, uninit 0. Not merged
    (lead: statePhase is a redundant alias).

- 2026-11-17 CleanraceOpponentCarBehaviorUpdate anthropic/claude-opus-5-5
  - f726c6 FIXED, fdiff 0 whole file, uninit 0, cfe warnings 0: the race/0
    raceOpponentBehaviourUpdate shape (Q1053 2026-11-17 correction) applied here. No phase,
    statePhase or selector local: raceStatus 0 `switch (state->unk35)` with `state->unk35++`
    in all three arms (case 0 included) and `if (state->unk35 < 3)`; raceStatus 5
    `switch (state->unk35)`. The two dropped homes become an untagged `s32 pad44[2]` after the
    named locals (homes 108/104/96 and the IV spill at 52(sp) kept). Measured: case 0 as
    `state->unk35 = state->unk35 + 1` (the 2026-11-16c no-local attempt) 9-13; no pad 13;
    `pad70[3]` 15; keeping statePhase for raceStatus 5 plus `s32 pad` also 0 (not chosen:
    the two switches read the field the same way without it).
  - Brief levers measured before the fix (all with a dedicated stunTimer local, scores =
    variants.py try full): (d) block-scoped selector in the raceStatus 0 block, u32 18-27,
    s32/u16/u8 9-18 (v0/v1 swap; the block local also moves the IV spill to 48(sp));
    shared s32 selector 7 (cfe shared temp at 1.5, forbidden v0, loses to the cvt at 2.5);
    shared u32 `sel = F` 16; (a)/(b) statement orders `phase = F; sel = F` / `sel = F;
    phase = F` / `switch (sel = F)` identical (uopt CSE); `sel = phase = F` 9 (coalesce);
    `phase = sel = F` 4 order-only; case 0 via `phase + 1` / `sel + 1` 12-13, `phase++;
    state->unk35 = phase` 16; (c) u8/u16 phase: `phase = F; switch (phase)` 4 (`move v0,v1;
    beqz v0; move a0,v0`), with a u32 sel `phase = sel = F` 2 (`andi a0,v1,0xff` in the
    delay slot); s8/s16 phase 81-101.
  - Review: stunTimer is a u8 local (u8 and u16 also 0 per variants scan; the field is u8);
    raceStatus 5 loop `idx = 0; do { ... idx += 1; } while (idx != 2)` -> `for (idx = 0;
    idx < 2; idx++)` after the pitch/roll stores (fdiff 0); `(s16)` cast on the mathSinF
    argument dropped (prototype takes s16, fdiff 0); a `RaceCarActor *car` local for the four
    component reads scores 6-21 (casts kept, file convention); flagPtr -> bumpCooldown,
    cam -> pathId.

## Untried ideas
- (none left: no hack sites)

## Evidence
- Target 0x1098-0x10ac: `lbu v1,53(s1); li at,1; lui t5; move a0,v1; beqz v1; move v0,v1`;
  case compares `beq v0,at` 0x10b0/0x10bc; case 0 `addiu t7,v1,1` 0x10d0, `andi a0,t7,0xff`
  0x10ec; case 1 `andi a0,t2,0xff` 0x111c; case 2 `beqzl v0; lbu a0,53(s1)` 0x1128/0x112c and
  `lbu a0,53(s1)` 0x1144; end test `slti at,a0,3` 0x1148.
- Target 0x12ac-0x12e8: loop `addu t3,a2,v1; lh t6,110(t3)`, IV v1 spilled `sw v1,52(sp)`
  0x12d4 around `sfxStopSlotSound`; homes 108/104/96, frame 0x78.
- 2026-11-16d lead ruling (not merged): the u32 sel form (fdiff 0) keeps `statePhase = state->unk35;` only to copy it into sel (`sel = state->unk35` scores 16): a redundant alias, so it would carry its own `// FAKE` tag; swapping the tagged reuse for a tagged alias is no net drop.
