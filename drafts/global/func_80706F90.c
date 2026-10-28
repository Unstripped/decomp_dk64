// func_80706F90 (src/global/109660.c): L9 stage 5 (parked NON_MATCHING in .scratch/L9/109660.c): text identical except epilogue D_80754F70 accesses (target direct lui/lh + lui at/sh per access, mine CSEs the address: lui/addiu v1; lh 0(v1); sh 0(v1)) and one reloc (D_807FD978+0x20 vs label D_807FD998). Tried epilogue orders/forms, volatile, array decl, ps types, dead stmts (deadsweep +locals). Key tricks: (j<<2)/(i<<2) not *4 (stops strength reduction), real gDPLoadTextureBlock(32x64) on one line, gSPScisTextureRectangle, y2=y; rect; y2+=0x200 chain, tv local before the macro
extern s16 D_80754CE0;
extern s16 D_80754CEC[];
extern s16 D_80754F70;
extern s16 D_80754F74;
extern s32 D_807FD998;
s32 func_8066B0F8(s32, s32, s32, s32);

Gfx *func_80706F90(Gfx *dl) {
    s32 tv;
    s32 n;
    s32 x;
    s32 i;
    s32 j;
    s16 ps;
    s32 y;
    s32 y2;
    u16 k;
    s16 scroll;

    gSPClearGeometryMode(dl++, 0xFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    { Gfx *_g = (Gfx *)(dl++); _g->words.w0 = 0xFC11FE23; _g->words.w1 = 0xFFFFF3F9; }
    gDPSetTexturePersp(dl++, G_TP_NONE);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPPipeSync(dl++);
    scroll = D_80754F74 + D_80754CE0;
    if (scroll < 0) {
        scroll += 0x200;
    }
    if (scroll >= 0x200) {
        scroll -= 0x200;
    }
    if (D_807FD978 == 0) {
        for (n = 0; n < 8; n++) {
            (&D_807FD978)[n] = func_8066B0F8(0x19, D_80754CEC[n], 0, 0);
        }
    }
    k = 0;
    j = 0x40;
    do {
        i = 0;
        y = (j << 2) - scroll;
        do {
            gDPPipeSync(dl++);
            tv = (&D_807FD978)[k];
            gDPLoadTextureBlock(dl++, (u32)tv + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            x = (i << 2) - D_80754F70;
            for (n = 0; n != 4; n++) {
                y2 = y;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                x += 0x200;
            }
            k++;
            i += 0x20;
        } while (i != 0x80);
        j -= 0x40;
    } while (j >= 0);
    ps = D_80754F70 + 4;
    D_80754F74 += 4;
    D_80754F70 = ps;
    if (ps >= 0x200) {
        D_80754F70 = 0;
    }
    if (D_80754F74 >= 0x200) {
        D_80754F74 = 0;
    }
    gDPPipeSync(dl++);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    return dl;
}
