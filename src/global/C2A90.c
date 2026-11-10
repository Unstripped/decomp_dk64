#include "common.h"
#include "actor.h"
#define PROTO_SKIP_slotQueueAddValue // FAKE: callee prototype steer
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
void slotQueueAddValue();  // FAKE: callee prototype steer

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern PlayerState *gActivePlayerState;

typedef struct R1C2CB_Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0xBC];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x62];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[4];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
} R1C2CB_Actor;

#define R1C2CBA ((R1C2CB_Actor *)gCurrentActor)


u8 func_806BDD90(void) {
    s16 i;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        if (mapHasCollectedSufficientItems() != 0) {
            gCurrentActor->state = 0x40;
        } else {
            R1C2CBA->unk130 = 0x3C;
            R1C2CBA->unk131 = 0x3C;
            R1C2CBA->unk12A = 0x3E8;
            func_80724CA4(2, 1);
            gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
            R1C2CBA->unkC4 = (f64)R1C2CBA->unkC4 / 1.5;
        }
    }
    actorApplyGravity();
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 3) {
            return ((u8 *)gActorGlobalState.unk278[i])[3];
        }
    }
    return 0;
}

typedef struct R1C2CB_Sub174 {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
} R1C2CB_Sub174;

typedef struct R1C2CB_ActorC0 {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
} R1C2CB_ActorC0;

#define R1C2CBC0 ((R1C2CB_ActorC0 *)gCurrentActor)


