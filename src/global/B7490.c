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

#define B7490A ((B7490Actor *)gCurrentActor)
#define B7490MAXD(a, b) ((a) < (b) ? (b) : (a))

extern Actor *gCurrentActor;
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
void tagBarrelSpawnActorSmokePuffs(s32, s32);
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
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (gCurrentActor->state != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, 0x2E1);
        D_807FDC98->unk46 |= 8;
    }
    effectSpawnSparks(0x1F, 0);
    st = gCurrentActor->state;
    switch (st) {
        case 0x27:
            flag = 0;
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2E0);
                    gCurrentActor->unk155[0] = 1;
                    break;
                case 2:
                    flag = 1;
                    gCurrentActor->speedXZ = 150.0f;
                    gCurrentActor->unk132 = 2;
                    break;
                case 3:
                    gCurrentActor->unk132 = 1;
                    flag = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2DE);
                    break;
            }
            st = gCurrentActor->state;
            if (flag) {
                func_8072A86C(st, D_807FDC94->x, D_807FDC94->z, 100.0f, 0x2240);
            }
            break;
        case 1:
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((randomNonNegative() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(gCurrentActor->state, 0, D_807FDC94->x, D_807FDC90->targetY, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 15);
            func_8072A920(gCurrentActor->state, 0, D_807FDC94->x, ((gCurrentActor->unkAC - gCurrentActor->unk15E) < D_807FDC94->y) ? (gCurrentActor->unkAC - gCurrentActor->unk15E) : D_807FDC94->y, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072A920(st, 0, D_807FDC90->targetX, (D_807FDC90->targetY < (gCurrentActor->unkAC - gCurrentActor->unk15E)) ? D_807FDC90->targetY : (gCurrentActor->unkAC - gCurrentActor->unk15E), D_807FDC90->targetZ, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    B7490A->unkE4 = mathAngleEaseToward(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14);
                    break;
                case 2:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2DE);
            break;
    }
    st = gCurrentActor->state;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
        default:
            enemyAggroStateUpdate(0x6400, 0x2DE, 0x2DE);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
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
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (gCurrentActor->state != 0x37)) {
        D_807FDC98->unk46 |= 8;
        func_8072D714(D_807FBB70.unk1FC, 0x2E7);
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x2E5, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
        gCurrentActor->speedXZ = 0.0f;
    }
    st = gCurrentActor->state;
    switch (st) {
        case 0x31:
            effectSpawnSparks(0x1F, 2);
            if ((gCurrentActor->unk155[0] != 0) || (((B7490Sub4Ptr *)gCurrentActor->unk4)->unk0->unk24 == 0.0f)) {
                actorSetDefaultState(0x2E2);
            }
            break;
        case 0x27:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2E6);
                    gCurrentActor->unk155[0] = 1;
                    break;
                case 2:
                    gCurrentActor->unk132 = 2;
                    break;
                case 3:
                    gCurrentActor->unk132 = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2E2);
                    break;
            }
            break;
        case 0x25:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2E4);
                    gCurrentActor->unk155[0] = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(gCurrentActor, 1);
                    projectileSpawnNodeEntry(0x112, 0, 0.3f, gCurrentActor->yaw, 300.0f, func_80612794(B7490A->unkE8) * 300.0f, gCurrentActor);
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
            func_8072A920(gCurrentActor->state, 0, D_807FDC94->x, D_807FDC90->targetY, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            actorEmptyStub();
            func_8072A920(gCurrentActor->state, 0, D_807FDC94->x, ((gCurrentActor->unkAC - gCurrentActor->unk15E) < D_807FDC94->y) ? (gCurrentActor->unkAC - gCurrentActor->unk15E) : D_807FDC94->y, D_807FDC94->z, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
            gCurrentActor->unk132 = 2;
        case 7:
        case 0x35:
            actorEmptyStub();
            func_8072A920(gCurrentActor->state, 0, D_807FDC90->targetX, (D_807FDC90->targetY < (gCurrentActor->unkAC - gCurrentActor->unk15E)) ? D_807FDC90->targetY : (gCurrentActor->unkAC - gCurrentActor->unk15E), D_807FDC90->targetZ, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    B7490A->unkE4 = mathAngleEaseToward(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14);
                    break;
                case 2:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2E2);
            break;
    }
    st = gCurrentActor->state;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
            break;
        default:
            enemyAggroStateUpdate(0x6400, 0x2E2, 0x2E2);
            break;
    }
    func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B3420(void) {
    f32 dx;
    f32 dy;
    f32 dz;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 0x24;
        gCurrentActor->flags |= 0x400;
        D_807FDC90->timer = 0x5A;
        gCurrentActor->state = 0;
        gCurrentActor->unk155[0] = 0;
        func_8067ACB4(gCurrentActor);
        actorClearNodeFlag(gCurrentActor, 1);
    }
    dx = gCurrentActor->x - D_807FDC94->x;
    dy = gCurrentActor->y - D_807FDC94->y;
    dz = gCurrentActor->z - D_807FDC94->z;
    if (dx * dx + dy * dy + dz * dz > 90000.0f) {
        gCurrentActor->flags |= 0x80000000;
    } else {
        gCurrentActor->flags &= 0x7FFFFFFF;
    }
    switch (gCurrentActor->state) {
        case 0:
            if (D_807FDC90->timer != 0) {
                D_807FDC90->timer--;
            } else {
                actorScriptStart(gCurrentActor, 0x35D);
                scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
                gCurrentActor->state = 1;
                gCurrentActor->unk155[0] = 0;
            }
            break;
        case 1:
            if (gCurrentActor->unk155[0] != 0) {
                gCurrentActor->state = 2;
                gCurrentActor->unk155[0] = 0;
                D_807FDC90->timer = 0x5A;
            }
            break;
        case 2:
            if (D_807FDC90->timer != 0) {
                D_807FDC90->timer--;
            } else {
                gCurrentActor->unk132 = 2;
                scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
                gCurrentActor->state = 3;
                gCurrentActor->unk155[0] = 0;
            }
            break;
        case 3:
            if (gCurrentActor->unk155[0] != 0) {
                gCurrentActor->unk132 = 1;
                gCurrentActor->state = 0;
                gCurrentActor->unk155[0] = 0;
                D_807FDC90->timer = 0x5A;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSwellBurstUpdate(void) {
    f32 dx;
    f32 var;
    f32 scaleMultiplier;
    u8 st;
    s16 i;

    var = gCurrentActor->unk4->unk38 * 800.0f;
    scaleMultiplier = 1.1f;
    if (gCurrentMap == 0xC7) {
        if (!(D_807FBB4C->contactFlags & 4)) {
            var = 0.0f;
            scaleMultiplier = 0.4f;
        } else {
            var = var * 0.75;
            scaleMultiplier = 0.7f;
        }
    }
    var = var * var;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 4;
        func_8067ACB4(gCurrentActor);
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (gCurrentActor->state != 0x27)) {
        gCurrentActor->state = 0x27;
        gCurrentActor->unk155[0] = 0;
    } else if (gCurrentActor->state != 0x27) {
        dx = D_807FDC94->x - gCurrentActor->x;
        if (dx * dx + (D_807FDC94->y - gCurrentActor->y) * (D_807FDC94->y - gCurrentActor->y) + (D_807FDC94->z - gCurrentActor->z) * (D_807FDC94->z - gCurrentActor->z) < var) {
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155[0] = 0;
        }
    }
    effectSpawnSparks(0x1F, 0);
    switch (gCurrentActor->state) {
        case 4:
            actorMoveWithinZone(0, 0.0f, 0.0f, 2, 0.0f);
            if (gCurrentActor->y < gCurrentActor->unkAC) {
                gCurrentActor->y = gCurrentActor->unkAC;
                B7490A->unkC0 = B7490A->unkC4;
            }
        case 0:
            func_8072E1A4(0xA, D_807FDC94);
            break;
        case 0x27:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C2, 0xFF, 0x7F, 0);
                    D_807FDC90->scale = 2.0 * gCurrentActor->unk4->unk38;
                    gCurrentActor->unk155[0]++;
                case 1:
                    if (D_807FDC90->scale > (dx = gCurrentActor->unk4->unk38)) {
                        actorSetUniformScale(gCurrentActor, dx * 1.01);
                    } else {
                        for (i = 0; i < 0xC; i++) {
                            func_807149B8(1);
                            func_807149FC(2);
                            func_80714950(i + 0x0B020000);
                            func_8071498C(effectRadialSprayUpdate);
                            func_80714998(1);
                            func_80714CC0(D_8072073C, 2.0 * gCurrentActor->unk4->unk38, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                        }
                        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3D, 0xFF, 0x7F, 0);
                        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x35C, 0xFF, 0x7F, 0, 0x32, 0.3f, 0);
                        tagBarrelSpawnActorSmokePuffs(0, 1);
                        actorGetOrSetNodeScale(gCurrentActor, 1, gCurrentActor->unk140->unkC * scaleMultiplier);
                        actorSetCollisionRadius(gCurrentActor, gCurrentActor->unk140->unkC * scaleMultiplier);
                        gCurrentActor->flags &= ~4;
                        gCurrentActor->unk155[0]++;
                    }
                    break;
                case 5:
                    gCurrentActor->state = 0x40;
                    break;
                default:
                    gCurrentActor->unk155[0]++;
            }
            break;
        case 2:
        case 3:
            dx = D_807FDC90->targetY;
            func_8072A920(gCurrentActor->state, 0, D_807FDC90->targetX, (dx < (gCurrentActor->unkAC - gCurrentActor->unk15E)) ? dx : (gCurrentActor->unkAC - gCurrentActor->unk15E), D_807FDC90->targetZ, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        default:
            func_8072B7CC(0x32E);
            break;
    }
    st = gCurrentActor->state;
    if (st == 2 || st == 3) {
        patrolPathStep(st, 1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void projectileSpawnFromActorNode(u8 nodeIndex) {
    projectileGetTargetCoords(gCurrentActor, nodeIndex);
    projectileSpawnNodeEntry(0x32, 1, 0.3f, ((s16 *)gCurrentActor)[0xEE / 2], 80.0f, 0.0f, gCurrentActor);
}

void projectileAimAtTargetFromActor(void) {
    projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y - 5.0f, gCurrentActor->z);
    projectileAimAndSpawn(0x51, 1, 0.3f, D_807FDC94->x, D_807FDC94->y, D_807FDC94->z, 80.0f, gCurrentActor);
}


void func_806B3D18(void) {
    switch (gCurrentActor->unk155[0]) {
        case 0:
            if (func_8072E0A8(0x96, 0x96)) {
                actorScriptStart(gCurrentActor, 0x253);
                gCurrentActor->unk155[0] = 1;
            }
            break;
        case 2:
            projectileSpawnFromActorNode(2);
            gCurrentActor->unk155[0] = 3;
            break;
    }
}

void func_806B3DA4(void) {
    if (D_807FDC90->timer != 0) {
        D_807FDC90->timer--;
        return;
    }
    if (func_8072E0A8(0x96, 0x96)) {
        projectileSpawnFromActorNode(1);
        D_807FDC90->timer = D_80750340;
    }
}

void func_806B3E08(void) {
    if (D_807FDC90->timer != 0) {
        D_807FDC90->timer--;
        if (gFrameCounter & 1) {
            projectileAimAtTargetFromActor();
        }
    } else if (func_8072E0A8(0x96, 0x96)) {
        D_807FDC90->timer = 0x14;
    }
}

void func_806B3E7C(void) {
    if (D_807FDC90->timer != 0) {
        D_807FDC90->timer--;
        return;
    }
    if (zoneCanReachPoint(gCurrentActor, D_807FDC94->x, D_807FDC94->y, D_807FDC94->z, D_807FDCA0) && func_8072E0A8(0x96, 0x96)) {
        gCurrentActor->state = 0x26;
        gCurrentActor->unk155[0] = 0;
    }
}


void func_806B3F3C(void) {
    if (((randomNonNegative() >> 15) % 1000) >= 0x3E4) {
        gCurrentActor->state = 0x1C;
        gCurrentActor->unk155[0] = 0;
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
        func_807149C8(col, col, col, *(u8 *) ((u8 *) gCurrentActor + 0x129));
        effectSpawnBoneDefault(gCurrentActor, 1, f, 0.0f, 0.0f, 0.0f, -0x50);
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
    if ((sfxId != 0) && (gCurrentActor->state != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(gCurrentActor, sfxId, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    if (!(gCurrentActor->flags & 0x10)) {
        *heightTarget = D_807FDC9C->unkA;
        if (D_807FDC9C->unkB == 0) {
            D_807FDC9C->unkB = 0x28;
        }
    }
    st = gCurrentActor->state;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (st != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, animId1);
        B7490A->unkC0 = 300.0f;
        *heightTarget = 0;
        D_807FDC90->timer = 0x2BC;
        st = gCurrentActor->state;
    }
    targetX = D_807FDC90->targetX;
    targetZ = D_807FDC90->targetZ;
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
            if (gCurrentActor->y < (f32) (*heightTarget + (0, D_807FDC9C->unk6))) { // FAKE: comma wrapper steers ugen temp order
                gCurrentActor->y = (f32) ((f64) gCurrentActor->y + ((f64) (u32) D_807FDC9C->unkB * 0.03125));
            } else {
                if ((camIsCutsceneActive(D_807FDC90) == 0) && (callback != NULL)) {
                    callback();
                }
            }
            actorMoveWithinZone(gCurrentActor->state, (f32) targetX, (f32) targetZ, 0x2C1, 0.0f);
            B7490A->unkE8 = mathAngleEaseToward(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    D_807FDC90->targetX = (s16) (s32) D_807FDC94->x;
                    D_807FDC90->targetY = (s16) (s32) D_807FDC94->y;
                    D_807FDC90->targetZ = (s16) (s32) D_807FDC94->z;
                    gCurrentActor->unk155[0] = gCurrentActor->unk155[0] + 1;
                    D_807FDC90->timer = 0x64;
                case 1:
                    if ((actorFlyTowardPosition((B7490Pos *) D_807FDC90, 0x23) & 1) || (gCurrentActor->y < (f32) (D_807FDC90->targetY + 0xF))) {
                        gCurrentActor->state = D_807FDC9C->unk10;
                        gCurrentActor->unk155[0] = 0;
                    }
                    break;
            }
            break;
        case 0x37:
            gCurrentActor->yaw = gCurrentActor->yaw + D_807FDC90->timer;
            D_807FDC90->timer = ((D_807FDC90->timer - 0x11) < 0) ? 0 : (D_807FDC90->timer - 0x11);
            if (D_807FDC90->timer == 0) {
                sfxStopSlotSound(gCurrentActor, 0);
            }
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    if (gCurrentActor->actorType == 0x11D) {
                        gCurrentActor->unk155[0] = 3;
                        break;
                    }
                    B7490A->unkC0 = 50.0f;
                    gCurrentActor->unk155[0] = gCurrentActor->unk155[0] + 1;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x222, 0.0f);
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(animId2);
            break;
    }
    st = gCurrentActor->state;
    switch (st) {
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (!gCurrentActor->state) {
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
    if (gCurrentActor->state != 0x37) {
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
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(1, 1);
        D_807FDC90->scale = gCurrentActor->unk4->unk38;
        gCurrentActor->speedXZ = (f32) (u32) D_807FDC9C->unkC;
        *heightPtr = D_807FDC9C->unkA;
        B7490A->unkC4 = D_807502EC;
    }
    targetHeight = D_807FDC9C->unk6 - (0 - *heightPtr);  // FAKE: negated subtrahend flips the commutative + operand order
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (action != 0x37)) {
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155[0] = 0;
    }
    switch (action) {
        case 2:
        case 3:
            if (gCurrentActor->unk155[0] == 0) {
                actorScriptStart(gCurrentActor, animId1);
                gCurrentActor->unk155[0] = gCurrentActor->unk155[0] + 1;
            }
            actorMoveWithinZone(action, (f32) D_807FDC90->targetX, (f32) D_807FDC90->targetZ, 0xE1, 0.0f);
            if (gCurrentActor->y < (f32) targetHeight) {
                if (gCurrentActor->unk155[0] == 2) {
                    gCurrentActor->y = (f32) ((f64) gCurrentActor->y + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.03125));
                } else {
                    gCurrentActor->y = (f32) ((f64) gCurrentActor->y + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.015625));
                }
            }
            B7490A->unkE8 = mathAngleEaseToward(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                case 1:
                case 2:
                    actorScriptStart(gCurrentActor, animId2);
                    gCurrentActor->unk155[0] = 3;
                case 3:
                    actorFlyTowardPosition((void *) D_807FDC90, 0x26);
                    break;
            }
            break;
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            if (gCurrentActor->contactFlags & 1) {
                gCurrentActor->state = 0x40;
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
                gCurrentActor->state = D_807FDC9C->unk10;
                gCurrentActor->unk155[0] = 0;
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

    heightPtr = ((B7490Actor *) gCurrentActor)->unk178;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags = gCurrentActor->flags | 0x400;
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x40;
        gCurrentActor->unk16A = 0xFA;
        gCurrentActor->unk16B = 0xFA;
        gCurrentActor->unk16C = 0xFA;
        actorSpawnNodeEntryAtActor(0x2D, 0x44);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2C1, 0xFF, 0x7F, 0, 0x14, 0.0f, 0);
    }
    deltaHeight = D_807FDC90->targetY - D_807FDC9C->unk6;
    *heightPtr = (deltaHeight < 0) ? 0 : deltaHeight;
    if ((D_807FBD70 == 9) && (gCurrentActor->state != 0x37)) {
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155[0] = 0;
        actorScriptStart(gCurrentActor, 0x248);
        actorAttachChildCallbacks();
        sfxAllocateChannel(0x14, 1.0f);
        csModelStateSetFirstByte(0x7F, 0xA);
    }
    action = gCurrentActor->state;
    if ((action != 0x37) && (action != 0x40)) {
        actorPlaceAttachedChildren(-0x1E);
    }
    curScale = gCurrentActor->unk4->unk34;
    origScale = gCurrentActor->unk4->unk34;
    actorSetUniformScale(gCurrentActor, (f32) (((f64) (D_807FDC90->scale - origScale) * 0.05) + (f64) origScale));
    timer = D_807FDC90->timer;
    if (timer != 0) {
        D_807FDC90->timer = timer - 1;
        if (gFrameCounter & 4) {
            gCurrentActor->flags = gCurrentActor->flags | 0x800000;
        } else {
            gCurrentActor->flags = gCurrentActor->flags & 0xFF7FFFFF;
        }
    } else {
        gCurrentActor->unk132 = 1;
        gCurrentActor->flags = gCurrentActor->flags & 0xFF7FFFFF;
        if (D_807FBD70 == 4) {
            gCurrentActor->unk132 = 2;
            D_807FDC90->timer = 0x1E;
            D_807FDC90->scale = (f32) ((f64) D_807FDC90->scale * 0.7);
            func_8072D9D4();
            camStartPath(gCurrentActor, 3, 5);
            if (((B7490Actor *) gCurrentActor)->unk134 & 1) {
                actorScriptStart(gCurrentActor, 0x24A);
            } else {
                actorScriptStart(gCurrentActor, 0x249);
            }
        }
    }
    actorAirPatrolStep(gCurrentActor->state, 0x247, 0x246);
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B50F4(void) {
    behaviourFrameBegin();
    actorAirPatrolStep(gCurrentActor->state, 0x23D, 0x23E);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B513C(void) {
    s32 inWaterFlag;
    s16 alphaDelta;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x30C, 0x30B, 0x30D);
        gCurrentActor->flags = gCurrentActor->flags & 0xFFFF7FFF;
    }
    if (gCurrentMap == 0xA6) {
        inWaterFlag = gActivePlayerState->stateFlags & 0x40;
        if ((inWaterFlag != 0) && (gCurrentActor->unk128 == 0)) {
            D_807FDC90->timer = 0xA;
            gCurrentActor->unk144 = 0x24;
        } else if ((inWaterFlag == 0) && (gCurrentActor->unk128 == 0xFF)) {
            D_807FDC90->timer = -0xA;
            gCurrentActor->unk144 = 1;
        }
        alphaDelta = D_807FDC90->timer;
        if (alphaDelta != 0) {
            gCurrentActor->unk128 = gCurrentActor->unk128 + alphaDelta;
            if (gCurrentActor->unk128 >= 0x100) {
                gCurrentActor->unk128 = 0xFF;
                D_807FDC90->timer = 0;
            } else if (gCurrentActor->unk128 < 0) {
                gCurrentActor->unk128 = 0;
                D_807FDC90->timer = 0;
            }
        }
    }
    func_806B42A8((gFrameCounter & 1) ? func_806B3E7C : func_806B3F3C, 0x30E, 0x30B, 0);
}

void func_806B52DC(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x60;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        gCurrentActor->speedXZ = (f32) (((randomNonNegative() >> 15) % 100) + 0x12C);
        gCurrentActor->y += (f32) ((randomNonNegative() >> 15) % 30);
        gCurrentActor->flags = gCurrentActor->flags & 0xFFFF7FFF;
        gCurrentActor->unk128 = 0;
        ((B7490Actor *) gCurrentActor)->unkEC = ((randomNonNegative() >> 15) % 7) + 0xF;
    }
    func_8067ACB4(gCurrentActor);
    actorApplyVelocityCustom(gCurrentActor, gCurrentActor->speedXZ, 0.0f);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    switch (gCurrentActor->state) {
    case 6:
        gCurrentActor->unk128 = gCurrentActor->unk128 + ((B7490Actor *) gCurrentActor)->unkEC;
        if (gCurrentActor->unk128 >= 0xFF) {
            gCurrentActor->unk128 = 0xFF;
            gCurrentActor->state = 0x37;
        }
        break;
    case 0x37:
        gCurrentActor->unk128 = gCurrentActor->unk128 - ((B7490Actor *) gCurrentActor)->unkEC;
        if (gCurrentActor->unk128 < 0) {
            gCurrentActor->state = 0x3C;
            gCurrentActor->unk128 = 0;
        }
        break;
    default:
        func_8072B7CC(0x333);
        break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
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
    if ((gCurrentActor->state != 0x40) && (gCurrentActor->state != 0x37) && ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0))) {
        sfxStopSlotSound(gCurrentActor, 0);
        actorScriptStart(gCurrentActor, 0x331);
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155[0] = 0;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB4C, 0x16, 0xFF, 0x7F, 0x1E);
    }
    if (!(gCurrentActor->flags & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x20;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        gCurrentActor->speedXZ = 40.0f;
        gCurrentActor->state = 0x23;
        gCurrentActor->unk155[0] = 0;
        B7490A->unkEC = ((randomNonNegative() >> 15) % 7) + 0xF;
        state->unk0 = gCurrentActor->x;
        state->unk4 = gCurrentActor->y;
        state->unk8 = gCurrentActor->z;
        state->unk10 = 1;
        state->unkC = gCurrentActor->y;
        state->unk12 = (randomLcgNext() & 0xFF) + 0x78;
    }
    if ((gCurrentActor->state != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(gCurrentActor, 0x10E, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    switch (gCurrentActor->state) {
        case 0x26:
            state->unk0 = D_807FBB4C->x;
            state->unk4 = D_807FBB4C->y;
            state->unk8 = D_807FBB4C->z;
            state->unk12 = (randomLcgNext() & 0xFF) + 0x78;
        case 0x23:
            gCurrentActor->yaw = gCurrentActor->yaw - (mathAngleSignedDistance(mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, state->unk0, state->unk8) + 0x800, gCurrentActor->yaw) >> 4);
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
                gCurrentActor->state = 0x23;
            }
            if (gCurrentActor->state == 0x23) {
                state->unk12 = state->unk12 - 1;
                if (state->unk12 <= 0) {
                    state->unk10 = 0x3C;
                    gCurrentActor->state = 0x26;
                }
            }
            zoneY = (f32) ((f64) (state->unk4 - gCurrentActor->y) * 0.0625);
            if ((f64) zoneY > 8.0) {
                zoneY = 8.0f;
            }
            if ((f64) zoneY < -8.0) {
                zoneY = -8.0f;
            }
            gCurrentActor->x += func_80612794(gCurrentActor->yaw) * 8.0;
            gCurrentActor->y = gCurrentActor->y + zoneY;
            gCurrentActor->z += func_80612790(gCurrentActor->yaw) * 8.0;
            break;
        case 0x37:
            gCurrentActor->flags = gCurrentActor->flags & 0xFFFF7FFF;
            gCurrentActor->unk128 = gCurrentActor->unk128 - 8;
            gCurrentActor->y = (f32) ((f64) gCurrentActor->y - 10.0);
            if (gCurrentActor->unk128 < 0) {
                gCurrentActor->unk128 = 0;
                gCurrentActor->state = 0x40;
                gCurrentActor->unk155[0] = 0;
                gCurrentActor->unk144 = 1;
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
    actorUpdateModelMatrix(gCurrentActor, 0);
}
