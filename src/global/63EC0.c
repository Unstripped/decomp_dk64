#include "common.h"
#include "actor.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

typedef struct EffectSubNode {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x10];
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0xC];
    union {
        struct {
            u8 pad50[0x14];
            u8 val;
            u8 pad65;
        };
        s16 unk50[11];
    };
    u8 unk66;
    u8 unk67;
} EffectSubNode;

typedef struct EffectNode {
    union {
        EffectSubNode *sub;
        EffectSubNode *target;
        EffectSubNode *unk0;
    };
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    void *dl[2];
    void *vtx[2];
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    u8 pad48[2];
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 pad4D[3];
    struct EffectNode *next;
} EffectNode;

typedef struct EffectTableEntry {
    void (*fn0)();
    void (*fn1)();
    void (*fn2)(EffectNode *);
    void *res0;
    void *res1;
    union {
        u32 flags;
        struct {
            u8 pad14[2];
            u8 unk16;
            u8 pad17;
        };
    };
} EffectTableEntry;

typedef struct TextureCacheEntry {
    void *unk0;
    u8 pad4[0x14];
} TextureCacheEntry;

typedef struct EffectTableFlags {
    u8 unk0;
    u8 pad1[0x17];
} EffectTableFlags;

typedef struct EffectBufferEntry {
    u8 unk0;
    u8 pad1[0x1C7];
} EffectBufferEntry;

void *func_8066B0F8(s32, s32, s32, s32);
void func_8065F4F4(EffectNode *);
void func_806615BC(void);
Gfx *func_8065FEB8(Gfx *, EffectNode *);
void func_80660070(void *, void *, EffectNode *);
Gfx *func_80661F0C(Gfx *, s32, u8);

extern EffectNode *D_807F93C0;
extern EffectTableEntry D_80748A90[];
extern TextureCacheEntry D_80748A9C[];
extern EffectTableFlags D_80748AA5[];
extern EffectBufferEntry *D_807F6C18;
extern s32 D_807FBB60;
extern u8 D_807444FC;
extern u8 D_807F93C4;
extern f32 D_807F93C8[2];
extern f32 D_807F93D0;
extern f32 D_807F93D4;
extern f32 D_807F93D8;
extern f32 D_807F93DC;
extern f32 D_807F93E0;
extern f32 D_807F93E4;
extern f32 D_807F93E8;

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F1C0.s")

void func_8065F49C(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    EffectNode *node = D_807F93C0;

    if (node != NULL && arg0 != 0) {
        do {
            node = node->next;
            arg0--;
            if (node == NULL) {
                break;
            }
        } while (arg0 != 0);
    }
    if (node != NULL) {
        node->x = arg1;
        node->y = arg2;
        node->z = arg3;
    }
}

void func_8065F4F4(EffectNode *arg0) {
    if (arg0->target->unkC < arg0->x) {
        arg0->target->unkC += arg0->z;
        if (arg0->x < arg0->target->unkC) {
            arg0->target->unkC = arg0->x;
        }
    } else {
        arg0->target->unkC -= arg0->z;
        if (arg0->target->unkC < arg0->x) {
            arg0->target->unkC = arg0->x;
        }
    }

    if (arg0->target->unk10 < arg0->y) {
        arg0->target->unk10 += arg0->z;
        if (arg0->y < arg0->target->unk10) {
            arg0->target->unk10 = arg0->y;
        }
    } else {
        arg0->target->unk10 -= arg0->z;
        if (arg0->target->unk10 < arg0->y) {
            arg0->target->unk10 = arg0->y;
        }
    }
}

u8 func_8065F5F0(EffectNode *arg0) {
    return D_80748AA5[arg0->target->unk66].unk0;
}

void func_8065F614(void) {
    EffectNode *node = D_807F93C0;

    if (node != NULL) {
        do {
            node->unk4C = 0;
            func_8065F4F4(node);
            node = node->next;
        } while (node != NULL);
    }
    if (!(D_807FBB60 & 2)) {
        func_806615BC();
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F678.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F964.s")

s32 func_8065FB04(EffectSubNode *arg0) {
    s32 i;

    for (i = 0; i < arg0->unk67; i++) {
        if (D_807F6C18[arg0->unk50[i]].unk0 == 1) {
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065FB64.s")

Gfx *func_8065FD88(Gfx *gdl, u8 arg1, u8 arg2) {
    EffectNode *water;

    water = D_807F93C0;
    while (water != NULL) {
        if ((water->unk4C & 1) && (arg2 == D_80748A90[water->unk0->unk66].unk16)) {
            gdl = func_8065FEB8(gdl, water);
            gSPDisplayList(gdl++, osVirtualToPhysical(water->vtx[D_807444FC]));
            if (!(water->unk4C & 4)) {
                func_80660070(water->vtx[D_807444FC], water->dl[D_807444FC], water);
                water->unk4C |= 4;
            }
        }
        water = water->next;
    }
    return gdl;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065FEB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660070.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660520.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806608FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660D38.s")

s32 func_8066104C(s32 arg0) {
    return ~arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661054.s")

void func_80661264(s32 arg0, u8 arg1) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->sub->val = arg1;
    }
}

void func_806612B4(s32 arg0, u8 arg1) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk4A = arg1;
    }
}

u8 func_80661300(s32 arg0) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        return node->unk4B;
    }
    return 0;
}

void func_8066134C(s32 arg0, u8 arg1) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk4B = arg1;
    }
}

void func_80661398(s32 arg0, f32 arg1, f32 arg2) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk8 = arg1;
        node->unkC = arg2;
    }
}

void func_806613E8(s32 arg0, f32 arg1, f32 arg2) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk8 += arg1;
        node->unkC = arg2;
    }
}

