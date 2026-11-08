#include "common.h"
#include "actor.h"

typedef struct B7490Actor {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0xC];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ u8 padE6[2];
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[0x46];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x42];
    /* 0x178 */ s16 *unk178;
} B7490Actor;

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 x;
    /* 0x0C */ s16 y;
    /* 0x0E */ s16 z;
} B7490Pos;

#define B7490A ((B7490Actor *)D_807FBB40)
#define B7490MAXD(a, b) ((a) < (b) ? (b) : (a))

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;
extern Struct807FD580 *gActivePlayerState;
extern s32 D_807FDCA0;
extern u32 gFrameCounter;
extern s32 gCurrentMap;
extern u8 D_8072073C[];
extern s16 D_80750340;

void actorScriptStart(void *, s32);
s32 func_8072E0A8(s32, s32);
void behaviourFrameBegin(void);
void func_8067ACB4(Actor *);
void actorUpdateModelMatrix(void *, s32);
void effectSpawnSparks(s32, s32);
s32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void func_8072A920(s16, s32, f32, f32, f32, s32, f32, f32, s32);
void func_8072A86C(s16, f32, f32, f32, s32);
void func_8072B7CC(s32);
s32 patrolPathStep(u8, s32);
void func_8072D714(s32, s32);
void actorSetDefaultState();
void func_8072DC7C();
void func_8072AA80(void);
void enemyAggroStateUpdate(s32, s32, s32);
s32 randomNonNegative(void);
f32 func_80612794(s16);
s16 mathAngleEaseToward(s16, s16, f32);
void actorClearNodeFlag(Actor *, s32);
void scriptSetActorRampTarget(void *, f32, f32);
void func_8072E1A4(s32, void *);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void actorSetUniformScale(void *, f32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714950(s32);
void func_8071498C(void *);
void effectRadialSprayUpdate();
void func_80714998(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8067E278(s32, s32);
void actorGetOrSetNodeScale(void *, s32, f32);
void actorSetCollisionRadius(void *, f32);
void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
s32 zoneCanReachPoint(void *, s16, s16, s16, s32);
f32 sqrtf(f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void func_8072881C();
void actorSpawnPeriodicBoneEffect(void);
void func_806B42A8(void (*)(), u16, u16, s16);
void actorAirPatrolStep(u8, s16, s16);
void actorSpawnNodeEntryAtActor(s32, s32);
void actorAttachChildCallbacks(void);
void sfxAllocateChannel(s32, f32);
void csModelStateSetFirstByte(s32, s32);
void actorPlaceAttachedChildren(s32);
void func_8072D9D4(void);
void camStartPath(void *, s32, s32);
void behaviourSetAnimIds(s32, s32, s32);
void actorApplyVelocityCustom(void *, f32, f32);
void actorUpdateFloorContactAndTilt(void *, f32);

void func_806B2790(void) {
    u8 flag;
    s32 st;

    behaviourFrameBegin();
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->state != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, 0x2E1);
        D_807FDC98->unk46 |= 8;
    }
    effectSpawnSparks(0x1F, 0);
    st = D_807FBB40->state;
    switch (st) {
        case 0x27:
            flag = 0;
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorScriptStart(D_807FBB40, 0x2E0);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    flag = 1;
                    D_807FBB40->unkB8 = 150.0f;
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    flag = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2DE);
                    break;
            }
            st = D_807FBB40->state;
            if (flag) {
                func_8072A86C(st, D_807FDC94->x, D_807FDC94->z, 100.0f, 0x2240);
            }
            break;
        case 1:
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((randomNonNegative() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->state, 0, D_807FDC94->x, D_807FDC90->unkC, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 15);
            func_8072A920(D_807FBB40->state, 0, D_807FDC94->x, ((D_807FBB40->unkAC - D_807FBB40->unk15E) < D_807FDC94->y) ? (D_807FBB40->unkAC - D_807FBB40->unk15E) : D_807FDC94->y, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                D_807FBB40->state = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072A920(st, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    B7490A->unkE4 = mathAngleEaseToward(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14);
                    break;
                case 2:
                    D_807FBB40->state = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2DE);
            break;
    }
    st = D_807FBB40->state;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->state, 1);
        default:
            enemyAggroStateUpdate(0x6400, 0x2DE, 0x2DE);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void actorEmptyStub(void) {
}

typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B7490Node;

typedef struct {
    /* 0x00 */ B7490Node *unk0;
} B7490Sub4Ptr;

void func_8072DEA8(s32, s32, s32, void *);
void func_8072881C(s32, void *);

void func_806B2D64(void) {
    s32 st;
    f32 min;
    f32 fa;
    f32 fb;

    behaviourFrameBegin();
    effectSpawnSparks(0x1F, 2);
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->state != 0x37)) {
        D_807FDC98->unk46 |= 8;
        func_8072D714(D_807FBB70.unk1FC, 0x2E7);
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x2E5, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
        D_807FBB40->unkB8 = 0.0f;
    }
    st = D_807FBB40->state;
    switch (st) {
        case 0x31:
            effectSpawnSparks(0x1F, 2);
            if ((D_807FBB40->unk155[0] != 0) || (((B7490Sub4Ptr *)D_807FBB40->unk4)->unk0->unk24 == 0.0f)) {
                actorSetDefaultState(0x2E2);
            }
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorScriptStart(D_807FBB40, 0x2E6);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2E2);
                    break;
            }
            break;
        case 0x25:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorScriptStart(D_807FBB40, 0x2E4);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(D_807FBB40, 1);
                    projectileSpawnNodeEntry(0x112, 0, 0.3f, D_807FBB40->yaw, 300.0f, func_80612794(B7490A->unkE8) * 300.0f, D_807FBB40);
                    effectSpawnSparks(1, 1);
                    break;
                case 3:
                    actorSetDefaultState(0x2E2);
                    break;
            }
            break;
        case 1:
            actorEmptyStub();
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((randomNonNegative() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->state, 0, D_807FDC94->x, D_807FDC90->unkC, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            actorEmptyStub();
            func_8072A920(D_807FBB40->state, 0, D_807FDC94->x, ((D_807FBB40->unkAC - D_807FBB40->unk15E) < D_807FDC94->y) ? (D_807FBB40->unkAC - D_807FBB40->unk15E) : D_807FDC94->y, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                D_807FBB40->state = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
            D_807FBB40->unk132 = 2;
        case 7:
        case 0x35:
            actorEmptyStub();
            func_8072A920(D_807FBB40->state, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    B7490A->unkE4 = mathAngleEaseToward(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14);
                    break;
                case 2:
                    D_807FBB40->state = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2E2);
            break;
    }
    st = D_807FBB40->state;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->state, 1);
            break;
        default:
            enemyAggroStateUpdate(0x6400, 0x2E2, 0x2E2);
            break;
    }
    func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806B3420(void) {
    f32 dx;
    f32 dy;
    f32 dz;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 0x24;
        D_807FBB40->unk60 |= 0x400;
        D_807FDC90->unk2C = 0x5A;
        D_807FBB40->state = 0;
        D_807FBB40->unk155[0] = 0;
        func_8067ACB4(D_807FBB40);
        actorClearNodeFlag(D_807FBB40, 1);
    }
    dx = D_807FBB40->x - D_807FDC94->x;
    dy = D_807FBB40->y - D_807FDC94->y;
    dz = D_807FBB40->z - D_807FDC94->z;
    if (dx * dx + dy * dy + dz * dz > 90000.0f) {
        D_807FBB40->unk60 |= 0x80000000;
    } else {
        D_807FBB40->unk60 &= 0x7FFFFFFF;
    }
    switch (D_807FBB40->state) {
        case 0:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                actorScriptStart(D_807FBB40, 0x35D);
                scriptSetActorRampTarget(D_807FBB40, 0.5f, 0.0f);
                D_807FBB40->state = 1;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 1:
            if (D_807FBB40->unk155[0] != 0) {
                D_807FBB40->state = 2;
                D_807FBB40->unk155[0] = 0;
                D_807FDC90->unk2C = 0x5A;
            }
            break;
        case 2:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk132 = 2;
                scriptSetActorRampTarget(D_807FBB40, 0.5f, 0.0f);
                D_807FBB40->state = 3;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] != 0) {
                D_807FBB40->unk132 = 1;
                D_807FBB40->state = 0;
                D_807FBB40->unk155[0] = 0;
                D_807FDC90->unk2C = 0x5A;
            }
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void actorSwellBurstUpdate(void) {
    f32 dx;
    f32 var;
    f32 scaleMultiplier;
    u8 st;
    s16 i;

    var = D_807FBB40->unk4->unk38 * 800.0f;
    scaleMultiplier = 1.1f;
    if (gCurrentMap == 0xC7) {
        if (!(D_807FBB4C->unk6A & 4)) {
            var = 0.0f;
            scaleMultiplier = 0.4f;
        } else {
            var = var * 0.75;
            scaleMultiplier = 0.7f;
        }
    }
    var = var * var;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 4;
        func_8067ACB4(D_807FBB40);
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->state != 0x27)) {
        D_807FBB40->state = 0x27;
        D_807FBB40->unk155[0] = 0;
    } else if (D_807FBB40->state != 0x27) {
        dx = D_807FDC94->x - D_807FBB40->x;
        if (dx * dx + (D_807FDC94->y - D_807FBB40->y) * (D_807FDC94->y - D_807FBB40->y) + (D_807FDC94->z - D_807FBB40->z) * (D_807FDC94->z - D_807FBB40->z) < var) {
            D_807FBB40->state = 0x27;
            D_807FBB40->unk155[0] = 0;
        }
    }
    effectSpawnSparks(0x1F, 0);
    switch (D_807FBB40->state) {
        case 4:
            actorMoveWithinZone(0, 0.0f, 0.0f, 2, 0.0f);
            if (D_807FBB40->y < D_807FBB40->unkAC) {
                D_807FBB40->y = D_807FBB40->unkAC;
                B7490A->unkC0 = B7490A->unkC4;
            }
        case 0:
            func_8072E1A4(0xA, D_807FDC94);
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C2, 0xFF, 0x7F, 0);
                    D_807FDC90->unk30 = 2.0 * D_807FBB40->unk4->unk38;
                    D_807FBB40->unk155[0]++;
                case 1:
                    if (D_807FDC90->unk30 > (dx = D_807FBB40->unk4->unk38)) {
                        actorSetUniformScale(D_807FBB40, dx * 1.01);
                    } else {
                        for (i = 0; i < 0xC; i++) {
                            func_807149B8(1);
                            func_807149FC(2);
                            func_80714950(i + 0x0B020000);
                            func_8071498C(effectRadialSprayUpdate);
                            func_80714998(1);
                            func_80714CC0(D_8072073C, 2.0 * D_807FBB40->unk4->unk38, D_807FBB40->x, D_807FBB40->y, D_807FBB40->z);
                        }
                        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3D, 0xFF, 0x7F, 0);
                        sfxPlayAtPositionPooled(D_807FBB40->x, D_807FBB40->y, D_807FBB40->z, 0x35C, 0xFF, 0x7F, 0, 0x32, 0.3f, 0);
                        func_8067E278(0, 1);
                        actorGetOrSetNodeScale(D_807FBB40, 1, D_807FBB40->unk140->unkC * scaleMultiplier);
                        actorSetCollisionRadius(D_807FBB40, D_807FBB40->unk140->unkC * scaleMultiplier);
                        D_807FBB40->unk60 &= ~4;
                        D_807FBB40->unk155[0]++;
                    }
                    break;
                case 5:
                    D_807FBB40->state = 0x40;
                    break;
                default:
                    D_807FBB40->unk155[0]++;
            }
            break;
        case 2:
        case 3:
            dx = D_807FDC90->unkC;
            func_8072A920(D_807FBB40->state, 0, D_807FDC90->unkA, (dx < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? dx : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        default:
            func_8072B7CC(0x32E);
            break;
    }
    st = D_807FBB40->state;
    if (st == 2 || st == 3) {
        patrolPathStep(st, 1);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void projectileSpawnFromActorNode(u8 nodeIndex) {
    projectileGetTargetCoords(D_807FBB40, nodeIndex);
    projectileSpawnNodeEntry(0x32, 1, 0.3f, ((s16 *)D_807FBB40)[0xEE / 2], 80.0f, 0.0f, D_807FBB40);
}

void projectileAimAtTargetFromActor(void) {
    projectileSetTargetCoords(D_807FBB40->x, D_807FBB40->y - 5.0f, D_807FBB40->z);
    projectileAimAndSpawn(0x51, 1, 0.3f, D_807FDC94->x, D_807FDC94->y, D_807FDC94->z, 80.0f, D_807FBB40);
}


void func_806B3D18(void) {
    switch (D_807FBB40->unk155[0]) {
        case 0:
            if (func_8072E0A8(0x96, 0x96)) {
                actorScriptStart(D_807FBB40, 0x253);
                D_807FBB40->unk155[0] = 1;
            }
            break;
        case 2:
            projectileSpawnFromActorNode(2);
            D_807FBB40->unk155[0] = 3;
            break;
    }
}

void func_806B3DA4(void) {
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
        return;
    }
    if (func_8072E0A8(0x96, 0x96)) {
        projectileSpawnFromActorNode(1);
        D_807FDC90->unk2C = D_80750340;
    }
}

void func_806B3E08(void) {
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
        if (gFrameCounter & 1) {
            projectileAimAtTargetFromActor();
        }
    } else if (func_8072E0A8(0x96, 0x96)) {
        D_807FDC90->unk2C = 0x14;
    }
}

