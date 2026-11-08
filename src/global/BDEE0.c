#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gBossFightPhase;

typedef struct BDEE0Node {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} BDEE0Node;

typedef struct BDEE0Sub1C {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
} BDEE0Sub1C;

typedef struct BDEE0Sub4 {
    /* 0x00 */ BDEE0Node *unk0;
    /* 0x04 */ u8 pad4[0x18];
    /* 0x1C */ BDEE0Sub1C *unk1C;
    /* 0x20 */ u8 pad20[0x44];
    /* 0x64 */ u16 unk64;
} BDEE0Sub4;

// Actor view whose unk178 is a s16 array (func_806B91E0, func_806BA130, func_806BA240).
typedef struct BDEE0ActorAlt {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ BDEE0Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x68];
    /* 0x070 */ s16 unk70;
    /* 0x072 */ u8 pad72[0x4E];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x2C];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x42];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x42];
    /* 0x178 */ s16 *unk178;
} BDEE0ActorAlt;

#define BDEE0AA ((BDEE0ActorAlt *)gCurrentActor)

typedef struct BDEE0View90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0xE];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u8 pad1E[0x10];
    /* 0x2E */ s16 unk2E;
} BDEE0View90;

#define BDEE0S90 ((BDEE0View90 *)gBehaviourWorkState)

typedef struct BDEE0View98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ u16 unk28;
    /* 0x2A */ s16 unk2A;
} BDEE0View98;

#define BDEE0S98 ((BDEE0View98 *)gBehaviourAnimState)

typedef struct BDEE0View9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
} BDEE0View9C;

#define BDEE0S9C ((BDEE0View9C *)gBehaviourExtraState)

