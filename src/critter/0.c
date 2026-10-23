#include "common.h"

void func_80024000(u8 *arg0, u8 *arg1, f32 arg2) {
    switch (*arg1) {
    case 0:
    case 1:
        *(f32 *)(arg0 + 0x34) = (f32)((f64)arg2 * 3.0);
        return;
    case 2:
        *(f32 *)(arg0 + 0x34) = (f32)((f64)arg2 * 0.5);
        return;
    case 3:
        *(f32 *)(arg0 + 0x34) = (f32)((f64)arg2 * 1.1);
        return;
    case 4:
        *(f32 *)(arg0 + 0x34) = (f32)((f64)arg2 + (f64)arg2);
    default:
        return;
    }
}

void func_8002409C(u8 *arg0) {
    s32 i;
    u8 *ptr;

    ptr = *(u8 **)(arg0 + 8);
    i = 0;
    if ((s32)arg0[2] > 0) {
        do {
            *(f32 *)(ptr + 0x24) = 7.0f;
            *(u16 *)(ptr + 0x1E4) = 0x82;
            ptr[0x1E1] |= 2;
            i++;
            ptr += 0x1F0;
        } while (i < (s32)arg0[2]);
    }
}

void func_800240EC(u8 *arg0) {
    s32 var_v1;
    s32 var_a1;
    s32 i;
    u8 *ptr;

    ptr = *(u8 **)(arg0 + 8);
    var_v1 = 0x7A;
    var_a1 = 0x7B;
    if (arg0[0] == 1) {
        var_v1 = 0x80;
        var_a1 = 0x81;
    }
    i = 0;
    if ((s32)arg0[2] > 0) {
        do {
            *(f32 *)(ptr + 0x24) = 5.0f;
            *(u16 *)(ptr + 0x1E4) = var_v1;
            *(u16 *)(ptr + 0x1E6) = var_a1;
            i++;
            ptr += 0x1F0;
        } while (i < (s32)arg0[2]);
    }
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80024154.s")
#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002427C.s")

s32 func_8066B0F8(s32, s32, s32, s32);

void critterPlayAudio(u8 *arg0) {
    s32 i;
    u8 *ptr2;
    u16 v;
    u8 *ptr;

    i = 0;
    ptr2 = arg0;
    do {
        ptr = (u8 *)((s32 *)arg0 + i);
        if (v = *(u16 *)(ptr2 + 0x1E4)) {
            if (*(s32 *)(ptr + 0x1E8) == 0) {
                *(s32 *)(ptr + 0x1E8) = func_8066B0F8(0xE, v, 0, 0);
            }
        }
        i++;
        ptr2 += 2;
    } while (i != 2);
}

void assetFreeBuffer(s32, s32, s32);

void critterStopAudio(u8 *arg0) {
    s32 i;
    u8 *ptr = arg0;
    for (i = 0; i < 8; i += 4, ptr += 4) {
        s32 val = *(s32 *)(ptr + 0x1E8);
        if (val != 0) {
            assetFreeBuffer(val, 0x179, 0x5A);
            *(s32 *)(ptr + 0x1E8) = 0;
        }
    }
}


void critterUpdateAudio(u8 *arg0) {
    if (arg0[0x1E1] & 1) {
        critterPlayAudio(arg0);
    } else {
        critterStopAudio(arg0);
    }
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_800245B8.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_800247F4.s")

f32 func_80612794(s32);

void func_80024B78(u8 *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;

    if (arg0[0x1E1] & 1) {
        temp_fv1 = (f32)((f64)*(f32 *)(arg0 + 0x28) * (1.0 / 1.1));
        *(s16 *)(arg0 + 0x42) = (s16)(s32)((f64)*(s16 *)(arg0 + 0x42) + (90.0 * (0.5 + (f64)(10.0f * temp_fv1))));
        *(s16 *)(arg0 + 0x42) &= 0xFFF;
        temp_fv0 = func_80612794(*(s16 *)(arg0 + 0x42));
        *(f32 *)(arg0 + 0x48) = (((-15.0f * temp_fv1) + 45.0f) * temp_fv0) + (temp_fv1 * 30.0f);
        *(f32 *)(arg0 + 0x14) = (f32)((f64)(*(f32 *)(arg0 + 0x28) * temp_fv0) * 0.4);
    }
    critterUpdateAudio(arg0);
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80024C88.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80024F28.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002516C.s")

s32 func_806119A0(void);
void func_806086CC(f32, f32, s32, s16, s32, s32, s32, s32, f32, s32);

void func_80025500(u8 *arg0) {
    if (arg0[0x1E0] != 0 && (arg0[0x1E1] & 1) && (s16)(func_806119A0() % 255U) < 6) {
        func_806086CC(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x10),
                      (s16)((func_806119A0() & 3) + 0x1A9),
                      0xFF, 0x5A, 0x1E, 0x5A, 0.7f, 0);
    }
    critterUpdateAudio(arg0);
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_800255C4.s")

extern Gfx D_1000118;
extern u8 D_807FC929;
extern u8 *D_807FC924;
extern Mtx D_2000200;
extern u8 D_807444FC;
extern Mtx D_2000180;

Gfx *func_800257D4(Gfx *gdl) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPLoadGeometryMode(gdl++, 0);
    gSPMatrix(gdl++, (Mtx *)((s32)D_807FC924 + (D_807FC929 * 0x2F0) + (D_807444FC << 6) + 0x88), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    return gdl;
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_800258B0.s")

extern u8 D_807444FC;
void func_800258B0(f32 (*)[4], s32, s32, s32, f32, f32, f32, f32);

void func_80025A3C(u8 *arg0) {
    f32 sp30[4][4];

    func_800258B0(sp30, (s16)-*(s16 *)(arg0 + 2), *(s16 *)(arg0 + 0), 0,
                  *(f32 *)(arg0 + 0x38) * 0.07f,
                  *(f32 *)(arg0 + 8),
                  *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0xC),
                  *(f32 *)(arg0 + 0x10));
    guMtxF2L(sp30, (Mtx *)((s32)arg0 + (D_807444FC << 6) + 0x60));
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80025AD0.s")

#if 0
// Draft: arg0/arg1 register move order and loop branch likely difference
s32 func_800257D4(s32);
s32 func_80025AD0(s32, void *);
extern s32 D_80029BA8;
s32 func_80025D1C(s32 arg0, u8 *arg1) {
    s32 var_s0;
    u8 *var_s1;
    s32 var_s2 = arg0;
    if (arg1 == NULL) {
        return arg0;
    }
    D_80029BA8 = 0;
    var_s1 = *(u8 **)(arg1 + 4);
    if (var_s1 != NULL) {
        var_s2 = func_800257D4(var_s2);
    }
    var_s0 = 0;
    if ((s32)arg1[0] > 0) {
        do {
            var_s0++;
            var_s2 = func_80025AD0(var_s2, var_s1);
            var_s1 += 0xC;
        } while (var_s0 < (s32)arg1[0]);
    }
    return var_s2;
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80025D1C.s")

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80025DB8.s")

void func_80025DB8(void *, void *, u8, s16, u8);
s32 func_806119A0(void);

void func_80025F3C(void *arg0, void *arg1, u8 arg2, u8 arg3) {
    func_80025DB8(arg0, arg1, arg2, (s16)(func_806119A0() & 0xFFF), arg3);
}

void func_80025F8C(s16 *arg0, u8 *arg1, u8 arg2) {
    func_80025F3C(arg0, arg1, arg2, 0);
    *(f32 *)(arg1 + 8) += (f32)arg0[0];
    *(f32 *)(arg1 + 0xC) += (f32)arg0[1];
    *(f32 *)(arg1 + 0x10) += (f32)arg0[2];
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002601C.s")

void *func_80026298(arg0, arg1)
void *arg0;
u8 arg1;
{
    u8 *ptr = *(u8 **)((u8 *)arg0 + 4);
    return ptr + arg1 * 0x2C;
}

void func_800262C0(u8 *arg0, u8 *arg1) {
    s32 temp_t8;

    temp_t8 = (func_806119A0() % (u32)(arg1[1] - 1)) & 0xFF;
    if (temp_t8 < arg0[0x50]) {
        goto end;
    }
    temp_t8 = (temp_t8 + 1) & 0xFF;
end:
    arg0[0x50] = temp_t8;
    *(void **)(arg0 + 0x54) = func_80026298(arg1, temp_t8);
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026338.s")

extern u8 D_807444FC;
extern u8 *D_807FBB48;

void critterCalcDistToPlayer(u8 *arg0) {
    f32 dx;
    f32 dz;

    if (D_807444FC != arg0[0x40]) {
        dx = *(f32 *)(arg0 + 8) - *(f32 *)(D_807FBB48 + 0x7C);
        dz = *(f32 *)(arg0 + 0x10) - *(f32 *)(D_807FBB48 + 0x84);
        *(f32 *)(arg0 + 0x3C) = (dx * dx) + (dz * dz);
        arg0[0x40] = D_807444FC;
    }
}

#if 0
// Draft: temp_v0 spilled to stack across func_80025F3C call in conditional branch
void func_8002646C(u8 *arg0, u8 *arg1) {
    void *temp_v0;

    *(f32 *)(arg0 + 0x28) = *(f32 *)(arg1 + 0x28);
    *(void **)(arg0 + 0x58) = *(void **)(arg1 + 0x58);
    arg0[0x1E1] = arg1[0x1E1];
    temp_v0 = *(void **)(arg1 + 0x54);
    if (temp_v0 != *(void **)(arg0 + 0x54)) {
        *(void **)(arg0 + 0x54) = temp_v0;
        func_80025F3C(temp_v0, arg0, 1, 1);
    }
    arg0[0x1E0] = arg1[0x1E0];
    if (arg0[0x1E0] == 0 && !(arg0[0x1E1] & 4)) {
        *(s16 *)(arg0 + 2) = 0;
        return;
    }
    if ((u32)(func_806119A0() % 255U) < 50) {
        func_80025F3C(*(void **)(arg0 + 0x54), arg0, 1, 1);
    }
}
#endif
#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002646C.s")


s32 func_80026530(u8 *arg0, void *arg1) {
    func_80024000(arg0, arg1, (f32)((f64)*(f32 *)(arg0 + 0x38) * 0.5));
    func_80025F3C(*(void **)(arg0 + 0x54), arg0, 1, 1);
    return 0;
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002658C.s")

void func_8002658C(void *, void *, s32, void *);

void func_80026874(u8 *arg0, u8 *arg1) {
    u8 flags;

    flags = arg0[0x1E1];
    if ((flags & 1) && (flags & 4)) {
        func_8002658C(arg0, arg1, 0, func_80026530);
    }
    if (arg0[0x1E2] == 2) {
        func_8002646C(arg0, *(void **)(arg1 + 8));
        return;
    }
    if (*(u8 *)(*(u8 **)(arg0 + 0x58) + 0x25) != 0) {
        critterCalcDistToPlayer(arg0);
        func_80026338(arg0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026904.s")

extern void *D_80029BA4;

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026A5C.s")
void func_800245B8(void *);
void func_80024F28(void *);
void func_8002601C(void *);
void func_80026904(void);
s32 func_80026A5C(u8 *, u8 *);

void critterDispatchAll(u8 *arg0) {
    void *cb;
    void (*var_s3)(void *);
    s32 var_s1;
    u8 *var_s0;
    var_s0 = *(u8 **)(arg0 + 8);
    var_s3 = NULL;
    switch (arg0[0]) {
    case 0:
    case 1:
        var_s3 = (void (*)(void *))func_800245B8;
        break;
    case 2:
        var_s3 = (void (*)(void *))func_80024F28;
        break;
    case 3:
        var_s3 = (void (*)(void *))func_80024B78;
        break;
    case 4:
        var_s3 = (void (*)(void *))func_80025500;
        break;
    default:
        var_s3 = NULL;
        break;
    }
    cb = func_80026A5C;
    for (var_s1 = 0; var_s1 < (s32)arg0[2]; var_s1++, var_s0 += 0x1F0) {
        func_8002601C(var_s0);
        if (var_s0[0x1E0] == 0) {
            func_80026874(var_s0, arg0);
        } else {
            func_8002658C(var_s0, arg0, (s32)func_80026904, cb);
        }
        *(s16 *)(var_s0 + 0x44) = *(s16 *)(var_s0 + 0x42);
        if (var_s3 != NULL) {
            var_s3(var_s0);
        }
    }
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026C9C.s")
#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026E0C.s")

extern s32 D_80029BA8;
extern void *D_80029BA0;
extern void *D_80029BA4;
void func_80026E0C(void *);
void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_80026FD0(void *arg0) {
    D_80029BA8 = 0;
    D_80029BA0 = func_80610FE8(8);
    heapClearBlock(D_80029BA0);
    func_80026E0C(arg0);
    D_80029BA4 = func_80610FE8(0x2C);
    heapClearBlock(D_80029BA4);
}

extern s32 D_807FBB60;
extern void *D_80029BA0;
void func_80026C9C(void *);

s32 critterRender(s32 arg0) {
    if (D_807FBB60 & 0x10) {
        if (!(D_807FBB60 & 2)) {
            func_80026C9C(D_80029BA0);
        }
        arg0 = func_80025D1C(arg0, D_80029BA0);
    }
    return arg0;
}

void heapFreeDeferred(void *);

void critterCleanup(u8 *arg0) {
    u8 temp_s2;
    u8 *var_s0;
    s32 var_s1;

    temp_s2 = arg0[2];
    var_s0 = *(u8 **)(arg0 + 8);
    var_s1 = 0;
    if ((s32)temp_s2 > 0 && var_s0 != NULL) {
        do {
            critterStopAudio(var_s0);
            var_s1++;
            var_s0 += 0x1F0;
        } while (var_s1 < (s32)temp_s2 && var_s0 != NULL);
    }
    if (*(void **)(arg0 + 8) != NULL) {
        heapFreeDeferred(*(void **)(arg0 + 8));
    }
    *(void **)(arg0 + 8) = NULL;
    arg0[2] = 0;
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80027118.s")
