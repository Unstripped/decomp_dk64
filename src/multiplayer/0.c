#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/1295B0.h"
#include "proto/global/13A7A0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/36880.h"
#include "proto/global/42630.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/90D80.h"
#include "proto/global/AA960.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/multiplayer/0.h"

// Match controller state (actor +0x174 of the controller actor).
typedef struct MpControllerState {
    u64 startTime;
    s32 timeLeft;
    s32 timeLimit;
    s32 blinkTimer;
    char pad14[4];
    Actor *spawnerActor;
    s16 spawnerDelay;
    char pad1E[2];
    G00Entry *viewports[4];
    Mtx *hudScaleMtx;
    u32 sfxLastTick;
    u8 sfxStep;
    char pad39[3];
    struct GfSndState *ambientSound;
    s16 volumeTarget;
    s16 volume;
    void *glyphFull;
    void *glyphHalf;
    u8 crownSpawnDelay;
    char pad4D[3];
    struct EffectNode *hudIcons[8];
    u8 hudIconsShown;
} MpControllerState;

extern u8 gSplitScreenMode;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 D_1000118[];
extern u8 D_20000C0[];

extern PlayerInventory gPlayerInventoryTable[];
extern u8 gPlayerCount;
extern s8 D_8076A105;
typedef struct MpSpawnPoint {
    s16 x;
    s16 y;
    s16 z;
    s16 radius;
    s16 respawnTimer;
} MpSpawnPoint;

typedef struct MpMapEntry {
    s32 mapId;
    s32 count;
    MpSpawnPoint *items;
    s32 modelIds[4];
    char pad1C[4];
} MpMapEntry;
extern MpMapEntry D_80026FA4[];
extern s32 gCurrentMap;
extern Actor *gCurrentActor;
extern PlayerStruct *gPlayerSlots;

Gfx *mpDrawTimer(Gfx *glistp, Actor *controller) {
    MpControllerState *state;
    f32 posX;
    f32 posY;

    state = controller->customState;
    if (gSplitScreenMode == 1) {
        posX = 278.0f;
        posY = 210.0f;
    } else {
        posX = (f32) (gScreenWidth * 0.5);
        posY = (f32) (gScreenHeight * 0.5);
    }
    glistp = gfxInit2DDisplayList(glistp);
    gSPDisplayList(glistp++, &D_1000118);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPPipeSync(glistp++);
    if (gSplitScreenMode == 1) {
        gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(glistp++, 0, 0, 0, 120, 255, 80);
        glistp = renderRotatedSprite(glistp, 0x60, 4, 0, 0x40, 0x40, (s32) (posX * 4.0f), (s32) (posY * 4.0f), 3.7f, 2.0f, 0xB4, 0.0f);
    }
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    return renderTimerMinutesSecondsHUD(glistp, posX, posY, state->timeLeft);
}

s32 mpCalcKillScore(PlayerInventory *score, s32 playerIndex) {
    s32 netKills;
    s32 i;

    netKills = -score->kills[playerIndex];
    for (i = 0; i < 4; i++) {
        if (i != playerIndex) {
            netKills += score->kills[i];
        }
    }
    return netKills;
}

s32 mpGetPlayerScore(s32 playerIndex) {
    s32 score;

    score = 0;
    switch (D_807552E4.unk4) {
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
        score = mpCalcKillScore(&gPlayerInventoryTable[playerIndex], playerIndex);
        break;
    }
    return score;
}

void mpDetermineWinner(MpControllerState *controllerState) {
    s32 score;
    s32 highestScore;
    s32 i;
    s32 winnerIndex;

    D_807552E4.unk8 = 2;
    winnerIndex = 0;
    highestScore = -99999;
    for (i = 0; i < gPlayerCount; i++) {
        score = mpGetPlayerScore(i);
        if (highestScore < score) {
            highestScore = score;
            winnerIndex = i;
        } else if (score == highestScore) {
            winnerIndex = -1;
        }
    }
    gGlobalPauseFlags |= 0x40001;
    menuReturnToTitleWithMode3();
    D_8076A105 = winnerIndex;
}

