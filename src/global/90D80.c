#include "common.h"
#include "actor.h"

typedef struct TexCacheEntry {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} TexCacheEntry;

extern TexCacheEntry D_807FC690[];

void texCacheReset(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        D_807FC690[i].unk6 = 0;
    }
}

void assetFreeBuffer(s32, s32, s32);

void texCacheUpdate(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        TexCacheEntry *entry = &D_807FC690[i];

        if (entry->unk6 != 0) {
            entry->unk6--;
            if (entry->unk6 == 0) {
                assetFreeBuffer(entry->unk0, 0x6A, 0x46);
            }
        }
    }
}

s32 assetLoad(s32, s32, s32, s32);

s32 texCacheFindOrLoad(u16 arg0) {
    s16 i;
    TexCacheEntry *entry;

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
            entry->unk0 = assetLoad(0xE, arg0, 0, 0);
            entry->unk6 = 2;
            entry->unk4 = arg0;
            return entry->unk0;
        }
    }

    D_807FC690[0].unk6 = 2;
    return D_807FC690[0].unk0;
}

typedef struct RenderCallbackEntry {
    /* 0x0 */ Gfx *(*func)(Gfx *, void *);
    /* 0x4 */ void *actor;
    /* 0x8 */ u8 layer;
} RenderCallbackEntry;

extern u8 D_807501E0;
extern RenderCallbackEntry D_807FC630[];

Gfx *renderCallbacksExecute(Gfx *glist, u8 arg1) {
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

void renderCallbacksReset(void) {
    D_807501E0 = 0;
}

void renderCallbacksDisableForActor(Actor *arg0) {
    u8 i;

    for (i = 0; i < D_807501E0; i++) {
        if (arg0 == (Actor *)D_807FC630[i].actor) {
            D_807FC630[i].layer = 8;
        }
    }
}

void renderCallbacksRegister(void *func, void *actor, u8 layer) {
    if (D_807501E0 < 8) {
        D_807FC630[D_807501E0].func = func;
        D_807FC630[D_807501E0].actor = actor;
        D_807FC630[D_807501E0].layer = layer;
        D_807501E0++;
    }
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

void *func_80610FE8(s32);
void heapFreeDeferred(void *);
typedef f32 RenderMtxF[4][4];
void matrixMakeRotationZ(RenderMtxF, f32);
extern u32 D_807501E8;

Gfx *renderRotatedQuad(Gfx *glist, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    RenderMtxF spA0;
    RenderMtxF sp60;
    Mtx *mtx;
    s32 pad;
    mtx = func_80610FE8(sizeof(Mtx));
    heapFreeDeferred(mtx);

    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, (u8 *)(arg1 + 0x80000000), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);

    matrixMakeRotationZ(spA0, (f32)arg4);
    guTranslateF(sp60, (f32)arg2, (f32)arg3, 0.0f);
    guMtxCatF(spA0, sp60, spA0);
    guMtxF2L(spA0, mtx);

    WRITE_GFX(glist++, 0xDA380000, (u32)mtx);
    WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(&D_807501E8));
    WRITE_GFX(glist++, 0x06000204, 0x00000406);
    WRITE_GFX(glist++, 0xD8380002, 0x00000040);
    gDPPipeSync(glist++);

    return glist;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C5A8.s")

typedef struct KaG_Player {
    u8 pad[0x270];
    s16 rect[4];
} KaG_Player;
extern KaG_Player *D_807FC924;
extern u32 D_80744478;
extern f32 D_8075022C, D_80750228;
extern u32 D_80750230;
extern s32 D_8076A0A8;
extern Mtx D_2000080;
extern Mtx D_2000180;

Gfx *func_8068D264(Gfx *glist, f32 *arg1) {
    s32 sp84;
    f32 sp80;
    f32 sp7C;

    sp80 = *arg1;
    sp7C = D_80744478 * 0.5;
    sp84 = assetLoad(0x19, 0x173C, 1, 0);
    assetFreeBuffer(sp84, 0x1B2, 0x46);

    gDPPipeSync(glist++);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_807FC924->rect[0], D_807FC924->rect[1], D_807FC924->rect[2], D_807FC924->rect[3]);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xE3000F00, 0x10000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200004);
    WRITE_GFX(glist++, 0xD7000002, -1);
    WRITE_GFX(glist++, 0xE200001C, 0x00504340);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (D_8076A0A8 == 0x26) {
        gDPSetPrimColor(glist++, 0, 0, 0x8A, 0x52, 0x16, 200.0f * sp80);
    } else {
        gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 35.0f * sp80);
    }

    gDPLoadTextureBlock(glist++, (u8 *)(sp84 + 0x80000000), G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);

    gDPSetTileSize(glist++, 0, (s32)D_8075022C, (s32)D_80750228, 63 << 2, 63 << 2);
    gDPSetTile(glist++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 1, 0, G_TX_WRAP, 6, 0, G_TX_WRAP, 6, 0);

    WRITE_GFX(glist++, 0xDA380007, (u32)&D_2000080);
    if (D_80744478 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    WRITE_GFX(glist++, 0xDA380003, (u32)&D_2000180);
    WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(&D_80750230));
    WRITE_GFX(glist++, 0x06000204, 0x00000406);
    gDPPipeSync(glist++);

    if (D_8076A0A8 == 0x26) {
        f64 temp = sp7C;
        D_80750228 -= 2.0 * temp;
        D_8075022C -= 14.0 * temp;
    } else {
        f64 temp = sp7C;
        D_80750228 -= temp;
        D_8075022C -= 0.5 * temp;
    }

    if (D_80750228 < 0.0) {
        D_80750228 = 255.0f;
    }
    if (D_8075022C < 0.0) {
        D_8075022C = 255.0f;
    }

    return glist;
}

