// func_8067A1DC (src/global/7CA80.c): stage 5: frame 0x70, regs, stack slots all match; only diff: loop 2 (unk39) guard lbu->v1 + move v0,v1 in target vs mine lbu v0 directly (12 lines incl. branch offsets). for(i=0;..) loops with array indexing, pad60 local (FAKE)
#include "common.h"
#include "actor.h"

extern ActorGlobalState D_807FBB70;
void func_8067A69C(s32, Actor *, f32, f32, u8, u8);
void func_8067A70C(s32, Actor *, f32, f32, f32, u8, u8);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);

extern s32 D_807FBC08;
extern s32 D_807FBC14;
extern u8 D_807FBC68[][0x40];
extern u8 D_807FBC74[][0x40];

typedef struct Ac7B_Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Ac7B_Vec3;

typedef struct Ac7B_Slot {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    u8 pad10[0x30];
} Ac7B_Slot;

typedef struct Ac7B_GlobalState {
    u8 pad0[0x3C];
    Ac7B_Vec3 unk3C[4];
    s32 unk6C[4];
    s32 unk7C[4];
    u8 unk8C[4];
    u8 unk90;
    u8 unk91;
    u8 pad92[0x36];
    s32 unkC8;
    s32 unkCC;
    s32 unkD0;
    s32 unkD4;
    u8 padD8[0x50];
    Ac7B_Slot unk128[1];
} Ac7B_GlobalState;

#define Ac7B_GLOBAL ((Ac7B_GlobalState *)&D_807FBB70)

s32 func_80674B90(Actor *, s32, f32 *, f32 *);
void collisionTransformPointByActorMtx(Actor *, u32, f32 *, f32, f32 *);
void func_806776A0(Actor *, s32, void *, void *, s32, s32, s32, s32);
void func_806CF42C(Actor *);

void func_8067A1DC(Actor *arg0) {
    s32 i;
    f32 sp68;
    f32 sp64;
    s32 pad60; // FAKE: unused local reproducing the frame slot between sp64 and sp5C
    f32 sp5C;
    f32 sp58;

    for (i = 0; i < D_807FBB70.unk201; i++) {
        switch (D_807FBB70.unk244[i]) {
        case 0:
            break;
        case 1:
            if (func_80674B90(arg0, D_807FBB70.unk204[i], &sp68, &sp64) != 0) {
                func_8067A69C((s32)arg0, (Actor *)D_807FBB70.unk204[i], sp68, sp64, 0, 1);
            }
            break;
        case 2:
            func_80674B90(arg0, D_807FBB70.unk204[i], &sp5C, &sp58);
            break;
        case 4:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 1, 0, 0);
            break;
        case 3:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 0, 0, 0);
            break;
        case 8:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 2, 0, 0);
            break;
        case 10:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 3, 0, 0);
            break;
        case 13:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 6, 0, 0);
            break;
        case 11:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 4, 0, 0);
            break;
        case 12:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 5, 0, 0);
            break;
        case 6:
        case 7:
            if (D_807FBB70.unk244[i] == 6) {
                actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x40, 0, 0, 0);
            }
            func_8067A70C((s32)arg0, (Actor *)D_807FBB70.unk204[i], arg0->unk7C, arg0->unk80, arg0->unk84, 2, 1);
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x80, 0, 0, 0);
            func_806CF42C(arg0);
            break;
        case 5:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 8, 0, 0, 0);
            break;
        case 15:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 4, 0, 0, 0);
            break;
        case 9:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x1000, 0, 0, 0);
            break;
        case 14:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x02000000, 0, 0, 0);
            break;
        }
    }

    if (D_807FBB70.unk39 != 0) {
        for (i = 0; i < D_807FBB70.unk39; i++) {
            if (Ac7B_GLOBAL->unk8C[i] == 0) {
                collisionTransformPointByActorMtx(arg0, Ac7B_GLOBAL->unk6C[i], &Ac7B_GLOBAL->unk3C[i].x, Ac7B_GLOBAL->unk3C[i].y, &Ac7B_GLOBAL->unk3C[i].z);
                func_8067A69C((s32)arg0, (Actor *)Ac7B_GLOBAL->unk7C[i], Ac7B_GLOBAL->unk3C[i].x, Ac7B_GLOBAL->unk3C[i].z, 1, 1);
            }
        }
    }

    if (D_807FBB70.unk91 != 0) {
        func_806776A0(arg0, Ac7B_GLOBAL->unkCC, &D_807FBC08, &D_807FBC14, Ac7B_GLOBAL->unkC8, Ac7B_GLOBAL->unkD0, Ac7B_GLOBAL->unkD4, 1);
    }

    for (i = 0; i < D_807FBB70.unk1F8; i++) {
        func_806776A0(arg0, Ac7B_GLOBAL->unk128[i].unkC, D_807FBC68[i], D_807FBC74[i], Ac7B_GLOBAL->unk128[i].unk0, Ac7B_GLOBAL->unk128[i].unk4, Ac7B_GLOBAL->unk128[i].unk8, 0);
    }
}
