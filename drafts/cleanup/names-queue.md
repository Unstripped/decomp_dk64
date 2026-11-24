# Names queue (continue-unit names stream)

Accepted proposals waiting for the next names window (`.omp/skills/continue-unit/names.md`). The lead appends after
the "Check"; the window that applies a line deletes it. Format:
`- [field|global|func] <seg or include/h.h> <Record|-> <old> -> <new> | <evidence, file:line> | <worker>`;
`held:` lines keep an item out until new evidence arrives.

## Queue
- [field] include/map.h MapBspNode unk18 -> translucentOverlayDl | 2F550 mapTreeRender 700-702 draws it last in a leaf (after opaqueDl / unk14 / translucentDl), 1536-1537 relocated like the named lists; only map 0x6B populates it (8-tri ZMODE_XLU surface); runtime toggle removes the arena light halo / floor shading (.scratch/EmuFieldsU5/MapBspNode.unk18.md); window needs `--macro-arg src/global/2F550_map_render.c:701:77` (inspected: gSPDisplayList argument) | EmuFieldsU5 (2026-11-24b)
- [field] include/heap.h DynamicBuffer unk14 -> pushBothSides | 42630:1793 cutscene op 0x2A stores cmd->a into the slot boxBuffer, 36880:577 zeroed at slot init, 70FD0:1801 copied to D_807FB603 before resolving against the slot boxes; read by hand-written func_80673D48 (asm/global/77B90.s:1176-1197, 0x80673EF8): when set (and D_807FB5FE == 1, gCollisionDeferredPush) the pair is swapped so the box plane's other side pushes too; op 0x2A is in none of the 145 cutscene assets: add a header comment on the dead effect (ruling 2026-11-23) | EmuFieldsU5 (2026-11-24b)
- [field] include/actor.h ActorSub140 unkAC -> pushBothSides | 7BBD0:1350 copied to D_807FB603 for actor-box collisions (same reader); 70FD0:1014 zero at alloc is the only store in any segment: header comment on the dead effect | EmuFieldsU5 (2026-11-24b)
- [global] global - D_807FB603 -> gCollisionPushBothSides | the flag both fields above are copied into (70FD0:1801, 7BBD0:1350) and func_80673D48 reads (77B90.s:1177); lead name from EmuFieldsU5's evidence; EmuGlobalsU5 holds it too: compare when its report lands | continue-lead (2026-11-24b)
- WINDOW BLOCKED until TypesOwner17 batch_18 releases src/global/42630_cutscene_interp.c (in its files.txt).

## Held
- held: [global] global D_80753C84 -> gKongPathRespawnTimers, D_80753CA4 -> gKongPathCheckRespawnTimers (worker: tentative) | per-kong s16 tables stored to respawnTimer every frame of playerStateAttachedCallbackFall/CheckFall while proxPathFollowerStep runs | PolishglobalD5E10c (2026-11-24)
- held: [field] EmuFieldsU5 (2026-11-24b, runtime + asm store scans; notes .scratch/EmuFieldsU5/*.md): MapBspNode.unk14 (no shipped map populates it: 0 of 15 BSP leaves, 121 chunk maps all -1); PlayerState.unk18 (nonzero forces swim idle, D5E10:195/217/2673/2713; no nonzero writer in any segment; 75 s swim on map 0x2E never wrote it), unk64 (zero writes only; read by scriptCmdCheckGlobalToggle 19A00:1923); KongInventory.unk5 (3-bit lobby index + flag, EEPROM round trip only, always 0); ActorEntry.unk4 (zero-written, no reader); N_ChanState.unk31 (always 0; initOsc's 7th argument, which oscInit never loads: a dead-parameter-ruling candidate, needs a role name); ActorGlobalState.unk18 (subtype-2 hit flag, event 8; confirm with anim 25/31/32/33/64/67 attacks, breakpoint 0x80679798); CamState.unkF8/unk1C, CsState.unk3C/40/9C, ScriptedActorState.unk18/1A, PlayerState.unk128/12C, ModelPathEntry.unk8/unk15, AnimInitData.unkC: write-only or never set
