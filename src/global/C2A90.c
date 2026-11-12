#include "common.h"
#include "actor.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/1332B0.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8D3E0.h"
#include "proto/global/90D80.h"
#include "proto/global/AA960.h"
#include "proto/global/ACDC0.h"
#include "proto/global/C2A90.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;



u8 func_806BDD90(void) {
    s16 i;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        if (mapHasCollectedSufficientItems() != 0) {
            gCurrentActor->state = 0x40;
        } else {
            gCurrentActor->cullMarginX = 0x3C;
            gCurrentActor->cullMarginY = 0x3C;
            gCurrentActor->drawDistance = 0x3E8;
            func_80724CA4(2, 1);
            gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
            gCurrentActor->accelY /= 1.5;
        }
    }
    actorApplyGravity();
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        if (gActorGlobalState.volumeTriggerQueueOp[i] == 3) {
            return ((u8 *)gActorGlobalState.volumeTriggerQueueId[i])[3];
        }
    }
    return 0;
}



void func_806BDEC8(void) {
    PlayerState *playerState = gPrimaryPlayerActor->customState;

    if (func_806BDD90() == 1) {
        gCurrentActor->state = 0x12;
        gCurrentActor->unk155 = 0;
    }
    if (gCurrentActor->state == 0x12) {
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->speedY = 150.0f;
            actorScriptStart(gCurrentActor, 0x28E);
            camSetTargetCutscene(playerState->camActor, gCurrentActor, 4, 0xE77, 0xFA, 2, 0x32, 0x20, 0x3F, 0x4A, 0.16f);
            gBehaviourWorkState->timer = 0x32;
            gCurrentActor->unk155++;
            break;
        case 2:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                actorScriptStart(gCurrentActor, 0x28F);
                gCurrentActor->unk155++;
                gBehaviourWorkState->timer = 0x78;
            }
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else if (mapHasCollectedSufficientItems() == 0) {
                gCurrentActor->state = 0;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}


extern u8 gCurrentWorldId;
extern u8 gPlayerCharacterId;
extern u16 D_807446C0[];
extern u16 gLevelCollectibleCounts[];
extern KongInventory gPlayerInventoryTable[];


void func_806BE09C(void) {
    PlayerState *playerState;
    s16 angle;
    u8 idx;
    f32 ratio;
    f32 target;
    KongInventory *row;
    s32 sum;
    s32 i;

    playerState = gPrimaryPlayerActor->customState;
    idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
    ratio = (f32)gLevelCollectibleCounts[idx] / (f32)D_807446C0[idx];
    if (func_806BDD90() == 1) {
        gBehaviourWorkState->timer = slotQueueGetValue(0, 0);
        if (gBehaviourWorkState->timer != 0) {
            gCurrentActor->state = 0x12;
            gCurrentActor->unk155 = 0;
            gBehaviourWorkState->unk2E = 0x32;
            actorScriptStart(gCurrentActor, 0x28A);
            camSetTargetCutsceneUnscaled(playerState->camActor, gPrimaryPlayerActor, 4, 0x990, 0x5A, -0x2E, 0x3C, 0xA, 0x20, 0, 0.3f);
            angle = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
            gPrimaryPlayerActor->yaw = angle;
            gPrimaryPlayerActor->moveYaw = gPrimaryPlayerActor->yaw;
        }
    }
    func_80724E48(0);
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    target = gBehaviourWorkState->scale + (0.44 - gBehaviourWorkState->scale) * ratio;
    if (!(gCurrentActor->flags & 0x10)) {
        actorSetUniformScale(gCurrentActor, target);
    }
    switch (gCurrentActor->state) {
    case 0x12:
        actorSetUniformScale(gCurrentActor, (target - gCurrentActor->sub4->scaleX) * 0.1 + gCurrentActor->sub4->scaleX);
        switch (gCurrentActor->unk155) {
        case 0:
            if (gBehaviourWorkState->unk2E != 0) {
                gBehaviourWorkState->unk2E--;
                if (gBehaviourWorkState->unk2E == 0) {
                    camSetTargetCutsceneUnscaled(playerState->camActor, gCurrentActor, 4, 0x305, 0x14A, 3, 0x32, 0x7F, 0x5A, 0, 0.03f);
                }
            }
            if (gBehaviourWorkState->timer != 0) {
                if (!(gFrameCounter & 3)) {
                    row = &gPlayerInventoryTable[gPlayerCharacterId];
                    gBehaviourWorkState->timer--;
                    slotQueueAddValue(0, 0, -1);
                    row->unk26[idx] += 1;
                    sum = 0;
                    for (i = 0; i < 5; i++) sum += gPlayerInventoryTable[i].unk26[idx]; // LAYOUT: body on the for line keeps as1 emitting the unrolled i=1 address add (v0) before the i=0 one (t3)
                    if (sum >= D_807446C0[idx]) {
                        gBehaviourWorkState->timer = 0;
                        slotQueueCancel(0, 0);
                    }
                    effectSetCallback(effectConvergeOnNodeUpdate);
                    effectSetDuration(-1);
                    effectSetDepth(1);
                    effectSetSpeed((s32)gCurrentActor);
                    effectCreateAtActorBone(slotQueueGetSpriteAsset(0), 0.3f, gPrimaryPlayerActor, 4, 0);
                }
            } else if (gBehaviourWorkState->unk2E == 0) {
                gBehaviourWorkState->timer = 0x1E;
                gCurrentActor->unk155 = 1;
            }
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                actorScriptStart(gCurrentActor, 0x28B);
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x27:
        if (gCurrentActor->unk155 == 1) {
            effectSpawnMultiTierRing(4.0f, 1, gCurrentActor->x, gCurrentActor->y + 5.0f, gCurrentActor->z);
            gCurrentActor->state = 0x28;
            gCurrentActor->unk155 = 0;
            gBehaviourWorkState->timer = 0x3C;
        }
        break;
    case 0x28:
        gBehaviourWorkState->timer--;
        if (gBehaviourWorkState->timer == 0) {
            gCurrentActor->state = 0;
            gCurrentActor->unk155 = 0;
            gBehaviourWorkState->unk2E = 0;
        }

        break;
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_807506C0[];

void func_806BE674(u8 spawn) {
    s16 i;

    for (i = 0; i < 0x10U; i++) {
        if (spawn) {
            actorListForceSpawnId(D_807506C0[i]);
        } else {
            actorListForceDespawnId(D_807506C0[i]);
        }
    }
}

extern Gfx D_1000118;

Gfx *func_806BE6F0(Gfx *gdl, Actor *actor) {
    u8 v;
    u8 buf[3];
    s32 n;

    v = actor->yawSpeed / 30;
    if (v) {
        if (v >= 4) {
            n = 3;
        } else {
            n = v;
        }
        _sprintf(buf, "%d", n);
    } else {
        _sprintf(buf, (char *)textTableGetString(0x26, 9, 1));
    }
    if (actor->yawSpeed % 30 == 0) {
        if (v != 0) {
            if (v >= 2) {
                n = 0x75;
            } else {
                n = 0x74;
            }
            sfxPlayOnFreeSlot(n, 0x7FFF, 64.0f, 1.0f, 0, 0x80);
        }
    }
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
    gdl = func_8070068C(gdl);
    gdl = textDrawStringVtx(gdl, 1, (s16)((0x140 - textGetStringWidth(1, buf)) << 1), 0xAA, buf, 1);
    n = actor->yawSpeed-- == 0;
    if (n) {
        actor->unk155++;
    }
    return gdl;
}


extern Actor *gCamActor;
extern s32 gGlobalOverlayFlags;


void func_806BE8BC(void) {
    u8 flagF8Set;
    s16 i;
    s16 j;
    s16 ang;
    s32 sel;

    flagF8Set = flagGet(0xF8, 0);
    behaviourFrameBegin();
    if (gActivePlayerState->stateFlags & 0x100000) {
        gCurrentActor->state = 0x40;
        return;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 1);
        gBehaviourAnimState->flags |= 0x20;
        actorScriptStart(gCurrentActor, 0x306);
        func_80728950(0);
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unk15F = 0;
    }
    switch (gCurrentActor->state) {
        case 0x26:
            actorScriptStart(gCurrentActor, 0x307);
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155 = 0;
            break;
        case 0x1E:
            effectSpawnSmoke(1);
            if (gCurrentActor->alpha < 0xFF) {
                gCurrentActor->alpha += 5;
            }
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0x1F, 3);
                actorClearMovementFlags(gPrimaryPlayerActor);
                func_80726EE0(1);
                gBehaviourAnimState->flags |= 4;
                func_806BE674(1);
                currentActorAnimSetFrame(0, 0);
                if (flagF8Set != 0) {
                    csSendActorMessagePayload(0x17, 0x14);
                    resQueueAttachActor(gCurrentActor, 0x14, 1);
                } else {
                    resQueueAttachActor(gCurrentActor, 0x14, 0);
                }
                actorScriptStart(gCurrentActor, 0x309);
                gCurrentActor->state = 0x1F;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 0x1F:
            sel = gCurrentActor->unk155;
            switch (sel) {
                case 0:
                    if (currentActorTestClearFlag() != 0) {
                        camPausePath();
                        camPausePath();
                        gCurrentActor->unk155++;
                        gCurrentActor->yawSpeed = 0x78;
                    }
                    break;
                case 1:
                    renderCallbacksRegister(func_806BE6F0, gCurrentActor, 3);
                    break;
                case 2:
                    sfxAllocateChannel(0xA9, 1.0f);
                    gGlobalOverlayFlags |= 4;
                    camResumePath();
                    camSetZoomLevel(gCamActor, 3);
                    actorScriptStart(gCurrentActor, 0x302);
                    actorSetTargetSpeed(gCurrentActor, (s32)((flagF8Set ? 1.5 : 1.0) * (u32)gBehaviourExtraState->unkD));
                    gCurrentActor->state = 2;
                    gCurrentActor->unk155 = 0;
                    camSetZoneWeight(1, 0xA);
                    gActivePlayerState->stateFlags2 |= 0x40;
                    break;
            }
            break;
        case 0x27:
            if (gCurrentActor->unk155 == 0) {
                sfxStopChannel(0xA9, 0);
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0xFF;
                func_806BE674(0);
                camStartPath(gCurrentActor, 0xF, 5);
                gCurrentActor->yaw = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
                resQueueAttachActor(gCurrentActor, 0x14, 4);
                gCurrentActor->state = 0x37;
                gCurrentActor->unk155 = 0;
                gCurrentActor->y = gCurrentActor->floorY;
            }
            break;
        case 0x28:
            sel = gCurrentActor->unk155;
            switch (sel) {
                case 0:
                    sfxStopChannel(0xA9, 0);
                    gCurrentActor->flags &= ~0x8000;
                    gCurrentActor->alpha = 0xFF;
                    func_806BE674(0);
                    camStartPath(gCurrentActor, 0x1F, 1);
                    gCurrentActor->yaw = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
                    actorScriptStart(gCurrentActor, 0x308);
                    resQueueSetValue(1);
                    if (flagF8Set != 0) {
                        resQueueAttachActor(gCurrentActor, 0x14, 3);
                    } else {
                        resQueueAttachActor(gCurrentActor, 0x14, 2);
                    }
                    gCurrentActor->unk155 = 1;
                    gCurrentActor->y = gCurrentActor->floorY;
                    break;
                case 1:
                    if (currentActorTestClearFlag() != 0) {
                        if (flagF8Set != 0) {
                            csModelStateSetFirstByte(0x57, 0xA);
                            gBehaviourWorkState->flags |= 0x8000;
                        } else {
                            ang = gCurrentActor->yaw - 0x12C;
                            sfxAllocateChannel(0x2F, 1.0f);
                            for (j = 0; j < 3; j++, ang += 0x12C) {
                                actorSpawnNodeEntryScaled(0x35, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, ang, 0x63, -1, 0);
                            }
                        }
                        flagSet(0xF8, 1, 0);
                        gCurrentActor->state = 0x37;
                        gCurrentActor->unk155 = 0;
                        gCurrentActor->y = gCurrentActor->floorY;
                    }
                    break;
            }
            break;
        case 0x37:
            if (!(gCurrentActor->flags & 0x2000000)) {
                behaviourFadeOutWithinZone(2);
                if (gCurrentActor->unk155 != 0) {
                    gGlobalOverlayFlags &= ~4;
                    gActivePlayerState->padHintTimer = 2;
                    camSetZoneWeight(1, 0);
                    gActivePlayerState->stateFlags2 &= ~0x40;
                    volumeTriggerSetEnabled(0x16, 0);
                    func_80726EE0(2);
                    if (gBehaviourWorkState->flags & 0x8000) {
                        gCurrentActor->state = 0x40;
                    } else {
                        if (gCurrentActor->sub4->animId != 0x308) {
                            hudSpawnTextScreen(2);
                        }
                        csModelStateSetFirstByte(0x1F, 1);
                        gCurrentActor->state = 0x3C;
                    }
                }
            }
            break;
        case 0x13:
            actorScriptStart(gCurrentActor, 0x305);
            gCurrentActor->speedY = 200.0f;
            gCurrentActor->state = 2;
            gCurrentActor->unk155 = 0;
        default:
            if (gCurrentActor->unk15F < 0x10U) {
                renderCallbacksRegister(actorDrawAnimatedEffect, gCurrentActor, 3);
            }
            if (((randomNonNegative() >> 0xF) % 1000) >= 0x3DF && gCurrentActor->sub4->animId == 0x302) {
                if (gFrameCounter & 1) {
                    sel = 0x303;
                } else {
                    sel = 0x304;
                }
                actorScriptStart(gCurrentActor, sel);
            }
            if (gActorGlobalState.unk0 != 0) {
                if (gActorGlobalState.unk1[0] >= D_807506C0[gCurrentActor->unk15F] && gCurrentActor->unk15F < 0x10U) {
                    if (gActorGlobalState.unk1[0] != D_807506C0[gCurrentActor->unk15F]) {
                        actorScriptStart(gCurrentActor, 0x301);
                        gCurrentActor->state = 0x27;
                        gCurrentActor->unk155 = 0;
                    } else {
                        gCurrentActor->unk15F++;
                        if (gCurrentActor->unk15F >= 0x10U) {
                            volumeTriggerSetEnabled(0x16, 1);
                        }
                    }
                }
            }
            for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
                if (gActorGlobalState.volumeTriggerQueueOp[i] == 3) {
                    gCurrentActor->state = 0x28;
                    gCurrentActor->unk155 = 0;
                }
            }
            func_8072881C(0, &gBehaviourWorkState->unk28);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x10, 0.0f);
            patrolPathStep(gCurrentActor->state, 0);
            break;
    }
    if (gCurrentActor->sub4->animId == 0x301 || gCurrentActor->sub4->animId == 0x302) {
        func_80724E48(0);
    }
    behaviourUpdateShadowAlpha();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct LgBF218Sub124 {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
} LgBF218Sub124;

typedef struct LgBF218Node {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} LgBF218Node;

typedef struct LgBF218Sub14 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
} LgBF218Sub14;

