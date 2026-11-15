# csCmdExec (global, src/global/42630.c)

## Sites
- global:8063FA48:other:4f1968 (line 1070) `void *dm = &csId;` — two effects: (1) dm's own frame word (sel at sp+0xB3, all slots below); (2) csId becomes aliased, so the case 0x2D actor loop reloads `lh t5,210(sp)` each iteration (0x3694) instead of a hoisted a1 piece. An unused `s32 pad0` reproduces (1) only (full=100).
- global:8063FA48:dead-if:e8c5ea (line 1108) `if (found) {}` — puts found's live range into block 0 where the incoming-csId candidate {282|1} (a2) lives, so a2 is forbidden and found takes a3 (move a3,zero at 0x2140; 0x3848/0x385c/0x388c/0x38a0).
- global:8063FA48:dead-if:1c9d00 (line 1246) `b = (s32)D_807F61F0.hostActor; if (b) {}` — b's dead a3 range in case 0x68 splits the &D_807F61F0 const web: v0 piece for 0x2670-0x2688, folded `lui a0; lw a0,%lo(D_807F61F0+4)(a0)` at 0x268c/0x2694, a3 rematerialised for the store.
- global:8063FA48:other:7acbc2 x3 (cases 0xE/0x7D/0xF) `c &= 0xFF;` — redundant mask keeps `move a2,v0; andi t5,a2,0x7f; move a2,t5` (Q0186).
- global:8063FA48:dead-if:543cb7 x2 (cases 0xE/0x7D) `if (b && b && b) {}` — keeps b's copy `move a3,v1; andi t9,a3,0x2; move a3,t9` (0x301c-0x3028, 0x30ec-0x30f8).

## Attempts
- 2026-11-09..14 (history, rounds 2-6 + OwnerCsCmdExecProtos): per-site remove/cond/classify/plain/recipe sweeps, permuter per site and from v_pcmd (best 34..500, all hack shapes), reconstruct (1845 vs 1848 insns) — all nohit. Proto steers resolved as ORIG; views/casts retired.
- 2026-11-15 HackcsCmdExec2 anthropic/claude-opus-5-5:high:
  - sweep: 84 checks, 0 hits.
  - 4f1968: `s32 pad0` at dm's position -> full=100 (csId a1 piece hoisted before the 0x2D loop, 0x3674); `u8 pad0` / none -> 157.
  - e8c5ea: `u8 found = 0;` 5; found = 0 at top of case 0x1C 6; `!found` 5; s32/s16 found 5; inverted return 5; variants scan of removed copy best 5. uopt -l5: forbidden set loses a2 (5) without the guard.
  - 1c9d00: named `actor` local / actor dead-test / actor = NULL / plain: 10; `actorDespawn((Actor *)b)`: 2.
  - 7acbc2: single masks 270; c widths 253-567; u8 pitch/pan7 538/559; masks in the call 536-606; redundant casts `(u8)cmd->c & 0x7F`, `(u8)(cmd->c & 0x7F)`, `(u16)cmd->c & 0x7F`, `c = (u8)cmd->c; c &= 0x7F` -> 0 at all three sites (hidden steer, same count, not adopted).
  - 543cb7: guard removed 4; b = cmd->b at 7 positions 4-10; i = b & 1 297; b &= 2 before if 265; mask/cast spellings 1-259 (b = cmd->b & 0xFF: 1, b = (u8)cmd->b: 2); widths 476-581/u32 4.
  - reconstruct case 0xE natural bodies: n1 305, n2 299, n3 257, n4 30. All steers but dm removed with c cast: 23.

## Untried ideas
- e8c5ea: a natural real use of found or another value occupying a2 across block 0 (no candidate found).
- 543cb7: a natural second real use of b between `b = cmd->b` and `b &= 2` that emits no code (none found).
- 4f1968: a codeless natural escape of csId (none in the target asm).

## Evidence
- Target prologue: `sw a2,208(sp)` (csId home), every csId use `lh aN,210(sp)`; no `addiu aN,sp,208` anywhere.
- 0x2D loop 0x3678-0x36ec: `lh t5,210(sp)` per iteration; also `lh t6,2(s1)` (cmd->a) reloaded (stores through actor alias).
- Case 0xE 0x2fb0-0x307c, 0x7D 0x3080-0x3154, 0xF 0x3158-0x31d8.
