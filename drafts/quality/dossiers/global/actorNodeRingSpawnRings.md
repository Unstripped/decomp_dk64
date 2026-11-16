# actorNodeRingSpawnRings (global, src/global/C1E70.c)
(formerly func_806BD170; dossier was drafts/quality/dossiers/global/func_806BD170.md)
## Sites
global:806BD170:other:03a376 (other): `s16 activeRingCount` -- held s5; init move s5,zero at 0x60, increment addiu s5,s5,1 + sll/sra at 0x1a8-0x1b8 in the active-ring arm; never read. `// ORIG:` (Q0865) -> not a site.
global:806BD170:proto-type:726a32 (proto-type): PROTO_SKIP_actorSpawn + K&R `s32 actorSpawn();` for the actorNodeRingUpdate call passing a spare third argument &gCurrentActor. FIXED 2026-11-15 (consolidate): define, K&R declaration and third argument removed; shared `s32 actorSpawn(s32, s32)` (7CA80.h); whole-object fdiff 0. uopt still puts &gCurrentActor in a2 (lui a2 0x2b0, addiu a2 0x2c8, lw t3,0(a2) 0x2cc of actorNodeRingUpdate) without the argument.
global:806BD170:other:0c7a30 (other): `i = 0; activeRingCount = 0; for (; i < 8; i++)`. FIXED 2026-11-15 (diagnose): retagged `// LAYOUT:` -- the lever is as1 .loc line order, not statement order or a steer -> not a site.
## Attempts
2026-11-12 CleanGlobalC1E70 claude-opus-5-5:low: remove count -> fdiff fail (0x60 move and 0x1a8-0x1b8 increment vanish, s6->s5 etc).
2026-11-12 CleanGlobalC1E70: diagnose nohit; permute nohit (perm_count).
2026-11-14 U Hackfunc_806BD170 claude-opus-5-5:high: classify count as ORIG (asm offsets 0x60, 0x1a8-0x1b8) -> fdiff 0, site gone.
2026-11-14 U Hackfunc_806BD170: review: pos moved before mathSinF (variants try: full=0 at 4 placements); sub->ring; &= ~0x8000 -> fdiff 0.
2026-11-14: loop init spellings (variants try): for (i = 0;...) 2, for (i = 0, count = 0;...) 4, count before idx + for-init 4, decl initializer 4, idx after inits 2, count before idx with i = 0; for (;...) 2 -> base `activeRingIdx = -1; i = 0; count = 0; for (; ...)` kept.
2026-11-14: activeRingActor->state = 5 via gSpawnedActor -> full=20 (target reuses t4 from sw 84(sp)).
2026-11-15 PolishglobalViews: views blocked (actorSpawn never homes or reads a2, 0x228-0x290 of 7CA80).
2026-11-15 PolishglobalCarve56: tagged 0c7a30 FAKE (pre-existing).
2026-11-15 U HackactorNodeRingSpawnRings claude-opus-5-5:high: shared prototype, third argument dropped at both calls -> fdiff 0 (726a32 consolidate fixed).
2026-11-15 U HackactorNodeRingSpawnRings: line-placement variants (variants try, full=): `for (i = activeRingCount = 0;...)` 4, `for (activeRingCount = i = 0;...)` 4, `i = activeRingCount = 0; for (;...)` 0, `activeRingCount = i = 0; for (;...)` 0, `i = 0; activeRingCount = 0;` on one line 0, `activeRingCount = 0; i = 0;` on one line 0, count line then i line 2, `for (i = 0;` / `i < 8; i++)` split header 2, `activeRingCount = 0; for (i = 0;...)` on one line 4, `for (activeRingIdx = -1, i = 0;...)` 6, `for (i = 0, activeRingIdx = -1;...)` 6, while (i < 8) with i line first 0, with count line first 2 -> 0c7a30 retagged LAYOUT, fdiff 0.
## Untried ideas
none (no FAKE, PROTO or goto left).
## Evidence
0x58 sh t6,80(sp) (activeRingIdx = -1); 0x5c move s1,zero (i); 0x60 move s5,zero (activeRingCount); 0x64-0x78 ori s8/ori s7/addiu s4/addiu s0/li s3 255/li s6 2000 (preheader hoists; luis scheduled into the prologue at 0x3c-0x48); 0x1a8 addiu s5,s5,1; 0x1b0 sll t7,s5,16; 0x1b8 sra s5,t7,16; activeRingActor at sp+84 (sw t4 at 0x1b4).
ugen (as1probe keep, natural `for (i = 0;...)`): `.loc 60` move $21,$0 (count), then `.loc 61` (for line) move $17,$0 (i) followed by li.s $f22/$f20, li $30/$23/$22, la $20, li $19, la $16 -- the for-init shares the hoists .loc, so move s1,zero lands at 0x70.
