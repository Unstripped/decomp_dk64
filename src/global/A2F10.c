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
s32 actorDespawn(Actor *);
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
void func_806319C4(void *, s32);

void func_8069E210(void) {
    Actor *actor;
    Actor **p;
    s16 i;

    actor = D_807FBB40;
    p = &D_807FBB40;
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
        actor = *p;
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

int func_8069E660(Actor *arg0, f32 arg1, f32 arg2) {
    return arg0->unk80 - 8.0f <= D_807FBB40->unk80 &&
           D_807FBB40->unk80 < arg0->unk80 + arg1 &&
           arg2 > (arg0->unk7C - D_807FBB40->unk7C) *
                      (arg0->unk7C - D_807FBB40->unk7C) +
                  (arg0->unk84 - D_807FBB40->unk84) *
                      (arg0->unk84 - D_807FBB40->unk84) &&
           arg0->unk144 != 1;
}

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

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M5_A2F10Quad;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M5_A2F10Vec3;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 unkE;
    /* 0x00F */ u8 unkF;
    u8 pad10[0x1F0];
    s16 unk200;
} M5_A2F10Sub;

typedef struct {
    /* 0x000 */ struct M5_A2F10Model *unk0;
    /* 0x004 */ struct M5_A2F10Sub4 *unk4;
    /* 0x008 */ void *unk8;
    /* 0x00C */ u8 padC[0x50];
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0xC];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ f32 unkBC;
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x20];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0xC];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x1F];
    /* 0x11C */ struct M5_A2F10SpActor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ M5_A2F10Vec3 *unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[6];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x10];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[1];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0xA];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 pad16D[7];
    /* 0x174 */ M5_A2F10Sub *unk174;
} M5_A2F10Actor;

typedef struct M5_A2F10Sub4 {
    /* 0x000 */ u8 pad0[0x24];
    /* 0x024 */ M5_A2F10Quad *unk24;
    /* 0x028 */ u8 pad28[0xC];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
} M5_A2F10Sub4;

typedef struct M5_A2F10Model {
    /* 0x000 */ u8 pad0[0x20];
    /* 0x020 */ u8 unk20;
} M5_A2F10Model;

typedef struct {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xC];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x20];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x9A];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xE];
    /* 0x156 */ u8 unk156;
} M5_A2F10Target;

typedef struct M5_A2F10SpActor {
    /* 0x000 */ u8 pad0[8];
    /* 0x008 */ void *unk8;
    /* 0x00C */ u8 padC[0x48];
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x20];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x20];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x9A];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[9];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[0x14];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 pad178[0x88];
    /* 0x200 */ s16 unk200;
} M5_A2F10SpActor;

s32 func_80611A44(void);
void func_806319C4(void *, s32);
void func_80665564(Actor *, f32);
void func_8067ACB4(Actor *);
void actorApplyVelocity(Actor *);
extern f32 D_80750394;

#define M5_A2F10_ACTOR ((M5_A2F10Actor *) D_807FBB40)

