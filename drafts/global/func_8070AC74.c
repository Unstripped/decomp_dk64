// func_8070AC74 (src/global/10E1D0.c): stage 2: display-list setup behavior recovered; missing raw commands after perspective
typedef struct R1F10E1D0bMatrixBuffer {
    Mtx unk0;
    Mtx unk40;
    Mtx unk80;
    Mtx unkC0;
    Mtx unk100;
    Mtx unk140;
    Mtx unk180;
    Mtx unk1C0;
    Mtx unk200;
} R1F10E1D0bMatrixBuffer;

extern Gfx *D_8076A050[];
extern void *D_8076A080;
extern u16 D_8076A09C;
extern Gfx D_1000090[];
Gfx *func_805FCFD8();
Gfx *func_805FE398(Gfx *);
Gfx *func_805FE4D4(Gfx *);

void func_8070AC74(R1F10E1D0bMatrixBuffer *arg0, Gfx **arg1) {
    Gfx *glist = D_8076A050[D_807444FC];

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(arg0));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(glist++, &D_1000090);
    glist = func_805FE398(func_805FCFD8(glist));
    gDPPipeSync(glist++);
    guTranslate(&arg0->unk180, 0.0f, 0.0f, 0.0f);
    guLookAt(&arg0->unk200, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guPerspective(&arg0->unk0, &D_8076A09C, 61.9f, 1.3333334f, 10.0f, 1000.0f, 1.0f);
    gDPPipeSync(glist++);
    glist = func_805FE4D4(glist);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 6, 2, 0);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 4, 2, 0);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    gSPPerspNormalize(glist++, D_8076A09C);
    *arg1 = glist;
}
