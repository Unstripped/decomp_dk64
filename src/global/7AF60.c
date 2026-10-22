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

#include "actor.h"

f32 func_80665E94(f32, f32, f32, f32, f32, f32, s32);

u8 func_806764D8(Actor* arg0, Actor* arg1, s32 arg2) {
    return (f64)func_80665E94(arg0->unk7C, arg0->unk80, arg0->unk84, arg1->unk7C, arg1->unk80, arg1->unk84, 0) > 0.7;
}

u8 func_80676540(void* arg0, void* arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806764D8(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = *(f32*)((u8*)arg1 + 0xC0) < -100.0f;
    }
    return var_a0;
}


u8 func_80676590(Actor* arg0, Actor* arg1, u8 arg2) {
    s32 var_v1;

    var_v1 = *(f32*)((u8*)arg0 + 0xB4) < 10.0f;
    if (var_v1) {
        var_v1 = arg0->unk80 < arg1->unk80;
    }
    return var_v1;
}

void func_80671C0C();

u8 func_806765E8(Actor* arg0, Actor* arg1, s32 arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 var_v1;

    if (*(u8*)((u8*)arg0 + 0xCC)) {
        func_80671C0C(arg0, *(u8*)((u8*)arg0 + 0xCC), &sp34, &sp30, &sp2C);
    } else {
        sp34 = arg0->unk7C;
        sp30 = arg0->unk80;
        sp2C = arg0->unk84;
    }
    return (*(f32*)((u8*)arg1 + 0xB4) < 10.0f) && (arg1->unk80 < sp30);
}

u8 func_8067641C();
s32 func_80676CB0();

u8 func_80676690(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_80676CB0(arg2, 1) != 0;
    if (var_a0) {
        var_a0 = func_8067641C(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

u8 func_806766E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_80676CB0(arg2, 2) != 0;
    if (var_a0) {
        var_a0 = func_8067641C(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}


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

#include "actor.h"

typedef struct Beh7AF2A_PlayerData {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} Beh7AF2A_PlayerData;

extern Beh7AF2A_PlayerData *D_807FC924;

u8 func_806769A8(s32 arg0, Actor* arg1, s32 arg2) {
    if (arg1->unk58 == 6) {
        u8 kong = ((u8*)arg1->unk174)[0x1A4];
        if (D_807FC924[kong].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

u8 func_80676A0C(s32 arg0, Actor* arg1, s32 arg2) {
    if (arg1->unk58 == 5) {
        u8 kong = ((u8*)arg1->unk174)[0x1A4];
        if (D_807FC924[kong].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

s32 func_8067680C();

u8 func_80676A70(s32 arg0, Actor* arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806769A8(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = func_8067680C(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

extern u8 D_807FC928;

u8 func_80676AB8(Actor* arg0, Actor* arg1, s32 arg2) {
    u8 kong = ((u8*)arg0->unk174)[0x1A4];
    u8 var_v1 = 0;

    if (arg1->unk5C & 2) {
        var_v1 = D_807FC924[kong].unk2C0 == 2;
        if (var_v1 && D_807FC928 == 1) {
            var_v1 = arg0->unk58 == 6;
        }
    }
    return var_v1;
}

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
u8 func_80676BCC(s32 arg0, Actor* arg1, s32 arg2) {
    u8 kong = ((u8*)arg1->unk174)[0x1A4];
    return D_807FC924[kong].unk2C0 == 2;
}

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
