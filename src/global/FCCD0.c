#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

extern void *D_80754280;

s32 slotQueueGetAddress(arg0)
u8 arg0;
{
    return (arg0 * 0x2D0) + (s32)D_80754280;
}

typedef struct FcAPlayer {
    u8 pad0[0x284];
    f32 unk284;
    u8 pad288[0x68];
} FcAPlayer;

void func_806F8004(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp88[4][4];
    f32 sp48[4][4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    sp34 = ((FcAPlayer *)D_807FC924)[D_807FC929].unk284;
    guRotateF(sp88, arg0, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp88, 0.0f, 0.0f, -sp34, &sp3C, &sp40, &sp44);
    guRotateF(sp48, arg1, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp48, sp3C, sp40, sp44, arg2, arg3, arg4);
    sp38 = -sp34 / *arg4;
    *arg2 *= sp38;
    *arg3 *= sp38;
    *arg4 = -sp34;
    *arg2 = (f32)((f64)*arg2 * 10.5);
    *arg3 = (f32)((f64)*arg3 * 10.5);
    *arg4 = (f32)((f64)*arg4 * 10.5);
}

void func_806F8004(f32, f32, f32 *, f32 *, f32 *);

typedef struct R2FCCD0eTransformSlot {
    void *unk0;
    u16 unk4;
    u8 pad6[0xA];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x14];
} R2FCCD0eTransformSlot;

