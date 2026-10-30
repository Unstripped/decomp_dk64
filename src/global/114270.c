#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern void *D_807FC924;
extern s32 D_8076A0A8;
extern u8 D_80755314;
extern u8 D_80755318;

extern u16 *D_807550E0;
extern u8 D_807FDA1A;
extern u8 D_807FDA1C;
extern u8 D_807FDA28;
extern u8 D_807FDA30;

void func_8070F570(void) {
    s16 i;

    *D_807550E0 = 0;
    D_807FDA1C = 6;
    for (i = 0; i < 0x80; i++) {
        (&D_807FDA30)[i] = i;
    }
    D_807FDA1A = 0x7F;
    D_807FDA28 = 0;
}

typedef struct AngAPlayer {
    u8 unk0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
    u8 unk228[0x9C];
    f32 unk2C4;
    s16 unk2C8;
} AngAPlayer;

#define ANGA_PLAYER ((AngAPlayer *)D_807FC924)

s32 randomNonNegative(void);

typedef struct AngASpawnView {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    s16 unk22;
    u8 pad24[4];
    f32 unk28;
    u8 pad2C[0x84];
    u8 unkB0;
    u8 unkB1;
    u8 unkB2;
    u8 unkB3;
    u8 padB4[4];
} AngASpawnView;

typedef struct AngASpawnPool {
    u16 count;
    u8 pad2[2];
    AngASpawnView *entries;
} AngASpawnPool;

typedef struct AngATextureSetup {
    u8 count;
    u8 type;
    u8 pad2[2];
    u16 *images;
    u8 pad8[2];
    u8 width;
    u8 height;
    s32 unkC;
    s32 unk10;
} AngATextureSetup;

extern u8 D_80755264;
extern u32 D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;
extern s32 D_807FDA20;
extern s32 D_807FDA24;
void *heapAlloc(s32);
void heapClearBlock(void *);
void *assetLoad(s32, s32, s32, s32);

#define ANGA_SETUP ((AngATextureSetup *)(&D_80755264 + arg0 * 0x14))
#define ANGA_POP_SLOT(out) \
    out = (&D_807FDA30)[D_807FDA1A]; (&D_807FDA30)[D_807FDA1A] = 0xFF; D_807FDA1A--
#define ANGA_POOL ((AngASpawnPool *)D_807550E0)

void func_8070F5CC(u8 arg0, s16 arg1, f32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    AngASpawnView *entry;
    s16 i;
    s32 idx;

    if (ANGA_POOL->count >= 0x80) {
        return;
    }
    if (ANGA_POOL->count == 0 && D_807FDA28 == 0) {
        ANGA_POOL->entries = heapAlloc(0x5C00);
        heapClearBlock(ANGA_POOL->entries);
        D_807FDA1C = arg0;
        for (i = 0; i < ANGA_SETUP->count; i++) {
            D_807FD9F0[i] = (u32)assetLoad(ANGA_SETUP->type != 0 ? 0x19 : 7, ANGA_SETUP->images[i], 1, 1);
        }
        D_807FDA18 = ANGA_SETUP->width;
        D_807FDA19 = ANGA_SETUP->height;
        D_807FDA20 = ANGA_SETUP->unkC;
        D_807FDA24 = ANGA_SETUP->unk10;
        D_807FDA28 = 1;
    }
    ANGA_POP_SLOT(idx);
    entry = &ANGA_POOL->entries[idx];
    entry->unkB0 = 1;
    entry->unk4 = (f32)arg3;
    entry->unk8 = (f32)arg3;
    entry->unkC = (f32)(s16)arg4;
    entry->unk10 = arg2;
    entry->unk0 = arg1;
    entry->unkB1 = *(u8 *)((u8 *)&arg5 + 3); // FAKE: lbu of the narrow arg5 home; the shared prototype passes s32
    entry->unk14 = ANGA_PLAYER->unk2C4;
    entry->unk18 = ANGA_PLAYER->unk210;
    entry->unk1C = ANGA_PLAYER->unk218;
    entry->unk20 = (randomNonNegative() >> 15) % 32767 % 0xFFF;
    entry->unk22 = (randomNonNegative() >> 15) % 32767 % 360;
    switch (D_807FDA1C) {
    case 3:
        entry->unk28 = (randomNonNegative() >> 15) % 32767 % 100 * 0.02;
        break;
    case 4:
    case 5:
        entry->unk20 = (randomNonNegative() >> 15) % 20 + 5;
        entry->unk28 = (randomNonNegative() >> 15) % 70 + 30;
        entry->unk22 = 0;
        if ((randomNonNegative() >> 15) % 100 > 80) {
            entry->unkB3 = 200;
        } else {
            entry->unkB3 = (randomNonNegative() >> 15) % 32767 % 6 + 5;
        }
        break;
    default:
        entry->unk28 = (randomNonNegative() >> 15) % 32767 % 100 * 0.1;
        break;
    }
    ANGA_POOL->count++;
}
#undef ANGA_POOL
#undef ANGA_SETUP
#undef ANGA_POP_SLOT