void func_806A018C(void) {
    M5_A2F10Sub *sub;
    s32 pad;

    sub = M5_A2F10_ACTOR->unk174;
    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unkB8 = M5_A2F10_ACTOR->unk124->unk0;
        M5_A2F10_ACTOR->unkEE = M5_A2F10_ACTOR->unk124->unk4;
        M5_A2F10_ACTOR->unkC0 = M5_A2F10_ACTOR->unk124->unk8;
        M5_A2F10_ACTOR->unk144 = 1;
        sub->unk0 = (func_80611A44() >> 15) % 0x46;
        sub->unk4 = (func_80611A44() >> 15) % 0xC8;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    M5_A2F10_ACTOR->unkC0 += D_80750394;
    M5_A2F10_ACTOR->unkE8 += sub->unk4;
    M5_A2F10_ACTOR->unkE4 += sub->unk0;
    if (M5_A2F10_ACTOR->unkFC != 0 || ((M5_A2F10_ACTOR->unk6A & 1) && !(M5_A2F10_ACTOR->unk6C & 1))) {
        actorDespawn(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806A02F0(void) {
    func_806A018C();
}

void func_806A0310(void) {
    func_806A018C();
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x24];
} M5_A2F10Pos;

s32 func_8061CB50(void);
void billboardSetFlags(s32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8061F0B0(void *, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_8071496C(s16);
void func_807149B8(s32);
void func_8071498C(void *);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8071BB14(void);
extern void *D_807F5D10;
extern u8 D_807FBD70;
extern f32 D_80750398;
extern u8 D_80720BE8;

void func_806A0330(void) {
    M5_A2F10Pos pos;
    s32 i;

    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unk144 = 0x1C;
        M5_A2F10_ACTOR->unkC0 = 0.0f;
        M5_A2F10_ACTOR->unk12A = 0x7D0;
        M5_A2F10_ACTOR->unkA4 = 99999.0f;
        func_80665564(D_807FBB40, 0.0f);
    }
    if (func_8061CB50() != 0) {
        M5_A2F10_ACTOR->unk132 = 2;
    } else {
        M5_A2F10_ACTOR->unk132 = 1;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    M5_A2F10_ACTOR->unkC0 += D_80750398;
    if (M5_A2F10_ACTOR->unkA4 != 99999.0f) {
        billboardSetFlags(1);
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x18, 0x18, 1, 0x96, 0xB4, 0, 1.0f);
    } else {
        actorDespawn(D_807FBB40);
    }
    if (D_807FBD70 == 4 || M5_A2F10_ACTOR->unkFC != 0
        || ((M5_A2F10_ACTOR->unk6A & 1) && !(M5_A2F10_ACTOR->unk6C & 1))) {
        func_8061F0B0(D_807F5D10, 0xF, 0xF);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x162, 0xE1, 0x3C, 1);
        for (i = 1; i != 7; i++) {
            actorGetNodePos(D_807FBB40, i, &pos.unk8, &pos.unk4, &pos.unk0);
            func_8071496C(i);
            func_807149B8(1);
            func_8071498C(func_8071BB14);
            func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
            func_80714CC0(&D_80720BE8, 1.5f, pos.unk8, pos.unk4, pos.unk0);
        }
        actorDespawn(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}


void func_806A05D4(void) {
    func_806319C4(D_807FBB40, 0);
}

void func_806A05FC(void) {
    M5_A2F10Sub *sub;
    s32 temp;
    s32 v;

    sub = M5_A2F10_ACTOR->unk11C->unk174;
    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unk60 &= 0xFFFF7FFF;
        M5_A2F10_ACTOR->unk128 = 0xFF;
        M5_A2F10_ACTOR->unk60 |= 0x800000;
        M5_A2F10_ACTOR->unk16A = 0xFF;
        M5_A2F10_ACTOR->unk16B = 0xFF;
        M5_A2F10_ACTOR->unk16C = 0xFF;
        M5_A2F10_ACTOR->unk160 = (f64) M5_A2F10_ACTOR->unk11C->unk15E * 0.1 * 0.15;
    }
    M5_A2F10_ACTOR->unk7C = M5_A2F10_ACTOR->unk11C->unk7C;
    M5_A2F10_ACTOR->unk80 = M5_A2F10_ACTOR->unk11C->unk80;
    M5_A2F10_ACTOR->unk84 = M5_A2F10_ACTOR->unk11C->unk84;
    if (M5_A2F10_ACTOR->unk128 & 8) {
        M5_A2F10_ACTOR->unk4->unk34 = (M5_A2F10_ACTOR->unk160 * 0.8 - M5_A2F10_ACTOR->unk4->unk34) * 0.3 + M5_A2F10_ACTOR->unk4->unk34;
    } else {
        M5_A2F10_ACTOR->unk4->unk34 = (M5_A2F10_ACTOR->unk160 * 1.2 - M5_A2F10_ACTOR->unk4->unk34) * 0.3 + M5_A2F10_ACTOR->unk4->unk34;
    }
    M5_A2F10_ACTOR->unk4->unk3C = M5_A2F10_ACTOR->unk4->unk34;
    temp = sub->unk200;
    v = temp > 0 ? temp : 0;
    if (v < 0xFF) {
        v = temp > 0 ? temp : 0;
        M5_A2F10_ACTOR->unk128 = v;
    } else {
        M5_A2F10_ACTOR->unk128 = 0xFF;
    }
    if (M5_A2F10_ACTOR->unk128 == 0 || M5_A2F10_ACTOR->unk11C->unk154 != 0x7C) {
        actorDespawn(D_807FBB40);
    } else {
        func_806319C4(D_807FBB40, 0);
    }
}

s32 func_80613448(Actor *);

void func_806A081C(Actor *arg0) {
    actorSpawn(0x6A, func_80613448(arg0));
    D_807FBB44->unk11C = (s32) arg0;
    arg0->unk6A |= 0x800;
}

u8 func_80665AAC(Actor *);
s32 actorIsActive(Actor *);
s32 actorTableContains(Actor *);
void func_806131D4(void *, s16);
extern u8 D_807444FC;

void func_806A0864(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    M5_A2F10Sub *sub;
    Mtx *dst;
    s32 i;

    sub = M5_A2F10_ACTOR->unk174;
    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unk60 |= 0x8100000;
        M5_A2F10_ACTOR->unk60 &= 0xFFFF7FFF;
        func_806131D4(D_807FBB40, func_80613448(D_807FBB40));
        sub->unk4 = M5_A2F10_ACTOR->unk11C->unk54;
        sub->unk0 = (s32) M5_A2F10_ACTOR->unk11C;
        sub->unk8 = M5_A2F10_ACTOR->unk11C->unk58;
    }
    if (!actorTableContains((Actor *) sub->unk0) || sub->unk4 != M5_A2F10_ACTOR->unk11C->unk54) {
        actorDespawn(D_807FBB40);
        return;
    }
    if (!(func_80665AAC((Actor *) sub->unk0) && sub->unk8 == M5_A2F10_ACTOR->unk11C->unk58
          && actorIsActive((Actor *) sub->unk0) && (((M5_A2F10Target *) sub->unk0)->unk68 & 0x40))) {
        actorDespawn(D_807FBB40);
        ((M5_A2F10Target *) sub->unk0)->unk6A &= 0xF7FF;
        return;
    }
    {
        M5_A2F10_ACTOR->unk128 = 0xFF;
        M5_A2F10_ACTOR->unk146 = ((M5_A2F10Target *) sub->unk0)->unk146;
        M5_A2F10_ACTOR->unk7C = ((M5_A2F10Target *) sub->unk0)->unk7C;
        M5_A2F10_ACTOR->unk80 = ((M5_A2F10Target *) sub->unk0)->unk80;
        M5_A2F10_ACTOR->unkA8 = ((M5_A2F10Target *) sub->unk0)->unkA8;
        M5_A2F10_ACTOR->unk84 = ((M5_A2F10Target *) sub->unk0)->unk84;
        M5_A2F10_ACTOR->unk60 |= 0x200;
        M5_A2F10_ACTOR->unk8 = ((void **) ((u8 *) M5_A2F10_ACTOR->unk4 + 0x14))[D_807444FC];
        memcpy(M5_A2F10_ACTOR->unk8, M5_A2F10_ACTOR->unk11C->unk8, M5_A2F10_ACTOR->unk0->unk20 << 6);
        guMtxIdentF(mtx1);
        mtx1[1][1] = -1.0f;
        guTranslateF(mtx2, -M5_A2F10_ACTOR->unk7C, -M5_A2F10_ACTOR->unkA8, -M5_A2F10_ACTOR->unk84);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, M5_A2F10_ACTOR->unk7C, M5_A2F10_ACTOR->unkA8, M5_A2F10_ACTOR->unk84);
        dst = M5_A2F10_ACTOR->unk8;
        for (i = 0; i < M5_A2F10_ACTOR->unk0->unk20; i++) {
            guMtxL2F(mtx3, dst);
            guMtxCatF(mtx3, mtx1, mtx3);
            guMtxCatF(mtx3, mtx2, mtx3);
            guMtxF2L(mtx3, dst);
            dst++;
        }
    }
}


void func_80663BE8(void *);

void func_806A0B74(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    M5_A2F10Sub *sub;
    Mtx *dst;
    s32 i;

    sub = M5_A2F10_ACTOR->unk174;
    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unk60 |= 0x8100000;
        M5_A2F10_ACTOR->unk60 &= 0xFFFF7FFF;
        func_806131D4(D_807FBB40, func_80613448(D_807FBB40));
        sub->unk4 = M5_A2F10_ACTOR->unk11C->unk54;
        sub->unk0 = (s32) M5_A2F10_ACTOR->unk11C;
        sub->unk8 = M5_A2F10_ACTOR->unk11C->unk58;
    }
    if (!actorTableContains((Actor *) sub->unk0) || sub->unk4 != M5_A2F10_ACTOR->unk11C->unk54) {
        actorDespawn(D_807FBB40);
        func_80663BE8(D_807FBB40);
        return;
    }
    if (!(sub->unk8 == M5_A2F10_ACTOR->unk11C->unk58 && actorIsActive((Actor *) sub->unk0)
          && (((M5_A2F10Target *) sub->unk0)->unk68 & 0x80))) {
        actorDespawn(D_807FBB40);
        func_80663BE8(D_807FBB40);
        ((M5_A2F10Target *) sub->unk0)->unk156--;
        return;
    }
    M5_A2F10_ACTOR->unk128 = sub->unkF;
    M5_A2F10_ACTOR->unk146 = M5_A2F10_ACTOR->unk11C->unk146;
    M5_A2F10_ACTOR->unk7C = M5_A2F10_ACTOR->unk11C->unk7C;
    M5_A2F10_ACTOR->unk80 = M5_A2F10_ACTOR->unk11C->unk80;
    M5_A2F10_ACTOR->unkA8 = M5_A2F10_ACTOR->unk11C->unkA8;
    M5_A2F10_ACTOR->unk84 = M5_A2F10_ACTOR->unk11C->unk84;
    M5_A2F10_ACTOR->unk60 |= 0x200;
    M5_A2F10_ACTOR->unk8 = ((void **) ((u8 *) M5_A2F10_ACTOR->unk4 + 0x14))[D_807444FC];
    memcpy(M5_A2F10_ACTOR->unk8, M5_A2F10_ACTOR->unk11C->unk8, M5_A2F10_ACTOR->unk0->unk20 << 6);
    guMtxIdentF(mtx1);
    if (sub->unkE & 1) {
        mtx1[0][0] = -1.0f;
        guTranslateF(mtx2, -sub->unkC, 0.0f, 0.0f);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, sub->unkC, 0.0f, 0.0f);
    } else {
        mtx1[2][2] = -1.0f;
        guTranslateF(mtx2, 0.0f, 0.0f, -sub->unkC);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, 0.0f, 0.0f, sub->unkC);
    }
    dst = M5_A2F10_ACTOR->unk8;
    for (i = 0; i < M5_A2F10_ACTOR->unk0->unk20; i++) {
        guMtxL2F(mtx3, dst);
        guMtxCatF(mtx3, mtx1, mtx3);
        guMtxCatF(mtx3, mtx2, mtx3);
        guMtxF2L(mtx3, dst);
        dst++;
    }
    {
        f32 sp58;
        f32 sp54;
        f32 sp50;

        guMtxXFMF(mtx1, M5_A2F10_ACTOR->unk7C, M5_A2F10_ACTOR->unk80, M5_A2F10_ACTOR->unk84, &sp58, &sp54, &sp50);
        guMtxXFMF(mtx2, sp58, sp54, sp50, &M5_A2F10_ACTOR->unk7C, &M5_A2F10_ACTOR->unk80, &M5_A2F10_ACTOR->unk84);
    }
}


