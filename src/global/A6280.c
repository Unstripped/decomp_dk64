#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;

void actorUpdateModelMatrix(Actor *, s32);

typedef struct ActorView {
    u8 pad0[0x130];
    u8 unk130;
    u8 unk131;
    u8 pad132[0x178 - 0x132];
    void *unk178;
} ActorView;

typedef struct ActorSubView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0x15F - 0xEE];
    u8 unk15F;
} ActorSubView;

typedef struct PlayerSlot_A6280 {
    u8 unk0;
    u8 pad1[0x20F];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} PlayerSlot_A6280;

extern Actor *gPrimaryPlayerActor;
extern PlayerSlot_A6280 *gPlayerSlots;
extern u8 D_807506C0[];
extern u8 gBossFightPhase;

s16 actorListFindIdByActor(Actor *);
void *spawnNodeActivate(s32, s32);
void animSetStartFrame(Actor *, s32, s32);
s32 animIsPlaying(Actor *, s32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void actorAppendCallback(void *, s32, s32, u8, s32, void *);
void sfxAllocateChannel(s32, f32);

void actorSeekTargetUpdate(void) {
    s16 actorId;
    ActorSubView *targetNode;
    f32 targetAngle;
    f32 dx;
    f32 dz;

    actorId = actorListFindIdByActor(gCurrentActor);
    targetNode = spawnNodeActivate(2, 0);
    if (!(gCurrentActor->flags & 0x10)) {
        ((ActorView *)gCurrentActor)->unk130 = 0x46;
        ((ActorView *)gCurrentActor)->unk131 = 0x32;
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->unk144 = 2;
        gCurrentActor->flags |= 0x80000000;
        gCurrentActor->renderFlags |= 0x28;
        animSetStartFrame(gCurrentActor, 0, 1);
    }
    dx = gPrimaryPlayerActor->x - gCurrentActor->x;
    dz = gPrimaryPlayerActor->z - gCurrentActor->z;
    if (dx * dx + dz * dz < 50000.0f) {
        gCurrentActor->flags |= 0x400;
    } else {
        gCurrentActor->flags &= ~0x400;
    }
    if (targetNode != NULL) {
        if (actorId == D_807506C0[targetNode->unk15F]) {
            dx = gCurrentActor->x - gPrimaryPlayerActor->x;
            dz = gCurrentActor->z - gPrimaryPlayerActor->z;
            if (dx * dx + dz * dz > 900.0f) {
                targetAngle = mathAngleBetweenPointsDeg((s32)gCurrentActor->x, (s32)gCurrentActor->z, (s32)gPrimaryPlayerActor->x, (s32)gPrimaryPlayerActor->z);
                targetNode->unkEC = (s16)(targetAngle - mathAngleBetweenPointsDeg((s32)gPlayerSlots->unk228, (s32)gPlayerSlots->unk230, (s32)gPlayerSlots->unk210, (s32)gPlayerSlots->unk218));
            }
            if (animIsPlaying(gCurrentActor, 0) == 0) {
                animSetSpeed(gCurrentActor, 0, 1.0f);
                animSetLoopLimit(gCurrentActor, 0, -1);
            }
        } else if (animIsPlaying(gCurrentActor, 0) != 0) {
            animSetFinished(gCurrentActor, 0, 1);
            animSetFrameAndSubframe(gCurrentActor, 0, 0, 0);
        }
        if (gBossFightPhase == 4) {
            if (gCurrentActor->interactionType == 4) {
                gCurrentActor->interactionType = 8;
                sfxAllocateChannel(0x43, 1.0f);
                actorAppendCallback(targetNode, (s32)gCurrentActor, 0x02000000, (u8)actorId, 0, NULL);
            } else {
                gCurrentActor->interactionType *= 2;
            }
        }
        if ((gPrimaryPlayerActor->contactFlags & 1) && gPrimaryPlayerActor->attachMode == 0) {
            gCurrentActor->interactionType = 1;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


typedef struct ActorSub178 {
    u8 unk0;
    u8 unk1;
} ActorSub178;

typedef struct ActorParentRamp {
    u8 pad0[0xB8];
    f32 unkB8;
} ActorParentRamp;

typedef struct ActorModelScript {
    u8 pad0[0x64];
    u16 unk64;
} ActorModelScript;

void func_80724CA4(s32, s32);
void actorCopyPoseAndScale(Actor *, void *, f32);
void actorUpdatePulseIntensity(s32);
void actorScriptStart(Actor *, s32);
void scriptSetActorRampTarget(void *, f32, f32);
void billboardSubmit(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void actorUpdateRampTarget(void) {
    ActorSub178 *rampState;
    ActorParentRamp *parentRamp;

    rampState = ((ActorView *)gCurrentActor)->unk178;
    parentRamp = (ActorParentRamp *)gCurrentActor->parentActor;
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 2);
    }
    actorCopyPoseAndScale(gCurrentActor, parentRamp, 0.15f);
    if (gCurrentActor->state != 0) {
        actorUpdatePulseIntensity(1);
        if (rampState->unk1 == 0) {
            gCurrentActor->state = 0;
        }
    }
    if (0.0f != parentRamp->unkB8) {
        if (parentRamp->unkB8 > 50.0f && ((ActorModelScript *)gCurrentActor->sub4)->unk64 != 0x233) {
            actorScriptStart(gCurrentActor, 0x233);
        } else if (50.0f >= parentRamp->unkB8) {
            if (((ActorModelScript *)gCurrentActor->sub4)->unk64 != 0x232) {
                actorScriptStart(gCurrentActor, 0x232);
            }
        }
        scriptSetActorRampTarget(gCurrentActor, parentRamp->unkB8 * 0.01, 4.0f);
    } else {
        if (((ActorModelScript *)gCurrentActor->sub4)->unk64 != 0x234) {
            actorScriptStart(gCurrentActor, 0x234);
        }
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xA, 0xA, 1, 0x12C, 0xC8, 0, 1.0f);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorNoopA6280(void) {
}

extern s32 gFrameCounter;
extern s32 sEffectSparkConfig;
extern ActorGlobalState gActorGlobalState;

s32 flagGet(s16, s32);
void controllerAnimSetStateIfChanged(Actor *, s16, f32, f32);
void func_80728950(s32);
void actorSetUniformScale(Actor *, f32);
void currentActorAnimSetFrame(s32, s32);
void resQueueRemove(Actor *);
void resQueueAttachActor(Actor *, s32, s32);
void camStartPath(Actor *, s32, s32);
void flagSet(s32, s32, s32);
s32 randomNonNegative(void);
void effectDecelDriftFadeUpdate(void);
void func_8071498C(void *);
void func_80714950(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714998(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8072881C(s32, void *);

void func_806A1AC4(void) {
    f32 driftSpeed;
    s16 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags &= ~0x8000;
        func_80728950(0);
        actorSetUniformScale(gCurrentActor, 1.2f);
        gCurrentActor->flags |= 0x400;
        gCurrentActor->drawDistance = 0x3E8;
        if (flagGet(0xFB, 0) != 0) {
            controllerAnimSetStateIfChanged(gCurrentActor, 0x597, 0.0f, 0.0f);
            currentActorAnimSetFrame(0, 0);
            gCurrentActor->state = 3;
        } else {
            controllerAnimSetStateIfChanged(gCurrentActor, 0x598, 0.0f, 0.0f);
            scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= ~4;
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gActorGlobalState.unk254 != 0 && gActorGlobalState.unk258[0] == 1) {
            resQueueRemove(gCurrentActor);
            resQueueAttachActor(gCurrentActor, 0x1F, 1);
            camStartPath(gCurrentActor, 0x12, 1);
            flagSet(0xFB, 1, 0);
            gCurrentActor->state = 1;
        } else if (flagGet(0xFB, 0) == 0 && flagGet(0x21, 2) == 0) {
            if ((gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z) < 19600.0f) {
                resQueueAttachActor(gPrimaryPlayerActor, 0x1F, 0);
                flagSet(0x21, 1, 2);
            }
        }
        break;
    case 1:
        if (gActorGlobalState.unk254 != 0 && gActorGlobalState.unk258[0] == 1) {
            actorScriptStart(gCurrentActor, 0x328);
            gCurrentActor->state = 2;
            gCurrentActor->unk144 = 2;
            gCurrentActor->flags |= 4;
        }
        break;
    case 2:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            if (!(gFrameCounter & 7)) {
                for (i = 0; i < 0xC; i++) {
                    driftSpeed = (((randomNonNegative() >> 15) % 32767) % 171 + 0x96) * 0.01;
                    func_8071498C((void *)effectDecelDriftFadeUpdate);
                    func_80714950(i);
                    func_807149B8(1);
                    func_807149C8(0x8C, 0x8C, 0x8C, 0xFF);
                    func_80714998(5);
                    func_80714CC0(&sEffectSparkConfig, driftSpeed, gCurrentActor->x, gCurrentActor->y + 50.0f, gCurrentActor->z);
                }
            }
            break;
        case 2:
            currentActorAnimSetFrame(0, 0);
            gCurrentActor->unk155[0]++;
            break;
        case 4:
            currentActorAnimSetFrame(0, 2);
            gCurrentActor->unk155[0]++;
            break;
        case 6:
            currentActorAnimSetFrame(0, 0);
            gCurrentActor->state++;
            break;
        }
        break;
    case 3:
        func_8072881C(0, (u8 *)gCurrentActor + 0xEC);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorFinishInRange(void) {
    gCurrentActor->flags |= 0x400;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 camIsCutsceneActive(void);

void actorPlaySoundVariantAndFinish(void) {
    if (camIsCutsceneActive() != 0) {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x640, 0, 8.0f);
    } else {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x63F, 0, 8.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

static void stub_806A1FD0(void) {
}

typedef struct ActorSinkState {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
} ActorSinkState;

extern s32 D_8071FF18;

void actorDespawn(Actor *);
s32 actorListLookupEntry(u16);
s32 actorTableContains(Actor *);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_80717D4C(void);

void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void actorSinkAndDespawn(void) {
    s32 count;
    s32 i;
    s32 node;
    u8 found;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    ActorSinkState *sub;
    Actor *act;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 8;
        sub->unk0 = 0;
        sub->unk4 = 0.0f;
        sub->unk8 = gCurrentActor->y;
        ((ActorView *)gCurrentActor)->unk130 = 0x46;
        ((ActorView *)gCurrentActor)->unk131 = 0x14;
        node = actorListFindIdByActor(gCurrentActor);
        i = actorListLookupEntry(node);
        if (flagGet(i, 0) != 0) {
            actorDespawn(gCurrentActor);
        }
    }
    if (gPrimaryPlayerActor->state == 0x2D && gPrimaryPlayerActor->unk155[0] != 0) {
        found = 0;
        if (gCurrentActor->riderList != NULL) {
            count = gCurrentActor->riderList->count;
            do { i = 0; } while (0);
            if (count != 0) {
                do {
                    act = (Actor *)gCurrentActor->riderList->items[i];
                    if (actorTableContains(act) != 0 && act == gPrimaryPlayerActor) {
                        found = 1;
                    }
                    count--;
                    i++;
                } while (count != 0 && found == 0);
            }
        }
        if (found != 0) {
            node = 1;
            if (sub->unk0 == 0) {
                do {
                    func_80714998(2);
                    func_807149B8(1);
                    func_8071498C(&func_80717D4C);
                    func_80714950(-0x64);
                    func_807149C8(0x64, 0x46, 0x1E, 0xFF);
                    actorGetNodePos(gCurrentActor, node, &nodeX, &nodeY, &nodeZ);
                    func_80714CC0(&D_8071FF18, 2.0f, nodeX, nodeY + 10.0, nodeZ);
                    node++;
                } while (node != 9);
                sub->unk0 = 0xF;
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C1, 0xFF, 0x7F, 1);
            }
        }
    }
    if (sub->unk0 >= 2) {
        sub->unk0--;
    }
    if (sub->unk0 == 2) {
        node = actorListFindIdByActor(gCurrentActor);
        i = actorListLookupEntry(node);
        actorSpawnNodeEntryScaled(0x8C, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z, 0, 1, i, 0);
    }
    if (sub->unk0 < 0xA && sub->unk0 != 0) {
        sub->unk4 = sub->unk4 + 1.0;
        if (sub->unk4 > 20.0) {
            sfxAllocateChannel(0x90, 1.0f);
            actorDespawn(gCurrentActor);
        }
    }
    gCurrentActor->y -= sub->unk4;
    actorUpdateModelMatrix(gCurrentActor, 0);
    gCurrentActor->y = sub->unk8;
}


typedef struct MidpointOrbitActorView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0xFA - 0xEE];
    s16 unkFA;
} MidpointOrbitActorView;

typedef struct MidpointOrbitConfig {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[4];
    f32 unkC;
} MidpointOrbitConfig;

typedef struct MidpointOrbitState {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} MidpointOrbitState;

#define ORBIT_ACTOR ((MidpointOrbitActorView *)gCurrentActor)

void billboardSetFlags(s16);
void func_8067ACB4(Actor *);
f32 mathCosF(s16);
f32 mathSinF(s16);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void actorMidpointOrbitUpdate(void) {
    MidpointOrbitState *sub;
    f32 ratio;
    Actor *p;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x1000;
        actorSetUniformScale(gCurrentActor, ((MidpointOrbitConfig *)gCurrentActor->spawnData)->unkC);
        gCurrentActor->yawSpeed = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
        gCurrentActor->movePitch = (gPrimaryPlayerActor->y + (f32)gPrimaryPlayerActor->eyeHeight - gCurrentActor->y) * 0.5;
        ORBIT_ACTOR->unkEC = sqrtf((gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z)) * 0.5;
        sub->unk0 = gCurrentActor->x + (gPrimaryPlayerActor->x - gCurrentActor->x) * 0.5;
        sub->unk2 = gCurrentActor->y + (gPrimaryPlayerActor->y - gCurrentActor->y) * 0.5;
        sub->unk4 = gCurrentActor->z + (gPrimaryPlayerActor->z - gCurrentActor->z) * 0.5;
        gCurrentActor->unk144 = 0x24;
        ORBIT_ACTOR->unkFA = 0x2328;
        gCurrentActor->splineT = ((MidpointOrbitConfig *)gCurrentActor->spawnData)->unk4;
        {
            f64 v = gCurrentActor->splineT * (ORBIT_ACTOR->unkEC * 0.01);
            gCurrentActor->splineT = (v > 15.0 ? v : 15.0) < 150.0 ? (v > 15.0 ? v : 15.0) : 150.0;
        }
        sub->unk8 = gCurrentActor->splineT;
    }
    func_8067ACB4(gCurrentActor);
    ratio = (sub->unk8 / gCurrentActor->splineT) * -4096.0 + 4096.0;
    sub->unk6 = gCurrentActor->yawSpeed + ratio;
    gCurrentActor->x = mathSinF(sub->unk6) * ORBIT_ACTOR->unkEC + sub->unk0;
    gCurrentActor->z = mathCosF(sub->unk6) * ORBIT_ACTOR->unkEC + sub->unk4;
    gCurrentActor->y = mathCosF(2048.0f + ratio) * gCurrentActor->movePitch + sub->unk2;
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    gCurrentActor->yaw += 0x12C;
    if ((gCurrentActor->yaw & 0x7FF) < 0x12C) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1DF, 0xFF, 0x7F, 0x14, 0x3C, 0.7f, 0);
    }
    if (sub->unk8 != 0) {
        sub->unk8 = sub->unk8 - 1;
        if (sub->unk8 == 0xB) {
            p = gCurrentActor->parentActor;
            if (p != NULL) {
                p->unk155[0]++;
            }
        }
    } else {
        actorDespawn(gCurrentActor);
    }
    billboardSetFlags(1);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x12C, 0xB4, 0, 1.0f);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void mathAngleBetweenPoints3D(s16 *, s16 *, f32, f32, f32, f32, f32, f32);

void actorPlaceModelAtCamera(void) {
    s16 pitchAngle;
    s16 yawAngle;
    f32 mtx1[4][4];
    f32 mtx2[4][4];

    mathAngleBetweenPoints3D(&pitchAngle, &yawAngle, gPlayerSlots->unk210, gPlayerSlots->unk214, gPlayerSlots->unk218, gPlayerSlots->unk228, gPlayerSlots->unk22C, gPlayerSlots->unk230);
    gCurrentActor->yaw = yawAngle;
    gCurrentActor->roll = pitchAngle;
    guRotateF(mtx1, pitchAngle / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, yawAngle / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, gPlayerSlots->unk210, gPlayerSlots->unk214, gPlayerSlots->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -11.0f, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    guTranslateF((f32 (*)[4])((u8 *)gCurrentActor + 0xC), 0.0f, -20.0f, 0.0f);
    actorUpdateModelMatrix(gCurrentActor, 1);
}
