#include "common.h"

void critterSetTargetSpeed(u8 *arg0, u8 *arg1, f32 arg2) {
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
            critterSetTargetSpeed(ptr, arg0, (f32)((f64)*(f32 *)(ptr + 0x38) * 0.5));
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

void critterBuildMatrix(u8 *arg0);
void matrixMakeRotationZ(f32 (*)[4], f32);
extern u8 D_807444FC;
extern Vtx D_80029870;
extern Vtx D_800298D0;
extern Vtx D_800298E0;
extern Gfx D_80029B40;
extern s32 critterCurrentTexture;

Gfx *func_800247F4(Gfx *gdl, u8 *arg1) {
    f32 sp90[4][4];
    f32 sp8C;

    sp8C = *(f32 *)(arg1 + 0x48);
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gDPLoadTextureBlock(gdl++, *(s32 *)(arg1 + 0x1E8), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    critterBuildMatrix(arg1);
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
    critterCurrentTexture = 0;
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
    if (critterCurrentTexture != *(s32 *)(arg1 + 0x1E8)) {
        critterCurrentTexture = *(s32 *)(arg1 + 0x1E8);
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(arg1);
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

extern s32 critterCurrentTexture;
extern u8 D_807444FC;
void critterBuildMatrix(u8 *);
extern Vtx D_80029940[];
extern Vtx D_80029980[];
void matrixMakeRotationY(f32 (*)[4], f32);

Gfx *func_8002516C(Gfx *gdl, u8 *arg1) {
    f32 spD0[4][4];
    f32 sp90[4][4];

    if (critterCurrentTexture != *(s32 *)(arg1 + 0x1E8)) {
        critterCurrentTexture = *(s32 *)(arg1 + 0x1E8);
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(arg1);
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x60), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    matrixMakeRotationY(spD0, *(f32 *)(arg1 + 0x4C));
    guMtxF2L(spD0, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x160));
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x160), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPClearGeometryMode(gdl++, G_CULL_BOTH);
    guTranslateF(sp90, 0.0f, 0.0f, -27.0f);
    matrixMakeRotationY(spD0, *(f32 *)(arg1 + 0x48));
    guMtxCatF(spD0, sp90, spD0);
    guMtxF2L(spD0, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0xE0));
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0xE0), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(gdl++, D_80029940, 4, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 2, 3, 0, 0);
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gSPSetGeometryMode(gdl++, G_CULL_BACK);
    gSPVertex(gdl++, D_80029980, 9, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 3, 4, 0);
    gSP2Triangles(gdl++, 5, 1, 6, 0, 4, 3, 5, 0);
    gSP2Triangles(gdl++, 0, 4, 6, 0, 0, 6, 1, 0);
    gSP2Triangles(gdl++, 4, 5, 6, 0, 5, 2, 1, 0);
    gSP2Triangles(gdl++, 0, 7, 3, 0, 3, 7, 5, 0);
    gSP2Triangles(gdl++, 2, 5, 8, 0, 2, 8, 0, 0);
    gSP2Triangles(gdl++, 0, 8, 7, 0, 7, 8, 5, 0);
    gDPPipeSync(gdl++);
    return gdl;
}

s32 func_806119A0(void);

void func_80025500(u8 *arg0) {
    if (arg0[0x1E0] != 0 && (arg0[0x1E1] & 1) && (s16)(func_806119A0() % 255U) < 6) {
        func_806086CC(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x10),
                      (s16)((func_806119A0() & 3) + 0x1A9),
                      0xFF, 0x5A, 0x1E, 0x5A, 0.7f, 0);
    }
    critterUpdateAudio(arg0);
}

extern Gfx D_80029A10;

