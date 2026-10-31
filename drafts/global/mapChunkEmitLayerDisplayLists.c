// mapChunkEmitLayerDisplayLists (src/global/55B20.c): stage 6 (MapB): 10 diff lines (text 8), unchanged from prior best. Exhaustive grids over 12 GBI-store spellings per slot x fakes x shared/block _g x param gfx x 'entry' local (entry=&..[i] after node=D_807F70B0 reproduces addu a3; compare 'entry->unk0 == node->unk2' matches bnel t2,a0) + 2 random hill-climbs (60k compiles): remaining only 'lui a2' vs 'lui v0' for D_807F70B0 and E7 stores via sw zero,-4(s0) instead of move v1,s0. All-form-0 (WRITE_GFX(gfx++) everywhere) has the right E7/v1 shape but s0/s1/s2 rotated (gfx s2, _g s0, DE _g s1 vs target gfx s0, _g s1, DE _g s2): gfx needs higher coloring priority; no fake found. Parked NON_MATCHING in 55B20.c
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
    if (((MapChunkEffect *)D_807F6C18)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk2C));
            break;
        case 1:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk30));
            break;
        case 2:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk34));
            break;
        case 3:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((MapChunkEffect *)D_807F6C18)[arg1].unk50; i++) {
            if (((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = D_807F70B0;
            do {
                if (node->unk2 == ((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (D_807F70B0 == 0) {} // FAKE: rs
            if (node->unk18 == 0) {
                continue;
            }
            if ((((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk2 & (1 << arg2)) == 0) {
                continue;
            }
            WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk14[arg2]));
            { Gfx *_g = gfx; _g->words.w0 = (0xE7000000); _g->words.w1 = (u32)(0); gfx++; }
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2]));
            { Gfx *_g = gfx; _g->words.w0 = (0xE7000000); gfx++; _g->words.w1 = (u32)(0); }
        }
    }
    return (s32)gfx;
}
