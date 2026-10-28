#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} BossE_B100_Sub20;

typedef struct {
    u8 pad0[0x20];
    BossE_B100_Sub20 *unk20;
    u8 pad24[0x38 - 0x24];
    f32 unk38;
} BossE_B100_Sub4;

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} BossE_B100_Sub178;

typedef struct {
    u8 pad0[0x178];
    BossE_B100_Sub178 *unk178;
} BossE_B100_Sub11C;

typedef struct BossE_B100_Actor {
    u8 pad0[0x4];
    BossE_B100_Sub4 *unk4;
    u8 pad8[0x60 - 0x8];
    s32 unk60;
    u8 pad64[0x11C - 0x64];
    void *unk11C;
    u8 pad120[0x132 - 0x120];
    s16 unk132;
    s16 unk134;
    s32 unk138;
    u8 pad13C[0x144 - 0x13C];
    u8 unk144;
    u8 pad145[0x15F - 0x145];
    u8 unk15F;
    u8 pad160[0x17C - 0x160];
    struct BossE_B100_Actor **unk17C;
} BossE_B100_Actor;

extern BossE_B100_Actor *D_807FBB40;
extern BossE_B100_Actor *D_807FBB44;
extern u8 D_807FBD70;
extern s32 D_8076A064;

void animSetLoopLimit(s32, s32, s32);
void animSetFinished(s32, s32, s32);
void animSetFrameAndSubframe(s32, s32, s32, f32);
void func_8002FB7C();
void func_8002FC98();
void actorSpawn(s32, s32);
void func_8067B238(void *, void *, f32);
void actorScriptStart(void *, s32);
void func_80724DB0();
void func_8072DA60(void);
void actorUpdateModelMatrix(void *, s32);

f32 func_80612794(s16);

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0x154 - 0xE8];
    u8 unk154;
    u8 unk155;
} BsA7e_Cam;

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
} BsA7e_DC90;

typedef struct {
    u8 pad0[0x14];
    s16 *unk14;
} BsA7e_DCA0;

extern BsA7e_Cam *D_807FBB4C;
extern BsA7e_DC90 *D_807FDC90;
extern BsA7e_DCA0 *D_807FDCA0;
s32 flagGet(s16, u8);
void func_80027BA8(u8 *, s32, f32);

#ifdef NON_MATCHING
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
extern BsB2F_C924 *D_807FC924;
extern BsB2F_DC9C *D_807FDC9C;
extern void *gCamActor;

void behaviourFrameBegin(void);
void func_8070B308(s32);
void camSetSecondTarget(void *, s32, s32);
void func_80724CA4(s32, s32);
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
            BsFA->unkE6 = func_806CC190(BsFA->unkE6, mathAngleBetweenPoints2D((f32)((BsB2F_DCA0 *)D_807FDCA0)->unk14->unk0, (f32)((BsB2F_DCA0 *)D_807FDCA0)->unk14->unk4, BsFA->unk7C, BsFA->unk84), 10.0f);
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
#else

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/func_8002F100.s")
#endif

void func_8002FB7C(arg0)
u8 arg0;
{
    BossE_B100_Sub20 *sub;
    f32 sin_val;

    sub = D_807FBB40->unk4->unk20;
    sub->unk0 = 2;
    sub->unk1 = 4;
    sub->unk4 = 1.0f;
    sin_val = func_80612794((s16)(D_8076A064 << 7));
    sub->unk4 += (f64)arg0 * (0.04 + 0.04 * (f64)sin_val);
    sub->unk8 = sub->unk4;
    sub->unkC = 1.0f;
}
void func_8002FC48(arg0, arg1)
s32 arg0;
u8 arg1;
{
    animSetLoopLimit(arg0, 0, 1);
    animSetFinished(arg0, 0, 1);
    animSetFrameAndSubframe(arg0, 0, arg1, 0.0f);
}

void func_80614D00(void *, f32, f32);

void func_8002FC98(arg0, arg1, arg2, arg3)
BossE_B100_Actor *arg0;
u8 arg1;
s32 arg2;
u8 arg3;
{
    BossE_B100_Actor **actor_list;
    BossE_B100_Actor *actor;
    s16 i;

    actor_list = arg0->unk17C;
    for (i = 0; i < 4; i++) {
        if (arg1 & (1 << i)) {
            actor = i != 0 ? actor_list[i - 1] : arg0;
            switch (arg2) {
            case 1:
            case 2:
                actor->unk132 = arg2;
                break;
            case -1:
            case 0:
                actor->unk138 = arg2;
                break;
            default:
                actorScriptStart(actor, arg2);
                if (arg3) {
                    func_80614D00(actor, (f64)arg3 * 0.01, 0.0f);
                }
                break;
            }
        }
    }
}


