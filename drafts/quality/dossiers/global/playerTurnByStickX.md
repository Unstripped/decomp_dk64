# playerTurnByStickX (global, src/global/E4090.c)

## Sites
Final (HackplayerTurnByStickX5, fdiff 0): one site, one construct.

| key | site | class (Q0908) | what it steers |
|---|---|---|---|
| dead-store:98dc2b | dead copy of the sibling's scaled turn: the scale chain `scale = pad->stickMagNorm; scale = scale * scale; if (scale < 0.2) scale = 0.2f;` after `pad =` plus `turn = turn * (gActivePlayerState->turnRate / 400.0) * scale;` after the 400 clamp, overwritten by the stick term | block split + pad use; Q0200 keeper | the chain's deleted stickMagNorm read and 0.2 compare make ugen emit `la $7,gCurrentActor` after `addu $5` (lui t8 0x19d0 before lui a3 0x19d8; pad a1, state a2); the store's read of turn keeps the 400 compare (0x1a7c) and the 2048/4096 chain |

Removed 2026-11-17 (HackplayerTurnByStickX5): other:3f6a5c, the -400 clamp `if (turn < -400.0f) turn = -400.0f;` (tagged by the lead after X4), replaced by the scaled-turn store inside the 98dc2b construct.

Base sites (all removed by HackplayerTurnByStickX4): aa1df8, #2, #3, #4 (entry `if (1) {}`), dead-store:c5577b (turnRate dead store), aa1df8#5, 72ccc1 (`!gCurrentActor` x3), 149c00 (`if (delta) {}`). Older removed: 3617c0, cbe8d1.
Base register names: yaw {573} v1 (0x1a08), delta a0 (0x1a1c), pad a1 (0x1a24), state load {165} a2, gCurrentActor load {645} v0, yaw reload {103} v1 (0x1ad4), &gCurrentActor {916} a3, &gActivePlayerState {676} t0.

## Attempts
- **2026-11-14, HackE4090InputA, high:** clamp spellings without cbe8d1 full=11; all 15 removal subsets of {3617c0, 72ccc1, 149c00, cbe8d1} (149c00 6, 3617c0 9, 3617c0+cbe8d1 11, 72ccc1 16, cbe8d1 32, all four 30).
- **2026-11-15, HackplayerTurnByStickX2, opus-5-5:high:** E4090 .data carve (Q0552/Q0929): no effect, no switch `jr`.
- **2026-11-16, HackplayerTurnByStickX3, anthropic/claude-opus-5-5:high:**
  - Q0908 classification (fdiff full via variants.py try):
    - 3617c0: `1`/`delta` 9; `yaw && yaw`, `turn && turn`, `delta || delta`, `delta && yaw`, `gCurrentActor && gCurrentActor`, `delta && delta && delta` 0; `pad && pad` 9; moved after the 400 block 0, after the stickX term 9.
    - cbe8d1: `turn` 0; `1`/`delta`/`yaw` 25; `pad` 32; `turn > 0.0f` 37.
    - 72ccc1: `1`, one or two `!gCurrentActor` 16; four 2; `||` triple 0; `!delta` x3 14; `!yaw` x3 25; `!gActivePlayerState` x3 31; moved after the >= block 0, before the test 18; swapped with 149c00 0.
    - 149c00: `1`/`gCurrentActor` 19; `pad` 25; `yaw` 29; `delta && delta` 0; after the >= block 0; at the aa1df8#5 slot 6.
    - aa1df8#5: `delta`/`yaw`/`gCurrentActor` 0; `pad` 9. Position: before the store 13, before the stickX term 71, inside the >= block 72, after it 72.
    - Entry four: as `if (pad)` x4 9, `if (gCurrentActor)` x4 9; one `&&` chain of four gCurrentActor 38, of gActivePlayerState 27. Position: 1-3 moved before `pad =` 9 (all four 18); moved after the yaw load or after `delta =` 13 (all four 34).
  - Merges: `delta && delta && turn > 1.0f` (or `&& turn`) after the 400 block 2 (as1: `bc1f 1a84; nop` instead of `bc1fl 1a88; lb t2` at 0x1a7c); `turn > 1.0f && delta && delta` 27; 72ccc1+149c00 in one test 2-3 (a real `bnezl v0` survives at 0x1ae4).
  - **FIXED (fdiff 0):** 3617c0 + cbe8d1 -> one dead store `turn = turn * (gActivePlayerState->turnRate / 400.0);` (the line playerInputUpdateMoveTargetWithDeadzone2 executes). `turn *=` and `/ 400.0f` also 0. A separate `f32 dist` local carrying the chain: 11 (chain deleted).
  - After the merge, plain re-runs: drop 1/2/3/4 entry ifs 12/16/16/24; aa1df8#5 72; 72ccc1 16; 149c00 6; 72ccc1+149c00 19.
  - Sibling scale chain (`scale = stickMagNorm; scale = scale * scale; if (scale < 0.2) scale = 0.2f;`) in place of the entry four, with the dead store: 16 (shape 0, delta {477} colours first: delta v1, pad a0, state a1, yaw a2); with 149c00 removed also 16; with every dead if removed 29; before `pad =` 71-78; plus `turn = turn * scale;` 79-87.
  - Reconstruct: all nine removed 42; dead store only 31; sibling scale + dead store 29 (scan: nothing lower); ternary/else 400 clamp 9; `pad =` before the maxSpeed test 104-106; `Actor *actor` temp for the yaw read 78-89; ternary abs 0 (respelling only).
