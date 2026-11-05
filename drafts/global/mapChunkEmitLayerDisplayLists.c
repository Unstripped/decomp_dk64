// mapChunkEmitLayerDisplayLists (src/global/55B20.c): ForbidSet revisit 9: stage 6 park, 176/176 insns, frame 0x40 ok, full=2 text=2 reloc=0 shape=0. Closest diff: lui a2/lw v0,lo(a2) vs target lui v0/lw v0,lo(v0) for D_807F70B0. Proved uopt assign order: cand 84 node->v0, cand 81 found->v1, cand 91 unk0->a0, cand 74 unk4C->a1. Target has a2 occupied/forbidden so cand 90 (&entries[i]) takes a3. Tested FAKE-removal, alternate dead tests, and s32 arg2.
s32 mapChunkEmitLayerDisplayLists(arg0, arg1, arg2)
u32 *arg0;
s32 arg1;
u8 arg2;
{
    MapChunkEffectEntry *entry;
    struct MapCell *node;
    Gfx *gfx;
    s32 i;
    s32 found;

    gfx = (Gfx *)arg0;
    if (arg0 == 0) {} // FAKE: rs
    gDPPipeSync(gfx++);
    if (((MapChunkEffect *)gMapChunks)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk2C));
            break;
        case 1:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk30));
            break;
        case 2:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk34));
            break;
        case 3:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((MapChunkEffect *)gMapChunks)[arg1].unk50; i++) {
            gfx = (Gfx *)((u32)gfx | 0); // FAKE: extra gfx reference (raises its colouring priority above the packet pointers)
            if (((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = (struct MapCell *)D_807F70B0; do { // LAYOUT: joined onto the do line (keeps lh a0 before lw v0)
                if (node->unk2 == ((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (D_807F70B0 == 0) {} // FAKE: shares the node load's hi constant; that candidate takes a2 ahead of the entry pointer (target a3)
            if (node->unk18 == 0) {
                continue;
            }
            if ((((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk2 & (1 << arg2)) == 0) {
                continue;
            }
            gSPSegment(gfx++, 6, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk14[arg2]));
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2]));
            gDPPipeSync(gfx++);
        }
    }
    return (s32)gfx;
}