Gfx *func_800255C4(Gfx *gdl, u8 *arg1) {
    if (critterCurrentTexture != *(s32 *)(arg1 + 0x1E8)) {
        critterCurrentTexture = *(s32 *)(arg1 + 0x1E8);
        gDPLoadTextureBlock(gdl++, critterCurrentTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD);
    }
    critterBuildMatrix(arg1);
    gSPMatrix(gdl++, (Mtx *)((s32)arg1 + (D_807444FC << 6) + 0x60), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, &D_80029A10, 11, 0);
    gSP2Triangles(gdl++, 0, 1, 2, 0, 0, 3, 1, 0);
    gSP2Triangles(gdl++, 0, 2, 4, 0, 0, 5, 6, 0);
    gSP2Triangles(gdl++, 0, 4, 5, 0, 0, 6, 3, 0);
    gSP2Triangles(gdl++, 7, 2, 1, 0, 1, 8, 7, 0);
    gSP2Triangles(gdl++, 3, 6, 9, 0, 5, 10, 9, 0);
    gSP2Triangles(gdl++, 6, 5, 9, 0, 10, 8, 9, 0);
    gSP2Triangles(gdl++, 1, 3, 9, 0, 8, 1, 9, 0);
    gDPPipeSync(gdl++);
    return gdl;
}

extern Gfx D_1000118;
extern u8 D_807FC929;
extern u8 *D_807FC924;
extern Mtx D_2000200;
extern u8 D_807444FC;
extern Mtx D_2000180;

Gfx *critterRenderSetup(Gfx *gdl) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPLoadGeometryMode(gdl++, 0);
    gSPMatrix(gdl++, (Mtx *)((s32)D_807FC924 + (D_807FC929 * 0x2F0) + (D_807444FC << 6) + 0x88), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    return gdl;
}

void critterMakeMatrix(f32 (*m)[4], s16 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;

    temp_fs0 = func_80612794(arg1);
    temp_fs1 = func_80612790(arg1);
    sp40 = func_80612794(arg2);
    sp34 = func_80612790(arg2);
    sp3C = func_80612794(arg3);
    temp_fv0 = func_80612790(arg3);
    m[0][0] = sp34 * temp_fv0 * arg4;
    m[0][1] = sp34 * sp3C * arg4;
    m[0][2] = -sp40 * arg4;
    m[0][3] = 0.0f;
    temp_fa1 = temp_fs0 * sp40;
    m[1][0] = ((temp_fa1 * temp_fv0) - (temp_fs1 * sp3C)) * arg4;
    m[1][3] = 0.0f;
    m[1][1] = ((temp_fa1 * sp3C) + (temp_fs1 * temp_fv0)) * arg4;
    m[1][2] = temp_fs0 * sp34 * arg4;
    temp_fa1_2 = temp_fs1 * sp40;
    m[2][0] = ((temp_fa1_2 * temp_fv0) + (temp_fs0 * sp3C)) * arg4;
    m[2][3] = 0.0f;
    m[2][1] = ((temp_fa1_2 * sp3C) - (temp_fs0 * temp_fv0)) * arg4;
    m[2][2] = temp_fs1 * sp34 * arg4;
    m[3][0] = arg5;
    m[3][1] = arg6;
    m[3][2] = arg7;
    m[3][3] = 1.0f;
}

void critterBuildMatrix(u8 *arg0) {
    f32 sp30[4][4];

    critterMakeMatrix(sp30, (s16)-*(s16 *)(arg0 + 2), *(s16 *)(arg0 + 0), 0,
                  *(f32 *)(arg0 + 0x38) * 0.07f,
                  *(f32 *)(arg0 + 8),
                  *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0xC),
                  *(f32 *)(arg0 + 0x10));
    guMtxF2L(sp30, (Mtx *)((s32)arg0 + (D_807444FC << 6) + 0x60));
}

extern Gfx D_80029B18;
extern Gfx D_80029B30;
extern Gfx D_80029B78;
extern Gfx D_80029B88;
extern s32 D_807F6C28;
Gfx *func_800247F4(Gfx *, u8 *);
Gfx *func_80024C88(Gfx *, u8 *);
Gfx *func_8002516C(Gfx *, u8 *);
void func_8065C334(f32, f32, s32, s32, u8 *, u8 *, u8 *, s32);

