#include "common.h"
#include "actor.h"

typedef struct PlayerData {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} PlayerData;

extern u8 D_807F6902;
extern u8 D_807FC928;
extern PlayerData *D_807FC924;

void func_806D0DE4(s32, s32);
s32 func_806D10D0(s32);
s32 func_806767E0();
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void actorGetNodePos();
u8 actorIsFacingTarget();
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_806CC14C(s16, s16);
s32 func_8067680C();
s32 actorListContainsId();
u8 func_80714608();
void func_80676260(s32 arg0, s32 arg1, s32 arg2) {
    func_806D0DE4(arg0, arg1);
}

u8 func_80676280(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806D10D0(arg1) != 0;
    if (var_a0) {
        var_a0 = D_807F6902 == 0;
    }
    return var_a0;
}

u8 func_806762C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806767E0(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = func_80676280(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

s32 actorIsDamageFatal(void* arg0, void* arg1, u8 arg2) {
    s16 diff = *(s16*)((u8*)arg0 + 0x134) - *(s16*)((u8*)arg1 + 0x136);

    if (diff <= 0) {
        return 1;
    }
    return 0;
}

u8 func_80676338(s32 arg0, s32 arg1, s32 arg2) {
    u8 var_a0;

    var_a0 = func_806CC14C(mathAngleBetweenPoints2D((s16)((Actor*)arg0)->unk7C, (s16)((Actor*)arg0)->unk84, (s16)((Actor*)arg1)->unk7C, (s16)((Actor*)arg1)->unk84), *(s16*)((u8*)arg0 + 0xE6)) < 0x200;
    if (var_a0) {
        var_a0 = actorIsFacingTarget(arg0, arg1, arg2);
    }
    return var_a0;
}

u8 actorIsFacingTarget(s32 arg0, s32 arg1, s32 arg2) {
    Actor* a0 = (Actor*)arg0;
    Actor* a1 = (Actor*)arg1;
    return func_806CC14C(mathAngleBetweenPoints2D((s16)a0->unk7C, (s16)a0->unk84, (s16)a1->unk7C, (s16)a1->unk84), *(s16*)((u8*)a1 + 0xE6)) < 0x3A9;
}

u8 func_806764D8(Actor* arg0, Actor* arg1, s32 arg2) {
    return (f64)mathCalculatePitchAngle(arg0->unk7C, arg0->unk80, arg0->unk84, arg1->unk7C, arg1->unk80, arg1->unk84, 0) > 0.7;
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

u8 func_806765E8(Actor* arg0, Actor* arg1, s32 arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 var_v1;

    if (*(u8*)((u8*)arg0 + 0xCC)) {
        actorGetNodePos(arg0, *(u8*)((u8*)arg0 + 0xCC), &sp34, &sp30, &sp2C);
    } else {
        sp34 = arg0->unk7C;
        sp30 = arg0->unk80;
        sp2C = arg0->unk84;
    }
    return (*(f32*)((u8*)arg1 + 0xB4) < 10.0f) && (arg1->unk80 < sp30);
}

u8 func_80676690(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = actorListContainsId(arg2, 1) != 0;
    if (var_a0) {
        var_a0 = actorIsFacingTarget(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

u8 func_806766E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = actorListContainsId(arg2, 2) != 0;
    if (var_a0) {
        var_a0 = actorIsFacingTarget(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}


s32 func_80676730(s32 arg0, s32 arg1, s32 arg2) {
    return actorListContainsId(arg2, 1);
}

s32 func_8067675C(s32 arg0, s32 arg1, s32 arg2) {
    return actorListContainsId(arg2, 3);
}

s32 func_80676788(s32 arg0, s32 arg1, s32 arg2) {
    return actorListContainsId(arg2, 5);
}

s32 func_806767B4(s32 arg0, s32 arg1, s32 arg2) {
    return actorListContainsId(arg2, 4);
}

s32 func_806767E0(s32 arg0, s32 arg1, s32 arg2) {
    return actorListContainsId(arg2, 2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_8067680C.s")

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

u8 func_80676A70(s32 arg0, Actor* arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_806769A8(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = func_8067680C(arg0, arg1, arg2) != 0;
    }
    return var_a0;
}

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

u8 func_80676B38(Actor* arg0, Actor* arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = func_80676AB8(arg0, arg1, arg2) != 0;
    if (var_a0) {
        var_a0 = (*(u16*)((u8*)arg0 + 0x6A) & 1) != 0;
    }
    return var_a0;
}

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
    if (actorListContainsId(arg2, 1)) {
        if (*(u8*)((u8*)arg1 + 0x154) == 0x1C) {
            return 1;
        }
    }
    return 0;
}

typedef struct Beh7AF3_Node {
    char pad[0x14];
    s32 id;
    char pad2[4];
} Beh7AF3_Node;

typedef struct Beh7AF3_List {
    char pad[0xC];
    s32 count;
    Beh7AF3_Node* items;
} Beh7AF3_List;

s32 actorListContainsId(list, id)
Beh7AF3_List* list;
u8 id;
{
    Beh7AF3_Node* items = list->items;
    s32 i = 0;

    while (i < list->count) {
        if (items[i].id == id) {
            return 1;
        }
        i++;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7AF60/func_80676D00.s")
