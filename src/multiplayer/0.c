#include "common.h"

typedef struct MpActor MpActor;

typedef struct MpViewport {
    char pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} MpViewport;

// Match controller state (actor +0x174 of the controller actor).
typedef struct MpControllerState {
    u64 unk0;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    char pad14[4];
    MpActor *unk18;
    s16 unk1C;
    char pad1E[2];
    MpViewport *unk20[4];
    Mtx *unk30;
    u32 unk34;
    u8 unk38;
    char pad39[3];
    void *unk3C;
    s16 unk40;
    s16 unk42;
    void *unk44;
    void *unk48;
    u8 unk4C;
    char pad4D[3];
    s32 unk50[8];
    u8 unk70;
} MpControllerState;

typedef struct MpControllerActor {
    char pad0[0x60];
    s32 unk60;
    s32 unk64;
    char pad68[0x174 - 0x68];
    MpControllerState *unk174;
} MpControllerActor;

// Kong actor state (actor +0x174 of a player actor).
typedef struct MpKongState {
    char pad0[0xD4];
    s16 unkD4;
    char padD6[0x1A4 - 0xD6];
    u8 unk1A4;
    char pad1A5[0x1F0 - 0x1A5];
    s32 unk1F0;
    char pad1F4[0x200 - 0x1F4];
    s16 unk200;
    char pad202[0x246 - 0x202];
    s8 unk246;
    s8 unk247;
    char pad248[0x260 - 0x248];
    s32 unk260;
    s32 unk264;
} MpKongState;

struct MpActor {
    char pad0[0x5C];
    u16 unk5C;
    char pad5E[2];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x128 - 0xE8];
    s16 unk128;
    char pad12A[0x144 - 0x12A];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    MpKongState *unk174;
};

// D_807FC924: player array, stride 0x2F0.
typedef struct MpPlayer {
    u8 unk0;
    char pad1[3];
    MpActor *unk4;
    char pad8[0x2A0 - 8];
    void *unk2A0;
    char pad2A4[0x2E2 - 0x2A4];
    u16 unk2E2;
    char pad2E4[0x2EA - 0x2E4];
    u8 unk2EA;
    char pad2EB[0x2F0 - 0x2EB];
} MpPlayer;

// D_807FC950: per-player score array, stride 0x306.
typedef struct MpScore {
    char pad0[0x2F0];
    s16 unk2F0;
    s16 unk2F2;
    s16 unk2F4;
    s16 unk2F6;
    char pad2F8[2];
    s8 unk2FA;
    s8 unk2FB;
    s8 unk2FC;
    s8 unk2FD;
    u16 unk2FE[4];
} MpScore;

typedef struct MpSettings {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} MpSettings;

typedef struct MpFlagState {
    char pad0[0x21E];
    s16 unk21E;
} MpFlagState;

extern u8 D_80750AB8;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_1000118[];
extern u8 D_20000C0[];

Gfx *func_805FD030(Gfx *);
Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *renderTimerMinutesSecondsHUD(Gfx *, f32, f32, s32);
extern s32 D_807552E8;
extern MpScore D_807FC950[];
s32 slotQueueGetValue(s32, u8);
extern s32 D_807552EC;
extern u8 D_807FC928;
extern s32 D_807FBB60;
extern s8 D_8076A105;
void func_80714638(void);
s32 randomNonNegative(void);
typedef struct MpSpawnPoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} MpSpawnPoint;

typedef struct MpMapEntry {
    s32 unk0;
    s32 count;
    MpSpawnPoint *items;
    s32 ids[4];
    char pad1C[4];
} MpMapEntry;
extern MpMapEntry D_80026FA4[];
extern s32 D_8076A0A8;
extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
extern MpControllerActor *D_807FBB40;
void renderCallbacksRegister(void *, void *, s32);
extern MpSettings D_807552E4;
extern MpPlayer *D_807FC924;

Gfx *mpDrawTimer(Gfx *glistp, MpControllerActor *arg1) {
    MpControllerState *sp44;
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
        glistp = renderRotatedSprite(glistp, 0x60, 4, 0, 0x40, 0x40, (s32) (var_fv1 * 4.0f), (s32) (var_fa0 * 4.0f), 3.7f, 2.0f, 0xB4, 0.0f);
    }
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    return renderTimerMinutesSecondsHUD(glistp, var_fv1, var_fa0, sp44->unk8);
}

s32 mpCalcKillScore(MpScore *arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = -*(u16 *)((u8 *)arg0->unk2FE + (arg1 << 1));
    if (arg1 != 0) {
        var_v1 += arg0->unk2FE[0];
    }
    if (arg1 != 1) {
        var_v1 += arg0->unk2FE[1];
    }
    if (arg1 != 2) {
        var_v1 += arg0->unk2FE[2];
    }
    if (arg1 != 3) {
        var_v1 += arg0->unk2FE[3];
    }
    return var_v1;
}