Gfx *critterRenderGroup(Gfx *gdl, u8 *arg1) {
    s32 col;
    s32 i;
    u8 *obj;
    u8 r;
    u8 g;
    u8 b;
    Gfx *(*cb)(Gfx *, u8 *);

    obj = *(u8 **)(arg1 + 8);
    switch (arg1[0]) {
    case 0:
    case 1:
        gSPDisplayList(gdl++, &D_80029B30);
        cb = func_800247F4;
        break;
    case 3:
        gSPDisplayList(gdl++, &D_80029B18);
        cb = func_80024C88;
        break;
    case 2:
        gSPDisplayList(gdl++, &D_80029B78);
        cb = func_8002516C;
        break;
    case 4:
        gSPDisplayList(gdl++, &D_80029B88);
        cb = func_800255C4;
        break;
    }
    i = 0;
    if ((s32)arg1[2] > 0) {
        do {
            if (D_807F6C28 != 0) {
                func_8065C334(*(f32 *)(obj + 8), *(f32 *)(obj + 0xC), *(s32 *)(obj + 0x10), 0, &r, &g, &b,
                              *(s16 *)(*(u8 **)(obj + 0x58) + 0x28));
            } else {
                r = 0xFF;
                g = 0xFF;
                b = 0xFF;
            }
            gDPPipeSync(gdl++);
            {
                Gfx *_g = gdl++;

                _g->words.w0 = 0xFA000000;
                col = _SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8);
                _g->words.w1 = _SHIFTL(*(u8 *)(*(u8 **)(obj + 0x58) + 0x26), 0, 8) | (0, col);
            }
            if (obj[0x1E1] & 1) {
                gdl = cb(gdl, obj);
            }
            i++;
            obj += 0x1F0;
        } while (i < (s32)arg1[2]);
    }
    gDPPipeSync(gdl++);
    return gdl;
}

s32 critterRenderGroups(s32 gdl, u8 *arg1) {
    u8 *ptr;
    s32 i;

    if (arg1 == NULL) {
        return gdl;
    }
    critterCurrentTexture = 0;
    ptr = *(u8 **)(arg1 + 4);
    if (ptr != NULL) {
        gdl = (s32)critterRenderSetup((Gfx *)gdl);
    }
    for (i = 0; i < (s32)arg1[0]; i++) {
        gdl = (s32)critterRenderGroup((Gfx *)gdl, ptr);
        ptr += 0xC;
    }
    return gdl;
}


void critterSetOffsetAtAngle(void *arg0, void *arg1, u8 arg2, s16 arg3, u8 arg4) {
    f32 sp2C;
    f32 sp28;
    f32 base;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 v;

    base = (f32)*(s16 *)((u8 *)arg0 + 0xC);
    if (arg2 == 0) {
        sp2C = (f32)*(s32 *)((u8 *)arg0 + 0x14);
        base += (f32)*(s16 *)((u8 *)arg0 + 0x10);
    } else {
        sp2C = (f32)*(s16 *)((u8 *)arg0 + 8) * ((f32)(func_806119A0() & 0xFFFU) * 0.000244140625f);
    }
    v = (f32)((f64)((f32)(func_806119A0() & 0xFFFU) * 0.000244140625f * base) - 0.5 * (f64)base);
    if (arg4 != 0) {
        px = (f32 *)((u8 *)arg1 + 0x18);
        py = (f32 *)((u8 *)arg1 + 0x1C);
        pz = (f32 *)((u8 *)arg1 + 0x20);
    } else {
        px = (f32 *)((u8 *)arg1 + 8);
        py = (f32 *)((u8 *)arg1 + 0xC);
        pz = (f32 *)((u8 *)arg1 + 0x10);
    }
    *py = v;
    *px = func_80612794(arg3) * sp2C;
    *pz = func_80612790(arg3) * sp2C;
}

void critterSetOffsetAtAngle(void *, void *, u8, s16, u8);

void critterSetRandomOffset(void *arg0, void *arg1, u8 arg2, u8 arg3) {
    critterSetOffsetAtAngle(arg0, arg1, arg2, (s16)(func_806119A0() & 0xFFF), arg3);
}

void critterPlaceInZone(s16 *arg0, u8 *arg1, u8 arg2) {
    critterSetRandomOffset(arg0, arg1, arg2, 0);
    *(f32 *)(arg1 + 8) += (f32)arg0[0];
    *(f32 *)(arg1 + 0xC) += (f32)arg0[1];
    *(f32 *)(arg1 + 0x10) += (f32)arg0[2];
}

