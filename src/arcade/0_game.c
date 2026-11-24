#include "common.h"
#include "render.h"
#include "arcade.h"
#include "proto/arcade/0_game.h"
#include "proto/boot/3D20_sprintf.h"
#include "proto/boot/6690_texture_desc.h"
#include "proto/global/100180_text_font.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/104F0_eeprom.h"
#include "proto/global/1135F0_dl_texture.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/13A7A0_n_sndplayer.h"
#include "proto/global/14CF0_gfx_task.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/450_main_loop.h"
#include "proto/global/F600_controller_input.h"

extern ArcadeEntity gArcadeEntities[];

extern void *gArcadeTexImage;
extern s32 gArcadeTexScaleT;

extern s8 gArcadeBonusTimer;
extern u8 gArcadeFrozen;
extern u8 gArcadePlayerIndex;
extern u8 gArcadePaulineVisible;
extern u8 gArcadeStage;
extern u8 gArcadeScreenMode;
extern s32 gArcadeGirderState;
extern s32 gArcadeScreenTimer;
extern u8 gArcadeAdventureMode;
extern u8 gArcadeLevel;
extern s32 gArcadeConveyorSpeeds[];

extern u8 gArcadeTextColorR;
extern u8 gArcadeTextColorG;
extern u8 gArcadeTextColorB;
extern u8 gArcadeTextColorA;


extern u8 gGfxBufferIndex;
extern Gfx *gGfxTaskBuffers[];
extern s32 gGfxListCommandCount;
extern s32 gGfxSubListCommandCount;
extern FrameMatrices *gGfxCurrentFrameBuffer;
extern FrameMatrices gFrameMatrices[];
extern u8 gScreenRenderFlags;
extern f32 gScreenFadeProgress;
extern u8 gGameMode;
extern void *gSegment1Data;
extern Gfx D_1000090;
extern Gfx D_1000040;

void arcadeRunFrame(void) {
    Gfx *glist;
    Gfx *subList;

    controllerStartRead();
    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], gGfxListCommandCount, 3, 1, 0x4D2, 1);
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    gGfxCurrentFrameBuffer = &gFrameMatrices[gGfxBufferIndex];
    controllerUpdate();
    if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
        glist = gGfxTaskBuffers[gGfxBufferIndex];
    } else {
        arcadeBuildDisplayList(gGfxCurrentFrameBuffer, &glist);
    }
    glist = screenFadeUpdate(glist, 0);
    if (gGameMode != 3) {
        subList = gGfxCurrentFrameBuffer->subDisplayList;
        gfxEndDisplayList(glist, gGfxBufferIndex, &gGfxListCommandCount, 0);
        gfxEndSubDisplayList(subList, gGfxCurrentFrameBuffer, &gGfxSubListCommandCount, 1);
    } else {
        gfxEndDisplayList(glist, gGfxBufferIndex, &gGfxListCommandCount, 1);
    }
}

void arcadeBuildDisplayList(FrameMatrices *frameBuf, Gfx **glistp) {
    Gfx *glist = gGfxTaskBuffers[gGfxBufferIndex];

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(frameBuf));
    gSPSegment(glist++, 1, osVirtualToPhysical(gSegment1Data));
    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist++, &D_1000040);
    gDPPipeSync(glist++);
    glist = gfxSetFrameBufferColorImage(glist);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 6, 2, 0);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 4, 2, 0);
    gDPSetFillColor(glist++, 0x00050005);
    gDPFillRectangle(glist++, 0, 0, 319, 239);
    arcadeDispatchState(&glist);
    *glistp = glist;
}
extern s32 gArcadeHighScores[5];
extern u8 gArcadeHighScoreInitials[5][3];
extern s32 gArcadeTopScore;

void arcadeSaveHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        eepromSetField(0x15, 0, i, 0, gArcadeHighScores[i]);
        eepromSetField(0x12, 0, i, 0, gArcadeHighScoreInitials[i][0]);
        eepromSetField(0x13, 0, i, 0, gArcadeHighScoreInitials[i][1]);
        eepromSetField(0x14, 0, i, 0, gArcadeHighScoreInitials[i][2]);
    }
    gArcadeTopScore = gArcadeHighScores[0];
    eepromRequestSaveRecords();
}

void arcadeLoadHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        gArcadeHighScores[i] = eepromGetField(0x15, 0, i, 0);
        gArcadeHighScoreInitials[i][0] = eepromGetField(0x12, 0, i, 0);
        gArcadeHighScoreInitials[i][1] = eepromGetField(0x13, 0, i, 0);
        gArcadeHighScoreInitials[i][2] = eepromGetField(0x14, 0, i, 0);
    }
    gArcadeTopScore = gArcadeHighScores[0];
}

void arcadeSetTextColor(s32 r, s32 g, s32 b, s32 a) {
    gArcadeTextColorR = r;
    gArcadeTextColorG = g;
    gArcadeTextColorB = b;
    gArcadeTextColorA = a;
}

extern s32 gArcadeTextX;
extern s32 gArcadeTextY;
void arcadeSetTextPosition(s32 xPos, s32 yPos) {
    gArcadeTextX = xPos;
    gArcadeTextY = yPos;
}

void arcadeDrawString(Gfx **glistp, u8 *str) {
    Gfx *g = *glistp;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200004);
    gDPSetPrimColor(g++, 0, 0, gArcadeTextColorR, gArcadeTextColorG, gArcadeTextColorB, gArcadeTextColorA);
    gDPSetCombine(g++, 0x119623, 0xFF2FFFFF);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    *glistp = textDrawString(g, 2, gArcadeTextX, gArcadeTextY, str);
}

extern u32 gArcadeRandSeed;
s32 arcadeRand(void) {
    gArcadeRandSeed = gArcadeRandSeed * 0x41C64E6D + 0x3039;
    return (gArcadeRandSeed >> 16) & 0x7FFF;
}

extern s32 gArcadeScore;
extern u8 gArcadeSpareLives;
extern u8 gArcadeLifeIconCount;
void arcadeAddScore(s32 points) {
    s32 old = gArcadeScore;
    gArcadeScore += points;
    if (gArcadeScore >= 0x2710 && old < 0x2710) {
        gArcadeSpareLives++;
        gArcadeLifeIconCount++;
    }
}

f32 arcadeMinFloat(f32 a, f32 b) {
    if (b < a) {
        return b;
    }
    return a;
}


s32 arcadeFindFreeEntity(void) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (gArcadeEntities[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntityAfterPlayer(void) {
    s32 i;
    for (i = gArcadePlayerIndex + 1; i < 0x50; i++) {
        if (gArcadeEntities[i].type == 0) {
            return i;
        }
    }
    return 0;
}
s32 arcadeFindFreeEntityReverse(void) {
    s32 i;
    for (i = 0x4F; i >= 0; i--) {
        if (gArcadeEntities[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntitySlot39(void) {
    s32 i;
    for (i = 0x27; i >= 0; i--) {
        if (gArcadeEntities[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntitySlot36(void) {
    s32 i;
    for (i = 0x24; i >= 0; i--) {
        if (gArcadeEntities[i].type == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindEntityByType(s32 type) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (gArcadeEntities[i].type == type) {
            return i;
        }
    }
    return -1;
}

s32 arcadeCountEntitiesByType(s32 type) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 0x50; i++) {
        if (gArcadeEntities[i].type == type) {
            count++;
        }
    }
    return count;
}
extern s32 gArcadeInitPending[];
s32 D_8004A790 = 0;
extern s32 gArcadeFrameCounter;

void arcadeDispatchState(Gfx **glistp) {
    Gfx *glist = *glistp;

    if (gArcadeInitPending[0] != 0) {
        gArcadeInitPending[0] = 0;
        gArcadeStage = 1;
        arcadeInitTitleScreen();
        arcadeLoadHighScores();
    }
    switch (gArcadeScreenMode) {
    case 0:
        arcadeTitleLoop(&glist);
        break;
    case 1:
        arcadeStageIntroLoop(&glist);
        break;
    case 5:
        arcadeGameplayLoop(&glist);
        break;
    case 4:
        arcadePauseMenuLoop(&glist);
        break;
    case 3:
        arcadeAttractLoop(&glist);
        break;
    default:
        arcadeDemoLoop(&glist);
        break;
    }
    arcadeDrawHud(&glist);
    gArcadeFrameCounter++;
    glist--;
    *glistp = glist;
    gArcadeInitPending[1]++;
}


void arcadeInsertHighScore(s32 rank) {
    s32 i;
    s32 j;
    u8 blank[1] = { ' ' };

    for (i = 4; i > rank; i--) {
        gArcadeHighScores[i] = gArcadeHighScores[i - 1];
        for (j = 0; j < 3; j++) {
            gArcadeHighScoreInitials[i][j] = gArcadeHighScoreInitials[i - 1][j];
        }
    }
    gArcadeHighScores[rank] = gArcadeScore;
    for (i = 0; i < 3; i++) gArcadeHighScoreInitials[rank][i] = blank[0];  // LAYOUT: body on the for line
}

extern ArcadeEntity gArcadeNameCursorTemplate;
extern u8 gArcadeEntryInitials[3];
extern u8 gArcadeCursorRepeatTimer;
void arcadeCheckGameOver(void) {
    u8 rank;
    u8 i;

    for (rank = 0; rank < 5; rank++) {
        if (gArcadeHighScores[rank] < gArcadeScore) {
            arcadeInsertHighScore(rank);
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        gArcadeEntryInitials[i] = 0x20;
    }
    gArcadeScreenMode = 3;
    gArcadeStage = 0;
    gArcadeScreenTimer = 0;
    for (i = 0; i < 0x50; i++) {
        gArcadeCursorRepeatTimer = 0;
        gArcadeEntities[i].type = 0;
        gArcadeEntities[0] = gArcadeNameCursorTemplate;
        gArcadeEntities[0].param = rank;
    }
}

extern u8 gArcadeExitRequested;
extern u8 gArcadeLevelCleared;
void arcadeExit(void) {
    if (gArcadeExitRequested == 0) {
        if (gArcadeLevelCleared != 0 && gArcadeAdventureMode != 0 && flagGet(0x84, 0) == 0) {
            if (flagGet(0x82, 0) != 0) {
                flagSet(0x11, 1, 2);
            } else {
                flagSet(0x10, 1, 2);
            }
        }
        if (gArcadeAdventureMode != 0) {
            mapTransitionToPreviousOrExit();
        } else {
            mapRequestTransition(0x50, 0);
        }
        gArcadeExitRequested = 1;
    }
}
void arcadeAttractLoop(Gfx **glistp) {
    Gfx *glist = *glistp;
    gArcadeScreenTimer++;
    arcadeDrawBackground(&glist);
    arcadeDispatchEntities();
    arcadeRenderEntities(&glist);
    if (gArcadeScreenTimer >= 0x7BD) {
        if (gArcadeAdventureMode != 0) {
            arcadeExit();
        } else {
            arcadeInitTitleScreen();
        }
    }
    *glistp = glist;
}
extern ArcadeEntity gArcadeKongIntroTemplate;
extern u16 gArcadeKongStompSprite[];
void arcadeInitTitleScreen(void) {
    ArcadeEntity *e;
    s32 idx;

    gArcadeScreenMode = 0;
    gArcadeAdventureMode = flagGet(0x63, 2);
    gArcadeStage = 0;
    gArcadeScreenTimer = 0x200;
    gArcadeFrozen = 1;
    for (e = gArcadeEntities; e < &gArcadeEntities[80]; e++) {
        e->type = 0;
    }
    idx = arcadeFindFreeEntity();
    gArcadeEntities[idx] = gArcadeKongIntroTemplate;
    gArcadeEntities[idx].sprite = gArcadeKongStompSprite;
    gArcadeEntities[idx].x = 138.0f;
    gArcadeEntities[idx].y = 180.0f;
}

extern ArcadeEntity gArcadePaulineLowerTemplate;
extern ArcadeEntity gArcadePaulineUpperTemplate;
extern ArcadeEntity gArcadeCoinTemplate;
extern u8 gArcadeRound;
void arcadeTitleLoop(Gfx **glistp) {
    Gfx *glist;
    s32 i;
    s32 idx;

    glist = *glistp;
    gArcadeScreenTimer++;
    arcadeDrawBackground(&glist);
    if (gArcadeScreenTimer & 0x200) {
        arcadeRenderEntities(&glist);
    }
    if ((gArcadeAdventureMode != 0 && gArcadeScreenTimer == 0x5FE) || (gPadPressedButtons[0] & 0x9000)) {
        gArcadeScore = 0;
        gArcadeRound = 0;
        gArcadeSpareLives = 2;
        if (gArcadeAdventureMode != 0) {
            gArcadeSpareLives = 0;
            if (flagGet(0x84, 0) != 0) {
                gArcadeRound = 8;
            } else if (flagGet(0x82, 0) != 0) {
                gArcadeRound = 4;
            }
        }
        if (gArcadeRound / 4 + 1 >= 10) {
            gArcadeLevel = 9;
        } else {
            gArcadeLevel = gArcadeRound / 4 + 1;
        }
        gArcadeLifeIconCount = gArcadeSpareLives + 1;
        gArcadeStage = 1;
        gArcadeScreenMode = 1;
        gArcadeScreenTimer = 0;
        gArcadeFrozen = 1;
        gArcadePaulineVisible = 0;
        for (i = 0; i < 0x50; i++) {
            gArcadeEntities[i].type = 0;
        }
        idx = arcadeFindFreeEntity();
        gArcadeEntities[idx] = gArcadePaulineUpperTemplate;
        idx = arcadeFindFreeEntity();
        gArcadeEntities[idx] = gArcadePaulineLowerTemplate;
        idx = arcadeFindFreeEntity();
        gArcadeEntities[idx] = gArcadeKongIntroTemplate;
        if (gArcadeLevel == 2 && gArcadeAdventureMode != 0) {
            idx = arcadeFindFreeEntity();
            gArcadeEntities[idx] = gArcadeCoinTemplate;
        }
        gArcadeGirderState = 0;
    }
    *glistp = glist;
}

void arcadeStageIntroLoop(Gfx **glistp) {
    Gfx *glist = *glistp;
    arcadeDispatchEntities();
    arcadeDrawBackground(&glist);
    arcadeRenderEntities(&glist);
    if (gArcadeScreenTimer++ >= 0x2F9) {
        arcadeFinishStageIntro();
    }
    *glistp = glist;
}

extern s32 gArcadeMusicId;
void arcadeSetStageMusic(void) {
    if (gArcadeStage == 1) {
        gArcadeMusicId = 0x4D;
    } else if (gArcadeStage == 2) {
        gArcadeMusicId = 0x4F;
    } else if (gArcadeStage == 4) {
        gArcadeMusicId = 0x4E;
    } else {
        gArcadeMusicId = -1;
    }
}

extern struct GfSndState *gLoopSfxHandles[];
void arcadeStopSound(s32 soundId) {
    gArcadeMusicId = soundId;
    if (gLoopSfxHandles[0] != NULL) {
        n_alSndpStop(gLoopSfxHandles[0]);
    }
}

extern ALBank *gSfxBank;
void arcadeGameplayLoop(Gfx **glistp) {
    Gfx *glist = *glistp;

    arcadeDrawBackground(&glist);
    if ((gArcadeBonusTimer < 0xA) && ((gArcadeMusicId == 0x4D) || (gArcadeMusicId == 0x4E) || (gArcadeMusicId == 0x4F) || (gArcadeMusicId == -1))) {
        arcadeStopSound(0x48);
    }
    if ((gLoopSfxHandles[0] == NULL) && (gArcadeMusicId > 0)) {
        n_alSndpPlay(gSfxBank, gArcadeMusicId, 0x7FFF, 0x3F, 1.0f, 0, &gLoopSfxHandles[0]);
    }
    if (gArcadeTopScore < gArcadeScore) {
        gArcadeTopScore = gArcadeScore;
    }
    if (gArcadeScreenTimer++ == 0x3C) {
        gArcadeLifeIconCount = gArcadeSpareLives;
        gArcadeFrozen = 0;
        gArcadeEntities[arcadeFindEntityByType(0xD)].state = 2;
    }
    arcadeDispatchEntities();
    arcadeRenderEntities(&glist);
    if (gArcadeFrozen == 0) {
        if (gArcadeStage == 2) {
            arcadeSpawnStage2Enemies();
        }
        if (gArcadeStage == 4) {
            arcadeSpawnStage4Enemies();
        }
        if (gPadPressedButtons[0] & 0x1000) {
            arcadeOpenPauseMenu();
            gArcadeScreenMode = 4;
        }
    }
    *glistp = glist;
}
extern ArcadeEntity gArcadePanelTileTemplate;
extern OSContPad *gInputContPads;
extern s8 gArcadePauseSelection;
extern s32 gArcadePrevStickY;
extern u8 gArcadeHighScoresDeleted;

void arcadeOpenPauseMenu(void) {
    s32 col;
    s32 row;
    f32 colX;

    for (col = 0x60; col != 0xE0; col += 0x10) {
        colX = col;
        for (row = 0x8C; row != 0xCC; row += 0x10) {
            s32 index = arcadeFindFreeEntityReverse();
            gArcadeEntities[index] = gArcadePanelTileTemplate;
            gArcadeEntities[index].x = colX;
            gArcadeEntities[index].y = row;
        }
    }
    gArcadePauseSelection = 0;
    gArcadePrevStickY = gInputContPads->stick_y;
    gArcadeHighScoresDeleted = 0;
}

void arcadeClearEntitiesByType1C(void) {
    s32 index;
    do {
        index = arcadeFindEntityByType(0x1C);
        if (index >= 0) {
            gArcadeEntities[index].type = 0;
        }
    } while (index >= 0);
}

void arcadePauseMenuLoop(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawBackground(&glist);
    arcadeRenderEntities(&glist);
    if ((gPadPressedButtons[0] & 0x800) || (gInputContPads->stick_y >= 0x1F && gArcadePrevStickY < 0x1F)) {
        gArcadePauseSelection--;
    }
    if ((gPadPressedButtons[0] & 0x400) || (gInputContPads->stick_y < -0x1E && gArcadePrevStickY >= -0x1E)) {
        gArcadePauseSelection++;
    }
    if (gArcadePauseSelection >= 3) {
        gArcadePauseSelection = 0;
    }
    if (gArcadePauseSelection < 0) {
        gArcadePauseSelection = 2;
    }
    gArcadePrevStickY = gInputContPads->stick_y;
    if (gPadPressedButtons[0] & 0x1000) {
        arcadeClearEntitiesByType1C();
        gArcadeScreenMode = 5;
    }
    if (gPadPressedButtons[0] & 0xC000) {
        switch (gArcadePauseSelection) {
        case 0:
            arcadeClearEntitiesByType1C();
            gArcadeScreenMode = 5;
            break;
        case 1:
            if (gArcadeHighScoresDeleted == 0) {
                eepromInitConfigs(2);
                arcadeLoadHighScores();
                arcadeSaveHighScores();
                if (gArcadeTopScore < gArcadeScore) {
                    gArcadeTopScore = gArcadeScore;
                }
                gArcadeHighScoresDeleted = 1;
            }
            break;
        case 2:
            arcadeExit();
            break;
        }
    }
    *glistp = glist;
}

extern ArcadeEntity gArcadeKongHeadTemplate;
void arcadeFinishStageIntro(void) {
    s32 i;
    s32 idx;
    s32 level;

    for (i = 0; i < 80; i++) {
        gArcadeEntities[i].type = 0;
    }
    for (i = 0; i < (gArcadeRound & 3) + 1; i++) {
        idx = arcadeFindFreeEntity();
        gArcadeEntities[idx] = gArcadeKongHeadTemplate;
        gArcadeEntities[idx].y -= i * 0x20;
    }
    gArcadeScreenTimer = 0;
    level = gArcadeRound / 4 + 1;
    if (level >= 10) {
        gArcadeLevel = 9;
    } else {
        gArcadeLevel = level;
    }
    n_alSndpPlay(gSfxBank, 0x47, 0x7FFF, 0x3F, 1.0f, 0, 0);
    gArcadeScreenMode = 2;
    gArcadeFrozen = 1;
}

void arcadeDemoLoop(Gfx **glistp) {
    Gfx *glist = *glistp;
    arcadeDrawBackground(&glist);
    arcadeRenderEntities(&glist);
    if (gArcadeScreenTimer++ >= 0xA1) {
        arcadeInitStage();
        gArcadeScreenMode = 5;
    }
    *glistp = glist;
}

extern u16 gArcadeLadderSprite[];
extern u16 gArcadeLadderStage2Sprite[];
extern u16 gArcadeLadderStage4Sprite[];
extern TextureDescriptor gArcadeLadderTextures[];
extern TextureDescriptor gArcadeLadder1RowTextures[];
extern TextureDescriptor gArcadeLadder2RowTextures[];
extern TextureDescriptor gArcadeLadder3RowTextures[];
extern u8 gArcadeTexWidth;
extern u8 gArcadeTexHeight;
extern TextureDescriptor gArcadeGirderTextures[];
extern u16 gArcadeBlockSprite[];
extern u16 gArcadeBlockFlashSprite[];
void arcadeDrawBackground(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    gDPSetAlphaCompare(glist++, G_AC_NONE);
    gDPSetTexturePersp(glist++, G_TP_NONE);
    gDPSetTextureFilter(glist++, G_TF_BILERP);
    gDPSetTextureConvert(glist++, G_TC_FILT);
    gDPSetTextureDetail(glist++, G_TD_CLAMP);
    gDPSetTextureLOD(glist++, G_TL_TILE);
    gDPSetTextureLUT(glist++, G_TT_NONE);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    gDPSetCombine(glist++, 0x11FE23, 0xFFFFF3F9);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 48, 36, 272, 232);

    switch (gArcadeScreenMode) {
    case 0:
        if (gArcadeScreenTimer & 0x200) {
            arcadeDrawTitleText(&glist);
        }
        break;
    case 1:
    case 4:
    case 5:
        switch (gArcadeStage) {
        case 1:
            arcadeDrawStage1Background(&glist);
            break;
        case 2:
            arcadeDrawStage2Background(&glist);
            break;
        case 3:
            arcadeDrawStage3Background(&glist);
            break;
        default:
            arcadeDrawStage4Background(&glist);
            break;
        }
        break;
    }
    *glistp = glist;
}

void arcadeDrawLadder(Gfx **glistp, s32 x, s32 y, s32 height) {
    s32 i;
    Gfx *glist;

    gArcadeTexWidth = 8;
    gArcadeTexHeight = 4;
    gArcadeTexScaleT = 0x400;
    if (gArcadeStage == 2) gArcadeTexImage = gArcadeLadderStage2Sprite; // LAYOUT: then-arm store on the if line (as1 .loc; on its own line: fdiff 1)
    else if (gArcadeStage == 4) gArcadeTexImage = gArcadeLadderStage4Sprite; // LAYOUT: then-arm store on the else-if line (as1 .loc; on its own line: fdiff 1)
    else gArcadeTexImage = gArcadeLadderSprite;
    dlInitTextureDescriptor(&gArcadeLadderTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlInitTextureDescriptor(&gArcadeLadder1RowTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, 1, 0, 2, 0, 0);
    dlInitTextureDescriptor(&gArcadeLadder2RowTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, 2, 0, 2, 0, 0);
    dlInitTextureDescriptor(&gArcadeLadder3RowTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, 3, 0, 2, 0, 0);
    glist = *glistp;
    dlAppendTextureLoad(&glist, &gArcadeLadderTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0; i < height / 4; i++) {
        dlAppendTextureRectangle(&glist, x * 4, (i * 4 + y + 8) * 4.0);
    }
    gArcadeTexHeight = height % 4;
    if (gArcadeTexHeight != 0) {
        switch (gArcadeTexHeight) {
        case 1:
            dlAppendTextureLoad(&glist, &gArcadeLadder1RowTextures[gGfxBufferIndex]);
            break;
        case 2:
            dlAppendTextureLoad(&glist, &gArcadeLadder2RowTextures[gGfxBufferIndex]);
            break;
        case 3:
            dlAppendTextureLoad(&glist, &gArcadeLadder3RowTextures[gGfxBufferIndex]);
            break;
        }
        dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
        dlAppendTextureRectangle(&glist, x * 4, (i * 4 + y + 8) * 4.0);
    }
    *glistp = glist;
}

void arcadeDrawStage1Ladders(Gfx **glistp) {
    Gfx *glist;
    s32 height;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x70, 0x1C, 0x2E);
    arcadeDrawLadder(&glist, 0x80, 0x1C, 0x2E);
    arcadeDrawLadder(&glist, 0xB0, 0x38, 0x12);
    if (gArcadeScreenMode == 1) {
        if (gArcadeScreenTimer < 0x190) {
            height = 0x82 - (gArcadeScreenTimer - 0x3C) / 20 * 8;
            if (height >= 0x83) {
                height = 0x82;
            }
            if (height < 0x22) {
                height = 0x22;
            }
            arcadeDrawLadder(&glist, 0xA0, 0x51, height);
            arcadeDrawLadder(&glist, 0xB0, 0x51, height);
        }
    } else {
        arcadeDrawLadder(&glist, 0x88, 0x50, 4);
        arcadeDrawLadder(&glist, 0x88, 0x5B, 0xC);
        arcadeDrawLadder(&glist, 0xE8, 0x53, 0xE);
        arcadeDrawLadder(&glist, 0x50, 0x70, 0xE);
        arcadeDrawLadder(&glist, 0x78, 0x6E, 0x12);
        arcadeDrawLadder(&glist, 0xD8, 0x69, 8);
        arcadeDrawLadder(&glist, 0xD8, 0x7D, 8);
        arcadeDrawLadder(&glist, 0x70, 0x87, 5);
        arcadeDrawLadder(&glist, 0x70, 0x99, 8);
        arcadeDrawLadder(&glist, 0xA8, 0x89, 0x16);
        arcadeDrawLadder(&glist, 0xE8, 0x8D, 0xE);
        arcadeDrawLadder(&glist, 0x50, 0xAA, 0xE);
        arcadeDrawLadder(&glist, 0x90, 0xA6, 0x15);
        arcadeDrawLadder(&glist, 0x80, 0xC1, 4);
        arcadeDrawLadder(&glist, 0x80, 0xD1, 8);
        arcadeDrawLadder(&glist, 0xE8, 0xC7, 0xE);
    }
    *glistp = glist;
}

void arcadeDrawStage2Ladders(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x38, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x100, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x40, 0x9B, 0x1C);
    arcadeDrawLadder(&glist, 0xF8, 0x9B, 0x1C);
    arcadeDrawLadder(&glist, 0x48, 0x7A, 0x1A);
    arcadeDrawLadder(&glist, 0xF0, 0x7A, 0x1A);
    arcadeDrawLadder(&glist, 0x50, 0x58, 0x1C);
    arcadeDrawLadder(&glist, 0xE8, 0x58, 0x1C);
    if (gArcadeGirderState == 0) {
        arcadeDrawLadder(&glist, 0x98, 0xBD, 0x1C);
        arcadeDrawLadder(&glist, 0x78, 0x9B, 0x1C);
        arcadeDrawLadder(&glist, 0xC0, 0x9B, 0x1C);
        arcadeDrawLadder(&glist, 0x98, 0x7A, 0x1A);
        arcadeDrawLadder(&glist, 0x70, 0x58, 0x1C);
        arcadeDrawLadder(&glist, 0xC8, 0x58, 0x1C);
    }
    *glistp = glist;
}

void arcadeDrawStage3Ladders(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x70, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0x80, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0xB0, 0x38, 0x15);
    arcadeDrawLadder(&glist, 0xD0, 0x54, 0x15);
    arcadeDrawLadder(&glist, 0x100, 0x62, 0x1C);
    arcadeDrawLadder(&glist, 0xB8, 0x77, 0x15);
    arcadeDrawLadder(&glist, 0x40, 0x7E, 0x2A);
    arcadeDrawLadder(&glist, 0x70, 0x7E, 0x38);
    arcadeDrawLadder(&glist, 0x80, 0x7E, 0x38);
    arcadeDrawLadder(&glist, 0xE8, 0x85, 0x15);
    arcadeDrawLadder(&glist, 0x100, 0xA8, 0xE);
    arcadeDrawLadder(&glist, 0x38, 0xAF, 0x1C);
    *glistp = glist;
}

void arcadeDrawStage4Ladders(Gfx **glistp) {
    Gfx *glist;

    glist = *glistp;
    arcadeDrawLadder(&glist, 0x70, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0x80, 0x1C, 0x31);
    arcadeDrawLadder(&glist, 0xB0, 0x38, 0x15);
    arcadeDrawLadder(&glist, 0x48, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x80, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0xB8, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0xF0, 0xBD, 0x1C);
    arcadeDrawLadder(&glist, 0x70, 0x9A, 0x1C);
    arcadeDrawLadder(&glist, 0xC0, 0x9A, 0x1C);
    arcadeDrawLadder(&glist, 0x48, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0x80, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0xB8, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0xF0, 0x77, 0x1C);
    arcadeDrawLadder(&glist, 0x40, 0x62, 0xE);
    arcadeDrawLadder(&glist, 0xF8, 0x62, 0xE);
    *glistp = glist;
}

void arcadeDrawTitleText(Gfx **glistp) {
    s32 row;
    s32 j;
    Gfx *glist;
    s32 titleBitmap[12] = {
        0x019D2975,
        0x0155AA45,
        0x0155EE77,
        0x01556A42,
        0x019D2972,
        0x00000000,
        0x00000000,
        0x0035E938,
        0x003DAD60,
        0x0039AF6C,
        0x0035AB64,
        0x0035E938,
    };
    s32 i;

    glist = *glistp;
    gArcadeTexWidth = 8;
    gArcadeTexHeight = 8;
    gArcadeTexScaleT = 0x400;
    if (gArcadeScreenTimer & 0x182) gArcadeTexImage = gArcadeBlockSprite; // LAYOUT: then-arm store on the if line (as1 .loc; split onto its own line: text=2)
    else gArcadeTexImage = gArcadeBlockFlashSprite;
    dlInitTextureDescriptor(&gArcadeGirderTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeGirderTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0; i < 12; i++) {
        row = titleBitmap[i];
        for (j = 0; j < 25; j++) {
            if ((1 << j) & row) {
                dlAppendTextureRectangle(&glist, 0x3E0 - (j << 5), (i * 8 + 0x3F) * 4.0);
            }
        }
    }
    *glistp = glist;
}

extern u16 gArcadeGirderSprite[];
void arcadeDrawStage1Background(Gfx **glistp) {
    s32 i;
    Gfx *glist;

    gArcadeTexWidth = 8;
    gArcadeTexHeight = 0xA;
    gArcadeTexScaleT = 0x492;
    gArcadeTexImage = gArcadeGirderSprite;
    dlInitTextureDescriptor(&gArcadeGirderTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    glist = *glistp;
    dlAppendTextureLoad(&glist, &gArcadeGirderTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0; i < 6; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0x220, 0xE0);
    }
    if (gArcadeGirderState >= 6) {
        for (i = 0; i < 0xE; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x380);
        }
        for (i = 0xE; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, ((0xF7 - (i - 0xC) / 2) * 0.875 + 8.0) * 4.0);
        }
    } else {
        for (i = 0; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x368);
        }
    }
    if (gArcadeGirderState >= 5) {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, ((i / 2 + 0xCF) * 0.875 + 8.0) * 4.0);
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F4);
        }
    }
    if (gArcadeGirderState >= 4) {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, ((0xBB - i / 2) * 0.875 + 8.0) * 4.0);
        }
    } else {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x281);
        }
    }
    if (gArcadeGirderState >= 3) {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, ((i / 2 + 0x8D) * 0.875 + 8.0) * 4.0);
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x20D);
        }
    }
    if (gArcadeGirderState >= 2) {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, ((0x79 - i / 2) * 0.875 + 8.0) * 4.0);
        }
    } else {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x19A);
        }
    }
    if (gArcadeGirderState > 0) {
        for (i = 0; i < 0x12; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x142);
        }
        for (i = 0x12; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, (((i - 0x10) / 2 + 0x53) * 0.875 + 8.0) * 4.0);
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x142);
        }
    }
    arcadeDrawStage1Ladders(&glist);
    *glistp = glist;
}

