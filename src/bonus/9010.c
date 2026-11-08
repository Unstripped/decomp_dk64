
#include "common.h"
#include "actor.h"

extern Gfx D_1000118;
extern Mtx D_2000180;
extern s8 D_8002D92C;
extern s8 D_8002DEF0[];
extern s32 gCurrentMap;
extern Actor *D_807FBB40;
s32 _sprintf(char *, const char *, ...);
Gfx *textDrawAnimated(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *hudDrawRollingCounter(Gfx *, s32, s32, void *, s16, void *);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);

typedef struct BonusEHud {
    s16 unk0;
    u8 pad2;
    u8 unk3;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 pad9;
    s16 unkA;
    u8 unkC;
    u8 unkD;
} BonusEHud;

Gfx *bonusRenderScoreHud(Gfx *gdl, Actor *actor) {
    BonusEHud *hud = actor->unk174;
    s16 i;
    s16 y;
    char buf[24];

    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_OPA_SURF, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gdl = textDrawAnimated(gdl, hud->unk3, 8, 30.0f, 36.0f, 0.0f, 1.0f);
    gdl = hudDrawRollingCounter(gdl, 0x26, 0x2D, &hud->unk8, hud->unkA, &hud->unk6);
    if (hud->unk6 > 0) {
        hud->unk6 -= 2;
    }
    switch (gCurrentMap) {
    case 0xBF:
        if (actor->state == 2) {
            y = 0x1E0 - (D_8002D92C * 3 << 4);
            for (i = -1; i < D_8002D92C; i++) {
                if (i >= 0) {
                    _sprintf(buf, "HIT %d", D_8002DEF0[i]);
                } else if (D_8002D92C >= 2) {
                    _sprintf(buf, "COMBO x2");
                } else {
                    buf[0] = 0;
                }
                gdl = textDrawStringVtx(gdl, 6, 0x280 - textGetStringWidth(6, buf) * 2, y, buf, 1);
                y += 0x30;
            }
        }
        break;
    case 0xB8:
        if (hud->unkC != 0) {
            hud->unkC -= 1;
            if ((hud->unkC & 0x1F) < 0x14) {
                gdl = textDrawAnimated(gdl, hud->unkD, 8, 100.0f, 100.0f, 0.0f, 1.0f);
            }
        }
        break;
    }
    return gdl;
}

extern u8 D_807444EC;
extern s16 D_80744518;
extern u16 D_807ECD58;
extern u16 D_807ECD60;
extern Actor *D_807FBB4C;
extern s8 D_8002D920;
extern s8 D_8002D924;
extern s8 D_8002D928;
extern s8 D_8002D930;
void camStartPath(void *, s32, s32);
s32 camIsPathPaused(void);
void camResumePath(void);
void actorSetStateTwo(void *);
void func_805FF378(s32, s32);
void hudSpawnCountdownTimer(s32, s32, s32);
s32 gfxResourceCreate(s32, char *, s32, f32, f32, f32);
void func_8070D8C0(void *, s32, u8);
void renderCallbacksRegister(void *, void *, s32);

void bonusScoreHudUpdate(void) {
    BonusEHud *hud = D_807FBB40->unk174;
    s32 actionParam;

    if (!(D_807FBB40->unk60 & 0x10)) {
        camStartPath(0, 0, 1);
        D_807FBB40->state = 0;
        hud->unk4 = 0x3C;
        D_8002D92C = 0;
        D_8002D930 = 0;
        D_80744518 = 0;
        hud->unk3 = gfxResourceCreate(1, "SCORE", 8, 0.0f, 0.0f, 0.0f);
        hud->unkD = gfxResourceCreate(1, "LAP BONUS", 8, 0.0f, 0.0f, 0.0f);
        D_8002D920 = 0;
        D_8002D924 = 0;
        D_8002D928 = 0;
    }
    switch (D_807FBB40->state) {
    case 0:
        if (D_807444EC == 1) {
            if (camIsPathPaused()) {
                switch (gCurrentMap) {
                case 0xBF:
                    actionParam = 0x1F;
                    break;
                case 0xB8:
                    actionParam = 0x20;
                    break;
                }
                func_8070D8C0(D_807FBB40, 0, actionParam);
                D_807FBB40->state = 1;
                hudSpawnCountdownTimer(0xDC, 0x2A, (u8)hud->unk4);
            } else if ((D_807ECD58 & 0x8000) && !(D_807ECD60 & 0x8000)) {
                camStartPath(D_807FBB4C, 1, 1);
                D_807FBB40->state = 2;
                hudSpawnCountdownTimer(0xDC, 0x2A, (u8)hud->unk4);
                actorSetStateTwo((void *)D_807FBB40->unk11C);
            }
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000) || ((D_807ECD58 & 0x8000) && !(D_807ECD60 & 0x8000))) {
            camResumePath();
            D_807FBB40->state = 2;
            actorSetStateTwo((void *)D_807FBB40->unk11C);
        }
        break;
    case 2:
        if (((Actor *)D_807FBB40->unk11C)->state == 5) {
            D_8002D930 = 0;
            D_807FBB40->state = 3;
            hud->unk0 = 0x78;
        }
        switch (gCurrentMap) {
        case 0xBF:
            D_8002D930 -= 1;
            if (D_8002D930 <= 0) {
                D_8002D930 = 0;
                if (D_8002D92C > 0) {
                    s32 shift = 0;
                    if (D_8002D92C >= 2) {
                        shift = 1;
                    }
                    while (D_8002D92C > 0) {
                        D_8002D92C -= 1;
                        hud->unkA += D_8002DEF0[D_8002D92C] << shift;
                    }
                }
            }
            break;
        case 0xB8:
            if (D_8002D928 != 0) {
                hud->unkA += D_8002D928;
                if (D_8002D928 >= 0x33) {
                    hud->unkC = 0x3C;
                }
                D_8002D928 = 0;
            }
            break;
        }
        break;
    case 3:
        ((Actor *)D_807FBB40->unk11C)->state = 1;
        hud->unk0 -= 1;
        if (hud->unk0 == 0) {
            func_805FF378(0x50, 0);
            D_807FBB40->state = 4;
        }
        break;
    }
    D_80744518 = hud->unkA;
    renderCallbacksRegister(bonusRenderScoreHud, D_807FBB40, 3);
}

extern s8 D_8002D910[];
extern s8 D_8002D91C[];

void bonusQueueScore(s16 targetId) {
    s32 i;
    s32 j;

    D_8002D928 = 5;
    for (i = 0; i < 4; i++) {
        if (targetId == D_8002D91C[i]) {
            D_8002D928 += 0xF;
        }
    }
    i = 0;
    while (i < 10 && targetId != D_8002D910[i]) {
        i++;
    }
    j = i - 1;
    if (j < 0) {
        j = 10;
    }
    if (j == D_8002D920) {
        D_8002D924 += 1;
        if (D_8002D924 >= 10) {
            D_8002D924 = 0;
            D_8002D928 += 0x32;
        }
    } else {
        D_8002D924 = 0;
    }
    D_8002D920 = i;
}


void bonusRegisterHit(s16 targetType) {
    s8 points;

    if (targetType == 0xD4) {
        points = 0xA;
    } else {
        points = 2;
    }
    if (D_8002D92C < 6) {
        D_8002DEF0[D_8002D92C] = points;
        D_8002D92C += 1;
        D_8002D930 = 0x14;
    }
    if (D_8002D92C >= 5) {
        D_8002D930 = 0;
    }
}
