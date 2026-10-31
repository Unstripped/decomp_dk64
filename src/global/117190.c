#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern void *D_807FC924;
extern s32 D_8076A0A8;
extern u32 D_807FBB68;
extern u8 D_80755314;
extern u8 D_80755318;

extern s32 flagCountRange(s32, s32, s32);
extern s8 D_8075536C;
extern s32 D_80755338;
extern s32 D_8075533C;
extern u8 D_80755350;
extern s8 D_80755330;
extern s8 D_80750754;




void func_805FF378(s32, s32);

void func_80712490(s32 arg0, s32 arg1, u8 arg2) {
    func_805FF378(arg0, arg1);
    D_80755318 = arg2;
}

void func_805FF158(s32);
s32 func_80712798(void);

void func_807124B8(s32 arg0, s32 arg1, u8 arg2) {
    if (func_80712798() == 0) {
        func_805FF158(0);
        func_80712490(arg0, D_8075536C, arg2);
        D_80755338 = 1;
        D_8075533C = arg1;
        D_8075536C = 0;
    }
}

void func_80712524(s32 arg0, s32 arg1) {
    func_807124B8(arg0, arg1, D_80755318);
}

s32 func_80712548(void) {
    return flagCountRange(0x1FD, 0x28, 0) + 0xA;
}

typedef struct R117gTimedState {
    u64 time;
    s32 unk8;
    s32 duration;
    u8 active;
    u8 index;
} R117gTimedState;

extern R117gTimedState D_80755340;
extern u16 D_80755358[];

void func_80712574(void) {
    u32 i;
    s32 found = 0;

    D_80755340.active = 1;
    D_80755340.index = 0;
    D_80755340.time = osGetTime();
    D_80755340.duration = func_80712548() * 60;
    for (i = 0; (i < 10) && (found == 0); i++) {
        if (D_80755358[i] < D_80755340.duration) {
            D_80755340.index = i;
            found = 1;
        }
    }
}

void func_8071261C(void) {
    D_80755350 = 0;
}

s32 func_80712628(void) {
    return D_80755350;
}

void func_80712634(s32 arg0, s32 arg1) {
    func_807124B8(arg0, arg1, 0xB);
    D_80755330 = 0;
}

s32 func_80712658(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 0xB;
    if (var_v0 == 0) {
        return D_80755318 == 0xB;
    }
}

void func_8071268C(void) {
    if (D_80755314 == 0xB) {
        D_80755330 = 1;
    }
}

extern u8 D_807FC950[][0x5E];
extern s8 D_8074E77C;

void func_807126B0(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s8 arg4, s8 arg5, s8 arg6) {
    s32 i;

    D_8074E77C = arg2;
    D_807FC950[8][0xC] = arg6;
    D_807FC950[8][0xB] = arg6 * 4;
    for (i = 0; i < 5; i++) {
        D_807FC950[i][0] = arg3;
        D_807FC950[i][1] = arg4;
        D_807FC950[i][4] = arg5;
    }
    func_80712490(arg0, arg1, 12);
}

void func_80712774(s32 arg0) {
    func_80712490(arg0, 0, 0xD);
}

s32 func_80712798(void) {
    return D_80755314 != D_80755318;

}
void func_805FFFC8(void);
void flagSet(s32, s32, s32);

void func_807127B4(void) {
    func_805FFFC8();
    flagSet(0x314, 1, 0);
    func_807124B8(0x1C, 0x17, 7);
}

void func_807127F4(s32 arg0) {
    u8 temp;

    if (arg0 == 0) {
        temp = 0xA;
    } else {
        temp = 0xE;
    }
    func_807124B8(0x99, 0xB, temp);
    D_80750754 = -2;
}

typedef struct R117d2MenuObject {
    u8 unk0[0x155];
    u8 unk155;
} R117d2MenuObject;

extern s32 D_807FBB64;
extern u8 D_807FC928;
void healthRefill(u8);
s32 func_805FF800(s32 *, s32 *);
void func_80026D40(void *);
void func_805FF1B0(s32);

