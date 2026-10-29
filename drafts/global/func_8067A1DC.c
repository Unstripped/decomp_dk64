// func_8067A1DC (src/global/7CA80.c): from .scratch/R3C/func_8067A1DC_best.c
#include "common.h"
#include "actor.h"

extern ActorGlobalState D_807FBB70;
extern s32 D_807FBC08;
extern s32 D_807FBC14;
extern s32 D_807FBC68;
extern s32 D_807FBC74;

typedef struct R3C_GlobalState {
    u8 pad0[0x3C];
    s32 unk3C[4][3];
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
    u8 padD8[0x24];
    f32 unkFC[3];
    f32 unk108[3];
    u8 pad114[0x14];
    s32 unk128;
    s32 unk12C;
    s32 unk130;
    s32 unk134;
} R3C_GlobalState;

#define GLOBAL ((R3C_GlobalState *)&D_807FBB70)

s32 func_80674B90(Actor *, s32, s32 *, s32 *);
void func_8067A69C(Actor *, s32, s32, s32, s32, s32);
void func_80679200(Actor *, s32, s32, u8, s32, void *);
void func_8067A70C(Actor *, s32, f32, f32, f32, u8, u8);
void func_806CF42C(Actor *);
void collisionTransformPointByActorMtx(Actor *, s32, void *, s32, void *);
void func_806776A0(Actor *, s32, void *, void *, s32, s32, s32, s32);

void func_8067A1DC(Actor *arg0) {
    s32 sp68;
    s32 sp64;
    s32 sp5C;
    s32 sp58;
    u8 *var_s0;
    u8 *var_s1;
    s32 i;
    u8 *var_s3;

    i = 0;
    if (D_807FBB70.unk201 > 0) {
        do {
            switch (D_807FBB70.unk244[i]) {
            case 0:
                break;
            case 1:
                if (func_80674B90(arg0, D_807FBB70.unk204[i], &sp68, &sp64) != 0) {
                    func_8067A69C(arg0, D_807FBB70.unk204[i], sp68, sp64, 0, 1);
                }
                break;
            case 2:
                func_80674B90(arg0, D_807FBB70.unk204[i], &sp5C, &sp58);
                break;
            case 4:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 1, 0, 0);
                break;
            case 3:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 0, 0, 0);
                break;
            case 8:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 2, 0, 0);
                break;
            case 10:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 3, 0, 0);
                break;
            case 13:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 6, 0, 0);
                break;
            case 11:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 4, 0, 0);
                break;
            case 12:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 5, 0, 0);
                break;
            case 6:
            case 7:
                if (D_807FBB70.unk244[i] == 6) {
                    func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x40, 0, 0, 0);
                }
                func_8067A70C(arg0, D_807FBB70.unk204[i], arg0->unk7C, arg0->unk80, arg0->unk84, 2, 1);
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x80, 0, 0, 0);
                func_806CF42C(arg0);
                break;
            case 5:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 8, 0, 0, 0);
                break;
            case 15:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 4, 0, 0, 0);
                break;
            case 9:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x1000, 0, 0, 0);
                break;
            case 14:
                func_80679200((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x02000000, 0, 0, 0);
                break;
            }
            i++;
        } while (i < D_807FBB70.unk201);
        i = 0;
    }

    if (D_807FBB70.unk39 != 0 && D_807FBB70.unk39 > 0) {
        do {
            if (GLOBAL->unk8C[i] == 0) {
                var_s1 = (u8 *)&D_807FBB70 + i * 4;
                var_s0 = (u8 *)&D_807FBB70 + i * 12;
                collisionTransformPointByActorMtx(arg0, *(s32 *)(var_s1 + 0x6C), var_s0 + 0x3C, *(s32 *)(var_s0 + 0x40), var_s0 + 0x44);
                func_8067A69C(arg0, *(s32 *)(var_s1 + 0x7C), *(s32 *)(var_s0 + 0x3C), *(s32 *)(var_s0 + 0x44), 1, 1);
            }
            i++;
        } while (i < D_807FBB70.unk39);
        i = 0;
    }

    if (D_807FBB70.unk91 != 0) {
        func_806776A0(arg0, GLOBAL->unkCC, &D_807FBC08, &D_807FBC14, GLOBAL->unkC8, GLOBAL->unkD0, GLOBAL->unkD4, 1);
    }

    var_s0 = (u8 *)&D_807FBB70;
    if (D_807FBB70.unk1F8 > 0) {
        var_s1 = (u8 *)&D_807FBC68;
        var_s3 = (u8 *)&D_807FBC74;
        do {
            func_806776A0(arg0, ((R3C_GlobalState *)var_s0)->unk134, var_s1, var_s3, ((R3C_GlobalState *)var_s0)->unk128, ((R3C_GlobalState *)var_s0)->unk12C, ((R3C_GlobalState *)var_s0)->unk130, 0);
            i++;
            var_s0 += 0x40;
            var_s1 += 0x40;
            var_s3 += 0x40;
        } while (i < D_807FBB70.unk1F8);
    }
}