extern u16 gArcadeStage2PostSprite[];
extern TextureDescriptor gArcadeColumnTextures[];
void arcadeDrawStage2Background(Gfx **glistp) {
    s32 i;
    Gfx *glist;

    glist = *glistp;
    if (gArcadeGirderState < 2) {
        gArcadeTexWidth = 2;
        gArcadeTexHeight = 8;
        gArcadeTexScaleT = 0x400;
        gArcadeTexImage = gArcadeStage2PostSprite;
        dlInitTextureDescriptor(&gArcadeColumnTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
        dlAppendTextureLoad(&glist, &gArcadeColumnTextures[gGfxBufferIndex]);
        dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
        for (i = 0; i < 4; i++) {
            dlAppendTextureRectangle(&glist, 0x1DC, (s32)(i * 8 + 51.625 + 8.0) * 4.0);
        }
        for (i = 0; i < 4; i++) {
            dlAppendTextureRectangle(&glist, 0x31C, (s32)(i * 8 + 51.625 + 8.0) * 4.0);
        }
    }
    gArcadeTexWidth = 8;
    gArcadeTexHeight = 8;
    gArcadeTexScaleT = 0x400;
    gArcadeTexImage = gArcadeBlockSprite;
    dlInitTextureDescriptor(&gArcadeGirderTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeGirderTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0; i < 0x1C; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x380);
    }
    if (gArcadeGirderState == 0) {
        for (i = 1; i < 0x1B; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F8);
            }
        }
        for (i = 2; i < 0x1A; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x270);
            }
        }
        for (i = 3; i < 0x19; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x1EC);
            }
        }
        for (i = 4; i < 0x18; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x164);
            }
        }
    } else {
        for (i = 8; i < 0x14; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x360);
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x340);
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x320);
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x300);
        }
        for (i = 1; i < 0x1B; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F8);
            }
        }
        for (i = 2; i < 0x1A; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x270);
            }
        }
        for (i = 3; i < 0x19; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x1EC);
            }
        }
        for (i = 4; i < 0x18; i++) {
            if (i < 7 || i >= 0x15 || gArcadeGirderState == 2) {
                dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x164);
            }
        }
    }
    if (gArcadeGirderState < 2) {
        for (i = 0; i < 0xE; i++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0x1A0, 0xD8);
        }
    }
    arcadeDrawStage2Ladders(&glist);
    *glistp = glist;
}

void arcadeDrawGirderSpan(Gfx **glistp, u8 startX, u8 endX, s16 y) {
    u8 i;
    Gfx *glist;

    glist = *glistp;
    for (i = startX; i < endX; i++) {
        dlAppendTextureRectangle(&glist, ((i << 5) + 0xC0), (y * 0.875 + 8.0) * 4.0);
    }
    *glistp = glist;
}

typedef struct ArcadeGirderSpan {
    u8 startX;
    u8 endX;
    s16 y;
} ArcadeGirderSpan;
typedef struct ArcadeLift {
    f32 x;
    f32 y;
    f32 vy;
} ArcadeLift;
ArcadeLift gArcadeLifts[6];
extern u16 gArcadeLiftCableSprite[];
ArcadeGirderSpan gArcadeStage3Girders[] = {
    { 0x0B, 0x11, 0x37 },
    { 0x00, 0x1C, 0xF7 },
    { 0x00, 0x15, 0x57 },
    { 0x00, 0x03, 0xE7 },
    { 0x00, 0x03, 0xBF },
    { 0x00, 0x03, 0x87 },
    { 0x0F, 0x12, 0xE7 },
    { 0x13, 0x15, 0xDF },
    { 0x16, 0x18, 0xD7 },
    { 0x19, 0x1C, 0xCF },
    { 0x08, 0x0B, 0xCF },
    { 0x07, 0x0B, 0x87 },
    { 0x1A, 0x1C, 0xB7 },
    { 0x17, 0x19, 0xAF },
    { 0x14, 0x16, 0xA7 },
    { 0x11, 0x13, 0x9F },
    { 0x10, 0x13, 0x7F },
    { 0x17, 0x1C, 0x8F },
    { 0x1A, 0x1C, 0x67 },
    { 0x17, 0x19, 0x6F },
    { 0x14, 0x16, 0x77 },
};
void arcadeDrawStage3Background(Gfx **glistp) {
    s32 i;
    s32 j;
    s32 count;
    Gfx *glist;
    ArcadeGirderSpan *pt;

    glist = *glistp;
    gArcadeTexWidth = 2;
    gArcadeTexHeight = 8;
    gArcadeTexScaleT = 0x400;
    gArcadeTexImage = gArcadeLiftCableSprite;
    dlInitTextureDescriptor(&gArcadeColumnTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeColumnTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (j = 5; j < 0x14; j++) {
        dlAppendTextureRectangle(&glist, 0x15C, (s32)(j * 8 + 51.625 + 8.0) * 4.0);
    }
    for (j = 5; j < 0x14; j++) {
        dlAppendTextureRectangle(&glist, 0x25C, (s32)(j * 8 + 51.625 + 8.0) * 4.0);
    }
    gArcadeTexWidth = 8;
    gArcadeTexHeight = 0xA;
    gArcadeTexScaleT = 0x492;
    gArcadeTexImage = gArcadeGirderSprite;
    dlInitTextureDescriptor(&gArcadeGirderTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeGirderTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    count = sizeof(gArcadeStage3Girders) / sizeof(gArcadeStage3Girders[0]); // FAKE: constant-valued array-count bound local (Q0780); assigned here, not as its initialiser (69)
    for (pt = gArcadeStage3Girders; pt < gArcadeStage3Girders + count; pt++) {
        arcadeDrawGirderSpan(&glist, pt->startX, pt->endX, pt->y);
    }
    for (i = 0; i < 6; i++) {
        if (gArcadeFrozen == 0 && gArcadeScreenMode == 5) {
            gArcadeLifts[i].y += gArcadeLifts[i].vy;
            if (gArcadeLifts[i].y < 99.0f) {
                gArcadeLifts[i].y += 144.0f;
            }
            if (gArcadeLifts[i].y > 243.0f) {
                gArcadeLifts[i].y -= 144.0f;
            }
        }
        for (j = 0; j < 2; j++) {
            dlAppendTextureRectangle(&glist, (gArcadeLifts[i].x + 40.0f + j * 8) * 4.0f, (gArcadeLifts[i].y * 0.875 + 8.0) * 4.0);
        }
    }
    arcadeDrawStage3Ladders(&glist);
    *glistp = glist;
}

extern u16 gArcadeConveyorSprite[];
extern u16 gArcadeStage4GirderSprite[];
extern u16 gArcadeCrossBraceSprite[];
extern TextureDescriptor gArcadeConveyorTextures[];
void arcadeDrawStage4Background(Gfx **glistp) {
    s32 i;
    s32 j;
    Gfx *glist;

    glist = *glistp;
    gArcadeTexWidth = 8;
    gArcadeTexHeight = 0xA;
    gArcadeTexScaleT = 0x492;
    gArcadeTexImage = gArcadeStage4GirderSprite;
    dlInitTextureDescriptor(&gArcadeGirderTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeGirderTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0xB; i < 0x11; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0xE0);
    }
    for (i = 0; i < 0x1C; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x380);
    }
    for (i = 1; i < 0x1B; i++) {
        if (i != 6 && i != 7 && i != 0x13 && i != 0x14) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x268);
        }
    }
    gArcadeTexImage = gArcadeConveyorSprite;
    dlInitTextureDescriptor(&gArcadeConveyorTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeConveyorTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 1; i < 0x1B; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x150);
    }
    for (i = 0; i < 0x1C; i++) {
        if (i < 0xC || i >= 0x10) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x1DC);
        }
    }
    for (i = 1; i < 0x1B; i++) {
        dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, 0x2F4);
    }
    gArcadeTexImage = gArcadeCrossBraceSprite;
    dlInitTextureDescriptor(&gArcadeColumnTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&glist, &gArcadeColumnTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0xC; i < 0x10; i++) {
        for (j = 0; j < 3; j++) {
            dlAppendTextureRectangle(&glist, i * 0x20 + 0xC0, ((0x9F - j * 8) * 0.875 + 8.0) * 4.0);
        }
    }
    arcadeDrawStage4Ladders(&glist);
    *glistp = glist;
}

