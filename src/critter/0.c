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

typedef struct { s16 v[3]; } C0aTbl;
extern C0aTbl D_80029F6C;

void func_80024154(u8 *arg0) {
    u8 *ptr;
    s32 i;
    C0aTbl tbl;
    u8 idx;

    ptr = *(u8 **)(arg0 + 8);
    tbl = D_80029F6C;
    idx = 0;
    i = 0;
    if ((s32)arg0[2] > 0) {
        do {
            if ((idx == 0 && (f64)(u32)arg0[2] * 0.4 < (f64)i) || (idx == 1 && (f64)(u32)arg0[2] * 0.7 < (f64)i)) {
                idx++;
            }
            *(f32 *)(ptr + 0x24) = 10.0f;
            *(s16 *)(ptr + 0x1E4) = tbl.v[idx];
            *(s32 *)(ptr + 0x1E8) = 0;
            i++;
            ptr += 0x1F0;
        } while (i < (s32)arg0[2]);
    }
}
typedef struct { s16 v[4]; } C0aTbl2;
extern C0aTbl2 D_80029F74;

void func_8002427C(u8 *arg0) {
    u8 *ptr;
    s32 i;
    C0aTbl2 tbl;
    u8 idx;

    ptr = *(u8 **)(arg0 + 8);
    tbl = D_80029F74;
    idx = 0;
    for (i = 0; i < (s32)arg0[2]; i++, ptr += 0x1F0) {
        {
            if ((idx == 0 && (f64)(u32)arg0[2] * 0.3 < (f64)i) || (idx == 1 && (f64)(u32)arg0[2] * 0.5 < (f64)i) || (idx == 2 && (f64)(u32)arg0[2] * 0.7 < (f64)i)) {
                idx++;
            }
            *(f32 *)(ptr + 0x24) = 20.0f;
            *(s16 *)(ptr + 0x1E4) = tbl.v[idx];
            *(s32 *)(ptr + 0x1E8) = 0;
            ptr[0x1E1] |= 4;
            func_80024000(ptr, arg0, (f32)((f64)*(f32 *)(ptr + 0x38) * 0.5));
        }
    }
}

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

s32 func_806119A0(void);
void func_806086CC(f32, f32, s32, s16, s32, s32, s32, s32, f32, s32);
void sfxPlayAtPosition(f32, f32, s32, s16, u8, f32, u8, u8);
f32 func_80612790(s16);
extern u8 D_80770DC9;

void func_800245B8(void *arg0) {
    s16 r;
    f32 temp;
    f32 sp3C;

    if (((u8 *)arg0)[0x1E0] != 0 && (((u8 *)arg0)[0x1E1] & 1)) {
        r = func_806119A0() % 255U;
        sp3C = (f32)((f64)*(f32 *)((u8 *)arg0 + 0x28) * (1.0 / 3.0));
        if (r < 6) {
            func_806086CC(*(f32 *)((u8 *)arg0 + 8), *(f32 *)((u8 *)arg0 + 0xC), *(s32 *)((u8 *)arg0 + 0x10),
                          (s16)((func_806119A0() & 3) + 0x1A9),
                          0xFF, 0x7F, 0x1E, 0x5A, 0.7f, 0);
        }
        *(s16 *)((u8 *)arg0 + 0x42) = (s16)(s32)((f32)*(s16 *)((u8 *)arg0 + 0x42) + 1200.0f * sp3C);
        *(s16 *)((u8 *)arg0 + 0x42) &= 0xFFF;
        if (*(s16 *)((u8 *)arg0 + 0x44) > 0x800) {
            if (*(s16 *)((u8 *)arg0 + 0x42) < 0x800) {
                sfxPlayAtPosition(*(f32 *)((u8 *)arg0 + 8), *(f32 *)((u8 *)arg0 + 0xC), *(s32 *)((u8 *)arg0 + 0x10), 0x5E,
                                  D_80770DC9 * 100 + 0x73, 2.0f, 0x1E, 0x4B);
            }
        } else {
            if (*(s16 *)((u8 *)arg0 + 0x42) > 0x800) {
                sfxPlayAtPosition(*(f32 *)((u8 *)arg0 + 8), *(f32 *)((u8 *)arg0 + 0xC), *(s32 *)((u8 *)arg0 + 0x10), 0x5F,
                                  D_80770DC9 * 100 + 0x73, 2.0f, 0x1E, 0x4B);
            }
        }
        temp = 1.0f - func_80612790(*(s16 *)((u8 *)arg0 + 0x42));
        *(f32 *)((u8 *)arg0 + 0x48) = 60.0f * temp;
        *(f32 *)((u8 *)arg0 + 0x14) = (f32)((f64)(*(f32 *)((u8 *)arg0 + 0x28) * temp) * 0.5);
    }
    critterUpdateAudio(arg0);
}