s32 mpGetPlayerScore(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    switch (D_807552E8) {
    case 2:
    case 3:
        var_v1 = slotQueueGetValue(1, arg0);
        break;
    case 4:
    case 5:
        var_v1 = slotQueueGetValue(7, arg0);
        break;
    case 0:
    case 1:
        var_v1 = mpCalcKillScore(&D_807FC950[arg0], arg0);
        break;
    }
    return var_v1;
}

void mpDetermineWinner(MpControllerState *arg0) {
    s32 temp_v0;
    s32 var_s1;
    s32 var_s0;
    s32 var_s2;

    D_807552EC = 2;
    var_s2 = 0;
    var_s1 = -99999;
    var_s0 = 0;
    if (D_807FC928 > 0) {
        do {
            temp_v0 = mpGetPlayerScore(var_s0);
            if (var_s1 < temp_v0) {
                var_s1 = temp_v0;
                var_s2 = var_s0;
            } else if (temp_v0 == var_s1) {
                var_s2 = -1;
            }
            var_s0 += 1;
        } while (var_s0 < D_807FC928);
    }
    D_807FBB60 |= 0x40001;
    func_80714638();
    D_8076A105 = var_s2;
}

void mpUpdateMatchTimer(void) {
    MpControllerState *temp_s0;
    u64 x;

    temp_s0 = D_807FBB40->unk174;
    x = __ull_div(__ll_mul(osGetTime() - temp_s0->unk0, 0x40), 0xBB8);
    if (!(D_807FBB60 & 2)) {
        x = __ull_div(x, 0xF4240);
        temp_s0->unk8 = temp_s0->unkC - x;
    }
    if (temp_s0->unk8 <= 0) {
        temp_s0->unk8 = 0;
        mpDetermineWinner(temp_s0);
    }
    renderCallbacksRegister(mpDrawTimer, D_807FBB40, 7);
}

void mpCheckScoreLimit(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    if (D_807FC928 > 0) {
        do {
            temp_v0 = mpGetPlayerScore(var_s0);
            if ((temp_v0 >= D_807552E4.unkC) || (temp_v0 < -0x3E7)) {
                mpDetermineWinner(D_807FBB40->unk174);
                return;
            }
            var_s0++;
        } while (var_s0 < D_807FC928);
    }
}

void mpCheckLastPlayerStanding(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    if (D_807FC928 > 0) {
        do {
            if (mpGetPlayerScore(var_s0) != 0) {
                var_s1++;
            }
            var_s0++;
        } while (var_s0 < D_807FC928);
    }
    if (var_s1 < 2) {
        mpDetermineWinner(D_807FBB40->unk174);
    }
}

