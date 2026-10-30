// func_80656B98 (src/global/55B20.c): stage 6: 10 diff lines (text 8) via rs.py random dead statements (if (arg1 == 0.0f) {} right after gfx=arg0 => arg2 reloaded lbu 0x4b(sp), -1 in s8; if (D_807F70B0 == 0) {} before node->unk18 test) + per-site GBI macro form search (E7 write after DB06 as '_g=gfx; w0; w1; gfx++', last E7 as '_g=gfx; w0; gfx++; w1'). Remaining: 'lui a2' vs 'lui v0' for D_807F70B0 (caused by the fake), and loop E7 stores use sw zero,-4(s0) instead of move v1,s0; stores via v1. Earlier basin (form 0 everywhere, 37 diff) differs only by s0/s1/s2 rotation (gfx must be s0, _g s1, 3rd _g s2).
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x1];
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
} MapChunkEffectEntry;

// WRITE_GFX, MapChunkEffect, D_807F6C18, D_807F70B0, struct MapCell as in src/global/55B20.c
s32 func_80656B98(arg0, arg1, arg2)
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