typedef struct LgBF218Sub4 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ LgBF218Sub14 *unk14;
} LgBF218Sub4;

typedef struct LgBF218Global {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ LgBF218Sub4 *unk4;
} LgBF218Global;

extern LgBF218Global *D_80755690;

void *memcpy(void *, const void *, u32);

void func_806BF218(void) {
    LgBF218Node *node;
    Actor *other;
    s32 kind;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spawn[3];
    f32 ex;
    f32 ey;
    f32 ez;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->eyeHeight = 0x2D;
    }
    other = gCurrentActor->parentActor;
    if (other == NULL) {
        actorDespawn(gCurrentActor);
    } else {
        kind = other->state;
        if (kind != 0x63) {
            switch (gCurrentActor->state) {
                case 0:
                    if (flagGet(0xFD, 0)) {
                        other = gCurrentActor->parentActor;
                        if (((LgBF218Sub124 *)other->spawnData)->unk8 == 0) {
                            func_8068A2FC(other);
                        } else {
                            actorScriptStart(gCurrentActor, 0x3A8);
                            actorScriptStart(gCurrentActor->parentActor, 0x3AA);
                            gCurrentActor->state = 4;
                            gCurrentActor->unk155 = 0;
                        }
                    } else {
                        other = gCurrentActor->parentActor;
                        if (((LgBF218Sub124 *)other->spawnData)->unk8 == 1) {
                            func_8068A2FC(other);
                        } else if (other->state == 1) {
                            actorScriptStart(gCurrentActor, 0x3A9);
                            actorScriptStart(gCurrentActor->parentActor, 0x3AB);
                            gCurrentActor->state = 1;
                            gCurrentActor->unk155 = 0;
                        } else if (!(gCurrentActor->flags & 0x02000000)) {
                            dx = gCurrentActor->x - gPrimaryPlayerActor->x;
                            dy = gCurrentActor->y - gPrimaryPlayerActor->y;
                            dz = gCurrentActor->z - gPrimaryPlayerActor->z;
                            if ((dx * dx + dy * dy + dz * dz) < 90000.0f) {
                                switch (gCurrentActor->unk155) {
                                    case 0:
                                        actorScriptStart(gCurrentActor, 0x3A8);
                                        actorScriptStart(gCurrentActor->parentActor, 0x3AA);
                                        if (flagGet(0x29, 2) == 0) {
                                            resQueueSetValue(1);
                                            resQueueAttachActor(gCurrentActor, 0x16, 0);
                                            camStartPath(gCurrentActor, 0x19, 1);
                                            flagSet(0x29, 1, 2);
                                        }
                                        gCurrentActor->unk155++;
                                        break;
                                    case 1:
                                        if (other->interactionType == 2) {
                                            if (flagGet(0x2A, 2) == 0) {
                                                resQueueSetValue(1);
                                                resQueueAttachActor(gCurrentActor, 0x16, 1);
                                                camStartPath(gCurrentActor, 0x19, 1);
                                                flagSet(0x2A, 1, 2);
                                            }
                                            gCurrentActor->unk155++;
                                        }
                                        break;
                                }
                            }
                        }
                        if (spawnNodeIsInCooldown(9) && spawnNodeIsInCooldown(0xA) && spawnNodeIsInCooldown(0xB) && spawnNodeIsInCooldown(0xC)) {
                            gCurrentActor->parentActor->interactionType = 2;
                        } else {
                            gCurrentActor->parentActor->interactionType = 4;
                        }
                    }
                    break;
                case 1:
                    if (!(gCurrentActor->flags & 0x02000000)) {
                        if (gCurrentActor->unk155 == 0) {
                            gCurrentActor->unk155++;
                            resQueueAttachActor(gCurrentActor, 0x16, 2);
                            other = gCurrentActor->parentActor;
                            kind = other->state;
                        }
                    }
                    if (kind == 2) {
                        gPrimaryPlayerActor->yaw += 0x800;
                        gCurrentActor->state = 2;
                        gCurrentActor->unk155 = 0;
                        actorScriptStart(gCurrentActor, 0x3A7);
                        actorScriptStart(gCurrentActor->parentActor, 0x3AA);
                    }
                    break;
                case 2:
                    switch (gCurrentActor->unk155) {
                        case 0:
                            ez = gCurrentActor->z - D_80755690->unk4->unk14->unk2C;
                            ex = gCurrentActor->x - D_80755690->unk4->unk14->unk28;
                            ey = gCurrentActor->y - D_80755690->unk4->unk14->unk2A;
                            if ((ez * ez + (ex * ex + ey * ey)) < 22500.0f) {
                                camStartPath(gCurrentActor, 0x17, 1);
                                resQueueAttachActor(gCurrentActor, 0x16, 4);
                                flagSet(0xFC, 1, 0);
                                gCurrentActor->unk155++;
                                actorClearMovementFlags(gPrimaryPlayerActor);
                                zoneEntryGetPosition(1, 5, &gPrimaryPlayerActor->x, &gPrimaryPlayerActor->y, &gPrimaryPlayerActor->z);
                                gPrimaryPlayerActor->yaw = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
                            } else {
                                camStartPath(other, 0x12, 5);
                                resQueueAttachActor(gCurrentActor, 0x16, 3);
                                gCurrentActor->state = 3;
                                gCurrentActor->unk155 = 0;
                                gCurrentActor->flags &= ~0x8000;
                                other = gCurrentActor->parentActor;
                                other->flags &= ~0x8000;
                            }
                            gCurrentActor->parentActor->interactionType = 4;
                            break;
                        case 1:
                            if (!(gCurrentActor->flags & 0x02000000)) {
                                csModelStateSetFirstByte(0x3E, 0xA);
                                gCurrentActor->state = 4;
                                gCurrentActor->unk155 = 0;
                            }
                            break;
                    }
                    break;
                case 3:
                    if (!(gCurrentActor->flags & 0x02000000)) {
                        node = other->customState;
                        switch (gCurrentActor->unk155) {
                            case 0:
                                gCurrentActor->alpha -= 5;
                                if (gCurrentActor->alpha < 0) {
                                    gCurrentActor->unk155++;
                                    gCurrentActor->alpha = 0;
                                }
                                gCurrentActor->parentActor->alpha = gCurrentActor->alpha;
                                break;
                            case 1:
                                camResumePath();
                                func_8068A2FC(gCurrentActor->parentActor);
                                spawn[0] = 1;
                                spawn[1] = 1;
                                spawn[2] = 0;
                                actorListSpawnNodeEntry((s16)gCurrentActor->parentActor->actorType, node->unk4, node->unk8, node->unkC, 0, node->unk10, 0, spawn);
                                break;
                        }
                    }
                    break;
                case 4:
                    break;
            }
        } else {
            actorDespawn(gCurrentActor);
        }
    }
    other = gCurrentActor->parentActor;
    if (other != NULL) {
        actorCopyPoseAndScale(gCurrentActor, other, other->sub4->scaleY);
        memcpy(gCurrentActor->modelMtx, gCurrentActor->parentActor->modelMtx, 0x40);
    }
}
