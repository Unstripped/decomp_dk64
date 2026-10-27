#include "common.h"
#include "actor.h"

extern u8 D_807444FC;

#ifdef NON_MATCHING
extern u8 D_807444F0;
extern u8 D_807444EC;
extern s8 D_807444C0;
extern s32 D_8076A0A8;
extern f32 D_80747CD0;

f32 func_8062A850(void) {
    f32 target;
    f32 step;
    f32 cur;
    s32 flag;

    target = 1.0f;
    if (D_807444F0 != 1 && D_807444EC == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = D_807444EC == 1;
    if (flag) {
        flag = D_8076A0A8 != 0x50;
    }
    if (D_807444C0 != 0 && !flag) {
        target = target * 1.2;
    }
    cur = D_80747CD0;
    if (cur < target) {
        cur += step;
        if (target < cur) {
            cur = target;
        }
    } else {
        cur -= step;
        if (cur < target) {
            cur = target;
        }
    }
    D_80747CD0 = cur;
    return cur;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062A850.s")
#endif

extern f32 D_807F5DF0;

#ifdef NON_MATCHING
extern f32 D_807F5DF4;
extern f32 D_807F5DF8;
extern f32 D_807F5DFC;
extern f32 D_807F5E00;
extern f32 D_807F5E04;
extern f32 D_807F5E08;
extern f32 D_807F5E0C;
extern f32 D_807F5E10;
extern f32 D_807F5E14;
extern f32 D_807F5E18;
extern f32 D_807F5E1C;

void func_8062A944(f32 arg0, f32 arg1, f32 arg2) {
    f32 negZ;
    f32 scale;
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp58;
    f32 sp54;
    f32 sp4C;

    sp58 = arg0 * 0.5;
    guRotateF(spB0, sp58, 1.0f, 0.0f, 0.0f);
    negZ = -arg2;
    guMtxXFMF(spB0, 0.0f, 0.0f, negZ, &sp64, &sp68, &sp6C);
    sp54 = sp58 * arg1;
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0, &D_807F5DF4, &D_807F5DF8);
    sp4C = -sp54;
    guRotateF(sp70, sp4C, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DFC, &D_807F5E00, &D_807F5E04);
    guRotateF(spB0, -sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, negZ, &sp64, &sp68, &sp6C);
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5E08, &D_807F5E0C, &D_807F5E10);
    guRotateF(sp70, sp4C, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5E14, &D_807F5E18, &D_807F5E1C);
    scale = negZ / D_807F5DF8;
    D_807F5DF0 *= scale;
    D_807F5DF4 *= scale;
    D_807F5DF8 = negZ;
    scale = negZ / D_807F5E04;
    D_807F5DFC *= scale;
    D_807F5E00 *= scale;
    D_807F5E04 = negZ;
    scale = negZ / D_807F5E10;
    D_807F5E08 *= scale;
    D_807F5E0C *= scale;
    D_807F5E10 = negZ;
    scale = negZ / D_807F5E1C;
    D_807F5E14 *= scale;
    D_807F5E18 *= scale;
    D_807F5E1C = negZ;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062A944.s")
#endif

extern f32 D_807F5E20[];
extern f32 D_807F5E24[];
extern f32 D_807F5E28[];

s32 func_8062FF10(f32 (*)[4], f32 (*)[4]);

void func_8062AC68(Mtx *arg0) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    s32 i;

    guMtxL2F(sp98, arg0);
    func_8062FF10(sp58, sp98);
    for (i = 0; i < 4; i++) {
        guMtxXFMF(sp58, (&D_807F5DF0)[i * 3], (&D_807F5DF0)[i * 3 + 1], (&D_807F5DF0)[i * 3 + 2], &D_807F5E20[i * 3], &D_807F5E24[i * 3], &D_807F5E28[i * 3]);
    }
}

typedef struct R2F550aPoly {
    /* 0x00 */ s16 v[12];
    /* 0x18 */ u8 type;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 a;
    /* 0x28 */ f64 b;
    /* 0x30 */ f64 c;
    /* 0x38 */ f64 d;
} R2F550aPoly; /* 0x40 */

#ifdef NON_MATCHING
void func_8062B194(R2F550aPoly *);
void func_8062B220(R2F550aPoly *);

