# csCmdExec (global, src/global/42630.c)

## Sites
- global:8063FA48:other:4f1968 (line 1064) `void *dm = &csId;` — two effects: (1) dm's own frame word (sel at sp+0xB3, all slots below); (2) csId becomes aliased, so the case 0x2D actor loop reloads `lh t5,210(sp)` each iteration (0x3694) instead of a hoisted a1 piece. An unused `s32 pad0` reproduces (1) only.
- global:8063FA48:dead-if:e8c5ea (line 1100) `if (found) {}` — puts found's live range into block 0 where the incoming-csId candidate {282|1} (a2) lives, so a2 is forbidden and found takes a3 (move a3,zero at 0x2140; 0x3848/0x385c/0x388c/0x38a0).
- global:8063FA48:dead-if:1c9d00 (line 1238) `b = (s32)D_807F61F0.hostActor; if (b) {}` — b's dead range in case 0x68 splits the &D_807F61F0 const web: v0 piece for 0x2670-0x2688, folded `lui a0; lw a0,%lo(D_807F61F0+4)(a0)` at 0x268c/0x2694, a3 rematerialised for the store. (b is now u8; the line still matches.)
- ORIG 2026-11-17 (HackcsCmdExec4): 83069d#2 (case 0x7E) `i = cmd->b & 0x7F;` the spread is the original i: 0x7E spills it to i's home sp+0xBC (0x3268/0x327c), the same home the case 0x76 actor loop spills its index to (0x2450/0x2460).
- FAKE KEPT 2026-11-17 (HackcsCmdExec4, lead/director ruling): 83069d (case 0xF): 0xF computes the spread into t0 (0x31b0), i's register in every piece, but register sharing is not proof of one variable and 0xF has no spill of its own. Measured: dedicated spread best full=6, 37 declaration positions 6-114, type x order best text=3, inline 238, block-scoped 114, u8 238.
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
- 2026-11-17 HackcsCmdExec4 anthropic/claude-opus-5-5:
  - sweep: 21 checks, 0 hits (base a7789b50).
  - Swap: s32 spread at i's declaration, i in pad's slot: full=98 (the 0x76 loop spill moves to sp+0x64 while the target spills loop index and spread to sp+0xBC; i colours v1 in 0xE); u8/s16 there 367-369. One home for both values = one variable: both tags -> ORIG.
  - Case 0xF alone with a dedicated local (0x7E keeping i): s32 at pad's slot full=6 (spread v0, c t0 vs target t0/t1); 37 declaration positions 6-114; s32/int/u32/s16/u16 x 6 statement positions best text=3 (read first: t0, but the andi leaves the 0x31b0 delay slot); inlined into the call 238; block-scoped s32 114; u8 238.
- 2026-11-17 2026-11-17: cleanup HackcsCmdExec5 HackcsCmdExec5 anthropic/claude-opus-5-5 (re-score at 1f27b4f2 after the c7ee74ab comment-only retag of 83069d#2; no code change):
  - sweep: 21 checks, 0 hits. Scores with variants.py try (full) and objdump of csCmdExec with branch targets normalised.
  - 4f1968: no dm 593 (1851 vs 1847 insns; csId hoisted `lh t4,210(sp)` at 0x3674 before the 0x2D loop, temps renumber from 0x2184, frame -1 word); s32 pad0 548 (slots equal, same hoist); scan on the pad0 copy best 503. K&R definition of csCmdExec (PROTO_SKIP stand-in, `void csCmdExec();`): csCmdExec identical with dm, 593 without: an old-style s16 formal does not make csId memory-resident.
  - e8c5ea: no guard 5 (found a2 vs a3 at 0x2140/0x3848/0x385c/0x388c/0x38a0 only); scan all 5; no dm + no guard = no dm (593), pad0 + no guard = pad0 (548): not coupled to the dm steer.
  - 1c9d00: no line 10 (1848 insns: &D_807F61F0 a3 instead of v0 at 0x2670-0x2688, re-materialised lui/addiu a3 + `lw a0,4(a3)` instead of folded `lui a0; lw a0,%lo(D_807F61F0+4)(a0)` at 0x268c/0x2694). uopt -l6: with the line the 0x68 lda range splits (583 -> 620/623: a3 piece, v0 rest) and b takes a3. Hand classify: guards on cmd/cs/1/hostActor between the despawns, `b = 0`, a dead `b = hostActor;`, i or actor instead of b: all 10 (= removal); `b = cmd->b` 22; `b = active` 6; the line after the 2nd despawn 3 (store base v1 vs a3), before the 1st 6. Natural rewrites: `CsSpawnReq *req` pointer local 120; u8/s32 `active` local in pad's slot 473; `Actor *host` in pad's slot before the 1st despawn 9, between 10; `b = D_807F61F0.active` as the test 470.
  - reconstruct: all non-kept steers removed 603 (1852 insns), with pad0 558. All nohit.

## Untried ideas
- e8c5ea: a natural real use of found or another value occupying a2 across block 0 (no candidate found; not coupled to dm).
- 4f1968: a codeless natural escape of csId (none in the target asm; K&R definition ruled out).
- 1c9d00: a natural u8 value live in a3 between the two despawns of case 0x68 (only the u8 b web assigned from hostActor reproduces it; dedicated locals, pointer locals and guards do not).

## Evidence
- Target prologue: `sw a2,208(sp)` (csId home), every csId use `lh aN,210(sp)`; no `addiu aN,sp,208` anywhere.
- 0x2D loop 0x3678-0x36ec: `lh t5,210(sp)` per iteration; also `lh t6,2(s1)` (cmd->a) reloaded (stores through actor alias).
- Case 0xE 0x2fb0-0x307c, 0x7D 0x3080-0x3154, 0xF 0x3158-0x31d8, 0x7E 0x31dc-.
- sp+0xBC (i's home) accesses: only 0x2450/0x2460 (case 0x76 loop index spill/reload around actorAppendCallback) and 0x3268/0x327c (0x7E spread around modelSlotGetNodePos). i is t0 in every piece: 0x23f4/0x3664 loops, 0x3008/0x30d8 slot index, 0x31b0/0x3240 spread.
- Case 0x1C 0x3824-0x38ac: found spilled `sb a3,195(sp)` across hashTableLookup; `bnezl a3` and `b` both reach 0x3de4.
- Case 0x68 0x2670-0x26a4: `lui/addiu v0` &D_807F61F0, `lbu t7,8(v0)`, `jal actorDespawn` with `lw a0,0(v0)` in the slot; folded `lui a0` 0x268c / `lw a0,%lo(D_807F61F0+4)(a0)` 0x2694 in the 2nd jal slot; fresh `lui/addiu a3` 0x2698/0x269c for `sb zero,8(a3)` 0x26a4.
