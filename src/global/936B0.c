#include "common.h"

#include "actor.h"
void func_80671C0C(Actor *, s32, f32 *, f32 *, f32 *);
void func_806319C4(Actor *, s32);

typedef struct M93A_Actor174 {
    s16 unk0;
    u8 pad2[0x25];
    u8 unk27;
    u8 unk28;
    u8 pad29[0xB];
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0x88 - 0x37];
    Actor *unk88;
    u8 pad8C[0x1A4 - 0x8C];
    u8 unk1A4;
} M93A_Actor174;

typedef struct M93A_ActorE4 {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x7C - 0x5C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xAC - 0x88];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
    u8 padBC[0xE4 - 0xBC];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0x174 - 0xEA];
    void *unk174;
} M93A_ActorE4;

void func_8068E9B0(Actor **arg0) {
    f32 sp2C;
    M93A_Actor174 *temp_v1;

    temp_v1 = (*arg0)->unk174;
    func_80671C0C(temp_v1->unk88, 9, &(*arg0)->unk7C, &sp2C, &(*arg0)->unk84);
    if ((*arg0)->unk80 < sp2C) {
        (*arg0)->unk80 = sp2C;
    }
    (*arg0)->unkE6 = temp_v1->unk88->unkE6;
    func_806319C4(*arg0, 0);
}

void func_8068EA38(M93A_ActorE4 **arg0) {
    M93A_ActorE4 *temp_a2;
    M93A_Actor174 *temp_v0;
    M93A_ActorE4 *temp_v1;
    M93A_Actor174 *temp_a1;

    temp_a2 = *arg0;
    temp_v0 = temp_a2->unk174;
    temp_v1 = (M93A_ActorE4 *)temp_v0->unk88;
    if (temp_v1 != NULL) {
        temp_a1 = temp_v1->unk174;
        if (temp_a1->unk34 < 5) {
            temp_a2->unk7C = temp_v1->unk7C;
            (*arg0)->unk80 = ((M93A_ActorE4 *)temp_v0->unk88)->unk80;
            (*arg0)->unk84 = ((M93A_ActorE4 *)temp_v0->unk88)->unk84;
            (*arg0)->unkE6 = ((M93A_ActorE4 *)temp_v0->unk88)->unkE6;
            (*arg0)->unkE8 = ((M93A_ActorE4 *)temp_v0->unk88)->unkE8;
            (*arg0)->unkE4 = ((M93A_ActorE4 *)temp_v0->unk88)->unkE4;
            (*arg0)->unkAC = ((M93A_ActorE4 *)temp_v0->unk88)->unkAC;
            temp_v1 = (M93A_ActorE4 *)temp_v0->unk88;
            if (temp_v1->unk58 == 0x12E) {
                (*arg0)->unkB8 = temp_v1->unkB8 * 10.0f;
            } else {
                (*arg0)->unkB8 = temp_v1->unkB8;
            }
            temp_a2 = *arg0;
        } else {
            temp_a2 = *arg0;
            temp_a2->unkB8 = 0.0f;
            temp_a2 = *arg0;
        }
    }
    func_806319C4((Actor *)temp_a2, 0);
}

typedef struct M93E_Vec3f {
    f32 x, y, z;
} M93E_Vec3f;
void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_8068EB3C(f32 arg0, f32 arg1, f32 arg2, M93E_Vec3f *arg3, M93E_Vec3f *arg4, M93E_Vec3f *arg5, M93E_Vec3f *arg6, f32 *arg7, f32 *arg8, f32 *arg9) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    func_8061F2B8(arg0, arg1, arg2, arg3->x, arg3->y, arg3->z, arg4->x, arg4->y, arg4->z, &sp48, &sp4C, &sp50);
    func_8061F2B8(arg0, arg1, arg2, arg5->x, arg5->y, arg5->z, arg6->x, arg6->y, arg6->z, &sp54, &sp58, &sp5C);
    if (((arg0 - sp48) * (arg0 - sp48) + (arg1 - sp4C) * (arg1 - sp4C) + (arg2 - sp50) * (arg2 - sp50)) <
        ((arg2 - sp5C) * (arg2 - sp5C) + ((arg0 - sp54) * (arg0 - sp54) + (arg1 - sp58) * (arg1 - sp58)))) {
        *arg7 = sp48;
        *arg8 = sp4C;
        *arg9 = sp50;
        return 0;
    }
    *arg7 = sp54;
    *arg8 = sp58;
    *arg9 = sp5C;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8068ECF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8068EF54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8068F72C.s")

