#include "common.h"
#include "actor.h"

typedef struct M4ActorTail {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x58];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x6F];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
} M4ActorTail;

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u16 D_807FBB34;
extern ActorEntry D_807FB930[];

void func_80609140(s32, s32, f32, f32, s32, s32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void func_806A5DF0(s16, s32, s32, s32, s16, u8, s16, s32);
void func_8067A70C(Actor *, Actor *, s32, f32, f32, s32, s32);

extern Gfx D_1000118;
extern Mtx D_20000C0;
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32,
                   f32);
extern u32 D_80744478;
extern u8 D_80750AD4;
void renderCallbacksRegister(void *, void *, s32);
s32 actorSpawn(s32, s32);
void actorDespawn(Actor *);
void func_8069FA40(Gfx *, Actor *);

#define WRITE_GFX(pkt, _w0, _w1)                                               \
    {                                                                          \
        Gfx *_g = (Gfx *)(pkt);                                                \
        _g->words.w0 = (_w0);                                                  \
        _g->words.w1 = (_w1);                                                  \
    }

#ifdef NON_MATCHING
typedef struct M4Sub4 {
    /* 0x00 */ void *unk0;
} M4Sub4;

typedef struct M4Sub4Inner {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} M4Sub4Inner;

void func_80613C48(Actor *, s16, f32, f32);
void func_80613CA8(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
s32 actorListFindIdByActor(Actor *);
void func_806319C4(Actor *, s32);

void func_8069E210(void) {
    Actor *actor;
    s16 i;

    actor = D_807FBB40;
    if (!(actor->unk60 & 0x10)) {
        actor->unk60 &= ~4;
        func_80613C48(D_807FBB40, 0x407, 0.0f, 0.0f);
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
        actor = D_807FBB40;
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (*D_807FBB70.unk278[i] == 0) {
            actor->unk60 |= 4;
            func_80613CA8(D_807FBB40, 0x407, 0.0f, 0.0f);
            func_80614D00(D_807FBB40, 1.0f, 0.0f);
            switch (actorListFindIdByActor(D_807FBB40)) {
            case 5:
                func_80609140(0x1D7, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 6:
                func_80609140(0x1D8, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 7:
                func_80609140(0x1D9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                break;
            case 8:
                func_80609140(0x1DA, 0x7FFF, 63.0f, 1.0f, 2, 0);
                break;
            case 9:
                func_80609140(0x1DB, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 10:
                func_80609140(0x1DC, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            }
            actor = D_807FBB40;
        }
    }
    if (0.0f == ((M4Sub4Inner *)((M4Sub4 *)actor->unk4)->unk0)->unk24) {
        actor->unk60 &= ~4;
        actor = D_807FBB40;
    }
    func_806319C4(actor, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_8069E210.s")
#endif

void func_8069E490(s32 arg0, s16 arg1) {
    Actor *actor;

    actor = D_807FBB40;
    func_806A5DF0(arg0, *(s32 *)&actor->unk7C, *(s32 *)&actor->unk80,
                  *(s32 *)&actor->unk84, 0, 0, arg1, (s32)actor);
}

void func_8069E4E0(s16 arg0) {
    Actor *actor;
    s16 i;

    for (i = 0; i < D_807FBB34; i++) {
        actor = D_807FB930[i].actor;
        if ((s32)actor->unk11C == (s32)D_807FBB40) {
            func_8067A70C(D_807FBB40, actor, *(s32 *)&D_807FBB40->unk7C,
                          D_807FBB40->unk80 + (f32)arg0, D_807FBB40->unk84, 2,
                          1);
        }
    }
}

void func_8069E5B8(void) {
    Actor *actor;
    s16 i;

    for (i = 0; i < D_807FBB34; i++) {
        actor = D_807FB930[i].actor;
        if ((s32)actor->unk11C == (s32)D_807FBB40) {
            actorAppendCallback(actor, (s32)D_807FBB40, 0x2000000, 1, 0, NULL);
        }
    }
}

#ifdef NON_MATCHING
s32 func_8069E660(Actor *arg0, f32 arg1, f32 arg2) {
    f32 dx;
    f32 dz;

    dx = arg0->unk80 - 8.0f;
    return dx <= D_807FBB40->unk80 &&
           D_807FBB40->unk80 < arg0->unk80 + arg1 &&
           arg2 > (arg0->unk7C - D_807FBB40->unk7C) *
                      (arg0->unk7C - D_807FBB40->unk7C) +
                  (arg0->unk84 - D_807FBB40->unk84) *
                      (arg0->unk84 - D_807FBB40->unk84) &&
           arg0->unk144 != 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_8069E660.s")
#endif

s32 func_8069E724(s32 arg0) {
    switch (arg0 - 2) {
    case 0:
        return 0xB;
    case 1:
        return 0xE;
    case 3:
    case 4:
    case 5:
        return 0xA;
    case 2:
        return 0xD;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_8069E774.s")

s32 func_8069EF50(s16 arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4) {
    Actor *actor;
    f32 dx;
    f32 dz;

    actor = D_807FBB4C;
    dx = actor->unk7C - arg0;
    dz = actor->unk84 - arg2;
    if (dx * dx + dz * dz < arg4 * arg4 && arg1 <= actor->unk80 &&
        actor->unk80 < arg1 + arg3) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_8069F020.s")

void func_8069F904(Gfx *arg0, Actor *arg1) {
    f32 scale;

    scale = ((M4ActorTail *)arg1)->unkE0;
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504340);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg1->unkE6 & 0xFF) | 0xFFFFFF00);
    func_8068C5A8(arg0, (u16)(arg1->unk15F + 0x61), 0, 2, 0x28, 0x33,
                  (s32)arg1->unk7C, (s32)arg1->unk80, scale, scale, 0, 0.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A438.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A440.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A444.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A44C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_8069FA40.s")
void func_8069FDA0(void) {
    f32 ratio;
    s16 sp22;

    if (!(((M4ActorTail *)D_807FBB40)->unk60 & 0x10)) {
        ((M4ActorTail *)D_807FBB40)->unkEE =
            (s16)((M4ActorTail *)D_807FBB40)->unk160;
    }
    if ((f64)(u32)D_80744478 * 0.5 < ((M4ActorTail *)D_807FBB40)->unk160) {
        ((M4ActorTail *)D_807FBB40)->unk160 -=
            (f64)(u32)D_80744478 * 0.5;
        ratio = (f32)(((M4ActorTail *)D_807FBB40)->unk160 /
                      (f64)(f32)((M4ActorTail *)D_807FBB40)->unkEE);
        ((M4ActorTail *)D_807FBB40)->unkE0 =
            (f32)((f64)ratio * -8.0 + 12.0);
        ((M4ActorTail *)D_807FBB40)->unkE6 = (s16)(255.0f * ratio);
        if (((M4ActorTail *)D_807FBB40)->unk15F >= 0x14 &&
            ((M4ActorTail *)D_807FBB40)->unk15F < 0x1E) {
            renderCallbacksRegister(func_8069F904, D_807FBB40, 3);
        } else {
            renderCallbacksRegister(func_8069FA40, D_807FBB40, 3);
        }
        if (((M4ActorTail *)D_807FBB40)->unk15F == 0 &&
            (s16)(s32)((M4ActorTail *)D_807FBB40)->unk160 == 3) {
            actorSpawn(0x104, 0);
            ((M4ActorTail *)D_807FBB44)->unk160 =
                (f64)((M4ActorTail *)D_807FBB40)->unkEE;
            ((M4ActorTail *)D_807FBB44)->unk15F = D_80750AD4;
            ((M4ActorTail *)D_807FBB44)->unk80 = 80.0f;
            ((M4ActorTail *)D_807FBB44)->unk7C = 640.0f;
            func_80609140((s16)(D_80750AD4 + 0x3F3), 0x7FFF, 63.0f, 1.0f, 0,
                          0);
            return;
        }
        if (((M4ActorTail *)D_807FBB40)->unk15F >= 0x1E &&
            ((M4ActorTail *)D_807FBB40)->unk15F < 0x25 &&
            (s16)(s32)((M4ActorTail *)D_807FBB40)->unk160 == 5) {
            actorSpawn(0x104, 0);
            ((M4ActorTail *)D_807FBB44)->unk160 =
                (f64)((M4ActorTail *)D_807FBB40)->unkEE;
            if (((M4ActorTail *)D_807FBB40)->unk15F == 0x23) {
                ((M4ActorTail *)D_807FBB44)->unk15F = 0x24;
            } else if (((M4ActorTail *)D_807FBB40)->unk15F == 0x24) {
                ((M4ActorTail *)D_807FBB44)->unk15F = 0x25;
            } else {
                ((M4ActorTail *)D_807FBB44)->unk15F = 0x26;
            }
            ((M4ActorTail *)D_807FBB44)->unk80 = 80.0f;
            ((M4ActorTail *)D_807FBB44)->unk7C = 500.0f;
        }
    } else {
        if ((((M4ActorTail *)D_807FBB40)->unk15F & 0xC0) != 0 &&
            (((M4ActorTail *)D_807FBB40)->unk15F & 0x3F) != 0) {
        sp22 = 0x3FC - (((M4ActorTail *)D_807FBB40)->unk15F & 0x3F);
        actorSpawn(0x104, 0);
        ((M4ActorTail *)D_807FBB44)->unk160 =
            (f64)((M4ActorTail *)D_807FBB40)->unkEE;
        ((M4ActorTail *)D_807FBB44)->unk15F =
            (((M4ActorTail *)D_807FBB40)->unk15F & 0xC0) +
            (((M4ActorTail *)D_807FBB40)->unk15F & 0x3F) - 1;
        if (((M4ActorTail *)D_807FBB40)->unk15F & 0x80) {
            sp22 += 2;
        }
        func_80609140(sp22, 0x7FFF, 63.0f, 1.0f, 0, 0);
        ((M4ActorTail *)D_807FBB44)->unk80 = 80.0f;
        ((M4ActorTail *)D_807FBB44)->unk7C = 600.0f;
        }
        actorDespawn(D_807FBB40);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A018C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A02F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A0310.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A0330.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A05D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A05FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A081C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A0864.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A0B74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A0F78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A1008.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A10BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A112C.s")
