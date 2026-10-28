// func_80704960 (src/global/109660.c): stage 6: only regalloc left (4 text hunks: gDP packet temps start at a1/a2 instead of a2/a3 -> a1,a2,a3,t0 vs a2,a3,t0,t1); index loop 'for (i=0; D[i].unk0 != -1; i++)' + stmt order F6|lrx|lry, ulx|uly reproduces everything else; tried dead stmts, line joining, pointer loops, permuter 18 min
typedef struct {
    s8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R1F109660aRect;

extern R1F109660aRect D_80750840[];
extern u8 D_80750AB8;
extern u8 D_80750ABC;
extern u8 D_8074450C;

Gfx *func_80704960(Gfx *dl) {
    s32 i;

    gDPPipeSync(dl++);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
    gDPSetCycleType(dl++, G_CYC_FILL);
    gDPSetFillColor(dl++, 0x10001);
    for (i = 0; D_80750840[i].unk0 != -1; i++) {
        if (((D_80750840[i].unk0 == 2) && ((s32)D_807FC928 >= 2) && (D_80750840[i].unk2 & D_80750ABC)) || ((D_807FC928 == D_80750840[i].unk0) && (D_80750AB8 == D_80750840[i].unk1) && (D_80750840[i].unk2 & D_80750ABC))) {
            Gfx *_g = (Gfx *)(dl++);
            _g->words.w0 = 0xF6000000 | (((((D_80750840[i].unk8 + 1) * D_8074450C) - 1) & 0x3FF) << 14) | (((((D_80750840[i].unkA + 1) * D_8074450C) - 1) & 0x3FF) << 2);
            _g->words.w1 = ((((D_80750840[i].unk4 * D_8074450C) & 0x3FF)) << 14) | ((((D_80750840[i].unk6 * D_8074450C) & 0x3FF)) << 2);
        }
    }
    gDPPipeSync(dl++);
    return dl;
}
