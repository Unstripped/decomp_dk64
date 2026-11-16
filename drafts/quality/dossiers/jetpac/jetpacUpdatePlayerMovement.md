# jetpacUpdatePlayerMovement (jetpac, src/jetpac/1A60.c)

## Sites
- **jetpac:80026318:volatile:1d4065** (line 269) and **jetpac:80026318:volatile:1d4065#2** (line 272).
  - Each is a volatile reload of player->flying after the vy store in the flying arm. Target loads: `lw v0,48(s0)` at 0x9c4 and 0x9e0.
  - Without them, the vx>0/vx<0 reloads at 0xac8/0xaf8 also disappear.
- **jetpac:80026318:other:b4a3d4** (line 281, plus 288/293/296): `flying = player->flying` re-reads at the end of the btnLeft/btnRight/vx arms. These produce 0xa30/0xa40, 0xa8c/0xa9c and 0xac8/0xaf8.

## Attempts
**2026-11-14 U HackjetpacUpdatePlayerMovement (strong retry).**

Untried natural sources from the brief:
- **(a) global vy store:** rejected by addressing. Every vy store is `swc1 12(s0)` through the parameter (0x9a8/0x9cc/0x9ec); there is no `lui %hi(jetpacPlayer)`.
- **(b) a call between the store and the read:** rejected. There is no `jal` in 0x9b8-0x9ec.
- **(c) structural grid of 312 bodies.** Best is 2 instructions, in two families:
  - **Family X:** the test assigns `flying` and the flying arm has no reads. 0xac8/0xaf8 are right, but 0x9c4/0x9e0 are missing.
  - **Family Y:** a join read `flying = player->flying` after the chain. PRE inserts 0x9c4/0x9e0, but that makes 0xac8/0xaf8 redundant.

Probes:
- These address spellings are all CSEd with the test load (full=4): the JetpacActor view `explosion.x`, `*(s32 *)((u8 *)player + 0x30)`, `(&player->timer)[1]`, `player[0].flying`, `(*player).flying`, `*&player->flying`.
- Replacing the flying-arm vy stores with vx stores keeps the vx-arm reloads; removing the stores makes them redundant. So the f32 stores through player do break global availability of player->flying. A plain reload after them is still value-numbered equal to the test load.

Result:
- With `volatile s32 flying` in JetpacPlayerActor (include/jetpac.h), the plain reads match as a whole object, and all jetpac.h users still match.
- **Blocked** on the shared-type ruling (the director rejected the header change).

**2026-11-15 U HackjetpacUpdatePlayerMovement2 HackjetpacUpdatePlayerMovement2 anthropic/claude-opus-5-5:high.**

New: the two-join-read family (Family Y extended with a final `player->flying` read), a 120-body grid over it, and load-dtype probes.
- **Natural body** (no `flying` local, no arm reads, final `if (player->flying != 0)`): full=87. The final load stays at the 0xb08 join because flying is not available on the vx==0 path.
- **Two-join-read body.** The first chain has no arm reads, `flying = player->flying;` sits between the chains, and the final test is `if (player->flying != 0)`.
  - PRE of the 0x9f0 join read inserts 0x99c/0x9c4/0x9e0.
  - PRE of the final read inserts 0xa30/0xa40/0xa8c/0xa9c/0xac8/0xaf8, and v0 carries through the vx==0 path. All of 0x968-0xb10 matches.
  - The join-read local still needs a consumer:
    - Used as the jetpacSetFlying argument: `move a1,v0` at the btnLeft test replaces `lw a1,48(s0)` at 0xa3c/0xa98 (full=5).
    - Used as the line-317 `if (flying != 0)`: v0 spills to 40(sp), and 0xbfc/0xc10/0xc18 become `lw t1,40(sp)` instead of `lw t1,48(s0)` (full=4).
    - With no consumer, the join read is dead (full=87).
