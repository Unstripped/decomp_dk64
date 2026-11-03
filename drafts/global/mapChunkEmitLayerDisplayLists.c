// mapChunkEmitLayerDisplayLists (src/global/55B20.c): W3IntB 2026-11-02: unchanged full=2 (shared hi const 'lui a2' vs target 'lui v0'). Tried: named 'entry' pointer local (the target's a3 = &arr[i] is a separate recomputation after the -1 check) in 162 variants (assign position x spelling x uses x with/without the D_807F70B0 dead test x node join): best 11 (it flips lh a0/lw v0 order and bnel operand order); ins2 (all single+top-40 pairs) and deletion-of-FAKE x single over D_807F70B0/gMapChunks/arg1/arg2/i/found/node/node fields; random-order pair search covering 26k of 103k pairs: none < 2.
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
