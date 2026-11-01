// mapChunkEmitLayerDisplayLists (src/global/55B20.c): leftovers5 MapA: stage 6 (parked NON_MATCHING), full=5 text=3 shape=2 (was 10): KEY = write the packets with the real GBI macros (gDPPipeSync(gfx++), gSPSegment(gfx++,6,x), gSPDisplayList(gfx++,x)) instead of WRITE_GFX words: the E7 'move v1,s0 / sw zero,4(v1) / sw s6,0(v1)' shape and the whole loop then match; gfx colouring fixed by deadsweep '{gfx = (Gfx *)((u32)gfx | 0);}' at the loop top (+1 gfx ref) and 'if (arg0 == 0) {}' (natural form of the old arg1==0.0f). Remaining: D_807F70B0 hi: target 'lui v0 ... lh a0,0(a3); lw v0,lo(v0)' (lui reg = node reg, lw after the hoisted lh) vs ours 'lui a2; lw v0,0(a2); lh a0' (87 = uilod D_807F70B0 CSE'd with the post-loop dead test gets a2; removing/moving/reforming the test, key-local orders, while/for/swap loop spellings, 231 dead-statement forms all >= 5).
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
            gfx = (Gfx *)((u32)gfx | 0);  // FAKE: extra gfx reference (raises its colouring priority above the packet pointers)
            if (((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = D_807F70B0;
            do {
                if (node->unk2 == ((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (D_807F70B0 == 0) {} // FAKE: rs
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
