// func_8002F100 (src/boss/B100.c): stage 6: 671 insns frame 80, opcode seq identical to expected except ONE compare: expected 'slti v0,a0,4 ; addiu t8,a0,-1 ; beqz v0 ; sh t8' (case 0x27/3: if (t<4) after t=unk2C; unk2C=t-1) vs mine 'addiu ; slti at ; beqz at'. Named function-level s16 t reused for every unk2C read fixed the a0-vs-v0 temp swaps; pad[1] keeps frame; projectileSpawnWithShockwave must be s32-returning; remaining rodata/jtbl addends only. Tried: post-dec forms, c=(t<4) temp, && 1, <= 3, > forms.
typedef struct BsB2F_Sub178 {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17[1];
    u8 unk18;
} BsB2F_Sub178;

typedef struct BsB2F_Actor {
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
    u8 padE8[0x11C - 0xE8];
    void *unk11C;
    u8 pad120[0x132 - 0x120];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[1];
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x168 - 0x156];
    s16 unk168;
    u8 pad16A[0x178 - 0x16A];
    BsB2F_Sub178 *unk178;
} BsB2F_Actor;

typedef struct BsB2F_DC90 {
    u8 pad0[0x2C];
    s16 unk2C;
} BsB2F_DC90;

typedef struct BsB2F_C924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BsB2F_C924;

typedef struct BsB2F_Node {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[4];
} BsB2F_Node;

typedef struct BsB2F_DCA0 {
    u8 pad0[0x14];
    BsB2F_Node *unk14;
} BsB2F_DCA0;

typedef struct BsB2F_DC9C {
    u8 pad0[0xC];
    u8 unkC;
} BsB2F_DC9C;

extern u8 *D_80035A90[];
extern void *D_807FBB4C;
extern BsB2F_C924 *D_807FC924;
extern void *D_807FDC90;
extern BsB2F_DC9C *D_807FDC9C;
extern BsB2F_DCA0 *D_807FDCA0;
extern void *gCamActor;

