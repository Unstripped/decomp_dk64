// mapChunkEmitLayerDisplayLists (src/global/55B20.c): Map55 r7: stage 5, unchanged full=2 (only 'lui a2,hi(D_807F70B0)' vs target 'lui v0' ; entry ptr a3 correct). uopt (non-leaf: all constrained, adjsave order): the FAKE makes the D_807F70B0 load a CSE candidate (86, adj 10.0) that ties the entry pointer (90, adj 10.0), takes a2 first and carries the hi reg; target has NO such candidate (lui v0; lw v0,lo(v0)) yet a2 is occupied by something code-less when 90 is coloured (a3). Without the FAKE the dead if's block count also changes arg2 (andi s8,a2,0xff; full 82). With FAKE removed + one ghost (gh = gMapChunks[arg1].unk4C tested after the node loop) lui v0 is right but 90 takes a2 (full 3). Tried (new): ghost grids (11 sources x all point pairs x 4 forms; 3-ref ghosts; 3 hill-climbs ~110k evals, ghost types s32/u8/s16/u32), dead-test pairs of 27 unrelated globals at all point pairs, neighbour-symbol spellings of the node load and of the FAKE, osVirtualToPhysical prototype is fixed by include/PR/os_convert.h. Untried: a source-level reason for a code-less a2 occupant (named entry local was tried by W3IntB).
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
