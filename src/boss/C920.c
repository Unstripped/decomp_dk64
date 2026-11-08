#include "common.h"

typedef struct BossD_Actor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x144 - 0xF0];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x160 - 0x155];
    f64 unk160;
} BossD_Actor;

typedef struct BossD_Sub178 {
    u8 pad0[0x14];
    u8 unk14;
} BossD_Sub178;

typedef struct BossD_D580 {
    u8 pad0[0x1D8];
    f32 unk1D8;
    u8 pad1DC[0x1F4 - 0x1DC];
    s32 unk1F4;
    u8 pad1F8[0x1FE - 0x1F8];
    s16 unk1FE;
} BossD_D580;

typedef struct BossD_DC90 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0x1A - 0x10];
    u16 unk1A;
    u8 pad1C[0x28 - 0x1C];
    u8 unk28[4];
} BossD_DC90;

extern BossD_Actor *gCurrentActor;
extern BossD_Actor *D_807FBB4C;
extern BossD_D580 *gActivePlayerState;
extern BossD_DC90 *D_807FDC90;
extern void *gCamActor;

void func_800290D4(s32);
s32 playerStateQueueCallback(s32, void *, s32);
void zoneEntryGetPosition(s32, s32, void *, void *, void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void actorScriptStart(void *, s32);
s32 camIsCutsceneActive(void);
void camEndPath(void *);
void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void playerResumeLocomotion(void *);
void camReturnToFollow(void *, void *);
void csModelStateSetFirstByte(s32, s16);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80030920(s32 unused) {
    s16 targetYaw;

    gActivePlayerState->unk1FE = 1;
    func_800290D4(1);
    gCurrentActor->unk144 = 0x24;
    playerStateQueueCallback(0x19, gCurrentActor, 0);
    zoneEntryGetPosition(1, 8, &gCurrentActor->unk7C, &gCurrentActor->unk80, &gCurrentActor->unk84);
    D_807FDC90->unkA = gCurrentActor->unk7C;
    D_807FDC90->unkC = gCurrentActor->unk80;
    D_807FDC90->unkE = gCurrentActor->unk84;
    zoneEntryGetPosition(1, 0x20, &D_807FBB4C->unk7C, &D_807FBB4C->unk80, &D_807FBB4C->unk84);
    D_807FBB4C->unkE6 = mathAngleBetweenPoints2D(gCurrentActor->unk7C, gCurrentActor->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk84);
    targetYaw = D_807FBB4C->unkE6 + 0x800;
    gCurrentActor->unkE6 = targetYaw;
    gCurrentActor->unkEE = targetYaw;
    actorScriptStart(gCurrentActor, 0x3F9);
    if (camIsCutsceneActive() != 0) {
        camEndPath(gCamActor);
    }
    camSetTarget(gCamActor, D_807FBB4C, 4, 0x800, 0x5A, 0, 0x46, 0x64, 0x3A, 0, 0.3f);
}
void func_80030AE0(BossD_Sub178 *sub178) {
    func_800290D4(0);
    gActivePlayerState->unk1F4 = 0;
    if (D_807FBB4C->unk154 != 0x36) {
        playerResumeLocomotion(D_807FBB4C);
    }
    camReturnToFollow(gCamActor, D_807FBB4C);
    gActivePlayerState->unk1D8 = 0.01f;
    csModelStateSetFirstByte(0xB, (sub178->unk14 <= 0) ? 0 : 4);
    csModelStateSetFirstByte(0xC, (sub178->unk14 < 2) ? 0 : 4);
    csModelStateSetFirstByte(0xD, (sub178->unk14 < 3) ? 0 : 4);
    csModelStateSetFirstByte(0xE, (sub178->unk14 < 4) ? 0 : 4);
    csModelStateSetFirstByte(0xA, 0xA);
}

void func_80030C30(f32 stepRate) {
    gCurrentActor->unk7C = (f32) (((f64) (D_807FBB4C->unk7C - (f32) D_807FDC90->unkA) * gCurrentActor->unk160) + (f64) D_807FDC90->unkA);
    gCurrentActor->unk80 = (f32) (((f64) (D_807FBB4C->unk80 - (f32) D_807FDC90->unkC) * gCurrentActor->unk160) + (f64) D_807FDC90->unkC);
    gCurrentActor->unk84 = (f32) (((f64) (D_807FBB4C->unk84 - (f32) D_807FDC90->unkE) * gCurrentActor->unk160) + (f64) D_807FDC90->unkE);
    gCurrentActor->unk160 += stepRate;
    if (gCurrentActor->unk160 > 0.8) {
        gCurrentActor->unk160 = 0.8;
    }
}

void func_80030D50(void) {
    s32 pad[1];
    f32 sinOffset;
    sinOffset = func_80612794((s16)(gCurrentActor->unk160 * 10240.0));
    gCurrentActor->unk7C += (80.0f * func_80612794(gCurrentActor->unkE6 + 0x400)) * sinOffset;
    sinOffset = func_80612794((s16)(gCurrentActor->unk160 * 10240.0));
    gCurrentActor->unk84 += (80.0f * func_80612790(gCurrentActor->unkE6 + 0x400)) * sinOffset;
}

void func_80030E58(void) {
    D_807FDC90->unk1A |= 1;
    sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x2E2, 0xFF, 0x65, 0, 0, 0.0f, 0);
}

