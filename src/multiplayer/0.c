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

// gPlayerSlots: player array, stride 0x2F0.
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

Gfx *gfxInit2DDisplayList(Gfx *);
Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *renderTimerMinutesSecondsHUD(Gfx *, f32, f32, s32);
extern s32 D_807552E8;
extern MpScore D_807FC950[];
s32 slotQueueGetValue(s32, u8);
extern s32 D_807552EC;
extern u8 gPlayerCount;
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
extern s32 gCurrentMap;
extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
extern MpControllerActor *D_807FBB40;
void renderCallbacksRegister(void *, void *, s32);
extern MpSettings D_807552E4;
extern MpPlayer *gPlayerSlots;

Gfx *mpDrawTimer(Gfx *glistp, MpControllerActor *controller) {
    MpControllerState *state;
    f32 posX;
    f32 posY;

    state = controller->unk174;
    if (D_80750AB8 == 1) {
        posX = 278.0f;
        posY = 210.0f;
    } else {
        posX = (f32) (D_80744490 * 0.5);
        posY = (f32) (D_80744494 * 0.5);
    }
    glistp = gfxInit2DDisplayList(glistp);
    gSPDisplayList(glistp++, &D_1000118);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPPipeSync(glistp++);
    if (D_80750AB8 == 1) {
        gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(glistp++, 0, 0, 0, 120, 255, 80);
        glistp = renderRotatedSprite(glistp, 0x60, 4, 0, 0x40, 0x40, (s32) (posX * 4.0f), (s32) (posY * 4.0f), 3.7f, 2.0f, 0xB4, 0.0f);
    }
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    return renderTimerMinutesSecondsHUD(glistp, posX, posY, state->unk8);
}

s32 mpCalcKillScore(MpScore *score, s32 playerIndex) {
    s32 netKills;

    netKills = -*(u16 *)((u8 *)score->unk2FE + (playerIndex << 1));
    if (playerIndex != 0) {
        netKills += score->unk2FE[0];
    }
    if (playerIndex != 1) {
        netKills += score->unk2FE[1];
    }
    if (playerIndex != 2) {
        netKills += score->unk2FE[2];
    }
    if (playerIndex != 3) {
        netKills += score->unk2FE[3];
    }
    return netKills;
}

s32 mpGetPlayerScore(s32 playerIndex) {
    s32 score;

    score = 0;
    switch (D_807552E8) {
    case 2:
    case 3:
        score = slotQueueGetValue(1, playerIndex);
        break;
    case 4:
    case 5:
        score = slotQueueGetValue(7, playerIndex);
        break;
    case 0:
    case 1:
        score = mpCalcKillScore(&D_807FC950[playerIndex], playerIndex);
        break;
    }
    return score;
}

void mpDetermineWinner(MpControllerState *controllerState) {
    s32 score;
    s32 highestScore;
    s32 i;
    s32 winnerIndex;

    D_807552EC = 2;
    winnerIndex = 0;
    highestScore = -99999;
    i = 0;
    if (gPlayerCount > 0) {
        do {
            score = mpGetPlayerScore(i);
            if (highestScore < score) {
                highestScore = score;
                winnerIndex = i;
            } else if (score == highestScore) {
                winnerIndex = -1;
            }
            i += 1;
        } while (i < gPlayerCount);
    }
    D_807FBB60 |= 0x40001;
    func_80714638();
    D_8076A105 = winnerIndex;
}

void mpUpdateMatchTimer(void) {
    MpControllerState *state;
    u64 x;

    state = D_807FBB40->unk174;
    x = __ull_div(__ll_mul(osGetTime() - state->unk0, 0x40), 0xBB8);
    if (!(D_807FBB60 & 2)) {
        x = __ull_div(x, 0xF4240);
        state->unk8 = state->unkC - x;
    }
    if (state->unk8 <= 0) {
        state->unk8 = 0;
        mpDetermineWinner(state);
    }
    renderCallbacksRegister(mpDrawTimer, D_807FBB40, 7);
}

