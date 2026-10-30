// func_80714D08 (src/global/119370.c): stage 4: 0x30 frame and s0-s2 reached; parameter/FPR/register order remains
#include "common.h"

extern EffectGridNode *D_807FDB00;
extern EffectNode *D_807FDB04;
extern EffectNode *D_807FDB08;
extern s8 D_807FDB0C, D_807FDB0D, D_807FDB0E, D_807FDB0F;
extern s32 D_807FDB10, D_807FDB14, D_807FDB2C, D_807FDB30, D_807FBB64;
extern s16 D_807FDB1A, D_807FDB38, D_807FDB3A, D_807FDB3C, D_807FDB3E, D_807FDB40, D_807FDB42;
extern u8 D_807FDB18, D_807FDB1C, D_807FDB1D, D_807FDB28, D_80750AB4;
extern f32 D_807FDB20, D_807FDB24;
extern u16 D_807FDB36;
void *heapAlloc(s32);
void effectGridRegister(EffectGridNode *);
void effectResetState(void);
void func_8071509C(EffectNode *);

#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))

void func_80714D08(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, void *arg5, s32 arg6, s32 arg7, s32 arg8) {
    EffectGridNode *node;
    EffectNode *effect;
    EffectNode *cursor;
    f32 x;
    f32 y;
    f32 z;
    s32 found;
    s32 i;

    effectGridRegister((EffectGridNode *)arg0);
    z = arg2;
    x = arg1;
    y = arg3;
    node = D_807FDB00;
    found = 0;
    if (node != NULL) {
        do {
            if (node->unk0 == (void *)arg0) {
                found = 1;
            }
            node = node->unk24;
        } while ((found == 0) && (node != NULL));
    }
    if (found == 0) {
        effectResetState();
        return;
    }
    effect = heapAlloc(0x3A0);
    if (D_807FDB04 != NULL) {
        D_807FDB08->next = effect;
        effect->previous = D_807FDB08;
    } else {
        D_807FDB04 = effect;
        effect->previous = NULL;
    }
    D_807FDB08 = effect;
    if (D_807FDB1D != 0) {
        z *= 4.0f;
        y *= 4.0f;
        x *= 4.0f;
        arg4 *= 4.0f;
        D_807FDB20 *= 4.0f;
        D_807FDB24 *= 4.0f;
    }
    UA1_D08_FIELD(f32, effect, 0x340) = z;
    UA1_D08_FIELD(f32, effect, 0x344) = y;
    UA1_D08_FIELD(f32, effect, 0x348) = arg4;
    if (D_807FDB28 != 0) {
        UA1_D08_FIELD(f32, effect, 0x360) = D_807FDB20;
        UA1_D08_FIELD(f32, effect, 0x364) = D_807FDB24;
    } else {
        UA1_D08_FIELD(f32, effect, 0x360) = x;
        UA1_D08_FIELD(f32, effect, 0x364) = x;
    }
    if (D_807FDB0F != 0) {
        UA1_D08_FIELD(u8, effect, 0x36A) = D_807FDB0C;
        UA1_D08_FIELD(u8, effect, 0x36B) = D_807FDB0D;
        UA1_D08_FIELD(u8, effect, 0x36C) = D_807FDB0E;
        UA1_D08_FIELD(u8, effect, 0x36D) = D_807FDB0F;
    } else {
        UA1_D08_FIELD(u8, effect, 0x36A) = *((u8 *)node + 0x10);
        UA1_D08_FIELD(u8, effect, 0x36B) = *((u8 *)node + 0x11);
        UA1_D08_FIELD(u8, effect, 0x36C) = *((u8 *)node + 0x12);
        UA1_D08_FIELD(u8, effect, 0x36D) = *((u8 *)node + 0x13);
    }
    UA1_D08_FIELD(u8, effect, 0x36E) = D_807FDB18;
    effect->mode = D_807FDB1D;
    UA1_D08_FIELD(s16, effect, 0x368) = D_807FDB1A;
    UA1_D08_FIELD(s32, effect, 0x380) = *((u8 *)node + 8) * *((u8 *)node + 9);
    UA1_D08_FIELD(u8, effect, 0x334) = arg8;
    effect->resource = (s32)arg5;
    UA1_D08_FIELD(s16, effect, 0x33C) = arg6;
    UA1_D08_FIELD(s8, effect, 0x33E) = arg7;
    UA1_D08_FIELD(s16, effect, 0x34E) = D_807FDB30;
    UA1_D08_FIELD(u8, effect, 0x351) = 0;
    UA1_D08_FIELD(u8, effect, 0x350) = D_807FDB1C;
    UA1_D08_FIELD(s32, effect, 0x358) = 0;
    UA1_D08_FIELD(s32, effect, 0x354) = D_807FDB10;
    UA1_D08_FIELD(s32, effect, 0x35C) = D_807FDB2C;
    if (D_807FBB64 & 0x100) {
        UA1_D08_FIELD(s16, effect, 0x34C) = 0x7D0;
    } else {
        UA1_D08_FIELD(s16, effect, 0x34C) = D_807FDB3A;
    }
    UA1_D08_FIELD(EffectGridNode *, effect, 0x330) = node;
    effect->next = NULL;
    effect->allocation = NULL;
    UA1_D08_FIELD(s32, effect, 0x328) = D_807FDB14;
    UA1_D08_FIELD(s8, effect, 0x38A) = -1;
    UA1_D08_FIELD(s16, effect, 0x388) = D_807FDB38;
    effect->flags = D_807FDB36;
    UA1_D08_FIELD(s16, effect, 0x38E) = D_807FDB3C;
    UA1_D08_FIELD(s16, effect, 0x390) = D_807FDB3E;
    UA1_D08_FIELD(s16, effect, 0x392) = D_807FDB40;
    UA1_D08_FIELD(s16, effect, 0x394) = D_807FDB42;
    cursor = effect;
    for (i = 0; i < D_80750AB4; i++) {
        *((void **)cursor + 0) = heapAlloc(0x200);
        *((void **)cursor + 1) = heapAlloc(0x200);
        cursor = (EffectNode *)((u8 *)cursor + 8);
    }
    *((u8 *)effect + 0x20) = D_80750AB4;
    func_8071509C(effect);
    effectResetState();
}