- **2026-11-16, HackplayerTurnByStickX4, anthropic/claude-opus-5-5:high:**
  - Deleted the s16 `yaw` local from every use (Q0911; aa33e86e lever): `delta = gCurrentActor->yaw - targetYaw;`, `gCurrentActor->yaw -= turn;`. With all 8 base sites still in: 0. 40 removal subsets of the 7 dead ifs (entry count 0-4 x aa1df8#5 x 72ccc1 x 149c00, with the dead store): 1, 3 or 4 entry ifs alone 0; 2 alone 10; 0 entry ifs 16-30. Applied: one `if (1) {}` + dead store, fdiff 0.
  - Plain no-yaw body (no steer): 18 with the dead store, 29 without. One entry if, no dead store: 11.
  - Single-if position (no-yaw, dead store): after the delta line / abs / 2048 / 400 clamp 9; after the dead store 20.
  - Keeper alternatives: sibling `if (turn < -400.0f) turn = -400.0f;` after the 400 clamp replaces the dead store; with no entry steer 9 (only the entry lui order: ugen puts `la $7,gCurrentActor` at the head of the bc1t fall-through block); with `if (1) {}` 10 (pad adjsave 1.0 ties state, a1/a2 swap). Clamp as `else if` 20; -400 before 400 12; extra -2048 wrap 68; dead store after the -400 clamp 17, between the clamps 80.
  - Guards at every statement gap of the -400 form (`1`, pad, delta, gCurrentActor, gActivePlayerState, turn, `pad && pad`, `delta && delta`): only right after `pad =`: `if (pad) {}` 0, `if (pad && pad) {}` 0, `if (pad->stickMagNorm) {}` 0; `if (1)`/`if (gActivePlayerState)` 10; elsewhere 9-45.
  - Sibling scale chain after `pad =` (no-yaw form): with the -400 clamp 0 (FINAL); with `turn = turn * scale;` after the 400 clamp and no -400 clamp 0; with the turnRate dead store and no -400 clamp 0; alone 11; with -400 + `turn * scale` 8; with -400 + both sibling lines 91; `scale = stickMagNorm * 0.5 + 0.5` form 9-100.
  - Other no-yaw respellings (no entry steer): refine delta in place 37 / 85; ternary abs 18; `<= 0` first 23; s16 targetYaw local 70; `pad =` after the delta line 22, before the stick term 117; stickX local 85; operand-swapped multiply 12; pad array inlined 100; second pad local or inlined pad in the tail: no help. `variants.py scan` on the no-steer bodies: nothing under 9.
- **2026-11-17, HackplayerTurnByStickX5, anthropic/claude-opus-5-5:high:** (variants.py try, full lines)
  - Merged the two tags into one construct (FINAL): scale chain + one dead store after the 400 clamp, `turn = turn * (gActivePlayerState->turnRate / 400.0) * scale;` 0; `turn * scale * (turnRate / 400.0)` 0; `turn * scale` alone 0; the sibling's two separate lines 83. Chain as `scale = pad->stickMagNorm * pad->stickMagNorm;` 0.
  - Q1148 inline operand: no scale local or 0.2 clamp, `turn * (turnRate / 400.0) * (pad->stickMagNorm * pad->stickMagNorm)` 18 (the block split after `pad =` needs the deleted 0.2 compare).
  - Plain removals of the merged construct: all of it 29; chain only (store as `turn * (turnRate / 400.0)`) 18; store only 11.
  - Sweep on the merged copy: no hits. fdiff 0, uninit 0, cfe warnings 0, file FAKE count 13 -> 12.

## Untried ideas
- A version with no dead code at all: the target still needs a block boundary between `pad =` and the delta line (la placement) plus a pad use there, and a reader of turn after the 400 clamp; no live code is known for either.
- Whether the whole dead sibling scaled-turn computation (copy residue the target's surviving 2048/400 compares prove existed) can be ORIG instead of FAKE: the target executes the abs/2048/400 part but not the stickMagNorm read, 0.2 compare or the store, so it stays FAKE under the current rule; a lead decision.

## Evidence
- The clamped turn is dead in the target: both arms of the 400 compare rejoin at 0x1a88 (`bc1fl 1a88` with `lb t2,46(a1)` copied into the delay slot at 0x1a80).
- The stick term (`lb t2,46(a1)`, `multu`, `div` by 400 at 0x1aa8) never reads turn.
- 0x19f8-0x1a24 (pad address, actor load, yaw load, delta) is one straight-line block: no real control flow can supply the entry blocks.
- The >= 0x1000 block reloads gCurrentActor through `lui v0/lw v0` (0x1ae8/0x1aec), not through a3.
- Sibling playerInputUpdateMoveTargetWithDeadzone2 (same file) runs `turn = turn * (gActivePlayerState->turnRate / 400.0);` after the same 400 clamp.
- Entry order: target `lui t8,%hi(gPlayerPadState)` 0x19d0 before `lui a3,%hi(gCurrentActor)` 0x19d8: the `la $7,gCurrentActor` must follow `addu $5` in the ugen stream (a block boundary after `pad =`), not open the bc1t fall-through block.
