#include "common.h"
#include "proto/critter/3340.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/CEAE0.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;




void critterSetDigitFrames(s32 val) {
    s32 digit;
    f32 zero = 0.0f;
    s32 n = val;

    for (digit = 2; digit >= 0; digit--) {
        animSetLoopLimit(gCurrentActor, digit, 1);
        animSetSpeed(gCurrentActor, digit, zero);
        animSetFrameAndSubframe(gCurrentActor, digit, (n % 10) + 1, zero);
        animSetFinished(gCurrentActor, digit, 0);
        n /= 10;
    }
}


extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gPlayerCharacterId;
extern u16 D_807446C0[];
extern s16 D_807446D0[];
extern s8 D_807446E0[];
extern s8 D_807446EE;
extern u16 gLevelCollectibleCounts[];
extern u16 D_807ECD48;
extern u16 D_80029F90[];
extern s8 D_80029F80;
extern s8 D_80029F84;
extern f32 D_8002A1B0;
extern u8 D_8071FE08[];
extern u8 D_80720A7C[];
extern Actor *gCamActor;

f32 sqrtf(f32);

void critterBananaFairyUpdate(void) {
    s32 worldIndex;
    s32 pad;
    s32 requiredCount;
    s16 *timerPtr;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 padF1;
    f32 padF2;
    s8 hasSecretDiscount;
    s8 canSecretUnlock;

    timerPtr = gCurrentActor->customState;
    canSecretUnlock = 0;
    hasSecretDiscount = 0;
    worldIndex = mapGetHubWorldIndex(gCurrentWorldId, 0);
    if (worldIndex >= 8) {
        worldIndex = 7;
    }
    if (gCurrentMap == 0x2A) {
        requiredCount = D_807446C0[worldIndex];
    } else {
        requiredCount = D_807446D0[worldIndex];
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 0x20;
        if (gCurrentMap == 0x2A) {
            actorScriptStart(gCurrentActor, 0x39F);
            gCurrentActor->unk155 = 4;
            if (gLevelCollectibleCounts[worldIndex] < requiredCount) {
                slotQueueUpdate(0, 1, 0);
            }
        } else {
            slotQueueUpdate(9, 1, 0);
            if (flagGet((s16)(worldIndex + 0x1CD), 0) != 0) {
                gCurrentActor->unk155 = 4;
            }
            actorScriptStart(gCurrentActor, 0x39E);
            critterSetDigitFrames(requiredCount);
        }
        *timerPtr = 0;
        D_8002A1B0 = 0.0f;
        D_80029F84 = 0;
        D_80029F80 = 0;
    } else if (D_80029F84 != 0) {
        s8 *pair = &D_807446E0[worldIndex + worldIndex];

        if (gPlayerCharacterId == pair[1]) {
            if (func_806FB418() < requiredCount && worldIndex != 7) {
                requiredCount = pair[0];
                hasSecretDiscount = 1;
            }
            if (worldIndex == 7) {
                if (D_80029F84 == 1) {
                    canSecretUnlock = 1;
                } else {
                    requiredCount = D_807446EE;
                    hasSecretDiscount = 1;
                }
            }
        }
    }
    gCurrentActor->eyeHeight = 0x23;
    if (gCurrentMap != 0x2A) {
        dx = gPrimaryPlayerActor->x - gCurrentActor->x;
        dy = 2.0 * (gPrimaryPlayerActor->y - gCurrentActor->y);
        dz = gPrimaryPlayerActor->z - gCurrentActor->z;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (dist < 300.0 && flagGet(0x17E, 0) == 0) {
            resQueueSetValue(1);
            resQueueAttachActor(gCurrentActor, 0x1D, 0);
            camStartPath(gCurrentActor, 1, 1);
            flagSet(0x17E, 1, 0);
        } else if (canSecretUnlock != 0 && dist < 200.0 && camIsCutsceneActive() == 0 && gPrimaryPlayerActor->state == 0x24 && gPrimaryPlayerActor->unk155 == 2 && dz > -35.0) {
            if (dx > -27.0 && dx < 27.0 && (gPrimaryPlayerActor->yaw < 0x200 || gPrimaryPlayerActor->yaw >= 0xE01)) {
                D_80029F84 = 2;
                sfxPlayOnFreeSlot(0x145, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                camStartShake(gCamActor, 0xA, 0xA);
                gCurrentActor->unk155 = 0xA;
                *timerPtr = 0;
                actorScriptStart(gCurrentActor, 0x3A1);
            }
        }
        switch (gCurrentActor->unk155) {
        case 10:
            *timerPtr += 1;
            if (*timerPtr == 0xA) {
                critterSetDigitFrames(requiredCount);
                sfxPlayOnFreeSlot(0xE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
            }
            if (*timerPtr >= 0x2E) {
                gCurrentActor->unk155 = 0;
                if (func_806FB418() < requiredCount) { // FAKE: empty test; the original emits the call, the slt and the branch
                }
            }
            break;
        case 0:
            if (gCurrentMap == 0xAA && gPlayerCharacterId != 4) {
                D_8002A1B0 = 0.0f;
            }
            if (dist < 70.0 && D_8002A1B0 >= 70.0) {
                s16 var;

                resQueueSetValue(1);
                camStartPath(gCurrentActor, 0x1B, 5);
                if (func_806FB418() < requiredCount) {
                    resQueueAttachActor(gCurrentActor, 0x1D, 1);
                    actorScriptStart(gCurrentActor, 0x3A1);
                    gCurrentActor->unk155 = 1;
                } else {
                    flagSet((s16)(worldIndex + 0x1CD), 1, 0);
                    var = hasSecretDiscount != 0 ? worldIndex + 2 : 2;
                    resQueueAttachActor(gCurrentActor, 0x1D, (u8)var);
                    actorScriptStart(gCurrentActor, 0x3A0);
                    gCurrentActor->unk155 = 2;
                    *timerPtr = 0;
                }
            }
            break;
        case 1:
            if (dist > 110.0) {
                gCurrentActor->unk155 = 0;
            }
            break;
        case 2:
            if (camIsPathPaused() == 0 && *timerPtr >= 0x14) {
                if (*timerPtr == 0x32) {
                    actorScriptStart(gCurrentActor, 0x3A2);
                }
                if (*timerPtr >= 0x3D) {
                    effectSetDepth(0);
                    effectSetDuration(1);
                    effectCreateAtPosition(D_80720A7C, 0.5f, (randomFloat() * 35.0 + gCurrentActor->x) - 15.0, randomFloat() * 35.0 + gCurrentActor->y, (randomFloat() * 35.0 + gCurrentActor->z) - 15.0);
                }
                if (*timerPtr >= 0x51) {
                    gCurrentActor->sub4->scaleX = gCurrentActor->sub4->scaleX * 0.9;
                    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleX;
                    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
                }
                *timerPtr += 1;
            } else {
                if (*timerPtr < 0x14) {
                    *timerPtr += 1;
                }
            }
            break;
        case 3:
            gCurrentActor->sub4->scaleX = 0.0f;
            gCurrentActor->sub4->scaleY = 0.0f;
            gCurrentActor->sub4->scaleZ = 0.0f;
            sfxStopSlotSound(gCurrentActor, 0);
            gCurrentActor->unk155 = 4;
            effectSetDepth(0);
            effectSetDuration(1);
            effectCreateAtPosition(D_8071FE08, 0.5f, gCurrentActor->x, gCurrentActor->y + 7.0f, gCurrentActor->z);
            break;
        case 4:
            gCurrentActor->sub4->scaleX = 0.0f;
            gCurrentActor->sub4->scaleY = 0.0f;
            gCurrentActor->sub4->scaleZ = 0.0f;
            break;
        }
        D_8002A1B0 = dist;
        if (D_807ECD48 != 0) {
            if (D_80029F90[D_80029F80] & D_807ECD48) {
                D_80029F80 += 1;
                if (D_80029F80 == 4) {
                    D_80029F80 = 0;
                    sfxPlayOnFreeSlot(0x1EE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                    D_80029F84 = 1;
                }
            } else {
                D_80029F80 = 0;
            }
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (gCurrentActor->unk155 != 4) {
        gCurrentActor->flags |= 4;
    } else {
        gCurrentActor->flags &= ~4;
        gCurrentActor->unk144 = 1;
    }
}


void critterBananaFairyRewardUpdate(void) {
    f32 dx;
    f32 dz;
    Actor *savedActor;
    s32 inRangeIntro;
    s32 inRangeReward;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        sfxPlayActorSound(gCurrentActor, 0x10F, 0x46, 1, 0, 0x1E, 1.0f, 0);
        gCurrentActor->state = 0;
        if (flagGet(0x179, 0) == 0) {
            gCurrentActor->state = 1;
        } else if (flagGet(0x189, 0) != 0) {
            actorScriptStart(gCurrentActor, 0x2B5);
        } else if (flagCountRange(0x24D, 0x14, 0) == 0x14) {
            actorScriptStart(gCurrentActor, 0x2B5);
            gCurrentActor->state = 3;
        }
    }
    dx = gCurrentActor->x - gPrimaryPlayerActor->x;
    dz = gCurrentActor->z - gPrimaryPlayerActor->z;
    switch (gCurrentActor->state) {
    case 1:
        inRangeIntro = ((dx * dx + dz * dz) < 10000.0f) != 0;
        if (inRangeIntro) {
            flagSet(0x179, 1, 0);
            camStartPath(gPrimaryPlayerActor, 0, 1);
            currentActorClearFlag();
            gCurrentActor->state = 2;
        }
        break;
    case 2:
        savedActor = gCurrentActor;
        if (gCurrentActor->unk155 != 0) {
            gCurrentActor->unk155++;
            if (gCurrentActor->unk155 < 0x4B) {
                gCurrentActor = gPrimaryPlayerActor;
                if (!(gFrameCounter & 3)) {
                    effectSpawnBurst(0);
                }
                gCurrentActor = savedActor;
            } else {
                gCurrentActor = gPrimaryPlayerActor;
                gPrimaryPlayerActor->state = 0x2D;
                gPrimaryPlayerActor->unk155 = 0;
                actorScriptStartByIndex(gPrimaryPlayerActor, 0x42);
                sfxPlayFromActorWithAltitudeCheck(gPrimaryPlayerActor, 0xF2, 0xFF, 0x7F, 0);
                gCurrentActor = savedActor;
                gCurrentActor->unk155 = 0;
                sfxStopSlotSound(gPrimaryPlayerActor, 1);
            }
        } else if (currentActorTestClearFlag() != 0) {
            gCurrentActor->unk155 = 1;
            sfxPlayActorSound(gPrimaryPlayerActor, 0x104, 0x3C, 1, 1, 0xFF, 1.0f, 0);
            slotQueueUpdate(6, 0, 0);
            slotQueueAddValue(6, gActivePlayerState->playerIndex, 0x3E7);
        }
        break;
    case 3:
        inRangeReward = ((dx * dx + dz * dz) < 10000.0f) != 0;
        if (inRangeReward) {
            camStartPath(gCurrentActor, 1, 1);
            currentActorClearFlag();
            gCurrentActor->state = 4;
        }
        break;
    case 4:
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}



typedef struct FlutterState {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} FlutterState;


void critterFlutterFlyUpdate(void) {
    f32 dx;
    f32 dz;
    f32 k;
    f32 pad;
    f32 t;
    f32 pad2;
    s32 near;
    s32 angleTmp;
    FlutterState *d;
    AnimSlot *sub;

    d = gCurrentActor->customState;
    sub = gCurrentActor->sub4->model;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = 0x78;
        if (flagGet(0x189, 0) != 0) {
            if (flagGet(0x23, 1) == 0) {
                gCurrentActor->state = 1;
            } else if (flagGet(0x18A, 0) == 0) {
                if (flagGet(0x24, 1) != 0) {
                    gCurrentActor->state = 0xA;
                } else {
                    gCurrentActor->state = 0x64;
                }
            }
            actorScriptStart(gCurrentActor, 0x43B);
        } else {
            gCurrentActor->state = 0;
        }
        d->unk20 = gCurrentActor->x;
        d->unk24 = gCurrentActor->y;
        d->unk28 = gCurrentActor->z;
        d->unk4 = 0.028571429f;
        d->unk0 = 2.0f;
        d->unk14 = d->unk20;
        d->unk1C = d->unk28;
    }
    dx = gCurrentActor->x - gPrimaryPlayerActor->x;
    dz = gCurrentActor->z - gPrimaryPlayerActor->z;
    if (gCurrentActor->state != 1) {
        gCurrentActor->yaw = gCurrentActor->yaw - (mathAngleSignedDistance(mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z), gCurrentActor->yaw) >> 3);
    }
    gCurrentActor->eyeHeight = 0xF;
    switch (gCurrentActor->state) {
    case 0:
        if (flagGet(0x189, 0) != 0) {
            actorScriptStart(gCurrentActor, 0x43B);
            gCurrentActor->state = 1;
        }
        break;
    case 0x64:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0 && (D_807ECD48 & 0x8000)) {
            camStartPath(gCurrentActor, 4, 1);
            currentActorClearFlag();
            gCurrentActor->state = 0x65;
        }
        if (flagGet(0x24, 1) != 0) {
            gCurrentActor->state = 0xA;
        }
        break;
    case 0x65:
        if (camIsCutsceneActive() == 0) {
            gCurrentActor->state = 0x64;
        }
        break;
    case 1: {
        t = sub->frame / 19.0;
        if (t < d->unk0) {
            d->unk8 = gCurrentActor->x;
            d->unkC = d->unk24;
            d->unk10 = gCurrentActor->z;
            angleTmp = randomFloat() * 4096.0;
            k = randomFloat() * 65.0;
            d->unk14 = (mathCosF((s16)angleTmp) * k) + d->unk20;
            d->unk18 = d->unk24;
            d->unk1C = (mathSinF((s16)angleTmp) * k) + d->unk28;
        }
        d->unk0 = t;
        t = (t - 0.5) * 2.5;
        if (t > 1.0) {
            t = 1.0f;
        }
        if (t < 0.0) {
            t = 0.0f;
        }
        gCurrentActor->x = d->unk8 + (t * (d->unk14 - d->unk8));
        gCurrentActor->z = d->unk10 + (t * (d->unk1C - d->unk10));
        if (gActorGlobalState.bossFightPhase == 4) {
            actorScriptStart(gCurrentActor, 0x43C);
            gCurrentActor->state = 2;
            d->unk0 = 0.0f;
        }
        break;
    }
    case 2:
        d->unk0 = d->unk0 + 1.0;
        if (d->unk0 > 49.0) {
            camStartPath(gCurrentActor, 2, 1);
            currentActorClearFlag();
            d->unk0 = 0.0f;
            gCurrentActor->state = 0x64;
        } else if (d->unk0 < 20.0) {
            k = sqrtf((dx * dx) + (dz * dz));
            if (k > 1.0) {
                k = 3.0 / k;
                gCurrentActor->x = gCurrentActor->x + (dx * k);
                gCurrentActor->z = gCurrentActor->z + (dz * k);
            }
        }
        break;
    case 0xA:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0) {
            gCurrentActor->state = 0xB;
            camStartPath(gCurrentActor, 3, 1);
        }
        break;
    case 0xB:
        break;
    }
    func_8072881C(0, &gCurrentActor->frameCursor);
    if (gCurrentActor->state == 0) {
        gCurrentActor->flags = gCurrentActor->flags & ~4;
    } else {
        gCurrentActor->flags = gCurrentActor->flags | 4;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x23, 0xF, 1, 0x4B, 0x78, gCurrentActor->yaw, 1.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

