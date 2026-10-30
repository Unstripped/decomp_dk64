// func_806BFBF4 (src/global/C4620.c): Stage 5-6 (regalloc only): ~91 structural diff lines of 1545 (was ~117), frame 152/saved regs/size within +9 insns. Needs s32 func_8072881C (C4620.c later decl 'void' -> 's32'; other TUs already s32) else cast gives jalr. FIXED this round: local decl order j,t,i first (puts i at 146(sp)); timers 1-3 share f32 ratio, timer4 ratio2 (fixes f0/f2 swap); cases 12/14 store order unkE,unk10,unk1E. REMAINING: (1) const-3 live range lump split after case 6: our T6 &D_807FDCA0 takes a0 (target a1) so ours remats li a0,3 at all later case tails (+9 insns); (2) entry: li 255 not hoisted above bnez, lw s2 not in delay slot; (3) continue edge reaches addiu not lh (target latch starts with lh a2); (4) particle loop: &sp70 CSE takes s4 instead of const 254 (priority 254 adjsave -1.17 vs &sp70); (5) case 0xD hoists &D_807FDC94 above beqz (node lands a1 not v0). Tried without effect: local decl permutations of ptr/f32 locals, node var removal, f32 sp[3] array, do-while/if==3 loop forms, break/default, 0xFE local var, 600+840s permuter (best is a dead u64 local, no hint).
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
void func_80614EBC(void *, s32);
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
s32 func_8072881C(s32, void *);
void actorApplyGravity(void);
void func_8072A450(void);
void func_8072DC7C(s32);
void func_8072E320(f32);
s32 mathAngleLerp(s16, s16, f32);
void lightUpdateFromActorLighting(void *, void *, void *);
void heapFree(void *);
s32 func_80611A44(void);
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
        lightUpdateFromActorLighting(&LgBV->unk16A, &LgBV->unk16B, &LgBV->unk16C);
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
                func_80614EBC(D_807FBB40, D_80747750[cmd->unk4]);
                if (cmd->unk6 != 0) {
                    func_80614D00(D_807FBB40, cmd->unk6 / 100.0, 0.0f);
                }
                break;
            case 3:
                if (LgBV->unk4->unk64 != 0) {
                    func_80614EBC(D_807FBB40, 0);
                }
                func_80613CA8(D_807FBB40, cmd->unk6 + D_80747904[cmd->unk4], 0.0f, 0.0f);
                func_80614D00(D_807FBB40, 1.0f, 0.0f);
                func_806BFA8C(cmd->unk6 + D_80747904[cmd->unk4]);
                break;
            case 13:
                if (LgBV->unk4->unk64 != 0) {
                    func_80614EBC(D_807FBB40, 0);
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
                LgBS98->unk20 = heapAlloc(2);
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
            sp74 = (((func_80611A44() >> 15) % 32767) % 51 + 0x4B) * 0.01;
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
                func_80714950(-10 - (func_80611A44() >> 15) % 30);
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
    if ((LgBS98->unk46 & 0x1000) && func_8072881C(0, LgBS90->unk28) != 0 && (state->unk0 == 1 || state->unk0 == 9 || state->unk0 == 0x68)) {
        func_8072881C(0x81, LgBS90->unk28);
    }
}
