// func_8065D254 (src/global/61AA0.c): stage 5, parked NON_MATCHING in 61AA0.c: text identical except one insn: loop-2 preheader li a0,-1 is last (before lw) instead of first (bnez delay slot); mask/i*1 FAKE nodes used; D_807F8E8A should be u16 (lhu), cast used
#include "common.h"
#include "actor.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    void *unk8;
} BillboardCacheEntry;
extern BillboardCacheEntry D_807F8E90[4];
extern s16 D_807F8E8A;

typedef struct {
    Mtx matrices[2];
    Vtx verts[2][4];
    u16 unk100;
    u8 unk102;
    u8 unk103;
    u8 unk104;
    u8 unk105;
    u8 unk106;
    s8 unk107;
} RenderLBillboard;
extern RenderLBillboard D_807F7F10[16];
extern u8 D_807F8E88;
extern u8 D_807444FC;

void billboardSetVertex(s16 *, s16, s16, s16, s16);
void *assetLoad(s32, s32, s32, s32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
extern s32 D_8076A064;
#define RL_ACT(T, off) (*(T *)((u8 *)actor + (off)))

void func_8065D254(Actor *actor, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6, s16 arg7, u8 arg8, s16 arg9, f32 arg10) {
    s32 found;
    s32 i;
    f32 scale;
    f32 sp8C[4][4];
    f32 sp4C[4][4];
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
    i = 0; found = FALSE;
    while ((i < 4) && !found) {
        if ((D_807F8E90[i].unk0 & 0xFFFFFFFF) == -1) { // FAKE: no-op mask gives this -1 its own constant candidate
            found = TRUE;
        } else {
            i++;
        }
    }

    if (!found) {
        return;
    }
    D_807F8E90[i].unk8 = assetLoad(7, arg1, 0, 0);
    D_807F8E90[i].unk4 = arg1;

block_21:
    D_807F8E90[i * 1].unk0 = D_8076A064; // FAKE: no-op index multiply keeps this address from being CSEd with the loop IV
    D_807F7F10[D_807F8E88].unk102 = i;
    D_807F7F10[D_807F8E88].unk106 = arg8;
    if (actor->unk64 & 0x40) {
        *(u16 *)&D_807F8E8A |= 1;
    }
    D_807F7F10[D_807F8E88].unk100 = *(u16 *)&D_807F8E8A;
    D_807F7F10[D_807F8E88].unk107 = RL_ACT(s16, 0x12C);

    billboardSetVertex((s16 *)&D_807F7F10[D_807F8E88].verts[D_807444FC][0], (s16)-((f32)arg4 * arg10), -arg5, 0, 0);
    billboardSetVertex((s16 *)&D_807F7F10[D_807F8E88].verts[D_807444FC][1], arg4, -arg5, arg2 - 1, 0);
    billboardSetVertex((s16 *)&D_807F7F10[D_807F8E88].verts[D_807444FC][2], (s16)-((f32)arg4 * arg10), arg5, 0, arg3 - 1);
    billboardSetVertex((s16 *)&D_807F7F10[D_807F8E88].verts[D_807444FC][3], arg4, arg5, arg2 - 1, arg3 - 1);

    sp48 = actor->unkA4;
    if ((*(u16 *)&D_807F8E8A & 2) && (actor->unk6A & 2) && (actor->unkAC <= actor->unk80)) {
        f32 diff1 = (actor->unk80 > actor->unkAC) ? (actor->unk80 - actor->unkAC) : -(actor->unk80 - actor->unkAC);
        f32 diff2 = (actor->unk80 > actor->unkA4) ? (actor->unk80 - actor->unkA4) : -(actor->unk80 - actor->unkA4);
        if (diff1 < diff2) {
            sp48 = actor->unkAC;
        }
    }
    scale = 1.0 - (f64)((actor->unk80 - sp48) / (f32)arg7);
    if (scale < 0.0) {
        scale = 0.0f;
    }
    guScaleF(sp8C, scale, scale, scale);

    guRotateF(sp4C, (f32)((arg9 * 360) / 4095), 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp8C, sp4C, sp8C);
    if (actor->unk60 & 2) {
        if (RL_ACT(s16, 0xDA) < 1000) {
            guRotateF(sp4C, -((f64)RL_ACT(s16, 0xD8) / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(sp8C, sp4C, sp8C);
        }
        guRotateF(sp4C, 90.0 - (f64)RL_ACT(s16, 0xDA) / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(sp8C, sp4C, sp8C);
        if (RL_ACT(s16, 0xDA) < 1000) {
            guRotateF(sp4C, (f64)RL_ACT(s16, 0xD8) / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
            guMtxCatF(sp8C, sp4C, sp8C);
        }
    }

    if (RL_ACT(u8, 0xCC)) {
        actorGetNodePos(actor, RL_ACT(u8, 0xCC), &sp44, &sp40, &sp3C);
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
