#include "common.h"

void jetpacInitLedges(void);
void jetpacResetPlayers(void);
void jetpacStartStage(void);
void func_80024408(s32);
void jetpacUpdateRocketFlight(void);
void jetpacInitRdp(s32);
void func_80028E88(void);
void func_800289EC(void);
void jetpacGridDraw(s32);
void func_8060C648(s32, s32, s32, s32, s32);
void func_8060DEA8(void);
extern s32 D_8002EC48;
void n_alSndpStop(s32);
extern s32 D_80770DF8[];
void n_alSndpPostEvent(s32, ...);
void jetpacUpdateLasers(void);
void jetpacUpdateActors(void);
void jetpacDrawActors(void);
void func_800285DC(void);
void jetpacDrawLasers(void);
extern s32 D_8076D1F8;
extern s16 D_8002BA52[];
extern s32 D_80770E14[];
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);
typedef struct {
    s32 stage;
    s32 score;
    s32 lives;
    s32 unkC;
    s32 unk10;
    u8 pad14[0x114 - 0x14];
    s32 unk114;
    u8 pad118[0x148 - 0x118];
    u8 unk148[0x18C - 0x148];
    void (*unk18C)(void *);
    u8 pad190[0x194 - 0x190];
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
    u8 pad350[0x78C - 0x350];
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
void func_80610044(Gfx *, s32, s32, s32, s32, s32);
Gfx *func_80704484(Gfx *, s32);
void func_805FE71C(Gfx *, u8, s32 *, s32);
void func_805FE7B4(Gfx *, u8 *, s32 *, s32);
Gfx *func_805FE4D4(Gfx *);
Gfx *func_80610FE8(s32);
void heapFreeDeferred(void *);
void func_80025168();
void jetpacBuildDisplayList(u8 *, Gfx **);

extern u8 D_807444FC;
extern u8 D_807444EC;
extern Gfx *D_8076A050[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern s32 D_8076A064;
extern u8 *D_8076A048;
extern u8 D_80767CE8;
extern u8 D_8076A0B1;
extern f32 D_807FD888;
extern void *D_8076A080;
extern Gfx D_1000090;
extern Gfx D_1000040;
extern Gfx D_2000080;

void jetpacRunFrame(void) {
    Gfx *sp2C;
    u8 *sp28;

    controllerStartRead();
    func_80610044(D_8076A050[D_807444FC], D_8076A088, 3, 1, 0x4D2, 1);
    D_807444FC ^= 1;
    D_8076A064++;
    D_8076A048 = (u8 *)&D_80767CE8 + D_807444FC * 0x11B0;
    controllerUpdate();
    if ((D_8076A0B1 & 1) && D_807FD888 == 31.0f) {
        sp2C = D_8076A050[D_807444FC];
    } else {
        jetpacBuildDisplayList(D_8076A048, &sp2C);
    }
    sp2C = func_80704484(sp2C, 0);
    if (D_807444EC != 4) {
        sp28 = D_8076A048 + 0xDB0;
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 0);
        func_805FE7B4((Gfx *)sp28, D_8076A048, &D_8076A08C, 1);
    } else {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 1);
    }
}

#define J0a_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
void jetpacBuildDisplayList(u8 *arg0, Gfx **arg1) {
    Gfx *sp6C;
    Gfx *sp68;
    Gfx *glist;

    glist = D_8076A050[D_807444FC];
    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(arg0));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist++, &D_1000040);
    guOrtho((Mtx *)(arg0 + 0x80), 0.0f, 320.0f, 0.0f, 240.0f, 1.0f, 10.0f, 1.0f);
    gDPPipeSync(glist++);
    glist = func_805FE4D4(glist);
    J0a_WRITE_GFX(glist++, 0xE3001801, 0);
    J0a_WRITE_GFX(glist++, 0xE3001A01, 0);
    gDPSetFillColor(glist++, 0x00010001);
    gDPFillRectangle(glist++, 0, 0, 319, 239);
    J0a_WRITE_GFX(glist++, 0xDA380007, &D_2000080);
    sp68 = func_80610FE8(0x5DC0);
    heapFreeDeferred(sp68);
    sp6C = sp68;
    func_80025168(&sp6C);
    gSPEndDisplayList(sp6C++);
    gSPDisplayList(glist++, sp68);
    *arg1 = glist;
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