void mpUpdateMatchTimer(void) {
    MpControllerState *state;
    u64 elapsedUs;

    state = gCurrentActor->customState;
    elapsedUs = (osGetTime() - state->startTime) * 64 / 3000;
    if (!(gGlobalPauseFlags & 2)) {
        state->timeLeft = state->timeLimit - elapsedUs / 1000000;
    }
    if (state->timeLeft <= 0) {
        state->timeLeft = 0;
        mpDetermineWinner(state);
    }
    renderCallbacksRegister(mpDrawTimer, gCurrentActor, 7);
}

void mpCheckScoreLimit(void) {
    s32 score;
    s32 i;

    for (i = 0; i < gPlayerCount; i++) {
        score = mpGetPlayerScore(i);
        if (score >= D_807552E4.unkC || score < -999) {
            mpDetermineWinner(gCurrentActor->customState);
            return;
        }
    }
}

void mpCheckLastPlayerStanding(void) {
    s32 i;
    s32 aliveCount;

    aliveCount = 0;
    for (i = 0; i < gPlayerCount; i++) {
        if (mpGetPlayerScore(i) != 0) {
            aliveCount++;
        }
    }
    if (aliveCount < 2) {
        mpDetermineWinner(gCurrentActor->customState);
    }
}

Gfx *mpDrawGlyph(Gfx *glistp, s16 *pX, s16 y, void *texture, s32 count) {
    gDPLoadTextureBlock(glistp++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_WRAP, G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glistp++, (*pX) << 2, y << 2, (*pX + count * 8) << 2, (y + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    *pX += count * 8;
    return glistp;
}

Gfx *mpDrawScoreGlyphs(Gfx *glistp, MpControllerState *controllerState, f32 spacing) {
    s16 glyphX;
    s32 i;
    s32 count;
    s32 half;
    s32 rem;
    s16 y;
    s32 alpha;
    G00Entry *viewport;
    PlayerInventory *inventory;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gSPSetOtherMode(glistp++, G_SETOTHERMODE_L, 3, 29, 0x404240);
    gDPSetCombine(glistp++, 0xFFFFFF, 0xFFFCF279);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    for (i = 0; i < gPlayerCount; i++) {
        viewport = controllerState->viewports[i];
        alpha = 0xFF;
        if (gPlayerSlots[i].unk2EA != 0) {
            alpha = gPlayerSlots[i].actor->alpha & 0xFF; // FAKE: redundant early alpha load (overwritten below) keeps alpha in v1 and the lh in a0 (else: alpha in a0, beqzl at shape)
            if (gPlayerSlots[i].actor->alpha >= 0x100) {
                alpha = 0xFF;
            } else {
                alpha = gPlayerSlots[i].actor->alpha & 0xFF;
            }
        }
        if (gPlayerSlots[i].active == 0 || alpha == 0) {
            continue;
        }
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
        inventory = &gPlayerInventoryTable[i];
        if (gSplitScreenMode == 0) {
            glyphX = viewport->right - 0x30;
        } else {
            glyphX = (s16) ((f32) (i + 1) * spacing - 20.0);
        }
        y = viewport->top + 8;
        if (inventory->health < 0) {
            count = 0;
        } else {
            count = inventory->health;
        }
        half = count / 2;
        if (half != 0) {
            glistp = mpDrawGlyph(glistp, &glyphX, y, controllerState->glyphFull, half);
        }
        rem = count - half * 2;
        if (rem != 0) {
            glistp = mpDrawGlyph(glistp, &glyphX, y, controllerState->glyphHalf, rem);
        }
    }
    return glistp;
}


Gfx *mpDrawPlayerScores(Gfx *glistp, Actor *controller) {
    u8 scoreStr[32];
    f32 posY;
    f32 posXStep;
    s32 i;
    MpControllerState *state;
    G00Entry *viewport;

    state = controller->customState;
    viewport = state->viewports[0];
    posXStep = (f32) gScreenWidth / (f32) (gPlayerCount + 1);
    posY = (f32) (viewport->top + 8);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);
    glistp = mpDrawScoreGlyphs(glistp, state, posXStep);
    if (D_807552E4.unk4 != 3) {
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 180);
        gSPDisplayList(glistp++, &D_1000118);
        gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(glistp++, state->hudScaleMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(glistp++);
        gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 180);
        posY += 8.0f;
        for (i = 0; i < gPlayerCount; i++) {
            _sprintf(scoreStr, "%d", mpGetPlayerScore(i));
            glistp = textDrawStringVtx(glistp, 1, (s16) ((((f32) (i + 1) * posXStep) - (f32) ((f32) textGetStringWidth(1, scoreStr) * 0.25)) * 8.0f), (s16) (posY * 8.0f), scoreStr, 4);
        }
    }
    return glistp;
}