void func_80712830(R117d2MenuObject *arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 pad;
    s32 sp20;
    s32 sp1C;

    healthRefill((u8) arg1);
    if (arg1 == 0) {} // FAKE: keeps arg1 in a1 with an eager restore after healthRefill
    if (D_807FBB64 & 1) {
        arg0->unk155++;
        if (D_807FBB68 & 2) {
            flagSet(0x5C, 1, 2);
            var_a0 = 0x22;
            var_a1 = 0xC;
        } else {
            if (D_8076A0A8 == 0x3C) {
                var_a0 = 0x3E;
                var_a1 = 1;
            } else {
                var_a0 = 0x2A;
                var_a1 = 2;
            }
        }
        func_805FF378(var_a0, var_a1);
        return;
    }
    if (D_807FBB64 & 0x400) {
        arg0->unk155++;
        func_805FF800(&sp20, &sp1C);
        func_805FF378(sp20, sp1C);
        return;
    }
    if (D_807FC928 >= 2) {
        func_80026D40(arg0);
        return;
    }
    func_805FF1B0(arg1);
}

extern u16 D_80755308;
extern u8 D_8075530C;
extern u8 D_80755310;

void func_80712944(OSContPad *arg0) {
    s32 i;

    controllerGetReadData();
    for (i = 0; i < 4; i++) {
        arg0[i].stick_x &= D_8075530C;
        arg0[i].stick_y &= D_80755310;
        arg0[i].button &= D_80755308;
    }
}
extern u8 D_80755324;


extern u64 D_807445B8;
extern u64 D_807445C0;
extern s8 D_80746B60;
extern u32 D_807FBB60;
extern s32 D_80755320;

void func_8060B6CC(void);
void setRandomSeed(u32);

void func_80712A40(void) {
    u64 elapsed;

    func_8060B6CC();
    if ((D_80755318 == 3) || (D_80755318 == 4)) {
        setRandomSeed(0x8E32B6F7U);
        D_80746B60 = 1;
    } else {
        setRandomSeed((u32)osGetTime());
        D_80746B60 = 0;
    }
    D_8075530C = 0;
    D_80755310 = 0;
    D_80755314 = D_80755318;
    D_80755324 = 0;
    D_80755320 = 0;
    if (D_807FBB60 & 2) {
        elapsed = osGetTime() - D_807445C0;
        D_807445B8 += elapsed;
        if (D_80755340.active != 0) {
            D_80755340.time += elapsed;
        }
    }
}

extern u8 D_80755328;
extern u8 D_80750AC0;
extern u16 D_8075531C;
extern u16 D_807ECD66;
extern u8 D_8075E5C0[];

void func_8060B750(s32);
s32 func_8060B7C4(void);

void func_80712B80(void) {
    if (D_80755318 == 3) {
        func_8060B750(D_8075E5C0[D_80755328 * 4]);
        D_8074E77C = func_8060B7C4();
    }
}

typedef struct R117iPlayerView {
    s32 unk0;
    s32 unk4;
} R117iPlayerView;

extern u16 D_8075E5C2[];

extern u8 D_807467CC;
extern u8 D_8076A0AB;
extern u8 D_8075532C;
extern s32 D_80755334;
extern s32 D_807552EC;
extern Mtx D_807FDAC0;
s32 flagGet(s32, s32);
s32 func_805FF030(u8, s32);
s32 func_8060B49C(s32, s32);
void eepromInit(void);
void func_80712574(void);
void eepromSavePlayerData(void);
void actorSpawn(s32, s32);

