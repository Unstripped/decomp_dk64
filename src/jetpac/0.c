#include "common.h"

void func_80028C3C(void);
void func_80024390(void);
void func_800250A0(void);
void func_80024408(s32);
void func_800286D0(void);
void func_800255D4(s32);
void func_80028E88(void);
void func_800289EC(void);
void func_80025904(s32);
void func_8060C648(s32, s32, s32, s32, s32);
void func_8060DEA8(void);
extern s32 D_8002EC48;
void n_alSndpDeallocate(s32);
extern s32 D_80770DF8[];
void func_80737AC4(s32, ...);
void func_80026CEC(void);
void func_8002ABDC(void);
void func_8002AD8C(void);
void func_800285DC(void);
void func_80026CA4(void);
extern s32 D_8076D1F8;
extern s16 D_8002BA52[];
extern s32 D_80770E14[];
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
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
    u8 pad0[0x18];
    s32 high_score;
    JetpacPlayer players[2];
    s32 active_player;
    s32 num_players;
    u8 pad34C[0x78C - 0x34C];
    s32 unk78C;
    s32 unk790;
    s32 unk794;
    u8 unk798;
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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024000.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_8002419C.s")

#if 0
// Register scheduling order in prologue (lui a0 vs a2)
void func_80024390(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_8002EC30.players[i].entity.stage = -1;
        D_8002EC30.players[i].entity.score = 0;
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
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024390.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024408.s")

void func_8002463C(void) {
    func_80028C3C();
    func_80024390();
    func_800250A0();
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_8002466C.s")

void func_800248A0(s32 arg0) {
    func_80024408(arg0);
    func_800286D0();
    func_800255D4(arg0);
    func_80028E88();
    func_800289EC();
    func_80025904(arg0);
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_800248E8.s")

void func_80024A4C(void) {
    func_8060C648(0x11, 0, 0, 0, D_8002EC48);
    func_8060DEA8();
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024A8C.s")

void func_80024C90(s32 arg0) {
    JetpacPlayer *sp1C = &D_8002EC30.players[D_8002EC30.active_player];

    func_80024408(arg0);
    func_80026CEC();
    sp1C->unk18C(&sp1C->unk148);
    func_800286D0();
    func_8002ABDC();
    func_800255D4(arg0);
    func_80028E88();
    func_8002AD8C();
    func_800289EC();
    func_800285DC();
    func_80026CA4();
    func_80025904(arg0);
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024D48.s")

#if 0
// Instruction scheduling swap between lui/addiu s1 and addu s0
void func_80024E70(s32 arg0) {
    s32 *var_s0;

    if (arg0 < 7) {
        var_s0 = &D_80770DF8[arg0];
        do {
            if (*var_s0 != 0) {
                n_alSndpDeallocate(*var_s0);
            }
            var_s0++;
        } while (var_s0 != D_80770E14);
    }
    n_alSndpAllocate(D_8076D1F8, *(s16 *)((u8 *)D_8002BA52 + arg0 * 4), 0x7FFF, 0x3F, 1.0f, 0, &D_80770DF8[arg0]);
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80024E70.s")

void func_80024F24(s32 arg0, s32 arg1) {
    if (D_80770DF8[arg0] != 0) {
        s32 *p = &arg1;
        func_80737AC4(D_80770DF8[arg0], 0x10, *p);
    }
}

void func_80024F64(s32 arg0) {
    if (D_80770DF8[arg0] != 0) {
        n_alSndpDeallocate(D_80770DF8[arg0]);
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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80025168.s")

#if 0
// 1 instruction difference: pointer offset addiu a0, 0x1C vs direct offset 0x1C(a0)
void func_80025368(JetpacEntity *arg0) {
    s32 other_player_idx = D_8002EC30.active_player ^ 1;
    JetpacEntity *other_entity;

    if (arg0->lives < 0 && D_8002EC30.unk78C != 5) {
        if (D_8002EC30.players[0].high_score < arg0->score) {
            D_8002EC30.players[0].high_score = arg0->score;
            func_80024A4C();
        }
        func_80024F9C(5);
        return;
    }

    other_entity = (JetpacEntity *)((u8 *)&D_8002EC30.players[other_player_idx] + 0x1C);
    if (other_entity->lives >= 0) {
        D_8002EC30.active_player = other_player_idx;
        if (other_entity->stage < 0) {
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
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/0/func_80025368.s")