Gfx *mpDrawGlyph(Gfx *glistp, s16 *arg1, s16 arg2, void *arg3, s32 arg4) {
    gDPLoadTextureBlock(glistp++, arg3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_WRAP, G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glistp++, (*arg1) << 2, arg2 << 2, (*arg1 + arg4 * 8) << 2, (arg2 + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    *arg1 += arg4 * 8;
    return glistp;
}

Gfx *func_800246EC(Gfx *glistp, MpControllerState *arg1, f32 arg2) {
    s16 spAE;
    s32 i;
    s32 nxt;
    s32 off;
    s32 sc;
    s32 half;
    s16 y;
    s32 alpha;
    MpViewport *sub;
    MpPlayer *plr;
    MpScore *scp;
    MpControllerState *p;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gSPSetOtherMode(glistp++, G_SETOTHERMODE_L, 3, 29, 0x404240);
    gDPSetCombine(glistp++, 0xFFFFFF, 0xFFFCF279);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    i = 0;
    if ((s32) D_807FC928 > 0) {
        p = arg1;
        off = 0;
        do {
            sub = p->unk20[0];
            alpha = 0xFF;
            plr = (MpPlayer *)((u8 *)D_807FC924 + off);
            if (plr->unk2EA != 0) {
                alpha = plr->unk4->unk128 & 0xFF;
                if (plr->unk4->unk128 >= 0x100) {
                    alpha = 0xFF;
                } else {
                    alpha = plr->unk4->unk128 & 0xFF;
                }
            }
            if (plr->unk0 == 0 || alpha == 0) {
                nxt = i + 1;
            } else {
                gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
                scp = &D_807FC950[i];
                if (scp != 0) {}  // FAKE: dead use makes scp a cross-block temp (steers uopt)
                if (D_80750AB8 == 0) {
                    nxt = i + 1;
                    spAE = sub->unk8 - 0x30;
                } else {
                    nxt = i + 1;
                    spAE = (s16) ((f32) nxt * arg2 - 20.0);
                    if (D_1000118) {}  // FAKE: deadsweep dead statement (steers uopt)
                }
                y = sub->unk6 + 8;
                half = scp->unk2FB;
                if (half < 0) {
                    sc = 0;
                } else {
                    sc = half;
                }
                half = sc / 2;
                if (half != 0) {
                    glistp = mpDrawGlyph(glistp, &spAE, y, arg1->unk44, half);
                }
                alpha = sc - half * 2;
                if (alpha != 0) {
                    glistp = mpDrawGlyph(glistp, &spAE, y, arg1->unk48, alpha);
                }
                if (D_807FC928 == 0) {}  // FAKE: deadsweep dead statement (steers uopt)
            }
            i = nxt;
            p = (MpControllerState *)((u8 *)p + 4);
            off += 0x2F0;
        } while (nxt < (s32) D_807FC928);
        if (D_807FC928 == 0) {}  // FAKE: deadsweep dead statement (steers uopt)
    }
    return glistp;
}

int _sprintf(char *, const char *, ...);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
Gfx *func_800246EC(Gfx *, MpControllerState *, f32);

Gfx *mpDrawPlayerScores(Gfx *glistp, MpControllerActor *arg1) {
    char sp98[32];
    f32 temp_fs0;
    f32 temp_fs2;
    s32 var_s2;
    MpControllerState *temp_s0;
    void *temp;

    temp_s0 = arg1->unk174;
    temp = temp_s0->unk20[0];
    temp_fs2 = (f32) D_80744490 / (f32) (D_807FC928 + 1);
    temp_fs0 = (f32) (((MpViewport *)temp)->unk6 + 8);
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
        if (D_807FC928 > 0) {
            do {
                _sprintf(sp98, "%d", mpGetPlayerScore(var_s2));
                temp = textDrawStringVtx(glistp, 1, (s16) ((((f32) (var_s2 + 1) * temp_fs2) - (f32) ((f32) textGetStringWidth(1, sp98) * 0.25)) * 8.0f), (s16) (temp_fs0 * 8.0f), sp98, 4);
                var_s2 = var_s2 + 1;
                glistp = temp;
            } while (var_s2 < D_807FC928);
        }
    }
    return glistp;
}

u32 textGetFontHeight(s32);

Gfx *func_80024CA4(Gfx *arg0, MpControllerActor *arg1) {
    MpControllerState *sp104;
    Gfx *g0;
    f32 fx;
    f32 fy;
    s32 temp_s2;
    f32 spF0;
    Gfx *var_s0;
    char spCC[32];
    s32 var_s7;
    s32 var_s1;
    f32 spC0;
    s32 pre;
    MpViewport *rect;
    Gfx *g2;

    sp104 = arg1->unk174;
    spF0 = (f32) textGetFontHeight(1);
    spC0 = (f32) textGetFontHeight(1);
    var_s0 = func_800246EC(arg0, sp104, 0.0f);
    gSPDisplayList(var_s0++, &D_1000118);
    gSPMatrix(var_s0++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(var_s0++, sp104->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(var_s0++);
    gDPSetCombineMode(var_s0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (var_s7 = 0; var_s7 < D_807FC928; var_s7++) {
            rect = sp104->unk20[var_s7];
            if (D_807FC924[var_s7].unk4->unk154 == 0x84) {
                fx = (f32) ((f64) rect->unk4 + ((f64) (rect->unk8 - rect->unk4) * 0.5));
                fy = (f32) ((f64) rect->unk6 + ((f64) (rect->unkA - rect->unk6) * 0.5));
                var_s1 = (u8) D_807FC924[var_s7].unk4->unk128;
                gDPSetPrimColor(var_s0++, 0, 0, 255, 255, 255, (0xFF - var_s1));
                _sprintf(spCC, "BAD LUCK");
                fx = (f32) ((f64) fx - ((f64) textGetStringWidth(1, spCC) * 0.25));
                fy = (f32) ((f64) fy - ((f64) spF0 * 0.25));
                var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), (s16) (fy * 8.0f), spCC, 4);
            } else {
                var_s1 = 0xFF;
            }
            if (var_s1 == 0) {
            } else {
                g0 = var_s0++;
                g0->words.w1 = (var_s1 & 0xFF) | 0xFFFFFF00;
                g0->words.w0 = 0xFA000000;
                if (sp104->unk70 == 0) {
                    fx = (f32) rect->unk4 + 4.0f;
                    fy = (f32) rect->unkA - ((8.0f + spC0) * 0.5f);
                    fy = fy * 8.0f;
                    pre = (s32) slotQueueGetValue(3, var_s7);
                    if (pre != 0) {
                        g0 = var_s0++; g0->words.w0 = 0xFA000000; g0->words.w1 = (var_s1 & 0xFF) | 0x641E0000; // FAKE: same-line packet stores steer as1 scheduling
                        _sprintf(spCC, "%d", pre);
                    } else {
                        _sprintf(spCC, "%d", slotQueueGetValue(2, var_s7));
                    }
                    temp_s2 = (s16) fy;
                    var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), temp_s2, spCC, 4);
                    if (pre != 0) {
                        g2 = var_s0++;
                        g2->words.w0 = 0xFA000000;
                        g2->words.w1 = (var_s1 & 0xFF) | 0xFFFFFF00;
                    }
                    _sprintf(spCC, "%d", slotQueueGetValue(4, var_s7));
                    fx = (f32) rect->unk8 - ((f32) (textGetStringWidth(1, spCC) + 8) * 0.5f);
                    var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), temp_s2, spCC, 4);
                }
                _sprintf(spCC, "%d", mpGetPlayerScore(var_s7));
                fx = (f32) rect->unk8 - (((f32) textGetStringWidth(1, spCC) * 0.5f) + 50.0f);
                fy = (f32) ((f64) rect->unk6 + (8.0 + ((f64) (8.0f - (spC0 * 0.5f)) * 0.5)));
                fy = fy * 8.0f;
                var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), (s16) fy, spCC, 4);
            }
    }
    return var_s0;
}

