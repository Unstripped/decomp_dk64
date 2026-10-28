#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
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

#define R1V ((R1C46aActor *)D_807FBB40)

void *func_80610FE8(s32);
void func_806C8220();
void func_806F22A8(Actor *, void *, s32 *);
void func_806F1EB0(Actor *, void *, s32 *);
void func_806F1C04(Actor *, void *, s32 *);

void func_806BF920(void) {
    u16 *state;
    s32 sp20;
    s32 sp1C;

    state = R1V->unk17C;
    sp20 = 0;
    if (!(R1V->unk60 & 0x10)) {
        sp1C = 0;
        switch (*state) {
            case 1:
            case 2:
            case 3:
                sp1C = 3;
                break;
            case 9:
            case 10:
            case 11:
                sp1C = 5;
                break;
            case 4:
            case 5:
                sp1C = 2;
                break;
        }
        if (sp1C != 0) {
            R1V->unk4->unk1C = func_80610FE8(0x100);
            func_806C8220(0, R1V->unk178, sp1C);
        }
    }
    switch (*state) {
        case 1:
        case 2:
        case 3:
            func_806F22A8(D_807FBB40, R1V->unk4->unk1C, &sp20);
            break;
        case 9:
        case 10:
        case 11:
            func_806F1EB0(D_807FBB40, R1V->unk4->unk1C, &sp20);
            break;
        case 4:
        case 5:
            func_806F1C04(D_807FBB40, R1V->unk4->unk1C, &sp20);
            break;
    }
    if (sp20 != 0) {
        R1V->unk4->unk1C[sp20 * 8] = 0;
    }
}

void func_806F0D68();
void func_806C7BAC();
void func_806F0C18(void *);
void func_806F10E8();
void func_80613214();
void func_80613CA8(Actor *, s16, f32, f32);

void func_806BFA8C(u16 arg0) {
    switch (arg0) {
        case 0xEA:
        case 0x23E:
        case 0x23F:
        case 0x240:
        case 0x4C7:
            R1V->unk155 = 1;
            break;
        case 0x112:
            func_806F0D68(D_807FBB40);
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
            func_806C7BAC(D_807FBB40, 0);
            break;
        case 0x114:
            func_806F0C18(D_807FBB40);
            func_806F10E8(D_807FBB40);
            break;
        case 0x2CF:
            func_80613214(D_807FBB40);
            func_80613CA8(D_807FBB40, 0x2CF, 0.0f, 0.0f);
            break;
    }
}

void func_8061421C();
void actorUpdateModelMatrix(Actor *, s32);
void func_80614A64(Actor *);

void func_806BFBB4(void) {
    func_8061421C(D_807FBB40);
    actorUpdateModelMatrix(D_807FBB40, 0);
    func_80614A64(D_807FBB40);
}

#ifdef NON_MATCHING
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

#define LgBV ((LgBFActor *)D_807FBB40)
#define LgBS90 ((LgBFS90 *)D_807FDC90)
#define LgBS98 ((LgBFS98 *)D_807FDC98)
#define LgBS9C ((LgBFS9C *)D_807FDC9C)

extern u8 D_807444EC;
extern s32 D_8076A0A8;
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
void func_80614D00(Actor *, f32, f32);
s32 func_80723020(void *, s32, s32, f32, f32, f32, s32);
void func_80723284(s32, u8);
void func_80723320(s32, s32);
void func_8072334C(s32, s32);
void func_80723484(s32);
void func_807238D4(s32, f32 *, f32 *, f32 *);
s32 func_80723C98();
void actorSetUniformScale(Actor *, f32);
void *spawnNodeActivate(s32, s32);
void func_8072881C(s32, void *);
void actorApplyGravity(void);
void func_8072A450(void);
void func_8072DC7C(s32);
void func_8072E320(f32);
s32 mathAngleLerp(s16, s16, f32);
void func_8068A858(void *, void *, void *);
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
s32 func_8072D13C(u8, s32);

