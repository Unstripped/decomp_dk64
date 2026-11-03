// gfxSwapGeometryModeCullBits (src/global/17B90.c): W2IntA: stage 4 (frame 0x18 + s0-s3 + 60 insns exact), score 15 (was 22), regs only. Annealer (dead tests, guarded) added 'if ((w1 & 0x600) == 0x200) {}' before the loop + 'if (w1 == 0) {}' in the arm: field-load expr now t0 and w0 v1 as target. Remaining: target (w0>>24) is a coloured cand in v0 (ours ring t6, bne operand order flipped), w1 var copy a3 (ours v0), w1&0x600 mask v0 (ours a3). Tried: u32 op local for (w0>>24) (forward-substituted = same 15; with dead test 39), 15k+7k anneal evals.
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
