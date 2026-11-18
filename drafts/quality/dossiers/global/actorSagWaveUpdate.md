# actorSagWaveUpdate (global, src/global/9DD70.c)
## Sites
global:80699958:other:8cbc73 other (FIXED 2026-11-17): `*(f32 *)((u8 *)gCurrentActor->sub4->boneOffsets + (numNodes << 4) - 8) = 0.0f;` was a byte-offset view (ushl node) that kept the end store from CSEing numNodes * 16 with the heapAlloc size term; the natural `boneOffsets[numNodes - 1].y` with `heapAlloc((numNodes + 1) * 0x10)` keeps umpy{ucvt numNodes,16} live from 0x950 to the end (spill sw/lw 0x94(sp), frame 0x1a8 -> 0x1b0, .text +16). Fixed by `heapAlloc((numNodes + 1) * sizeof(BoneVector))`.
## Attempts
2026-11-11 round 16 Rev16I opus-5-5:low: natural index form -> .text +16, score 1258; permute best only adds new_var = numNodes + 1 (steer)
2026-11-12 round 20 Rev20B opus-5-5:low: natural form diagnosed: sll t3,s0,0x4 spilled to 0x94(sp), frame 0x1a8 -> 0x1b0
2026-11-12 round 20/26 Perm20B/Rev26B: permute best=0 only by a found = 1 carrier in the index (steer swap, changes behaviour)
2026-11-13 round 38 CleanGlobal9DD70 opus-5-5:xhigh: uopt trace: natural index is uixa over umpy{ucvt numNodes,16} (bit 10, the heapAlloc term) vs separate ushl in the byte-offset form; permute (453 s) best=0 only by (numNodes ^ 0) + 1 (no-op steer)
2026-11-17 2026-11-17: cleanup CleanactorSagWaveUpdate CleanactorSagWaveUpdate opus-5-5: `heapAlloc((numNodes + 1) * sizeof(BoneVector))` + natural `boneOffsets[numNodes - 1].y = 0.0f` -> fdiff 0 (FAKE 1 -> 0). Same session: whole-function polish (casts, for loops, compound updates), each fdiff 0
## Untried ideas
none open for the site (fixed)
cross-file names: ActorGlobalState unk39/unk3C/unk7C/unk6C/unk8C -> riderCount/riderPos/riderActors/riderPointIndex/riderSpansNodes (7CA80.c callback 0x1 append, cap 4, actorRiderListAdd) (2026-11-17 review)
## Evidence
target: heapAlloc size `sll a0,s0,0x4; addiu a0,a0,16` at 0x950/0x954; `boneOffsets[numNodes].bone = 0xFF` recomputes `sll t7,s0,0x4` at 0xb38 (plain uixa index, no shared umpy); end store `sll t9,s6,0x4` at 0x1530, `addu t2,t8,t9` at 0x1550, `swc1 $f28,-8(t2)` at 0x1554; frame 0x1a8 (posOffsets sp+0x128..0x1a8, nodeForces sp+0xC0..0x128)
uopt -l 5 candidate table (tools/uopt_trace.sh -l 5): int size `(numNodes + 1) * 0x10` = bit 9 ucvt numNodes {1160}, bit 10 umpy{1160}{16} {279}, bit 11 uadd{279}{16}, bit 12 ucvt (to u32 for heapAlloc(u32)); the end-store uixa (bit 290) reuses {279} -> one candidate live across every call. sizeof size = bit 10 uadd{1160}{1}, bit 11 ucvt (to size_t), bit 12 umpy{1565}{16}: not distributed; {279} first appears at bit 290 (uixa bit 291), local to the last block
`x * 0.5` in the nodeY decay (case 0) shares the 0.5 double with `slotAmp < 0.5` / `slotPhase * 0.5`: .text -16 (Q1018, Q0421); `/ 2.0` or `(f64)d * 0.5f` keep the separate lui 0x3fe0 / mtc1 $f15,$f14 hoist at 0x13a0
