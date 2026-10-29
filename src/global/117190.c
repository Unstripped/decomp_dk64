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

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712574.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807126B0.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712830.s")

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

typedef struct R117gTimedState {
    u64 time;
    s32 unk8;
    s32 duration;
    u8 active;
    u8 index;
} R117gTimedState;

extern u64 D_807445B8;
extern u64 D_807445C0;
extern s8 D_80746B60;
extern u32 D_807FBB60;
extern R117gTimedState D_80755340;
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
extern s8 D_8074E77C;
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80712BD4.s")

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


extern s32 D_80755334;
extern u8 D_8075532C;
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

void *func_807132DC(void) {
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
extern Mtx D_807FDAC0;
void *func_8070E750(s32, s32, s32);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32);

void func_8071338C(Gfx *arg0) {
    f32 temp_f0 = 20.0f;
    void *temp_v0;

    temp_v0 = func_8070E750(0xC, 0, 1);
    R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
    R117D_WRITE_GFX(arg0++, 0xDA380003, &D_807FDAC0);
    textDrawStringVtx(arg0, 1, 0x118, (s16) ((temp_f0 + temp_f0) * 4.0f), temp_v0, 4);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/D_8075E5C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713438.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807135B4.s")

s32 func_8071375C(s32 arg0) {
    return arg0;
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713764.s")

void *func_807132DC(void);
void func_807135B4(void *);

void func_807138A4(void) {
    func_807135B4(func_807132DC());
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807138CC.s")


Gfx *func_80713AA8(Gfx *arg0) {
    R117D_WRITE_GFX(arg0++, 0xE7000000, 0);
    R117D_WRITE_GFX(arg0++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(arg0++, 0xE3000A01, 0);
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    R117D_WRITE_GFX(arg0++, 0xDA380007, &D_20000C0);
    return arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713B40.s")


extern u64 D_807445B0;
extern u16 D_80755358[];
s32 flagGet(s32, s32);
void sfxAllocateChannel(s32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);

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
                func_80609140(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                D_80755340.index++;
            }
            if (D_80755340.unk8 <= 0) {
                func_807127B4();
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713DFC.s")

s32 func_80713EA8(s32 arg0) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80713EB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_80714060.s")

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

extern s32 D_807552EC;
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/func_807144B8.s")

void func_806C9AE0(void);


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

extern u8 D_807FC928;

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
