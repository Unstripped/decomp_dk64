#include "common.h"
#include "actor.h"

struct ActorTargetEntry;
struct ActorTargetDistanceEntry;

typedef struct RenderB67890_Quad {
    f32 unk0[8];
    s16 unk20[12];
    s16 pad38[4];
} RenderB67890_Quad;

typedef struct RenderB67890_Dist {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[4];
} RenderB67890_Dist;

typedef struct RenderB67890_Vtx {
    s16 ob[3];
    s16 flag;
    s16 tc[2];
    u8 cn[4];
} RenderB67890_Vtx;

extern struct ActorTargetEntry *D_807F93F0;
extern struct ActorTargetDistanceEntry *D_807F93F4;
extern s32 D_807F93F8;
extern RenderB67890_Vtx *D_807F93FC;
extern u32 D_807F9400;

void *func_80610FE8(s32);
s32 assetLoad(s32, s32, s32, s32);

#define RB_QUAD(i) (&((RenderB67890_Quad *)D_807F93F0)[i])
#define RB_VTX(off) ((RenderB67890_Vtx *)((u8 *)D_807F93FC + (off)))

void func_80662B90(void *arg0) {
    s32 j;
    s32 sp[3];
    s32 i;
    s32 vtx_off;
    u8 *p;

    p = arg0;
    sp[0] = 0;
    D_807F93F8 = *(s32 *)(p + *(s32 *)(p + 0x50));
    if (D_807F93F8 != 0) {
        D_807F93F0 = (struct ActorTargetEntry *)(p + *(s32 *)(p + 0x50) + 4);
        D_807F93F4 = func_80610FE8(D_807F93F8 * 0x14);
        D_807F93FC = func_80610FE8(D_807F93F8 << 6);
        i = 0;
        if (D_807F93F8 > 0) {
            vtx_off = sp[0] * 0x10;
            do {
                for (j = 0; j < 4; j++) {
                    RB_VTX(vtx_off)->ob[0] = RB_QUAD(i)->unk20[j];
                    RB_VTX(vtx_off)->ob[1] = RB_QUAD(i)->unk20[j + 4];
                    RB_VTX(vtx_off)->ob[2] = RB_QUAD(i)->unk20[j + 8];
                    RB_VTX(vtx_off)->tc[0] = (s32)(RB_QUAD(i)->unk0[j * 2] * 50.0f) << 5;
                    RB_VTX(vtx_off)->tc[1] = (s32)(RB_QUAD(i)->unk0[j * 2 + 1] * 50.0f) << 5;
                    vtx_off += 0x10;
                }

                ((RenderB67890_Dist *)D_807F93F4)[i].unk4 = (f32)((f64)(RB_QUAD(i)->unk20[0] + RB_QUAD(i)->unk20[1] + RB_QUAD(i)->unk20[2] + RB_QUAD(i)->unk20[3]) * 0.25);
                ((RenderB67890_Dist *)D_807F93F4)[i].unk8 = (f32)((f64)(RB_QUAD(i)->unk20[4] + RB_QUAD(i)->unk20[5] + RB_QUAD(i)->unk20[6] + RB_QUAD(i)->unk20[7]) * 0.25);
                ((RenderB67890_Dist *)D_807F93F4)[i].unkC = (f32)((f64)(RB_QUAD(i)->unk20[8] + RB_QUAD(i)->unk20[9] + RB_QUAD(i)->unk20[10] + RB_QUAD(i)->unk20[11]) * 0.25);
                i++;
            } while (i < D_807F93F8);
        }
        D_807F9400 = assetLoad(7, 0x3C7, 1, 0);
    }
}

typedef struct ActorTargetEntry {
    u8 pad0[0x38];
    s16 unk38;
    u8 pad3A[6];
} ActorTargetEntry;

extern ActorTargetEntry *D_807F93F0;

s32 actorTargetTableContainsId(s32 arg0) {
    s32 i;

    for (i = 0; i < D_807F93F8; i++) {
        if (arg0 == D_807F93F0[i].unk38) {
            return 1;
        }
    }
    return 0;
}

typedef struct ActorTargetQuadEntry {
    f32 unk0[8];
    s16 unk20[12];
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    u8 unk3E;
    u8 unk3F;
} ActorTargetQuadEntry;

typedef struct ActorTargetDistanceEntry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    s8 unk12;
    s8 unk13;
} ActorTargetDistanceEntry;