void func_8002FDF8(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s32 v0;
    s32 temp_a1;

    if (D_807FBB40->unk15F == 2) {
        v0 = 4;
    } else {
        v0 = arg1;
    }
    func_8002FB7C(v0 & 0xFF);
    if (D_807FBD70 == 4) {
        func_8002FC98(arg0, 0xF, 0, 0);
        temp_a1 = (0xA - D_807FBB40->unk134) & 0xFF;
        func_8002FC48(D_807FBB40, temp_a1);
        actorScriptStart(D_807FBB40, 0x415);
    }
    if (D_807FBD70 == 5 || D_807FBD70 == 4) {
        func_8072DA60();
    }
}

void func_8002FEC0(arg0, arg1, arg2)
BossE_B100_Actor **arg0;
u8 arg1;
s32 arg2;
{
    actorSpawn(0xE5, arg2);
    func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
    D_807FBB44->unk60 |= 0x1400;
    D_807FBB44->unk11C = D_807FBB40;
    D_807FBB44->unk144 = D_807FBB40->unk144;
    D_807FBB44->unk60 = D_807FBB40->unk60;
    arg0[arg1] = D_807FBB44;
}

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
    u8 padA[0x12 - 0xA];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    u8 unk18;
    u8 unk19;
} BsA7e_State;

typedef struct BsA7e_Actor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x138 - 0x64];
    s32 unk138;
    u8 pad13C[0x154 - 0x13C];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x178 - 0x160];
    BsA7e_State *unk178;
    struct BsA7e_Actor **unk17C;
} BsA7e_Actor;

typedef struct {
    u8 pad0[0x38];
    f32 unk38;
} BsA7e_D580;

#define BsA7e_A ((BsA7e_Actor *)D_807FBB40)

extern BsA7e_D580 *D_807FD580;
extern u8 *D_80035AA4[];

void flagSet(s16, s32, s32);
void func_8070B308(s32);
void func_806FB370(s32, s32, s32);
void func_80614E78(void *, s32);
void func_805FF158(s32);
void func_805FF378(s32, s32);
void func_80724A20(void);
void behaviourFrameBegin(void);
void camClosestPointOnSegment(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);

void func_8002FDF8(s32, u8);