struct M114aAngle;

typedef struct AngAAngle {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} AngAAngle;

extern s16 D_807FDA1E;
f32 sinApprox(f32);
f32 func_80612794(s16);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s16 func_806CC10C(s16, s16);

void func_8070FA58(struct M114aAngle *arg0_in) {
#define arg0 ((AngAAngle *)arg0_in)
    f32 diff;
    f32 dist1;
    f32 dz;
    f32 dx;
    s16 ang;
    f32 dist2;

    dz = ANGA_PLAYER->unk218 - arg0->unk1C;
    dx = ANGA_PLAYER->unk210 - arg0->unk18;
    dist1 = sqrtf(dz * dz + dx * dx);
    arg0->unk18 = ANGA_PLAYER->unk210;
    arg0->unk1C = ANGA_PLAYER->unk218;
    diff = ANGA_PLAYER->unk2C4 - arg0->unk14;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    }
    if (diff < -3.1415927f) {
        diff = -6.2831855f - diff;
    }
    arg0->unk4 = (f32)((f64)arg0->unk4 + ((f64)(diff * 180.0f) - 0.3 * (f64)D_807FDA1E));
    arg0->unk4 += 4.0f * dist1 * sinApprox(diff);
    ang = mathAngleBetweenPoints2D(ANGA_PLAYER->unk210, ANGA_PLAYER->unk218, ANGA_PLAYER->unk21C, ANGA_PLAYER->unk224);
    dz = ANGA_PLAYER->unk218 - ANGA_PLAYER->unk224;
    dx = ANGA_PLAYER->unk210 - ANGA_PLAYER->unk21C;
    dist2 = sqrtf(dz * dz + dx * dx);
    arg0->unk4 -= 2.0 * dist2 * func_80612794(func_806CC10C(ANGA_PLAYER->unk2C8, ang));
    arg0->unk14 = ANGA_PLAYER->unk2C4;
}
#undef arg0

typedef struct M114aAngle {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    f32 unk24;
    f32 unk28;
    u8 unk2C[0x84];
    u8 unkB0;
    u8 unkB1;
} M114aAngle;

void func_8070FC40(M114aAngle *arg0) {
    if (315.0f < arg0->unk4) {
        arg0->unk4 = arg0->unk4 - 315.0f + 2.0f;
    }
    if (arg0->unk4 < 2.0f) {
        arg0->unk4 = 315.0f - arg0->unk4;
    }
    arg0->unk4 = (s32)arg0->unk4 % 320;
}

typedef struct AngACamState {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0x66];
    u8 unkFA;
} AngACamState;

typedef struct AngAFcccView {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x9C];
    u8 unkB0;
    u8 unkB1;
} AngAFcccView;

extern Actor *gCamActor;
extern Actor *D_807FBB4C;
extern u32 D_807FBB68;
extern f32 D_807FD9EC;
extern u8 D_8071FEF4;
f32 cosApprox(f32);
void func_807149B8(s32);
void func_8071498C(void *);
void func_80714A58(s16);
void func_80714A28(s16);
void func_80714CC0(s32, f32, f32, f32, f32);
void func_80718380();

#define ANGA_CAM ((AngACamState *)gCamActor->unk174)
#define ANGA_A8 (*(f32 *)&D_807FBB4C->unkA8)
#define ANGA_DIST(x) ((x) < ANGA_PLAYER->unk214 ? ANGA_PLAYER->unk214 - (x) : -(ANGA_PLAYER->unk214 - (x)))