extern Gfx D_1000118;
extern u32 D_8076A064;

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *renderBonusTargetMarker(Gfx *arg0, s32 arg1) {
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFA0);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_2000080);
    return func_8068C5A8(arg0, (u16)((((D_8076A064 >> 1) & 0xF) + 0x8F)), 0, 2, 0x20, 0x20, 0x118, 0xD2, 1.0f, 1.0f, 0, 0.0f);
}

Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32);
int _sprintf();

typedef struct KaG_Countdown {
    u64 last;
    s64 duration;
    s64 left;
    s64 fired;
} KaG_Countdown;

Gfx *func_8068D9DC(Gfx *arg0, KaG_Countdown *arg1) {
    char sp3C[12];
    char sp38[4];

    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFF96);
    _sprintf(sp3C, "%d", (s32)arg1->left);
    arg0 = textDrawStringVtx(textDrawStringVtx(arg0, 3, 0x424, 0x50, sp3C, 1), 1, 0x50, 0x50, "HIT", 1);
    _sprintf(sp38, "%d", (s32)arg1->fired);
    return textDrawStringVtx(arg0, 3, 0x50, 0xB0, sp38, 1);
}

Gfx *func_8068DAF4(Gfx *arg0, u8 *arg1) {
    char sp38[8];

    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFF96);
    _sprintf(sp38, "%d", *arg1);
    return textDrawStringVtx(arg0, 3, 0x104, 0x50, sp38, 1);
}

Gfx *func_8068DBA4(Gfx *arg0, KaG_Countdown *arg1) {
    char sp34[12];

    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFF96);
    _sprintf(sp34, "%d", (s32)arg1->left);
    return textDrawStringVtx(arg0, 3, 0x370, 0x50, sp34, 1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DC54.s")


extern Mtx D_20000C0;
extern s32 D_807FBB64;


typedef struct ActorEffect174 {
    u8 pad[0x34];
    u8 *unk34;
} ActorEffect174;

typedef struct ActorEffect {
    u8 pad[0xE6];
    s16 unkE6;
    u8 padE8[4];
    s16 unkEC;
    u8 padEE[0x174 - 0xEE];
    ActorEffect174 *unk174;
} ActorEffect;
#define ANIM_TEX ((((D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF)

Gfx *actorDrawAnimatedEffect(Gfx *arg0, ActorEffect *arg1) {
    s16 unkEC = arg1->unkEC + 0x5A;

    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);

    if (D_807FBB64 & 0x80000) {
        s16 yaw = arg1->unkE6;
        ActorEffect174 *unk174 = arg1->unk174;
        if (yaw < 0x200 || yaw >= 0xE01 || (yaw >= 0x601 && yaw < 0xA00)) {
            if (*unk174->unk34 != 0x10 && *unk174->unk34 != 0x13) {
                arg0 = func_8068C5A8(arg0, ANIM_TEX, 0, 2, 0x20, 0x10, 0x78, 0x1E0, 4.0f, 4.0f, 0, 0.0f);
                arg0 = func_8068C5A8(arg0, ANIM_TEX, 0, 2, 0x20, 0x10, 0x488, 0x1E0, 4.0f, 4.0f, 0xB4, 0.0f);
            }
        } else {
            arg0 = func_8068C5A8(arg0, ANIM_TEX, 0, 2, 0x20, 0x10, 0x280, 0x78, 4.0f, 4.0f, 0x5A, 0.0f);
            arg0 = func_8068C5A8(arg0, ANIM_TEX, 0, 2, 0x20, 0x10, 0x280, 0x348, 4.0f, 4.0f, 0x10E, 0.0f);
        }
    } else {
        arg0 = func_8068C5A8(arg0, ANIM_TEX, 0, 2, 0x20, 0x10, 0xB4, 0xC8, 8.0f, 8.0f, unkEC, 0.0f);
    }

    return arg0;
}

s32 textGetStringWidth(s32, char *);
u32 textGetFontHeight(s32);

Gfx *func_8068E7B4(Gfx *arg0, f32 arg1, f32 arg2, s32 arg3) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    char sp3C[16];
    s16 sp2E;
    s32 sp30;

    sp50 = arg2 - ((f32)(u32)textGetFontHeight(0x86) * 0.5f);
    _sprintf(sp3C, ":");
    sp4C = (f32)textGetStringWidth(6, sp3C) * 0.5f;
    sp30 = arg3 / 60;
    sp54 = arg1 - sp4C;
    sp2E = (s16)(s32)(sp50 * 4.0f);
    arg0 = textDrawStringVtx(arg0, 6, (s16)(s32)(sp54 * 4.0f), sp2E, sp3C, 1);
    sp30 = arg3 / 60;
    _sprintf(sp3C, "%2d", sp30);
    sp54 = sp54 - (f32)textGetStringWidth(0x86, sp3C);
    arg0 = textDrawStringVtx(arg0, 0x86, (s16)(s32)(sp54 * 4.0f), sp2E, sp3C, 1);
    _sprintf(sp3C, "%02d", arg3 - sp30 * 60);
    return textDrawStringVtx(arg0, 0x86, (s16)(s32)((arg1 + sp4C) * 4.0f), sp2E, sp3C, 1);
}
