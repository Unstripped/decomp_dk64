#include "common.h"

void jetpacInitLedges(void);
void jetpacResetPlayers(void);
void jetpacStartStage(void);
void jetpacDrawScoreboard(s32);
void jetpacUpdateRocketFlight(void);
void jetpacInitRdp(s32);
void jetpacDrawLedges(void);
void jetpacDrawRocket(void);
void jetpacGridDraw(s32);
void eepromSetField(s32, s32, s32, s32, s32);
void func_8060DEA8(void);
extern s32 D_8002EC48;
void n_alSndpStop(s32);
extern s32 D_80770DF8[];
void n_alSndpPostEvent(s32, ...);
void jetpacUpdateLasers(void);
void jetpacUpdateActors(void);
void jetpacDrawActors(void);
void jetpacDrawBonusItem(void);
void jetpacDrawLasers(void);
extern s32 D_8076D1F8;
extern s16 D_8002BA52[];
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);
typedef struct {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 pad20[0x44 - 0x20];
    void (*unk44)(void *);
    u8 pad48[4];
} J0aItem;

typedef struct {
    s32 stage;
    s32 score;
    s32 lives;
    s32 unkC;
    s32 unk10;
    J0aItem items[4];
    s32 unk144;
    J0aItem bonus;
} JetpacPlayer;

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    s8 unkC;
    u8 padD[0x18 - 0xD];
    s32 high_score;
    JetpacPlayer players[2];
    s32 active_player;
    s32 num_players;
    s32 unk34C;
    u8 pad350[0x44C - 0x350];
    s32 unk44C;
    u8 pad450[0x78C - 0x450];
    s32 unk78C;
    s32 unk790;
    s32 unk794;
    u8 unk798;
    u8 unk799;
} JetpacGlobal;

extern JetpacGlobal jetpacGame;

void jetpacSpawnBonusItem(JetpacPlayer *);
void jetpacInitRocketParts(JetpacPlayer *);
void jetpacSpawnFuelPod(JetpacPlayer *);
void jetpacSetState(s32);
void jetpacPlaceRocketAboveScreen(void);
void jetpacInitPlayer(void);
void jetpacInitActors(void);
void jetpacSetRocketSpriteFrames(JetpacPlayer *);
void jetpacPlaceRocketOnPad(void);
extern s32 D_8002F064;

void controllerStartRead(void);
void controllerUpdate(void);
void schedSubmitGfxTask(Gfx *, s32, s32, s32, s32, s32);
Gfx *screenFadeUpdate(Gfx *, s32);
void func_805FE71C(Gfx *, u8, s32 *, s32);
void func_805FE7B4(Gfx *, u8 *, s32 *, s32);
Gfx *func_805FE4D4(Gfx *);
Gfx *heapAlloc(s32);
void heapFreeDeferred(void *);
void jetpacUpdateStateAndInput();
void jetpacBuildDisplayList(u8 *, Gfx **);

extern u8 gGfxBufferIndex;
extern u8 D_807444EC;
extern Gfx *gGfxTaskBuffers[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern s32 gFrameCounter;
extern u8 *gGfxCurrentFrameBuffer;
extern u8 D_80767CE8;
extern u8 D_8076A0B1;
extern f32 gScreenFadeProgress;
extern void *D_8076A080;
extern Gfx D_1000090;
extern Gfx D_1000040;
extern Gfx D_2000080;

void jetpacRunFrame(void) {
    Gfx *glist;
    u8 *gfxEnd;

    controllerStartRead();
    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], D_8076A088, 3, 1, 0x4D2, 1);
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    gGfxCurrentFrameBuffer = (u8 *)&D_80767CE8 + gGfxBufferIndex * 0x11B0;
    controllerUpdate();
    if ((D_8076A0B1 & 1) && gScreenFadeProgress == 31.0f) {
        glist = gGfxTaskBuffers[gGfxBufferIndex];
    } else {
        jetpacBuildDisplayList(gGfxCurrentFrameBuffer, &glist);
    }
    glist = screenFadeUpdate(glist, 0);
    if (D_807444EC != 4) {
        gfxEnd = gGfxCurrentFrameBuffer + 0xDB0;
        func_805FE71C(glist, gGfxBufferIndex, &D_8076A088, 0);
        func_805FE7B4((Gfx *)gfxEnd, gGfxCurrentFrameBuffer, &D_8076A08C, 1);
    } else {
        func_805FE71C(glist, gGfxBufferIndex, &D_8076A088, 1);
    }
}