void mpCheckScoreLimit(void) {
    s32 score;
    s32 i;

    i = 0;
    if (gPlayerCount > 0) {
        do {
            score = mpGetPlayerScore(i);
            if ((score >= D_807552E4.unkC) || (score < -0x3E7)) {
                mpDetermineWinner(D_807FBB40->unk174);
                return;
            }
            i++;
        } while (i < gPlayerCount);
    }
}

void mpCheckLastPlayerStanding(void) {
    s32 i;
    s32 aliveCount;

    aliveCount = 0;
    i = 0;
    if (gPlayerCount > 0) {
        do {
            if (mpGetPlayerScore(i) != 0) {
                aliveCount++;
            }
            i++;
        } while (i < gPlayerCount);
    }
    if (aliveCount < 2) {
        mpDetermineWinner(D_807FBB40->unk174);
    }
}

Gfx *mpDrawGlyph(Gfx *glistp, s16 *pX, s16 y, void *texture, s32 count) {
    gDPLoadTextureBlock(glistp++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_WRAP, G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glistp++, (*pX) << 2, y << 2, (*pX + count * 8) << 2, (y + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    *pX += count * 8;
    return glistp;
}

Gfx *func_800246EC(Gfx *glistp, MpControllerState *controllerState, f32 spacing) {
    s16 glyphX;
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
    if ((s32) gPlayerCount > 0) {
        p = controllerState;
        off = 0;
        do {
            sub = p->unk20[0];
            alpha = 0xFF;
            plr = (MpPlayer *)((u8 *)gPlayerSlots + off);
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
                    glyphX = sub->unk8 - 0x30;
                } else {
                    nxt = i + 1;
                    glyphX = (s16) ((f32) nxt * spacing - 20.0);
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
                    glistp = mpDrawGlyph(glistp, &glyphX, y, controllerState->unk44, half);
                }
                alpha = sc - half * 2;
                if (alpha != 0) {
                    glistp = mpDrawGlyph(glistp, &glyphX, y, controllerState->unk48, alpha);
                }
                if (gPlayerCount == 0) {}  // FAKE: deadsweep dead statement (steers uopt)
            }
            i = nxt;
            p = (MpControllerState *)((u8 *)p + 4);
            off += 0x2F0;
        } while (nxt < (s32) gPlayerCount);
        if (gPlayerCount == 0) {}  // FAKE: deadsweep dead statement (steers uopt)
    }
    return glistp;
}

int _sprintf(char *, const char *, ...);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
Gfx *func_800246EC(Gfx *glistp, MpControllerState *controllerState, f32 spacing);

Gfx *mpDrawPlayerScores(Gfx *glistp, MpControllerActor *controller) {
    char scoreStr[32];
    f32 posY;
    f32 posXStep;
    s32 i;
    MpControllerState *state;
    void *temp;

    state = controller->unk174;
    temp = state->unk20[0];
    posXStep = (f32) D_80744490 / (f32) (gPlayerCount + 1);
    posY = (f32) (((MpViewport *)temp)->unk6 + 8);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    glistp = func_800246EC(glistp, state, posXStep);
    if (D_807552E8 != 3) {
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 180);
        gSPDisplayList(glistp++, &D_1000118);
        gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(glistp++, state->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(glistp++);
        gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 180);
        posY += 8.0f;
        i = 0;
        if (gPlayerCount > 0) {
            do {
                _sprintf(scoreStr, "%d", mpGetPlayerScore(i));
                temp = textDrawStringVtx(glistp, 1, (s16) ((((f32) (i + 1) * posXStep) - (f32) ((f32) textGetStringWidth(1, scoreStr) * 0.25)) * 8.0f), (s16) (posY * 8.0f), scoreStr, 4);
                i = i + 1;
                glistp = temp;
            } while (i < gPlayerCount);
        }
    }
    return glistp;
}