void arcadeKillPlayer(void) {
    arcadeStopSound(0);
    n_alSndpPlay(gSfxBank, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
    gArcadeEntities[gArcadePlayerIndex].state = 8;
    gArcadeEntities[gArcadePlayerIndex].vx = 0.0f;
    gArcadeEntities[gArcadePlayerIndex].animTimer = 0.0f;
    gArcadeFrozen = 1;
}

extern ArcadeEntity gArcadePlayerTemplate;
extern ArcadeEntity gArcadeBonusBoxTemplate;
extern ArcadeEntity gArcadeOilDrumTemplate;
extern ArcadeEntity gArcadeHelpBubbleTemplate;
extern ArcadeEntity gArcadeKongStage1Template;
extern ArcadeEntity gArcadeHammerTemplate;
extern ArcadeEntity gArcadeBarrelStackTemplate;
void arcadeSpawnStage1Entities(void) {
    s32 i;

    i = 0x25;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineUpperTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineLowerTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeHelpBubbleTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeKongStage1Template;
    if (gArcadeLevel == 2 && gArcadeAdventureMode != 0) {
        gArcadeEntities[arcadeFindFreeEntity()] = gArcadeCoinTemplate;
    }
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeBonusBoxTemplate;
    gArcadePlayerIndex = arcadeFindFreeEntity();
    gArcadeEntities[gArcadePlayerIndex] = gArcadePlayerTemplate;
    gArcadeEntities[i--] = gArcadeOilDrumTemplate;
    gArcadeEntities[i--] = gArcadeHammerTemplate;
    gArcadeEntities[i] = gArcadeHammerTemplate;
    gArcadeEntities[i].x = 68.0f;
    gArcadeEntities[i].y = 110.0f;
    i--;
    gArcadeEntities[i] = gArcadeBarrelStackTemplate;
    i--;
    gArcadeEntities[i] = gArcadeBarrelStackTemplate;
    gArcadeEntities[i].param = 1;
    gArcadeEntities[i].x = 48.0f;
    i--;
    gArcadeEntities[i] = gArcadeBarrelStackTemplate;
    gArcadeEntities[i].y = 65.0f;
    gArcadeEntities[i--].param = 2;
    gArcadeEntities[i] = gArcadeBarrelStackTemplate;
    gArcadeEntities[i].param = 3;
    gArcadeEntities[i].x = 48.0f;
    gArcadeEntities[i].y = 65.0f;
    gArcadeGirderState = 7;
}

extern ArcadeEntity gArcadeKongStage2Template;
extern ArcadeEntity gArcadeBonusItemTemplate;
extern ArcadeEntity gArcadeRivetTemplate;
extern u16 gArcadeBonusBoxStage2Sprite[];
extern u16 gArcadePurseSprite[];
extern u16 gArcadeUmbrellaSprite[];
void arcadeSpawnStage2Entities(void) {
    s32 bit;
    s32 idx;
    s32 i;
    u8 pos[8][2] = {
        { 0x6C, 0xD0 },
        { 0xD4, 0xD0 },
        { 0x6C, 0xAA },
        { 0xD4, 0xAA },
        { 0x6C, 0x84 },
        { 0xD4, 0x84 },
        { 0x6C, 0x5D },
        { 0xD4, 0x5D },
    };

    bit = 1;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineUpperTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineLowerTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeHelpBubbleTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeKongStage2Template;
    if (gArcadeLevel == 2 && gArcadeAdventureMode != 0) {
        gArcadeEntities[arcadeFindFreeEntity()] = gArcadeCoinTemplate;
    }
    for (i = 0; i < 8; i++) {
        idx = arcadeFindFreeEntity();
        gArcadeEntities[idx] = gArcadeRivetTemplate;
        gArcadeEntities[idx].x = pos[i][0];
        gArcadeEntities[idx].y = pos[i][1];
        gArcadeEntities[idx].param = bit;
        bit = bit * 2;
    }
    idx = arcadeFindFreeEntity();
    gArcadeEntities[idx] = gArcadeBonusBoxTemplate;
    gArcadeEntities[idx].sprite = gArcadeBonusBoxStage2Sprite;
    gArcadePlayerIndex = arcadeFindFreeEntity();
    gArcadeEntities[gArcadePlayerIndex] = gArcadePlayerTemplate;
    gArcadeEntities[0x25] = gArcadeBonusItemTemplate;
    gArcadeEntities[0x25].sprite = gArcadePurseSprite;
    gArcadeEntities[0x24] = gArcadeBonusItemTemplate;
    gArcadeEntities[0x24].x = 252.0f;
    gArcadeEntities[0x24].y = 208.0f;
    gArcadeEntities[0x23] = gArcadeBonusItemTemplate;
    gArcadeEntities[0x23].sprite = gArcadeUmbrellaSprite;
    gArcadeEntities[0x23].x = 84.0f;
    gArcadeEntities[0x23].y = 93.0f;
    gArcadeEntities[0x22] = gArcadeHammerTemplate;
    gArcadeEntities[0x22].x = 60.0f;
    gArcadeEntities[0x22].y = 152.0f;
    gArcadeEntities[0x21] = gArcadeHammerTemplate;
    gArcadeEntities[0x21].x = 156.0f;
    gArcadeEntities[0x21].y = 114.0f;
}

extern s32 gArcadeLadderX;
extern s32 gArcadeLadderTop;
extern s32 gArcadeLadderBottom;
extern s32 gArcadeLadderClimbTop;
extern s32 gArcadeWalkMinX;
extern s32 gArcadeWalkMaxX;
extern s32 gArcadeFloorRow;

extern u8 gArcadeTypeDrawFlags[];
extern u8 gArcadeTypeOriginX[];
extern u8 gArcadeTypeOriginY[];
extern TextureDescriptor gArcadeEntityTextures[][80];

extern u16 gArcadeBarrelRollTopLeftSprite[];
extern u16 gArcadeBarrelRollBottomLeftSprite[];
extern u16 gArcadeBarrelRollBottomRightSprite[];
extern u16 gArcadeBarrelRollTopRightSprite[];
extern u16 gArcadeBarrelBlueRollTopLeftSprite[];
extern u16 gArcadeBarrelBlueRollBottomLeftSprite[];
extern u16 gArcadeBarrelBlueRollBottomRightSprite[];
extern u16 gArcadeBarrelBlueRollTopRightSprite[];
extern u16 gArcadeBarrelSideDarkBandSprite[];
extern u16 gArcadeBarrelSideLightBandSprite[];
extern u16 gArcadeBarrelBlueSideDarkBandSprite[];
extern u16 gArcadeBarrelBlueSideLightBandSprite[];


extern u8 gArcadeRoundStages[];
extern s32 gArcadeHammerTimer;
extern u8 gArcadeRivetMask;
extern u8 gArcadeGameOver;


extern ArcadeEntity gArcadeLiftMotorTemplate;
extern ArcadeEntity gArcadeKongStage3Template;
extern ArcadeEntity gArcadeFireballTemplate;
void arcadeSpawnStage3Entities(void) {
    s32 i;
    ArcadeEntity *p;
    f32 t;

    i = 0x25;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineUpperTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineLowerTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeHelpBubbleTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeKongStage3Template;
    if (gArcadeLevel == 2 && gArcadeAdventureMode != 0) {
        gArcadeEntities[arcadeFindFreeEntity()] = gArcadeCoinTemplate;
    }
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeBonusBoxTemplate;
    gArcadePlayerIndex = arcadeFindFreeEntity();
    gArcadeEntities[gArcadePlayerIndex] = gArcadePlayerTemplate;
    gArcadeEntities[gArcadePlayerIndex].x = 56.0f;
    gArcadeEntities[gArcadePlayerIndex].y = 231.0f;
    p = &gArcadeEntities[i];
    *p = gArcadeLiftMotorTemplate;
    i--;
    p = &gArcadeEntities[i];
    *p = gArcadeLiftMotorTemplate;
    p->x = 144.0f;
    i--;
    p = &gArcadeEntities[i];
    *p = gArcadeLiftMotorTemplate;
    p->flipY = 1;
    p->y = 238.0f;
    i--;
    p = &gArcadeEntities[i];
    *p = gArcadeLiftMotorTemplate;
    p->flipY = 1;
    p->x = 144.0f;
    p->y = 238.0f;
    i--;
    p = &gArcadeEntities[i];
    *p = gArcadeBonusItemTemplate;
    p->sprite = gArcadePurseSprite;
    p->x = 260.0f;
    p->y = 103.0f;
    i--;
    p = &gArcadeEntities[i];
    *p = gArcadeBonusItemTemplate;
    p->sprite = gArcadeUmbrellaSprite;
    p->x = 60.0f;
    p->y = 135.0f;
    i = arcadeFindFreeEntity();
    p = &gArcadeEntities[i];
    *p = gArcadeFireballTemplate;
    p->facing = 1;
    p->vx = 0.5f;
    p->x = 114.0f;
    p->y = 135.0f;
    i = arcadeFindFreeEntity();
    p = &gArcadeEntities[i];
    *p = gArcadeFireballTemplate;
    p->facing = 1;
    p->vx = 0.5f;
    p->x = 260.0f;
    p->y = 103.0f;
    gArcadeLifts[0].x = 40.0f;
    gArcadeLifts[1].x = 40.0f;
    gArcadeLifts[2].x = 40.0f;
    gArcadeLifts[3].x = 104.0f;
    gArcadeLifts[4].x = 104.0f;
    gArcadeLifts[5].x = 104.0f;
    gArcadeLifts[0].y = 95.0f;
    gArcadeLifts[3].y = 95.0f;
    gArcadeLifts[1].y = 143.0f;
    gArcadeLifts[4].y = 143.0f;
    gArcadeLifts[2].y = 191.0f;
    gArcadeLifts[5].y = 191.0f;
    t = (arcadeMinFloat(gArcadeLevel, 4.0f) - 2.0) / 16 + 0.5;
    gArcadeLifts[3].vy = t;
    gArcadeLifts[0].vy = -t;
    gArcadeLifts[1].vy = -t;
    gArcadeLifts[2].vy = -t;
    gArcadeLifts[4].vy = t;
    gArcadeLifts[5].vy = t;
}

extern ArcadeEntity gArcadeRetractableLadderTemplate;
extern ArcadeEntity gArcadeKongStage4Template;
extern ArcadeEntity gArcadeOilFireTemplate;
extern ArcadeEntity gArcadeConveyorPulleyTemplate;
extern u16 gArcadeBonusBoxStage4Sprite[];
void arcadeSpawnStage4Entities(void) {
    s32 idx;

    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeRetractableLadderTemplate;
    idx = arcadeFindFreeEntity();
    gArcadeEntities[idx] = gArcadeRetractableLadderTemplate;
    gArcadeEntities[idx].x = 244.0f;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineUpperTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadePaulineLowerTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeHelpBubbleTemplate;
    gArcadeEntities[arcadeFindFreeEntity()] = gArcadeKongStage4Template;
    if (gArcadeLevel == 2 && gArcadeAdventureMode != 0) {
        gArcadeEntities[arcadeFindFreeEntity()] = gArcadeCoinTemplate;
    }
    idx = arcadeFindFreeEntity();
    gArcadeEntities[idx] = gArcadeBonusBoxTemplate;
    gArcadeEntities[idx].sprite = gArcadeBonusBoxStage4Sprite;
    gArcadePlayerIndex = arcadeFindFreeEntity();
    gArcadeEntities[gArcadePlayerIndex] = gArcadePlayerTemplate;
    gArcadeEntities[0x25] = gArcadeOilDrumTemplate;
    gArcadeEntities[0x25].x = 152.0f;
    gArcadeEntities[0x25].y = 127.0f;
    gArcadeEntities[0x24] = gArcadeOilFireTemplate;
    gArcadeEntities[0x24].x = 152.0f;
    gArcadeEntities[0x24].y = 113.0f;
    gArcadeEntities[0x23] = gArcadeBonusItemTemplate;
    gArcadeEntities[0x23].sprite = gArcadePurseSprite;
    gArcadeEntities[0x23].x = 172.0f;
    gArcadeEntities[0x22] = gArcadeBonusItemTemplate;
    gArcadeEntities[0x22].y = 167.0f;
    gArcadeEntities[0x22].x = 116.0f;
    gArcadeEntities[0x21] = gArcadeBonusItemTemplate;
    gArcadeEntities[0x21].sprite = gArcadeUmbrellaSprite;
    gArcadeEntities[0x21].y = 167.0f;
    gArcadeEntities[0x21].x = 252.0f;
    gArcadeEntities[0x20] = gArcadeHammerTemplate;
    gArcadeEntities[0x20].x = 68.0f;
    gArcadeEntities[0x20].y = 148.0f;
    gArcadeEntities[0x1F] = gArcadeHammerTemplate;
    gArcadeEntities[0x1F].x = 156.0f;
    gArcadeEntities[0x1F].y = 188.0f;
    gArcadeEntities[0x1E] = gArcadeConveyorPulleyTemplate;
    gArcadeEntities[0x1D] = gArcadeConveyorPulleyTemplate;
    gArcadeEntities[0x1D].facing = 1;
    gArcadeEntities[0x1D].flipY = 1;
    gArcadeEntities[0x1D].param = 0;
    gArcadeEntities[0x1D].x = 256.0f;
    gArcadeEntities[0x1D].y = 84.0f;
    gArcadeEntities[0x1C] = gArcadeConveyorPulleyTemplate;
    gArcadeEntities[0x1C].facing = 1;
    gArcadeEntities[0x1C].flipY = 1;
    gArcadeEntities[0x1C].param = 1;
    gArcadeEntities[0x1C].y = 124.0f;
    gArcadeEntities[0x1C].x = 139.0f;
    gArcadeEntities[0x1B] = gArcadeConveyorPulleyTemplate;
    gArcadeEntities[0x1B].y = 124.0f;
    gArcadeEntities[0x1B].param = 2;
    gArcadeEntities[0x1B].x = 165.0f;
    gArcadeEntities[0x1A] = gArcadeConveyorPulleyTemplate;
    gArcadeEntities[0x1A].y = 204.0f;
    gArcadeEntities[0x1A].param = 3;
    gArcadeEntities[0x1A].x = 48.0f;
    gArcadeEntities[0x19] = gArcadeConveyorPulleyTemplate;
    gArcadeEntities[0x19].facing = 1;
    gArcadeEntities[0x19].flipY = 1;
    gArcadeEntities[0x19].x = 256.0f;
    gArcadeEntities[0x19].y = 204.0f;
    gArcadeEntities[0x19].param = 3;
}

void arcadeInitStage(void) {
    s32 i;
    s32 bonusTimer;

    gArcadeGirderState = 0;
    gArcadeStage = gArcadeRoundStages[gArcadeRound & 3];
    for (i = 0; i < 80; i++) {
        gArcadeEntities[i].type = 0;
    }
    switch (gArcadeStage) {
    case 1:
        arcadeSpawnStage1Entities();
        break;
    case 2:
        arcadeSpawnStage2Entities();
        break;
    case 3:
        arcadeSpawnStage3Entities();
        break;
    default:
        arcadeSpawnStage4Entities();
        break;
    }
    arcadeSetStageMusic();
    bonusTimer = gArcadeLevel * 10 + 40;
    if (bonusTimer >= 91) {
        gArcadeBonusTimer = 90;
    } else {
        gArcadeBonusTimer = bonusTimer;
    }
    gArcadeHammerTimer = 0;
    gArcadeRivetMask = 0xFF;
    gArcadeGameOver = 0;
    gArcadeScreenTimer = 0;
    gArcadeFrozen = 1;
    gArcadeFloorRow = 1;
    gArcadePaulineVisible = 1;
    gArcadeConveyorSpeeds[0] = 0;
    gArcadeConveyorSpeeds[1] = 0;
    gArcadeConveyorSpeeds[2] = 0;
    gArcadeConveyorSpeeds[3] = 0;
}

s32 arcadeCheckStage1Collision(s32 posX, s32 posY) {
    s32 floorY;

    if (posY < 0x5D) {
        gArcadeWalkMinX = 0x88;
    } else {
        gArcadeWalkMinX = 0x36;
    }
    gArcadeWalkMaxX = 0x10A;

    if (posY < 0x3F) {
        gArcadeFloorRow = 0;
        if (posX >= 0x85 && posX < 0xBC) {
            floorY = 0x37;
        } else {
            floorY = 0xF8;
        }
    } else if (posY < 0x5D) {
        gArcadeFloorRow = 1;
        floorY = posX / 16;
        if (floorY < 0xB) {
            floorY = 0xB;
        }
        floorY += 0x48;
        if (posX >= 0x105) {
            floorY = 0xF8;
        }
    } else if (posY < 0x7F) {
        gArcadeFloorRow = 2;
        floorY = 0x7C - (posX / 16);
        if (posX < 0x3C) {
            floorY = 0xF8;
        }
    } else if (posY < 0xA0) {
        gArcadeFloorRow = 3;
        floorY = (posX / 16) + 0x8A;
        if (posX >= 0x105) {
            floorY = 0xF8;
        }
    } else if (posY < 0xC3) {
        gArcadeFloorRow = 4;
        floorY = 0xBE - (posX / 16);
        if (posX < 0x3C) {
            floorY = 0xF8;
        }
    } else if (posY < 0xE1) {
        gArcadeFloorRow = 5;
        floorY = (posX / 16) + 0xCC;
        if (posX >= 0x105) {
            floorY = 0xF8;
        }
    } else {
        gArcadeFloorRow = 6;
        floorY = 0x100 - (posX / 16);
        if (floorY >= 0xF8) {
            floorY = 0xF7;
        }
    }

    if (floorY < posY) {
        gArcadeFloorRow++;
    }
    return floorY;
}

s32 arcadeCheckStage2Collision(s32 posX, s32 posY) {
    s32 floorY;

    gArcadeWalkMinX = 0x36;
    gArcadeWalkMaxX = 0x10A;
    if (posY < 0x6E) {
        gArcadeFloorRow = 1;
        if (posX >= 0x4D && posX < 0xF4 &&
            (posX < 0x6C || posX >= 0x6D || (gArcadeRivetMask & 0x40)) &&
            (posX < 0xD4 || posX >= 0xD5 || (gArcadeRivetMask & 0x80))) {
            floorY = 0x5D;
        } else {
            floorY = 0xF7;
        }
    } else if (posY < 0x8C) {
        gArcadeFloorRow = 2;
        if (posX >= 0x45 && posX < 0xFC &&
            (posX < 0x6C || posX >= 0x6D || (gArcadeRivetMask & 0x10)) &&
            (posX < 0xD4 || posX >= 0xD5 || (gArcadeRivetMask & 0x20))) {
            floorY = 0x84;
        } else {
            floorY = 0xF7;
        }
    } else if (posY < 0xBE) {
        gArcadeFloorRow = 3;
        if (posX >= 0x3D && posX < 0x104 &&
            (posX < 0x6C || posX >= 0x6D || (gArcadeRivetMask & 4)) &&
            (posX < 0xD4 || posX >= 0xD5 || (gArcadeRivetMask & 8))) {
            floorY = 0xAA;
        } else {
            floorY = 0xF7;
        }
    } else if (posY < 0xDC) {
        gArcadeFloorRow = 4;
        if ((posX < 0x6C || posX >= 0x6D || (gArcadeRivetMask & 1)) &&
            (posX < 0xD4 || posX >= 0xD5 || (gArcadeRivetMask & 2))) {
            floorY = 0xD0;
        } else {
            floorY = 0xF7;
        }
    } else {
        gArcadeFloorRow = 5;
        floorY = 0xF7;
    }

    if (floorY < posY) {
        gArcadeFloorRow++;
    }
    return floorY;
}

s32 arcadeCheckStage3Collision(s32 posX, s32 posY) {
    s32 floorY;
    s32 i;

    if (posY < 0x5D) {
        gArcadeWalkMinX = 0x88;
    } else {
        gArcadeWalkMinX = 0x36;
    }
    gArcadeWalkMaxX = 0x10A;
    gArcadeFloorRow = 1;
    if (posY < 0x3F) {
        if (posX >= 0x85 && posX < 0xBC) {
            floorY = 0x37;
            gArcadeFloorRow = 0;
        } else {
            floorY = 0xF8;
        }
    } else if (posY < 0x62) {
        if (posX < 0xDC) {
            floorY = 0x57;
        } else {
            floorY = 0xF8;
        }
    } else if (posY < 0x8C) {
        if (posX >= 0xFD) {
            floorY = 0x67;
        } else if (posX >= 0xE5 && posX < 0xFC) {
            floorY = 0x6F;
        } else if (posX >= 0xCD && posX < 0xE4) {
            floorY = 0x77;
        } else if (posX >= 0xAD && posX < 0xCC) {
            floorY = 0x7F;
        } else if ((posX >= 0x65 && posX < 0x8C) || posX < 0x4C) {
            floorY = 0x87;
        } else {
            floorY = 0xF8;
        }
    } else if (posY < 0x94) {
        if (posX >= 0xE5) {
            floorY = 0x8F;
        } else {
            floorY = 0xF7;
        }
    } else if (posY < 0xC6) {
        if (posX >= 0xFD) {
            floorY = 0xB7;
        } else if (posX >= 0xE5 && posX < 0xFC) {
            floorY = 0xAF;
        } else if (posX >= 0xCD && posX < 0xE4) {
            floorY = 0xA7;
        } else if (posX >= 0xB5 && posX < 0xCC) {
            floorY = 0x9F;
        } else if (posX < 0x4C) {
            floorY = 0xBF;
        } else {
            floorY = 0xF8;
        }
    } else {
        if (posY < 0xF0) {
            if ((posX >= 0x6D && posX < 0x8C) || posX >= 0xF5) {
                floorY = 0xCF;
            } else if (posX >= 0xDD && posX < 0xF4) {
                floorY = 0xD7;
            } else if (posX >= 0xC5 && posX < 0xDC) {
                floorY = 0xDF;
            } else if ((posX >= 0xA5 && posX < 0xC4) || posX < 0x4C) {
                floorY = 0xE7;
            } else {
                floorY = 0xF8;
            }
        } else {
            floorY = 0xF7;
        }
    }
    if (posX >= 0x4D && posX < 0x64) {
        for (i = 0; i < 3; i++) {
            f32 y = gArcadeLifts[i].y;
            if (y < posY + 4 && posY - 0x10 < y) {
                floorY = (s32)y;
            }
        }
    }
    if (posX >= 0x8D && posX < 0xA4) {
        for (i = 3; i < 6; i++) {
            f32 y = gArcadeLifts[i].y;
            if (y < posY + 4 && posY - 0x10 < y) {
                floorY = (s32)y;
            }
        }
    }
    return floorY;
}

s32 arcadeCheckStage4Collision(s32 posX, s32 posY) {
    s32 floorY;

    gArcadeWalkMinX = 0x36;
    gArcadeWalkMaxX = 0x10A;
    if (posY < 0x6E) {
        gArcadeFloorRow = 0;
        floorY = 0x57;
    } else if (posY < 0x8C) {
        if (posX < 0x9C) {
            floorY = 0x7F;
            gArcadeFloorRow = 1;
        } else if (posX >= 0xA5) {
            floorY = 0x7F;
            gArcadeFloorRow = 2;
        } else {
            floorY = 0xF7;
        }
    } else if (posY < 0xBE) {
        gArcadeFloorRow = 4;
        if ((posX < 0x64 || posX >= 0x6D) && (posX < 0xCC || posX >= 0xD5)) {
            floorY = 0xA7;
        } else {
            floorY = 0xF7;
        }
    } else if (posY < 0xDC) {
        gArcadeFloorRow = 3;
        floorY = 0xCF;
    } else {
        gArcadeFloorRow = 5;
        floorY = 0xF7;
    }
    if (floorY < posY) {
        gArcadeFloorRow++;
    }
    return floorY;
}

s32 arcadeCheckPlayerCollision(s32 posX, s32 posY) {
    if (gArcadeStage == 1) {
        return arcadeCheckStage1Collision(posX, posY);
    } else if (gArcadeStage == 2) {
        return arcadeCheckStage2Collision(posX, posY);
    } else if (gArcadeStage == 3) {
        return arcadeCheckStage3Collision(posX, posY);
    } else {
        return arcadeCheckStage4Collision(posX, posY);
    }
}

s32 arcadeCheckLadderBounds(s32 posX, s32 posY, s32 ladderX, s32 topY, s32 climbTop, s32 bottomY) {
    if ((posY >= topY) & (bottomY >= posY) & ((ladderX - 4) < posX) & (posX < (ladderX + 3))) {
        gArcadeLadderX = ladderX;
        gArcadeLadderTop = topY;
        gArcadeLadderBottom = bottomY;
        gArcadeLadderClimbTop = climbTop;
        return 1;
    }
    return 0;
}

s32 arcadeCheckStage1Ladders(s32 posX, s32 posY) {
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0xD4, 0xEB, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0xDA, 0xDA, 0xF2)) {
        return 2;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x94, 0xB5, 0xB5, 0xD5)) {
        return 3;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x54, 0xB9, 0xB9, 0xD1)) {
        return 4;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0x91, 0xAB, 0xB7)) {
        return 5;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xAC, 0x94, 0x94, 0xB4)) {
        return 6;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x98, 0x98, 0xB0)) {
        return 7;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xDC, 0x6F, 0x8B, 0x97)) {
        return 8;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x7C, 0x75, 0x75, 0x91)) {
        return 9;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x54, 0x77, 0x77, 0x8F)) {
        return 10;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x8C, 0x53, 0x64, 0x74)) {
        return 11;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x56, 0x56, 0x6E)) {
        return 12;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xB4, 0x37, 0x37, 0x53)) {
        return 13;
    }
    gArcadeLadderX = 0;
    gArcadeLadderTop = 0x12C;
    gArcadeLadderClimbTop = 0x12C;
    gArcadeLadderBottom = 1;
    return 0;
}