Gfx *func_80024CA4(Gfx *, MpControllerActor *);

Gfx *mpDrawHud(Gfx *glistp, MpControllerActor *arg1) {
    s32 t0 = D_807552E4.unk8 >= 2;
    s32 cond = D_807FBB60 & 3;

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    if (!cond) {
        if (D_807552E4.unk0 == 0) {
            if ((D_807552E4.unk8 == 1) || t0) {
                glistp = mpDrawPlayerScores(glistp, arg1);
            }
        } else if ((D_807552E4.unk8 == 1) || t0) {
            glistp = func_80024CA4(glistp, arg1);
        }
    }
    return glistp;
}

MpMapEntry *mpFindCurrentMapEntry(void) {
    s32 i;
    MpMapEntry *ret = NULL;

    for (i = 0; (i < 4U) && (ret == NULL); i++) {
        if (D_8076A0A8 == D_80026FA4[i].unk0) {
            ret = &D_80026FA4[i];
        }
    }
    return ret;
}

s32 mpRandomSpawnDelay(void) {
    return (((randomNonNegative() >> 15) % 0x7FFF) % 211) + 0x5A;
}

extern u8 D_8074E77C[];
extern u8 D_8071F3C0;
extern u8 D_807207BC;
void effectFreeAndUnlink(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8071498C(void *);
s32 func_80714C08(void *, f32, void *, s32, s32);

s32 mpUpdateScoreEffects(void) {
    s32 i;
    s32 ret = -1;
    s32 temp_s3;
    MpScore *sc;
    MpKongState *ac;
    s32 var_s6;
    void *p;

    i = 0;
    if (D_807FC928 > 0) {
        do {
            ac = D_807FC924[i].unk4->unk174;
            sc = &D_807FC950[i];
            if (slotQueueGetValue(1, i) != 0) {
                temp_s3 = sc->unk2FD + sc->unk2FB;
                if (ac->unk260 == 0) {
                    p = (void *)(s32)&D_8071F3C0;
                    switch (D_8074E77C[i]) {
                    case 0:
                    case 3:
                        var_s6 = 0xF;
                        break;
                    case 1:
                    case 2:
                    case 4:
                    case 5:
                        var_s6 = 0xD;
                        break;
                    }
                    func_807149B8(1);
                    func_807149FC(-1);
                    func_80714998(2);
                    func_807149C8(0xFF, 0xFF, 0xFF, 0x7F);
                    func_8071498C(p);
                    ac->unk260 = func_80714C08(&D_807207BC, 0.5f, D_807FC924[i].unk4, var_s6, 2);
                    sc->unk2FA = temp_s3;
                }
                if (sc->unk2FA < temp_s3) {
                    sc->unk2FA = temp_s3;
                }
                ret = i;
            } else {
                if (ac->unk260 != 0) {
                    effectFreeAndUnlink(ac->unk260);
                    ac->unk260 = 0;
                    sc = &D_807FC950[i];
                    sc->unk2FA = 0;
                }
            }
            i++;
        } while (i < D_807FC928);
    }
    return ret;
}

s32 modelSlotFindByType(s32, s32 *, f32 *, f32 *, f32 *, s16 *, s16 *);

s32 mpFindModelSlotByType(s32 arg0) {
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    sp3C = 0;
    sp2E = 0;
    sp2C = 0;
    return modelSlotFindByType(arg0, &sp3C, &sp38, &sp34, &sp30, &sp2E, &sp2C);
}

s32 func_8071432C(void);
void *actorFindByType();
s32 delayedSpawnQueueContains(s32, s32, s16, s16, s16);
void func_806F5FE8(s32, s16, s16, s16, s32);

extern s32 D_807552F0;

void func_80025654(MpControllerState *arg0) {
    s32 temp;
    MpSpawnPoint * volatile sp20; // FAKE: volatile forces stack home

    sp20 = mpFindCurrentMapEntry()->items;
    if (func_8071432C() != 0 && !(D_807FBB60 & 2)) {
        if (D_807552E8 == 3) {
            mpUpdateMatchTimer();
        }
        temp = mpUpdateScoreEffects();
        if (temp == -1) {
            if (arg0->unk4C == 0 && actorFindByType(0x7A) == 0 && mpFindModelSlotByType(0x1D2) == 0) {
                MpSpawnPoint *pos = sp20;
                if (delayedSpawnQueueContains(0x1D2, 0, pos->unk0, pos->unk2, pos->unk4) == 0) {
                    pos = sp20;
                    func_806F5FE8(0x1D2, pos->unk0, pos->unk2, pos->unk4, 10);
                }
            }
        } else if (D_807552E8 == 5 && mpGetPlayerScore(temp) >= D_807552F0) {
            mpDetermineWinner(arg0);
        }
        if (arg0->unk4C != 0) {
            arg0->unk4C--;
        }
    }
}

f32 randomFloat(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_806F5F2C(s32, s32, s16, s16, s32);

void mpUpdateItemSpawns(void) {
    MpMapEntry *sp84;
    s32 sp80;
    s32 sp7C;
    MpSpawnPoint *items;
    MpSpawnPoint *item;
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

    sp84 = mpFindCurrentMapEntry();
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
                        num_outer = ((randomNonNegative() >> 15) % 0x7FFF % 3) + 1;
                    }
                    if (num_outer > 0) {
                        do {
                            k = 0;
                            num_inner = ((randomNonNegative() >> 15) % 0x7FFF % 3) + 1;
                            temp_s4 = (s16) mpRandomSpawnDelay();
                            fs1 = (f32) ((((f64) randomFloat() * 0.8) + 0.2) * (f64) item->unk6);
                            angle = (randomNonNegative() >> 15) % 4096;
                            fs3 = (f32) item->unk0;
                            fs0 = (f32) (item->unk2 - 23);
                            fs4 = (f32) item->unk4;
                            fs3 += fs1 * func_80612794(angle);
                            fs4 += fs1 * func_80612790(angle);
                            if (num_inner >= 2) {
                                angle = (randomNonNegative() >> 15) % 4096;
                                fs1 = 15.0f;
                                fs2 = 4096.0f / (f32) num_inner;
                            } else {
                                fs1 = 0.0f;
                                fs2 = 0.0f;
                                angle = 0;
                            }
                            if (num_inner > 0) {
                                s2_val = (s16) fs0;
                                do {
                                    f32 x = fs3 + func_80612794(angle) * fs1;
                                    f32 z = fs4 + func_80612790(angle) * fs1;
                                    func_806F5F2C(0x7A, temp_s4, (s16) x, s2_val, (s32) z);
                                    k++;
                                    angle += fs2;
                                    angle &= 0xFFF;
                                } while (k != num_inner);
                            }
                            j++;
                        } while (j != num_outer);
                    }
                    item->unk8 = mpRandomSpawnDelay();
                }
                item++;
                sp7C++;
            } while (sp7C < sp84->count);
        }
    }
}