void func_80661440(f32 *arg0) {
    EffectNode *node = D_807F93C0;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        arg0[i] = node->unk8;
        node = node->next;
    }
}

void func_80661484(f32 *arg0) {
    EffectNode *node = D_807F93C0;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        node->unk8 = arg0[i];
        node->unk4 = node->unk8;
        node = node->next;
    }
}

f32 func_806614D0(s32 arg0) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        return node->unk4;
    }
    return 0.0f;
}

void func_80661520(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    if (D_807F93C4 == 0) {
        D_807F93C8[0] = arg0;
        D_807F93C8[1] = arg1;
        D_807F93D4 = 0.0f;
        D_807F93D0 = arg2;
        D_807F93D8 = arg3;
        D_807F93DC = 0.0f;
        D_807F93E0 = arg4;
        D_807F93E4 = arg5;
        D_807F93E8 = (arg5 * 2) / 3.0f;
        D_807F93C4 = 1;
    }
}

void func_806615BC(void) {
    if (D_807F93C4 != 0) {
        D_807F93D4 += D_807F93D8;
        if (D_807F93D0 < D_807F93D4) {
            D_807F93D4 = D_807F93D0;
        }
        D_807F93DC += D_807F93E0;
        if (D_807F93E4 < D_807F93DC) {
            D_807F93C4 = 0;
        }
    }
}

void func_8066164C(void) {
    D_807F93C4 = 0;
}

void func_80661658(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(7, 0x3C5, 1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806616A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806618A0.s")

void func_80661AB4(EffectNode *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->sub->unk40 -= arg0->sub->unk38;
    if (arg0->sub->unk40 < 0.0) {
        arg0->sub->unk40 = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}

void func_80661B84(u8 arg0) {
    D_80748A90[arg0].res0 = func_8066B0F8(0x19, 0x2EE, 1, 0);
    D_80748A90[arg0].res1 = func_8066B0F8(0x19, 0x2EF, 1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80661BF0.s")

void func_80661E34(EffectNode *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}

void func_80661EC4(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(0x19, 0xF0, 1, 0);
}

Gfx *func_80661F0C(Gfx *glist, s32 arg1, u8 arg2) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[arg2].unk0);
    WRITE_GFX(glist++, 0xF5100000, 0x07000000);
    WRITE_GFX(glist++, 0xE6000000, 0);
    WRITE_GFX(glist++, 0xF3000000, 0x0754F000);
    WRITE_GFX(glist++, 0xF5101000, 0x00014050);
    WRITE_GFX(glist++, 0xF2002002, 0x0007E07E);
    WRITE_GFX(glist++, 0xF5100900, 0x01010441);
    WRITE_GFX(glist++, 0xF2002002, 0x0103E03E);
    WRITE_GFX(glist++, 0xF5100540, 0x0200C832);
    WRITE_GFX(glist++, 0xF2002002, 0x0201E01E);
    WRITE_GFX(glist++, 0xF5100350, 0x03008C23);
    WRITE_GFX(glist++, 0xF2002002, 0x0300E00E);
    WRITE_GFX(glist++, 0xFC26A004, 0x1F1093FF);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7001802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C192230);
    return glist;
}

void func_80662108(s32 arg0) {
}

void func_80662110(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(0x19, 0xAF4, 1, 0);
}

void func_80662158(Gfx *arg0, s32 arg1, u8 arg2) {
    func_80661F0C(arg0, arg1, arg2);
}

void func_80662180(s32 arg0) {
}

void func_80662188(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(0x19, 0x75C, 1, 0);
}

Gfx *func_806621D0(Gfx *glist, s32 arg1, u8 arg2) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[arg2].unk0);
    WRITE_GFX(glist++, 0xF5100000, 0x07000000);
    WRITE_GFX(glist++, 0xE6000000, 0);
    WRITE_GFX(glist++, 0xF3000000, 0x0754F000);
    WRITE_GFX(glist++, 0xF5101000, 0x00014050);
    WRITE_GFX(glist++, 0xF2002002, 0x0007E07E);
    WRITE_GFX(glist++, 0xF5100900, 0x01010441);
    WRITE_GFX(glist++, 0xF2002002, 0x0103E03E);
    WRITE_GFX(glist++, 0xF5100540, 0x0200C832);
    WRITE_GFX(glist++, 0xF2002002, 0x0201E01E);
    WRITE_GFX(glist++, 0xF5100350, 0x03008C23);
    WRITE_GFX(glist++, 0xF2002002, 0x0300E00E);
    WRITE_GFX(glist++, 0xFC26A004, 0x1F1093FF);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7001802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C192230);
    return glist;
}

void func_806623CC(s32 arg0) {
}

void func_806623D4(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(7, 0x3B9, 1, 0);
}

Gfx *func_8066241C(Gfx *glist, EffectSubNode **arg1, u8 arg2) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[arg2].unk0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*arg1)->unk3C & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void func_806625D0(u8 arg0) {
    D_80748A9C[arg0].unk0 = func_8066B0F8(7, 0x3D2, 1, 0);
}

Gfx *func_80662618(Gfx *glist, EffectSubNode **arg1, u8 arg2) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[arg2].unk0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*arg1)->unk3C & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void func_806627CC(u8 arg0) {
    D_80748A90[arg0].res0 = func_8066B0F8(7, 0x3BA, 1, 0);
    D_80748A90[arg0].res1 = func_8066B0F8(7, 0x3DB, 1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80662838.s")

void func_80662AB4(EffectNode *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->sub->unk40 -= arg0->sub->unk38;
    if (arg0->sub->unk40 < 0.0) {
        arg0->sub->unk40 = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}
