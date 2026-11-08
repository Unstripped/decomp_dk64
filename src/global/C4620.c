#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBDC4;

typedef struct R1C46aInner {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} R1C46aInner;

typedef struct R1C46aSub4 {
    /* 0x00 */ R1C46aInner *unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 *unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 pad20[0x14];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} R1C46aSub4;

typedef struct R1C46aActor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ R1C46aSub4 *unk4;
    /* 0x008 */ u8 pad8[0x52];
    /* 0x05A */ u16 unk5A;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 unkCC;
    /* 0x0CD */ u8 padCD[0x19];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x34];
    /* 0x11C */ struct R1C46aActor *unk11C;
    /* 0x120 */ u8 pad120[0x20];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 pad144[2];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ void *unk178;
    /* 0x17C */ u16 *unk17C;
} R1C46aActor;

#define R1V ((R1C46aActor *)gCurrentActor)

void *heapAlloc(s32);
void func_806C8220();
void func_806F22A8(Actor *, void *, s32 *);
void func_806F1EB0(Actor *, void *, s32 *);
void func_806F1C04(Actor *, void *, s32 *);

void func_806BF920(void) {
    u16 *state;
    s32 outCount;
    s32 bufferSize;

    state = R1V->unk17C;
    outCount = 0;
    if (!(R1V->unk60 & 0x10)) {
        bufferSize = 0;
        switch (*state) {
            case 1:
            case 2:
            case 3:
                bufferSize = 3;
                break;
            case 9:
            case 10:
            case 11:
                bufferSize = 5;
                break;
            case 4:
            case 5:
                bufferSize = 2;
                break;
        }
        if (bufferSize != 0) {
            R1V->unk4->unk1C = heapAlloc(0x100);
            func_806C8220(0, R1V->unk178, bufferSize);
        }
    }
    switch (*state) {
        case 1:
        case 2:
        case 3:
            func_806F22A8(gCurrentActor, R1V->unk4->unk1C, &outCount);
            break;
        case 9:
        case 10:
        case 11:
            func_806F1EB0(gCurrentActor, R1V->unk4->unk1C, &outCount);
            break;
        case 4:
        case 5:
            func_806F1C04(gCurrentActor, R1V->unk4->unk1C, &outCount);
            break;
    }
    if (outCount != 0) {
        R1V->unk4->unk1C[outCount * 8] = 0;
    }
}

void func_806F0D68();
void func_806C7BAC();
void func_806F0C18(void *);
void func_806F10E8();
void controllerAnimFreeStateAsset();
void controllerAnimSetState(Actor *, s16, f32, f32);

void func_806BFA8C(u16 animId) {
    switch (animId) {
        case 0xEA:
        case 0x23E:
        case 0x23F:
        case 0x240:
        case 0x4C7:
            R1V->unk155 = 1;
            break;
        case 0x112:
            func_806F0D68(gCurrentActor);
        case 0x113:
        case 0x128:
        case 0x129:
        case 0x12A:
        case 0x12B:
        case 0x12C:
        case 0x12D:
        case 0x12E:
        case 0x12F:
        case 0x130:
            func_806C7BAC(gCurrentActor, 0);
            break;
        case 0x114:
            func_806F0C18(gCurrentActor);
            func_806F10E8(gCurrentActor);
            break;
        case 0x2CF:
            controllerAnimFreeStateAsset(gCurrentActor);
            controllerAnimSetState(gCurrentActor, 0x2CF, 0.0f, 0.0f);
            break;
    }
}

void controllerStepMotionWindows();
void actorUpdateModelMatrix(Actor *, s32);
void actorCheckWorldBounds(Actor *);

void func_806BFBB4(void) {
    controllerStepMotionWindows(gCurrentActor);
    actorUpdateModelMatrix(gCurrentActor, 0);
    actorCheckWorldBounds(gCurrentActor);
}

typedef struct LgBFInner {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} LgBFInner;

typedef struct LgBFInnerPtr {
    /* 0x00 */ LgBFInner *unk0;
    /* 0x04 */ u8 pad4[0x34];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x28];
    /* 0x64 */ u16 unk64;
} LgBFInnerPtr;

typedef struct LgBFState {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u8 pad20[2];
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B[2];
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
} LgBFState;

typedef struct LgBFActor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgBFInnerPtr *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
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
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[10];
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 pad16D[0xF];
    /* 0x17C */ LgBFState *unk17C;
} LgBFActor;

typedef struct LgBFCmd {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} LgBFCmd;

typedef struct LgBFS90 {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x15];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ u8 pad2C[4];
    /* 0x30 */ f32 unk30;
} LgBFS90;

typedef struct LgBFS98 {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s8 *unk20;
    /* 0x24 */ u8 pad24[0x22];
    /* 0x46 */ u16 unk46;
} LgBFS98;

typedef struct LgBFS9C {
    /* 0x00 */ u8 pad0[0x11];
    /* 0x11 */ u8 unk11;
} LgBFS9C;

typedef struct LgBFNode {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[4];
} LgBFNode;

typedef struct LgBFDCA0 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ LgBFNode *unk14;
} LgBFDCA0;

#define LgBV ((LgBFActor *)gCurrentActor)
#define LgBS90 ((LgBFS90 *)D_807FDC90)
#define LgBS98 ((LgBFS98 *)D_807FDC98)
#define LgBS9C ((LgBFS9C *)D_807FDC9C)

extern u8 D_807444EC;
extern s32 gCurrentMap;
extern f32 D_807502E8;
extern u16 D_80747750[];
extern u16 D_80747904[];
extern u8 D_807478F4[];
extern u8 D_80747B00[];
extern void *D_80746B80[];
extern LgBFDCA0 *D_807FDCA0;

