#include "common.h"
#include "actor.h"


typedef struct B2CE0Sub178 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
} B2CE0Sub178;

typedef struct B2CE0Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[4];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xC];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[4];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ u8 pad13C[0xA];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0xE];
    /* 0x178 */ B2CE0Sub178 *unk178;
} B2CE0Actor;

typedef struct B2CE0Node {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B2CE0Node;

typedef struct B2CE0ModelHdr {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} B2CE0ModelHdr;

typedef struct B2CE0View90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xD];
    /* 0x35 */ u8 unk35;
} B2CE0View90;

typedef struct B2CE0View9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} B2CE0View9C;

extern B2CE0Actor *gCurrentActor;
extern B2CE0Actor *gSpawnedActor;

s32 randomNonNegative(void);
void actorUpdateModelMatrix(B2CE0Actor *, s32);

void matrixMakeRotationX(f32 (*)[4], f32);
void collisionSetQueryMode(s32);
void actorApplyGravity(void);
void actorUpdatePrevContactFlags(B2CE0Actor *);
void actorApplyVelocity(B2CE0Actor *);
void actorUpdateFloorContactAndTilt(B2CE0Actor *, f32);
void billboardSubmit(B2CE0Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void effectCreateAtPosition(void *, f32, f32, f32, f32);
void actorDespawn(B2CE0Actor *);
extern u8 D_8071FBC8[];
extern ActorGlobalState gActorGlobalState;
void behaviourSetAnimIds(s32, s32, s32);
void func_80724CA4(s32, s32);
void actorScriptStart(B2CE0Actor *, s32);
void func_80724E48(u8);
u32 actorMoveWithinZone(u32, f32, f32, s32, f32);
void actorSetTargetSpeed(B2CE0Actor *, s32);
void behaviourUpdateShadowAlpha();
void actorSetDefaultState();
s32 behaviourCheckRandomAnimTrigger();
void patrolPathStep(u32, s32);
void behaviourUpdateContactAndState();
void behaviourFrameBegin(void);
s32 behaviourIsTargetWithinAngle(u16);
s16 mathAngleEaseToward(s16, s16, f32);
void enemyAggroStateUpdate(s32, s32, s32);
void behaviourCalculateDamageForce(s32, s32);
void behaviourFadeOutWithinZone(s32);
void behaviourSpawnExplosionAndSound();
void actorTurnTowardActorYaw(s32, void *);
void sfxSpawnTableNodes(void *);
void actorPatrolFollowerUpdate();
void effectSpawnOctagonRing(f32, f32, f32, f32);
s32 zoneCanReachPoint(B2CE0Actor *, s16, s16, s16, s32);
void projectileGetTargetCoords(B2CE0Actor *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s16, f32, f32, B2CE0Actor *);
void func_8072881C(s32, void *);
s32 actorIsTargetWithinDistance(s32);
extern s32 D_807FDCA0;
extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];

void func_806ADFE0(void) {
    f32 transMtx[4][4];
    f32 rotMtx[4][4];

    if (!(gCurrentActor->unk60 & 0x10)) {
        gCurrentActor->unkB8 = (randomNonNegative() >> 15) % 50 + 0x46;
        gCurrentActor->unkC0 = gCurrentActor->unkB8 * 2;
        gCurrentActor->unkC4 = -30.0f;
        gCurrentActor->unkC8 = -220.0f;
        gCurrentActor->unk168 = (randomNonNegative() >> 15) % 400 + 200;
    }
    gCurrentActor->unkE6 += gCurrentActor->unk168;
    if (gCurrentActor->unk168 > 0) {
        gCurrentActor->unk168 -= 10;
    }
    collisionSetQueryMode(1);
    actorApplyGravity();
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 200, 0x80, 0, 1.0f);
    if (gCurrentActor->unk15F != 0) {
        actorUpdateModelMatrix(gCurrentActor, 0);
    } else {
        guTranslateF(transMtx, 0, -30.0f, 0);
        matrixMakeRotationX(rotMtx, 180.0f);
        guMtxCatF(transMtx, rotMtx, transMtx);
        guTranslateF(rotMtx, 0, 30.0f, 0.0f);
        guMtxCatF(transMtx, rotMtx, gCurrentActor->unkC);
        actorUpdateModelMatrix(gCurrentActor, 1);
    }
    if ((gCurrentActor->unk6A & 1) && !(gCurrentActor->unk6C & 1)) {
        sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x56, 0xB4, 0x96, 1, 0x4B, 0.3f, 0);
        gCurrentActor->unkB8 = gCurrentActor->unkB8 * 0.6;
        gCurrentActor->unkC0 = gCurrentActor->unkB8 * 3.0f;
        return;
    }
    if ((gCurrentActor->unk6A & 1) && (gCurrentActor->unk6C & 1)) {
        effectCreateAtPosition(D_8071FBC8, 1.0f, gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84);
        actorDespawn(gCurrentActor);
    }
}