void func_806BFBF4(void) {
    s16 j;
    s16 t;
    s16 i;
    LgBFCmd *cmd;
    LgBFState *state;
    f32 ratio;
    f32 ratio2;
    u8 *col;
    u8 node;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;

    state = LgBV->unk17C;
    if (!(LgBV->unk60 & 0x10)) {
        state->unk1A = 0;
        state->unk18 = 0;
        state->unk30 = 0xFF;
        state->unk33 = 0x12;
        state->unk22 = 0x64;
        func_806F09F0(D_807FBB40, (u16)D_807FBB40->unk58);
        actorSetTargetSpeed(D_807FBB40, 0);
        LgBV->unk60 &= 0xFFFDFFFF;
        if (D_8076A0A8 == 0x4C) {
            LgBV->unk60 &= 0xFEFFFFFF;
            LgBV->unk60 |= 0x400;
        }
        LgBV->unkC4 = D_807502E8;
    }
    if (D_807444EC != 1 && D_8076A0A8 != 0x4C && D_807FBB40->unk58 != 0xFE) {
        LgBV->unk60 &= 0xEFFFFFFF;
        return;
    }
    if (D_8076A0A8 == 0x4C) {
        func_8068A858(&LgBV->unk16A, &LgBV->unk16B, &LgBV->unk16C);
    }
    for (i = 0; i < D_807FBDC4; i++) {
        if (D_807FBB70.unk258[i] != 3) {
            continue;
        }
        cmd = (LgBFCmd *)D_807FBB70.unk278[i];
        switch (cmd->unk2) {
            case 25:
                state->unk33 = cmd->unk4;
                state->unk22 = cmd->unk6;
                break;
            case 24:
                state->unk30 = func_80723020(D_807FBB40, state->unk2D, 0, 0.0f, 0.0f, 0.0f, 0);
                state->unk31 = cmd->unk4;
                state->unk32 = cmd->unk6;
                func_80723284(state->unk30, state->unk2E / cmd->unk4);
                func_80723320(state->unk30, 1);
                func_8072334C(state->unk30, 1);
                break;
            case 23:
                t = cmd->unk4;
                state->unk2D = t;
                state->unk2E = cmd->unk6;
                state->unk2F = func_80723020(D_807FBB40, t & 0xFF, 0, 0.0f, 0.0f, 0.0f, 0);
                func_80723284(state->unk2F, state->unk2E);
                func_80723320(state->unk2F, 1);
                func_8072334C(state->unk2F, 1);
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
                actorScriptStart(D_807FBB40, D_80747750[cmd->unk4]);
                if (cmd->unk6 != 0) {
                    func_80614D00(D_807FBB40, cmd->unk6 / 100.0, 0.0f);
                }
                break;
            case 3:
                if (LgBV->unk4->unk64 != 0) {
                    actorScriptStart(D_807FBB40, 0);
                }
                func_80613CA8(D_807FBB40, cmd->unk6 + D_80747904[cmd->unk4], 0.0f, 0.0f);
                func_80614D00(D_807FBB40, 1.0f, 0.0f);
                func_806BFA8C(cmd->unk6 + D_80747904[cmd->unk4]);
                break;
            case 13:
                if (LgBV->unk4->unk64 != 0) {
                    actorScriptStart(D_807FBB40, 0);
                }
                func_80613CA8(D_807FBB40, cmd->unk6 + D_80747904[cmd->unk4], 0.0f, 8.0f);
                func_80614D00(D_807FBB40, 1.0f, 0.0f);
                func_806BFA8C(cmd->unk6 + D_80747904[cmd->unk4]);
                break;
            case 4:
                func_80614D00(D_807FBB40, cmd->unk4 / 100.0, cmd->unk6);
                break;
            case 5:
                LgBV->unk154 = 2;
                LgBV->unk155 = 0;
                if (LgBS98->unk20 != NULL) {
                    heapFree(LgBS98->unk20);
                }
                LgBS9C->unk11 = 1;
                LgBS98->unk20 = func_80610FE8(2);
                LgBS98->unk20[1] = 0;
                LgBS98->unk20[0] = cmd->unk4;
                LgBS90->unk25 = 0;
                actorSetTargetSpeed(D_807FBB40, cmd->unk6);
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
                    actorSetUniformScale(D_807FBB40, cmd->unk4 * 0.01);
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
        actorSetUniformScale(D_807FBB40, LgBS90->unk30 + (state->unk14 - LgBS90->unk30) * ratio2);
    }
    if (state->unk30 != 0xFF) {
        for (j = 0; j < state->unk31 && state->unk30 != 0xFF; j++) {
            sp74 = (((randomNonNegative() >> 15) % 32767) % 51 + 0x4B) * 0.01;
            if (state->unk30 == 0xFE) {
                actorGetNodePos(D_807FBB40, 4, &sp70, &sp6C, &sp68);
            } else if (func_80723C98(state->unk30, 4, &sp70, &sp6C) != 0) {
                func_80723484(state->unk30);
                func_807238D4(state->unk30, &sp70, &sp6C, &sp68);
                sp6C += 10.0f;
            } else {
                state->unk30 = 0xFF;
            }
            if (state->unk30 == 0xFE || (state->unk30 != 0xFF && func_80723C98(state->unk30) != 0)) {
                func_807149A8(0x7D0);
                func_807149B8(1);
                func_80714998(2);
                col = &D_80747B00[state->unk32 * 3u];
                func_807149C8(col[0], col[1], col[2], 0xFF);
                func_8071498C(func_80717D4C);
                func_80714950(-10 - (randomNonNegative() >> 15) % 30);
                func_80714CC0(D_80746B80[state->unk33], (f32)state->unk22 * 0.01 * sp74, sp70, sp6C, sp68);
            }
        }
    }
    switch (D_807FBB40->unk154) {
        case 0xD:
            node = LgBV->unk15F;
            if (node != 0) {
                actorGetNodePos(LgBS90->unk4, node, &LgBV->unk7C, &LgBV->unk80, &LgBV->unk84);
            } else {
                LgBV->unk7C = D_807FDC94->unk7C;
                LgBV->unk80 = D_807FDC94->unk80;
                LgBV->unk84 = D_807FDC94->unk84;
            }
            LgBV->unkE6 = LgBS90->unk4->unkE6;
            break;
        case 0xC:
            func_80723484(state->unk2F);
            func_807238D4(state->unk2F, &LgBV->unk7C, &LgBV->unk80, &LgBV->unk84);
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
                actorSetTargetSpeed(D_807FBB40, 0);
            }
            break;
        case 0x2:
            actorMoveWithinZone(2, LgBS90->unkA, LgBS90->unkE, 0x210, 0.0f);
            if (func_8072D13C(2, 0) != 0) {
                LgBV->unk154 = 0;
                LgBV->unk155 = 0;
                actorSetTargetSpeed(D_807FBB40, 0);
            }
            break;
        case 0x0:
            actorMoveWithinZone(0, LgBS90->unkA, LgBS90->unkE, 0x210, 0.0f);
            break;
        case 0x1D:
            actorApplyGravity();
            actorApplyVelocityCustom(D_807FBB40, 0.0f, LgBV->unkC0);
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
    if ((LgBS98->unk46 & 0x1000) && ((s32 (*)(s32, void *))func_8072881C)(0, LgBS90->unk28) != 0 && (state->unk0 == 1 || state->unk0 == 9 || state->unk0 == 0x68)) {
        func_8072881C(0x81, LgBS90->unk28);
    }
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806BFBF4.s")
#endif

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

extern Actor *D_807FBB44;
void actorScriptStart(void *, s32);
void func_8070D8C0(Actor *, s32, u8);
void actorSetTargetSpeed(Actor *, s32);
s32 actorMoveWithinZone(u8, f32, f32, s32, f32);
s32 func_8072D13C(u8, s32);
s32 func_80724A20(void);
s32 currentActorTestClearFlag(void);
s32 actorSpawn(s32, s32);
void func_80613C48(Actor *, s16, f32, f32);
void func_8067B238(void *, void *, f32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);

void func_806C10A0(u8 arg0, u16 arg1, s16 arg2) {
    f32 sp34;

    if (!(R1V->unk60 & 0x10)) {
        func_806F0C18(D_807FBB40);
        D_807FDC98->unk46 |= 0x200;
        actorSetTargetSpeed(D_807FBB40, 0);
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
            func_8072D13C(2, 0);
            break;
        case 0x12:
            switch (R1V->unk155) {
                case 0:
                    func_8070D8C0(D_807FBB40, arg1, arg0);
                    actorScriptStart(D_807FBB40, arg2);
                    R1V->unk155++;
                    break;
                case 2:
                    if (!(R1V->unk60 & 0x2000000)) {
                        func_80613C48(D_807FBB40, 0xE4, 0.0f, 2.0f);
                        actorSpawn(0xE1, 0x98);
                        func_8067B238(D_807FBB44, D_807FBB40, 0.21f);
                        actorGetNodePos(D_807FBB40, 1, &D_807FBB44->unk7C, &sp34, &D_807FBB44->unk84);
                        actorScriptStart(D_807FBB44, 0x298);
                        ((R1C46aActor *)D_807FBB44)->unk11C = R1V;
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
            actorDespawn(D_807FBB40);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_8067ACB4(Actor *);
s32 func_806CD9A0(Actor *, f32, f32, u8, s16);

void func_806C13AC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s16 val;
    s32 ret;

    if (!(R1V->unk60 & 0x10)) {
        R1V->unk6A |= 1;
        func_8067ACB4(D_807FBB40);
        R1V->unkCC = 1;
    }
    val = ret = func_806CD9A0(D_807FBB40, R1V->unkB8, R1S90->unk26, R1S90->unk34, arg0);
    if (ret != R1S90->unk34) {
        switch (ret) {
            case 0:
            case 1:
            case 2:
                func_80613C48(D_807FBB40, arg1, 0.0f, 6.0f);
                break;
            case 3:
                func_80613C48(D_807FBB40, arg2, 0.0f, 6.0f);
                break;
            case 4:
                func_80613C48(D_807FBB40, arg3, 0.0f, 6.0f);
                break;
            case 5:
                func_80613C48(D_807FBB40, arg4, 0.0f, 6.0f);
                break;
        }
        R1S90->unk34 = val;
    }
}

s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);

void func_806C151C(u16 arg0, u8 arg1, s16 arg2) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 near;

    dx = D_807FBB4C->unk7C - R1V->unk7C;
    dy = D_807FBB4C->unk80 - R1V->unk80;
    dz = D_807FBB4C->unk84 - R1V->unk84;
    near = 0;
    if (dx * dx + dy * dy + dz * dz < 4900.0f) {
        near = 1;
    }
    if ((u8)near) {
        if (!flagGet(arg2, 2)) {
            func_8070D8C0(D_807FBB40, arg0, arg1);
            flagSet(arg2, 1, 2);
        }
    }
}

void func_806C15E8(void) {
    D_807FDC98->unk46 |= 0x1000;
    R1V->unk146 = 0;
    actorSetTargetSpeed(D_807FBB40, 0);
    R1V->unkCC = 1;
}

void behaviourFrameBegin(void);
extern s32 D_8076A0A8;
void func_806BFBF4(void);

void func_806C1640(void) {
    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
        if (D_8076A0A8 == 0x4C) {
            R1V->unk4->unk34 *= 0.8;
            R1V->unk4->unk38 *= 0.8;
            R1V->unk4->unk3C *= 0.8;
        }
    }
    func_806BF920();
    if (R1V->unk60 & 0x10000000) {
        func_806BFBF4();
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u32 D_8076A064;
extern u8 D_8071FB08;
extern u8 D_807200D4;
void func_80714998(s32);
void func_807149B8(s32);
void func_8071498C(void *);
void func_8071C818(void);
void func_80714950(s32);
void func_8071A8B0(void);
void func_80714C08(void *, f32, void *, s32, s32);
void func_806F1048();
s32 randomNonNegative(void);
void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);

void func_806C1734(void) {
    R1C46aSub4 *sub;
    s32 rnd;
    R1C46aInner *inner;
    s16 sp2A;
    u8 sp29;

    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
    }
    func_806BF920();
    if (R1V->unk60 & 0x10000000) {
        sp2A = R1V->unk4->unk0->unk4;
        func_806BFBF4();
        sub = R1V->unk4;
        if (*sub->unk8 == 0) {
            inner = sub->unk0;
            switch (inner->unk10) {
                case 0xBB:
                    if (30.0f < R1V->unkC0 && !(D_8076A064 & 3)) {
                        func_80714998(2);
                        func_807149B8(1);
                        func_8071498C(func_8071C818);
                        func_80714C08(&D_8071FB08, 0.8f, D_807FBB40, 5, 0);
                    }
                    break;
                case 0x114:
                    if (0.0f == inner->unk24) {
                        func_806F1048(D_807FBB40);
                    }
                    break;
                case 0xEA:
                    if (R1V->unk155 != 0 && sp2A >= 10) {
                        R1V->unk155 = 0;
                        projectileGetTargetCoords(D_807FBB40, 7);
                        projectileSpawnNodeEntry(0x29, 0xCA, 0.4f, R1V->unkE6, 250.0f, 0.0f, D_807FBB40);
                    }
                    break;
                case 0x112:
                    if (sp2A >= 0x44 && sp2A < 0x64 && (D_8076A064 % 3) == 0) {
                        rnd = randomNonNegative() >> 15;
                        sp29 = (rnd % 0x7FFF) % 2;
                        func_807149B8(1);
                        func_80714950(0x50);
                        func_8071498C(func_8071A8B0);
                        func_80714C08(&D_807200D4, 0.5f, D_807FBB40, sp29 + 9, 2);
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
    actorUpdateModelMatrix(D_807FBB40, 0);
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
        func_806F09F0(D_807FBB40, R1V->unk5A);
    }
    if (R1V->unk60 & 0x10000000) {
        func_806BFBF4();
        if (R1V->unk4->unk0->unk10 == 0x1A4) {
            func_807149B8(1);
            func_807149C8(0x96, 0xFF, 0xFF, 0xFF);
            func_80714C08(&D_8071FBA0, 0.7f, D_807FBB40, 5, 0);
        }
        func_80724E48(D_807FDC94 == D_807FBB4C ? 5 : 7);
    } else {
        func_806C10A0(2, 6, 0x3D9);
        func_80724E48(0);
        func_806C151C(6, 1, 6);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u8 D_8071FB34;

void func_806C1B50(void) {
    u8 kind;
    u32 thr;

    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        func_806C15E8();
        func_806F09F0(D_807FBB40, R1V->unk5A);
    }
    func_806BF920();
    if (R1V->unk60 & 0x10000000) {
        func_806BFBF4();
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
                func_80714C08(&D_8071FB34, 0.5f, D_807FBB40, kind, 0);
                R1V->unk155 = 0;
            }
        }
    } else {
        func_806C10A0(2, 4, 0x3DB);
        func_806C151C(4, 1, 8);
    }
done:
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_80613194();
void renderCallbacksRegister(void *, void *, s32);
void func_807035C4();

void func_806C1CCC(void) {
    behaviourFrameBegin();
    if (!(R1V->unk60 & 0x10)) {
        R1V->unkC8 = -2000.0f;
        R1V->unkC4 = -200.0f;
        func_806C15E8();
        func_80724CA4(2, 1);
        if (D_8076A0A8 == 0x4C) {
            func_80613194(D_807FBB40, 0xE);
        }
        func_806F09F0(D_807FBB40, R1V->unk5A);
    }
    if (R1V->unk60 & 0x10000000) {
        func_806BFBF4();
        if (R1V->unk60 & 4) {
            if (R1V->unk4->unk0->unk10 == 0x2C4 && 25.0f < R1V->unk4->unk0->unk4) {
                renderCallbacksRegister(func_807035C4, 0, 3);
            }
        }
        func_80724E48(D_807FDC94 == D_807FBB4C ? 5 : 7);
    } else {
        func_806C10A0(2, 5, 0x3DA);
        func_80724E48(0);
        func_806C151C(5, 1, 0xF);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u8 D_8071FF58[];
extern u8 D_80720B58[];
void func_807197B4();
void func_8071F078();
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
void func_807149FC(s32);

void func_806C1E44(void) {
    s32 i;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        animSetLoopLimit(D_807FBB40, 0, 1);
        animSetFinished(D_807FBB40, 0, 1);
        switch (D_8076A0A8) {
            case 0x14:
                D_807FBB40->unk12C[4] = 0xFF;
                D_807FBB40->unk12C[5] = 0xFF;
                if (flagGet(0x4C, 0) == 0) {
                    animSetFrameAndSubframe(D_807FBB40, 0, 1, 0);
                    actorScriptStart(D_807FBB40, 0x2BD);
                    D_807FBB40->unk154 = 0;
                    D_807FBB40->unk155[0] = 0;
                } else {
                    D_807FBB40->unk154 = 0x27;
                    D_807FBB40->unk155[0] = 0;
                    D_807FBB40->unk155[0] = 4;
                }
                break;
            case 0x26:
                animSetFrameAndSubframe(D_807FBB40, 0, 0, 0);
                D_807FBB40->unk154 = 5;
                D_807FBB40->unk155[0] = 0;
                break;
        }
    }
    switch (D_807FBB40->unk154) {
        case 0:
            func_80724A20();
            switch (D_807FBB40->unk155[0]) {
                case 1:
                    D_807FDC90->unk2C = 3;
                    D_807FBB40->unk155[0] = 2;
                case 2:
                    if (!(D_8076A064 & 7)) {
                        if (D_807FDC90->unk2C != 0) {
                            D_807FDC90->unk2C--;
                            if (D_807FDC90->unk2C == 0) {
                                D_807FBB40->unk155[0] = 0;
                            }
                            func_80714998(2);
                            func_807149B8(1);
                            func_807149FC(0x28);
                            func_8071498C(func_807197B4);
                            func_80714C08(D_8071FF58, 0.05f, D_807FBB40, 1, 0);
                        }
                    }
            }
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    animSetFrameAndSubframe(D_807FBB40, 0, 0, 0);
                    actorScriptStart(D_807FBB40, 0x2BE);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 3:
                    i = 0;
                    do {
                        func_807149B8(1);
                        func_807149FC(0x28);
                        func_8071498C(func_8071F078);
                        func_80714950(D_807FBB40->unkE6);
                        func_80714C08(D_80720B58, 0.7f, D_807FBB40, 1, 0);
                        i++;
                    } while (i != 10);
                    D_807FBB40->unk155[0]++;
                    break;
            }
            break;
        case 5:
            func_80724A20();
            func_806C151C(0xA, 1, 7);
            func_806C13AC(4, 0x4F1, 0x4F7, 0x4F7, 0x4F7);
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk154 = 0x12;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 0x12:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorScriptStart(D_807FBB40, 0x2BF);
                    animSetFrameAndSubframe(D_807FBB40, 0, 2, 0);
                    actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    actorMoveWithinZone(2, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
                    func_8072D13C(2, 0);
                    break;
            }
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern f32 D_807502F4;
extern s16 gCsModelIds[];
extern u8 D_8074E77C;
extern s32 D_807FBDC8[];
extern u8 D_8071FC40;
void func_80718BF4(void);
void func_8072A920(s16, s32, f32, f32, f32, s32, f32, f32, s32);
void modelSlotGetNodePos(s16, s32, s32, f32 *, f32 *, f32 *);
s16 func_806CC190(s16, s16, f32);
void zoneEntryGetPosition(s32, s32, f32 *, f32 *, f32 *);
void func_8072E1A4(s32, void *);
s32 actorIsTargetWithinDistance(s32);
void func_8072881C(s32, void *);
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
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((R1C46bActor *)D_807FBB40)->unkC4 = D_807502F4;
        D_807FBB40->unk80 = D_807FBB40->unkA4;
        D_807FBB40->unk12A = 0x4B0;
        if (flagGet(0x9E, 0) != 0) {
            if (((R1C46bState9C *)D_807FDC9C)->unk13 == 0x16) {
                D_807FBB40->unk154 = 0x28;
                D_807FBB40->unk155[0] = 0;
            } else {
                D_807FBB40->unk154 = 0x40;
            }
        } else if (((R1C46bState9C *)D_807FDC9C)->unk13 == 0x16) {
            D_807FBB40->unk154 = 0x40;
        }
    }
    for (i = 0; i < D_807FBDC4; i++) {
        if (D_807FBDC8[i] == 3) {
            actorScriptStart(D_807FBB40, 0x2A3);
            D_807FBB40->unk154 = 0x27;
            D_807FBB40->unk155[0] = 0;
            camStartPath(D_807FBB40, 0x16, 1);
            flagSet(0x9E, 1, 0);
        }
    }
    switch (D_807FBB40->unk154) {
        case 0x27:
            if (D_807FBB40->unk6A & 4) {
                func_8072A920(2, 0, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkC, (f32)D_807FDC90->unkE, 0x46, 30.0f, 100.0f, 0);
                if (((randomNonNegative() >> 15) % 1000) >= 0x3A3) {
                    func_8071498C(func_80718BF4);
                    func_807149B8(1);
                    func_807149FC(-1);
                    func_80714CC0(&D_8071FC40, 0, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                }
            } else {
                if ((D_807FBB40->unk6A ^ D_807FBB40->unk6C) & 1) {
                    actorScriptStart(D_807FBB40, 0x2A4);
                }
                actorMoveWithinZone(2, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0x200, 0.0f);
                if (((R1C46bActor *)D_807FBB40)->unkC0 < -10.0f) {
                    ((R1C46bActor *)D_807FBB40)->unkE8 = func_806CC190(((R1C46bActor *)D_807FBB40)->unkE8, 0x400, 10.0f);
                }
            }
            func_8072D13C(2, 0);
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk154 = 0x40;
            }
            break;
        case 0x28:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    zoneEntryGetPosition(2, 3, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
                    actorScriptStart(D_807FBB40, 0x2A6);
                    ((R1C46bActor *)D_807FBB40)->unkE8 = 0;
                    D_807FBB40->unk155[0]++;
                case 1:
                    if (actorIsTargetWithinDistance(0xC8) != 0) {
                        D_807FBB40->unk155[0]++;
                        if (flagGet(0xC1, 0) != 0) {
                            if (D_8074E77C == 0 && flagGet(0xA5, 0) == 0) {
                                func_8070D8C0(D_807FBB40, 0x1C, 2);
                            } else if (D_8074E77C != 0) {
                                func_8070D8C0(D_807FBB40, 0x1C, 0);
                            }
                        } else if (D_8074E77C == 0) {
                            camStartPath(D_807FBB40, 0x1E, 1);
                            func_8070E8DC(1);
                            func_8070D8C0(D_807FBB40, 0x1C, 1);
                            D_807FBB40->unk155[0] = 0x63;
                        } else {
                            func_8070D8C0(D_807FBB40, 0x1C, 0);
                        }
                    }
                    break;
                case 2:
                    if (flagGet(0xC1, 0) == 0 && actorIsTargetWithinDistance(0x12C) == 0) {
                        D_807FBB40->unk155[0] = 1;
                    }
                    break;
                case 0x63:
                    if (camIsCutsceneActive() == 0 && !(D_807FBB40->unk60 & 0x2000000)) {
                        func_8070D8C0(D_807FBB40, 0x1C, 2);
                        D_807FBB40->unk155[0] = 3;
                    }
                    break;
            }
            modelSlotGetNodePos(gCsModelIds[58], 1, 1, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
            func_8072E1A4(0xA, D_807FDC94);
            break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void effectSpawnActorBone(Actor *, u8, f32);

void actorPlaySoundSpawnBoneEffects(void) {
    f32 scale = D_807FBB40->unk4->unk38 / 0.15;

    sfxPlayActorSound(D_807FBB40, 0x114, 0x50, 0, 0, 0xFF, 0.5f, 0);
    if (D_8076A064 & 1) {
        effectSpawnActorBone(D_807FBB40, 1, scale);
        effectSpawnActorBone(D_807FBB40, 3, scale);
    } else {
        effectSpawnActorBone(D_807FBB40, 2, scale);
        effectSpawnActorBone(D_807FBB40, 4, scale);
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
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 s;
    f32 pad;
    s16 i;

    v = ((R1C46bSub4 *)D_807FBB40->unk4)->unk0->unk4;
    if (v > 83.0f) {
        actorPlaySoundSpawnBoneEffects();
        v = ((R1C46bSub4 *)D_807FBB40->unk4)->unk0->unk4;
    }
    if (v > 2.0f && v < 90.0f) {
        i = 1;
        if (D_8076A064 % 6 == 0) {
            s = (v / 70.0 > 1.0) ? 1.0 : v / 70.0;
            do {
                actorGetNodePos(D_807FBB40, i, &sp78, &sp74, &sp70);
                effectSpawnOctagonRing((s * 0.3 < 0.15) ? 0.15 : s * 0.3, sp78, sp74 + 3.0f, sp70);
                i++;
            } while (i < 5);
        }
    }
}

void func_807149A8(s32);
void func_80714944(s32);
void func_80717D84();

void effectSpawnColoredParticleAtPoint(u8 arg0, u8 arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6, f32 arg7) {
    func_807149A8(1000);
    func_80714998(0xFF);
    func_80714944(((randomNonNegative() >> 15) % 0x7FFF) % 11);
    func_807149C8(arg0, arg1, arg2, 0xFF);
    func_8071498C(func_80717D84);
    func_80714950(2);
    func_80714CC0(arg6, arg7 * 0.2, arg3, arg4, arg5);
}

extern u8 D_80747B00[];

void actorSpawnParticlesAlongNodeLoop(u8 arg0, u8 arg1, u8 arg2, void *arg3) {
    f32 scale;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 frac;
    s16 i;
    s16 j;

    scale = D_807FBB40->unk4->unk38 / 0.15;
    scale = scale / 1.5;
    for (i = arg0; i <= arg1; i++) {
        for (j = 0; j < 3.0; j++) {
            frac = (f32)j / 3.0;
            actorGetNodePos(D_807FBB40, i, &spA8, &spA4, &spA0);
            if (i < arg1) {
                actorGetNodePos(D_807FBB40, i + 1, &sp9C, &sp98, &sp94);
            } else {
                actorGetNodePos(D_807FBB40, arg0, &sp9C, &sp98, &sp94);
            }
            effectSpawnColoredParticleAtPoint(D_80747B00[arg2 * 3], D_80747B00[arg2 * 3 + 1], D_80747B00[arg2 * 3 + 2], (sp9C - spA8) * frac + spA8, (sp98 - spA4) * frac + spA4, (sp94 - spA0) * frac + spA0, arg3, scale);
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

#define LgV ((LgC2DF4Actor *)D_807FBB40)

void func_806136B4(Actor *);
void func_806134B4(Actor *, u16);
ActorSub140 *func_80665F24(Actor *);
void actorSetUniformScale(Actor *, f32);
void func_80728950(s32);
void currentActorAnimSetFrame(s32, s32);
void actorGetNodePosOrPosition(Actor *, s32 *, s32 *, s32 *);
void func_806871DC(s32);
void func_80686F90(s32, s16, s16);
void effectSpawnBoneDefault(Actor *, s16, f32, f32, f32, f32, s32);
void effectSpawnActorScale(Actor *);
void func_80685F60(Actor *);
void sfxStopSlotSound(Actor *, s32);
void actorSetGroupState(u8, u8);
void func_8072177C(Actor *, s16, s16, s16, s32, s32, s32, s32, s32);
void effectSpawnJointBeam(s32, s32, s32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
extern s32 D_807FBB68;

void func_806C2DF4(void) {
    LgC2DF4State *state;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    f32 sp54;
    s32 rnd;

    state = LgV->unk17C;
    behaviourFrameBegin();
    if (!(LgV->unk60 & 0x10)) {
        sp54 = LgV->unk4->unk38;
        func_806136B4(D_807FBB40);
        func_806134B4(D_807FBB40, state->unk0);
        LgV->unk140 = func_80665F24(D_807FBB40);
        LgV->unk146 = 0;
        LgV->unk12A = 0xFA0;
        D_807FDC98->unk46 |= 0x20;
        LgV->unk60 &= 0xFEFFFFFF;
        LgV->unk144 = 1;
        switch (state->unk0) {
            case 0x21:
                if (D_8076A0A8 == 0x98 || D_8076A0A8 == 0x1C) {
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
                func_806F0C18(D_807FBB40);
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
                    animSetLoopLimit(D_807FBB40, 1, 1);
                    animSetFinished(D_807FBB40, 1, 1);
                    animSetFrameAndSubframe(D_807FBB40, 1, 1, 0);
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
                animSetLoopLimit(D_807FBB40, 0, 1);
                animSetFinished(D_807FBB40, 0, 1);
                animSetFrameAndSubframe(D_807FBB40, 0, ((LgC2DF4S9C *)D_807FDC9C)->unk14, 0);
                break;
            case 0x45:
                sp54 *= 10.0f;
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
                if (D_8076A0A8 == 0x4C) {
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
                sp54 *= 8.0f;
                actorSetUniformScale(D_807FBB40, sp54);
                LgV->unkE8 = 0xC8;
                func_806BFBB4();
                actorSpawnParticlesAlongNodeRanges();
                break;
            case 0x68:
                if (D_8076A0A8 == 0xCD) {
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
        actorSetUniformScale(D_807FBB40, sp54);
        if (D_8076A0A8 == 0xD0) {
            D_807FDC98->unk46 |= 0x100;
            LgV->unk60 &= 0xFEFFFFFF;
        }
    }
    actorGetNodePosOrPosition(D_807FBB40, &sp60, &sp5C, &sp58);
    func_806BF920();
    func_806BFBF4();
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
            if (!(D_8076A064 & 1)) {
                func_807149A8(0x7D0);
                func_80714998(3);
                func_807149C8(0x32, 0x32, 0x32, 0xFF);
                effectSpawnBoneDefault(D_807FBB40, 1, 1.3f, 0, 0, 0, -0x50);
            }
            break;
        case 0x4DA:
        case 0x4DB:
        case 0x4DC:
        case 0x4DD:
        case 0x4DE:
            if (!(D_8076A064 & 3)) {
                func_807149B8(1);
                func_8071498C(func_8071C818);
                func_80714C08(&D_8071FB08, 0.6f, D_807FBB40, 2, 0);
            }
            break;
        case 0x4C7:
            if (LgV->unk4->unk0->unk4 >= 23.0f && LgV->unk155 != 0) {
                LgV->unk155 = 0;
                projectileGetTargetCoords(D_807FBB40, 2);
                projectileSpawnNodeEntry(0x29, 0xCB, 0.4f, LgV->unkE6, 400.0f, 0, D_807FBB40);
            }
            break;
        case 0x54D:
            if (LgV->unk4->unk0->unk24 == 0) {
                LgV->unk154 = 0x40;
            } else if (LgV->unk4->unk0->unk4 < 210.0f) {
                func_806871DC(2);
            } else if (LgV->unk4->unk0->unk4 < 235.0f) {
                func_806871DC(3);
            }
            break;
        case 0x549:
            if (LgV->unk4->unk0->unk4 > 65.0f && LgV->unk4->unk0->unk4 < 101.0f) {
                rnd = randomNonNegative();
                func_80686F90(2, (rnd >> 15) % 2048 + LgV->unkE6 - 0x400, (randomNonNegative() >> 15) % 2048);
            }
            break;
        case 0x498:
            if (LgV->unk4->unk0->unk4 < 2.0f) {
                effectSpawnActorScale(D_807FBB40);
            }
            func_80685F60(D_807FBB40);
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
                sfxStopSlotSound(D_807FBB40, 0);
            }
            break;
        case 0x52E:
            if (LgV->unk4->unk0->unk4 < 2.0f) {
                func_80714C08(&D_8071FB34, 1.5f, D_807FBB40, 6, 0);
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
    if (D_8076A0A8 == 0xD0 && (LgV->unk60 & 0x1000)) {
        func_8072177C(D_807FBB40, LgV->unk7C, LgV->unk80 + 30.0f, LgV->unk84, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    }
    if (LgV->unk4->unk64 == 0x22A) {
        if ((randomNonNegative() >> 15) % 100 >= 0x47 || LgV->unk155 != 0) {
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            func_806086CC(LgV->unk7C, LgV->unk80, LgV->unk84, 0x8A, 0x64, 0x7F, 0x28, 0, 0.3f, 0);
            LgV->unk60 |= 4;
        } else {
            LgV->unk60 &= ~4;
            sfxStopSlotSound(D_807FBB40, 0);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern s16 D_80750AC8;
void csModelStateSetFirstByte(s32, s32);

void func_806C3A8C(void) {
    s32 dist;
    f32 pad0;
    f32 pad1;
    u8 sp23;
    u8 sp22;
    u8 sp21;
    u8 sp20;

    dist = (D_807FBB4C->unk7C - D_807FBB40->unk7C) * (D_807FBB4C->unk7C - D_807FBB40->unk7C) + (D_807FBB4C->unk80 - D_807FBB40->unk80) * (D_807FBB4C->unk80 - D_807FBB40->unk80) + (D_807FBB4C->unk84 - D_807FBB40->unk84) * (D_807FBB4C->unk84 - D_807FBB40->unk84);
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk15E = 0x19;
        func_8067ACB4(D_807FBB40);
        if (flagGet(0x1E, 2) == 0) {
            camStartPath(D_807FBB40, 0x14, 1);
            flagSet(0x1E, 1, 2);
        }
        if (flagGet(0xBF, 0) == 0) {
            if (flagGet(0xBA, 0) && flagGet(0xBB, 0) && flagGet(0xBC, 0) && flagGet(0xBD, 0) && flagGet(0xBE, 0)) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            } else if (flagGet(0xBA, 0) || flagGet(0xBB, 0) || flagGet(0xBC, 0) || flagGet(0xBD, 0) || flagGet(0xBE, 0)) {
                D_807FBB40->unk154 = 0x1F;
                D_807FBB40->unk155[0] = 0;
            } else {
                D_807FBB40->unk154 = 0x1E;
                D_807FBB40->unk155[0] = 0;
            }
        } else {
            D_807FBB40->unk154 = 0x20;
            D_807FBB40->unk155[0] = 0;
        }
    }
    func_806BFBF4();
    switch (D_807FBB40->unk154) {
        case 0x1E:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    if ((u8)(dist < 0xF424)) {
                        D_807FBB40->unk155[0]++;
                    }
                    break;
                case 1:
                    if ((u8)(dist < 0x2710)) {
                        actorScriptStart(D_807FBB40, 0x3A4);
                        func_8070D8C0(D_807FBB40, 0x17, 0);
                        D_807FBB40->unk155[0]++;
                    }
                    break;
            }
            break;
        case 0x1F:
            if ((u8)(dist < 0x2710) && D_807FBB40->unk155[0] == 0) {
                sp20 = flagGet(0xBD, 0);
                sp21 = flagGet(0xBC, 0);
                sp22 = flagGet(0xBB, 0);
                sp23 = flagGet(0xBA, 0);
                D_80750AC8 = flagGet(0xBE, 0) + sp23 + sp22 + sp21 + sp20;
                func_8070D8C0(D_807FBB40, 0x17, 2);
                D_807FBB40->unk155[0]++;
            }
            break;
        case 0x20:
            if ((u8)(dist < 0x2710) && D_807FBB40->unk155[0] == 0 && camIsCutsceneActive() == 0) {
                camStartPath(D_807FBB40, 0x18, 1);
                func_8070D8C0(D_807FBB40, 0x17, 3);
                D_807FBB40->unk155[0]++;
            }
            break;
        case 0x27:
            if (camIsCutsceneActive() == 0) {
                switch (D_807FBB40->unk155[0]) {
                    case 0:
                        camStartPath(D_807FBB40, 0x17, 1);
                        func_8070E8DC(1);
                        func_8070D8C0(D_807FBB40, 0x17, 1);
                        D_807FBB40->unk155[0]++;
                        break;
                    case 1:
                        if (!(D_807FBB40->unk60 & 0x2000000)) {
                            csModelStateSetFirstByte(0xE, 0xA);
                            D_807FBB40->unk154 = 0x20;
                            D_807FBB40->unk155[0] = 0;
                        }
                        break;
                }
            }
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
