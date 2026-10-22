#include "common.h"
#include "actor.h"

typedef struct ActorMapFlag {
    u16 map;
    u8 unk2;
    s16 unk4;
} ActorMapFlag;

typedef struct TagBarrelState {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    union {
        f32 unkC;
        struct {
            u8 unkC_b;
            u8 unkD;
        };
    };
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
} TagBarrelState;

typedef struct ActorD580 {
    /* 0x000 */ u8 pad0[0xCA];
    /* 0x0CA */ u8 unkCA;
} ActorD580;

typedef struct ActorAnimLookup {
    struct {
        s16 unk0;
        s16 unk2;
    } arr[5];
} ActorAnimLookup;

typedef struct ActorGroup5 {
    u8 pad0[8];
    Actor *unk8[5];
} ActorGroup5;

typedef struct ActorKongAction {
    u8 pad0[4];
    u8 unk4;
    u8 unk5;
} ActorKongAction;

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern ActorD580 *D_807FD580;
extern void *D_807FBB4C;
extern u16 *D_807FBB54;
extern s32 D_8076A0A8;
extern s32 D_8071FE08;
extern u8 D_8074E77C;
extern ActorMapFlag D_8074E7A0[];
extern s16 D_8074E7E0[];
extern ActorKongAction D_8074E814[];
extern ActorAnimLookup D_8074E834;
extern s32 D_8074E85C[];
extern u8 D_80720120;
extern u8 D_80720340;
extern u8 D_8072038C;