void func_80712BD4(void) {
    u8 blocked;

    blocked = flagGet(0x302, 0);
    D_80755334 = 0;
    D_80755330 = 0;
    if (D_807467CC == 0) {
        eepromInit();
    }
    if (func_805FF030(D_8076A0AB, 1) == 8) {
        if ((D_807FBB68 & 2) == 0) {
            if (D_8076A0A8 != 0xD6) {
                if (func_80712628() == 0) {
                    if (blocked == 0) {
                        func_80712574();
                    }
                }
            }
        }
    }
    guScale(&D_807FDAC0, 0.5f, 0.5f, 1.0f);
    switch (D_80755314) {
    case 0:
        D_8075531C = 0x708;
        D_80755308 = 0;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 1:
        D_8075531C = 0x708;
        D_80755308 = 0x1000;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 2:
        D_8075531C = 0x1644;
        D_80755308 = 0x1000;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 3:
        D_8075532C++;
        D_8075531C = func_8060B49C(((R117iPlayerView *)D_807FC924)->unk4, D_8075E5C0[D_80755328 * 4]);
        if (D_8075531C < *(u16 *) ((u8 *) D_8075E5C2 + D_80755328 * 4)) {
            D_8075531C = D_8075531C;
        } else {
            D_8075531C = *(u16 *) ((u8 *) D_8075E5C2 + D_80755328 * 4);
        }
        D_80755328++;
        D_80755328 = (u32) D_80755328 % 5U;
        D_80755308 = 0x1000;
        break;
    case 7:
        D_8075531C = 0x410;
        D_80755318 = D_80755314 = 9;
    case 9:
        D_80755308 = 0x9000;
        break;
    case 5:
        D_807552EC = 0;
    case 6:
    case 12:
    case 13:
        D_8075531C = 1;
        D_80755308 = 0xFFFF;
        D_8075530C = 0xFF;
        D_80755310 = 0xFF;
        break;
    case 10:
        D_8075531C = 1;
        D_8075530C = 0;
        D_80755310 = 0;
        D_80755308 = 0;
        actorSpawn(0x152, 0);
        break;
    case 14:
        actorSpawn(0x152, 0);
    case 11:
        D_8075531C = 0x1E;
        break;
    }
    eepromSavePlayerData();
}

void func_80712EDC(void) {
    D_80750AC0 = 1;
    func_80712490(0x50, 0, 5);
}

void func_80712F10(s32 *arg0, s32 *arg1) {
    if (D_80755314 == 0xC) {
        if (((D_807FBB68 & 2) == 0) || (D_8076A0A8 == 0xCF) || (*arg0 == 0x22)) {
            *arg0 = 0x50;
            *arg1 = 0;
            D_80755318 = 5;
            return;
        }
    }
    if ((D_80755314 == 0xD) && (D_8076A0A8 != *arg0)) {
        *arg0 = 0xF;
        *arg1 = 0;
        D_80755318 = 6;
        return;
    }
    if (D_80755330 != 0) {
        *arg0 = -1;
    }
}


void func_8060B7D0(s32 *, s32 *);
extern u16 D_807ECD48;
void func_80712FC8(void) {
    s32 arg0;
    s32 arg1;

    if ((D_80755334 >= 0x5A) && (D_807ECD48 & 0x1000)) {
        func_80712EDC();
    } else if (D_8075531C == 0) {
        if (D_8075532C >= 3) {
            func_807124B8(0x28, 0, 1);
        } else {
            func_8060B750(D_8075E5C0[D_80755328 * 4]);
            func_8060B7D0(&arg0, &arg1);
            func_805FF158(1);
            func_805FF378(arg0, arg1);
        }
    }
}

void func_8070B308(s32);

void func_80713088(void) {
    D_8075531C = 0x1E;
    if (D_807ECD66 & 0x8000) {
        func_8070B308(0);
        func_80712490(0x50, 0, 5);
    }
}

s32 camIsCutsceneActive(void);

void func_807130D4(void) {
    if (camIsCutsceneActive()) {
        D_8075531C = 0x1E;
    }
    if ((D_80755330 == 1) || (D_8075531C == 0) || (D_807ECD66 & 0x8000)) {
        func_8070B308(0);
        D_80755330 = 0;
        func_80712490(0x50, 0, 5);
        D_80755330 = 2;
    }
}
void func_80713168(void) {
    if (D_80755334 >= 0x1E) {
        if (D_807ECD66 & 0x9000) {
            goto block_5;
        }
    }
    if (D_8075531C != 0) {
        return;
    }
block_5:
    func_807124B8(0x28, 0, 1);
}


void func_807131BC(void) {
    s32 arg0;
    s32 arg1;

    D_8075532C = 0;
    func_8060B750(D_8075E5C0[D_80755328 * 4]);
    func_8060B7D0(&arg0, &arg1);
    func_805FF158(1);
    func_80712490(arg0, arg1, 3);
}
void func_807131BC(void);

void func_8071321C(void) {
    if ((D_8075531C == 0) || ((D_80755334 >= 0xA) && (D_807ECD48 & 0x1000))) {
        func_807131BC();
    }
}

void func_80713270(void) {
    if (D_80755324 == 0) {
        if (D_80755314 != 1) {
            return;
        }
        if (D_80755334 < 0x5A) {
            return;
        }
        if ((D_807ECD48 & 0x1000) == 0) {
            return;
        }
    }
    func_807124B8(0x4C, 0, 2);
}
#define R117D_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
Gfx *func_805FD030(void);