void func_806BDEC8(void) {
    R1C2CB_Sub174 *sub = gPrimaryPlayerActor->customState;

    if (func_806BDD90() == 1) {
        gCurrentActor->state = 0x12;
        gCurrentActor->unk155 = 0;
    }
    if (gCurrentActor->state == 0x12) {
        switch (gCurrentActor->unk155) {
        case 0:
            R1C2CBC0->unkC0 = 150.0f;
            actorScriptStart(gCurrentActor, 0x28E);
            camSetTargetCutscene(sub->unk104, gCurrentActor, 4, 0xE77, 0xFA, 2, 0x32, 0x20, 0x3F, 0x4A, 0.16f);
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
    func_8072881C(0, gBehaviourWorkState->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct R1C2CB_S90 {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
} R1C2CB_S90;

typedef struct R1C2CB_ActorEE {
    /* 0x00 */ u8 pad0[0xEE];
    /* 0xEE */ s16 unkEE;
} R1C2CB_ActorEE;

#define R1C2CBS ((R1C2CB_S90 *)gBehaviourWorkState)
#define R1C2CBE ((R1C2CB_ActorEE *)gPrimaryPlayerActor)

extern s32 gFrameCounter;

extern u8 gCurrentWorldId;
extern u8 gPlayerCharacterId;
extern u16 D_807446C0[];
extern u16 gLevelCollectibleCounts[];
extern u8 gPlayerInventoryTable[][0x5E];


void func_806BE09C(void) {
    R1C2CB_Sub174 *sub;
    s16 angle;
    u8 idx;
    f32 ratio;
    f32 target;
    u8 *row;
    s32 sum;
    s32 i;

    sub = gPrimaryPlayerActor->customState;
    idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
    ratio = (f32)gLevelCollectibleCounts[idx] / (f32)D_807446C0[idx];
    if (func_806BDD90() == 1) {
        R1C2CBS->unk2C = slotQueueGetValue(0, 0);
        if (R1C2CBS->unk2C != 0) {
            gCurrentActor->state = 0x12;
            gCurrentActor->unk155 = 0;
            R1C2CBS->unk2E = 0x32;
            actorScriptStart(gCurrentActor, 0x28A);
            camSetTargetCutsceneUnscaled(sub->unk104, gPrimaryPlayerActor, 4, 0x990, 0x5A, -0x2E, 0x3C, 0xA, 0x20, 0, 0.3f);
            angle = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
            gPrimaryPlayerActor->yaw = angle;
            R1C2CBE->unkEE = gPrimaryPlayerActor->yaw;
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
            if (R1C2CBS->unk2E != 0) {
                R1C2CBS->unk2E--;
                if (R1C2CBS->unk2E == 0) {
                    camSetTargetCutsceneUnscaled(sub->unk104, gCurrentActor, 4, 0x305, 0x14A, 3, 0x32, 0x7F, 0x5A, 0, 0.03f);
                }
            }
            if (R1C2CBS->unk2C != 0) {
                if (!(gFrameCounter & 3)) {
                    row = gPlayerInventoryTable[gPlayerCharacterId];
                    R1C2CBS->unk2C--;
                    slotQueueAddValue(0, 0, -1, gPlayerInventoryTable);
                    ((u16 *)(row + 0x26))[idx] += 1;
                    sum = 0;
                    for (i = 0; i < 5; i++) sum += ((u16 *)(gPlayerInventoryTable[i] + 0x26))[idx];
                    if (sum >= D_807446C0[idx]) {
                        R1C2CBS->unk2C = 0;
                        slotQueueCancel(0, 0);
                    }
                    effectSetCallback(effectConvergeOnNodeUpdate);
                    effectSetDuration(-1);
                    effectSetDepth(1);
                    effectSetSpeed(gCurrentActor);
                    effectCreateAtActorBone(slotQueueGetSpriteAsset(0), 0.3f, gPrimaryPlayerActor, 4, 0);
                }
            } else if (R1C2CBS->unk2E == 0) {
                R1C2CBS->unk2C = 0x1E;
                gCurrentActor->unk155 = 1;
            }
            break;
        case 1:
            if (R1C2CBS->unk2C != 0) {
                R1C2CBS->unk2C--;
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
            R1C2CBS->unk2C = 0x3C;
        }
        break;
    case 0x28:
        R1C2CBS->unk2C--;
        if (R1C2CBS->unk2C == 0) {
            gCurrentActor->state = 0;
            gCurrentActor->unk155 = 0;
            R1C2CBS->unk2E = 0;
        }

        break;
    }
    func_8072881C(0, gBehaviourWorkState->unk28);
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
    char buf[3];
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

typedef struct LgBE8Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} LgBE8Sub4;

typedef struct LgBE8A {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgBE8Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x18];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x40];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x2A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
} LgBE8A;

typedef struct LgBE8S90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ u8 unk28[4];
} LgBE8S90;

typedef struct LgBE8G {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[0x47];
    /* 0x23F */ u8 unk23F;
} LgBE8G;

typedef struct LgBE8S9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} LgBE8S9C;

#define LgBA ((LgBE8A *)gCurrentActor)
#define LgBB ((LgBE8A *)gPrimaryPlayerActor)
#define LgBG ((LgBE8G *)gActivePlayerState)
#define LgBS ((LgBE8S90 *)gBehaviourWorkState)
#define LgB9C ((LgBE8S9C *)gBehaviourExtraState)

extern void *gCamActor;
extern s32 gGlobalOverlayFlags;


void func_806BE8BC(void) {
    u8 sp37;
    s16 i;
    s16 j;
    s16 ang;
    s32 sel;

    sp37 = flagGet(0xF8, 0);
    behaviourFrameBegin();
    if (gActivePlayerState->stateFlags & 0x100000) {
        LgBA->unk154 = 0x40;
        return;
    }
    if (!(LgBA->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        gBehaviourAnimState->stateFlags |= 0x20;
        actorScriptStart(gCurrentActor, 0x306);
        func_80728950(0);
        LgBA->unk154 = 0x1E;
        LgBA->unk155 = 0;
        LgBA->unk15F = 0;
    }
    switch (LgBA->unk154) {
        case 0x26:
            actorScriptStart(gCurrentActor, 0x307);
            LgBA->unk154 = 0x27;
            LgBA->unk155 = 0;
            break;
        case 0x1E:
            effectSpawnSmoke(1);
            if (LgBA->unk128 < 0xFF) {
                LgBA->unk128 += 5;
            }
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0x1F, 3);
                actorClearMovementFlags(gPrimaryPlayerActor);
                func_80726EE0(1);
                gBehaviourAnimState->stateFlags |= 4;
                func_806BE674(1);
                currentActorAnimSetFrame(0, 0);
                if (sp37 != 0) {
                    csSendActorMessagePayload(0x17, 0x14);
                    resQueueAttachActor(gCurrentActor, 0x14, 1);
                } else {
                    resQueueAttachActor(gCurrentActor, 0x14, 0);
                }
                actorScriptStart(gCurrentActor, 0x309);
                LgBA->unk154 = 0x1F;
                LgBA->unk155 = 0;
            }
            break;
        case 0x1F:
            sel = LgBA->unk155;
            switch (sel) {
                case 0:
                    if (currentActorTestClearFlag() != 0) {
                        camPausePath();
                        camPausePath();
                        LgBA->unk155++;
                        LgBA->unk168 = 0x78;
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
                    actorSetTargetSpeed(gCurrentActor, (s32)((sp37 ? 1.5 : 1.0) * (u32)LgB9C->unkD));
                    LgBA->unk154 = 2;
                    LgBA->unk155 = 0;
                    camSetZoneWeight(1, 0xA);
                    LgBG->unk1F4 |= 0x40;
                    break;
            }
            break;
        case 0x27:
            if (LgBA->unk155 == 0) {
                sfxStopChannel(0xA9, 0);
                LgBA->unk60 &= ~0x8000;
                LgBA->unk128 = 0xFF;
                func_806BE674(0);
                camStartPath(gCurrentActor, 0xF, 5);
                LgBA->unkE6 = mathAngleBetweenPoints2D(LgBB->unk7C, LgBB->unk84, LgBA->unk7C, LgBA->unk84);
                resQueueAttachActor(gCurrentActor, 0x14, 4);
                LgBA->unk154 = 0x37;
                LgBA->unk155 = 0;
                LgBA->unk80 = LgBA->unkA4;
            }
            break;
        case 0x28:
            sel = LgBA->unk155;
            switch (sel) {
                case 0:
                    sfxStopChannel(0xA9, 0);
                    LgBA->unk60 &= ~0x8000;
                    LgBA->unk128 = 0xFF;
                    func_806BE674(0);
                    camStartPath(gCurrentActor, 0x1F, 1);
                    LgBA->unkE6 = mathAngleBetweenPoints2D(LgBB->unk7C, LgBB->unk84, LgBA->unk7C, LgBA->unk84);
                    actorScriptStart(gCurrentActor, 0x308);
                    resQueueSetValue(1);
                    if (sp37 != 0) {
                        resQueueAttachActor(gCurrentActor, 0x14, 3);
                    } else {
                        resQueueAttachActor(gCurrentActor, 0x14, 2);
                    }
                    LgBA->unk155 = 1;
                    LgBA->unk80 = LgBA->unkA4;
                    break;
                case 1:
                    if (currentActorTestClearFlag() != 0) {
                        if (sp37 != 0) {
                            csModelStateSetFirstByte(0x57, 0xA);
                            LgBS->unk1A |= 0x8000;
                        } else {
                            ang = LgBA->unkE6 - 0x12C;
                            sfxAllocateChannel(0x2F, 1.0f);
                            for (j = 0; j < 3; j++, ang += 0x12C) {
                                actorSpawnNodeEntryScaled(0x35, LgBA->unk7C, LgBA->unk80, LgBA->unk84, ang, 0x63, -1, 0);
                            }
                        }
                        flagSet(0xF8, 1, 0);
                        LgBA->unk154 = 0x37;
                        LgBA->unk155 = 0;
                        LgBA->unk80 = LgBA->unkA4;
                    }
                    break;
            }
            break;
        case 0x37:
            if (!(LgBA->unk60 & 0x2000000)) {
                behaviourFadeOutWithinZone(2);
                if (LgBA->unk155 != 0) {
                    gGlobalOverlayFlags &= ~4;
                    LgBG->unk23F = 2;
                    camSetZoneWeight(1, 0);
                    LgBG->unk1F4 &= ~0x40;
                    volumeTriggerSetEnabled(0x16, 0);
                    func_80726EE0(2);
                    if (LgBS->unk1A & 0x8000) {
                        LgBA->unk154 = 0x40;
                    } else {
                        if (LgBA->unk4->unk64 != 0x308) {
                            hudSpawnTextScreen(2);
                        }
                        csModelStateSetFirstByte(0x1F, 1);
                        LgBA->unk154 = 0x3C;
                    }
                }
            }
            break;
        case 0x13:
            actorScriptStart(gCurrentActor, 0x305);
            LgBA->unkC0 = 200.0f;
            LgBA->unk154 = 2;
            LgBA->unk155 = 0;
        default:
            if (LgBA->unk15F < 0x10U) {
                renderCallbacksRegister(actorDrawAnimatedEffect, gCurrentActor, 3);
            }
            if (((randomNonNegative() >> 0xF) % 1000) >= 0x3DF && LgBA->unk4->unk64 == 0x302) {
                if (gFrameCounter & 1) {
                    sel = 0x303;
                } else {
                    sel = 0x304;
                }
                actorScriptStart(gCurrentActor, sel);
            }
            if (gActorGlobalState.unk0 != 0) {
                if (gActorGlobalState.unk1[0] >= D_807506C0[LgBA->unk15F] && LgBA->unk15F < 0x10U) {
                    if (gActorGlobalState.unk1[0] != D_807506C0[LgBA->unk15F]) {
                        actorScriptStart(gCurrentActor, 0x301);
                        LgBA->unk154 = 0x27;
                        LgBA->unk155 = 0;
                    } else {
                        LgBA->unk15F++;
                        if (LgBA->unk15F >= 0x10U) {
                            volumeTriggerSetEnabled(0x16, 1);
                        }
                    }
                }
            }
            for (i = 0; i < gActorGlobalState.unk254; i++) {
                if (gActorGlobalState.unk258[i] == 3) {
                    LgBA->unk154 = 0x28;
                    LgBA->unk155 = 0;
                }
            }
            func_8072881C(0, LgBS->unk28);
            actorMoveWithinZone(LgBA->unk154, LgBS->unkA, LgBS->unkE, 0x10, 0.0f);
            patrolPathStep(LgBA->unk154, 0);
            break;
    }
    if (LgBA->unk4->unk64 == 0x301 || LgBA->unk4->unk64 == 0x302) {
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

typedef struct LgBF218Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x52];
    /* 0x05A */ s16 unk5A;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x34];
    /* 0x11C */ struct LgBF218Actor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ LgBF218Sub124 *unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[8];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x20];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x15];
    /* 0x174 */ LgBF218Node *unk174;
} LgBF218Actor;

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
#define LA ((LgBF218Actor *)gCurrentActor)
#define LB ((LgBF218Actor *)gPrimaryPlayerActor)