Gfx *mpDrawPlayerViewportHud(Gfx *glist, Actor *controller) {
    MpControllerState *state;
    Gfx *gfx;
    f32 fx;
    f32 fy;
    s32 textY;
    f32 fontHeight;
    Gfx *curGlist;
    u8 textBuf[32];
    s32 playerIndex;
    s32 alpha;
    f32 fontHeight2;
    s32 bonusValue;
    G00Entry *rect;
    Gfx *gfx2; // FAKE: second packet pointer for the colour reset (reusing gfx moves the 0x641E0000 packet registers)

    state = controller->customState;
    fontHeight = (f32) textGetFontHeight(1);
    fontHeight2 = (f32) textGetFontHeight(1);
    curGlist = mpDrawScoreGlyphs(glist, state, 0.0f);
    gSPDisplayList(curGlist++, &D_1000118);
    gSPMatrix(curGlist++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(curGlist++, state->hudScaleMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(curGlist++);
    gDPSetCombineMode(curGlist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (playerIndex = 0; playerIndex < gPlayerCount; playerIndex++) {
        rect = state->viewports[playerIndex];
        if (gPlayerSlots[playerIndex].actor->state == 0x84) {
            fx = rect->left + (rect->right - rect->left) * 0.5;
            fy = rect->top + (rect->bottom - rect->top) * 0.5;
            alpha = (u8) gPlayerSlots[playerIndex].actor->alpha;
            gDPSetPrimColor(curGlist++, 0, 0, 255, 255, 255, (0xFF - alpha));
            _sprintf(textBuf, "BAD LUCK");
            fx = fx - textGetStringWidth(1, textBuf) * 0.25;
            fy = fy - fontHeight * 0.25;
            curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), (s16) (fy * 8.0f), textBuf, 4);
        } else {
            alpha = 0xFF;
        }
        if (alpha == 0) {
            continue;
        }
        gfx = curGlist++;
        gfx->words.w1 = (alpha & 0xFF) | 0xFFFFFF00; // FAKE: hand-written G_SETPRIMCOLOR storing w1 before w0 (the gDPSetPrimColor w0-first order reschedules the loop)
        gfx->words.w0 = 0xFA000000;
        if (state->hudIconsShown == 0) {
            fx = (f32) rect->left + 4.0f;
            fy = (f32) rect->bottom - ((8.0f + fontHeight2) * 0.5f);
            fy = fy * 8.0f;
            bonusValue = slotQueueGetValue(3, playerIndex);
            if (bonusValue != 0) {
                gfx = curGlist++; gfx->words.w0 = 0xFA000000; gfx->words.w1 = (alpha & 0xFF) | 0x641E0000; // LAYOUT: same-line packet stores steer as1 scheduling
                _sprintf(textBuf, "%d", bonusValue);
            } else {
                _sprintf(textBuf, "%d", slotQueueGetValue(2, playerIndex));
            }
            textY = (s16) fy;
            curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), textY, textBuf, 4);
            if (bonusValue != 0) {
                gfx2 = curGlist++;
                gfx2->words.w0 = 0xFA000000;
                gfx2->words.w1 = (alpha & 0xFF) | 0xFFFFFF00;
            }
            _sprintf(textBuf, "%d", slotQueueGetValue(4, playerIndex));
            fx = (f32) rect->right - ((f32) (textGetStringWidth(1, textBuf) + 8) * 0.5f);
            curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), textY, textBuf, 4);
        }
        _sprintf(textBuf, "%d", mpGetPlayerScore(playerIndex));
        fx = (f32) rect->right - (((f32) textGetStringWidth(1, textBuf) * 0.5f) + 50.0f);
        fy = rect->top + (8.0 + (8.0f - fontHeight2 * 0.5f) * 0.5);
        fy = fy * 8.0f;
        curGlist = textDrawStringVtx(curGlist, 1, (s16) (fx * 8.0f), (s16) fy, textBuf, 4);
    }
    return curGlist;
}


