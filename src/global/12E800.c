#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern void *D_807FC924;

typedef struct D1S10 {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} D1S10;

typedef struct D1S4 {
    /* 0x00 */ D1S10 *unk0;
} D1S4;

typedef struct D1S174 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[4];
    /* 0x1F8 */ u32 unk1F8;
} D1S174;

typedef struct D1Dc90ViewD {
    /* 0x00 */ Struct807FDC98 *unk0;
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0xE];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 unk18;
} D1Dc90ViewD;

typedef struct D1Dc98ViewD {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[0xA];
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 pad2C[0x1A];
    /* 0x46 */ u16 unk46;
} D1Dc98ViewD;

#define D1DC90D ((D1Dc90ViewD *)D_807FDC90)
#define D1DC98D ((D1Dc98ViewD *)D_807FDC98)
typedef struct D1ActorViewE {
    /* 0x00 */ u8 pad0[0xAC];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0x10];
    /* 0xC0 */ f32 unkC0;
} D1ActorViewE;

#define D1AE ((D1ActorViewE *)D_807FBB40)

extern void *D_807FDCA0;
extern u8 D_807444EC;
extern s32 D_8076A0A8;
extern u8 D_807FBB85;
void func_80614EBC(Actor *, s32);
void func_8067AC38(void);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxStopSlotSound(Actor *, s32);
void collisionClearFlags(void);

void func_80729B00(void) {
    D_807FDC90 = D_807FBB40->unk174;
    D_807FDC94 = D1DC90D->unk4;
    D_807FDC9C = (Struct807FDC9C *)(D_807FDC98 = D1DC90D->unk0);
    D_807FDCA0 = D1DC98D->unk1C;
    D_807FDC90->unk18++;
    if (D_807FBB40->unk60 & 0x20000000) {
        if (D_807FBB40->unk154 != 0x37 && D_807FBB40->unk154 != 0x36) {
            if (((D1S4 *)D_807FDC94->unk4)->unk0->unk10 != D1DC90D->unk16) {
                D_807FBB40->unk60 &= ~0x20000000;
            }
        }
    }
    if (D_807FBB40->unk5C & 2) {
        if ((D_807444EC == 1 && (D1DC98D->unk46 & 8)) || (D_807FDC94 != NULL && D_807FDC94->unk154 == 0x42)) {
            if (D_807FBB40->unk154 >= 0x23 && D_807FBB40->unk154 < 0x36) {
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk154 = 0x3A;
                D_807FBB40->unk155[0] = 0;
            }
        }
        if (D_807FBB70.unk1B) {
            if (D_807FBB40->unk154 != 0x39) {
                if (D1DC98D->unk46 & 0x800) {
                    D_807FBB70.unk15 = 1;
                } else {
                    func_8067AC38();
                    D_807FBB40->unk138 = 0;
                    D_807FBB40->unk60 &= 0xFFFD7FFF;
                    D_807FBB40->unk144 = 1;
                    D_807FBB40->unk154 = 0x39;
                    D_807FBB40->unk155[0] = 0;
                    func_80614EBC(D_807FBB40, D1DC98D->unk2A);
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0x14);
                    D1AE->unkC0 = -220.0f;
                }
            }
        }
        if ((D1DC98D->unk46 & 0x4000) && (D_807FBB40->unk6A & 4)) {
            if (D_807FBB40->unk80 + (f32)(u32)D_807FBB40->unk15E < D1AE->unkAC) {
                D_807FBB70.unk15 = 1;
            }
        }
        if (D_8076A0A8 == 0x30) {
            if (D_807FDC94->unk5C & 1) {
                if ((((D1S174 *)D_807FDC94->unk174)->unk1F0 ^ ((D1S174 *)D_807FDC94->unk174)->unk1F8) & 0x100000) {
                    sfxStopSlotSound(D_807FBB40, 0);
                    D_807FBB40->unk154 = 0;
                    D_807FBB40->unk155[0] = 0;
                    D_807FBB85 = 1;
                }
            }
        }
    }
    if (D_807FBB40->unk58 != 0xAF && D_807FBB40->unk154 == 0x37 && D_807FBB40->unk138 != 0) {
        D_807FBB40->unk138 = 0;
        if (!D_807FBB70.unk1B) {
        }
    }
    collisionClearFlags();
}

typedef struct D1ActorView {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ f32 unkC8;
} D1ActorView;

#define D1A ((D1ActorView *)D_807FBB40)