void func_80025A3C(u8 *arg0);
void matrixMakeRotationZ(f32 (*)[4], f32);
extern u8 D_807444FC;
extern Vtx D_80029870;
extern Vtx D_800298D0;
extern Vtx D_800298E0;
extern Gfx D_80029B40;
extern s32 D_80029BA8;

Gfx *func_800247F4(Gfx *gdl, u8 *arg1) {
    f32 sp90[4][4];
    f32 sp8C;

    sp8C = *(f32 *)(arg1 + 0x48);
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gDPLoadTextureBlock(gdl++, *(s32 *)(arg1 + 0x1E8), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    func_80025A3C(arg1);
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x60), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, &D_80029870, 6, 0);
    gSPDisplayList(gdl++, &D_80029B40);
    gDPLoadTextureBlock(gdl++, *(s32 *)(arg1 + 0x1EC), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 48, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    matrixMakeRotationZ(sp90, -sp8C);
    guMtxF2L(sp90, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0xE0));
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0xE0), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_800298D0, 4, 6);
    gSP2Triangles(gdl++, 6, 7, 8, 0, 6, 8, 9, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    matrixMakeRotationZ(sp90, sp8C);
    guMtxF2L(sp90, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x160));
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x160), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_800298E0, 6, 7);
    gSP2Triangles(gdl++, 10, 11, 7, 0, 10, 7, 12, 0);
    D_80029BA8 = 0;
    gDPPipeSync(gdl++);
    return gdl;
}

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

extern Vtx D_800297F0;
extern Vtx D_80029830;

Gfx *func_80024C88(Gfx *gdl, u8 *arg1) {
    f32 sp70[4][4];
    f32 sp6C;

    sp6C = *(f32 *)(arg1 + 0x48);
    if (D_80029BA8 != *(s32 *)(arg1 + 0x1E8)) {
        D_80029BA8 = *(s32 *)(arg1 + 0x1E8);
        gDPLoadTextureBlock(gdl++, D_80029BA8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    func_80025A3C(arg1);
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x60), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    matrixMakeRotationZ(sp70, sp6C);
    guMtxF2L(sp70, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0xE0));
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0xE0), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_800297F0, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    matrixMakeRotationZ(sp70, -sp6C);
    guMtxF2L(sp70, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x160));
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x160), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, &D_80029830, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gDPPipeSync(gdl++);
    return gdl;
}

s16 func_806CC10C(s16, s16);
void func_807149B8(s32);
void func_80714950(s32);
void func_807149FC(s32);
void func_8071498C(void *);
void func_80714CC0(void *, f32, s32, s32, f32);
extern u8 D_80718BF4;
extern u8 D_8071FC40;