typedef struct BossScriptState {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
} BossScriptState;

typedef struct BossActor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xCC - 0xBC];
    u8 unkCC;
    u8 padCD[0xE6 - 0xCD];
    s16 unkE6;
    u8 padE8[0xEC - 0xE8];
    s16 unkEC;
    s16 unkEE;
    u8 padF0[0x110 - 0xF0];
    u8 unk110;
    u8 pad111[0x128 - 0x111];
    s16 unk128;
    u8 pad12A[0x132 - 0x12A];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[1];
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x160 - 0x156];
    f64 unk160;
    u8 pad168[0x178 - 0x168];
    BossScriptState *unk178;
} BossActor;

typedef struct BossWorkState {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0x1A - 0x10];
    u16 unk1A;
    u8 pad1C[0x25 - 0x1C];
    u8 unk25;
} BossWorkState;

typedef struct BossPlayerData {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0x1F0 - 0xD6];
    s32 unk1F0;
} BossPlayerData;

typedef struct BossGlobalC924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BossGlobalC924;

typedef struct BossLayoutData {
    u8 pad0[0x20];
    u8 (*unk20)[2];
} BossLayoutData;

typedef struct BossConfig {
    u8 pad0[0xC];
    u8 unkC;
} BossConfig;

extern u8 D_80036A90[];
extern u8 D_80036AA8[];

// C920's .data (0x80035AC0-0x80035AF4; the TU ends here, DAA0's data starts 16-aligned at 0x80035B00)
u8 *D_80035AC0[4] = { D_80036A90, D_80036AA8, D_80036AA8, D_80036AA8 };
u8 D_80035AD0[4] = { 3, 0, 2, 1 };
f32 D_80035AD4[4] = { 0.015f, 0.025f, 0.03f, 0.01f };
f32 D_80035AE4[4] = { 1.0f, 1.3f, 1.8f, 0.7f };
extern u8 D_807FBD70;
extern BossGlobalC924 *gPlayerSlots;
extern BossLayoutData *D_807FDC98;
extern BossConfig *D_807FDC9C;

