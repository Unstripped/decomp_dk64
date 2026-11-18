# controllerAnimCacheFree (global, src/global/17B90.c)
## Sites
global:80613944:other:af40b1 other (removed): `for (i = 0; i + 1 <= count; i++)` with `count = gAnimClipCacheCount` held in a local; the `i + 1 <=` spelling kept the counter test `slt at,v0,a0` (0xaf4) + `bnez at` latch (0xb84) that plain `i < count` turns into `bne v0,a0`. Fixed by reading the bound from the global in the test and deleting the `count` local.
## Attempts
2026-11-11 2026-11-11: cleanup round 12 file agents CleanGlobal17B90 claude-opus-5-5: punned-cast sites on D_807FBB30/D_807FBB32 -> fixed (fdiff 0); loop untouched (tagged LAYOUT then)
2026-11-14 2026-11-14: cleanup OwnerAnimCacheSlotShared claude-opus-5-5: views fixed (file-local AnimCacheEntry -> shared from include/actor.h); loop line kept as LAYOUT
2026-11-18 2026-11-17: cleanup Polishglobal17B90 claude-opus-5-5: plain `i < count` -> fails fdiff (LAYOUT kept as load-bearing)
2026-11-18 2026-11-17: cleanup Polishglobal17B90 CleanupLeadD claude-opus-5-5: retag LAYOUT -> FAKE (director ruling turn 159); diagnose nohit: plain `for (i = 0; i < count; i++)` full=300 scale, same .text size
2026-11-18 2026-11-17: cleanup CleancontrollerAnimCacheFree CleancontrollerAnimCacheFree claude-opus-5-5: variants.py try (deadsweep full=, lower is better):
- plain `for (i = 0; i < count; i++)`, s32 count -> full=2 (latch `bne v0,a0`, no slt; 75 lines)
- s16 count -> full=3 (`lh a0` + bne latch); u16 count -> full=12
- sibling guarded do-while `i = 0; if (G) do { ... break; } while (++i < count);`: G=`count != 0` -> full=4 (slt kept, guard `beqz a0` scheduled before `addiu v1`); G=`count` -> full=4; G=`count > 0` -> full=6 (bne latch); u32 i + `!= 0` -> full=5 (sltu); u16 count `> 0`/`!= 0` -> 16/14
- `for (i = 0; i < gAnimClipCacheCount; i++)` keeping a dead `count = gAnimClipCacheCount;` -> full=10 (frame 48, all sp offsets +8); with `s32 pad` -> full=10; u32 i -> full=2
- `for (i = 0; i < gAnimClipCacheCount; i++)` with no count local -> full=0, fdiff exit 0 (KEPT)
## Untried ideas
none open (site removed)
## Evidence
- 0xad8 `lhu a0,0(a3)` the single bound load (PRE-hoisted above the guard even when the source reads the global in the test)
- 0xae4 `blez a0` entry guard (signed `0 < bound`), 0xae8 `move v0,zero` in its delay slot (for-init order)
- 0xaec loop top `lw t7,8(v1)`; 0xaf0 `addiu v0,v0,1`; 0xaf4 `slt at,v0,a0` (counter test kept); 0xb84 `bnez at,0xaec` latch with `addiu v1,v1,12` in the 0xb88 slot
- 0xb20 `sw v1,24(sp)` / 0xb50 reload: entry pointer spilled across assetFreeBuffer; frame 40
