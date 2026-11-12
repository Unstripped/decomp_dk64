#include "common.h"
#include "jetpac.h"
#define PROTO_SKIP_flagGet // FAKE: callee prototype steer
#include "proto/boot/3D20.h"
#include "proto/global/103AB0.h"
#include "proto/global/104F0.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/14CF0.h"
#include "proto/global/15050.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/F600.h"
#include "proto/jetpac/0.h"
#include "proto/jetpac/1460.h"
#include "proto/jetpac/1A60.h"
#include "proto/jetpac/3480.h"
#include "proto/jetpac/4FC0.h"

extern struct GfSndState *D_80770DF8[];
extern ALBank *D_8076D1F8;
typedef struct {
    s16 sfx;
    s16 unk2;
} JetpacSoundEntry;
extern JetpacSoundEntry D_8002BA52[];


extern s32 D_8002F064;


extern u8 gGfxBufferIndex;
extern u8 gGameMode;
extern Gfx *gGfxTaskBuffers[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 *gGfxCurrentFrameBuffer;
extern u8 D_80767CE8;
extern u8 gScreenRenderFlags;
extern f32 gScreenFadeProgress;
extern void *D_8076A080;
extern Gfx D_1000090;
extern Gfx D_1000040;
extern Gfx D_2000080;

void jetpacRunFrame(void) {
    Gfx *glist;
    Gfx *gfxEnd;

    controllerStartRead();
    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], D_8076A088, 3, 1, 0x4D2, 1);
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    gGfxCurrentFrameBuffer = (u8 *)&D_80767CE8 + gGfxBufferIndex * 0x11B0;
    controllerUpdate();
    if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
        glist = gGfxTaskBuffers[gGfxBufferIndex];
    } else {
        jetpacBuildDisplayList(gGfxCurrentFrameBuffer, &glist);
    }
    glist = screenFadeUpdate(glist, 0);
    if (gGameMode != 4) {
        gfxEnd = (Gfx *)(gGfxCurrentFrameBuffer + 0xDB0);
        gfxEndDisplayList(glist, gGfxBufferIndex, &D_8076A088, 0);
        gfxEndSubDisplayList(gfxEnd, gGfxCurrentFrameBuffer, &D_8076A08C, 1);
    } else {
        gfxEndDisplayList(glist, gGfxBufferIndex, &D_8076A088, 1);
    }
}

void jetpacBuildDisplayList(u8 *basePtr, Gfx **outGlist) {
    Gfx *cmdGlist;
    Gfx *cmdBuffer;
    Gfx *glist;

    glist = gGfxTaskBuffers[gGfxBufferIndex];
    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(basePtr));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist++, &D_1000040);
    guOrtho((Mtx *)(basePtr + 0x80), 0.0f, 320.0f, 0.0f, 240.0f, 1.0f, 10.0f, 1.0f);
    gDPPipeSync(glist++);
    glist = gfxSetFrameBufferColorImage(glist);
    gDPSetColorDither(glist++, G_CD_MAGICSQ);
    gDPSetAlphaDither(glist++, G_AD_PATTERN);
    gDPSetFillColor(glist++, 0x00010001);
    gDPFillRectangle(glist++, 0, 0, 319, 239);
    gSPMatrix(glist++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    cmdBuffer = heapAlloc(0x5DC0);
    heapFreeDeferred(cmdBuffer);
    cmdGlist = cmdBuffer;
    jetpacUpdateStateAndInput(&cmdGlist);
    gSPEndDisplayList(cmdGlist++);
    gSPDisplayList(glist++, cmdBuffer);
    *outGlist = glist;
}


void jetpacResetPlayers(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        JetpacPlayer *p = &jetpacGame.players[i];
        p->stage = -1;
        p->score = 0;
        if (i < jetpacGame.numPlayers) {
            if (jetpacGame.unk798 != 0) {
                p->lives = 3;
            } else {
                p->lives = 5;
            }
        } else {
            p->lives = -1;
        }
    }
    jetpacGame.activePlayer = 0;
}

extern s32 D_8002BA6C;