s32 actorSpawn(s32, s32);
u32 actorGetNodePos(B2CE0Actor *, s16, f32 *, f32 *, f32 *);
void actorSetUniformScale(void *, s32);

void actorSpawnChildAtNode(s32 actorType, s16 angleOffset, s16 nodeIndex, s16 extraParam) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    if (actorSpawn(0xED, actorType) != 0) {
        actorGetNodePos(gCurrentActor, nodeIndex, &nodeX, &nodeY, &nodeZ);
        gSpawnedActor->unkA4 = gCurrentActor->unkA4;
        gSpawnedActor->unkE6 = gCurrentActor->unkE6 + angleOffset;
        gSpawnedActor->unkEE = gSpawnedActor->unkE6;
        gSpawnedActor->unk168 = extraParam;
        gSpawnedActor->unk7C = nodeX;
        gSpawnedActor->unk80 = nodeY;
        gSpawnedActor->unk84 = nodeZ;
        actorSetUniformScale(gSpawnedActor, *(s32 *)&gCurrentActor->unk4->scaleY);
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void lensFlareAddSource(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32);
f32 mathCosF(s16);
f32 mathSinF(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void playerStateQueueCallback(s32, B2CE0Actor *, s32);

void func_806AE394(f32 distOffset, f32 radius) {
    f32 node1X;
    f32 node1Y;
    f32 node1Z;
    f32 node2X;
    f32 node2Y;
    f32 node2Z;
    s16 angle;

    actorGetNodePos(gCurrentActor, 1, &node1X, &node1Y, &node1Z);
    actorGetNodePos(gCurrentActor, 2, &node2X, &node2Y, &node2Z);
    angle = mathAngleBetweenPoints2D(node2X, node2Z, node1X, node1Z);
    lensFlareAddSource(node1X, node1Y, node1Z, node2X, node2Y, node2Z, 0.6f, 0xFF, 0xFF, 0xFF);
    node1X = mathSinF(angle) * distOffset + gCurrentActor->unk7C;
    node1Z = mathCosF(angle) * distOffset + gCurrentActor->unk84;
    lightAdd(node1X, gCurrentActor->unk80, node1Z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, 0xFF, 0xFF);
    if (gCurrentActor->unk154 != 0) {
        if ((gBehaviourTargetActor->x - node1X) * (gBehaviourTargetActor->x - node1X) + (gBehaviourTargetActor->y - gCurrentActor->unk80) * (gBehaviourTargetActor->y - gCurrentActor->unk80) + (gBehaviourTargetActor->z - node1Z) * (gBehaviourTargetActor->z - node1Z) < radius * radius) {
            gCurrentActor->unkE6 = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->unk7C, gCurrentActor->unk84);
            playerStateQueueCallback(0x43, gCurrentActor, 0);
            gCurrentActor->unk154 = 0;
            gCurrentActor->unk155 = 0;
        }
    }
}

typedef struct B2CE0ActorView134 {
    /* 0x000 */ u8 pad0[0x134];
    /* 0x134 */ s16 unk134;
} B2CE0ActorView134;

extern s32 gCurrentMap;
void actorClearNodeFlag(B2CE0Actor *, s32);
void csModelStateSetFirstByte(s32, s32);

void func_806AE588(void) {
    s32 sel;
    s32 sw;

    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        behaviourSetAnimIds(0x1FD, 0x1FB, 0x1FC);
        func_80724CA4(3, 1);
        actorClearNodeFlag(gCurrentActor, 3);
        if (gCurrentMap == 0xA5) {
            gCurrentActor->unk132 = 1;
        }
    }
    func_8072881C(0, gBehaviourWorkState->unk28);
    sel = gCurrentActor->unk154;
    if ((sel != 0x32) || (gActorGlobalState.unk15 != 0)) {
        if (((gActorGlobalState.unk200 == 9) || (gActorGlobalState.unk15 != 0)) && (sel != 0x37)) {
            if (((B2CE0ActorView134 *)gCurrentActor)->unk134 < -1) {
                behaviourCalculateDamageForce(gActorGlobalState.unk1FC, 0x202);
                gCurrentActor->unkC0 = 250.0f;
            } else {
                behaviourCalculateDamageForce(gActorGlobalState.unk1FC, 0x201);
                gCurrentActor->unkC0 = 200.0f;
            }
            ((B2CE0View90 *)gBehaviourWorkState)->unk35 = 2;
            gCurrentActor->unk138 &= 0xFFFF7FFF;
        } else if (gActorGlobalState.unk200 == 4) {
            behaviourSpawnExplosionAndSound(0x1FF, 0x31, gActorGlobalState.unk1FC);
        } else if (gActorGlobalState.unk200 == 5) {
            behaviourSpawnExplosionAndSound(0x200, 0x32, gActorGlobalState.unk1FC);
            gCurrentActor->unkC0 = 220.0f;
        }
    }
    sel = gCurrentActor->unk154;
    sw = sel;
    switch (sel) {
    case 0x31:
        if ((gCurrentActor->unk155 != 0) || ((*(B2CE0Node **)gCurrentActor->unk4)->unk24 == 0.0f)) {
            actorSetDefaultState(0x1FB);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        gCurrentActor->unkE6 = mathAngleEaseToward(gCurrentActor->unkE6, gCurrentActor->unkEE, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            gCurrentActor->unkC0 = 200.0f;
            gCurrentActor->unkB8 = 120.0f;
            gCurrentActor->unk155++;
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 3:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x1FD);
            gCurrentActor->unk155++;
        case 1:
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->unkB8 < 1.0f) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 0xF) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x1FB);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x1FE);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            gCurrentActor->unk132 = 2;
            break;
        case 3:
            gCurrentActor->unk132 = 1;
            break;
        case 4:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger() != 0) {
            gCurrentActor->unk154 = 0x11;
            gCurrentActor->unk155 = 0;
        }
    case 0x23:
        if ((gActorGlobalState.unk200 == 2) && (behaviourIsTargetWithinAngle(0x2710) != 0)) {
            gCurrentActor->unk154 = 0x27;
            gCurrentActor->unk155 = 0;
        }
        sel = gCurrentActor->unk154;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sw == 0x35) ? 2 : 3);
        actorMoveWithinZone(gCurrentActor->unk154, (f32)gBehaviourWorkState->targetX, (f32)gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->unkE6 = mathAngleEaseToward(gCurrentActor->unkE6, gCurrentActor->unkEE, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if ((gCurrentMap == 0xA5) && (gCurrentActor->unk15F != 0)) {
                csModelStateSetFirstByte(0, 0xA);
            }
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->unk155++;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            behaviourFadeOutWithinZone(8);
            break;
        case 3:
            gCurrentActor->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        behaviourUpdateContactAndState(0x1FB, sel);
        break;
    }
    sel = gCurrentActor->unk154;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->unk154, 1);
    default:
        enemyAggroStateUpdate(0x6400, 0x1FB, 0x1FC);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806AEE08(void) {
    if ((randomNonNegative() >> 15) % 1000 >= 0x3D5 && behaviourIsTargetWithinAngle(0xFA0) != 0 && !(((B2CE0View90 *)gBehaviourWorkState)->unk1A & 0x80)) {
        gCurrentActor->unk154 = 0x25;
        gCurrentActor->unk155 = 0;
    }
}

