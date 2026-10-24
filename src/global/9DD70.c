#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699070.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699128.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699284.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_806998C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_806998F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699914.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_80699958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A614.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A750.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069A7C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069AB74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069AFF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B010.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B3FC.s")

extern Actor *D_807FBB40;
extern s32 D_8076A068;
extern s16 D_80744490;
s32 actorTableContains();
void func_8069B908(void);
void func_80689114(s16, f32, f32, f32, s16, f32, s32);
s32 func_8073110C(s32, s32);

s32 func_8069B85C(void) {
    ActorCallbackNode *node = D_807FBB40->unk13C;

    while (node != NULL) {
        if ((u32)node->callback == 0x8000) {
            Actor *actor;
            void *sub;
            if (actorTableContains(node->unk8) != 0) {
                actor = (Actor *)node->unk8;
                if (actor->unk5C & 1) {
                    sub = actor->unk174;
                    if ((u32)(D_8076A068 - *(s32 *)((u8 *)sub + 0x120)) < 2) {
                        return 1;
                    }
                }
            }
        }
        node = node->next;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069B908.s")

#ifdef NON_MATCHING
typedef struct M2_CamState {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} M2_CamState;

extern M2_CamState *D_807FC924;

void func_8069CD9C(void) {
    f32 frac;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 dist;
    u32 val;

    if (!(D_807FBB40->unk60 & 0x10)) {
        frac = D_807FBB40->unk4->unk34 / 0.15;
        frac = frac - 1.0;
        if (frac < 0.0) {
            frac = 0.0f;
        }
        val = (u32)(80.0f * frac);
        D_807FBB40->unk12C[4] = val;
        D_807FBB40->unk12C[5] = val;
        D_807FBB40->unk12A = 0x2BC;
    }
    dx = D_807FBB40->unk7C - D_807FC924->unk210;
    dz = D_807FBB40->unk84 - D_807FC924->unk218;
    dy = D_807FBB40->unk80 - D_807FC924->unk214;
    dist = dx * dx + dy * dy;
    if (dz * dz + dist < 18000.0) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    func_8069B908();
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069CD9C.s")
#endif

void func_8069CF54(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12C[4] = 0x3C;
        D_807FBB40->unk12C[5] = 0x3C;
        func_80689114(0x83, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84,
                      0, 1.0f, (s32)D_807FBB40);
    }
    func_8069B908();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (*(s32 *)((u8 *)D_807FBB40->unk124 + 0x8) == 1) {
            if (func_8073110C(0xFD, 0) != 0) {
                D_807FBB40->unk132 = 4;
            }
        }
    }
}

void func_8069D018(void) {
    Actor *actor = D_807FBB40;

    if (!(actor->unk60 & 0x10)) {
        actor->unk12A = 0x2BC;
    }
    func_8069B908();
}

void func_8069D058(void) {
    func_8069D018();
}

void func_8069D078(void) {
    func_8069D018();
}

void func_8069D098(void) {
    func_8069D018();
}

void func_8069D0B8(void) {
    func_8069D018();
}

void func_8069D0D8(void) {
    func_8069B908();
}

#ifdef NON_MATCHING
typedef struct M2_Sub {
    void *unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} M2_Sub;

s32 actorSpawn(s32, s32);
s32 func_806FDB8C(s16, s32, s32, f32, f32, f32);
s32 func_806FBD5C(s16, s32);
Mtx *func_80610FE8(s32);
extern Actor *D_807FBB44;

void func_8069D0F8(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    s32 len;
    M2_Sub *sub;

    if (actorSpawn(0xE8, 0) != 0) {
        sub = D_807FBB44->unk174;
        if (arg0 & 0x80) {
            f32 f = (f32)arg2;
            sub->unkA = func_806FDB8C((s16)(arg0 & 0xFF7F), arg3, 2, 160.0f, f, 0.0f);
            *(s16 *)((u8 *)D_807FBB44 + 0xEE) = 1;
            D_807FBB44->unk80 = f;
            return;
        }
        if (arg1 == 0) {
            D_807FBB44->unk7C = (f32)((D_80744490 - func_806FBD5C((s16)arg0, arg3)) * 2);
        } else {
            D_807FBB44->unk7C = (f32)(arg1 * 4);
        }
        D_807FBB44->unk80 = (f32)(arg2 * 4);
        D_807FBB44->unk84 = (f32)arg0;
        D_807FBB44->unk16A = 0xFF;
        D_807FBB44->unk16B = 0xFF;
        D_807FBB44->unk16C = 0xFF;
        len = strlen((char *)arg3) + 1;
        sub->unk0 = func_80610FE8(len);
        _strcpy((char *)sub->unk0, (char *)arg3);
        sub->unk4 = arg4;
        sub->unk6 = arg5;
        sub->unk8 = arg6;
        sub->unk9 = arg7;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069D0F8.s")
#endif

extern u8 D_807FC928;
s32 func_80714450();
s32 func_807142D8();
s32 func_8071432C();
s32 func_80712658();
void func_8069D0F8(u8, s16, s16, s32, u16, u16, u8, u8);

void func_8069D2AC(u8 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u8 arg6, u8 arg7) {
    if (D_807FC928 < 2) {
        if (func_80714450() == 0) {
            if (func_807142D8() == 0) {
                if (func_8071432C() != 0 || func_80712658() != 0) {
                    func_8069D0F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }
    }
}

typedef struct M2_Pos {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
} M2_Pos;

void heapFreeDeferred(Mtx *);

void *func_8069D358(void *arg0, M2_Pos *arg1, s16 arg2, f32 arg3) {
    Mtx *temp;
    f32 mtxA[4][4];
    f32 mtxB[4][4];

    temp = func_80610FE8(0x40);
    heapFreeDeferred(temp);
    guScaleF(mtxA, arg3, arg3, 1.0f);
    guTranslateF(mtxB, (f32)((f64)arg1->unk7C + 2.0 * (f64)arg2), arg1->unk80, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, temp);
    ((u32 *)arg0)[0] = 0xDA380003;
    ((u32 *)arg0)[1] = (u32)temp;
    return (u8 *)arg0 + 8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069D424.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069D930.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DA54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DC10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DC80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DD40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069DF58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069E018.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069E040.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9DD70/func_8069E088.s")