s32 func_8070FCCC(AngAFcccView *arg0) {
    f32 inc;
    f32 nv;
    f32 bound;
    s32 var_v1;
    f32 angle;
    f32 jitter;

    if (ANGA_CAM->unkFA != 0 && ANGA_PLAYER->unk214 < ANGA_CAM->unk90 + 3.0f) {
        bound = D_807FBB4C->unkAC;
    } else {
        bound = ANGA_DIST(ANGA_A8) < ANGA_DIST(D_807FBB4C->unkAC) ? ANGA_A8 : D_807FBB4C->unkAC;
    }
    func_8070FA58((M114aAngle *)arg0);
    func_8070FC40((M114aAngle *)arg0);
    var_v1 = arg0->unkB0 < 0x10;
    arg0->unkB0++;
    arg0->unk8 = arg0->unk4;
    if (var_v1 == 0) {
        if (arg0->unkB1 >= 0x50) {
            arg0->unkB1 -= 0x50;
        }
    }
    nv = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 60.0);
    inc = (f32)((f64)((30.0f - (nv - 30.0f)) + 30.0f) * 0.25);
    inc = inc > 5.0 ? inc : 5.0;
    arg0->unkC += inc;
    if (arg0->unkB1 < 0x50) {
        if ((randomNonNegative() >> 15) % 0x80 >= 0x56) {
            if (ANGA_DIST(bound) < 50.0f) {
                angle = ((randomNonNegative() >> 15) % 60 - 30) * 0.017453292f + ANGA_PLAYER->unk2C4;
                jitter = (randomNonNegative() >> 15) % 0x82;
                if ((D_807FBB68 & 8) == 0) {
                    func_807149B8(1);
                    func_8071498C(&func_80718380);
                    func_80714A58(arg0->unk0);
                    func_80714A28(4);
                    func_80714CC0((s32)&D_8071FEF4, 0.3f, ANGA_PLAYER->unk210 - sinApprox(angle) * jitter, (f32)((f64)bound + 1.0), ANGA_PLAYER->unk218 - cosApprox(angle) * jitter);
                }
                return 1;
            }
        }
    }
    return (D_807FD9EC < arg0->unkC) & 0xFF;
}

#undef ANGA_CAM
#undef ANGA_A8
#undef ANGA_DIST

void func_8070FA58(M114aAngle *);


s32 func_8071006C(M114aAngle *arg0) {
    s32 var_v1;
    f32 new_var;
    s32 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    func_8070FC40(arg0);
    temp_v0 = arg0->unkB0;
    var_v1 = (s32)temp_v0 < 0xF;
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unk8 = (f32)arg0->unk4;
    temp_v0 = 0x50;
    if (var_v1 == 0) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0x50) {
            arg0->unkB1 = (u8)(temp_v0_2 - temp_v0);
        }
    }
    new_var = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 60.0);
    var_v1 = 0;
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((30.0f - (new_var - 30.0f)) + 30.0f) * 0.2));
    if (arg0->unkC > 240.0f) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0x50;
    }
    return var_v1 & 0xFF;
}

s32 func_80710174(M114aAngle *arg0) {
    f32 new_var2;
    s32 var_v1;
    f32 new_var;
    s32 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    new_var2 = func_80612794(arg0->unk20);
    arg0->unk4 = (f32)(arg0->unk4 + (new_var2 * arg0->unk28));
    func_8070FC40(arg0);
    arg0->unk8 = (f32)arg0->unk4;
    new_var = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 8.0);
    temp_v0 = arg0->unkB0;
    var_v1 = 0x3D;
    var_v1 = (s32)temp_v0 < var_v1;
    arg0->unk20 = (s16)(arg0->unk20 + 0x14);
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((10.0f - (new_var - 10.0f)) + 10.0f) * 0.25));
    temp_v0 = 0xA;
    if (var_v1 == 0) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0xA) {
            arg0->unkB1 = (u8)(temp_v0_2 - temp_v0);
        }
    }
    var_v1 = 0;
    if (arg0->unkC > 240.0f) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0xA;
    }
    return var_v1 & 0xFF;
}

