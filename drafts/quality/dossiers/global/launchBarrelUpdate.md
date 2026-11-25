# launchBarrelUpdate (global, src/global/80150_barrels.c)

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
2026-11-24b ReMeasureB18H opus-5-5:xhigh (after the cb17735e EffectGridAsset extern retype; gEffectSpriteBlast is only &-passed in case 2): removal full=2 (lui a1,0x3f80 one slot earlier, as before); as1probe keep of base vs removal: the `.alias $3,$17` / `.alias $3,$sp` pair sits at ugen records 412/413 (before $38) in the base and 375/376 (right after jal camStartPath) without the dead if; as1probe scan of the removal: only `insert alias` into the .rdata jump-table words (records 390-397) reaches 0; Q0855 explicit empty labels `case 0: case 4: ... case 19:` for `case 0: default:` with or without default -> 197, default without case 0 -> 61.
2026-11-25 continue CleantagBarrelCheckKongFlag anthropic/claude-opus-5-5 (base 594af197, variants.py try): uopt ucode (as1probe ucode, line numbers stripped) base vs removal: the dead if leaves an orphan `lab 17` between the `state = 1` istr (u8 340) and the `timer = 10` istr (u8 20); with it uopt emits `unal $v1 $s1 0` / `unal $v1 $sp 0` after the 22-entry jump table (before case 1 `lab 22`) and restores `rlda $v1` (&gActorGlobalState) before `rldc $a3 1` / `rldc $t0 2` after `cup camStartPath`; without it the unal pair follows the cup directly and the restores are `rldc $a3 1; rldc $t0 2; rlda $v1`. Natural levers measured on the removal: `u8 phase = gActorGlobalState.bossFightPhase` selector local -> 80; one-case `switch (gActorGlobalState.bossFightPhase) { case 4: ... break; }` -> 6 (text 4; also not ordinary: nothing switches on bossFightPhase); the nested `hidden == 1` / `tagBarrelIsSpecial() == 0` ifs merged into one `&&` -> 2 (base 0: no effect).
2026-11-25 same: permuter perm_lb (hack-free weights incl. 12452351, -j 2, 900 s, 7975 iterations) from the removal body: base 60, best 60, no improving output.

## Untried ideas
A natural construct that leaves a code-free block boundary (an orphan ucode label) between the `state = 1` and `timer = 10` stores in the bossFightPhase block: a condition uopt folds away completely (constant-false debug code would do it, but nothing in the target proves one).

## Evidence
Target 0x324/0x328 `lui v1,%hi(gActorGlobalState); addiu v1,v1,%lo(...)` after `jal camStartPath` (same in both builds).
Target 0x35c-0x378: `lbu t1,0x14(s2); li at,6; addiu t4,t1,-1; andi v0,t4,0xff; bne v0,at,3a0; sb t4,0x14(s2); lw a0,0(s1); lui a1,0x3f80` (lui after the branch).
uopt ucode (base): `cup camStartPath; rlda $v1 (&gActorGlobalState); rldc $a3 1; rldc $t0 2; lab 16; ... xjp; clab; 22 ujp; unal $v1 $s1 0; unal $v1 $sp 0; lab 22` (case 1). Target 0x324-0x330 `lui v1; addiu v1; li a3,1; li t0,2`.
