#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);
s32 func_8066B0F8(s32, s32, s32, s32);
extern u8 *D_807FC7C0;

#ifdef NON_MATCHING
typedef struct L97230_State {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
} L97230_State;

extern Gfx D_1000118;
extern Mtx D_2000000;
extern Mtx D_2000200;
extern Gfx D_80750280;
extern u8 D_807444FC;
extern u8 *D_807FC924;

void actorFreeModelNodeList(Actor *);
void func_8066EB40(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_80612C30(f32 (*)[4], f32);

#define L97230_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80697230(Gfx *arg0, Actor *arg1) {
    L97230_State *sub;
    f32 mtx2[4][4];
    f32 mtx1[4][4];
    s16 i;
    s16 sp110;
    f64 q0;
    f64 q1;
    f64 q2;
    f64 q3;
    f32 f;
    s32 idx;
    f32 spE4;
    f32 vx;
    f32 vz;
    f32 vy;
    f32 vscale;

    sub = arg1->unk174;
    sp110 = 0x1000 / sub->unk0;
    idx = (((sub->unk10++) % 16) + arg1->unk168) & 0xFF;

    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xDE000000; _g->words.w1 = (u32)(&D_1000118); } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xDA380007; _g->words.w1 = (u32)(&D_2000000); } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xDA380005; _g->words.w1 = (u32)(&D_2000200); } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xD7000002; _g->words.w1 = 0x80008000; } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xFC119623; _g->words.w1 = 0xFF2FFFFF; } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xE3001201; _g->words.w1 = 0x00002000; } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xD9FFFFFF; _g->words.w1 = 0x00000001; } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xE200001C; _g->words.w1 = 0x00504A50; } ;
    { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xFA000000; _g->words.w1 = 0xFFFFFFFF; } ;

    actorFreeModelNodeList(arg1);

    if (arg1->unk15F != 0) {
        switch (sub->unk11) {
        case 0:
            spE4 = (f32)(((f64)sub->unk8) * 10.0);
            break;
        case 1:
            spE4 = (f32)((((f64)sub->unk8) * 0.15) * 2048.0);
            break;
        }
        func_8066EB40(arg1, spE4);
    }

    i = 0;
    if (sub->unk0 > 0) {
        do {
            switch (sub->unk11) {
            case 0:
                vx = func_80612794(i * sp110) * sub->unk8;
                vy = func_80612790(i * sp110) * sub->unk8;
                vscale = 1.0f;
                vz = 0.0f;
                break;
            case 1:
                q0 = ((f64)((*((s16 *)(((u8 *)arg1) + 0xEE))) - arg1->unk15F)) * 0.05;
                q1 = (1.0 < q0) ? (1.0) : (q0);
                f = (f32)((q1 * 0.029) + 0.001);
                vscale = 130.0f * f;
                vz = 1500.0f * f;
                vx = func_80612794(arg1->unkE6 + 0x400) * ((f * sub->unk8) * ((f32)(0x800 - ((s16)(i * sp110)))));
                vy = func_80612790(arg1->unkE6 + 0x400) * ((f * sub->unk8) * ((f32)(0x800 - ((s16)(i * sp110)))));
                break;
            }
            if (arg1->unk15F != 0) {
                actorAppendModelNode(arg1, vx, vz, vy, (f32)(((f64)vscale) * 80.0), -1);
            }
            { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xFD180000; _g->words.w1 = ((s32 *)D_807FC7C0)[idx]; } ;
            { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xF5180000; _g->words.w1 = 0x07080200; } ;             { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xE6000000; _g->words.w1 = 0x00000000; } ;             { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xF3000000; _g->words.w1 = 0x073FF080; } ;             { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xE7000000; _g->words.w1 = 0x00000000; } ;             { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xF5181000; _g->words.w1 = 0x00080200; } ;             { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xF2000000; _g->words.w1 = 0x0007C07C; } ;

            guScaleF(mtx2, vscale, vscale, vscale);
            func_80612C30(mtx1, (f32)(((*((s16 *)(D_807FC924 + 0x2C8))) * 0x168) / 4096));
            guMtxCatF(mtx2, mtx1, mtx2);
            guTranslateF(mtx1, arg1->unk7C + vx, arg1->unk80, arg1->unk84 + vy);
            guMtxCatF(mtx2, mtx1, mtx2);
            guMtxF2L(mtx2, (Mtx *)(sub->unk4 + (((i * 2) + D_807444FC) << 6)));
            { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)(sub->unk4 + (((i * 2) + D_807444FC) << 6)); } ;
            { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0x01004008; _g->words.w1 = osVirtualToPhysical(&D_80750280); } ;
            { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0x06000204; _g->words.w1 = 0x00000406; } ;
            { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = 0xE7000000; _g->words.w1 = 0x00000000; } ;
            i++;
        } while (i < sub->unk0);
    }
    return arg0;
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9BF30/func_80697230.s")
#endif