#define J0a_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
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
    glist = func_805FE4D4(glist);
    J0a_WRITE_GFX(glist++, 0xE3001801, 0);
    J0a_WRITE_GFX(glist++, 0xE3001A01, 0);
    gDPSetFillColor(glist++, 0x00010001);
    gDPFillRectangle(glist++, 0, 0, 319, 239);
    J0a_WRITE_GFX(glist++, 0xDA380007, &D_2000080);
    cmdBuffer = heapAlloc(0x5DC0);
    heapFreeDeferred(cmdBuffer);
    cmdGlist = cmdBuffer;
    jetpacUpdateStateAndInput(&cmdGlist);
    gSPEndDisplayList(cmdGlist++);
    gSPDisplayList(glist++, cmdBuffer);
    *outGlist = glist;
}



extern JetpacPlayer D_8002EC4C[];

void jetpacResetPlayers(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        jetpacGame.players[i].stage = -1;
        jetpacGame.players[i].score = 0;
        if (i < jetpacGame.num_players) {
            if (jetpacGame.unk798 != 0) {
                D_8002EC4C[i].lives = 3;
            } else {
                D_8002EC4C[i].lives = 5;
            }
        } else {
            D_8002EC4C[i].lives = -1;
        }
    }
    jetpacGame.active_player = 0;
}

extern s32 D_8002BA6C;
s32 jetpacIsSpawnDelay(void);
void jetpacSetupTextRdp(s32);
void jetpacSetTextColor(s32, s32, s32, s32);
void jetpacDrawString(s32, char *, s32, s32, s32);
s32 _sprintf(char *, char *, ...);

extern s32 D_8002EF74;
extern s32 D_8002EC50;
extern s32 D_8002EDE4;

void jetpacDrawScoreboard(s32 glist) {
    char buf[0x50];
    s32 mask;
    s32 i;
    JetpacPlayer *p;

    mask = jetpacIsSpawnDelay() & D_8002BA6C;
    jetpacSetupTextRdp(glist);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "1UP", 0x38, 0x18, mask != 0 && D_8002EF74 == 0);
    p = D_8002EC4C;
    for (i = 0; i < 2; i++) {
        if (p->lives > 0) {
            _sprintf(buf, "%d!", p->lives);
            jetpacDrawString(glist, buf, i * 0x70 + 0x60, 0x18, 0);
        }
        p++;
    }
    jetpacDrawString(glist, "2UP", 0xF8, 0x18, mask != 0 && D_8002EF74 == 1);
    jetpacSetTextColor(0, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "HI", 0x98, 0x18, 0);
    jetpacSetTextColor(0xFF, 0xFF, 0, 0xFF);
    _sprintf(buf, "%06d", D_8002EC50);
    jetpacDrawString(glist, buf, 0x28, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EC48);
    jetpacDrawString(glist, buf, 0x88, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EDE4);
    jetpacDrawString(glist, buf, 0xE8, 0x20, 0);
}

void jetpacStartGame(void) {
    jetpacInitLedges();
    jetpacResetPlayers();
    jetpacStartStage();
}


void jetpacStateSelection(s32 glist) {
    s32 flags;
    char buf[0x24];

    jetpacDrawScoreboard(glist);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "JETPAC GAME SELECTION", 0x50, 0x38, 0);
    jetpacDrawString(glist, "1@@@1@PLAYER@GAME", 0x50, 0x50, D_8002BA6C != 0 && jetpacGame.num_players == 1);
    jetpacDrawString(glist, "2@@@2@PLAYER@GAME", 0x50, 0x60, D_8002BA6C != 0 && jetpacGame.num_players == 2);
    jetpacDrawString(glist, "3@@@KEYBOARD", 0x50, 0x70, D_8002BA6C != 0 && jetpacGame.unk34C == 0);
    jetpacDrawString(glist, "4@@@KEMPSTON@JOYSTICK", 0x50, 0x80, D_8002BA6C != 0 && jetpacGame.unk34C != 0);
    jetpacDrawString(glist, "5   START GAME", 0x50, 0xB8, 0);
    _sprintf(buf, "%c1983 A.C.G. ALL RIGHTS RESERVED", 0x7F);
    jetpacDrawString(glist, buf, 0x20, 0xD8, 0);
    if (jetpacGame.unk798 != 0) {
        if (!(jetpacGame.unk8 & 0x1000) && jetpacGame.unk799 < 0x78) {
            jetpacGame.unk799++;
            return;
        }
        jetpacGame.unk799 = 0;
        jetpacStartGame();
        return;
    }
    flags = jetpacGame.unk8;
    if (flags & 0x4000) {
        jetpacGame.num_players ^= 3;
    }
    if (flags & 0x8000) {
        jetpacGame.unk34C ^= 1;
    }
    if (flags & 0x1000) {
        jetpacStartGame();
    }
}

