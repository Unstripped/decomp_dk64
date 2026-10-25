// func_80708DA4 (src/global/10D2D0.c): Stage 3 typed m2c draft; matching only s0 but frame remains 0x68 vs 0x48; verified player byte layout 0x2E3/4/5 and 16-bit flags at 0x2E2; K&R 3-arg definition tried.
typedef struct R3F10D2D0_PlayerView {
    u8 pad0[0x2E0];
    u16 unk2E0;
    u8 unk2E2;
    u8 unk2E3;
    u8 unk2E4;
    u8 unk2E5;
} R3F10D2D0_PlayerView;

typedef struct R3F10D2D0_HudView {
    u8 pad0[0x2FB];
    s8 unk2FB;
    u8 unk2FC;
    u8 pad2FD[9];
} R3F10D2D0_HudView;

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern s32 D_8076A064;
extern s32 D_807FBB60;
f32 func_80612794(s16);
f32 func_80612D1C();
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
s32 func_80714464();
#define R3F10D2D0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
#define R3F10D2D0_FLAGS(player) (*(u16 *)&(player)->unk2E2)



s32 func_805FCA64();
void func_80708C24();
s32 func_80708DA4();


s32 func_80708DA4(arg0, arg1, arg2)
s32 arg0;
s16 arg1;
s32 arg2;
{
    R3F10D2D0_PlayerView *player;
    R3F10D2D0_HudView *hud;
    void *sp38;
    u8 sp37;
    void *sp28;
    s32 sp24;
    f64 var_ft0;
    f64 var_ft1;
    f64 var_ft3;
    f64 var_ft5;
    s32 temp_a0;
    u16 temp_t3_3;
    u8 temp_t3;
    u8 temp_t3_2;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 var_t0;
    void *temp_t9;

    player = (R3F10D2D0_PlayerView *)arg2;
    hud = (R3F10D2D0_HudView *)((arg1 * 0x306) + (s32)D_807FC950);
    temp_t9 = hud;
    sp38 = &D_807FC950[func_806C8DE0(arg1)];
    sp28 = temp_t9;
    temp_a0 = D_807FC928 == 1;
    var_t0 = player->unk2E4;
    if (temp_a0 == 0) {
        var_t0 = 0;
    }
    if (temp_a0 == 0) {
        sp37 = var_t0;
        func_80708C24(arg1, player, sp28, sp38);
        R3F10D2D0_FLAGS(player) = (u16)(R3F10D2D0_FLAGS(player) & 0xFFEA);
    }
    if ((s32)player->unk2E3 & 0x10) {
        switch (var_t0) {
        case 2:
            player->unk2E5 = 0x32U;
            break;
        case 3:
            temp_t3 = player->unk2E5;
            var_ft1 = (f64)temp_t3;
            if ((s32)temp_t3 < 0) {
                var_ft1 += 4294967296.0;
            }
            player->unk2E5 = (u8)(u32)(18.0 - var_ft1);
            player->unk2E4 = 1U;
            break;
        }
    }
    if ((s32)player->unk2E3 & 1) {
        R3F10D2D0_FLAGS(player) = (u16)(R3F10D2D0_FLAGS(player) ^ 1);
        switch (var_t0) {
        case 1:
            break;
        case 0:
            player->unk2E5 = 0x12U;
            player->unk2E4 = 1U;
            break;
        case 3:
            temp_t3_2 = player->unk2E5;
            var_ft0 = (f64)temp_t3_2;
            if ((s32)temp_t3_2 < 0) {
                var_ft0 += 4294967296.0;
            }
            player->unk2E5 = (u8)(u32)(18.0 - var_ft0);
            player->unk2E4 = 1U;
            break;
        }
    } else if ((s32)player->unk2E3 & 4) {
        player->unk2E5 = 1U;
        player->unk2E4 = 2U;
        temp_t3_3 = R3F10D2D0_FLAGS(player) ^ 4;
        R3F10D2D0_FLAGS(player) = temp_t3_3;
        R3F10D2D0_FLAGS(player) = (u16)(temp_t3_3 & 8);
    } else {
        switch (var_t0) {
        case 1:
            temp_t5 = player->unk2E5;
            var_ft5 = (f64)temp_t5;
            if ((s32)temp_t5 < 0) {
                var_ft5 += 4294967296.0;
            }
            sp24 = (s32)player->unk2E3;
            temp_v0 = player->unk2E5;
            player->unk2E0 = (s16)(u32)((f64)func_80612D1C((f32)(((var_ft5 / 18.0) * 1.5707963705062866) + 1.5707963705062866), 3) * 65535.0);
            player->unk2E5 = (u8)(temp_v0 - 1);
            if (temp_v0 == 0) {
                player->unk2E4 = 2U;
                player->unk2E5 = 0x32U;
            }
            break;
        case 2:
            sp24 = (s32)player->unk2E3;
            func_80708C24(arg1, player, sp28, sp38);
            break;
        case 3:
            temp_t4 = player->unk2E5;
            var_ft3 = (f64)temp_t4;
            if ((s32)temp_t4 < 0) {
                var_ft3 += 4294967296.0;
            }
            sp24 = (s32)player->unk2E3;
            temp_v0_2 = player->unk2E5;
            player->unk2E0 = (s16)(u32)((f64)func_80612D1C((f32)((1.5707963705062866 - ((var_ft3 / 18.0) * 1.5707963705062866)) + 1.5707963705062866), 3, player) * 65535.0);
            player->unk2E5 = (u8)(temp_v0_2 - 1);
            if (temp_v0_2 == 0) {
                player->unk2E4 = 0U;
            }
            break;
        }
    }
    sp24 = (s32)player->unk2E3;
    if (((func_805FCA64() != 0) || ((s32)player->unk2E3 & 0x80)) && ((player->unk2E4 != 0) || (R3F10D2D0_FLAGS(player) != 0))) {
        arg0 = (s32)func_807085D0((Gfx *)arg0, (R3F10D2D0_HudView *)sp28, sp38, player);
    }
    return arg0;
}