void func_806F09F0(Actor *, u16);
void actorSetTargetSpeed(Actor *, s32);
void actorScriptStart(void *, s32);
void scriptSetActorRampTarget(Actor *, f32, f32);
s32 pathPlaybackStart(void *, s32, s32, f32, f32, f32, s32);
void pathPlaybackSetSpeed(s32, u8);
void pathPlaybackSetLoopLimit(s32, s32);
void pathPlaybackSetActive(s32, s32);
void pathPlaybackAdvance(s32);
void pathPlaybackGetPosition(s32, f32 *, f32 *, f32 *);
s32 pathPlaybackIsActive();
void actorSetUniformScale(Actor *, f32);
void *spawnNodeActivate(s32, s32);
s32 func_8072881C(s32, void *);
void actorApplyGravity(void);
void func_8072A450(void);
void func_8072DC7C(s32);
void func_8072E320(f32);
s32 mathAngleLerp(s16, s16, f32);
void lightUpdateFromActorLighting(void *, void *, void *);
void heapFree(void *);
s32 randomNonNegative(void);
void func_80714950(s32);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80717D4C(void);
void actorApplyVelocityCustom(void *, f32, f32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s32 actorMoveWithinZone(u8, f32, f32, s32, f32);
s32 patrolPathStep(u8, s32);

void actorScriptedCommandUpdate(void) {
    s16 j;
    s16 t;
    s16 i;
    LgBFCmd *cmd;
    LgBFState *state;
    f32 ratio;
    f32 ratio2;
    u8 *col;
    s32 node;
    f32 particleScale;
    f32 posX;
    f32 posY;
    f32 posZ;

    state = LgBV->unk17C;
    if (!(LgBV->unk60 & 0x10)) {
        state->unk1A = 0;
        state->unk18 = 0;
        state->unk30 = 0xFF;
        state->unk33 = 0x12;
        state->unk22 = 0x64;
        func_806F09F0(gCurrentActor, (u16)gCurrentActor->actorType);
        actorSetTargetSpeed(gCurrentActor, 0);
        LgBV->unk60 &= 0xFFFDFFFF;
        if (gCurrentMap == 0x4C) {
            LgBV->unk60 &= 0xFEFFFFFF;
            LgBV->unk60 |= 0x400;
        }
        LgBV->unkC4 = D_807502E8;
    }
    if (D_807444EC != 1 && gCurrentMap != 0x4C && gCurrentActor->actorType != 0xFEU) { // FAKE: unsigned literal keeps the early 254 const out of the loop-spanning 254 live range
        LgBV->unk60 &= 0xEFFFFFFF;
        return;
    }
    if (gCurrentMap == 0x4C) {
        lightUpdateFromActorLighting(&LgBV->unk16A, &LgBV->unk16B, &LgBV->unk16C);
    }
    for (i = 0; i < D_807FBDC4; i++) {
        if (D_807FBB70.unk258[i] == 3) {
        cmd = (LgBFCmd *)D_807FBB70.unk278[i];
        switch (cmd->unk2) {
            case 25:
                state->unk33 = cmd->unk4;
                state->unk22 = cmd->unk6;
                break;
            case 24:
                state->unk30 = pathPlaybackStart(gCurrentActor, state->unk2D, 0, 0.0f, 0.0f, 0.0f, 0);
                state->unk31 = cmd->unk4;
                state->unk32 = cmd->unk6;
                pathPlaybackSetSpeed(state->unk30, state->unk2E / cmd->unk4);
                pathPlaybackSetLoopLimit(state->unk30, 1);
                pathPlaybackSetActive(state->unk30, 1);
                break;
            case 23:
                state->unk2D = cmd->unk4;
                state->unk2E = cmd->unk6;
                state->unk2F = pathPlaybackStart(gCurrentActor, state->unk2D, 0, 0.0f, 0.0f, 0.0f, 0);
                pathPlaybackSetSpeed(state->unk2F, state->unk2E);
                pathPlaybackSetLoopLimit(state->unk2F, 1);
                pathPlaybackSetActive(state->unk2F, 1);
                LgBV->unk154 = 0xC;
                LgBV->unk155 = 0;
                break;
            case 0:
                LgBV->unkC0 = cmd->unk4;
                break;
            case 7:
                LgBV->unkB8 = cmd->unk4;
                LgBV->unkEE = (cmd->unk6 << 12) / 360;
                break;
            case 2:
                LgBV->unk4->unk0->unk10 = -1;
                actorScriptStart(gCurrentActor, D_80747750[cmd->unk4]);
                if (cmd->unk6 != 0) {
                    scriptSetActorRampTarget(gCurrentActor, cmd->unk6 / 100.0, 0.0f);
                }
                break;
            case 3:
                if (LgBV->unk4->unk64 != 0) {
                    actorScriptStart(gCurrentActor, 0);
                }
                controllerAnimSetState(gCurrentActor, cmd->unk6 - (0 - D_80747904[cmd->unk4]), 0.0f, 0.0f); // FAKE: cmd6 evaluated before the table lookup (ring order)
                scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
                func_806BFA8C(cmd->unk6 - (0 - D_80747904[cmd->unk4])); // FAKE: cmd6 evaluated before the table lookup (ring order)
                break;
            case 13:
                if (LgBV->unk4->unk64 != 0) {
                    actorScriptStart(gCurrentActor, 0);
                }
                controllerAnimSetState(gCurrentActor, cmd->unk6 - (0 - D_80747904[cmd->unk4]), 0.0f, 8.0f); // FAKE: cmd6 evaluated before the table lookup (ring order)
                scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
                func_806BFA8C(cmd->unk6 - (0 - D_80747904[cmd->unk4])); // FAKE: cmd6 evaluated before the table lookup (ring order)
                break;
            case 4:
                scriptSetActorRampTarget(gCurrentActor, cmd->unk4 / 100.0, cmd->unk6);
                break;
            case 5:
                LgBV->unk154 = 2;
                LgBV->unk155 = 0;
                if (LgBS98->unk20 != NULL) {
                    heapFree(LgBS98->unk20);
                }
                LgBS9C->unk11 = 1;
                LgBS98->unk20 = heapAlloc(2);
                LgBS98->unk20[1] = 0;
                LgBS98->unk20[0] = cmd->unk4;
                LgBS90->unk25 = 0;
                actorSetTargetSpeed(gCurrentActor, cmd->unk6);
                break;
            case 6:
                LgBV->unkB8 = 0.0f;
                LgBV->unkC0 = 0.0f;
                LgBV->unk7C = D_807FDCA0->unk14[cmd->unk4].unk0;
                LgBV->unk80 = D_807FDCA0->unk14[cmd->unk4].unk2;
                LgBV->unk84 = D_807FDCA0->unk14[cmd->unk4].unk4;
                LgBV->unkE6 = (cmd->unk6 << 12) / 360;
                LgBV->unkEE = LgBV->unkE6;
                break;
            case 8:
                if (cmd->unk6 != 0) {
                    state->unk2 = LgBV->unkE6;
                    state->unk4 = (cmd->unk4 << 12) / 360;
                    state->unk23 = cmd->unk6;
                    state->unk24 = cmd->unk6;
                } else {
                    LgBV->unkE6 = (cmd->unk4 << 12) / 360;
                }
                break;
            case 19:
                if (cmd->unk6 != 0) {
                    state->unk6 = LgBV->unkE4;
                    state->unk8 = (cmd->unk4 << 12) / 360;
                    state->unk25 = cmd->unk6;
                    state->unk26 = cmd->unk6;
                } else {
                    LgBV->unkE4 = (cmd->unk4 << 12) / 360;
                }
                break;
            case 20:
                if (cmd->unk6 != 0) {
                    state->unkA = LgBV->unkE8;
                    state->unkC = (cmd->unk4 << 12) / 360;
                    state->unk27 = cmd->unk6;
                    state->unk28 = cmd->unk6;
                } else {
                    LgBV->unkE8 = (cmd->unk4 << 12) / 360;
                }
                break;
            case 21:
                LgBV->unkC4 = cmd->unk4;
                LgBV->unkC0 = 0.0f;
                LgBV->unk154 = 0x1D;
                break;
            case 16:
                if (cmd->unk6 != 0) {
                    state->unk14 = LgBV->unk4->unk38;
                    LgBS90->unk30 = cmd->unk4 * 0.01;
                    state->unk29 = cmd->unk6;
                    state->unk2A = cmd->unk6;
                } else {
                    actorSetUniformScale(gCurrentActor, cmd->unk4 * 0.01);
                }
                break;
            case 9:
                LgBS90->unk4 = spawnNodeActivate(cmd->unk4, 0);
                break;
            case 11:
                state->unk1C = cmd->unk4;
                break;
            case 12:
                state->unkE = cmd->unk4;
                state->unk10 = cmd->unk6;
                state->unk1E = state->unk1C;
                LgBV->unk154 = 0xE;
                LgBV->unk155 = 0;
                break;
            case 14:
                state->unkE = cmd->unk4;
                state->unk10 = cmd->unk6;
                state->unk1E = state->unk1C;
                LgBV->unk154 = 0xF;
                LgBV->unk155 = 0;
                break;
            case 10:
                state->unk18 = (cmd->unk4 << 12) / 360;
                state->unk1A = cmd->unk6;
                break;
            case 15:
                LgBV->unk16A = D_807478F4[cmd->unk4 * 3];
                LgBV->unk16B = D_807478F4[cmd->unk4 * 3 + 1];
                LgBV->unk16C = D_807478F4[cmd->unk4 * 3 + 2];
                break;
            case 17:
                LgBV->unk60 &= 0xFFFF7FFF;
                LgBV->unk154 = 0x37;
                LgBV->unk155 = 0;
                break;
            case 18:
                LgBV->unk60 &= 0xFF7FFFFF;
                break;
            case 26:
                LgBS90->unk4 = spawnNodeActivate(cmd->unk4, 0);
                LgBV->unk15F = cmd->unk6;
                LgBV->unk154 = 0xD;
                LgBV->unk155 = 0;
                break;
            case 22:
                LgBV->unk154 = 2;
                LgBV->unk155 = 0;
                break;
        }
        }
    }
    if (state->unk28 != 0) {
        ratio = (f32)(u32)state->unk28-- / (f32)(u32)state->unk27;
        LgBV->unkE8 = mathAngleLerp(state->unkC, state->unkA, ratio);
    }
    if (state->unk26 != 0) {
        ratio = (f32)(u32)state->unk26-- / (f32)(u32)state->unk25;
        LgBV->unkE4 = mathAngleLerp(state->unk8, state->unk6, ratio);
    }
    if (state->unk24 != 0) {
        ratio = (f32)(u32)state->unk24-- / (f32)(u32)state->unk23;
        LgBV->unkE6 = mathAngleLerp(state->unk4, state->unk2, ratio);
        LgBV->unkEE = LgBV->unkE6;
    }
    if (state->unk2A != 0) {
        ratio2 = (f32)(u32)state->unk2A-- / (f32)(u32)state->unk29;
        actorSetUniformScale(gCurrentActor, LgBS90->unk30 + (state->unk14 - LgBS90->unk30) * ratio2);
    }
    if (state->unk30 != 0xFF) {
        for (j = 0; j < state->unk31 && state->unk30 != 0xFF; j++) {
            if (j == 0xFE) {} // FAKE: extra 254 reference gives the 254 const a higher colouring priority (s4); dropping it costs 75 lines
            particleScale = (((randomNonNegative() >> 15) % 32767) % 51 + 0x4B) * 0.01;
            if (state->unk30 == 0xFE) {
                actorGetNodePos(gCurrentActor, 4, &posX, &posY, &posZ);
            } else if (pathPlaybackIsActive(state->unk30) != 0) {
                pathPlaybackAdvance(state->unk30);
                pathPlaybackGetPosition(state->unk30, &posX, &posY, &posZ);
                posY += 10.0f;
            } else {
                state->unk30 = 0xFF;
            }
            if (state->unk30 == 0xFE || (state->unk30 != 0xFF && pathPlaybackIsActive(state->unk30) != 0)) {
                func_807149A8(0x7D0);
                func_807149B8(1);
                func_80714998(2);
                col = &D_80747B00[state->unk32 * 3u];
                func_807149C8(col[0], col[1], col[2], 0xFF);
                func_8071498C(func_80717D4C);
                func_80714950(-10 - (randomNonNegative() >> 15) % 30);
                func_80714CC0(D_80746B80[state->unk33], (f32)state->unk22 * 0.01 * particleScale, posX, posY, posZ);
            }
        }
    }
    switch (gCurrentActor->state) {
        case 0xD:
            if (LgBV->unk15F != 0) {
                node = LgBV->unk15F;
                actorGetNodePos(LgBS90->unk4, node, &LgBV->unk7C, &LgBV->unk80, &LgBV->unk84);
            } else {
                LgBV->unk7C = D_807FDC94->x;
                LgBV->unk80 = D_807FDC94->y;
                LgBV->unk84 = D_807FDC94->z;
            }
        LgBV->unkE6 = LgBS90->unk4->yaw;
            break;
        case 0xC:
            pathPlaybackAdvance(state->unk2F);
            pathPlaybackGetPosition(state->unk2F, &LgBV->unk7C, &LgBV->unk80, &LgBV->unk84);
            func_8072E320(8.0f);
            break;
        case 0xE:
        case 0xF:
            if (state->unk1E != 0) {
                LgBFNode *a3 = &D_807FDCA0->unk14[state->unkE];
                LgBFNode *v1 = &D_807FDCA0->unk14[state->unk10];
                f32 frac = (f32)state->unk1E / (f32)state->unk1C;
                state->unk1E--;
                LgBV->unk7C = v1->unk0 + (a3->unk0 - v1->unk0) * frac;
                LgBV->unk84 = v1->unk4 + (a3->unk4 - v1->unk4) * frac;
                if (LgBV->unk154 == 0xF) {
                    LgBV->unk80 = v1->unk2 + (a3->unk2 - v1->unk2) * frac;
                } else {
                    actorMoveWithinZone(0, v1->unk0, v1->unk4, 0x212, 0.0f);
                }
            } else {
                LgBV->unk154 = 0;
                LgBV->unk155 = 0;
                actorSetTargetSpeed(gCurrentActor, 0);
            }
            break;
        case 0x2:
            actorMoveWithinZone(2, LgBS90->unkA, LgBS90->unkE, 0x210, 0.0f);
            if (patrolPathStep(2, 0) != 0) {
                LgBV->unk154 = 0;
                LgBV->unk155 = 0;
                actorSetTargetSpeed(gCurrentActor, 0);
            }
            break;
        case 0x0:
            actorMoveWithinZone(0, LgBS90->unkA, LgBS90->unkE, 0x210, 0.0f);
            break;
        case 0x1D:
            actorApplyGravity();
            actorApplyVelocityCustom(gCurrentActor, 0.0f, LgBV->unkC0);
            break;
        case 0x37:
            if (LgBV->unk155 != 0) {
                LgBV->unk154 = 0x40;
            } else {
                func_8072DC7C(0xA);
            }
            break;
    }
    func_8072A450();
    if ((LgBS98->unk46 & 0x1000) && func_8072881C(0, LgBS90->unk28) != 0 && (state->unk0 == 1 || state->unk0 == 9 || state->unk0 == 0x68)) {
        func_8072881C(0x81, LgBS90->unk28);
    }
}

typedef struct R1C46aS90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x16];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xC];
    /* 0x34 */ u8 unk34;
} R1C46aS90;

