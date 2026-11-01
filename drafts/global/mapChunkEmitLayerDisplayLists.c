// mapChunkEmitLayerDisplayLists (src/global/55B20.c): stage 6 (MapB, MapC2 revisit): 10 diff lines. Root cause found: uopt colours by adjsave; gfx (cand 0) must outrank both DB/DE2 _g cands (15.0). With all-WRITE_GFX(gfx++) forms (right E7 'move v1,s0 / sw zero,4(v1)' shape, two v1 cands) gfx has adjsave 13.4 (colours after the _g's -> gfx s2, _g s0/s1, target gfx s0/_g s1/s2); the E7b/E7c explicit '{ _g = gfx; ...; gfx++; }' forms add +1 gfx ref per block (15.4, right rotation) but lose the v1 copy (sw zero,-4(s0)). Need +1.6 adjsave on gfx (2 extra gfx refs in loop blocks) keeping E7 'gfx++ before stores' shape: dead tests/self-assignments (if (gfx==0), gfx=gfx, gfx+=0, {Gfx *t=gfx;}) vanish before allocation; param-gfx, ANSI, Gfx* return (needs head decl s32->Gfx *), E7 spelling grid (8x8: only stores-before-gfx++ forms differ) all no change. Second independent issue: lui a2 vs lui v0 for D_807F70B0 + lw v0/lh a0 order.
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
    if (arg1 == 0.0f) {} // FAKE: rs
    WRITE_GFX(gfx++, 0xE7000000, 0);
    if (((MapChunkEffect *)gMapChunks)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk2C));
            break;
        case 1:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk30));
            break;
        case 2:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk34));
            break;
        case 3:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((MapChunkEffect *)gMapChunks)[arg1].unk50; i++) {
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
            WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk14[arg2]));
            { Gfx *_g = gfx; _g->words.w0 = (0xE7000000); _g->words.w1 = (u32)(0); gfx++; }
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2]));
            { Gfx *_g = gfx; _g->words.w0 = (0xE7000000); gfx++; _g->words.w1 = (u32)(0); }
        }
    }
    return (s32)gfx;
}
