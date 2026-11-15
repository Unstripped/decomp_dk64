# actorLightPulseUpdate (global, src/global/A2F10.c)
## Sites
- global:8069E774:other:0e8922 `u8 isAttached[4]` (element 3 = 0x7F(sp)) kept the flag in its home: a scalar u8 tested `!= 0` in the player loop was coloured before the loop (`lbu v0,0x87(sp)` at 0xad0, `sw v0,0x50(sp)`, `lw t4,0x50(sp)` per iteration) and the frame grew 0x90 -> 0x98. FIXED.
- global:8069E774:dead-if:c42ccd `if (gPlayerCount && gPlayerCount) {}` inside the loop made uopt load the pre-loop count into v0 (lui/lbu v0 at 0xb18/0xb20) instead of t3. FIXED.
## Attempts
- 2026-11-14 HackactorLightPulseUpdate anthropic/claude-opus-5-5:high: loop guard as `if (isAttached && (i == hostState->playerIndex || target->state == 0x84)) continue;` then the in-range call -> c42ccd gone, fdiff 0 (array kept).
- same: scalar u8 isAttached with the continue loop, `!= 0` tests -> full=106 (frame 0x98). variants width scan: s8 / char -> full=4 (only lb vs lbu), so the compare is the steer.
- same: scalar u8 with bare tests everywhere -> fdiff 0. Only the in-loop test needs to be bare (single flip at the loop guard: full=0; flips at 0x249/0x287 alone: 106/93). Nested-if loop with bare tests (no continue): full=47, so both changes are needed.
- same: dropped (u16) on collision->radius and the outer (f32) on the four 6.66666667 arguments: fdiff 0.
## Untried ideas
- none left; function has no tagged sites.
## Evidence
- target: isAttached home 0x7F(sp) read with lbu at 0x798, 0x7f8, 0xad0 and per iteration at 0xb54; despawned 0x87(sp); lightRadius 0x8E(sp); loop count reloaded lui/lbu v0 at 0xbd4; frame 0x90.
- Q0384: explicit compare on a u8 creates a zero-extended (ucvt) candidate that gets its own spill instead of the home slot; same mechanism here inside a loop.
