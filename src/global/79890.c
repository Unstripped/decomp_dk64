#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80674B90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80674E14.s")

typedef struct Beh7982_80675180_0 {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
} Beh7982_80675180_0;

typedef struct Beh7982_80675180_4 {
    u8 pad0[0x20];
    s32 unk20;
} Beh7982_80675180_4;

extern u8 D_807444FC;
void matrix4Invert(float [4][4], float [4][4]);

void func_80675180(Beh7982_80675180_0 *arg0, f32 arg1, f32 arg2, f32 arg3, Beh7982_80675180_4 *arg4, f32 *arg5, f32 *arg6, f32 *arg7) {
    float sp70[4][4];
    float sp30[4][4];
    u32 temp_v0;
    Mtx *mtx;

    mtx = arg0->unk74[D_807444FC];
    temp_v0 = arg4->unk20;
    if (temp_v0 == -1) {
        memcpy(sp70, arg0->unk70, sizeof(sp70));
    } else {
        guMtxL2F(sp70, (Mtx *)(((temp_v0 >> 6) << 6) + (u8 *)mtx));
    }
    matrix4Invert(sp30, sp70);
    guMtxXFMF(sp30, arg1, arg2, arg3, arg5, arg6, arg7);
}

f32 func_80675234(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;

    temp_fv0 = (f32) (arg0 - arg3);
    temp_fv1 = (f32) (arg1 - arg4);
    temp_fa1 = (f32) (arg2 - arg5);
    temp_fv1_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)) - (f32) arg6;
    var_fa0 = temp_fv1_2;
    if ((f64) temp_fv1_2 < 0.0) {
        var_fa0 = 0.0f;
    }
    return var_fa0 / (f32)8;
}

typedef struct Beh798_Node {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    struct Beh798_Node *next;
} Beh798_Node;

void *heapAlloc(s32);
extern Beh798_Node *D_807FB620;
extern Beh798_Node *D_807FB624;
extern s32 D_807FB628;

void func_806752D4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    Beh798_Node *temp_v0;

    temp_v0 = heapAlloc(sizeof(Beh798_Node));
    temp_v0->unk0 = arg1;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = arg4;
    temp_v0->unk10 = arg5;
    temp_v0->unk14 = arg6;
    temp_v0->unk18 = arg0;
    temp_v0->next = NULL;
    if (D_807FB620 != NULL) {
        D_807FB624->next = temp_v0;
    } else {
        D_807FB620 = temp_v0;
    }
    D_807FB624 = temp_v0;
    D_807FB628 += 1;
}

typedef struct Beh7982_Elem {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Beh7982_Elem;

void heapFree(void *);
void actorAppendCallback(void *, s32, s32, u8, s32, void *);

void func_80675380(s32 arg0, void *arg1) {
    Beh7982_Elem *arr;
    s32 i;
    Beh798_Node *node;
    Beh798_Node *next;

    arr = heapAlloc(D_807FB628 * sizeof(Beh7982_Elem));
    node = D_807FB620;
    for (i = 0; i < D_807FB628; i++) {
        arr[i].unk0 = node->unk0;
        arr[i].unk4 = node->unk4;
        arr[i].unk8 = node->unk8;
        arr[i].unkC = node->unkC;
        arr[i].unk10 = node->unk10;
        arr[i].unk14 = node->unk14;
        arr[i].unk18 = node->unk18;
        next = node->next;
        heapFree(node);
        node = next;
    }
    actorAppendCallback(arg1, arg0, 0x8000, 0, D_807FB628, arr);
}

typedef struct Beh7982_Node28 {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x4];
    struct Beh7982_Node28 *next;
} Beh7982_Node28;

typedef struct Beh7982_Sub140 {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
    u8 pad7C[0x10];
    Beh7982_Node28 *unk8C;
} Beh7982_Sub140;

typedef struct Beh7982_Arg0_5478 {
    u8 pad0[0x140];
    Beh7982_Sub140 *unk140;
} Beh7982_Arg0_5478;

typedef struct Beh7982_Arg1_5478 {
    u8 pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x4];
    s32 unk14;
} Beh7982_Arg1_5478;

void func_80675478(Beh7982_Arg0_5478 *arg0, Beh7982_Arg1_5478 *arg1, f32 *arg2, f32 *arg3) {
    s32 i;
    Beh7982_Node28 *node;
    Mtx *mtx;
    float sp4C[4][4];
    u32 temp_v1;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    node = arg0->unk140->unk8C;
    for (i = arg1->unk14 - 1; i != 0; i--) {
        node = node->next;
    }
    mtx = arg0->unk140->unk74[D_807444FC ^ 1];
    temp_v1 = node->unk20;
    if (temp_v1 == -1) {
        memcpy(sp4C, arg0->unk140->unk70, sizeof(sp4C));
        guMtxXFMF(sp4C, arg1->unk4, arg1->unk8, arg1->unkC, &sp44, &sp40, &sp3C);
    } else {
        guMtxXFML((Mtx *)(((temp_v1 >> 6) << 6) + (u8 *)mtx), arg1->unk4, arg1->unk8, arg1->unkC, &sp44, &sp40, &sp3C);
    }
    *arg2 = sp44;
    *arg3 = sp3C;
}

s32 func_80611E60(s32);
void func_806742C0(s16, s16, s32, s32);

void func_806755A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad1;
    s32 pad2;
    f32 dist;
    s16 angle;
    s32 dx;
    s32 dy;
    s32 abs_val;

    dx = arg2 - arg0;
    if (dx > 0) {
        abs_val = dx;
    } else {
        abs_val = -dx;
    }
    if (abs_val < 0x2711) {
        dy = arg3 - arg1;
        if (dy > 0) {
            abs_val = dy;
        } else {
            abs_val = -dy;
        }
        if (abs_val < 0x2711) {
            dist = sqrtf((f32)((dx * dx) + (dy * dy)));
            if ((f64)dist != 0.0) {
                if (dx >= 0 && dy >= 0) {
                    angle = (s16)(func_80611E60((s32)(((f64)dx * 65535.9) / (f64)dist)) >> 4);
                }
                if (dx >= 0 && dy < 0) {
                    angle = (s16)((func_80611E60((s32)(((f64)(arg1 - arg3) * 65535.9) / (f64)dist)) >> 4) + 0x400);
                }
                if (dx < 0 && dy < 0) {
                    angle = (s16)((func_80611E60((s32)(((f64)(arg0 - arg2) * 65535.9) / (f64)dist)) >> 4) + 0x800);
                }
                if (dx < 0 && dy >= 0) {
                    angle = (s16)((func_80611E60((s32)(((f64)dy * 65535.9) / (f64)dist)) >> 4) + 0xC00);
                }
                func_806742C0(angle + 0x400, angle - 0x400, arg4, arg5);
            }
        }
    }
}