s32 func_807102AC(M114aAngle *arg0) {
    f32 new_var2;
    s32 var_v1;
    f32 new_var;
    s32 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    new_var2 = func_80612794(arg0->unk20);
    arg0->unk4 = (f32)(arg0->unk4 + (new_var2 * arg0->unk28));
    func_8070FC40(arg0);
    arg0->unk8 = (f32)arg0->unk4;
    new_var = (f32)((1.0 / ((f64)arg0->unk10 * 3.0)) * 8.0);
    temp_v0 = arg0->unkB0;
    var_v1 = 0x6F;
    var_v1 = (s32)temp_v0 < var_v1;
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((10.0f - (new_var - 10.0f)) + 10.0f) * 0.07));
    arg0->unk20 = (s16)(arg0->unk20 + 0x32);
    arg0->unkB0 = (u8)(temp_v0 + 1);
    temp_v0 = 0xA;
    if (var_v1 == 0) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0xA) {
            arg0->unkB1 = (u8)(temp_v0_2 - temp_v0);
        }
    }
    var_v1 = 0;
    if (D_807FD9EC < arg0->unkC) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0xA;
    }
    return var_v1 & 0xFF;
}


typedef struct AngAView {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0xC];
    s16 unk20;
    s16 unk22;
    s16 unk24;
    f32 unk28;
    u8 pad2C[0x84];
    u8 unkB0;
    u8 unkB1;
    u8 unkB2;
    u8 unkB3;
} AngAView;

s32 func_807103E0(AngAView *arg0) {
    f32 temp_fv1;
    f32 var_fa0;
    s32 var_v1;

    func_8070FA58((M114aAngle *)arg0);
    arg0->unk4 += func_80612794((s16)(s32)(arg0->unk22 * 0.5)) * (f32)(arg0->unk28 * 0.05);
    func_8070FC40((M114aAngle *)arg0);
    arg0->unk8 = arg0->unk4;
    arg0->unkC += (1.0 + (f64)func_80612794(arg0->unk22)) * (f64)(f32)(1.0 + arg0->unk20 * 0.08);
    arg0->unk22 += 0x64;
    arg0->unk24 = (s16)(s32)((func_80612794((s16)(s32)(arg0->unk22 * 0.5)) * 0.5 + 0.5) * (f64)(arg0->unkB3 * 4 - -arg0->unkB3 * 4) + (f64)(-arg0->unkB3 * 4));
    temp_fv1 = arg0->unk10;
    if (temp_fv1 > 0.0f) {
        var_fa0 = temp_fv1;
    } else {
        var_fa0 = -temp_fv1;
    }
    if ((var_fa0 * 140.0f) < arg0->unkC) {
        if (arg0->unkB1 >= 0xA) {
            arg0->unkB1 -= 0xA;
        }
    }
    var_v1 = 0;
    if (D_807FD9EC < arg0->unkC) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = arg0->unkB1 < 0xA;
    }
    return var_v1 & 0xFF;
}

typedef struct L105D4TextureDescriptor {
    u8 unk0[8];
    u8 format;
    u8 type;
    u8 unkA[0xA];
} L105D4TextureDescriptor;


#define L105D4_TEXTURE ((L105D4TextureDescriptor *)((u8 *)&D_80755264 + (D_807FDA1C * 0x14)))

