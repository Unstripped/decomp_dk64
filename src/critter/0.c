#include "common.h"

typedef struct CritterZoneShape {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
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
    /* 0x28 */ s16 unk28;
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
    /* 0x1E8 */ s32 tex[2];
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

typedef struct CritterViewer {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ Mtx projection[2];
    /* 0x108 */ u8 pad108[0x210 - 0x108];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
    /* 0x21C */ u8 pad21C[0x2F0 - 0x21C];
} CritterViewer;

void critterSetTargetSpeed(CritterObj *obj, CritterGroup *grp, f32 baseSpeed) {
    switch (grp->type) {
    case 0:
    case 1:
        obj->targetSpeed = (f32)((f64)baseSpeed * 3.0);
        return;
    case 2:
        obj->targetSpeed = (f32)((f64)baseSpeed * 0.5);
        return;
    case 3:
        obj->targetSpeed = (f32)((f64)baseSpeed * 1.1);
        return;
    case 4:
        obj->targetSpeed = (f32)((f64)baseSpeed + (f64)baseSpeed);
    default:
        return;
    }
}

void func_8002409C(CritterGroup *grp) {
    s32 i;
    CritterObj *obj;

    obj = grp->objs;
    i = 0;
    if (grp->count > 0) {
        do {
            obj->turnRate = 7.0f;
            obj->texId[0] = 0x82;
            obj->flags |= 2;
            i++;
            obj++;
        } while (i < grp->count);
    }
}

void func_800240EC(CritterGroup *grp) {
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
    i = 0;
    if (grp->count > 0) {
        do {
            obj->turnRate = 5.0f;
            obj->texId[0] = tex0;
            obj->texId[1] = tex1;
            i++;
            obj++;
        } while (i < grp->count);
    }
}

typedef struct { s16 v[3]; } C0aTbl;
extern C0aTbl D_80029F6C;

void func_80024154(CritterGroup *grp) {
    CritterObj *obj;
    s32 i;
    C0aTbl tbl;
    u8 idx;

    obj = grp->objs;
    tbl = D_80029F6C;
    idx = 0;
    i = 0;
    if (grp->count > 0) {
        do {
            if ((idx == 0 && (f64)grp->count * 0.4 < (f64)i) || (idx == 1 && (f64)grp->count * 0.7 < (f64)i)) {
                idx++;
            }
            obj->turnRate = 10.0f;
            obj->texId[0] = tbl.v[idx];
            obj->tex[0] = 0;
            i++;
            obj++;
        } while (i < grp->count);
    }
}
typedef struct { s16 v[4]; } C0aTbl2;
extern C0aTbl2 D_80029F74;

void func_8002427C(CritterGroup *grp) {
    CritterObj *obj;
    s32 i;
    C0aTbl2 tbl;
    u8 idx;

    obj = grp->objs;
    tbl = D_80029F74;
    idx = 0;
    for (i = 0; i < grp->count; i++, obj++) {
        if ((idx == 0 && (f64)grp->count * 0.3 < (f64)i) || (idx == 1 && (f64)grp->count * 0.5 < (f64)i) || (idx == 2 && (f64)grp->count * 0.7 < (f64)i)) {
            idx++;
        }
        obj->turnRate = 20.0f;
        obj->texId[0] = tbl.v[idx];
        obj->tex[0] = 0;
        obj->flags |= 4;
        critterSetTargetSpeed(obj, grp, (f32)((f64)obj->scale * 0.5));
    }
}

s32 assetLoad(s32, s32, s32, s32);

void critterPlayAudio(CritterObj *obj) {
    s32 i;
    u16 v;

    for (i = 0; i < 2; i++) {
        if (v = obj->texId[i]) {
            if (obj->tex[i] == 0) {
                obj->tex[i] = assetLoad(0xE, v, 0, 0);
            }
        }
    }
}

void assetFreeBuffer(s32, s32, s32);

void critterStopAudio(CritterObj *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        s32 val = obj->tex[i];
        if (val != 0) {
            assetFreeBuffer(val, 0x179, 0x5A);
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

s32 randomLcgNext(void);
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void sfxPlayAtPosition(f32, f32, f32, s16, u8, f32, u8, u8);
f32 func_80612790(s16);
extern u8 D_80770DC9;

void func_800245B8(CritterObj *obj) {
    s16 r;
    f32 temp;
    f32 speedScaled;

    if (obj->state != 0 && (obj->flags & 1)) {
        r = randomLcgNext() % 255U;
        speedScaled = (f32)((f64)obj->speed * (1.0 / 3.0));
        if (r < 6) {
            sfxPlayAtPositionPooled(obj->x, obj->y, obj->z,
                          (s16)((randomLcgNext() & 3) + 0x1A9),
                          0xFF, 0x7F, 0x1E, 0x5A, 0.7f, 0);
        }
        obj->anim = (s16)((f32)obj->anim + 1200.0f * speedScaled);
        obj->anim &= 0xFFF;
        if (obj->prevAnim > 0x800) {
            if (obj->anim < 0x800) {
                sfxPlayAtPosition(obj->x, obj->y, obj->z, 0x5E,
                                  D_80770DC9 * 100 + 0x73, 2.0f, 0x1E, 0x4B);
            }
        } else {
            if (obj->anim > 0x800) {
                sfxPlayAtPosition(obj->x, obj->y, obj->z, 0x5F,
                                  D_80770DC9 * 100 + 0x73, 2.0f, 0x1E, 0x4B);
            }
        }
        temp = 1.0f - func_80612790(obj->anim);
        obj->flapA = 60.0f * temp;
        obj->yBob = (f32)((f64)(obj->speed * temp) * 0.5);
    }
    critterUpdateAudio(obj);
}

void critterBuildMatrix(CritterObj *obj);
void matrixMakeRotationZ(f32 (*)[4], f32);
extern u8 D_807444FC;
extern Vtx D_80029870;
extern Vtx D_800298D0;
extern Vtx D_800298E0;
extern Gfx D_80029B40;
extern s32 critterCurrentTexture;

Gfx *func_800247F4(Gfx *gdl, CritterObj *obj) {
    f32 rotMtx[4][4];
    f32 flapAngle;

    flapAngle = obj->flapA;
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gDPLoadTextureBlock(gdl++, obj->tex[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][D_807444FC], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, &D_80029870, 6, 0);
    gSPDisplayList(gdl++, &D_80029B40);
    gDPLoadTextureBlock(gdl++, obj->tex[1], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 48, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    matrixMakeRotationZ(rotMtx, -flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[1][D_807444FC]);
    gSPMatrix(gdl++, &obj->mtx[1][D_807444FC], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_800298D0, 4, 6);
    gSP2Triangles(gdl++, 6, 7, 8, 0, 6, 8, 9, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    matrixMakeRotationZ(rotMtx, flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[2][D_807444FC]);
    gSPMatrix(gdl++, &obj->mtx[2][D_807444FC], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_800298E0, 6, 7);
    gSP2Triangles(gdl++, 10, 11, 7, 0, 10, 7, 12, 0);
    critterCurrentTexture = 0;
    gDPPipeSync(gdl++);
    return gdl;
}

f32 func_80612794(s32);

void func_80024B78(CritterObj *obj) {
    f32 sinVal;
    f32 speedScaled;

    if (obj->flags & 1) {
        speedScaled = (f32)((f64)obj->speed * (1.0 / 1.1));
        obj->anim = (s16)((f64)obj->anim + (90.0 * (0.5 + (f64)(10.0f * speedScaled))));
        obj->anim &= 0xFFF;
        sinVal = func_80612794(obj->anim);
        obj->flapA = (((-15.0f * speedScaled) + 45.0f) * sinVal) + (speedScaled * 30.0f);
        obj->yBob = (f32)((f64)(obj->speed * sinVal) * 0.4);
    }
    critterUpdateAudio(obj);
}

extern Vtx D_800297F0;
extern Vtx D_80029830;

Gfx *func_80024C88(Gfx *gdl, CritterObj *obj) {
    f32 rotMtx[4][4];
    f32 flapAngle;

    flapAngle = obj->flapA;
    if (critterCurrentTexture != obj->tex[0]) {
        critterCurrentTexture = obj->tex[0];
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][D_807444FC], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    matrixMakeRotationZ(rotMtx, flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[1][D_807444FC]);
    gSPMatrix(gdl++, &obj->mtx[1][D_807444FC], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_800297F0, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    matrixMakeRotationZ(rotMtx, -flapAngle);
    guMtxF2L(rotMtx, &obj->mtx[2][D_807444FC]);
    gSPMatrix(gdl++, &obj->mtx[2][D_807444FC], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_80029830, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gDPPipeSync(gdl++);
    return gdl;
}

s16 mathAngleSignedDistance(s16, s16);
void func_807149B8(s32);
void func_80714950(s32);
void func_807149FC(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
extern u8 effectWobbleRiseUpdate;
extern u8 D_8071FC40;

void func_80024F28(CritterObj *obj) {
    s16 randVal;
    f32 temp;
    f32 finWave;
    f32 accelVal;
    s16 yawDelta;
    f32 temp2;
    s32 absv;

    if (obj->flags & 1) {
        randVal = randomLcgNext() % 400U;
        temp = obj->accel;
        if (temp < 0.0f) {
            accelVal = 0.0f;
        } else {
            accelVal = temp;
        }
        yawDelta = mathAngleSignedDistance(obj->yaw, obj->prevYaw);
        if (randVal <= 0) {
            func_807149B8(1);
            func_80714950(1);
            func_807149FC(-1);
            func_8071498C(&effectWobbleRiseUpdate);
            func_80714CC0(&D_8071FC40, 0, obj->x, obj->y, obj->z);
        }
        if (yawDelta > 0) {
            absv = yawDelta;
        } else {
            absv = -yawDelta;
        }
        if (absv >= 0x5B) {
            sfxPlayAtPositionPooled(obj->x, obj->y, obj->z, 0x16F, 0x46, 0xDC, 0x1E, 0x5A, 0.7f, 0);
        }
        obj->anim = (s16)((f64)obj->anim + 200.0 * (1.5 + (f64)(150.0f * obj->accel)));
        obj->anim &= 0xFFF;
        temp2 = func_80612794(obj->anim) * (10.0f + 200.0f * accelVal);
        finWave = temp2 * 1.0f + temp2 * ((f32)yawDelta * 0.00024414062f);
        obj->flapB = func_80612794((s16)(obj->anim + 0xC8)) * 2;
        obj->flapA = (f32)((f64)finWave + (f64)yawDelta * 0.2);
    }
    critterUpdateAudio(obj);
}

extern s32 critterCurrentTexture;
extern u8 D_807444FC;
void critterBuildMatrix(CritterObj *);
extern Vtx D_80029940[];
extern Vtx D_80029980[];
void matrixMakeRotationY(f32 (*)[4], f32);

Gfx *func_8002516C(Gfx *gdl, CritterObj *obj) {
    f32 tailMtx[4][4];
    f32 finTransMtx[4][4];

    if (critterCurrentTexture != obj->tex[0]) {
        critterCurrentTexture = obj->tex[0];
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][D_807444FC], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    matrixMakeRotationY(tailMtx, obj->flapB);
    guMtxF2L(tailMtx, &obj->mtx[2][D_807444FC]);
    gSPMatrix(gdl++, &obj->mtx[2][D_807444FC], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPClearGeometryMode(gdl++, G_CULL_BOTH);
    guTranslateF(finTransMtx, 0.0f, 0.0f, -27.0f);
    matrixMakeRotationY(tailMtx, obj->flapA);
    guMtxCatF(tailMtx, finTransMtx, tailMtx);
    guMtxF2L(tailMtx, &obj->mtx[1][D_807444FC]);
    gSPMatrix(gdl++, &obj->mtx[1][D_807444FC], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, D_80029940, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 2, 3, 0, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gSPVertex(gdl++, D_80029980, 9, 0);
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


s32 randomLcgNext(void);

void func_80025500(CritterObj *obj) {
    if (obj->state != 0 && (obj->flags & 1) && (s16)(randomLcgNext() % 255U) < 6) {
        sfxPlayAtPositionPooled(obj->x, obj->y, obj->z,
                      (s16)((randomLcgNext() & 3) + 0x1A9),
                      0xFF, 0x5A, 0x1E, 0x5A, 0.7f, 0);
    }
    critterUpdateAudio(obj);
}

extern Gfx D_80029A10;

Gfx *func_800255C4(Gfx *gdl, CritterObj *obj) {
    if (critterCurrentTexture != obj->tex[0]) {
        critterCurrentTexture = obj->tex[0];
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(obj);
    gSPMatrix(gdl++, &obj->mtx[0][D_807444FC], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, &D_80029A10, 11, 0);
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
extern CritterViewer *gPlayerSlots;
extern Mtx D_2000200;
extern u8 D_807444FC;
extern Mtx D_2000180;

Gfx *critterRenderSetup(Gfx *gdl) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPLoadGeometryMode(gdl++, 0);
    gSPMatrix(gdl++, &gPlayerSlots[gCurrentPlayerIndex].projection[D_807444FC], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    return gdl;
}

void critterMakeMatrix(f32 (*m)[4], s16 pitch, s16 yaw, s16 roll, f32 scale, f32 x, f32 y, f32 z) {
    f32 pad;
    f32 cosYaw;
    f32 cosRoll;
    f32 pad2;
    f32 sinYaw;
    f32 cosPitchCosYaw;
    f32 sinPitchCosYaw;
    f32 cosPitch;
    f32 sinPitch;
    f32 sinRoll;

    cosPitch = func_80612794(pitch);
    sinPitch = func_80612790(pitch);
    cosYaw = func_80612794(yaw);
    sinYaw = func_80612790(yaw);
    cosRoll = func_80612794(roll);
    sinRoll = func_80612790(roll);
    m[0][0] = sinYaw * sinRoll * scale;
    m[0][1] = sinYaw * cosRoll * scale;
    m[0][2] = -cosYaw * scale;
    m[0][3] = 0.0f;
    cosPitchCosYaw = cosPitch * cosYaw;
    m[1][0] = ((cosPitchCosYaw * sinRoll) - (sinPitch * cosRoll)) * scale;
    m[1][3] = 0.0f;
    m[1][1] = ((cosPitchCosYaw * cosRoll) + (sinPitch * sinRoll)) * scale;
    m[1][2] = cosPitch * sinYaw * scale;
    sinPitchCosYaw = sinPitch * cosYaw;
    m[2][0] = ((sinPitchCosYaw * sinRoll) + (cosPitch * cosRoll)) * scale;
    m[2][3] = 0.0f;
    m[2][1] = ((sinPitchCosYaw * cosRoll) - (cosPitch * sinRoll)) * scale;
    m[2][2] = sinPitch * sinYaw * scale;
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    m[3][3] = 1.0f;
}

void critterBuildMatrix(CritterObj *obj) {
    f32 transMtx[4][4];

    critterMakeMatrix(transMtx, (s16)-obj->pitch, obj->yaw, 0,
                  obj->scale * 0.07f,
                  obj->x,
                  obj->y + obj->yBob,
                  obj->z);
    guMtxF2L(transMtx, &obj->mtx[0][D_807444FC]);
}

extern Gfx D_80029B18;
extern Gfx D_80029B30;
extern Gfx D_80029B78;
extern Gfx D_80029B88;
extern s32 gMapChunkCount;
Gfx *func_800247F4(Gfx *, CritterObj *);
Gfx *func_80024C88(Gfx *, CritterObj *);
Gfx *func_8002516C(Gfx *, CritterObj *);
void lightSampleColorAtPosition(f32, f32, f32, s32, u8 *, u8 *, u8 *, s32);

Gfx *critterRenderGroup(Gfx *gdl, CritterGroup *grp) {
    s32 col;
    s32 i;
    CritterObj *obj;
    u8 r;
    u8 g;
    u8 b;
    Gfx *(*cb)(Gfx *, CritterObj *);

    obj = grp->objs;
    switch (grp->type) {
    case 0:
    case 1:
        gSPDisplayList(gdl++, &D_80029B30);
        cb = func_800247F4;
        break;
    case 3:
        gSPDisplayList(gdl++, &D_80029B18);
        cb = func_80024C88;
        break;
    case 2:
        gSPDisplayList(gdl++, &D_80029B78);
        cb = func_8002516C;
        break;
    case 4:
        gSPDisplayList(gdl++, &D_80029B88);
        cb = func_800255C4;
        break;
    }
    i = 0;
    if (grp->count > 0) {
        do {
            if (gMapChunkCount != 0) {
                lightSampleColorAtPosition(obj->x, obj->y, obj->z, 0, &r, &g, &b, obj->homeZone->unk28);
            } else {
                r = 0xFF;
                g = 0xFF;
                b = 0xFF;
            }
            gDPPipeSync(gdl++);
            gDPSetPrimColor(gdl++, 0, 0, r, g, b, obj->homeZone->alpha);
            if (obj->flags & 1) {
                gdl = cb(gdl, obj);
            }
            i++;
            obj++;
        } while (i < grp->count);
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
    critterCurrentTexture = 0;
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


void critterSetOffsetAtAngle(CritterZone *zone, CritterObj *obj, u8 angle, s16 radius, u8 heightOffset) {
    f32 cosVal;
    f32 sinVal;
    f32 base;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 v;

    base = (f32)zone->shape.unk4;
    if (angle == 0) {
        cosVal = (f32)zone->shape.unkC;
        base += (f32)zone->shape.unk8;
    } else {
        cosVal = (f32)zone->shape.unk0 * ((f32)(randomLcgNext() & 0xFFFU) * 0.000244140625f);
    }
    v = (f32)((f64)((f32)(randomLcgNext() & 0xFFFU) * 0.000244140625f * base) - 0.5 * (f64)base);
    if (heightOffset != 0) {
        px = &obj->offX;
        py = &obj->offY;
        pz = &obj->offZ;
    } else {
        px = &obj->x;
        py = &obj->y;
        pz = &obj->z;
    }
    *py = v;
    *px = func_80612794(radius) * cosVal;
    *pz = func_80612790(radius) * cosVal;
}

void critterSetRandomOffset(CritterZone *zone, CritterObj *obj, u8 radius, u8 heightOffset) {
    critterSetOffsetAtAngle(zone, obj, radius, (s16)(randomLcgNext() & 0xFFF), heightOffset);
}

void critterPlaceInZone(CritterZone *zone, CritterObj *obj, u8 isRandom) {
    critterSetRandomOffset(zone, obj, isRandom, 0);
    obj->x += (f32)zone->x;
    obj->y += (f32)zone->y;
    obj->z += (f32)zone->z;
}

typedef struct CritterPlayer {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 x;
    /* 0x80 */ f32 y;
    /* 0x84 */ f32 z;
} CritterPlayer;

extern CritterPlayer *D_807FBB48;
extern CritterZone *critterPlayerZone;

void critterUpdateZoneProximity(CritterObj *obj) {
    CritterViewer *m;
    f32 lim;
    f32 fv0;
    f32 dist;
    s16 half;
    s32 f;

    fv0 = 0.0f;
    lim = (f32)(obj->homeZone->shape.unk10 + 0x1DE84);
    if (obj->homeZone->frame != D_807444FC) {
        half = (obj->homeZone->shape.unk4 + obj->homeZone->shape.unk8) >> 1;
        dist = ((f32)obj->homeZone->x - D_807FBB48->x) * ((f32)obj->homeZone->x - D_807FBB48->x) + ((f32)obj->homeZone->z - D_807FBB48->z) * ((f32)obj->homeZone->z - D_807FBB48->z);
        fv0 = 0.0f;
        f = critterPlayerZone->y < obj->homeZone->y + half;
        if (f) {
            f = obj->homeZone->y - half < critterPlayerZone->y;
        }
        f = (u8)f != 0;
        if (f) {
            f = 0;
            if (dist < (f32)obj->homeZone->shape.unk10) {
                f = 1;
            }
        }
        obj->homeZone->near = f;
        obj->homeZone->frame = D_807444FC;
        m = (CritterViewer *)((u8 *)gPlayerSlots + gCurrentPlayerIndex * sizeof(CritterViewer)); // FAKE: int temp ring
        dist = ((f32)obj->homeZone->z - m->z) * ((f32)obj->homeZone->z - m->z) + (((f32)obj->homeZone->x - m->x) * ((f32)obj->homeZone->x - m->x) + ((f32)obj->homeZone->y - m->y) * ((f32)obj->homeZone->y - m->y));
        obj->homeZone->distSq = dist;
        if (dist < lim) {
            fv0 = (lim - dist) * 0.000051020408f;
            if (fv0 > 1.0f) {
                fv0 = 1.0f;
            }
        }
        obj->homeZone->alpha = (u32)(255.0f * fv0);
    }
    if (obj->homeZone->distSq < lim) {
        obj->flags |= 1;
    } else {
        obj->flags &= ~1;
    }
}

CritterZone *critterGetZone(CritterGroup *grp, u8 idx) {
    CritterZone *ptr = grp->zones;
    return ptr + idx;
}

void critterPickNewZone(CritterObj *obj, CritterGroup *grp) {
    u8 idx;

    idx = randomLcgNext() % (u32)(grp->zoneCount - 1);
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
    if (obj->distSq < (f32)lim) {
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

    if (obj->frame != D_807444FC) {
        dx = obj->x - D_807FBB48->x;
        dz = obj->z - D_807FBB48->z;
        obj->distSq = (dx * dx) + (dz * dz);
        obj->frame = D_807444FC;
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


s32 func_80026530(CritterObj *obj, CritterGroup *grp) {
    critterSetTargetSpeed(obj, grp, (f32)((f64)obj->scale * 0.5));
    critterSetRandomOffset(obj->zone, obj, 1, 1);
    return 0;
}

extern f32 sqrtf(f32);
f32 func_80611BB4(f32, f32);
f32 func_80612800(s16);
s16 mathAngleEaseToward(s16, s16, f32);
s16 mathAngleDiscrete(f32, f32, f32, f32, f32);

void critterSteerToTarget(CritterObj *obj, CritterGroup *grp, void (*steerFunc)(CritterObj *, CritterGroup *), s32 (*targetPred)(CritterObj *, CritterGroup *)) {
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 dxz;
    f32 d2;
    f32 old;
    f32 tgt;
    f32 spd;
    f32 rate;
    CritterZone *off;
    s32 ret;
    s16 ang;
    s32 use_y;

    rate = 0.02f;
    use_y = (obj->flags & 2) == 0;
    if (steerFunc != NULL) {
        steerFunc(obj, grp);
    }
    off = obj->zone;
    tx = obj->offX + (f32)off->x;
    ty = obj->offY + (f32)off->y;
    tz = obj->offZ + (f32)off->z;
    dx = tx - obj->x;
    dy = ty - obj->y;
    dz = tz - obj->z;
    if (obj->role != 2) {
        dxz = dx * dx + dz * dz;
        d2 = dxz;
        if ((u8)use_y) {
            d2 += dy * dy;
        }
        tgt = obj->targetSpeed;
        if (d2 < 2500.0f) {
            tgt = (f32)((f64)tgt * 0.3 + 0.7 * (f64)tgt * (f64)(d2 * 0.0004f));
            rate = 0.1f;
            if (d2 < 25.0f && targetPred != NULL) {
                ret = targetPred(obj, grp);
                if (ret != 0) {
                    return;
                }
            }
        }
        old = obj->speed;
        obj->speed += (tgt - old) * rate;
        obj->accel = obj->speed - old;
    }
    dist = sqrtf(dx * dx + dz * dz);
    if ((u8)use_y) {
        obj->pitch = mathAngleEaseToward(obj->pitch, (s16)(((f64)func_80611BB4(dy, dist) * 2048.0) / 3.1415927410125732), obj->turnRate);
    }
    ang = mathAngleDiscrete(tx, tz, obj->x, obj->z, dist);
    obj->prevYaw = obj->yaw;
    obj->yaw = mathAngleEaseToward(obj->yaw, ang, obj->turnRate);
    spd = obj->speed;
    obj->x += spd * func_80612794(obj->yaw);
    obj->z += spd * func_80612790(obj->yaw);
    if ((u8)use_y) {
        obj->y += spd * func_80612800(obj->pitch);
    }
}

void critterUpdateIdle(CritterObj *obj, CritterGroup *grp) {
    u8 flags;

    flags = obj->flags;
    if ((flags & 1) && (flags & 4)) {
        critterSteerToTarget(obj, grp, NULL, func_80026530);
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

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_80026904(CritterObj *obj, CritterGroup *grp) {
    s16 angleDiff;
    CritterZone *targetZone;

    if (obj->role == 2) {
        critterFollowLeader(obj, grp->objs);
        return;
    }
    if (obj->role == 0) {
        targetZone = obj->homeZone;
        if (targetZone->near != 0) {
            critterCalcDistToPlayer(obj);
            if (critterPlayerZone != obj->zone) {
                critterTryActivate(obj, grp);
                return;
            }
            if (obj->state == 2 && obj->distSq < (f32)critterPlayerZone->shape.unk2) {
                angleDiff = mathAngleBetweenPoints2D(obj->x, obj->z, D_807FBB48->x, D_807FBB48->z);
                angleDiff += (randomLcgNext() & 0x7FF) - 0x400;
                obj->state = 1;
                critterSetOffsetAtAngle(obj->zone, obj, 0, angleDiff, 1);
            }
        } else if (critterPlayerZone == obj->zone) {
            obj->zone = targetZone;
            critterSetRandomOffset(targetZone, obj, 1, 1);
            obj->frame = 0xFF;
        }
    }
}

s32 func_80026A5C(CritterObj *obj, CritterGroup *grp) {
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
        if ((f64)obj->speed < 0.05) {
            obj->state = 0;
            obj->speed = 0.0f;
            return 1;
        }
    }
    return 0;
}
void func_800245B8(CritterObj *);
void func_80024F28(CritterObj *);
void critterUpdateZoneProximity(CritterObj *);

void critterDispatchAll(CritterGroup *grp) {
    s32 (*cb)(CritterObj *, CritterGroup *);
    void (*obj)(CritterObj *);
    s32 objIdx;
    CritterObj *groupIdx;
    groupIdx = grp->objs;
    switch (grp->type) {
    case 0:
    case 1:
        obj = func_800245B8;
        break;
    case 2:
        obj = func_80024F28;
        break;
    case 3:
        obj = func_80024B78;
        break;
    case 4:
        obj = func_80025500;
        break;
    default:
        obj = NULL;
        break;
    }
    cb = func_80026A5C;
    for (objIdx = 0; objIdx < grp->count; objIdx++, groupIdx++) {
        critterUpdateZoneProximity(groupIdx);
        if (groupIdx->state == 0) {
            critterUpdateIdle(groupIdx, grp);
        } else {
            critterSteerToTarget(groupIdx, grp, func_80026904, cb);
        }
        groupIdx->prevAnim = groupIdx->anim;
        if (obj != NULL) {
            obj(groupIdx);
        }
    }
}

extern u8 gPlayerCharacterId;
typedef struct CritterZoneRow {
    CritterZoneShape shape;
    s16 unk14;
    s16 pad16;
} CritterZoneRow;
extern CritterZoneRow D_80029BAC[][5];

void critterUpdateGroups(CritterGroups *groups) {
    s32 i;
    CritterGroup *p;
    CritterZoneRow *tbl;
    CritterZoneRow *e;
    s16 idx;
    u8 sel = gPlayerCharacterId;

    if (groups != NULL) {
        p = groups->groups;
        critterPlayerZone->x = (s16)D_807FBB48->x;
        tbl = D_80029BAC[sel];
        critterPlayerZone->z = (s16)D_807FBB48->z;
        for (i = 0; i < groups->count; i++, p++) {
            idx = p->type;
            if (idx > 0) {
                idx = idx - 1;
            }
            e = &tbl[idx];
            critterPlayerZone->y = (s16)(D_807FBB48->y + (f32)e->unk14);
            critterPlayerZone->shape = e->shape;
            critterDispatchAll(p);
        }
    }
}

extern CritterGroups *critterGroups;
void *memcpy(void *, const void *, unsigned int);
void *heapAlloc(s32);
void heapClearBlock(void *);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
void critterInitGroup(CritterGroup *);

void critterLoadData(u8 *data) {
    s32 g;
    CritterGroup *grp;
    CritterZone *ent;
    s32 j;
    u8 *src;

    if (data != NULL) {
        memcpy(critterGroups, data, 1);
        src = data + 1;
        for (g = 0; g < critterGroups->count; g++) {
            j = 0;
            if (g == 0) {
                critterGroups->groups = heapAlloc(critterGroups->count * 0xC);
                heapClearBlock(critterGroups->groups);
                grp = critterGroups->groups;
            } else {
                grp++;
            }
            memcpy(grp, src, 3);
            src += 3;
            if (grp->zoneCount > 0) {
                do {
                    if (j == 0) {
                        grp->zones = heapAlloc(grp->zoneCount * 0x2C);
                        heapClearBlock(grp->zones);
                        ent = grp->zones;
                    } else {
                        ent++;
                    }
                    memcpy(ent, src, 0x20);
                    if (gMapChunkCount != 0) {
                        ent->unk28 = mapChunkFindByPosition((f32)ent->x, (f32)ent->y, (f32)ent->z, 0);
                        ent->frame = 0xFF;
                    }
                    j++;
                    src += 0x20;
                } while (j < grp->zoneCount);
            }
            critterInitGroup(grp);
        }
    }
}

void critterInit(void *groups) {
    critterCurrentTexture = 0;
    critterGroups = heapAlloc(8);
    heapClearBlock(critterGroups);
    critterLoadData(groups);
    critterPlayerZone = heapAlloc(0x2C);
    heapClearBlock(critterPlayerZone);
}

extern s32 D_807FBB60;
void critterUpdateGroups(CritterGroups *);

Gfx *critterRender(Gfx *glist) {
    if (D_807FBB60 & 0x10) {
        if (!(D_807FBB60 & 2)) {
            critterUpdateGroups(critterGroups);
        }
        glist = critterRenderGroups(glist, critterGroups);
    }
    return glist;
}

void heapFreeDeferred(void *);

void critterCleanup(CritterGroup *grp) {
    u8 objCount;
    CritterObj *obj;
    s32 i;

    objCount = grp->count;
    obj = grp->objs;
    i = 0;
    if (objCount > 0 && obj != NULL) {
        do {
            critterStopAudio(obj);
            i++;
            obj++;
        } while (i < objCount && obj != NULL);
    }
    if (grp->objs != NULL) {
        heapFreeDeferred(grp->objs);
    }
    grp->objs = NULL;
    grp->count = 0;
}

s32 func_807142D8(void);
extern f32 D_80029F7C;

void critterInitGroup(CritterGroup *grp) {
    CritterObj *ent;
    s32 i;
    u8 flag;
    void (*cb)(CritterGroup *);

    if (grp->count == 0) {
        grp->objs = NULL;
        return;
    }
    switch (grp->type) {
    case 0:
    case 1:
        cb = func_800240EC;
        break;
    case 3:
        cb = func_80024154;
        break;
    case 4:
        cb = func_8002409C;
        break;
    case 2:
        cb = func_8002427C;
        break;
    }
    heapClearBlock(grp->objs = heapAlloc(grp->count * 0x1F0));
    ent = grp->objs;
    if (grp->zoneCount == 1) {
        flag = 0;
    } else {
        flag = 1;
    }
    i = 0;
    if (grp->count > 0) {
        do {
            critterPlaceInZone(grp->zones, ent, 1);
            if (func_807142D8() == 0) {
                critterSetRandomOffset(grp->zones, ent, 1, 1);
            }
            ent->zone = ent->homeZone = grp->zones;
            ent->role = flag;
            ent->frame = 0xFF;
            ent->yaw = randomLcgNext() & 0xFFF;
            ent->anim = randomLcgNext() & 0xFFF;
            ent->scale = 1.0f - (f32)(randomLcgNext() % 1000U) / 4000.0f;
            ent->scale = ent->scale * D_80029F7C;
            ent++;
            if (flag == 1) {
                flag = 2;
            }
            i++;
        } while (i < grp->count);
    }
    cb(grp);
}