void jetpacDrawScoreboard(Gfx **glist) {
    char buf[0x50];
    s32 mask;
    s32 i;
    JetpacPlayer *p;

    mask = jetpacIsSpawnDelay() & D_8002BA6C;
    jetpacSetupTextRdp(glist);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "1UP", 0x38, 0x18, mask != 0 && jetpacGame.activePlayer == 0);
    p = jetpacGame.players;
    for (i = 0; i < 2; i++) {
        if (p->lives > 0) {
            _sprintf(buf, "%d!", p->lives);
            jetpacDrawString(glist, buf, i * 0x70 + 0x60, 0x18, 0);
        }
        p++;
    }
    jetpacDrawString(glist, "2UP", 0xF8, 0x18, mask != 0 && jetpacGame.activePlayer == 1);
    jetpacSetTextColor(0, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "HI", 0x98, 0x18, 0);
    jetpacSetTextColor(0xFF, 0xFF, 0, 0xFF);
    _sprintf(buf, "%06d", jetpacGame.players[0].score);
    jetpacDrawString(glist, buf, 0x28, 0x20, 0);
    _sprintf(buf, "%06d", jetpacGame.highScore);
    jetpacDrawString(glist, buf, 0x88, 0x20, 0);
    _sprintf(buf, "%06d", jetpacGame.players[1].score);
    jetpacDrawString(glist, buf, 0xE8, 0x20, 0);
}

void jetpacStartGame(void) {
    jetpacInitLedges();
    jetpacResetPlayers();
    jetpacStartStage();
}


void jetpacStateSelection(Gfx **glist) {
    s32 flags;
    char buf[0x24];

    jetpacDrawScoreboard(glist);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "JETPAC GAME SELECTION", 0x50, 0x38, 0);
    jetpacDrawString(glist, "1@@@1@PLAYER@GAME", 0x50, 0x50, D_8002BA6C != 0 && jetpacGame.numPlayers == 1);
    jetpacDrawString(glist, "2@@@2@PLAYER@GAME", 0x50, 0x60, D_8002BA6C != 0 && jetpacGame.numPlayers == 2);
    jetpacDrawString(glist, "3@@@KEYBOARD", 0x50, 0x70, D_8002BA6C != 0 && jetpacGame.controlType == 0);
    jetpacDrawString(glist, "4@@@KEMPSTON@JOYSTICK", 0x50, 0x80, D_8002BA6C != 0 && jetpacGame.controlType != 0);
    jetpacDrawString(glist, "5   START GAME", 0x50, 0xB8, 0);
    _sprintf(buf, "%c1983 A.C.G. ALL RIGHTS RESERVED", 0x7F);
    jetpacDrawString(glist, buf, 0x20, 0xD8, 0);
    if (jetpacGame.unk798 != 0) {
        if (!(jetpacGame.pressedButtons & 0x1000) && jetpacGame.unk799 < 0x78) {
            jetpacGame.unk799++;
            return;
        }
        jetpacGame.unk799 = 0;
        jetpacStartGame();
        return;
    }
    flags = jetpacGame.pressedButtons;
    if (flags & 0x4000) {
        jetpacGame.numPlayers ^= 3;
    }
    if (flags & 0x8000) {
        jetpacGame.controlType ^= 1;
    }
    if (flags & 0x1000) {
        jetpacStartGame();
    }
}

void jetpacStateLanding(Gfx **glist) {
    jetpacDrawScoreboard(glist);
    jetpacUpdateRocketFlight();
    jetpacInitRdp(glist);
    jetpacDrawLedges();
    jetpacDrawRocket();
    jetpacGridDraw(glist);
}


void jetpacStateGameplay(Gfx **glist) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];

    if (player->score >= 1000000) {
        player->score -= 1000000;
    }
    jetpacDrawScoreboard(glist);
    if (player->items[player->currentItem].unk44) { // FAKE: empty guard steers regalloc
    }
    jetpacPlayerStateUpdate();
    jetpacUpdateLasers();
    player->bonus.unk44(&player->bonus);
    {
        JetpacItem *it = &player->items[player->currentItem];
        it->unk44(it);
    }
    jetpacUpdateActors();
    jetpacInitRdp(glist);
    jetpacDrawLedges();
    jetpacDrawPlayer();
    jetpacDrawActors();
    jetpacItemsUpdate();
    jetpacDrawBonusItem();
    jetpacDrawLasers();
    jetpacGridDraw(glist);
    if (jetpacIsSpawnDelay() != 0) {
        jetpacGame.player.timer++;
    }
    if (jetpacGame.pressedButtons & 0x1000) {
        jetpacGame.gameState = 3;
        jetpacGame.menuSelection = 1;
    }
}