extern u8 *D_807FBB48;
extern void *critterPlayerZone;

#ifdef NON_MATCHING
extern void *critterPlayerZone;

#define CR58 (*(u8 **)((u8 *)arg0 + 0x58))
void func_8002601C(void *arg0) {
    u8 *m;
    f32 lim;
    f32 fv0;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ddy;
    s16 half;
    s32 f;

    fv0 = 0.0f;
    lim = (f32)(*(s32 *)(CR58 + 0x18) + 0x1DE84);
    if (D_807444FC != CR58[0x24]) {
        half = (*(s16 *)(CR58 + 0x10) + *(s16 *)(CR58 + 0xC)) >> 1;
        dx = (f32)*(s16 *)(CR58 + 0) - *(f32 *)(D_807FBB48 + 0x7C);
        dz = (f32)*(s16 *)(CR58 + 4) - *(f32 *)(D_807FBB48 + 0x84);
        dx = dx * dx + dz * dz;
        fv0 = 0.0f;
        f = *(s16 *)((u8 *)critterPlayerZone + 2) < (*(s16 *)(CR58 + 2)) + half;
        if (f) {
            f = (*(s16 *)(CR58 + 2)) - half < *(s16 *)((u8 *)critterPlayerZone + 2);
        }
        f = (u8)f != 0;
        if (f) {
            f = 0;
            if (dx < (f32)*(s32 *)(CR58 + 0x18)) {
                f = 1;
            }
        }
        CR58[0x25] = f;
        CR58[0x24] = D_807444FC;
        m = D_807FC924 + D_807FC929 * 0x2F0;
        dz = (f32)*(s16 *)(CR58 + 4) - *(f32 *)(m + 0x218);
        dx = (f32)*(s16 *)(CR58 + 0) - *(f32 *)(m + 0x210);
        ddy = (f32)*(s16 *)(CR58 + 2) - *(f32 *)(m + 0x214);
        dist = dz * dz + (dx * dx + ddy * ddy);
        *(f32 *)(CR58 + 0x20) = dist;
        if (dist < lim) {
            fv0 = (lim - dist) * 0.000051020408f;
            if (fv0 > 1.0f) {
                fv0 = 1.0f;
            }
        }
        CR58[0x26] = (u32)(255.0f * fv0);
    }
    if (*(f32 *)(CR58 + 0x20) < lim) {
        ((u8 *)arg0)[0x1E1] |= 1;
    } else {
        ((u8 *)arg0)[0x1E1] &= ~1;
    }
}
#undef CR58
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/0/func_8002601C.s")
#endif

void *critterGetZone(arg0, arg1)
void *arg0;
u8 arg1;
{
    u8 *ptr = *(u8 **)((u8 *)arg0 + 4);
    return ptr + arg1 * 0x2C;
}

void critterPickNewZone(u8 *arg0, u8 *arg1) {
    s32 temp_t8;

    temp_t8 = (func_806119A0() % (u32)(arg1[1] - 1)) & 0xFF;
    if (temp_t8 < arg0[0x50]) {
        goto end;
    }
    temp_t8 = (temp_t8 + 1) & 0xFF;
end:
    arg0[0x50] = temp_t8;
    *(void **)(arg0 + 0x54) = critterGetZone(arg1, temp_t8);
}


void critterTryActivate(u8 *arg0, u8 *arg1) {
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
                *(void **)(arg0 + 0x54) = critterPlayerZone;
            } else {
                critterPickNewZone(arg0, arg1);
            }
            critterSetRandomOffset(*(void **)(arg0 + 0x54), arg0, 1, 1);
            critterSetTargetSpeed(arg0, arg1, *(f32 *)(arg0 + 0x38));
        }
    }
}


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

