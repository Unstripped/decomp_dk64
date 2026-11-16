# playerStateTakeDamagePrep (global, src/global/EFDC0.c)
## Sites
- global:806EB744:dead-if:398172 `if (gPlayerSlots && gPlayerSlots) {}` (FIXED 2026-11-16): a block split between `camState =` and the type load. Without it the `camActor` local (cand 0, M-4, v0) shares a block with type (cand 9), so:
  - type v1 (target v0)
  - speed a1 (target v1)
  - 8 r at 0x6a8-0x6d8
## Attempts
- CleanEFDC0 (opus:low): remove/cond/classify/diagnose; permute 0 only via a do-while(0).
- 2026-11-14 U, scored with variants.py try (full=):
  - extra blocks: speed `?:` 91, if/else 21, one-case switch on type/kind 8
  - declaration orders: 8-11
  - widths: 8
  - camActor reuse: worse
  - slot pointer early 101, late 69
  - scan of the plain removal: 8
- 2026-11-16 HackplayerStateTakeDamagePrep2 (opus:high), classification with `if (X) {}` in place of the guard:
  - `1`, `1 && 1`, `gPlayerSlots`, `camState`, `camActor`, `gCurrentPlayerIndex && ...`: 0 (block split)
  - `;` 8, `gActivePlayerState && gActivePlayerState` 57
  - `if (1) {}` at other positions: 5-10; only between `camState =` and `type =` gives 0
  - no camActor local (`camState = gActivePlayerState->camActor->customState`): 2 (speed home sp+0x2e, target 0x2a)
  - same with 16 of 120 declaration orders: 0 (camState or param first, then speed); applied `CamState *camState; s16 speed; u8 type;`
  - param/kind chain: `camState->mode = queuedParam0; if (camState->mode == 3)` 0 (applied); u8/s16 kind, param-only forms 36-42
## Untried ideas
- none (no hack site left)
## Evidence
- target 0x698 `lw a0,0x104(t6)`, 0x6a0 `lw s0,0x174(a0)`, 0x6a8 `lbu v0,0xef(s0)`, 0x6b0 `mfc1 v1,$f6`, 0x6d8 `sh v1,0x2a(sp)` (speed home, frame 0x30, local offset -6)
- 0x718 `lw t6,0x2a8(t5)`, 0x724 `andi t7,t6,0xff`, 0x72c `sb t6,0xf3(s0)`: the stored mode byte is forwarded to the compare
- uopt -l 6: try/trace_one.txt (`if (1) {}`) vs try/trace_plain.txt: type 1 (v0) -> 2 (v1), speed 2 (v1) -> 4 (a1)