void func_806B3E7C(void) {
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
        return;
    }
    if (zoneCanReachPoint(D_807FBB40, D_807FDC94->x, D_807FDC94->y, D_807FDC94->z, D_807FDCA0) && func_8072E0A8(0x96, 0x96)) {
        D_807FBB40->state = 0x26;
        D_807FBB40->unk155[0] = 0;
    }
}


void func_806B3F3C(void) {
    if (((randomNonNegative() >> 15) % 1000) >= 0x3E4) {
        D_807FBB40->state = 0x1C;
        D_807FBB40->unk155[0] = 0;
    }
}

s32 actorFlyTowardPosition(B7490Pos *targetPos, u8 action) {
    f32 dz;
    f32 dx;
    f32 dist;
    f32 t;
    f32 dy;

    dz = targetPos->z - B7490A->unk84;
    dx = targetPos->x - B7490A->unk7C;
    dist = sqrtf(dz * dz + dx * dx);
    t = B7490MAXD(dist / B7490MAXD(B7490A->unkB8, 0.0001), 0.0001);
    B7490A->unkC0 = 0.0f;
    dy = (B7490A->unk80 < targetPos->y) ? 0.0f : B7490A->unk80 - targetPos->y;
    B7490A->unkC4 = -(dy / t);
    B7490A->unkE8 = mathAngleEaseToward(B7490A->unkE8, (s32)((mathCalculatePitchAngle(targetPos->x, targetPos->y, targetPos->z, B7490A->unk7C, B7490A->unk80, B7490A->unk84, 0x46) * 2048.0) / 3.1415927410125732), 3.3f);
    return actorMoveWithinZone(action, targetPos->x, targetPos->z, 0x2E0, 0.0f);
}