void jetpacStateLanding(s32 glist) {
    jetpacDrawScoreboard(glist);
    jetpacUpdateRocketFlight();
    jetpacInitRdp(glist);
    jetpacDrawLedges();
    jetpacDrawRocket();
    jetpacGridDraw(glist);
}

void jetpacPlayerStateUpdate(void);
void jetpacItemsUpdate(void);
void jetpacDrawPlayer(void);

void jetpacStateGameplay(s32 glist) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.active_player];

    if (player->score >= 1000000) {
        player->score -= 1000000;
    }
    jetpacDrawScoreboard(glist);
    if (player->items[player->unk10].unk44) { // FAKE: empty guard steers regalloc
    }
    jetpacPlayerStateUpdate();
    jetpacUpdateLasers();
    player->bonus.unk44(&player->bonus);
    {
        J0aItem *it = &player->items[player->unk10];
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
        jetpacGame.unk44C++;
    }
    if (jetpacGame.unk8 & 0x1000) {
        jetpacGame.unk78C = 3;
        jetpacGame.unkC = 1;
    }
}

void jetpacSaveHighScore(void) {
    eepromSetField(0x11, 0, 0, 0, D_8002EC48);
    func_8060DEA8();
}

s32 flagGet(s32, s32);
void mapRequestTransition(s32, s32);
s32 eepromGetField(s32, s32, s32, s32);
void eepromInitConfigs(s32);
void jetpacNextPlayerOrGameOver(JetpacPlayer *);


void jetpacStatePause(s32 glist) {
    jetpacDrawScoreboard(glist);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, "RETURN", 0x88, 0x70, D_8002BA6C != 0 && jetpacGame.unkC == 1);
    jetpacDrawString(glist, "DELETE@HISCORE", 0x68, 0x80, D_8002BA6C != 0 && jetpacGame.unkC == 2);
    jetpacDrawString(glist, "EXIT@@JETPAC", 0x70, 0x90, D_8002BA6C != 0 && jetpacGame.unkC == 0);
    if (jetpacGame.unk8 & 0xE000) {
        switch (jetpacGame.unkC) {
        default:
        case 0:
            mapRequestTransition(jetpacGame.unk798 != 0 ? 5 : 0x50, 0);
            break;
        case 1:
            jetpacGame.unk78C = 2;
            break;
        case 2:
            if (jetpacGame.high_score != 0) {
                eepromInitConfigs(1);
                jetpacGame.high_score = eepromGetField(0x11, 0, 0, 0);
                jetpacSaveHighScore();
            }
            break;
        }
    }
    if (jetpacGame.unk8 & 0x400) {
        jetpacGame.unkC++;
    }
    if (jetpacGame.unk8 & 0x800) {
        jetpacGame.unkC--;
    }
    if (jetpacGame.unkC >= 3) {
        jetpacGame.unkC = 0;
    }
    if (jetpacGame.unkC < 0) {
        jetpacGame.unkC = 2;
    }
}

void jetpacStateTakeoff(s32 glist) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.active_player];

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

