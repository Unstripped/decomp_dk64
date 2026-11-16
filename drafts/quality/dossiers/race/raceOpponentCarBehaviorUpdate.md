# raceOpponentCarBehaviorUpdate (race, src/race/36B0.c)

## Sites
- race:80028440:other:f726c6 (`cursorVal = statePhase;`, first `switch (cursorVal)` on raceStatus 0):
  steers uopt colouring of the dispatch `lbu v1,53(s1); move a0,v1; beqz v1; move v0,v1`
  (load/cvt in v1, phase in a0, selector in v0). The selector must be a variable colored
  before the u8->s32 cvt of the load (cvt adjsave 2.0-2.5); cursorVal (u32 stunTimer local,
  adjsave 3.5 from its earlier uses) is that variable. Still OPEN (kept tagged).
- race:80028440:other:1dd5de (byte-offset iterator `*(s16 *)((u8 *)soundSlots + audioSlot)`):
  REMOVED in this session (see Attempts 2026-11-16).

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

## Untried ideas
- A selector variable whose own earlier uses give it priority > the cvt without reusing an
  unrelated local (none found among the function's roles).

## Evidence
- Target 0x1098-0x10ac: `lbu v1,53(s1); li at,1; lui t5; move a0,v1; beqz v1; move v0,v1`.
- Target 0x12ac-0x12e8: loop `addu t3,a2,v1; lh t6,110(t3)`, IV v1 spilled `sw v1,52(sp)`
  around `sfxStopSlotSound`; homes 108/104/96, frame 0x78.
