#include "common.h"
#include "actor.h"
#include "proto/global/114270.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/55B20.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/90D80.h"
#include "proto/global/CEAE0.h"

extern Actor *gCurrentActor;
extern void *gPlayerSlots;
extern s32 gCurrentMap;
extern u8 gMenuCurrentMode;
extern u8 gMenuTargetMode;

extern u16 *D_807550E0;
extern u8 D_807FDA1A;
extern u8 D_807FDA1C;
extern u8 D_807FDA28;
extern u8 D_807FDA30;

void effectSpritePoolReset(void) {
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

#define ANGA_PLAYER ((AngAPlayer *)gPlayerSlots)


typedef struct EffectSpriteParticle {
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
} EffectSpriteParticle;

typedef struct EffectSpritePoolHeader {
    u16 count;
    u8 pad2[2];
    EffectSpriteParticle *entries;
} EffectSpritePoolHeader;

typedef struct EffectSpriteTextureSetup {
    u8 count;
    u8 type;
    u8 pad2[2];
    u16 *images;
    u8 pad8[2];
    u8 width;
    u8 height;
    s32 unkC;
    s32 unk10;
} EffectSpriteTextureSetup;

extern u8 D_80755264;
extern u32 D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;
extern s32 D_807FDA20;
extern s32 D_807FDA24;

#define ANGA_SETUP ((EffectSpriteTextureSetup *)(&D_80755264 + poolType * 0x14))
#define ANGA_POP_SLOT(out) \
    out = (&D_807FDA30)[D_807FDA1A]; (&D_807FDA30)[D_807FDA1A] = 0xFF; D_807FDA1A--
#define ANGA_POOL ((EffectSpritePoolHeader *)D_807550E0)

void effectSpritePoolSpawn(u8 poolType, s16 mapChunk, f32 scale, s16 spawnX, s32 spawnY, u8 initialAlpha) {
    EffectSpriteParticle *entry;
    s16 i;
    s32 idx;

    if (ANGA_POOL->count >= 0x80) {
        return;
    }
    if (ANGA_POOL->count == 0 && D_807FDA28 == 0) {
        ANGA_POOL->entries = heapAlloc(0x5C00);
        heapClearBlock(ANGA_POOL->entries);
        D_807FDA1C = poolType;
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
    entry->unk4 = (f32)spawnX;
    entry->unk8 = (f32)spawnX;
    entry->unkC = (f32)(s16)spawnY;
    entry->unk10 = scale;
    entry->unk0 = mapChunk;
    entry->unkB1 = initialAlpha;
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
f32 mathSinF(s16);

void effectSpriteParticleTrackCamera(struct M114aAngle *particle) {
#define p ((AngAAngle *)particle)
    f32 diff;
    f32 dist1;
    f32 dz;
    f32 dx;
    s16 ang;
    f32 dist2;

    dz = ANGA_PLAYER->unk218 - p->unk1C;
    dx = ANGA_PLAYER->unk210 - p->unk18;
    dist1 = sqrtf(dz * dz + dx * dx);
    p->unk18 = ANGA_PLAYER->unk210;
    p->unk1C = ANGA_PLAYER->unk218;
    diff = ANGA_PLAYER->unk2C4 - p->unk14;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    }
    if (diff < -3.1415927f) {
        diff = -6.2831855f - diff;
    }
    p->unk4 = (f32)((f64)p->unk4 + ((f64)(diff * 180.0f) - 0.3 * (f64)D_807FDA1E));
    p->unk4 += 4.0f * dist1 * sinApprox(diff);
    ang = mathAngleBetweenPoints2D(ANGA_PLAYER->unk210, ANGA_PLAYER->unk218, ANGA_PLAYER->unk21C, ANGA_PLAYER->unk224);
    dz = ANGA_PLAYER->unk218 - ANGA_PLAYER->unk224;
    dx = ANGA_PLAYER->unk210 - ANGA_PLAYER->unk21C;
    dist2 = sqrtf(dz * dz + dx * dx);
    p->unk4 -= 2.0 * dist2 * mathSinF(mathAngleSignedDistance(ANGA_PLAYER->unk2C8, ang));
    p->unk14 = ANGA_PLAYER->unk2C4;
}
#undef p

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

void effectSpriteParticleWrapX(M114aAngle *particle) {
    if (315.0f < particle->unk4) {
        particle->unk4 = particle->unk4 - 315.0f + 2.0f;
    }
    if (particle->unk4 < 2.0f) {
        particle->unk4 = 315.0f - particle->unk4;
    }
    particle->unk4 = (s32)particle->unk4 % 320;
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
extern Actor *gPrimaryPlayerActor;
extern u32 gGlobalCutsceneFlags;
extern f32 D_807FD9EC;
extern u8 sEffectImpactPuffConfig;
f32 cosApprox(f32);

#define ANGA_CAM ((AngACamState *)gCamActor->customState)
#define ANGA_A8 (*(f32 *)&gPrimaryPlayerActor->unkA8)
#define ANGA_DIST(x) ((x) < ANGA_PLAYER->unk214 ? ANGA_PLAYER->unk214 - (x) : -(ANGA_PLAYER->unk214 - (x)))

s32 func_8070FCCC(AngAFcccView *particle) {
    f32 inc;
    f32 nv;
    f32 bound;
    s32 isUnderMaxAge;
    f32 angle;
    f32 jitter;

    if (ANGA_CAM->unkFA != 0 && ANGA_PLAYER->unk214 < ANGA_CAM->unk90 + 3.0f) {
        bound = gPrimaryPlayerActor->waterY;
    } else {
        bound = ANGA_DIST(ANGA_A8) < ANGA_DIST(gPrimaryPlayerActor->waterY) ? ANGA_A8 : gPrimaryPlayerActor->waterY;
    }
    effectSpriteParticleTrackCamera((M114aAngle *)particle);
    effectSpriteParticleWrapX((M114aAngle *)particle);
    isUnderMaxAge = particle->unkB0 < 0x10;
    particle->unkB0++;
    particle->unk8 = particle->unk4;
    if (isUnderMaxAge == 0) {
        if (particle->unkB1 >= 0x50) {
            particle->unkB1 -= 0x50;
        }
    }
    nv = (f32)((1.0 / ((f64)particle->unk10 * 4.0)) * 60.0);
    inc = (f32)((f64)((30.0f - (nv - 30.0f)) + 30.0f) * 0.25);
    inc = inc > 5.0 ? inc : 5.0;
    particle->unkC += inc;
    if (particle->unkB1 < 0x50) {
        if ((randomNonNegative() >> 15) % 0x80 >= 0x56) {
            if (ANGA_DIST(bound) < 50.0f) {
                angle = ((randomNonNegative() >> 15) % 60 - 30) * 0.017453292f + ANGA_PLAYER->unk2C4;
                jitter = (randomNonNegative() >> 15) % 0x82;
                if ((gGlobalCutsceneFlags & 8) == 0) {
                    effectSetDepth(1);
                    effectSetCallback(&effectRandomYRotDecalUpdate);
                    effectSetLifetime(particle->unk0);
                    effectSetFlags(4);
                    effectCreateAtPosition((s32)&sEffectImpactPuffConfig, 0.3f, ANGA_PLAYER->unk210 - sinApprox(angle) * jitter, (f32)((f64)bound + 1.0), ANGA_PLAYER->unk218 - cosApprox(angle) * jitter);
                }
                return 1;
            }
        }
    }
    return (D_807FD9EC < particle->unkC) & 0xFF;
}

#undef ANGA_CAM
#undef ANGA_A8
#undef ANGA_DIST



s32 func_8071006C(M114aAngle *particle) {
    s32 isDone;
    f32 new_var;
    s32 age;
    u8 curAlpha;

    effectSpriteParticleTrackCamera(particle);
    effectSpriteParticleWrapX(particle);
    age = particle->unkB0;
    isDone = (s32)age < 0xF;
    particle->unkB0 = (u8)(age + 1);
    particle->unk8 = (f32)particle->unk4;
    age = 0x50;
    if (isDone == 0) {
        curAlpha = particle->unkB1;
        if ((s32)curAlpha >= 0x50) {
            particle->unkB1 = (u8)(curAlpha - age);
        }
    }
    new_var = (f32)((1.0 / ((f64)particle->unk10 * 4.0)) * 60.0);
    isDone = 0;
    particle->unkC = (f32)((f64)particle->unkC + ((f64)((30.0f - (new_var - 30.0f)) + 30.0f) * 0.2));
    if (particle->unkC > 240.0f) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = (s32)particle->unkB1 < 0x50;
    }
    return isDone & 0xFF;
}

s32 func_80710174(M114aAngle *particle) {
    f32 new_var2;
    s32 isDone;
    f32 new_var;
    s32 age;
    u8 curAlpha;

    effectSpriteParticleTrackCamera(particle);
    new_var2 = mathSinF(particle->unk20);
    particle->unk4 = (f32)(particle->unk4 + (new_var2 * particle->unk28));
    effectSpriteParticleWrapX(particle);
    particle->unk8 = (f32)particle->unk4;
    new_var = (f32)((1.0 / ((f64)particle->unk10 * 4.0)) * 8.0);
    age = particle->unkB0;
    isDone = 0x3D;
    isDone = (s32)age < isDone;
    particle->unk20 = (s16)(particle->unk20 + 0x14);
    particle->unkB0 = (u8)(age + 1);
    particle->unkC = (f32)((f64)particle->unkC + ((f64)((10.0f - (new_var - 10.0f)) + 10.0f) * 0.25));
    age = 0xA;
    if (isDone == 0) {
        curAlpha = particle->unkB1;
        if ((s32)curAlpha >= 0xA) {
            particle->unkB1 = (u8)(curAlpha - age);
        }
    }
    isDone = 0;
    if (particle->unkC > 240.0f) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = (s32)particle->unkB1 < 0xA;
    }
    return isDone & 0xFF;
}

s32 func_807102AC(M114aAngle *particle) {
    f32 new_var2;
    s32 isDone;
    f32 new_var;
    s32 age;
    u8 curAlpha;

    effectSpriteParticleTrackCamera(particle);
    new_var2 = mathSinF(particle->unk20);
    particle->unk4 = (f32)(particle->unk4 + (new_var2 * particle->unk28));
    effectSpriteParticleWrapX(particle);
    particle->unk8 = (f32)particle->unk4;
    new_var = (f32)((1.0 / ((f64)particle->unk10 * 3.0)) * 8.0);
    age = particle->unkB0;
    isDone = 0x6F;
    isDone = (s32)age < isDone;
    particle->unkC = (f32)((f64)particle->unkC + ((f64)((10.0f - (new_var - 10.0f)) + 10.0f) * 0.07));
    particle->unk20 = (s16)(particle->unk20 + 0x32);
    particle->unkB0 = (u8)(age + 1);
    age = 0xA;
    if (isDone == 0) {
        curAlpha = particle->unkB1;
        if ((s32)curAlpha >= 0xA) {
            particle->unkB1 = (u8)(curAlpha - age);
        }
    }
    isDone = 0;
    if (D_807FD9EC < particle->unkC) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = (s32)particle->unkB1 < 0xA;
    }
    return isDone & 0xFF;
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

s32 func_807103E0(AngAView *particle) {
    f32 scaleY;
    f32 absScaleY;
    s32 isDone;

    effectSpriteParticleTrackCamera((M114aAngle *)particle);
    particle->unk4 += mathSinF((s16)(s32)(particle->unk22 * 0.5)) * (f32)(particle->unk28 * 0.05);
    effectSpriteParticleWrapX((M114aAngle *)particle);
    particle->unk8 = particle->unk4;
    particle->unkC += (1.0 + (f64)mathSinF(particle->unk22)) * (f64)(f32)(1.0 + particle->unk20 * 0.08);
    particle->unk22 += 0x64;
    particle->unk24 = (s16)(s32)((mathSinF((s16)(s32)(particle->unk22 * 0.5)) * 0.5 + 0.5) * (f64)(particle->unkB3 * 4 - -particle->unkB3 * 4) + (f64)(-particle->unkB3 * 4));
    scaleY = particle->unk10;
    if (scaleY > 0.0f) {
        absScaleY = scaleY;
    } else {
        absScaleY = -scaleY;
    }
    if ((absScaleY * 140.0f) < particle->unkC) {
        if (particle->unkB1 >= 0xA) {
            particle->unkB1 -= 0xA;
        }
    }
    isDone = 0;
    if (D_807FD9EC < particle->unkC) {
        isDone = 1;
    }
    if (isDone == 0) {
        isDone = particle->unkB1 < 0xA;
    }
    return isDone & 0xFF;
}

typedef struct L105D4TextureDescriptor {
    u8 unk0[8];
    u8 format;
    u8 type;
    u8 unkA[0xA];
} L105D4TextureDescriptor;


#define L105D4_TEXTURE ((L105D4TextureDescriptor *)((u8 *)&D_80755264 + (D_807FDA1C * 0x14)))

Gfx *effectSpritePoolLoadTexture(Gfx *glist, u8 textureIndex) {
    switch (L105D4_TEXTURE->type) {
    case 1:
        gDPLoadTextureBlock(glist++, D_807FD9F0[textureIndex], L105D4_TEXTURE->format, G_IM_SIZ_8b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock(glist++, D_807FD9F0[textureIndex], L105D4_TEXTURE->format, G_IM_SIZ_16b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
        gDPLoadTextureBlock(glist++, D_807FD9F0[textureIndex], L105D4_TEXTURE->format, G_IM_SIZ_32b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return glist;
}

#undef L105D4_TEXTURE

typedef struct L10CA0Entry {
    s16 unk0; u8 pad2[6]; f32 unk8; f32 unkC; f32 unk10; u8 pad14[0xC];
    s16 unk20; s16 unk22; s16 unk24; u8 pad26[2]; f32 unk28; u8 pad2C[0x84];
    u8 unkB0; u8 unkB1; u8 unkB2; u8 padB3[5];
} L10CA0Entry;
typedef struct L10CA0Header { u16 count; u8 pad2[2]; L10CA0Entry *entries; } L10CA0Header;
typedef struct L10CA0CamView { u8 pad0[0xB4]; f32 unkB4; } L10CA0CamView;
typedef struct L10CA0PlayerView { u8 pad0[0x90]; f32 unk90; u8 pad94[0x66]; u8 unkFA; u8 padFB[0x119]; f32 unk214; } L10CA0PlayerView;
typedef struct L10CA0TimerView { u8 pad0[0xBC]; s16 unkBC; } L10CA0TimerView;

extern void *gActivePlayerState;
extern void *D_807FDAB0;
extern s16 D_807FDAB4;
extern u8 gGfxBufferIndex;
extern u8 D_807FDA1B;
extern u8 D_1000020, D_1000118, D_20000C0;

#define L10CA0_POOL ((L10CA0Header *)D_807550E0)
#define L10CA0_TEX (&D_80755264)[D_807FDA1C * 0x14]

Gfx *effectSpriteRenderPool(Gfx *glist, Actor *actor) {
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
    L10CA0PlayerView *player = (L10CA0PlayerView *)gCamActor->customState;

    skipTimer = 0;
    skipNearPlayer = 0;

    if ((gPrimaryPlayerActor->state == 3) || (gPrimaryPlayerActor->state == 5)) {
        f32 rem = (((L10CA0CamView *)gCamActor)->unkB4 > 180.0f) ? 0.0f : 180.0f - ((L10CA0CamView *)gCamActor)->unkB4;
        if (count == 0) {}  // FAKE: deadsweep dead statement (steers uopt: count's temp slot)
        D_807FD9EC = (f32)((f64)rem * 0.02 * 240.0);
    } else {
        D_807FD9EC = 240.0f;
    }
    if ((gPrimaryPlayerActor->state == 0x42) && ((((L10CA0TimerView *)gActivePlayerState)->unkBC == 0x62) || (((L10CA0TimerView *)gActivePlayerState)->unkBC == 0x88))) {
        skipTimer = 1;
    }
    if ((player->unkFA != 0) && (((L10CA0PlayerView *)gPlayerSlots)->unk214 < player->unk90 + 3.0f)) {
        skipNearPlayer = 1;
    }
    gDPPipeSync(glist++);
    gSPDisplayList(glist++, &D_1000118);
    gSPDisplayList(glist++, &D_1000020);
    gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPTexture(glist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureFilter(glist++, G_TF_BILERP);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    i = 0x80;
    if (L10CA0_TEX == 1) {
        glist = effectSpritePoolLoadTexture(glist, 0);
    }
    while (--i >= 0 && processed != count) {  // i = 0x80 above: pre-decrement while with i set before an unrelated if keeps the entry guard
        entry = &L10CA0_POOL->entries[i];
        D_807FDAB0 = entry;
        D_807FDAB4 = D_807FDA1E;
        if ((entry->unkB0 != 0) && ((entry->unk0 == -1) || mapChunkContainsPoint((s16)entry->unk8, (s16)entry->unkC, entry->unk0)) && !skipNearPlayer && !skipTimer) {
            gDPSetPrimColor(glist++, 0, 0, D_807FDA1B, D_807FDA1B, D_807FDA1B, entry->unkB1);
            if (D_807FDA1C == 4) {
                switch (entry->unk20) {
                case 8: case 10: case 12: glist = effectSpritePoolLoadTexture(glist, ((entry->unkB2++ >> 2) % 8) + 2); break;
                case 15: case 18: case 22: glist = effectSpritePoolLoadTexture(glist, 0); break;
                default: glist = effectSpritePoolLoadTexture(glist, 1); break;
                }
            } else if (L10CA0_TEX >= 2) {
                glist = effectSpritePoolLoadTexture(glist, entry->unkB2++ % L10CA0_TEX);
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
            guMtxF2L(mtxScale, (Mtx *)((u8 *)entry + (gGfxBufferIndex << 6) + 0x30));
            gSPMatrix(glist++, (u8 *)entry + (gGfxBufferIndex << 6) + 0x30, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPVertex(glist++, osVirtualToPhysical((void *)D_807FDA20), 4, 0);
            gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(glist++);
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
    return glist;
}

#undef L10CA0_POOL
#undef L10CA0_TEX

typedef struct AngBPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} AngBPlayerView;

extern s32 gGlobalPauseFlags;
extern u8 D_807FDA1B;
extern f32 *D_8076A0B4;
extern u8 D_8077058C[];

void func_80711410(f32 density, s16 windAngle, f32 alpha, s16 mapChunk, f32 scale) {
    f32 randX;
    f64 calcAlpha;
    f64 densityVal;
    f64 alphaVal;
    f64 clampedAlpha;
    s32 idx;
    s32 count;

    if (gGlobalPauseFlags & 0x10) {
        densityVal = (f64)density;
        alphaVal = (f64)alpha;
        D_807FDA1E = (s16)(s32)(cosApprox(((AngBPlayerView *)gPlayerSlots)->unk2C4) * (f32)windAngle);
        calcAlpha = (densityVal * 255) / 3.9;
        if (calcAlpha > 255.0) {
            clampedAlpha = 255.0;
        } else {
            clampedAlpha = calcAlpha;
        }
        D_8077058C[0] = (u8)(u32)(clampedAlpha * alphaVal);
        if (densityVal < 1.0) {
            density *= 100.0f;
            if ((f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 100) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)density;
        }
        D_807FDA1B = (u8)(u32)((*D_8076A0B4 * 100.0f) + 100.0f);
        idx = 0;
        if (count > 0) do { // LAYOUT: if/do on one line steers as1 preheader scheduling
            randX = (f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 320);
            effectSpritePoolSpawn(0, mapChunk, (f32)(((f64)(f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)scale), (s16)(s32)randX, -10, 90.0f * scale);
            idx += 1;
        } while (idx != count);
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}

typedef struct R114cPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} R114cPlayerView;


void func_80711950(f32 density, s16 windAngle, s16 mapChunk) {
    s32 random;
    s32 count;
    s32 i;
    f32 value;

    if (gGlobalPauseFlags & 0x10) {
        D_807FDA1E = (s16)(cosApprox(((R114cPlayerView *)gPlayerSlots)->unk2C4) * windAngle);
        if (density < 1.0) {
            density *= 100.0f;
            random = randomLcgNext() / 10000;
            if ((f32)(s32)((u32)random % 100U) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)density;
        }
        D_807FDA1B = 0xFF;
        for (i = 0; i < count; i++) {
            random = randomLcgNext() / 10000;
            value = (f32)((f64)((u32)random % 125U) / 1000.0);
            random = randomLcgNext() / 10000;
            effectSpritePoolSpawn(1, mapChunk, (f32)((f64)value + 0.075), (s16)(s32)((u32)random % 320U), -10, 200);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}




extern u8 D_807212E0;

void func_80711BD0(f32 density, s16 windAngle, s16 mapChunk, u8 poolType) {
    f32 randScale;
    f32 scaleVal;
    f64 scaledVal;
    s32 randSeed;
    s32 idx;
    s32 count;

    if (gGlobalPauseFlags & 0x10) {
        if ((poolType == 3) && (((s32)(randomNonNegative() >> 0xF) % 1000) >= 0x3DA)) {
            effectSetDuration(-1);
            effectSetCallback(&effectSwayRiseUpdate);
            effectEnableFade();
            randSeed = randomNonNegative();
            effectCreateAtPosition((s32)&D_807212E0, (f32)(((f64)((s32)(randSeed >> 0xF) % 100) * 0.01) + 0.4), (f32)((s32)(randomNonNegative() >> 0xF) % 320), 0.0f, -5.0f);
        }
        D_807FDA1E = (s16)(s32)(cosApprox(((R114cPlayerView *)gPlayerSlots)->unk2C4) * (f32)windAngle);
        if ((f64)density < 1.0) {
            density *= 100.0f;
            if ((f32)(s32)((u32)(randomLcgNext() / 10000U) % 100U) < density) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)density;
        }
        D_807FDA1B = 0xFF;
        idx = 0;
        if (count > 0) {
            do {
                randScale = (f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 80) * 0.005);
                scaleVal = randScale;
                if (D_807FDA1C != 3) {
                    scaledVal = (f64)randScale * 3.0;
                    scaleVal = (f32)((scaledVal > 0.3 ? scaledVal : 0.3) < 2.0 ? (scaledVal > 0.3 ? scaledVal : 0.3) : 2.0);
                }
                scaleVal = (f32)((f64)scaleVal + 0.2);
                if ((D_807FDA1C == 4) && (((s32)(randomNonNegative() >> 0xF) % 100) >= 0x33)) {
                    scaleVal *= -1.0f;
                }
                effectSpritePoolSpawn(poolType, mapChunk, scaleVal, (s16)(s32)((u32)(randomLcgNext() / 10000U) % 320U), -10, 0xC8);
                idx += 1;
            } while (idx != count);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
        }
    }
}


void func_80711F90(f32 density, s16 windAngle, s32 unused, s16 mapChunk, f32 scale) {
    f32 randX;
    s32 idx;
    s32 count;

    D_807FDA1E = (s16)(s32)(cosApprox(((R114cPlayerView *)gPlayerSlots)->unk2C4) * (f32)windAngle);
    if ((f64)density < 1.0) {
        density *= 100.0f;
        if ((f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 100) < density) {
            count = 1;
        } else {
            count = 0;
        }
    } else {
        count = (s32)density;
    }
    D_807FDA1B = 0xFF;
    idx = 0;
    if (count > 0) {
        do {
            randX = (f32)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 320);
            effectSpritePoolSpawn(2, mapChunk, (f32)(((f64)(f32)((f64)((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)scale), (s16)(s32)randX, -10, 0xFF);
            idx += 1;
        } while (idx != count);
    }
    if (*D_807550E0 != 0) {
        renderCallbacksRegister(&effectSpriteRenderPool, 0, 1);
    }
}


s32 effectSpritePoolFadeOut(void) {
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
    // FAKE: no final return; fall-through path (*queue == 0 && D_807FDA1C == 6) returns queue (D_807550E0) in v0 implicitly
}

