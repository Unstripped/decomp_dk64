#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#include "proto/critter/0.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
#include "proto/global/CEAE0.h"

typedef struct CritterZoneShape {
    /* 0x00 */ s16 radius;
    /* 0x02 */ s16 reactDistSq;
    /* 0x04 */ s16 height;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 extraHeight;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 ringRadius;
    /* 0x10 */ s32 nearDistSq;
} CritterZoneShape;

typedef struct CritterZone {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ CritterZoneShape shape;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 pad1D[3];
    /* 0x20 */ f32 distSq;
    /* 0x24 */ u8 frame;
    /* 0x25 */ u8 near;
    /* 0x26 */ u8 alpha;
    /* 0x27 */ u8 pad27;
    /* 0x28 */ s16 chunkIdx;
    /* 0x2A */ u8 pad2A[2];
} CritterZone;

typedef struct CritterObj {
    /* 0x00 */ s16 yaw;
    /* 0x02 */ s16 pitch;
    /* 0x04 */ s16 prevYaw;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ f32 yBob;
    /* 0x18 */ f32 offX;
    /* 0x1C */ f32 offY;
    /* 0x20 */ f32 offZ;
    /* 0x24 */ f32 turnRate;
    /* 0x28 */ f32 speed;
    /* 0x2C */ u8 pad2C[4];
    /* 0x30 */ f32 accel;
    /* 0x34 */ f32 targetSpeed;
    /* 0x38 */ f32 scale;
    /* 0x3C */ f32 distSq;
    /* 0x40 */ u8 frame;
    /* 0x41 */ u8 pad41;
    /* 0x42 */ s16 anim;
    /* 0x44 */ s16 prevAnim;
    /* 0x46 */ u8 pad46[2];
    /* 0x48 */ f32 flapA;
    /* 0x4C */ f32 flapB;
    /* 0x50 */ u8 zoneIdx;
    /* 0x51 */ u8 pad51[3];
    /* 0x54 */ CritterZone *zone;
    /* 0x58 */ CritterZone *homeZone;
    /* 0x5C */ u8 pad5C[4];
    /* 0x60 */ Mtx mtx[3][2];
    /* 0x1E0 */ u8 state;
    /* 0x1E1 */ u8 flags;
    /* 0x1E2 */ u8 role;
    /* 0x1E3 */ u8 pad1E3;
    /* 0x1E4 */ u16 texId[2];
    /* 0x1E8 */ void *tex[2];
} CritterObj;

typedef struct CritterGroup {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 zoneCount;
    /* 0x02 */ u8 count;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ CritterZone *zones;
    /* 0x08 */ CritterObj *objs;
} CritterGroup;

typedef struct CritterGroups {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ CritterGroup *groups;
} CritterGroups;

typedef struct CritterZoneRow {
    CritterZoneShape shape;
    s16 yOffset;
    s16 pad16;
} CritterZoneRow;

