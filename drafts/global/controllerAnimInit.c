// controllerAnimInit (src/global/17B90.c): stage 5: score 65 (improved from 245); anim->unk80 = 0.0 double literal matched delay-slot unk80 vs unk48 store scheduling; remaining 12 insns diff is t6/t7 regalloc swap
#include "common.h"

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[4];
    s16 unk10;
    u8 pad12[2];
    f32 unk14;
    f32 unk18;
    u16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} AnimSlotInit;

typedef struct {
    AnimSlotInit *unk0;
    AnimSlotInit *unk4;
    AnimSlotInit *unk8;
    AnimSlotInit *unkC;
    f32 unk10;
    Mtx *unk14;
    Mtx *unk18;
    void *unk1C;
    void *unk20;
    void *unk24;
    u8 pad28[0xC];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    u8 pad40[4];
    f32 unk44;
    f32 unk48;
    u8 pad4C[0xC];
    f32 unk58;
    u8 pad5C[8];
    s16 unk64;
    u8 pad66[2];
    s32 unk68;
    u8 pad6C[4];
    s32 unk70;
    u8 pad74[4];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s32 unk88;
} AnimStateInit;

typedef struct {
    void *unk0;
    AnimStateInit *unk4;
    u8 pad8[4];
    f32 unkC[4][4];
    s32 unk4C;
    s32 unk50;
} AnimControllerInit;

typedef struct {
    u8 pad[0x20];
    u8 unk20;
} CtrlB_Asset;

void *func_80612E90(void *, s32, s32);
void *heapAlloc(s32);
void guMtxIdent(Mtx *);
void guMtxIdentF(float mf[4][4]);

s32 controllerAnimInit(AnimControllerInit *arg0, u16 arg1) {
    CtrlB_Asset *resource;
    s32 i;
    void *alloc;
    AnimStateInit *anim;

    resource = (CtrlB_Asset *)func_80612E90(arg0, arg1, 0);
    if (resource != NULL) {
        arg0->unk0 = resource;
        arg0->unk4C = 0;
        arg0->unk50 = 0;

        alloc = heapAlloc((resource->unk20 << 7) + 0x170);
        arg0->unk4 = (AnimStateInit *)alloc;
        arg0->unk4->unk0 = (AnimSlotInit *)((u8 *)alloc + 0x90);
        arg0->unk4->unk4 = (AnimSlotInit *)((u8 *)alloc + 0xC8);
        arg0->unk4->unk8 = (AnimSlotInit *)((u8 *)alloc + 0x100);
        arg0->unk4->unkC = (AnimSlotInit *)((u8 *)alloc + 0x138);
        arg0->unk4->unk14 = (Mtx *)((u8 *)alloc + 0x170);
        arg0->unk4->unk18 = (Mtx *)((resource->unk20 << 6) + (u8 *)arg0->unk4->unk14);

        for (i = 0; i < resource->unk20; i++) {
            guMtxIdent((Mtx *)((u8 *)arg0->unk4->unk14 + (i << 6)));
            guMtxIdent((Mtx *)((u8 *)arg0->unk4->unk18 + (i << 6)));
        }

        guMtxIdentF(arg0->unkC);
        anim = arg0->unk4;
        anim->unk1C = NULL;
        anim->unk20 = NULL;
        anim->unk24 = NULL;
        anim->unk34 = 0.15f;
        anim->unk38 = 0.15f;
        anim->unk3C = 0.15f;

        anim->unk0->unk4 = 0.0f;
        anim->unk0->unk8 = 0.0f;
        anim->unk0->unk0 = NULL;
        anim->unk0->unk10 = -1;
        anim->unk0->unk1C = 0;
        anim->unk0->unk14 = 0.0f;
        anim->unk0->unk18 = 0.0f;
        anim->unk0->unk24 = 1.0f;
        anim->unk0->unk34 = 0.0f;

        anim->unk4->unk0 = NULL;
        anim->unk4->unk34 = 0.0f;
        anim->unk8->unk0 = NULL;
        anim->unk8->unk34 = 0.0f;
        anim->unkC->unk0 = NULL;
        anim->unkC->unk34 = 0.0f;

        anim->unk68 = 0;
        anim->unk64 = 0;
        anim->unk70 = 0;
        anim->unk78 = 0;
        anim->unk7C = 0;
        anim->unk84 = 0;
        anim->unk88 = 0;

        anim->unk10 = 0.0f;
        anim->unk44 = 0.0f;
        anim->unk58 = 0.0f;
        anim->unk48 = 1.0f;
        anim->unk80 = 0.0;

        return 1;
    }
    return 0;
}
