#include "common.h"
#include "actor.h"

typedef struct Struct_5390 {
    f32 arr[3];
} Struct_5390;

typedef struct Actor174_5390 {
    f32 unk0;
    u16 unk4;
    u8 unk6;
} Actor174_5390;

typedef struct Actor338 {
    u8 pad[0x338];
    void *unk338;
} Actor338;

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Struct_5390 D_8074E88C;
extern void *D_8074E880[];
extern u32 D_8076A064;
extern u8 D_80750AD0;
extern s32 D_8071FC0C;
extern s32 D_8071FE08;
extern s32 D_8071FED0;
extern s32 D_8071FF18;
extern s32 D_8071FF40;
extern s32 D_8071FFA0;
extern s32 D_8072006C;
extern s32 D_80720120;
extern s32 D_80720558;
extern s32 D_8072073C;
extern s32 D_80720B58;
extern s32 D_807210EC;
extern s32 D_80721158;
extern s32 D_8072139C;

s32 actorSpawn();
void actorDespawn(Actor *);
void func_80602A94(s32, f32);
void func_80608528(void *, s32, s32, s32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
s32 func_806119A0(void);
s32 func_80611A44(void);
void func_80614EBC(Actor *, s32);
void func_806319C4(Actor *, s32);
void func_80663844(Actor *);
s32 func_80665AAC(Actor *);
void func_80671C0C(Actor *, s32, f32 *, f32 *, f32 *);
void func_8067B238(Actor *, Actor *, f32);
void func_8068581C(Actor *, s16, f32, f32, f32, f32, s32);
void func_8068588C(Actor *, s16, f32, f32, f32, f32, s32);
void func_806858E8(Actor *, s16, f32, f32, f32, f32, s32);
void func_80685F60(Actor *);
void func_80686390(Actor *, f32, f32, f32, f32);
void func_80688370(Actor *, s32, f32);
void func_8068842C(Actor *, s32, s32);
s32 func_80688540(Actor *, s32);
void func_806A081C(Actor *);
void func_80714950();
void func_8071495C(void);
void func_8071496C(s32);
void func_8071498C(void (*)(void));
void func_80714998(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
Actor338 *func_80714CC0(void *, f32, f32, f32, f32);
void func_80717930(void);
void func_80717D4C(void);
void func_80718080(void);
void func_8071827C(void);
void func_807184F4(void);
void func_8071910C(void);
void func_80719A0C(void);
void func_80719B88(void);
void func_80719C00(void);
void func_80719EF4(void);
void func_8071AF30(void);
void func_8071DB74(void);
void func_8071DC90(void);
void func_8071E110(void *, s32, s32, f32, f32, s32);
void func_8071E1C8(void);
void func_8071EA24(void);
void func_8071EFDC(void);

void func_80684550(s32 arg0, u8 arg1, f32 arg2) {
    func_807149B8(1);
    func_8071498C(func_8071AF30);
    func_80714950(arg0);
    func_80714A28(4);
    func_80714C08(&D_80720120, arg2, D_807FBB40, arg1, 0);
}

void func_806845B8(u8 arg0, u8 arg1) {
    f32 sp2C;
    u8 sp2B;

    if (!(D_8076A064 & 3)) {
        sp2C = (f32)(D_807FBB40->unk4->unk38 / 0.15);
        sp2B = ((func_80611A44() >> 15) % 0x7FFF) % ((arg1 - arg0) + 1) + arg0;
        func_80714998(3);
        func_807149C8(0xE6, 0xE6, 0xE6, 0xE6);
        func_8068588C(D_807FBB40, sp2B, sp2C, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

void func_806846B4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, Actor *arg5, u8 arg6) {
    s32 var_a1 = 0xAD;

    if (arg5 != NULL) {
        switch (arg5->unk58) {
        case 5:
        case 0xF4:
            var_a1 = 0xD1;
            break;
        case 4:
        case 0xF3:
            var_a1 = 0xD0;
            break;
        case 6:
        case 0xF5:
            var_a1 = 0xCF;
            break;
        case 3:
        case 0xF2:
            var_a1 = 0xAE;
            break;
        }
    }
    actorSpawn(0xFF, var_a1, arg5);
    D_807FBB44->unk11C = (s32)arg5;
    D_807FBB44->unk4->unk34 = arg3;
    D_807FBB44->unk4->unk3C = arg3;
    D_807FBB44->unk4->unk38 = arg4;
    D_807FBB44->unk7C = arg0;
    D_807FBB44->unk80 = arg1;
    D_807FBB44->unk84 = arg2;
    if ((arg5 != NULL) && (arg5->unk5C & 1)) {
        if (arg6 != 0) {
            D_807FBB44->unk168 = 0xF;
            *(f64*)&D_807FBB44->unk160 = 1.11;
            D_807FBB44->unk15F = 1;
            return;
        }
        D_807FBB44->unk168 = 0x19;
        *(f64*)&D_807FBB44->unk160 = 1.09;
        return;
    }
    D_807FBB44->unk168 = 0x20;
    *(f64*)&D_807FBB44->unk160 = 1.07;
    D_807FBB44->unk15F = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80684850.s")

void func_80684900(u8 arg0) {
    if (arg0) {
        func_80714950(((s32)(func_80611A44() >> 15) % 10) + 0x8008);
    } else {
        func_80714950(((s32)(func_80611A44() >> 15) % 8) + 6);
    }
    func_807149FC(2);
    func_8071498C(func_80717930);
    func_807149B8(1);
    func_80714A28(4);
    func_80714C08(&D_8072139C, (f32)(((f64)((s32)(func_80611A44() >> 15) % 50) / 80.0) + 0.1), D_807FBB40, 8, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80684A00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80684BB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80684D98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80685020.s")

void func_806850D0(void) {
    f32 temp;
    s32 i;

    temp = (f32)(D_807FBB40->unk4->unk38 / 0.15);
    func_807149B8(0);
    func_807149FC(1);
    func_80714CC0(&D_8071FE08, (f32)((f64)temp * 0.75), D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    for (i = 0; i < 7; i++) {
        func_807149B8(1);
        func_807149FC(0xA);
        func_8071498C(func_8071910C);
        func_80714998(2);
        func_80714950(0);
        func_80714CC0(&D_8072073C, (f32)((f64)temp * 0.15), D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    }
}

void func_80685210(f32 arg0, s16 arg1, s16 arg2) {
    if (((D_8076A064 % 3) == 0) && ((f32)arg1 < D_807FBB40->unkB8)) {
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_80717D4C);
        func_80714950(-0x32);
        func_80714A28(4);
        func_80714C08(&D_8071FF18, arg0, D_807FBB40, arg2, 0);
    }
}

void func_806852C4(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s16 var_s0;

    for (var_s0 = 0; var_s0 < 8; var_s0++) {
        func_8071498C(func_80719A0C);
        func_80714950(var_s0);
        func_807149B8(1);
        func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
        func_80714CC0(&D_8071FFA0, arg0, arg1, arg2, arg3);
    }
}

void func_80685390(void) {
    Actor174_5390 *temp_v0 = D_807FBB40->unk174;
    Struct_5390 sp20 = D_8074E88C;

    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_v0->unk0 = D_807FBB40->unk4->unk38;
    }
    temp_v0->unk4++;
    switch (D_807FBB40->unk154) {
    case 0:
        D_807FBB40->unk4->unk38 = sp20.arr[temp_v0->unk6] * (temp_v0->unk0 * (f32)(u32)temp_v0->unk4 * 0.33333334f);
        if ((f32)(u32)temp_v0->unk4 > 3.0f) {
            D_807FBB40->unk154 = 1;
            temp_v0->unk4 = 0;
            func_8068842C(D_807FBB40, 0, 1);
            func_80688370(D_807FBB40, 0, 0.5f);
        }
        break;
    case 1:
        if (func_80688540(D_807FBB40, 0) == 0) {
            actorDespawn(D_807FBB40);
        }
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_80685520(f32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 temp_t6;
    s32 var_s0;

    temp_t6 = arg1;
    if (D_80750AD0 == 0) {
        if (temp_t6 > 0) {
            func_806852C4(arg0, arg2, arg3, arg4);
        }
        if (temp_t6 >= 2) {
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                func_8071498C(func_80719B88);
                func_80714950(var_s0);
                func_807149B8(1);
                func_807149FC(-1);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                func_80714CC0(&D_8071FF40, (f32)((f64)arg0 * 0.5), arg2, arg3, arg4);
            }
        }
        if (temp_t6 >= 3) {
            for (var_s0 = 0; var_s0 < 9; var_s0++) {
                func_8071498C(func_80719C00);
                func_80714950(var_s0);
                func_807149B8(1);
                func_807149FC(-1);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                func_80714CC0(D_8074E880[var_s0 % 3], arg0, arg2, arg3, arg4);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80685708.s")

void func_8068581C(Actor *arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    func_80714998(2);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    func_8068588C(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

void func_8068588C(Actor *arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    func_807149B8(1);
    func_806858E8(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

void func_806858E8(Actor *arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Actor338 *temp;

    if (arg0 != NULL && arg1 != 0) {
        func_80671C0C(arg0, arg1, &arg3, &arg4, &arg5);
    }
    func_8071498C(func_80718080);
    func_80714950(arg6);
    temp = func_80714CC0(&D_8071FFA0, arg2, arg3, arg4 + 5.0f, arg5);
    temp->unk338 = arg0;
}

void func_80685984(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 pad[2];
    s32 sp24;
    s32 mod100k;
    s32 mod10;
    if (((func_80611A44() >> 15) % 100) >= 51) {
        func_80714998(2);
        func_80714950((func_80611A44() >> 15) % 360);
        func_807149B8(1);
        func_807149C8(0x9B, 0x9B, 0x9B, 0xC8);
        func_8071498C(func_80719EF4);
        sp24 = func_80611A44();
        mod100k = 100000;
        mod10 = 10;
        func_80714CC0(&D_8071FFA0, arg0, (f32)(((sp24 >> 15) % mod100k) % mod10) + (arg1 - 5.0f), arg2, (f32)(((func_80611A44() >> 15) % mod100k) % mod10) + (arg3 - 5.0f));
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80685B44.s")

void func_80685D84(Actor *arg0) {
    if (!(arg0->unk64 & 4)) {
        if ((arg0->unk60 & 0x10) && ((arg0->unk6A ^ arg0->unk6C) & 4)) {
            func_80686390(arg0, 0.0f, arg0->unk7C, arg0->unkAC, arg0->unk84);
        }
        if (arg0->unk6A & 4) {
            func_80685F60(arg0);
        }
    }
    if ((arg0->unk68 & 0x40) && func_80665AAC(arg0) && !(arg0->unk6A & 0x800) && (arg0->unkA4 <= arg0->unk80)) {
        func_806A081C(arg0);
    }
    if (arg0->unk68 & 0x80) {
        func_80663844(arg0);
    }
}

void func_80685E78(Actor *arg0) {
    s32 pad;
    f32 sp28;

    sp28 = (arg0->unk4 != NULL) ? (f64)arg0->unk4->unk38 / 0.15 : 1.0;
    func_80714998(3);
    func_807149B8(1);
    func_807149FC(1);
    func_8071498C(func_807184F4);
    func_80714A28(4);
    func_807149C8(0xC8, 0xFF, 0xFF, 0xC8);
    ((Actor338 *)func_80714CC0(&D_8071FED0, (f64) sp28 * 0.6, arg0->unk7C, arg0->unkAC, arg0->unk84))->unk338 = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80685F60.s")

void func_8068613C(Actor *arg0) {
    f32 var_fs0;
    f32 scale01;
    u8 count;
    u8 i;

    var_fs0 = (arg0->unk4 != NULL) ? (f64)arg0->unk4->unk38 / 0.15 : 1.0;
    if (arg0->unk58 == 0x1E) {
        var_fs0 *= 2;
        func_8068588C(arg0, 0, 4.0f, arg0->unk7C, arg0->unk80, arg0->unk84, -0x96);
        actorDespawn(arg0);
    }
    func_80608528(arg0, 0xC, 0xFF, 0x7F, 1);
    func_807149B8(1);
    func_807149FC(1);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
    func_80714CC0(&D_8071FC0C, (f64)var_fs0 * 0.65, arg0->unk7C, arg0->unkAC + 15.0f, arg0->unk84);
    if (D_80750AD0 == 0) {
        count = (func_806119A0() & 3) + 4;
        i = 0;
        if (count > 0) {
            scale01 = (f64)var_fs0 * 0.1;
            do {
                func_807149B8(1);
                func_807149FC(-1);
                func_8071498C(func_8071DB74);
                func_80714A28(4);
                func_80714CC0(&D_80720B58, scale01, arg0->unk7C, arg0->unkAC, arg0->unk84);
                i++;
            } while (i < count);
        }
    }
}

void func_80686340(void) {
    func_807149B8(1);
    func_807149FC(0x14);
    func_8071498C(func_8071827C);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    func_80714A28(4);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80686390.s")

void func_8068696C(Actor *arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(arg0);
        func_8071498C(func_8071DC90);
        func_80714CC0((void *)D_8074E880[i % 3], 0.7f, arg0->unk7C, arg0->unk80, arg0->unk84);
    }
}

void func_80686A5C(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(arg0);
        func_8071498C(func_8071E1C8);
        func_8071E110(func_80714CC0((void *)D_8074E880[i], 0.7f, arg0->unk7C, arg0->unk80, arg0->unk84), 1, (u16)(i * 1365.3334f), arg1, arg2, arg3);
    }
    for (i = 0; i != 3; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(arg0);
        func_8071498C(func_8071E1C8);
        func_8071E110(func_80714CC0((void *)D_8074E880[i], 0.7f, arg0->unk7C, arg0->unk80, arg0->unk84), 0, (u16)(i * 1365.3334f), arg1, arg2, arg3);
    }
}

void func_80686CF8(Actor *arg0) {
    s32 i;

    for (i = 0; i < 30; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_8071EA24);
        func_8071496C((s16)(i / 7));
        func_80714CC0((void *)D_8074E880[i % 3], 1.4f, arg0->unk7C, arg0->unk80 + 10.0f, arg0->unk84);
    }
}

void func_80686E40(f32 arg0, f32 arg1, f32 arg2, void *arg3) {
    s32 i;
    s32 var_s4;
    s32 var_s5;

    var_s5 = (D_80750AD0 != 0) ? 3 : 16;
    var_s4 = (D_80750AD0 != 0) ? 0 : 2;

    for (i = 0; i < var_s5; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_80717930);
        func_8071496C((s16)(i >> var_s4));
        func_80714950(arg3);
        func_80714CC0((void *)D_8074E880[i % 3], 0.5f, arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_80686F90.s")

void func_80687080(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = ((func_80611A44() >> 15) % 75) + 0xB4;
        D_807FBB40->unk16C = 0x28;
        D_807FBB40->unk128 = 0xFF;
    }
    if ((f64)D_807FBB40->unk4->unk38 > 1.0) {
        D_807FBB40->unk128 -= 0x28;
        if (D_807FBB40->unk128 < 0) {
            actorDespawn(D_807FBB40);
        }
    } else {
        D_807FBB40->unk4->unk38 = (f32)(D_807FBB40->unk4->unk38 * 1.8);
        D_807FBB40->unk4->unk34 = (f32)(D_807FBB40->unk4->unk34 * 1.1);
        D_807FBB40->unk4->unk3C = (f32)(D_807FBB40->unk4->unk3C * 1.1);
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_806871DC.s")

void func_80687400(void) {
    func_80609140(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_80721158, 1.0f, 160.0f, 120.0f, -10.0f);
}

void func_80687474(Actor *arg0, f32 arg1) {
    actorSpawn(0xB3, 0x5D);
    D_807FBB44->unk60 |= 0x400;
    func_80614EBC(D_807FBB44, 0x334);
    func_8067B238(D_807FBB44, arg0, arg0->unk4->unk38 * arg1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_806874EC.s")

void func_806877C8(arg0)
u8 arg0;
{
    func_807149B8(1);
    func_80714C08(&D_8072006C, 1.0f, D_807FBB40, arg0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/89250/func_8068780C.s")

void func_80687C48(void) {
    func_80609140(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    func_80602A94(0x97, 1.0f);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_80720558, 1.0f, 160.0f, 120.0f, -10.0f);
}

void func_80687CC8(void) {
    func_80609140(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    func_80602A94(0x97, 1.0f);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_807210EC, 1.0f, 160.0f, 120.0f, -10.0f);
}
