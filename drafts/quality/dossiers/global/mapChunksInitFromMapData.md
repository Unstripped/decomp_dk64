# mapChunksInitFromMapData (global, src/global/55B20.c)
## Sites
- 12a29f dead-if (kept, class 1): `if (data) {}` splits the uopt block, so the cells/boxes/vecs offsets (v1/a0/a1 at 0x140-0x184) sit in a block without the heapAlloc(gMapPortalSlotCount) call; without it they take a1/a2/a3. The split behaves like a varreflimit cut (Q0556): a dead statement with 6 or more counted data lods at the same spot also matches.
- 551532 dead-if (kept): the dead `(u32)data == (u32)gMapPortals[i].dl1` read is a second data use in the dl0-arm block. That lifts data (cand 8) from adjsave 5.92 to 6.69, above the -1 constant (6.27), so data takes s7 and -1 takes s8.
- fc3dbd dead-if (kept): `if (gMapChunks) {}` after the plane loop stretches the lda gMapChunks web over the plane-loop blocks (adjsave 48 -> 40.1). That ties the chunk-record pointer p (40.1), which colours first: p takes s2 and lda gMapChunks takes s3.
- 512c53 (removed 2026-11-17): the collision entry byte offset has its own `s32 entryOff = n * sizeof(MapChunkCollEntry);` local, declared after relocsOff; its slot is paid by `u8 buf[0xE2C]` (was 0xE30). `size` now holds only layer sizes.
- 4a8a7f, 5f674b (removed 2026-11-15): the portal-table and portal-list offsets are the role-named locals `portalsOff` and `relocsOff`.
## Attempts
- 2026-11-14 (earlier units):
  - 551532: removal 38; MapPortal * snapshot 64; both dead tests removed with the snapshot 139.
  - fc3dbd: removal 76; for-loop fill 79; real `if (gMapChunks != NULL)` guard 7 (adds a branch).
- 2026-11-15 HackmapChunksInitFromMapData anthropic/claude-opus-5-5:high:
  - portalsOff + relocsOff locals with buf 0xE30: fdiff 0.
  - Typed index `[n]` and its spellings: 9. `MapChunkCollEntry *coll` local: 90. `(u8 *)data + off`: 356.
  - 551532: removal 38; 8 relocation-sum orders 42; portal pointer local 55; portal pointer walk 417; split loops 400; data instead of p in the first part 71-79.
  - fc3dbd: removal 76; inverted if/else 92; early return 92; permuter 900 s.
  - 12a29f: removal 360.
- 2026-11-17 (session 2026-11-17f) CleanmapChunkEmitLayerDisplayLists anthropic/claude-opus-5-5:
  - 512c53 fixed: dedicated entryOff local, buf 0xE2C (0 at any slot from after `base` to after `relocsOff`; 6 after i/off; 15 at the end; 0xE30 at the end 9).
  - 12a29f: a dead `n = (s32)data + ...` scores by data-lod count k: k>=6 0; k=5 2; k=3-4 4; k=1-2 14; `n = 0` 330.
  - 12a29f natural lod-adding head respellings: two data->cellsOff reads 351; `(u8 *)data` for p 340 (434 without p = data); three offsets inlined 360; p assigned late 383.
  - 551532 re-measured on the entryOff body: removal 33. `(s32)data + base` in either arm 35, in both 37; `dl0 = dl0 + p + base` 37; -1 respellings 33; u32 compares 330; `*(s32 *)(p + relocsOff)` bound 122; data in the chunk-loop relocations 54.
  - fc3dbd: before the enable loop or before `D_807F70AA = 0`: 0; after it 6; before the plane alloc 76; in the plane loop 88. `if (1) {}` and `if (gMapChunkCount) {}` at the spot: 76.
  - Removal combinations on the entryOff body: all three 345; 12a29f+551532 347; 12a29f+fc3dbd 329; 551532+fc3dbd 108.
  - Consistent `size` use for layer 0: 3; layer 3: 158; both: 161.
  - Permuter: hack-free weights, -j 2, 900 s, from the all-removed body (perm_i): baseline 2595, best 500, which only re-inserts `if (gMapChunks) {}` at the 12a29f spot.
## Untried ideas
- Natural code adding 6 or more counted variable lods between the node 3 start and line 228 without changing instructions (12a29f varreflimit route).
- A natural use of data at portal-loop weight that is not copy-propagated into the existing arm uses (551532).
- A real reference to gMapChunks after the plane loop (fc3dbd). The target has none, so the original probably had a different block or web structure there.
## Evidence
- Frame 0xED8: dlBase home sp+0xECC (3788); buf sp+0x78 (120); count sp+0x74; spilltemps sp+0x54 data+off+4, sp+0x58 data+off, sp+0x5C n*12 (stored +12 at 0x7b4-0x7b8).
- 0x140-0x184: cellsOff v1, boxesOff a0, vecsOff a1; `lui a0,%hi(gMapPortalSlotCount)` at 0x17c after the last a0 use; 0x18c collOff -> s4, 0x190 chunksOff -> s1, 0x198 portalsOff -> v1, 0x1c8 relocsOff -> a0.
- Portal loop 0x214-0x25c: -1 in s8, data in s7, data+base hoisted twice (t0, t3); gMapPortals reload (0x230-0x234) only on the dl0 store path.
- Chunk loop: lda gMapChunks s3, p s2, n s6, n*0x1C8 s1; plane loop lda gMapGridTrianglePlanes s2; else branch stores through s3 (0x8a8-0x8b0).
- Level-5 traces (.scratch/CleanmapChunkEmitLayerDisplayLists/ti5_*.txt):
  - data cand 8: 6.69 base, 5.92 removed; -1 cand 351/356: 6.27.
  - lda gMapChunks cand 358/359: 40.1 base, 48 removed; p cand 6: 40.1.