void func_806AEE84(void) {
    B2CE0Sub178 *patrolState;
    f32 scaleFactor;

    patrolState = gCurrentActor->unk178;
    scaleFactor = gCurrentActor->unk4->scaleY / 0.15;
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        patrolState->unk0 = 0x2710;
        patrolState->unk2 = 0x20;
        behaviourSetAnimIds(0x2AD, 0x2AB, 0x2AC);
        func_80724CA4(2, 1);
    }
    if (gCurrentActor->unk154 != 0x32 || gActorGlobalState.unk15 != 0) {
        if ((gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->unk154 != 0x37) {
            behaviourCalculateDamageForce(gActorGlobalState.unk1FC, 0x2AE);
            gBehaviourWorkState->timer = 0x1C2;
        } else if (gActorGlobalState.unk200 == 4) {
            behaviourSpawnExplosionAndSound(0x2B2, 0x31, gActorGlobalState.unk1FC, &gActorGlobalState);
            gCurrentActor->unkB8 = 0.0f;
        } else if (gActorGlobalState.unk200 == 5) {
            behaviourSpawnExplosionAndSound(0x2B1, 0x31, gActorGlobalState.unk1FC, &gActorGlobalState);
            gCurrentActor->unkB8 = 0.0f;
        }
    }
    switch (gCurrentActor->unk154) {
        case 0x31:
            if (gCurrentActor->unk155 != 0 || (*(B2CE0ModelHdr **)gCurrentActor->unk4)->unk24 == 0.0f) {
                actorSetDefaultState(0x2AB);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x11:
            func_80724E48(5);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2B0);
                    gCurrentActor->unk155 = 1;
                case 1:
                    actorMoveWithinZone(0x11, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    if (gCurrentActor->unkB8 < 1.0f) {
                        gCurrentActor->unk155++;
                    }
                    break;
                case 2:
                    func_806AEE08();
                    behaviourUpdateShadowAlpha();
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3DF && (*(B2CE0ModelHdr **)gCurrentActor->unk4)->unk10 != 0x4C4) {
                        actorSetDefaultState(0x2AB);
                    }
            }
            break;
        case 0x27:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    gCurrentActor->unkB8 = 0.0f;
                    actorScriptStart(gCurrentActor, 0x2B4);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    gCurrentActor->unk132 = 2;
                    break;
                case 3:
                    gCurrentActor->unk132 = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            break;
        case 0x25:
            func_80724E48(0);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2B3);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(gCurrentActor, 2);
                    projectileSpawnNodeEntry(0x32, 0x63, scaleFactor * 0.4, gCurrentActor->unkE6, 300.0f, 280.0f, gCurrentActor);
                    gCurrentActor->unk155 = 3;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->unk154 = 0x11;
                gCurrentActor->unk155 = 0;
            }
        case 0x23:
            if (gActorGlobalState.unk200 == 2 && behaviourIsTargetWithinAngle(0x1388) != 0) {
                gCurrentActor->unk154 = 0x27;
                gCurrentActor->unk155 = 0;
            }
        case 0x10:
            func_806AEE08();
            func_80724E48(gCurrentActor->unk154 == 1 ? 2 : 0);
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(gCurrentActor->unk154 == 0x35 ? 2 : 3);
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->unkE6 += gBehaviourWorkState->timer;
                    gBehaviourWorkState->timer = gBehaviourWorkState->timer * 0.95;
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->unk155++;
                case 2:
                    behaviourFadeOutWithinZone(5);
                    break;
                case 3:
                    gCurrentActor->unk154 = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            behaviourUpdateContactAndState(0x2AB);
            break;
    }
    switch (gCurrentActor->unk154) {
        case 0x24:
        case 0x25:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->unk154, 1);
        default:
            enemyAggroStateUpdate(0x6400, 0x2AB, 0x2AC);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806AF688(void) {
    s32 var;

    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        behaviourSetAnimIds(0x2C0, 0x2C1, 0x2C1);
        func_80724CA4(0xE, 1);
        ((B2CE0View90 *)gBehaviourWorkState)->unk1A |= 0x800;
        gCurrentActor->unk60 |= 0x400;
    }
    func_806AE394(40.0f, 70.0f);
    if (gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) {
        gCurrentActor->unk154 = 0x3A;
        gCurrentActor->unk155 = 0;
    }
    switch (gCurrentActor->unk154) {
        case 0x11:
            func_80724E48(2);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2C0);
                    gCurrentActor->unk155++;
                case 1:
                    actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    if (gCurrentActor->unkB8 < 1.0f) {
                        gCurrentActor->unk155++;
                    }
                    break;
                case 2:
                    behaviourUpdateShadowAlpha();
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                        actorSetDefaultState(0x1FB);
                    }
                    break;
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->unk154 = 0x11;
                gCurrentActor->unk155 = 0;
            }
            func_80724E48(gCurrentActor->unk154 == 1 ? 2 : 0);
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(gCurrentActor->unk154 == 0x35 ? 2 : 3);
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        case 0x37:
            gCurrentActor->unk154 = 0x40;
            break;
        default:
            behaviourUpdateContactAndState(0x2C0);
            break;
    }
    switch (gCurrentActor->unk154) {
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->unk154, 1);
            break;
        case 0x31:
        case 0x37:
        case 0x40:
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void effectSetDepth(s32);
void effectSetDuration(s32);
void effectSetCallback(void (*)());
void effectSetMode(s32);
void effectSetSpeed(s32);
void effectCreateAtActorBone(void *, f32, B2CE0Actor *, s32, s32);
void effectTumbleBounceUpdate();
extern u8 D_8072073C;