void func_807149C8(u8, u8, u8, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void actorSpawnPeriodicBoneEffect(void) {
    u8 col2;
    u8 col;
    f32 f;
    u32 period;

    switch (B7490A->unk134) {
        case 2:
            col = 0xC8;
            period = 0x20;
            f = 0.5f;
            break;
        case 1:
            period = 0x18;
            col = 0x64;
            f = 1.0f;
            break;
        case 0:
            period = 8;
            col = 0x32;
            f = 1.5f;
            break;
        default:
            period = 0;
    }
    if ((period != 0) && ((gFrameCounter % period) == 0)) {
        func_80714998(3);
        func_807149C8(col, col, col, *(u8 *) ((u8 *) D_807FBB40 + 0x129));
        effectSpawnBoneDefault(D_807FBB40, 1, f, 0.0f, 0.0f, 0.0f, -0x50);
    }
}

s32 camIsCutsceneActive(void *);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void sfxSpawnTableNodes(Actor *);

void func_806B42A8(void (*callback)(), u16 animId1, u16 animId2, s16 sfxId) {
    s16 *heightTarget;
    s16 targetX;
    s16 targetZ;
    s32 st;

    heightTarget = B7490A->unk178;
    if ((sfxId != 0) && (D_807FBB40->state != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, sfxId, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        *heightTarget = D_807FDC9C->unkA;
        if (D_807FDC9C->unkB == 0) {
            D_807FDC9C->unkB = 0x28;
        }
    }
    st = D_807FBB40->state;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (st != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, animId1);
        B7490A->unkC0 = 300.0f;
        *heightTarget = 0;
        D_807FDC90->unk2C = 0x2BC;
        st = D_807FBB40->state;
    }
    targetX = D_807FDC90->unkA;
    targetZ = D_807FDC90->unkE;
    switch (st) {
        case 1:
        case 0x10:
        case 0x23:
            targetX = (s16) (s32) D_807FDC94->x;
            targetZ = (s16) (s32) D_807FDC94->z;
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (D_807FBB40->y < (f32) (*heightTarget + (0, D_807FDC9C->unk6))) { // FAKE: comma wrapper steers ugen temp order
                D_807FBB40->y = (f32) ((f64) D_807FBB40->y + ((f64) (u32) D_807FDC9C->unkB * 0.03125));
            } else {
                if ((camIsCutsceneActive(D_807FDC90) == 0) && (callback != NULL)) {
                    callback();
                }
            }
            actorMoveWithinZone(D_807FBB40->state, (f32) targetX, (f32) targetZ, 0x2C1, 0.0f);
            B7490A->unkE8 = mathAngleEaseToward(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    D_807FDC90->unkA = (s16) (s32) D_807FDC94->x;
                    D_807FDC90->unkC = (s16) (s32) D_807FDC94->y;
                    D_807FDC90->unkE = (s16) (s32) D_807FDC94->z;
                    D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                    D_807FDC90->unk2C = 0x64;
                case 1:
                    if ((actorFlyTowardPosition((B7490Pos *) D_807FDC90, 0x23) & 1) || (D_807FBB40->y < (f32) (D_807FDC90->unkC + 0xF))) {
                        D_807FBB40->state = D_807FDC9C->unk10;
                        D_807FBB40->unk155[0] = 0;
                    }
                    break;
            }
            break;
        case 0x37:
            D_807FBB40->yaw = D_807FBB40->yaw + D_807FDC90->unk2C;
            D_807FDC90->unk2C = ((D_807FDC90->unk2C - 0x11) < 0) ? 0 : (D_807FDC90->unk2C - 0x11);
            if (D_807FDC90->unk2C == 0) {
                sfxStopSlotSound(D_807FBB40, 0);
            }
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    if (D_807FBB40->actorType == 0x11D) {
                        D_807FBB40->unk155[0] = 3;
                        break;
                    }
                    B7490A->unkC0 = 50.0f;
                    D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x222, 0.0f);
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    D_807FBB40->state = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(animId2);
            break;
    }
    st = D_807FBB40->state;
    switch (st) {
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->state, 1);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (!D_807FBB40->state) {
    }
}

