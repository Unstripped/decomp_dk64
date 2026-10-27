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

void func_8062FF10(f32 (*)[4], f32 (*)[4]);

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062DB70.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E040.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E67C.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EE48.s")


s32 mapChunkIsVisible(u8);
void assetFreeBuffer(s32, s32, s32);

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F050.s")

void func_8062F318(void) {
    D_807F5FED = 1;
}

#ifdef NON_MATCHING
extern s32 D_807F5FD0;
extern s32 *D_807F5FD4;

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

extern s32 D_807F5FC8;
extern s32 D_807F5FCC;

s32 func_8062F388(s32 *arg0) {
    *arg0 = D_807F5FCC;
    return D_807F5FC8;
}

#ifdef NON_MATCHING
s32 func_8066B0F8(s32, s32, s32, s32);

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F538.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F640.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F998.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062FBC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062FF10.s")
