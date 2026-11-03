// gfxSwapGeometryModeCullBits (src/global/17B90.c): from .scratch/W2Ring/gfxSwapGeometryModeCullBits_best.c
typedef struct GfxCmdWords {
    u32 unk0;
    u32 unk4;
} GfxCmdWords;
void gfxSwapGeometryModeCullBits(GfxCmdWords *arg0, GfxCmdWords *arg1) {
    u32 w0;
    u32 w1;
    s32 x1;
    s32 x2;
    w1 = 0; // FAKE: pre-loop def, extends w1 web over the loop (regalloc)
    w0 = 0; // FAKE: pre-loop def (regalloc)
    x2 = 0; // FAKE: pre-loop def (regalloc)
    if (arg0 != arg1) {
        if ((w1 & 0x600) == 0x200) {} // FAKE: dead test, extends w1's web before the loop (regalloc)
        do {
            w0 = arg0->unk0;
            w1 = arg0->unk4;
            if ((w0 >> 24) == 0xD9) {
                if (arg0->unk4 == 0) {
                    w0 = ~w0 & 0xFFFFFF;
                    if ((w0 & 0x600) == 0x200) {
                        if (w1 == 0) {} // FAKE: dead test, steers uopt colouring
                        x1 = w0 | 0x400;
                        x1 &= ~0x200;
                        arg0->unk0 = ~x1 | 0xD9000000;
                    } else if ((w0 & 0x600) == 0x400) {
                        x2 = w0 | 0x200;
                        x2 &= ~0x400;
                        arg0->unk0 = ~x2 | 0xD9000000;
                    }
                } else {
                    if ((w1 & 0x600) == 0x200) {
                        arg0->unk4 |= 0x400;
                        arg0->unk4 &= ~0x200;
                    } else if ((w1 & 0x600) == 0x400) {
                        arg0->unk4 |= 0x200;
                        if (x2 && x2) {} // FAKE: dead test, steers uopt colouring
                        arg0->unk4 &= ~0x400;
                    }
                    if (w0 && w0) {} // FAKE: dead test, steers uopt colouring
                }
            }
            arg0++;
            if (arg0 == arg1) {
                break;
            }
        } while (1);
    }
}
