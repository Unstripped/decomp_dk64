# billboardRenderQueued (global, src/global/61AA0.c)
## Sites
global:8065D994:other:89b2f5 other (FIXED 2026-11-17f): `bb = &gBillboardQueue[i * 1];` kept the matrix/vertex base $s5 (i*264 + &gBillboardQueue recomputed from $s4 = i at 0xdc0) apart from the field-load induction pointer $s1. It stood in for the original's inline `&gBillboardQueue[i].matrices[gGfxBufferIndex]` / `&gBillboardQueue[i].verts[gGfxBufferIndex][0]` with no element-pointer local.
## Attempts
2026-11-10 (round 9) CleanGlobal61AA0 anthropic/claude-opus-5-5:low: diagnose (i * 1 keeps bb distinct from the IV), permute -> nohit.
2026-11-13 (round 38) CleanGlobal61AA0 anthropic/claude-opus-5-5:xhigh: `if (count > 0) do {} while` -> for loop, blend-mode ifs merged (review fixed); diagnose keepR vs bb uopt traces (keep gives bb its own add); permute on plain bb (best adds a Mtx * temp for &bb->matrices) -> nohit.
2026-11-17 "2026-11-17: cleanup CleanbillboardRenderQueued" CleanbillboardRenderQueued anthropic/claude-opus-5-5: bb local dropped, both osVirtualToPhysical addresses written inline as gBillboardQueue[i].matrices[gGfxBufferIndex] / .verts[gGfxBufferIndex][0] -> variants.py full=0, fdiff 0 (FIXED, FAKE 1 -> 0).
Measured on the way (variants.py try full=): plain `bb = &gBillboardQueue[i]` 223 (for, pre-tested while and if/do-while alike); `bb = gBillboardQueue + i` 227; bb for every element access in the if (layer test still gBillboardQueue[i]) 201; bb + i for every access 226; inline `(gBillboardQueue + i)->matrices/verts` 227; inline `gBillboardQueue[i].matrices/verts` 0 in for, while and if/do-while. Review: case 1 using curTex instead of the re-read 131; case 1 without the (u8 *) cast is a cfe error (void * + int).
## Untried ideas
none open: function has no hack sites.
## Evidence
- First loop 0xc4c-0xca0: entry test `blez a2` (count read once into $a2 at 0xc00), induction pointer $s1 with LFTR end $v1 = &gBillboardQueue[count] (`sltu at,s1,v1` at 0xc84), `beqzl v0` on found.
- Second loop 0xd68-0x1260: entry test `blez a2,0x1264` at 0xd74; layer homed (`sh a3,78(sp)` at 0xd88, `lh t7,78(sp)` per pass at 0xd8c); field loads off the induction pointer $s1 (layer `lb 263(s1)` 0xd90, renderFlags `lhu 256(s1)` 0xdc4/0xdfc, alpha `lbu 262(s1)` 0xe34, cacheIndex `lbu 258(s1)` 0xe40, texFormat `lbu 261(s1)` 0xe60), `addiu s1,s1,264` in the back-edge slot 0x1260; $s4 = i kept for `slt at,s4,a2` with count reloaded at 0x124c (calls in the body block LFTR).
- Matrix/vertex base: `sll t8,s4,5; addu t8,t8,s4` (0xd94/0xda0), `sll t8,t8,3` 0xdac, `addu s5,t8,t3` 0xdc0 (guarded block); `addu a0,s5,t8` 0x11d8 (&matrices[gGfxBufferIndex]), `addu a0,s5,t4; addiu a0,a0,128` 0x1200/0x1208 (&verts[gGfxBufferIndex][0]).
- Case 1 re-reads the texture: `lbu t5,258(s1)` 0x101c, `lw t3,8(t7)` 0x1038 (after the gdl store at 0x1018); case 0 uses the loaded $a1 (`addu t5,a1,at` 0xe94).
- prevTex spilled to sp+64 (`lw t2,64(sp)` 0x120c); $s7 = 0xe7000000 (PipeSync word), $s8 = &gBillboardCache, $s6 = blendMode.