void slotQueueGetPosition(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (arg0 < 0) {
        func_806F8004(16.5f, 0.0f, arg1, arg2, arg3);
    } else if (arg0 == 8) {
        func_806F8004((f32)(1.5 - (f64)(((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk4 * 7)), 26.0f, arg1, arg2, arg3);
    } else {
        *arg1 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk10;
        *arg2 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk14;
        *arg3 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk18;
    }
}

typedef struct R2FCCD0cSlot {
    void *unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    void *unk28;
    u8 unk2C;
    u8 pad2D[3];
} R2FCCD0cSlot;




#ifdef NON_MATCHING
typedef struct FcASlot30 {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[0x2A];
} FcASlot30;

void func_806F8278(u8 arg0) {
    s32 sum;
    u16 (*p)[0x2F];
    s32 i;
    s32 j;

    sum = 0;
    p = (u16 (*)[0x2F])((u8 *)D_807FC950 + arg0 * 0x306);
    for (i = 0; i < 14; i++) {
        for (j = 0; j < 5; j++) {
            sum += p[j][i + 0x21];
        }
    }
    ((FcASlot30 *)D_80754280)[arg0 * 15 + 9].unk4 = sum;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8278.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F833C.s")

void func_806F8A8C(u8 arg0, u8 arg1, s32 arg2) {
    *(s16 *)((u8 *)slotQueueGetAddress(arg1 & 0xFF) + (arg0 * 0x30) + 4) = arg2;
}

s32 func_806C8DE0(s32);
s32 flagGridSumRows(s32, s32, s32, s32);

extern s32 func_805FF030();
u16 func_806F8AD4(u8 arg0, u8 arg1) {
    u16 var_a2;
    u16 sp26;
    s32 temp_v0;
    s32 sp1C;
    u8 *pa;
    R2FCCD0cSlot *slot;

    pa = &arg1;
    sp26 = 0;
    var_a2 = sp26;
    slot = (R2FCCD0cSlot *)slotQueueGetAddress(arg1) + arg0;
    switch (slot->unk2C) {
    case 2:
        break;
    case 0:
        if ((u16 *)slot->unk0 != NULL) {
            if (D_8076A0AB && D_8076A0AB) {}
            var_a2 = *(u16 *)slot->unk0;
        } else {
            sp1C = func_806C8DE0(arg1);
            temp_v0 = func_805FF030(D_8076A0AB, 1);
            if (arg0 != 0xA) {
                if (arg0 == 0xC) {
                    var_a2 = flagGridSumRows(0x1D5, temp_v0, temp_v0, sp1C);
                }
            } else {
                var_a2 = flagGridSumRows(0x225, temp_v0, temp_v0, sp1C);
            }
        }
        break;
    case 1:
        var_a2 = 0x14;
        break;
    }
    return var_a2;
}

void slotQueueUpdate(s32 arg0, u8 arg1, s32 arg2) {
    R2FCCD0cSlot *temp_v0;

    if ((D_807FC928 < 2) && (func_807142D8() == 0)) {
        if (arg0 == 8) {
            slotQueueUpdate(9, arg1, arg2 + 0xA);
            if (D_8076A0A8 == 0xF) {
                return;
            }
        }
        ((R2FCCD0cSlot *)D_80754280)[arg0].unk24 = arg1;
        temp_v0 = &((R2FCCD0cSlot *)D_80754280)[arg0];
        if (temp_v0->unk20 == 0) {
            temp_v0->pad4[3] = arg2;
        } else {
            temp_v0->pad4[3] = 0;
        }
        ((R2FCCD0cSlot *)D_80754280)[arg0].unk20 = 1;
        temp_v0 = &((R2FCCD0cSlot *)D_80754280)[arg0];
        if (temp_v0->pad4[2] == 0) {
            temp_v0->pad4[2] = arg1 != 0;
        }
    }
}


void func_806F8CB0(s32 arg0) {
    s32 var_v1;
    void *var_v0;

    if (arg0 == 8) {
        var_v0 = *(void **)((u8 *)D_80754280 + (arg0 * 0x30) + 0x28);
        var_v1 = 0;
        if (var_v0 != NULL) {
            do {
                *(s32 *)((u8 *)var_v0 + 0xC) = var_v1;
                var_v0 = *(void **)((u8 *)var_v0 + 0x18);
                var_v1 += 2;
            } while (var_v0 != NULL);
        }
    }
}


void slotQueueClearFlags(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s32 temp_v0;

    temp_v0 = arg0 * 0x30;
    *((u8 *)D_80754280 + temp_v0 + 7) = 0;
    *((u8 *)D_80754280 + temp_v0 + 6) = 0;
    if (arg0 == 8) {
        slotQueueCancel(9, 0);
    }
}

extern void *D_80754284;

int slotQueueCancel(arg0)
s32 arg0;
{
    s32 mask;
    void *var_v0 = D_80754284;

    *((u8 *)D_80754280 + (arg0 * 0x30) + 0x1C) = 0;
    if (var_v0 != NULL) {
        mask = ~(1 << arg0);
        do {
            *(s32 *)var_v0 &= mask;
            var_v0 = *(void **)((u8 *)var_v0 + 4);
        } while (var_v0 != NULL);
    }
    slotQueueClearFlags();
}

extern s32 func_805FF030();

void func_806F8DC4(s8 *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    s32 temp_a3;
    s32 temp_v0;

    sp1C = func_805FF030(D_8076A0AB, 1);
    temp_v0 = func_806C8DE0(0);
    temp_a3 = temp_v0;
    *arg0 = 0x7F;
    if (arg2 != 8) {
        if (arg2 != 0xA) {
            if ((arg2 == 0xC) && (flagGridSumRows(0x1D5, sp1C, sp1C, temp_a3) != 0)) {
                *(u8 *)arg0 = 0xFF;
            }
        } else if (flagGridSumRows(0x225, sp1C, sp1C, temp_a3) != 0) {
            *(u8 *)arg0 = 0xFF;
        }
    } else if (arg1 < ((u16 *)&D_807FC950[temp_v0][0x42])[sp1C]) {
        *(u8 *)arg0 = 0xFF;
    }
}

extern s32 flagCountRange(s32, s32, s32);

void func_806F8EB4(void) {
    flagCountRange(0x24D, 0x14, 0);
}

#ifdef NON_MATCHING
extern s32 func_806F6EDC();
extern s32 flagGet(s32, s32);
extern u8 D_807FC953[];
extern u8 D_807FC954[];

s32 func_806F8EDC(s32 arg0, s32 arg1) {
    s32 temp_t5;
    s32 temp_v0;
    s32 var_a0;
    s32 var_v1;
    u8 temp_a0;
    u8 var_v0;

    temp_v0 = func_806C8DE0(arg1);
    var_a0 = 0x64;
    switch (arg0) {
    case 1:
        var_a0 = 0x3E7;
        break;
    case 2:
        var_a0 = ((1 << D_807FC953[(arg1 * 0x306) + (temp_v0 * 0x5E)]) * 0x32) & 0xFFFF;
        break;
    case 3:
        if (D_807FC928 >= 2) {
            var_a0 = 0xA;
        } else {
            var_a0 = ((1 << D_807FC953[(arg1 * 0x306) + (temp_v0 * 0x5E)]) * 0x32) & 0xFFFF;
        }
        break;
    case 4:
        var_a0 = ((D_807FC953[(arg1 * 0x306) + (temp_v0 * 0x5E)] * 5) + 0x14) & 0xFFFF;
        break;
    case 5:
        if (D_807FC928 >= 2) {
            var_a0 = 0xBB8;
        } else if (func_806F6EDC() != 0) {
            var_a0 = ((((s32 (*)(void))func_806F8EB4)() * 0x96) + 0xBB8) & 0xFFFF;
        } else {
            var_a0 = 0;
        }
        break;
    case 7:
        if (D_807FC928 >= 2) {
            var_a0 = 0x14;
        } else {
            temp_a0 = D_807FC954[(arg1 * 0x306) + (temp_v0 * 0x5E)];
            var_v1 = 1;
            if (temp_a0 & 1) {
                var_v0 = temp_a0;
                if (temp_a0 != 0) {
                    do {
                        temp_t5 = (s32)var_v0 >> 1;
                        var_v1 += 1;
                        var_v0 = temp_t5;
                    } while (temp_t5 != 0);
                }
                var_a0 = (var_v1 * 5) & 0xFFFF;
            } else {
                var_a0 = 0;
            }
        }
        break;
    case 6:
        if (flagGet(0x179, 0) != 0) {
            var_a0 = (((s32 (*)(void))func_806F8EB4)() + 0xA) & 0xFFFF;
        } else {
            var_a0 = 0;
        }
        break;
    case 9:
        var_a0 = 0xC8;
        break;
    }
    return var_a0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F8EDC.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F91B4.s")



void bitfieldSetMappedFlag(u16 *arg0, s32 arg1) {
    *arg0 |= 1 << func_805FF030(arg1 & 0xFF, 1);
}

void bitfieldClearMappedFlag(u16 *arg0, s32 arg1) {
    *arg0 &= ~(1 << func_805FF030(arg1 & 0xFF, 1));
}


s32 bitfieldHasMappedFlag(u16 arg0, s32 arg1) {
    return (1 << func_805FF030(arg1 & 0xFF, 1)) & arg0 & 0xFF;
}

typedef struct FcAScaleInfo {
    u8 pad0[9];
    u8 unk9;
    u8 padA[4];
    s16 unkE;
} FcAScaleInfo;

typedef struct FcAScaleActor {
    u8 pad0[0x330];
    FcAScaleInfo *unk330;
    u8 pad334[0x2C];
    f32 unk360;
    f32 unk364;
} FcAScaleActor;

void func_806F94AC(void *arg0_, s32 arg1) {
    FcAScaleActor *arg0 = arg0_;
    f32 temp_fv0;
    f32 temp_fa0;
    f32 var_fv1;

    temp_fv0 = arg0->unk330->unk9 * arg0->unk330->unkE;
    var_fv1 = 32.0f / temp_fv0;
    temp_fa0 = var_fv1;
    if (arg1 == 9) {
        var_fv1 = (f64)temp_fa0 * 1.2;
    }
    arg0->unk360 = arg0->unk360 * var_fv1;
    arg0->unk364 = arg0->unk364 * var_fv1;
}

#ifdef NON_MATCHING
typedef struct FcAAllocNode {
    s32 type;
    u8 pad4[0x10];
    void *unk14;
    struct FcAAllocNode *next;
} FcAAllocNode;

void effectFreeAndUnlink(s32);
void heapFree(void *);

void func_806F9518(s32 arg0) {
    FcAAllocNode **var_s1;
    FcAAllocNode *temp_s0;
    FcAAllocNode **temp_s2;
    s32 idx;
    void *base;

    idx = arg0 * 0x30;
    base = D_80754280;
    ((R2FCCD0cSlot *)base)[arg0].unk20 = 0;
    var_s1 = (FcAAllocNode **)&((R2FCCD0cSlot *)(idx + (s32)base))->unk28;
    if (*var_s1 != NULL) {
        do {
            temp_s0 = *var_s1;
            temp_s2 = &temp_s0->next;
            if (temp_s0->type == 1) {
                effectFreeAndUnlink(*(s32 *)((u8 *)temp_s0->unk14 + 8));
                temp_s0 = *var_s1;
            }
            heapFree(temp_s0->unk14);
            heapFree(*var_s1);
            *var_s1 = NULL;
            var_s1 = temp_s2;
        } while (*temp_s2 != NULL);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9518.s")
#endif

void func_806F9518(s32);

void slotQueueReleaseAll(void) {
    s32 i;

    i = 0;
    do {
        func_806F9518(i);
        i++;
    } while (i != 0xF);
}

typedef struct R1FCCD0bAllocRecord {
    s32 unk0;
    u8 pad4[0x10];
    void *unk14;
} R1FCCD0bAllocRecord;

void *func_80610FE8(s32);
void heapClearBlock(void *);

void func_806F9608(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 1;
    (*arg0)->unk14 = func_80610FE8(0xC);
    heapClearBlock((*arg0)->unk14);
}

void func_806F966C(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 0;
    (*arg0)->unk14 = func_80610FE8(0x88);
    heapClearBlock((*arg0)->unk14);
}

typedef struct R1FCCD0bEffect {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    s32 unkC;
} R1FCCD0bEffect;

void effectSetDirection(R1FCCD0bEffect *arg0, u32 arg1) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    arg0->unkC = 0;
    switch (arg1) {
    case 0:
    case 13:
    case 14:
        var_v0 = -1;
        break;
    case 9:
    case 10:
    case 12:
        var_v1 = 1;
        break;
    default:
        var_v0 = 1;
        break;
    }
    arg0->unk4 = (f32)(var_v0 * 0x30);
    arg0->unk8 = (f32)(var_v1 * 0x30);
}

typedef struct R1FCCD0bEffectNode {
    u8 pad0[2];
    s16 unk2;
    u8 unk4;
    u8 pad5[3];
    void *unk8;
} R1FCCD0bEffectNode;

void func_806F94AC(void *, s32);
s32 func_806FACE8(s32);
void func_80714944(s32);
void func_80714950(void *);
void func_8071495C(void);
void func_8071498C(void (*)(void));
void func_80714998(u8);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void *func_80714CC0(s32, f32, f32, f32, f32);
void func_8071BE04(void);

void effectSpawnSprite(void *arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    u8 unused_byte;
    s32 unused_word;
    s32 sp2C;
    R1FCCD0bEffectNode *temp_s0;

    temp_s0 = *(R1FCCD0bEffectNode **)((u8 *)arg0 + 0x14);
    sp2C = 2;
    func_8071495C();
    func_807149FC(-1);
    if (arg1 == 0xE) {
        sp2C = 1;
    }
    func_80714998(((u8 *)&sp2C)[3]);
    func_80714944(arg4);
    func_80714950(arg0);
    func_8071498C(func_8071BE04);
    func_80714A28(0x21);
    if (arg1 == 3) {
        func_807149C8(0xFF, 0, 0, 0xFF);
    }
    temp_s0->unk8 = func_80714CC0(func_806FACE8(arg1), 1.0f, arg2, arg3, -10.0f);
    temp_s0->unk2 = 0;
    if (arg1 == 7) {
        temp_s0->unk4 = 1;
    } else {
        temp_s0->unk4 = 0;
    }
    func_806F94AC(temp_s0->unk8, arg1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9848.s")

typedef struct NmFCCD0ActorView {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x16];
    s16 unk35E;
    f32 unk360;
    f32 unk364;
} NmFCCD0ActorView;

extern u8 D_807FD7A0;
extern u8 D_807FD7B8;
extern u8 D_807FD7D0;

void effectSpriteUpdatePosition(NmFCCD0ActorView *arg0, s8 *arg1) {
    f32 *temp_a2;
    f32 *temp_v0;
    int new_var;
    f32 temp_fv0;
    s32 temp_v1;

    new_var = arg0->unk35E;
    temp_v1 = 4 * new_var;
    temp_a2 = (f32 *)(temp_v1 + &D_807FD7A0);
    temp_fv0 = *temp_a2;
    if (*temp_a2 == -200.0f) {
        *arg1 = 1;
        return;
    }
    arg0->unk340 = *temp_a2;
    temp_v0 = (f32 *)(temp_v1 + &D_807FD7D0);
    arg0->unk344 = *(f32 *)(temp_v1 + &D_807FD7B8);
    arg0->unk360 = *temp_v0;
    arg0->unk364 = *temp_v0;
    *temp_a2 = -200.0f;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9B64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9CD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F9D8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA1A4.s")

s32 func_806F9D8C();
s32 func_806FA1A4();

s32 func_806FA504(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    if (*(s32 *)arg1 == 0) {
        if (arg0 != 8) {
            arg3 = func_806F9D8C(arg0, arg1, arg3);
        } else {
            arg3 = func_806FA1A4(arg0, arg1, arg3);
        }
    } else if ((arg0 == 8) || (arg0 == 0xA) || (arg0 == 0xC)) {
        func_806F8DC4(*(s8 **)((u8 *)arg1 + 0x14), arg2, arg0);
    }
    return arg3;
}

typedef struct FcCNode {
    s32 unk0;
    u8 pad4[8];
    s32 unkC;
    s16 unk10;
    u8 pad12[6];
    struct FcCNode *unk18;
} FcCNode;

typedef struct FcCSlot {
    u16 *unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    u8 pad8[0x18];
    s32 unk20;
    u8 pad24[4];
    FcCNode *unk28;
} FcCSlot;

s32 func_806F9848();
s32 func_806F9B64();
s32 func_806F9CD0();

s32 func_806FA5A4(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s2;
    s32 s3;
    FcCNode *node;

    node = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk28;
    s2 = 0;
    s3 = 0;
    s1 = 0;
    if (((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 != 0) {
        ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 - 1;
        return arg1;
    }
    if (node == NULL) {
        switch (arg0) {
        case 8:
            func_806F9B64(arg0);
            return arg1;
        case 10:
        case 12:
            func_806F9CD0(arg0);
            return arg1;
        default:
            func_806F9848(arg0);
            return arg1;
        }
    } else {
        if (node != NULL) {
            do {
                s3 += 1;
                if (node->unkC != 0) {
                    node->unkC = node->unkC - 1;
                } else {
                    if (node->unk10 < 0x400) {
                        node->unk10 = (s32)((f32)node->unk10 + 102.4f);
                    } else {
                        s2 += 1;
                    }
                    if (node->unk10 >= 0x401) {
                        node->unk10 = 0x400;
                    }
                    arg1 = func_806FA504(arg0, node, s1, arg1);
                }
                if (node->unk0 == 1) {
                    s1 += 1;
                }
                node = node->unk18;
            } while (node != NULL);
        }
        if (s2 == s3) {
            if (((arg0 * 0x30) == 0x180) || ((arg0 * 0x30) == 0x1B0)) {
                ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = 0x5A;
            } else {
                ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = 0x1E;
            }
            ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk20 = 2;
            if (D_80754280 == 0) {}
        }
        return arg1;
    }
}

s32 func_806FA7A4(s32 arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (arg0 == 5) {
        var_v1 = 0x96;
    }
    return var_v1;
}

#ifdef NON_MATCHING
#define FCC_SLOT ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))

s32 func_806FA7BC(s32 arg0, s32 arg1) {
    extern s32 func_806FA7A4();
    s32 s1;
    FcCNode *node;
    u8 flag;
    u16 *p;
    s32 x;
    s32 step;
    s32 absd;
    s32 sign;
    s32 tmp;

    node = FCC_SLOT->unk28;
    s1 = 0;
    p = FCC_SLOT->unk0;
    if (p != NULL) {
        flag = *p == ((u16 *)FCC_SLOT)[2];
    } else {
        flag = 1;
    }
    if (node != NULL) {
        do {
            arg1 = func_806FA504(arg0, node, s1, arg1);
            if (node->unk0 == 1) {
                s1 += 1;
            }
            node = node->unk18;
        } while (node != NULL);
    }
    if (flag == 0) {
        if (FCC_SLOT->unk0 != NULL) {
            x = *FCC_SLOT->unk0;
            s1 = FCC_SLOT->unk4;
            step = func_806FA7A4(arg0, *FCC_SLOT->unk0, FCC_SLOT->unk4);
            if ((x - s1) > 0) {
                absd = (x - s1);
            } else {
                absd = -(x - s1);
            }
            sign = -1;
            if (absd < step) {
                if ((x - s1) > 0) {
                    tmp = (x - s1);
                } else {
                    tmp = -(x - s1);
                }
                step = tmp;
            }
            if ((x - s1) >= 0) {
                sign = 1;
            }
            FCC_SLOT->unk4 += sign * step;
        }
        flag = *FCC_SLOT->unk0 == ((u16 *)FCC_SLOT)[2];
    }
    if ((FCC_SLOT->unk7 == 0) && (flag != 0)) {
        FCC_SLOT->unk20 = 3;
        func_806F8CB0(arg0);
        if ((arg0 * 0x30) == 0x180) {
            slotQueueCancel(9, 5);
        }
        return arg1;
    } else if ((FCC_SLOT->unk7 != 0) && (FCC_SLOT->unk6 == 0)) {
        FCC_SLOT->unk7 = FCC_SLOT->unk7 - 1;
    }
    return arg1;
}

#undef FCC_SLOT
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA7BC.s")
#endif

s32 func_806FA9C0(s32 arg0, s32 arg1) {
    s32 s1;
    FcCNode *node;
    s32 cnt;
    s32 done;

    node = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk28;
    s1 = 0;
    if (node != NULL) {
        do {
            arg1 = func_806FA504(arg0, node, s1, arg1);
            if (node->unk0 == 1) {
                s1 += 1;
            }
            node = node->unk18;
        } while (node != NULL);
    }
    if (((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 != 0) {
        ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 - 1;
    } else {
        node = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk28;
        done = 0;
        cnt = 0;
        if (node != NULL) {
            do {
                cnt += 1;
                if (node->unkC != 0) {
                    node->unkC = node->unkC - 1;
                } else {
                    if (node->unk10 > 0) {
                        node->unk10 = (s32)((f32)node->unk10 - 102.4f);
                    }
                    if (node->unk10 < 0) {
                        node->unk10 = 0;
                        done += 1;
                    }
                }
                node = node->unk18;
            } while (node != NULL);
        }
        if (cnt == done) {
            ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk20 = 0;
        }
    }
    return arg1;
}

extern Mtx D_2000180;
s32 func_806FA7BC(s32, s32);

Gfx *func_806FAB20(Gfx *arg0) {
    s32 i;

    if (D_807FC928 >= 2) {
        return arg0;
    }
    gDPPipeSync(arg0++);
    gSPMatrix(arg0++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    for (i = 0; i != 0xF; i++) {
        switch (*(s32 *)((u8 *)D_80754280 + i * 0x30 + 0x20)) {
        case 0:
            func_806F9518(i);
            break;
        case 1:
            arg0 = (Gfx *)func_806FA5A4(i, (s32)arg0);
            break;
        case 2:
            arg0 = (Gfx *)func_806FA7BC(i, (s32)arg0);
            break;
        case 3:
            arg0 = (Gfx *)func_806FA9C0(i, (s32)arg0);
            break;
        }
    }
    return arg0;
}

extern s32 D_80754288;

void func_806FAC64(u8 arg0) {
    s32 resource;

    resource = func_805FF030(D_8076A0AB, 0);
    *(u8 **)((u8 *)D_80754280 + 0x270) = &D_807FC950[arg0][resource * 2 + 0x26];
    *(u16 *)((u8 *)D_80754280 + 0x274) = **(u16 **)((u8 *)D_80754280 + 0x270);
    D_80754288 = arg0;
}

extern s32 D_807200A0, D_807201A0, D_80720268, D_8072029C, D_807203B0, D_807203D4, D_807203F8, D_8072041C, D_80720440, D_80720488, D_807204BC, D_80720508, D_8072052C, D_80720558, D_8072057C, D_807205A0, D_807205C4, D_807205E8, D_8072060C, D_807206A8, D_807207BC, D_807207E0, D_80720854, D_80720878, D_80720890, D_807208A8, D_807208C0, D_807208D8, D_807209EC, D_80720A10, D_80720A34, D_80720A58, D_80721200, D_8072121C, D_80721250, D_8072145C, D_807214A0, D_807214B8, D_807214D0, D_807214E8, D_80721500;

s32 func_806FACE8(s32 arg0) {
    s32 result;
    u32 player;

    result = 0;
    player = func_806C8DE0(0);
    if (arg0 == 13) {
        player = D_80754288;
    }
    switch (arg0) {
    case 0:
    case 13:
        switch (player) {
        case 1:
            result = (s32)&D_8072057C;
            break;
        case 0:
            result = (s32)&D_807205E8;
            break;
        case 3:
            result = (s32)&D_8072060C;
            break;
        case 2:
            result = (s32)&D_807205C4;
            break;
        case 4:
        case 5:
            result = (s32)&D_807205A0;
            break;
        }
        break;
    case 6:
        result = (s32)&D_80720488;
        break;
    case 4:
        result = (s32)&D_807204BC;
        break;
    case 2:
    case 3:
        switch (player) {
        case 1:
            result = (s32)&D_807200A0;
            break;
        case 0:
            result = (s32)&D_807206A8;
            break;
        case 3:
            result = (s32)&D_80720854;
            break;
        case 2:
            result = (s32)&D_8072029C;
            break;
        case 4:
            result = (s32)&D_807201A0;
            break;
        case 5:
            result = (s32)&D_80720268;
            break;
        }
        break;
    case 1:
    case 14:
        switch (player) {
        case 1:
            result = (s32)&D_807203B0;
            break;
        case 0:
            result = (s32)&D_8072041C;
            break;
        case 3:
            result = (s32)&D_80720440;
            break;
        case 2:
            result = (s32)&D_807203F8;
            break;
        case 4:
        case 5:
            result = (s32)&D_807203D4;
            break;
        }
        break;
    case 11:
        result = (s32)&D_807207BC;
        break;
    case 7:
        switch (player) {
        case 1:
            result = (s32)&D_80720878;
            break;
        case 0:
            result = (s32)&D_80720890;
            break;
        case 3:
            result = (s32)&D_807208A8;
            break;
        case 2:
            result = (s32)&D_807208D8;
            break;
        case 4:
        case 5:
            result = (s32)&D_807208C0;
            break;
        }
        break;
    case 5:
        result = (s32)&D_80720508;
        break;
    case 8:
        result = (s32)&D_8072052C;
        break;
    case 9:
        result = (s32)&D_8072052C;
        break;
    case 10:
        result = (s32)&D_80720558;
        break;
    case 12:
        switch (player) {
        case 1:
            result = (s32)&D_807209EC;
            break;
        case 0:
            result = (s32)&D_80720A34;
            break;
        case 3:
            result = (s32)&D_80720A58;
            break;
        case 2:
            result = (s32)&D_807207E0;
            break;
        case 4:
        case 5:
            result = (s32)&D_80720A10;
            break;
        }
        break;
    case 16:
        result = (s32)&D_8072145C;
        break;
    case 17:
        result = (s32)&D_80721250;
        break;
    case 18:
        result = (s32)&D_80721200;
        break;
    case 19:
        result = (s32)&D_8072121C;
        break;
    case 20:
        result = (s32)&D_807214A0;
        break;
    case 21:
        result = (s32)&D_807214B8;
        break;
    case 22:
        result = (s32)&D_807214D0;
        break;
    case 23:
        result = (s32)&D_807214E8;
        break;
    case 24:
        result = (s32)&D_80721500;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FAFE4.s")

void slotQueueClearAllFlags(void)
{
  s32 i;
  s32 offset;
  func_806FAFE4();
 i = 0; offset = 0; do {
    if ((*((((u8 *) D_80754280) + offset) + 6)) != 0)
    {
      slotQueueClearFlags(i, 0);
    }
    i++;
    offset += 0x30;
  }
  while (i != 0xF);
}

void slotQueueReset(void) {
    func_806FAFE4();
    slotQueueReleaseAll();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB2B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB370.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB3D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FB418.s")
