# minecartFollowTrack (minecart, src/minecart/0.c)
## Sites
minecart:800253C0:other:dfe0c8 other: `i = (*cart->routeCursor + cart->junctionOffset) & 0x3F;` reuses the u8 sfx slot counter `i` (first busy-slot loop) as the junction track index; the reuse keeps `junctionPt` in v1 at 0x1dd8-0x1e08 (pre-existing, tagged 2026-11-17 by Polishminecart0).
## Attempts
2026-11-17 2026-11-17: cleanup Polishminecart0 Polishminecart0 anthropic/claude-opus-5-5: dedicated `u8 junctionTrack` in the unused pad slot (frame kept) -> 25 (junctionPt v0, t8/t1 swap); the same added beside the pad at 16 declaration positions -> 48..874 (spill offsets shift by 4); dedicated s32/u32 -> 445, s16/s8 -> 905, u16 -> 25; index inline in `gMinecartTrackPoints[...]` -> 120; `gMinecartTrackPoints[...] + pointIndex` -> 120; `MinecartTrackPoint *track` row local -> 350; reuse of `trackIndex` instead -> 25; both slot loops sharing i/busySlots (i2/cnt2 left as pads) with any dedicated junction local -> 25.
## Untried ideas
uopt_trace of the i web vs a dedicated junction web (Q1055: a reused local is one coloring candidate across all its uses); permuter on the junction block with the dedicated local in the pad slot.
## Evidence
0x1da0-0x1dbc: lw t3,0x34(s1); lbu t7,0x40(s1); lbu t6,0(t3); addu t5,t6,t7; andi t9,t5,0x3f (no andi 0xff: the u8 narrowing of i folds). 0x1dd8 addu v1,t4,t6 forms &gMinecartTrackPoints[track][pointIndex]; 0x1ddc/0x1e00/0x1e04/0x1e08 use v1 for junctionPt +1, -1 and the two stack arguments. Frame 0x130: every declared local takes a word; the former unused `MinecartTrackPoint *p` was a pad (now the absTilt local).
