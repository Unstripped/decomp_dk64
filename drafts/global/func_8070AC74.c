// func_8070AC74 (src/global/10E1D0.c): compilable explicit display-list reconstruction; command body matches closely, prologue allocation remains
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

#define R1F10E1D0B_WRITE_GFX(pkt, _w0, _w1) \
    (pkt)->words.w0 = (_w0);                 \
    (pkt)->words.w1 = (_w1);                 \
    (pkt)++

extern Gfx *D_8076A050[];
extern void *D_8076A080;
extern u16 D_8076A09C;
extern Gfx D_1000090[];

Gfx *func_805FCFD8();
Gfx *func_805FE398();
Gfx *func_805FE4D4();

void func_8070AC74(R1F10E1D0bMatrixBuffer *arg0, Gfx **arg1) {
    Gfx *glist = D_8076A050[D_807444FC];

    R1F10E1D0B_WRITE_GFX(glist, 0xDB060000, 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xDB060008, osVirtualToPhysical(arg0));
    R1F10E1D0B_WRITE_GFX(glist, 0xDB060004, osVirtualToPhysical(D_8076A080));
    R1F10E1D0B_WRITE_GFX(glist, 0xDE000000, &D_1000090);
    glist = func_805FE398(func_805FCFD8(glist));
    R1F10E1D0B_WRITE_GFX(glist, 0xE7000000, 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xE3000A01, 0);
    guTranslate(&arg0->unk180, 0.0f, 0.0f, 0.0f);
    guLookAt(&arg0->unk200, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guPerspective(&arg0->unk0, &D_8076A09C, 61.9f, 1.3333334f, 10.0f, 1000.0f, 1.0f);
    R1F10E1D0B_WRITE_GFX(glist, 0xE7000000, 0);
    glist = func_805FE4D4(glist);
    R1F10E1D0B_WRITE_GFX(glist, 0xE3001801, 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xE3001A01, 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xED028028, 0x4D4394);
    R1F10E1D0B_WRITE_GFX(glist, 0xF7000000, 0xFFC1FFC1);
    R1F10E1D0B_WRITE_GFX(glist, 0xE200001C, 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xD9FFFFFE, 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xF6000000 | (((D_80744490 - 1) & 0x3FF) << 14) | (((D_80744494 - 1) & 0x3FF) << 2), 0);
    R1F10E1D0B_WRITE_GFX(glist, 0xDB0E0000, D_8076A09C);
    R1F10E1D0B_WRITE_GFX(glist, 0xDB040004, 2);
    R1F10E1D0B_WRITE_GFX(glist, 0xDB04000C, 2);
    R1F10E1D0B_WRITE_GFX(glist, 0xDB040014, 0xFFFE);
    R1F10E1D0B_WRITE_GFX(glist, 0xDB04001C, 0xFFFE);
    *arg1 = glist;
}