void animSetLoopLimit(void *, s32, s32);
void animSetFinished(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s32, f32);

void func_806A0F78(void *arg0, u8 arg1, u8 arg2) {
    animSetLoopLimit(arg0, 0, 1);
    animSetFinished(arg0, 0, 1);
    animSetFrameAndSubframe(arg0, 0, arg1, 0.0f);
    animSetLoopLimit(arg0, 1, 1);
    animSetFinished(arg0, 1, 1);
    animSetFrameAndSubframe(arg0, 1, arg2, 0.0f);
}


void func_806A1008(u8 arg0, u8 arg1) {
    Actor *actor;
    s16 i;

    for (i = 0; i < D_807FBB34; i++) {
        actor = D_807FB930[i].actor;
        if (actor->unk58 == 0x94 && actor->unk15F / 3 == arg0) {
            actor->unk154 = arg1;
            actor->unk155[0] = 0;
        }
    }
}

typedef struct {
    f32 *unk0;
} M5_A2F10Mat;

void func_806A10BC(M5_A2F10Mat *arg0) {
    M5_A2F10Quad *dst;
    s16 i;

    dst = M5_A2F10_ACTOR->unk4->unk24;
    for (i = 0; i < 7; i++) {
        dst->unkC = (f64) arg0->unk0[i * 0x34 + M5_A2F10_ACTOR->unk168];
        dst++;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/func_806A112C.s")
