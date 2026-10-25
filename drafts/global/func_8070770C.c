// func_8070770C (src/global/109660.c): stage 1 renderer/display-list reconstruction; command sequence recovered, frame and display-list pointer allocation differ
typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} R2F109660cRendererPlayer;

extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;

Gfx *func_8070770C(Gfx *glist) {
    Gfx *sp1C;
    Gfx *spC;
    R2F109660cRendererPlayer *player;

    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
    gDPSetFillColor(glist++, 0x00010001);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
    sp1C = glist;
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_80744498, D_8074449C, D_807444A0, D_807444A4);
    gDPFillRectangle(glist++, D_80744498, D_8074449C, D_807444A0 - 1, D_807444A4 - 1);
    gDPPipeSync(glist++);
    player = (R2F109660cRendererPlayer *)D_807FC924;
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, player->unk270, player->unk272, player->unk274, player->unk276);
    spC = glist;
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
    return glist;
}
