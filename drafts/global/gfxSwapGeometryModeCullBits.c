// gfxSwapGeometryModeCullBits (src/global/17B90.c): gfxSwapGeometryModeCullBits (src/global/17B90.c): stage 4: frame 0x18 + s0-s3 + all 60 insns/hoisted consts match (4 distinct typed mask webs via s32 x1/x2 temps + (u32) sw arms); score 22, regs only: loop values (field t0/a3 copy/v0 mask) shuffled; FAKEs: pre-loop w0/w1/x2=0, dead tests x2&&x2, w0&&w0
typedef struct RvR2_Cmd {
    u32 unk0;
    u32 unk4;
} RvR2_Cmd;
void gfxSwapGeometryModeCullBits(RvR2_Cmd *arg0, RvR2_Cmd *arg1) {
    u32 w0;
    u32 w1;
    s32 x1;
    s32 x2;
    w1 = 0; // FAKE: pre-loop def, extends w1 web over the loop (regalloc)
    w0 = 0; // FAKE: pre-loop def (regalloc)
    x2 = 0; // FAKE: pre-loop def (regalloc)
    if (arg0 != arg1) {
        do {
            w0 = arg0->unk0;
            w1 = arg0->unk4;
            if ((w0 >> 24) == 0xD9) {
                if (arg0->unk4 == 0) {
                    w0 = ~w0 & 0xFFFFFF;
                    if ((w0 & 0x600) == 0x200) {
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