void func_806B486C(void) {
    behaviourFrameBegin();
    func_806B42A8(func_806B3E7C, 0x251, 0x250, 0x10E);
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806B48B8(void) {
    behaviourFrameBegin();
    func_806B42A8(func_806B3DA4, 0x251, 0x250, 0x10E);
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806B4904(void) {
    behaviourFrameBegin();
    func_806B42A8(func_806B3D18, 0x254, 0x252, 0x108);
    actorSpawnPeriodicBoneEffect();
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806B4958(void) {
    behaviourFrameBegin();
    func_806B42A8(func_806B3E7C, 0x251, 0x250, 0x10E);
    if (D_807FBB40->state != 0x37) {
        func_806B3E08();
    }
}

extern f32 D_807502EC;
void func_80724CA4(s32, s32);

void actorAirPatrolStep(u8 action, s16 animId1, s16 animId2) {
    s16 *heightPtr;
    s32 pad1;
    s32 pad2;
    s16 targetHeight;

    heightPtr = B7490A->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(1, 1);
        D_807FDC90->unk30 = D_807FBB40->unk4->unk38;
        D_807FBB40->unkB8 = (f32) (u32) D_807FDC9C->unkC;
        *heightPtr = D_807FDC9C->unkA;
        B7490A->unkC4 = D_807502EC;
    }
    targetHeight = D_807FDC9C->unk6 - (0 - *heightPtr);  // FAKE: negated subtrahend flips the commutative + operand order
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (action != 0x37)) {
        D_807FBB40->state = 0x37;
        D_807FBB40->unk155[0] = 0;
    }
    switch (action) {
        case 2:
        case 3:
            if (D_807FBB40->unk155[0] == 0) {
                actorScriptStart(D_807FBB40, animId1);
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            }
            actorMoveWithinZone(action, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0xE1, 0.0f);
            if (D_807FBB40->y < (f32) targetHeight) {
                if (D_807FBB40->unk155[0] == 2) {
                    D_807FBB40->y = (f32) ((f64) D_807FBB40->y + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.03125));
                } else {
                    D_807FBB40->y = (f32) ((f64) D_807FBB40->y + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.015625));
                }
            }
            B7490A->unkE8 = mathAngleEaseToward(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                case 1:
                case 2:
                    actorScriptStart(D_807FBB40, animId2);
                    D_807FBB40->unk155[0] = 3;
                case 3:
                    actorFlyTowardPosition((void *) D_807FDC90, 0x26);
                    break;
            }
            break;
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                D_807FBB40->state = 0x40;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(animId1);
            break;
    }
    switch (action) {
        case 2:
        case 3:
            patrolPathStep(action, 1);
            break;
        case 0x26:
            if (patrolPathStep(action, 1) != 0) {
                D_807FBB40->state = D_807FDC9C->unk10;
                D_807FBB40->unk155[0] = 0;
            }
            break;
    }
}

