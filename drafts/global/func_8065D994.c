// func_8065D994 (src/global/61AA0.c): s4/s5 inversion in loop 2 and prologue resolved by (D_807F7F10 + i) for temp_s5, loop 1 remaining: entry in v0 vs s1
#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    void *unk8;
} R1A_Struct807F8E90;
extern R1A_Struct807F8E90 D_807F8E90[4];

typedef struct {
    u8 pad0[0x100];
    u16 unk100;
    u8 unk102;
    u8 unk103;
    u8 unk104;
    u8 unk105;
    u8 unk106;
    s8 unk107;
} R6B_Struct807F7F10;

extern R6B_Struct807F7F10 D_807F7F10[];
extern u8 D_807F8E88;
extern u8 D_807444FC;

#define R6B_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *func_8065D994(Gfx *gdl, s16 arg1) {
    s32 i;
    s32 var_t2;
    s32 var_s6;
    s32 found;
    R6B_Struct807F7F10 *entry;
    s32 temp_a1;

    i = 0;
    var_t2 = 0;
    var_s6 = 1;
    found = 0;
    while (i < D_807F8E88 && found == 0) {
        entry = &D_807F7F10[i];
        if (arg1 == entry->unk107) {
            found = 1;
        }
        i++;
    }
    if (found == 0) {
        return gdl;
    }

    R6B_WRITE_GFX(gdl++, 0xE7000000, 0);
    R6B_WRITE_GFX(gdl++, 0xE200001C, 0x00504DD8);
    R6B_WRITE_GFX(gdl++, 0xD9000000, 0);
    R6B_WRITE_GFX(gdl++, 0xD9FFFFFF, 0x00200405);
    R6B_WRITE_GFX(gdl++, 0xE3000A01, 0);
    R6B_WRITE_GFX(gdl++, 0xD7000002, 0xFFFFFFFF);
    R6B_WRITE_GFX(gdl++, 0xFC119623, 0xFF2FFFFF);

    i = 0;
    if (D_807F8E88 > 0) {
        entry = D_807F7F10;
        do {
            if (arg1 == entry->unk107) {
                u8 *temp_s5;

                R6B_WRITE_GFX(gdl++, 0xE7000000, 0);
                temp_s5 = (u8 *)(D_807F7F10 + i);
                if (var_s6 != 0) {
                    if (entry->unk100 & 1) {
                        R6B_WRITE_GFX(gdl++, 0xE200001C, 0x00504240);
                        var_s6 = 0;
                    }
                }
                if (var_s6 == 0) {
                    if (!(entry->unk100 & 1)) {
                        R6B_WRITE_GFX(gdl++, 0xE200001C, 0x00504DD8);
                        var_s6 = 1;
                    }
                }
                R6B_WRITE_GFX(gdl++, 0xFA000000, entry->unk106);
                temp_a1 = (s32)D_807F8E90[entry->unk102].unk8;
                if (temp_a1 != var_t2) {
                    var_t2 = temp_a1;
                    switch (entry->unk105) {
                    case 0:
                        gDPLoadTextureBlock_4b(
                            gdl++,
                            (u8 *)temp_a1 + 0x80000000,
                            G_IM_FMT_IA,
                            entry->unk103,
                            entry->unk104,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            0,
                            0,
                            0,
                            0
                        );
                        break;
                    case 1:
                        gDPLoadTextureBlock(
                            gdl++,
                            (u8 *)D_807F8E90[entry->unk102].unk8 + 0x80000000,
                            G_IM_FMT_IA,
                            G_IM_SIZ_8b,
                            entry->unk103,
                            entry->unk104,
                            0,
                            G_TX_CLAMP,
                            G_TX_CLAMP,
                            0,
                            0,
                            0,
                            0
                        );
                        break;
                    }
                }
                R6B_WRITE_GFX(gdl++, 0xDA380000, osVirtualToPhysical(temp_s5 + (D_807444FC << 6)));
                R6B_WRITE_GFX(gdl++, 0x01004008, osVirtualToPhysical(temp_s5 + (D_807444FC << 6) + 0x80));
                R6B_WRITE_GFX(gdl++, 0x06000602, 0x00000406);
                R6B_WRITE_GFX(gdl++, 0xD8380002, 0x00000040);
            }
            i++;
            entry++;
        } while (i < D_807F8E88);
    }
    R6B_WRITE_GFX(gdl++, 0xE7000000, 0);
    return gdl;
}
