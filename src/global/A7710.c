#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2A10.s")

void actorSetStateTwo(Actor *actor) {
    actor->unk154 = 2;
    actor->unk155[0] = 0;
    actor->unk128 = 0xFF;
}

void actorSetStateOne(Actor *actor) {
    if (actor != NULL) {
        actor->unk154 = 1;
        actor->unk155[0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2B38.s")

void actorSetStateThree(Actor *actor) {
    actor->unk154 = 3;
    actor->unk155[0] = 0;
}

typedef struct GfxResource {
    /* 0x0 */ u8 pad[4];
    /* 0x4 */ void *unk4;
} GfxResource;

typedef struct RenderActorSub {
    /* 0x00 */ u8 pad[0x10];
    /* 0x10 */ u8 unk10;
} RenderActorSub;

typedef struct RenderState {
    /* 0x276 */ u8 pad[0x276];
    /* 0x276 */ s16 unk276;
} RenderState;

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Gfx D_1000118;
extern Mtx D_2000180;
extern Gfx D_8071FC58;
extern RenderState *D_807FC924;
s32 func_805FCA64(void);
Gfx *func_8070068C(Gfx *);
GfxResource *gfxResourceFindById(u8);
Gfx *func_806FC530(Gfx *, s32, s16, s16, void *, s32);
Gfx *func_806FE078(Gfx *, u8, s32, f32, f32, f32, f32);
f32 func_80612D1C(f32);
f32 func_80612D10(f32);
void func_8071495C(void);
void func_80714CC0(void *, f32, f32, f32, f32);

Gfx *renderActorSpriteCallback(Gfx *gfx, Actor *actor) {
    RenderActorSub *sub;
    /* unused: the original function reserves 0x18 and 8 bytes of its frame here */
    u8 stackPad0[0x18];
    f32 angle;
    u8 stackPad1[8];
    f32 sinAngle;
    s32 unk15F;
    s32 offset;

    sub = actor->unk174;
    if (func_805FCA64() != 0) {
        WRITE_GFX(gfx++, 0xDE000000, (u32)&D_1000118);
        WRITE_GFX(gfx++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(gfx++, 0xFA000000, (actor->unk128 & 0xFF) | 0xFFFFFF00);
        WRITE_GFX(gfx++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(gfx++, 0xE200001C, 0x00504240);
        unk15F = actor->unk15F;
        if (unk15F == 0xB) {
            gfx = func_8070068C(gfx);
            gfx = func_806FC530(gfx, 0x86, (s16)(s32)(actor->unk7C * 4.0f),
                                (s16)((D_807FC924->unk276 * 4) - 0x3C),
                                gfxResourceFindById(sub->unk10)->unk4, 1);
        } else {
            angle = (f32)(6.28318548202514648 - 2.0 * *(f64 *)actor->unk160);
            offset = 8;
            if (actor->unk168 == 3) {
                offset = -7;
            }
            gfx = func_806FE078(gfx, sub->unk10, unk15F, actor->unk7C + (f32)offset,
                                actor->unk80 + 5.0f, 0.0f, 1.0f);
            if (actor->unk154 == 2) {
                gfx = func_8070068C(gfx);
                func_8071495C();
                sinAngle = func_80612D1C(angle);
                func_80714CC0(&D_8071FC58, 0.5f,
                              (f32)((f64)sinAngle * 40.0 + (f64)(40.0f + actor->unk7C)),
                              (f32)((f64)func_80612D10(angle) * 25.0 + (f64)actor->unk80),
                              0.0f);
            }
        }
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2E30.s")
