#include "common.h"

void jetpacInitLedges(void);
void func_80024390(void);
void func_800250A0(void);
void func_80024408(s32);
void func_800286D0(void);
void jetpacInitRdp(s32);
void func_80028E88(void);
void func_800289EC(void);
void func_80025904(s32);
void func_8060C648(s32, s32, s32, s32, s32);
void func_8060DEA8(void);
extern s32 D_8002EC48;
void n_alSndpStop(s32);
extern s32 D_80770DF8[];
void n_alSndpPostEvent(s32, ...);
void func_80026CEC(void);
void func_8002ABDC(void);
void func_8002AD8C(void);
void func_800285DC(void);
void func_80026CA4(void);
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

extern JetpacGlobal D_8002EC30;

void func_80027D64(JetpacPlayer *);
void func_800275F4(JetpacPlayer *);
void func_80028340(JetpacPlayer *);
void func_80024F9C(s32);
void func_80028950(void);
void func_80026DC8(void);
void func_8002AAD4(void);
void func_80028B54(JetpacPlayer *);
void func_80028634(void);
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
void func_8002419C(u8 *, Gfx **);

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

void func_80024000(void) {
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
        func_8002419C(D_8076A048, &sp2C);
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
void func_8002419C(u8 *arg0, Gfx **arg1) {
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

void func_80024390(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_8002EC30.players[i].stage = -1;
        D_8002EC30.players[i].score = 0;
        if (i < D_8002EC30.num_players) {
            if (D_8002EC30.unk798 != 0) {
                D_8002EC4C[i].lives = 3;
            } else {
                D_8002EC4C[i].lives = 5;
            }
        } else {
            D_8002EC4C[i].lives = -1;
        }
    }
    D_8002EC30.active_player = 0;
}

extern s32 D_8002BA6C;
s32 func_80026FE0(void);
void func_8002AE00(s32);
void func_8002AE94(s32, s32, s32, s32);
void func_8002AEFC(s32, char *, s32, s32, s32);
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

    mask = func_80026FE0() & D_8002BA6C;
    func_8002AE00(arg0);
    func_8002AE94(0xFF, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, "1UP", 0x38, 0x18, mask != 0 && D_8002EF74 == 0);
    for (i = 0; i < 2; i++) {
        if (D_8002EC4C[i].lives > 0) {
            _sprintf(buf, "%d!", D_8002EC4C[i].lives);
            func_8002AEFC(arg0, buf, i * 0x70 + 0x60, 0x18, 0);
        }
    }
    func_8002AEFC(arg0, "2UP", 0xF8, 0x18, mask != 0 && D_8002EF74 == 1);
    func_8002AE94(0, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, "HI", 0x98, 0x18, 0);
    func_8002AE94(0xFF, 0xFF, 0, 0xFF);
    _sprintf(buf, "%06d", D_8002EC50);
    func_8002AEFC(arg0, buf, 0x28, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EC48);
    func_8002AEFC(arg0, buf, 0x88, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EDE4);
    func_8002AEFC(arg0, buf, 0xE8, 0x20, 0);
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024408.s")
#endif

void func_8002463C(void) {
    jetpacInitLedges();
    func_80024390();
    func_800250A0();
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
#define J0aG ((J0aGlobalView *)&D_8002EC30)

void func_8002466C(s32 arg0) {
    s32 flags;
    char buf[0x24];

    func_80024408(arg0);
    func_8002AE94(0xFF, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, "JETPAC GAME SELECTION", 0x50, 0x38, 0);
    func_8002AEFC(arg0, "1@@@1@PLAYER@GAME", 0x50, 0x50, D_8002BA6C != 0 && J0aG->unk348 == 1);
    func_8002AEFC(arg0, "2@@@2@PLAYER@GAME", 0x50, 0x60, D_8002BA6C != 0 && J0aG->unk348 == 2);
    func_8002AEFC(arg0, "3@@@KEYBOARD", 0x50, 0x70, D_8002BA6C != 0 && J0aG->unk34C == 0);
    func_8002AEFC(arg0, "4@@@KEMPSTON@JOYSTICK", 0x50, 0x80, D_8002BA6C != 0 && J0aG->unk34C != 0);
    func_8002AEFC(arg0, "5   START GAME", 0x50, 0xB8, 0);
    _sprintf(buf, "%c1983 A.C.G. ALL RIGHTS RESERVED", 0x7F);
    func_8002AEFC(arg0, buf, 0x20, 0xD8, 0);
    if (J0aG->unk798 != 0) {
        if (!(J0aG->unk8 & 0x1000) && J0aG->unk799 < 0x78) {
            J0aG->unk799++;
            return;
        }
        J0aG->unk799 = 0;
        func_8002463C();
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
        func_8002463C();
    }
}

void func_800248A0(s32 arg0) {
    func_80024408(arg0);
    func_800286D0();
    jetpacInitRdp(arg0);
    func_80028E88();
    func_800289EC();
    func_80025904(arg0);
}

#ifdef NON_MATCHING
void jetpacPlayerStateUpdate(void);
void jetpacItemsUpdate(void);
void func_80026AB0(void);

typedef struct {
    u8 pad0[0x44];
    void (*unk44)(void *);
    u8 pad48[4];
} J0aItem;

void func_800248E8(s32 arg0) {
    JetpacPlayer *sp1C = &D_8002EC30.players[D_8002EC30.active_player];

    if (sp1C->score >= 1000000) {
        sp1C->score -= 1000000;
    }
    func_80024408(arg0);
    jetpacPlayerStateUpdate();
    func_80026CEC();
    sp1C->unk18C(&sp1C->unk148);
    ((J0aItem *)&sp1C->pad14[sp1C->unk10 * 0x4C])->unk44(&sp1C->pad14[sp1C->unk10 * 0x4C]);
    func_8002ABDC();
    jetpacInitRdp(arg0);
    func_80028E88();
    func_80026AB0();
    func_8002AD8C();
    jetpacItemsUpdate();
    func_800285DC();
    func_80026CA4();
    func_80025904(arg0);
    if (func_80026FE0() != 0) {
        J0aG->unk44C++;
    }
    {
        J0aGlobalView *g = J0aG;
        if (g->unk8 & 0x1000) {
            g->unk78C = 3;
            g->unkC = 1;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_800248E8.s")
#endif

void func_80024A4C(void) {
    func_8060C648(0x11, 0, 0, 0, D_8002EC48);
    func_8060DEA8();
}

s32 flagGet(s32, s32);
void func_805FF378(s32, s32);
s32 func_8060C6B8(s32, s32, s32, s32);
void func_8060C8AC(s32);
void func_80025368(JetpacPlayer *);


void func_80024A8C(s32 arg0) {
    func_80024408(arg0);
    func_8002AE94(0xFF, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, "RETURN", 0x88, 0x70, D_8002BA6C != 0 && D_8002EC30.unkC == 1);
    func_8002AEFC(arg0, "DELETE@HISCORE", 0x68, 0x80, D_8002BA6C != 0 && D_8002EC30.unkC == 2);
    func_8002AEFC(arg0, "EXIT@@JETPAC", 0x70, 0x90, D_8002BA6C != 0 && D_8002EC30.unkC == 0);
    if (D_8002EC30.unk8 & 0xE000) {
        switch (D_8002EC30.unkC) {
        default:
        case 0:
            func_805FF378(D_8002EC30.unk798 != 0 ? 5 : 0x50, 0);
            break;
        case 1:
            D_8002EC30.unk78C = 2;
            break;
        case 2:
            if (D_8002EC30.high_score != 0) {
                func_8060C8AC(1);
                D_8002EC30.high_score = func_8060C6B8(0x11, 0, 0, 0);
                func_80024A4C();
            }
            break;
        }
    }
    if (D_8002EC30.unk8 & 0x400) {
        D_8002EC30.unkC++;
    }
    if (D_8002EC30.unk8 & 0x800) {
        D_8002EC30.unkC--;
    }
    if (D_8002EC30.unkC >= 3) {
        D_8002EC30.unkC = 0;
    }
    if (D_8002EC30.unkC < 0) {
        D_8002EC30.unkC = 2;
    }
}

void func_80024C90(s32 arg0) {
    JetpacPlayer *sp1C = &D_8002EC30.players[D_8002EC30.active_player];

    func_80024408(arg0);
    func_80026CEC();
    sp1C->unk18C(&sp1C->unk148);
    func_800286D0();
    func_8002ABDC();
    jetpacInitRdp(arg0);
    func_80028E88();
    func_8002AD8C();
    func_800289EC();
    func_800285DC();
    func_80026CA4();
    func_80025904(arg0);
}

void func_80024D48(s32 arg0) {
    s32 sp4C;
    char sp2C[0x20];

    sp4C = 7;
    func_80024408(arg0);
    if (D_8002EC30.unk798 != 0 && flagGet(0x62, 2) != 0) {
        _sprintf(sp2C, "RAREWARE COIN COLLECTED");
        sp4C = 5;
    } else {
        _sprintf(sp2C, "GAME OVER PLAYER %d", D_8002EC30.active_player + 1);
    }
    func_8002AE94(0xFF, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, sp2C, sp4C * 8 + 0x20, 0x88, 0);
    if ((u32)D_8002EC30.unk790 >= 0x79U) {
        if (D_8002EC30.unk798 != 0) {
            if (D_8002EC30.unk799 == 0) {
                D_8002EC30.unk799 = 1;
                func_805FF378(5, 0);
            }
        } else {
            func_80025368(&D_8002EC30.players[D_8002EC30.active_player]);
        }
    }
}

void func_80024E70(s32 arg0) {
    s32 *var_s0;

    if (arg0 < 7) { var_s0 = &D_80770DF8[arg0]; do { if (*var_s0 != 0) { n_alSndpStop(*var_s0); } var_s0++; } while (var_s0 != D_80770E14); }
    n_alSndpPlay(D_8076D1F8, *(s16 *)((u8 *)D_8002BA52 + arg0 * 4), 0x7FFF, 0x3F, 1.0f, 0, &D_80770DF8[arg0]);
}

void func_80024F24(s32 arg0, s32 arg1) {
    if (D_80770DF8[arg0] != 0) {
        s32 *p = &arg1;
        n_alSndpPostEvent(D_80770DF8[arg0], 0x10, *p);
    }
}

void func_80024F64(s32 arg0) {
    if (D_80770DF8[arg0] != 0) {
        n_alSndpStop(D_80770DF8[arg0]);
    }
}

void func_80024F9C(s32 arg0) {
    s32 pad;
    JetpacPlayer *player = &D_8002EC30.players[D_8002EC30.active_player];

    D_8002EC30.unk794 = 0;
    switch (arg0) {
    case 0:
    case 3:
        break;
    case 1:
        func_80028950();
        break;
    case 2:
        if (D_8002EC30.unk78C == 1) {
            D_8002EC30.unk794 = 3;
            player->lives--;
        }
        func_80026DC8();
        func_8002AAD4();
        func_80028B54(player);
        break;
    case 4:
        D_8002F064 = 1;
        func_80028634();
        D_8002EC30.unk794 = 3;
        player->lives++;
        break;
    case 5:
        D_8002EC30.unk790 = 0;
        break;
    }
    D_8002EC30.unk78C = arg0;
}

void func_800250A0(void) {
    JetpacPlayer *player = &D_8002EC30.players[D_8002EC30.active_player];

    if (player->stage < 0) {
        player->lives--;
    }
    player->stage++;
    func_80027D64(player);
    if ((player->stage & 3) == 0) {
        func_800275F4(player);
        player->unk114 = 0;
        player->unk10 = 1;
        func_80024F9C(2);
    } else {
        func_80028340(player);
        func_80024F9C(1);
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
void func_8002466C(s32);
void func_800248E8(s32);

void func_80025168(s32 arg0) {
    u8 flag;
    s32 zero;
    volatile s32 *p;

    zero = 0;
    if (D_8002BA70 != 0) {
        D_8002EC30.unk78C = 0;
        D_8002EC30.unk790 = 0;
        D_8002EC30.unk794 = 3;
        D_8002EC30.num_players = 1;
        D_8002EC30.unk34C = 0;
        D_8002BA70 = zero;
        D_8002EC30.high_score = func_8060C6B8(0x11, zero, zero, zero);
        flag = flagGet(0x61, 2);
        D_8002EC30.unk798 = flag;
        if (flag != zero) {
            D_8002EC30.unk799 = 0;
        }
    }
    p = &D_8002BA6C;
    *p = (s64)D_8002EC30.unk790;
    *p = D_8002EC30.unk790 % 60;
    *p = D_8002EC30.unk790 % 60 / 30;
    D_8002EC30.unk4 = D_8002EC30.unk0;
    D_8002EC30.unk0 = D_807ECDE8->unk0;
    if (0) {
    }
    if ((zero = D_807ECDE8->unk2) >= 0x1F) {
        D_8002EC30.unk0 |= 0x100;
    }
    if (D_807ECDE8->unk2 < -0x1E) {
        D_8002EC30.unk0 |= 0x200;
    }
    if (D_807ECDE8->unk3 >= 0x1F) {
        D_8002EC30.unk0 |= 0x800;
    }
    if (D_807ECDE8->unk3 < -0x1E) {
        D_8002EC30.unk0 |= 0x400;
    }
    D_8002EC30.unk8 = (D_8002EC30.unk0 ^ D_8002EC30.unk4) & D_8002EC30.unk0;
    if ((u32)D_8002EC30.unk794 < 3) {
        D_8002EC30.unk794++;
        return;
    }
    switch (D_8002EC30.unk78C) {
    case 0:
        func_8002466C(arg0);
        break;
    case 1:
        func_800248A0(arg0);
        break;
    case 2:
        func_800248E8(arg0);
        break;
    case 3:
        func_80024A8C(arg0);
        break;
    case 4:
        func_80024C90(arg0);
        break;
    case 5:
        func_80024D48(arg0);
        break;
    }
    D_8002EC30.unk790 = D_8002EC30.unk790 + 1;
}

#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80025168.s")
#endif

void func_80025368(JetpacPlayer *arg0) {
    s32 other_idx = D_8002EC30.active_player ^ 1;
    JetpacPlayer *other = &D_8002EC30.players[other_idx];

    if (arg0->lives < 0 && D_8002EC30.unk78C != 5) {
        if (D_8002EC30.high_score < arg0->score) {
            D_8002EC30.high_score = arg0->score;
            func_80024A4C();
        }
        func_80024F9C(5);
        return;
    }

    if (other->lives >= 0) {
        D_8002EC30.active_player = other_idx;
        if (other->stage < 0) {
            func_800250A0();
            return;
        }
        func_80024F9C(2);
        return;
    }
    if (arg0->lives >= 0) {
        func_80024F9C(2);
        return;
    }
    func_80024F9C(0);
}

