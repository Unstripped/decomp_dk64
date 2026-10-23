#include "common.h"
#include "actor.h"

typedef struct ActorMapFlag {
    u16 map;
    u8 unk2;
    s16 unk4;
} ActorMapFlag;

typedef struct TagBarrelState {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    union {
        f32 unkC;
        struct {
            u8 unkC_b;
            u8 unkD;
        };
    };
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
} TagBarrelState;

typedef struct ActorD580 {
    /* 0x000 */ u8 pad0[0xCA];
    /* 0x0CA */ u8 unkCA;
} ActorD580;

typedef struct ActorAnimLookup {
    struct {
        s16 unk0;
        s16 unk2;
    } arr[5];
} ActorAnimLookup;

typedef struct ActorGroup5 {
    u8 pad0[8];
    Actor *unk8[5];
} ActorGroup5;

typedef struct ActorKongAction {
    u8 pad0[4];
    u8 unk4;
    u8 unk5;
} ActorKongAction;

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern ActorD580 *D_807FD580;
extern void *D_807FBB4C;
extern u16 *D_807FBB54;
extern s32 D_8076A0A8;
extern s32 D_8071FE08;
extern u8 D_8074E77C;
extern ActorMapFlag D_8074E7A0[];
extern s16 D_8074E7E0[];
extern ActorKongAction D_8074E814[];
extern ActorAnimLookup D_8074E834;
extern s32 D_8074E85C[];
extern u8 D_80720120;
extern u8 D_80720340;
extern u8 D_8072038C;

