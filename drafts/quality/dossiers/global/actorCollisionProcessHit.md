# actorCollisionProcessHit (global, src/global/7A510.c)

## Sites
- global:80675810:other:d9962d other (removed 2026-11-17): `bossFightPhase = (interactions + i)->phase` re-read kept the strength-reduced entry induction in $s1 and &gActorGlobalState in $s0
- global:80675810:other:818f85 other (removed 2026-11-17): `entry = &interactions[0] + i` kept the base-first init `addu s1,a0,t1` at 0x110

## Attempts
- 2026-11-14 HackSentinelSwitchChains opus:high: switch on entry->chain alone 37; with phase as entry->phase 40, interactions[i].phase 85, hitPhase 53; same without the switch: entry->phase 40, hitPhase 53
- 2026-11-14 HackSentinelSwitchChains opus:high: switch (entry->chain) {case 0: case 2:} combined with each entry spelling and each phase spelling
- 2026-11-17 cleanup HackactorCollisionProcessHit2 HackactorCollisionProcessHit2 anthropic/claude-opus-5-5: entry local dropped, every field read as `interactions[i].f` (targetMask, attackerMask, filter, phase twice, event, chain three times) -> fdiff 0 (both sites removed, uninit 0, cwarn 0)
- same unit, natural forms with the cached `entry` kept (variants.py try): `entry = &interactions[i]` + `entry->phase` 40; same with i as u32 40, s16/s8 108, u16/u8 107; drop hitPhase/curPhase (`bossFightPhase < entry->phase` or mirrored) 108; `for (i = 0; !done; i++)` 83
- same unit, no entry local: every field as `(interactions + i)->f` 1 (the 0x110 addu operand order only); every field as `interactions[i].f` 0
- same unit, on the fixed body: drop hitPhase/curPhase (`bossFightPhase < interactions[i].phase` or mirrored) 59; drop curPhase only 53: the snapshot locals are real (load order phase, bossFightPhase, unk201 at 0x168-0x170)

## Untried ideas
- none: no sites left

## Evidence
- loop pointer: `sll t1,s0,2; subu; sll` (i*12, i still in $s0 = 0 from 0x28) then `addu s1,a0,t1` at 0x110, `addiu s1,s1,12` at 0x27c; every field load is off $s1 (0(s1), 2(s1), 4(s1), 8(s1) twice, 9(s1), 10(s1)), so the original indexes interactions[i] at each use and uopt CSEs the address into one strength-reduced induction
- phase re-read: `lbu v0,8(s1)` 0x168, `lbu v1,512(s0)` 0x16c, `lbu a0,513(s0)` 0x170, `slt at,v1,v0`; in the arm `sw s2,508(s0)` 0x180 then `lbu t8,8(s1)` 0x184, `sb t8,512(s0)` 0x188: the store to targetActor may alias the field, so the second `interactions[i].phase` is reloaded
- the chain test is lbu v0,10(s1) at 0x24c, beqzl v0 at 0x254, bnel v0,2 at 0x25c; a switch (entry->chain) {case 0: case 2:} gives the same compares but swaps the s0/s1 colouring of &gActorGlobalState and entry (37 lines)
- a cached `entry = &interactions[i]` pointer is what forced both steers: with it every spelling of the address or the re-read recolours (40) or flips the 0x110 addu (1); without it the plain indexed form matches (Q0589 actorTargetEntriesUpdateSfx pattern)