void *func_807132DC() {
    Gfx *gfx = func_805FD030();

    R117D_WRITE_GFX(gfx++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(gfx++, 0xDA380007, &D_20000C0);
    R117D_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
    R117D_WRITE_GFX(gfx++, 0xE7000000, 0);
    R117D_WRITE_GFX(gfx++, 0xFC11FE23, 0xFFFFF7FB);
    R117D_WRITE_GFX(gfx++, 0xFA000000, 0xFFFFFFFF);
    R117D_WRITE_GFX(gfx++, 0xED028028, 0x4D4394);
    return gfx;
}
void *textTableGetString(s32, s32, s32);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32);

Gfx *func_8071338C(Gfx *arg0) {
    f32 temp_f0 = 20.0f;
    void *temp_v0;

    temp_v0 = textTableGetString(0xC, 0, 1);
    R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
    R117D_WRITE_GFX(arg0++, 0xDA380003, &D_807FDAC0);
    return textDrawStringVtx(arg0, 1, 0x118, (s16) ((temp_f0 + temp_f0) * 4.0f), temp_v0, 4);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/D_8075E5C0.s")

extern s16 D_80744490;

s32 heapAlloc(s32);
void heapFreeDeferred(void *);
s32 textGetStringWidth(s16, s32);
s32 strlen(char *);
s32 _sprintf(char *, const char *, ...);

Gfx *func_80713438(Gfx *arg0, u8 arg1) {
    s32 sp34;
    s32 sp30;
    f32 y;
    f32 sp28;
    s16 new_var2;
    f64 temp_ft4;
    s32 temp_a0;

    sp30 = (s32) textTableGetString(0xC, 1, 1);
    temp_a0 = strlen((char *) sp30) + 2;
    sp28 = (f32) ((f64) D_80744490 * 0.5 * 2.0f);
    y = 418.0f;
    sp34 = heapAlloc(temp_a0);
    heapFreeDeferred((void *) sp34);
    _sprintf((char *) sp34, "%c%s", 0x63, sp30);
    temp_ft4 = (f64) textGetStringWidth(1, sp34);
    temp_ft4 = 0.5 * temp_ft4;
    sp28 = (f32) (((f64) sp28) - temp_ft4);
    new_var2 = (s16) ((s32) (sp28 * 4.0f));
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFA000000, arg1 & 0xFF);
    R117D_WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
    return textDrawStringVtx(arg0, 1, new_var2, (s16) ((s32) (y * 4.0f)), (void *) sp34, 4);
}


typedef struct {
    s32 unk0;
    s32 unk4;
} R117fPair;

extern u8 D_8074450C;
extern R117fPair D_80755370;
extern s32 D_8076A064;
extern u8 D_807ECD09;
u8 textGetFontHeight(s16);
s32 func_807142D8();
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

Gfx *func_807135B4(Gfx *arg0) {
    s32 temp_v0;
    s32 var_v1;
    R117fPair sp38;
    f32 sp34;
    f32 sp30;

    temp_v0 = D_8076A064 - 0x5A;
    if ((temp_v0 >= 0) && !(temp_v0 & 0x10)) {
        sp38 = D_80755370;
        var_v1 = 0;
        sp34 = (f32) D_80744490;
        sp30 = (f32) (0xBD - textGetFontHeight(6));
        if ((D_807ECD09 != 0) && ((func_807142D8() == 0) || (var_v1 = 1, (D_8076A0A8 == 0x4C)))) {
            return arg0;
        }
        if (&D_80755370 && &D_80755370 && &D_80755370) {}  // FAKE: dead address test, steers as1 delay-slot fill (bne+nop instead of bnel)
        sp34 = (f32) ((f64) sp34 * 0.5);
        R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
        arg0 = hudDrawScaledText(arg0, (s16) (s32) (sp34 * 4.0f), (s16) (s32) ((f32) D_8074450C * sp30 * 4.0f), 0.7f, textTableGetString(0xC, (s32) (&sp38.unk0)[var_v1], 1));
    }
    return arg0;
}

