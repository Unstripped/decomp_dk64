// gfxSwapGeometryModeCullBits (src/global/17B90.c): Revisit 7 (Ctrl 2026-11-03): stage 4 score 15 unchanged (60 insns, frame 0x18, s0-s3 exact; regs only: srl t6 vs v0 + bne operand order, w1 copy v0 vs a3, w1&0x600 mask a3 vs v0, x1 chain ring vs v0). Diagnosis: uopt colours unconstrained candidates first-fit in first-appearance order; target has srl/mask1/x1/x2 all v0 (a v0 web family), W0 v1, ghost a2 (explains 4 s-reg consts), W1 a3; the park has W1 v0 (first appearance via pre-loop fake), mask1 a3. Tried this unit, none < 15: single-case switch (identical code) and inner switches (24-34); local 2-word struct (15); op local for w0>>24 x pre-loop-def order permutations (24) x dead-test forms/positions (u32/s32/u8/s16: >=39, op takes a3 and W1 v0 = exact v0<->a3 swap of the target); x1/x2 pre-loop defs + dead tests everywhere (384 slots); dead tests on (w0>>24), arg0, arg1, fields (no change); shared temp across roles (grid of 1568 role merges, >=45); w1/w0 read via fields at each use site (>=15); loop forms do-break/do-while/while/for (identical or worse); 0xD9 spellings (U, cast, comma, swapped) identical (permuter 540s -j2: only (0,0xD9), same 15). Fake-free spelling loses count (56 vs 60): the pre-loop fakes pull a2/a3 out of the constant pool.
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