u32 textGetFontHeight(s32);

Gfx *mpDrawPlayerViewportHud(Gfx *glist, MpControllerActor *controller) {
    MpControllerState *state;
    Gfx *g0;
    f32 fx;
    f32 fy;
    s32 textY;
    f32 fontHeight;
    Gfx *curGlist;
    char textBuf[32];
    s32 playerIndex;
    s32 alpha;
    f32 fontHeight2;
    s32 pre;
    MpViewport *rect;
    Gfx *g2;

    state = controller->unk174;
    fontHeight = (f32) textGetFontHeight(1);
    fontHeight2 = (f32) textGetFontHeight(1);
    curGlist = func_800246EC(glist, state, 0.0f);
    gSPDisplayList(curGlist++, &D_1000118);
    gSPMatrix(curGlist++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(curGlist++, state->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(curGlist++);
    gDPSetCombineMode(curGlist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (playerIndex = 0; playerIndex < gPlayerCount; playerIndex++) {
            rect = state->unk20[playerIndex];
            if (gPlayerSlots[playerIndex].unk4->unk154 == 0x84) {
                fx = (f32) ((f64) rect->unk4 + ((f64) (rect->unk8 - rect->unk4) * 0.5));
                fy = (f32) ((f64) rect->unk6 + ((f64) (rect->unkA - rect->unk6) * 0.5));
                alpha = (u8) gPlayerSlots[playerIndex].unk4->unk128;
                gDPSetPrimColor(curGlist++, 0, 0, 255, 255, 255, (0xFF - alpha));
                _sprintf(textBuf, "BAD LUCK");
                fx = (f32) ((f64) fx - ((f64) textGetStringWidth(1, textBuf) * 0.25));
                fy = (f32) ((f64) fy - ((f64) fontHeight * 0.25));
                curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), (s16) (fy * 8.0f), textBuf, 4);
            } else {
                alpha = 0xFF;
            }
            if (alpha == 0) {
            } else {
                g0 = curGlist++;
                g0->words.w1 = (alpha & 0xFF) | 0xFFFFFF00;
                g0->words.w0 = 0xFA000000;
                if (state->unk70 == 0) {
                    fx = (f32) rect->unk4 + 4.0f;
                    fy = (f32) rect->unkA - ((8.0f + fontHeight2) * 0.5f);
                    fy = fy * 8.0f;
                    pre = (s32) slotQueueGetValue(3, playerIndex);
                    if (pre != 0) {
                        g0 = curGlist++; g0->words.w0 = 0xFA000000; g0->words.w1 = (alpha & 0xFF) | 0x641E0000; // FAKE: same-line packet stores steer as1 scheduling
                        _sprintf(textBuf, "%d", pre);
                    } else {
                        _sprintf(textBuf, "%d", slotQueueGetValue(2, playerIndex));
                    }
                    textY = (s16) fy;
                    curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), textY, textBuf, 4);
                    if (pre != 0) {
                        g2 = curGlist++;
                        g2->words.w0 = 0xFA000000;
                        g2->words.w1 = (alpha & 0xFF) | 0xFFFFFF00;
                    }
                    _sprintf(textBuf, "%d", slotQueueGetValue(4, playerIndex));
                    fx = (f32) rect->unk8 - ((f32) (textGetStringWidth(1, textBuf) + 8) * 0.5f);
                    curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), textY, textBuf, 4);
                }
                _sprintf(textBuf, "%d", mpGetPlayerScore(playerIndex));
                fx = (f32) rect->unk8 - (((f32) textGetStringWidth(1, textBuf) * 0.5f) + 50.0f);
                fy = (f32) ((f64) rect->unk6 + (8.0 + ((f64) (8.0f - (fontHeight2 * 0.5f)) * 0.5)));
                fy = fy * 8.0f;
                curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), (s16) fy, textBuf, 4);
            }
    }
    return curGlist;
}