s16 func_805FF018(s32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 func_80611A44(void);
void func_80614EBC();
void func_8061CC40(void *, s32, s32);
void func_806319C4(Actor *, s32);
void func_80665564(Actor *, f32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void actorDespawn(Actor *);
void func_8067B4C8(void);
void func_8067BA7C(s32);
s32 func_8067BF84(s32, u8 *, u8 *, u8 *);
void func_8067C71C(void);
void func_8067DCC0(void);
void func_8067DF44(f32, f32, f32, f32, u8, u8);
void tagBarrelResetMovement(void);
void tagBarrelTriggerRecoil(void);
void tagBarrelCheckRecoil(void);
void func_8067E784(void);
void func_806809F0(void);
void func_8068412C(void);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
s32 actorListFindIdByActor(Actor *);
void func_8068A764(Actor *, u8);
void func_8069B908(void);
void func_806F8D58(s32, s32);
s32 func_8070E750(s32, s32, s32);
void func_80714950(s32);
void func_8071496C(s32);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8071ABDC(void);
void func_8071B89C(void);
void func_8071BB14(void);
s32 func_8073110C(s16, s32);
void func_8073129C(s16, s32, s32);

s32 func_8067B450(void *actor) {
    s32 count = 4;
    s32 val = actorListFindIdByActor(actor);
    s32 i;

    for (i = 0; i < count; i++) {
        if (D_8076A0A8 == D_8074E7A0[i].map && val == D_8074E7A0[i].unk2) {
            return func_8073110C(D_8074E7A0[i].unk4, 0);
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067B4C8.s")

void func_8067BA3C(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x7D0;
    }
    func_8067B4C8();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067BA7C.s")
void func_8067BC68(void) {
    func_8067BA7C(0x13);
}

void func_8067BC88(void) {
    func_8067BA7C(0x13);
}

void func_8067BCA8(void) {
    func_8067BA7C(0x13);
}

void func_8067BCC8(void) {
    func_8067BA7C(0x13);
}

void func_8067BCE8(void) {
    func_8067BA7C(0x13);
}

void func_8067BD08(void) {
    func_8067BA7C(0x13);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067BD28.s")

void func_8067BDB8(void) {
    func_8067BA7C(0x95);
    func_80665564(D_807FBB40, 0.0f);
    D_807FBB40->unk80 = D_807FBB40->unkA4;
}

void func_8067BDF8(void) {
    u8 sp1F;
    u8 *ptr;

    sp1F = 0;
    ptr = D_807FBB40->unk174;
    func_8067BF84(0x13, ptr, ptr + 1, &sp1F);
}

void func_8067BE30(void) {
    u8 *t0 = D_807FBB40->unk174;
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x7D0;
        *(s16 *)t0 = 0x1A;
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        switch (D_807FBB70.unk258[i]) {
        case 1:
            *(s16 *)t0 = 0x60;
            break;
        case 2:
            *(s16 *)t0 = 0;
            break;
        case 3:
            *(s16 *)t0 = 0x1A;
            break;
        }
    }
    if (*(s16 *)t0 != 0) {
        if (func_8067BF84(*(s16 *)t0, t0 + 2, t0 + 3, t0 + 4)) {
            *(s16 *)t0 = 0x1A;
        }
    } else {
        if (D_807FBB70.unk38 != 0) {
            t0[4] = 1;
        }
        func_806319C4(D_807FBB40, 0);
    }
}

void func_8067BF4C(void) {
    u8 *ptr = D_807FBB40->unk174;
    func_8067BF84(0x1A, ptr + 2, ptr + 3, ptr + 4);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067BF84.s")

typedef struct R2H_8067C2B8 {
    u8 unk0;
    u8 pad1[3];
    f32 unk4;
    u8 unk8;
} R2H_8067C2B8;

typedef struct R2H_Actor {
    /* 0x000 */ u8 unk00[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 unk64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u8 unk6A[0x16];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 unk84[0x20];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 unkA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 unkBC[0x32];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 unkF0[0xA];
    /* 0x0FA */ s16 unkFA;
    /* 0x0FC */ u8 unkFC[0x48];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 unk145[0x2F];
    /* 0x174 */ void *unk174;
} R2H_Actor;

typedef struct R2H_ActorGlobalState {
    /* 0x000 */ u8 unk0[0x90];
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ s16 unk92;
    /* 0x094 */ s16 unk94;
} R2H_ActorGlobalState;

#define R2H_ACTOR ((R2H_Actor *)D_807FBB40)
#define R2H_STATE ((R2H_ActorGlobalState *)&D_807FBB70)

void func_80604CBC(Actor *, s32, s32, s32, s32, s32, f32, s32);
void func_80605314(Actor *, s32);
void func_80665160(Actor *, s16, s16);
void func_806651FC(Actor *);

void func_8067C2B8(void) {
    R2H_8067C2B8 *temp_v0;
    f32 temp_fv1;
    f32 temp_fv0;
    s16 temp_a1;

    temp_v0 = (R2H_8067C2B8 *) R2H_ACTOR->unk174;
    if (!(R2H_ACTOR->unk60 & 0x10)) {
        R2H_ACTOR->unk68 |= 4;
        R2H_ACTOR->unk60 |= 0x80;
        temp_v0->unk0 = 0;
        temp_v0->unk8 = 0;
        temp_v0->unk4 = 0.0f;
    }
    if (!(R2H_ACTOR->unk68 & 4)) {
        R2H_ACTOR->unkB8 = 0.0f;
    }
    if (R2H_STATE->unk90 != 0) {
        temp_v0->unk8 = 1;
    }
    if (R2H_STATE->unk91 != 0) {
        if (temp_v0->unk0 == 0) {
            func_80604CBC(D_807FBB40, 0x10C, 0, 1, 0, 0xFF, 1.0f, 0);
            temp_v0->unk0 = 1;
        }
        temp_v0->unk4 = (f64) R2H_STATE->unk94 / 1.1;
        R2H_ACTOR->unkEE = R2H_STATE->unk92;
        temp_fv1 = R2H_ACTOR->unkB8;
        if (temp_fv1 < temp_v0->unk4) {
            R2H_ACTOR->unkB8 = temp_fv1 + 0.8;
            temp_fv0 = temp_v0->unk4;
            if (temp_fv0 < R2H_ACTOR->unkB8) {
                R2H_ACTOR->unkB8 = temp_fv0;
            }
        } else {
            R2H_ACTOR->unkB8 = temp_fv1 - 1.5;
            if (R2H_ACTOR->unkB8 < 0.0f) {
                R2H_ACTOR->unkB8 = 0.0f;
            }
        }
        R2H_ACTOR->unkFA = 0x64;
        temp_a1 = R2H_ACTOR->unkEE;
        func_80665160(D_807FBB40, temp_a1, temp_a1);
        func_806651FC(D_807FBB40);
        func_80665564(D_807FBB40, 0.0f);
        R2H_ACTOR->unk80 = R2H_ACTOR->unkA4;
        if (temp_v0->unk8 == 0) {
            R2H_ACTOR->unk144 = 0x3C;
        }
    } else {
        if ((temp_v0->unk0 != 0) && ((f64) R2H_ACTOR->unkB8 == 0.0)) {
            temp_v0->unk0 = 0;
            func_80605314(D_807FBB40, 0);
        }
        temp_v0->unk4 = 0.0f;
        temp_fv1 = R2H_ACTOR->unkB8;
        if (temp_fv1 < 0.0f) {
            R2H_ACTOR->unkB8 = temp_fv1 + 0.8;
            temp_fv0 = temp_v0->unk4;
            if (temp_fv0 < R2H_ACTOR->unkB8) {
                R2H_ACTOR->unkB8 = temp_fv0;
            }
        } else {
            R2H_ACTOR->unkB8 = temp_fv1 - 1.5;
            if (R2H_ACTOR->unkB8 < 0.0f) {
                R2H_ACTOR->unkB8 = 0.0f;
            }
        }
        R2H_ACTOR->unkFA = 0x64;
        temp_a1 = R2H_ACTOR->unkEE;
        func_80665160(D_807FBB40, temp_a1, temp_a1);
        func_806651FC(D_807FBB40);
        func_80665564(D_807FBB40, 0.0f);
        if (temp_v0->unk8 == 0) {
            if (((f64) R2H_ACTOR->unkB8 == 0.0) || !(R2H_ACTOR->unk60 & 0x10)) {
                R2H_ACTOR->unk144 = 2;
            } else {
                R2H_ACTOR->unk144 = 0x3C;
            }
        }
        R2H_ACTOR->unk80 = R2H_ACTOR->unkA4;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_8067C67C(void) {
    func_8067C71C();
}

void func_8067C69C(void) {
    func_8067C71C();
}

void func_8067C6BC(void) {
    func_8067C71C();
}

void func_8067C6DC(void) {
    func_8069B908();
}

void func_8067C6FC(void) {
    func_8067C71C();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067C71C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067DCC0.s")

void func_8067DF44(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f64 sp80;
    f32 sp7C;
    f32 temp_fs2;
    f32 temp_fs1;
    f32 temp_fs0;
    s32 var_s0;

    if (arg5 != 0) {
        func_806086CC(arg0, arg1, arg2, 0xF6, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
    }
    func_807149B8(1);
    func_8071498C(func_8071B89C);
    func_80714CC0(&D_80720120, 0.0f, arg0, arg1 + 5.0f, arg2);
    sp80 = (f64) arg3;
    sp7C = sp80 * 1.5;
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        temp_fs1 = (f32) (((s32) (func_80611A44() >> 15) % 20) - 10) * arg3;
        temp_fs2 = (f32) (((s32) (func_80611A44() >> 15) % 20) - 10) * arg3;
        temp_fs0 = (f32) (((s32) (func_80611A44() >> 15) % 20) - 10) * arg3;
        func_8071496C(4);
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_8071BB14);
        func_80714CC0(&D_80720340, sp7C, arg0 + temp_fs1, arg1 + temp_fs2, arg2 + temp_fs0);
    }
    func_8071496C(4);
    func_807149B8(1);
    func_807149FC(1);
    func_8071498C(func_8071BB14);
    func_80714CC0(&D_80720340, sp7C, arg0, arg1, arg2);
    if (arg4 != 0) {
        for (var_s0 = 0; var_s0 != 12; var_s0++) {
            func_807149B8(1);
            func_807149FC(2);
            func_80714950(var_s0 + 0x0B020000);
            func_8071498C(func_8071ABDC);
            func_80714998(1);
            func_80714CC0(&D_8072038C, (f32)(sp80 * 0.5), arg0, arg1, arg2);
        }
    }
}

void func_8067E278(arg0, arg1)
u8 arg0;
u8 arg1;
{
    func_8067DF44(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (f32) ((f64) D_807FBB40->unk4->unk38 / 0.15), arg0, arg1);
}

void func_8067E2E4(s32 arg0, u8 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    actorGetNodePos(D_807FBB40, arg1, &sp2C, &sp28, &sp24);
    func_8067DF44(sp2C, sp28, sp24, arg2, 0, 1);
}

void tagBarrelResetMovement(void) {
    TagBarrelState *temp_v0 = D_807FBB40->unk174;

    D_807FBB40->unk4->unk34 = temp_v0->unkC;
    D_807FBB40->unk4->unk38 = temp_v0->unkC;
    D_807FBB40->unk4->unk3C = temp_v0->unkC;
    D_807FBB40->unk80 = temp_v0->unk14;
    temp_v0->unk8 = 0;
    temp_v0->unk18 = 0;
    temp_v0->unk10 = temp_v0->unkC;
    D_807FBB40->unk154 = 0;
    D_807FBB40->unk144 = 2;
    D_807FBB40->unk60 &= ~0x200000;
}

void tagBarrelTriggerRecoil(void) {
    tagBarrelResetMovement();
    D_807FBB40->unk154 = 0x14;
    D_807FBB40->unk144 = 1;
    D_807FBB40->unk60 &= ~0x8000;
    D_807FBB40->unk128 = 0;
    func_806F8D58(5, 0);
}

void tagBarrelCheckRecoil(void) {
    s16 i;

    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0xFF) {
            tagBarrelTriggerRecoil();
        }
    }
}

void func_8067E4D4(void) {
    func_8067E784();
    if (D_807FBB40->unk154 == 0) {
        tagBarrelCheckRecoil();
    }
}

void func_8067E510(void) {
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk4->unk34 = (f32)(D_807FBB40->unk4->unk34 * 1.5);
        D_807FBB40->unk4->unk38 = (f32)(D_807FBB40->unk4->unk38 * 1.5);
        D_807FBB40->unk4->unk3C = (f32)(D_807FBB40->unk4->unk3C * 1.5);
        D_807FBB40->unk12A = 0x7D0;
    }
    if (D_807FBB40->unk154 == 0) {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1) {
                func_807149B8(0);
                func_807149FC(1);
                func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
                actorDespawn(D_807FBB40);
            }
        }
    }
    func_8067E784();
}

void func_8067E69C(void) {
    func_8067E784();
    tagBarrelCheckRecoil();
}

void func_8067E6C4(void) {
    func_8067E784();
}

void func_8067E6E4(void) {
    func_8067E784();
}

void func_8067E704(void) {
    func_8067E784();
}

void func_8067E724(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x320;
    }
    func_8067E784();
}

void func_8067E764(void) {
    func_8067E784();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067E784.s")

void func_8067FAC8(void) {
    s16 i;

    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 1) {
            func_8067DCC0();
            actorDespawn(D_807FBB40);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8067FB6C.s")

typedef struct R2FStructD580 {
    /* 0x000 */ char unk0[0xCA];
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ char unkCB[0x1F0 - 0xCB];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
} R2FStructD580;

typedef struct PlayerData {
    /* 0x000 */ u8 unk0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 unk21C[0xA4];
    /* 0x2C0 */ u8 unk2C0;
} PlayerData;

extern PlayerData *D_807FC924;

void tagBarrelUpdateInteractable(void) {
    s32 one = 1;

    if (one != D_807FC924->unk2C0 || (((R2FStructD580 *)D_807FD580)->unk1F4 & 0x40) || D_8074E77C >= 5) {
        D_807FBB40->unk132 = 4;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x7F;
    } else if (one == D_807FC924->unk2C0 && !(((R2FStructD580 *)D_807FD580)->unk1F0 & 0x40) && D_8074E77C < 5) {
        D_807FBB40->unk60 |= 0x8000;
        D_807FBB40->unk132 = one;
    }
    if (((R2FStructD580 *)D_807FD580)->unkCA != 0) {
        D_807FBB40->unk132 = 4;
    }
}

void func_8068086C(void) {
    if (D_8074E77C >= 5) {
        D_807FBB40->unk132 = 4;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x7F;
    } else {
        D_807FBB40->unk60 |= 0x8000;
        D_807FBB40->unk132 = 1;
    }
    if (D_807FD580->unkCA != 0) {
        D_807FBB40->unk132 = 4;
    }
}

u8 func_80680908(void) {
    u8 ret = 0x64;

    switch (D_8076A0A8) {
    case 0x1A:
        if (actorListFindIdByActor(D_807FBB40) == 0xD || actorListFindIdByActor(D_807FBB40) == 0xF) {
            ret = 2;
        }
        break;
    case 0x3B:
        if (actorListFindIdByActor(D_807FBB40) == 3) {
            ret = 2;
        }
        break;
    case 0x30:
        if (actorListFindIdByActor(D_807FBB40) == 0x12) {
            ret = 2;
        }
        break;
    case 0xAD:
    case 0xC3:
        ret = 2;
        break;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806809F0.s")

void func_80681B14(void) {
    TagBarrelState *sub = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        if (func_8073110C(0x302, 0) != 0) {
            actorDespawn(D_807FBB40);
            return;
        }
    }
    func_806809F0();
    if (D_807FBB40->unk154 == 0xC && sub->unkD < 3) {
        func_8073129C(D_8074E7E0[sub->unkA], 1, 2);
        func_8067DCC0();
        actorDespawn(D_807FBB40);
    }
}

void func_80681BD8(void) {
    TagBarrelState *sub = D_807FBB40->unk174;
    s32 sp28;
    s32 count;
    s32 i;

    func_806809F0();
    if (func_8073110C(0x17F, 0) == 0) {
        D_807FBB40->unk154 = 0x14;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
    } else {
        if (func_8073110C(0x187, 0) == 0) {
            count = 0;
            if (D_807FBB40->unk154 == 0xB) {
                i = 0;
                do {
                    count += (func_8073110C((s16)(i + 0x182), 0) != 0);
                } while (++i != 4);
                if (count == 4) {
                    func_8061CC40(D_807FBB4C, 3, 1);
                    func_8073129C(0x187, 1, 0);
                }
            }
        }
        switch (sub->unk6) {
        case 0xB1:
            sp28 = 0x182;
            break;
        case 0xB6:
            sp28 = 0x183;
            break;
        case 0xB4:
            sp28 = 0x184;
            break;
        case 0xB5:
            sp28 = 0x185;
            break;
        }
        if (func_8073110C(sp28, 0) != 0) {
            sub->unkC_b = 1;
            sub->unkA = 0;
            if (D_807FBB40->unk154 == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        } else if (D_807FBB40->unk154 == 0x14) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk154 = 0x15;
        }
    }
    if (D_807FBB40->unk154 == 0xC && sub->unkD < 3) {
        func_8067DCC0();
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80681E18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806822FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80682AB4.s")

void func_80682DF4(void *arg0, u16 *arg1, s32 arg2) {
    arg2 = arg2 * 7;
    arg2 += *arg1 - 2;
    func_80614EBC(arg0, D_807FBB54[arg2], arg2);
}

typedef struct R2FStruct_80682E38 {
    u8 pad0[6];
    s8 unk6;
    u8 pad7;
    Actor *unk8[5];
    Actor *unk1C;
} R2FStruct_80682E38;

typedef struct R2FKongAction {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} R2FKongAction;

extern Actor *D_807FBB44;
s32 actorSpawn(s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_806F09F0(Actor *, u16);
void func_80682AB4(void *);

void tagBarrelSpawnKongs(R2FStruct_80682E38 *arg0) {
    s32 i;
    s32 actorType;
    s16 model;
    u16 *temp_s0;
    s32 var_a2;
    s32 flag = 0x40000000;
    actorSpawn(0x136, 0xA8);
    arg0->unk1C = D_807FBB44;
    D_807FBB44->unk7C = D_807FBB40->unk7C + func_80612794(D_807FBB40->unkE6) * 35.0f;
    D_807FBB44->unk80 = (D_807FBB40->unk80 - 10.0f) - 2.0f;
    D_807FBB44->unk84 = D_807FBB40->unk84 + func_80612790(D_807FBB40->unkE6) * 35.0f;

    for (i = 0; i < 5; i++) {
        if (func_8073110C(func_805FF018(D_807FBB40->unk58, i), 0)) {
            actorType = 0x13C;
            model = ((R2FKongAction *)D_8074E814)[i].unk0;
        } else {
            actorType = 0x13D;
            model = 0xD2;
        }
        actorSpawn(actorType, model);
        arg0->unk8[i] = D_807FBB44;
        D_807FBB44->unkE6 = D_807FBB40->unkE6;
        D_807FBB44->unk60 |= flag;
        if (actorType == 0x13C) {
            temp_s0 = D_807FBB44->unk174;
            *temp_s0 = ((R2FKongAction *)D_8074E814)[i].unk2;
            func_806F09F0(D_807FBB44, *temp_s0);
            var_a2 = (i == arg0->unk6) ? 0x8B : 0x8A;
            func_80682DF4(D_807FBB44, temp_s0, var_a2);
        } else {
            u8 *temp = D_807FBB44->unk174;
            *temp = i;
        }
    }
    func_80682AB4(arg0);
}

void tagBarrelUpdateSelectedKong(void) {
    ActorAnimLookup sp2C;
    u8 *sp28;

    if (!(D_807FBB40->unk60 & 0x10)) {
        sp2C = D_8074E834;
        sp28 = D_807FBB40->unk174;
        D_807FBB40->unk60 |= 0x1000;
        animSetLoopLimit(D_807FBB40, 0, 1);
        animSetFinished(D_807FBB40, 0, 1);
        animSetFrameAndSubframe(D_807FBB40, 0, sp2C.arr[*sp28].unk2, 0.0f);
        func_80614EBC(D_807FBB40, 0x329);
    }
    D_807FBB40->unk16D = D_807FBB40->unk15F;
    D_807FBB40->unkE6 += 0x32;
    D_807FBB40->unkE6 &= 0xFFF;
    func_806319C4(D_807FBB40, 0);
}

typedef struct R2G_ActorExtra {
    u16 unk0;
    u16 pad2;
    void (*unk4)(Actor *, void *, s32 *);
    u8 unk8[1];
} R2G_ActorExtra;

typedef struct R2G_ActorSub4 {
    u8 pad0[0x1C];
    void *unk1C;
} R2G_ActorSub4;

typedef struct R2G_Actor {
    u8 pad0[0xC0];
    f32 unkC0;
    u8 padC4[0x146 - 0xC4];
    s16 unk146;
    u8 pad148[0x168 - 0x148];
    s16 unk168;
    u8 pad16A[0x178 - 0x16A];
    void *unk178;
} R2G_Actor;


void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_806C8220(s32, void *, u16);
void func_806F1C04(Actor *, void *, s32 *);
void func_806F22A8(Actor *, void *, s32 *);
void func_806F1EB0(Actor *, void *, s32 *);
s32 func_80665DE0(f32, f32, f32, f32);
s32 func_8072881C(s32, void *);

void func_80683158(void) {
    s32 sp3C;
    R2G_ActorExtra *extra;
    u8 *extra8;

    sp3C = 0;
    extra = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x1000;
        ((R2G_ActorSub4 *)D_807FBB40->unk4)->unk1C = func_80610FE8(0x100);
        heapClearBlock(((R2G_ActorSub4 *)D_807FBB40->unk4)->unk1C);
        func_806C8220(0, ((R2G_Actor *)D_807FBB40)->unk178, extra->unk0);
        switch (extra->unk0) {
        case 2:
            extra->unk4 = func_806F1C04;
            break;
        case 3:
            extra->unk4 = func_806F22A8;
            break;
        case 5:
            extra->unk4 = func_806F1EB0;
            break;
        }
    } else {
        if (extra->unk4 != NULL) {
            extra->unk4(D_807FBB40, ((R2G_ActorSub4 *)D_807FBB40->unk4)->unk1C, &sp3C);
        }
    }
    *((u8 *)((R2G_ActorSub4 *)D_807FBB40->unk4)->unk1C + sp3C * 8) = 0;
    D_807FBB40->unk16D = D_807FBB40->unk15F;
    D_807FBB40->unkE6 = func_80665DE0(D_807FC924->unk210, D_807FC924->unk218, D_807FBB40->unk7C, D_807FBB40->unk84);
    extra8 = extra->unk8;
    if (func_8072881C(0, extra8) != 0) {
        if (extra->unk0 == 3 || extra->unk0 == 5) {
            func_8072881C(0x81, extra8);
        }
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806832F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806833DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_806836D0.s")

s32 tagBarrelIsKongUnlocked(ActorGroup5 *arg0, s32 arg1) {
    s32 type = arg0->unk8[arg1]->unk58;
    s32 ret = 0;

    if ((type ^ 0x13C) == 0) {
        ret = func_8070E750(2, D_8074E85C[arg1], 1);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80683AD8.s")

void tagBarrelInitUnlockedKongs(Actor *arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (func_8073110C(func_805FF018(arg0->unk58, i), 0)) {
            func_8068A764(arg0, D_8074E814[i].unk4);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_8068412C.s")

void func_806844EC(void) {
    func_8068412C();
}

void func_8068450C(void) {
    func_8068412C();
}

void func_8068452C(void) {
    func_8068412C();
}