void *memcpy(void *, const void *, u32);

void func_806BF218(void) {
    LgBF218Node *node;
    LgBF218Actor *other;
    s32 kind;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spawn[3];
    f32 ex;
    f32 ey;
    f32 ez;

    if (!(LA->unk60 & 0x10)) {
        LA->unk15E = 0x2D;
    }
    other = LA->unk11C;
    if (other == NULL) {
        actorDespawn(LA);
    } else {
        kind = other->unk154;
        if (kind != 0x63) {
            switch (LA->unk154) {
                case 0:
                    if (flagGet(0xFD, 0)) {
                        other = LA->unk11C;
                        if (other->unk124->unk8 == 0) {
                            func_8068A2FC(other);
                        } else {
                            actorScriptStart(LA, 0x3A8);
                            actorScriptStart(LA->unk11C, 0x3AA);
                            LA->unk154 = 4;
                            LA->unk155 = 0;
                        }
                    } else {
                        other = LA->unk11C;
                        if (other->unk124->unk8 == 1) {
                            func_8068A2FC(other);
                        } else if (other->unk154 == 1) {
                            actorScriptStart(LA, 0x3A9);
                            actorScriptStart(LA->unk11C, 0x3AB);
                            LA->unk154 = 1;
                            LA->unk155 = 0;
                        } else if (!(LA->unk60 & 0x02000000)) {
                            dx = LA->unk7C - LB->unk7C;
                            dy = LA->unk80 - LB->unk80;
                            dz = LA->unk84 - LB->unk84;
                            if ((dx * dx + dy * dy + dz * dz) < 90000.0f) {
                                switch (LA->unk155) {
                                    case 0:
                                        actorScriptStart(LA, 0x3A8);
                                        actorScriptStart(LA->unk11C, 0x3AA);
                                        if (flagGet(0x29, 2) == 0) {
                                            resQueueSetValue(1);
                                            resQueueAttachActor(LA, 0x16, 0);
                                            camStartPath(LA, 0x19, 1);
                                            flagSet(0x29, 1, 2);
                                        }
                                        LA->unk155++;
                                        break;
                                    case 1:
                                        if (other->unk132 == 2) {
                                            if (flagGet(0x2A, 2) == 0) {
                                                resQueueSetValue(1);
                                                resQueueAttachActor(LA, 0x16, 1);
                                                camStartPath(LA, 0x19, 1);
                                                flagSet(0x2A, 1, 2);
                                            }
                                            LA->unk155++;
                                        }
                                        break;
                                }
                            }
                        }
                        if (spawnNodeIsInCooldown(9) && spawnNodeIsInCooldown(0xA) && spawnNodeIsInCooldown(0xB) && spawnNodeIsInCooldown(0xC)) {
                            LA->unk11C->unk132 = 2;
                        } else {
                            LA->unk11C->unk132 = 4;
                        }
                    }
                    break;
                case 1:
                    if (!(LA->unk60 & 0x02000000)) {
                        if (LA->unk155 == 0) {
                            LA->unk155++;
                            resQueueAttachActor(LA, 0x16, 2);
                            other = LA->unk11C;
                            kind = other->unk154;
                        }
                    }
                    if (kind == 2) {
                        LB->unkE6 += 0x800;
                        LA->unk154 = 2;
                        LA->unk155 = 0;
                        actorScriptStart(LA, 0x3A7);
                        actorScriptStart(LA->unk11C, 0x3AA);
                    }
                    break;
                case 2:
                    switch (LA->unk155) {
                        case 0:
                            ez = LA->unk84 - D_80755690->unk4->unk14->unk2C;
                            ex = LA->unk7C - D_80755690->unk4->unk14->unk28;
                            ey = LA->unk80 - D_80755690->unk4->unk14->unk2A;
                            if ((ez * ez + (ex * ex + ey * ey)) < 22500.0f) {
                                camStartPath(LA, 0x17, 1);
                                resQueueAttachActor(LA, 0x16, 4);
                                flagSet(0xFC, 1, 0);
                                LA->unk155++;
                                actorClearMovementFlags(LB);
                                zoneEntryGetPosition(1, 5, &LB->unk7C, &LB->unk80, &LB->unk84);
                                LB->unkE6 = mathAngleBetweenPoints2D(LA->unk7C, LA->unk84, LB->unk7C, LB->unk84);
                            } else {
                                camStartPath(other, 0x12, 5);
                                resQueueAttachActor(LA, 0x16, 3);
                                LA->unk154 = 3;
                                LA->unk155 = 0;
                                LA->unk60 &= ~0x8000;
                                other = LA->unk11C;
                                other->unk60 &= ~0x8000;
                            }
                            LA->unk11C->unk132 = 4;
                            break;
                        case 1:
                            if (!(LA->unk60 & 0x02000000)) {
                                csModelStateSetFirstByte(0x3E, 0xA);
                                LA->unk154 = 4;
                                LA->unk155 = 0;
                            }
                            break;
                    }
                    break;
                case 3:
                    if (!(LA->unk60 & 0x02000000)) {
                        node = other->unk174;
                        switch (LA->unk155) {
                            case 0:
                                LA->unk128 -= 5;
                                if (LA->unk128 < 0) {
                                    LA->unk155++;
                                    LA->unk128 = 0;
                                }
                                LA->unk11C->unk128 = LA->unk128;
                                break;
                            case 1:
                                camResumePath();
                                func_8068A2FC(LA->unk11C);
                                spawn[0] = 1;
                                spawn[1] = 1;
                                spawn[2] = 0;
                                actorListSpawnNodeEntry(LA->unk11C->unk5A, node->unk4, node->unk8, node->unkC, 0, node->unk10, 0, spawn);
                                break;
                        }
                    }
                    break;
                case 4:
                    break;
            }
        } else {
            actorDespawn(LA);
        }
    }
    other = LA->unk11C;
    if (other != NULL) {
        actorCopyPoseAndScale(LA, other, other->unk4->scaleY);
        memcpy((u8 *)LA + 0xC, (u8 *)LA->unk11C + 0xC, 0x40);
    }
}