void func_8002FF74(void) {
    BsA7e_State *st;
    BsA7e_Actor **list;
    u8 *tbl;
    f32 sp60;

    st = BsA7e_A->unk178;
    list = BsA7e_A->unk17C;
    behaviourFrameBegin();
    if (!(BsA7e_A->unk60 & 0x10)) {
        func_8070B308(0);
        func_806FB370(2, 0, 1);
        D_807FBB4C->unk154 = 0x5F;
        D_807FBB4C->unk155 = 0;
        func_80614E78(D_807FBB4C, 0x4B);
        BsA7e_A->unk154 = 0;
        BsA7e_A->unk155 = 0;
        func_80724DB0(2, 1);
        func_8002FEC0(list, 0, 0x6D);
        func_8002FEC0(list, 1, 0x6E);
        func_8002FEC0(list, 2, 0x6F);
        st->unk12 = 0;
        if (flagGet(0x51, 2)) {
            func_8002FC48(D_807FBB40, 4);
            BsA7e_A->unk15F = 2;
            list[0]->unk15F = 1;
            st->unk12 = 1;
        }
        if (flagGet(0x52, 2)) {
            func_8002FC48(list[0], 4);
            list[0]->unk15F = 2;
            list[1]->unk15F = 1;
            st->unk12 = 2;
        }
        if (flagGet(0x53, 2)) {
            func_8002FC48(list[1], 4);
            list[1]->unk15F = 2;
            list[2]->unk15F = 1;
            st->unk12 = 3;
        }
        st->unk14 = 0;
        func_8002FC98(D_807FBB40, 0xF, 0x40E, 0);
    }
    tbl = D_80035AA4[st->unk14];
    if (BsA7e_A->unk154) {
        s16 *p = D_807FDCA0->unk14;
        camClosestPointOnSegment(D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84, p[0], p[1], p[2], p[5], p[6], p[7], &D_807FBB4C->unk7C, &sp60, &D_807FBB4C->unk84);
        D_807FBB4C->unkE6 = 0xFD2;
        D_807FD580->unk38 = 150.0f;
    }
    func_8002FDF8((s32)BsA7e_A, st->unk14);
    func_8002FC98(D_807FBB40, (1 << st->unk12) & 0xFF, 1, 0);
    switch (BsA7e_A->unk154) {
    case 0x1F:
        switch (BsA7e_A->unk155) {
        case 0:
            D_807FDC90->unk2C = tbl[st->unk15++];
            BsA7e_A->unk155++;
        case 1:
            if (D_807FDC90->unk2C) {
                D_807FDC90->unk2C--;
            } else {
                BsA7e_A->unk154 = tbl[st->unk15++];
                BsA7e_A->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        if (BsA7e_A->unk155 == 0) {
            D_807FBB4C->unk154 = 0x5F;
            D_807FBB4C->unk155 = 0;
            func_80614E78(D_807FBB4C, 0x4A);
            func_805FF158(1);
            func_8070B308(1);
            func_805FF378(0xCE, 0);
            flagSet(st->unk12 + 0x51, 1, 2);
            BsA7e_A->unk155++;
        }
        break;
    case 0:
        func_80724A20();
        break;
    case 1:
        func_8002FC98(BsA7e_A, 0xF, 0x410, 0);
        BsA7e_A->unk154 = tbl[st->unk15++];
        BsA7e_A->unk155 = 0;
        break;
    case 0x27:
        switch (BsA7e_A->unk155) {
        case 0:
            BsA7e_A->unk155++;
            func_8002FC98(BsA7e_A, 0xF, -1, 0);
            st->unk18 = tbl[st->unk15++];
            st->unk19 = tbl[st->unk15++] + st->unk12 * 10;
            st->unk8 = tbl[st->unk15++];
            if (st->unk18 == 0xFF) {
                st->unk18 = 8 >> (s32)((D_807FBB4C->unk7C - 117.0f) / 50.0f);
            }
            func_8002FC98(BsA7e_A, st->unk18, 0x413, 0);
            D_807FDC90->unk2C = 0x14;
            break;
        case 1:
            if (D_807FDC90->unk2C) {
                D_807FDC90->unk2C--;
            } else {
                BsA7e_A->unk155++;
            }
            break;
        case 2:
            BsA7e_A->unk155++;
            func_8002FC98(BsA7e_A, st->unk18, 0x414, (st->unk19 + st->unk12 * 15) & 0xFF);
            D_807FDC90->unk2C = st->unk8;
        case 3:
            if (D_807FDC90->unk2C) {
                D_807FDC90->unk2C--;
            } else {
                BsA7e_A->unk154 = tbl[st->unk15++];
                BsA7e_A->unk155 = 0;
            }
            break;
        }
        break;
    case 0x28:
        func_8002FC98(BsA7e_A, (1 << st->unk12) & 0xFF, 2, 0);
        if (st->unk14 == st->unk12 && BsA7e_A->unk138 == 0) {
            BsA7e_A->unk154 = 0x37;
            BsA7e_A->unk155 = 0;
            break;
        }
        switch (BsA7e_A->unk155) {
        case 0:
            D_807FDC90->unk2C = tbl[st->unk15++];
            func_8002FC98(BsA7e_A, (1 << st->unk12) & 0xFF, 0x411, 0);
            BsA7e_A->unk155++;
            break;
        case 1:
        case 2:
            if (D_807FDC90->unk2C) {
                D_807FDC90->unk2C--;
            } else {
                if (BsA7e_A->unk155 == 1 && BsA7e_A->unk138) {
                    func_8002FC98(BsA7e_A, (1 << st->unk12) & 0xFF, 0x412, 0);
                }
                D_807FDC90->unk2C = 10;
                BsA7e_A->unk155++;
            }
            break;
        case 3:
            if (BsA7e_A->unk138 == 0) {
                st->unk14++;
                st->unk15 = 0;
                tbl = D_80035AA4[st->unk14];
            }
            BsA7e_A->unk154 = tbl[st->unk15++];
            BsA7e_A->unk155 = 0;
            break;
        }
        break;
    case 0x29:
        if (BsA7e_A->unk155 == 0) {
        }
        break;
    default:
        func_80027BA8(tbl, 0, 0);
        break;
    }
    actorUpdateModelMatrix(BsA7e_A, 0);
}

void func_80030888(void) {
    BossE_B100_Sub11C *sp1C;
    BossE_B100_Sub178 *sp18;
    s32 var_v0;

    sp1C = D_807FBB40->unk11C;
    sp18 = sp1C->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724DB0(2, 1, sp1C);
    }
    var_v0 = (D_807FBB40->unk15F == 1) ? sp18->unk14 : 0;
    func_8002FDF8(sp1C, (u8)var_v0);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368C0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368E4.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368F8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036910.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036950.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036968.s")
