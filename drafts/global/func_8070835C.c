// func_8070835C (src/global/109660.c): stage 2 display-list reconstruction; frame and call shape match, but player base pointer and command pointer allocation differ
typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x5C];
    void *unk2D4;
    void *unk2D8;
} R2F109660cPlayerView;

Gfx *func_80706F90(Gfx *);
Gfx *func_80707980(Gfx *, void *, void *, void *, s32);
extern s32 D_807FBB60;
extern s32 D_807552EC;

Gfx *func_8070835C(Gfx *glist, s16 player) {
    R2F109660cPlayerView *player_view;
    s32 draw_black;

    if ((D_807FC928 >= 2) || !(D_807FBB60 & 0x10)) {
        if (D_8076A0A8 == 0x50) {
            glist = func_80706F90(glist);
        } else {
            draw_black = !(D_807FBB60 & 2);
            if (D_807FC928 >= 2) {
                draw_black |= (D_8076A0A8 != 0xBE) | (D_807552EC >= 2);
            }
            if (draw_black != 0) {
                gDPPipeSync(glist++);
                gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
                gDPSetFillColor(glist++, 0x00010001);
                gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
                player_view = ((R2F109660cPlayerView **)(&D_807FC924))[0] + player;
                glist->words.w0 = 0xF6000000 | (((player_view->unk276 - 1) & 0x3FF) * 4)
                    | (((player_view->unk274 - 1) & 0x3FF) << 14);
                glist->words.w1 = ((player_view->unk272 & 0x3FF) * 4)
                    | ((player_view->unk270 & 0x3FF) << 14);
                glist++;
                gDPPipeSync(glist++);
                gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
            }
        }
    } else {
        player_view = ((R2F109660cPlayerView **)(&D_807FC924))[0] + player;
        glist = func_80707980(glist, player_view->unk2D4, player_view->unk2D8,
            (u8 *)player_view + (D_807444FC << 6) + 0x108, player);
    }
    return glist;
}