- **Grid over 120 bodies:**
  - first chain: none / test-assign / all-arm reads
  - join read: yes / no
  - call argument: expression / local
  - arm re-reads: none / all / left-right only / vx-else join / left-right + vx-else join
  - final test: local / expression

  Best is 2 (Family X, already known). Other notable scores: join read + left-right re-reads + final local = 2; join read + local argument + final expression = 5.
- **Second-chain re-reads (b4a3d4):** dropping them with a final `if (player->flying)` scores 72 under both the volatile and the u32 first chain; with a final `if (flying)` it scores 12.
- **Split test chain** (`else if (flying && btnZLR) ... else if (flying)`): 16 with arm reads. Adding the join read lowers it to 14, but the flying arm then has its own reload and the vx-arm reads are VN-deleted.
- **Load-dtype probes in place of each volatile:**
  - `*(u32 *)&player->flying`: **full=0**. The value-numbering candidate key includes the load dtype, which corrects Q0820. This is a punned cast, so using it would swap one hack for another; not applied.
  - `(u32)player->flying` (a value cast): 11.
  - `player->flying != 0`: 11.
- `variants.py scan` of the plain-read copy (baseline 4) and the two-join copy (baseline 5): no zero.

**2026-11-15 U HackjetpacUpdatePlayerMovement3 HackjetpacUpdatePlayerMovement3 anthropic/claude-opus-5-5:high.**

