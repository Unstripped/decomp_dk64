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

## Untried ideas
- A JetpacPlayerActor field type that gives the flying-arm loads a different dtype from the test loads, for example a union. This is a header change and is unlikely to be natural (source: this attempt's u32 probe).
- A natural consumer of the 0x9f0 join read that leaves no trace except the v0 carry into 0xb0c on the vx==0 path. None was found among the function's uses of flying (the call arguments, the final test, the line-317 test).

## Evidence
**Target 0x968-0xaf8:**
- One `lw 48(s0)` per source read of flying: the btnA test 0x970, the else-if test 0x9ac (plus delay-slot copies 0x96c/0x984), the flying arms 0x9c4/0x9e0, and the btnA arm 0x99c.
- The left/right arms reload after `jetpacSetFlying` (0xa40/0xa9c, delay copies 0xa30/0xa8c). The call arguments are fresh `lw a1,48(s0)` at 0xa3c/0xa98, after the `sw 24(s0)` flip store.
- vx>0/<0: 0xac8/0xaf8. On the vx==0 path, v0 is carried into `beqz v0` at 0xb0c.
- The vx join read follows the same pattern: `lwc1 $f16,8(s0)` at 0xa48/0xaa4/0xad8/0xb04, with the vx==0 path carrying the 0xaa8 load.
- Line 317's test is a fresh `lw t1,48(s0)` at the 0xc18 join (delay copies 0xbfc/0xc10), after the 0xb84/0xba4 vy stores.