Gfx *mpDrawHud(Gfx *glistp, Actor *controller) {
    s32 matchOver = D_807552E4.unk8 >= 2; // FAKE: early-load local (reads unk8 before the display-list stores, slti/xori result in t0)
    s32 paused = gGlobalPauseFlags & 3; // FAKE: early-load local (reads gGlobalPauseFlags before the display-list stores)

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);
    if (!paused) {
        if (D_807552E4.unk0 == 0) {
            if ((D_807552E4.unk8 == 1) || matchOver) {
                glistp = mpDrawPlayerScores(glistp, controller);
            }
        } else if ((D_807552E4.unk8 == 1) || matchOver) {
            glistp = mpDrawPlayerViewportHud(glistp, controller);
        }
    }
    return glistp;
}

MpMapEntry *mpFindCurrentMapEntry(void) {
    s32 i;
    MpMapEntry *ret = NULL;

    for (i = 0; (i < 4U) && (ret == NULL); i++) {
        if (gCurrentMap == D_80026FA4[i].mapId) {
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

s32 mpUpdateScoreEffects(void) {
    s32 i;
    s32 ret = -1;
    s32 totalScore;
    PlayerInventory *score;
    PlayerState *playerState;
    s32 boneIndex;
    void *callback;

    i = 0;
    if (gPlayerCount > 0) {
        do {
            playerState = gPlayerSlots[i].actor->customState;
            score = &gPlayerInventoryTable[i];
            if (slotQueueGetValue(1, i) != 0) {
                totalScore = score->healthDelta + score->health;
                if (playerState->scoreEffect == 0) {
                    callback = (void *)(s32)&D_8071F3C0; // FAKE: cast round-trip keeps the hoisted address register
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
                    effectSetDepth(1);
                    effectSetDuration(-1);
                    effectSetMode(2);
                    effectSetColor(0xFF, 0xFF, 0xFF, 0x7F);
                    effectSetCallback(callback);
                    playerState->scoreEffect = effectCreateAtActorBone(&D_807207BC, 0.5f, gPlayerSlots[i].actor, boneIndex, 2);
                    score->unk2FA = totalScore;
                }
                if (score->unk2FA < totalScore) {
                    score->unk2FA = totalScore;
                }
                ret = i;
            } else {
                if (playerState->scoreEffect != 0) {
                    effectFreeAndUnlink(playerState->scoreEffect);
                    playerState->scoreEffect = 0;
                    score->unk2FA = 0;
                }
            }
            i++;
        } while (i < gPlayerCount);
    }
    return ret;
}


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



void mpUpdateCrownSpawns(MpControllerState *controllerState) {
    s32 leaderIndex;
    MpSpawnPoint *spawnPoint;

    spawnPoint = mpFindCurrentMapEntry()->items;
    if (menuIsTransitionType6() == 0 || (gGlobalPauseFlags & 2)) {
        return;
    }
    if (D_807552E4.unk4 == 3) {
        mpUpdateMatchTimer();
    }
    leaderIndex = mpUpdateScoreEffects();
    if (leaderIndex == -1) {
        if (controllerState->crownSpawnDelay == 0 && actorFindByType(0x7A) == 0 && mpFindModelSlotByType(0x1D2) == 0) {
            if (delayedSpawnQueueContains(0x1D2, 0, spawnPoint->x, spawnPoint->y, spawnPoint->z) == 0) {
                func_806F5FE8(0x1D2, spawnPoint->x, spawnPoint->y, spawnPoint->z, 10);
            }
        }
    } else if (D_807552E4.unk4 == 5 && mpGetPlayerScore(leaderIndex) >= D_807552E4.unkC) {
        mpDetermineWinner(controllerState);
    }
    if (controllerState->crownSpawnDelay != 0) {
        controllerState->crownSpawnDelay--;
    }
}


void mpUpdateItemSpawns(void) {
    MpMapEntry *mapEntry;
    s32 pad;
    s32 itemIndex;
    MpSpawnPoint *items;
    MpSpawnPoint *item;
    s32 j;
    s32 k;
    s32 clusterCount;
    s32 itemCount;
    s32 spawnDelay;
    s16 angle;
    f32 baseY;
    f32 radius;
    f32 angleStep;
    f32 centerX;
    f32 centerZ;
    s16 spawnY;

    mapEntry = mpFindCurrentMapEntry();
    items = mapEntry->items;
    mpUpdateMatchTimer();
    if (menuIsTransitionType6() != 0 && !(gGlobalPauseFlags & 2)) {
        itemIndex = 0;
        item = items;
        if (mapEntry->count > 0) {
            do {
                if (item->respawnTimer != 0) {
                    item->respawnTimer--;
                } else {
                    j = 0;
                    if (item->radius == 0) {
                        clusterCount = 1;
                    } else {
                        clusterCount = ((randomNonNegative() >> 15) % 0x7FFF % 3) + 1;
                    }
                    if (clusterCount > 0) {
                        do {
                            k = 0;
                            itemCount = ((randomNonNegative() >> 15) % 0x7FFF % 3) + 1;
                            spawnDelay = (s16) mpRandomSpawnDelay();
                            radius = (f32) ((((f64) randomFloat() * 0.8) + 0.2) * (f64) item->radius);
                            angle = (randomNonNegative() >> 15) % 4096;
                            centerX = (f32) item->x;
                            baseY = (f32) (item->y - 23);
                            centerZ = (f32) item->z;
                            centerX += radius * mathSinF(angle);
                            centerZ += radius * mathCosF(angle);
                            if (itemCount >= 2) {
                                angle = (randomNonNegative() >> 15) % 4096;
                                radius = 15.0f;
                                angleStep = 4096.0f / (f32) itemCount;
                            } else {
                                radius = 0.0f;
                                angleStep = 0.0f;
                                angle = 0;
                            }
                            if (itemCount > 0) {
                                spawnY = (s16) baseY;
                                do {
                                    f32 x = centerX + mathSinF(angle) * radius;
                                    f32 z = centerZ + mathCosF(angle) * radius;
                                    func_806F5F2C(0x7A, spawnDelay, (s16) x, spawnY, (s32) z);
                                    k++;
                                    angle += angleStep;
                                    angle &= 0xFFF;
                                } while (k != itemCount);
                            }
                            j++;
                        } while (j != clusterCount);
                    }
                    item->respawnTimer = mpRandomSpawnDelay();
                }
                item++;
                itemIndex++;
            } while (itemIndex < mapEntry->count);
        }
    }
}


void mpUpdateRandomSpawner(MpControllerState *controllerState) {
    s32 spawnNodeId;

    spawnNodeId = 0;
    if (controllerState->spawnerActor != NULL) {
        if (controllerState->spawnerActor->state == 0x40) {
            controllerState->spawnerActor = NULL;
            spawnNodeId = 1;
        }
    } else {
        spawnNodeId = 1;
    }

    if (controllerState->spawnerDelay == 0) {
        if (spawnNodeId != 0) {
            controllerState->spawnerDelay = (((randomNonNegative() >> 15) % 0x7FFF) % 271) + 30;
        }
    } else {
        controllerState->spawnerDelay--;
    }

    if (spawnNodeId != 0 && controllerState->spawnerDelay == 0) {
        spawnNodeId = (((randomNonNegative() >> 15) % 0x7FFF) % 3) + 1;
        if (spawnNodeId == 3) {
            spawnNodeId += (((randomNonNegative() >> 15) % 0x7FFF) % 5);
        }
        controllerState->spawnerActor = spawnNodeActivate(spawnNodeId, 0);
        if (controllerState->spawnerActor == NULL) {
            controllerState->spawnerActor = spawnNodeSpawnById(spawnNodeId, 0, 0, 0, 0, 0, 0);
        }
        if (controllerState->spawnerActor != NULL) {
            controllerState->spawnerActor->state = 0x36;
            controllerState->spawnerActor->unk155 = 0;
        }
    }
}


void mpApplyPendingEffect(s32 playerIndex) {
    Actor *playerActor;
    PlayerState *playerState;
    Actor *otherActor;
    PlayerState *otherState;
    s32 i;

    playerActor = gPlayerSlots[playerIndex].actor;
    playerState = playerActor->customState;
    switch (playerState->unk264) {
    case 0:
        playerSetSizeMode(playerActor, 2);
        func_806F54E0(playerIndex, 0x8E, 0);
        break;
    case 1:
        i = 0;
        if (gPlayerCount > 0) {
            do {
                otherActor = gPlayerSlots[i].actor;
                otherState = otherActor->customState;
                if (i != playerIndex && otherState->surfaceTimer == 0 && otherActor->state != 0x84) {
                    playerStateQueueCallback(0x27, playerActor, i);
                    otherState->unk200 = 0x96;
                }
                i++;
            } while (i < gPlayerCount);
        }
        break;
    case 2:
        playerState->stateFlags |= 0x20;
        playerState->stateFlags &= ~0x08000000;
        func_806F54E0(playerIndex, 0x8E, 0);
        break;
    case 3:
        actorSpawnEffectChild(playerActor->x, playerActor->y, playerActor->z, 0.1f, 0.1f, playerActor, 1);
        break;
    case 4:
        switch ((u32) (randomNonNegative() >> 15) % 5U) {
        case 0:
            playerSetSizeMode(playerActor, 0);
            func_806F54E0(playerIndex, 0x8E, 0);
            break;
        case 1:
            playerState->unk200 = 0x96;
            playerState->stateFlags |= 0x80;
            break;
        case 2:
            playerState->stateFlags |= 0x08000000;
            playerState->stateFlags &= ~0x20;
            playerState->unk200 = 0x96;
            break;
        case 3:
            func_806C9974(playerIndex, 0x40);
            break;
        case 4:
            actorSpawnEffectChild(playerActor->x, playerActor->y, playerActor->z, 0.1f, 0.1f, playerActor, 1);
            break;
        }
        break;
    }
    playerState->unk264 = -1;
}



void mpResetMapModelStates(void) {
    MpMapEntry *mapEntry;
    s32 i;

    mapEntry = mpFindCurrentMapEntry();
    i = 0;
    while (i < 4 && mapEntry->modelIds[i] != -1) {
        csModelStateSetFirstByte(mapEntry->modelIds[i], 0);
        i++;
    }
}


void mpFreeHudIcons(MpControllerState *controllerState) {
    s32 i;

    if (controllerState->hudIconsShown != 0) {
        for (i = 0; i < gPlayerCount * 2; i++) {
            if (controllerState->hudIcons[i] != 0) {
                effectFreeAndUnlink(controllerState->hudIcons[i]);
            }
            controllerState->hudIcons[i] = 0;
        }
    }
    controllerState->hudIconsShown = 0;
}

extern ALBank *D_8076D1F8;
extern SchedStruct gScheduler;
extern u64 D_807445B0;
extern u8 D_80026F70;

typedef struct MpHudIconTableEntry {
    void *unk0;
    f32 unk4;
    s32 unk8;
} MpHudIconTableEntry;
extern MpHudIconTableEntry D_80027024[];

void mpUpdate(void) {
    MpControllerState *state;
    s32 i;
    s32 j;
    s32 k;
    s32 flag;
    G00Entry *vp;
    f32 x;
    f32 y;
    s32 sfxId;
    s32 volumeDecay;
    s32 volumeRamp;
    s32 volumeBoost;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        flag = 0;
        playerResetSpawnGlobals();
        for (i = 0; i < gPlayerCount; i++) {
            state->viewports[i] = cameraFindViewportEntry(i);
        }
        D_807552E4.unk8 = 1;
        state->startTime = osGetTime();
        state->sfxLastTick = gScheduler.unk280;
        state->sfxStep = 0;
        state->volume = 0;
        state->volumeTarget = 0;
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &state->ambientSound);
        D_80026F70 = 0;
        switch (D_807552E4.unk4) {
        case 3:
        case 5:
            flag = 1; // FAKE: flag + fallthrough into case 2 (steers branch shape)
        case 2:
            if (flag != 0) {
                MpSpawnPoint *q = mpFindCurrentMapEntry()->items;
                func_806F5FE8(0x1D2, q->x, q->y, q->z, 10);
            }
            break;
        case 4:
            for (i = 0; i < gPlayerCount; i++) {
                slotQueueAddValue(7, i, D_807552E4.unkC);
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
        state->hudScaleMtx = heapAlloc(0x40);
        guScale(state->hudScaleMtx, 0.5f, 0.5f, 1.0f);
        state->timeLimit = D_807552E4.unkC;
        state->timeLimit = state->timeLimit * 60; // the target stores unkC twice (raw value, then * 60)
        gCurrentActor->renderFlags |= 2;
        state->glyphFull = assetLoad(0xE, 0xB9, 0, 0);
        state->glyphHalf = assetLoad(0xE, 0xBA, 0, 0);
        state->blinkTimer = 0;
    }
    state->startTime += D_807445B0;
    switch (D_807552E4.unk8) {
    case 1:
        switch (D_807552E4.unk4) {
        case 3:
        case 5:
            mpUpdateCrownSpawns(state);
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
            mpUpdateRandomSpawner(state);
        }
    } else if ((gGlobalPauseFlags & 2) || ((s16)((f32)state->blinkTimer * 0.033333335f) & 1)) {
        mpFreeHudIcons(state);
    } else if (state->hudIconsShown == 0) {
        for (j = 0; j != 2; j++) {
            for (k = 0; k < gPlayerCount; k++) {
                if (gPlayerSlots[k].active == 0) {
                    continue;
                }
                vp = state->viewports[k];
                effectEnableFade();
                effectSetDuration(-1);
                effectSetMode(0);
                effectSetParam(D_80027024[j].unk8);
                if (j == 0) {
                    x = (f32)(vp->left + 0xB);
                } else {
                    x = (f32)(vp->right - 0xB);
                }
                y = (f32)(vp->bottom - 0xB);
                state->hudIcons[j * gPlayerCount + k] = effectCreateAtPosition(D_80027024[j].unk0, D_80027024[j].unk4, x, y, -10.0f);
            }
        }
        state->hudIconsShown = 1;
    }
    state->blinkTimer += 1;
    state->blinkTimer = state->blinkTimer % 180;
    volumeDecay = state->volumeTarget - 100;
    if (volumeDecay < 0x1F40) {
        state->volumeTarget = 0x1F40;
    } else {
        state->volumeTarget = volumeDecay;
    }
    volumeRamp = state->volume + 0x3E8;
    if (state->volumeTarget < volumeRamp) {
        state->volume = state->volumeTarget;
    } else {
        state->volume = volumeRamp;
    }
    n_alSndpPostEvent(state->ambientSound, 8, state->volume);
    if (D_80026F70 & 0x80) {
        state->volumeTarget = 0x7FFF;
        D_80026F70 &= ~0x80;
    }
    if (D_80026F70 & 7) {
        if (gScheduler.unk280 - state->sfxLastTick >= 6) {
            state->sfxLastTick = gScheduler.unk280;
            state->sfxStep = 0;
            sfxId = 0x1E8;
            if (D_80026F70 & 4) {
                sfxId = 0x1EA;
            } else if (D_80026F70 & 3) {
                if ((D_80026F70 & 2) * 300 + 500 < (randomNonNegative() >> 15) % 1000) {
                    if (((randomNonNegative() >> 15) % 1000) & 1) {
                        sfxId = 0x1E7;
                    } else {
                        sfxId = 0x1EA;
                    }
                }
            }
            sfxPlayOnFreeSlot(sfxId, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
        }
        volumeBoost = state->volumeTarget + 0x4650;
        if (volumeBoost >= 0x8000) {
            state->volumeTarget = 0x7FFF;
        } else {
            state->volumeTarget = volumeBoost;
        }
        D_80026F70 &= ~7;
    }
    if (state->sfxStep * 35 + 0x384 < gScheduler.unk280 - state->sfxLastTick) {
        sfxPlayOnFreeSlot(0x1E9, state->sfxStep * 3000 + 0x511F, 64.0f, 1.0f, 0xA, 0x80);
        state->sfxStep++;
        if (state->sfxStep == 5) {
            state->sfxStep = 0;
            state->sfxLastTick = gScheduler.unk280;
        }
    }
    renderCallbacksRegister(mpDrawHud, gCurrentActor, 7);
}


void mpSetFlags(u8 flags) {
    D_80026F70 |= flags;
}

extern PlayerState *gActivePlayerState;

void mpResetPlayerOnRespawn(Actor *playerActor, PlayerState *kongState, PlayerInventory *playerScore) {
    playerScore->unk2F6 = 0;
    playerScore->unk2F0 = 0;
    playerScore->unk2F4 = 0;
    playerScore->unk2F2 = 0;
    kongState->surfaceTimer = 90;
    playerKongStopSoundByState(playerActor);
    playerActor->flags &= ~0x20000000;
    kongState->hitSourcePlayerIndex = -1;
    kongState->hitSourceSpawnNodeId = 0;
    if (func_80714608(0) != 0) {
        gActivePlayerState->unk21E = 0;
    }
    if (D_807552E4.unk4 == 3 || D_807552E4.unk4 == 5) {
        slotQueueAddValue(1, kongState->playerIndex, -10);
    }
}

void mpDeductDeathPenalty(PlayerState *kongState) {
    if (D_807552E4.unk4 == 2) {
        slotQueueAddValue(1, kongState->playerIndex, -3);
    }
}

void mpDropItemsOnHit(u8 playerIndex, s8 delta) {
    s32 pad0;
    MpControllerState *ctrl;
    s32 healthAfter;
    s32 healthLost;
    Actor *playerActor;
    PlayerInventory *score;

    playerActor = gPlayerSlots[playerIndex].actor;
    score = &gPlayerInventoryTable[playerIndex];
    healthAfter = score->health + score->healthDelta + delta;
    healthLost = score->unk2FA - healthAfter;
    if (slotQueueGetValue(1, playerIndex) != 0 && (healthAfter <= 0 || healthLost >= 2)) {
        ctrl = actorFindByType(0x13E)->customState;
        ctrl->crownSpawnDelay = 1;
        slotQueueAddValue(1, playerIndex, -10);
        if (D_807552E4.unk4 == 5) {
            mpResetMapModelStates();
        }
        actorSpawnNodeEntryScaled(0x7A, playerActor->x, playerActor->y, playerActor->z, playerActor->yaw, 1, -1, 0);
        score->unk2FA = 0;
    }
}

void mpApplyDeathPenalty(s32 playerIndex) {
    Actor *playerActor;
    playerActor = gPlayerSlots[playerIndex].actor;
    playerActor->unk144 = 12;
    switch (D_807552E4.unk4) {
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


s32 mpFindFurthestSpawn(s32 playerIndex) {
    s32 i;
    s32 j;
    s32 bestSpawn;
    f32 bestDist;
    f32 nearestDist;
    G01Pos *spawn;
    Actor *playerActor;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    bestSpawn = 0;
    bestDist = 0.0f;

    for (i = 0; i < 4; i++) {
        nearestDist = 9999999.0f;
        spawn = func_806C96C4(i);
        for (j = 0; j < gPlayerCount; j++) {
            playerActor = gPlayerSlots[j].actor;
            if (gPlayerSlots[j].active != 0 && playerActor->state != 0x84) {
                dx = spawn->unk0 - playerActor->x;
                dy = spawn->unk2 - playerActor->y;
                dz = spawn->unk4 - playerActor->z;
                dist = (dx * dx + dy * dy) + dz * dz;
                if (dist < nearestDist) {
                    nearestDist = dist;
                }
            }
        }
        if (bestDist < nearestDist) {
            bestDist = nearestDist;
            bestSpawn = i;
        }
    }
    return bestSpawn;
}


void mpRespawnPlayer(Actor *playerActor, s32 playerIndex) {
    if (D_807552E4.unk4 == 4 && mpGetPlayerScore(playerIndex) == 0) {
        gPlayerInventoryTable[playerIndex].health = 0;
        playerActor->unk155++;
        playerStateQueueCallback(0x5B, 0, playerIndex);
        playerActor->unk144 = 1;
        return;
    }
    playerSyncInventoryOnSpawn(mpFindFurthestSpawn(playerIndex));
    gPlayerSlots[playerIndex].unk2E2 |= 1;
    playerResumeLocomotion(playerActor);
}


void mpCreditKill(u8 victimIndex, s8 delta) {
    s32 pad[3];
    PlayerInventory *victimScore;
    PlayerStruct *victimPlayer;
    Actor *killer;
    PlayerState *killerState;

    victimScore = &gPlayerInventoryTable[victimIndex];
    victimPlayer = &gPlayerSlots[victimIndex];
    if (victimScore->health + victimScore->healthDelta > 0) {
        if (victimPlayer->queuedActor != NULL) {
            killer = actorResolveKillCreditOwner(victimPlayer->queuedActor);
            if (killer != NULL && killer->collisionFlags == 1) {
                killerState = killer->customState;
                if (victimScore->health + victimScore->healthDelta + delta <= 0) {
                    gPlayerInventoryTable[killerState->playerIndex].kills[victimIndex]++;
                }
            }
        }
    }
    if (D_807552E4.unk4 == 3 || D_807552E4.unk4 == 5) {
        mpDropItemsOnHit(victimIndex, delta);
    }
}
