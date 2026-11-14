# playerUpdateCommon (global, src/global/CEAE0.c)

## Sites
- global:806CA5F8:dead-if:8ce181 dead-if: `if (gCurrentActor && gCurrentActor) {}` before the first statement. It keeps the gActivePlayerActor pointer web coloured into v1 at 0xf14-0xf2c (removal gives s0; adjsave tie order, Q0199).
- global:806CA5F8:other:81cda0 other: `(u32)attackerIndex != gActivePlayerState->playerIndex`. The cast makes the local a ucvt isop numbered after the field's, so the compare at 0xe54 is `beq t2,v0`; without it, `beq v0,t2` (Q0715).
- global:806CA5F8:other:8b0fd9 other: `&((PlayerStruct *)gPlayerSlots)[gCurrentPlayerIndex].headX/Y/Z`. The identity cast builds uadd(load, idx*size); cast-free spellings build uadd(idx*size, load) and rotate the t7/t8/t0 scratch ring from 0x12d0 (Q0717).
- global:806CA5F8:goto:u933fb / u36185 / u72d9b / u72d9b#2 goto: the heavyImpact dispatch into the shared `done` tail (Q0591, kept). Switch forms add the 8-byte switch temp (frame 0x78 -> 0x80, Q0296/Q0714); if-chains add 16 bytes.

## Attempts
- 2026-11-09 .. 2026-11-14 (rounds 2-36, opus-5-5 :low/:xhigh): see `uv run tools/quality.py history playerUpdateCommon`. Removals, cond/classify/recipe, uopt_trace diagnoses, permuter runs (all hack swaps), goto-hand switch/if-chain forms, natural reconstructs (1175+).
- 2026-11-14 HackplayerUpdateCommon (anthropic/claude-opus-5-5:high), after the PadInputState/PlayerStruct typings:
  - fresh sweep: all nohit;
  - variants.py scan on each single-removal copy: no zero; best is the float-suffix noise at the removal score.
  - 8b0fd9:
    - PlayerStruct *slot snapshot: function-scope first/last 79, block-scoped 79, also feeding the camProjectToScreen headY 240.
    - `&(gPlayerSlots + i)->headX`: 37 (same as plain).
  - 81cda0:
    - u8 selfIndex snapshot before/after: 269.
    - s32 attackerIndex: 43.
    - inverted if/else: 17.
    - `!(==)`: 1.
  - 8ce181:
    - `Actor *attacker = gCurrentActor` initialiser: 24.
    - state assignment first: 26.
  - Coupled removals: 8ce181+81cda0 25, 8ce181+8b0fd9 61, 81cda0+8b0fd9 38, all three 62, all three + slot local 103.

## Untried ideas
- A field-type change for PlayerState.attackerPlayerIndex/playerIndex was ruled out: playerIndex is already u8, and the s8 side needs the `>= 0` test.
- A natural form that numbers the playerIndex ucvt before the local's (Q0715) would fix 81cda0. A u8 snapshot did not; it reorders far more (269).

## Evidence
- 0xe54: target `beq t2,v0` (field operand first).
- 0xf14-0xf2c: gActivePlayerActor in v1 (target) vs s0 (dead test removed).
- 0x12d0-0x12ec: gCurrentPlayerIndex/gPlayerSlots in t8/t7 ring order (target) vs rotated (cast removed).
