# launchBarrelUpdate (global, src/global/80150.c)

## Sites
global:8067B4C8:dead-if:bd5eb8 dead-if: `if (0) {}` after `gCurrentActor->state = 1;` in the bossFightPhase == 4 block. It moves uopt's `.alias $3,$17` / `.alias $3,$sp` records (the $3 = &gActorGlobalState region) from right after `jal camStartPath` to the case-1 entry $38; without it as1 hoists case 1's `lui a1,0x3f80` above `bne v0,at`.

## Attempts
2026-11-15 HacktagBarrelOrbitKongs2 HacktagBarrelOrbitKongs2 anthropic/claude-opus-5-5:high: removal at c85737c -> full=2 (lui a1,0x3f80 at 0x364 instead of 0x378); no v0/v1 change any more.
2026-11-15 same: as1probe scan 200-300 of the dead-if-free listing -> only `insert alias` in the jump-table/.text gap before $38 gives full=0.
2026-11-15 same: 60 statement orders of the block (rider store before rider->yaw) -> best is the current order (full=2).
2026-11-15 same: `ActorGlobalState *gs = &gActorGlobalState;` for all uses / the block / the case-20 loop -> 208 / 17 / 209; rider local -> 82.
2026-11-15 same: case-20 loop base-depth spellings (`*(op + i)`, `(&op[0])[i]`, `*(&op[0] + i)`, `(&gActorGlobalState)->`, `i[op]`, mirrored compares) and `(&gActorGlobalState)->` in the block -> full=2.
2026-11-15 same: `default: case 0:`, separate `case 0: break; default: break;`, labels moved last -> 2; dropping case 0 / default -> 61.
2026-11-15 same: case-1 `--sub->timer == 6` respellings (split decrement, `-= 1`, mirrored, 1.0 / 1) -> 2; variants.py scan (21 variants) -> no zero.

## Untried ideas
A natural construct that ends the $3 (&gActorGlobalState) uopt region at the switch head rather than after camStartPath (own diagnosis).
Permuter on the dead-if-free body with hack-free weights (optional).

## Evidence
Target 0x324/0x328 `lui v1,%hi(gActorGlobalState); addiu v1,v1,%lo(...)` after `jal camStartPath` (same in both builds).
Target 0x35c-0x378: `lbu t1,0x14(s2); li at,6; addiu t4,t1,-1; andi v0,t4,0xff; bne v0,at,3a0; sb t4,0x14(s2); lw a0,0(s1); lui a1,0x3f80` (lui after the branch).