s16 func_805FF018(s32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 func_80611A44(void);
void func_80614EBC();
void func_8061CC40(void *, s32, s32);
void func_806319C4(Actor *, s32);
void func_80665564(Actor *, f32);
void func_80671C0C(Actor *, s32, f32 *, f32 *, f32 *);
void func_806782C0(Actor *);
void func_8067B4C8(void);
void func_8067BA7C(s32);
s32 func_8067BF84(s32, u8 *, u8 *, u8 *);
void func_8067C71C(void);
void func_8067DCC0(void);
void func_8067DF44(f32, f32, f32, f32, u8, u8);
void func_8067E348(void);
void func_8067E3D0(void);
void func_8067E43C(void);
void func_8067E784(void);
void func_806809F0(void);
void func_8068412C(void);
void func_806883F4(Actor *, s32, s16, f32);
void func_8068842C(Actor *, s32, s32);
void func_80688460(Actor *, s32, s32);
s32 func_80688E68(Actor *);
void func_8068A764(Actor *, u8);
void func_8069B908(void);
void func_806F8D58(s32, s32);
s32 func_8070E750(s32, s32, s32);
void func_80714950(s32);
void func_8071496C(s32);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8071ABDC(void);
void func_8071B89C(void);
void func_8071BB14(void);
s32 func_8073110C(s16, s32);
void func_8073129C(s16, s32, s32);

s32 func_8067B450(void *actor) {
    s32 count = 4;
    s32 val = func_80688E68(actor);
    s32 i;

    for (i = 0; i < count; i++) {
        if (D_8076A0A8 == D_8074E7A0[i].map && val == D_8074E7A0[i].unk2) {
            return func_8073110C(D_8074E7A0[i].unk4, 0);
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067B4C8.s")

void func_8067BA3C(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x7D0;
    }
    func_8067B4C8();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067BA7C.s")

void func_8067BC68(void) {
    func_8067BA7C(0x13);
}

void func_8067BC88(void) {
    func_8067BA7C(0x13);
}

void func_8067BCA8(void) {
    func_8067BA7C(0x13);
}

void func_8067BCC8(void) {
    func_8067BA7C(0x13);
}

void func_8067BCE8(void) {
    func_8067BA7C(0x13);
}

void func_8067BD08(void) {
    func_8067BA7C(0x13);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067BD28.s")

void func_8067BDB8(void) {
    func_8067BA7C(0x95);
    func_80665564(D_807FBB40, 0.0f);
    D_807FBB40->unk80 = D_807FBB40->unkA4;
}

void func_8067BDF8(void) {
    u8 sp1F;
    u8 *ptr;

    sp1F = 0;
    ptr = D_807FBB40->unk174;
    func_8067BF84(0x13, ptr, ptr + 1, &sp1F);
}

void func_8067BE30(void) {
    u8 *t0 = D_807FBB40->unk174;
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x7D0;
        *(s16 *)t0 = 0x1A;
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        switch (D_807FBB70.unk258[i]) {
        case 1:
            *(s16 *)t0 = 0x60;
            break;
        case 2:
            *(s16 *)t0 = 0;
            break;
        case 3:
            *(s16 *)t0 = 0x1A;
            break;
        }
    }
    if (*(s16 *)t0 != 0) {
        if (func_8067BF84(*(s16 *)t0, t0 + 2, t0 + 3, t0 + 4)) {
            *(s16 *)t0 = 0x1A;
        }
    } else {
        if (D_807FBB70.unk38 != 0) {
            t0[4] = 1;
        }
        func_806319C4(D_807FBB40, 0);
    }
}

void func_8067BF4C(void) {
    u8 *ptr = D_807FBB40->unk174;
    func_8067BF84(0x1A, ptr + 2, ptr + 3, ptr + 4);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067BF84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067C2B8.s")

void func_8067C67C(void) {
    func_8067C71C();
}

void func_8067C69C(void) {
    func_8067C71C();
}

void func_8067C6BC(void) {
    func_8067C71C();
}

void func_8067C6DC(void) {
    func_8069B908();
}

void func_8067C6FC(void) {
    func_8067C71C();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067C71C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067DCC0.s")

void func_8067DF44(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f64 sp80;
    f32 sp7C;
    f32 temp_fs2;
    f32 temp_fs1;
    f32 temp_fs0;
    s32 var_s0;

    if (arg5 != 0) {
        func_806086CC(arg0, arg1, arg2, 0xF6, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
    }
    func_807149B8(1);
    func_8071498C(func_8071B89C);
    func_80714CC0(&D_80720120, 0.0f, arg0, arg1 + 5.0f, arg2);
    sp80 = (f64) arg3;
    sp7C = sp80 * 1.5;
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        temp_fs1 = (f32) (((s32) (func_80611A44() >> 15) % 20) - 10) * arg3;
        temp_fs2 = (f32) (((s32) (func_80611A44() >> 15) % 20) - 10) * arg3;
        temp_fs0 = (f32) (((s32) (func_80611A44() >> 15) % 20) - 10) * arg3;
        func_8071496C(4);
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_8071BB14);
        func_80714CC0(&D_80720340, sp7C, arg0 + temp_fs1, arg1 + temp_fs2, arg2 + temp_fs0);
    }
    func_8071496C(4);
    func_807149B8(1);
    func_807149FC(1);
    func_8071498C(func_8071BB14);
    func_80714CC0(&D_80720340, sp7C, arg0, arg1, arg2);
    if (arg4 != 0) {
        for (var_s0 = 0; var_s0 != 12; var_s0++) {
            func_807149B8(1);
            func_807149FC(2);
            func_80714950(var_s0 + 0x0B020000);
            func_8071498C(func_8071ABDC);
            func_80714998(1);
            func_80714CC0(&D_8072038C, (f32)(sp80 * 0.5), arg0, arg1, arg2);
        }
    }
}

void func_8067E278(arg0, arg1)
u8 arg0;
u8 arg1;
{
    func_8067DF44(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (f32) ((f64) D_807FBB40->unk4->unk38 / 0.15), arg0, arg1);
}

void func_8067E2E4(s32 arg0, u8 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    func_80671C0C(D_807FBB40, arg1, &sp2C, &sp28, &sp24);
    func_8067DF44(sp2C, sp28, sp24, arg2, 0, 1);
}

void func_8067E348(void) {
    TagBarrelState *temp_v0 = D_807FBB40->unk174;

    D_807FBB40->unk4->unk34 = temp_v0->unkC;
    D_807FBB40->unk4->unk38 = temp_v0->unkC;
    D_807FBB40->unk4->unk3C = temp_v0->unkC;
    D_807FBB40->unk80 = temp_v0->unk14;
    temp_v0->unk8 = 0;
    temp_v0->unk18 = 0;
    temp_v0->unk10 = temp_v0->unkC;
    D_807FBB40->unk154 = 0;
    D_807FBB40->unk144 = 2;
    D_807FBB40->unk60 &= ~0x200000;
}

void func_8067E3D0(void) {
    func_8067E348();
    D_807FBB40->unk154 = 0x14;
    D_807FBB40->unk144 = 1;
    D_807FBB40->unk60 &= ~0x8000;
    D_807FBB40->unk128 = 0;
    func_806F8D58(5, 0);
}

void func_8067E43C(void) {
    s16 i;

    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0xFF) {
            func_8067E3D0();
        }
    }
}

void func_8067E4D4(void) {
    func_8067E784();
    if (D_807FBB40->unk154 == 0) {
        func_8067E43C();
    }
}

void func_8067E510(void) {
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk4->unk34 = (f32)(D_807FBB40->unk4->unk34 * 1.5);
        D_807FBB40->unk4->unk38 = (f32)(D_807FBB40->unk4->unk38 * 1.5);
        D_807FBB40->unk4->unk3C = (f32)(D_807FBB40->unk4->unk3C * 1.5);
        D_807FBB40->unk12A = 0x7D0;
    }
    if (D_807FBB40->unk154 == 0) {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1) {
                func_807149B8(0);
                func_807149FC(1);
                func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
                func_806782C0(D_807FBB40);
            }
        }
    }
    func_8067E784();
}

void func_8067E69C(void) {
    func_8067E784();
    func_8067E43C();
}

void func_8067E6C4(void) {
    func_8067E784();
}

void func_8067E6E4(void) {
    func_8067E784();
}

void func_8067E704(void) {
    func_8067E784();
}

