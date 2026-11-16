# effectDecelerateDriftUpdate (global, src/global/11BC10.c)
## Sites
global:80719A0C:other:5c1124 other: `newState = state;` (first half of a round-trip copy) gave a second pointer web: v0 = copy of v1 (`move v0,v1` at 0x2bb8), spilled to 0x1c(sp) across mathSinF/mathCosF. REMOVED (2026-11-15).
global:80719A0C:other:3658da other: `state = newState;` (second half), blocked copy propagation so the post-clamp uses stayed on the copy's web. REMOVED together with 5c1124 (2026-11-15).
## Attempts
2026-11-14 Rereview11BC10a Rereview11BC10a anthropic/claude-opus-5-5:high: tagged the pre-existing round trip; dropping both copy lines (head `state = effect->allocation; if (state == NULL)`) -> full=9; stepping/clamping through effect->allocation -> full=10-15.
2026-11-15 U HackeffectDecelerateDriftUpdate anthropic/claude-opus-5-5:high: Q0375 head `if (effect->allocation == NULL) { state = heapAlloc(8); effect->allocation = state; ... } state = effect->allocation;` with one pointer -> fdiff 0 (same with a separate `newState` for the allocation declared after `state`; `newState` declared before `state` -> full=3). Casts dropped afterwards (-= 0.2, plain compare, scaleX / 0.36 * 2.5, no (f32)(u32) on the u32 sum, no (s16)(s32) on mathSinF/mathCosF(s16)) -> fdiff 0. Folding `stepX = state->speed * mathSinF(...)` into one statement -> full=2 (not kept).
## Untried ideas
none open: function is hack-free.
## Evidence
0x2b0c lw v1,900(a0) + bnezl v1: null test on the field load. 0x2b9c lw v1,900(a1): reload after the init block (PRE inserts it on the init path only). 0x2bb8 move v0,v1: v1 is the field-load temp, used for the 0.2 decrement and the 0.8 clamp (stores at 0x2bc0/0x2be8); v0 is `state`, used for heading/speed after the clamp, saved at 0x2bf4 sw v0,28(sp) and reloaded at 0x2c10/0x2c3c. Frame 0x28: stepX at 0x24(sp).
