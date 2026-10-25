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
void func_806319C4(Actor *, s32);
void func_80614A64(Actor *);

void func_806BFBB4(void) {
    func_8061421C(D_807FBB40);
    func_806319C4(D_807FBB40, 0);
    func_80614A64(D_807FBB40);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806BFBF4.s")

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
void func_80614EBC(void *, s32);
void func_8070D8C0(Actor *, s32, u8);
void func_8072B324(Actor *, s32);
s32 func_8072AB74(u8, f32, f32, s32, f32);
s32 func_8072D13C(u8, s32);
s32 func_80724A20(void);
s32 func_80629148(void);
s32 actorSpawn(s32, s32);
void func_80613C48(Actor *, s16, f32, f32);
void func_8067B238(void *, void *, f32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);

void func_806C10A0(u8 arg0, u16 arg1, s16 arg2) {
    f32 sp34;

    if (!(R1V->unk60 & 0x10)) {
        func_806F0C18(D_807FBB40);
        D_807FDC98->unk46 |= 0x200;
        func_8072B324(D_807FBB40, 0);
    }
    func_80724A20();
    switch (R1V->unk154) {
        case 5:
            func_8072AB74(0, 0.0f, 0.0f, 2, 0.0f);
        case 0:
            if (func_80629148()) {
                R1V->unk154 = 0x12;
                R1V->unk155 = 0;
            }
            break;
        case 2:
            func_8072AB74(2, R1S90->unkA, R1S90->unkE, 0, 0.0f);
            func_8072D13C(2, 0);
            break;
        case 0x12:
            switch (R1V->unk155) {
                case 0:
                    func_8070D8C0(D_807FBB40, arg1, arg0);
                    func_80614EBC(D_807FBB40, arg2);
                    R1V->unk155++;
                    break;
                case 2:
                    if (!(R1V->unk60 & 0x2000000)) {
                        func_80613C48(D_807FBB40, 0xE4, 0.0f, 2.0f);
                        actorSpawn(0xE1, 0x98);
                        func_8067B238(D_807FBB44, D_807FBB40, 0.21f);
                        actorGetNodePos(D_807FBB40, 1, &D_807FBB44->unk7C, &sp34, &D_807FBB44->unk84);
                        func_80614EBC(D_807FBB44, 0x298);
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

void func_8061D4E4(void *);
void actorDespawn(Actor *);
extern void *D_807F5D10;

void func_806C1300(void) {
    switch (R1V->unk155) {
        case 1:
            R1V->unk11C->unk60 &= ~4;
            R1V->unk155++;
            break;
        case 3:
            func_8061D4E4(D_807F5D10);
            R1V->unk11C->unk154 = 0x40;
            actorDespawn(D_807FBB40);
            break;
    }
    func_806319C4(D_807FBB40, 0);
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

s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);

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
        if (!func_8073110C(arg2, 2)) {
            func_8070D8C0(D_807FBB40, arg0, arg1);
            func_8073129C(arg2, 1, 2);
        }
    }
}

void func_806C15E8(void) {
    D_807FDC98->unk46 |= 0x1000;
    R1V->unk146 = 0;
    func_8072B324(D_807FBB40, 0);
    R1V->unkCC = 1;
}

void func_80729B00(void);
extern s32 D_8076A0A8;
void func_806BFBF4(void);

void func_806C1640(void) {
    func_80729B00();
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
    func_806319C4(D_807FBB40, 0);
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
s32 func_80611A44(void);
void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);

void func_806C1734(void) {
    R1C46aSub4 *sub;
    s32 rnd;
    R1C46aInner *inner;
    s16 sp2A;
    u8 sp29;

    func_80729B00();
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
                        rnd = func_80611A44() >> 15;
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
        if (func_8073110C(4, 0)) {
            func_806C151C(3, 3, 0);
        }
    }
    func_806319C4(D_807FBB40, 0);
}

void func_80724CA4(s32, s32);
void func_806F09F0(Actor *, u16);
void func_807149C8(s32, s32, s32, s32);
void func_80724E48(u8);
extern Actor *D_807FDC94;
extern u8 D_8071FBA0;

void func_806C19F4(void) {
    func_80729B00();
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
    func_806319C4(D_807FBB40, 0);
}

extern u8 D_8071FB34;

void func_806C1B50(void) {
    u8 kind;
    u32 thr;

    func_80729B00();
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
    func_806319C4(D_807FBB40, 0);
}

void func_80613194();
void renderCallbacksRegister(void *, void *, s32);
void func_807035C4();

void func_806C1CCC(void) {
    func_80729B00();
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
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C1E44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C226C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C27DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C28B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C2A64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C2B2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C2D7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C2DF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/C4620/func_806C3A8C.s")