#define R1S90 ((R1C46aS90 *)D_807FDC90)

extern Actor *gSpawnedActor;
void actorScriptStart(void *, s32);
void func_8070D8C0(Actor *, s32, u8);
void actorSetTargetSpeed(Actor *, s32);
s32 actorMoveWithinZone(u8, f32, f32, s32, f32);
s32 patrolPathStep(u8, s32);
s32 func_80724A20(void);
s32 currentActorTestClearFlag(void);
s32 actorSpawn(s32, s32);
void func_80613C48(Actor *, s16, f32, f32);
void actorCopyPoseAndScale(void *, void *, f32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);

void func_806C10A0(u8 paramA, u16 actionId, s16 scriptId) {
    f32 nodeY;

    if (!(R1V->unk60 & 0x10)) {
        func_806F0C18(gCurrentActor);
        D_807FDC98->unk46 |= 0x200;
        actorSetTargetSpeed(gCurrentActor, 0);
    }
    func_80724A20();
    switch (R1V->unk154) {
        case 5:
            actorMoveWithinZone(0, 0.0f, 0.0f, 2, 0.0f);
        case 0:
            if (currentActorTestClearFlag()) {
                R1V->unk154 = 0x12;
                R1V->unk155 = 0;
            }
            break;
        case 2:
            actorMoveWithinZone(2, R1S90->unkA, R1S90->unkE, 0, 0.0f);
            patrolPathStep(2, 0);
            break;
        case 0x12:
            switch (R1V->unk155) {
                case 0:
                    func_8070D8C0(gCurrentActor, actionId, paramA);
                    actorScriptStart(gCurrentActor, scriptId);
                    R1V->unk155++;
                    break;
                case 2:
                    if (!(R1V->unk60 & 0x2000000)) {
                        func_80613C48(gCurrentActor, 0xE4, 0.0f, 2.0f);
                        actorSpawn(0xE1, 0x98);
                        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.21f);
                        actorGetNodePos(gCurrentActor, 1, &gSpawnedActor->x, &nodeY, &gSpawnedActor->z);
                        actorScriptStart(gSpawnedActor, 0x298);
                        ((R1C46aActor *)gSpawnedActor)->unk11C = R1V;
                        R1V->unk155++;
                    }
                    break;
                case 3:
                    R1V->unk80 += 0.5;
                    break;
            }
            break;
    }
}