Gfx *mpDrawPlayerViewportHud(Gfx *glist, MpControllerActor *controller);

Gfx *mpDrawHud(Gfx *glistp, MpControllerActor *controller) {
    s32 t0 = D_807552E4.unk8 >= 2;
    s32 cond = D_807FBB60 & 3;

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    if (!cond) {
        if (D_807552E4.unk0 == 0) {
            if ((D_807552E4.unk8 == 1) || t0) {
                glistp = mpDrawPlayerScores(glistp, controller);
            }
        } else if ((D_807552E4.unk8 == 1) || t0) {
            glistp = mpDrawPlayerViewportHud(glistp, controller);
        }
    }
    return glistp;
}

MpMapEntry *mpFindCurrentMapEntry(void) {
    s32 i;
    MpMapEntry *ret = NULL;

    for (i = 0; (i < 4U) && (ret == NULL); i++) {
        if (gCurrentMap == D_80026FA4[i].unk0) {
            ret = &D_80026FA4[i];
        }
    }
    return ret;
}

s32 mpRandomSpawnDelay(void) {
    return (((randomNonNegative() >> 15) % 0x7FFF) % 211) + 0x5A;
}

extern u8 gPlayerCharacterId[];
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
    s32 totalScore;
    MpScore *sc;
    MpKongState *ac;
    s32 boneIndex;
    void *p;

    i = 0;
    if (gPlayerCount > 0) {
        do {
            ac = gPlayerSlots[i].unk4->unk174;
            sc = &D_807FC950[i];
            if (slotQueueGetValue(1, i) != 0) {
                totalScore = sc->unk2FD + sc->unk2FB;
                if (ac->unk260 == 0) {
                    p = (void *)(s32)&D_8071F3C0;
                    switch (gPlayerCharacterId[i]) {
                    case 0:
                    case 3:
                        boneIndex = 0xF;
                        break;
                    case 1:
                    case 2:
                    case 4:
                    case 5:
                        boneIndex = 0xD;
                        break;
                    }
                    func_807149B8(1);
                    func_807149FC(-1);
                    func_80714998(2);
                    func_807149C8(0xFF, 0xFF, 0xFF, 0x7F);
                    func_8071498C(p);
                    ac->unk260 = func_80714C08(&D_807207BC, 0.5f, gPlayerSlots[i].unk4, boneIndex, 2);
                    sc->unk2FA = totalScore;
                }
                if (sc->unk2FA < totalScore) {
                    sc->unk2FA = totalScore;
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
        } while (i < gPlayerCount);
    }
    return ret;
}

s32 modelSlotFindByType(s32, s32 *, f32 *, f32 *, f32 *, s16 *, s16 *);

s32 mpFindModelSlotByType(s32 slotType) {
    s32 slotIndex;
    f32 slotX;
    f32 slotY;
    f32 slotZ;
    s16 angleA;
    s16 angleB;

    slotIndex = 0;
    angleA = 0;
    angleB = 0;
    return modelSlotFindByType(slotType, &slotIndex, &slotX, &slotY, &slotZ, &angleA, &angleB);
}

s32 func_8071432C(void);
void *actorFindByType();
s32 delayedSpawnQueueContains(s32, s32, s16, s16, s16);
void func_806F5FE8(s32, s16, s16, s16, s32);

extern s32 D_807552F0;

void func_80025654(MpControllerState *controllerState) {
    s32 temp;
    MpSpawnPoint * volatile spawnPoint; // FAKE: volatile forces stack home

    spawnPoint = mpFindCurrentMapEntry()->items;
    if (func_8071432C() != 0 && !(D_807FBB60 & 2)) {
        if (D_807552E8 == 3) {
            mpUpdateMatchTimer();
        }
        temp = mpUpdateScoreEffects();
        if (temp == -1) {
            if (controllerState->unk4C == 0 && actorFindByType(0x7A) == 0 && mpFindModelSlotByType(0x1D2) == 0) {
                MpSpawnPoint *pos = spawnPoint;
                if (delayedSpawnQueueContains(0x1D2, 0, pos->unk0, pos->unk2, pos->unk4) == 0) {
                    pos = spawnPoint;
                    func_806F5FE8(0x1D2, pos->unk0, pos->unk2, pos->unk4, 10);
                }
            }
        } else if (D_807552E8 == 5 && mpGetPlayerScore(temp) >= D_807552F0) {
            mpDetermineWinner(controllerState);
        }
        if (controllerState->unk4C != 0) {
            controllerState->unk4C--;
        }
    }
}

f32 randomFloat(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_806F5F2C(s32, s32, s16, s16, s32);

void mpUpdateItemSpawns(void) {
    MpMapEntry *mapEntry;
    s32 pad80;
    s32 itemIndex;
    MpSpawnPoint *items;
    MpSpawnPoint *item;
    s32 j;
    s32 k;
    s32 num_outer;
    s32 num_inner;
    s32 spawnDelay;
    s16 angle;
    f32 fs0;
    f32 fs1;
    f32 fs2;
    f32 fs3;
    f32 fs4;
    s16 s2_val;

    mapEntry = mpFindCurrentMapEntry();
    items = mapEntry->items;
    mpUpdateMatchTimer();
    if (func_8071432C() != 0 && !(D_807FBB60 & 2)) {
        itemIndex = 0;
        item = items;
        if (mapEntry->count > 0) {
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
                            spawnDelay = (s16) mpRandomSpawnDelay();
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
                                    func_806F5F2C(0x7A, spawnDelay, (s16) x, s2_val, (s32) z);
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
                itemIndex++;
            } while (itemIndex < mapEntry->count);
        }
    }
}

void *spawnNodeActivate(s16, s32);
void *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);

