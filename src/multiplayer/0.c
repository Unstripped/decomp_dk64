#include "common.h"

typedef struct Struct_80024000_2_MpLow {
    u64 unk0;
    s32 unk8;
    s32 unkC;
} Struct_80024000_2_MpLow;

typedef struct Struct_80024000_1_MpLow {
    char pad[0x174];
    Struct_80024000_2_MpLow *unk174;
} Struct_80024000_1_MpLow;

extern u8 D_80750AB8;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_1000118[];
extern u8 D_20000C0[];

Gfx *func_805FD030(Gfx *);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *func_8068E7B4(Gfx *, f32, f32, s32);
extern s32 D_807552E8;
extern u8 D_807FC950[];
s32 func_806F8AD4(s32, u8);
extern s32 D_807552EC;
extern u8 D_807FC928;
extern s32 D_807FBB60;
extern s8 D_8076A105;
void func_80714638(void);
s32 func_80611A44(void);
typedef struct Struct_80026FA4_MpLow {
    s32 unk0;
    char pad[0x1C];
} Struct_80026FA4_MpLow;
extern Struct_80026FA4_MpLow D_80026FA4[];
extern s32 D_8076A0A8;
extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
extern Struct_80024000_1_MpLow *D_807FBB40;
void renderCallbacksRegister(void *, void *, s32);
typedef struct Struct_807552E4_MpLow {
    char pad[0xC];
    s32 unkC;
} Struct_807552E4_MpLow;
extern Struct_807552E4_MpLow D_807552E4;
extern u8 *D_807FC924;
typedef struct Struct_800246EC_Sub_MpLow {
    char pad[0x6];
    s16 unk6;
    s16 unk8;
} Struct_800246EC_Sub_MpLow;

typedef struct Struct_800246EC_Arg1_MpLow {
    char pad[0x20];
    Struct_800246EC_Sub_MpLow *unk20[4];
    char pad2[0x14];
    void *unk44;
    void *unk48;
} Struct_800246EC_Arg1_MpLow;

Gfx *func_80024000(Gfx *glistp, Struct_80024000_1_MpLow *arg1) {
    Struct_80024000_2_MpLow *sp44;
    f32 var_fv1;
    f32 var_fa0;

    sp44 = arg1->unk174;
    if (D_80750AB8 == 1) {
        var_fv1 = 278.0f;
        var_fa0 = 210.0f;
    } else {
        var_fv1 = (f32) (D_80744490 * 0.5);
        var_fa0 = (f32) (D_80744494 * 0.5);
    }
    glistp = func_805FD030(glistp);
    gSPDisplayList(glistp++, &D_1000118);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPPipeSync(glistp++);
    if (D_80750AB8 == 1) {
        gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(glistp++, 0, 0, 0, 120, 255, 80);
        glistp = func_8068C5A8(glistp, 0x60, 4, 0, 0x40, 0x40, (s32) (var_fv1 * 4.0f), (s32) (var_fa0 * 4.0f), 3.7f, 2.0f, 0xB4, 0.0f);
    }
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    return func_8068E7B4(glistp, var_fv1, var_fa0, sp44->unk8);
}

s32 func_800241F4(void *arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = -*(u16 *)((u8 *)arg0 + (arg1 << 1) + 0x2FE);
    if (arg1 != 0) {
        var_v1 += *(u16 *)((u8 *)arg0 + 0x2FE);
    }
    if (arg1 != 1) {
        var_v1 += *(u16 *)((u8 *)arg0 + 0x300);
    }
    if (arg1 != 2) {
        var_v1 += *(u16 *)((u8 *)arg0 + 0x302);
    }
    if (arg1 != 3) {
        var_v1 += *(u16 *)((u8 *)arg0 + 0x304);
    }
    return var_v1;
}

s32 mpGetPlayerScore(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    switch (D_807552E8) {
    case 2:
    case 3:
        var_v1 = func_806F8AD4(1, arg0);
        break;
    case 4:
    case 5:
        var_v1 = func_806F8AD4(7, arg0);
        break;
    case 0:
    case 1:
        var_v1 = func_800241F4(&D_807FC950[arg0 * 0x306], arg0);
        break;
    }
    return var_v1;
}