#ifdef NON_MATCHING
extern s32 D_8002EF74;
extern s32 D_8002EC50;
extern s32 D_8002EDE4;

void func_80024408(s32 arg0) {
    char buf[0x50];
    s32 mask;
    s32 i;
    s32 pad;

    mask = jetpacIsSpawnDelay() & D_8002BA6C;
    jetpacSetupTextRdp(arg0);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, "1UP", 0x38, 0x18, mask != 0 && D_8002EF74 == 0);
    for (i = 0; i < 2; i++) {
        if (D_8002EC4C[i].lives > 0) {
            _sprintf(buf, "%d!", D_8002EC4C[i].lives);
            jetpacDrawString(arg0, buf, i * 0x70 + 0x60, 0x18, 0);
        }
    }
    jetpacDrawString(arg0, "2UP", 0xF8, 0x18, mask != 0 && D_8002EF74 == 1);
    jetpacSetTextColor(0, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, "HI", 0x98, 0x18, 0);
    jetpacSetTextColor(0xFF, 0xFF, 0, 0xFF);
    _sprintf(buf, "%06d", D_8002EC50);
    jetpacDrawString(arg0, buf, 0x28, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EC48);
    jetpacDrawString(arg0, buf, 0x88, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EDE4);
    jetpacDrawString(arg0, buf, 0xE8, 0x20, 0);
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024408.s")
#endif

void jetpacStartGame(void) {
    jetpacInitLedges();
    jetpacResetPlayers();
    jetpacStartStage();
}

typedef struct {
    u8 pad0[8];
    s32 unk8;
    u8 unkC;
    u8 padD[0x348 - 0xD];
    s32 unk348;
    s32 unk34C;
    u8 pad350[0x44C - 0x350];
    s32 unk44C;
    u8 pad450[0x78C - 0x450];
    s32 unk78C;
    u8 pad790[0x798 - 0x790];
    u8 unk798;
    u8 unk799;
} J0aGlobalView;
#define J0aG ((J0aGlobalView *)&jetpacGame)

void jetpacStateSelection(s32 arg0) {
    s32 flags;
    char buf[0x24];

    func_80024408(arg0);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, "JETPAC GAME SELECTION", 0x50, 0x38, 0);
    jetpacDrawString(arg0, "1@@@1@PLAYER@GAME", 0x50, 0x50, D_8002BA6C != 0 && J0aG->unk348 == 1);
    jetpacDrawString(arg0, "2@@@2@PLAYER@GAME", 0x50, 0x60, D_8002BA6C != 0 && J0aG->unk348 == 2);
    jetpacDrawString(arg0, "3@@@KEYBOARD", 0x50, 0x70, D_8002BA6C != 0 && J0aG->unk34C == 0);
    jetpacDrawString(arg0, "4@@@KEMPSTON@JOYSTICK", 0x50, 0x80, D_8002BA6C != 0 && J0aG->unk34C != 0);
    jetpacDrawString(arg0, "5   START GAME", 0x50, 0xB8, 0);
    _sprintf(buf, "%c1983 A.C.G. ALL RIGHTS RESERVED", 0x7F);
    jetpacDrawString(arg0, buf, 0x20, 0xD8, 0);
    if (J0aG->unk798 != 0) {
        if (!(J0aG->unk8 & 0x1000) && J0aG->unk799 < 0x78) {
            J0aG->unk799++;
            return;
        }
        J0aG->unk799 = 0;
        jetpacStartGame();
        return;
    }
    flags = J0aG->unk8;
    if (flags & 0x4000) {
        J0aG->unk348 ^= 3;
    }
    if (flags & 0x8000) {
        J0aG->unk34C ^= 1;
    }
    if (flags & 0x1000) {
        jetpacStartGame();
    }
}

void jetpacStateLanding(s32 arg0) {
    func_80024408(arg0);
    jetpacUpdateRocketFlight();
    jetpacInitRdp(arg0);
    func_80028E88();
    func_800289EC();
    jetpacGridDraw(arg0);
}