// This TU's .data (0x800297F0-0x80029F80), in address order: IDO emits .data in definition order, so the
// texIds templates of critterInitGroupType3/2 and critterScaleFactor follow with those functions below.
// Type 3 critter wing quads (critterDrawObjType3).
Vtx critterType3LeftWingVtx[4] = {
    {{ { -28, 28, -20 }, 0, { 1024, 1024 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -28, 28, 20 }, 0, { 1024, 0 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 0, 20 }, 0, { 0, 0 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 0, -20 }, 0, { 0, 1024 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
};
Vtx critterType3RightWingVtx[4] = {
    {{ { 0, 0, -20 }, 0, { 0, 1024 }, { 0xA5, 0xA5, 0xA5, 0xFF } }},
    {{ { 0, 0, 20 }, 0, { 0, 0 }, { 0xA5, 0xA5, 0x78, 0xFF } }},
    {{ { 28, 28, 20 }, 0, { 1024, 0 }, { 0xA5, 0xA5, 0xA5, 0xFF } }},
    {{ { 28, 28, -20 }, 0, { 1024, 1024 }, { 0xA5, 0xA5, 0xA5, 0xFF } }},
};
// Type 1 critter (critterDrawObjType1): body 0-5 (critterType1BodyDL), wings 6-9 and 7-12.
Vtx critterType1Vtx[13] = {
    {{ { 0, 9, 12 }, 0, { 285, 493 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -4, 33 }, 0, { -13, 305 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 13, -6, 12 }, 0, { 286, 265 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -13, -6, 12 }, 0, { 286, 265 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -21, 13 }, 0, { 268, 48 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -13, -40 }, 0, { 1028, 160 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 13, -6, 12 }, 0, { 157, 105 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -13, -40 }, 0, { 1024, 0 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 5, 93, -22 }, 0, { 646, 1598 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 18, 83, 31 }, 0, { -215, 1451 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -18, 83, 31 }, 0, { -215, 1451 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -5, 93, -22 }, 0, { 646, 1598 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -13, -6, 12 }, 0, { 157, 105 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
};
// Type 2 critter (critterDrawObjType2).
Vtx critterType2TailVtx[4] = {
    {{ { 0, -4, 0 }, 0, { 975, 436 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -24, -31 }, 0, { 1512, 94 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 26, -31 }, 0, { 1512, 944 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 5, 0 }, 0, { 975, 589 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
};
Vtx critterType2BodyVtx[9] = {
    {{ { -9, 1, 10 }, 0, { 335, 512 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -26, -14 }, 0, { 756, 49 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -21, 10 }, 0, { 332, 138 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 28, -14 }, 0, { 756, 975 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 5, -27 }, 0, { 975, 589 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 9, 1, 10 }, 0, { 335, 512 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, -4, -27 }, 0, { 975, 436 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 23, 10 }, 0, { 332, 886 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 1, 29 }, 0, { 14, 512 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
};
// Type 4 critter (critterDrawObjType4).
Vtx critterType4Vtx[11] = {
    {{ { -19, 13, 6 }, 0, { 418, 222 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 0, 23, -26 }, 0, { 938, 376 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -18, 0, -17 }, 0, { 797, 16 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 29, -11 }, 0, { 691, 477 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { -23, 0, 0 }, 0, { 505, 16 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 0, 31 }, 0, { -3, 16 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 26, 11 }, 0, { 331, 428 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 0, 0, -31 }, 0, { 1024, 16 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 18, 0, -17 }, 0, { 797, 16 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
    {{ { 19, 13, 6 }, 0, { 418, 222 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 23, 0, 0 }, 0, { 505, 16 }, { 0xFE, 0xFE, 0xFE, 0xFF } }},
};
// Render state shared by every critter type's setup list.
Gfx critterRenderStateDL[11] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsDPSetTextureLOD(G_TL_TILE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};
// Per-type setup lists selected by critterRenderGroup (type 3, types 0/1).
Gfx critterType3SetupDL[3] = {
    gsSPDisplayList(critterRenderStateDL),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPEndDisplayList(),
};
Gfx critterType1SetupDL[2] = {
    gsSPDisplayList(critterRenderStateDL),
    gsSPEndDisplayList(),
};
Gfx critterType1BodyDL[7] = {
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(4, 1, 3, 0, 4, 2, 1, 0),
    gsSP2Triangles(0, 2, 5, 0, 3, 0, 5, 0),
    gsSP2Triangles(4, 3, 5, 0, 2, 4, 5, 0),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPEndDisplayList(),
};
// Setup lists for types 2 and 4.
Gfx critterType2SetupDL[2] = {
    gsSPDisplayList(critterRenderStateDL),
    gsSPEndDisplayList(),
};
Gfx critterType4SetupDL[3] = {
    gsSPDisplayList(critterRenderStateDL),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
CritterGroups *critterGroups = NULL;
CritterZone *critterPlayerZone = NULL;
void *critterCurrentTexture = NULL;
// Player proximity zone per character (gPlayerCharacterId) and group row (critterUpdateGroups).
CritterZoneRow critterPlayerZoneRows[8][5] = {
    {
        { { 15, 225, 14, 40, 0, 0, 55, 3025 }, 20, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 15, 225, 16, 30, 0, 0, 45, 2025 }, 12, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 15, 225, 12, 40, 0, 0, 55, 3025 }, 14, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 15, 225, 14, 30, 0, 0, 45, 2025 }, 10, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 18, 324, 16, 40, 0, 0, 58, 3364 }, 20, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 18, 324, 18, 30, 0, 0, 48, 2304 }, 12, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 15, 225, 16, 40, 0, 0, 55, 3025 }, 20, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 15, 225, 18, 30, 0, 0, 45, 2025 }, 12, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 21, 441, 24, 40, 0, 0, 61, 3721 }, 24, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 21, 441, 28, 30, 0, 0, 51, 2601 }, 18, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 21, 441, 24, 40, 0, 0, 61, 3721 }, 24, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 21, 441, 28, 30, 0, 0, 51, 2601 }, 18, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 30, 900, 28, 40, 0, 0, 70, 4900 }, 30, 0 },
        { { 20, 400, 24, 40, 0, 0, 60, 3600 }, 0, 0 },
        { { 30, 900, 32, 30, 0, 0, 60, 3600 }, 22, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
    {
        { { 15, 225, 12, 40, 0, 0, 55, 3025 }, 14, 0 },
        { { 20, 400, 24, 20, 0, 0, 40, 1600 }, -10, 0 },
        { { 15, 225, 14, 30, 0, 0, 45, 2025 }, 10, 0 },
        { { 14, 196, 12, 20, 0, 0, 34, 1156 }, 8, 0 },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0 },
    },
};

void critterSetTargetSpeed(CritterObj *obj, CritterGroup *grp, f32 baseSpeed) {
    switch (grp->type) {
    case 0:
    case 1:
        obj->targetSpeed = baseSpeed * 3.0;
        return;
    case 2:
        obj->targetSpeed = baseSpeed * 0.5;
        return;
    case 3:
        obj->targetSpeed = baseSpeed * 1.1;
        return;
    case 4:
        obj->targetSpeed = (f64)baseSpeed + baseSpeed;
    default:
        return;
    }
}

void critterInitGroupType4(CritterGroup *grp) {
    s32 i;
    CritterObj *obj;

    obj = grp->objs;
    for (i = 0; i < grp->count; i++, obj++) {
        obj->turnRate = 7.0f;
        obj->texId[0] = 0x82;
        obj->flags |= 2;
    }
}

void critterInitGroupType01(CritterGroup *grp) {
    s32 tex0;
    s32 tex1;
    s32 i;
    CritterObj *obj;

    obj = grp->objs;
    tex0 = 0x7A;
    tex1 = 0x7B;
    if (grp->type == 1) {
        tex0 = 0x80;
        tex1 = 0x81;
    }
    for (i = 0; i < grp->count; i++, obj++) {
        obj->turnRate = 5.0f;
        obj->texId[0] = tex0;
        obj->texId[1] = tex1;
    }
}

void critterInitGroupType3(CritterGroup *grp) {
    CritterObj *obj = grp->objs;
    s32 i;
    s16 texIds[3] = { 0x77, 0x78, 0x79 };
    u8 idx;

    idx = 0;
    for (i = 0; i < grp->count; i++, obj++) {
        if ((idx == 0 && grp->count * 0.4 < i) || (idx == 1 && grp->count * 0.7 < i)) {
            idx++;
        }
        obj->turnRate = 10.0f;
        obj->texId[0] = texIds[idx];
        obj->tex[0] = NULL;
    }
}

void critterInitGroupType2(CritterGroup *grp) {
    CritterObj *obj = grp->objs;
    s32 i;
    s16 texIds[4] = { 0x7C, 0x7D, 0x7E, 0x7F };
    u8 idx;

    idx = 0;
    for (i = 0; i < grp->count; i++, obj++) {
        if ((idx == 0 && grp->count * 0.3 < i) || (idx == 1 && grp->count * 0.5 < i) || (idx == 2 && grp->count * 0.7 < i)) {
            idx++;
        }
        obj->turnRate = 20.0f;
        obj->texId[0] = texIds[idx];
        obj->tex[0] = NULL;
        obj->flags |= 4;
        critterSetTargetSpeed(obj, grp, obj->scale * 0.5);
    }
}
// After the texIds templates above: the end of this TU's .data.
f32 critterScaleFactor = 2.0f;


void critterPlayAudio(CritterObj *obj) {
    s32 i;
    u16 texId;

    for (i = 0; i < 2; i++) {
        if (texId = obj->texId[i]) {
            if (obj->tex[i] == 0) {
                obj->tex[i] = assetLoad(0xE, texId, 0, 0);
            }
        }
    }
}


void critterStopAudio(CritterObj *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        void *tex = obj->tex[i];
        if (tex != 0) {
            assetFreeBuffer(tex, 0x179, 0x5A);
            obj->tex[i] = 0;
        }
    }
}


void critterUpdateAudio(CritterObj *obj) {
    if (obj->flags & 1) {
        critterPlayAudio(obj);
    } else {
        critterStopAudio(obj);
    }
}

extern u8 gAmbientIndoors;

void critterUpdateObjType1(CritterObj *obj) {
    s16 randVal;
    f32 flap;
    f32 speedScaled;

    if (obj->state != 0 && (obj->flags & 1)) {
        randVal = randomLcgNext() % 255U;
        speedScaled = obj->speed * (1.0 / 3.0);
        if (randVal < 6) {
            sfxPlayAtPositionPooled(obj->x, obj->y, obj->z,
                          (randomLcgNext() & 3) + 0x1A9,
                          0xFF, 0x7F, 0x1E, 0x5A, 0.7f, 0);
        }
        obj->anim += 1200.0f * speedScaled;
        obj->anim &= 0xFFF;
        if (obj->prevAnim > 0x800) {
            if (obj->anim < 0x800) {
                sfxPlayAtPosition(obj->x, obj->y, obj->z, 0x5E,
                                  gAmbientIndoors * 100 + 0x73, 2.0f, 0x1E, 0x4B);
            }
        } else {
            if (obj->anim > 0x800) {
                sfxPlayAtPosition(obj->x, obj->y, obj->z, 0x5F,
                                  gAmbientIndoors * 100 + 0x73, 2.0f, 0x1E, 0x4B);
            }
        }
        flap = 1.0f - mathCosF(obj->anim);
        obj->flapA = 60.0f * flap;
        obj->yBob = obj->speed * flap * 0.5;
    }
    critterUpdateAudio(obj);
}

extern u8 gGfxBufferIndex;

Gfx *critterDrawObjType1(Gfx *gdl, CritterObj *obj) {
    f32 rotMtx[4][4];
    f32 flapAngle;

    flapAngle = obj->flapA;
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gDPLoadTextureBlock(gdl++, obj->tex[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, critterType1Vtx, 6, 0);
    gSPDisplayList(gdl++, critterType1BodyDL);
    gDPLoadTextureBlock(gdl++, obj->tex[1], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 48, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    matrixMakeRotationZ(rotMtx, -flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[1][gGfxBufferIndex]);
    gSPMatrix(gdl++, &obj->mtx[1][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &critterType1Vtx[6], 4, 6);
    gSP2Triangles(gdl++, 6, 7, 8, 0, 6, 8, 9, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    matrixMakeRotationZ(rotMtx, flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[2][gGfxBufferIndex]);
    gSPMatrix(gdl++, &obj->mtx[2][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &critterType1Vtx[7], 6, 7);
    gSP2Triangles(gdl++, 10, 11, 7, 0, 10, 7, 12, 0);
    critterCurrentTexture = NULL;
    gDPPipeSync(gdl++);
    return gdl;
}


void critterUpdateObjType3(CritterObj *obj) {
    f32 sinVal;
    f32 speedScaled;

    if (obj->flags & 1) {
        speedScaled = obj->speed * (1.0 / 1.1);
        obj->anim += 90.0 * (0.5 + 10.0f * speedScaled);
        obj->anim &= 0xFFF;
        sinVal = mathSinF(obj->anim);
        obj->flapA = (((-15.0f * speedScaled) + 45.0f) * sinVal) + (speedScaled * 30.0f);
        obj->yBob = obj->speed * sinVal * 0.4;
    }
    critterUpdateAudio(obj);
}

Gfx *critterDrawObjType3(Gfx *gdl, CritterObj *obj) {
    f32 rotMtx[4][4];
    f32 flapAngle;

    flapAngle = obj->flapA;
    if (critterCurrentTexture != obj->tex[0]) {
        critterCurrentTexture = obj->tex[0];
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    matrixMakeRotationZ(rotMtx, flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[1][gGfxBufferIndex]);
    gSPMatrix(gdl++, &obj->mtx[1][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, critterType3LeftWingVtx, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    matrixMakeRotationZ(rotMtx, -flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[2][gGfxBufferIndex]);
    gSPMatrix(gdl++, &obj->mtx[2][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, critterType3RightWingVtx, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gDPPipeSync(gdl++);
    return gdl;
}

extern EffectGridAsset gEffectSpriteBubble;

void critterUpdateObjType2(CritterObj *obj) {
    s16 randVal;
    f32 accel;
    f32 finWave;
    f32 accelVal;
    s16 yawDelta;
    f32 wave;
    s32 absYawDelta;

    if (obj->flags & 1) {
        randVal = randomLcgNext() % 400U;
        accel = obj->accel;
        if (accel < 0.0f) {
            accelVal = 0.0f;
        } else {
            accelVal = accel;
        }
        yawDelta = mathAngleSignedDistance(obj->yaw, obj->prevYaw);
        if (randVal <= 0) {
            effectSetDepth(1);
            effectSetSpeed(1);
            effectSetDuration(-1);
            effectSetCallback(effectWobbleRiseUpdate);
            effectCreateAtPosition(&gEffectSpriteBubble, 0.0f, obj->x, obj->y, obj->z);
        }
        if (yawDelta > 0) {
            absYawDelta = yawDelta;
        } else {
            absYawDelta = -yawDelta;
        }
        if (absYawDelta >= 0x5B) {
            sfxPlayAtPositionPooled(obj->x, obj->y, obj->z, 0x16F, 0x46, 0xDC, 0x1E, 0x5A, 0.7f, 0);
        }
        obj->anim += 200.0 * (1.5 + 150.0f * obj->accel);
        obj->anim &= 0xFFF;
        wave = mathSinF(obj->anim) * (10.0f + 200.0f * accelVal);
        finWave = wave;
        finWave += wave * (yawDelta * 0.00024414062f);
        obj->flapB = mathSinF(obj->anim + 0xC8) * 2;
        obj->flapA = finWave + yawDelta * 0.2;
    }
    critterUpdateAudio(obj);
}

Gfx *critterDrawObjType2(Gfx *gdl, CritterObj *obj) {
    f32 rotMtx[4][4];
    f32 transMtx[4][4];

    if (critterCurrentTexture != obj->tex[0]) {
        critterCurrentTexture = obj->tex[0];
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    matrixMakeRotationY(rotMtx, obj->flapB);
    guMtxF2L(rotMtx, &obj->mtx[2][gGfxBufferIndex]);
    gSPMatrix(gdl++, &obj->mtx[2][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPClearGeometryMode(gdl++, G_CULL_BOTH);
    guTranslateF(transMtx, 0.0f, 0.0f, -27.0f);
    matrixMakeRotationY(rotMtx, obj->flapA);
    guMtxCatF(rotMtx, transMtx, rotMtx);
    guMtxF2L(rotMtx, &obj->mtx[1][gGfxBufferIndex]);
    gSPMatrix(gdl++, &obj->mtx[1][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, critterType2TailVtx, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 2, 3, 0, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gSPVertex(gdl++, critterType2BodyVtx, 9, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 3, 4, 0);
    gSP2Triangles(gdl++, 5, 1, 6, 0, 4, 3, 5, 0);
    gSP2Triangles(gdl++, 0, 4, 6, 0, 0, 6, 1, 0);
    gSP2Triangles(gdl++, 4, 5, 6, 0, 5, 2, 1, 0);
    gSP2Triangles(gdl++, 0, 7, 3, 0, 3, 7, 5, 0);
    gSP2Triangles(gdl++, 2, 5, 8, 0, 2, 8, 0, 0);
    gSP2Triangles(gdl++, 0, 8, 7, 0, 7, 8, 5, 0);
    gDPPipeSync(gdl++);
    return gdl;
}



void critterUpdateObjType4(CritterObj *obj) {
    if (obj->state != 0 && (obj->flags & 1) && (s16)(randomLcgNext() % 255U) < 6) {
        sfxPlayAtPositionPooled(obj->x, obj->y, obj->z,
                      (randomLcgNext() & 3) + 0x1A9,
                      0xFF, 0x5A, 0x1E, 0x5A, 0.7f, 0);
    }
    critterUpdateAudio(obj);
}

Gfx *critterDrawObjType4(Gfx *gdl, CritterObj *obj) {
    if (critterCurrentTexture != obj->tex[0]) {
        critterCurrentTexture = obj->tex[0];
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, critterType4Vtx, 11, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 3, 1, 0);
    gSP2Triangles(gdl++, 0, 2, 4, 0, 0, 5, 6, 0);
    gSP2Triangles(gdl++, 0, 4, 5, 0, 0, 6, 3, 0);
    gSP2Triangles(gdl++, 7, 2, 1, 0, 1, 8, 7, 0);
    gSP2Triangles(gdl++, 3, 6, 9, 0, 5, 10, 9, 0);
    gSP2Triangles(gdl++, 6, 5, 9, 0, 10, 8, 9, 0);
    gSP2Triangles(gdl++, 1, 3, 9, 0, 8, 1, 9, 0);
    gDPPipeSync(gdl++);
    return gdl;
}

extern Gfx D_1000118;
extern u8 gCurrentPlayerIndex;
extern PlayerStruct *gPlayerSlots;
extern Mtx D_2000200;
extern Mtx D_2000180;

Gfx *critterRenderSetup(Gfx *gdl) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPLoadGeometryMode(gdl++, 0);
    gSPMatrix(gdl++, &gPlayerSlots[gCurrentPlayerIndex].projMtx[gGfxBufferIndex], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    return gdl;
}

void critterMakeMatrix(f32 (*m)[4], s16 pitch, s16 yaw, s16 roll, f32 scale, f32 x, f32 y, f32 z) {
    f32 pad;
    f32 sinYaw;
    f32 sinRoll;
    f32 pad2;
    f32 cosYaw;
    f32 sinPitchSinYaw;
    f32 cosPitchSinYaw;
    f32 sinPitch;
    f32 cosPitch;
    f32 cosRoll;

    sinPitch = mathSinF(pitch);
    cosPitch = mathCosF(pitch);
    sinYaw = mathSinF(yaw);
    cosYaw = mathCosF(yaw);
    sinRoll = mathSinF(roll);
    cosRoll = mathCosF(roll);
    m[0][0] = cosYaw * cosRoll * scale;
    m[0][1] = cosYaw * sinRoll * scale;
    m[0][2] = -sinYaw * scale;
    m[0][3] = 0.0f;
    sinPitchSinYaw = sinPitch * sinYaw;
    m[1][0] = ((sinPitchSinYaw * cosRoll) - (cosPitch * sinRoll)) * scale;
    m[1][3] = 0.0f;
    m[1][1] = ((sinPitchSinYaw * sinRoll) + (cosPitch * cosRoll)) * scale;
    m[1][2] = sinPitch * cosYaw * scale;
    cosPitchSinYaw = cosPitch * sinYaw;
    m[2][0] = ((cosPitchSinYaw * cosRoll) + (sinPitch * sinRoll)) * scale;
    m[2][3] = 0.0f;
    m[2][1] = ((cosPitchSinYaw * sinRoll) - (sinPitch * cosRoll)) * scale;
    m[2][2] = cosPitch * cosYaw * scale;
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    m[3][3] = 1.0f;
}

void critterBuildMatrix(CritterObj *obj) {
    f32 transMtx[4][4];

    critterMakeMatrix(transMtx, -obj->pitch, obj->yaw, 0,
                  obj->scale * 0.07f,
                  obj->x,
                  obj->y + obj->yBob,
                  obj->z);
    guMtxF2L(transMtx, &obj->mtx[0][gGfxBufferIndex]);
}

extern s32 gMapChunkCount;

Gfx *critterRenderGroup(Gfx *gdl, CritterGroup *grp) {
    s32 pad;
    s32 i;
    CritterObj *obj;
    u8 r;
    u8 g;
    u8 b;
    Gfx *(*drawFn)(Gfx *, CritterObj *);

    obj = grp->objs;
    switch (grp->type) {
    case 0:
    case 1:
        gSPDisplayList(gdl++, critterType1SetupDL);
        drawFn = critterDrawObjType1;
        break;
    case 3:
        gSPDisplayList(gdl++, critterType3SetupDL);
        drawFn = critterDrawObjType3;
        break;
    case 2:
        gSPDisplayList(gdl++, critterType2SetupDL);
        drawFn = critterDrawObjType2;
        break;
    case 4:
        gSPDisplayList(gdl++, critterType4SetupDL);
        drawFn = critterDrawObjType4;
        break;
    }
    for (i = 0; i < grp->count; i++, obj++) {
        if (gMapChunkCount != 0) {
            lightSampleColorAtPosition(obj->x, obj->y, obj->z, 0, &r, &g, &b, obj->homeZone->chunkIdx);
        } else {
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
        }
        gDPPipeSync(gdl++);
        gDPSetPrimColor(gdl++, 0, 0, r, g, b, obj->homeZone->alpha);
        if (obj->flags & 1) {
            gdl = drawFn(gdl, obj);
        }
    }
    gDPPipeSync(gdl++);
    return gdl;
}

Gfx *critterRenderGroups(Gfx *gdl, CritterGroups *groups) {
    CritterGroup *grp;
    s32 i;

    if (groups == NULL) {
        return gdl;
    }
    critterCurrentTexture = NULL;
    grp = groups->groups;
    if (grp != NULL) {
        gdl = critterRenderSetup(gdl);
    }
    for (i = 0; i < groups->count; i++) {
        gdl = critterRenderGroup(gdl, grp);
        grp++;
    }
    return gdl;
}


void critterSetOffsetAtAngle(CritterZone *zone, CritterObj *obj, u8 mode, s16 yaw, u8 heightOffset) {
    f32 dist;
    f32 pad;
    f32 base;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 height;

    base = zone->shape.height;
    if (mode == 0) {
        dist = zone->shape.ringRadius;
        base += zone->shape.extraHeight;
    } else {
        dist = zone->shape.radius * ((randomLcgNext() & 0xFFFU) * 0.000244140625f);
    }
    height = (randomLcgNext() & 0xFFFU) * 0.000244140625f * base - 0.5 * base;
    if (heightOffset != 0) {
        px = &obj->offX;
        py = &obj->offY;
        pz = &obj->offZ;
    } else {
        px = &obj->x;
        py = &obj->y;
        pz = &obj->z;
    }
    *py = height;
    *px = mathSinF(yaw) * dist;
    *pz = mathCosF(yaw) * dist;
}

void critterSetRandomOffset(CritterZone *zone, CritterObj *obj, u8 mode, u8 heightOffset) {
    critterSetOffsetAtAngle(zone, obj, mode, randomLcgNext() & 0xFFF, heightOffset);
}

void critterPlaceInZone(CritterZone *zone, CritterObj *obj, u8 isRandom) {
    critterSetRandomOffset(zone, obj, isRandom, 0);
    obj->x += zone->x;
    obj->y += zone->y;
    obj->z += zone->z;
}

extern Actor *gActivePlayerActor;

void critterUpdateZoneProximity(CritterObj *obj) {
    f32 lim;
    f32 fade;
    f32 playerDistSq;
    f32 camDistSq;
    s16 half;
    s32 f;

    lim = obj->homeZone->shape.nearDistSq + 0x1DE84;
    if (obj->homeZone->frame != gGfxBufferIndex) {
        half = (obj->homeZone->shape.height + obj->homeZone->shape.extraHeight) >> 1;
        playerDistSq = (obj->homeZone->x - gActivePlayerActor->x) * (obj->homeZone->x - gActivePlayerActor->x) + (obj->homeZone->z - gActivePlayerActor->z) * (obj->homeZone->z - gActivePlayerActor->z);
        fade = 0.0f;
        f = critterPlayerZone->y < obj->homeZone->y + half;
        if (f) {
            f = obj->homeZone->y - half < critterPlayerZone->y;
        }
        f = (u8)f != 0; // ORIG: the target narrows the in-height flag and re-tests it (andi t5,a3,0xff; sltu a3,zero,t5 at 0x20cc)
        if (f) {
            f = 0;
            if (playerDistSq < obj->homeZone->shape.nearDistSq) {
                f = 1;
            }
        }
        obj->homeZone->near = f;
        obj->homeZone->frame = gGfxBufferIndex;
        camDistSq = (obj->homeZone->x - gPlayerSlots[gCurrentPlayerIndex].camX) * (obj->homeZone->x - gPlayerSlots[gCurrentPlayerIndex].camX) +
                    (obj->homeZone->y - gPlayerSlots[gCurrentPlayerIndex].camY) * (obj->homeZone->y - gPlayerSlots[gCurrentPlayerIndex].camY) +
                    (obj->homeZone->z - gPlayerSlots[gCurrentPlayerIndex].camZ) * (obj->homeZone->z - gPlayerSlots[gCurrentPlayerIndex].camZ);
        obj->homeZone->distSq = camDistSq;
        if (camDistSq < lim) {
            fade = (lim - camDistSq) * 0.000051020408f;
            if (fade > 1.0f) {
                fade = 1.0f;
            }
        }
        obj->homeZone->alpha = 255.0f * fade;
    }
    if (obj->homeZone->distSq < lim) {
        obj->flags |= 1;
    } else {
        obj->flags &= ~1;
    }
}

CritterZone *critterGetZone(CritterGroup *grp, u8 idx) {
    CritterZone *zones = grp->zones;
    return zones + idx;
}

void critterPickNewZone(CritterObj *obj, CritterGroup *grp) {
    u8 idx;

    idx = randomLcgNext() % (grp->zoneCount - 1);
    if (idx >= obj->zoneIdx) {
        idx++;
    }
    obj->zoneIdx = idx;
    obj->zone = critterGetZone(grp, idx);
}


void critterTryActivate(CritterObj *obj, CritterGroup *grp) {
    s32 lim;

    switch (grp->type) {
    default:
        lim = 0x1900;
        break;
    case 3:
        lim = 0x1900;
        break;
    case 0:
    case 1:
        lim = 0x57E4;
        break;
    }
    if (obj->distSq < lim) {
        if (obj->homeZone->near != 0) {
            obj->state = 2;
            if (obj->role == 0) {
                obj->zone = critterPlayerZone;
            } else {
                critterPickNewZone(obj, grp);
            }
            critterSetRandomOffset(obj->zone, obj, 1, 1);
            critterSetTargetSpeed(obj, grp, obj->scale);
        }
    }
}


void critterCalcDistToPlayer(CritterObj *obj) {
    f32 dx;
    f32 dz;

    if (obj->frame != gGfxBufferIndex) {
        dx = obj->x - gActivePlayerActor->x;
        dz = obj->z - gActivePlayerActor->z;
        obj->distSq = (dx * dx) + (dz * dz);
        obj->frame = gGfxBufferIndex;
    }
}

void critterFollowLeader(CritterObj *obj, CritterObj *leader) {
    obj->speed = leader->speed;
    obj->homeZone = leader->homeZone;
    obj->flags = leader->flags;
    if (obj->zone != leader->zone) {
        obj->zone = leader->zone;
        critterSetRandomOffset(obj->zone, obj, 1, 1);
    }
    obj->state = leader->state;
    if (obj->state == 0 && !(obj->flags & 4)) {
        obj->pitch = 0;
        return;
    }
    if (randomLcgNext() % 255U < 50) {
        critterSetRandomOffset(obj->zone, obj, 1, 1);
    }
}


s32 critterSteerToTargetCallback(CritterObj *obj, CritterGroup *grp) {
    critterSetTargetSpeed(obj, grp, obj->scale * 0.5);
    critterSetRandomOffset(obj->zone, obj, 1, 1);
    return 0;
}

f32 mathTanF(s16);

void critterSteerToTarget(CritterObj *obj, CritterGroup *grp, void (*steerFunc)(CritterObj *, CritterGroup *), s32 (*targetPred)(CritterObj *, CritterGroup *)) {
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 pad;
    f32 distSq;
    f32 prevSpeed;
    f32 targetSpeed;
    f32 speed;
    f32 rate;
    CritterZone *zone;
    s32 reached;
    s16 targetYaw;
    s32 useY;

    rate = 0.02f;
    useY = (obj->flags & 2) == 0;
    if (steerFunc != NULL) {
        steerFunc(obj, grp);
    }
    zone = obj->zone;
    tx = obj->offX + zone->x;
    ty = obj->offY + zone->y;
    tz = obj->offZ + zone->z;
    dx = tx - obj->x;
    dy = ty - obj->y;
    dz = tz - obj->z;
    if (obj->role != 2) {
        distSq = dx * dx + dz * dz;
        if ((u8)useY) {
            distSq += dy * dy;
        }
        targetSpeed = obj->targetSpeed;
        if (distSq < 2500.0f) {
            targetSpeed = targetSpeed * 0.3 + 0.7 * targetSpeed * (distSq * 0.0004f);
            rate = 0.1f;
            if (distSq < 25.0f && targetPred != NULL) {
                reached = targetPred(obj, grp);
                if (reached != 0) {
                    return;
                }
            }
        }
        prevSpeed = obj->speed;
        obj->speed += (targetSpeed - prevSpeed) * rate;
        obj->accel = obj->speed - prevSpeed;
    }
    dist = sqrtf(dx * dx + dz * dz);
    if ((u8)useY) {
        obj->pitch = mathAngleEaseToward(obj->pitch, mathAtan2(dy, dist) * 2048.0 / 3.1415927410125732, obj->turnRate);
    }
    targetYaw = mathAngleDiscrete(tx, tz, obj->x, obj->z, dist);
    obj->prevYaw = obj->yaw;
    obj->yaw = mathAngleEaseToward(obj->yaw, targetYaw, obj->turnRate);
    speed = obj->speed;
    obj->x += speed * mathSinF(obj->yaw);
    obj->z += speed * mathCosF(obj->yaw);
    if ((u8)useY) {
        obj->y += speed * mathTanF(obj->pitch);
    }
}

void critterUpdateIdle(CritterObj *obj, CritterGroup *grp) {
    u8 flags;

    flags = obj->flags;
    if ((flags & 1) && (flags & 4)) {
        critterSteerToTarget(obj, grp, NULL, critterSteerToTargetCallback);
    }
    if (obj->role == 2) {
        critterFollowLeader(obj, grp->objs);
        return;
    }
    if (obj->homeZone->near != 0) {
        critterCalcDistToPlayer(obj);
        critterTryActivate(obj, grp);
    }
}


void critterUpdateFollowTarget(CritterObj *obj, CritterGroup *grp) {
    s16 angleDiff;
    CritterZone *home;

    if (obj->role == 2) {
        critterFollowLeader(obj, grp->objs);
        return;
    }
    if (obj->role == 0) {
        home = obj->homeZone;
        if (home->near != 0) {
            critterCalcDistToPlayer(obj);
            if (critterPlayerZone != obj->zone) {
                critterTryActivate(obj, grp);
                return;
            }
            if (obj->state == 2 && obj->distSq < critterPlayerZone->shape.reactDistSq) {
                angleDiff = mathAngleBetweenPoints2D(obj->x, obj->z, gActivePlayerActor->x, gActivePlayerActor->z);
                angleDiff += (randomLcgNext() & 0x7FF) - 0x400;
                obj->state = 1;
                critterSetOffsetAtAngle(obj->zone, obj, 0, angleDiff, 1);
            }
        } else if (critterPlayerZone == obj->zone) {
            obj->zone = home;
            critterSetRandomOffset(home, obj, 1, 1);
            obj->frame = 0xFF;
        }
    }
}

s32 critterCheckZoneState(CritterObj *obj, CritterGroup *grp) {
    CritterZone *zone;

    if (obj->role == 1) {
        zone = obj->zone;
        obj->homeZone = zone;
        if (zone->flags & 1) {
            obj->pitch = 0;
            obj->state = 0;
            obj->speed = 0.0f;
            obj->targetSpeed = 0;
            return 1;
        }
        critterPickNewZone(obj, grp);
    } else if (critterPlayerZone == obj->zone) {
        if (obj->state == 2) {
            obj->state = 1;
        } else {
            obj->state = 2;
        }
        critterSetRandomOffset(obj->zone, obj, obj->state == 2, 1);
    } else {
        obj->pitch = 0;
        obj->targetSpeed = 0;
        if (obj->speed < 0.05) {
            obj->state = 0;
            obj->speed = 0.0f;
            return 1;
        }
    }
    return 0;
}

void critterDispatchAll(CritterGroup *grp) {
    void (*updateFn)(CritterObj *);
    s32 objIdx;
    CritterObj *obj;

    obj = grp->objs;
    switch (grp->type) {
    case 0:
    case 1:
        updateFn = critterUpdateObjType1;
        break;
    case 2:
        updateFn = critterUpdateObjType2;
        break;
    case 3:
        updateFn = critterUpdateObjType3;
        break;
    case 4:
        updateFn = critterUpdateObjType4;
        break;
    default:
        updateFn = NULL;
        break;
    }
    for (objIdx = 0; objIdx < grp->count; objIdx++, obj++) {
        critterUpdateZoneProximity(obj);
        if (obj->state == 0) {
            critterUpdateIdle(obj, grp);
        } else {
            critterSteerToTarget(obj, grp, critterUpdateFollowTarget, critterCheckZoneState);
        }
        obj->prevAnim = obj->anim;
        if (updateFn != NULL) {
            updateFn(obj);
        }
    }
}

void critterUpdateGroups(CritterGroups *groups) {
    s32 i;
    CritterGroup *grp;
    CritterZoneRow *rows;
    CritterZoneRow *row;
    s16 rowIdx;
    u8 character = gPlayerCharacterId[0];

    if (groups != NULL) {
        grp = groups->groups;
        rows = critterPlayerZoneRows[character];
        critterPlayerZone->x = gActivePlayerActor->x;
        critterPlayerZone->z = gActivePlayerActor->z;
        for (i = 0; i < groups->count; i++, grp++) {
            rowIdx = grp->type;
            if (rowIdx > 0) {
                rowIdx--;
            }
            row = &rows[rowIdx];
            critterPlayerZone->y = gActivePlayerActor->y + row->yOffset;
            critterPlayerZone->shape = row->shape;
            critterDispatchAll(grp);
        }
    }
}

void critterLoadData(u8 *data) {
    s32 groupIdx;
    CritterGroup *grp;
    CritterZone *zone;
    s32 zoneIdx;
    u8 *src;

    if (data != NULL) {
        memcpy(critterGroups, data, 1);
        src = data + 1;
        for (groupIdx = 0; groupIdx < critterGroups->count; groupIdx++) {
            if (groupIdx == 0) {
                critterGroups->groups = heapAlloc(critterGroups->count * sizeof(CritterGroup));
                heapClearBlock(critterGroups->groups);
                grp = critterGroups->groups;
            } else {
                grp++;
            }
            memcpy(grp, src, 3);
            src += 3;
            for (zoneIdx = 0; zoneIdx < grp->zoneCount; zoneIdx++) {
                if (zoneIdx == 0) {
                    grp->zones = heapAlloc(grp->zoneCount * sizeof(CritterZone));
                    heapClearBlock(grp->zones);
                    zone = grp->zones;
                } else {
                    zone++;
                }
                memcpy(zone, src, 0x20);
                if (gMapChunkCount != 0) {
                    zone->chunkIdx = mapChunkFindByPosition(zone->x, zone->y, zone->z, 0);
                    zone->frame = 0xFF;
                }
                src += 0x20;
            }
            critterInitGroup(grp);
        }
    }
}

void critterInit(void *data) {
    critterCurrentTexture = NULL;
    critterGroups = heapAlloc(sizeof(CritterGroups));
    heapClearBlock(critterGroups);
    critterLoadData(data);
    critterPlayerZone = heapAlloc(sizeof(CritterZone));
    heapClearBlock(critterPlayerZone);
}


Gfx *critterRender(Gfx *glist) {
    if (gGlobalPauseFlags & 0x10) {
        if (!(gGlobalPauseFlags & 2)) {
            critterUpdateGroups(critterGroups);
        }
        glist = critterRenderGroups(glist, critterGroups);
    }
    return glist;
}


void critterCleanup(CritterGroup *grp) {
    u8 objCount;
    CritterObj *obj;
    s32 i;

    objCount = grp->count;
    obj = grp->objs;
    for (i = 0; i < objCount && obj != NULL; i++, obj++) {
        critterStopAudio(obj);
    }
    if (grp->objs != NULL) {
        heapFreeDeferred(grp->objs);
    }
    grp->objs = NULL;
    grp->count = 0;
}

void critterInitGroup(CritterGroup *grp) {
    CritterObj *obj;
    s32 i;
    u8 role;
    void (*initFn)(CritterGroup *);

    if (grp->count == 0) {
        grp->objs = NULL;
        return;
    }
    switch (grp->type) {
    case 0:
    case 1:
        initFn = critterInitGroupType01;
        break;
    case 3:
        initFn = critterInitGroupType3;
        break;
    case 4:
        initFn = critterInitGroupType4;
        break;
    case 2:
        initFn = critterInitGroupType2;
        break;
    }
    grp->objs = heapAlloc(grp->count * sizeof(CritterObj));
    heapClearBlock(grp->objs);
    obj = grp->objs;
    if (grp->zoneCount == 1) {
        role = 0;
    } else {
        role = 1;
    }
    for (i = 0; i < grp->count; i++) {
        critterPlaceInZone(grp->zones, obj, 1);
        if (menuIsTransitionType3Or4() == 0) {
            critterSetRandomOffset(grp->zones, obj, 1, 1);
        }
        obj->zone = obj->homeZone = grp->zones;
        obj->role = role;
        obj->frame = 0xFF;
        obj->yaw = randomLcgNext() & 0xFFF;
        obj->anim = randomLcgNext() & 0xFFF;
        obj->scale = 1.0f - (randomLcgNext() % 1000U) / 4000.0f;
        obj->scale *= critterScaleFactor;
        obj++;
        if (role == 1) {
            role = 2;
        }
    }
    initFn(grp);
}