void func_806B4DCC(void) {
    f64 curScale;
    s16 *heightPtr;
    f32 origScale;
    s32 deltaHeight;
    s16 timer;
    u8 action;

    heightPtr = ((B7490Actor *) D_807FBB40)->unk178;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 = D_807FBB40->unk60 | 0x400;
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x40;
        D_807FBB40->unk16A = 0xFA;
        D_807FBB40->unk16B = 0xFA;
        D_807FBB40->unk16C = 0xFA;
        actorSpawnNodeEntryAtActor(0x2D, 0x44);
        sfxPlayAtPositionPooled(D_807FBB40->x, D_807FBB40->y, D_807FBB40->z, 0x2C1, 0xFF, 0x7F, 0, 0x14, 0.0f, 0);
    }
    deltaHeight = D_807FDC90->unkC - D_807FDC9C->unk6;
    *heightPtr = (deltaHeight < 0) ? 0 : deltaHeight;
    if ((D_807FBD70 == 9) && (D_807FBB40->state != 0x37)) {
        D_807FBB40->state = 0x37;
        D_807FBB40->unk155[0] = 0;
        actorScriptStart(D_807FBB40, 0x248);
        actorAttachChildCallbacks();
        sfxAllocateChannel(0x14, 1.0f);
        csModelStateSetFirstByte(0x7F, 0xA);
    }
    action = D_807FBB40->state;
    if ((action != 0x37) && (action != 0x40)) {
        actorPlaceAttachedChildren(-0x1E);
    }
    curScale = D_807FBB40->unk4->unk34;
    origScale = D_807FBB40->unk4->unk34;
    actorSetUniformScale(D_807FBB40, (f32) (((f64) (D_807FDC90->unk30 - origScale) * 0.05) + (f64) origScale));
    timer = D_807FDC90->unk2C;
    if (timer != 0) {
        D_807FDC90->unk2C = timer - 1;
        if (gFrameCounter & 4) {
            D_807FBB40->unk60 = D_807FBB40->unk60 | 0x800000;
        } else {
            D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFF7FFFFF;
        }
    } else {
        D_807FBB40->unk132 = 1;
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFF7FFFFF;
        if (D_807FBD70 == 4) {
            D_807FBB40->unk132 = 2;
            D_807FDC90->unk2C = 0x1E;
            D_807FDC90->unk30 = (f32) ((f64) D_807FDC90->unk30 * 0.7);
            func_8072D9D4();
            camStartPath(D_807FBB40, 3, 5);
            if (((B7490Actor *) D_807FBB40)->unk134 & 1) {
                actorScriptStart(D_807FBB40, 0x24A);
            } else {
                actorScriptStart(D_807FBB40, 0x249);
            }
        }
    }
    actorAirPatrolStep(D_807FBB40->state, 0x247, 0x246);
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806B50F4(void) {
    behaviourFrameBegin();
    actorAirPatrolStep(D_807FBB40->state, 0x23D, 0x23E);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806B513C(void) {
    s32 inWaterFlag;
    s16 alphaDelta;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        behaviourSetAnimIds(0x30C, 0x30B, 0x30D);
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
    }
    if (gCurrentMap == 0xA6) {
        inWaterFlag = gActivePlayerState->unk1F0 & 0x40;
        if ((inWaterFlag != 0) && (D_807FBB40->unk128 == 0)) {
            D_807FDC90->unk2C = 0xA;
            D_807FBB40->unk144 = 0x24;
        } else if ((inWaterFlag == 0) && (D_807FBB40->unk128 == 0xFF)) {
            D_807FDC90->unk2C = -0xA;
            D_807FBB40->unk144 = 1;
        }
        alphaDelta = D_807FDC90->unk2C;
        if (alphaDelta != 0) {
            D_807FBB40->unk128 = D_807FBB40->unk128 + alphaDelta;
            if (D_807FBB40->unk128 >= 0x100) {
                D_807FBB40->unk128 = 0xFF;
                D_807FDC90->unk2C = 0;
            } else if (D_807FBB40->unk128 < 0) {
                D_807FBB40->unk128 = 0;
                D_807FDC90->unk2C = 0;
            }
        }
    }
    func_806B42A8((gFrameCounter & 1) ? func_806B3E7C : func_806B3F3C, 0x30E, 0x30B, 0);
}