void jetpacPlayerStateUpdate(void);
void jetpacItemsUpdate(void);
void jetpacDrawPlayer(void);

typedef struct {
    u8 pad0[0x44];
    void (*unk44)(void *);
    u8 pad48[4];
} J0aItem;

void jetpacStateGameplay(s32 arg0) {
    JetpacPlayer *sp1C = &jetpacGame.players[jetpacGame.active_player];

    if (sp1C->score >= 1000000) {
        sp1C->score -= 1000000;
    }
    func_80024408(arg0);
    if (((J0aItem *)&sp1C->pad14[sp1C->unk10 * 0x4C])->unk44) {
    }
    jetpacPlayerStateUpdate();
    jetpacUpdateLasers();
    sp1C->unk18C(&sp1C->unk148);
    {
        J0aItem *it = (J0aItem *)&sp1C->pad14[sp1C->unk10 * 0x4C];
        it->unk44(it);
    }
    jetpacUpdateActors();
    jetpacInitRdp(arg0);
    func_80028E88();
    jetpacDrawPlayer();
    jetpacDrawActors();
    jetpacItemsUpdate();
    func_800285DC();
    jetpacDrawLasers();
    jetpacGridDraw(arg0);
    if (jetpacIsSpawnDelay() != 0) {
        J0aG->unk44C++;
    }
    if (J0aG->unk8 & 0x1000) {
        J0aG->unk78C = 3;
        J0aG->unkC = 1;
    }
}

void jetpacSaveHighScore(void) {
    func_8060C648(0x11, 0, 0, 0, D_8002EC48);
    func_8060DEA8();
}

s32 flagGet(s32, s32);
void func_805FF378(s32, s32);
s32 func_8060C6B8(s32, s32, s32, s32);
void func_8060C8AC(s32);
void jetpacNextPlayerOrGameOver(JetpacPlayer *);