s32 arcadeCheckStage2Ladders(s32 posX, s32 posY) {
    if (arcadeCheckLadderBounds(posX, posY, 0x3C, 0xD0, 0xD0, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x9C, 0xD0, 0xD0, 0xF7)) {
        return 2;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x104, 0xD0, 0xD0, 0xF7)) {
        return 3;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x44, 0xAA, 0xAA, 0xD0)) {
        return 4;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x7C, 0xAA, 0xAA, 0xD0)) {
        return 5;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xC4, 0xAA, 0xAA, 0xD0)) {
        return 6;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xFC, 0xAA, 0xAA, 0xD0)) {
        return 7;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x4C, 0x84, 0x84, 0xAA)) {
        return 8;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x9C, 0x84, 0x84, 0xAA)) {
        return 9;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xF4, 0x84, 0x84, 0xAA)) {
        return 10;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x54, 0x5D, 0x5D, 0x84)) {
        return 11;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0x5D, 0x5D, 0x84)) {
        return 12;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xCC, 0x5D, 0x5D, 0x84)) {
        return 13;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x5D, 0x5D, 0x84)) {
        return 14;
    }
    gArcadeLadderX = 0;
    gArcadeLadderTop = 0x12C;
    gArcadeLadderClimbTop = 0x12C;
    gArcadeLadderBottom = 1;
    return 0;
}

s32 arcadeCheckStage3Ladders(s32 posX, s32 posY) {
    if (arcadeCheckLadderBounds(posX, posY, 0xB4, 0x37, 0x37, 0x57)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xD4, 0x57, 0x57, 0x77)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x104, 0x67, 0x67, 0x8F)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xBC, 0x7F, 0x7F, 0x9F)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xEC, 0x8F, 0x8F, 0xAF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x104, 0xB7, 0xB7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x44, 0x87, 0x87, 0xBF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x3C, 0xBF, 0xBF, 0xE7)) {
        return 1;
    }
    gArcadeLadderX = 0;
    gArcadeLadderTop = 0x12C;
    gArcadeLadderClimbTop = 0x12C;
    gArcadeLadderBottom = 1;
    return 0;
}