extern u8 D_80770629[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void behaviourSetAnimIds(s32, s32, s32);
void func_80724CA4(s32, s32);
void actorClearNodeFlag(void *, s32);
void func_8072D714(s32, s32);
void func_8072DEA8();
void actorSetDefaultState();
void actorSetTargetSpeed(Actor *, s32);
void actorScriptStart(void *, s32);
s32 actorMoveWithinZone(u8, f32, f32, s32, f32);
void func_8072A450();
s32 randomNonNegative(void);
void actorUpdateAnimSpeedFromSpeed();
s32 func_8072E54C();
s32 func_8072DE10(u16);
void func_8072DC7C(s32);
void func_8072B7CC();
void behaviourFrameBegin(void);
void enemyAggroStateUpdate(s32, s32, s32);
void patrolPathStep(u32, s32);
void actorUpdateModelMatrix(Actor *, s32);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxSpawnTableNodes(void *);
void sfxStopSlotSound(Actor *, s32);

void func_806B91E0(void) {
    u16 animFlags = 0;
    s16 *heightTarget = BDEE0AA->unk178;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x321, 0x322, 0x323);
        func_80724CA4(0x11, 1);
        actorClearNodeFlag(gCurrentActor, 4);
        *heightTarget = BDEE0S9C->unkA * 10;
    }
    if ((gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        gBehaviourWorkState->timer = 0x1388;
        func_8072D714(gActorGlobalState.unk1FC, 0x327);
        gCurrentActor->callbackMask &= 0xFFFF7FFF;
    } else if (gActorGlobalState.unk200 == 4) {
        func_8072DEA8(0x325, 0x31, gActorGlobalState.unk1FC);
    } else if (gActorGlobalState.unk200 == 5) {
        func_8072DEA8(0x326, 0x31, gActorGlobalState.unk1FC);
    }
    switch (gCurrentActor->state) {
    case 0x18:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->unk155[0]++;
                gBehaviourWorkState->timer = 0xD;
            }
            BDEE0AA->unk4->unk1C->unk6 += 0x7D0;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                break;
            }
            if (BDEE0S90->unk2E != 0) {
                gCurrentActor->unk155[0] = 0;
                BDEE0S90->unk2E--;
                gBehaviourWorkState->timer = 0xA;
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1BA, 0x96, 0x7F, 0);
                break;
            }
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 0x31:
        if ((gCurrentActor->unk155[0] != 0) || (BDEE0AA->unk4->unk0->unk24 == 0.0f)) {
            actorSetDefaultState(0x322);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x11:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x321);
            gCurrentActor->unk155[0]++;
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->unk155[0]++;
            }
            break;
        case 2:
            func_8072A450();
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x322);
            }
            break;
        }
        break;
    case 0x27:
        BDEE0AA->unk4->unk1C->unk6 -= gCurrentActor->speedXZ * 50.0f;
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155[0]) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x324);
            gCurrentActor->unk155[0] = 1;
            break;
        case 2:
            gCurrentActor->interactionType = 2;
            break;
        case 3:
            gCurrentActor->interactionType = 1;
            break;
        case 4:
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            gCurrentActor->state = 0x11;
            gCurrentActor->unk155[0] = 0;
        }
    case 0x23:
        if (gActorGlobalState.unk200 == 2) {
            if (func_8072DE10(0x2710) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155[0] = 0;
            }
        }
    case 0x10:
        if ((gCurrentActor->state != 0x11) && (gCurrentActor->state != 0x27)) {
            if (gCurrentActor->unk155[0] == 0) {
                *heightTarget = BDEE0S9C->unkA * 2;
                gCurrentActor->unk155[0] = 1;
            }
            if (*heightTarget != 0) {
                (*heightTarget)--;
            } else {
                animFlags = 0x20;
                actorUpdateAnimSpeedFromSpeed(0);
                if (gCurrentActor->speedXZ != 0.0f) {
                    gCurrentActor->speedXZ = gCurrentActor->speedXZ - 1.0f;
                } else {
                    gCurrentActor->state = 0x18;
                    gCurrentActor->unk155[0] = 0;
                    gCurrentActor->unk155[0] = 1;
                    gBehaviourWorkState->timer = 0;
                    BDEE0S90->unk2E = 4;
                }
            }
        }
        BDEE0AA->unk4->unk1C->unk6 -= gCurrentActor->speedXZ * 50.0f;
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, animFlags, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        actorMoveWithinZone(gCurrentActor->state, (f32)gBehaviourWorkState->targetX, (f32)gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        BDEE0AA->unk4->unk1C->unk6 -= gBehaviourWorkState->timer;
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer -= 0x32;
        }
        switch (gCurrentActor->unk155[0]) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->unk155[0]++;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            gCurrentActor->state = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x322);
        break;
    }
    if (gCurrentActor->speedXZ != 0.0f) {
        if (BDEE0AA->unk70 == -1) {
            sfxPlayActorSound(gCurrentActor, 0x10A, 0, 1, 1, 0xFF, 1.0f, 0);
        } else {
            f64 t = ((f64)gCurrentActor->speedXZ * 0.6) / 40.0;
            u8 idx = D_80770629[BDEE0AA->unk70 * 2];

            D_80770B68[idx] = (t < 0.0 ? 0.0 : t) + 0.4;
            D_80770BC0[idx] = 1.0f;
        }
    } else {
        sfxStopSlotSound(gCurrentActor, 1);
    }
    switch (gCurrentActor->state) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->state, 1);
    default:
        enemyAggroStateUpdate(0x57E4, 0x322, 0x323);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806B9CB0(void) {
    behaviourFrameBegin();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void effectSetSpeed(s32);
void effectSetCallback(void *);
void effectSetDepth(s32);
void effectCreateAtPosition(void *, f32, f32, f32, f32);
void effectPuffRiseUpdate(void);
void func_80717D4C(void);
extern void *D_8074E880[];

void actorSpawnRandomParticleNearActor(u8 particleType, s8 yOffset) {
    s32 pad;
    s32 randC;
    s32 randB;
    s32 randA;

    switch (particleType) {
        case 0:
            effectSetCallback(effectPuffRiseUpdate);
            break;
        case 1:
            effectSetSpeed(-0x258);
            effectSetCallback(func_80717D4C);
            break;
    }
    effectSetDepth(1);
    randA = randomNonNegative();
    randB = randomNonNegative();
    randC = randomNonNegative();
    effectCreateAtPosition(D_8074E880[((randA >> 15) % 1000) % 3], (f32)(((randB >> 15) % 256) * 0.001953125 + 0.5), (f32)((randC >> 15) % 6) + (gCurrentActor->x - 3.0f), gCurrentActor->y + (f32)yOffset, (f32)((randomNonNegative() >> 15) % 6) + (gCurrentActor->z - 3.0f));
}

extern u8 D_80750628[];
typedef struct BDEE0DCA0 {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 unk20;
} BDEE0DCA0;

extern BDEE0DCA0 *D_807FDCA0;
s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void mathNudgeCoords(f32, f32, f32 *, f32 *);
f32 mathAtan2(f32, f32);
void matrixMakeRotationX(f32 (*)[4], f32);
void matrixMakeRotationY(f32 (*)[4], f32);

s32 actorBuildNodeAlignedMatrix(u8 nodeLookupIdx, u8 yOffset, f32 x, f32 y, f32 z) {
    f32 spA[4][4];
    f32 spB[4][4];
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u8 node;

    node = D_80750628[nodeLookupIdx];
    if (node) {
        f32 ang;

        actorGetNodePos(*(Actor **)&D_807FDCA0->unk1C, node, &nodeX, &nodeY, &nodeZ);
        mathNudgeCoords(x, z, &nodeX, &nodeZ);
        ang = mathAtan2(nodeX - x, nodeZ - z);
        guTranslateF(spA, 0.0f, -yOffset, 0.0f);
        matrixMakeRotationY(spB, (gCurrentActor->yaw * 0x168) / 4096);
        guMtxCatF(spA, spB, spA);
        matrixMakeRotationX(spB, -90.0f);
        guMtxCatF(spA, spB, spA);
        guAlignF(spB, (ang * 57.295776f) + 180.0f, nodeX - x, nodeY - y, nodeZ - z);
        guMtxCatF(spA, spB, spA);
        guTranslateF(spB, 0.0f, yOffset, 0.0f);
        guMtxCatF(spA, spB, spA);
        guScaleF(spB, gCurrentActor->sub4->scaleX, gCurrentActor->sub4->scaleY, gCurrentActor->sub4->scaleZ);
        guMtxCatF(spA, spB, spA);
        guTranslateF(spB, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        guMtxCatF(spA, spB, (f32 (*)[4])((u8 *)gCurrentActor + 0xC));
        return 1;
    }
    return 0;
}


void func_806BA130(void) {
    gCurrentActor->collisionFlags = 2;
    gCurrentActor->state = 0x23;
    gCurrentActor->unk155[0] = 0;
    BDEE0AA->unk134 = 1;
    gCurrentActor->interactionType = 1;
    BDEE0S90->unk4 = gPrimaryPlayerActor;
    actorScriptStart(gCurrentActor, BDEE0S98->unk2A);
    gCurrentActor->yaw = ((randomNonNegative() >> 15) % 1024) + gPrimaryPlayerActor->yaw - 0x200;
    gCurrentActor->speedXZ = ((randomNonNegative() >> 15) % 100) + 0x32;
    BDEE0AA->unkC0 = ((randomNonNegative() >> 15) % 150) + 0x64;
}

typedef struct BDEE0DC924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BDEE0DC924;

extern BDEE0DC924 *gPlayerSlots;
s32 func_806BA240(u8 action, s16 animId);

typedef struct BDEE0DCA0Tgt {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ u8 unk20;
} BDEE0DCA0Tgt;

#define BDEE0DCA0T ((BDEE0DCA0Tgt *)D_807FDCA0)

extern u8 D_8071FB34[];
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void controllerAnimSetStateIfChanged(void *, s16, f32, f32);
s32 playerStateQueueCallback(s32, void *, s32);
s32 func_8072DCF4(void *, void *, s32);

s32 func_806BA240(u8 action, s16 animId) {
    s16 *p;
    Actor *tgt;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u8 node;
    s32 var;

    p = BDEE0AA->unk178;
    tgt = BDEE0DCA0T->unk1C;
    if (tgt != NULL && tgt->state == 0x23 && BDEE0DCA0T->unk20 < 10) {
        if (gCurrentActor->state != 0x15 && gCurrentActor->state != 0x17) {
            gCurrentActor->collisionFlags = 0x80;
            gCurrentActor->state = 0x15;
            gCurrentActor->unk155[0] = 0;
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->interactionType = 2;
            p[3] = gCurrentActor->x;
            p[4] = gCurrentActor->z;
        }
    }
    if (gCurrentActor->state == 0x15 && (tgt == NULL || tgt->state != 0x23)) {
        func_806BA130();
    }
    if (gCurrentActor->state == 0x15) {
        node = gBehaviourExtraState->unkA;
        if (node == 5 || node == 7) {
            if ((((BDEE0Sub4 *)tgt->sub4)->unk64 == 0x21E || ((BDEE0Sub4 *)tgt->sub4)->unk64 == 0x21F) && ((BDEE0Sub4 *)tgt->sub4)->unk0->unk4 >= 4.0f && ((BDEE0Sub4 *)tgt->sub4)->unk0->unk4 <= 12.0f) {
                gCurrentActor->interactionType = 4;
            } else {
                gCurrentActor->interactionType = 2;
            }
        }
        if (node == 1) {
            gCurrentActor->interactionType = 8;
        }
        if (BDEE0AA->unkF0 != 0) {
            BDEE0AA->unkF0 = BDEE0AA->unkF0 - 1;
        }
        if (tgt->unk155[0] != 0) {
            if (tgt->unk155[0] == 1 && gBossFightPhase == 2 && func_8072DCF4(tgt, gPrimaryPlayerActor, 0x1F40) != 0) {
                if (gPlayerSlots->unk2C0 == 1) {
                    playerStateQueueCallback(0x32, gCurrentActor, 0);
                } else {
                    if (((randomNonNegative() >> 15) % 1000) >= 0x1F5) {
                        var = 0x21F;
                    } else {
                        var = 0x21E;
                    }
                    actorScriptStart(tgt, var);
                    tgt->unk155[0] = 2;
                }
            } else if (gBossFightPhase == 4) {
                BDEE0S90->unk16 = ((BDEE0Sub4 *)gBehaviourTargetActor->sub4)->unk0->unk10;
                gCurrentActor->flags |= 0x20000000;
                if (BDEE0AA->unkF0 == 0) {
                    BDEE0AA->unkF0 = 0x28;
                    effectCreateAtPosition(D_8071FB34, 2.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                    sfxPlayOnFreeSlot(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    actorScriptStart(tgt, 0x220);
                    tgt->unk155[0] = 2;
                    ((BDEE0ActorAlt *)tgt)->unk134 = ((BDEE0ActorAlt *)tgt)->unk134 - 1;
                    if (((BDEE0ActorAlt *)tgt)->unk134 == 0) {
                        tgt->state = 0x37;
                        tgt->unk155[0] = 0;
                    }
                }
            }
        }
        BDEE0DCA0T->unk20 = BDEE0DCA0T->unk20 + 1;
        actorGetNodePos(tgt, node, &nodeX, &nodeY, &nodeZ);
        if (BDEE0S90->unk1A & 0x80) {
            if (!(BDEE0S90->unk1C & 0x80)) {
                BDEE0AA->unkC0 = 300.0f;
            }
            if (BDEE0AA->unkC0 > 0.0f) {
                return 0;
            }
            gCurrentActor->unk144 = 0x24;
            if (animId != 0) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0.0f, 4.0f);
            }
            p[0] = (-p[0]) * 0.1 + p[0];
            p[1] = (-p[1]) * 0.1 + p[1];
            if (node < 0xB) {
                gCurrentActor->yaw = tgt->yaw;
            }
            gCurrentActor->x = nodeX;
            gCurrentActor->z = nodeZ;
            gCurrentActor->y = nodeY;
            if (actorBuildNodeAlignedMatrix(node, action, nodeX, nodeY, nodeZ) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void func_8072B7CC(s32);

void func_806BA76C(f32 speedMultiplier) {
    s16 *p;
    f32 x;
    f32 z;
    u8 sel;
    s32 flags;

    sel = gCurrentActor->state;
    p = BDEE0AA->unk178;
    x = gBehaviourWorkState->targetX;
    z = gBehaviourWorkState->targetZ;
    switch (sel) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            x = gBehaviourTargetActor->x;
            z = gBehaviourTargetActor->z;
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (gCurrentActor->hasArcBounds != 0) {
                flags = 0x10;
            } else {
                flags = 0x810;
            }
            if (!(actorMoveWithinZone(sel, x, z, flags & 0xFFFF, 0.0f) & 1) && gCurrentActor->hasArcBounds == 0) {
                *p = *p + speedMultiplier;
            }
            break;
        case 0x37:
            switch (gCurrentActor->unk155[0]) {
                case 2:
                    func_8072DC7C(10);
                    break;
                case 3:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 4:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        default:
            func_8072B7CC(0);
            break;
    }
}


void func_806BA8C8(void) {
    u8 arg = gCurrentActor->state;
    s32 sel = arg;

    switch (sel) {
        case 0x15:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(arg, 0);
        default:
            enemyAggroStateUpdate(0x2710, 0, 0);
    }
}

typedef struct BDEE0Sub178 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
} BDEE0Sub178;

// Actor view whose unk178 is a BDEE0Sub178 (func_806BA93C, func_806BB874).
typedef struct BDEE0Actor {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xE4];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x22];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ BDEE0Sub178 *unk178;
} BDEE0Actor;
#define BDEE0A ((BDEE0Actor *)gCurrentActor)

void func_806BA76C(f32);
void func_806BA8C8(void);
f32 cosApprox(f32);
f32 mathCosF(s16);
f32 mathSinF(s16);
s32 sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void matrixMakeRotationZ(f32 (*)[4], f32);
s16 mathAngleEaseToward(s16, s16, f32);

void func_806BA93C(sideOffset, rollAmount, pivotZ)
u8 sideOffset;
u8 rollAmount;
u8 pivotZ;
{
    BDEE0Sub178 *s1;
    f32 modelMtx[4][4];
    f32 rotMtx[4][4];
    s16 sgn;
    s32 dir;
    f32 stepDist;
    s16 a;

    s1 = BDEE0A->unk178;
    if (gBehaviourExtraState->unkA && func_806BA240(0x64, 0)) {
        return;
    }
    {
        if ((gActorGlobalState.unk200 == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0x32);
            func_8072D714(gActorGlobalState.unk1FC, 0);
            gBehaviourWorkState->timer = 0xA6;
            s1->unk4 = 0x32;
        }
        func_806BA76C(gCurrentActor->speedXZ * 5.0f);
        switch (gCurrentActor->state) {
        case 4:
            s1->unk0 = s1->unk0 + (-s1->unk0) * 0.3;
            break;
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x12, 0.0f);
            if (BDEE0A->unk155 == 0) {
                gBehaviourWorkState->timer += s1->unk4;
                if (gBehaviourWorkState->timer == 0x196 || gBehaviourWorkState->timer == 0x244 || gBehaviourWorkState->timer == 0x307 || gBehaviourWorkState->timer == 0x3B1 || gBehaviourWorkState->timer == 0x45C || gBehaviourWorkState->timer == 0x508) {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17D, 0x9B, (s16)(s1->unk4 + 0x5A), 0);
                }
                s1->unk4--;
                if (s1->unk4 < 2) {
                    BDEE0A->unk155++;
                    dir = s1->unk4;
                    s1->unk4 = 0;
                    gBehaviourWorkState->scale = 0.0f;
                }
            }
            break;
        }
        if (s1->unk0 >= 0x801) {
            stepDist = sqrtf((1.0 - cosApprox(0.7853982f)) * (2 * (f32)(sideOffset * 2) * (f32)(sideOffset * 2)));
            if (s1->unk2) {
                dir = 1;
            } else {
                dir = -1;
            }
            s1->unk0 -= 0x800;
            s1->unk2 ^= 1;
            a = dir << 8;
            gCurrentActor->x += gCurrentActor->sub4->scaleY * stepDist * mathSinF(gCurrentActor->yaw + a);
            gCurrentActor->z += gCurrentActor->sub4->scaleY * stepDist * mathCosF(gCurrentActor->yaw + a);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1B1, 0xFF, 0x7F, 0xA, 0x3C, 0.3f, 0);
        }
        func_806BA8C8();
        if (s1->unk2) {
            sgn = -1;
        } else {
            sgn = 1;
        }
        guTranslateF(modelMtx, sgn * sideOffset, 0.0f, 0.0f);
        matrixMakeRotationZ(rotMtx, mathSinF(s1->unk0) * (f32)(sgn * rollAmount));
        guMtxCatF(modelMtx, rotMtx, modelMtx);
        if (gCurrentActor->state == 0x37) {
            matrixMakeRotationY(rotMtx, (f32)(sgn * gBehaviourWorkState->timer));
        } else {
            matrixMakeRotationY(rotMtx, mathSinF(s1->unk0 - 0x400) * (f32)(-sgn * 0x2D));
        }
        guMtxCatF(modelMtx, rotMtx, modelMtx);
        if (gCurrentActor->state == 0x37) {
            switch (BDEE0A->unk155) {
            case 1:
                gBehaviourWorkState->timer = mathAngleEaseToward((gBehaviourWorkState->timer << 12) / 0x168, 0, 3.0f) * 0x168 / 4096;
                s1->unk0 = s1->unk0 + (-s1->unk0) * 0.3;
                guTranslateF(rotMtx, 0.0f, 0.0f, (f32)-pivotZ);
                guMtxCatF(modelMtx, rotMtx, modelMtx);
                matrixMakeRotationX(rotMtx, (f32)s1->unk4);
                guMtxCatF(modelMtx, rotMtx, modelMtx);
                guTranslateF(rotMtx, 0.0f, 0.0f, (f32)pivotZ);
                gBehaviourWorkState->scale += 2.0f;
                s1->unk4 = (f32)s1->unk4 + gBehaviourWorkState->scale;
                if (s1->unk4 >= 0x5B) {
                    s1->unk4 = 0x5A;
                    if (gBehaviourWorkState->scale < 3.0f) {
                        BDEE0A->unk155++;
                    } else {
                        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1B1, (u32)(gBehaviourWorkState->scale * 255.0f / 20.0f), (s32)(gBehaviourWorkState->scale + 100.0f), 0, 0x3C, 0.3f, 0);
                        gBehaviourWorkState->scale = -(gBehaviourWorkState->scale * 0.5);
                    }
                }
                break;
            case 2:
                guTranslateF(rotMtx, 0.0f, 0.0f, (f32)-pivotZ);
                guMtxCatF(modelMtx, rotMtx, modelMtx);
                matrixMakeRotationX(rotMtx, 90.0f);
                guMtxCatF(modelMtx, rotMtx, modelMtx);
                guTranslateF(rotMtx, 0.0f, 0.0f, (f32)pivotZ);
                break;
            }
            guMtxCatF(modelMtx, rotMtx, modelMtx);
        }
        guTranslateF(rotMtx, (f32)(-sgn * sideOffset), 0.0f, 0.0f);
        guMtxCatF(modelMtx, rotMtx, BDEE0A->unkC);
        actorUpdateModelMatrix(gCurrentActor, 1);
    }
}