void jetpacStatePause(s32 arg0) {
    func_80024408(arg0);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, "RETURN", 0x88, 0x70, D_8002BA6C != 0 && jetpacGame.unkC == 1);
    jetpacDrawString(arg0, "DELETE@HISCORE", 0x68, 0x80, D_8002BA6C != 0 && jetpacGame.unkC == 2);
    jetpacDrawString(arg0, "EXIT@@JETPAC", 0x70, 0x90, D_8002BA6C != 0 && jetpacGame.unkC == 0);
    if (jetpacGame.unk8 & 0xE000) {
        switch (jetpacGame.unkC) {
        default:
        case 0:
            func_805FF378(jetpacGame.unk798 != 0 ? 5 : 0x50, 0);
            break;
        case 1:
            jetpacGame.unk78C = 2;
            break;
        case 2:
            if (jetpacGame.high_score != 0) {
                func_8060C8AC(1);
                jetpacGame.high_score = func_8060C6B8(0x11, 0, 0, 0);
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

void jetpacStateTakeoff(s32 arg0) {
    JetpacPlayer *sp1C = &jetpacGame.players[jetpacGame.active_player];

    func_80024408(arg0);
    jetpacUpdateLasers();
    sp1C->unk18C(&sp1C->unk148);
    jetpacUpdateRocketFlight();
    jetpacUpdateActors();
    jetpacInitRdp(arg0);
    func_80028E88();
    jetpacDrawActors();
    func_800289EC();
    func_800285DC();
    jetpacDrawLasers();
    jetpacGridDraw(arg0);
}

void jetpacStateGameOver(s32 arg0) {
    s32 sp4C;
    char sp2C[0x20];

    sp4C = 7;
    func_80024408(arg0);
    if (jetpacGame.unk798 != 0 && flagGet(0x62, 2) != 0) {
        _sprintf(sp2C, "RAREWARE COIN COLLECTED");
        sp4C = 5;
    } else {
        _sprintf(sp2C, "GAME OVER PLAYER %d", jetpacGame.active_player + 1);
    }
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, sp2C, sp4C * 8 + 0x20, 0x88, 0);
    if ((u32)jetpacGame.unk790 >= 0x79U) {
        if (jetpacGame.unk798 != 0) {
            if (jetpacGame.unk799 == 0) {
                jetpacGame.unk799 = 1;
                func_805FF378(5, 0);
            }
        } else {
            jetpacNextPlayerOrGameOver(&jetpacGame.players[jetpacGame.active_player]);
        }
    }
}

void jetpacPlaySound(s32 arg0) {
    s32 *var_s0;

    if (arg0 < 7) { var_s0 = &D_80770DF8[arg0]; do { if (*var_s0 != 0) { n_alSndpStop(*var_s0); } var_s0++; } while (var_s0 != D_80770E14); }
    n_alSndpPlay(D_8076D1F8, *(s16 *)((u8 *)D_8002BA52 + arg0 * 4), 0x7FFF, 0x3F, 1.0f, 0, &D_80770DF8[arg0]);
}

void jetpacSetSoundPitch(s32 arg0, s32 arg1) {
    if (D_80770DF8[arg0] != 0) {
        s32 *p = &arg1;
        n_alSndpPostEvent(D_80770DF8[arg0], 0x10, *p);
    }
}

void jetpacStopSound(s32 arg0) {
    if (D_80770DF8[arg0] != 0) {
        n_alSndpStop(D_80770DF8[arg0]);
    }
}

void jetpacSetState(s32 arg0) {
    s32 pad;
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.active_player];

    jetpacGame.unk794 = 0;
    switch (arg0) {
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
    jetpacGame.unk78C = arg0;
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
        player->unk114 = 0;
        player->unk10 = 1;
        jetpacSetState(2);
    } else {
        jetpacSpawnFuelPod(player);
        jetpacSetState(1);
    }
}

#ifdef NON_MATCHING
typedef struct {
    u16 unk0;
    s8 unk2;
    s8 unk3;
} J0bPad;

extern u8 D_8002BA70;
extern J0bPad *D_807ECDE8;
void jetpacStateSelection(s32);
void jetpacStateGameplay(s32);

void func_80025168(s32 arg0) {
    u8 flag;
    s32 zero;
    volatile s32 *p;

    zero = 0;
    if (D_8002BA70 != 0) {
        jetpacGame.unk78C = 0;
        jetpacGame.unk790 = 0;
        jetpacGame.unk794 = 3;
        jetpacGame.num_players = 1;
        jetpacGame.unk34C = 0;
        D_8002BA70 = zero;
        jetpacGame.high_score = func_8060C6B8(0x11, zero, zero, zero);
        flag = flagGet(0x61, 2);
        jetpacGame.unk798 = flag;
        if (flag != zero) {
            jetpacGame.unk799 = 0;
        }
    }
    p = &D_8002BA6C;
    *p = (s64)jetpacGame.unk790;
    *p = jetpacGame.unk790 % 60;
    *p = jetpacGame.unk790 % 60 / 30;
    jetpacGame.unk4 = jetpacGame.unk0;
    jetpacGame.unk0 = D_807ECDE8->unk0;
    if (0) {
    }
    if ((zero = D_807ECDE8->unk2) >= 0x1F) {
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
        jetpacStateSelection(arg0);
        break;
    case 1:
        jetpacStateLanding(arg0);
        break;
    case 2:
        jetpacStateGameplay(arg0);
        break;
    case 3:
        jetpacStatePause(arg0);
        break;
    case 4:
        jetpacStateTakeoff(arg0);
        break;
    case 5:
        jetpacStateGameOver(arg0);
        break;
    }
    jetpacGame.unk790 = jetpacGame.unk790 + 1;
}

#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80025168.s")
#endif

void jetpacNextPlayerOrGameOver(JetpacPlayer *arg0) {
    s32 other_idx = jetpacGame.active_player ^ 1;
    JetpacPlayer *other = &jetpacGame.players[other_idx];

    if (arg0->lives < 0 && jetpacGame.unk78C != 5) {
        if (jetpacGame.high_score < arg0->score) {
            jetpacGame.high_score = arg0->score;
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
    if (arg0->lives >= 0) {
        jetpacSetState(2);
        return;
    }
    jetpacSetState(0);
}