typedef struct M93A_ActorSub4 {
    u8 pad0[0x1C];
    void *unk1C;
} M93A_ActorSub4;

typedef struct M93A_Actor {
    u8 pad0[4];
    M93A_ActorSub4 *unk4;
} M93A_Actor;

typedef struct M93A_StructC {
    u8 pad0[0xC];
    f32 unkC;
} M93A_StructC;

typedef struct M93A_Struct2 {
    s16 unk0;
    s16 unk2;
} M93A_Struct2;

typedef struct M93A_Sub1C {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} M93A_Sub1C;

s16 func_806CC190(s16, s16, f32);

extern Actor *D_807FBB40;

void func_8068FF40(u8 arg0, M93A_StructC *arg1, M93A_Struct2 *arg2) {
    f32 var_fv0;
    f32 var_fv1;
    M93A_Sub1C *temp_v1;

    temp_v1 = ((M93A_ActorSub4 *)D_807FBB40->unk4)->unk1C;
    if (arg0) {
        var_fv0 = 500.0f;
        var_fv1 = 0.0f;
    } else {
        var_fv0 = 0.0f;
        var_fv1 = (f32)((f64)arg1->unkC * (400.0 - (0.7 * (f64)D_807FBB40->unkB8)));
    }
    arg2->unk2 = func_806CC190(arg2->unk2, (s16)(s32)var_fv0, 5.0f);
    arg2->unk0 = func_806CC190(arg2->unk0, (s16)((s32)var_fv1 & 0xFFF), 3.0f);
    temp_v1->unk0 = -0x80;
    temp_v1->unk1 = 1;
    temp_v1->unk2 = (u16)arg2->unk2 * 16;
    temp_v1->unk4 = (u16)arg2->unk0 * 16;
    temp_v1->unk6 = 0;
    temp_v1->unk8 = 0;
}

void *func_80610FE8(s32);
void heapClearBlock(void *);

void func_80690058(Actor *arg0, s32 arg1) {
    ((M93A_Actor *)arg0)->unk4->unk1C = func_80610FE8(arg1 * 8);
    heapClearBlock(((M93A_Actor *)arg0)->unk4->unk1C);
}