void mpDetermineWinner(s32 arg0) {
    s32 temp_v0;
    s32 var_s1;
    s32 var_s0;
    s32 var_s2;

    D_807552EC = 2;
    var_s2 = 0;
    var_s1 = 0xFFFE7961;
    var_s0 = 0;
    if ((s32) D_807FC928 > 0) {
        do {
            temp_v0 = mpGetPlayerScore(var_s0);
            if (var_s1 < temp_v0) {
                var_s1 = temp_v0;
                var_s2 = var_s0;
            } else if (temp_v0 == var_s1) {
                var_s2 = -1;
            }
            var_s0 += 1;
        } while (var_s0 < (s32) D_807FC928);
    }
    D_807FBB60 |= 0x40001;
    func_80714638();
    D_8076A105 = var_s2;
}

void mpUpdateMatchTimer(void) {
    Struct_80024000_2_MpLow *temp_s0;
    u64 x;

    temp_s0 = D_807FBB40->unk174;
    x = __ull_div(__ll_mul(osGetTime() - temp_s0->unk0, 0x40), 0xBB8);
    if (!(D_807FBB60 & 2)) {
        x = __ull_div(x, 0xF4240);
        temp_s0->unk8 = temp_s0->unkC - x;
    }
    if (temp_s0->unk8 <= 0) {
        temp_s0->unk8 = 0;
        mpDetermineWinner((s32)temp_s0);
    }
    renderCallbacksRegister(func_80024000, D_807FBB40, 7);
}

void func_8002449C(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    if ((s32) D_807FC928 > 0) {
        do {
            temp_v0 = mpGetPlayerScore(var_s0);
            if ((temp_v0 >= D_807552E4.unkC) || (temp_v0 < -0x3E7)) {
                mpDetermineWinner((s32) D_807FBB40->unk174);
                return;
            }
            var_s0++;
        } while (var_s0 < (s32) D_807FC928);
    }
}

void func_8002452C(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    if ((s32) D_807FC928 > 0) {
        do {
            if (mpGetPlayerScore(var_s0) != 0) {
                var_s1++;
            }
            var_s0++;
        } while (var_s0 < (s32) D_807FC928);
    }
    if (var_s1 < 2) {
        mpDetermineWinner((s32) D_807FBB40->unk174);
    }
}