void func_80729E6C(void) {
    D1A->unkC0 = D1A->unkC0 + D1A->unkC4;
    if (D1A->unkC0 < D1A->unkC8) {
        D1A->unkC0 = D1A->unkC8;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_80729EB0.s")

typedef struct D1Tbl8075EB80 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
} D1Tbl8075EB80; // size = 0x18

typedef struct D1Dc98ViewC {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[0x10];
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} D1Dc98ViewC;

#define D1DC98C ((D1Dc98ViewC *)D_807FDC98)

extern D1Tbl8075EB80 D_8075EB80[];
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void func_8072A450(void) {
    u8 a;
    u8 b;
    u8 c;
    D1Tbl8075EB80 *e;
    ActorSub4 *sub;

    if (!(D_807FBB40->unk60 & 0x1000000) && (D_807FBB40->unk60 & 4)) {
        if (!(D1DC98C->unk46 & 0x100)) {
            a = (u32)((f64)D_807FBB40->unk128 * 0.7);
            sub = D_807FBB40->unk4;
            e = &D_8075EB80[D1DC98C->unk44];
            b = (u32)(sub->unk34 * (u32)e->unk14 * D1DC98C->unk30);
            c = (u32)(sub->unk3C * (u32)e->unk15 * D1DC98C->unk30);
            func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, b, c, 1, 0x12C, a, D_807FBB40->unkE6, 1.0f);
        }
    }
}

typedef struct D1Sub4View {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x28];
    /* 0x64 */ u16 unk64;
} D1Sub4View;

typedef struct D1ActorView3 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ D1Sub4View *unk4;
    /* 0x08 */ u8 pad8[0x54];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0x1E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x24];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0x10];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x2C];
    /* 0xF0 */ s16 unkF0;
    /* 0xF2 */ u8 padF2[0x6C];
    /* 0x15E */ u8 unk15E;
} D1ActorView3;

#define D1A3 ((D1ActorView3 *)D_807FBB40)
#define D1A3_154 (*(u8 *)((u8 *)D_807FBB40 + 0x154))

extern u8 D_80720120[];
extern u16 D_80744508;
s32 func_80666A94();
s32 func_80666AA0();
void func_80714CC0(void *, f32, f32, f32, f32);

void func_8072A714(void) {
    if (D1A3->unk5C & 2) {
        if (func_80666A94() || func_80666AA0()) {
            if (func_80666AA0()) {
                func_80714CC0(&D_80720120, D1A3->unk4->unk38 * 6.66666666999999968, D1A3->unk7C, D1A3->unk80, D1A3->unk84);
            }
            D1A3_154 = 0x40;
            D_80744508++;
        }
    }
}

typedef struct D1Dc90View {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 pad0E[0xC];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x1C];
    /* 0x38 */ u8 unk38;
} D1Dc90View;

#define D1DC90 ((D1Dc90View *)D_807FDC90)

typedef struct D1ActorView2 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
} D1ActorView2;

#define D1A2 ((D1ActorView2 *)D_807FBB40)

void func_8072A7DC(void) {
    if (!(D1DC90->unk1A & 0x40)) {
        if (D1A2->unk7C == D1A2->unk88 && D1A2->unk84 == D1A2->unk90) {
            D1DC90->unk38++;
            if (D1DC90->unk38 >= 0x1F) {
                D1DC90->unk1A |= 0x40;
            }
        } else {
            D1DC90->unk38 = 0;
        }
    }
}

f32 func_80612794(s16);
u32 func_8072AB74(u8, f32, f32, u16, f32);

void func_8072A86C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4) {
    D1A3->unkC0 = func_80612794(D1A3->unkF0) * -arg3;
    func_8072AB74(arg0, arg1, arg2, (arg4 & 0xFFFF) | 0x1080, 0.5 * (u32)D1A3->unk15E);
}

typedef struct D1ActorView4 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x60];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[6];
    /* 0xF0 */ s16 unkF0;
} D1ActorView4;

#define D1A4 ((D1ActorView4 *)D_807FBB40)

f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
s16 func_806CC190(s16, s16, f32);

void func_8072A920(s16 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, f32 arg6, f32 arg7, u16 arg8) {
    D1A4->unkE8 = func_806CC190(D1A4->unkE8, (s16)(s32)(mathCalculatePitchAngle(arg2, arg3, arg4, D1A4->unk7C, D1A4->unk80, D1A4->unk84, arg5) * 2048.0 / 3.14159274101257324), arg6);
    D1A4->unkF0 = func_806CC190(D1A4->unkF0, (s16)(s32)(mathCalculatePitchAngle(arg2, (f32)arg1 + arg3, arg4, D1A4->unk7C, D1A4->unk80, D1A4->unk84, arg5) * 2048.0 / 3.14159274101257324), arg6);
    func_8072A86C(arg0, arg2, arg4, arg7, arg8);
}

typedef struct D1Dc9cView {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
} D1Dc9cView;

#define D1DC9C ((D1Dc9cView *)D_807FDC9C)

s32 func_80611A44(void);