void *spawnNodeActivate(s16, s32);
void *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);

void mpUpdateRandomSpawner(MpControllerState *arg0) {
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
            arg0->unk1C = (((randomNonNegative() >> 15) % 0x7FFF) % 271) + 30;
        }
    } else {
        arg0->unk1C--;
    }

    if (var_a2 != 0 && arg0->unk1C == 0) {
        var_a2 = (((randomNonNegative() >> 15) % 0x7FFF) % 3) + 1;
        if (var_a2 == 3) {
            var_a2 += (((randomNonNegative() >> 15) % 0x7FFF) % 5);
        }
        arg0->unk18 = spawnNodeActivate(var_a2, 0);
        if (arg0->unk18 == NULL) {
            arg0->unk18 = spawnNodeSpawnById((s16)var_a2, 0, 0, 0, 0, 0, 0);
        }
        if (arg0->unk18 != NULL) {
            arg0->unk18->unk154 = 0x36;
            arg0->unk18->unk155 = 0;
        }
    }
}

void func_806D0468(void *, s32);
void func_806F54E0(u8, s16, u8);
void func_806C9974(u8, s32);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, void *, u8);
void playerStateQueueCallback(s32, void *, u8);

void mpApplyPendingEffect(s32 arg0) {
    MpActor *act;
    MpKongState *st;
    MpActor *oact;
    MpKongState *ost;
    s32 i;

    act = D_807FC924[arg0].unk4;
    st = act->unk174;
    switch (st->unk264) {
    case 0:
        func_806D0468(act, 2);
        func_806F54E0(arg0, 0x8E, 0);
        break;
    case 1:
        i = 0;
        if (D_807FC928 > 0) {
            do {
                oact = D_807FC924[i].unk4;
                ost = oact->unk174;
                if (i != arg0 && ost->unkD4 == 0 && oact->unk154 != 0x84) {
                    playerStateQueueCallback(0x27, act, i);
                    ost->unk200 = 0x96;
                }
                i++;
            } while (i < D_807FC928);
        }
        break;
    case 2:
        st->unk1F0 |= 0x20;
        st->unk1F0 &= ~0x08000000;
        func_806F54E0(arg0, 0x8E, 0);
        break;
    case 3:
        actorSpawnEffectChild(act->unk7C, act->unk80, act->unk84, 0.1f, 0.1f, act, 1);
        break;
    case 4:
        switch ((u32) (randomNonNegative() >> 15) % 5U) {
        case 0:
            func_806D0468(act, 0);
            func_806F54E0(arg0, 0x8E, 0);
            break;
        case 1:
            st->unk200 = 0x96;
            st->unk1F0 |= 0x80;
            break;
        case 2:
            st->unk1F0 |= 0x08000000;
            st->unk1F0 &= ~0x20;
            st->unk200 = 0x96;
            break;
        case 3:
            func_806C9974(arg0, 0x40);
            break;
        case 4:
            actorSpawnEffectChild(act->unk7C, act->unk80, act->unk84, 0.1f, 0.1f, act, 1);
            break;
        }
        break;
    }
    st->unk264 = -1;
}