void critterFollowLeader(u8 *arg0, u8 *arg1) {
    *(f32 *)(arg0 + 0x28) = *(f32 *)(arg1 + 0x28);
    *(void **)(arg0 + 0x58) = *(void **)(arg1 + 0x58);
    arg0[0x1E1] = arg1[0x1E1];
    if (*(void **)(arg1 + 0x54) != *(void **)(arg0 + 0x54)) {
        *(void **)(arg0 + 0x54) = *(void **)(arg1 + 0x54);
        critterSetRandomOffset(*(void **)(arg0 + 0x54), arg0, 1, 1);
    }
    arg0[0x1E0] = arg1[0x1E0];
    if (arg0[0x1E0] == 0 && !(arg0[0x1E1] & 4)) {
        *(s16 *)(arg0 + 2) = 0;
        return;
    }
    if ((u32)(func_806119A0() % 255U) < 50) {
        critterSetRandomOffset(*(void **)(arg0 + 0x54), arg0, 1, 1);
    }
}


s32 func_80026530(u8 *arg0, void *arg1) {
    critterSetTargetSpeed(arg0, arg1, (f32)((f64)*(f32 *)(arg0 + 0x38) * 0.5));
    critterSetRandomOffset(*(void **)(arg0 + 0x54), arg0, 1, 1);
    return 0;
}

extern f32 sqrtf(f32);
f32 func_80611BB4(f32, f32);
f32 func_80612800(s16);
s16 func_806CC190(s16, s16, s32);
s16 mathAngleDiscrete(f32, f32, f32, f32, f32);

void critterSteerToTarget(u8 *arg0, void *arg1, s32 arg2, void *arg3) {
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
    tx = (f32)off[0] + *(f32 *)(arg0 + 0x18);
    ty = (f32)off[1] + *(f32 *)(arg0 + 0x1C);
    tz = (f32)off[2] + *(f32 *)(arg0 + 0x20);
    dx = tx - *(f32 *)(arg0 + 8);
    dy = ty - *(f32 *)(arg0 + 0xC);
    dz = tz - *(f32 *)(arg0 + 0x10);
    if (arg0[0x1E2] != 2) {
        dxz = dx * dx + dz * dz;
        d2 = dxz;
        if ((u8)use_y) {
            d2 += dy * dy;
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
        spd = (tgt - old) * rate;
        *(f32 *)(arg0 + 0x28) = old + spd;
        *(f32 *)(arg0 + 0x30) = *(volatile f32 *)(arg0 + 0x28) - old;
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

void critterSteerToTarget();

void critterUpdateIdle(u8 *arg0, u8 *arg1) {
    u8 flags;

    flags = arg0[0x1E1];
    if ((flags & 1) && (flags & 4)) {
        critterSteerToTarget(arg0, arg1, 0, func_80026530);
    }
    if (arg0[0x1E2] == 2) {
        critterFollowLeader(arg0, *(void **)(arg1 + 8));
        return;
    }
    if (*(u8 *)(*(u8 **)(arg0 + 0x58) + 0x25) != 0) {
        critterCalcDistToPlayer(arg0);
        critterTryActivate(arg0, arg1);
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_80026904(u8 *arg0, u8 *arg1) {
    s16 sp2E;
    u8 *temp_a0;

    if (arg0[0x1E2] == 2) {
        critterFollowLeader(arg0, *(u8 **)(arg1 + 8));
        return;
    }
    if (arg0[0x1E2] == 0) {
        temp_a0 = *(u8 **)(arg0 + 0x58);
        if (temp_a0[0x25] != 0) {
            critterCalcDistToPlayer(arg0);
            if (critterPlayerZone != *(void **)(arg0 + 0x54)) {
                critterTryActivate(arg0, arg1);
                return;
            }
            if (arg0[0x1E0] == 2 && *(f32 *)(arg0 + 0x3C) < (f32)*(s16 *)((u8 *)critterPlayerZone + 0xA)) {
                sp2E = mathAngleBetweenPoints2D(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0x10), *(f32 *)(D_807FBB48 + 0x7C), *(f32 *)(D_807FBB48 + 0x84));
                sp2E += (func_806119A0() & 0x7FF) - 0x400;
                arg0[0x1E0] = 1;
                critterSetOffsetAtAngle(*(void **)(arg0 + 0x54), arg0, 0, sp2E, 1);
            }
        } else if (critterPlayerZone == *(void **)(arg0 + 0x54)) {
            *(u8 **)(arg0 + 0x54) = temp_a0;
            critterSetRandomOffset(temp_a0, arg0, 1, 1);
            arg0[0x40] = 0xFF;
        }
    }
}

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
        critterPickNewZone(arg0, arg1);
    } else if (critterPlayerZone == *(void **)(arg0 + 0x54)) {
        if (arg0[0x1E0] == 2) {
            arg0[0x1E0] = 1;
        } else {
            arg0[0x1E0] = 2;
        }
        critterSetRandomOffset(*(void **)(arg0 + 0x54), arg0, (u8)(arg0[0x1E0] == 2), 1);
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
            critterUpdateIdle(var_s0, arg0);
        } else {
            critterSteerToTarget(var_s0, arg0, (s32)func_80026904, cb);
        }
        *(s16 *)(var_s0 + 0x44) = *(s16 *)(var_s0 + 0x42);
        if (var_s3 != NULL) {
            var_s3(var_s0);
        }
    }
}

extern u8 D_8074E77C;
extern u8 D_80029BAC[];
typedef struct {
    s32 w[5];
} C0cBlk5;

void critterUpdateGroups(u8 *arg0) {
    s32 i;
    u8 *p;
    u8 *tbl;
    u8 *e;
    s16 idx;
    u8 sel = D_8074E77C;

    if (arg0 != NULL) {
        p = *(u8 **)(arg0 + 4);
        *(s16 *)critterPlayerZone = (s16)(s32) * (f32 *)(D_807FBB48 + 0x7C);
        tbl = D_80029BAC + sel * 0x78;
        *(s16 *)((u8 *)critterPlayerZone + 4) = (s16)(s32) * (f32 *)(D_807FBB48 + 0x84);
        for (i = 0; i < (s32)arg0[0]; i++, p += 0xC) {
            idx = *p;
            if (idx > 0) {
                idx = idx - 1;
            }
            e = tbl + idx * 0x18;
            *(s16 *)((u8 *)critterPlayerZone + 2) = (s16)(s32)((f32) * (s16 *)(e + 0x14) + *(f32 *)(D_807FBB48 + 0x80));
            *(C0cBlk5 *)((u8 *)critterPlayerZone + 8) = *(C0cBlk5 *)e;
            critterDispatchAll(p);
        }
    }
}

extern void *critterGroups;
void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);
void heapClearBlock(void *);
s16 func_806531B8(f32, f32, f32, s32);
void critterInitGroup();