void jetpacSaveHighScore(void) {
    eepromSetField(0x11, 0, 0, 0, jetpacGame.highScore);
    func_8060DEA8();
}

s32 flagGet(s32, s32); // FAKE: callee prototype steer


void jetpacStatePause(Gfx **glist) {
    jetpacDrawScoreboard(glist);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "RETURN", 0x88, 0x70, D_8002BA6C != 0 && jetpacGame.menuSelection == 1);
    jetpacDrawString(glist, "DELETE@HISCORE", 0x68, 0x80, D_8002BA6C != 0 && jetpacGame.menuSelection == 2);
    jetpacDrawString(glist, "EXIT@@JETPAC", 0x70, 0x90, D_8002BA6C != 0 && jetpacGame.menuSelection == 0);
    if (jetpacGame.pressedButtons & 0xE000) {
        switch (jetpacGame.menuSelection) {
        default:
        case 0:
            mapRequestTransition(jetpacGame.unk798 != 0 ? 5 : 0x50, 0);
            break;
        case 1:
            jetpacGame.gameState = 2;
            break;
        case 2:
            if (jetpacGame.highScore != 0) {
                eepromInitConfigs(1);
                jetpacGame.highScore = eepromGetField(0x11, 0, 0, 0);
                jetpacSaveHighScore();
            }
            break;
        }
    }
    if (jetpacGame.pressedButtons & 0x400) {
        jetpacGame.menuSelection++;
    }
    if (jetpacGame.pressedButtons & 0x800) {
        jetpacGame.menuSelection--;
    }
    if (jetpacGame.menuSelection >= 3) {
        jetpacGame.menuSelection = 0;
    }
    if (jetpacGame.menuSelection < 0) {
        jetpacGame.menuSelection = 2;
    }
}

void jetpacStateTakeoff(Gfx **glist) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];

    jetpacDrawScoreboard(glist);
    jetpacUpdateLasers();
    player->bonus.unk44(&player->bonus);
    jetpacUpdateRocketFlight();
    jetpacUpdateActors();
    jetpacInitRdp(glist);
    jetpacDrawLedges();
    jetpacDrawActors();
    jetpacDrawRocket();
    jetpacDrawBonusItem();
    jetpacDrawLasers();
    jetpacGridDraw(glist);
}

void jetpacStateGameOver(Gfx **glist) {
    s32 textCol;
    char textBuf[0x20];

    textCol = 7;
    jetpacDrawScoreboard(glist);
    if (jetpacGame.unk798 != 0 && flagGet(0x62, 2) != 0) {
        _sprintf(textBuf, "RAREWARE COIN COLLECTED");
        textCol = 5;
    } else {
        _sprintf(textBuf, "GAME OVER PLAYER %d", jetpacGame.activePlayer + 1);
    }
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, textBuf, textCol * 8 + 0x20, 0x88, 0);
    if (jetpacGame.stateTimer >= 0x79) {
        if (jetpacGame.unk798 != 0) {
            if (jetpacGame.unk799 == 0) {
                jetpacGame.unk799 = 1;
                mapRequestTransition(5, 0);
            }
        } else {
            jetpacNextPlayerOrGameOver(&jetpacGame.players[jetpacGame.activePlayer]);
        }
    }
}

void jetpacPlaySound(s32 soundId) {
    s32 i;

    for (i = soundId; i < 7; i++) {
        if (D_80770DF8[i] != 0) {
            n_alSndpStop(D_80770DF8[i]);
        }
    }
    n_alSndpPlay(D_8076D1F8, D_8002BA52[soundId].sfx, 0x7FFF, 0x3F, 1.0f, 0, &D_80770DF8[soundId]);
}

void jetpacSetSoundPitch(s32 soundId, f32 pitch) {
    if (D_80770DF8[soundId] != 0) {
        n_alSndpPostEvent(D_80770DF8[soundId], 0x10, *(s32 *)&pitch);
    }
}

void jetpacStopSound(s32 soundId) {
    if (D_80770DF8[soundId] != 0) {
        n_alSndpStop(D_80770DF8[soundId]);
    }
}