void jetpacStateGameOver(s32 glist) {
    s32 textCol;
    char textBuf[0x20];

    textCol = 7;
    jetpacDrawScoreboard(glist);
    if (jetpacGame.unk798 != 0 && flagGet(0x62, 2) != 0) {
        _sprintf(textBuf, "RAREWARE COIN COLLECTED");
        textCol = 5;
    } else {
        _sprintf(textBuf, "GAME OVER PLAYER %d", jetpacGame.active_player + 1);
    }
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(glist, textBuf, textCol * 8 + 0x20, 0x88, 0);
    if ((u32)jetpacGame.unk790 >= 0x79U) {
        if (jetpacGame.unk798 != 0) {
            if (jetpacGame.unk799 == 0) {
                jetpacGame.unk799 = 1;
                mapRequestTransition(5, 0);
            }
        } else {
            jetpacNextPlayerOrGameOver(&jetpacGame.players[jetpacGame.active_player]);
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
    n_alSndpPlay(D_8076D1F8, *(s16 *)((u8 *)D_8002BA52 + soundId * 4), 0x7FFF, 0x3F, 1.0f, 0, &D_80770DF8[soundId]);
}

void jetpacSetSoundPitch(s32 soundId, s32 pitch) {
    if (D_80770DF8[soundId] != 0) {
        s32 *p = &pitch;
        n_alSndpPostEvent(D_80770DF8[soundId], 0x10, *p);
    }
}

void jetpacStopSound(s32 soundId) {
    if (D_80770DF8[soundId] != 0) {
        n_alSndpStop(D_80770DF8[soundId]);
    }
}

void jetpacSetState(s32 state) {
    s32 pad;
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.active_player];

    jetpacGame.unk794 = 0;
    switch (state) {
    case 0:
    case 3:
        break;
    case 1:
        jetpacPlaceRocketAboveScreen();
        break;
    case 2:
        if (jetpacGame.unk78C == 1) {
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
        jetpacGame.unk790 = 0;
        break;
    }
    jetpacGame.unk78C = state;
}

void jetpacStartStage(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.active_player];

    if (player->stage < 0) {
        player->lives--;
    }
    player->stage++;
    jetpacSpawnBonusItem(player);
    if ((player->stage & 3) == 0) {
        jetpacInitRocketParts(player);
        player->items[3].unk1C = 0;
        player->unk10 = 1;
        jetpacSetState(2);
    } else {
        jetpacSpawnFuelPod(player);
        jetpacSetState(1);
    }
}

typedef struct {
    u16 unk0;
    s8 unk2;
    s8 unk3;
} J0bPad;

extern u8 D_8002BA70;
extern J0bPad *D_807ECDE8;
void jetpacStateSelection(s32);
void jetpacStateGameplay(s32);

void jetpacUpdateStateAndInput(s32 glist) {
    u8 flag;
    s32 zero;

    zero = 0;
    if (D_8002BA70 != 0) {
        jetpacGame.unk78C = 0;
        jetpacGame.unk790 = 0;
        jetpacGame.unk794 = 3;
        jetpacGame.num_players = 1;
        jetpacGame.unk34C = 0;
        D_8002BA70 = zero;
        jetpacGame.high_score = eepromGetField(0x11, zero, zero, zero);
        flag = flagGet(0x61, 2);
        jetpacGame.unk798 = flag;
        if (flag != zero) {
            jetpacGame.unk799 = 0;
        }
    }
    D_8002BA6C = jetpacGame.unk790;
    D_8002BA6C %= 60;
    D_8002BA6C /= 30;
    jetpacGame.unk4 = jetpacGame.unk0;
    jetpacGame.unk0 = D_807ECDE8->unk0;
    if (D_807ECDE8->unk2 >= 0x1F) {
        jetpacGame.unk0 |= 0x100;
    }
    if (D_807ECDE8->unk2 < -0x1E) {
        jetpacGame.unk0 |= 0x200;
    }
    if (D_807ECDE8->unk3 >= 0x1F) {
        jetpacGame.unk0 |= 0x800;
    }
    if (D_807ECDE8->unk3 < -0x1E) {
        jetpacGame.unk0 |= 0x400;
    }
    jetpacGame.unk8 = (jetpacGame.unk0 ^ jetpacGame.unk4) & jetpacGame.unk0;
    if ((u32)jetpacGame.unk794 < 3) {
        jetpacGame.unk794++;
        return;
    }
    switch (jetpacGame.unk78C) {
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
    jetpacGame.unk790 = jetpacGame.unk790 + 1;
}

void jetpacNextPlayerOrGameOver(JetpacPlayer *player) {
    s32 other_idx = jetpacGame.active_player ^ 1;
    JetpacPlayer *other = &jetpacGame.players[other_idx];

    if (player->lives < 0 && jetpacGame.unk78C != 5) {
        if (jetpacGame.high_score < player->score) {
            jetpacGame.high_score = player->score;
            jetpacSaveHighScore();
        }
        jetpacSetState(5);
        return;
    }

    if (other->lives >= 0) {
        jetpacGame.active_player = other_idx;
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