extern u8 *D_807F6C2C;
extern ActorTargetDistanceEntry *D_807F93F4;
f32 func_80611BB4(f32, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void actorCalculateTargetDistancesAndAngles(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    f32 ratio;
    f32 dist2d;
    s16 angle;
    f32 dz, dx;

    for (i = 0; i < D_807F93F8; i++) {
        D_807F93F4[i].unk11 = 0;
        if (D_807F6C2C[((ActorTargetQuadEntry *)D_807F93F0)[i].unk38] != 0) {
            D_807F93F4[i].unk0 = sqrtf((((arg0 - D_807F93F4[i].unk4) * (arg0 - D_807F93F4[i].unk4)) + ((arg1 - D_807F93F4[i].unk8) * (arg1 - D_807F93F4[i].unk8))) + ((arg2 - D_807F93F4[i].unkC) * (arg2 - D_807F93F4[i].unkC)));
            ratio = (D_807F93F4[i].unk0 - (f32)((ActorTargetQuadEntry *)D_807F93F0)[i].unk3A) / (f32)(((ActorTargetQuadEntry *)D_807F93F0)[i].unk3C - ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3A);
            if ((f64)ratio > 1.0) {
                D_807F93F4[i].unk10 = ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3F;
            } else if ((f64)ratio < 0.0) {
                D_807F93F4[i].unk10 = ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3E;
            } else {
                u8 e3E = ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3E;
                f32 fa = (u32)e3E;
                D_807F93F4[i].unk10 = (u8)(u32)(((f32)(((ActorTargetQuadEntry *)D_807F93F0)[i].unk3F - e3E) * ratio) + fa);
            }
            D_807F93F4[i].unk12 = (s32)((f64)mathAngleBetweenPoints2D(arg0, arg2, D_807F93F4[i].unk4, D_807F93F4[i].unkC) * 0.5) % 255;
            dz = arg2 - D_807F93F4[i].unkC;
            dx = arg0 - D_807F93F4[i].unk4;
            dist2d = sqrtf((dz * dz) + (dx * dx));
            angle = ((f64)func_80611BB4(D_807F93F4[i].unk8 - arg1, dist2d) * 2048.0) / 3.1415927410125732;
            D_807F93F4[i].unk13 = (s32)((f64)angle * 0.5) % 255;
            D_807F93F4[i].unk11 = 1;
        } else {
            D_807F93F4[i].unk11 = 0;
        }
    }
}

Gfx *func_80663594(Gfx *, s32);

Gfx *renderDepthSortedTargets(Gfx *arg0) {
    s32 pad;
    s32 var_s1;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fv1;
    s32 var_s0;
    s32 var_v0;

    var_fs0 = 100000000.0f;
    do {
        var_s0 = 0;
        var_fv1 = 0.0f;
        var_v0 = 0;
        if (D_807F93F8 > 0) {
            do {
                if (D_807F93F4[var_v0].unk11 != 0) {
                    temp_fv0 = D_807F93F4[var_v0].unk0;
                    if ((temp_fv0 < var_fs0) && (var_fv1 < temp_fv0)) {
                        var_s1 = var_v0;
                        var_fv1 = temp_fv0;
                        var_s0 = 1;
                    }
                }
                var_v0 += 1;
            } while (var_v0 < D_807F93F8);
        }
        var_fs0 = var_fv1;
        if (var_s0 != 0) {
            arg0 = func_80663594(arg0, var_s1);
        }
    } while (var_s0 != 0);
    return arg0;
}

typedef struct RenderB67890_TargetView {
    u8 pad0[0x10];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} RenderB67890_TargetView;

#define RB_TGT ((RenderB67890_TargetView *)D_807F93F4)

#define W(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *func_80663594(Gfx *glist, s32 arg1) {
    W(glist++, 0xE7000000, 0);
    W(glist++, 0xE200001C, 0x00504A50);
    W(glist++, 0xFC11FE23, 0xFFFFF7FB);
    W(glist++, 0xE3000A01, 0);
    W(glist++, 0xD9000000, 0);
    W(glist++, 0xD9FFFFFF, 0x00200005);
    gDPSetPrimColor(glist++, 0, 0, 100, 100, 100, RB_TGT[arg1].unk10);
    W(glist++, 0xD7000002, 0xFFFFFFFF);
    gDPLoadTextureBlock(glist++, D_807F9400, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    gDPSetTileSize(glist++, 0, RB_TGT[arg1].unk12, RB_TGT[arg1].unk13, 63 << 2, 63 << 2);
    gSPVertex(glist++, osVirtualToPhysical(&D_807F93FC[arg1 * 4]), 4, 0);
    W(glist++, 0x06000204, 0x00000406);
    W(glist++, 0xE7000000, 0);
    return glist;
}
