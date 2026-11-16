# playerTurnByStickX (global, src/global/E4090.c)

## Sites
Register names: yaw {573} bit 10 (v1, `lh v1,230(v0)` 0x1a08), delta {477} bit 15 (a0, `subu a0` 0x1a1c), pad {413} bit 4 (a1, `addu a1,t7,t8` 0x1a24), state load {165} bit 0 (a2), gCurrentActor load {645} bit 12 (v0), yaw reload {103} bit 13 (v1, 0x1ad4), &gCurrentActor {916} (a3), &gActivePlayerState {676} (t0).

| key | site | class (Q0908) | what it steers |
|---|---|---|---|
| aa1df8, #2, #3, #4 | four entry `if (1) {}` | (i) block split | blocks in pad's web before yaw starts; pad adjsave 0.714 < yaw 0.75 (Q0722) |
| dead-store:c5577b (copy only) | `turn = turn * (gActivePlayerState->turnRate / 400.0);` | value use + blocks | replaces 3617c0 + cbe8d1: keeps the 2048/4096/400 chain (0x1a44-0x1a84) and pad in a1 |
| aa1df8#5 | `if (1) {}` after the yaw store | (i) block split | {645} 2.0->1.71, delta 1.4->1.17; &gActivePlayerState in t0 (0x19c0) |
| 72ccc1 | `if (!gCurrentActor && !gCurrentActor && !gCurrentActor) {}` | (ii) same value, 3 reads | {645} 1.5->1.71, {103} 2.0->1.5; yaw v1 / actor v0 |
| 149c00 | `if (delta) {}` | (ii) same value | extends delta into the >= block (2.0->1.17); delta a0 |
| 3617c0 (removed) | `if (delta && delta) {}` in the 400 arm | (i) block split, needs 2 blocks | pad 0.833->0.714 |
| cbe8d1 (removed) | `if (turn > 1.0f) {}` | (ii) value use of the clamped turn | Q0200 keeper of the 400 compare |

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

## Untried ideas
- An entry block structure that gives pad (bit 4) the four blocks without lifting delta's priority: the sibling scale chain is the closest real-looking code (16); a variant that also uses `scale` later (playerInputUpdateMoveTargetWithDeadzone2 uses `turn * scale`, 79-87 here) in another position is untested.
- 72ccc1 needs three conditional reads of gCurrentActor in or after the >= 0x1000 block; real code that reads gCurrentActor there without emitting a branch is not known.

## Evidence
- The clamped turn is dead in the target: both arms of the 400 compare rejoin at 0x1a88 (`bc1fl 1a88` with `lb t2,46(a1)` copied into the delay slot at 0x1a80).
- The stick term (`lb t2,46(a1)`, `multu`, `div` by 400 at 0x1aa8) never reads turn.
- 0x19f8-0x1a24 (pad address, actor load, yaw load, delta) is one straight-line block: no real control flow can supply the entry blocks.
- The >= 0x1000 block reloads gCurrentActor through `lui v0/lw v0` (0x1ae8/0x1aec), not through a3.
- Sibling playerInputUpdateMoveTargetWithDeadzone2 (same file) runs `turn = turn * (gActivePlayerState->turnRate / 400.0);` after the same 400 clamp.
