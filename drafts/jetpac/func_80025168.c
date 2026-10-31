// func_80025168 (src/jetpac/0.c): stage 5-6: 7 diff lines (frame/size/regs identical). Remaining diff: target p=v0, rem=t1; ours p=a0, rem=v0. uopt candidate 1243 (rem) adjsave 3.0 colors into v0 before p adjsave 2.0
typedef struct {
    u16 unk0;
    s8 unk2;
    s8 unk3;
} J0bPad;

typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
    u8 padC[0x18 - 0xC];
    s32 high_score;
    u8 pad1C[0x348 - 0x1C];
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
extern s32 D_8002BA6C;
extern u8 D_8002BA70;
extern J0bPad *D_807ECDE8;

s32 func_8060C6B8(s32, s32, s32, s32);
u8 flagGet(s32, s32);
void jetpacStateSelection(s32);
void jetpacStateLanding(s32);
void jetpacStateGameplay(s32);
void jetpacStatePause(s32);
void jetpacStateTakeoff(s32);
void jetpacStateGameOver(s32);

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