void critterLoadData(u8 *arg0) {
    s32 g;
    u8 *grp;
    u8 *ent;
    s32 j;
    u8 *src;

    if (arg0 != NULL) {
        memcpy(critterGroups, arg0, 1);
        src = arg0 + 1;
        for (g = 0; g < *(u8 *)critterGroups; g++) {
            j = 0;
            if (g == 0) {
                *(void **)((u8 *)critterGroups + 4) = func_80610FE8(*(u8 *)critterGroups * 0xC);
                heapClearBlock(*(void **)((u8 *)critterGroups + 4));
                grp = *(u8 **)((u8 *)critterGroups + 4);
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
            critterInitGroup(grp);
        }
    }
}

extern void *critterGroups;
void critterLoadData();
void critterInit(void *arg0) {
    critterCurrentTexture = 0;
    critterGroups = func_80610FE8(8);
    heapClearBlock(critterGroups);
    critterLoadData(arg0);
    critterPlayerZone = func_80610FE8(0x2C);
    heapClearBlock(critterPlayerZone);
}

extern s32 D_807FBB60;
void critterUpdateGroups();

s32 critterRender(s32 arg0) {
    if (D_807FBB60 & 0x10) {
        if (!(D_807FBB60 & 2)) {
            critterUpdateGroups(critterGroups);
        }
        arg0 = critterRenderGroups(arg0, critterGroups);
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

void critterInitGroup(u8 *arg0) {
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
            critterPlaceInZone(*(s16 **)(arg0 + 4), ent, 1);
            if (func_807142D8() == 0) {
                critterSetRandomOffset(*(void **)(arg0 + 4), ent, 1, 1);
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