void func_806EB0C0(s32, Actor *, u8);
void func_80604CBC(Actor *, s32, s32, s32, s32, s32, f32, s32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
void func_8067B238(Actor *, Actor *, f32);
extern s32 D_8076A0A8;

void func_80690094(Actor *arg0, Actor *arg1) {
    u8 sp37[4];
    M93A_Actor174 *temp_v0;

    sp37[3] = 0;
    temp_v0 = arg1->unk174;
    func_806EB0C0(0x4C, arg0, temp_v0->unk1A4);
    if (D_8076A0A8 == 0x6F) {
        sp37[3] = 0x3C;
    }
    func_80604CBC(arg0, 0x115, sp37[3], 1, 0, 0xFF, 1.0f, 0);
    func_80604CBC(arg0, 0x116, sp37[3], 1, 1, 0xFF, 1.0f, 0);
    animSetSpeed(arg0, 0, 1.0f);
    animSetLoopLimit(arg0, 0, -1);
    func_80690058(arg0, 2);
    func_8067B238(arg0, arg1, 0.15f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690190.s")

typedef struct M93A_Coord {
    s16 x;
    s16 y;
    s16 z;
    u8 yaw;
} M93A_Coord;

typedef struct M93A_ActorEE {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
} M93A_ActorEE;

M93A_Coord *func_806C96C4(s32);

void func_806903BC(M93A_ActorEE *arg0, M93A_Actor174 *arg1) {
    M93A_Coord *temp_v0;
    s16 temp;

    temp_v0 = func_806C96C4(arg1->unk36);
    arg0->unk7C = temp_v0->x;
    arg0->unk80 = temp_v0->y;
    arg0->unk84 = temp_v0->z;
    temp = (u32)temp_v0->yaw * 16.062746f;
    arg0->unkE6 = temp;
    arg0->unkEE = temp;
    arg1->unk0 = temp;
}

void actorSpawn(s32, s32);
void func_80690094(Actor *, Actor *);
extern Actor *D_807FBB44;

void func_80690470(Actor *arg0) {
    M93A_Actor174 *sp24 = arg0->unk174;
    M93A_Actor174 *temp_v0;
    s32 pad;
    Actor *temp_a0;

    actorSpawn(0x13F, 0xDA);
    temp_a0 = D_807FBB44;
    temp_v0 = temp_a0->unk174;
    temp_v0->unk28 = sp24->unk1A4;
    func_80690094(temp_a0, arg0);
    temp_v0->unk35 = 0;
    temp_v0->unk27 = 0;
    temp_v0->unk0 = arg0->unkE6;
    sp24->unk88 = temp_a0;
    temp_a0->unk60 &= ~0x20000;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690500.s")

void func_806907B8(void) {
    func_806319C4(D_807FBB40, 0);
}

extern u8 D_80750270;
void func_806907E0(void) {
    D_80750270 = 1;
}

extern f32 D_807FC7B0;
extern f32 D_807FC7B4;
extern f32 D_807FC7B8;
void func_806907F0(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC7B0 = arg0;
    D_807FC7B4 = arg1;
    D_807FC7B8 = arg2;
}

#include "actor.h"

s16 func_80665DE0(f32, f32, f32, f32);
void func_80690930(s16, s16, s16, f32, f32, f32, f32, f32, s32);
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} M93B_ActorListSub20;
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
typedef struct {
    s16 unk0;
    char pad2[6];
    f32 unk8;
    f32 unkC;
    u8 pad10;
    u8 unk11;
} M93B_Actor107Sub174;
extern s32 D_807F5D10;
void func_80661520(f32, f32, f32, f32, f32, f32);
void func_8061F0B0(s32, s32, s32);
void func_807149B8(s32);
void func_80714950(s32);
void func_80714998(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
extern u8 D_80750AD0;

void func_80690814(Actor *arg0, s32 arg1) {
    func_80671C0C(arg0, arg1, &D_807FC7B0, &D_807FC7B4, &D_807FC7B8);
}

void func_8069084C(s16 arg0, s16 arg1, f32 arg2, s16 arg3, f32 arg4, f32 arg5, s32 arg6) {
    M93B_ActorListSub20 sp28;

    sp28.unk0 = (f32)(((f64)arg3 / 4095.0) * 6.28318548202514648);
    sp28.unk4 = arg4;
    sp28.unkC = arg2;
    sp28.unk8 = arg5;
    sp28.unk10 = (f32)arg1;
    sp28.unk14 = (f32)(u32)D_80750270;
    actorListSpawnNodeEntry(arg0, D_807FC7B0, D_807FC7B4, D_807FC7B8, 0, arg2, arg6, &sp28);
    D_80750270 = 0;
}

void func_80690930(s16 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8) {
    f32 sp2C;
    f32 sp28;

    sp2C = sqrtf(((arg4 - D_807FC7B0) * (arg4 - D_807FC7B0)) + ((arg5 - D_807FC7B4) * (arg5 - D_807FC7B4)) + ((arg6 - D_807FC7B8) * (arg6 - D_807FC7B8)));
    sp28 = arg5 - D_807FC7B4;
    func_8069084C(arg1, arg2, arg3, arg0, sqrtf(((arg4 - D_807FC7B0) * (arg4 - D_807FC7B0)) + ((arg6 - D_807FC7B8) * (arg6 - D_807FC7B8))) / (sp2C / arg7), sp28 / (sp2C / arg7), arg8);
}

void func_80690A28(s16 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    func_80690930(func_80665DE0(arg3, arg5, D_807FC7B0, D_807FC7B8), arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690AB0.s")

void func_80690BE8(s16 arg0, s16 arg1, f32 arg2, Actor *arg3, s32 arg4, f32 arg5, s32 arg6) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    func_80671C0C(arg3, arg4, &sp34, &sp30, &sp2C);
    func_80690A28(arg0, arg1, arg2, sp34, sp30, sp2C, arg5, arg6);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690C60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80690F30.s")

u32 func_806119A0(void);
void func_807149C8(s32, s32, s32, s32);
extern s32 D_8071FFA0;
void func_80717D4C(void);
void func_806915B0(void) {
    s32 count;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80750AD0 != 0) {
        count = 3;
    } else {
        count = 6;
    }
    for (i = 0; i < count; i++) {
        dx = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        dy = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        dz = (f32)(((f64)(u32)((func_806119A0() / 10000) % 200) / 5.0) - 20.0);
        func_807149B8(1);
        func_807149C8(0x8C, 0x8C, 0x8C, 0x64);
        func_80714950(i * -0x14);
        func_80714998(3);
        func_8071498C(func_80717D4C);
        func_80714CC0(&D_8071FFA0, 2.0f, D_807FBB40->unk7C + dx, D_807FBB40->unk80 + 42.0f + dy, D_807FBB40->unk84 + dz);
    }
}

void func_80691830(s16 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    actorSpawn(0x102, arg0);
    func_8067B238(D_807FBB44, D_807FBB40, arg1);
    *(s16 *)((u8 *)D_807FBB44 + 0xF0) = arg0;
    D_807FBB44->unk16A = arg2;
    D_807FBB44->unk16B = arg3;
    D_807FBB44->unk16C = arg4;
    D_807FBB44->unk15F = arg5;
    D_807FBB44->unk168 = 1;
    *(f64 *)&D_807FBB44->unk160 = (f64)arg6;
    if (arg7 != 0.0f) {
        func_80661520(D_807FBB40->unk7C, D_807FBB40->unk84, arg7, 2.0f, arg8, arg9);
    }
    func_8061F0B0(D_807F5D10, 0x50, 0x14);
}

void func_80691930(u8 arg0, u8 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    M93B_Actor107Sub174 *sub;

    actorSpawn(0x107, 0);
    func_8067B238(D_807FBB44, D_807FBB40, 0.15f);
    sub = D_807FBB44->unk174;
    sub->unk11 = arg0;
    sub->unk8 = arg2;
    sub->unkC = arg3;
    sub->unk0 = arg1;
    D_807FBB44->unk80 = *(f32 *)D_807FBB40->unkA8;
    D_807FBB44->unk15F = arg4;
    D_807FBB44->unk168 = arg5;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806919E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806921DC.s")

void func_806921DC(s32);
void func_806919E0(void *);
extern u8 D_807201D4;

void func_80692500(void) {
    func_806921DC(0);
}

void func_80692520(void) {
    func_806921DC(1);
}

void func_80692540(void) {
    func_806919E0(&D_807201D4);
}

#include "actor.h"

typedef struct M93C_Actor124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} M93C_Actor124;

typedef struct M93C_PlayerActorSub {
    u8 pad0[0x104];
    s32 unk104;
} M93C_PlayerActorSub;

typedef struct M93C_PlayerActor {
    u8 pad0[0x174];
    M93C_PlayerActorSub *unk174;
} M93C_PlayerActor;

typedef struct M93C_PlayerEntry {
    u8 pad0[0x4];
    M93C_PlayerActor *actor;
    u8 pad8[0x2F0 - 0x8];
} M93C_PlayerEntry;

typedef struct M93C_ActorExtra {
    u32 unk0;
    u8 pad4[0x13 - 4];
    u8 unk13;
    f32 unk14;
    u8 pad18[4];
    s32 unk1C;
} M93C_ActorExtra;

typedef struct M93C_Actor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 unkFC;
    u8 unkFD;
    u8 padFE[0x11C - 0xFE];
    Actor *unk11C;
    u8 pad120[4];
    M93C_Actor124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x16E - 0x145];
    u8 unk16E;
    u8 unk16F;
    u8 pad170[0x174 - 0x170];
    void *unk174;
} M93C_Actor;

extern u8 D_80720020;
extern u8 D_807202D0;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern s16 D_80750344;
extern u32 D_8076A068;
extern ActorGlobalState D_807FBB70;
extern u8 D_807200EC;
extern u8 D_80720120;
extern M93C_PlayerEntry *D_807FC924;
extern u8 D_807FC928;
extern u8 D_8072029C;
extern u8 D_80720BA0;
extern s16 D_8075035C;
extern s16 D_80750370;
extern u8 D_807FBB85;

void func_8066EB40(Actor *, f32);
void func_8066E8E4(Actor *, f32, f32, f32, f32, s32);
void func_8066E854(Actor *, f32, f32, f32, s32);
void func_807149FC(s32);
s32 func_80714C08(void *, f32, Actor *, s32, s32);
void func_8067ACB4(Actor *);
void func_806651FC(Actor *);
void func_80665564(Actor *, f32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void actorDespawn(Actor *);
void func_8071D260(void);
void func_8071A8B0(void);
void func_8071ABDC(void);
void func_8061EF4C(s32, s32, s32, f32, f32, f32, f32, f32);
void func_806915B0(void);
void func_80608528(void *, s32, s32, s32, s32);
void func_80714A28(s32);
void func_80690C60(s32, Actor *, void *, s32);
s32 func_80665558(void);
s32 func_8066641C(void);

void func_80692564(void) {
    func_806919E0(&D_807201D4);
}

void func_80692588(void) {
    func_806919E0(&D_807201D4);
}

void func_806925AC(void) {
    M93C_ActorExtra *extra;
    f32 temp;

    extra = (M93C_ActorExtra *)D_807FBB40->unk174;
    func_806919E0(&D_807201D4);
    if (extra->unk13 == 1) {
        ((M93C_Actor *)D_807FBB40)->unkC0 += D_807502E4;
        temp = (f32)D_807502D0;
        if (((M93C_Actor *)D_807FBB40)->unkC0 < temp) {
            ((M93C_Actor *)D_807FBB40)->unkC0 = temp;
        }
    }
}

#define M93C_ACTOR ((M93C_Actor *)D_807FBB40)

void func_80692640(void) {
    u32 *sp44;
    u8 unkFC;
    Actor *other;

    sp44 = (u32 *)M93C_ACTOR->unk174;
    if (!(M93C_ACTOR->unk60 & 0x10)) {
        M93C_ACTOR->unk6A &= 0xFFFE;
        M93C_ACTOR->unkEE = (s16)((M93C_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93C_ACTOR->unkB8 = M93C_ACTOR->unk124->unk4;
        M93C_ACTOR->unkC0 = M93C_ACTOR->unk124->unk8;
        M93C_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 50.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714C08(&D_80720020, M93C_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        *sp44 = D_8076A068;
    }
    func_8067ACB4(D_807FBB40);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x96, 0x78, 0, 1.0f);
    unkFC = M93C_ACTOR->unkFC;
    if (unkFC != 0 || (M93C_ACTOR->unk6A & 1) || D_807FBB70.unk15 != 0 || D_807FBB70.unk200 == 9) {
        other = M93C_ACTOR->unk11C;
        if (other == NULL || other->unk58 != 0x2E || (other->unk58 == 0x2E && (unkFC != 0 || (M93C_ACTOR->unk6A & 1)))) {
            func_807149B8(0);
            func_807149FC(1);
            func_8071498C(func_8071D260);
            func_80714950(0xC);
            func_80714CC0(&D_807202D0, 0.75f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x61, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(D_807FBB40);
    }
    if ((u32)(*sp44 + D_80750344) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80692940.s")

void func_80692E50(void) {
    M93C_ActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;
    s32 var_s1;
    sp44 = (M93C_ActorExtra *)M93C_ACTOR->unk174;
    if (!(M93C_ACTOR->unk60 & 0x10)) {
        M93C_ACTOR->unk6A &= 0xFFFE;
        M93C_ACTOR->unkEE = (s16)((M93C_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93C_ACTOR->unkB8 = M93C_ACTOR->unk124->unk4;
        M93C_ACTOR->unkC0 = M93C_ACTOR->unk124->unk8;
        M93C_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_8072029C, M93C_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp44->unk14 = M93C_ACTOR->unk124->unkC;
        sp44->unk0 = D_8076A068;
        M93C_ACTOR->unk60 |= 0x01080000;
        M93C_ACTOR->unk16E = 0x3C;
        M93C_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)M93C_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_8075035C;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, &D_8072029C, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750370;
    }
    func_8067ACB4(D_807FBB40);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (M93C_ACTOR->unkFD != 0 ||
        func_80665558() != 0 ||
        ((M93C_ACTOR->unk6A & 1) && func_8066641C() == 1) ||
        D_807FBB85 != 0 ||
        (M93C_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < D_8076A068)) {
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                func_807149B8(1);
                func_80714950(0x05000000 + var_s1);
                func_80714998(1);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_80720BA0, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
        func_80608528(D_807FBB40, 0x91, 0xFF, 0x7F, 0x1E);
        actorDespawn(D_807FBB40);
    }
    if (D_807FC928 >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

void func_8069329C(void) {
    s32 i;

    func_807149B8(1);
    func_80714950(0x1006E);
    func_8071498C(func_8071A8B0);
    func_80714CC0(&D_80720120, 2.0f, D_807FBB40->unk7C, D_807FBB40->unk80 + 22.0f, D_807FBB40->unk84);

    for (i = 0; i < D_807FC928; i++) {
        func_8061EF4C(D_807FC924[i].actor->unk174->unk104, 7, 0x16, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 200.0f, 400.0f);
    }

    func_806915B0();

    if (D_80750AD0 == 0) {
        for (i = 0; i < 12; i++) {
            func_807149B8(1);
            func_80714950(0x0B010000 + i);
            func_8071498C(func_8071ABDC);
            func_80714CC0(&D_807200EC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
    }

    func_80608528(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_8069346C.s")

#include "actor.h"

typedef struct M93D_Actor124 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} M93D_Actor124;

typedef struct M93D_ActorExtra {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[0x13 - 0x05];
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 unk1C;
} M93D_ActorExtra;

typedef struct M93D_Actor {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ u16 unk68;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u8 pad6E[0x7C - 0x6E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xB8 - 0x88];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0xEE - 0xC4];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[4];
    /* 0xF4 */ s16 unkF4;
    /* 0xF6 */ s16 unkF6;
    /* 0xF8 */ u8 padF8[2];
    /* 0xFA */ s16 unkFA;
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x124 - 0xFE];
    /* 0x124 */ M93D_Actor124 *unk124;
    /* 0x128 */ u8 pad128[0x144 - 0x128];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x154 - 0x145];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x16E - 0x155];
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ void *unk174;
} M93D_Actor;

#define M93D_ACTOR ((M93D_Actor *)D_807FBB40)

extern s16 D_80750358;
extern s16 D_8075036C;

void func_8069329C(void);
extern u8 D_8071FB34;
extern u8 D_807201A0;

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80693EC0.s")

void func_806944BC(void) {
    M93D_ActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;
    s32 var_s1;
    sp44 = (M93D_ActorExtra *)M93D_ACTOR->unk174;
    if (!(M93D_ACTOR->unk60 & 0x10)) {
        M93D_ACTOR->unk6A &= 0xFFFE;
        M93D_ACTOR->unkEE = (s16)((M93D_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        M93D_ACTOR->unkB8 = M93D_ACTOR->unk124->unk4;
        M93D_ACTOR->unkC0 = M93D_ACTOR->unk124->unk8;
        M93D_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 60.0f);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714A28(4);
        func_80714C08(&D_807201A0, M93D_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sp44->unk14 = M93D_ACTOR->unk124->unkC;
        sp44->unk0 = D_8076A068;
        M93D_ACTOR->unk60 |= 0x01080000;
        M93D_ACTOR->unk16E = 0x3C;
        M93D_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)M93D_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750358;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (D_807FC928 >= 2) {
            var_a0 = 3;
        }
        func_80690C60(var_a0, D_807FBB40, &D_807201A0, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_8075036C;
    }
    func_8067ACB4(D_807FBB40);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (func_80665558() != 0 ||
        M93D_ACTOR->unkFD != 0 ||
        ((M93D_ACTOR->unk6A & 1) && func_8066641C() == 1) ||
        D_807FBB85 != 0 ||
        (M93D_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < D_8076A068)) {
        func_807149B8(1);
        func_80714950(0x1006E);
        func_8071498C(func_8071A8B0);
        func_80714CC0(&D_8071FB34, 0.45f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        func_80608528(D_807FBB40, 0x1E5, 0xFF, 0x7F, 0x1E);
        actorDespawn(D_807FBB40);
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                func_807149B8(1);
                func_80714950(0x0B000000 + var_s1);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_807200EC, 0.35f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            }
        }
    }
    if (D_807FC928 >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < D_8076A068) {
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80694948.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80694D20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806951B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806951E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80695724.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80695B50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80695BAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806960A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80696574.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80696A6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_806970CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/936B0/func_80697184.s")
