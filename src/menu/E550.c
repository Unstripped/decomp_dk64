#include "common.h"

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xCD - 0x88];
    u8 unkCD;
    char padCE[0x154 - 0xCE];
    u8 unk154;
    u8 unk155;
    char pad156[0x15F - 0x156];
    u8 unk15F;
    char pad160[0x16A - 0x160];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
} MenuLightFadeActor;

extern MenuLightFadeActor *D_807FBB40;
extern u8 D_80033FB0;
extern u8 D_80033FB1;
extern u8 D_80033FB2;

void behaviourFrameBegin(void);
void lightUpdateFromActorLighting(u8 *, u8 *, u8 *);
s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void actorScriptStart(MenuLightFadeActor *, s32);
void actorUpdateModelMatrix(MenuLightFadeActor *, s32);

void func_80032550(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkCD = 1;
        D_807FBB40->unk60 &= ~4;
    }
    if (D_807FBB40->unk60 & 4) {
        lightUpdateFromActorLighting(&D_80033FB0, &D_80033FB1, &D_80033FB2);
    }
    if (D_807FBB40->unk154 == 0 && D_807FBB40->unk155 == 0) {
        do {
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                actorScriptStart(D_807FBB40, 0x2A7);
                D_807FBB40->unk155++;
            }
        } while (0); // FAKE: do/while(0) wrapper steers branch codegen
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u8 D_800339D0;
extern s32 D_807FBB60;
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_807145F8(void);
void renderCallbacksRegister(void *, void *, s32);
Gfx *func_8003292C(Gfx *, void *);

void menuUpdateLightFadeActor(void) {
    s32 d;
    s32 cur;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk15F = 0;
        currentActorClearFlag();
        D_807FBB40->unk154 = 0;
    }
    behaviourFrameBegin();
    switch (D_807FBB40->unk154) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            actorScriptStart(D_807FBB40, 0x2D6);
            D_807FBB40->unk154++;
            D_807FBB40->unk155 = 0;
            D_807FBB60 &= ~0x30;
        }
        break;
    case 1:
        lightSetFovAngles(20.0f, 40.0f);
        cur = D_807FBB40->unk15F;
        if (D_807FBB40->unk15F != 0xFF) {
            d = (0xFF - cur < 3) ? 0xFF - cur : 3;
            D_807FBB40->unk15F = cur + d;
        }
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80 + 20.0f, D_807FBB40->unk84, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f, 1, D_807FBB40->unk15F, D_807FBB40->unk15F, D_807FBB40->unk15F);
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            D_807FBB40->unk60 |= 0x800000;
            D_807FBB40->unk154 = 2;
        }
        break;
    case 2:
        D_807FBB40->unk16A -= 8;
        D_807FBB40->unk16B -= 8;
        D_807FBB40->unk16C -= 8;
        if (D_807FBB40->unk16A < 9) {
            D_807FBB40->unk16A = 0;
            D_807FBB40->unk16B = 0;
            D_807FBB40->unk16C = 0;
            D_807FBB40->unk154 = 3;
            D_800339D0 = 0;
        }
        break;
    case 3:
        if (D_800339D0 < 0xFF) {
            D_800339D0++;
        }
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            D_807FBB40->unk154 = 4;
        }
        break;
    case 4:
        func_807145F8();
        D_807FBB40->unk154++;
        break;
    }
    if (D_807FBB40->unk154 >= 3) {
        renderCallbacksRegister(func_8003292C, D_807FBB40, 3);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}



#pragma GLOBAL_ASM("asm/menu/nonmatchings/E550/func_8003292C.s")