void func_806B52DC(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x60;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        D_807FBB40->unkB8 = (f32) (((randomNonNegative() >> 15) % 100) + 0x12C);
        D_807FBB40->y += (f32) ((randomNonNegative() >> 15) % 30);
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
        D_807FBB40->unk128 = 0;
        ((B7490Actor *) D_807FBB40)->unkEC = ((randomNonNegative() >> 15) % 7) + 0xF;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocityCustom(D_807FBB40, D_807FBB40->unkB8, 0.0f);
    actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    switch (D_807FBB40->state) {
    case 6:
        D_807FBB40->unk128 = D_807FBB40->unk128 + ((B7490Actor *) D_807FBB40)->unkEC;
        if (D_807FBB40->unk128 >= 0xFF) {
            D_807FBB40->unk128 = 0xFF;
            D_807FBB40->state = 0x37;
        }
        break;
    case 0x37:
        D_807FBB40->unk128 = D_807FBB40->unk128 - ((B7490Actor *) D_807FBB40)->unkEC;
        if (D_807FBB40->unk128 < 0) {
            D_807FBB40->state = 0x3C;
            D_807FBB40->unk128 = 0;
        }
        break;
    default:
        func_8072B7CC(0x333);
        break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} B7490St178;

extern u16 D_80744508;
s32 randomLcgNext(void);
f32 randomFloat(void);
f32 func_80612790(s16);
s32 mathAngleSignedDistance(s16, s16);
void zoneEntryGetPosition(s32, s32, f32 *, f32 *, f32 *);
s32 flagGet(s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);

void func_806B54BC(void) {
    f32 dead;
    f32 zoneX;
    f32 zoneY;
    f32 zoneZ;
    f32 dist;
    s16 D_807FBB40_3;
    B7490St178 *state;

    state = (B7490St178 *) B7490A->unk178;
    behaviourFrameBegin();
    dead = state->unk0; // dead store: reserves the extra frame slot above zoneX
    if ((D_807FBB40->state != 0x40) && (D_807FBB40->state != 0x37) && ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0))) {
        sfxStopSlotSound(D_807FBB40, 0);
        actorScriptStart(D_807FBB40, 0x331);
        D_807FBB40->state = 0x37;
        D_807FBB40->unk155[0] = 0;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB4C, 0x16, 0xFF, 0x7F, 0x1E);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x20;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        D_807FBB40->unkB8 = 40.0f;
        D_807FBB40->state = 0x23;
        D_807FBB40->unk155[0] = 0;
        B7490A->unkEC = ((randomNonNegative() >> 15) % 7) + 0xF;
        state->unk0 = D_807FBB40->x;
        state->unk4 = D_807FBB40->y;
        state->unk8 = D_807FBB40->z;
        state->unk10 = 1;
        state->unkC = D_807FBB40->y;
        state->unk12 = (randomLcgNext() & 0xFF) + 0x78;
    }
    if ((D_807FBB40->state != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, 0x10E, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    switch (D_807FBB40->state) {
        case 0x26:
            state->unk0 = D_807FBB4C->x;
            state->unk4 = D_807FBB4C->y;
            state->unk8 = D_807FBB4C->z;
            state->unk12 = (randomLcgNext() & 0xFF) + 0x78;
        case 0x23:
            D_807FBB40->yaw = D_807FBB40->yaw - (mathAngleSignedDistance(mathAngleBetweenPoints2D(D_807FBB40->x, D_807FBB40->z, state->unk0, state->unk8) + 0x800, D_807FBB40->yaw) >> 4);
            state->unk10 = state->unk10 - 1;
            if (state->unk10 <= 0) {
                zoneEntryGetPosition(1, 0, &zoneX, &zoneY, &zoneZ);
                state->unk10 = (randomLcgNext() & 0x3F) + 0xF;
                D_807FBB40_3 = mathAngleBetweenPoints2D(zoneX, zoneZ, state->unk0, state->unk8);
                D_807FBB40_3 += ((randomLcgNext() & 7) << 8) + 0x400;
                dist = (f32) ((f64) randomFloat() * 180.0);
                state->unk0 = (func_80612794(D_807FBB40_3) * dist) + zoneX;
                state->unk4 = state->unkC;
                state->unk8 = (func_80612790(D_807FBB40_3) * dist) + zoneZ;
                D_807FBB40->state = 0x23;
            }
            if (D_807FBB40->state == 0x23) {
                state->unk12 = state->unk12 - 1;
                if (state->unk12 <= 0) {
                    state->unk10 = 0x3C;
                    D_807FBB40->state = 0x26;
                }
            }
            zoneY = (f32) ((f64) (state->unk4 - D_807FBB40->y) * 0.0625);
            if ((f64) zoneY > 8.0) {
                zoneY = 8.0f;
            }
            if ((f64) zoneY < -8.0) {
                zoneY = -8.0f;
            }
            D_807FBB40->x += func_80612794(D_807FBB40->yaw) * 8.0;
            D_807FBB40->y = D_807FBB40->y + zoneY;
            D_807FBB40->z += func_80612790(D_807FBB40->yaw) * 8.0;
            break;
        case 0x37:
            D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
            D_807FBB40->unk128 = D_807FBB40->unk128 - 8;
            D_807FBB40->y = (f32) ((f64) D_807FBB40->y - 10.0);
            if (D_807FBB40->unk128 < 0) {
                D_807FBB40->unk128 = 0;
                D_807FBB40->state = 0x40;
                D_807FBB40->unk155[0] = 0;
                D_807FBB40->unk144 = 1;
                if (gCurrentMap == 0xA7) {
                    D_80744508 = D_80744508 + 1;
                    if ((D_80744508 == 5) && (flagGet(0x15F, 0) == 0)) {
                        csModelStateSetFirstByte(4, 0xA);
                    }
                }
            }
            break;
        default:
            func_8072B7CC(0x32F);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
