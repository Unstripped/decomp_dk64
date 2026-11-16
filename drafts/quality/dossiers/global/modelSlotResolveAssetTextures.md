# modelSlotResolveAssetTextures (global, src/global/36880.c)
## Sites
global:80636D38:volatile:8d1318 volatile (REMOVED 2026-11-16): `ModelSlotAsset *volatile textures` copy of seg gave the else-arm `sw s0,60(sp)` home and `lw 60(sp)` reloads (0x178/0x198/0x1ac). Replaced by `textures = slot->unk20` as its own local (CSE shares the one `lw s0,32(a0)`; textures stays uncoloured) plus `s16 flags`.
global:80636D38:other:75aced other (now ORIG): `node = ((ModelType1ObjAddrs *)slot->unk20)->texAnims` — the target reloads slot (`lw t6,72(sp)` at 0x90) and slot->unk20 (`lw t7,32(t6)` at 0xA0); `seg->texAnims` scores full=48. Cast stays while ModelSlot.unk20 is `void *` (model.h H1/H2 regeneration).
global:80636D38:dead-store:afe8f9 dead-store: `temp = (u32)seg;` kills copy propagation of `obj = temp`, so obj's early uses (unk8 store, unk0 load) stay temp's web v0 and later ones obj's s1 with `move s1,v0` at 0x40 (Q0546).
(copy-only key, see ledger-copy-only.txt) other: `temp = (seg->displayListB - cmds) >> 3;` reuses obj's early pointer local for the command count; temp's webs share one colour, so the B-A diff (`subu v0,v1,a0` at 0xA4) and obj's early web are both v0. A dedicated count0 local swaps v0/v1 (obj early v1, displayListB v0).
global:80636D38:dead-store:28cb6a dead-store: `temp = 0;` after `size0 = temp * 8` keeps size0 a declared variable (home 36(sp), t1) instead of a copy-propagated expression temploc (Q0550).
global:80636D38:dead-store:2c2a64 dead-store: `count = 0;` after `size1 = count * 8` keeps size1 a declared variable (home 32(sp), t1 at 0xE4) (Q0550).
global:80636D38:dead-if:bb36c3 dead-if (EXHAUSTED): `if (seg->displayListA == 0) {}` keeps seg live past the last call so it stays in s0.
## Attempts
2026-11-09..2026-11-14 (263 events, rounds Clean36880 .. RereviewModelAudio): see `uv run tools/quality.py history modelSlotResolveAssetTextures` (permuter, uopt traces, natural rewrites, Q0546/Q0547/Q0549/Q0550).
2026-11-16 HackmodelSlotResolveAssetTextures anthropic/claude-opus-5-5:high:
- volatile removed: `textures = slot->unk20` (separate local, no volatile) -> full=4 (flags lbu t0 vs a3); `variants.py scan` width `flags` u8 -> s16 -> fdiff 0. `textures = (ModelSlotAsset *)seg` without volatile: full=7.
- plain removal of every other site on the new body (31 combos of afe/28c/2c2/bb3/75a): best single r_2c2 full=31, r_28c 33, r_75a 48, r_bb3 64, r_afe 90; none 0.
- c-form (no size0/size1 locals, `(DisplayListCmd *)cmds + temp/count`, `|=`): instruction stream identical, frame 0x50 (+8): `res |= call()` makes a cfe temp (M -36vreg, dead ustr) above the two uopt size temps (Q0445). `res = res | call()` (any of the three ors): frame 0x48 and every home exact, but uior takes the call result first (`or v1,v0,v1` x3) -> full=3; casts `(s32)res`, `(u32)res`, `(u8)`, call-first order, `!= 0`: all full=3 or worse.
- c-form + result local: `s32 ret; ret = call(); res = res | ret;` restores `or v1,v1,v0` but costs a declared slot (0x50); ret u8/s8/s16/u16 x flags s16/u8/s8/u16 x 3 positions x 3 or-forms (144): best full=17 (ring t2/t9 vs t9/t8 after call 2). Without `cmds` (direct fields) + s32 ret (10 decl orders): best full=48, homes exact but a0/t0 colours shift from 0x48.
- multi-op sizes on the base body: `size0 = ((seg->displayListB - cmds) >> 3) * 8` without temp: shape 0, full=33 (v0/v1 swap); `& ~7`: 18 (li at,-8/and); `temp / 8 * 8`: 40; size1 forms: 31..57.
- dedicated count0 local (temp kept only for obj): full=8, v0/v1 swap -> temp's count reuse is a colour steer (tagged).
## Untried ideas
- A natural reason for one local holding both slot->unk24 and the command count (a generic `u32`/`void *` scratch in the original?), which would explain afe8f9 + the reuse together (Q0507).
- c-form with the cfe temp slot absorbed: a declaration layout that drops one 4-byte register-only local (seg/obj/temp/cmds) while keeping the ugen ring (m-series lost it through the cmds web).
## Evidence
- 0x1C `lw s0,32(a0)` (seg) then 0x2C `sw s0,60(sp)` (textures home); else arm reloads 60(sp) at 0x178, 0x198 (jal delay), 0x1ac (jal delay).
- 0x24 `lw v0,36(a0)`, 0x34 `sw t8,8(v0)`, 0x40 `move s1,v0`, 0x54 `lw t3,0(v0)`: obj early web v0, later s1.
- 0x44 `lbu a3,140(t9)` flags in a3 (Q0549).
- 0x90 `lw t6,72(sp)`, 0xA0 `lw t7,32(t6)`, 0xAC `lw a2,184(t7)`: node read through a reloaded slot->unk20.
- 0xA4 `subu v0,v1,a0`, 0xA8 `srl t4,v0,3`, 0xB8 `sll t1,t4,3`, 0xBC `sw t1,36(sp)` (size0), 0xC0 `sw t5,48(sp)` (count), 0xD4 `lw t0,48(sp)`, 0xE0 `sll t1,t0,3`, 0xE4 `sw t1,32(sp)` (size1).
- `or v1,v1,v0` (res first) at 0x104, 0x134, 0x150; res byte home 43(sp); node home 44(sp).