void func_806BB32C(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->tintR = 0xFA;
        gCurrentActor->tintG = 0xFA;
        gCurrentActor->tintB = 0xFA;
    }
    if (gCurrentActor->state == 0x17) {
        actorSpawnRandomParticleNearActor(0, 0);
    }
    if (BDEE0S90->unk2E != 0) {
        BDEE0S90->unk2E--;
        gCurrentActor->hasArcBounds = 0;
        if (BDEE0S90->unk2E == 0 && gBehaviourTargetActor == gPrimaryPlayerActor) {
            gCurrentActor->unk144 = 0x24;
        }
    }
}

void playerSetLargeModeScale(f32);
void actorSetUniformScale(Actor *, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_806BB400(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        playerSetLargeModeScale(0.525f);
        gPrimaryPlayerActor->flags |= 0x400;
        gPrimaryPlayerActor->drawDistance = 0x7D0;
        gCurrentActor->flags &= ~4;
        actorSetUniformScale(gCurrentActor, 1.0f);
        gCurrentActor->unk15F = 0;
        gCurrentActor->yaw = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
        actorScriptStart(gCurrentActor, 0x21B);
        gBehaviourAnimState->unk46 |= 8;
        ((BDEE0View98 *)gBehaviourAnimState)->unk28 = 0x21C;
    }
    switch (gCurrentActor->state) {
        case 4:
            gCurrentActor->state = 0x23;
            gCurrentActor->unk155[0] = 0;
        case 0x23:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                default:
                    gCurrentActor->unk155[0] = 1;
                    goto join;
                join:
                case 1:
                    if (((BDEE0Sub4 *)gCurrentActor->sub4)->unk64 != 0x21C) {
                        actorScriptStart(gCurrentActor, 0x21C);
                    }
                    actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                    break;
                case 2:
                    break;
            }
            break;
        case 0x37:
            playerSetLargeModeScale(0.3f);
            gCurrentActor->state = 0x40;
            break;
    }
    D_807FDCA0->unk20 = 0;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct BDEE0Sub174 {
    /* 0x00 */ struct BDEE0Sub174Hdr *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x26];
    /* 0x2E */ s16 unk2E;
} BDEE0Sub174;