s32 arcadeCheckStage4Ladders(s32 posX, s32 posY) {
    s32 ladderY;
    s32 climbTop;

    if (arcadeCheckLadderBounds(posX, posY, 0x4C, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xBC, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xF4, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x74, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xC4, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x4C, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x84, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xBC, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xF4, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    ladderY = (s32)gArcadeEntities[0].y;
    if (ladderY == 0x61) {
        climbTop = 0x57;
    } else {
        climbTop = 0x74;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0x44, 0x57, climbTop, 0x7F)) {
        return 1;
    }
    ladderY = (s32)gArcadeEntities[1].y;
    if (ladderY == 0x61) {
        climbTop = 0x57;
    } else {
        climbTop = 0x74;
    }
    if (arcadeCheckLadderBounds(posX, posY, 0xFC, 0x57, climbTop, 0x7F)) {
        return 1;
    }
    gArcadeLadderX = 0;
    gArcadeLadderTop = 0x12C;
    gArcadeLadderClimbTop = 0x12C;
    gArcadeLadderBottom = 1;
    return 0;
}

s32 arcadeCheckStageLadders(s32 posX, s32 posY) {
    if (gArcadeStage == 1) {
        return arcadeCheckStage1Ladders(posX, posY);
    } else if (gArcadeStage == 2) {
        return arcadeCheckStage2Ladders(posX, posY);
    } else if (gArcadeStage == 3) {
        return arcadeCheckStage3Ladders(posX, posY);
    } else {
        return arcadeCheckStage4Ladders(posX, posY);
    }
}

void arcadeRenderEntity(Gfx **glistp, s32 entIndex) {
    Gfx *glist;
    s32 yOffset;
    f32 scale;

    if (gArcadeTypeDrawFlags[gArcadeEntities[entIndex].type] & 1) {
        scale = 1024.0f;
    } else {
        scale = 1170.2858f;
    }
    dlInitTextureDescriptor(&gArcadeEntityTextures[gGfxBufferIndex][entIndex], gArcadeEntities[entIndex].sprite, 0, gArcadeEntities[entIndex].width, gArcadeEntities[entIndex].width, gArcadeEntities[entIndex].height, 0, 2, 0, 0);
    glist = *glistp;
    dlAppendTextureLoad(&glist, &gArcadeEntityTextures[gGfxBufferIndex][entIndex]);
    dlSetTextureScaleAndFlip(0x400, scale, gArcadeEntities[entIndex].facing & 1, gArcadeEntities[entIndex].flipY);
    if (gArcadeTypeDrawFlags[gArcadeEntities[entIndex].type] & 2) {
        dlAppendTextureRectangle(&glist, (s32)(gArcadeEntities[entIndex].x - gArcadeTypeOriginX[gArcadeEntities[entIndex].type]) * 4, (s32)((gArcadeEntities[entIndex].y - gArcadeTypeOriginY[gArcadeEntities[entIndex].type]) * 0.875 + 8.0) * 4);
    } else {
        if (gArcadeEntities[entIndex].type == 2) {
            yOffset = (s32)gArcadeEntities[entIndex].animTimer;
            if (yOffset >= 3) {
                yOffset = 5 - yOffset;
            }
        } else {
            yOffset = 0;
        }
        dlAppendTextureRectangle(&glist, (s32)(gArcadeEntities[entIndex].x - gArcadeTypeOriginX[gArcadeEntities[entIndex].type]) * 4, ((gArcadeEntities[entIndex].y - yOffset - gArcadeTypeOriginY[gArcadeEntities[entIndex].type]) * 0.875 + 8.0) * 4.0);
    }
    *glistp = glist;
}

void arcadeRenderEntities(Gfx **glistp) {
    s32 i;
    Gfx *glist;
    glist = *glistp;
    for (i = 0; i < 80; i++) {
        if (gArcadeEntities[i].type != 0 && gArcadeEntities[i].sprite != NULL) {
            if (gArcadeEntities[i].type >= 8 || gArcadeFrozen < 2) {
                arcadeRenderEntity(&glist, i);
            }
        }
    }
    *glistp = glist;
}

s32 arcadeAbs(s32 val) {
    if (val >= 0) {
        return val;
    }
    return -val;
}

extern u16 gArcadePlayerStandSprite[];
extern u16 gArcadePlayerWalkFrontLegUpSprite[];
extern u16 gArcadePlayerWalkBackLegUpSprite[];
extern u16 gArcadePlayerClimbSprite[];
extern u16 gArcadePlayerClimbOverHunchSprite[];
extern u16 gArcadePlayerClimbOverCrawlSprite[];
extern u16 gArcadePlayerClimbEndSprite[];
extern u16 gArcadePlayerHammerUpSprite[];
extern u16 gArcadePlayerHammerDownSprite[];
extern u16 gArcadePlayerHammerUpWalkFrontLegUpSprite[];
extern u16 gArcadePlayerHammerDownWalkFrontLegUpSprite[];
extern u16 gArcadePlayerHammerUpWalkBackLegUpSprite[];
extern u16 gArcadePlayerHammerDownWalkBackLegUpSprite[];
extern u16 gArcadePlayerJumpSprite[];
extern u16 gArcadePlayerLandSprite[];
extern u16 gArcadePlayerSpinFrontSprite[];
extern u16 gArcadePlayerSpinSideSprite[];
extern u16 gArcadePlayerDeadSprite[];

void arcadeUpdatePlayerAnimation(s32 entIndex) {
    s32 frame;
    s32 dirBit;
    s32 col;
    s32 row;
    f32 colX;
    f32 y;

    dirBit = gArcadeEntities[entIndex].facing & 2;
    gArcadeEntities[entIndex].facing = dirBit / 2 | dirBit;
    gArcadeEntities[entIndex].flipY = 0;
    frame = gArcadeEntities[entIndex].animTimer;
    if (gArcadeEntities[entIndex].state == 2) {
        if (gArcadeGameOver && gArcadeGameOver) {} // FAKE: empty guard steers regalloc
        if (gArcadeHammerTimer != 0) {
            if (gArcadeHammerTimer & 8) {
                switch (frame & 3) {
                case 0:
                case 2:
                    gArcadeEntities[entIndex].sprite = gArcadePlayerHammerUpSprite;
                    break;
                case 1:
                    gArcadeEntities[entIndex].sprite = gArcadePlayerHammerUpWalkFrontLegUpSprite;
                    break;
                case 3:
                    gArcadeEntities[entIndex].sprite = gArcadePlayerHammerUpWalkBackLegUpSprite;
                    break;
                }
            } else {
                switch (frame & 3) {
                case 0:
                case 2:
                    gArcadeEntities[entIndex].sprite = gArcadePlayerHammerDownSprite;
                    break;
                case 1:
                    gArcadeEntities[entIndex].sprite = gArcadePlayerHammerDownWalkFrontLegUpSprite;
                    break;
                case 3:
                    gArcadeEntities[entIndex].sprite = gArcadePlayerHammerDownWalkBackLegUpSprite;
                    break;
                }
            }
        } else {
            switch (frame & 3) {
            case 0:
            case 2:
                gArcadeEntities[entIndex].sprite = gArcadePlayerStandSprite;
                break;
            case 1:
                gArcadeEntities[entIndex].sprite = gArcadePlayerWalkFrontLegUpSprite;
                break;
            case 3:
                gArcadeEntities[entIndex].sprite = gArcadePlayerWalkBackLegUpSprite;
                break;
            }
        }
    } else if (gArcadeEntities[entIndex].state == 3) {
        gArcadeEntities[entIndex].sprite = gArcadePlayerJumpSprite;
    } else if (gArcadeEntities[entIndex].state == 5) {
        y = gArcadeEntities[entIndex].y;
        if (gArcadeLadderBottom - y < 1.0f || y - gArcadeLadderTop < 1.0f) {
            gArcadeEntities[entIndex].sprite = gArcadePlayerClimbEndSprite;
        } else if (y - gArcadeLadderTop < 6.0f) {
            gArcadeEntities[entIndex].sprite = gArcadePlayerClimbSprite;
        } else if (y - gArcadeLadderTop < 10.0f) {
            gArcadeEntities[entIndex].sprite = gArcadePlayerClimbOverCrawlSprite;
        } else if (y - gArcadeLadderTop < 14.0f) {
            gArcadeEntities[entIndex].sprite = gArcadePlayerClimbOverHunchSprite;
        } else {
            gArcadeEntities[entIndex].sprite = gArcadePlayerClimbSprite;
        }
        gArcadeEntities[entIndex].facing = (s32)(gArcadeEntities[entIndex].animTimer / 4.5) & 1;
    } else if (gArcadeEntities[entIndex].state == 8) {
        if (gArcadeEntities[entIndex].animTimer > 38.0f) {
            if (gArcadeSpareLives == 0) {
                if (gArcadeEntities[entIndex].animTimer > 48.0f) {
                    if (gArcadeHighScores[4] < gArcadeScore) {
                        arcadeCheckGameOver();
                        return;
                    }
                    if (gArcadeAdventureMode != 0) {
                        arcadeExit();
                        return;
                    }
                    arcadeInitTitleScreen();
                    return;
                }
                if (gArcadeGameOver == 0) {
                    gArcadeGameOver = 1;
                    for (col = 0x6C; col != 0xCC; col += 0x10) {
                        colX = col;
                        for (row = 0xA6; row != 0xC6; row += 0x10) {
                            s32 index = arcadeFindFreeEntitySlot39();
                            gArcadeEntities[index] = gArcadePanelTileTemplate;
                            gArcadeEntities[index].x = colX;
                            gArcadeEntities[index].y = row;
                        }
                    }
                }
            } else {
                gArcadeSpareLives--;
                arcadeFinishStageIntro();
            }
        } else if (gArcadeEntities[entIndex].animTimer > 20.0f) {
            gArcadeEntities[entIndex].sprite = gArcadePlayerDeadSprite;
        } else if (gArcadeEntities[entIndex].animTimer > 8.0f) {
            gArcadeFrozen = 2;
            if ((s32)gArcadeEntities[entIndex].animTimer & 1) {
                gArcadeEntities[entIndex].sprite = gArcadePlayerSpinFrontSprite;
            } else {
                gArcadeEntities[entIndex].sprite = gArcadePlayerSpinSideSprite;
            }
            if (((s32)gArcadeEntities[entIndex].animTimer & 3) == 2) {
                gArcadeEntities[entIndex].facing ^= 1;
            }
            if (((s32)gArcadeEntities[entIndex].animTimer & 3) == 1) {
                gArcadeEntities[entIndex].flipY = !gArcadeEntities[entIndex].flipY;
            }
        }
    } else {
        gArcadeEntities[entIndex].sprite = gArcadePlayerLandSprite;
    }
}

extern s32 gArcadePlayerFloorRow;
extern s32 gArcadePlayerLadder;
extern s32 gArcadePlayerLadderDepth;
extern ArcadeEntity gArcadeScorePopupTemplate;
extern u16 gArcadeScoreThreeHundredSprite[];
extern u16 gArcadeScoreFiveHundredSprite[];
void arcadeUpdatePlayerEntity(s32 entIndex) {
    union {
        f32 f;
        s32 bits;
    } soundPitch;
    s32 floorY;
    s32 i; // ORIG: one index local: the conveyor exit value, scan counter and popup slot are stored to its home sp+0x3c (+0x6b0, +0xce8/+0xd60, +0xe04); a separate popup slot local grows the frame 0x48 -> 0x50
    s32 jumpedCount;
    s32 phase;
    static s32 sStepTimer;
    static s32 sStepPhase;

    if (gArcadeEntities[entIndex].state == 8 || gArcadeFrozen == 0) {
        if (gArcadeEntities[entIndex].state == 2) {
            arcadeCheckPlayerCollision((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
            if (gArcadeEntities[entIndex].vx < 0.0f) {
                gArcadeEntities[entIndex].facing &= 1;
            } else if (gArcadeEntities[entIndex].vx > 0.0f) {
                gArcadeEntities[entIndex].facing |= 2;
            }
            if (((gInputContPads->button & 0x200) || gInputContPads->stick_x < -0x14) && gArcadeWalkMinX < gArcadeEntities[entIndex].x) {
                sStepTimer += 3;
                gArcadeEntities[entIndex].vx = -0.7f;
                gArcadeEntities[entIndex].animTimer += 0.3;
            } else if (((gInputContPads->button & 0x100) || gInputContPads->stick_x >= 0x15) && gArcadeEntities[entIndex].x < gArcadeWalkMaxX) {
                sStepTimer += 3;
                gArcadeEntities[entIndex].vx = 0.7f;
                gArcadeEntities[entIndex].animTimer += 0.3;
            } else {
                gArcadeEntities[entIndex].vx = 0.0f;
            }
            if ((gPadPressedButtons[0] & 0xE000) && gArcadeHammerTimer == 0) {
                n_alSndpPlay(gSfxBank, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                gArcadeEntities[entIndex].animTimer = 0.0f;
                gArcadeEntities[entIndex].vy = -1.2f;
                gArcadeEntities[entIndex].vx *= 0.65;
                gArcadeEntities[entIndex].param2 = gArcadeEntities[entIndex].y;
                gArcadeEntities[entIndex].state = 3;
            }
        }
        if (gArcadeEntities[entIndex].y < arcadeCheckPlayerCollision((s32)(gArcadeEntities[entIndex].x + gArcadeEntities[entIndex].vx), (s32)gArcadeEntities[entIndex].y) + 3) {
            gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
        } else {
            gArcadeEntities[entIndex].vx = 0.0f;
        }
        if (gArcadeEntities[entIndex].state != 8 && gArcadeStage == 3 &&
            ((76.0f < gArcadeEntities[entIndex].x && gArcadeEntities[entIndex].x < 100.0f) || (140.0f < gArcadeEntities[entIndex].x && gArcadeEntities[entIndex].x < 164.0f)) &&
            ((gArcadeEntities[entIndex].y < 116.0f && 90.0f < gArcadeEntities[entIndex].y) || 239.0f < gArcadeEntities[entIndex].y)) {
            arcadeKillPlayer();
            return;
        }
        gArcadePlayerLadder = arcadeCheckStageLadders((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
        floorY = arcadeCheckPlayerCollision((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
        gArcadePlayerFloorRow = gArcadeFloorRow;
        switch (gArcadeEntities[entIndex].state) {
        case 2:
            for (i = 0; i < 4; i++) {
                if (gArcadeFloorRow == i) {
                    gArcadeEntities[gArcadePlayerIndex].x += gArcadeConveyorSpeeds[i];
                }
            }
            if (gArcadeEntities[entIndex].x <= gArcadeWalkMinX - 1) {
                gArcadeEntities[entIndex].x = gArcadeWalkMinX;
            }
            if (gArcadeWalkMaxX + 1 <= gArcadeEntities[entIndex].x) {
                gArcadeEntities[entIndex].x = gArcadeWalkMaxX;
            }
            if (gArcadeLadderClimbTop < gArcadeEntities[entIndex].y &&
                ((gInputContPads->button & 0x800) | (gInputContPads->stick_y >= 0x15)) &&
                gInputContPads->stick_x < 0x29 && gInputContPads->stick_x >= -0x28 &&
                !(gInputContPads->button & 0x300) && gArcadeHammerTimer == 0) {
                gArcadeEntities[entIndex].state = 5;
                gArcadeEntities[entIndex].vx = 0.0f;
                gArcadeEntities[entIndex].y -= 1.0f;
                gArcadeEntities[entIndex].x = gArcadeLadderX;
                break;
            } else if (gArcadeEntities[entIndex].y < gArcadeLadderBottom && gArcadeLadderClimbTop <= gArcadeEntities[entIndex].y &&
                       !(gInputContPads->button & 0x300) &&
                       gInputContPads->stick_x < 0x29 && gInputContPads->stick_x >= -0x28 &&
                       ((gInputContPads->button & 0x400) | (gInputContPads->stick_y < -0x14)) &&
                       gArcadeHammerTimer == 0) {
                gArcadeEntities[entIndex].state = 5;
                gArcadeEntities[entIndex].vx = 0.0f;
                gArcadeEntities[entIndex].y += 1.0f;
                gArcadeEntities[entIndex].x = gArcadeLadderX;
                break;
            } else {
                if (floorY - gArcadeEntities[entIndex].y < 2.0f) {
                    gArcadeEntities[entIndex].y = floorY;
                } else {
                    gArcadeEntities[entIndex].state = 3;
                    gArcadeEntities[entIndex].vx = 0.0f;
                    gArcadeEntities[entIndex].vy = 0.0f;
                    gArcadeEntities[entIndex].param2 = gArcadeEntities[entIndex].y;
                }
            }
            break;
        case 5:
            if (floorY == gArcadeEntities[entIndex].y &&
                ((gInputContPads->button & 0x300) | (gInputContPads->stick_x >= 0x15) | (gInputContPads->stick_x < -0x14) ||
                 (gArcadeFloorRow == 2 && gArcadeConveyorSpeeds[2] != 0) ||
                 (gArcadeFloorRow == 1 && gArcadeConveyorSpeeds[1] != 0) ||
                 (gArcadeFloorRow == 3 && gArcadeConveyorSpeeds[3] != 0))) {
                gArcadeEntities[entIndex].state = 2;
            } else if (floorY == gArcadeEntities[entIndex].y && (gPadPressedButtons[0] & 0xE000)) {
                n_alSndpPlay(gSfxBank, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                gArcadeEntities[entIndex].animTimer = 0.0f;
                gArcadeEntities[entIndex].vy = -1.2f;
                gArcadeEntities[entIndex].vx *= 0.65;
                gArcadeEntities[entIndex].state = 3;
                gArcadeEntities[entIndex].param2 = gArcadeEntities[entIndex].y;
            } else {
                if (gArcadeEntities[entIndex].y < gArcadeLadderClimbTop) {
                    gArcadeEntities[entIndex].y += 0.2;
                    if (gArcadeLadderClimbTop - gArcadeEntities[entIndex].y > 10.0f) {
                        gArcadeEntities[entIndex].y = gArcadeLadderClimbTop - 10;
                    }
                    if (gArcadeLadderClimbTop < gArcadeEntities[entIndex].y) {
                        gArcadeEntities[entIndex].y = gArcadeLadderClimbTop;
                    }
                } else {
                    if (gArcadeLadderClimbTop < gArcadeEntities[entIndex].y &&
                        ((gInputContPads->button & 0x800) | (gInputContPads->stick_y >= 0x15))) {
                        gArcadeEntities[entIndex].vy = -0.5f;
                        sStepTimer += 2;
                    } else if (gArcadeEntities[entIndex].y < gArcadeLadderBottom &&
                               ((gInputContPads->button & 0x400) | (gInputContPads->stick_y < -0x14))) {
                        gArcadeEntities[entIndex].vy = 0.5f;
                        sStepTimer += 2;
                    } else {
                        gArcadeEntities[entIndex].vy = 0.0f;
                    }
                    gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
                    gArcadeEntities[entIndex].animTimer += gArcadeEntities[entIndex].vy;
                }
            }
            break;
        case 3:
            if (gArcadeWalkMaxX < gArcadeEntities[entIndex].x) {
                gArcadeEntities[entIndex].x = gArcadeWalkMaxX;
                if (gArcadeEntities[entIndex].vy < 1.8) {
                    gArcadeEntities[entIndex].facing &= 1;
                    gArcadeEntities[entIndex].vx = -gArcadeEntities[entIndex].vx;
                    gArcadeEntities[entIndex].vy = -gArcadeEntities[entIndex].vy;
                }
            } else if (gArcadeEntities[entIndex].x < gArcadeWalkMinX) {
                gArcadeEntities[entIndex].x = gArcadeWalkMinX;
                if (gArcadeEntities[entIndex].vy < 1.8) {
                    gArcadeEntities[entIndex].facing |= 2;
                    gArcadeEntities[entIndex].vx = -gArcadeEntities[entIndex].vx;
                    gArcadeEntities[entIndex].vy = -gArcadeEntities[entIndex].vy;
                }
            }
            gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
            gArcadeEntities[entIndex].vy += 0.06;
            if (0.0f <= gArcadeEntities[entIndex].vy && gArcadeEntities[entIndex].vy < 0.06) {
                jumpedCount = 0;
                for (i = 0; i < 0x50; i++) {
                    if (gArcadeEntities[i].type == 1 || gArcadeEntities[i].type == 2) {
                        if (arcadeAbs((s32)(gArcadeEntities[i].x - gArcadeEntities[entIndex].x)) < 0xD) {
                            if (gArcadeEntities[i].y - gArcadeEntities[entIndex].y < 24.0f && gArcadeEntities[entIndex].y < gArcadeEntities[i].y) {
                                jumpedCount++;
                            }
                        }
                    }
                }
                if (jumpedCount != 0) {
                    i = arcadeFindFreeEntitySlot39();
                    gArcadeEntities[i] = gArcadeScorePopupTemplate;
                    gArcadeEntities[i].x = gArcadeEntities[entIndex].x;
                    gArcadeEntities[i].y = gArcadeEntities[entIndex].y + 9.0f;
                    if (jumpedCount == 1) {
                        arcadeAddScore(100);
                    } else if (jumpedCount == 2) {
                        gArcadeEntities[i].sprite = gArcadeScoreThreeHundredSprite;
                        arcadeAddScore(300);
                    } else {
                        gArcadeEntities[i].sprite = gArcadeScoreFiveHundredSprite;
                        arcadeAddScore(500);
                    }
                }
            }
            if (gArcadeEntities[entIndex].y - gArcadeEntities[entIndex].param2 > 15.0f) {
                n_alSndpPlay(gSfxBank, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
                gArcadeEntities[entIndex].param2 = 0xFF;
            }
            if (gArcadeEntities[entIndex].vy > 2.5) {
                gArcadeEntities[entIndex].vy = 2.5f;
            }
            if (floorY < gArcadeEntities[entIndex].y && gArcadeEntities[entIndex].y - floorY < 3.0f) {
                gArcadeEntities[entIndex].y = floorY;
                if (gArcadeEntities[entIndex].param2 == 0xFF) {
                    arcadeKillPlayer();
                } else {
                    gArcadeEntities[entIndex].state = 4;
                    gArcadeEntities[entIndex].vy = 0.0f;
                    gArcadeEntities[entIndex].vx = 0.0f;
                    gArcadeEntities[entIndex].animTimer = 4.0f;
                }
            }
            break;
        case 4:
            gArcadeEntities[entIndex].y = floorY;
            gArcadeEntities[entIndex].animTimer -= 1.0f;
            if (gArcadeEntities[entIndex].animTimer == 0.0f) {
                gArcadeEntities[entIndex].state = 2;
            }
            break;
        case 8:
            gArcadeEntities[entIndex].animTimer += 0.125;
            if (gArcadeEntities[entIndex].animTimer == 8.0f) {
                n_alSndpPlay(gSfxBank, 0x54, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            break;
        }
        if (sStepTimer >= 0x24) {
            sStepTimer = 0;
            sStepPhase++;
            if (sStepPhase == 7) {
                sStepPhase = 0;
            }
            phase = sStepPhase;
            if (phase & 1) {
                soundPitch.f = 1.0f;
            } else {
                soundPitch.f = 0.7071120143f;
            }
            n_alSndpPlay(gSfxBank, 0x40, 0x7FFF, 0x3F, 1.0f, 0, &gLoopSfxHandles[1]);
            n_alSndpPostEvent(gLoopSfxHandles[1], 0x10, soundPitch.bits);
        }
        floorY = arcadeCheckPlayerCollision((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
        gArcadeEntities[entIndex].param = gArcadeFloorRow;
        gArcadePlayerLadderDepth = (s32)(gArcadeEntities[entIndex].y - gArcadeLadderTop);
        if (gArcadeBonusTimer < 0 && gArcadeEntities[entIndex].state != 8) {
            arcadeKillPlayer();
        }
        if (gArcadeFloorRow == 0 && floorY == gArcadeEntities[entIndex].y) {
            n_alSndpPlay(gSfxBank, 0x4C, 0x7FFF, 0x3F, 1.0f, 0, 0);
            arcadeStopSound(0);
            if (gArcadeStage == 1) {
                i = arcadeFindEntityByType(0x16);
            } else if (gArcadeStage == 3) {
                i = arcadeFindEntityByType(0x18);
            } else if (gArcadeStage == 4) {
                i = arcadeFindEntityByType(0x19);
            }
            gArcadeEntities[i].state = 5;
            if (gArcadeStage != 4) {
                gArcadeEntities[i].type = 0x16;
            }
            gArcadeEntities[i].animTimer = 0.0f;
            gArcadeFrozen = 3;
            gArcadeEntities[entIndex].sprite = gArcadePlayerStandSprite;
            gArcadeEntities[entIndex].facing = 0;
            return;
        }
        if (gArcadeEntities[entIndex].state != 0) {
            arcadeUpdatePlayerAnimation(entIndex);
        }
    }
}

void arcadeUpdateEntitySprite(s32 entIndex) {
    ArcadeEntity *barrel = &gArcadeEntities[entIndex];
    s32 frame = (s32)barrel->animTimer;

    if (barrel->state == 5 || barrel->state == 7 || barrel->state == 1) {
        if (barrel->param2 != 0) {
            switch (frame & 1) {
            case 0:
                barrel->sprite = gArcadeBarrelBlueSideDarkBandSprite;
                return;
            case 1:
                barrel->sprite = gArcadeBarrelBlueSideLightBandSprite;
                return;
            }
        } else {
            switch (frame & 1) {
            case 0:
                barrel->sprite = gArcadeBarrelSideDarkBandSprite;
                return;
            case 1:
                barrel->sprite = gArcadeBarrelSideLightBandSprite;
                return;
            }
        }
    } else {
        if (barrel->param2 != 0) {
            switch (frame & 3) {
            case 0:
                barrel->sprite = gArcadeBarrelBlueRollTopRightSprite;
                return;
            case 1:
                barrel->sprite = gArcadeBarrelBlueRollBottomRightSprite;
                return;
            case 2:
                barrel->sprite = gArcadeBarrelBlueRollBottomLeftSprite;
                return;
            case 3:
                barrel->sprite = gArcadeBarrelBlueRollTopLeftSprite;
                return;
            }
        } else {
            switch (frame & 3) {
            case 0:
                barrel->sprite = gArcadeBarrelRollTopRightSprite;
                return;
            case 1:
                barrel->sprite = gArcadeBarrelRollBottomRightSprite;
                return;
            case 2:
                barrel->sprite = gArcadeBarrelRollBottomLeftSprite;
                return;
            case 3:
                barrel->sprite = gArcadeBarrelRollTopLeftSprite;
                return;
            }
        }
    }
}


void arcadeUpdateBarrelEntity(s32 entIndex) {
    s32 floorY;
    s32 idx;

    if (gArcadeFrozen == 0) {
        if (gArcadeEntities[entIndex].state == 0 || gArcadeEntities[entIndex].state == 1) {
            arcadeUpdateEntitySprite(entIndex);
            return;
        }
        gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
        floorY = arcadeCheckPlayerCollision((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
        arcadeCheckStageLadders((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
        switch (gArcadeEntities[entIndex].state) {
        case 2:
            gArcadeEntities[entIndex].animTimer += 0.2;
            gArcadeEntities[entIndex].vx = 1 - gArcadeEntities[entIndex].facing * 2;
            if (gArcadeEntities[entIndex].y < gArcadeLadderBottom &&
                (gArcadeFloorRow + 1 < gArcadePlayerFloorRow ||
                 (gArcadePlayerFloorRow == gArcadeFloorRow + 1 && (gArcadePlayerLadderDepth >= 0x12 || gArcadeEntities[gArcadePlayerIndex].state != 5)))) {
                if (gArcadeEntities[entIndex].param & 0x80) {
                    break;
                }
                gArcadeEntities[entIndex].param &= 0xF;
                if (gArcadeEntities[entIndex].param > 0) {
                    gArcadeEntities[entIndex].param -= 1;
                    gArcadeEntities[entIndex].state = 5;
                    gArcadeEntities[entIndex].vx = 0.0f;
                    gArcadeEntities[entIndex].y += 1.0f;
                    gArcadeEntities[entIndex].vy = 1.0f;
                    gArcadeEntities[entIndex].x = gArcadeLadderX;
                    break;
                }
                gArcadeEntities[entIndex].param |= 0x80;
            } else if (!(gArcadeEntities[entIndex].param & 0x47)) {
                gArcadeEntities[entIndex].param = (4096.0f + arcadeMinFloat(gArcadeLevel, 5.0f) * 1512.0f > arcadeRand()) | 0x40;
            }
            if (floorY - gArcadeEntities[entIndex].y < 3.0f) {
                gArcadeEntities[entIndex].y = floorY;
            } else {
                gArcadeEntities[entIndex].state = 3;
                gArcadeEntities[entIndex].vy = 0.0f;
                gArcadeEntities[entIndex].vx /= 2;
            }
            break;
        case 3:
            gArcadeEntities[entIndex].animTimer += 0.2;
            gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
            gArcadeEntities[entIndex].vy += 0.06;
            if (gArcadeEntities[entIndex].y > floorY && gArcadeEntities[entIndex].y - floorY < 3.0f) {
                gArcadeEntities[entIndex].y = floorY;
                gArcadeEntities[entIndex].vy = -gArcadeEntities[entIndex].vy / 3.0f;
                if (gArcadeEntities[entIndex].vy > -0.2) {
                    gArcadeEntities[entIndex].state = 2;
                }
            }
            break;
        case 5:
            gArcadeEntities[entIndex].animTimer += 0.3;
            gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
            if (gArcadeEntities[entIndex].y > gArcadeLadderBottom - 1) {
                gArcadeEntities[entIndex].y = floorY;
                gArcadeEntities[entIndex].facing = 1 - gArcadeEntities[entIndex].facing;
                gArcadeEntities[entIndex].vx = 1 - gArcadeEntities[entIndex].facing * 2;
                gArcadeEntities[entIndex].state = 2;
            }
            break;
        case 7:
            gArcadeEntities[entIndex].animTimer += 0.3;
            gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
            gArcadeEntities[entIndex].vy += 0.06;
            floorY = arcadeCheckPlayerCollision((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
            if (gArcadeEntities[entIndex].y > floorY && gArcadeEntities[entIndex].y - floorY < 8.0f && gArcadeEntities[entIndex].param < gArcadeFloorRow) {
                gArcadeEntities[entIndex].param = gArcadeFloorRow;
                gArcadeEntities[entIndex].y = floorY;
                gArcadeEntities[entIndex].vy = 0.0f;
                if (gArcadeEntities[entIndex].param2 != 2) {
                    gArcadeEntities[entIndex].vx = -gArcadeEntities[entIndex].vx * 0.2 + ((arcadeRand() - 16384.0) * arcadeMinFloat(3.0f, gArcadeLevel)) / 40000.0;
                }
                if (gArcadeEntities[entIndex].y > 230.0f) {
                    gArcadeEntities[entIndex].state = 3;
                    gArcadeEntities[entIndex].facing = 1;
                    gArcadeEntities[entIndex].vx = -1.0f;
                    gArcadeEntities[entIndex].vy = -0.7f;
                }
            }
            break;
        }
        if (gArcadeEntities[gArcadePlayerIndex].param >= gArcadeFloorRow || gArcadeEntities[entIndex].param2 != 0) {
            if (gArcadeEntities[entIndex].x > 270.0f) {
                gArcadeEntities[entIndex].facing = 1;
                gArcadeEntities[entIndex].vx = 1 - gArcadeEntities[entIndex].facing * 2;
            } else if (gArcadeEntities[entIndex].x < 50.0f) {
                gArcadeEntities[entIndex].facing = 0;
                gArcadeEntities[entIndex].vx = 1 - gArcadeEntities[entIndex].facing * 2;
            }
        }
        if (gArcadeEntities[entIndex].x > 278.0f || gArcadeEntities[entIndex].x < 2.0f) {
            gArcadeEntities[entIndex].type = 0;
        }
        if ((gArcadeEntities[entIndex].y > 242.0f) & (gArcadeEntities[entIndex].x < 74.0f)) {
            if (gArcadeEntities[entIndex].param2 != 0) {
                n_alSndpPlay(gSfxBank, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                idx = arcadeFindEntityByType(0x13);
                if (idx < 0) {
                    idx = arcadeFindFreeEntity();
                    gArcadeEntities[idx] = gArcadeOilFireTemplate;
                }
                gArcadeEntities[idx].state = 3;
                gArcadeEntities[entIndex].type = 0;
            } else {
                gArcadeEntities[entIndex].type = 0;
            }
        }
        if (gArcadeEntities[entIndex].x - gArcadeEntities[gArcadePlayerIndex].x < 8.0f && gArcadeEntities[gArcadePlayerIndex].x - gArcadeEntities[entIndex].x < 8.0f) {
            if (gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y < 3.0f && gArcadeEntities[gArcadePlayerIndex].y - gArcadeEntities[entIndex].y < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(entIndex);
    }
}

extern u16 gArcadeConveyorPulleyTiltRightSprite[];
extern u16 gArcadeConveyorPulleyFlatSprite[];
extern u16 gArcadeConveyorPulleyTiltLeftSprite[];
extern u16 gArcadePaulineLowerSprite[];
extern u16 gArcadeScoreEightHundredSprite[];
extern u16 gArcadeSmashRingSprite[];
extern u16 gArcadeSmashSmallRingSprite[];
extern u16 gArcadeSmashDotSprite[];
extern u16 gArcadeSmashBurstSprite[];
extern u16 gArcadeCoinSprite[];
extern u16 gArcadeHeartSprite[];
extern u16 gArcadePaulineUpperSprite[];
extern u16 gArcadePaulineUpperFrontSprite[];
extern u16 gArcadeBrokenHeartSprite[];
extern u16 gArcadeHelpSprite[];
extern u16 gArcadeHelpBlueSprite[];
extern s32 gArcadeFireballSpawnPoints[];

extern u16 gArcadeFireballSprite[];
extern u16 gArcadeFireballFlickerSprite[];
extern u16 gArcadeFireballStage2Sprite[];
extern u16 gArcadeFireballStage2FlickerSprite[];
extern u16 gArcadeFireballStage2BlueSprite[];
extern u16 gArcadeFireballStage2BlueFlickerSprite[];
extern u16 gArcadeFireballBlueSprite[];
extern u16 gArcadeFireballBlueFlickerSprite[];
void arcadeUpdateFireballEntity(s32 entIndex) {
    s32 floorY;
    s32 bias;

    if (gArcadeFrozen != 0) {
        return;
    }
    gArcadeEntities[entIndex].animTimer += 0.15;
    if (gArcadeEntities[entIndex].animTimer >= 5.0f) {
        gArcadeEntities[entIndex].animTimer -= 5.0f;
    }
    if (gArcadeStage == 2) {
        if (gArcadeHammerTimer != 0) {
            if ((gArcadeScreenTimer / 4) & 1) {
                gArcadeEntities[entIndex].sprite = gArcadeFireballStage2BlueSprite;
            } else {
                gArcadeEntities[entIndex].sprite = gArcadeFireballStage2BlueFlickerSprite;
            }
        } else if ((gArcadeScreenTimer / 4) & 1) {
            gArcadeEntities[entIndex].sprite = gArcadeFireballStage2Sprite;
        } else {
            gArcadeEntities[entIndex].sprite = gArcadeFireballStage2FlickerSprite;
        }
    } else if (gArcadeHammerTimer != 0) {
        if ((gArcadeScreenTimer / 4) & 1) {
            gArcadeEntities[entIndex].sprite = gArcadeFireballBlueSprite;
        } else {
            gArcadeEntities[entIndex].sprite = gArcadeFireballBlueFlickerSprite;
        }
    } else if ((gArcadeScreenTimer / 4) & 1) {
        gArcadeEntities[entIndex].sprite = gArcadeFireballSprite;
    } else {
        gArcadeEntities[entIndex].sprite = gArcadeFireballFlickerSprite;
    }
    floorY = arcadeCheckPlayerCollision((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
    arcadeCheckStageLadders((s32)gArcadeEntities[entIndex].x, (s32)gArcadeEntities[entIndex].y);
    switch (gArcadeEntities[entIndex].state) {
    case 2:
        if (arcadeRand() < arcadeMinFloat(gArcadeLevel, 5.0f) * 60.0f + 256.0f) {
            bias = gArcadeEntities[entIndex].x < gArcadeEntities[gArcadePlayerIndex].x;
            bias += ((gArcadeEntities[gArcadePlayerIndex].facing & 2) * 3) / 2;
            gArcadeEntities[entIndex].facing = (arcadeRand() + bias * 0xFB8) - 0x1F70 >= 0x4001;
        }
        if (arcadeCheckPlayerCollision((s32)(gArcadeEntities[entIndex].x + gArcadeEntities[entIndex].vx * 8.0f), (s32)gArcadeEntities[entIndex].y) - gArcadeEntities[entIndex].y > 5.0f) {
            gArcadeEntities[entIndex].facing = !gArcadeEntities[entIndex].facing;
        } else {
            gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
        }
        gArcadeEntities[entIndex].vx = (gArcadeEntities[entIndex].facing - 0.5) * (arcadeMinFloat(gArcadeLevel, 5.0f) / 15.0 + 1.0);
        bias = (s32)((gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y) * arcadeMinFloat(gArcadeLevel, 5.0f) * 3.0f);
        if (gArcadeEntities[entIndex].y < gArcadeLadderBottom && arcadeRand() < 0x400 - bias) {
            gArcadeEntities[entIndex].state = 5;
            gArcadeEntities[entIndex].vx = 0.0f;
            gArcadeEntities[entIndex].y += 1.0f;
            gArcadeEntities[entIndex].vy = 2.0 * (arcadeMinFloat(gArcadeLevel, 5.0f) / 30.0 + 0.2);
            gArcadeEntities[entIndex].x = gArcadeLadderX;
        } else if (gArcadeEntities[entIndex].y > gArcadeLadderTop && arcadeRand() < bias + 0x400) {
            gArcadeEntities[entIndex].state = 6;
            gArcadeEntities[entIndex].vx = 0.0f;
            gArcadeEntities[entIndex].y -= 1.0f;
            gArcadeEntities[entIndex].vy = -(arcadeMinFloat(gArcadeLevel, 5.0f) / 30.0 + 0.2);
            gArcadeEntities[entIndex].x = gArcadeLadderX;
        } else if (floorY - gArcadeEntities[entIndex].y < 3.0f) {
            gArcadeEntities[entIndex].y = floorY;
        } else {
            gArcadeEntities[entIndex].facing = !gArcadeEntities[entIndex].facing;
        }
        break;
    case 3:
        gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
        gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
        gArcadeEntities[entIndex].vy += 0.06;
        if (gArcadeEntities[entIndex].y > floorY && gArcadeEntities[entIndex].y - floorY < 3.0f) {
            gArcadeEntities[entIndex].y = floorY;
            gArcadeEntities[entIndex].vy = -gArcadeEntities[entIndex].vy / 3.0f;
            if (gArcadeEntities[entIndex].vy > -0.2) {
                gArcadeEntities[entIndex].state = 2;
            }
        }
        break;
    case 5:
        gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
        if (gArcadeEntities[entIndex].y > gArcadeLadderBottom - 1) {
            gArcadeEntities[entIndex].y = floorY;
            gArcadeEntities[entIndex].facing = 1 - gArcadeEntities[entIndex].facing;
            gArcadeEntities[entIndex].vx = 1 - gArcadeEntities[entIndex].facing * 2;
            gArcadeEntities[entIndex].state = 2;
        }
        break;
    case 6:
        gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
        if (gArcadeEntities[entIndex].y < gArcadeLadderTop + 1) {
            gArcadeEntities[entIndex].y = floorY;
            gArcadeEntities[entIndex].facing = 1 - gArcadeEntities[entIndex].facing;
            gArcadeEntities[entIndex].vx = 1 - gArcadeEntities[entIndex].facing * 2;
            gArcadeEntities[entIndex].state = 2;
        }
        break;
    }
    if (gArcadeEntities[entIndex].x > 270.0f) {
        gArcadeEntities[entIndex].facing = 0;
        gArcadeEntities[entIndex].vx = gArcadeEntities[entIndex].facing - 0.5;
    } else if (gArcadeEntities[entIndex].x < 50.0f) {
        gArcadeEntities[entIndex].facing = 1;
        gArcadeEntities[entIndex].vx = gArcadeEntities[entIndex].facing - 0.5;
    }
    if (gArcadeEntities[entIndex].x - gArcadeEntities[gArcadePlayerIndex].x < 8.0f && gArcadeEntities[gArcadePlayerIndex].x - gArcadeEntities[entIndex].x < 8.0f) {
        if (gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y < 3.0f && gArcadeEntities[gArcadePlayerIndex].y - gArcadeEntities[entIndex].y < 8.0f) {
            arcadeKillPlayer();
        }
    }
}

extern u16 gArcadeSpringExtendedSprite[];
extern u16 gArcadeSpringCompressedSprite[];

void arcadeUpdateSpringEntity(s32 entIndex) {
    s32 frame;

    if (gArcadeFrozen == 0) {
        gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
        gArcadeEntities[entIndex].animTimer += 0.1;
        frame = (s32)gArcadeEntities[entIndex].animTimer;
        switch (frame & 1) {
        case 0:
            gArcadeEntities[entIndex].sprite = gArcadeSpringExtendedSprite;
            break;
        case 1:
            gArcadeEntities[entIndex].sprite = gArcadeSpringCompressedSprite;
            break;
        }
        gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
        if (gArcadeEntities[entIndex].vy < 5.0f) {
            gArcadeEntities[entIndex].vy += 0.3;
        }
        if (gArcadeEntities[entIndex].y > 81.0f) {
            if (gArcadeEntities[entIndex].x < 220.0f) {
                gArcadeEntities[entIndex].y = 81.0f;
                gArcadeEntities[entIndex].vy = -3.5f;
                if (gArcadeEntities[entIndex].x > 40.0f) {
                    n_alSndpPlay(gSfxBank, 0x43, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
            } else if (gArcadeEntities[entIndex].vx != 0.0f) {
                gArcadeEntities[entIndex].vx = 0.0f;
                n_alSndpPlay(gSfxBank, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
        }
        if (gArcadeEntities[entIndex].y > 271.0f) {
            gArcadeEntities[entIndex].type = 0;
        }
        if (arcadeAbs(gArcadeEntities[entIndex].x - gArcadeEntities[gArcadePlayerIndex].x) < 7) {
            if (gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y < 4.0f && gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

extern u16 gArcadeOilFireSprite[];
extern u16 gArcadeOilFireFlickerSprite[];
extern u16 gArcadeOilFireFlareSprite[];
extern u16 gArcadeOilFireFlareFlickerSprite[];

void arcadeUpdateOilDrumEntity(s32 entIndex) {
    s32 n; // FAKE: one local for the case-2 barrel-count limit (home sp+0x24, sw/lw +0x15c/+0x160) and the case-3 new slot (register only); a separate slot local keeps the frame 0x28 but moves the a1 spill 0x1c -> 0x18

    if (gArcadeFrozen == 0) {
        if (--gArcadeEntities[entIndex].param >= 0x15) {
            gArcadeEntities[entIndex].param = arcadeRand() & 0xF;
            gArcadeEntities[entIndex].param2 = !gArcadeEntities[entIndex].param2;
        }
        switch (gArcadeEntities[entIndex].state) {
        case 2:
            switch (gArcadeEntities[entIndex].param2) {
            case 0:
                gArcadeEntities[entIndex].sprite = gArcadeOilFireSprite;
                break;
            case 1:
                gArcadeEntities[entIndex].sprite = gArcadeOilFireFlickerSprite;
                break;
            }
            n = arcadeMinFloat(gArcadeLevel, 5.0f);
            if (gArcadeStage == 4) {
                if (0x64 - n * 0x14 == gArcadeEntities[entIndex].animTimer++) {
                    if (arcadeCountEntitiesByType(2) < n) {
                        gArcadeEntities[entIndex].state = 3;
                        gArcadeEntities[entIndex].animTimer = 0.0f;
                    }
                }
            }
            break;
        case 3:
            if (gArcadeEntities[entIndex].animTimer++ > 40.0f) {
                gArcadeEntities[entIndex].state = 2;
                gArcadeEntities[entIndex].animTimer = 0.0f;
                n = arcadeFindFreeEntitySlot36();
                gArcadeEntities[n] = gArcadeFireballTemplate;
                gArcadeEntities[n].state = 3;
                gArcadeEntities[n].vy = -1.0f;
                if (gArcadeStage == 1) {
                    gArcadeEntities[n].vx = 0.4f;
                } else {
                    if (gArcadeEntities[gArcadePlayerIndex].x < 160.0f) {
                        gArcadeEntities[n].vx = -0.5f;
                    } else {
                        gArcadeEntities[n].vx = 0.5f;
                    }
                    gArcadeEntities[n].facing = 0;
                    gArcadeEntities[n].x = 160.0f;
                    gArcadeEntities[n].y = 135.0f;
                }
            }
            switch (gArcadeEntities[entIndex].param2) {
            case 0:
                gArcadeEntities[entIndex].sprite = gArcadeOilFireFlareSprite;
                break;
            case 1:
                gArcadeEntities[entIndex].sprite = gArcadeOilFireFlareFlickerSprite;
                break;
            }
            break;
        }
    }
}

void arcadeUpdatePaulineLower(s32 entIndex) {
    ArcadeEntity *entry = &gArcadeEntities[entIndex];

    if (gArcadeStage == 2) {
        entry->facing = gArcadeEntities[gArcadePlayerIndex].x < 160.0f;
        entry->x = 152.0f;
        if (gArcadeGirderState == 2) {
            entry->facing = 0;
            entry->y = 63.0f;
        }
    }
    if (gArcadePaulineVisible == 0) {
        entry->sprite = NULL;
    } else {
        entry->sprite = gArcadePaulineLowerSprite;
    }
}

void arcadeUpdatePaulineUpper(s32 entIndex) {
    ArcadeEntity *entry = &gArcadeEntities[entIndex];

    if (gArcadeStage == 2) {
        entry->facing = gArcadeEntities[gArcadePlayerIndex].x < 160.0f;
        entry->x = 152.0f;
        if (gArcadeGirderState == 2) {
            entry->facing = 0;
            entry->y = 79.0f;
        }
    }
    if (gArcadePaulineVisible == 0) {
        entry->sprite = NULL;
        return;
    }
    if (entry->sprite == NULL) {
        entry->sprite = gArcadePaulineUpperSprite;
    }
    if (gArcadeFrozen == 0) {
        if ((entry->param++ & 0xC8) || (gArcadeScreenMode == 1)) {
            entry->sprite = gArcadePaulineUpperSprite;
        } else {
            entry->sprite = gArcadePaulineUpperFrontSprite;
        }
    }
}

void arcadeUpdateHeartEntity(s32 entIndex) {
    gArcadeEntities[entIndex].sprite = gArcadeCoinSprite;
    if (gArcadePaulineVisible != 0) {
        gArcadeEntities[entIndex].y = gArcadeEntities[arcadeFindEntityByType(0x1A)].y - 8.0f;
        gArcadeEntities[entIndex].x = gArcadeEntities[arcadeFindEntityByType(0x1A)].x;
    } else {
        if (gArcadeEntities[entIndex - 1].sprite == NULL) {
            gArcadeEntities[entIndex].sprite = NULL;
        }
        gArcadeEntities[entIndex].y = gArcadeEntities[entIndex - 1].y + 20.0f;
        gArcadeEntities[entIndex].x = gArcadeEntities[entIndex - 1].x + 30.0f;
    }
    gArcadeEntities[arcadeFindEntityByType(0x1A)].sprite = NULL;
    gArcadeEntities[arcadeFindEntityByType(0x1B)].sprite = NULL;
    if (arcadeFindEntityByType(0x1D) >= 0 && gArcadeEntities[arcadeFindEntityByType(0x1D)].sprite != gArcadeHeartSprite) {
        gArcadeEntities[arcadeFindEntityByType(0x1D)].sprite = NULL;
    }
}

void arcadeUpdateHelpSpeechBubble(s32 entIndex) {
    if (gArcadeStage == 2) {
        gArcadeEntities[entIndex].x = (gArcadeEntities[gArcadePlayerIndex].x >= 160.0f) * 0x28 + 0x80;
        if (gArcadeGirderState == 2) {
            gArcadeEntities[entIndex].facing = 0;
            gArcadeEntities[entIndex].y = 63.0f;
        }
    }
    if (gArcadeFrozen == 3) {
        if (gArcadePaulineVisible == 0) {
            gArcadeEntities[entIndex].sprite = gArcadeBrokenHeartSprite;
        } else {
            gArcadeEntities[entIndex].sprite = gArcadeHeartSprite;
        }
        gArcadeEntities[entIndex].width = 0x10;
        gArcadeEntities[entIndex].height = 0x10;
        return;
    }
    if (gArcadePaulineVisible == 0) {
        gArcadeEntities[entIndex].sprite = NULL;
        return;
    }
    if (gArcadeFrozen == 0) {
        if (!(gArcadeEntities[entIndex].param++ & 0xC0)) {
            if (gArcadeStage == 2 || gArcadeStage == 4) {
                gArcadeEntities[entIndex].sprite = gArcadeHelpBlueSprite;
                return;
            }
            gArcadeEntities[entIndex].sprite = gArcadeHelpSprite;
            return;
        }
        gArcadeEntities[entIndex].sprite = NULL;
    }
}

void arcadeUpdateConveyorPulleys(s32 entIndex) {
    s32 phase;
    ArcadeEntity *entity;

    if (gArcadeFrozen == 0) {
        entity = &gArcadeEntities[entIndex];
        entity->param2 += gArcadeConveyorSpeeds[entity->param];
        phase = entity->param2;
        if (phase < 0) {
            entity->param2 = phase + 0x2EE00;
            phase = entity->param2;
        }
        switch ((phase / 8) % 3) {
        case 0:
            entity->sprite = gArcadeConveyorPulleyTiltRightSprite;
            break;
        case 1:
            entity->sprite = gArcadeConveyorPulleyFlatSprite;
            break;
        case 2:
            entity->sprite = gArcadeConveyorPulleyTiltLeftSprite;
            break;
        }
    }
}
extern u16 gArcadeKongGrinSprite[];
extern u16 gArcadeKongStandSprite[];
extern u16 gArcadeKongCarryClimbReachSprite[];
extern u16 gArcadeKongCarryClimbPullSprite[];

void arcadeUpdateDonkeyKongIntro(s32 entIndex) {
    if (gArcadeScreenTimer == 0x3C) {
        n_alSndpPlay(gSfxBank, 0x46, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    if (gArcadeScreenTimer >= 0x3C) {
        if (gArcadeScreenTimer >= 0x169) {
            gArcadeEntities[entIndex].vy += 0.05;
            gArcadeEntities[entIndex].y += gArcadeEntities[entIndex].vy;
            gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
            if (gArcadeEntities[entIndex].vy > 0.0f && gArcadeEntities[entIndex].y >= 38.0f) {
                gArcadePaulineVisible = 1;
                gArcadeEntities[entIndex].y = 38.0f;
                if (gArcadeScreenTimer == 0x26C) {
                    n_alSndpPlay(gSfxBank, 0x53, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    gArcadeEntities[entIndex].sprite = gArcadeKongGrinSprite;
                }
                if (gArcadeScreenTimer == 0x2D0 || gArcadeScreenTimer < 0x26C) {
                    gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
                }
                if (gArcadeEntities[entIndex].vy > 0.06) {
                    gArcadeGirderState += 1;
                    n_alSndpPlay(gSfxBank, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
                if (gArcadeEntities[entIndex].x > 74.0f && gArcadeScreenTimer >= 0x1A5) {
                    gArcadeEntities[entIndex].vx = -0.5f;
                    gArcadeEntities[entIndex].vy = -0.81f;
                    return;
                }
                gArcadeEntities[entIndex].vx = 0.0f;
                gArcadeEntities[entIndex].vy = 0.0f;
            }
        } else {
            if (gArcadeEntities[entIndex].y > 74.0f) {
                gArcadeEntities[entIndex].vy = -2.0f;
                gArcadeEntities[entIndex].vx = 0.0f;
                gArcadeEntities[entIndex].y = 0xC5 - ((gArcadeScreenTimer - 0x3C) / 2);
                if (gArcadeScreenTimer & 8) {
                    gArcadeEntities[entIndex].sprite = gArcadeKongCarryClimbReachSprite;
                    return;
                }
                gArcadeEntities[entIndex].sprite = gArcadeKongCarryClimbPullSprite;
            }
        }
    }
}

extern u16 gArcadeKongSideSprite[];
extern u16 gArcadeKongHoldBarrelSprite[];
extern u16 gArcadeKongClimbSprite[];
extern ArcadeEntity gArcadeBarrelTemplate;
void arcadeUpdateDonkeyKongStage1(s32 entIndex) {
    s32 idx;
    s32 barrelNum;

    if (gArcadeFrozen == 0 || gArcadeEntities[entIndex].state == 5) {
        switch (gArcadeEntities[entIndex].state) {
        case 12:
            gArcadeEntities[entIndex].param -= 1;
            if (gArcadeEntities[entIndex].param == 0) {
                gArcadeEntities[entIndex].param = 0x14;
                gArcadeEntities[entIndex].state = 9;
                gArcadeEntities[entIndex].sprite = gArcadeKongSideSprite;
                gArcadeEntities[entIndex].facing = 0;
                idx = arcadeFindFreeEntity();
                gArcadeEntities[entIndex].param2 = idx;
                barrelNum = (s32)gArcadeEntities[entIndex].animTimer++;
                gArcadeEntities[idx] = gArcadeBarrelTemplate;
                if (!(barrelNum & 7)) {
                    gArcadeEntities[idx].param2 = 1;
                }
                if (barrelNum == 2 && gArcadeRound != 0) {
                    gArcadeEntities[idx].param = 2;
                    return;
                }
                if (barrelNum == 1) {
                    if (gArcadeRound == 0) {
                        gArcadeEntities[idx].param = 2;
                        return;
                    }
                    gArcadeEntities[idx].param = 5;
                    return;
                }
                if (barrelNum != 0) {
                    if (!(arcadeRand() < arcadeMinFloat(gArcadeLevel, 3.0f) * 2000.0f + 2048.0f)) {
                        return;
                    }
                }
                gArcadeEntities[idx].animTimer = 1.0f;
                if (barrelNum == 0) {
                    gArcadeEntities[idx].param2 = 2;
                    if (gArcadeLevel == 1) {
                        gArcadeEntities[idx].vx = 0.0f;
                        return;
                    }
                    if (gArcadeLevel == 2) {
                        gArcadeEntities[idx].vx = 0.65f;
                        return;
                    }
                    gArcadeEntities[idx].vx = 0.77f;
                    return;
                }
                gArcadeEntities[idx].vx = ((gArcadeEntities[gArcadePlayerIndex].x - 92.0) / 200.0 + (arcadeRand() - 16384.0) / 30000.0) * arcadeMinFloat(3.0f, gArcadeLevel);
                if (arcadeRand() < arcadeMinFloat(gArcadeLevel, 3.0f) * 2000.0f + 4096.0f) {
                    gArcadeEntities[idx].param = 6;
                }
            } else if (gArcadeEntities[entIndex].param == 0x14) {
                gArcadeBonusTimer -= 1;
                return;
            }
            break;
        case 9:
            gArcadeEntities[entIndex].param -= 1;
            if (gArcadeEntities[entIndex].param == 0) {
                idx = gArcadeEntities[entIndex].param2;
                gArcadeEntities[idx].x = 92.0f;
                if (gArcadeEntities[idx].animTimer != 0.0f) {
                    gArcadeEntities[entIndex].param = 0x1E;
                    gArcadeEntities[entIndex].state = 0xB;
                    gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
                    gArcadeEntities[entIndex].facing = 0;
                    gArcadeEntities[idx].state = 7;
                    gArcadeEntities[idx].param = 2;
                    return;
                }
                gArcadeEntities[entIndex].param = 0x3C;
                gArcadeEntities[entIndex].state = 0xA;
                gArcadeEntities[entIndex].sprite = gArcadeKongHoldBarrelSprite;
                gArcadeEntities[entIndex].facing = 0;
                gArcadeEntities[idx].state = 1;
            }
            break;
        case 11:
            gArcadeEntities[entIndex].param -= 1;
            if (gArcadeEntities[entIndex].param == 0) {
                gArcadeEntities[entIndex].param = 51.0f - arcadeMinFloat(gArcadeLevel, 3.0f) * 5.0f + (arcadeRand() & 0xF);
                gArcadeEntities[entIndex].state = 0xC;
                gArcadeEntities[entIndex].sprite = gArcadeKongStompSprite;
                gArcadeEntities[entIndex].facing = 0;
            }
            break;
        case 10:
            idx = gArcadeEntities[entIndex].param2;
            gArcadeEntities[entIndex].param -= 1;
            if (gArcadeEntities[entIndex].param == arcadeMinFloat(gArcadeLevel, 3.0f) * 3.0f) {
                gArcadeEntities[entIndex].param = 51.0f - arcadeMinFloat(gArcadeLevel, 3.0f) * 5.0f + (arcadeRand() & 0xF);
                gArcadeEntities[entIndex].state = 0xC;
                gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
                gArcadeEntities[entIndex].facing = 0;
                return;
            }
            if (gArcadeEntities[entIndex].param == 0x28) {
                gArcadeEntities[entIndex].sprite = gArcadeKongSideSprite;
                gArcadeEntities[entIndex].facing = 1;
                gArcadeEntities[idx].state = 0;
                gArcadeEntities[idx].x = 122.0f;
                gArcadeEntities[idx].y = 83.0f;
                return;
            }
            if (gArcadeEntities[entIndex].param == 0x14) {
                gArcadeEntities[idx].state = 2;
                return;
            }
            break;
        case 5:
            if (gArcadeEntities[entIndex].animTimer++ > 60.0f) {
                if (gArcadePaulineVisible != 0) {
                    gArcadeEntities[entIndex].sprite = gArcadeKongClimbSprite;
                    gArcadeEntities[entIndex].facing = (s32)(gArcadeEntities[entIndex].animTimer / 8) & 1;
                } else {
                    gArcadeEntities[entIndex].facing = 0;
                    if ((s32)(gArcadeEntities[entIndex].animTimer / 8) & 1) {
                        gArcadeEntities[entIndex].sprite = gArcadeKongCarryClimbPullSprite;
                    } else {
                        gArcadeEntities[entIndex].sprite = gArcadeKongCarryClimbReachSprite;
                    }
                }
                if (gArcadeStage != 4) {
                    gArcadeEntities[entIndex].x = 100.0f;
                }
                gArcadeEntities[entIndex].y -= 0.4;
                if (gArcadeEntities[entIndex].y < 23.0f) {
                    gArcadePaulineVisible = 0;
                }
                if (gArcadeEntities[entIndex].animTimer > 280.0f) {
                    gArcadeRound += 1;
                    arcadeFinishStageIntro();
                    return;
                }
                if (gArcadeEntities[entIndex].animTimer == 200.0f && gArcadeBonusTimer > 0) {
                    arcadeAddScore(gArcadeBonusTimer * 0x64);
                    return;
                }
            } else {
                gArcadeEntities[entIndex].facing = 1;
                gArcadeEntities[entIndex].sprite = gArcadeKongSideSprite;
            }
            break;
        }
    }
}

extern u16 gArcadeKongDazedEyesRightSprite[];
extern u16 gArcadeKongDazedEyesUpLeftSprite[];
extern u16 gArcadeKongDazedEyesDownSprite[];
extern ArcadeEntity gArcadeKongStarsTemplate;

void arcadeUpdateDonkeyKongStage4(s32 entIndex) {
    s32 tmp; // FAKE: one register-only local for the incremented param byte and the frame selector; a separate s32 frame local moves the t0 spill 0x2c -> 0x28, the frame inline flips bne v0,v1 at 0xbc7c

    switch (gArcadeEntities[entIndex].state) {
    case 2:
        if (gArcadeFrozen == 0) {
            if (gArcadeScreenTimer % 120 == 0) {
                gArcadeBonusTimer -= 1;
            }
            if (gArcadeEntities[gArcadePlayerIndex].y < 95.0f && gArcadeEntities[gArcadePlayerIndex].y > 76.0f) {
                if (gArcadeEntities[gArcadePlayerIndex].x > 135.0f && gArcadeEntities[gArcadePlayerIndex].x < 186.0f) {
                    arcadeKillPlayer();
                }
            }
            tmp = ++gArcadeEntities[entIndex].param;
            if ((u8)tmp < 0xA0) {
                gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
                return;
            }
            if (!(gArcadeEntities[entIndex].param & 0x1F)) {
                n_alSndpPlay(gSfxBank, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            gArcadeEntities[entIndex].sprite = gArcadeKongStompSprite;
            gArcadeEntities[entIndex].facing = !((gArcadeEntities[entIndex].param & 0x20) / 32);
        }
        break;
    case 8:
        if (gArcadeEntities[entIndex].animTimer++ == 720.0f) {
            gArcadeRound += 1;
            if (gArcadeAdventureMode != 0) {
                gArcadeLevelCleared = 1;
                if (gArcadeHighScores[4] < gArcadeScore) {
                    arcadeCheckGameOver();
                } else {
                    arcadeExit();
                }
            } else {
                arcadeFinishStageIntro();
            }
        } else {
            if (gArcadeEntities[entIndex].animTimer > 480.0f) {
                break;
            }
            if (gArcadeEntities[entIndex].animTimer == 400.0f) {
                if (gArcadeBonusTimer > 0) {
                    arcadeAddScore(gArcadeBonusTimer * 0x64);
                }
            } else if (gArcadeEntities[entIndex].animTimer > 200.0f) {
                if (gArcadeEntities[entIndex].y < 178.0f) {
                    gArcadeEntities[entIndex].flipY = 1;
                    gArcadeEntities[entIndex].y += 1.0f;
                    if (gArcadeEntities[entIndex].y >= 178.0f) {
                        gArcadeEntities[arcadeFindFreeEntity()] = gArcadeKongStarsTemplate;
                    }
                } else {
                    if (gArcadeGirderState != 2) {
                        gArcadeGirderState = 2;
                        n_alSndpPlay(gSfxBank, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    }
                    gArcadeEntities[entIndex].y = 178.0f;
                    gArcadeEntities[entIndex].facing = 0;
                    tmp = (s32)(gArcadeEntities[entIndex].animTimer / 6.0f) % 3;
                    if (tmp == 0) {
                        gArcadeEntities[entIndex].sprite = gArcadeKongDazedEyesRightSprite;
                    } else if (tmp == 1) {
                        gArcadeEntities[entIndex].sprite = gArcadeKongDazedEyesUpLeftSprite;
                    } else if (tmp == 2) {
                        gArcadeEntities[entIndex].sprite = gArcadeKongDazedEyesDownSprite;
                    }
                    if (gArcadeEntities[entIndex].animTimer == 350.0f) {
                        n_alSndpPlay(gSfxBank, 0x50, 0x7FFF, 0x3F, 1.0f, 0, 0);
                        gArcadeEntities[gArcadePlayerIndex].sprite = gArcadePlayerStandSprite;
                        gArcadeEntities[gArcadePlayerIndex].facing = 0;
                        gArcadeEntities[gArcadePlayerIndex].x = 190.0f;
                        gArcadeEntities[gArcadePlayerIndex].y = 93.0f;
                        gArcadeFrozen = 3;
                    }
                }
            } else if (gArcadeEntities[entIndex].animTimer > 180.0f) {
                gArcadeEntities[entIndex].facing = 0;
                gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
            } else if (gArcadeEntities[entIndex].animTimer > 30.0f) {
                gArcadeEntities[entIndex].facing = (s32)(gArcadeEntities[entIndex].animTimer / 6.0f) & 1;
                gArcadeEntities[entIndex].sprite = gArcadeKongStompSprite;
            }
        }
        if (gArcadeEntities[entIndex].animTimer == 2.0f) {
            n_alSndpPlay(gSfxBank, 0x52, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        if (gArcadeEntities[entIndex].animTimer == 200.0f) {
            n_alSndpPlay(gSfxBank, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        break;
    }
}

extern ArcadeEntity gArcadeSpringTemplate;

void arcadeUpdateDonkeyKongStage2(s32 entIndex) {
    s32 flash;

    if (gArcadeFrozen == 0) {
        gArcadeEntities[entIndex].animTimer += 1.0f;
        if ((u8)(s32)gArcadeEntities[entIndex].animTimer < 0xA0) {
            gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
        } else {
            if (!((s32)gArcadeEntities[entIndex].animTimer & 0x1F)) {
                n_alSndpPlay(gSfxBank, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            gArcadeEntities[entIndex].sprite = gArcadeKongStompSprite;
            flash = (((s32)gArcadeEntities[entIndex].animTimer & 0x20) / 32) == 0;
            gArcadeEntities[entIndex].facing = flash;
        }
        if ((s32)gArcadeEntities[entIndex].animTimer % (0x72 - (s32)arcadeMinFloat(gArcadeLevel, 4.0f) * 0xC) == 0) {
            gArcadeBonusTimer -= 1;
            entIndex = arcadeFindFreeEntity(); // ORIG: the parameter is reused; the new index is spilled to the a0 home slot 0x30(sp) at 0xc000 (sw v0) and reloaded at 0xc010 (lw a1), not a frame local
            gArcadeEntities[entIndex] = gArcadeSpringTemplate;
            gArcadeEntities[entIndex].x = (arcadeRand() & 0xF) - 0x1C;
            gArcadeEntities[entIndex].state = 2;
        }
    }
}

void arcadeUpdateDonkeyKongStage3(s32 entIndex) {
    s32 frame;
    s32 timer;
    s32 flash;

    switch (gArcadeEntities[entIndex].state) {
    case 2:
        if (gArcadeFrozen != 0) {
            return;
        }
        frame = gArcadeScreenTimer;
        if (frame % 120 == 0) {
            gArcadeBonusTimer -= 1;
        }
        if (gArcadeEntities[entIndex].x > 204.0f) {
            gArcadeEntities[entIndex].vx = -1.0f;
        }
        if (gArcadeEntities[entIndex].x < 68.0f) {
            gArcadeEntities[entIndex].vx = 1.0f;
        }
        gArcadeEntities[entIndex].animTimer += 1.0f;
        timer = gArcadeEntities[entIndex].animTimer;
        if ((u8)timer < 0xA0) {
            gArcadeEntities[entIndex].sprite = gArcadeKongStandSprite;
        } else {
            gArcadeEntities[entIndex].sprite = gArcadeKongStompSprite;
            flash = (((s32)gArcadeEntities[entIndex].animTimer & 0x20) / 32) == 0;
            gArcadeEntities[entIndex].facing = flash;
        }
        break;
    case 5:
        if (gArcadeEntities[entIndex].x > 100.0f) {
            gArcadeEntities[entIndex].vx = -1.0f;
        } else if (gArcadeEntities[entIndex].x < 100.0f) {
            gArcadeEntities[entIndex].vx = 1.0f;
        } else {
            gArcadeEntities[entIndex].type = 0x16;
            gArcadeEntities[entIndex].vx = 0.0f;
            gArcadeEntities[entIndex].animTimer = 41.0f;
        }
        break;
    }
    if (!(gArcadeScreenTimer & 1)) {
        gArcadeConveyorSpeeds[0] = (s32)gArcadeEntities[entIndex].vx;
        gArcadeEntities[entIndex].x += gArcadeEntities[entIndex].vx;
    }
}

void arcadeUpdateScorePopup(s32 entIndex) {
    if (gArcadeEntities[entIndex].animTimer == 0.0f) {
        n_alSndpPlay(gSfxBank, 0x45, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    if (gArcadeEntities[entIndex].animTimer++ > 40.0f) {
        gArcadeEntities[entIndex].type = 0;
    }
}

void arcadeUpdateCollectibleItem(s32 entIndex) {
    if (gArcadeEntities[entIndex].x == (f32)(s32)gArcadeEntities[gArcadePlayerIndex].x &&
        gArcadeEntities[entIndex].y == (f32)(s32)gArcadeEntities[gArcadePlayerIndex].y) {
        gArcadeEntities[entIndex].type = 0x14;
        if (gArcadeLevel == 1) {
            gArcadeEntities[entIndex].sprite = gArcadeScoreThreeHundredSprite;
            arcadeAddScore(0x12C);
        } else if (gArcadeLevel == 2) {
            gArcadeEntities[entIndex].sprite = gArcadeScoreFiveHundredSprite;
            arcadeAddScore(0x1F4);
        } else {
            gArcadeEntities[entIndex].sprite = gArcadeScoreEightHundredSprite;
            arcadeAddScore(0x320);
        }
    }
}

extern u16 gArcadeHammerUpSprite[];
extern u16 gArcadeHammerDownSprite[];
extern u16 gArcadeHammerUpFlashSprite[];
extern u16 gArcadeHammerDownFlashSprite[];

void arcadeUpdateHammerEntity(u8 entIndex) {
    u8 i;
    u8 idx;

    if (gArcadeFrozen == 0) {
        switch (gArcadeEntities[entIndex].state) {
        case 0:
            if (gArcadeEntities[entIndex].x - gArcadeEntities[gArcadePlayerIndex].x < 8.0f && gArcadeEntities[entIndex].x - gArcadeEntities[gArcadePlayerIndex].x > -8.0f) {
                if (gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y < 8.0f && gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y > -8.0f) {
                    arcadeStopSound(0x49);
                    gArcadeHammerTimer = 0x258;
                    gArcadeEntities[entIndex].state = 2;
                }
            }
            break;
        case 2:
            gArcadeEntities[entIndex].facing = gArcadeEntities[gArcadePlayerIndex].facing;
            if ((gArcadeHammerTimer & 8) || gArcadeEntities[gArcadePlayerIndex].state != 2) {
                if (gArcadeHammerTimer >= 0xF1 || (gArcadeHammerTimer & 4)) {
                    gArcadeEntities[entIndex].sprite = gArcadeHammerUpSprite;
                } else {
                    gArcadeEntities[entIndex].sprite = gArcadeHammerUpFlashSprite;
                }
                gArcadeEntities[entIndex].x = gArcadeEntities[gArcadePlayerIndex].x;
                gArcadeEntities[entIndex].y = gArcadeEntities[gArcadePlayerIndex].y - 16.0f;
            } else {
                if (gArcadeHammerTimer >= 0xF1 || (gArcadeHammerTimer & 4)) {
                    gArcadeEntities[entIndex].sprite = gArcadeHammerDownSprite;
                } else {
                    gArcadeEntities[entIndex].sprite = gArcadeHammerDownFlashSprite;
                }
                if (gArcadeEntities[entIndex].facing != 0) {
                    gArcadeEntities[entIndex].x = gArcadeEntities[gArcadePlayerIndex].x + 15.0f;
                } else {
                    gArcadeEntities[entIndex].x = gArcadeEntities[gArcadePlayerIndex].x - 15.0f;
                }
                gArcadeEntities[entIndex].y = gArcadeEntities[gArcadePlayerIndex].y;
            }
            for (i = 0; i < 0x50; i++) {
                if (gArcadeEntities[i].type == 1 || gArcadeEntities[i].type == 4 || gArcadeEntities[i].type == 2) {
                    if (arcadeAbs(gArcadeEntities[i].x - gArcadeEntities[entIndex].x) < 0xD) {
                        if (arcadeAbs(gArcadeEntities[i].y - gArcadeEntities[entIndex].y) < 8) {
                            n_alSndpPlay(gSfxBank, 0x4B, 0x7FFF, 0x3F, 1.0f, 0, 0);
                            idx = arcadeFindFreeEntitySlot39();
                            gArcadeEntities[idx] = gArcadeBonusItemTemplate;
                            gArcadeEntities[idx].type = 7;
                            gArcadeEntities[idx].param2 = gArcadeEntities[i].type;
                            gArcadeEntities[idx].x = gArcadeEntities[entIndex].x;
                            gArcadeEntities[idx].y = gArcadeEntities[entIndex].y;
                            gArcadeEntities[i].type = 0;
                            gArcadeFrozen = 1;
                        }
                    }
                }
            }
            if (gArcadeHammerTimer-- == 1) {
                gArcadeEntities[entIndex].type = 0;
                arcadeStopSound(0);
                arcadeSetStageMusic();
            }
            break;
        }
    }
}

void arcadeUpdateHammerSmash(u8 entIndex) {
    ArcadeEntity *entity = &gArcadeEntities[entIndex];
    u8 frame;
    u8 roll;

    if (entity->param >= 0x37) {
        entity->sprite = gArcadeSmashBurstSprite;
    } else {
        frame = (entity->param / 6) % 3;
        if (frame == 0) {
            entity->sprite = gArcadeSmashRingSprite;
        } else if (frame == 1) {
            entity->sprite = gArcadeSmashSmallRingSprite;
        } else {
            entity->sprite = gArcadeSmashDotSprite;
        }
    }
    if (entity->param++ == 0x42) {
        entity->type = 0x14;
        roll = arcadeRand();
        if (entity->param2 == 2 && (roll & 3) == 0) {
            entity->sprite = gArcadeScoreEightHundredSprite;
            arcadeAddScore(0x320);
        } else if (entity->param2 == 2 && (roll & 3) == 1) {
            entity->sprite = gArcadeScoreFiveHundredSprite;
            arcadeAddScore(0x1F4);
        } else {
            entity->sprite = gArcadeScoreThreeHundredSprite;
            arcadeAddScore(0x12C);
        }
        entity->animTimer = 0.0f;
        gArcadeFrozen = 0;
    }
}

void arcadeUpdateRivetEntity(u8 entIndex) {
    if (gArcadeEntities[entIndex].x == (f32)(s32)gArcadeEntities[gArcadePlayerIndex].x) {
        f32 diff = gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y;
        if (diff < 20.0f && diff > -2.0f) {
            gArcadeEntities[entIndex].param2 = 1;
            return;
        }
    }
    if (gArcadeEntities[entIndex].param2 != 0) {
        gArcadeEntities[entIndex].type = 0;
        gArcadeRivetMask = gArcadeEntities[entIndex].param ^ gArcadeRivetMask;
        if (gArcadeRivetMask) {
            u8 slot = arcadeFindFreeEntitySlot39();
            ArcadeEntity *popup = &gArcadeEntities[slot];
            *popup = gArcadeScorePopupTemplate;
            popup->x = gArcadeEntities[gArcadePlayerIndex].x;
            popup->y = gArcadeEntities[gArcadePlayerIndex].y + 14.0f;
            popup->animTimer = 0.0f;
            arcadeAddScore(0x64);
        }
    }
}

void arcadeUpdateRetractableLadder(u8 entIndex) {
    f32 step; // FAKE: one local for the decremented timer read and the y step: it colours the timer reads $f2 (lwc1 +0x44/+0x78, c.lt.s +0x48/+0x88) and the step $f0 (+0xa0/+0xa4); the direct field compare swaps $f0/$f2, a separate timer local also grows the frame 0x20 -> 0x28

    if (gArcadeFrozen == 0) {
        gArcadeEntities[entIndex].animTimer -= 1.0f;
        step = gArcadeEntities[entIndex].animTimer;
        if (step < 0.0f) {
            gArcadeEntities[entIndex].animTimer = (arcadeRand() & 0x7F) + 0x1C2;
        }
        step = gArcadeEntities[entIndex].animTimer < 200.0f ? 0.2f : -0.2f;
        gArcadeEntities[entIndex].y += step;
        if (gArcadeEntities[entIndex].y < 97.0f) {
            gArcadeEntities[entIndex].y = 97.0f;
        }
        if (gArcadeEntities[entIndex].y > 110.0f) {
            gArcadeEntities[entIndex].y = 110.0f;
        }
    }
}

void arcadeUpdateCementPanEntity(u8 entIndex) {
    if (gArcadeFrozen == 0) {
        gArcadeEntities[entIndex].x += gArcadeConveyorSpeeds[gArcadeEntities[entIndex].param];
        if (gArcadeEntities[entIndex].x > 288.0f || gArcadeEntities[entIndex].x < 32.0f || (gArcadeEntities[entIndex].x == 160.0f && gArcadeEntities[entIndex].y == 127.0f)) {
            gArcadeEntities[entIndex].type = 0;
        }
        if (arcadeAbs(gArcadeEntities[entIndex].x - gArcadeEntities[gArcadePlayerIndex].x) < 12) {
            if (gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y < 4.0f && gArcadeEntities[entIndex].y - gArcadeEntities[gArcadePlayerIndex].y > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

void arcadeUpdateVictoryPauline(u8 entIndex) {
    if (460.0f < gArcadeEntities[arcadeFindEntityByType(0x17)].animTimer) {
        return;
    }
    gArcadeEntities[entIndex].facing = (gArcadeEntities[entIndex].param++ / 8) & 1;
}

extern u8 *gInitialsCharset;

void arcadeUpdateNameEntryCursor(u8 entIndex) {
    if (gArcadeEntities[entIndex].state != 4) {
        if ((gInputContPads->button & 0x200) || gInputContPads->stick_x < -0x14) {
            switch (--gArcadeCursorRepeatTimer) {
            case 0:
                gArcadeCursorRepeatTimer = 8;
            case 0xB:
                gArcadeEntities[entIndex].param2--;
                if (gArcadeEntities[entIndex].param2 >= 0x29) {
                    gArcadeEntities[entIndex].param2 = 0x1D;
                }
                break;
            }
        } else if ((gInputContPads->button & 0x100) || gInputContPads->stick_x >= 0x15) {
            switch (--gArcadeCursorRepeatTimer) {
            case 0:
                gArcadeCursorRepeatTimer = 8;
            case 0xB:
                gArcadeEntities[entIndex].param2++;
                if (gArcadeEntities[entIndex].param2 >= 0x1E) {
                    gArcadeEntities[entIndex].param2 -= 0x1E;
                }
                break;
            }
        } else {
            gArcadeCursorRepeatTimer = 0xC;
        }
        gArcadeEntities[entIndex].x = (gArcadeEntities[entIndex].param2 % 10) * 0x10 + 0x54;
        gArcadeEntities[entIndex].y = ((gArcadeEntities[entIndex].param2 / 10) << 7) / 7 + 0x4A;
        if (gPadPressedButtons[0] & 0x8000) {
            if (gArcadeEntities[entIndex].param2 == 0x1D || gArcadeScreenTimer == 0x708) {
                gArcadeScreenTimer = 0x744;
                gArcadeHighScoreInitials[gArcadeEntities[entIndex].param][0] = gArcadeEntryInitials[0];
                gArcadeHighScoreInitials[gArcadeEntities[entIndex].param][1] = gArcadeEntryInitials[1];
                gArcadeHighScoreInitials[gArcadeEntities[entIndex].param][2] = gArcadeEntryInitials[2];
                gArcadeEntities[entIndex].state = 4;
                arcadeSaveHighScores();
                return;
            }
            if (gArcadeEntities[entIndex].param2 == 0x1C) {
                if (gArcadeEntities[entIndex].state != 0) {
                    gArcadeEntryInitials[--gArcadeEntities[entIndex].state] = gInitialsCharset[0x1C];
                    return;
                }
            }
            if (gArcadeEntities[entIndex].state < 3) {
                gArcadeEntryInitials[gArcadeEntities[entIndex].state] = gInitialsCharset[gArcadeEntities[entIndex].param2];
                gArcadeEntities[entIndex].state++;
            }
        }
    }
}

void arcadeUpdateBonusBox(u8 entIndex) {
    if (gArcadeEntities[entIndex].param >= gArcadeBonusTimer) {
        gArcadeEntities[entIndex].type = 0;
    }
}


void arcadeDispatchEntities(void) {
    u8 i = 0;

    do {
        switch (gArcadeEntities[i].type) {
        case 1:
            arcadeUpdateBarrelEntity(i);
            break;
        case 2:
            arcadeUpdateFireballEntity(i);
            break;
        case 3:
            arcadeUpdateSpringEntity(i);
            break;
        case 19:
            arcadeUpdateOilDrumEntity(i);
            break;
        case 13:
            arcadeUpdatePlayerEntity(i);
            break;
        case 26:
            arcadeUpdatePaulineUpper(i);
            break;
        case 30:
            arcadeUpdateHeartEntity(i);
            break;
        case 29:
            arcadeUpdateHelpSpeechBubble(i);
            break;
        case 27:
            arcadeUpdatePaulineLower(i);
            break;
        case 18:
            arcadeUpdateConveyorPulleys(i);
            break;
        case 21:
            arcadeUpdateDonkeyKongIntro(i);
            break;
        case 22:
            arcadeUpdateDonkeyKongStage1(i);
            break;
        case 23:
            arcadeUpdateDonkeyKongStage4(i);
            break;
        case 24:
            arcadeUpdateDonkeyKongStage2(i);
            break;
        case 25:
            arcadeUpdateDonkeyKongStage3(i);
            break;
        case 20:
            arcadeUpdateScorePopup(i);
            break;
        case 5:
            arcadeUpdateCollectibleItem(i);
            break;
        case 6:
            arcadeUpdateHammerEntity(i);
            break;
        case 7:
            arcadeUpdateHammerSmash(i);
            break;
        case 11:
            arcadeUpdateRivetEntity(i);
            break;
        case 12:
            arcadeUpdateRetractableLadder(i);
            break;
        case 9:
            arcadeUpdateNameEntryCursor(i);
            break;
        case 4:
            arcadeUpdateCementPanEntity(i);
            break;
        case 15:
            arcadeUpdateVictoryPauline(i);
            break;
        case 10:
            arcadeUpdateBonusBox(i);
            break;
        }
    } while (++i < 0x50);
}

extern ArcadeEntity gArcadeCementPanTemplate;

void arcadeSpawnStage4Enemies(void) {
    u8 i; // FAKE: one local for the conveyor-clear counter (register v1) and the cement-pan slot (home sp+0x1f, sb +0x110 / lbu +0x124); a separate slot local after i moves the home to sp+0x1e, declared first it keeps home and frame but swaps v0/v1 in the loop and v1/a0 at +0x124

    if ((gArcadeScreenTimer & 1) == 0) {
        gArcadeConveyorSpeeds[1] = 1;
        gArcadeConveyorSpeeds[2] = -1;
        if ((gArcadeScreenTimer / 350) & 1) {
            gArcadeConveyorSpeeds[3] = 1;
        } else {
            gArcadeConveyorSpeeds[3] = -1;
        }
    } else {
        i = 0;
        do {
            gArcadeConveyorSpeeds[i++] = 0;
        } while (i < 4);
    }
    if (gArcadeScreenTimer % 120 == 0 && arcadeCountEntitiesByType(4) < 5) {
        i = arcadeFindFreeEntityAfterPlayer();
        gArcadeEntities[i] = gArcadeCementPanTemplate;
        if (arcadeRand() > 0x4000) {
            if ((gArcadeScreenTimer / 350) & 1) {
                gArcadeEntities[i].x = 40.0f;
            } else {
                gArcadeEntities[i].x = 280.0f;
            }
        } else {
            gArcadeEntities[i].y = 127.0f;
            if (arcadeRand() > 0x4000) {
                gArcadeEntities[i].param = 1;
                gArcadeEntities[i].x = 40.0f;
            } else {
                gArcadeEntities[i].param = 2;
                gArcadeEntities[i].x = 280.0f;
            }
        }
    }
}

void arcadeSpawnStage2Enemies(void) {
    u8 idx;
    u8 point;

    if (gArcadeScreenTimer % 200 == 0 && arcadeCountEntitiesByType(2) < 5) {
        idx = arcadeFindFreeEntityAfterPlayer();
        gArcadeEntities[idx] = gArcadeFireballTemplate;
        gArcadeEntities[idx].facing = 0;
        gArcadeEntities[idx].vx = -0.5f;
        gArcadeEntities[idx].x = 244.0f;
        point = arcadeRand() & 7;
        if (point >= 4) {
            point = 1;
        }
        gArcadeEntities[idx].x = gArcadeFireballSpawnPoints[point * 2];
        gArcadeEntities[idx].y = gArcadeFireballSpawnPoints[point * 2 + 1];
        if (160.0f < gArcadeEntities[gArcadePlayerIndex].x) {
            gArcadeEntities[idx].facing = 1 - gArcadeEntities[idx].facing;
            gArcadeEntities[idx].vx = -gArcadeEntities[idx].vx;
            gArcadeEntities[idx].x = 320.0f - gArcadeEntities[idx].x;
        }
    }
    if (gArcadeRivetMask == 0) {
        arcadeStopSound(0);
        gArcadeRivetMask = 1;
        gArcadeGirderState = 1;
        gArcadeFrozen = 2;
        gArcadeEntities[arcadeFindEntityByType(0x17)].state = 8;
    }
}

u8 gArcadeRankLabels[5][3] = { "1ST", "2ND", "3RD", "4TH", "5TH" };

void arcadeDrawNameRegistration(Gfx **glistp) {
    s32 i;
    Gfx *g;
    u8 buf[0x50];

    g = *glistp;
    if (gArcadeScreenMode == 3) {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x78, 0x3B);
        _sprintf(buf, "NAME %.3s", gArcadeEntryInitials);
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0xA0, 0x41);
        _sprintf(buf, "---");
        arcadeDrawString(&g, buf);
        if (gArcadeScreenTimer < 0x708) {
            arcadeSetTextPosition(0x60, 0x7B);
            _sprintf(buf, "REGI TIME <%02d>", 0x1E - gArcadeScreenTimer / 0x3C);
        } else {
            arcadeSetTextPosition(0x40, 0x7B);
            _sprintf(buf, "YOUR NAME WAS");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0xB0, 0x7B);
            _sprintf(buf, "REGISTERED.");
        }
        arcadeDrawString(&g, buf);
        arcadeSetTextColor(0xFF, 0, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x2B);
        _sprintf(buf, "NAME REGISTRATION");
        arcadeDrawString(&g, buf);
        arcadeSetTextColor(0, 0xFF, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x4B);
        _sprintf(buf, "A B C D E F G H I J");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0x5B);
        _sprintf(buf, "K L M N O P Q R S T");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0x6B);
        _sprintf(buf, "U V W X Y Z . -");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0xD4, 0x6B);
        _sprintf(buf, "ba");
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            arcadeSetTextColor(0xFF, 0xFF, 0, 0xFF);
        }
        arcadeSetTextPosition(0x38, 0x8B + i * 0x10);
        if (i == gArcadeEntities[0].param && (gArcadeScreenTimer & 0x20) && gArcadeScreenMode == 3) {
            _sprintf(buf, "%.3s", gArcadeRankLabels[i]);
        } else {
            _sprintf(buf, "%.3s  %06d  %.3s", gArcadeRankLabels[i], gArcadeHighScores[i], gArcadeHighScoreInitials[i]);
        }
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextColor(0, 0xFF, 0, 0xFF);
    arcadeSetTextPosition(0xB8, 0xDB);
    _sprintf(buf, "CREDIT 00");
    arcadeDrawString(&g, buf);
    *glistp = g;
}

void arcadeSetStageTextColor(s8 stageIndex) {
    if (stageIndex == gArcadePauseSelection) {
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else if (gArcadeStage == 2) {
        arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
    } else {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
    }
}

extern u16 gArcadeLifeIconSprite[];
extern TextureDescriptor gArcadeLifeIconTextures[];

void arcadeDrawHud(Gfx **glistp) {
    s32 i;
    Gfx *g;
    u8 buf[0x50];
    static s32 sFrameCount = 0;

    g = *glistp;
    gDPSetScissor(g++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gArcadeTexScaleT = 0x400;
    gArcadeTexWidth = 8;
    gArcadeTexImage = gArcadeLifeIconSprite;
    gArcadeTexHeight = 8;
    dlInitTextureDescriptor(&gArcadeLifeIconTextures[gGfxBufferIndex], gArcadeTexImage, 0, gArcadeTexWidth, gArcadeTexWidth, gArcadeTexHeight, 0, 2, 0, 0);
    dlAppendTextureLoad(&g, &gArcadeLifeIconTextures[gGfxBufferIndex]);
    dlSetTextureScaleAndFlip(0x400, gArcadeTexScaleT, 0, 0);
    for (i = 0; i < gArcadeLifeIconCount; i++) {
        dlAppendTextureRectangle(&g, i * 0x20 + 0x360, 0x4C);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    if ((gArcadeFrameCounter & 0x10) || gArcadeScreenMode == 0) {
        arcadeSetTextPosition(0x48, 0x13);
        _sprintf(buf, "1UP");
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextPosition(0x78, 0x13);
    _sprintf(buf, "HIGH SCORE");
    arcadeDrawString(&g, buf);
    arcadeSetTextColor(0, 0, 0xFF, 0xFF);
    arcadeSetTextPosition(0xD8, 0x1B);
    _sprintf(buf, "L=%02d", gArcadeLevel);
    arcadeDrawString(&g, buf);
    arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    arcadeSetTextPosition(0x38, 0x1B);
    _sprintf(buf, "%06d    %06d", gArcadeScore, gArcadeTopScore);
    arcadeDrawString(&g, buf);
    if (gArcadeScreenMode == 5 || gArcadeScreenMode == 4) {
        if (gArcadeGameOver != 0) {
            if (gArcadeStage == 2) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else if (gArcadeStage == 4) {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetTextPosition(0x78, 0xA3);
            _sprintf(buf, "GAME OVER");
            arcadeDrawString(&g, buf);
        }
        if (gArcadeScreenMode == 4) {
            if (gArcadePauseSelection == 0 || gArcadeStage == 4) {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else if (gArcadeStage == 2) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else {
                arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetStageTextColor(0);
            arcadeSetTextPosition(0x88, 0x8B);
            _sprintf(buf, "RETURN");
            arcadeDrawString(&g, buf);
            arcadeSetStageTextColor(1);
            arcadeSetTextPosition(0x68, 0x9B);
            _sprintf(buf, "DELETE HISCORE");
            arcadeDrawString(&g, buf);
            arcadeSetStageTextColor(2);
            arcadeSetTextPosition(0x68, 0xAB);
            _sprintf(buf, "EXIT DK ARCADE");
            arcadeDrawString(&g, buf);
        }
        if (gArcadeStage == 2) {
            if (gArcadeBonusTimer < 0xA) {
                arcadeSetTextColor(0, 0, 0xFF, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            }
        } else if (gArcadeStage == 4) {
            if (gArcadeBonusTimer < 0xA) {
                arcadeSetTextColor(0xF0, 0x30, 0, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
        } else {
            if (gArcadeBonusTimer < 0xA) {
                arcadeSetTextColor(0xFF, 0, 0, 0xFF);
            } else {
                arcadeSetTextColor(0x60, 0xE0, 0xFF, 0xFF);
            }
        }
        arcadeSetTextPosition(0xE0, 0x30);
        if (gArcadeBonusTimer > 0) {
            i = gArcadeBonusTimer; // FAKE: lives-loop counter i reused for the clamped bonus timer: the clamp lengthens the range of i, so the i*32+864 IV colours v0 first and i a3 (dedicated u8/s32 local with buf[0x4C]: 13/25)
        } else {
            i = 0;
        }
        _sprintf(buf, "%02d00", i);
        arcadeDrawString(&g, buf);
    }
    if (gArcadeScreenMode == 2) {
        u8 n;

        n = (gArcadeRound & 3) + 1;
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x48, 0xD7);
        _sprintf(buf, "HOW HIGH CAN YOU GET ?");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0xC9);
        _sprintf(buf, "@%% m");
        arcadeDrawString(&g, buf);
        if (n >= 2) {
            arcadeSetTextPosition(0x58, 0xAD);
            _sprintf(buf, "%%) m");
            arcadeDrawString(&g, buf);
        }
        if (n >= 3) {
            arcadeSetTextPosition(0x58, 0x91);
            _sprintf(buf, "&%% m");
            arcadeDrawString(&g, buf);
        }
        if (n >= 4) {
            arcadeSetTextPosition(0x50, 0x75);
            _sprintf(buf, "!)) m");
            arcadeDrawString(&g, buf);
        }
    }
    if (gArcadeScreenMode == 3) {
        arcadeDrawNameRegistration(&g);
    }
    if (gArcadeScreenMode == 0) {
        if (!(gArcadeScreenTimer & 0x200)) {
            arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            arcadeSetTextPosition(0x70, 0x33);
            _sprintf(buf, "INSERT COIN");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0x68, 0x43);
            _sprintf(buf, "PLAYER    COIN");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0x78, 0x53);
            _sprintf(buf, "1        1");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0x38, 0x7B);
            _sprintf(buf, "RANK  SCORE  NAME");
            arcadeDrawString(&g, buf);
            arcadeDrawNameRegistration(&g);
            arcadeSetTextColor(0xFF, 0, 0, 0xFF);
            arcadeSetTextPosition(0x78, 0x63);
            _sprintf(buf, "2        2");
            arcadeDrawString(&g, buf);
        } else {
            if (gArcadeScreenTimer & 0x182) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetTextPosition(0x68, 0xD7);
            _sprintf(buf, "c NINTENDO 1981");
            arcadeDrawString(&g, buf);
        }
    }
    *glistp = g;
    sFrameCount++;
}