void camEndPath(void *);
void actorDespawn(Actor *);
extern void *gCamActor;

void func_806C1300(void) {
    switch (R1V->unk155) {
        case 1:
            R1V->unk11C->unk60 &= ~4;
            R1V->unk155++;
            break;
        case 3:
            camEndPath(gCamActor);
            R1V->unk11C->unk154 = 0x40;
            actorDespawn(gCurrentActor);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_8067ACB4(Actor *);
s32 playerSelectMoveTier(Actor *, f32, f32, u8, s16);

void func_806C13AC(s16 threshold, s16 animLow, s16 animMid, s16 animHigh, s16 animMax) {
    s16 val;
    s32 ret;

    if (!(R1V->unk60 & 0x10)) {
        R1V->unk6A |= 1;
        func_8067ACB4(gCurrentActor);
        R1V->unkCC = 1;
    }
    val = ret = playerSelectMoveTier(gCurrentActor, R1V->unkB8, R1S90->unk26, R1S90->unk34, threshold);
    if (ret != R1S90->unk34) {
        switch (ret) {
            case 0:
            case 1:
            case 2:
                func_80613C48(gCurrentActor, animLow, 0.0f, 6.0f);
                break;
            case 3:
                func_80613C48(gCurrentActor, animMid, 0.0f, 6.0f);
                break;
            case 4:
                func_80613C48(gCurrentActor, animHigh, 0.0f, 6.0f);
                break;
            case 5:
                func_80613C48(gCurrentActor, animMax, 0.0f, 6.0f);
                break;
        }
        R1S90->unk34 = val;
    }
}

s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);

void func_806C151C(u16 actionId, u8 actionParam, s16 flagId) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 near;

    dx = D_807FBB4C->x - R1V->unk7C;
    dy = D_807FBB4C->y - R1V->unk80;
    dz = D_807FBB4C->z - R1V->unk84;
    near = 0;
    if (dx * dx + dy * dy + dz * dz < 4900.0f) {
        near = 1;
    }
    if ((u8)near) {
        if (!flagGet(flagId, 2)) {
            func_8070D8C0(gCurrentActor, actionId, actionParam);
            flagSet(flagId, 1, 2);
        }
    }
}

void func_806C15E8(void) {
    D_807FDC98->unk46 |= 0x1000;
    R1V->unk146 = 0;
    actorSetTargetSpeed(gCurrentActor, 0);
    R1V->unkCC = 1;
}

void behaviourFrameBegin(void);
extern s32 gCurrentMap;
void actorScriptedCommandUpdate(void);

void func_806C1640(void) {
    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
        if (gCurrentMap == 0x4C) {
            R1V->unk4->unk34 *= 0.8;
            R1V->unk4->unk38 *= 0.8;
            R1V->unk4->unk3C *= 0.8;
        }
    }
    func_806BF920();
    if (R1V->unk60 & 0x10000000) {
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u32 gFrameCounter;
extern u8 D_8071FB08;
extern u8 D_807200D4;
void func_80714998(s32);
void func_807149B8(s32);
void func_8071498C(void *);
void effectShrinkFadeMatrixUpdate(void);
void func_80714950(s32);
void effectLightPulseOscillate(void);
void func_80714C08(void *, f32, void *, s32, s32);
void func_806F1048();
s32 randomNonNegative(void);
void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);