void func_80024F28(void *arg0) {
    s16 sp4E;
    u8 pad;
    f32 temp;
    f32 sp44;
    f32 sp40;
    s16 sp3E;
    f32 temp2;
    s32 absv;

    if (((u8 *)arg0)[0x1E1] & 1) {
        sp4E = func_806119A0() % 400U;
        temp = *(f32 *)((u8 *)arg0 + 0x30);
        if (temp < 0.0f) {
            sp40 = 0.0f;
        } else {
            sp40 = temp;
        }
        sp3E = func_806CC10C(*(s16 *)((u8 *)arg0 + 0), *(s16 *)((u8 *)arg0 + 4));
        if (sp4E <= 0) {
            func_807149B8(1);
            func_80714950(1);
            func_807149FC(-1);
            func_8071498C(&D_80718BF4);
            func_80714CC0(&D_8071FC40, 0, *(s32 *)((u8 *)arg0 + 8), *(s32 *)((u8 *)arg0 + 0xC), *(f32 *)((u8 *)arg0 + 0x10));
        }
        if (sp3E > 0) {
            absv = sp3E;
        } else {
            absv = -sp3E;
        }
        if (absv >= 0x5B) {
            func_806086CC(*(f32 *)((u8 *)arg0 + 8), *(f32 *)((u8 *)arg0 + 0xC), *(s32 *)((u8 *)arg0 + 0x10), 0x16F, 0x46, 0xDC, 0x1E, 0x5A, 0.7f, 0);
        }
        *(s16 *)((u8 *)arg0 + 0x42) = (s16)(s32)((200.0 * (1.5 + (f64)(150.0f * *(f32 *)((u8 *)arg0 + 0x30)))) + (f64)*(s16 *)((u8 *)arg0 + 0x42));
        *(s16 *)((u8 *)arg0 + 0x42) &= 0xFFF;
        temp2 = func_80612794(*(s16 *)((u8 *)arg0 + 0x42)) * (10.0f + 200.0f * sp40);
        sp44 = temp2 * 1.0f + temp2 * ((f32)sp3E * 0.00024414062f);
        *(f32 *)((u8 *)arg0 + 0x4C) = func_80612794((s16)(*(s16 *)((u8 *)arg0 + 0x42) + 0xC8)) * 2;
        *(f32 *)((u8 *)arg0 + 0x48) = (f32)((f64)sp44 + (f64)sp3E * 0.2);
    }
    critterUpdateAudio(arg0);
}

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002516C.s")

s32 func_806119A0(void);

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

extern void *D_80029BA4;

void func_80026338(u8 *arg0, u8 *arg1) {
    s32 lim;

    switch (arg1[0]) {
    default:
        lim = 0x1900;
        break;
    case 3:
        lim = 0x1900;
        break;
    case 0:
    case 1:
        lim = 0x57E4;
        break;
    }
    if (*(f32 *)(arg0 + 0x3C) < (f32)lim) {
        if (*(u8 *)(*(u8 **)(arg0 + 0x58) + 0x25) != 0) {
            arg0[0x1E0] = 2;
            if (arg0[0x1E2] == 0) {
                *(void **)(arg0 + 0x54) = D_80029BA4;
            } else {
                func_800262C0(arg0, arg1);
            }
            func_80025F3C(*(void **)(arg0 + 0x54), arg0, 1, 1);
            func_80024000(arg0, arg1, *(f32 *)(arg0 + 0x38));
        }
    }
}

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

