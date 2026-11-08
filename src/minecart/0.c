#include "common.h"

typedef struct Struct_807FBB40_11C {
    char pad0[0x154];
    u8 unk154;
} Struct_807FBB40_11C;

struct MinecartCart;

typedef struct Struct_807FBB40_4 {
    char pad0[0x38];
    f32 unk38;
    char pad3C[0x64 - 0x3C];
    u16 unk64;
} Struct_807FBB40_4;

typedef struct Struct_807FBB40 {
    char pad0[0x4];
    Struct_807FBB40_4 *unk4;
    char pad8[4];
    float unkC[4][4];
    char pad4C[0x60 - 0x4C];
    s32 unk60;
    char pad64[10];
    s16 unk6E;
    char pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xA4 - 0x88];
    f32 unkA4;
    char padA8[0xB8 - 0xA8];
    f32 unkB8;
    char padBC[0xC0 - 0xBC];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    char padCC[0xE4 - 0xCC];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0xF0 - 0xEA];
    s16 unkF0;
    char padF2[0x11C - 0xF2];
    Struct_807FBB40_11C *unk11C;
    char pad120[0x144 - 0x120];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x168 - 0x156];
    s16 unk168;
    char pad16A[0x174 - 0x16A];
    struct MinecartCart *unk174;
} Struct_807FBB40;

typedef struct Struct_807FC924_4_174 {
    char pad0[0x104];
    void *unk104;
    char pad108[0x1F0 - 0x108];
    s32 stateFlags;
} Struct_807FC924_4_174;

typedef struct Struct_807FC924_4 {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x174 - 0x88];
    Struct_807FC924_4_174 *unk174;
} Struct_807FC924_4;

typedef struct Struct_807FC924 {
    char pad0[0x4];
    Struct_807FC924_4 *unk4;
    char pad8[0x214 - 0x8];
    f32 unk214;
} Struct_807FC924;
typedef struct MinecartTrackPoint {
    f32 x;
    f32 y;
    f32 z;
} MinecartTrackPoint;

typedef struct MinecartCart {
    s16 unk0;
    s16 unk2;
    Struct_807FC924_4 *unk4;
    u8 unk8;
    char pad9[3];
    MinecartTrackPoint *unkC;
    s16 unk10;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 *unk30;
    u8 *unk34;
    char pad38[1];
    u8 unk39;
    char pad3A[4];
    u8 unk3E;
    u8 unk3F;
    u8 unk40;
    u8 unk41;
    u8 unk42;
} MinecartCart;

extern Struct_807FC924 *gPlayerSlots;
extern s16 D_80750AC4;
extern s32 gCurrentMap;