Gfx *func_807105D4(Gfx *arg0, u8 arg1) {
    switch (L105D4_TEXTURE->type) {
    case 1:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_8b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_16b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_32b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return arg0;
}

#undef L105D4_TEXTURE

#ifdef NON_MATCHING
typedef struct L10CA0Entry {
    s16 unk0; u8 pad2[6]; f32 unk8; f32 unkC; f32 unk10; u8 pad14[0xC];
    s16 unk20; s16 unk22; s16 unk24; u8 pad26[2]; f32 unk28; u8 pad2C[0x84];
    u8 unkB0; u8 unkB1; u8 unkB2; u8 padB3[5];
} L10CA0Entry;
typedef struct L10CA0Header { u16 count; u8 pad2[2]; L10CA0Entry *entries; } L10CA0Header;
typedef struct L10CA0CamView { u8 pad0[0xB4]; f32 unkB4; } L10CA0CamView;
typedef struct L10CA0PlayerView { u8 pad0[0x90]; f32 unk90; u8 pad94[0x66]; u8 unkFA; u8 padFB[0x119]; f32 unk214; } L10CA0PlayerView;
typedef struct L10CA0TimerView { u8 pad0[0xBC]; s16 unkBC; } L10CA0TimerView;

extern void *D_807FD580;
extern void *D_807FDAB0;
extern s16 D_807FDAB4;
extern u8 D_807444FC;
extern u8 D_807FDA1B;
extern u8 D_1000020, D_1000118, D_20000C0;
void matrixMakeRotationZ(f32 (*)[4], f32);
s32 mapChunkContainsPoint(s16, s16, s16);

#define L10CA0_POOL ((L10CA0Header *)D_807550E0)
#define L10CA0_TEX (&D_80755264)[D_807FDA1C * 0x14]

Gfx *effectSpriteRenderPool(Gfx *arg0, Actor *arg1) {
    f64 scaleSize;
    f32 mtxScale[4][4];
    f32 mtxTemp[4][4];
    f64 posX;
    u8 skipNearPlayer;
    u8 skipTimer;
    s16 i;
    u16 count = L10CA0_POOL->count;
    u16 processed = 0;
    L10CA0Entry *entry;
    L10CA0PlayerView *player = (L10CA0PlayerView *)gCamActor->unk174;

    skipTimer = 0;
    skipNearPlayer = 0;

    if ((D_807FBB4C->unk154 == 3) || (D_807FBB4C->unk154 == 5)) {
        f32 rem = (((L10CA0CamView *)gCamActor)->unkB4 > 180.0f) ? 0.0f : 180.0f - ((L10CA0CamView *)gCamActor)->unkB4;
        D_807FD9EC = (f32)((f64)rem * 0.02 * 240.0);
    } else {
        D_807FD9EC = 240.0f;
    }
    if ((D_807FBB4C->unk154 == 0x42) && ((((L10CA0TimerView *)D_807FD580)->unkBC == 0x62) || (((L10CA0TimerView *)D_807FD580)->unkBC == 0x88))) {
        skipTimer = 1;
    }
    if ((player->unkFA != 0) && (((L10CA0PlayerView *)D_807FC924)->unk214 < player->unk90 + 3.0f)) {
        skipNearPlayer = 1;
    }
    gDPPipeSync(arg0++);
    gSPDisplayList(arg0++, &D_1000118);
    gSPDisplayList(arg0++, &D_1000020);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPTexture(arg0++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(arg0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureFilter(arg0++, G_TF_BILERP);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    i = 0x80;
    if (L10CA0_TEX == 1) {
        arg0 = func_807105D4(arg0, 0);
    }
    while (--i >= 0 && processed != count) {  // i = 0x80 above: pre-decrement while with i set before an unrelated if keeps the entry guard
        entry = &L10CA0_POOL->entries[i];
        D_807FDAB0 = entry;
        D_807FDAB4 = D_807FDA1E;
        if ((entry->unkB0 != 0) && ((entry->unk0 == -1) || mapChunkContainsPoint((s16)entry->unk8, (s16)entry->unkC, entry->unk0)) && !skipNearPlayer && !skipTimer) {
            gDPSetPrimColor(arg0++, 0, 0, D_807FDA1B, D_807FDA1B, D_807FDA1B, entry->unkB1);
            if (D_807FDA1C == 4) {
                switch (entry->unk20) {
                case 8: case 10: case 12: arg0 = func_807105D4(arg0, ((entry->unkB2++ >> 2) % 8) + 2); break;
                case 15: case 18: case 22: arg0 = func_807105D4(arg0, 0); break;
                default: arg0 = func_807105D4(arg0, 1); break;
                }
            } else if (L10CA0_TEX >= 2) {
                arg0 = func_807105D4(arg0, entry->unkB2++ % L10CA0_TEX);
            }
            scaleSize = (f64)entry->unk10 * 4.0;
            guScaleF(mtxScale, (f32)scaleSize, (f32)(scaleSize > 0.0 ? scaleSize : -scaleSize), 1.0f);
            switch (D_807FDA1C) {
            case 3:
                entry->unk22 = (s16)((f32)entry->unk22 + entry->unk28);
                matrixMakeRotationZ(mtxTemp, (f32)entry->unk22);
                break;
            case 4:
                matrixMakeRotationZ(mtxTemp, (f32)entry->unk24);
                break;
            default:
                matrixMakeRotationZ(mtxTemp, (f32)D_807FDA1E);
                break;
            }
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guTranslateF(mtxTemp, (f32)((f64)entry->unk8 * 4.0), (f32)((f64)entry->unkC * 4.0), -50.0f);
            guMtxCatF(mtxScale, mtxTemp, mtxScale);
            guMtxF2L(mtxScale, (Mtx *)((u8 *)entry + (D_807444FC << 6) + 0x30));
            gSPMatrix(arg0++, (u8 *)entry + (D_807444FC << 6) + 0x30, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPVertex(arg0++, osVirtualToPhysical((void *)D_807FDA20), 4, 0);
            gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(arg0++);
        }
        if (entry->unkB0 != 0) {
            processed++;
            if ((((s32 (*)(L10CA0Entry *))D_807FDA24)(entry) != 0) || ((f64)entry->unk10 < 0.01)) {
                entry->unkB0 = 0;
                (&D_807FDA30)[D_807FDA1A = D_807FDA1A + 1] = i;
                L10CA0_POOL->count--;
            }
        }
    }
    return arg0;
}

#undef L10CA0_POOL
#undef L10CA0_TEX
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/effectSpriteRenderPool.s")
#endif

typedef struct AngBPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} AngBPlayerView;

extern s32 D_807FBB60;
extern u8 D_807FDA1B;
extern f32 *D_8076A0B4;
extern u8 D_8077058C[];
void func_8070F5CC(u8, s16, f32, s16, s32, s32);
Gfx *effectSpriteRenderPool(Gfx *, Actor *);
void renderCallbacksRegister(void *, void *, s32);

void func_80711410(f32 arg0, s16 arg1, f32 arg2, s16 arg3, f32 arg4) {
    f32 temp_fs1;
    f64 temp_fa0;
    f64 temp_fv1;
    f64 temp_fv2;
    f64 var_fv0;
    s32 var_s0;
    s32 var_s5;

    if (D_807FBB60 & 0x10) {
        temp_fv1 = (f64)arg0;
        temp_fv2 = (f64)arg2;
        D_807FDA1E = (s16)(s32)(cosApprox(((AngBPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
        temp_fa0 = (temp_fv1 * 255) / 3.9;
        if (temp_fa0 > 255.0) {
            var_fv0 = 255.0;
        } else {
            var_fv0 = temp_fa0;
        }
        D_8077058C[0] = (u8)(u32)(var_fv0 * temp_fv2);
        if (temp_fv1 < 1.0) {
            arg0 *= 100.0f;
            if ((f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 100) < arg0) {
                var_s5 = 1;
            } else {
                var_s5 = 0;
            }
        } else {
            var_s5 = (s32)arg0;
        }
        D_807FDA1B = (u8)(u32)((*D_8076A0B4 * 100.0f) + 100.0f);
        var_s0 = 0;
        if (var_s5 > 0) do { // FAKE: if/do on one line steers as1 preheader scheduling
            temp_fs1 = (f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 320);
            func_8070F5CC(0, arg3, (f32)(((f64)(f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)arg4), (s16)(s32)temp_fs1, -10, (u32)(90.0f * arg4) & 0xFF);
            var_s0 += 1;
        } while (var_s0 != var_s5);
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}

typedef struct R114cPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} R114cPlayerView;

u32 func_806119A0(void);

void func_80711950(f32 arg0, s16 arg1, s16 arg2) {
    s32 random;
    s32 count;
    s32 i;
    f32 value;

    if (D_807FBB60 & 0x10) {
        D_807FDA1E = (s16)(cosApprox(((R114cPlayerView *)D_807FC924)->unk2C4) * arg1);
        if (arg0 < 1.0) {
            arg0 *= 100.0f;
            random = func_806119A0() / 10000;
            if ((f32)(s32)((u32)random % 100U) < arg0) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)arg0;
        }
        D_807FDA1B = 0xFF;
        for (i = 0; i < count; i++) {
            random = func_806119A0() / 10000;
            value = (f32)((f64)((u32)random % 125U) / 1000.0);
            random = func_806119A0() / 10000;
            func_8070F5CC(1, arg2, (f32)((f64)value + 0.075), (s16)(s32)((u32)random % 320U), -10, 200);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}




extern u8 D_807212E0;
s32 func_807149FC(s32);
void func_8071495C(void);
void effectSwayRiseUpdate(void);

void func_80711BD0(f32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    f32 temp_fv1;
    f32 var_fs0;
    f64 temp_fv0;
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;

    if (D_807FBB60 & 0x10) {
        if ((arg3 == 3) && (((s32)(randomNonNegative() >> 0xF) % 1000) >= 0x3DA)) {
            func_807149FC(-1);
            func_8071498C(&effectSwayRiseUpdate);
            func_8071495C();
            temp_s0 = randomNonNegative();
            func_80714CC0((s32)&D_807212E0, (f32)(((f64)((s32)(temp_s0 >> 0xF) % 100) * 0.01) + 0.4), (f32)((s32)(randomNonNegative() >> 0xF) % 320), 0.0f, -5.0f);
        }
        D_807FDA1E = (s16)(s32)(cosApprox(((R114cPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
        if ((f64)arg0 < 1.0) {
            arg0 *= 100.0f;
            if ((f32)(s32)((u32)(func_806119A0() / 10000U) % 100U) < arg0) {
                var_s1 = 1;
            } else {
                var_s1 = 0;
            }
        } else {
            var_s1 = (s32)arg0;
        }
        D_807FDA1B = 0xFF;
        var_s0 = 0;
        if (var_s1 > 0) {
            do {
                temp_fv1 = (f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 80) * 0.005);
                var_fs0 = temp_fv1;
                if (D_807FDA1C != 3) {
                    temp_fv0 = (f64)temp_fv1 * 3.0;
                    var_fs0 = (f32)((temp_fv0 > 0.3 ? temp_fv0 : 0.3) < 2.0 ? (temp_fv0 > 0.3 ? temp_fv0 : 0.3) : 2.0);
                }
                var_fs0 = (f32)((f64)var_fs0 + 0.2);
                if ((D_807FDA1C == 4) && (((s32)(randomNonNegative() >> 0xF) % 100) >= 0x33)) {
                    var_fs0 *= -1.0f;
                }
                func_8070F5CC(arg3, arg2, var_fs0, (s16)(s32)((u32)(func_806119A0() / 10000U) % 320U), -10, 0xC8);
                var_s0 += 1;
            } while (var_s0 != var_s1);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}


void func_80711F90(f32 arg0, s16 arg1, s32 arg2, s16 arg3, f32 arg4) {
    f32 temp_fs1;
    s32 var_s0;
    s32 var_s4;

    D_807FDA1E = (s16)(s32)(cosApprox(((R114cPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
    if ((f64)arg0 < 1.0) {
        arg0 *= 100.0f;
        if ((f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 100) < arg0) {
            var_s4 = 1;
        } else {
            var_s4 = 0;
        }
    } else {
        var_s4 = (s32)arg0;
    }
    D_807FDA1B = 0xFF;
    var_s0 = 0;
    if (var_s4 > 0) {
        do {
            temp_fs1 = (f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 320);
            func_8070F5CC(2, arg3, (f32)(((f64)(f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)arg4), (s16)(s32)temp_fs1, -10, 0xFF);
            var_s0 += 1;
        } while (var_s0 != var_s4);
    }
    if (*D_807550E0 != 0) {
        renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
    }
}

void assetFreeBuffer(void *, s32, s32);
void heapFreeDeferred(void *);

s32 func_807122B4(void) {
    s16 i;
    u16 *queue;

    queue = D_807550E0;
    if (*queue != 0) {
        D_8077058C[0] = (u8)(u32)((f64)(u32)D_8077058C[0] * 0.9);
        renderCallbacksRegister((void *)effectSpriteRenderPool, NULL, 1);
        return 0;
    }
    if (D_807FDA1C != 6) {
        D_8077058C[0] = 0;
        heapFreeDeferred(*(void **)((u8 *)queue + 4));
        for (i = 0; i < (s32)(&D_80755264)[D_807FDA1C * 0x14]; i++) {
            assetFreeBuffer((void *)D_807FD9F0[i], 0x34A, 0x64);
        }
        D_807FDA1C = 6;
        D_807FDA28 = 0;
        return 1;
    }
    // FAKE: no final return keeps queue in $v0
}

