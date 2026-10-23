// func_8065D254 (src/global/61AA0.c): diff 2987 (461 insns): full logic and types recovered, cache search/alloc + display list vertex/matrix generation; remaining diffs in loop 2 induction/branch delay slot scheduling, spill slots and regalloc in double trig math
#include "common.h"
#include "actor.h"

typedef struct {
    Mtx matrices[2];
    Vtx verts[2][4];
    s16 unk100;
    u8 unk102;
    s8 unk103;
    s8 unk104;
    u8 unk105;
    u8 unk106;
    s8 unk107;
} Struct807F7F10;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    void *unk8;
} Struct807F8E90;

typedef f32 MtxF[4][4];

extern u8 D_807444FC;
extern s32 D_8076A064;
extern Struct807F7F10 D_807F7F10[16];
extern u8 D_807F8E88;
extern s16 D_807F8E8A;
extern Struct807F8E90 D_807F8E90[4];

void *func_8066B0F8(s32, s32, s32, s32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_8065D964(s16 *, s16, s16, s16, s16);

void func_8065D254(Actor *actor, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6, s16 arg7, u8 arg8, s16 arg9, f32 arg10) {
    s32 i;
    s32 found;
    f32 scale;
    MtxF sp8C;
    MtxF sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    found = FALSE;
    i = 0;
    if (D_807F8E88 == 15) {
        D_807F8E8A = 0;
        return;
    }
    if ((actor->unkA4 > 32767.0f) || (actor->unkA4 < -32768.0f)) {
        D_807F8E8A = 0;
        return;
    }

    do {
        if ((D_807F8E90[i].unk0 != -1) && (arg1 == D_807F8E90[i].unk4)) {
            found = TRUE;
        } else {
            i++;
        }
    } while ((i < 4) && !found);

    if (found) {
        goto block_21;
    }
    for (i = 0, found = FALSE; (i < 4) && !found; ) {
        if (D_807F8E90[i].unk0 == -1) {
            found = TRUE;
        } else {
            i++;
        }
    }

    if (!found) {
        return;
    }
    D_807F8E90[i].unk8 = func_8066B0F8(7, arg1, 0, 0);
    D_807F8E90[i].unk4 = arg1;

block_21:
    D_807F8E90[i].unk0 = D_8076A064;
    D_807F7F10[D_807F8E88].unk102 = i;
    D_807F7F10[D_807F8E88].unk106 = arg8;
    if (actor->unk64 & 0x40) {
        D_807F8E8A |= 1;
    }
    D_807F7F10[D_807F8E88].unk100 = D_807F8E8A;
    D_807F7F10[D_807F8E88].unk107 = *(s16 *)&actor->unk12C[0];

    func_8065D964(D_807F7F10[D_807F8E88].verts[D_807444FC][0], (s16)-((f32)arg4 * arg10), -arg5, 0, 0);
    func_8065D964(D_807F7F10[D_807F8E88].verts[D_807444FC][1], arg4, -arg5, arg2 - 1, 0);
    func_8065D964(D_807F7F10[D_807F8E88].verts[D_807444FC][2], (s16)-((f32)arg4 * arg10), arg5, 0, arg3 - 1);
    func_8065D964(D_807F7F10[D_807F8E88].verts[D_807444FC][3], arg4, arg5, arg2 - 1, arg3 - 1);

    sp48 = actor->unkA4;
    scale = (f32)arg7;
    if (actor->unkF6 == 1) {
        f32 diff1 = (actor->unkAC > actor->unk80) ? (actor->unkAC - actor->unk80) : -(actor->unkAC - actor->unk80);
        f32 diff2 = (actor->unkB0 > actor->unk84) ? (actor->unkB0 - actor->unk84) : -(actor->unkB0 - actor->unk84);
        if (diff1 < diff2) {
            scale = (f32)arg7 - actor->unk80;
        } else {
            scale = (f32)arg7 - actor->unk84;
        }
    }
    if (scale <= 0.0f) {
        scale = 0.0f;
    }
    guScaleF(sp8C, scale, scale, scale);

    if (actor->unk60 & 1) {
        guRotateF(sp4C, (f32)(((s32)arg9 * 360) / 4095), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp8C, sp4C, sp8C);
    }
    if ((D_807F8E8A & 2) && (actor->unk6A & 2)) {
        if (actor->unkD8 != 0) {
            guRotateF(sp4C, (f32)-(((f64)*(s16 *)&actor->unkC0[0x18] / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(sp8C, sp4C, sp8C);
        }
        if (actor->unkDA != 0) {
            guRotateF(sp4C, (f32)(((f64)*(s16 *)&actor->unkC0[0x1A] / 4095.0) * 90.0), 1.0f, 0.0f, 0.0f);
            guMtxCatF(sp8C, sp4C, sp8C);
        }
    }
    if (actor->unk60 & 2) {
        if (*(s16 *)&actor->unkC0[0x1A] < 1000) {
            guRotateF(sp4C, (f32)(((f64)*(s16 *)&actor->unkC0[0x18] / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(sp8C, sp4C, sp8C);
        }
    }

    if (actor->unkC0[0x0C] != 0) {
        actorGetNodePos(actor, actor->unkC0[0x0C], &sp44, &sp40, &sp3C);
        guTranslateF(sp4C, sp44, actor->unkA4, sp3C);
    } else {
        guTranslateF(sp4C, actor->unk7C, sp48, actor->unk84);
    }
    guMtxCatF(sp8C, sp4C, sp8C);

    guMtxF2L(sp8C, &D_807F7F10[D_807F8E88].matrices[D_807444FC]);

    D_807F7F10[D_807F8E88].unk103 = arg2;
    D_807F7F10[D_807F8E88].unk104 = arg3;
    D_807F7F10[D_807F8E88].unk105 = arg6;
    D_807F8E88++;
    D_807F8E8A = 0;
}
