
#include "common.h"
#include "actor.h"
#include "proto/bonus/9010.h"
#include "proto/boot/3D20_sprintf.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/112080.h"
#include "proto/global/201B0.h"
#include "proto/global/3C10.h"
#include "proto/global/90D80.h"
#include "proto/global/A7710.h"

extern Gfx D_1000118;
extern Mtx D_2000180;
s8 sLapTargetOrder[10] = { 7, 20, 8, 9, 11, 10, 12, 13, 15, 14 };
s8 sExtraPointTargetIds[4] = { 8, 11, 12, 14 };
s8 sLastTargetIndex = 0;
s8 sLapStreak = 0;
s8 sPendingScore = 0;
s8 sHitCount = 0;
s8 sComboTimer = 0;
extern s8 sHitPoints[];
extern s32 gCurrentMap;
extern Actor *gCurrentActor;

typedef struct BonusScoreHud { // customState of the bonus-game score HUD actor
    s16 exitTimer;
    u8 pad2;
    u8 scoreLabel;
    s16 timeLimit;
    u8 rollTimer;
    u8 pad7;
    s16 shownScore;
    s16 score;
    u8 lapBonusTimer;
    u8 lapBonusLabel;
} BonusScoreHud;

Gfx *bonusRenderScoreHud(Gfx *gdl, Actor *actor) {
    BonusScoreHud *hud = actor->customState;
    s16 i;
    s16 y;
    u8 buf[24];

    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_OPA_SURF, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gdl = textDrawAnimated(gdl, hud->scoreLabel, 8, 30.0f, 36.0f, 0.0f, 1.0f);
    gdl = hudDrawRollingCounter(gdl, 0x26, 0x2D, &hud->shownScore, hud->score, &hud->rollTimer);
    if (hud->rollTimer > 0) {
        hud->rollTimer -= 2;
    }
    switch (gCurrentMap) {
    case 0xBF:
        if (actor->state == 2) {
            y = 0x1E0 - (sHitCount * 3 << 4);
            for (i = -1; i < sHitCount; i++) {
                if (i >= 0) {
                    _sprintf(buf, "HIT %d", sHitPoints[i]);
                } else if (sHitCount >= 2) {
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
        if (hud->lapBonusTimer != 0) {
            hud->lapBonusTimer -= 1;
            if ((hud->lapBonusTimer & 0x1F) < 0x14) {
                gdl = textDrawAnimated(gdl, hud->lapBonusLabel, 8, 100.0f, 100.0f, 0.0f, 1.0f);
            }
        }
        break;
    }
    return gdl;
}

extern u8 gGameMode;
extern s16 gMinigameScore;
extern Actor *gPrimaryPlayerActor;

void bonusScoreHudUpdate(void) {
    BonusScoreHud *hud = gCurrentActor->customState;
    s32 actionParam;

    if (!(gCurrentActor->flags & 0x10)) {
        camStartPath(0, 0, 1);
        gCurrentActor->state = 0;
        hud->timeLimit = 0x3C;
        sHitCount = 0;
        sComboTimer = 0;
        gMinigameScore = 0;
        hud->scoreLabel = gfxResourceCreate(1, "SCORE", 8, 0.0f, 0.0f, 0.0f);
        hud->lapBonusLabel = gfxResourceCreate(1, "LAP BONUS", 8, 0.0f, 0.0f, 0.0f);
        sLastTargetIndex = 0;
        sLapStreak = 0;
        sPendingScore = 0;
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gGameMode == 1) {
            if (camIsPathPaused()) {
                switch (gCurrentMap) {
                case 0xBF:
                    actionParam = 0x1F;
                    break;
                case 0xB8:
                    actionParam = 0x20;
                    break;
                }
                resQueueAttachActor(gCurrentActor, 0, actionParam);
                gCurrentActor->state = 1;
                hudSpawnCountdownTimer(0xDC, 0x2A, hud->timeLimit);
            } else if ((gContPadCur.button & 0x8000) && !(gContPadPrev.button & 0x8000)) {
                camStartPath(gPrimaryPlayerActor, 1, 1);
                gCurrentActor->state = 2;
                hudSpawnCountdownTimer(0xDC, 0x2A, hud->timeLimit);
                hudCountdownTimerStart(gCurrentActor->parentActor);
            }
        }
        break;
    case 1:
        if (!(gCurrentActor->flags & 0x02000000) || ((gContPadCur.button & 0x8000) && !(gContPadPrev.button & 0x8000))) {
            camResumePath();
            gCurrentActor->state = 2;
            hudCountdownTimerStart(gCurrentActor->parentActor);
        }
        break;
    case 2:
        if (gCurrentActor->parentActor->state == 5) {
            sComboTimer = 0;
            gCurrentActor->state = 3;
            hud->exitTimer = 0x78;
        }
        switch (gCurrentMap) {
        case 0xBF:
            sComboTimer -= 1;
            if (sComboTimer <= 0) {
                sComboTimer = 0;
                if (sHitCount > 0) {
                    s32 shift = 0;
                    if (sHitCount >= 2) {
                        shift = 1;
                    }
                    while (sHitCount > 0) {
                        sHitCount -= 1;
                        hud->score += sHitPoints[sHitCount] << shift;
                    }
                }
            }
            break;
        case 0xB8:
            if (sPendingScore != 0) {
                hud->score += sPendingScore;
                if (sPendingScore >= 0x33) {
                    hud->lapBonusTimer = 0x3C;
                }
                sPendingScore = 0;
            }
            break;
        }
        break;
    case 3:
        gCurrentActor->parentActor->state = 1;
        hud->exitTimer -= 1;
        if (hud->exitTimer == 0) {
            mapRequestTransition(0x50, 0);
            gCurrentActor->state = 4;
        }
        break;
    }
    gMinigameScore = hud->score;
    renderCallbacksRegister(bonusRenderScoreHud, gCurrentActor, 3);
}

void bonusQueueScore(s16 targetId) {
    s32 i;
    s32 j;

    sPendingScore = 5;
    for (i = 0; i < 4; i++) {
        if (targetId == sExtraPointTargetIds[i]) {
            sPendingScore += 0xF;
        }
    }
    i = 0;
    while (i < 10 && targetId != sLapTargetOrder[i]) {
        i++;
    }
    j = i - 1;
    if (j < 0) {
        j = 10;
    }
    if (j == sLastTargetIndex) {
        sLapStreak += 1;
        if (sLapStreak >= 10) {
            sLapStreak = 0;
            sPendingScore += 0x32;
        }
    } else {
        sLapStreak = 0;
    }
    sLastTargetIndex = i;
}


void bonusRegisterHit(s16 targetType) {
    s8 points;

    if (targetType == 0xD4) {
        points = 0xA;
    } else {
        points = 2;
    }
    if (sHitCount < 6) {
        sHitPoints[sHitCount] = points;
        sHitCount += 1;
        sComboTimer = 0x14;
    }
    if (sHitCount >= 5) {
        sComboTimer = 0;
    }
}