Gfx *mpDrawGlyph(Gfx *glistp, s16 *arg1, s16 arg2, void *arg3, s32 arg4) {
    gDPLoadTextureBlock(glistp++, arg3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_WRAP, G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glistp++, (*arg1) << 2, arg2 << 2, (*arg1 + arg4 * 8) << 2, (arg2 + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    *arg1 += arg4 * 8;
    return glistp;
}

#pragma GLOBAL_ASM("asm/multiplayer/nonmatchings/0/func_800246EC.s")

int _sprintf(char *, const char *, ...);
s32 func_806FBD5C(s32, char *);
Gfx *func_806FC530(Gfx *, s32, s16, s16, char *, s32);
Gfx *func_800246EC(Gfx *, void *, f32);

typedef struct Struct_800249D8_Sub_MpDraw {
    char pad[0x6];
    s16 unk6;
} Struct_800249D8_Sub_MpDraw;

typedef struct Struct_800249D8_Unk174_MpDraw {
    char pad[0x20];
    Struct_800249D8_Sub_MpDraw *unk20[4];
    Mtx *unk30;
} Struct_800249D8_Unk174_MpDraw;

typedef struct Struct_800249D8_Arg1_MpDraw {
    char pad[0x174];
    Struct_800249D8_Unk174_MpDraw *unk174;
} Struct_800249D8_Arg1_MpDraw;

Gfx *mpDrawPlayerScores(Gfx *glistp, Struct_800249D8_Arg1_MpDraw *arg1) {
    char sp98[32];
    f32 temp_fs0;
    f32 temp_fs2;
    s32 var_s2;
    Struct_800249D8_Unk174_MpDraw *temp_s0;
    void *temp;

    temp_s0 = arg1->unk174;
    temp = temp_s0->unk20[0];
    temp_fs2 = (f32) D_80744490 / (f32) (D_807FC928 + 1);
    temp_fs0 = (f32) (((Struct_800249D8_Sub_MpDraw *)temp)->unk6 + 8);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    glistp = func_800246EC(glistp, temp_s0, temp_fs2);
    if (D_807552E8 != 3) {
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 180);
        gSPDisplayList(glistp++, &D_1000118);
        gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(glistp++, temp_s0->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(glistp++);
        gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 180);
        temp_fs0 += 8.0f;
        var_s2 = 0;
        if ((s32) D_807FC928 > 0) {
            do {
                _sprintf(sp98, "%d", mpGetPlayerScore(var_s2));
                temp = func_806FC530(glistp, 1, (s16) (s32) ((((f32) (var_s2 + 1) * temp_fs2) - (f32) ((f32) func_806FBD5C(1, sp98) * 0.25)) * 8.0f), (s16) (s32) (temp_fs0 * 8.0f), sp98, 4);
                var_s2 = var_s2 + 1;
                glistp = temp;
            } while (var_s2 < (s32) D_807FC928);
        }
    }
    return glistp;
}

#pragma GLOBAL_ASM("asm/multiplayer/nonmatchings/0/func_80024CA4.s")

typedef struct Struct_807552E4_MpFix {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Struct_807552E4_MpFix;

#define SP_MpFix ((Struct_807552E4_MpFix *)&D_807552E4)

Gfx *func_80024CA4(Gfx *, void *);

Gfx *func_80025264(Gfx *glistp, void *arg1) {
    s32 t0 = SP_MpFix->unk8 >= 2;
    s32 cond = D_807FBB60 & 3;

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    if (!cond) {
        if (SP_MpFix->unk0 == 0) {
            if ((SP_MpFix->unk8 == 1) || t0) {
                glistp = mpDrawPlayerScores(glistp, arg1);
            }
        } else if ((SP_MpFix->unk8 == 1) || t0) {
            glistp = func_80024CA4(glistp, arg1);
        }
    }
    return glistp;
}

Struct_80026FA4_MpLow *mpFindCurrentMapEntry(void) {
    s32 i;
    Struct_80026FA4_MpLow *ret = NULL;

    for (i = 0; (i < 4U) && (ret == NULL); i++) {
        if (D_8076A0A8 == D_80026FA4[i].unk0) {
            ret = &D_80026FA4[i];
        }
    }
    return ret;
}

s32 func_800253C8(void) {
    return (((func_80611A44() >> 15) % 0x7FFF) % 211) + 0x5A;
}

#pragma GLOBAL_ASM("asm/multiplayer/nonmatchings/0/func_80025404.s")

void func_8063254C(s32, s32 *, s32 *, s32 *, s32 *, s16 *, s16 *);

s32 func_80025608(s32 arg0) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s16 sp2E;
    s16 sp2C;

    sp3C = 0;
    sp2E = 0;
    sp2C = 0;
    func_8063254C(arg0, &sp3C, &sp38, &sp34, &sp30, &sp2E, &sp2C);
}

typedef struct Struct_80025654_Pos_MpHigh {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Struct_80025654_Pos_MpHigh;

typedef struct Struct_80025654_Actor_MpHigh {
    char pad[0x4C];
    u8 unk4C;
} Struct_80025654_Actor_MpHigh;

s32 func_8071432C(void);
void mpUpdateMatchTimer(void);
s32 func_80025404(void);
void *actorFindByType();
s32 func_806F5EB4(s32, s32, s16, s16, s16);
void func_806F5FE8(s32, s16, s16, s16, s32);
s32 mpGetPlayerScore(s32);

extern s32 D_807FBB60;
extern s32 D_807552E8;
extern s32 D_807552F0;

void func_80025654(Struct_80025654_Actor_MpHigh *arg0) {
    s32 temp;
    Struct_80025654_Pos_MpHigh * volatile sp20;

    sp20 = *(Struct_80025654_Pos_MpHigh **)((u8 *)mpFindCurrentMapEntry() + 8);
    if (func_8071432C() != 0 && !(D_807FBB60 & 2)) {
        if (D_807552E8 == 3) {
            mpUpdateMatchTimer();
        }
        if ((temp = func_80025404()) == -1) {
            if (arg0->unk4C == 0 &&
                actorFindByType(0x7A) == 0 &&
                func_80025608(0x1D2) == 0) {
                {
                    Struct_80025654_Pos_MpHigh *pos = sp20;
                    if (func_806F5EB4(0x1D2, 0, pos->unk0, pos->unk2, pos->unk4) == 0) {
                        pos = sp20;
                        func_806F5FE8(0x1D2, pos->unk0, pos->unk2, pos->unk4, 10);
                    }
                }
            }
        } else if (D_807552E8 == 5 && mpGetPlayerScore(temp) >= D_807552F0) {
            mpDetermineWinner((s32)arg0);
        }
        if (arg0->unk4C != 0) {
            arg0->unk4C--;
        }
    }
}

typedef struct Item_80025794_MpBigHi {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Item_80025794_MpBigHi;

typedef struct Parent_80025794_MpBigHi {
    char pad0[4];
    s32 count;
    Item_80025794_MpBigHi *items;
} Parent_80025794_MpBigHi;

f32 func_806119FC(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_806F5F2C(s32, s32, s16, s16, s32);

void func_80025794(void) {
    Parent_80025794_MpBigHi *sp84;
    s32 sp80;
    s32 sp7C;
    Item_80025794_MpBigHi *items;
    Item_80025794_MpBigHi *item;
    s32 j;
    s32 k;
    s32 num_outer;
    s32 num_inner;
    s32 temp_s4;
    s16 angle;
    f32 fs0;
    f32 fs1;
    f32 fs2;
    f32 fs3;
    f32 fs4;
    s16 s2_val;

    sp84 = (Parent_80025794_MpBigHi *) mpFindCurrentMapEntry();
    items = sp84->items;
    mpUpdateMatchTimer();
    if (func_8071432C() != 0 && !(D_807FBB60 & 2)) {
        sp7C = 0;
        item = items;
        if (sp84->count > 0) {
            do {
                if (item->unk8 != 0) {
                    item->unk8--;
                } else {
                    j = 0;
                    if (item->unk6 == 0) {
                        num_outer = 1;
                    } else {
                        num_outer = ((s32) (func_80611A44() >> 15) % 0x7FFF % 3) + 1;
                    }
                    if (num_outer > 0) {
                        do {
                            k = 0;
                            num_inner = ((s32) (func_80611A44() >> 15) % 0x7FFF % 3) + 1;
                            temp_s4 = (s16) func_800253C8();
                            fs1 = (f32) ((((f64) func_806119FC() * 0.8) + 0.2) * (f64) item->unk6);
                            angle = (s32) (func_80611A44() >> 15) % 4096;
                            fs3 = (f32) item->unk0;
                            fs0 = (f32) (item->unk2 - 23);
                            fs4 = (f32) item->unk4;
                            fs3 += fs1 * func_80612794(angle);
                            fs4 += fs1 * func_80612790(angle);
                            if (num_inner >= 2) {
                                angle = (s32) (func_80611A44() >> 15) % 4096;
                                fs1 = 15.0f;
                                fs2 = 4096.0f / (f32) num_inner;
                            } else {
                                fs1 = 0.0f;
                                fs2 = 0.0f;
                                angle = 0;
                            }
                            if (num_inner > 0) {
                                s2_val = (s16) (s32) fs0;
                                do {
                                    f32 x = fs3 + func_80612794(angle) * fs1;
                                    f32 z = fs4 + func_80612790(angle) * fs1;
                                    func_806F5F2C(0x7A, temp_s4, (s16) (s32) x, s2_val, (s32) z);
                                    k++;
                                    angle += fs2;
                                    angle &= 0xFFF;
                                } while (k != num_inner);
                            }
                            j++;
                        } while (j != num_outer);
                    }
                    item->unk8 = func_800253C8();
                }
                item++;
                sp7C++;
            } while (sp7C < sp84->count);
        }
    }
}

void *func_807270C0(s16, s32);
void *func_807271F4(s32, s32, s32, s32, s32, s32, s32);

typedef struct Struct_80025B48_Actor_MpNearHi {
    char pad[0x154];
    u8 unk154;
    u8 unk155;
} Struct_80025B48_Actor_MpNearHi;

typedef struct Struct_80025B48_Struct_MpNearHi {
    char pad[0x18];
    Struct_80025B48_Actor_MpNearHi *unk18;
    s16 unk1C;
} Struct_80025B48_Struct_MpNearHi;

void func_80025B48(Struct_80025B48_Struct_MpNearHi *arg0) {
    s32 var_a2;

    var_a2 = 0;
    if (arg0->unk18 != NULL) {
        if (arg0->unk18->unk154 == 0x40) {
            arg0->unk18 = NULL;
            var_a2 = 1;
        }
    } else {
        var_a2 = 1;
    }

    if (arg0->unk1C == 0) {
        if (var_a2 != 0) {
            arg0->unk1C = (((func_80611A44() >> 15) % 0x7FFF) % 271) + 30;
        }
    } else {
        arg0->unk1C--;
    }

    if (var_a2 != 0 && arg0->unk1C == 0) {
        var_a2 = (((func_80611A44() >> 15) % 0x7FFF) % 3) + 1;
        if (var_a2 == 3) {
            var_a2 += (((func_80611A44() >> 15) % 0x7FFF) % 5);
        }
        arg0->unk18 = func_807270C0(var_a2, 0);
        if (arg0->unk18 == NULL) {
            arg0->unk18 = func_807271F4((s16)var_a2, 0, 0, 0, 0, 0, 0);
        }
        if (arg0->unk18 != NULL) {
            arg0->unk18->unk154 = 0x36;
            arg0->unk18->unk155 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/multiplayer/nonmatchings/0/func_80025CE8.s")

void func_8063DA40(s16, s32);

typedef struct Struct_80025F84_MpHigh {
    char pad[0xC];
    s32 unkC[4];
} Struct_80025F84_MpHigh;

void func_80025F84(void) {
    Struct_80025F84_MpHigh *temp;
    s32 i;

    temp = (Struct_80025F84_MpHigh *)mpFindCurrentMapEntry();
    i = 0;
    while (i < 4 && temp->unkC[i] != -1) {
        func_8063DA40(temp->unkC[i], 0);
        i++;
    }
}

void func_80715908(s32);

typedef struct Struct_80025FFC_MpHigh {
    char pad[0x50];
    s32 unk50[1];
    char pad2[0x70 - 0x54];
    u8 unk70;
} Struct_80025FFC_MpHigh;

void func_80025FFC(Struct_80025FFC_MpHigh *arg0) {
    s32 i;

    if (arg0->unk70 != 0) {
        for (i = 0; i < D_807FC928 * 2; i++) {
            if (arg0->unk50[i] != 0) {
                func_80715908(arg0->unk50[i]);
            }
            arg0->unk50[i] = 0;
        }
    }
    arg0->unk70 = 0;
}

#pragma GLOBAL_ASM("asm/multiplayer/nonmatchings/0/func_80026094.s")

extern u8 D_80026F70;

void mpSetFlags(u8 arg0) {
    D_80026F70 |= arg0;
}

extern void func_806F0C18(void *);
extern s32 func_80714608(s32);
extern void func_806F91B4(s32, u8, s32);
extern u8 *D_807FD580;

typedef struct Struct_800268DC_0_MpHigh {
    char pad[0x60];
    s32 unk60;
} Struct_800268DC_0_MpHigh;

typedef struct Struct_800268DC_1_MpHigh {
    char pad[0xD4];
    s16 unkD4;
    char pad2[0x1A4 - 0xD4 - 2];
    u8 unk1A4;
    char pad3[0x246 - 0x1A4 - 1];
    s8 unk246;
    s8 unk247;
} Struct_800268DC_1_MpHigh;

typedef struct Struct_800268DC_2_MpHigh {
    char pad[0x2F0];
    s16 unk2F0;
    s16 unk2F2;
    s16 unk2F4;
    s16 unk2F6;
} Struct_800268DC_2_MpHigh;

void func_800268DC(Struct_800268DC_0_MpHigh *arg0, Struct_800268DC_1_MpHigh *arg1, Struct_800268DC_2_MpHigh *arg2) {
    arg2->unk2F6 = 0;
    arg2->unk2F0 = 0;
    arg2->unk2F4 = 0;
    arg2->unk2F2 = 0;
    arg1->unkD4 = 90;
    func_806F0C18(arg0);
    arg0->unk60 &= ~0x20000000;
    arg1->unk247 = -1;
    arg1->unk246 = 0;
    if (func_80714608(0) != 0) {
        *(s16 *)(D_807FD580 + 0x21E) = 0;
    }
    if (D_807552E8 == 3 || D_807552E8 == 5) {
        func_806F91B4(1, arg1->unk1A4, -10);
    }
}

void func_8002698C(Struct_800268DC_1_MpHigh *arg0) {
    if (D_807552E8 == 2) {
        func_806F91B4(1, arg0->unk1A4, -3);
    }
}

void func_800269C8(u8, s8);
typedef struct Struct_800269C8_174_MpNearHi {
    char pad[0x4C];
    u8 unk4C;
} Struct_800269C8_174_MpNearHi;

typedef struct Struct_800269C8_ADB4_MpNearHi {
    char pad[0x174];
    Struct_800269C8_174_MpNearHi *unk174;
} Struct_800269C8_ADB4_MpNearHi;

typedef struct Struct_800269C8_Target_MpNearHi {
    char pad[0x7C];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    char pad2[0xE6 - 0x88];
    s16 unkE6;
} Struct_800269C8_Target_MpNearHi;

typedef struct Struct_800269C8_Player_MpNearHi {
    char pad[0x4];
    Struct_800269C8_Target_MpNearHi *unk4;
    char pad2[0x2F0 - 8];
} Struct_800269C8_Player_MpNearHi;

typedef struct Struct_800269C8_Array950_MpNearHi {
    char pad[0x2FA];
    s8 unk2FA;
    s8 unk2FB;
    char pad2;
    s8 unk2FD;
    char pad3[0x306 - 0x2FE];
} Struct_800269C8_Array950_MpNearHi;

void func_800269C8(u8 arg0, s8 arg1) {
    s32 pad0;
    s32 pad1;
    s32 sp34;
    s32 sp30;
    Struct_800269C8_Target_MpNearHi *s0;
    Struct_800269C8_Array950_MpNearHi *s1;

    s0 = ((Struct_800269C8_Player_MpNearHi *)D_807FC924)[arg0].unk4;
    s1 = &((Struct_800269C8_Array950_MpNearHi *)D_807FC950)[arg0];
    sp34 = s1->unk2FB + s1->unk2FD + arg1;
    sp30 = s1->unk2FA - sp34;
    if (func_806F8AD4(1, arg0) != 0 && (sp34 <= 0 || sp30 >= 2)) {
        sp34 = (s32)((Struct_800269C8_ADB4_MpNearHi *)actorFindByType(0x13E))->unk174;
        ((Struct_800269C8_174_MpNearHi *)sp34)->unk4C = 1;
        func_806F91B4(1, arg0, -10);
        if (D_807552E8 == 5) {
            func_80025F84();
        }
        actorSpawnNodeEntryScaled(0x7A, s0->unk7C, s0->unk80, s0->unk84, s0->unkE6, 1, -1, 0);
        s1->unk2FA = 0;
    }
}

typedef struct Struct_80026B0C_Target_MpHigh {
    char pad[0x144];
    u8 unk144;
} Struct_80026B0C_Target_MpHigh;

typedef struct Struct_80026B0C_Player_MpHigh {
    char pad[0x4];
    Struct_80026B0C_Target_MpHigh *unk4;
    char pad2[0x2F0 - 8];
} Struct_80026B0C_Player_MpHigh;

void func_80026B0C(s32 arg0) {
    Struct_80026B0C_Target_MpHigh *target;
    target = ((Struct_80026B0C_Player_MpHigh *)D_807FC924)[arg0].unk4;
    target->unk144 = 12;
    switch (D_807552E8) {
    case 2:
        func_806F91B4(1, arg0, -3);
        break;
    case 5:
        func_806F91B4(7, arg0, -0x40);
        /* fallthrough */
    case 3:
        func_800269C8(arg0, 0);
        break;
    case 4:
        func_806F91B4(7, arg0, -1);
        break;
    }
}

typedef struct Coord_MpBigHi {
    s16 x;
    s16 y;
    s16 z;
} Coord_MpBigHi;

typedef struct Target_MpBigHi {
    char pad0[0x7C];
    f32 x;
    f32 y;
    f32 z;
    char pad88[0x154 - 0x88];
    u8 unk154;
} Target_MpBigHi;

typedef struct Player_MpBigHi {
    u8 unk0;
    char pad1[3];
    Target_MpBigHi *target;
    char pad2[0x2F0 - 8];
} Player_MpBigHi;

Coord_MpBigHi *func_806C96C4(s32);

s32 mpFindFurthestSpawn(s32 arg0) {
    s32 i;
    s32 j;
    s32 best_i;
    f32 max_dist;
    f32 min_dist;
    Coord_MpBigHi *coord;
    Target_MpBigHi *target;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    best_i = 0;
    max_dist = 0.0f;

    for (i = 0; i < 4; i++) {
        min_dist = 9999999.0f;
        coord = func_806C96C4(i);
        for (j = 0; j < (s32) D_807FC928; j++) {
            target = ((Player_MpBigHi *) D_807FC924)[j].target;
            if (((Player_MpBigHi *) D_807FC924)[j].unk0 != 0 && target->unk154 != 0x84) {
                dx = coord->x - target->x;
                dy = coord->y - target->y;
                dz = coord->z - target->z;
                dist = (dx * dx + dy * dy) + dz * dz;
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
        if (max_dist < min_dist) {
            max_dist = min_dist;
            best_i = i;
        }
    }
    return best_i;
}

void func_806C9434(s32);
s32 mpFindFurthestSpawn(s32);
void func_806CFF9C(void *);
void playerStateQueueCallback(s32, s32, u8);
extern u8 D_807FCC4B[];

typedef struct Struct_80026D40_Target_MpHigh {
    char pad[0x144];
    u8 unk144;
    char pad2[0x155 - 0x145];
    u8 unk155;
} Struct_80026D40_Target_MpHigh;

typedef struct Struct_80026D40_Player_MpHigh {
    char pad[0x2E2];
    u16 unk2E2;
    char pad2[0x2F0 - 0x2E4];
} Struct_80026D40_Player_MpHigh;

void func_80026D40(Struct_80026D40_Target_MpHigh *arg0, s32 arg1) {
    Struct_80026D40_Player_MpHigh *temp_v0;

    if (D_807552E8 == 4 && mpGetPlayerScore(arg1) == 0) {
        *(u8 *)((u8 *)D_807FCC4B + arg1 * 0x306) = 0;
        arg0->unk155++;
        playerStateQueueCallback(0x5B, 0, arg1);
        arg0->unk144 = 1;
        return;
    }
    func_806C9434(mpFindFurthestSpawn(arg1));
    temp_v0 = (Struct_80026D40_Player_MpHigh *)((u8 *)D_807FC924 + (arg1 * 0x2F0));
    temp_v0->unk2E2 |= 1;
    func_806CFF9C(arg0);
}

typedef struct Struct_80026E20_174_MpNearHi {
    char pad[0x1A4];
    u8 unk1A4;
} Struct_80026E20_174_MpNearHi;

typedef struct Struct_80026E20_FD8_MpNearHi {
    char pad[0x5C];
    u16 unk5C;
    char pad2[0x174 - 0x5E];
    Struct_80026E20_174_MpNearHi *unk174;
} Struct_80026E20_FD8_MpNearHi;

typedef struct Struct_80026E20_Player_MpNearHi {
    char pad[0x2A0];
    void *unk2A0;
    char pad2[0x2F0 - 0x2A4];
} Struct_80026E20_Player_MpNearHi;

typedef struct Struct_80026E20_Array950_MpNearHi {
    char pad[0x2FB];
    s8 unk2FB;
    char pad2;
    s8 unk2FD;
    u16 unk2FE[1];
    char pad3[0x306 - 0x300];
} Struct_80026E20_Array950_MpNearHi;

void *func_806C9FD8(void *, s8, u8);

void func_80026E20(u8 arg0, s8 arg1) {
    void *sp18;
    s32 pad0;
    s32 pad1;
    Struct_80026E20_Array950_MpNearHi *temp_v1;
    Struct_80026E20_Player_MpNearHi *temp_player;
    Struct_80026E20_FD8_MpNearHi *temp_v0;
    Struct_80026E20_174_MpNearHi *temp_a0;

    temp_v1 = &((Struct_80026E20_Array950_MpNearHi *)D_807FC950)[arg0];
    temp_player = (Struct_80026E20_Player_MpNearHi *)(D_807FC924 + (arg0 * 0x2F0));
    if (temp_v1->unk2FB + temp_v1->unk2FD > 0) {
        if (temp_player->unk2A0 != NULL) {
            temp_v0 = func_806C9FD8(temp_player->unk2A0, arg1, arg0);
            if (temp_v0 != NULL && temp_v0->unk5C == 1) {
                temp_a0 = temp_v0->unk174;
                if (temp_v1->unk2FB + temp_v1->unk2FD + arg1 <= 0) {
                    ((Struct_80026E20_Array950_MpNearHi *)D_807FC950)[temp_a0->unk1A4].unk2FE[arg0]++;
                }
            }
        }
    }
    if (D_807552E8 == 3 || D_807552E8 == 5) {
        func_800269C8(arg0, arg1);
    }
}
