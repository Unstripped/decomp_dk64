# modelSlotUpdateGroundCoords (global, src/global/36880.c)

## Sites
global:80632FCC:dead-if:2e1f2a (removed): `if (gModelSlots[slot].unk20) {}` after the switch joined the per-arm unk20 loads into one v1 web (dst a0, groundX/groundZ t3).

## Attempts
2026-11-09..12 (Clean36880, Rev10C, Rev11B, Rev16E, Rev20A): removal recolours v1/a0 to t3/t4/v1; a ModelSlot *ms local 96-110; permuter reinstates the dead test. 9b93c2 fixed by `info = gModelSlots[slot].unk24; switch (info->unk1C)` (Rev20A). See history.
2026-11-15 HackmodelSlotsStepSegmentCommands anthropic/claude-opus-5-5:high: `ModelKindObj *obj` assigned `gModelSlots[slot].unk20` in each arm, `dst = obj->type1.subNode` / `obj->type2.subNode`, dead test removed, obj replaces the `s32 pad` word -> full=0, fdiff 0 (kept). With obj plus the old pad: 13.

## Untried ideas
(none open)

## Evidence
Target 0x150c lw v1,32(v0) (case 1), 0x1500 beql copy and 0x1518 lw v1,32(v0) (case 2): unk20 loads into v1 in every arm, then lw a0,188(v1) / lw a0,84(v1). Default path reads dst's home lw a0,48(sp) (switch without default: uninit pre-existing, original control flow). Q0601.