void behaviourFrameBegin(void);
void bossRoundFrame(u8 *);
void camSetSecondTarget(void *, s32, s32);
void func_80724CA4(s32, s32);
void playerSetLargeModeScale(f32);
void flagSet(s32, s32, s32);
void camStartPath(void *, s32, u8);
void func_80641874(s32, s32);
void actorSetTargetSpeed(void *, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void scriptSetActorRampTarget(void *, f32, f32);
void playerSetSizeMode(void *, s32);
s32 func_806C9974(s32, s32);
void func_80614E78(void *, s32);
void patrolGetNextWaypointPos(s16 *, s16 *, s16 *);
void actorSetGroupState(u8, s32);
s16 mathAngleSignedDistance(s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
s32 currentActorTestClearFlag(void);
s32 bossScriptStep(u8 *, s32, f32);
void billboardSetFlags(s32);
void billboardSubmit(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8072881C(s32, void *);
void actorUpdateModelMatrix(void *, s32);

#define BOSS_ACTOR ((BossActor *)gCurrentActor)
#define PLAYER_ACTOR ((BossActor *)D_807FBB4C)
#define WORK_STATE ((BossWorkState *)D_807FDC90)
#define PLAYER_DATA ((BossPlayerData *)gActivePlayerState)

void func_80030EC4(void) {
    BossScriptState *scriptState;
    u8 *scriptOpcodes;
    s16 waypointCoords[3];

    scriptState = BOSS_ACTOR->unk178;
    scriptOpcodes = D_80035AC0[scriptState->unk14];
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(BOSS_ACTOR->unk60 & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        BOSS_ACTOR->unk146 = 5;
        BOSS_ACTOR->unk154 = 0x1E;
        BOSS_ACTOR->unk155 = 0;
        BOSS_ACTOR->unkCC = 0;
        func_80724CA4(2, 1);
        BOSS_ACTOR->unk110 = 0;
        BOSS_ACTOR->unk60 &= ~0x8000;
        playerSetLargeModeScale(0.45f);
        func_800290D4(0);
        flagSet(0x5F, 0, 2);
    }
    if (WORK_STATE->unk1A & 1) {
        BOSS_ACTOR->unk128 -= (scriptState->unk14 > 0) ? 10 : 5;
        if (BOSS_ACTOR->unk128 < 0) {
            BOSS_ACTOR->unk128 = 0;
            WORK_STATE->unk1A &= ~1;
        }
    } else if (BOSS_ACTOR->unk154 != 0x29 && (PLAYER_DATA->unk1F0 & 0x40) && BOSS_ACTOR->unk128 < 0xFF) {
        if (!(WORK_STATE->unk1A & 0x8000)) {
            camStartPath(BOSS_ACTOR, 2, 1);
            WORK_STATE->unk1A |= 0x8000;
        } else {
            func_80641874(2, 0);
        }
        BOSS_ACTOR->unk128 += 5;
        if (BOSS_ACTOR->unk128 >= 0x100) {
            BOSS_ACTOR->unk128 = 0xFF;
        }
    }
    if (gPlayerSlots->unk2C0 != 1 && (BOSS_ACTOR->unk154 == 0x42 || BOSS_ACTOR->unk154 == 0x27)) {
        BOSS_ACTOR->unk144 = 1;
        actorSetTargetSpeed(BOSS_ACTOR, 0);
        BOSS_ACTOR->unk154 = 0x29;
        BOSS_ACTOR->unk155 = 0;
        BOSS_ACTOR->unk155 = 1;
    }
    switch (BOSS_ACTOR->unk154) {
    case 0x29:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            actorMoveWithinZone(0, (f32)WORK_STATE->unkA, (f32)WORK_STATE->unkE, 0x309, 0.0f);
            break;
        case 1:
            if (scriptState->unk14 >= 2) {
                func_80030E58();
            }
            BOSS_ACTOR->unk132 = 4;
            func_80030920((s32)scriptState);
            scriptSetActorRampTarget(BOSS_ACTOR, D_80035AE4[scriptState->unk14], 0.0f);
            BOSS_ACTOR->unk155++;
            break;
        case 3:
            BOSS_ACTOR->unk160 = 0.0;
            BOSS_ACTOR->unk155++;
            /* fallthrough */
        case 4:
            func_80030C30(D_80035AD4[scriptState->unk14]);
            if (scriptState->unk14 == 3) {
                func_80030D50();
            }
            break;
        case 5:
            BOSS_ACTOR->unk155++;
            break;
        case 6:
            if (D_807FBD70 == 5 && PLAYER_ACTOR->unk154 == 0x24 && BOSS_ACTOR->unk160 > 0.79) {
                if (scriptState->unk14 == 3) {
                    BOSS_ACTOR->unk154 = 0x37;
                    BOSS_ACTOR->unk155 = 0;
                    actorScriptStart(PLAYER_ACTOR, 0);
                    actorScriptStart(BOSS_ACTOR, 0);
                    camStartPath(BOSS_ACTOR, 0x16, 1);
                    flagSet(0x1B0, 1, 0);
                } else {
                    BOSS_ACTOR->unk128 = 0xFF;
                    BOSS_ACTOR->unk132 = 1;
                    BOSS_ACTOR->unk155 = 8;
                    camStartPath(BOSS_ACTOR, 0x17, 1);
                    actorScriptStart(BOSS_ACTOR, 0);
                }
                func_80641874(2, 0xFF);
            }
            func_80030C30(D_80035AD4[scriptState->unk14]);
            if (scriptState->unk14 == 3) {
                func_80030D50();
            }
            break;
        case 7:
            BOSS_ACTOR->unk128 = 0xFF;
            PLAYER_DATA->unkD4 = 0x12C;
            camStartPath(BOSS_ACTOR, 0x18, 1);
            func_80641874(2, 0xFF);
            scriptSetActorRampTarget(BOSS_ACTOR, 1.0f, 0.0f);
            actorScriptStart(BOSS_ACTOR, 0);
            BOSS_ACTOR->unk155 = 0xA;
            break;
        case 8:
            if (camIsCutsceneActive() == 0) {
                BOSS_ACTOR->unk155++;
            }
            break;
        case 9:
            scriptState->unk15 = 0;
            scriptState->unk14++;
            scriptOpcodes = D_80035AC0[scriptState->unk14];
            /* fallthrough */
        case 10:
        case 11:
        case 12:
            if (camIsCutsceneActive() == 0) {
                playerSetSizeMode(PLAYER_ACTOR, 1);
                actorSetTargetSpeed(BOSS_ACTOR, D_807FDC9C->unkC);
                if (BOSS_ACTOR->unk132 != 1) {
                    if (func_806C9974(0, -1) != 0) {
                        func_80614E78(PLAYER_ACTOR, 0x27);
                        PLAYER_ACTOR->unk154 = 0x36;
                        PLAYER_ACTOR->unk155 = 0;
                    }
                    BOSS_ACTOR->unk132 = 1;
                    scriptState->unk15 = scriptState->unk16;
                }
                func_80030AE0((BossD_Sub178 *)scriptState);
                BOSS_ACTOR->unk154 = scriptOpcodes[scriptState->unk15];
                scriptState->unk15++;
                BOSS_ACTOR->unk155 = 0;
                actorScriptStart(BOSS_ACTOR, 0x3E4);
                func_80030E58();
            }
            break;
        }
        break;
    case 0x28:
        func_80030E58();
        BOSS_ACTOR->unk154 = scriptOpcodes[scriptState->unk15];
        scriptState->unk15++;
        BOSS_ACTOR->unk155 = 0;
        break;
    case 0x27:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            patrolGetNextWaypointPos(&waypointCoords[2], &waypointCoords[1], &waypointCoords[0]);
            actorSetGroupState((D_80035AD0 - 1)[D_807FDC98->unk20[WORK_STATE->unk25 & 0x7F][0]], 1);
            BOSS_ACTOR->unkEC = mathAngleBetweenPoints2D((f32)waypointCoords[2], (f32)waypointCoords[0], BOSS_ACTOR->unk7C, BOSS_ACTOR->unk84);
            if (mathAngleSignedDistance(BOSS_ACTOR->unkE6, BOSS_ACTOR->unkEC) < 0) {
                actorScriptStart(BOSS_ACTOR, 0x401);
            } else {
                actorScriptStart(BOSS_ACTOR, 0x402);
            }
            actorSetTargetSpeed(BOSS_ACTOR, 0);
            BOSS_ACTOR->unk155++;
            break;
        case 1:
            BOSS_ACTOR->unkE6 = mathAngleEaseToward(BOSS_ACTOR->unkE6, (s16)(BOSS_ACTOR->unkEC + 0x800), 10.0f);
            actorMoveWithinZone(0, (f32)WORK_STATE->unkA, (f32)WORK_STATE->unkE, 0x309, 0.0f);
            break;
        case 2:
            BOSS_ACTOR->unkEE = BOSS_ACTOR->unkE6;
            BOSS_ACTOR->unkB8 = -150.0f;
            BOSS_ACTOR->unk155++;
            /* fallthrough */
        case 3:
            actorMoveWithinZone(0, (f32)WORK_STATE->unkA, (f32)WORK_STATE->unkE, 0x309, 0.0f);
            break;
        case 4:
            BOSS_ACTOR->unkB8 = BOSS_ACTOR->unkB8 * -1.0f;
            BOSS_ACTOR->unkE6 += 0x800;
            BOSS_ACTOR->unkEE = BOSS_ACTOR->unkE6;
            actorSetTargetSpeed(BOSS_ACTOR, D_807FDC9C->unkC);
            BOSS_ACTOR->unk154 = scriptOpcodes[scriptState->unk15];
            scriptState->unk15++;
            BOSS_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x1E:
        scriptState->unk14 = 0;
        scriptState->unk15 = 0;
        BOSS_ACTOR->unk154 = scriptOpcodes[scriptState->unk15];
        scriptState->unk15++;
        BOSS_ACTOR->unk155 = 0;
        BOSS_ACTOR->unkB8 = (f32)(u32)D_807FDC9C->unkC;
        break;
    case 0:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            actorScriptStart(BOSS_ACTOR, 0x3EA);
            BOSS_ACTOR->unk155++;
            break;
        case 2:
            BOSS_ACTOR->unk154 = scriptOpcodes[scriptState->unk15];
            scriptState->unk15++;
            BOSS_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            BOSS_ACTOR->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                PLAYER_ACTOR->unk60 &= ~4;
                camStartPath(BOSS_ACTOR, 0x1A, 1);
                BOSS_ACTOR->unk155++;
            }
            break;
        }
        break;
    default:
        bossScriptStep(scriptOpcodes, 0x19, 0.0f);
        break;
    }
    if (BOSS_ACTOR->unk60 & 4) {
        billboardSetFlags(1);
        billboardSubmit(BOSS_ACTOR, 0x3C8, 0x40, 0x40, 0x3C, 0x3C, 1, 0x12C, 0xB4, 0, 1.0f);
    }
    if (func_8072881C(0, D_807FDC90->unk28) != 0) {
        func_8072881C(0x81, D_807FDC90->unk28);
    }
    actorUpdateModelMatrix(BOSS_ACTOR, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036A90.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036AA8.s")