typedef struct BDEE0Sub174Hdr {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} BDEE0Sub174Hdr;

extern Actor *gSpawnedActor;

s32 spawnNodeSpawnById(u8, s16, s16, s16, s32, s32, s32);

s32 actorSpawnJitteredChild(u8 actorType, s16 animId, s16 subId, s32 extraParam) {
    BDEE0Sub174 *v;
    s32 r3;
    s32 r2;
    s32 r1;

    if (gBehaviourWorkState->timer != 0) {
        actorSpawnRandomParticleNearActor(0, 0xA);
        gBehaviourWorkState->timer--;
        return 0;
    }
    r1 = randomNonNegative();
    r2 = randomNonNegative();
    r3 = randomNonNegative();
    if (spawnNodeSpawnById(actorType,
                      (s16)((f32)((r1 >> 15) % 10) + (gCurrentActor->x - 5.0f)),
                      (s16)(gCurrentActor->y + 5.0f),
                      (s16)((f32)((r2 >> 15) % 10) + (gCurrentActor->z - 5.0f)),
                      ((r3 >> 15) % 1024) + gCurrentActor->yaw - 0x200,
                      animId, subId) != 0) {
        gSpawnedActor->state = 0x17;
        gSpawnedActor->unk155[0] = 0;
        v = gSpawnedActor->customState;
        v->unk2E = 0x1E;
        if (extraParam != 0) {
            v->unk0->unk46 &= ~8;
            v->unk4 = extraParam;
        }
        gSpawnedActor->unk144 = 1;
        gSpawnedActor->drawDistance = 0x3E8;
        return 1;
    }
    return 0;
}