void jetpacSetState(s32 state) {
    s32 pad;
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];

    jetpacGame.unk794 = 0;
    switch (state) {
    case 0:
    case 3:
        break;
    case 1:
        jetpacPlaceRocketAboveScreen();
        break;
    case 2:
        if (jetpacGame.gameState == 1) {
            jetpacGame.unk794 = 3;
            player->lives--;
        }
        jetpacInitPlayer();
        jetpacInitActors();
        jetpacSetRocketSpriteFrames(player);
        break;
    case 4:
        D_8002F064 = 1;
        jetpacPlaceRocketOnPad();
        jetpacGame.unk794 = 3;
        player->lives++;
        break;
    case 5:
        jetpacGame.stateTimer = 0;
        break;
    }
    jetpacGame.gameState = state;
}

void jetpacStartStage(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];

    if (player->stage < 0) {
        player->lives--;
    }
    player->stage++;
    jetpacSpawnBonusItem(player);
    if ((player->stage & 3) == 0) {
        jetpacInitRocketParts(player);
        player->items[3].unk1C = 0;
        player->currentItem = 1;
        jetpacSetState(2);
    } else {
        jetpacSpawnFuelPod(player);
        jetpacSetState(1);
    }
}

extern u8 D_8002BA70;
extern OSContPad *D_807ECDE8;

void jetpacUpdateStateAndInput(Gfx **glist) {
    u8 flag;
    s32 zero; // FAKE: value-named zero local steers regalloc (pre-existing, now tagged)

    zero = 0;
    if (D_8002BA70 != 0) {
        jetpacGame.gameState = 0;
        jetpacGame.stateTimer = 0;
        jetpacGame.unk794 = 3;
        jetpacGame.numPlayers = 1;
        jetpacGame.controlType = 0;
        D_8002BA70 = zero;
        jetpacGame.highScore = eepromGetField(0x11, zero, zero, zero);
        flag = flagGet(0x61, 2);
        jetpacGame.unk798 = flag;
        if (flag != zero) {
            jetpacGame.unk799 = 0;
        }
    }
    D_8002BA6C = jetpacGame.stateTimer;
    D_8002BA6C %= 60;
    D_8002BA6C /= 30;
    jetpacGame.prevButtons = jetpacGame.buttons;
    jetpacGame.buttons = D_807ECDE8->button;
    if (D_807ECDE8->stick_x >= 0x1F) {
        jetpacGame.buttons |= 0x100;
    }
    if (D_807ECDE8->stick_x < -0x1E) {
        jetpacGame.buttons |= 0x200;
    }
    if (D_807ECDE8->stick_y >= 0x1F) {
        jetpacGame.buttons |= 0x800;
    }
    if (D_807ECDE8->stick_y < -0x1E) {
        jetpacGame.buttons |= 0x400;
    }
    jetpacGame.pressedButtons = (jetpacGame.buttons ^ jetpacGame.prevButtons) & jetpacGame.buttons;
    if (jetpacGame.unk794 < 3) {
        jetpacGame.unk794++;
        return;
    }
    switch (jetpacGame.gameState) {
    case 0:
        jetpacStateSelection(glist);
        break;
    case 1:
        jetpacStateLanding(glist);
        break;
    case 2:
        jetpacStateGameplay(glist);
        break;
    case 3:
        jetpacStatePause(glist);
        break;
    case 4:
        jetpacStateTakeoff(glist);
        break;
    case 5:
        jetpacStateGameOver(glist);
        break;
    }
    jetpacGame.stateTimer++;
}

void jetpacNextPlayerOrGameOver(JetpacPlayer *player) {
    s32 other_idx = jetpacGame.activePlayer ^ 1;
    JetpacPlayer *other = &jetpacGame.players[other_idx];

    if (player->lives < 0 && jetpacGame.gameState != 5) {
        if (jetpacGame.highScore < player->score) {
            jetpacGame.highScore = player->score;
            jetpacSaveHighScore();
        }
        jetpacSetState(5);
        return;
    }

    if (other->lives >= 0) {
        jetpacGame.activePlayer = other_idx;
        if (other->stage < 0) {
            jetpacStartStage();
            return;
        }
        jetpacSetState(2);
        return;
    }
    if (player->lives >= 0) {
        jetpacSetState(2);
        return;
    }
    jetpacSetState(0);
}