void func_806C1734(void) {
    R1C46aSub4 *sub;
    s32 rnd;
    R1C46aInner *inner;
    s16 animFrame;
    u8 nodeIndex;

    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
    }
    func_806BF920();
    if (R1V->unk60 & 0x10000000) {
        animFrame = R1V->unk4->unk0->unk4;
        actorScriptedCommandUpdate();
        sub = R1V->unk4;
        if (*sub->unk8 == 0) {
            inner = sub->unk0;
            switch (inner->unk10) {
                case 0xBB:
                    if (30.0f < R1V->unkC0 && !(gFrameCounter & 3)) {
                        func_80714998(2);
                        func_807149B8(1);
                        func_8071498C(effectShrinkFadeMatrixUpdate);
                        func_80714C08(&D_8071FB08, 0.8f, gCurrentActor, 5, 0);
                    }
                    break;
                case 0x114:
                    if (0.0f == inner->unk24) {
                        func_806F1048(gCurrentActor);
                    }
                    break;
                case 0xEA:
                    if (R1V->unk155 != 0 && animFrame >= 10) {
                        R1V->unk155 = 0;
                        projectileGetTargetCoords(gCurrentActor, 7);
                        projectileSpawnNodeEntry(0x29, 0xCA, 0.4f, R1V->unkE6, 250.0f, 0.0f, gCurrentActor);
                    }
                    break;
                case 0x112:
                    if (animFrame >= 0x44 && animFrame < 0x64 && (gFrameCounter % 3) == 0) {
                        rnd = randomNonNegative() >> 15;
                        nodeIndex = (rnd % 0x7FFF) % 2;
                        func_807149B8(1);
                        func_80714950(0x50);
                        func_8071498C(effectLightPulseOscillate);
                        func_80714C08(&D_807200D4, 0.5f, gCurrentActor, nodeIndex + 9, 2);
                    }
                    break;
            }
        }
    } else {
        func_806C10A0(0, 3, 0x3D8);
        if (flagGet(4, 0)) {
            func_806C151C(3, 3, 0);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_80724CA4(s32, s32);
void func_806F09F0(Actor *, u16);
void func_807149C8(s32, s32, s32, s32);
void func_80724E48(u8);
extern Actor *D_807FDC94;
extern u8 D_8071FBA0;

void func_806C19F4(void) {
    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
        R1V->unk140->unk14 = 180.0f;
        func_80724CA4(2, 1);
        func_806F09F0(gCurrentActor, R1V->unk5A);
    }
    if (R1V->unk60 & 0x10000000) {
        actorScriptedCommandUpdate();
        if (R1V->unk4->unk0->unk10 == 0x1A4) {
            func_807149B8(1);
            func_807149C8(0x96, 0xFF, 0xFF, 0xFF);
            func_80714C08(&D_8071FBA0, 0.7f, gCurrentActor, 5, 0);
        }
        func_80724E48(D_807FDC94 == D_807FBB4C ? 5 : 7);
    } else {
        func_806C10A0(2, 6, 0x3D9);
        func_80724E48(0);
        func_806C151C(6, 1, 6);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_8071FB34;

void func_806C1B50(void) {
    u8 kind;
    u32 thr;

    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
        func_806F09F0(gCurrentActor, R1V->unk5A);
    }
    func_806BF920();
    if (R1V->unk60 & 0x10000000) {
        actorScriptedCommandUpdate();
        if ((R1V->unk60 & 4) && R1V->unk155 != 0) {
            switch (R1V->unk4->unk0->unk10) {
                case 0x23E:
                    kind = 0xD;
                    thr = 7;
                    break;
                case 0x23F:
                    kind = 0xE;
                    thr = 7;
                    break;
                case 0x240:
                    kind = 0x11;
                    thr = 3;
                    break;
                default:
                    goto done;
            }
            if ((f32)thr < R1V->unk4->unk0->unk4) {
                func_80714C08(&D_8071FB34, 0.5f, gCurrentActor, kind, 0);
                R1V->unk155 = 0;
            }
        }
    } else {
        func_806C10A0(2, 4, 0x3DB);
        func_806C151C(4, 1, 8);
    }
done:
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void controllerAnimLoadStateAsset();
void renderCallbacksRegister(void *, void *, s32);
void gfxBuildScanlineNoise();

void func_806C1CCC(void) {
    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        R1V->unkC8 = -2000.0f;
        R1V->unkC4 = -200.0f;
        func_806C15E8();
        func_80724CA4(2, 1);
        if (gCurrentMap == 0x4C) {
            controllerAnimLoadStateAsset(gCurrentActor, 0xE);
        }
        func_806F09F0(gCurrentActor, R1V->unk5A);
    }
    if (R1V->unk60 & 0x10000000) {
        actorScriptedCommandUpdate();
        if (R1V->unk60 & 4) {
            if (R1V->unk4->unk0->unk10 == 0x2C4 && 25.0f < R1V->unk4->unk0->unk4) {
                renderCallbacksRegister(gfxBuildScanlineNoise, 0, 3);
            }
        }
        func_80724E48(D_807FDC94 == D_807FBB4C ? 5 : 7);
    } else {
        func_806C10A0(2, 5, 0x3DA);
        func_80724E48(0);
        func_806C151C(5, 1, 0xF);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_8071FF58[];
extern u8 D_80720B58[];
void effectWobbleScaleUpdate();
void effectScatterFallUpdate();
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
void func_807149FC(s32);

void func_806C1E44(void) {
    s32 i;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetFinished(gCurrentActor, 0, 1);
        switch (gCurrentMap) {
            case 0x14:
                gCurrentActor->unk130 = 0xFF;
                gCurrentActor->unk131 = 0xFF;
                if (flagGet(0x4C, 0) == 0) {
                    animSetFrameAndSubframe(gCurrentActor, 0, 1, 0);
                    actorScriptStart(gCurrentActor, 0x2BD);
                    gCurrentActor->state = 0;
                    gCurrentActor->unk155[0] = 0;
                } else {
                    gCurrentActor->state = 0x27;
                    gCurrentActor->unk155[0] = 0;
                    gCurrentActor->unk155[0] = 4;
                }
                break;
            case 0x26:
                animSetFrameAndSubframe(gCurrentActor, 0, 0, 0);
                gCurrentActor->state = 5;
                gCurrentActor->unk155[0] = 0;
                break;
        }
    }
    switch (gCurrentActor->state) {
        case 0:
            func_80724A20();
            switch (gCurrentActor->unk155[0]) {
                case 1:
                    D_807FDC90->timer = 3;
                    gCurrentActor->unk155[0] = 2;
                case 2:
                    if (!(gFrameCounter & 7)) {
                        if (D_807FDC90->timer != 0) {
                            D_807FDC90->timer--;
                            if (D_807FDC90->timer == 0) {
                                gCurrentActor->unk155[0] = 0;
                            }
                            func_80714998(2);
                            func_807149B8(1);
                            func_807149FC(0x28);
                            func_8071498C(effectWobbleScaleUpdate);
                            func_80714C08(D_8071FF58, 0.05f, gCurrentActor, 1, 0);
                        }
                    }
            }
            break;
        case 0x27:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    animSetFrameAndSubframe(gCurrentActor, 0, 0, 0);
                    actorScriptStart(gCurrentActor, 0x2BE);
                    gCurrentActor->unk155[0] = 1;
                    break;
                case 3:
                    i = 0;
                    do {
                        func_807149B8(1);
                        func_807149FC(0x28);
                        func_8071498C(effectScatterFallUpdate);
                        func_80714950(gCurrentActor->yaw);
                        func_80714C08(D_80720B58, 0.7f, gCurrentActor, 1, 0);
                        i++;
                    } while (i != 10);
                    gCurrentActor->unk155[0]++;
                    break;
            }
            break;
        case 5:
            func_80724A20();
            func_806C151C(0xA, 1, 7);
            func_806C13AC(4, 0x4F1, 0x4F7, 0x4F7, 0x4F7);
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->state = 0x12;
                gCurrentActor->unk155[0] = 0;
            }
            break;
        case 0x12:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2BF);
                    animSetFrameAndSubframe(gCurrentActor, 0, 2, 0);
                    actorSetTargetSpeed(gCurrentActor, D_807FDC9C->unkC);
                    gCurrentActor->unk155[0] = 1;
                    break;
                case 2:
                    actorMoveWithinZone(2, (f32)D_807FDC90->targetX, (f32)D_807FDC90->targetZ, 0, 0.0f);
                    patrolPathStep(2, 0);
                    break;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_807502F4;
extern s16 gCsModelIds[];
extern u8 gPlayerCharacterId;
extern s32 D_807FBDC8[];
extern u8 D_8071FC40;
void effectWobbleRiseUpdate(void);
void func_8072A920(s16, s32, f32, f32, f32, s32, f32, f32, s32);
void modelSlotGetNodePos(s16, s32, s32, f32 *, f32 *, f32 *);
s16 mathAngleEaseToward(s16, s16, f32);
void zoneEntryGetPosition(s32, s32, f32 *, f32 *, f32 *);
void func_8072E1A4(s32, void *);
s32 actorIsTargetWithinDistance(s32);
s32 func_8072881C(s32, void *);
void func_80714CC0(void *, f32, f32, f32, f32);
void camStartPath(void *, s32, s32);
s32 camIsCutsceneActive(void);
void func_8070E8DC(s32);

typedef struct R1C46bActor {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ u8 padC8[0x20];
    /* 0xE8 */ s16 unkE8;
} R1C46bActor;

typedef struct R1C46bState9C {
    /* 0x00 */ u8 pad0[0x13];
    /* 0x13 */ u8 unk13;
} R1C46bState9C;

void func_806C226C(void) {
    s16 i;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        ((R1C46bActor *)gCurrentActor)->unkC4 = D_807502F4;
        gCurrentActor->y = gCurrentActor->unkA4;
        gCurrentActor->unk12A = 0x4B0;
        if (flagGet(0x9E, 0) != 0) {
            if (((R1C46bState9C *)D_807FDC9C)->unk13 == 0x16) {
                gCurrentActor->state = 0x28;
                gCurrentActor->unk155[0] = 0;
            } else {
                gCurrentActor->state = 0x40;
            }
        } else if (((R1C46bState9C *)D_807FDC9C)->unk13 == 0x16) {
            gCurrentActor->state = 0x40;
        }
    }
    for (i = 0; i < D_807FBDC4; i++) {
        if (D_807FBDC8[i] == 3) {
            actorScriptStart(gCurrentActor, 0x2A3);
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155[0] = 0;
            camStartPath(gCurrentActor, 0x16, 1);
            flagSet(0x9E, 1, 0);
        }
    }
    switch (gCurrentActor->state) {
        case 0x27:
            if (gCurrentActor->contactFlags & 4) {
                func_8072A920(2, 0, (f32)D_807FDC90->targetX, (f32)D_807FDC90->targetY, (f32)D_807FDC90->targetZ, 0x46, 30.0f, 100.0f, 0);
                if (((randomNonNegative() >> 15) % 1000) >= 0x3A3) {
                    func_8071498C(effectWobbleRiseUpdate);
                    func_807149B8(1);
                    func_807149FC(-1);
                    func_80714CC0(&D_8071FC40, 0, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                }
            } else {
                if ((gCurrentActor->contactFlags ^ gCurrentActor->prevContactFlags) & 1) {
                    actorScriptStart(gCurrentActor, 0x2A4);
                }
                actorMoveWithinZone(2, (f32)D_807FDC90->targetX, (f32)D_807FDC90->targetZ, 0x200, 0.0f);
                if (((R1C46bActor *)gCurrentActor)->unkC0 < -10.0f) {
                    ((R1C46bActor *)gCurrentActor)->unkE8 = mathAngleEaseToward(((R1C46bActor *)gCurrentActor)->unkE8, 0x400, 10.0f);
                }
            }
            patrolPathStep(2, 0);
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->state = 0x40;
            }
            break;
        case 0x28:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    zoneEntryGetPosition(2, 3, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
                    actorScriptStart(gCurrentActor, 0x2A6);
                    ((R1C46bActor *)gCurrentActor)->unkE8 = 0;
                    gCurrentActor->unk155[0]++;
                case 1:
                    if (actorIsTargetWithinDistance(0xC8) != 0) {
                        gCurrentActor->unk155[0]++;
                        if (flagGet(0xC1, 0) != 0) {
                            if (gPlayerCharacterId == 0 && flagGet(0xA5, 0) == 0) {
                                func_8070D8C0(gCurrentActor, 0x1C, 2);
                            } else if (gPlayerCharacterId != 0) {
                                func_8070D8C0(gCurrentActor, 0x1C, 0);
                            }
                        } else if (gPlayerCharacterId == 0) {
                            camStartPath(gCurrentActor, 0x1E, 1);
                            func_8070E8DC(1);
                            func_8070D8C0(gCurrentActor, 0x1C, 1);
                            gCurrentActor->unk155[0] = 0x63;
                        } else {
                            func_8070D8C0(gCurrentActor, 0x1C, 0);
                        }
                    }
                    break;
                case 2:
                    if (flagGet(0xC1, 0) == 0 && actorIsTargetWithinDistance(0x12C) == 0) {
                        gCurrentActor->unk155[0] = 1;
                    }
                    break;
                case 0x63:
                    if (camIsCutsceneActive() == 0 && !(gCurrentActor->flags & 0x2000000)) {
                        func_8070D8C0(gCurrentActor, 0x1C, 2);
                        gCurrentActor->unk155[0] = 3;
                    }
                    break;
            }
            modelSlotGetNodePos(gCsModelIds[58], 1, 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
            func_8072E1A4(0xA, D_807FDC94);
            break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void effectSpawnActorBone(Actor *, u8, f32);

void actorPlaySoundSpawnBoneEffects(void) {
    f32 scale = gCurrentActor->unk4->unk38 / 0.15;

    sfxPlayActorSound(gCurrentActor, 0x114, 0x50, 0, 0, 0xFF, 0.5f, 0);
    if (gFrameCounter & 1) {
        effectSpawnActorBone(gCurrentActor, 1, scale);
        effectSpawnActorBone(gCurrentActor, 3, scale);
    } else {
        effectSpawnActorBone(gCurrentActor, 2, scale);
        effectSpawnActorBone(gCurrentActor, 4, scale);
    }
}

void effectSpawnOctagonRing(f32, f32, f32, f32);

typedef struct R1C46bInner {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ f32 unk4;
} R1C46bInner;

typedef struct R1C46bSub4 {
    /* 0x0 */ R1C46bInner *unk0;
} R1C46bSub4;

void actorSpawnOctagonRingsByTimer(void) {
    f32 v;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 s;
    f32 pad;
    s16 i;

    v = ((R1C46bSub4 *)gCurrentActor->unk4)->unk0->unk4;
    if (v > 83.0f) {
        actorPlaySoundSpawnBoneEffects();
        v = ((R1C46bSub4 *)gCurrentActor->unk4)->unk0->unk4;
    }
    if (v > 2.0f && v < 90.0f) {
        i = 1;
        if (gFrameCounter % 6 == 0) {
            s = (v / 70.0 > 1.0) ? 1.0 : v / 70.0;
            do {
                actorGetNodePos(gCurrentActor, i, &nodeX, &nodeY, &nodeZ);
                effectSpawnOctagonRing((s * 0.3 < 0.15) ? 0.15 : s * 0.3, nodeX, nodeY + 3.0f, nodeZ);
                i++;
            } while (i < 5);
        }
    }
}

void func_807149A8(s32);
void func_80714944(s32);
void effectLinearFadeAlphaUpdate();

void effectSpawnColoredParticleAtPoint(u8 r, u8 g, u8 b, f32 x, f32 y, f32 z, void *particleGfx, f32 scale) {
    func_807149A8(1000);
    func_80714998(0xFF);
    func_80714944(((randomNonNegative() >> 15) % 0x7FFF) % 11);
    func_807149C8(r, g, b, 0xFF);
    func_8071498C(effectLinearFadeAlphaUpdate);
    func_80714950(2);
    func_80714CC0(particleGfx, scale * 0.2, x, y, z);
}

extern u8 D_80747B00[];

void actorSpawnParticlesAlongNodeLoop(u8 startNode, u8 endNode, u8 colorIndex, void *particleGfx) {
    f32 scale;
    f32 node1X;
    f32 node1Y;
    f32 node1Z;
    f32 node2X;
    f32 node2Y;
    f32 node2Z;
    f32 frac;
    s16 i;
    s16 j;

    scale = gCurrentActor->unk4->unk38 / 0.15;
    scale = scale / 1.5;
    for (i = startNode; i <= endNode; i++) {
        for (j = 0; j < 3.0; j++) {
            frac = (f32)j / 3.0;
            actorGetNodePos(gCurrentActor, i, &node1X, &node1Y, &node1Z);
            if (i < endNode) {
                actorGetNodePos(gCurrentActor, i + 1, &node2X, &node2Y, &node2Z);
            } else {
                actorGetNodePos(gCurrentActor, startNode, &node2X, &node2Y, &node2Z);
            }
            effectSpawnColoredParticleAtPoint(D_80747B00[colorIndex * 3], D_80747B00[colorIndex * 3 + 1], D_80747B00[colorIndex * 3 + 2], (node2X - node1X) * frac + node1X, (node2Y - node1Y) * frac + node1Y, (node2Z - node1Z) * frac + node1Z, particleGfx, scale);
        }
    }
}

extern u8 D_8071FFA0[];

void actorSpawnParticlesAlongNodeRanges(void) {
    actorSpawnParticlesAlongNodeLoop(1, 0xB, 6, D_8071FFA0);
    actorSpawnParticlesAlongNodeLoop(0x20, 0x30, 6, D_8071FFA0);
    actorSpawnParticlesAlongNodeLoop(0xC, 0x16, 2, D_8071FFA0);
    actorSpawnParticlesAlongNodeLoop(0x17, 0x1F, 2, D_8071FFA0);
}

typedef struct LgC2DF4Inner {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} LgC2DF4Inner;

typedef struct LgC2DF4Sub4 {
    /* 0x00 */ LgC2DF4Inner *unk0;
    /* 0x04 */ u8 pad4[0x34];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x28];
    /* 0x64 */ u16 unk64;
} LgC2DF4Sub4;

typedef struct LgC2DF4State {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x2A];
    /* 0x2C */ u8 unk2C;
} LgC2DF4State;

typedef struct LgC2DF4Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgC2DF4Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x40];
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 unkCC;
    /* 0x0CD */ u8 padCD[0x19];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x40];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x14];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145;
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x26];
    /* 0x17C */ LgC2DF4State *unk17C;
} LgC2DF4Actor;