Re-diagnosed under the Q0820/Q0887 framing. Sweep: 27 checks, 0 hits. New probes (variants.py try, full=):
- **Local type:** `u32 flying` local with plain reads: 4; with the volatiles: 0. The load's candidate dtype follows the field, not the local it is assigned to.
- **Inner-join read:** one `flying = player->flying;` after the btnZLR if/else instead of the two arm reads: 5 (s32 or u32 local).
- **Field-pointer base** (`s32 *pf = &player->flying;`):
  - `flying = *pf` at the two flying-arm sites only: **0**. A different base variable gives a non-candidate load (Q0820's third route), but this is an alias-pointer steer, so it was not applied.
  - `*pf` for every flying read, keeping the re-reads: 53. Without the second-chain re-reads (final `*pf`): 100. Natural body through `pf`: 109.
- **Semantics:** the second chain cannot change `player->flying`, because `jetpacSetFlying(player, player->flying)` stores the same value. Every mix of local and field reads is therefore behaviour-equivalent; only the codegen differs.
- **Review:** removed four redundant value casts: `(f32)` on the `jetpacGame.ledges[idx].boxY2`/`boxY1` comparisons, and `(s32)` on both float arguments of `jetpacCheckLedgeEdge(s32, s32, s32)`. fdiff OK, uninit 0, cwarn 0.
- The volatile pair and the four re-reads stay.

**2026-11-16 U HackjetpacUpdatePlayerMovement4 HackjetpacUpdatePlayerMovement4 anthropic/claude-opus-5-5:high (review only).**

Full top-to-bottom review at base 22f598c3. The copy is unchanged: fdiff OK, uninit 0, no warning sites. The director block on the volatile pair holds, and b4a3d4 got no new idea. Probes:
- **Drop `s32 pad`:** .text stays 5632 bytes but the stack offsets shift, so fdiff=1. `pad` is the frame filler and stays untagged.
- **`player->vy = 0;` (line 363) -> `0.0f`:** adds `mtc1 zero,$f12` webs at 0xd40/0xda8/0xe70/0xe8c/0xe9c and grows .text by 16 bytes (fdiff=1; Q0426/Q0473). The integer-zero store is ordinary C and is what the target does, so it stays untagged.
- **Review checklist:** fake 3 kept / 0 removed, goto 0, casts 0 (the only casts are the two volatile FAKE sites), views ok, protos ok (all five callees come from include/proto/jetpac), temps ok (`vx` is reused only as a copy of player->vx), names ok.

**2026-11-16 U HackjetpacUpdatePlayerMovement5 HackjetpacUpdatePlayerMovement5 anthropic/claude-opus-5-5:high.**

Sweep at base a543051e: 27 checks, 0 hits. variants.py try on new bodies (full=):
- **Family Z** (new): the else-if test assigns `flying`, the flying arms have no reads, `flying = player->flying;` sits at the 0x9f0 join, the four second-chain arms re-read (btnLeft/btnRight ends, vx>0, vx<0), and the final test is `if (flying != 0)`: **2**.
  - 0x968-0xa9c all match, including the PRE'd `lw v0,48(s0)` at 0x99c/0x9c4/0x9e0. The join read now has a natural consumer: the final local on the vx paths.
  - Only 0xac8/0xaf8 are missing. The explicit vx-arm reads are VN-merged with the 0x9f0 join `lw`, because they are in its extended block (0x9f0 -> 0xa4c -> 0xaa8 -> 0xac0) with only the f32 `swc1 8(s0)` store in between.
  - The `lw a1,48(s0)` call arguments at 0xa3c/0xa98 stay fresh, because the s32 `sw 24(s0)` flip store kills VN. The btnLeft/btnRight re-reads at 0xa40/0xa9c are fresh because they sit at the inner join.
  - The same 2 results with a btnA-arm read added, and with a `u32 flying` local. With an expression else-if test instead of test-assign: 8.
- Family Z is the mirror of Family X (which is missing 0x9c4/0x9e0). The two pairs conflict:
  - PRE into the flying arms needs a `lw 48(s0)` anticipated at 0x9f0.
  - Fresh vx-arm loads need no `lw 48(s0)` earlier in 0x9f0's extended block.
  - So one non-candidate pair remains in every body tried.
- **vx if/else inner-join read** (after the vx arms) in place of the vx-arm reads:
  - Without the btnLeft/btnRight re-reads: 14.
  - With them: 12. The 0x9f0 join read is dead, because the local is reassigned on every path. 0x99c/0x9c4/0x9e0 vanish, and the inner-join `lw` stays at the join (0xb00, with a delay copy).
- Final `if (flying != 0 && player->flying != 0)`: 65. A final `if (player->flying != 0)` with only the btnLeft/btnRight re-reads: 72.
- Copy unchanged: fdiff OK, uninit 0. The volatile pair and the four re-reads stay.

## Untried ideas
- A JetpacPlayerActor field type that gives the flying-arm loads a different dtype from the test loads, for example a union. This is a header change and is unlikely to be natural (source: the u32 probe in HackjetpacUpdatePlayerMovement2; a u32 *local* does not do it).
- A natural consumer of the 0x9f0 join read: found in Family Z (the final local through re-reads in all four second-chain arms), but it moves the missing pair to 0xac8/0xaf8. What is still untried is a source shape in which the vx>0/vx<0 arms leave the 0x9f0 extended block (a join in front of them) without adding code. No natural C form is known: the btnLeft/btnRight/else chain and the vx if/else are all single-predecessor blocks.
- A natural second base for player (a caller-side pointer or a struct view that is a distinct variable rather than a respelling). The `pf`/`new_var` probes show that any distinct base matches; no natural source for one is visible in this function.

## Evidence
**Target 0x968-0xaf8:**
- One `lw 48(s0)` per source read of flying: the btnA test 0x970, the else-if test 0x9ac (plus delay-slot copies 0x96c/0x984), the flying arms 0x9c4/0x9e0, and the btnA arm 0x99c.
- The left/right arms reload after `jetpacSetFlying` (0xa40/0xa9c, delay copies 0xa30/0xa8c). The call arguments are fresh `lw a1,48(s0)` at 0xa3c/0xa98, after the `sw 24(s0)` flip store.
- vx>0/<0: 0xac8/0xaf8. On the vx==0 path, v0 is carried into `beqz v0` at 0xb0c.
- The vx join read follows the same pattern: `lwc1 $f16,8(s0)` at 0xa48/0xaa4/0xad8/0xb04, with the vx==0 path carrying the 0xaa8 load.
- Line 317's test is a fresh `lw t1,48(s0)` at the 0xc18 join (delay copies 0xbfc/0xc10), after the 0xb84/0xba4 vy stores.