s32 func_8071375C(s32 arg0) {
    return arg0;
}
extern s16 D_80744494;
Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_80713764(Gfx *arg0, u8 arg1, f32 arg2) {
    f32 x;
    f32 y;

    x = (f32) ((f64) D_80744490 * 0.5);
    y = (f32) (((f64) D_80744494 * 0.5) + -20.0 + (f64) arg2);
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFA000000, (s32) ((arg1 & 0xFF) | ~0xFF)); // FAKE: no-op mask advances the scratch-register ring
    R117D_WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
    R117D_WRITE_GFX(arg0++, 0xE3001201, 0);
    return renderRotatedSprite(arg0, 0x2C, 0, 2, 0xE0, 0x80, (s32) x, (s32) y, 1.0f, 1.0f, 0, 0.0f);
}

void *func_807132DC();
Gfx *func_807135B4(Gfx *);

Gfx *func_807138A4(Gfx *arg0) {
    return func_807135B4(func_807132DC(arg0));
}
void viewportSetFromRect(void *, s32, s32, s32, s32);
Gfx *func_806FF144(void *);

Gfx *func_807138CC(Gfx *arg0) {
    void *sp3C;
    f32 temp_fv0;
    Gfx *g;

    sp3C = (void *)heapAlloc(0x10);
    heapFreeDeferred(sp3C);
    viewportSetFromRect(sp3C, 0xA, 0xA, 0x135, 0xE5);
    arg0 = func_807135B4(func_807132DC(arg0));
    arg0 = func_8071338C(arg0);
    if ((u32)++D_80755320 < 0xD3U) {
        temp_fv0 = (f32) (0xD2U - D_80755320) * 0.03333333507f;
        temp_fv0 = (temp_fv0 < 0.0f) ? 0.0f : ((temp_fv0 > 1.0f) ? 1.0f : temp_fv0);
        arg0 = func_80713764(func_80713438(arg0, (u32) (255.0f * temp_fv0)), (u32) (255.0f * temp_fv0), 0);
    }
    g = arg0++; g->words.w0 = 0xDC080008; // FAKE: same-line pointer-copy and first store steers as1 move/ori order
    g->words.w1 = (u32)sp3C;
    return func_806FF144(arg0);
}