typedef struct LgC2DF4S9C {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 unk14;
} LgC2DF4S9C;

#define LgV ((LgC2DF4Actor *)gCurrentActor)

void controllerAnimFree(Actor *);
void controllerAnimInit(Actor *, u16);
ActorSub140 *actorSub140CreateFromModel(Actor *);
void actorSetUniformScale(Actor *, f32);
void func_80728950(s32);
void currentActorAnimSetFrame(s32, s32);
void actorGetNodePosOrPosition(Actor *, s32 *, s32 *, s32 *);
void effectSpawnActorBoneEffects(s32);
void effectSpawnChildAtNode(s32, s16, s16);
void effectSpawnBoneDefault(Actor *, s16, f32, f32, f32, f32, s32);
void effectSpawnActorScale(Actor *);
void effectActorCheckGroundScaleSpawn(Actor *);
void sfxStopSlotSound(Actor *, s32);
void actorSetGroupState(u8, u8);
void commandQueuePush(Actor *, s16, s16, s16, s32, s32, s32, s32, s32);
void effectSpawnJointBeam(s32, s32, s32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
extern s32 D_807FBB68;

void func_806C2DF4(void) {
    LgC2DF4State *state;
    s32 nodePosX;
    s32 nodePosY;
    s32 nodePosZ;
    f32 scale;
    s32 rnd;

    state = LgV->unk17C;
    behaviourFrameBegin();
    if (!(LgV->unk60 & 0x10)) {
        scale = LgV->unk4->unk38;
        controllerAnimFree(gCurrentActor);
        controllerAnimInit(gCurrentActor, state->unk0);
        LgV->unk140 = actorSub140CreateFromModel(gCurrentActor);
        LgV->unk146 = 0;
        LgV->unk12A = 0xFA0;
        D_807FDC98->unk46 |= 0x20;
        LgV->unk60 &= 0xFEFFFFFF;
        LgV->unk144 = 1;
        switch (state->unk0) {
            case 0x21:
                if (gCurrentMap == 0x98 || gCurrentMap == 0x1C) {
                    LgV->unk60 |= 0x400;
                    D_807FDC98->unk46 |= 0x100;
                }
            case 0x22:
            case 0x23:
                func_80724CA4(2, 1);
                break;
            case 0x1:
            case 0x4:
            case 0x6:
            case 0x9:
            case 0xC:
                D_807FDC98->unk46 |= 0x1000;
                LgV->unk60 |= 0x400;
                LgV->unkCC = 1;
                LgV->unk60 |= 0x1000;
                func_80724CA4(2, 1);
                func_806F0C18(gCurrentActor);
                break;
            case 0x17:
                LgV->unkCC = 1;
            case 0x18:
            case 0x49:
                state->unk2C = 9;
            case 0x6B:
            case 0x88:
                LgV->unk60 |= 0x1000;
            case 0x38:
            case 0x3A:
            case 0x3C:
            case 0x58:
                D_807FDC98->unk46 |= 0x100;
            case 0x27:
            case 0x2D:
            case 0x66:
                LgV->unk60 |= 0x400;
                break;
            case 0x31:
                if (D_807FBB68 & 2) {
                    animSetLoopLimit(gCurrentActor, 1, 1);
                    animSetFinished(gCurrentActor, 1, 1);
                    animSetFrameAndSubframe(gCurrentActor, 1, 1, 0);
                }
                D_807FDC98->unk46 |= 0x1000;
                D_807FDC98->unk46 |= 0x100;
                LgV->unk60 |= 0x400;
                break;
            case 0x12:
                LgV->unkCC = 1;
                if (!(D_807FBB68 & 2)) {
                    LgV->unk146 = 1;
                }
                break;
            case 0x80:
                LgV->unk60 |= 0x800000;
                D_807FDC98->unk46 |= 0x100;
                LgV->unk60 |= 0x400;
                break;
            case 0x37:
                LgV->unk60 |= 0x400;
                animSetLoopLimit(gCurrentActor, 0, 1);
                animSetFinished(gCurrentActor, 0, 1);
                animSetFrameAndSubframe(gCurrentActor, 0, ((LgC2DF4S9C *)D_807FDC9C)->unk14, 0);
                break;
            case 0x45:
                scale *= 10.0f;
            case 0x3D:
                LgV->unkCC = 2;
                LgV->unk60 |= 0x400;
                break;
            case 0x3B:
                LgV->unkC8 = -10.0f;
                LgV->unk60 |= 0x400;
                break;
            case 0x25:
                LgV->unkC8 = -2000.0f;
                LgV->unk60 |= 0x400;
                LgV->unk146 = -1;
                break;
            case 0x11:
                D_807FDC98->unk46 |= 0x1000;
                if (gCurrentMap == 0x4C) {
                    LgV->unk146 = 0;
                } else {
                    LgV->unk146 = 2;
                }
            case 0x13:
            case 0xDC:
            case 0xDD:
            case 0xDE:
            case 0xDF:
            case 0xE3:
                LgV->unk60 |= 0x400;
                break;
            case 0xE2:
                scale *= 8.0f;
                actorSetUniformScale(gCurrentActor, scale);
                LgV->unkE8 = 0xC8;
                func_806BFBB4();
                actorSpawnParticlesAlongNodeRanges();
                break;
            case 0x68:
                if (gCurrentMap == 0xCD) {
                    LgV->unk146 = 1;
                } else {
                    LgV->unk146 = 5;
                }
            case 0x70:
                D_807FDC98->unk46 |= 0x1000;
                LgV->unkCC = 1;
            case 0x69:
                LgV->unk60 |= 0x400;
                LgV->unk60 |= 0x1000;
                break;
        }
        actorSetUniformScale(gCurrentActor, scale);
        if (gCurrentMap == 0xD0) {
            D_807FDC98->unk46 |= 0x100;
            LgV->unk60 &= 0xFEFFFFFF;
        }
    }
    actorGetNodePosOrPosition(gCurrentActor, &nodePosX, &nodePosY, &nodePosZ);
    func_806BF920();
    actorScriptedCommandUpdate();
    LgV->unk6A = 0;
    LgV->unk6C = 0;
    if (D_807FDC94 != D_807FBB4C) {
        func_80724E48(7);
    }
    switch (LgV->unk4->unk0->unk10) {
        case 0x3EA:
            LgV->unk146 = 0;
            break;
        case 0x8E:
        case 0x320:
        case 0x32F:
        case 0x341:
        case 0x3CC:
        case 0x52F:
        case 0x63A:
            if (D_807FDC98->unk46 & 0x1000) {
                D_807FDC98->unk46 &= ~0x1000;
                func_80728950(0);
                if (state->unk0 == 0x68) {
                    func_80728950(1);
                }
            }
            break;
        case 0x530:
            currentActorAnimSetFrame(1, 0);
            break;
        case 0x531:
        case 0x62C:
            if (!(D_807FDC98->unk46 & 0x1000)) {
                D_807FDC98->unk46 |= 0x1000;
                currentActorAnimSetFrame(0, 0);
            }
            break;
        case 0x92:
            if (!(D_807FDC98->unk46 & 0x1000) && LgV->unk4->unk0->unk4 >= 127.0f) {
                D_807FDC98->unk46 |= 0x1000;
                currentActorAnimSetFrame(0, 0);
            }
            break;
        case 0x434:
            if (LgV->unk4->unk0->unk4 < 60.0f) {
                break;
            }
        case 0x436:
            if (!(gFrameCounter & 1)) {
                func_807149A8(0x7D0);
                func_80714998(3);
                func_807149C8(0x32, 0x32, 0x32, 0xFF);
                effectSpawnBoneDefault(gCurrentActor, 1, 1.3f, 0, 0, 0, -0x50);
            }
            break;
        case 0x4DA:
        case 0x4DB:
        case 0x4DC:
        case 0x4DD:
        case 0x4DE:
            if (!(gFrameCounter & 3)) {
                func_807149B8(1);
                func_8071498C(effectShrinkFadeMatrixUpdate);
                func_80714C08(&D_8071FB08, 0.6f, gCurrentActor, 2, 0);
            }
            break;
        case 0x4C7:
            if (LgV->unk4->unk0->unk4 >= 23.0f && LgV->unk155 != 0) {
                LgV->unk155 = 0;
                projectileGetTargetCoords(gCurrentActor, 2);
                projectileSpawnNodeEntry(0x29, 0xCB, 0.4f, LgV->unkE6, 400.0f, 0, gCurrentActor);
            }
            break;
        case 0x54D:
            if (LgV->unk4->unk0->unk24 == 0) {
                LgV->unk154 = 0x40;
            } else if (LgV->unk4->unk0->unk4 < 210.0f) {
                effectSpawnActorBoneEffects(2);
            } else if (LgV->unk4->unk0->unk4 < 235.0f) {
                effectSpawnActorBoneEffects(3);
            }
            break;
        case 0x549:
            if (LgV->unk4->unk0->unk4 > 65.0f && LgV->unk4->unk0->unk4 < 101.0f) {
                rnd = randomNonNegative();
                effectSpawnChildAtNode(2, (rnd >> 15) % 2048 + LgV->unkE6 - 0x400, (randomNonNegative() >> 15) % 2048);
            }
            break;
        case 0x498:
            if (LgV->unk4->unk0->unk4 < 2.0f) {
                effectSpawnActorScale(gCurrentActor);
            }
            effectActorCheckGroundScaleSpawn(gCurrentActor);
            break;
        case 0x43E:
            actorSpawnOctagonRingsByTimer();
            break;
        case 0x43D:
        case 0x440:
            actorPlaySoundSpawnBoneEffects();
            break;
        case 0x43F:
            if (LgV->unk4->unk0->unk4 < 68.0f) {
                actorPlaySoundSpawnBoneEffects();
            }
            if (65.0f < LgV->unk4->unk0->unk4) {
                sfxStopSlotSound(gCurrentActor, 0);
            }
            break;
        case 0x52E:
            if (LgV->unk4->unk0->unk4 < 2.0f) {
                func_80714C08(&D_8071FB34, 1.5f, gCurrentActor, 6, 0);
            }
            break;
        case 0x527:
        case 0x528:
            actorSetGroupState(3, 0xA);
            break;
        case 0x52A:
            actorSetGroupState(3, 3);
            break;
    }
    if (gCurrentMap == 0xD0 && (LgV->unk60 & 0x1000)) {
        commandQueuePush(gCurrentActor, LgV->unk7C, LgV->unk80 + 30.0f, LgV->unk84, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    }
    if (LgV->unk4->unk64 == 0x22A) {
        if ((randomNonNegative() >> 15) % 100 >= 0x47 || LgV->unk155 != 0) {
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            sfxPlayAtPositionPooled(LgV->unk7C, LgV->unk80, LgV->unk84, 0x8A, 0x64, 0x7F, 0x28, 0, 0.3f, 0);
            LgV->unk60 |= 4;
        } else {
            LgV->unk60 &= ~4;
            sfxStopSlotSound(gCurrentActor, 0);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 D_80750AC8;
void csModelStateSetFirstByte(s32, s32);

void func_806C3A8C(void) {
    s32 dist;
    f32 pad0;
    f32 pad1;
    u8 flag1;
    u8 flag2;
    u8 flag3;
    u8 flag4;

    dist = (D_807FBB4C->x - gCurrentActor->x) * (D_807FBB4C->x - gCurrentActor->x) + (D_807FBB4C->y - gCurrentActor->y) * (D_807FBB4C->y - gCurrentActor->y) + (D_807FBB4C->z - gCurrentActor->z) * (D_807FBB4C->z - gCurrentActor->z);
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk15E = 0x19;
        func_8067ACB4(gCurrentActor);
        if (flagGet(0x1E, 2) == 0) {
            camStartPath(gCurrentActor, 0x14, 1);
            flagSet(0x1E, 1, 2);
        }
        if (flagGet(0xBF, 0) == 0) {
            if (flagGet(0xBA, 0) && flagGet(0xBB, 0) && flagGet(0xBC, 0) && flagGet(0xBD, 0) && flagGet(0xBE, 0)) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155[0] = 0;
            } else if (flagGet(0xBA, 0) || flagGet(0xBB, 0) || flagGet(0xBC, 0) || flagGet(0xBD, 0) || flagGet(0xBE, 0)) {
                gCurrentActor->state = 0x1F;
                gCurrentActor->unk155[0] = 0;
            } else {
                gCurrentActor->state = 0x1E;
                gCurrentActor->unk155[0] = 0;
            }
        } else {
            gCurrentActor->state = 0x20;
            gCurrentActor->unk155[0] = 0;
        }
    }
    actorScriptedCommandUpdate();
    switch (gCurrentActor->state) {
        case 0x1E:
            switch (gCurrentActor->unk155[0]) {
                case 0:
                    if ((u8)(dist < 0xF424)) {
                        gCurrentActor->unk155[0]++;
                    }
                    break;
                case 1:
                    if ((u8)(dist < 0x2710)) {
                        actorScriptStart(gCurrentActor, 0x3A4);
                        func_8070D8C0(gCurrentActor, 0x17, 0);
                        gCurrentActor->unk155[0]++;
                    }
                    break;
            }
            break;
        case 0x1F:
            if ((u8)(dist < 0x2710) && gCurrentActor->unk155[0] == 0) {
                flag4 = flagGet(0xBD, 0);
                flag3 = flagGet(0xBC, 0);
                flag2 = flagGet(0xBB, 0);
                flag1 = flagGet(0xBA, 0);
                D_80750AC8 = flagGet(0xBE, 0) + flag1 + flag2 + flag3 + flag4;
                func_8070D8C0(gCurrentActor, 0x17, 2);
                gCurrentActor->unk155[0]++;
            }
            break;
        case 0x20:
            if ((u8)(dist < 0x2710) && gCurrentActor->unk155[0] == 0 && camIsCutsceneActive() == 0) {
                camStartPath(gCurrentActor, 0x18, 1);
                func_8070D8C0(gCurrentActor, 0x17, 3);
                gCurrentActor->unk155[0]++;
            }
            break;
        case 0x27:
            if (camIsCutsceneActive() == 0) {
                switch (gCurrentActor->unk155[0]) {
                    case 0:
                        camStartPath(gCurrentActor, 0x17, 1);
                        func_8070E8DC(1);
                        func_8070D8C0(gCurrentActor, 0x17, 1);
                        gCurrentActor->unk155[0]++;
                        break;
                    case 1:
                        if (!(gCurrentActor->flags & 0x2000000)) {
                            csModelStateSetFirstByte(0xE, 0xA);
                            gCurrentActor->state = 0x20;
                            gCurrentActor->unk155[0] = 0;
                        }
                        break;
                }
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
