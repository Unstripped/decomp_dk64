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

2026-11-17 U CleanlightUpdateFromActorLighting (strength 3, base bdeab48a): new forms with variants.py try (full lines):
- mask chosen per mode by a single-label inner switch in a shared `case 1: case 2:` arm (`mask = 3; switch (mode) { case 1: mask = 0xF; }`, mask in the pad slot), one test after it: 128; the same with a `case 1:`/`default:` inner switch: 129
- nested early breaks under a shared `case 1: case 2:` label (`if (mode == 1) { if (gFrameCounter & 0xF) break; } else if (gFrameCounter & 3) break;` then the colour code): 16; with `mode != 2`: 18. A recipe scan of the 16 body found no zero (best 16).
- case-1 fallthrough into case 2 with a `mode == 1 ||` guard on case 2's test: 128
- re-measured for the block census: shared label with && and || 11, sentinel mask = 0 + one test 124, doColor flag 133, plain case-1 fallthrough 121
- permuter with hack-free weights (-j 2, 900 s) from the 11-line shared-label body: base 1231, best 650, nohit. The best output is not equivalent: it puts `case 1:` on a bare `break`, so mode 1 never colours.

Census (asm leaders from the mode load to the colour block; the target has 11, colour `jal` at 0x160, function 0x388 bytes):
- shared label with && and ||: +2 blocks, same size. The mode retests (`bne a0,v1` at 0x120; `li at,2` + `bne v1,at` at 0x134-0x138) replace case 1's `bnez`/`nop`/`b`. The mode stays live in v1 (`move v0,v1` at 0xe8, `li a0,1` at 0xdc instead of `li at,1`).
- sentinel mask = 0: +0 blocks, -3 instructions. The value-known `beqz v1` at 0x12c is kept on the case-0 path (Q1156), and the two `andi` tests become one `and t2,v0,v1`.
- doColor flag: +1 block, +4 instructions (`beqz v1` at 0x150, then gFrameCounter is reloaded into a0).
- plain fallthrough: +0 blocks, -3 instructions. Case 1 runs the `& 3` test. Its load goes to t2 (0x124), and PRE reloads v0 at 0x130/0x134.
- `mode == 1 ||` guard: +1 block. The value-known `beq a0,v1` at 0x134 is kept, case 1's load goes to t2, and the t-register numbering shifts down the whole function.
- single-label inner switch: no second cfe temp, and it compiles like an if (`bne a0,v1` at 0x120). This confirms the A2F10 finding here. But a single register-mask test (`and t2,v1,v0` at 0x134) cannot produce the target's two immediate tests.

## Untried ideas
none natural that avoid the jump (the only zero is the `if (0) { case 2: }` block). Every structured form either re-tests gCutsceneLightFlickerMode under the shared label, repeats the gFrameCounter test, or funnels both arms through one test or flag block. The 2026-11-17 census shows each one adds a test block or moves case 1's gFrameCounter load out of v0, while the target reuses v0 in the shared tail.

## Evidence
- 0xdc-0xfc: compare-chain dispatch. `beqzl v0` goes to case 0 (0x104, `li v0,255` in the delay slot), `beq v0,1` to 0x120, `beq v0,2` to 0x13c, and `b 0x238` to the end.
- 0x120-0x138 (case 1): `lw v0,gFrameCounter`; `andi t2,v0,0xf`; `bnez t2,0x238`; `b 0x150` with delay slot `sll a0,v0,0x2`.
- 0x13c-0x14c (case 2): `lw v0,gFrameCounter`; `andi t3,v0,0x3`; `bnez t3,0x238` with delay slot `sll a0,v0,0x2`; then falls through.
- v0 (gFrameCounter) stays live from both arms into 0x150 (`sll a0,v0,0x2` in each arm's delay slot), so both arms feed one block.
- 0x150-0x234: the shared colour block. It calls mathCosF (jal at 0x160), converts with float->u32 (0x180-0x204: `cfc1`/`ctc1`, 0x4f000000 subtract path), does `andi t8,t7,0xff`, and stores the gLightFlickerColors[idx][0..2] bytes through 72/76/80(sp).
- (f32)(u32) of the u8 fov fields: `bgez` + 0x4f800000 add at 0x350 and 0x370.
- uopt -l5 at the base: the switch is one cfe temp (`M -24vreg`) tested by `uequ` 0/1/2 (candidates 8/10/12). Flow graph: BB6 is the case 1 test, BB7 the `goto`, BB8 the `break`, BB9/10 the case 2 test and then-entry, and BB11-12 the shared colour block (preds BB7 and BB10).
