# jetpacUpdatePlayerMovement (jetpac, src/jetpac/1A60.c)

## Sites
- **jetpac:80026318:volatile:1d4065** (line 269) and **jetpac:80026318:volatile:1d4065#2** (line 272).
  - Each is a volatile reload of player->flying after the vy store in the flying arm. Target loads: `lw v0,48(s0)` at 0x9c4 and 0x9e0.
  - Without them, the vx>0/vx<0 reloads at 0xac8/0xaf8 also disappear.

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

## Result
- With `volatile s32 flying` in JetpacPlayerActor (include/jetpac.h), the plain reads match as a whole object, and all jetpac.h users still match.
- **Blocked** on the shared-type ruling: header-request.md, header.patch, vol/1A60.c.

## Untried ideas
- A second natural pointer to the actor, for example an original `JetpacActor *` parameter with a player view. That is the permuter's alias class, which was rejected as a steer.
- Nothing else is left in natural C.

## Evidence
**Target 0x968-0xaf8:**
- One `lw 48(s0)` per source read of flying: the btnA test 0x970, the else-if test 0x9ac (plus delay-slot copies 0x96c/0x984), the flying arms 0x9c4/0x9e0, and the btnA arm 0x99c.
- The left/right arms reload after `jetpacSetFlying` (0xa40/0xa9c, delay copies 0xa30/0xa8c).
- vx>0/<0: 0xac8/0xaf8. On the vx==0 path, v0 is carried into `beqz v0` at 0xb0c.
