# mapChunksInitFromMapData (global, src/global/55B20.c)
## Sites
- 12a29f dead-if (kept): `if (data) {}` splits the uopt block so the cells/boxes/vecs offsets (v1/a0/a1 at 0x140-0x184) sit in a block without the heapAlloc(gMapPortalSlotCount) call; without it they take a1/a2/a3.
- 551532 dead-if (kept): the dead `(u32)data == (u32)gMapPortals[i].dl1` read adds one loop-weight use of data, so data keeps s7 above the -1 constant (s8), and keeps the gMapPortals reload in the dl0 store arm (Q0566).
- 512c53 other (kept): `size = n * 12` puts umpy(n,12) into the expression table before data+off, so the spilltemps are sp+84 data+off+4, sp+88 data+off, sp+92 n*12 IV.
- fc3dbd dead-if (kept): `if (gMapChunks) {}` after the plane loop lengthens the coloured lda gMapChunks web, so it takes s3 and the chunk-record pointer p takes s2.
- 4a8a7f, 5f674b (removed 2026-11-15): the portal-table and portal-list offsets are role-named locals `portalsOff`/`relocsOff`; their two extra frame slots are paid for by `u8 buf[0xE30]` (was 0xE38).
## Attempts
- 2026-11-14 (earlier units): 551532 removal 38, MapPortal * snapshot 64, both dead tests removed with snapshot 139; fc3dbd removal 76, for-loop fill 79, real `if (gMapChunks != NULL)` guard 7 (adds a branch).
- 2026-11-15 HackmapChunksInitFromMapData anthropic/claude-opus-5-5:high: portalsOff + relocsOff locals together -> only frame 3800->3808 and the dlBase home 3788->3796 differ; with buf 0xE30 -> fdiff 0. Inlining boxesOff/vecsOff instead of shrinking buf: 437/356/364.
- same: typed index `((MapChunkCollEntry *)((s32)data + off + 4))[n]` (and `+ n`, `n + ptr`, swapped sums, `data + (off + 4)`, `off + data`) -> 9 (spilltemp slot order only); `MapChunkCollEntry *coll` local with buf 0xE2C -> 90; `(u8 *)data + off` spelling -> 356.
- same: 551532 removal 38 (s7/s8 swap only); 8 relocation-sum operand orders 42; portal pointer local 55; portal pointer walk 417; split dl0/dl1 loops 400; data instead of p in the first part 71-79.
- same: fc3dbd removal 76 (s2/s3 swap of p and lda gMapChunks); inverted if/else 92; early return 92; permuter 900 s on the fc3dbd removal (see ledger).
- same: 12a29f removal 360 (arg-register choice, then t-ring shift); variants scan floor 329.
## Untried ideas
- A natural use of data at portal-loop weight other than the dead compare (551532) (Q0563 priority 76 vs 69).
- A source statement that creates umpy(n,12) before data+off without a byte-offset local (512c53).
## Evidence
- Frame 0xED8: dlBase home sp+0xECC (3788); buf sp+0x78 (120); count sp+0x74; spilltemps sp+0x54 data+off+4, sp+0x58 data+off, sp+0x5C n*12 (stored +12 at 0x7b4-0x7b8).
- 0x140-0x184: cellsOff v1, boxesOff a0, vecsOff a1; `lui a0,%hi(gMapPortalSlotCount)` at 0x17c after the last a0 use; 0x18c collOff -> s4, 0x190 chunksOff -> s1, 0x198 portalsOff -> v1, 0x1c8 relocsOff -> a0.
- Portal loop 0x214-0x25c: -1 in s8, data in s7, data+base hoisted twice (t0, t3); gMapPortals reload (0x230-0x234) only on the dl0 store path.
- Chunk loop: lda gMapChunks s3, p s2, n s6, n*0x1C8 s1; plane loop lda gMapGridTrianglePlanes s2; else branch stores through s3 (0x8a8).