void func_8067E724(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x320;
    }
    func_8067E784();
}

void func_8067E764(void) {
    func_8067E784();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067E784.s")

void func_8067FAC8(void) {
    s16 i;

    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 1) {
            func_8067DCC0();
            func_806782C0(D_807FBB40);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067FB6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80680774.s")

void func_8068086C(void) {
    if (D_8074E77C >= 5) {
        D_807FBB40->unk132 = 4;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x7F;
    } else {
        D_807FBB40->unk60 |= 0x8000;
        D_807FBB40->unk132 = 1;
    }
    if (D_807FD580->unkCA != 0) {
        D_807FBB40->unk132 = 4;
    }
}

u8 func_80680908(void) {
    u8 ret = 0x64;

    switch (D_8076A0A8) {
    case 0x1A:
        if (func_80688E68(D_807FBB40) == 0xD || func_80688E68(D_807FBB40) == 0xF) {
            ret = 2;
        }
        break;
    case 0x3B:
        if (func_80688E68(D_807FBB40) == 3) {
            ret = 2;
        }
        break;
    case 0x30:
        if (func_80688E68(D_807FBB40) == 0x12) {
            ret = 2;
        }
        break;
    case 0xAD:
    case 0xC3:
        ret = 2;
        break;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806809F0.s")

void func_80681B14(void) {
    TagBarrelState *sub = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        if (func_8073110C(0x302, 0) != 0) {
            func_806782C0(D_807FBB40);
            return;
        }
    }
    func_806809F0();
    if (D_807FBB40->unk154 == 0xC && sub->unkD < 3) {
        func_8073129C(D_8074E7E0[sub->unkA], 1, 2);
        func_8067DCC0();
        func_806782C0(D_807FBB40);
    }
}

void func_80681BD8(void) {
    TagBarrelState *sub = D_807FBB40->unk174;
    s32 sp28;
    s32 count;
    s32 i;

    func_806809F0();
    if (func_8073110C(0x17F, 0) == 0) {
        D_807FBB40->unk154 = 0x14;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
    } else {
        if (func_8073110C(0x187, 0) == 0) {
            count = 0;
            if (D_807FBB40->unk154 == 0xB) {
                i = 0;
                do {
                    count += (func_8073110C((s16)(i + 0x182), 0) != 0);
                } while (++i != 4);
                if (count == 4) {
                    func_8061CC40(D_807FBB4C, 3, 1);
                    func_8073129C(0x187, 1, 0);
                }
            }
        }
        switch (sub->unk6) {
        case 0xB1:
            sp28 = 0x182;
            break;
        case 0xB6:
            sp28 = 0x183;
            break;
        case 0xB4:
            sp28 = 0x184;
            break;
        case 0xB5:
            sp28 = 0x185;
            break;
        }
        if (func_8073110C(sp28, 0) != 0) {
            sub->unkC_b = 1;
            sub->unkA = 0;
            if (D_807FBB40->unk154 == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        } else if (D_807FBB40->unk154 == 0x14) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk154 = 0x15;
        }
    }
    if (D_807FBB40->unk154 == 0xC && sub->unkD < 3) {
        func_8067DCC0();
        func_806782C0(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80681E18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806822FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80682AB4.s")

void func_80682DF4(void *arg0, u16 *arg1, s32 arg2) {
    arg2 = arg2 * 7;
    arg2 += *arg1 - 2;
    func_80614EBC(arg0, D_807FBB54[arg2], arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80682E38.s")

void func_8068304C(void) {
    ActorAnimLookup sp2C;
    u8 *sp28;

    if (!(D_807FBB40->unk60 & 0x10)) {
        sp2C = D_8074E834;
        sp28 = D_807FBB40->unk174;
        D_807FBB40->unk60 |= 0x1000;
        func_8068842C(D_807FBB40, 0, 1);
        func_80688460(D_807FBB40, 0, 1);
        func_806883F4(D_807FBB40, 0, sp2C.arr[*sp28].unk2, 0.0f);
        func_80614EBC(D_807FBB40, 0x329);
    }
    D_807FBB40->unk16D = D_807FBB40->unk15F;
    D_807FBB40->unkE6 += 0x32;
    D_807FBB40->unkE6 &= 0xFFF;
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80683158.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806832F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806833DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806836D0.s")

s32 func_80683A80(ActorGroup5 *arg0, s32 arg1) {
    s32 type = arg0->unk8[arg1]->unk58;
    s32 ret = 0;

    if ((type ^ 0x13C) == 0) {
        ret = func_8070E750(2, D_8074E85C[arg1], 1);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80683AD8.s")

void func_8068408C(Actor *arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (func_8073110C(func_805FF018(arg0->unk58, i), 0)) {
            func_8068A764(arg0, D_8074E814[i].unk4);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8068412C.s")

void func_806844EC(void) {
    func_8068412C();
}

void func_8068450C(void) {
    func_8068412C();
}

void func_8068452C(void) {
    func_8068412C();
}
