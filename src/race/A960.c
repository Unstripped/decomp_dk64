#include "common.h"

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002E960.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002E9AC.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002E9F8.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002EC08.s")

void raceScaleVelocity(u8 *arg0, f32 arg1) {
    (*(f32 *)(*(u8 **)(arg0 + 4) + 0x34)) *= arg1;
    (*(f32 *)(*(u8 **)(arg0 + 4) + 0x38)) = *(f32 *)(*(u8 **)(arg0 + 4) + 0x34);
    (*(f32 *)(*(u8 **)(arg0 + 4) + 0x3C)) = *(f32 *)(*(u8 **)(arg0 + 4) + 0x38);
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002ED04.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002EDD4.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002F04C.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002F0AC.s")

f32 func_80611BB4(f32, f32);
s32 func_806CC14C(s16, s16);
extern void *D_807FBB40;

s32 raceIsFacingWaypoint(u8 *arg0) {
    f32 diff_x = *(f32 *)((u8 *)D_807FBB40 + 0x7C) - (f32)*(s16 *)(arg0 + 0);
    f32 diff_z = *(f32 *)((u8 *)D_807FBB40 + 0x84) - (f32)*(s16 *)(arg0 + 4);
    s16 angle = (s32)(func_80611BB4(diff_x, diff_z) * 651.8986206f) & 0xFFF;

    return (func_806CC14C(angle, *(s16 *)(arg0 + 6)) < 0x400) & 0xFF;
}

f32 func_8002F04C(f32, f32, f32, f32, f32, f32, f32, f32);

f32 func_8002F304(u8 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0 = *(f32 *)(arg0 + 0xC);
    f32 temp_fv1 = *(f32 *)(arg0 + 8);

    return func_8002F04C((f32)*(s16 *)(arg0 + 0), (f32)*(s16 *)(arg0 + 4), -temp_fv0, temp_fv1, arg1, arg2, temp_fv1, temp_fv0);
}

void *func_8002E9AC(s32);
void func_8002DCF0(void *, s32);

void func_8002F36C(u8 *arg0, u8 *arg1) {
    u8 *node;

    if (*(u16 *)(arg1 + 8) != 0) {
        do {
            u16 val;
            *(u16 *)(arg0 + 0x3C) += 1;
            *(u16 *)(arg0 + 0x3C) %= *(u16 *)(arg1 + 0);
            val = *(u16 *)(*(u16 *)(arg0 + 0x3C) * 2 + *(u8 **)(arg1 + 4));
            node = func_8002E9AC(val & 0xFF);
        } while (node[0x10] == 0);
        func_8002DCF0(node, 1);
    }
}

void func_8002F420(u8 *arg0, u8 *arg1) {
    if (*(u16 *)(arg1 + 8) != 0) {
        if (*(u16 *)(arg0 + 0x3A) == *(u16 *)(arg0 + 0x3C)) {
            u16 val = *(u16 *)(*(u16 *)(arg0 + 0x3C) * 2 + *(u8 **)(arg1 + 4));
            func_8002DCF0(func_8002E9AC(val & 0xFF), 0);
            func_8002F36C(arg0, arg1);
        }
    }
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002F490.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002F784.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/raceGetProgressPercent.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/A960/func_8002F950.s")
