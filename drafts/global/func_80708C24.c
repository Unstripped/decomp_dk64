// func_80708C24 (src/global/10D2D0.c): Stage 2 behavioral draft: block order and s0/s1 match, but output frame remains 0x30 versus target 0x38; tried removing locals and inert padding.
typedef struct NmF10D2D0_PlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
    u8 unk2E5;
    u8 unk2E6;
    u8 pad2E7[9];
    s8 unk2F0[0xB];
    s8 unk2FB;
    u8 unk2FC;
    s8 unk2FD;
} NmF10D2D0_PlayerState;

extern s32 D_807FBB60;
void func_80026B0C();
void func_80609140();
s32 func_805FCA64(void);
s32 func_8071432C(void);
s32 func_8071441C(void);
s32 func_8070943C(void);

void func_80708C24(s32 arg0, NmF10D2D0_PlayerState *arg1, NmF10D2D0_PlayerState *arg2, s32 arg3) {
    NmF10D2D0_PlayerState *player;
    s32 state;
    s32 limit;

    player = arg1;
    state = player->unk2E2 & 0xFF;
    if (state & 0x10) {
        player->unk2E2 ^= 0x10;
        if (arg2->unk2FD > 0) {
            limit = arg2->unk2FC * func_8070943C();
            if ((arg2->unk2FB + arg2->unk2FD) < limit) {
                arg2->unk2FB += arg2->unk2FD;
            } else {
                arg2->unk2FB = limit;
            }
        } else if (arg2->unk2FD < 0) {
            if ((func_8071432C() != 0) || (func_8071441C() != 0)) {
                arg2->unk2FB += arg2->unk2FD;
            }
            if (arg2->unk2FB <= 0) {
                arg2->unk2FB = 0;
                player->unk2E6 = 0xC;
                if ((s32)D_807FC928 >= 2) {
                    func_80026B0C(arg0, 0x7FFF, 0x427C0000);
                }
            } else {
                func_80609140(0x24B, 0x7FFF, 0x427C0000, 0x3F800000, 0, 0);
            }
        }
        arg2->unk2FD = 0;
    }
    if ((!(D_807FBB60 & 2) && (func_805FCA64() != 0)) || (state & 0x80)) {
        player->unk2E5--;
        if (!player->unk2E5) {
            player->unk2E5 = 0x11;
            player->unk2E4 = 3;
        }
    }
}
