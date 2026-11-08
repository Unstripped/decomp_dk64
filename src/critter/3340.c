#include "common.h"

typedef struct J0b2Sub {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} J0b2Sub;

typedef struct Actor_3340 {
    char pad0[4];
    J0b2Sub *unk4;
    char pad8[0x60 - 0x8];
    s32 unk60;
    s32 unk64;
    char pad68[0x7C - 0x68];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x144 - 0xE8];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x15E - 0x156];
    u8 unk15E;
    char pad15F[0x174 - 0x15F];
    s16 *unk174;
    char pad178[0x1A4 - 0x178];
    u8 playerIndex;
} Actor_3340;

extern Actor_3340 *gCurrentActor;
extern Actor_3340 *gPrimaryPlayerActor;
extern Actor_3340 *gActivePlayerState;
extern s32 gFrameCounter;

void behaviourFrameBegin(void);
void sfxPlayActorSound(Actor_3340 *, s32, s32, s32, s32, s32, f32, s32);
s32 flagGet(s32, s32);
void actorScriptStart(Actor_3340 *, s32);
s32 flagCountRange(s32, s32, s32);
void flagSet(s32, s32, s32);
void camStartPath(Actor_3340 *, s32, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(Actor_3340 *);
void effectSpawnBurst(s32);
void actorScriptStartByIndex(Actor_3340 *, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor_3340 *, s32, s32, s32, s32);
void sfxStopSlotSound(Actor_3340 *, s32);
void slotQueueUpdate(s32, s32, s32);
void slotQueueAddValue(s32, u8, s32);
void actorUpdateModelMatrix(Actor_3340 *, s32);

void animSetLoopLimit(void *, s32, s32);
void animSetSpeed(void *, s32, f32);
void animSetFrameAndSubframe(void *, s32, s16, f32);
void animSetFinished(void *, s32, s32);


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
extern void *gCamActor;

s32 mapGetHubWorldIndex(u8, s32);
s32 camIsCutsceneActive(void);
s32 camIsPathPaused(void);
void camStartShake(void *, s32, s32);
s32 func_806FB418(void);
void resQueueSetValue(s32);
void resQueueAttachActor(void *, s32, s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
f32 randomFloat(void);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
f32 sqrtf(f32);
void critterSetDigitFrames(s32 val);

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

    timerPtr = gCurrentActor->unk174;
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
    if (!(gCurrentActor->unk60 & 0x10)) {
        gCurrentActor->unk64 |= 0x20;
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
    gCurrentActor->unk15E = 0x23;
    if (gCurrentMap != 0x2A) {
        dx = gPrimaryPlayerActor->unk7C - gCurrentActor->unk7C;
        dy = (f32)(2.0 * (f64)(gPrimaryPlayerActor->unk80 - gCurrentActor->unk80));
        dz = gPrimaryPlayerActor->unk84 - gCurrentActor->unk84;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if ((f64)dist < 300.0 && flagGet(0x17E, 0) == 0) {
            resQueueSetValue(1);
            resQueueAttachActor(gCurrentActor, 0x1D, 0);
            camStartPath(gCurrentActor, 1, 1);
            flagSet(0x17E, 1, 0);
        } else if (canSecretUnlock != 0 && (f64)dist < 200.0 && camIsCutsceneActive() == 0 && gPrimaryPlayerActor->unk154 == 0x24 && gPrimaryPlayerActor->unk155 == 2 && (f64)dz > -35.0) {
            if ((f64)dx > -27.0 && (f64)dx < 27.0 && (gPrimaryPlayerActor->unkE6 < 0x200 || gPrimaryPlayerActor->unkE6 >= 0xE01)) {
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
                if (func_806FB418() < requiredCount) { // FAKE: empty guard keeps the call; real body probably missing
                }
            }
            break;
        case 0:
            if (gCurrentMap == 0xAA && gPlayerCharacterId != 4) {
                D_8002A1B0 = 0.0f;
            }
            if ((f64)dist < 70.0 && (f64)D_8002A1B0 >= 70.0) {
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
            if ((f64)dist > 110.0) {
                gCurrentActor->unk155 = 0;
            }
            break;
        case 2:
            if (camIsPathPaused() == 0 && *timerPtr >= 0x14) {
                if (*timerPtr == 0x32) {
                    actorScriptStart(gCurrentActor, 0x3A2);
                }
                if (*timerPtr >= 0x3D) {
                    func_807149B8(0);
                    func_807149FC(1);
                    func_80714CC0(D_80720A7C, 0.5f, (f32)(((f64)randomFloat() * 35.0 + (f64)gCurrentActor->unk7C) - 15.0), (f32)((f64)randomFloat() * 35.0 + (f64)gCurrentActor->unk80), (f32)(((f64)randomFloat() * 35.0 + (f64)gCurrentActor->unk84) - 15.0));
                }
                if (*timerPtr >= 0x51) {
                    gCurrentActor->unk4->unk34 = (f32)((f64)gCurrentActor->unk4->unk34 * 0.9);
                    gCurrentActor->unk4->unk38 = gCurrentActor->unk4->unk34;
                    gCurrentActor->unk4->unk3C = gCurrentActor->unk4->unk34;
                }
                *timerPtr += 1;
            } else {
                if (*timerPtr < 0x14) {
                    *timerPtr += 1;
                }
            }
            break;
        case 3:
            gCurrentActor->unk4->unk34 = 0.0f;
            gCurrentActor->unk4->unk38 = 0.0f;
            gCurrentActor->unk4->unk3C = 0.0f;
            sfxStopSlotSound(gCurrentActor, 0);
            gCurrentActor->unk155 = 4;
            func_807149B8(0);
            func_807149FC(1);
            func_80714CC0(D_8071FE08, 0.5f, gCurrentActor->unk7C, gCurrentActor->unk80 + 7.0f, gCurrentActor->unk84);
            break;
        case 4:
            gCurrentActor->unk4->unk34 = 0.0f;
            gCurrentActor->unk4->unk38 = 0.0f;
            gCurrentActor->unk4->unk3C = 0.0f;
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
        gCurrentActor->unk60 |= 4;
    } else {
        gCurrentActor->unk60 &= ~4;
        gCurrentActor->unk144 = 1;
    }
}


void critterBananaFairyRewardUpdate(void) {
    f32 dx;
    f32 dz;
    Actor_3340 *savedActor;
    s32 inRangeIntro;
    s32 inRangeReward;

    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        sfxPlayActorSound(gCurrentActor, 0x10F, 0x46, 1, 0, 0x1E, 1.0f, 0);
        gCurrentActor->unk154 = 0;
        if (flagGet(0x179, 0) == 0) {
            gCurrentActor->unk154 = 1;
        } else if (flagGet(0x189, 0) != 0) {
            actorScriptStart(gCurrentActor, 0x2B5);
        } else if (flagCountRange(0x24D, 0x14, 0) == 0x14) {
            actorScriptStart(gCurrentActor, 0x2B5);
            gCurrentActor->unk154 = 3;
        }
    }
    dx = gCurrentActor->unk7C - gPrimaryPlayerActor->unk7C;
    dz = gCurrentActor->unk84 - gPrimaryPlayerActor->unk84;
    switch (gCurrentActor->unk154) {
    case 1:
        inRangeIntro = ((dx * dx + dz * dz) < 10000.0f) != 0;
        if (inRangeIntro) {
            flagSet(0x179, 1, 0);
            camStartPath(gPrimaryPlayerActor, 0, 1);
            currentActorClearFlag();
            gCurrentActor->unk154 = 2;
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
                gPrimaryPlayerActor->unk154 = 0x2D;
                gPrimaryPlayerActor->unk155 = 0;
                actorScriptStartByIndex(gPrimaryPlayerActor, 0x42);
                sfxPlayFromActorWithAltitudeCheck(gPrimaryPlayerActor, 0xF2, 0xFF, 0x7F, 0);
                gCurrentActor = savedActor;
                gCurrentActor->unk155 = 0;
                sfxStopSlotSound(gPrimaryPlayerActor, 1);
            }
        } else if (currentActorTestClearFlag(gCurrentActor) != 0) {
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
            gCurrentActor->unk154 = 4;
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

typedef struct FlutterModelView {
    char pad0[4];
    f32 unk4;
} FlutterModelView;

typedef struct FlutterActorView {
    char pad0[4];
    FlutterModelView **unk4;
    char pad8[0x60 - 8];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x154 - 0xE8];
    u8 unk154;
    char pad155[0x15E - 0x155];
    u8 unk15E;
    char pad15F[0x160 - 0x15F];
    u32 unk160;
    char pad164[0x174 - 0x164];
    FlutterState *unk174;
} FlutterActorView;

#define FLUTTER_ACTOR ((FlutterActorView *)gCurrentActor)

extern u8 gBossFightPhase;
f32 mathCosF(s16);
f32 mathSinF(s16);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleSignedDistance(s16, s16);
void billboardSubmit(Actor_3340 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void actorUpdateFloorContactAndTilt(Actor_3340 *, f32);
u8 func_8072881C(u8, u32 *);

void critterFlutterFlyUpdate(void) {
    f32 dx;
    f32 dz;
    f32 k;
    f32 v;
    f32 t;
    f32 w;
    s32 near;
    s32 angleTmp;
    FlutterState *d;
    FlutterModelView *sub;

    d = FLUTTER_ACTOR->unk174;
    sub = *FLUTTER_ACTOR->unk4;
    if (!(FLUTTER_ACTOR->unk60 & 0x10)) {
        FLUTTER_ACTOR->unk154 = 0x78;
        if (flagGet(0x189, 0) != 0) {
            if (flagGet(0x23, 1) == 0) {
                FLUTTER_ACTOR->unk154 = 1;
            } else if (flagGet(0x18A, 0) == 0) {
                if (flagGet(0x24, 1) != 0) {
                    FLUTTER_ACTOR->unk154 = 0xA;
                } else {
                    FLUTTER_ACTOR->unk154 = 0x64;
                }
            }
            actorScriptStart(gCurrentActor, 0x43B);
        } else {
            FLUTTER_ACTOR->unk154 = 0;
        }
        d->unk20 = FLUTTER_ACTOR->unk7C;
        d->unk24 = FLUTTER_ACTOR->unk80;
        d->unk28 = FLUTTER_ACTOR->unk84;
        d->unk4 = 0.028571429f;
        d->unk0 = 2.0f;
        d->unk14 = d->unk20;
        d->unk1C = d->unk28;
    }
    dx = FLUTTER_ACTOR->unk7C - ((FlutterActorView *)gPrimaryPlayerActor)->unk7C;
    dz = FLUTTER_ACTOR->unk84 - ((FlutterActorView *)gPrimaryPlayerActor)->unk84;
    if (FLUTTER_ACTOR->unk154 != 1) {
        FLUTTER_ACTOR->unkE6 = FLUTTER_ACTOR->unkE6 - (mathAngleSignedDistance(mathAngleBetweenPoints2D(((FlutterActorView *)gPrimaryPlayerActor)->unk7C, ((FlutterActorView *)gPrimaryPlayerActor)->unk84, FLUTTER_ACTOR->unk7C, FLUTTER_ACTOR->unk84), FLUTTER_ACTOR->unkE6) >> 3);
    }
    FLUTTER_ACTOR->unk15E = 0xF;
    switch (FLUTTER_ACTOR->unk154) {
    case 0:
        if (flagGet(0x189, 0) != 0) {
            actorScriptStart(gCurrentActor, 0x43B);
            FLUTTER_ACTOR->unk154 = 1;
        }
        break;
    case 0x64:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0 && (D_807ECD48 & 0x8000)) {
            camStartPath(gCurrentActor, 4, 1);
            currentActorClearFlag();
            FLUTTER_ACTOR->unk154 = 0x65;
        }
        if (flagGet(0x24, 1) != 0) {
            FLUTTER_ACTOR->unk154 = 0xA;
        }
        break;
    case 0x65:
        if (camIsCutsceneActive() == 0) {
            FLUTTER_ACTOR->unk154 = 0x64;
        }
        break;
    case 1: {
        t = sub->unk4 / 19.0;
        if (t < d->unk0) {
            d->unk8 = FLUTTER_ACTOR->unk7C;
            d->unkC = d->unk24;
            d->unk10 = FLUTTER_ACTOR->unk84;
            angleTmp = (s32)(randomFloat() * 4096.0);
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
        FLUTTER_ACTOR->unk7C = d->unk8 + (t * (d->unk14 - d->unk8));
        FLUTTER_ACTOR->unk84 = d->unk10 + (t * (d->unk1C - d->unk10));
        if (gBossFightPhase == 4) {
            actorScriptStart(gCurrentActor, 0x43C);
            FLUTTER_ACTOR->unk154 = 2;
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
            FLUTTER_ACTOR->unk154 = 0x64;
        } else if (d->unk0 < 20.0) {
            k = sqrtf((dx * dx) + (dz * dz));
            if (k > 1.0) {
                k = 3.0 / k;
                FLUTTER_ACTOR->unk7C = FLUTTER_ACTOR->unk7C + (dx * k);
                FLUTTER_ACTOR->unk84 = FLUTTER_ACTOR->unk84 + (dz * k);
            }
        }
        break;
    case 0xA:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0) {
            FLUTTER_ACTOR->unk154 = 0xB;
            camStartPath(gCurrentActor, 3, 1);
        }
        break;
    case 0xB:
        break;
    }
    func_8072881C(0, &FLUTTER_ACTOR->unk160);
    if (FLUTTER_ACTOR->unk154 == 0) {
        FLUTTER_ACTOR->unk60 = FLUTTER_ACTOR->unk60 & ~4;
    } else {
        FLUTTER_ACTOR->unk60 = FLUTTER_ACTOR->unk60 | 4;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x23, 0xF, 1, 0x4B, 0x78, FLUTTER_ACTOR->unkE6, 1.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