void func_8062AD28(f32 arg0, f32 arg1, f32 arg2, R2F550aPoly *arg3, f32 *arg4) {
    s32 i;
    f32 xs[5];
    f32 ys[5];
    f32 zs[5];
    R2F550aPoly *poly;
    s32 pad0;

    poly = arg3;
    for (i = 0; i < 4; i++) {
        poly++;
        poly[-1].v[0] = arg0;
        poly[-1].v[1] = arg1;
        poly[-1].v[2] = arg2;
        poly[-1].type = 3;
    }
    arg3[0].v[3] = arg4[0];
    arg3[0].v[4] = arg4[1];
    arg3[0].v[5] = arg4[2];
    arg3[0].v[6] = arg4[3];
    arg3[0].v[7] = arg4[4];
    arg3[0].v[8] = arg4[5];
    xs[0] = arg4[6];
    ys[0] = arg4[7];
    zs[0] = arg4[8];
    arg3[1].v[3] = arg4[6];
    arg3[1].v[4] = arg4[7];
    arg3[1].v[5] = arg4[8];
    arg3[1].v[6] = arg4[0];
    arg3[1].v[7] = arg4[1];
    arg3[1].v[8] = arg4[2];
    xs[1] = arg4[9];
    ys[1] = arg4[10];
    zs[1] = arg4[11];
    arg3[2].v[3] = arg4[9];
    arg3[2].v[4] = arg4[10];
    arg3[2].v[5] = arg4[11];
    arg3[2].v[6] = arg4[6];
    arg3[2].v[7] = arg4[7];
    arg3[2].v[8] = arg4[8];
    xs[2] = arg4[0];
    ys[2] = arg4[1];
    zs[2] = arg4[2];
    arg3[3].v[3] = arg4[3];
    arg3[3].v[4] = arg4[4];
    arg3[3].v[5] = arg4[5];
    arg3[3].v[6] = arg4[9];
    arg3[3].v[7] = arg4[10];
    arg3[3].v[8] = arg4[11];
    xs[3] = arg4[0];
    ys[3] = arg4[1];
    zs[3] = arg4[2];
    arg3[4].type = 4;
    arg3[4].v[0] = arg4[6];
    arg3[4].v[1] = arg4[7];
    arg3[4].v[2] = arg4[8];
    arg3[4].v[3] = arg4[9];
    arg3[4].v[4] = arg4[10];
    arg3[4].v[5] = arg4[11];
    arg3[4].v[6] = arg4[0];
    arg3[4].v[7] = arg4[1];
    arg3[4].v[8] = arg4[2];
    arg3[4].v[9] = arg4[3];
    arg3[4].v[10] = arg4[4];
    arg3[4].v[11] = arg4[5];
    zs[4] = arg2;
    ys[4] = arg1;
    xs[4] = arg0;
    poly = arg3;
    for (i = 0; i < 5; i++) {
        func_8062B220(poly);
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < 0.0) {
            func_8062B194(poly);
            func_8062B220(poly);
        }
        poly++;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062AD28.s")
#endif

void func_8062B194(R2F550aPoly *arg0) {
    s16 a0;
    s16 a1;
    s16 a2;

    switch (arg0->type) {
        case 3:
            a0 = arg0->v[0];
            a1 = arg0->v[1];
            a2 = arg0->v[2];
            arg0->v[0] = arg0->v[3];
            arg0->v[1] = arg0->v[4];
            arg0->v[2] = arg0->v[5];
            arg0->v[3] = a0;
            arg0->v[4] = a1;
            arg0->v[5] = a2;
            break;
        case 4:
            a0 = arg0->v[0];
            a1 = arg0->v[1];
            a2 = arg0->v[2];
            arg0->v[0] = arg0->v[6];
            arg0->v[1] = arg0->v[7];
            arg0->v[2] = arg0->v[8];
            arg0->v[6] = a0;
            arg0->v[7] = a1;
            arg0->v[8] = a2;
            break;
    }
}

#ifdef NON_MATCHING
void func_8062B220(R2F550aPoly *arg0) {
    s16 temp_v1;
    s16 temp_v0;
    f64 temp_fa0;
    f64 temp_ft4;
    f64 temp_fs2;
    s16 temp_a2;
    f64 temp_fv1;
    s16 temp_a1;
    f64 temp_fs1;
    s16 temp_t2;
    f64 temp_fs0;
    s16 temp_t0;
    s16 temp_a3;
    s16 *new_var;
    s16 temp_t3;
    s16 temp_t1;
    f64 new_var2;
    f64 temp_fa1;
    f64 temp_fv0;
    f64 temp_ft5;

    temp_t0 = arg0->v[4];
    new_var = arg0->v;
    temp_a3 = new_var[8];
    temp_a1 = arg0->v[7];
    temp_v1 = arg0->v[5];
    temp_a2 = new_var[1];
    temp_v0 = new_var[2];
    temp_fa0 = (f64) temp_t0;
    temp_fv0 = (f64) temp_a1;
    temp_t3 = new_var[6];
    temp_t2 = new_var[3];
    temp_t1 = arg0->v[0];
    temp_fv1 = (f64) temp_a2;
    temp_fa1 = (f64) temp_a3;
    arg0->a = (f64) (((f64) (temp_v0 - temp_v1) * temp_fv0) + ((temp_fv1 * (f64) (temp_v1 - temp_a3)) + (temp_fa0 * (f64) (temp_a3 - temp_v0))));
    temp_ft5 = (f64) temp_v1;
    temp_ft4 = (f64) temp_v0;
    temp_fs0 = (f64) temp_t3;
    arg0->b = (f64) (((f64) (temp_t1 - temp_t2) * temp_fa1) + ((temp_ft4 * (f64) (temp_t2 - temp_t3)) + (temp_ft5 * (f64) (temp_t3 - temp_t1))));
    new_var2 = temp_fs0;
    temp_fs2 = (f64) temp_t2;
    temp_fs1 = (f64) temp_t1;
    arg0->c = (f64) (((f64) (temp_a2 - temp_t0) * new_var2) + ((temp_fs1 * (f64) (temp_t0 - temp_a1)) + (temp_fs2 * (f64) (temp_a1 - temp_a2))));
    arg0->d = (f64) -((((temp_fv1 * temp_ft5) - (temp_ft4 * temp_fa0)) * new_var2) + ((temp_fs1 * ((temp_fa0 * temp_fa1) - (temp_fv0 * temp_ft5))) + (temp_fs2 * ((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)))));
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B220.s")
#endif

typedef struct R2F550aNode {
    /* 0x00 */ struct R2F550aNode *unk0;
    /* 0x04 */ struct R2F550aNode *unk4;
    /* 0x08 */ u8 pad8[0x68];
    /* 0x70 */ s16 unk70[0x1C];
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ u8 unkAC[0x19];
    /* 0xC5 */ u8 unkC5;
} R2F550aNode;

void func_8063C3C0(s16);

void func_8062B3C4(R2F550aNode *arg0, s32 *arg1) {
    s32 i;
    s32 temp;

    for (;;) {
        if (arg0 == NULL) {
            break;
        }
        for (i = 0; i < arg0->unkC5; i++) {
            func_8063C3C0(arg0->unk70[i]);
            temp = arg0->unkAC[i] + 1;
            if (*arg1 < temp) {
                *arg1 = temp;
            }
        }
        func_8062B3C4(arg0->unk0, arg1);
        arg0 = arg0->unk4;
    }
}

typedef struct R2F550aSlot {
    /* 0x00 */ Mtx mtx[2];
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} R2F550aSlot; /* 0x90 */

extern R2F550aSlot *D_807F5FB8;
extern s32 D_807F5FBC;
extern u8 D_807F5FC0;
void *func_80610FE8(s32);

void func_8062B478(s32 arg0) {
    s32 i;

    if (arg0 == 0) {
        D_807F5FB8 = NULL;
        D_807F5FBC = 0;
        return;
    }
    D_807F5FB8 = func_80610FE8(arg0 * 0x90);
    D_807F5FBC = arg0;
    for (i = 0; i < arg0; i++) {
        D_807F5FB8[i].unk80 = 0.0f;
        D_807F5FB8[i].unk84 = 0.0f;
        D_807F5FB8[i].unk88 = 0.0f;
        D_807F5FB8[i].unk8C = 1;
    }
    D_807F5FC0 = 0;
}

void func_8062B630(s16 arg0, u8 arg1) {
    D_807F5FB8[arg0].unk8C = arg1;
}

extern s32 D_807F6C28;

void func_8062B660(void) {
    s32 i;

    D_807F5FC0 = 0;
    for (i = 0; i < D_807F5FBC; i++) {
        if (D_807F5FB8[i].unk80 != 0.0) {
            guTranslate(&D_807F5FB8[i].mtx[D_807444FC], 0.0f, D_807F6C28 != 0 ? D_807F5FB8[i].unk80 * 3.0f : D_807F5FB8[i].unk80, 0.0f);
        }
        if (D_807F5FB8[i].unk80 != D_807F5FB8[i].unk84) {
            D_807F5FC0 = 1;
            if (D_807F5FB8[i].unk80 < D_807F5FB8[i].unk84) {
                D_807F5FB8[i].unk80 += D_807F5FB8[i].unk88;
                if (D_807F5FB8[i].unk84 < D_807F5FB8[i].unk80) {
                    D_807F5FB8[i].unk80 = D_807F5FB8[i].unk84;
                }
            } else {
                D_807F5FB8[i].unk80 -= D_807F5FB8[i].unk88;
                if (D_807F5FB8[i].unk80 < D_807F5FB8[i].unk84) {
                    D_807F5FB8[i].unk80 = D_807F5FB8[i].unk84;
                }
            }
        }
    }
}

f32 func_8062B840(s8 arg0) {
    return D_807F5FB8[arg0].unk80;
}

void func_8062B86C(s32 arg0, f32 arg1, f32 arg2) {
    D_807F5FB8[arg0].unk84 = arg1;
    D_807F5FB8[arg0].unk88 = arg2;
}

void func_8062B8A4(s32 arg0, f32 arg1, f32 arg2) {
    D_807F5FB8[arg0].unk84 += arg1;
    D_807F5FB8[arg0].unk88 = arg2;
}

void func_8062B8E4(f32 *arg0) {
    s32 i;
    s32 n;

    n = D_807F5FBC;
    for (i = 0; i < n; i++) {
        arg0[i] = D_807F5FB8[i].unk84;
    }
}

void func_8062BA0C(f32 *arg0) {
    s32 i;

    for (i = 0; i < D_807F5FBC; i++) {
        D_807F5FB8[i].unk84 = arg0[i];
        D_807F5FB8[i].unk80 = arg0[i];
    }
}

typedef struct R2F550bSrc {
    struct R2F550bSrc *unk0;
    struct R2F550bSrc *unk4;
} R2F550bSrc;

typedef struct R2F550bNode {
    u8 pad0;
    u8 unk1;
    u8 pad2[2];
    s32 unk4;
    s32 unk8;
    struct R2F550bNode *unkC;
    struct R2F550bNode *unk10;
} R2F550bNode;


R2F550bNode *func_8062BA74(R2F550bSrc *arg0) {
    R2F550bNode *node;

    if (arg0 == NULL) {
        return NULL;
    }
    node = func_80610FE8(0x14);
    node->unk4 = 0;
    node->unk8 = 0;
    node->unk1 = 3;
    node->unkC = func_8062BA74(arg0->unk0);
    node->unk10 = func_8062BA74(arg0->unk4);
    return node;
}

typedef struct R2F550bObj {
    struct R2F550bObj *unk0;
    struct R2F550bObj *unk4;
    u8 pad8[0xC];
    struct R2F550bObj *unk14;
    u8 pad18[6];
    s16 unk1E;
    u8 pad20[4];
    u8 unk24;
    u8 pad25[0x93];
    u8 unkB8;
} R2F550bObj;

typedef struct R2F550bTree {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    R2F550bObj *unk4;
    s32 unk8;
    struct R2F550bTree *unkC;
    struct R2F550bTree *unk10;
} R2F550bTree;

void func_8062BB2C(R2F550bObj *, R2F550bTree *, u8);

extern R2F550bObj *D_807F5DE4;
extern R2F550bTree *D_807F5E60;

void func_8063B4A4(void);
void func_8063B758(void);
void func_80641A78(void);

void func_8062BAE4(void) {
    func_8063B4A4();
    func_8062BB2C(D_807F5DE4, D_807F5E60, 1);
    func_8063B758();
    func_80641A78();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062BB2C.s")

extern R2F550bObj *D_807F5FF4;

u8 func_8062BDB0(void *, R2F550bObj *, R2F550bTree *, f32, f32, f32, s32);
s32 func_80668E9C(void *, s16, f32, f32, f32, s32);

u8 func_8062BCC8(void *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    u8 result;
    R2F550bObj *item;

    result = func_8062BDB0(arg0, D_807F5DE4, D_807F5E60, arg1, arg2, arg3, arg4);
    item = D_807F5FF4;
    while (item != NULL) {
        if (item->unk24 == 1) {
            result |= func_80668E9C(arg0, item->unk1E, arg1, arg2, arg3, arg4);
        }
        item = item->unk14;
    }
    return result;
}

u8 func_80652BC8(void *, f32, f32, f32, s32);

u8 func_8062BDB0(void *arg0, R2F550bObj *arg1, R2F550bTree *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    u8 result;
    s32 other;
    R2F550bObj *item;

    result = 0;
    switch (arg1->unkB8) {
        case 2:
            return func_80652BC8(arg0, arg3, arg4, arg5, arg6);
        case 1:
            item = arg2->unk4;
            while (item != NULL) {
                if (item->unk24 == 1) {
                    result |= func_80668E9C(arg0, item->unk1E, arg3, arg4, arg5, arg6);
                }
                item = item->unk14;
            }
            return result;
        case 0:
            result = func_8062BDB0(arg0, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
            other = func_8062BDB0(arg0, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
            return result | other;
    }
    return 0;
}

typedef struct R2F550bCamera {
    u8 pad0[0x129];
    u8 unk129;
} R2F550bCamera;

typedef struct R2F550bViewport {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R2F550bViewport;

typedef struct R2F550bPlayer {
    u8 unk0;
    u8 pad1[3];
    R2F550bCamera *unk4;
    u8 pad8[0x214];
    s32 unk21C;
    s32 unk220;
    s32 unk224;
    u8 pad228[0xC];
    f32 unk234;
    f32 unk238;
    f32 unk23C;
    u8 pad240[0x40];
    f32 unk280;
    u8 pad284[4];
    f32 unk288;
    f32 unk28C;
    u8 pad290[0x5A];
    u8 unk2EA;
    u8 pad2EB[5];
} R2F550bPlayer;

#define R2F550bPLAYER(i) (((R2F550bPlayer *)D_807FC924)[i])

extern Gfx D_1000118;
extern u8 D_80750AB4;
extern u8 D_807F5FEC;
extern u8 D_807F5FED;
extern u8 D_807FC929;
extern void *D_807FC924;

void func_8062C1C0(s32);
void func_8062C22C(void);
f32 func_8062A850(void);
Gfx *func_8062C29C(Gfx *, s32, s32, s32, f32, f32, f32, f32, f32, f32);
R2F550bViewport *cameraFindViewportEntry(u8);

Gfx *func_8062BF24(Gfx *gfx, s32 arg1) {
    s32 i;
    u8 alpha;
    R2F550bViewport *vp;

    func_8062C1C0(arg1);
    gDPPipeSync(gfx++);
    if (D_807F5FED != 0) {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_1PRIMITIVE);
    } else {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_NPRIMITIVE);
    }
    for (i = 0; i < D_80750AB4; i++) {
        if (R2F550bPLAYER(i).unk0 != 0) {
            D_807FC929 = i;
            gfx = func_8062C29C(gfx, R2F550bPLAYER(i).unk21C, R2F550bPLAYER(i).unk220, R2F550bPLAYER(i).unk224,
                                R2F550bPLAYER(i).unk234, R2F550bPLAYER(i).unk238, R2F550bPLAYER(i).unk23C,
                                R2F550bPLAYER(i).unk28C, R2F550bPLAYER(i).unk280 * func_8062A850(),
                                R2F550bPLAYER(i).unk288);
            D_807F5FEC = 0;
        }
        if (R2F550bPLAYER(i).unk0 == 0 || R2F550bPLAYER(i).unk2EA != 0) {
            alpha = R2F550bPLAYER(i).unk4->unk129;
            vp = cameraFindViewportEntry(i);
            gSPDisplayList(gfx++, &D_1000118);
            gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
            gDPPipeSync(gfx++);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0xFF - alpha);
            gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPFillRectangle(gfx++, vp->unk4, vp->unk6, vp->unk8, vp->unkA);
            gDPPipeSync(gfx++);
        }
    }
    func_8062C22C();
    gDPPipeSync(gfx++);
    return gfx;
}


void func_8065EFF0(void);
void func_8062D3E4(R2F550bObj *);
void func_8063039C(void);
void func_8062EE48(u8);
void mapChunkResetFlags(void);
void func_8065A884(void);
void effectUpdateNodes(void);

void func_8062C1C0(s32 arg0) {
    func_8065EFF0();
    func_8062D3E4(D_807F5FF4);
    func_8063039C();
    if (D_807F6C28 == 0) {
        func_8062EE48(0xFF);
    }
    mapChunkResetFlags();
    func_8065A884();
    effectUpdateNodes();
    D_807F5FEC = 1;
}

void mapChunkReleaseAndAdvance(void);
void func_8062EFA0(void);
void mapChunkFreeIdleBuffers(void);
void func_80653FA4(void);
void mapChunkSetIndexOverride(s8);
void func_8063C450(void);
void func_8062B660(void);
void func_80636C00(void);
void func_806364C4(void);

void func_8062C22C(void) {
    if (D_807F6C28 != 0) {
        mapChunkReleaseAndAdvance();
        func_8062EFA0();
        mapChunkFreeIdleBuffers();
        func_80653FA4();
        mapChunkSetIndexOverride(0);
    }
    func_8063C450();
    func_8062B660();
    func_80636C00();
    func_806364C4();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062C29C.s")

void func_8062C99C(s16 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0[0] = (arg3 - arg1) * 2;
    arg0[1] = (arg4 - arg2) * 2;
    arg0[2] = 0x1FF;
    arg0[3] = 0;
    arg0[4] = ((arg1 + arg3) / 2) * 4;
    arg0[5] = ((arg2 + arg4) / 2) * 4;
    arg0[6] = 0x1FF;
    arg0[7] = 0;
}

extern s32 D_807F5FF8;
extern u8 D_807F6009;

Gfx *func_80630B70(Gfx *, s32, f32, f32, f32, s32, s32, s32);

void func_8062CA0C(Gfx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_807F6009 = 0xFF;
    func_80630B70(arg0, D_807F5FF8, arg1, arg2, arg3, 0x30030, -1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062CA70.s")

typedef struct R2F550bMapView {
    u8 pad0[0x1C];
    void *unk1C[21];
    s16 unk70[12];
    s16 unk88[18];
    u8 unkAC[13];
    u8 unkB9[12];
    u8 unkC5;
} R2F550bMapView;


s32 mapChunkIsActive(s16);
Gfx *func_8063C418(Gfx *, s16);

Gfx *func_8062CEA8(Gfx *gfx, R2F550bMapView *arg1, u8 arg2) {
    s32 i;
    u8 idx;

    for (i = 0; i < arg1->unkC5; i++) {
        if (arg2 == arg1->unkB9[i] && (arg1->unk88[i] == -1 || mapChunkIsActive(arg1->unk88[i]) != 0)) {
            gfx = func_8063C418(gfx, arg1->unk70[i]);
            gSPClearGeometryMode(gfx++, G_CULL_BACK);
            idx = arg1->unkAC[i];
            if (D_807F5FB8[idx].unk80 != 0.0 && D_807F5FB8[idx].unk8C != 0) {
                gSPMatrix(gfx++, osVirtualToPhysical((u8 *)D_807F5FB8 + idx * 0x90 + (D_807444FC << 6)),
                          G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPDisplayList(gfx++, osVirtualToPhysical(arg1->unk1C[i]));
                gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
            } else {
                gSPDisplayList(gfx++, osVirtualToPhysical(arg1->unk1C[i]));
            }
            gDPPipeSync(gfx++);
        }
    }
    return gfx;
}

u8 func_8062D0CC(R2F550bObj *, R2F550bTree *, s32, u8);

void func_8062D094(s32 arg0, u8 arg1) {
    func_8062D0CC(D_807F5DE4, D_807F5E60, arg0, arg1);
}

void func_806524A0(s32, u8);
void func_806307CC(R2F550bObj *, s32, s32, u8, u8 *);

u8 func_8062D0CC(R2F550bObj *arg0, R2F550bTree *arg1, s32 arg2, u8 arg3) {
    u8 unused;
    u8 sp26;

    sp26 = 0;
    if (arg0 == NULL) {
        return 0;
    }
    switch (arg0->unkB8) {
        case 2:
            func_806524A0(arg2, arg3);
            return 1;
        case 1:
            func_806307CC(arg1->unk4, arg2, 0, arg3, &sp26);
            return sp26;
        case 0:
            if (func_8062D0CC(arg0->unk0, arg1->unkC, arg2, arg3) != 0) {
                return 1;
            }
            return func_8062D0CC(arg0->unk4, arg1->unk10, arg2, arg3);
    }
}

s32 func_807142D8(void);
void func_8062D1E0(R2F550bObj *, R2F550bTree *);

void func_8062D1A8(void) {
    if (func_807142D8() == 0) {
        func_8062D1E0(D_807F5DE4, D_807F5E60);
    }
}

void func_806323C0(R2F550bObj *);
void mapChunkResolveNodeAssets(void);

void func_8062D1E0(R2F550bObj *arg0, R2F550bTree *arg1) {
    for (;;) {
        if (arg0 == NULL) {
            return;
        }
        switch (arg0->unkB8) {
            case 2:
                mapChunkResolveNodeAssets();
                return;
            case 1:
                func_806323C0(arg1->unk4);
                return;
            case 0:
                func_8062D1E0(arg0->unk0, arg1->unkC);
                arg0 = arg0->unk4;
                arg1 = arg1->unk10;
                break;
            default:
                return;
        }
    }
}

R2F550bObj *func_80630588(R2F550bObj *, s32, s32, u8 *);
void func_8062D2AC(s32, s16 *, u8);

void func_8062D26C(s32 arg0) {
    u8 sp1F;
    s16 sp1C;

    func_80630588(NULL, arg0, 1, &sp1F);
    func_8062D2AC(arg0, &sp1C, 1);
}

u8 func_8062D2F0(R2F550bObj *, R2F550bTree *, s32, s16 *, u8);

void func_8062D2AC(s32 arg0, s16 *arg1, u8 arg2) {
    func_8062D2F0(D_807F5DE4, D_807F5E60, arg0, arg1, arg2);
}

u8 mapChunkPurgeNodeList(s32, s16 *, u8);

u8 func_8062D2F0(R2F550bObj *arg0, R2F550bTree *arg1, s32 arg2, s16 *arg3, u8 arg4) {
    u8 sp27;

    if (arg0 == NULL) {
        return 0;
    }
    switch (arg0->unkB8) {
        case 2:
            return mapChunkPurgeNodeList(arg2, arg3, arg4);
        case 1:
            arg1->unk4 = func_80630588(arg1->unk4, arg2, 0, &sp27);
            return sp27;
        case 0:
            if (func_8062D2F0(arg0->unk0, arg1->unkC, arg2, arg3, arg4) != 0 && arg4 == 0) {
                return 1;
            }
            return func_8062D2F0(arg0->unk4, arg1->unk10, arg2, arg3, arg4);
    }
    return 0;
}

typedef struct R2F550cEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ struct R2F550cEntry *unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 pad23;
    /* 0x24 */ u8 unk24;
} R2F550cEntry;

void func_8062D414(R2F550bObj *, R2F550bTree *, R2F550cEntry *);

void func_8062D3E4(R2F550bObj *arg0) {
    func_8062D414(D_807F5DE4, D_807F5E60, (R2F550cEntry *)arg0);
}

s32 func_806303C4(s32, u8, s32, f32, f32, f32, s32, s32, s32, s32, s32);
u8 func_8062E898(void *, u8 *, f32, f32, f32);
void func_806306D0(s32);
void mapChunkUpdateEntryNode(R2F550cEntry *);

void func_8062D414(R2F550bObj *arg0, R2F550bTree *arg1, R2F550cEntry *arg2) {
    s32 pad;
    s32 listA;
    s32 listB;
    s32 sp58;

    listA = 0;
    listB = 0;
    if (arg0 == NULL) {
        return;
    }
    switch (arg0->unkB8) {
        case 2:
            if (arg2 != NULL) {
                do {
                    mapChunkUpdateEntryNode(arg2);
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            break;
        case 1:
            if (arg2 != NULL) {
                do {
                    arg1->unk4 = (R2F550bObj *)func_806303C4((s32)arg1->unk4, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            break;
        case 0:
            if (arg2 != NULL) {
                do {
                    if (func_8062E898(arg0, (u8 *)&sp58 + 2, arg2->unk4, arg2->unk8, arg2->unkC) != 0) {
                        listB = func_806303C4(listB, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    } else {
                        listA = func_806303C4(listA, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    }
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            func_8062D414(arg0->unk0, arg1->unkC, (R2F550cEntry *)listA);
            func_8062D414(arg0->unk4, arg1->unk10, (R2F550cEntry *)listB);
            func_806306D0(listA);
            func_806306D0(listB);
            break;
    }
}

typedef struct R2F550cBox {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
} R2F550cBox;

extern f32 D_807F5FA8;
extern u8 D_807F5E68[];

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062D620.s")

s32 func_8062DBDC(s16, s16, s16, s16, s16, s16, f32, f32, f32, f32, void *);

s32 func_8062DAF4(R2F550bObj *arg0, f32 arg1, f32 arg2, f32 arg3) {
    R2F550cBox *box;

    box = (R2F550cBox *)arg0;
    return func_8062DBDC(box->unkA0, box->unkA2, box->unkA4, box->unkA6, box->unkA8, box->unkAA, arg1, arg2, arg3, D_807F5FA8, D_807F5E68);
}

extern f32 D_807F5E50[];

void func_8062DB70(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    D_807F5E50[0] = arg3 - arg0;
    D_807F5E50[1] = arg4 - arg1;
    D_807F5E50[2] = arg5 - arg2;
    D_807F5E50[3] = -(((D_807F5E50[0] * arg0) + (D_807F5E50[1] * arg1)) + (D_807F5E50[2] * arg2));
}


typedef struct R2F550cPlane {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 unk20;
    /* 0x28 */ f64 unk28;
    /* 0x30 */ f64 unk30;
    /* 0x38 */ f64 unk38;
} R2F550cPlane;

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062DBDC.s")

f32 func_8062E040(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 new_var;
    f32 sp30;
    f32 var_fs0;
    f32 sp58;
    f32 temp_fs1;
    f32 sp38;
    f32 sp3C;
    f32 temp_fs2;

    var_fs0 = (f32)arg0;
    sp3C = (var_fs0 - arg6) * (var_fs0 - arg6);
    sp38 = (((f32)arg1 - arg7) * ((f32)arg1 - arg7));
    temp_fs1 = (((f32)arg2 - arg8) * ((f32)arg2 - arg8));
    new_var = (((f32)arg4 - arg7) * ((f32)arg4 - arg7));
    temp_fs2 = (((f32)arg5 - arg8) * ((f32)arg5 - arg8));
    var_fs0 = (sp3C + sp38) + temp_fs1;
    sp30 = (sp58 = (sp3C + sp38) + temp_fs2);
    if (sp30 < var_fs0) {
        var_fs0 = sp30;
    }
    if ((sp3C + new_var) + temp_fs1 < var_fs0) {
        var_fs0 = (sp3C + new_var) + temp_fs1;
    }
    if ((sp3C + new_var) + temp_fs2 < var_fs0) {
        var_fs0 = (sp3C + new_var) + temp_fs2;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs1 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs1;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs2 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs2;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs1 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs1;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs2 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs2;
    }
    return sqrtf(var_fs0);
}


void func_8062E3B4(s16 *, s16 *, s32, s32 *, u8, f64, u8);

s32 func_8062E1F8(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, void *arg7) {
    s16 sp88[0x24];
    s16 sp40[0x24];
    s32 sp3C;
    char pad;

    func_8062E3B4((s16 *)((u8 *)arg7 + (arg0 << 6)), sp88, ((R2F550cPlane *)((u8 *)arg7 + (arg0 << 6)))->unk18, &sp3C, 0, arg1, 0);
    if (sp3C == 0) {
        return 0;
        do {
        } while (0);
    }
    func_8062E3B4(sp88, sp40, sp3C, &sp3C, 0, arg4, 1);
    if (sp3C == 0) {
        return 0;
    }
    func_8062E3B4(sp40, sp88, sp3C, &sp3C, 1, arg2, 0);
    if (sp3C == 0) {
        return 0;
    }
    func_8062E3B4(sp88, sp40, sp3C, &sp3C, 1, arg5, 1);
    if (sp3C == 0) {
        return 0;
    }
    func_8062E3B4(sp40, sp88, sp3C, &sp3C, 2, arg3, 0);
    if (sp3C == 0) {
        return 0;
    }
    func_8062E3B4(sp88, sp40, sp3C, &sp3C, 2, arg6, 1);
    if (sp3C != 0) {
        return 1;
    }
    return 0;
}

s32 func_8062E548(s16 *, u8, f64, u8);
void func_8062E608(void *, s32 *, void *);
void func_8062E67C(s16 *, s16 *, u8, f64, s16 *);

void func_8062E3B4(s16 *arg0, s16 *arg1, s32 arg2, s32 *arg3, u8 arg4, f64 arg5, u8 arg6) {
    s32 i;
    s16 *prev;
    s16 sp60[3];
    s16 *cur;
    s16 *last;

    *arg3 = 0;
    prev = (s16 *)(arg2 * 6 + (s32)arg0 - 6);
    i = 0;
    if (arg2 > 0) {
        cur = arg0;
        do {
            last = cur;
            if (func_8062E548(cur, arg4, arg5, arg6) != 0) {
                if (func_8062E548(prev, arg4, arg5, arg6) != 0) {
                    func_8062E608(cur, arg3, arg1);
                } else {
                    func_8062E67C(prev, cur, arg4, arg5, sp60);
                    func_8062E608(sp60, arg3, arg1);
                    func_8062E608(cur, arg3, arg1);
                }
            } else if (func_8062E548(prev, arg4, arg5, arg6) != 0) {
                func_8062E67C(prev, cur, arg4, arg5, sp60);
                func_8062E608(sp60, arg3, arg1);
            }
            i++;
            cur += 3;
            prev = last;
        } while (i != arg2);
    }
}

s32 func_8062E548(s16 *arg0, u8 arg1, f64 arg2, u8 arg3) {
    f64 coord;

    switch (arg1) {
        case 0:
            coord = arg0[0];
            break;
        case 1:
            coord = arg0[1];
            break;
        case 2:
            coord = arg0[2];
            break;
    }
    switch (arg3) {
        case 0:
            if (arg2 <= coord) {
                return 1;
            }
            break;
        case 1:
            if (coord <= arg2) {
                return 1;
            }
            break;
    }
    return 0;
}

void faultSetMessage(s32, s32, s32, s32);

void func_8062E608(void *arg0, s32 *arg1, void *arg2) {
    memcpy((u8 *)arg2 + *arg1 * 6, arg0, 6);
    *arg1 += 1;
    if (*arg1 >= 0xD) {
        faultSetMessage(1, 0, 0, 0);
    }
}

void func_8062E67C(s16 *arg0, s16 *arg1, u8 arg2, f64 arg3, s16 *arg4) {
    f32 t;

    switch (arg2) {
        case 0:
            t = (arg3 - arg0[0]) / (arg1[0] - arg0[0]);
            arg4[1] = (arg1[1] - arg0[1]) * t + arg0[1];
            arg4[2] = (arg1[2] - arg0[2]) * t + arg0[2];
            arg4[0] = arg3;
            break;
        case 1:
            t = (arg3 - arg0[1]) / (arg1[1] - arg0[1]);
            arg4[0] = (arg1[0] - arg0[0]) * t + arg0[0];
            arg4[2] = (arg1[2] - arg0[2]) * t + arg0[2];
            arg4[1] = arg3;
            break;
        case 2:
            t = (arg3 - arg0[2]) / (arg1[2] - arg0[2]);
            arg4[0] = (arg1[0] - arg0[0]) * t + arg0[0];
            arg4[1] = (arg1[1] - arg0[1]) * t + arg0[1];
            arg4[2] = arg3;
            break;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E898.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EBB8.s")


typedef struct R2F550a2Chunk {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x70];
} R2F550a2Chunk; /* 0x7C */

extern u8 D_807F5FC1;
extern R2F550a2Chunk *D_807F5FC4;

#ifdef NON_MATCHING
typedef struct R2F550a2Cmd {
    u32 unk0;
    u32 unk4;
} R2F550a2Cmd;

R2F550a2Cmd *func_8062EDA8(R2F550a2Cmd *arg0, u8 arg1) {
    R2F550a2Cmd *p;
    R2F550a2Cmd *q;
    R2F550a2Chunk *c;
    s32 i;

    p = arg0;
    for (i = 0; i < D_807F5FC1; i++) {
        c = &D_807F5FC4[i];
        if (arg1 == c->unk1) {
            q = p;
            q->unk0 = ((c->unk0 * 4) & 0xFFFF) | 0xDB060000;
            p++;
            q->unk4 = D_807F5FC4[i].unk8;
        }
    }
    return p;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EDA8.s")
#endif

typedef struct R2F550fChunk {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC[1];
    /* 0x10 */ u8 pad10[0x6C];
} R2F550fChunk; /* 0x7C */

void assetFreeBuffer(s32, s32, s32);
s32 func_8066B0F8(s32, s32, s32, s32);

#define R2F550F_CHUNK ((R2F550fChunk *)D_807F5FC4)[i]

void func_8062EE48(u8 arg0) {
    s32 i;
    s32 flag;

    for (i = 0; i < D_807F5FC1; i++) {
        if (arg0 == R2F550F_CHUNK.unk1) {
            flag = 0;
            R2F550F_CHUNK.unk4++;
            if (R2F550F_CHUNK.unk4 == R2F550F_CHUNK.unk2) {
                R2F550F_CHUNK.unk4 = 0;
                R2F550F_CHUNK.unk5++;
                if (R2F550F_CHUNK.unk5 == R2F550F_CHUNK.unk3) {
                    R2F550F_CHUNK.unk5 = 0;
                }
                flag = 1;
            }
            if (R2F550F_CHUNK.unk8 == 0) {
                flag = 1;
            }
            if (flag) {
                if (R2F550F_CHUNK.unk8 != 0) {
                    assetFreeBuffer(R2F550F_CHUNK.unk8, 0x7E3, 5);
                }
                R2F550F_CHUNK.unk8 = func_8066B0F8(7, R2F550F_CHUNK.unkC[R2F550F_CHUNK.unk5], 0, 0);
            }
        }
    }
}

#undef R2F550F_CHUNK


s32 mapChunkIsVisible(u8);

void func_8062EFA0(void) {
    s32 i;

    for (i = 0; i < D_807F5FC1; i++) {
        if (mapChunkIsVisible(D_807F5FC4[i].unk1) == 0) {
            if (D_807F5FC4[i].unk8 != 0) {
                assetFreeBuffer(D_807F5FC4[i].unk8, 0x7FB, 5);
                D_807F5FC4[i].unk8 = 0;
            }
        }
    }
}

typedef struct R2F550fMapHdr {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
} R2F550fMapHdr;

#define R2F550F_HDR ((R2F550fMapHdr *)arg0)

extern u8 *D_807F5DE0;
extern f32 D_807F5FDC;
extern f32 D_807444C4;
extern s32 D_807FB5E0;
extern s32 D_807FB5E4;
extern s16 D_807FB5E8;
extern s16 D_807FB5EA;
extern s16 D_807F9450;
extern s16 D_807F9452;
extern s16 D_807F9454;
extern s16 D_807F9456;
extern s16 D_807FD574;
extern s16 D_807FD576;
extern s16 D_807FD578;
extern s16 D_807F5FE4;
extern s16 D_807F5FE6;
extern s16 D_807F5FE8;
extern s16 D_807F5FEA;
extern s32 D_807F5FD0;
extern s32 *D_807F5FD4;
extern s32 D_807F5FC8;
extern s32 D_807F5FCC;
extern s32 D_807F5DE8;
extern void *D_807F5DEC;

f32 cosApprox(f32);
void fogSetParams(u8);
void renderSetSegment6Override(u8);
void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void func_8065E040(s32);
struct R2F550fNode;
void func_8062F420(struct R2F550fNode *, s32, s32);
void func_8062F3A0();
void func_8062F328(s32);
void func_8063C390(void);
void func_80650ECC(void *);
void func_8066C958(void *);
void func_80666090(void *);
void func_8065F1C0(void *);
void func_80662B90(void *);
void triggerZoneInit(void *);
void func_8062F318(void);

void func_8062F050(s32 arg0) {
    s32 off30;
    s32 off34;
    s32 off38;
    s32 off44;
    s32 off40;
    s32 off48;
    s32 pad[5];
    s32 sp28;

    D_807F5DE0 = (u8 *)arg0;
    sp28 = 0;
    D_807F5FDC = cosApprox(0.7853981853f);
    fogSetParams(R2F550F_HDR->unk8 & 1);
    renderSetSegment6Override((R2F550F_HDR->unk8 >> 1) & 1);
    D_807444C4 = R2F550F_HDR->unkA;
    D_807FB5E0 = R2F550F_HDR->unk14 << 3;
    D_807FB5E4 = R2F550F_HDR->unk16 << 3;
    D_807FB5E8 = R2F550F_HDR->unk10;
    D_807FB5EA = R2F550F_HDR->unk12;
    D_807F9450 = R2F550F_HDR->unk1C;
    D_807F9452 = R2F550F_HDR->unk1E;
    D_807F9454 = R2F550F_HDR->unk18;
    D_807F9456 = R2F550F_HDR->unk1A;
    D_807FD574 = R2F550F_HDR->unk20;
    D_807FD576 = R2F550F_HDR->unk22;
    D_807FD578 = R2F550F_HDR->unk24;
    D_807F5FE4 = R2F550F_HDR->unk26;
    D_807F5FE6 = R2F550F_HDR->unk28;
    D_807F5FE8 = R2F550F_HDR->unk2A;
    D_807F5FEA = R2F550F_HDR->unk2C;
    off40 = R2F550F_HDR->unk40;
    off30 = R2F550F_HDR->unk30;
    off34 = R2F550F_HDR->unk34;
    off38 = R2F550F_HDR->unk38;
    off44 = R2F550F_HDR->unk44;
    off48 = R2F550F_HDR->unk48;
    D_807F5FD0 = *(s32 *)(D_807F5DE0 + off40) + 1;
    D_807F5FD4 = (s32 *)(D_807F5DE0 + off40 + 4);
    D_807F5FC8 = *(s32 *)(D_807F5DE0 + off44);
    D_807F5FCC = (s32)(D_807F5DE0 + off44 + 4);
    D_807F5FC1 = *(s32 *)(D_807F5DE0 + off48);
    D_807F5FC4 = (R2F550a2Chunk *)(D_807F5DE0 + off48 + 4);
    D_807F5DE4 = (R2F550bObj *)(D_807F5DE0 + off30);
    D_807F5DE8 = (s32)(D_807F5DE0 + off38);
    D_807F5DEC = D_807F5DE0 + off34;
    lightSetTargetColor(1.0f, 1.0f, 1.0f, -1);
    lightCopyTargetColors(-1);
    func_8065E040(R2F550F_HDR->unkE << 10);
    func_8062F420((struct R2F550fNode *)(s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off34));
    func_8062F3A0(D_807F5DE0 + off34, D_807F5DE0 + off38);
    func_8062F328((s32)(D_807F5DE0 + off40));
    func_8063C390();
    func_8062B3C4((R2F550aNode *)D_807F5DE4, &sp28);
    func_8062B478(sp28);
    D_807F5E60 = (R2F550bTree *)func_8062BA74((R2F550bSrc *)D_807F5DE4);
    func_80650ECC((void *)arg0);
    func_8066C958((void *)arg0);
    func_80666090((void *)arg0);
    func_8065F1C0((void *)arg0);
    func_80662B90((void *)arg0);
    triggerZoneInit((void *)arg0);
    func_8062F318();
}

#undef R2F550F_HDR

void func_8062F318(void) {
    D_807F5FED = 1;
}

#ifdef NON_MATCHING

void func_8062F328(s32 arg0) {
    s32 i;

    if (D_807F5FD0 != 0) {
        i = 0;
        if (D_807F5FD0 >= 0) {
            do {
                D_807F5FD4[i] += arg0;
                i++;
            } while (D_807F5FD0 >= i);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F328.s")
#endif


s32 func_8062F388(s32 *arg0) {
    *arg0 = D_807F5FCC;
    return D_807F5FC8;
}

#ifdef NON_MATCHING

void func_8062F3A0(R2F550a2Cmd *arg0, R2F550a2Cmd *arg1) {
    R2F550a2Cmd *p;
    u32 t;

    p = arg0;
    if (p != arg1) {
        do {
            if ((p->unk0 >> 24) == 0xFD) {
                t = p->unk4;
                if (((t << 4) >> 28) == 0) {
                    p->unk4 = func_8066B0F8(0x19, t, 1, 0);
                }
            }
            p++;
        } while (p != arg1);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F3A0.s")
#endif

typedef struct R2F550fNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C[1];
    /* 0x20 */ u8 pad20[0x98];
    /* 0xB8 */ u8 unkB8;
    /* 0xB9 */ u8 padB9[0xC];
    /* 0xC5 */ u8 unkC5;
} R2F550fNode;

void func_8062F420(R2F550fNode *arg0, s32 arg1, s32 arg2) {
    s32 i;

    if (arg0 == NULL) {
        return;
    }
    switch (arg0->unkB8) {
        case 0:
            arg0->unk0 += arg1;
            arg0->unk4 += arg1;
            func_8062F420((R2F550fNode *)arg0->unk0, arg1, arg2);
            func_8062F420((R2F550fNode *)arg0->unk4, arg1, arg2);
            return;
        case 1:
        case 2:
            break;
        default:
            return;
    }
    if (arg0->unk8 != -1) {
        arg0->unk8 += arg2;
    }
    if (arg0->unkC != -1) {
        arg0->unkC += arg2;
    }
    if (arg0->unk10 != -1) {
        arg0->unk10 += arg2;
    }
    if (arg0->unk14 != -1) {
        arg0->unk14 += arg2;
    }
    if (arg0->unk18 != -1) {
        arg0->unk18 += arg2;
    }
    for (i = 0; i < arg0->unkC5; i++) {
        arg0->unk1C[i] += arg2;
    }
}

void func_8062F538(f32 (*arg0)[3], s32 arg1, s32 arg2, s32 arg3) {
    f32 t;
    s32 i;

    if (arg1 != 0) {
        i = 0;
        if (arg2 == 0) {
            for (i = 0; i < 3; i++) {
                t = arg0[arg2][i];
                arg0[arg2][i] = arg0[arg1][i];
                arg0[arg1][i] = t;
            }
            arg2 = arg1;
        } else {
            for (i = 0; i < 3; i++) {
                t = arg0[arg3][i];
                arg0[arg3][i] = arg0[arg1][i];
                arg0[arg1][i] = t;
            }
            arg3 = arg1;
        }
    }
    if (arg2 != 1) {
        for (i = 0; i < 3; i++) {
            t = arg0[arg3][i];
            arg0[arg3][i] = arg0[arg2][i];
            arg0[arg2][i] = t;
        }
    }
}

void func_8062F538(f32 (*)[3], s32, s32, s32);

s32 func_8062F640(f32 (*arg0)[3], f32 (*arg1)[3], s32 arg2) {
    s32 r0;
    s32 r1;
    s32 p;
    s32 q;
    s32 j;
    f32 t;
    f32 u;

    if (arg2 == 0) {
        r0 = 1;
        r1 = 2;
    } else if (arg2 == 1) {
        r0 = 0;
        r1 = 2;
    } else {
        r0 = 0;
        r1 = 1;
    }
    t = arg0[r0][1];
    if (t < 0.0f) {
        t = -t;
    }
    u = arg0[r1][1];
    if (u < 0.0f) {
        u = -u;
    }
    if (u < t) {
        p = r0;
    } else {
        p = r1;
    }
    if (p == r0) {
        q = r1;
    } else {
        q = r0;
    }
    if (arg0[p][1] < 1e-8 && arg0[p][1] > -1e-8) {
        return 0;
    }
    t = 1.0 / arg0[p][1];
    arg0[p][1] = 1.0f;
    arg0[p][2] *= t;
    arg1[p][p] = t;
    arg1[p][arg2] *= t;
    for (j = 0; j < 3; j++) {
        if (j != p) {
            t = arg0[j][1];
            arg0[j][1] = 0.0f;
            t = -t;
            arg0[j][2] += t * arg0[p][2];
            arg1[j][p] = arg1[p][p] * t;
            arg1[j][arg2] += t * arg1[p][arg2];
        }
    }
    if (arg0[q][2] < 1e-8 && arg0[q][2] > -1e-8) {
        return 0;
    }
    t = 1.0 / arg0[q][2];
    arg0[q][2] = 1.0f;
    arg1[q][q] = t;
    arg1[q][arg2] *= t;
    arg1[q][p] *= t;
    for (j = 0; j < 3; j++) {
        if (j != q) {
            t = arg0[j][2];
            arg0[j][2] = 0.0f;
            t = -t;
            arg1[j][arg2] += t * arg1[q][arg2];
            arg1[j][p] += t * arg1[q][p];
            arg1[j][q] += t * arg1[q][q];
        }
    }
    func_8062F538(arg1, arg2, p, q);
    return 1;
}


s32 func_8062F998(f32 (*arg0)[3], f32 (*arg1)[3]) {
    s32 p;
    s32 j;
    f32 t;
    f32 u;
    f32 v;

    arg1[2][2] = 1.0f;
    arg1[2][1] = 0.0f;
    arg1[2][0] = 0.0f;
    arg1[1][2] = 0.0f;
    arg1[1][1] = 1.0f;
    arg1[1][0] = 0.0f;
    arg1[0][2] = 0.0f;
    arg1[0][1] = 0.0f;
    arg1[0][0] = 1.0f;
    t = arg0[0][0];
    if (t < 0.0f) {
        t = -t;
    }
    u = arg0[1][0];
    if (u < 0.0f) {
        u = -u;
    }
    v = arg0[2][0];
    if (v < 0.0f) {
        v = -v;
    }
    if (u < t) {
        if (v < t) {
            p = 0;
        } else {
            p = 2;
        }
    } else {
        if (v < u) {
            p = 1;
        } else {
            p = 2;
        }
    }
    if (arg0[p][0] < 1e-8 && arg0[p][0] > -1e-8) {
        return 0;
    }
    v = 1.0 / arg0[p][0];
    arg0[p][0] = 1.0f;
    arg0[p][1] *= v;
    arg0[p][2] *= v;
    arg1[p][p] = v;
    for (j = 0; j < 3; j++) {
        if (j != p) {
            v = arg0[j][0];
            arg0[j][0] = 0.0f;
            v = -v;
            arg0[j][1] += v * arg0[p][1];
            arg0[j][2] += v * arg0[p][2];
            arg1[j][p] = arg1[p][p] * v;
        }
    }
    if (func_8062F640(arg0, arg1, p) == 0) {
        return 0;
    }
    return 1;
}


s32 func_8062FBC8(f32 (*arg0)[4], f32 *arg1, f32 *arg2, s32 *arg3) {
    f32 max;
    f32 abs;
    s32 i;
    s32 j;
    f32 tmp;

    *arg3 = -1;
    abs = arg0[3][3] > 0.0f ? arg0[3][3] : -arg0[3][3];
    if (abs < 1e-8) {
        max = 0.0f;
        for (i = 0; i < 4; i++) {
            if (max < arg0[i][3]) {
                *arg3 = i;
                max = arg0[i][3];
            } else if (arg0[i][3] < -max) {
                *arg3 = i;
                max = -arg0[i][3];
            }
        }
        if (*arg3 < 0) {
            return 0;
        }
        for (j = 0; j < 4; j++) {
            tmp = arg0[3][j];
            arg0[3][j] = arg0[*arg3][j];
            arg0[*arg3][j] = tmp;
        }
    }
    arg1[0] = -arg0[0][3];
    arg1[1] = -arg0[1][3];
    arg1[2] = -arg0[2][3];
    *arg2 = 1.0 / arg0[3][3];
    arg0[0][3] = 0.0f;
    arg0[1][3] = 0.0f;
    arg0[2][3] = 0.0f;
    arg0[3][3] = 1.0f;
    arg0[3][0] *= *arg2;
    arg0[3][1] *= *arg2;
    arg0[3][2] *= *arg2;
    for (i = 0; i < 3; i++) {
        arg0[0][i] += arg1[0] * arg0[3][i];
        arg0[1][i] += arg1[1] * arg0[3][i];
        arg0[2][i] += arg1[2] * arg0[3][i];
    }
    return 1;
}


s32 func_8062FF10(f32 (*arg0)[4], f32 (*arg1)[4]) {
    f32 m[4][4];
    f32 n[4][3];
    f32 inv[3][3];
    f32 scale;
    s32 i;
    s32 k;
    f32 w[3];
    f32 tmp;
    f32 v[3];
    s32 idx;
    s32 flag;

    for (i = 0; i < 4; i++) {
        for (k = 0; k < 4; k++) {
            m[i][k] = arg1[i][k];
            arg0[i][k] = 0.0f;
        }
    }
    arg0[0][0] = 1.0f;
    arg0[1][1] = 1.0f;
    arg0[2][2] = 1.0f;
    arg0[3][3] = 1.0f;
    flag = m[0][3] == 0.0; if (flag) { flag = m[1][3] == 0.0;
        if (flag) {
            flag = m[2][3] == 0.0;
            if (flag) {
                flag = m[3][3] == 1.0;
            }
        }
    }
    if (!flag) {
        if (!func_8062FBC8(m, w, &scale, &idx)) {
            return 0;
        }
    }
    v[0] = m[3][0];
    v[1] = m[3][1];
    v[2] = m[3][2];
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            n[i][k] = m[i][k];
        }
    }
    if (!func_8062F998(n, inv)) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            arg0[i][k] = inv[i][k];
        }
    }
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            arg0[3][i] -= v[k] * inv[k][i];
        }
    }
    if (!flag) {
        for (i = 0; i < 4; i++) {
            arg0[i][3] += w[0] * arg0[i][0] + w[1] * arg0[i][1] + w[2] * arg0[i][2];
            arg0[i][3] *= scale;
        }
        if (idx >= 0) {
            for (i = 0; i < 4; i++) {
                tmp = arg0[i][3];
                arg0[i][3] = arg0[i][idx];
                arg0[i][idx] = tmp;
            }
        }
    }
    return 1;
}