void func_8072AA80(void) {
    s16 lim;
    s32 rnd;
    s32 base;

    if (D1DC9C->unkA != 0) {
        lim = D1DC9C->unk6 + D1A3->unk15E + D1DC9C->unkA;
    } else {
        lim = (s32)(s16)D1A3->unkAC - D1A3->unk15E;
    }
    rnd = (func_80611A44() >> 15) % 0x7FFF;
    base = D1DC9C->unk6 + D1A3->unk15E;
    D1DC90->unkC = rnd % (lim - base + 1) + base;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072AB74.s")

typedef struct D1Unk174 {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
} D1Unk174;

void func_8072B324(Actor *arg0, s32 arg1) {
    D1Unk174 *s = arg0->unk174;
    s->unk26 = arg1;
}

typedef struct D1Dc98ViewB {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} D1Dc98ViewB;

typedef struct D1Sub4B {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ f32 unk48;
} D1Sub4B;

typedef struct D1ActorViewB {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ D1Sub4B *unk4;
    /* 0x08 */ u8 pad8[0x62];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x4C];
    /* 0xB8 */ f32 unkB8;
} D1ActorViewB;

#define D1AB ((D1ActorViewB *)D_807FBB40)
#define D1DC98B ((D1Dc98ViewB *)D_807FDC98)

void func_80614D00(void *, f32, f32);

void func_8072B330(u16 arg0) {
    f32 t;

    t = (D1AB->unkB8 * D1DC98B->unk38 > 3.0) ? 3.0 : D1AB->unkB8 * D1DC98B->unk38;
    if (D1AB->unk6A & 4) {
        t *= 0.5;
    }
    if (!(D1DC98B->unk3C < t)) {
        t = D1DC98B->unk3C;
    }
    if (!((arg0 & 0x400) && t < 1.0)) {
        if (!(arg0 & 0x200) && t != D1AB->unk4->unk48) {
            func_80614D00(D_807FBB40, t, 0.0f);
        }
    }
}

typedef struct D1Dc90ViewB {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xD];
    /* 0x35 */ u8 unk35;
} D1Dc90ViewB;

#define D1DC90B ((D1Dc90ViewB *)D_807FDC90)

extern u32 D_8076A064;
void func_8072DAA4();

void func_8072B438(u16 arg0) {
    s32 spd;
    f32 tgt;

    spd = D1DC90B->unk26;
    if (D1AB->unkB8 < -60.0f) {
        if ((D1AB->unk6A & 1) && (D_8076A064 % 5) == 0) {
            func_8072DAA4();
        }
    }
    tgt = spd;
    if (tgt != D1AB->unkB8) {
        if (D1AB->unkB8 < tgt) {
            D1AB->unkB8 = (tgt < D1AB->unkB8 + (u32)D1DC90B->unk35) ? tgt : D1AB->unkB8 + (u32)D1DC90B->unk35;
        } else if (tgt < D1AB->unkB8) {
            D1AB->unkB8 = (D1AB->unkB8 - (u32)D1DC90B->unk35 < tgt) ? tgt : D1AB->unkB8 - (u32)D1DC90B->unk35;
        }
    }
    func_8072B330(arg0);
}

void func_8072B59C(u8 arg0, s16 arg1, s32 arg2) {
    D1A3_154 = arg0;
    *((u8 *)D_807FBB40 + 0x155) = 0;
    if (arg2 != D1A3->unk4->unk64) {
        func_80614EBC(D_807FBB40, arg2);
    }
    func_8072B324(D_807FBB40, arg1);
}

void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
f32 func_80612790(s16);

void func_8072B608(void) {
    u32 phase;
    f32 x;
    f32 base;

    func_80612794((s16)(((D_8076A064 % 0xFFF) * 4) % 0xFFF));
    func_80612790((s16)(((D_8076A064 % 0xFFF) * 4) % 0xFFF));
    phase = (D_8076A064 * 4) % 150;
    base = 100.0f;
    if (phase > 75) {
        x = (f32)(phase - 75) + base;
    } else {
        x = base + 50.0 - phase;
    }
    lightAdd(D1A3->unk7C, D1A3->unk80 + 10.0f, D1A3->unk84, 0.0f, 0.0f, 0.0f, x, 0, 0xFF, 0xFF, 0xFF);
}

typedef struct D1Dc98View {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} D1Dc98View;

#define D1DC98 ((D1Dc98View *)D_807FDC98)

void func_8072B79C(s16 arg0, s16 arg1, s16 arg2) {
    D1DC98->unk26 = arg0;
    D1DC98->unk28 = arg1;
    D1DC98->unk2A = arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072B7CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072C670.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072C870.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072C918.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072CFE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072D08C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072D13C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072D714.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072D99C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072D9D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DA60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DAA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DB68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DC7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DCF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DE10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DE44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072DEA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E02C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E0A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E1A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E22C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E2B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E320.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/12E800/func_8072E54C.s")
