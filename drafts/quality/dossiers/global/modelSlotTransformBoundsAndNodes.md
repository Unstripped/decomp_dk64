# modelSlotTransformBoundsAndNodes (global, src/global/36880.c)

## Sites
- `global:806358E8:dead-if:e7e49a` dead-if: one of two coupled Q0908 block splits; without both splits, `flag` and `setYOffset` become callee-saved and the frame grows from 0x80 to 0x88.
- `global:806358E8:dead-if:20d7b0` dead-if: second coupled Q0908 block split; either guard alone has removal score 197, while replacing either term with `1` keeps full score 0.
- `global:806358E8:other:f20c24` other: integer-punned bbox address used by the case-2 Y/XZ checks to get offset-first `addu a0,s2,t0/t1` at 0x40c0/0x40f0.
- `global:806358E8:other:94c957` other: same integer-punned bbox address used by the case-1 XZ check at 0x418c.

## Attempts
- 2026-11-10 through 2026-11-14 prior cleanup units: removal/condition recipes did not remove either dead guard; typed bbox, base-first byte pointers, indexed fields, temporary base pointers, and permuter runs did not eliminate the integer address forms. See `history.txt` (137 events).
- 2026-11-16 HackmodelSlotTransformBoundsAndNodes openai-codex/gpt-5.6-sol:high: classified both dead guards as coupled Q0908 block splits. Removal of one or both scored 197; unrelated `if (1) {}` terms at many positions scored 0.
- 2026-11-16 HackmodelSlotTransformBoundsAndNodes openai-codex/gpt-5.6-sol:high: reconstructed the function with repeated typed `gModelSlots[slot]` accesses, dedicated `RenderQuadModelObj *quad` / `ModelType1Obj *model` roles, ordinary `for` loops, and `&gModelSlots[slot].unk48.bbox`; full score 0 with the guards still present and whole-object fdiff 0.
- 2026-11-16 HackmodelSlotTransformBoundsAndNodes openai-codex/gpt-5.6-sol:high: replaced the two dead guards with real control flow: early `break` on NULL `gPlayerSlots`, and `continue` for inactive player slots in cases 2 and 1. Multiline loops scored 8; putting each loop on one source line scored 0. as1probe baseline full=8 found backend record swaps around the loop latch; the one-line `.loc` grouping fixes both latches.
- 2026-11-16 HackmodelSlotTransformBoundsAndNodes openai-codex/gpt-5.6-sol:high: 900-second permuter run on the guard-free typed reconstruction had base 3828/best 0; reviewed zeros reintroduced a three-term dead `gModelSlots` guard, so none was used.

## Untried ideas
- None for the four assigned sites: all are removed. The two one-line loops remain documented `LAYOUT`, with measured line-order evidence.

## Evidence
- Target prologue is frame 0x80 and saves s0-s4 only. Removing the two dead guards alone grows the frame to 0x88 and introduces s5/s6; uopt level 5 changes flag candidate `{922|0}` adjsave 2.3158 to 2.4444 and `setYOffset` candidate `{1319|0}` adjsave 0.125 to 0.2222.
- Case 2 bbox addresses are `addu a0,s2,t0; addiu a0,84` at 0x40c0/0x40c4 and `addu a0,s2,t1; addiu a0,84` at 0x40f0/0x40f4. Case 1 is `addu a0,s2,t0; addiu a0,84` at 0x418c/0x4190. The typed array reconstruction emits these exact sequences without casts.
- The multiline real-control-flow candidate differs only at 0x410c-0x411c and 0x41a4-0x41b4: it hoists the `gPlayerCount` and slot-base reloads before the flag truncation/move. One-line loop grouping restores the target order. as1probe on the full=8 candidate identifies swaps around records 569-572 (`and`, `move`, `.loc`, `lw`) as the improving backend edits.
- Final whole-object `tools/fdiff.sh` exit 0; `clint uninit --base` exit 0; cfe warnings 0.
