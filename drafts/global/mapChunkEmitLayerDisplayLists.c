// mapChunkEmitLayerDisplayLists (src/global/55B20.c): Map55 r8: stage 6, count exact 186/186, full 2 (unchanged; park stays). Only diff: hi of D_807F70B0 is lui a2/lw v0,lo(a2) vs target lui v0/lw v0,lo(v0) (entry ptr a3 right). Cause: the FAKE if (D_807F70B0==0) after the node loop makes 86=uilod{D} a coloured candidate (a2) that blocks a2 so entry ptr 90 takes a3, but it also supplies the hi reg. Without it: lui v0 right but entry ptr a2 (score 3 with a dead test on ANY other global after the loop, e.g. D_8076A0B4; full 82 with no such test since -1 const hoist + arg2 s8 change). Tried (new): dead tests/pairs of 66 globals x 4 forms x all positions (9933 variants), neighbour-symbol spelling of the node load (D_807F70AC[1]) + test on D_807F70B0 (3), spelling variants of the test expr (*(&D), (s32)D, D->unk2: 2), first/ghost local copies (3-5), entry local pointer (84+), annealing over up to 6 dead tests (36 best), -1 compare tests. Needs a candidate coloured a2 live in the entry-ptr bb that emits no hi: none found.
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