void mpUpdateRandomSpawner(MpControllerState *controllerState) {
    s32 spawnNodeId;

    spawnNodeId = 0;
    if (controllerState->unk18 != NULL) {
        if (controllerState->unk18->unk154 == 0x40) {
            controllerState->unk18 = NULL;
            spawnNodeId = 1;
        }
    } else {
        spawnNodeId = 1;
    }

    if (controllerState->unk1C == 0) {
        if (spawnNodeId != 0) {
            controllerState->unk1C = (((randomNonNegative() >> 15) % 0x7FFF) % 271) + 30;
        }
    } else {
        controllerState->unk1C--;
    }

    if (spawnNodeId != 0 && controllerState->unk1C == 0) {
        spawnNodeId = (((randomNonNegative() >> 15) % 0x7FFF) % 3) + 1;
        if (spawnNodeId == 3) {
            spawnNodeId += (((randomNonNegative() >> 15) % 0x7FFF) % 5);
        }
        controllerState->unk18 = spawnNodeActivate(spawnNodeId, 0);
        if (controllerState->unk18 == NULL) {
            controllerState->unk18 = spawnNodeSpawnById((s16)spawnNodeId, 0, 0, 0, 0, 0, 0);
        }
        if (controllerState->unk18 != NULL) {
            controllerState->unk18->unk154 = 0x36;
            controllerState->unk18->unk155 = 0;
        }
    }
}

void playerSetSizeMode(void *, s32);
void func_806F54E0(u8, s16, u8);
void func_806C9974(u8, s32);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, void *, u8);
void playerStateQueueCallback(s32, void *, u8);