void behaviourFrameBegin(void);
void func_8070B308(s32);
void camSetSecondTarget(void *, s32, s32);
void func_80724CA4(s32, s32);
s32 flagGet(s32, s32);
void zoneEntryGetPosition(s32, s32, void *, void *, void *);
void func_80028878(u8 *);
void camStartPath(void *, s32, u8);
void func_806A2B38(void *);
void func_805FF158(s32);
void func_805FF378(s32, s32);
f32 func_80612790(s16);
void func_806F3BEC(void *, s16, s16, s32);
void func_80641874(s32, s32);
void func_806D0468(void *, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(void *, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s16 func_806CC190(s16, s16, f32);
s32 projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80613C48(void *, s32, f32, f32);
void func_80614D00(void *, f32, f32);
s32 currentActorTestClearFlag(void);
s32 func_80027BA8(u8 *, s32, f32);
void func_8072A450(void);
s32 func_8072881C(s32, void *);

#define BsFA ((BsB2F_Actor *)D_807FBB40)
#define BsFP ((BsB2F_Actor *)D_807FBB4C)
#define BsFB ((BsB2F_Actor *)D_807FBB44)
#define BsFS ((BsB2F_DC90 *)D_807FDC90)

void func_8002F100(void) {
    BsB2F_Sub178 *sp4C;
    u8 *sp48;
    s16 t;
    s32 pad[1];
    f32 sp3C;

    sp4C = BsFA->unk178;
    behaviourFrameBegin();
    if (!(BsFA->unk60 & 0x10)) {
        BsFA->unk132 = 8;
        func_8070B308(0);
        camSetSecondTarget(gCamActor, 0, 0);
        BsFA->unk146 = 5;
        BsFA->unkCC = 1;
        func_80724CA4(2, 1);
        BsFA->unk154 = 0x1E;
        BsFA->unk155 = 0;
        if (flagGet(0x54, 2) != 0) {
            sp4C->unk14 = 4;
            BsFA->unk154 = 0x37;
            BsFA->unk155 = 0;
        } else if (flagGet(0x53, 2) != 0) {
            sp4C->unk14 = 3;
        } else if (flagGet(0x52, 2) != 0) {
            sp4C->unk14 = 2;
        } else if (flagGet(0x51, 2) != 0) {
            sp4C->unk14 = 1;
        }
        if (sp4C->unk14 != 0 && BsFA->unk154 != 0x37) {
            BsFA->unk154 = 0x31;
            BsFA->unk155 = 0;
            zoneEntryGetPosition(1, 0, &BsFA->unk7C, &BsFA->unk80, &BsFA->unk84);
        }
    }
    sp48 = D_80035A90[sp4C->unk14];
    func_80028878(sp48);
    switch (BsFA->unk154) {
    case 0x28:
        if (D_807FBD70 == 5 && D_807FC924->unk2C0 != 1) {
            BsFA->unk144 = 1;
            BsFP->unk144 = 1;
            camStartPath(0, 2, 1);
            BsFA->unk154 = 0x29;
            func_806A2B38(BsFA->unk11C);
            func_805FF158(1);
            func_8070B308(1);
            func_805FF378(0xD6, 0);
            BsFP->unk7C = func_80612794(BsFA->unkE6 + 0x320) * 30.0 + BsFA->unk7C;
            BsFP->unk84 = func_80612790(BsFA->unkE6 + 0x320) * 30.0 + BsFA->unk84;
            sp3C = func_80612794(BsFA->unkE6 + 0x384);
            func_806F3BEC(BsFP, (s32)(sp3C * 15.0f + BsFA->unk7C), (s32)(func_80612790(BsFA->unkE6 + 0x384) * 15.0f + BsFA->unk84), 0x50);
        } else {
            switch (BsFA->unk155) {
            case 0:
                if (sp4C->unk16 != 0) {
                    func_80641874(0, 0);
                }
                actorScriptStart(BsFA, 0x3FF);
                BsFS->unk2C = sp48[sp4C->unk15] * 0x1E;
                sp4C->unk15++;
                BsFA->unk155++;
                break;
            case 1:
                t = BsFS->unk2C;
                if (t != 0) {
                    BsFS->unk2C = t - 1;
                } else {
                    actorScriptStart(BsFA, 0x400);
                    BsFA->unk155++;
                }
                break;
            case 3:
                if (D_807FC924->unk2C0 != 1) {
                    func_806D0468(BsFP, 1);
                }
                func_80641874(0, 0xFF);
                actorScriptStart(BsFA, 0x3E4);
                BsFA->unk154 = sp48[sp4C->unk15];
                sp4C->unk15++;
                BsFA->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
        switch (BsFA->unk155) {
        case 0:
            actorSetTargetSpeed(BsFA, 0);
            sp4C->unk18 = sp48[sp4C->unk15];
            sp4C->unk15++;
            BsFA->unk155++;
            /* fallthrough */
        case 1:
            BsFS->unk2C = 4;
            actorScriptStart(BsFA, 0x3E7);
            BsFA->unk155++;
            break;
        case 2:
            BsFA->unkE6 = func_806CC190(BsFA->unkE6, mathAngleBetweenPoints2D((f32)D_807FDCA0->unk14->unk0, (f32)D_807FDCA0->unk14->unk4, BsFA->unk7C, BsFA->unk84), 10.0f);
            break;
        case 3:
            t = BsFS->unk2C;
            if (t != 0 && (u32)D_8076A064 % 5 == 0) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 150, 3, (f32)((f64)(u32)sp4C->unk14 * 0.01 + 1.04), 0.0f, 0.0f, 0.0f);
                t = BsFS->unk2C;
                BsFS->unk2C = t - 1;
                if (t < 4) {
                    BsFB->unk168 = 0;
                } else {
                    func_806086CC(BsFA->unk7C, BsFA->unk80, BsFA->unk84, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                }
                func_80613C48(BsFB, 0x4F9, 0.0f, 0.0f);
                func_80614D00(BsFB, 0.5f, 0.0f);
            } else if (t == 0) {
                BsFS->unk2C = sp4C->unk18;
                BsFA->unk155++;
            }
            break;
        case 4:
            t = BsFS->unk2C;
            if (t != 0) {
                BsFS->unk2C = t - 1;
            } else {
                actorSetTargetSpeed(BsFA, D_807FDC9C->unkC);
                actorScriptStart(BsFA, 0x3E4);
                BsFA->unk154 = sp48[sp4C->unk15];
                sp4C->unk15++;
                BsFA->unk155 = 0;
            }
            break;
        }
        break;
    case 0x1E:
        sp4C->unk14 = 0;
        sp4C->unk15 = 0;
        BsFA->unk154 = sp48[sp4C->unk15];
        sp4C->unk15++;
        BsFA->unk155 = 0;
        BsFA->unkB8 = (f32)(u32)D_807FDC9C->unkC;
        break;
    case 0:
        switch (BsFA->unk155) {
        case 0:
            actorScriptStart(BsFA, 0x3EA);
            BsFA->unk155++;
            break;
        case 2:
            BsFA->unk154 = sp48[sp4C->unk15];
            sp4C->unk15++;
            BsFA->unk155 = 0;
            break;
        }
        break;
    case 0x31:
        switch (BsFA->unk155) {
        case 0:
            func_806D0468(BsFP, 0);
            func_806D0468(BsFP, 1);
            camStartPath(BsFA, 1, 1);
            actorScriptStart(BsFA, 0x3FB);
            BsFA->unk155++;
            break;
        case 2:
            actorScriptStart(BsFA, 0x3E4);
            BsFA->unk154 = sp48[sp4C->unk15];
            sp4C->unk15++;
            BsFA->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (BsFA->unk155) {
        case 0:
            actorScriptStart(BsFA, 0);
            camStartPath(BsFA, 0x15, 1);
            BsFA->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                func_805FF158(0);
                func_805FF378(0xCF, 0);
                BsFA->unk155++;
            }
            break;
        }
        break;
    default:
        func_80027BA8(sp48, 0x10, 0.0f);
        break;
    }
    func_8072A450();
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    actorUpdateModelMatrix(BsFA, 0);
}