void slotQueueUpdate(s32, s32, s32);
void actorUpdateModelMatrix(void *, s32);
void minecartFollowTrack(struct MinecartCart *cart, s16 angleDeltaInput, u8 maxTiltLimit);
void camSetTargetScaled(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 camIsCutsceneActive(void);
void actorSpawnNodeEffectFacingCamera(s32, s32);
void commandQueuePush(void *, s16, s16, s16, s32, s32, s32, s32, s32);
s32 actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void lightSetDistanceThreshold(s32);
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

typedef struct Struct_807FBB4C {
    char pad0[0x12C];
    s16 unk12C;
    char pad12E[0x174 - 0x12E];
    Struct_807FC924_4_174 *unk174;
} Struct_807FBB4C;

extern Struct_807FBB40 *gCurrentActor;
extern Struct_807FBB4C *D_807FBB4C;

void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
s32 textTableGetString();
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 playerStateQueueCallback();
void camStartPath();

void minecartTriggerLoss(u8 useCutsceneCam, u8 textIndex) {
    sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    gCurrentActor->unk11C->unk154 = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    gCurrentActor->unk154++;
    if (useCutsceneCam != 0) {
        camStartPath(D_807FBB4C, 5, 5);
    }
}

void minecartTriggerWin(u8 useCutsceneCam, u8 textIndex) {
    s32 temp = textTableGetString(0x1A, textIndex, 1);
    textSpawnMarkerChecked(0x81, 0, 0x78, temp, 0, 0x28, 8, 8);
    gCurrentActor->unk11C->unk154 = 0;
    sfxAllocateChannel(0x2A, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    gCurrentActor->unk154++;
    if (useCutsceneCam != 0) {
        camStartPath(D_807FBB4C, 5, 5);
    }
}

extern s32 D_80028C30;
extern s32 D_8071A440;
extern s32 D_8072006C;

s32 randomLcgNext();
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_80714950(void *);
void func_8071498C(void *);
s32 func_80714C08(void *, s32, void *, s32, s32);

void minecartSpawnWheelEffect(MinecartCart *cart, u8 side, u8 probabilityThreshold) {
    if ((u32)(u8)randomLcgNext() >= (u32)probabilityThreshold) {
        if (cart->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8A, 0x96, 0x7F, 0x32);
            func_80714950(gCurrentActor);
            func_8071498C(&D_8071A440);
            D_80028C30 = func_80714C08(&D_8072006C, 0x3ECCCCCD, gCurrentActor, side + 7, 2);
        }
    }
}

void minecartStepSpeedToTarget(MinecartCart *cart) {
    u32 targetSpeedInt = cart->unk3E;
    f32 nextSpeed;
    f32 targetSpeed = targetSpeedInt;

    if (targetSpeed != gCurrentActor->unkB8) {
        if (gCurrentActor->unkB8 < targetSpeed) {
            nextSpeed = gCurrentActor->unkB8 + 8.0f;
            if (targetSpeed < nextSpeed) {
                gCurrentActor->unkB8 = targetSpeed;
                return;
            }
            gCurrentActor->unkB8 = nextSpeed;
            return;
        }
        if (targetSpeed < gCurrentActor->unkB8) {
            nextSpeed = gCurrentActor->unkB8 - 8.0f;
            if (nextSpeed < targetSpeed) {
                gCurrentActor->unkB8 = targetSpeed;
                return;
            }
            gCurrentActor->unkB8 = nextSpeed;
        }
    }
}

void minecartPlayerCartUpdate(u8 initTrackSegment, s32 trackTable, s16 maxAngleDelta, u8 maxTiltLimit) {
    s32 pad94;
    Struct_807FC924_4_174 *playerState;
    MinecartCart *s1;
    s32 flags;
    s32 pad0, pad1, pad2, pad3, pad4, pad5, pad6, pad7, pad8;
    f32 nodePos[3];

    s1 = gCurrentActor->unk174;
    playerState = gPlayerSlots->unk4->unk174;
    flags = gCurrentActor->unk60;
    if (!(flags & 0x10)) {
        gCurrentActor->unk60 = flags | 0x1400;
        if (gCurrentMap == 6 || gCurrentMap == 0x37 || gCurrentMap == 0x6A) {
            slotQueueUpdate(0xB, 1, 0);
            D_80750AC4 = 0;
        }
    }
    if (s1->unk4 == NULL) {
        s1->unk4 = gPlayerSlots->unk4;
        s1->unk8 = 0;
    }
    switch (gCurrentActor->unk154) {
    case 0:
        if ((s1->unk4->unk7C - gCurrentActor->unk7C) * (s1->unk4->unk7C - gCurrentActor->unk7C) +
            (s1->unk4->unk80 - gCurrentActor->unk80) * (s1->unk4->unk80 - gCurrentActor->unk80) +
            (s1->unk4->unk84 - gCurrentActor->unk84) * (s1->unk4->unk84 - gCurrentActor->unk84) < 400.0f) {
            s1->unk34 = (u8 *)trackTable;
            s1->unk10 = initTrackSegment;
            s1->unk30 = (u8 *)trackTable;
            playerStateQueueCallback(0x45, gCurrentActor, s1->unk8);
            gCurrentActor->unk154++;
        } else {
            actorUpdateModelMatrix(gCurrentActor, 0);
            break;
        }
    case 1:
        minecartFollowTrack(s1, maxAngleDelta, maxTiltLimit);
        camSetTargetScaled(playerState->unk104, gCurrentActor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
        gCurrentActor->unk154++;
        break;

    case 2:
        actorGetNodePos(gCurrentActor, 9, &s1->unk4->unk7C, &s1->unk4->unk80, &s1->unk4->unk84);
        gCurrentActor->unk154++;
        if (gCurrentActor->unk168 == 0 && gCurrentMap != 6) {
            gCurrentActor->unk168 = 2;
        }
        /* fallthrough */
    case 3:
    case 5:
        if (gCurrentActor->unk168 == 0 && camIsCutsceneActive() != 0) {
            gCurrentActor->unk168 = 1;
        }
        if (gCurrentActor->unk168 == 1 && gCurrentActor->unk155 == 0) {
            if (camIsCutsceneActive() != 0) {
                playerState->stateFlags |= 8;
            } else {
                camSetTargetScaled(playerState->unk104, gCurrentActor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                playerState->stateFlags &= ~8;
                s1->unk3E = 0x3C;
                gCurrentActor->unk155++;
            }
        }
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        minecartStepSpeedToTarget(s1);
        minecartFollowTrack(s1, maxAngleDelta, maxTiltLimit);
        actorGetNodePos(gCurrentActor, 5, &nodePos[0], &nodePos[1], &nodePos[2]);
        commandQueuePush(gCurrentActor, (s16)(s32)nodePos[0], (s16)(s32)nodePos[1], (s16)(s32)nodePos[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        commandQueuePush(s1->unk4, (s16)(s32)nodePos[0], (s16)(s32)nodePos[1], (s16)(s32)nodePos[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        break;

    default:
        break;
    }
}

typedef struct Struct_807FD580 {
    char pad0[0x1F0];
    s32 stateFlags;
    char pad1F4[0x1FC - 0x1F4];
    u8 unk1FC;
} Struct_807FD580;
extern Struct_807FD580 *gActivePlayerState;


void minecartUpdateHeadlight(void) {
    f32 lightAim[3];
    f32 lightPos[3];

    if (gActivePlayerState->stateFlags & 0x10000002) {
        actorGetNodePos(gCurrentActor, 2, &lightPos[0], &lightPos[1], &lightPos[2]);
        actorGetNodePos(gCurrentActor, 1, &lightAim[0], &lightAim[1], &lightAim[2]);
    } else {
        actorGetNodePos(gCurrentActor, 1, &lightPos[0], &lightPos[1], &lightPos[2]);
        actorGetNodePos(gCurrentActor, 2, &lightAim[0], &lightAim[1], &lightAim[2]);
    }
    lightSetDistanceThreshold(0xC8);
    lightSetFovAngles(20.0f, 40.0f);
    lightAdd(lightPos[0], lightPos[1], lightPos[2], lightAim[0], lightAim[1], lightAim[2], 0.0f, 1, 0xFF, 0xFF, 0xFF);
}

extern s32 D_80028C34;
extern s32 D_80028C3C;

void minecartUpdateHeadlightAndSpeed(void) {
    MinecartCart *cart = gCurrentActor->unk174;

    if (!(gCurrentActor->unk60 & 0x10)) {
        cart->unk24 = 0.1f;
        cart->unk28 = 5.0f;
    }
    minecartPlayerCartUpdate(1, (s32)((gCurrentMap == 6) ? &D_80028C34 : &D_80028C3C), 0x7FFF, 0x23);
    minecartUpdateHeadlight();
}

extern s16 D_807502D0;
extern f32 D_807502F8;
extern s16 D_80750338;
extern s32 D_80028C40;

void actorApplyGravity(void);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);

void minecartUpdatePhysics(void) {
    s32 pad0;
    s32 pad1;
    s16 prevVertPos;
    MinecartCart *cart;

    f32 scaleFactor = (f32)((f64)gCurrentActor->unk4->unk38 * 0.16666666675);
    cart = gCurrentActor->unk174;
    prevVertPos = cart->unk0;
    if (!(gCurrentActor->unk60 & 0x10)) {
        gCurrentActor->unkC8 = (f32) D_807502D0;
        cart->unk24 = 3.0f;
        cart->unk28 = 12.0f;
    }
    if (cart->unk10 == 0x90) {
        gCurrentActor->unkB8 = 130.0f;
        gCurrentActor->unkC4 = (f32) ((f64) D_807502F8 * 0.6);
        if (cart->unk0 == 0) {
            gCurrentActor->unkC0 = (f32) ((f64) D_80750338 * 1.6);
        }
    } else {
        gCurrentActor->unkC4 = (f32) D_807502F8;
    }
    cart->unk0 = (s16)((f32)cart->unk0 + gCurrentActor->unkC0 * scaleFactor);
    actorApplyGravity();
    if (cart->unk0 < 0) {
        cart->unk0 = 0;
        if (prevVertPos != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    minecartPlayerCartUpdate(3, (s32)&D_80028C40, cart->unk2, 0x19);
    if (D_807FBB4C->unk12C != 0x12 && D_807FBB4C->unk12C != 0xB) {
        minecartUpdateHeadlight();
    }
    if (gCurrentActor->unk154 != 0) {
        actorGetNodePos(gCurrentActor, 9, &cart->unk4->unk7C, &cart->unk4->unk80, &cart->unk4->unk84);
    }
}


typedef struct MinecartPlayerActorFlags {
    char pad0[0x6A];
    u16 unk6A;
} MinecartPlayerActorFlags;

extern s32 D_807F5FD0;
extern MinecartTrackPoint **D_807F5FD4;
extern s32 D_80028C48;
extern s32 D_80028C50;
void actorSetUniformScale(void *, f32);

void minecartReverseTrackBehaviour(void) {
    s32 padA;
    f32 scaleFactor;
    s16 prevVertPos;
    s16 i;
    s16 j;
    s16 n;
    MinecartTrackPoint tmp;
    MinecartCart *s0;

    scaleFactor = (f32)((f64)gCurrentActor->unk4->unk38 * 0.16666666675);
    s0 = gCurrentActor->unk174;
    prevVertPos = s0->unk0;
    if (!(gCurrentActor->unk60 & 0x10)) {
        actorSetUniformScale(D_807FBB4C, 0.12f);
        gCurrentActor->unkC4 = D_807502F8;
        gCurrentActor->unkC8 = D_807502D0;
        s0->unk24 = 0.1f;
        s0->unk28 = 5.0f;
    }
    s0->unk0 = (s16)((f32)s0->unk0 + gCurrentActor->unkC0 * scaleFactor);
    actorApplyGravity();
    if (s0->unk0 < 0) {
        s0->unk0 = 0;
        if (prevVertPos != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    if (((MinecartPlayerActorFlags *)D_807FBB4C)->unk6A & 0x100) {
        ((MinecartPlayerActorFlags *)D_807FBB4C)->unk6A &= ~0x100;
        gCurrentActor->unk168 = 2;
    }
    minecartPlayerCartUpdate(1, (s32)&D_80028C48, 0x7FFF, 0x23);
    minecartUpdateHeadlight();
    if (*s0->unk34 >= 7 && camIsCutsceneActive() != 0 && gCurrentActor->unk154 != 5) {
        gCurrentActor->unkB8 = 300.0f;
    }
    if (gCurrentActor->unk154 == 4) {
        for (i = 0; i < D_807F5FD0; i++) {
            n = D_807F5FD4[i + 1] - D_807F5FD4[i];
            for (j = 0; j < n / 2; j++) {
                tmp = D_807F5FD4[i][j];
                D_807F5FD4[i][j] = D_807F5FD4[i][n - j - 1];
                D_807F5FD4[i][n - j - 1] = tmp;
            }
        }
        s0->unk34 = (u8 *)&D_80028C50;
        s0->unk10 = 2;
        gCurrentActor->unk154 = 5;
        s0->unkC = 0;
    }
    if (gCurrentActor->unk154 != 0) {
        actorGetNodePos(gCurrentActor, 9, &s0->unk4->unk7C, &s0->unk4->unk80, &s0->unk4->unk84);
    }
}

typedef struct MinecartElem {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} MinecartElem;


void heapFree(void *);
void *heapAlloc(s32);

void minecartApplyJunction(MinecartCart *cart, MinecartElem **junctionTable, u8 minTrack, u8 maxTrack) {
    u8 i = 0;
    s32 found = 0;
    u8 curTrack = *cart->unk34;

    for (; i < 4 && found == 0; i++) {
        if (((cart->unk42 == 1 && i < 2) || (cart->unk42 == 2 && i >= 2))) {
            MinecartElem *elem = &junctionTable[curTrack - minTrack][i];

            if (curTrack >= minTrack && curTrack <= maxTrack && cart->unk10 == elem->unk0) {
                heapFree(cart->unk30);
                found = 1;
                cart->unk30 = heapAlloc(3);
                cart->unk34 = cart->unk30;
                cart->unk30[0] = elem->unk3;
                cart->unk34[1] = elem->unk1;
                cart->unk34[2] = 0xFF;
                cart->unk41 = elem->unk2;
                cart->unk10 = 1;
            }
        }
    }
}

extern s32 D_80028C20;
void actorScriptStart(void *, s32);
void actorSetStateTwo(void *);
void hudSpawnCountdownTimer(s32, s32, u8);
void func_80726EE0(s32);
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);

void minecartPlayerCartJunctionBehaviour(void) {
    MinecartCart *cart;
    Struct_807FC924_4_174 *playerState;
    f32 diff;
    f32 scale;

    cart = gCurrentActor->unk174;
    playerState = D_807FBB4C->unk174;
    if (!(gCurrentActor->unk60 & 0x10)) {
        cart->unk30 = heapAlloc(3);
        cart->unk30[0] = 0x10;
        cart->unk30[1] = 0xFF;
        cart->unk24 = 3.0f;
        cart->unk28 = 12.0f;
        gCurrentActor->unk168 = 3;
        playerState->stateFlags |= 8;
        camStartPath(gCurrentActor, 0, 1, cart);
        actorScriptStart(gCurrentActor, 0);
    }
    if (gCurrentActor->unk154 != 5 && gCurrentActor->unk154 != 6) {
        diff = (gPlayerSlots->unk214 - gCurrentActor->unk80) - 100.0f;
        scale = (f32)(((f64)diff / 650.0 * 0.15) + .15);
        actorSetUniformScale(gCurrentActor, scale);
        actorSetUniformScale(D_807FBB4C, scale);
    }
    if (playerState->stateFlags & 8) {
        cart->unk3E = 3;
    }
    if (gCurrentActor->unk154 < 5) {
        minecartPlayerCartUpdate(0x16, (s32)cart->unk30, 0, 0x19);
    }
    if (camIsCutsceneActive() == 0) {
        camSetFixedView(playerState->unk104, 322.0f, 900.0f, 268.0f, 325.0f, -9000.0f, 500.0f, 0);
    }
    switch (gCurrentActor->unk154) {
    case 1:
    case 2:
    case 3:
        if (gCurrentActor->unk4->unk64 == 0x292) {
            minecartTriggerWin(1, 0x14);
            gCurrentActor->unk154 = 5;
        } else if (gCurrentActor->unk11C != NULL && gCurrentActor->unk11C->unk154 == 5) {
            func_80726EE0(0);
            minecartTriggerLoss(1, 0xE);
            gCurrentActor->unk154 = 5;
            break;
        }
        minecartApplyJunction(cart, (MinecartElem **)&D_80028C20, 0x10, 0x13);
        actorGetNodePos(gCurrentActor, 9, &cart->unk4->unk7C, &cart->unk4->unk80, &cart->unk4->unk84);
        return;
    case 4:
        gCurrentActor->unk154 = 3;
        cart->unk34--;
        break;
    case 5:
        actorSetUniformScale(gCurrentActor, 0.15f);
        actorSetUniformScale(D_807FBB4C, 0.225f);
        gCurrentActor->unkE4 = 0;
        gCurrentActor->unk154++;
        break;
    case 10:
        sfxAllocateChannel(0x5A, 1.0f);
        hudSpawnCountdownTimer(0x78, 0x78, (gCurrentMap == 0x4D) ? 0x1E : (gCurrentMap == 0x81) ? 0x2D : 0x3C);
        actorSetStateTwo(gCurrentActor->unk11C);
        playerState->stateFlags &= ~8;
        gCurrentActor->unk154 = 3;
        break;
    }
}


void minecartRampTiltRate(MinecartCart *cart) {
    f32 temp = cart->unk28;
    cart->unk20 += cart->unk24;
    if (temp < cart->unk20) {
        cart->unk20 = temp;
    }
}


extern s32 D_807457E4[];
extern s16 D_80770628[];
extern f32 D_80770B68[];
extern s32 gFrameCounter;
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathPickCloserTargetPoint3D(f32, f32, f32, MinecartTrackPoint *, MinecartTrackPoint *, MinecartTrackPoint *, MinecartTrackPoint *, f32 *, f32 *, f32 *);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
s16 mathAngleEaseToward(s16, s16, f32);
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8067ACB4(void *);
void matrixMakeRotationZ(f32 (*)[4], f32);
void actorUpdateFloorContactAndTilt(void *, f32);
void minecartFollowTrack(MinecartCart *cart, s16 angleDeltaInput, u8 maxTiltLimit) {
    u8 i;
    u8 cnt;
    s8 prevTiltSign;
    MinecartTrackPoint *targetPt;
    MinecartTrackPoint *prevPrevPt;
    f32 rearTargetPt[3];
    f32 frontTargetPt[3];
    f32 rearNodePos[3];
    f32 frontNodePos[3];
    s32 limit;
    f32 prev;
    s16 waypointAngle;
    s16 n;
    f32 diff;
    f32 predX, predY, predZ;
    f32 stepDist;
    f32 lim;
    f64 t;
    f32 mtxTilt[4][4];
    u8 i2;
    u8 cnt2;
    s16 oldYaw;
    s8 lateralShift;
    u8 trackIndex;
    s16 v1;
    f32 junctionX, junctionY, junctionZ;
    MinecartTrackPoint *q;
    MinecartTrackPoint *p;

    prevPrevPt = cart->unkC;
    oldYaw = gCurrentActor->unkE6;
    lateralShift = 0;
    trackIndex = (*cart->unk34 + cart->unk3F) & 0xFF3F;
    func_8067ACB4(gCurrentActor);
    if (cart->unk34 != NULL && prevPrevPt == NULL) {
        gCurrentActor->unk144 = 0x24;
        targetPt = &D_807F5FD4[trackIndex][cart->unk10++];
        gCurrentActor->unk7C = targetPt->x;
        targetPt++;
        gCurrentActor->unk80 = targetPt[-1].y;
        gCurrentActor->unk84 = targetPt[-1].z;
        gCurrentActor->unkA4 = targetPt[-1].y;
        gCurrentActor->unkE6 = mathAngleBetweenPoints2D(targetPt->x, targetPt->z, gCurrentActor->unk7C, gCurrentActor->unk84);
        gCurrentActor->unkE8 = (s16)(s32)(((f64)func_80611BB4(gCurrentActor->unk80 - targetPt->y,
                                sqrtf((gCurrentActor->unk7C - targetPt->x) * (gCurrentActor->unk7C - targetPt->x) + (gCurrentActor->unk84 - targetPt->z) * (gCurrentActor->unk84 - targetPt->z))) * 2048.0) / 3.1415927410125732);
        cart->unkC = targetPt - 2;
        sfxPlayActorSound(gCurrentActor, 0x113, 0, 1, 0, 0xFF, 1.0f, 0);
        cart->unk41 = 1;
    }
    targetPt = &D_807F5FD4[trackIndex][cart->unk10];
    if (cart->unk10 >= 2) {
        prevPrevPt = targetPt - 2;
    }
    if (gCurrentActor->unkB8 < 0.0f && gCurrentActor->unk7C == targetPt[-1].x && gCurrentActor->unk84 == targetPt[-1].z && cart->unk10 >= 2) {
        cart->unk10--;
        targetPt--;
    }
    actorGetNodePos(gCurrentActor, 3, &frontNodePos[0], &frontNodePos[1], &frontNodePos[2]);
    actorGetNodePos(gCurrentActor, 4, &rearNodePos[0], &rearNodePos[1], &rearNodePos[2]);
    stepDist = (f64)(gCurrentActor->unk4->unk38 * gCurrentActor->unkB8) * 0.16666666675;
    if (gCurrentMap == 0x4D || gCurrentMap == 0x81 || gCurrentMap == 0x82) {
        stepDist = (f64)stepDist * 1.8;
    } else {
        if ((2.0 * (f64)func_80612794(gCurrentActor->unkE8)) + 1.0 < 0.6) {
            t = 0.6;
        } else {
            t = (2.0 * (f64)func_80612794(gCurrentActor->unkE8)) + 1.0;
        }
        stepDist = (f64)stepDist * (2.5 * t);
    }
    waypointAngle = mathAngleBetweenPoints2D(targetPt->x, targetPt->z, targetPt[-1].x, targetPt[-1].z);
    if (cart->unk0 == 0) {
        D_80770B68[D_80770628[gCurrentActor->unk6E]] = ((f64)stepDist / 15.0) + 0.7;
    } else {
        D_80770B68[D_80770628[gCurrentActor->unk6E]] = 0.0f;
    }
    if (gCurrentActor->unkF0 != 0) {
        gCurrentActor->unkF0 = gCurrentActor->unkF0 - 1;
        mathPickCloserTargetPoint3D(frontNodePos[0], frontNodePos[1], frontNodePos[2], targetPt, targetPt + 1, targetPt + 1, targetPt + 2, &frontTargetPt[0], &frontTargetPt[1], &frontTargetPt[2]);
        mathPickCloserTargetPoint3D(rearNodePos[0], rearNodePos[1], rearNodePos[2], targetPt - 1, targetPt, targetPt, targetPt + 1, &rearTargetPt[0], &rearTargetPt[1], &rearTargetPt[2]);
    } else {
        mathPickCloserTargetPoint3D(frontNodePos[0], frontNodePos[1], frontNodePos[2], targetPt - 1, targetPt, targetPt, targetPt + 1, &frontTargetPt[0], &frontTargetPt[1], &frontTargetPt[2]);
        mathPickCloserTargetPoint3D(rearNodePos[0], rearNodePos[1], rearNodePos[2], prevPrevPt, prevPrevPt + 1, targetPt - 1, targetPt, &rearTargetPt[0], &rearTargetPt[1], &rearTargetPt[2]);
    }
    gCurrentActor->unkE6 = mathAngleEaseToward(gCurrentActor->unkE6, (s16)(f32)mathAngleBetweenPoints2D(frontTargetPt[0], frontTargetPt[2], rearTargetPt[0], rearTargetPt[2]), 1.7f);
    diff = sqrtf((frontTargetPt[0] - rearTargetPt[0]) * (frontTargetPt[0] - rearTargetPt[0]) + (frontTargetPt[2] - rearTargetPt[2]) * (frontTargetPt[2] - rearTargetPt[2]));
    prev = gCurrentActor->unkE8;
    gCurrentActor->unkE8 = (s16)(s32)(((f64)func_80611BB4(rearTargetPt[1] - frontTargetPt[1], diff) * 2048.0) / 3.1415927410125732);
    prev = prev - (f32)gCurrentActor->unkE8;
    if (prev > 2048.0f) {
        prev -= 4096.0f;
    }
    if (prev <= -2048.0f) {
        prev += 4096.0f;
    }
    if (prev > 25.0f) {
        cnt = 0;
        for (i = 0; i < 0x14; i++) {
            if (D_807457E4[i] != 0) {
                cnt++;
            }
        }
        if (cnt < 5) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x20, 0xFF, 0x7F, 0x14);
        }
    }
    predX = func_80612794(waypointAngle) * stepDist + gCurrentActor->unk7C;
    predZ = func_80612790(waypointAngle) * stepDist + gCurrentActor->unk84;
    predY = gCurrentActor->unkA4;
    if (mathPickCloserTargetPoint3D(predX, predY, predZ, targetPt - 1, targetPt, targetPt, targetPt + 1, &gCurrentActor->unk7C, &gCurrentActor->unk80, &gCurrentActor->unk84) != 0) {
        cart->unk10++;
    }
    gCurrentActor->unk80 = gCurrentActor->unk80 + (f32)cart->unk0;
    n = D_807F5FD4[trackIndex + 1] - D_807F5FD4[trackIndex];
    if (D_807F5FD0 == trackIndex + 1) {
        limit = n - 1;
    } else {
        limit = n;
    }
    if (cart->unk10 >= limit) {
        cart->unk34++;
        if (*cart->unk34 == 0xFF) {
            gCurrentActor->unk154++;
        }
        if (gActivePlayerState->unk1FC != 0 && cart->unk4 == (void *)D_807FBB4C) {
            cart->unk3F = gActivePlayerState->unk1FC;
            gActivePlayerState->unk1FC = 0;
        } else if (gCurrentMap == 0x6A) {
            gCurrentActor->unkF0 = 0x1E;
            cart->unk2C = 0.0f;
            if (*cart->unk34 & 0x80) {
                cart->unk3F = (u32)cart->unk3F >> 1;
            } else if (!(*cart->unk34 & 0x40)) {
                cart->unk3F = 0;
            } else {
                cart->unk3F = cart->unk3F << 1;
            }
            if (cart->unk3F & 0x80) {
                cart->unk3F = 0;
            }
        } else {
            cart->unk3F = 0;
        }
        cart->unk10 = cart->unk41;
        cart->unkC = targetPt - 1;
        cart->unk41 = 1;
    }
    if (cart->unk2C != 0.0f) {
        i = (*cart->unk34 + cart->unk40) & 0x3F;
        q = &D_807F5FD4[i][cart->unk10];
        mathPickCloserTargetPoint3D(predX, predY, predZ, q - 1, q, q, q + 1, &junctionX, &junctionY, &junctionZ);
        gCurrentActor->unk7C = gCurrentActor->unk7C + (junctionX - gCurrentActor->unk7C) * cart->unk2C;
        gCurrentActor->unk84 = gCurrentActor->unk84 + (junctionZ - gCurrentActor->unk84) * cart->unk2C;
        cart->unk2C = (f64)cart->unk2C - 0.06;
        if (cart->unk2C < 0.0f) {
            cart->unk2C = 0.0f;
        }
    }
    prevTiltSign = (cart->unk14 > 0.0f) ? 1 : ((cart->unk14 < 0.0f) ? -1 : 0);
    if (angleDeltaInput == 0x7FFF) {
        v1 = gCurrentActor->unkE6 - oldYaw;
        if (v1 >= 0x801) {
            v1 -= 0x1000;
        }
    } else {
        v1 = angleDeltaInput;
    }
    lim = ((f64)maxTiltLimit < (f64)((f32)(v1 > 0 ? v1 : -v1) * stepDist) * 0.25) ? (f64)maxTiltLimit : (f64)((f32)(v1 > 0 ? v1 : -v1) * stepDist) * 0.25;
    cart->unk18 = (f64)cart->unk18 + (f64)(lim - cart->unk18) * 0.2;
    if (v1 >= 0x1F && v1 < 0x5A) {
        if (cart->unk14 < lim) {
            minecartRampTiltRate(cart);
            cart->unk14 = cart->unk14 + cart->unk20;
            if (lim < cart->unk14) {
                cart->unk14 = lim;
            }
        }
    } else if (v1 < -0x1E && v1 >= -0x59) {
        if (-lim < cart->unk14) {
            minecartRampTiltRate(cart);
            cart->unk14 = cart->unk14 - cart->unk20;
            if (cart->unk14 < -lim) {
                cart->unk14 = -lim;
            }
        }
    }
    if (cart->unk14 > 1.0f) {
        lateralShift = 0x20;
        minecartSpawnWheelEffect(cart, 1, 0xE6);
    } else if (cart->unk14 < -1.0f) {
        lateralShift = -0x20;
        minecartSpawnWheelEffect(cart, 0, 0xE6);
    } else {
        minecartSpawnWheelEffect(cart, gFrameCounter & 1, 0xFA);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
    if (lateralShift != 0) {
        if (cart->unk18 < 10.0f) {
            cart->unk20 = 0.0f;
            if (cart->unk14 > 0.0f) {
                cart->unk14 = cart->unk14 - cart->unk1C;
                if (cart->unk14 < 0.0f) {
                    cart->unk14 = 0.0f;
                }
            } else if (cart->unk14 < 0.0f) {
                cart->unk14 = cart->unk14 + cart->unk1C;
                if (cart->unk14 > 0.0f) {
                    cart->unk14 = 0.0f;
                }
            }
            cart->unk1C = ((f64)cart->unk1C + 0.5 < 10.0) ? (f64)cart->unk1C + 0.5 : 10.0;
        } else {
            cart->unk1C = 0.0f;
            cnt2 = 0;
            i2 = 0;
            do {
                if (D_807457E4[i2] != 0) {
                    cnt2++;
                }
                i2++;
            } while (i2 < 0x14);
            if (cnt2 < 5) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x21, 0xFF, 0x7F, 0x14);
            }
        }
        guTranslateF(gCurrentActor->unkC, (f32)lateralShift, 0.0f, 0.0f);
        matrixMakeRotationZ(mtxTilt, cart->unk14);
        guMtxCatF(gCurrentActor->unkC, mtxTilt, gCurrentActor->unkC);
        guTranslateF(mtxTilt, (f32)-lateralShift, 0.0f, 0.0f);
        guMtxCatF(gCurrentActor->unkC, mtxTilt, gCurrentActor->unkC);
        actorUpdateModelMatrix(gCurrentActor, 1);
        lim = (cart->unk14 > 0.0f) ? cart->unk14 : -cart->unk14;
        if ((f32)cart->unk39 < lim) {
            if (cart->unk14 > 0.0f) {
                cart->unk39 = cart->unk14;
            } else {
                cart->unk39 = -cart->unk14;
            }
        }
    }
    if (((cart->unk14 > 0.0f) ? 1 : ((cart->unk14 < 0.0f) ? -1 : 0)) != prevTiltSign) {
        if (cart->unk39 != 0 && cart->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, ((cart->unk39 / maxTiltLimit) * 0x7F + 0x80) & 0xFF, 0x7F, 0x1E);
            cart->unk39 = 0;
        }
    }
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
}
