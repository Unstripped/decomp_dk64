# csCmdExec (global, src/global/42630.c)

## Sites
- global:8063FA48:other:4f1968 (line 1064) `void *dm = &csId;` — two effects: (1) dm's own frame word (sel at sp+0xB3, all slots below); (2) csId becomes aliased, so the case 0x2D actor loop reloads `lh t5,210(sp)` each iteration (0x3694) instead of a hoisted a1 piece. An unused `s32 pad0` reproduces (1) only.
- global:8063FA48:dead-if:e8c5ea (line 1100) `if (found) {}` — puts found's live range into block 0 where the incoming-csId candidate {282|1} (a2) lives, so a2 is forbidden and found takes a3 (move a3,zero at 0x2140; 0x3848/0x385c/0x388c/0x38a0).
- global:8063FA48:dead-if:1c9d00 (line 1238) `b = (s32)D_807F61F0.hostActor; if (b) {}` — b's dead range in case 0x68 splits the &D_807F61F0 const web: v0 piece for 0x2670-0x2688, folded `lui a0; lw a0,%lo(D_807F61F0+4)(a0)` at 0x268c/0x2694, a3 rematerialised for the store. (b is now u8; the line still matches.)
- global:8063FA48:other:83069d / 83069d#2 (cases 0xF/0x7E) `i = cmd->b & 0x7F;` spread reuse of the loop index — EXHAUSTED (a dedicated spread local, u8/s16/s32 at pad's position or after vol7: 246-792 diff lines on the new base).
- FIXED 2026-11-17 (HackcsCmdExec3): 7acbc2 x3 (`c &= 0xFF;`), 543cb7 x2 (`if (b && b && b) {}`) and the ORIG `sfxSlotAllocateSource(s16, s16, s32, s32, ...)` local prototype + PROTO_SKIP.

## Attempts
- 2026-11-09..14 (history, rounds 2-6 + OwnerCsCmdExecProtos): per-site remove/cond/classify/plain/recipe sweeps, permuter per site and from v_pcmd (best 34..500, all hack shapes), reconstruct (1845 vs 1848 insns) — all nohit. Proto steers resolved as ORIG; views/casts retired.
- 2026-11-15 HackcsCmdExec2 anthropic/claude-opus-5-5:high: see history (s32 b/c widths, mask/cast spellings, reconstruct n1-n4 257-305 with the s32 local prototype; all nohit).
- 2026-11-17 HackcsCmdExec3 anthropic/claude-opus-5-5:
  - sweep: 84 checks, 0 hits (base); 21 checks, 0 hits (after the fix).
  - FIX (fdiff 0): `u8 b;` declared before `s32 map;`, `u8 c;` after it; `c = cmd->c & 0x7F;` in 0xE/0x7D/0xF; `b = cmd->b & 2;` inside the `if (cs->unk10[i] < 0)` of 0xE/0x7D; `range = cmd->c & 0x7F;` in 0x7E; shared `u8 sfxSlotAllocateSource(s16, s16, u8, u8, u8, f32, s8)` from include/proto/global/7130.h (PROTO_SKIP define and the s32 local declaration deleted). The in-place copy `move a2,v0; andi t5,a2,0x7f; move a2,t5` is the u8 local's implicit narrowing stacked on the explicit mask (the same shape `pitch = (cmd->b / 128) & 0xFF` gives for u8 pitch).
  - Needed together: u8 c under the s32 local prototype puts c in t4 (`move a2,t4` before the jal); s32 b under the shared u8 prototype gives `move v1,t1; andi a3,v1,0x2`; adjacent `u8 b; u8 c;` pack into one word and shift every slot below by +4 (t1 spill 56->60, flag 110->114); `b = cmd->b & 2` before the if puts the andi ahead of the index sll (t7/t8/t9 rotate); keeping `c = cmd->c; range = c & 0x7F;` in 0x7E with u8 c stores c to 122(sp).
  - `pitch`/`vol`/`pitch7`/`vol7` without their `& 0xFF`: pitch/vol 23-26 diff lines in 0xE, pitch7/vol7 move every later branch target by 4 — the masks stay (ordinary explicit byte masks).
  - re-scores on the new base: no dm 1540 lines, s32 pad0 1357; no found guard 17 lines (found a2 vs a3 only); 0x68 without the b line 40 lines (one a3 web), `actor = hostActor` before the first despawn 22, between 27, `active = 0` first 37.

## Untried ideas
- e8c5ea: a natural real use of found or another value occupying a2 across block 0 (no candidate found).
- 4f1968: a codeless natural escape of csId (none in the target asm).
- 1c9d00: a natural second read of hostActor in case 0x68 that splits the &D_807F61F0 web after the first jal without a branch.

## Evidence
- Target prologue: `sw a2,208(sp)` (csId home), every csId use `lh aN,210(sp)`; no `addiu aN,sp,208` anywhere.
- 0x2D loop 0x3678-0x36ec: `lh t5,210(sp)` per iteration; also `lh t6,2(s1)` (cmd->a) reloaded (stores through actor alias).
- Case 0xE 0x2fb0-0x307c, 0x7D 0x3080-0x3154, 0xF 0x3158-0x31d8, 0x7E 0x31dc-.
- Case 0x1C 0x3824-0x38ac: found spilled `sb a3,195(sp)` across hashTableLookup; `bnezl a3` and `b` both reach 0x3de4.