void sfxAllocateChannel(s32, f32);

void func_806BB81C(void) {
    sfxPlayActorSound(gCurrentActor, 0x11F, 0, 0, 0, 0xFF, 1.0f, 0);
    sfxAllocateChannel(0x3B, 1.0f);
}

typedef struct BDEE0Tbl {
    u8 b[11];
} BDEE0Tbl;

typedef struct BDEE0DD580 {
    u8 pad0[0x1D8];
    f32 scaleChangeRate;
} BDEE0DD580;

extern BDEE0DD580 *gActivePlayerState;
extern s32 gGlobalCutsceneFlags;
extern s32 gCamActor;
extern BDEE0Tbl D_80750638;

void func_806BB81C();
s32 spawnNodeHasActor(s32);
void csSendActorMessagePayload(s32, s32);
f32 mathCosF(s16);
f32 mathSinF(s16);
void camStartPath(void *, s32, s32);
void camSetTarget(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void camSetTargetFocusActor(s32, void *);
void camReturnToFollow(s32, void *);
void func_80726EE0(s32);
void playerSetSizeMode(void *, s32);
void csModelStateSetFirstByte(s32, s32);
void effectSpawnChildAtNode(s32, s16, s16);
void sfxStopChannel();

void func_806BB874(void) {
    s16 i;
    s16 x;
    s16 y;
    BDEE0Tbl tbl;
    u8 t;
    s32 w;

    x = (randomNonNegative() >> 15) % 100 + 0x64;
    y = (randomNonNegative() >> 15) % 250 + 0xC8;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        BDEE0A->unk130 = 0x3C;
        BDEE0A->unk131 = 0x3C;
        gCurrentActor->drawDistance = 0x3E8;
        gCurrentActor->state = 0;
        BDEE0A->unk155 = 0;
        actorScriptStart(gCurrentActor, 0x3DC);
        gBehaviourWorkState->timer = 0x78;
        gCurrentActor->renderFlags |= 0x20;
    }
    switch (gCurrentActor->state) {
    case 0: {
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 3) {
                gCurrentActor->state++;
            }
        }
        break;
    }
    case 1:
        switch (BDEE0A->unk155) {
        case 0:
            if (gBehaviourWorkState->timer-- < 0x3C) {
                gCurrentActor->flags |= 0x400;
                actorScriptStart(gCurrentActor, 0x3DD);
                BDEE0A->unk155++;
            }
            break;
        case 2:
            effectSpawnChildAtNode(0, (randomNonNegative() >> 15) % 2048 + gCurrentActor->yaw - 0x400, (randomNonNegative() >> 15) % 1024);
            break;
        case 3:
            gGlobalCutsceneFlags |= 1;
            sfxAllocateChannel(0x68, 1.0f);
            gBehaviourWorkState->timer = 0x32;
            func_806BB81C();
            gCurrentActor->state++;
            break;
        }
        break;
    case 2:
        if (actorSpawnJitteredChild(0x2A, x, y, 0) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 3:
        if (spawnNodeHasActor(0x2A) == 0) {
            gBehaviourWorkState->timer = 0xA;
            gCurrentActor->state++;
        }
        break;
    case 4:
        func_806BB81C();
        actorSpawnJitteredChild(0x28, x, y, 0);
        if (actorSpawnJitteredChild(0x29, (s16)(x + 0x28), (s16)(y + 0x50), 0) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 5:
        if (spawnNodeHasActor(0x28) == 0 && spawnNodeHasActor(0x29) == 0) {
            gBehaviourWorkState->timer = 0xA;
            gCurrentActor->state++;
        }
        break;
    case 6:
        func_806BB81C();
        actorSpawnJitteredChild(0x2B, x, y, 0);
        if (actorSpawnJitteredChild(0x2C, (s16)(x + 0x28), (s16)(y + 0x50), 0) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 7:
        if (spawnNodeHasActor(0x2B) == 0 && spawnNodeHasActor(0x2C) == 0) {
            csSendActorMessagePayload(0x11, 1);
            spawnNodeSpawnById(0x2D, mathSinF(gCurrentActor->yaw) * 80.0f + gCurrentActor->x, gCurrentActor->y, mathCosF(gCurrentActor->yaw) * 80.0f + gCurrentActor->z, gCurrentActor->yaw, 0, 0);
            D_807FDCA0->unk1C = (s32)gSpawnedActor;
            camStartPath(gCurrentActor, 0x1F, 1);
            gCurrentActor->state++;
            gBehaviourWorkState->timer = 0x1E;
            BDEE0A->unk155 = 0xA;
        }
        break;
    case 8:
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer--;
        } else {
            tbl = D_80750638;
            t = 0xA - BDEE0A->unk155;
            if (BDEE0A->unk155 == 0xA) {
                func_806BB81C();
            }
            if (BDEE0A->unk155) {
                actorSpawnJitteredChild((u8)(tbl.b[BDEE0A->unk155--] + 0x22), (s16)(t * 8 + 0x64), (s16)(t * 20 + 0xFA), D_807FDCA0->unk1C);
            } else {
                gCurrentActor->flags &= 0xFFFF7FFF;
                gCurrentActor->unk144 = 1;
                gCurrentActor->state++;
                camSetTarget(gCamActor, gCurrentActor, 4, 0x1129, 0x264, 0, 0, 0xAF, 0, 0, 1.0f);
                camSetTargetFocusActor(gCamActor, gPrimaryPlayerActor);
            }
            gBehaviourWorkState->timer = 0xF;
        }
        break;
    case 9: {
        w = gCurrentActor->alpha - 0xA;
        if (w < 0) {
            gCurrentActor->alpha = 0;
        } else {
            gCurrentActor->alpha = w;
        }
        if (spawnNodeHasActor(0x2D) == 0) {
            csSendActorMessagePayload(0x11, 0xFF);
            camReturnToFollow(gCamActor, gPrimaryPlayerActor);
            func_80726EE0(0);
            gGlobalCutsceneFlags &= ~1;
            if (gPlayerSlots->unk2C0 != 1) {
                playerSetSizeMode(gPrimaryPlayerActor, 1);
                gActivePlayerState->scaleChangeRate = 0.05f;
            }
            gCurrentActor->state++;
            sfxStopChannel(0x68, 0);
            csModelStateSetFirstByte(0x7C, 0xA);
            gPrimaryPlayerActor->drawDistance = 0x1F4;
            gPrimaryPlayerActor->flags &= ~0x400;
            gCurrentActor->unk144 = 0x24;
            camStartPath(gCurrentActor, 0x1F, 5);
        }
        break;
    }
    case 10: {
        w = gCurrentActor->alpha + 0xA;
        if (w >= 0x100) {
            gCurrentActor->alpha = 0xFF;
        } else {
            gCurrentActor->alpha = w;
        }
        break;
    }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorPatrolFollowerUpdate();

void func_806BC080(void) {
    func_806BB32C();
    if (gBehaviourExtraState->unkA == 0 || func_806BA240(0, 0x446) == 0) {
        actorPatrolFollowerUpdate(0x2ED, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void func_806BC0E4(void) {
    func_806BB32C();
    if (gBehaviourExtraState->unkA == 0 || func_806BA240(0x32, 0x44E) == 0) {
        actorPatrolFollowerUpdate(0x2EC, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void func_806BC148(void) {
    func_806BB32C();
    if (gBehaviourExtraState->unkA == 0 || func_806BA240(0x14, 0x44A) == 0) {
        actorPatrolFollowerUpdate(0x2EE, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void func_806BA93C();

void func_806BC1AC(void) {
    func_806BB32C();
    func_806BA93C(0x24, 0x14, 0x1E);
}
