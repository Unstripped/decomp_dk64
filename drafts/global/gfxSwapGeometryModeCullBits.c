// gfxSwapGeometryModeCullBits (src/global/17B90.c): Ctrl17 2026-11-03: stage 4 park, score 15 unchanged (count/frame/callee-saved exact). Diff is colouring only: target srl is a COLOURED var candidate (v0, 'bne v0,t1' var left of const), w0=v1, ghost=a2, w1=a3, (w1&0x600)=v0, x1/x2 coloured v0; ours srl ring t6, w1=v0, E=a3, x1/x2 ring. -l 6: leaf, all candidates 'unconstrained' => first-fit in candidate-index (first-appearance) order; target needs srl cand coloured before w0/w1 and E before w1. Tried (all 15 or worse): op=w0>>24 var (+dead tests: forwarded, or coloured a3), switch(w0>>24), phantom 3rd/4th params, loop forms (for/while/do/user pointer p), pre-def order permutations of {op,w1,w0,x2,x1} (19k combos), single x var, u32* index forms, x/w0 in-place, p-local, dead tests on (w0>>24) via deadsweep, 3 annealer runs, permuter 540 s.
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