Gfx *func_80713AA8(Gfx *arg0) {
    R117D_WRITE_GFX(arg0++, 0xE7000000, 0);
    R117D_WRITE_GFX(arg0++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(arg0++, 0xE3000A01, 0);
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    R117D_WRITE_GFX(arg0++, 0xDA380007, &D_20000C0);
    return arg0;
}

extern u8 D_80755378[];

Gfx *func_80713B40(Gfx *arg0) {
    s16 temp_t0;
    s16 temp_v0;
    s16 var_v1;
    u32 new_var; // FAKE: extra temp for the alpha byte steers regalloc

    temp_t0 = D_8075531C - 0x8C;
    if (temp_t0 >= 0) {
        if (temp_t0 < 0x96) {
            temp_v0 = temp_t0 - 0x5A;
            var_v1 = temp_v0; // FAKE: copy of temp_v0 steers regalloc
            if (var_v1 < 0) {
                var_v1 = 0xFF;
            } else {
                var_v1 = 0x3C - var_v1;
                var_v1 = var_v1 * 5;
            }
            if (temp_t0 < 0x3C) {
                var_v1 = temp_t0 * 5;
            }
            if (var_v1 >= 0x100) {
                var_v1 = 0xFF;
            }
            arg0 = func_80713AA8(arg0);
            new_var = var_v1 & 0xFF;
            arg0->words.w0 = 0xFA000000;
            arg0->words.w1 = (u32)(new_var | ~0xFF);
            arg0 = hudDrawScaledText(arg0 + 1, 0x280, (s16)(s32)(480.0 - ((f64)(f32)((f64)(0x96 - temp_t0) / 40.0) * 32.0)), (f32)((f64)(0x96 - temp_t0) / 40.0), D_80755378);
        }
    }
    return arg0;
}



extern u64 D_807445B0;
void sfxAllocateChannel(s32, f32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);

void func_80713C8C(void) {
    u64 elapsed;

    D_8075531C = 1;
    if (D_80755340.active != 0) {
        if (flagGet(0x302, 0) != 0) {
            func_8071261C();
            sfxAllocateChannel(0x74, 1.0f);
            return;
        }
        D_80755340.time += D_807445B0;
        if (!(D_807FBB60 & 2)) {
            elapsed = (osGetTime() - D_80755340.time) * 64;
            D_80755340.unk8 = D_80755340.duration - (u32)(elapsed / 3000 / 1000000);
            if (((u32)D_80755340.index < 0xA) && (D_80755340.unk8 == D_80755358[D_80755340.index])) {
                sfxPlayOnFreeSlot(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                D_80755340.index++;
            }
            if (D_80755340.unk8 <= 0) {
                func_807127B4();
            }
        }
    }
}

extern s32 D_80755348;
Gfx *renderTimerMinutesSecondsHUD(Gfx *, f32, f32, s32);

Gfx *hudDrawCountdownTimer(Gfx *arg0) {
    s32 pad[8]; // FAKE: frame size 0x40 (eight unused words above sp1C)
    f32 sp1C;
    Gfx *temp_v0;

    if ((func_80712628() != 0) && !(D_807FBB60 & 3)) {
        sp1C = (f32) D_80744490 * 0.5f;
        temp_v0 = func_807132DC(arg0);
        R117D_WRITE_GFX(temp_v0++, 0xFC119623, 0xFF2FFFFF);
        R117D_WRITE_GFX(temp_v0++, 0xFA000000, 0xFFFFFFFF);
        arg0 = renderTimerMinutesSecondsHUD(temp_v0, sp1C, 214.0f, D_80755348);
    }
    return arg0;
}

s32 func_80713EA8(s32 arg0) {
    return arg0;
}

extern s16 D_807FC828[];
void hudPauseMenuRefreshTotals();

void func_80713EB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s32 sum;
    s32 i;

    if (arg0 >= 0) {
        if (D_80755314 == 0xE) {
            if (arg2 == 1) {
                if (flagGet(0x2A, 1) == 0) {
                    arg0 = -1;
                }
            }
            if (arg2 == 2) {
                if (flagGet(0x2B, 1) == 0) {
                    arg0 = -1;
                }
            }
        } else {
            hudPauseMenuRefreshTotals(); // FAKE: a0 still holds arg0; passing it makes uopt emit move a0,a3
            sum = 0; for (i = 0; i < 7; i++) { sum += D_807FC828[i]; } if (arg2 == 1) { // FAKE: one source line lets as1 reorder the unrolled loads
                if (sum < 0x118) {
                    arg0 = -1;
                } else {
                    flagSet(0x2A, 1, 1);
                }
            }
            if (arg2 == 2) {
                if (sum < 0x119) {
                    arg0 = -1;
                } else {
                    flagSet(0x2B, 1, 1);
                }
            }
        }
        if (arg0 >= 0) {
            func_80712524(arg0, arg1);
            return;
        }
    }
    if (D_80755314 == 0xE) {
        func_8070B308(0);
        func_80712490(0x50, 0, 5);
        return;
    }
    func_807124B8(0x28, 0, 1);
}

Gfx *func_807138CC(Gfx *);
Gfx *func_80713B40(Gfx *);
extern s8 D_807552E0;
void camStartPath(s32, s16, s32);

Gfx *screenStateTickAndDraw(Gfx *arg0) {
    char buffer[40];

    if ((D_80755338 != 0) && (D_8076A064 == 1)) {
        D_80755338 = 0;
        if (D_8075533C >= 0) {
            camStartPath(0, (s16)D_8075533C, 1);
        }
    }
    if (D_807552E0 != 0) {
        arg0 = func_807132DC(arg0);
        _sprintf(buffer, "SECURITY %d", D_807552E0);
        arg0 = hudDrawScaledText(arg0, 0x280, 0x1E0, 1.0f, buffer);
    }
    D_807552E0 = 0;
    R117D_WRITE_GFX(arg0++, 0xE7000000, 0);
    if (D_80755334 < 0x5A) {
        D_80755334++;
    }
    if ((func_80712628() != 0) && (D_80755314 != 6)) {
        func_8071261C();
    }
    if (D_8075531C != 0) {
        if (D_80755314 == D_80755318) {
            D_8075531C--;
            switch (D_80755314) {
            case 0:
            case 1: func_80713270(); break;
            case 2: func_8071321C(); break;
            case 3: func_80712FC8(); break;
            case 7:
            case 9: func_80713168(); break;
            case 14: func_80713088(); break;
            case 11: func_807130D4(); break;
            case 6: func_80713C8C(); break;
            }
        }
    }
    switch (D_80755314) {
    case 0:
    case 1: arg0 = (Gfx *)func_8071375C((s32)arg0); break;
    case 2: arg0 = func_807138A4(arg0); break;
    case 3: arg0 = func_807138CC(arg0); break;
    case 7:
    case 9: arg0 = func_80713B40(arg0); break;
    case 6: arg0 = hudDrawCountdownTimer(arg0); break;
    case 5: arg0 = (Gfx *)func_80713EA8((s32)arg0); break;
    case 11: break;
    }
    return arg0;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} R117cState;

extern s32 D_807552E4;
extern s32 D_80755384[];
extern s8 D_80750AB8;
#define R117c_STATE ((R117cState *) &D_807552E4)


s32 func_807142D8(void) {
    s32 var_v0;

    var_v0 = D_80755318 == 3;
    if (var_v0 == 0) {
        var_v0 = D_80755318 == 4;
        if (var_v0 == 0) {
            var_v0 = D_80755314 == 3;
            if (var_v0 == 0) {
                return D_80755314 == 4;
            }
        }
    }
}

s32 func_8071432C(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 6;
    if (var_v0 == 0) {
        return D_80755318 == 6;
    }
}

s32 func_80714360(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 8;
    if (var_v0 == 0) {
        return D_80755318 == 8;
    }
}

s32 func_80714394(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 7;
    if (var_v0 == 0) {
        var_v0 = D_80755318 == 7;
        if (var_v0 == 0) {
            var_v0 = D_80755314 == 9;
            if (var_v0 == 0) {
                return D_80755318 == 9;
            }
        }
    }
}

s32 func_807143E8(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 0xD;
    if (var_v0 == 0) {
        return D_80755318 == 0xD;
    }
}

s32 func_8071441C(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 0xC;
    if (var_v0 == 0) {
        return D_80755318 == 0xC;
    }
}

s32 func_80714450(void) {
    return D_80755314 == 5;
}

s32 func_80714464(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 0xA;
    if (var_v0 == 0) {
        var_v0 = D_80755314 == 0xE;
        if (var_v0 == 0) {
            var_v0 = D_80755318 == 0xA;
            if (var_v0 == 0) {
                return D_80755318 == 0xE;
            }
        }
    }
}

extern s8 D_8074452C;
extern u8 D_807467C8;
void func_806C9AE0(void);
void func_80731030(void);
void eepromLoadPlayerData(u8, s32);
s32 func_8060C6B8(s32, s32, s32, u8);
void func_805FF4D8(s32, s32);

void func_807144B8(u8 arg0) {
    s32 var_a0;
    s32 var_a1;

    D_807445B8 = osGetTime();
    D_80755350 = 0;
    func_806C9AE0();
    func_80731030();
    eepromLoadPlayerData(arg0, 1);
    D_8074E77C = 0;
    if ((func_8060C6B8(0xD, 0, 0, D_807467C8) != 0) || (D_8074452C != 0)) {
        if (flagGet(0x186, 0) != 0) {
            var_a0 = 0x22;
            var_a1 = 0;
        } else {
            var_a0 = 0xB0;
            var_a1 = 1;
        }
    } else {
        D_80755338 = 1;
        D_8075533C = 0;
        var_a0 = 0x99;
        var_a1 = 0;
    }
    func_805FF4D8(var_a0, var_a1);
    D_80755318 = 6;
}



void func_8071458C(void) {
    s32 var_a0;

    func_806C9AE0();
    D_80750AB8 = 0;
    if (R117c_STATE->unk0 == 0) {
        D_80750AB8 = 1;
        var_a0 = 0x6B;
    } else {
        var_a0 = D_80755384[R117c_STATE->unk20];
    }
    func_80712490(var_a0, 0, 6);
}

void func_807145F8(void) {
    D_80755324 = 1;
}


s32 func_80714608(s32 arg0) {
    s32 var_v0;

    var_v0 = (s32) D_807FC928 >= 2;
    if (var_v0 != 0) {
        return arg0 == D_807552E4;
    }
}

void func_80714638(void) {
    func_80712EDC();
    D_807552EC = 3;
}

void func_80714660(void) {
}