void func_8002646C(u8 *arg0, u8 *arg1) {
    *(f32 *)(arg0 + 0x28) = *(f32 *)(arg1 + 0x28);
    *(void **)(arg0 + 0x58) = *(void **)(arg1 + 0x58);
    arg0[0x1E1] = arg1[0x1E1];
    if (*(void **)(arg1 + 0x54) != *(void **)(arg0 + 0x54)) {
        *(void **)(arg0 + 0x54) = *(void **)(arg1 + 0x54);
        func_80025F3C(*(void **)(arg0 + 0x54), arg0, 1, 1);
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


s32 func_80026530(u8 *arg0, void *arg1) {
    func_80024000(arg0, arg1, (f32)((f64)*(f32 *)(arg0 + 0x38) * 0.5));
    func_80025F3C(*(void **)(arg0 + 0x54), arg0, 1, 1);
    return 0;
}

#ifdef NON_MATCHING
extern f32 sqrtf(f32);
f32 func_80611BB4(f32, f32);
f32 func_80612800(s16);
s16 func_806CC190(s16, s16, s32);
s16 mathAngleDiscrete(f32, f32, f32, f32, f32);

void func_8002658C(void *C0cArg0, void *arg1, s32 arg2, void *arg3) {
    u8 *arg0 = C0cArg0;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 dxz;
    f32 d2;
    f32 old;
    f32 tgt;
    f32 spd;
    f32 rate;
    s16 *off;
    s32 ret;
    s16 ang;
    s32 use_y;

    rate = 0.02f;
    use_y = (arg0[0x1E1] & 2) == 0;
    if (arg2 != 0) {
        ((void (*)(u8 *, void *))arg2)(arg0, arg1);
    }
    off = *(s16 **)(arg0 + 0x54);
    tx = *(f32 *)(arg0 + 0x18) + (f32)off[0];
    ty = *(f32 *)(arg0 + 0x1C) + (f32)off[1];
    tz = *(f32 *)(arg0 + 0x20) + (f32)off[2];
    dx = tx - *(f32 *)(arg0 + 8);
    dy = ty - *(f32 *)(arg0 + 0xC);
    dz = tz - *(f32 *)(arg0 + 0x10);
    if (arg0[0x1E2] != 2) {
        dxz = dx * dx + dz * dz;
        d2 = dxz;
        if ((u8)use_y) {
            d2 = dxz + dy * dy;
        }
        tgt = *(f32 *)(arg0 + 0x34);
        if (d2 < 2500.0f) {
            tgt = (f32)((f64)tgt * 0.3 + 0.7 * (f64)tgt * (f64)(d2 * 0.0004f));
            rate = 0.1f;
            if (d2 < 25.0f && arg3 != NULL) {
                ret = ((s32 (*)(u8 *, void *))arg3)(arg0, arg1);
                if (ret != 0) {
                    return;
                }
            }
        }
        old = *(f32 *)(arg0 + 0x28);
        *(f32 *)(arg0 + 0x28) = old + (tgt - old) * rate;
        *(f32 *)(arg0 + 0x30) = *(f32 *)(arg0 + 0x28) - old;
    }
    dist = sqrtf(dx * dx + dz * dz);
    if ((u8)use_y) {
        *(s16 *)(arg0 + 2) = func_806CC190(*(s16 *)(arg0 + 2), (s16)(s32)(((f64)func_80611BB4(dy, dist) * 2048.0) / 3.1415927410125732), *(s32 *)(arg0 + 0x24));
    }
    ang = mathAngleDiscrete(tx, tz, *(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0x10), dist);
    *(s16 *)(arg0 + 4) = *(s16 *)(arg0 + 0);
    *(s16 *)(arg0 + 0) = func_806CC190(*(s16 *)(arg0 + 0), ang, *(s32 *)(arg0 + 0x24));
    spd = *(f32 *)(arg0 + 0x28);
    *(f32 *)(arg0 + 8) = spd * func_80612794(*(s16 *)(arg0 + 0)) + *(f32 *)(arg0 + 8);
    *(f32 *)(arg0 + 0x10) = spd * func_80612790(*(s16 *)(arg0 + 0)) + *(f32 *)(arg0 + 0x10);
    if ((u8)use_y) {
        *(f32 *)(arg0 + 0xC) = spd * func_80612800(*(s16 *)(arg0 + 2)) + *(f32 *)(arg0 + 0xC);
    }
}
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002658C.s")
#endif

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

#ifdef NON_MATCHING
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_80026904(u8 *arg0, u8 *arg1) {
    s16 sp2E;
    s32 temp_t2;
    u8 *temp_a0;

    if (arg0[0x1E2] == 2) {
        func_8002646C(arg0, *(u8 **)(arg1 + 8));
        return;
    }
    if (arg0[0x1E2] == 0) {
        temp_a0 = *(u8 **)(arg0 + 0x58);
        if (temp_a0[0x25] != 0) {
            critterCalcDistToPlayer(arg0);
            if (D_80029BA4 != *(void **)(arg0 + 0x54)) {
                func_80026338(arg0, arg1);
                return;
            }
            if (arg0[0x1E0] == 2 && *(f32 *)(arg0 + 0x3C) < (f32)*(s16 *)((u8 *)D_80029BA4 + 0xA)) {
                sp2E = mathAngleBetweenPoints2D(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0x10), *(f32 *)(D_807FBB48 + 0x7C), *(f32 *)(D_807FBB48 + 0x84));
                temp_t2 = (sp2E + (func_806119A0() & 0x7FF)) - 0x400;
                arg0[0x1E0] = 1;
                func_80025DB8(*(void **)(arg0 + 0x54), arg0, 0, (s16)temp_t2, 1);
            }
        } else if (D_80029BA4 == *(void **)(arg0 + 0x54)) {
            *(u8 **)(arg0 + 0x54) = temp_a0;
            func_80025F3C(temp_a0, arg0, 1, 1);
            arg0[0x40] = 0xFF;
        }
    }
}

extern void *D_80029BA4;
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026904.s")
#endif

s32 func_80026A5C(u8 *arg0, u8 *arg1) {
    u8 *temp_v0;

    if (arg0[0x1E2] == 1) {
        temp_v0 = *(u8 **)(arg0 + 0x54);
        *(u8 **)(arg0 + 0x58) = temp_v0;
        if (temp_v0[0x1C] & 1) {
            *(s16 *)(arg0 + 2) = 0;
            arg0[0x1E0] = 0;
            *(f32 *)(arg0 + 0x28) = 0.0f;
            *(f32 *)(arg0 + 0x34) = 0;
            return 1;
        }
        func_800262C0(arg0, arg1);
    } else if (D_80029BA4 == *(void **)(arg0 + 0x54)) {
        if (arg0[0x1E0] == 2) {
            arg0[0x1E0] = 1;
        } else {
            arg0[0x1E0] = 2;
        }
        func_80025F3C(*(void **)(arg0 + 0x54), arg0, (u8)(arg0[0x1E0] == 2), 1);
    } else {
        *(s16 *)(arg0 + 2) = 0;
        *(f32 *)(arg0 + 0x34) = 0;
        if ((f64)*(f32 *)(arg0 + 0x28) < 0.05) {
            arg0[0x1E0] = 0;
            *(f32 *)(arg0 + 0x28) = 0.0f;
            return 1;
        }
    }
    return 0;
}
void func_800245B8(void *);
void func_80024F28(void *);
void func_8002601C(void *);
void func_80026904();
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

#ifdef NON_MATCHING
extern u8 D_8074E77C;
extern u8 D_80029BAC[];
typedef struct {
    s32 w[5];
} C0cBlk5;

void func_80026C9C(void *C0cArg0) {
    u8 *arg0 = C0cArg0;
    s32 i;
    u8 *p;
    u8 *tbl;
    u8 *e;
    s16 idx;

    if (arg0 != NULL) {
        p = *(u8 **)(arg0 + 4);
        *(s16 *)D_80029BA4 = (s16)(s32) * (f32 *)(D_807FBB48 + 0x7C);
        tbl = D_80029BAC + D_8074E77C * 0x78;
        i = 0;
        *(s16 *)((u8 *)D_80029BA4 + 4) = (s16)(s32) * (f32 *)(D_807FBB48 + 0x84);
        if ((s32)arg0[0] > 0) {
            do {
                idx = *p;
                if (idx > 0) {
                    idx = idx - 1;
                }
                e = tbl + idx * 0x18;
                *(s16 *)((u8 *)D_80029BA4 + 2) = (s16)(s32)(*(f32 *)(D_807FBB48 + 0x80) + (f32) * (s16 *)(e + 0x14));
                *(C0cBlk5 *)((u8 *)D_80029BA4 + 8) = *(C0cBlk5 *)e;
                critterDispatchAll(p);
                i++;
                p += 0xC;
            } while (i < (s32)arg0[0]);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026C9C.s")
#endif

#ifdef NON_MATCHING
extern void *D_80029BA0;
extern s32 D_807F6C28;
void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);
void heapClearBlock(void *);
s16 func_806531B8(f32, f32, f32, s32);
void func_80027118();

void func_80026E0C(void *C0cArg0) {
    u8 *arg0 = C0cArg0;
    s32 g;
    u8 *grp;
    u8 *ent;
    s32 j;
    u8 *src;

    if (arg0 != NULL) {
        memcpy(D_80029BA0, arg0, 1);
        src = arg0 + 1;
        g = 0;
        if (*(u8 *)D_80029BA0 > 0) {
            do {
                j = 0;
                if (g == 0) {
                    *(void **)((u8 *)D_80029BA0 + 4) = func_80610FE8(*(u8 *)D_80029BA0 * 0xC);
                    heapClearBlock(*(void **)((u8 *)D_80029BA0 + 4));
                    grp = *(u8 **)((u8 *)D_80029BA0 + 4);
                } else {
                    grp += 0xC;
                }
                memcpy(grp, src, 3);
                src += 3;
                if (grp[1] > 0) {
                    do {
                        if (j == 0) {
                            *(void **)(grp + 4) = func_80610FE8(grp[1] * 0x2C);
                            heapClearBlock(*(void **)(grp + 4));
                            ent = *(u8 **)(grp + 4);
                        } else {
                            ent += 0x2C;
                        }
                        memcpy(ent, src, 0x20);
                        if (D_807F6C28 != 0) {
                            *(s16 *)(ent + 0x28) = func_806531B8((f32) * (s16 *)(ent + 0), (f32) * (s16 *)(ent + 2), (f32) * (s16 *)(ent + 4), 0);
                            ent[0x24] = 0xFF;
                        }
                        j++;
                        src += 0x20;
                    } while (j < grp[1]);
                }
                func_80027118(grp);
                g++;
            } while (g < *(u8 *)D_80029BA0);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_80026E0C.s")
#endif

extern void *D_80029BA0;
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

void func_80024154(u8 *);
void func_8002427C(u8 *);
s32 func_807142D8(void);
extern f32 D_80029F7C;

void func_80027118(u8 *arg0) {
    u8 *ent;
    s32 i;
    u8 flag;
    void (*cb)(u8 *);

    if (arg0[2] == 0) {
        *(void **)(arg0 + 8) = NULL;
        return;
    }
    switch (arg0[0]) {
    case 0:
    case 1:
        cb = func_800240EC;
        break;
    case 3:
        cb = func_80024154;
        break;
    case 4:
        cb = func_8002409C;
        break;
    case 2:
        cb = func_8002427C;
        break;
    }
    heapClearBlock(*(void **)(arg0 + 8) = func_80610FE8(arg0[2] * 0x1F0));
    ent = *(u8 **)(arg0 + 8);
    if (arg0[1] == 1) {
        flag = 0;
    } else {
        flag = 1;
    }
    i = 0;
    if ((s32)arg0[2] > 0) {
        do {
            func_80025F8C(*(s16 **)(arg0 + 4), ent, 1);
            if (func_807142D8() == 0) {
                func_80025F3C(*(void **)(arg0 + 4), ent, 1, 1);
            }
            *(void **)(ent + 0x54) = *(void **)(ent + 0x58) = *(void **)(arg0 + 4);
            ent[0x1E2] = flag;
            ent[0x40] = 0xFF;
            *(s16 *)(ent + 0) = func_806119A0() & 0xFFF;
            *(s16 *)(ent + 0x42) = func_806119A0() & 0xFFF;
            *(f32 *)(ent + 0x38) = 1.0f - (f32)(func_806119A0() % 1000U) / 4000.0f;
            *(f32 *)(ent + 0x38) = *(f32 *)(ent + 0x38) * D_80029F7C;
            ent += 0x1F0;
            if (flag == 1) {
                flag = 2;
            }
            i++;
        } while (i < (s32)arg0[2]);
    }
    cb(arg0);
}