void mpApplyPendingEffect(s32 playerIndex) {
    MpActor *act;
    MpKongState *st;
    MpActor *oact;
    MpKongState *ost;
    s32 i;

    act = gPlayerSlots[playerIndex].unk4;
    st = act->unk174;
    switch (st->unk264) {
    case 0:
        playerSetSizeMode(act, 2);
        func_806F54E0(playerIndex, 0x8E, 0);
        break;
    case 1:
        i = 0;
        if (gPlayerCount > 0) {
            do {
                oact = gPlayerSlots[i].unk4;
                ost = oact->unk174;
                if (i != playerIndex && ost->unkD4 == 0 && oact->unk154 != 0x84) {
                    playerStateQueueCallback(0x27, act, i);
                    ost->unk200 = 0x96;
                }
                i++;
            } while (i < gPlayerCount);
        }
        break;
    case 2:
        st->unk1F0 |= 0x20;
        st->unk1F0 &= ~0x08000000;
        func_806F54E0(playerIndex, 0x8E, 0);
        break;
    case 3:
        actorSpawnEffectChild(act->unk7C, act->unk80, act->unk84, 0.1f, 0.1f, act, 1);
        break;
    case 4:
        switch ((u32) (randomNonNegative() >> 15) % 5U) {
        case 0:
            playerSetSizeMode(act, 0);
            func_806F54E0(playerIndex, 0x8E, 0);
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
            func_806C9974(playerIndex, 0x40);
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


void mpFreeHudIcons(MpControllerState *controllerState) {
    s32 i;

    if (controllerState->unk70 != 0) {
        for (i = 0; i < gPlayerCount * 2; i++) {
            if (controllerState->unk50[i] != 0) {
                effectFreeAndUnlink(controllerState->unk50[i]);
            }
            controllerState->unk50[i] = 0;
        }
    }
    controllerState->unk70 = 0;
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
        for (i = 0; i < gPlayerCount; i++) {
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
            for (i = 0; i < gPlayerCount; i++) {
                slotQueueAddValue(7, i, ((s16 *)&D_807552E4.unkC)[1]);
            }
            slotQueueInit(0);
            break;
        }
        if (D_807552E4.unk0 == 0 && gCurrentMap == 0x6B) {
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
        for (i = 0; i < gPlayerCount; i++) {
            mpApplyPendingEffect(i);
        }
        if (gPlayerCount == 2) {
            mpUpdateRandomSpawner(s7);
        }
    } else if ((D_807FBB60 & 2) || ((s16)((f32)s7->unk10 * 0.033333335f) & 1)) {
        mpFreeHudIcons(s7);
    } else if (s7->unk70 == 0) {
        for (j = 0; j != 2; j++) {
            for (k = 0; k < gPlayerCount; k++) {
                if (gPlayerSlots[k].unk0 == 0) {
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
                s7->unk50[j * gPlayerCount + k] = func_80714CC0(D_80027024[j].unk0, D_80027024[j].unk4, x, y, -10.0f);
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


void mpSetFlags(u8 flags) {
    D_80026F70 |= flags;
}

extern void func_806F0C18(void *);
extern s32 func_80714608(s32);
extern MpFlagState *gActivePlayerState;

void func_800268DC(MpActor *playerIndex, MpKongState *itemType, MpScore *count) {
    count->unk2F6 = 0;
    count->unk2F0 = 0;
    count->unk2F4 = 0;
    count->unk2F2 = 0;
    itemType->unkD4 = 90;
    func_806F0C18(playerIndex);
    playerIndex->unk60 &= ~0x20000000;
    itemType->unk247 = -1;
    itemType->unk246 = 0;
    if (func_80714608(0) != 0) {
        gActivePlayerState->unk21E = 0;
    }
    if (D_807552E8 == 3 || D_807552E8 == 5) {
        slotQueueAddValue(1, itemType->unk1A4, -10);
    }
}

void func_8002698C(MpKongState *playerIndex) {
    if (D_807552E8 == 2) {
        slotQueueAddValue(1, playerIndex->unk1A4, -3);
    }
}

void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void mpDropItemsOnHit(u8 playerIndex, s8 dropCount) {
    s32 pad0;
    MpControllerState *ctrl;
    s32 ammoCount;
    s32 orangeCount;
    MpActor *s0;
    MpScore *s1;

    s0 = gPlayerSlots[playerIndex].unk4;
    s1 = &D_807FC950[playerIndex];
    ammoCount = s1->unk2FB + s1->unk2FD + dropCount;
    orangeCount = s1->unk2FA - ammoCount;
    if (slotQueueGetValue(1, playerIndex) != 0 && (ammoCount <= 0 || orangeCount >= 2)) {
        ctrl = ((MpControllerActor *)actorFindByType(0x13E))->unk174;
        ctrl->unk4C = 1;
        slotQueueAddValue(1, playerIndex, -10);
        if (D_807552E8 == 5) {
            func_80025F84();
        }
        actorSpawnNodeEntryScaled(0x7A, s0->unk7C, s0->unk80, s0->unk84, s0->unkE6, 1, -1, 0);
        s1->unk2FA = 0;
    }
}

void mpApplyDeathPenalty(s32 playerIndex) {
    MpActor *target;
    target = gPlayerSlots[playerIndex].unk4;
    target->unk144 = 12;
    switch (D_807552E8) {
    case 2:
        slotQueueAddValue(1, playerIndex, -3);
        break;
    case 5:
        slotQueueAddValue(7, playerIndex, -0x40);
        /* fallthrough */
    case 3:
        mpDropItemsOnHit(playerIndex, 0);
        break;
    case 4:
        slotQueueAddValue(7, playerIndex, -1);
        break;
    }
}

typedef struct MpSpawnCoord {
    s16 x;
    s16 y;
    s16 z;
} MpSpawnCoord;

MpSpawnCoord *func_806C96C4(s32);

s32 mpFindFurthestSpawn(s32 pos) {
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
        for (j = 0; j < gPlayerCount; j++) {
            target = gPlayerSlots[j].unk4;
            if (gPlayerSlots[j].unk0 != 0 && target->unk154 != 0x84) {
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
void playerResumeLocomotion(void *);

void mpRespawnPlayer(MpActor *playerIndex, s32 isTeamSpawn) {
    if (D_807552E8 == 4 && mpGetPlayerScore(isTeamSpawn) == 0) {
        D_807FC950[isTeamSpawn].unk2FB = 0;
        playerIndex->unk155++;
        playerStateQueueCallback(0x5B, 0, isTeamSpawn);
        playerIndex->unk144 = 1;
        return;
    }
    func_806C9434(mpFindFurthestSpawn(isTeamSpawn));
    gPlayerSlots[isTeamSpawn].unk2E2 |= 1;
    playerResumeLocomotion(playerIndex);
}

MpActor *actorResolveKillCreditOwner(void *, s8, u8);

void mpCreditKill(u8 victimIndex, s8 killerIndex) {
    void *points;
    s32 pad0;
    s32 pad1;
    MpScore *killerActor;
    MpPlayer *victimPlayer;
    MpActor *killerPlayer;
    MpKongState *killerScore;

    killerActor = &D_807FC950[victimIndex];
    victimPlayer = &gPlayerSlots[victimIndex];
    if (killerActor->unk2FB + killerActor->unk2FD > 0) {
        if (victimPlayer->unk2A0 != NULL) {
            killerPlayer = actorResolveKillCreditOwner(victimPlayer->unk2A0, killerIndex, victimIndex);
            if (killerPlayer != NULL && killerPlayer->unk5C == 1) {
                killerScore = killerPlayer->unk174;
                if (killerActor->unk2FB + killerActor->unk2FD + killerIndex <= 0) {
                    D_807FC950[killerScore->unk1A4].unk2FE[victimIndex]++;
                }
            }
        }
    }
    if (D_807552E8 == 3 || D_807552E8 == 5) {
        mpDropItemsOnHit(victimIndex, killerIndex);
    }
}
