#include "common.h"
#include "actor.h"

typedef struct Act90A_Entry {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} Act90A_Entry;

extern Act90A_Entry D_807FC690[];

void func_8068C080(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        D_807FC690[i].unk6 = 0;
    }
}

void func_8066B434(s32, s32, s32);

void func_8068C0B4(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        Act90A_Entry *entry = &D_807FC690[i];

        if (entry->unk6 != 0) {
            entry->unk6--;
            if (entry->unk6 == 0) {
                func_8066B434(entry->unk0, 0x6A, 0x46);
            }
        }
    }
}

s32 func_8066B0F8(s32, s32, s32, s32);

s32 func_8068C12C(u16 arg0) {
    s16 i;
    Act90A_Entry *entry;

    for (i = 0; i < 0x20; i++) {
        entry = &D_807FC690[i];
        if (entry->unk4 == arg0 && entry->unk6 != 0) {
            entry->unk6 = 2;
            return entry->unk0;
        }
    }

    for (i = 0; i < 0x20; i++) {
        entry = &D_807FC690[i];
        if (entry->unk6 == 0) {
            entry->unk0 = func_8066B0F8(0xE, arg0, 0, 0);
            entry->unk6 = 2;
            entry->unk4 = arg0;
            return entry->unk0;
        }
    }

    D_807FC690[0].unk6 = 2;
    return D_807FC690[0].unk0;
}

typedef struct Act90A_Struct630 {
    /* 0x0 */ Gfx *(*func)(Gfx *, void *);
    /* 0x4 */ void *actor;
    /* 0x8 */ u8 layer;
} Act90A_Struct630;

extern u8 D_807501E0;
extern Act90A_Struct630 D_807FC630[];

Gfx *func_8068C20C(Gfx *glist, u8 arg1) {
    u8 count = D_807501E0;

    if (count != 0) {
        do {
            if (arg1 == D_807FC630[--count].layer) {
                gDPPipeSync(glist++);
                glist = D_807FC630[count].func(glist, D_807FC630[count].actor);
            }
        } while (count != 0);
    }
    if (arg1 == 7) {
        D_807501E0 = 0;
    }
    return glist;
}

void func_8068C2EC(void) {
    D_807501E0 = 0;
}

void func_8068C2F8(Actor *arg0) {
    u8 i;

    for (i = 0; i < D_807501E0; i++) {
        if (arg0 == (Actor *)D_807FC630[i].actor) {
            D_807FC630[i].layer = 8;
        }
    }
}

void func_8068C350(void *func, void *actor, u8 layer) {
    if (D_807501E0 < 8) {
        D_807FC630[D_807501E0].func = func;
        D_807FC630[D_807501E0].actor = actor;
        D_807FC630[D_807501E0].layer = layer;
        D_807501E0++;
    }
}

#define Act90A_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

void *func_80610FE8(s32);
void heapFreeDeferred(void *);
typedef f32 Act90A_MtxF[4][4];
void func_80612CA0(Act90A_MtxF, f32);
extern u32 D_807501E8;

Gfx *func_8068C3A0(Gfx *glist, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Act90A_MtxF spA0;
    Act90A_MtxF sp60;
    Mtx *mtx;
    s32 pad;
    mtx = func_80610FE8(sizeof(Mtx));
    heapFreeDeferred(mtx);

    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, (u8 *)(arg1 + 0x80000000), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);

    func_80612CA0(spA0, (f32)arg4);
    guTranslateF(sp60, (f32)arg2, (f32)arg3, 0.0f);
    guMtxCatF(spA0, sp60, spA0);
    guMtxF2L(spA0, mtx);

    Act90A_WRITE_GFX(glist++, 0xDA380000, (u32)mtx);
    Act90A_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(&D_807501E8));
    Act90A_WRITE_GFX(glist++, 0x06000204, 0x00000406);
    Act90A_WRITE_GFX(glist++, 0xD8380002, 0x00000040);
    gDPPipeSync(glist++);

    return glist;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C5A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068D264.s")

extern Gfx D_1000118;
extern Mtx D_2000080;
extern u32 D_8076A064;

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_8068D8C8(Gfx *arg0, s32 arg1) {
    Act90A_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Act90A_WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFA0);
    Act90A_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    Act90A_WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    Act90A_WRITE_GFX(arg0++, 0xDA380007, (u32)&D_2000080);
    return func_8068C5A8(arg0, (u16)((((D_8076A064 >> 1) & 0xF) + 0x8F)), 0, 2, 0x20, 0x20, 0x118, 0xD2, 1.0f, 1.0f, 0, 0.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068D9DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DAF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DBA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DC54.s")

#define Act90B_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Mtx D_20000C0;
extern s32 D_807FBB64;


typedef struct Act90B_Actor174 {
    u8 pad[0x34];
    u8 *unk34;
} Act90B_Actor174;

typedef struct Act90B_Actor {
    u8 pad[0xE6];
    s16 unkE6;
    u8 padE8[4];
    s16 unkEC;
    u8 padEE[0x174 - 0xEE];
    Act90B_Actor174 *unk174;
} Act90B_Actor;
#define Act90B_TEX ((((D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF)

Gfx *func_8068E474(Gfx *arg0, Act90B_Actor *arg1) {
    s16 unkEC = arg1->unkEC + 0x5A;

    Act90B_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Act90B_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
    Act90B_WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    Act90B_WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);

    if (D_807FBB64 & 0x80000) {
        s16 yaw = arg1->unkE6;
        Act90B_Actor174 *unk174 = arg1->unk174;
        if (yaw < 0x200 || yaw >= 0xE01 || (yaw >= 0x601 && yaw < 0xA00)) {
            if (*unk174->unk34 != 0x10 && *unk174->unk34 != 0x13) {
                arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x78, 0x1E0, 4.0f, 4.0f, 0, 0.0f);
                arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x488, 0x1E0, 4.0f, 4.0f, 0xB4, 0.0f);
            }
        } else {
            arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x280, 0x78, 4.0f, 4.0f, 0x5A, 0.0f);
            arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x280, 0x348, 4.0f, 4.0f, 0x10E, 0.0f);
        }
    } else {
        arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0xB4, 0xC8, 8.0f, 8.0f, unkEC, 0.0f);
    }

    return arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068E7B4.s")