void func_806978FC(void) {
    s16 i;
    s16 j;

    i = 0;
    D_807FC7C0 = func_80610FE8(0xC0);
    for (j = 0; j < 0x30; j++) {
        ((s32 *)D_807FC7C0)[i++] = func_8066B0F8(0x19, i + 0x1654, 1, 1);
    }
}

extern Actor *D_807FBB40;

#ifdef NON_MATCHING
typedef struct M9B_ActorState {
    s16 unk0;
    u8 pad2;
    u8 pad3;
    u8 *unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
} M9B_ActorState;

Gfx *func_80697230(Gfx *, Actor *);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void actorDespawn(Actor *);
void heapFree(void *);
void projectileSpawnActor107(u8, u8, f32, f32, u8, u8);
void renderCallbacksRegister(void *, void *, u8);

#define ACTOR2 ((Actor *)D_807FBB40)

void func_80697988(void) {
    M9B_ActorState *sub;
    Actor *actor;
    f64 temp;
    f64 max;

    sub = ACTOR2->unk174;
    if (!(ACTOR2->unk60 & 0x10)) {
        *(s16 *)((u8 *)ACTOR2 + 0xEE) = ACTOR2->unk15F;
        sub->unk4 = func_80610FE8(0x1000);
        if (ACTOR2->unk15F != 0) {
            ACTOR2->unk144 = 0x24;
        }
        if (sub->unk11 == 1) {
            sfxPlayActorSound(ACTOR2, 0x128, 1, 1, 0, 0xFF, 0.2f, 0);
            sfxPlayActorSound(ACTOR2, 0x139, 0x3C, 1, 1, 0xFF, 1.0f, 0);
        }
    }
    if (sub->unk11 != 0) {
        if (sub->unk11 == 1) {
            ACTOR2->unk7C += sub->unkC * func_80612794(ACTOR2->unkE6);
            ACTOR2->unk84 += sub->unkC * func_80612790(ACTOR2->unkE6);
            actor = D_807FBB40;
            if (actor->unk15F != 0) {
                actor->unk15F -= 1;
            } else if (actor->unk168 == 0x20) {
                actor->unk168 = 0x10;
                sub->unk10 = 0;
            } else if (sub->unk10 >= 0x10) {
                heapFree(sub->unk4);
                actorDespawn(actor);
            }
        }
    } else {
        if (ACTOR2->unk15F != 0) {
            sub->unk8 += sub->unkC;
            temp = (f64)sub->unk8 * 0.3;
            max = 32.0;
            if (temp > 32.0) {
                sub->unk0 = max;
            } else {
                sub->unk0 = temp;
            }
        } else {
            sub->unk8 = sub->unk8 + (f32)((ACTOR2->unk168 - sub->unk10) + 0x10)
                * (sub->unkC * 0.0625);
        }
        if ((sub->unk10 - ACTOR2->unk168) >= 0x10) {
            u8 count;

            count = ACTOR2->unk15F;
            ACTOR2->unk15F = count - 1;
            if (count) {
                projectileSpawnActor107(0, sub->unk0, sub->unk8, sub->unkC, 0, 0x10);
                if (ACTOR2->unk15F == 0) {
                    ACTOR2->unk168 = 0x10;
                } else {
                    sub->unk10 = 0;
                }
            } else {
                heapFree(sub->unk4);
                actorDespawn(ACTOR2);
            }
        }
    }
    renderCallbacksRegister(func_80697230, ACTOR2, 1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/9BF30/func_80697988.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/9BF30/func_80697CEC.s")