void csModelStateSetFirstByte(s16, s32);

void func_80025F84(void) {
    MpMapEntry *temp;
    s32 i;

    temp = mpFindCurrentMapEntry();
    i = 0;
    while (i < 4 && temp->ids[i] != -1) {
        csModelStateSetFirstByte(temp->ids[i], 0);
        i++;
    }
}


void mpFreeHudIcons(MpControllerState *arg0) {
    s32 i;

    if (arg0->unk70 != 0) {
        for (i = 0; i < D_807FC928 * 2; i++) {
            if (arg0->unk50[i] != 0) {
                effectFreeAndUnlink(arg0->unk50[i]);
            }
            arg0->unk50[i] = 0;
        }
    }
    arg0->unk70 = 0;
}

void slotQueueAddValue(s32, u8, s32);
MpViewport *cameraFindViewportEntry(u8);
void func_806C9AE0(void);
s32 n_alSndpPlay(s32, s32, s32, s32, f32, s32, void *);
void n_alSndpPostEvent(void *, s32, s16);
void sfxPlayOnFreeSlot(s16, s32, f32, f32, s32, s32);
void func_806F5FA0(s32, s32, s32);
void slotQueueInit(s32);
void *heapAlloc(s32);
void *assetLoad(s32, s32, s32, s32);
void func_8071495C(void);
void func_80714944(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
extern s32 D_8076D1F8;
extern u32 D_80767CC0;
extern u64 D_807445B0;
extern u8 D_80026F70;

typedef struct MpHudIconTableEntry {
    void *unk0;
    f32 unk4;
    s32 unk8;
} MpHudIconTableEntry;
extern MpHudIconTableEntry D_80027024[];

void mpUpdate(void) {
    MpControllerState *s7;
    s32 i;
    s32 j;
    s32 k;
    s32 flag;
    MpViewport *vp;
    f32 x;
    f32 y;
    s32 snd;
    s32 va;
    s32 vb;
    s32 vc;

    s7 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        flag = 0;
        func_806C9AE0();
        for (i = 0; i < D_807FC928; i++) {
            s7->unk20[i] = cameraFindViewportEntry(i);
        }
        D_807552E4.unk8 = 1;
        s7->unk0 = osGetTime();
        s7->unk34 = D_80767CC0;
        s7->unk38 = 0;
        s7->unk42 = 0;
        s7->unk40 = 0;
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &s7->unk3C);
        D_80026F70 = 0;
        switch (D_807552E4.unk4) {
        case 3:
        case 5:
            flag = 1;
        case 2:
            if (flag != 0) {
                MpSpawnPoint *q = mpFindCurrentMapEntry()->items;
                func_806F5FE8(0x1D2, q->unk0, q->unk2, q->unk4, 10);
            }
            break;
        case 4:
            for (i = 0; i < D_807FC928; i++) {
                slotQueueAddValue(7, i, ((s16 *)&D_807552E4.unkC)[1]);
            }
            slotQueueInit(0);
            break;
        }
        if (D_807552E4.unk0 == 0 && D_8076A0A8 == 0x6B) {
            func_806F5FA0(0x24E, 0xD4, 0x205);
            func_806F5FA0(0x24E, 0xD4, 0x285);
            func_806F5FA0(0x212, 0xD4, 0x24E);
            func_806F5FA0(0x28E, 0xD4, 0x247);
        }
        s7->unk30 = heapAlloc(0x40);
        guScale(s7->unk30, 0.5f, 0.5f, 1.0f);
        s7->unkC = D_807552E4.unkC;
        s7->unkC = s7->unkC * 60;
        D_807FBB40->unk64 |= 2;
        s7->unk44 = assetLoad(0xE, 0xB9, 0, 0);
        s7->unk48 = assetLoad(0xE, 0xBA, 0, 0);
        s7->unk10 = 0;
    }
    s7->unk0 += D_807445B0;
    switch (D_807552E4.unk8) {
    case 1:
        switch (D_807552E4.unk4) {
        case 3:
        case 5:
            func_80025654(s7);
            break;
        case 2:
            mpUpdateItemSpawns();
            break;
        case 0:
            mpUpdateMatchTimer();
            break;
        case 1:
            mpCheckScoreLimit();
            break;
        case 4:
            mpCheckLastPlayerStanding();
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
    if (D_807552E4.unk0 == 0) {
        for (i = 0; i < D_807FC928; i++) {
            mpApplyPendingEffect(i);
        }
        if (D_807FC928 == 2) {
            mpUpdateRandomSpawner(s7);
        }
    } else if ((D_807FBB60 & 2) || ((s16)((f32)s7->unk10 * 0.033333335f) & 1)) {
        mpFreeHudIcons(s7);
    } else if (s7->unk70 == 0) {
        for (j = 0; j != 2; j++) {
            for (k = 0; k < D_807FC928; k++) {
                if (D_807FC924[k].unk0 == 0) {
                    continue;
                }
                vp = s7->unk20[k];
                func_8071495C();
                func_807149FC(-1);
                func_80714998(0);
                func_80714944(D_80027024[j].unk8);
                if (j == 0) {
                    x = (f32)(vp->unk4 + 0xB);
                } else {
                    x = (f32)(vp->unk8 - 0xB);
                }
                y = (f32)(vp->unkA - 0xB);
                s7->unk50[j * D_807FC928 + k] = func_80714CC0(D_80027024[j].unk0, D_80027024[j].unk4, x, y, -10.0f);
            }
        }
        s7->unk70 = 1;
    }
    s7->unk10 += 1;
    s7->unk10 = s7->unk10 % 180;
    va = s7->unk40 - 100;
    if (va < 0x1F40) {
        s7->unk40 = 0x1F40;
    } else {
        s7->unk40 = va;
    }
    vb = s7->unk42 + 0x3E8;
    if (s7->unk40 < vb) {
        s7->unk42 = s7->unk40;
    } else {
        s7->unk42 = vb;
    }
    n_alSndpPostEvent(s7->unk3C, 8, s7->unk42);
    if (D_80026F70 & 0x80) {
        s7->unk40 = 0x7FFF;
        D_80026F70 &= ~0x80;
    }
    if (D_80026F70 & 7) {
        if (D_80767CC0 - s7->unk34 >= 6) {
            s7->unk34 = D_80767CC0;
            s7->unk38 = 0;
            snd = 0x1E8;
            if (D_80026F70 & 4) {
                snd = 0x1EA;
            } else if (D_80026F70 & 3) {
                if ((D_80026F70 & 2) * 300 + 500 < (randomNonNegative() >> 15) % 1000) {
                    if (((randomNonNegative() >> 15) % 1000) & 1) {
                        snd = 0x1E7;
                    } else {
                        snd = 0x1EA;
                    }
                }
            }
            sfxPlayOnFreeSlot(snd, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
        }
        vc = s7->unk40 + 0x4650;
        if (vc >= 0x8000) {
            s7->unk40 = 0x7FFF;
        } else {
            s7->unk40 = vc;
        }
        D_80026F70 &= ~7;
    }
    if (s7->unk38 * 35 + 0x384 < D_80767CC0 - s7->unk34) {
        sfxPlayOnFreeSlot(0x1E9, s7->unk38 * 3000 + 0x511F, 64.0f, 1.0f, 0xA, 0x80);
        s7->unk38++;
        if (s7->unk38 == 5) {
            s7->unk38 = 0;
            s7->unk34 = D_80767CC0;
        }
    }
    renderCallbacksRegister(mpDrawHud, D_807FBB40, 7);
}


void mpSetFlags(u8 arg0) {
    D_80026F70 |= arg0;
}

extern void func_806F0C18(void *);
extern s32 func_80714608(s32);
extern MpFlagState *D_807FD580;

void func_800268DC(MpActor *arg0, MpKongState *arg1, MpScore *arg2) {
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
        D_807FD580->unk21E = 0;
    }
    if (D_807552E8 == 3 || D_807552E8 == 5) {
        slotQueueAddValue(1, arg1->unk1A4, -10);
    }
}

void func_8002698C(MpKongState *arg0) {
    if (D_807552E8 == 2) {
        slotQueueAddValue(1, arg0->unk1A4, -3);
    }
}

void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void mpDropItemsOnHit(u8 arg0, s8 arg1) {
    s32 pad0;
    MpControllerState *ctrl;
    s32 sp34;
    s32 sp30;
    MpActor *s0;
    MpScore *s1;

    s0 = D_807FC924[arg0].unk4;
    s1 = &D_807FC950[arg0];
    sp34 = s1->unk2FB + s1->unk2FD + arg1;
    sp30 = s1->unk2FA - sp34;
    if (slotQueueGetValue(1, arg0) != 0 && (sp34 <= 0 || sp30 >= 2)) {
        ctrl = ((MpControllerActor *)actorFindByType(0x13E))->unk174;
        ctrl->unk4C = 1;
        slotQueueAddValue(1, arg0, -10);
        if (D_807552E8 == 5) {
            func_80025F84();
        }
        actorSpawnNodeEntryScaled(0x7A, s0->unk7C, s0->unk80, s0->unk84, s0->unkE6, 1, -1, 0);
        s1->unk2FA = 0;
    }
}

void mpApplyDeathPenalty(s32 arg0) {
    MpActor *target;
    target = D_807FC924[arg0].unk4;
    target->unk144 = 12;
    switch (D_807552E8) {
    case 2:
        slotQueueAddValue(1, arg0, -3);
        break;
    case 5:
        slotQueueAddValue(7, arg0, -0x40);
        /* fallthrough */
    case 3:
        mpDropItemsOnHit(arg0, 0);
        break;
    case 4:
        slotQueueAddValue(7, arg0, -1);
        break;
    }
}

typedef struct MpSpawnCoord {
    s16 x;
    s16 y;
    s16 z;
} MpSpawnCoord;

MpSpawnCoord *func_806C96C4(s32);

s32 mpFindFurthestSpawn(s32 arg0) {
    s32 i;
    s32 j;
    s32 best_i;
    f32 max_dist;
    f32 min_dist;
    MpSpawnCoord *coord;
    MpActor *target;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    best_i = 0;
    max_dist = 0.0f;

    for (i = 0; i < 4; i++) {
        min_dist = 9999999.0f;
        coord = func_806C96C4(i);
        for (j = 0; j < D_807FC928; j++) {
            target = D_807FC924[j].unk4;
            if (D_807FC924[j].unk0 != 0 && target->unk154 != 0x84) {
                dx = coord->x - target->unk7C;
                dy = coord->y - target->unk80;
                dz = coord->z - target->unk84;
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
void func_806CFF9C(void *);

void mpRespawnPlayer(MpActor *arg0, s32 arg1) {
    if (D_807552E8 == 4 && mpGetPlayerScore(arg1) == 0) {
        D_807FC950[arg1].unk2FB = 0;
        arg0->unk155++;
        playerStateQueueCallback(0x5B, 0, arg1);
        arg0->unk144 = 1;
        return;
    }
    func_806C9434(mpFindFurthestSpawn(arg1));
    D_807FC924[arg1].unk2E2 |= 1;
    func_806CFF9C(arg0);
}

MpActor *func_806C9FD8(void *, s8, u8);

void mpCreditKill(u8 arg0, s8 arg1) {
    void *sp18;
    s32 pad0;
    s32 pad1;
    MpScore *temp_v1;
    MpPlayer *temp_player;
    MpActor *temp_v0;
    MpKongState *temp_a0;

    temp_v1 = &D_807FC950[arg0];
    temp_player = &D_807FC924[arg0];
    if (temp_v1->unk2FB + temp_v1->unk2FD > 0) {
        if (temp_player->unk2A0 != NULL) {
            temp_v0 = func_806C9FD8(temp_player->unk2A0, arg1, arg0);
            if (temp_v0 != NULL && temp_v0->unk5C == 1) {
                temp_a0 = temp_v0->unk174;
                if (temp_v1->unk2FB + temp_v1->unk2FD + arg1 <= 0) {
                    D_807FC950[temp_a0->unk1A4].unk2FE[arg0]++;
                }
            }
        }
    }
    if (D_807552E8 == 3 || D_807552E8 == 5) {
        mpDropItemsOnHit(arg0, arg1);
    }
}
