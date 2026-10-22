#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80674B90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80674E14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80675180.s")

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

void *func_80610FE8(s32);
extern Beh798_Node *D_807FB620;
extern Beh798_Node *D_807FB624;
extern s32 D_807FB628;

void func_806752D4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    Beh798_Node *temp_v0;

    temp_v0 = func_80610FE8(sizeof(Beh798_Node));
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80675380.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_80675478.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/79890/func_806755A8.s")
