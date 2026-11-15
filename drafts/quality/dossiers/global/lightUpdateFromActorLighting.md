# lightUpdateFromActorLighting (global, src/global/8F4B0.c)

## Sites
global:8068A858:goto:ud2fe4 goto: in `case 1`, `goto set_color;` jumps into the then-arm of `case 2`. The target has one colour block (0x150-0x234) entered from case 1 (`b 0x150` at 0x134) and by case 2 falling through (0x148). KEPT (Q0591).

## Attempts
2026-11-11 round 11 CleanGlobal8F4B0 opus:low: merged case 1/2 with a ternary test (gA) and a ternary mask (gB): fdiff 1. Permute from the merged ternary: nohit.
2026-11-12 round 17 Rev17M opus:low: duplicating the colour lookup in case 1 adds the cosine/table code twice.
2026-11-14 U HacklightUpdateFromActorLighting opus-5-5: scored structured forms with variants.py try (full lines):
- per-case mask with one guarded block after the switch: 124
- sentinel mask plus default: 132
- doColor flag: 133
- case-1 fallthrough into case 2: 121 (38 with s32/u32 idx)
- if/else-if chain with && and ||: 18
- default arm with && and ||: 18
- shared `case 1: case 2:` label:
  - with && and ||: 11
  - with a u8 mode snapshot: 11
  - with ternary tests: 13/13/13/14

Recipe scans on the shared-label || body and the fallthrough body found no zero.
2026-11-15 U HacklightUpdateFromActorLighting2 opus-5-5:high: re-verified the shared tail at base 5c8c62b and scored new forms with variants.py try (full lines):
- `case 2:` label inside an `if (0) { ... }` block in case 1's then-arm: 0
- the same `if (0) { case 2: ... }` after case 1's `if (gFrameCounter & 0xF) break;`: 5
- `bits = gFrameCounter & mask` per arm, then one `if (!bits)` block after the switch: 131 (u32 and s32)
- case 2 textually before case 1, case 1 jumping back with goto: 125

The zero is Duff-style: the `if (0)` case-label block is the same steer as the goto, so it was not applied. A sentinel switch (Q0844/Q0845) does not apply: the mode switch already compares 0, 1, 2 in order, and the arm tests are masks, not an equality chain.

## Untried ideas
none natural that avoid the jump (the only zero is the `if (0) { case 2: }` block): every structured form either re-tests gCutsceneLightFlickerMode under the shared label or repeats the gFrameCounter test.

## Evidence
- 0xdc-0xfc: compare-chain dispatch. `beqzl v0` goes to case 0 (0x104, `li v0,255` in the delay slot), `beq v0,1` to 0x120, `beq v0,2` to 0x13c, and `b 0x238` to the end.
- 0x120-0x138 (case 1): `lw v0,gFrameCounter`; `andi t2,v0,0xf`; `bnez t2,0x238`; `b 0x150` with delay slot `sll a0,v0,0x2`.
- 0x13c-0x14c (case 2): `lw v0,gFrameCounter`; `andi t3,v0,0x3`; `bnez t3,0x238` with delay slot `sll a0,v0,0x2`; then falls through.
- v0 (gFrameCounter) stays live from both arms into 0x150 (`sll a0,v0,0x2` in each arm's delay slot), so both arms feed one block.
- 0x150-0x234: the shared colour block. It calls mathCosF (jal at 0x160), converts with float->u32 (0x180-0x204: `cfc1`/`ctc1`, 0x4f000000 subtract path), does `andi t8,t7,0xff`, and stores the gLightFlickerColors[idx][0..2] bytes through 72/76/80(sp).
- (f32)(u32) of the u8 fov fields: `bgez` + 0x4f800000 add at 0x350 and 0x370.