void effectSpawnActorParticleBurst(u8 nodeIndex) {
    s16 i;
    f32 temp;

    for (i = 0; i < 7; i++) {
        temp = gCurrentActor->unk4->scaleY / 0.15;
        effectSetDepth(1);
        effectSetDuration(10);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(0);
        effectCreateAtActorBone(&D_8072073C, temp * 0.15, gCurrentActor, nodeIndex, 0);
    }
}

void func_806AFB58(void) {
    s32 sel;

    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        gCurrentActor->unk146 = -1;
        behaviourSetAnimIds(0x2D9, 0x2D7, 0x2D8);
        func_80724CA4(2, 1);
        gCurrentActor->unkEC = 0x1770;
    }
    if (((gActorGlobalState.unk200 == 9) || (gActorGlobalState.unk15 != 0)) && (gCurrentActor->unk154 != 0x37)) {
        behaviourCalculateDamageForce(gActorGlobalState.unk1FC, 0x2DD);
        ((B2CE0View90 *)gBehaviourWorkState)->unk35 = 2;
        gCurrentActor->unk138 &= 0xFFFF7FFF;
    } else if ((gActorGlobalState.unk200 == 4) || (gActorGlobalState.unk200 == 5)) {
        if (gCurrentActor->unk146 & 1) {
            ((B2CE0View90 *)gBehaviourWorkState)->unk1E = 0xF;
            ((B2CE0View90 *)gBehaviourWorkState)->unk1F = 0xF;
            gCurrentActor->unkEC = -1;
            actorSpawnChildAtNode(0xC2, 0x800, 1, 0x190);
            gSpawnedActor->unk15F = 1;
            effectSpawnActorParticleBurst(1);
        } else if (gCurrentActor->unk146 & 2) {
            effectSpawnActorParticleBurst(2);
        }
        gCurrentActor->unk146 = gCurrentActor->unk146 * 2;
        behaviourSpawnExplosionAndSound(0x2DC, 0x31, gActorGlobalState.unk1FC);
        ((B2CE0View90 *)gBehaviourWorkState)->unk26 = 0;
        gCurrentActor->unkB8 = 0.0f;
    }
    sel = gCurrentActor->unk154;
    switch (gCurrentActor->unk154) {
    case 0x31:
        if ((gCurrentActor->unk155 != 0) || ((*(B2CE0Node **)gCurrentActor->unk4)->unk24 == 0.0f)) {
            actorSetDefaultState(0x2D7, sel);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
        break;
    case 0x11:
        func_80724E48(5);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x2D9);
            gCurrentActor->unk155++;
        case 1:
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->unkB8 < 1.0f) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 0xF) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x2D7);
            }
            break;
        }
        break;
    case 0x27:
        if (gCurrentActor->unkEC < 0xFFFF) {
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
        }
        actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            if (((f64)gCurrentActor->unk4->scaleY > 0.18) && ((randomNonNegative() >> 0xF) % 1000 >= 0x1F5)) {
                actorScriptStart(gCurrentActor, 0x2DB);
            } else {
                actorScriptStart(gCurrentActor, 0x2DA);
            }
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            gCurrentActor->unk132 = 2;
            break;
        case 3:
            gCurrentActor->unk132 = 1;
            break;
        case 4:
            actorSetDefaultState(0x2D7);
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger((u32)gCurrentActor->unk154, sel) != 0) {
            gCurrentActor->unk154 = 0x11;
            gCurrentActor->unk155 = 0;
        }
    case 0x23:
        if ((gActorGlobalState.unk200 == 2) && (behaviourIsTargetWithinAngle(gCurrentActor->unkEC) != 0)) {
            gCurrentActor->unk154 = 0x27;
            gCurrentActor->unk155 = 0;
        }
        sel = gCurrentActor->unk154;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sel == 0x35) ? 2 : 3);
        actorMoveWithinZone(gCurrentActor->unk154, (f32)gBehaviourWorkState->targetX, (f32)gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->unkE6 = mathAngleEaseToward(gCurrentActor->unkE6, gCurrentActor->unkEE, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->unk155++;
        case 2:
            behaviourFadeOutWithinZone(8);
            break;
        case 3:
            gCurrentActor->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        behaviourUpdateContactAndState(0x2D7, sel);
        break;
    }
    sel = gCurrentActor->unk154;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->unk154, 1);
    default:
        enemyAggroStateUpdate(0x6400, 0x2D7, 0x2D8);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B02EC(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        behaviourSetAnimIds(0, 0x31E, 0x31F);
    }
    actorPatrolFollowerUpdate(0x320, 0, 0);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B0354(void) {
    behaviourFrameBegin();
    if ((gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->unk154 != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.unk1FC, 0x37A);
        gCurrentActor->unk138 &= ~0x8000;
    }
    switch (gCurrentActor->unk154) {
        case 4:
            if (gCurrentActor->unk4->animId == 0x378) {
                gCurrentActor->unk154 = 0x23;
                gCurrentActor->unk155 = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0
                       && zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, D_807FDCA0) != 0) {
                actorScriptStart(gCurrentActor, 0x37B);
                gCurrentActor->unk154 = 0x23;
                gCurrentActor->unk155 = 0;
                effectSpawnOctagonRing(0.7f, gCurrentActor->unk7C, gCurrentActor->unk80 + 10.0f, gCurrentActor->unk84);
            }
            break;
        case 0x23:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, ((B2CE0View9C *)gBehaviourExtraState)->unkD);
                    gCurrentActor->unk155++;
                case 1:
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                        gCurrentActor->unk155++;
                        actorScriptStart(gCurrentActor, 0x379);
                        actorSetTargetSpeed(gCurrentActor, 0);
                    } else {
                        if (gCurrentActor->unk4->animId == 0x378) {
                            actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                        } else {
                            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
                        }
                        if (actorIsTargetWithinDistance(0xC8) == 0
                            || zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, D_807FDCA0) == 0) {
                            actorScriptStart(gCurrentActor, 0x37C);
                            gCurrentActor->unk154 = 4;
                            gCurrentActor->unk155 = 0;
                            actorSetTargetSpeed(gCurrentActor, 0);
                        }
                    }
                    break;
                case 2:
                    actorMoveWithinZone(0, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    break;
            }
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->unk155++;
                case 2:
                    behaviourFadeOutWithinZone(0xA);
                    break;
                case 3:
                    gCurrentActor->unk154 = 0x40;
                    break;
            }
            break;
        default:
            behaviourUpdateContactAndState(0x378);
            break;
    }
    func_8072881C(0, (u8 *)gBehaviourWorkState + 0x28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 func_806B0770(void) {
    s32 found;
    s16 i;
    Actor *other;
    f32 dx;
    f32 dy;
    f32 dz;

    found = 0;
    for (i = 0; !found && i < gActiveActorCount; i++) {
        other = gActiveActors[i].actor;
        if (other->actorType == 0x29) {
            dx = other->x - gCurrentActor->unk7C;
            dy = other->y - gCurrentActor->unk80;
            dz = other->z - gCurrentActor->unk84;
            if (dx * dx + dy * dy + dz * dz < 10000.0f) {
                gCurrentActor->unk154 = 0x28;
                found = 1;
                gCurrentActor->unk155 = 0;
            }
        }
    }
    return found;
}

typedef struct B2CE0ActorTail {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[6];
    /* 0x138 */ s32 unk138;
} B2CE0ActorTail;

typedef struct B2CE0NodeHdr {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B2CE0NodeHdr;

typedef struct B2CE0Sub4Ptr {
    /* 0x0 */ B2CE0NodeHdr *unk0;
} B2CE0Sub4Ptr;

typedef struct B2CE0Sub64 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} B2CE0Sub64;

typedef struct B2CE0View90Ptr {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s32 unk4;
} B2CE0View90Ptr;

s32 func_806B0770();
void behaviourSpawnExplosionAndSound(s32, s32, s32);
extern s32 gFrameCounter;
extern s32 gPrimaryPlayerActor;

void func_806B0848(void) {
    s32 sel;

    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        f64 d;
        f64 m = 255.0;

        d = (f64)gCurrentActor->unk4->scaleY / 0.15 * 100.0;
        if (d > m) ((B2CE0ActorTail *)gCurrentActor)->unk130 = m; else ((B2CE0ActorTail *)gCurrentActor)->unk130 = d;
        d = (f64)gCurrentActor->unk4->scaleY / 0.15 * 100.0;
        if (d > m) ((B2CE0ActorTail *)gCurrentActor)->unk131 = m; else ((B2CE0ActorTail *)gCurrentActor)->unk131 = d;
        behaviourSetAnimIds(0x35E, 0x35F, 0x360);
    }
    if ((gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->unk154 != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.unk1FC, 0x367);
        ((B2CE0ActorTail *)gCurrentActor)->unk138 &= 0xFFFF7FFF;
    } else if (gActorGlobalState.unk200 == 4) {
        behaviourSpawnExplosionAndSound(0x365, 0x31, gActorGlobalState.unk1FC);
    } else if (gActorGlobalState.unk200 == 5) {
        behaviourSpawnExplosionAndSound(0x366, 0x31, gActorGlobalState.unk1FC);
    }
    sel = gCurrentActor->unk154;
    if (sel == 4) {
        gCurrentActor->unk154 = 1;
        sel = gCurrentActor->unk154;
    }
    switch (sel) {
        case 0x37:
            gCurrentActor->unkE6 = mathAngleEaseToward(gCurrentActor->unkE6, gCurrentActor->unkEE, 7.0f);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
                case 2:
                    behaviourFadeOutWithinZone(8);
                    break;
                case 3:
                    gCurrentActor->unk154 = 0x40;
                    break;
            }
            break;
        case 0x31:
            if (gCurrentActor->unk155 != 0 || ((B2CE0Sub4Ptr *)gCurrentActor->unk4)->unk0->unk24 == 0.0f) {
                actorSetDefaultState(0x35F);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x27:
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, (gFrameCounter & 1) ? 0x362 : 0x361);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    gCurrentActor->unk132 = ((B2CE0Sub64 *)gCurrentActor->unk4)->unk64 == 0x362 ? 4 : 2;
                    break;
                case 3:
                    gCurrentActor->unk132 = ((B2CE0Sub64 *)gCurrentActor->unk4)->unk64 == 0x362 ? 8 : 1;
                    break;
                case 4:
                    gCurrentActor->unk132 = 1;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x28:
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x363);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    gCurrentActor->unk155++;
                    break;
                case 4:
                    ((B2CE0View90Ptr *)gBehaviourWorkState)->unk4 = gPrimaryPlayerActor;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x11:
            if (func_806B0770() == 0) {
                switch (gCurrentActor->unk155) {
                    case 0:
                        actorSetTargetSpeed(gCurrentActor, 0);
                        actorScriptStart(gCurrentActor, 0x35E);
                        gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
                    case 1:
                        actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                        if (gCurrentActor->unkB8 < 1.0f) {
                            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
                        }
                        break;
                    case 2:
                        behaviourUpdateShadowAlpha();
                        if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                            actorSetDefaultState(0x35F);
                        }
                        break;
                }
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->unk154 = 0x11;
                gCurrentActor->unk155 = 0;
            }
        case 0x23:
            if (actorIsTargetWithinDistance(0x50) != 0 && behaviourIsTargetWithinAngle(0x1770) != 0) {
                gCurrentActor->unk154 = 0x27;
                gCurrentActor->unk155 = 0;
            }
        case 0x10:
            func_806B0770();
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(gCurrentActor->unk154, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        default:
            behaviourUpdateContactAndState(0x2D7);
            break;
    }
    switch (gCurrentActor->unk154) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->unk154, 1);
        default:
            enemyAggroStateUpdate(0x6400, 0x35F, 0x360);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
