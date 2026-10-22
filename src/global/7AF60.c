#include "common.h"

void func_806D0DE4(s32, s32);

void func_80676260(s32 arg0, s32 arg1, s32 arg2) {
    func_806D0DE4(arg0, arg1);
}

extern u8 D_807F6902;
s32 func_806D10D0(s32);

u8 func_80676280(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806D10D0(arg1) != 0;
    if (var_a0) {
        var_a0 = D_807F6902 == 0;
    }
    return var_a0;
}

s32 func_806767E0();

u8 func_806762C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806767E0(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = func_80676280(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

s32 func_80676308(void* arg0, void* arg1, u8 arg2) {
    s16 diff = *(s16*)((u8*)arg0 + 0x134) - *(s16*)((u8*)arg1 + 0x136);

    if (diff <= 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676338.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_8067641C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_806764D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676540.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676590.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_806765E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676690.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_806766E0.s")

s32 func_80676CB0();

s32 func_80676730(s32 arg0, s32 arg1, s32 arg2) {
    return func_80676CB0(arg2, 1);
}

s32 func_8067675C(s32 arg0, s32 arg1, s32 arg2) {
    return func_80676CB0(arg2, 3);
}

s32 func_80676788(s32 arg0, s32 arg1, s32 arg2) {
    return func_80676CB0(arg2, 5);
}

s32 func_806767B4(s32 arg0, s32 arg1, s32 arg2) {
    return func_80676CB0(arg2, 4);
}

s32 func_806767E0(s32 arg0, s32 arg1, s32 arg2) {
    return func_80676CB0(arg2, 2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_8067680C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_806769A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676A0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676A70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676AB8.s")

#include "actor.h"

u8 func_80676AB8();

u8 func_80676B38(Actor* arg0, Actor* arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_80676AB8(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = (*(u16*)((u8*)arg0 + 0x6A) & 1) != 0;
    }
    return var_a0;
}

u8 func_80676540();
u8 func_80714608();

u8 func_80676B70(Actor* arg0, Actor* arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_80676AB8(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = func_80676540(arg1, arg0, arg2) != 0;
        if (!var_a0) {
            var_a0 = func_80714608(0) != 0;
        }
    }
    return var_a0;
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676BCC.s")

u8 func_806769A8();

u8 func_80676C10(s32 arg0, Actor* arg1, s32 arg2) {
    u8* beh = arg1->unk174;
    s32 var_a0;
    s32 var_v1 = *(s16*)(beh + 0xD4) != 0 ? 1 : 0;

    var_a0 = var_v1 != 0;
    if (!var_a0) {
        var_a0 = func_806769A8(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

s32 func_80676C64(s32 arg0, Actor* arg1, s32 arg2) {
    if (func_80676CB0(arg2, 1)) {
        if (*(u8*)((u8*)arg1 + 0x154) == 0x1C) {
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676CB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676D00.s")
