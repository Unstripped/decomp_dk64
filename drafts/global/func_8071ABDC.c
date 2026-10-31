// func_8071ABDC (src/global/11BC10.c): stage 6: 213 insns frame 0xC0, stack layout (sp24 0x24, sp2C 0x2C, sp30, sp38) and all control flow match; 11-line FP regalloc diff only: first const/cvt pair f4/f18 vs f18/f0 then shifted ring f8/f6/f16 vs f4/f8/f6. needs unused 128-byte buffer + (1.0f+1.0f) + if (sp34 == 0) {} fakes
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Q11Ba_AbdcMotion;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[2];
    s16 unk34E;
    u8 pad350[0xC];
    s32 unk35C;
    u8 pad360[0xD];
    u8 unk36D;
    u8 pad36E[0x16];
    Q11Ba_AbdcMotion *unk384;
} Q11Ba_ActorABDC;


void func_8071ABDC(Q11Ba_ActorABDC *arg0, s8 *arg1) {
    f32 sp80[4][4]; // FAKE: unused 128-byte buffer steers frame size
    f32 sp40[4][4]; // FAKE: unused 128-byte buffer steers frame size
    f32 pad3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s16 pad2E;
    s16 sp2C;
    s32 pad28;
    f32 sp24;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = heapAlloc(0x10);
        sp2C = (s16) ((arg0->unk35C >> 16) & 0xFF);
        if (sp2C == 0) {
            arg0->unk384->unk0 = (f32) (((f64) (f32) ((randomLcgNext() / 10000U) % 100U) / 20.0) - 2.5);
        } else {
            arg0->unk384->unk0 = (f32) (((f64) (f32) ((randomLcgNext() / 10000U) % 100U) / 10.0) - 2.5);
        }
        sp24 = (f32) ((arg0->unk35C & 0xFFFF) * 30) * 0.017453292f;
        sp38 = (f32) ((f64) sinApprox(sp24) * 2.5);
        sp34 = (f32) ((f64) cosApprox(sp24) * 2.5);
        if (sp34 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        arg0->unk384->unk4 = sp38;
        arg0->unk384->unk8 = sp34;
        if (sp2C != 1) {
            if (sp2C == 2) {
                arg0->unk384->unk4 = arg0->unk384->unk4 * 4.0f;
                arg0->unk384->unk8 = arg0->unk384->unk8 * 4.0f;
            }
        } else {
            arg0->unk384->unk4 = arg0->unk384->unk4 * (1.0f + 1.0f); // FAKE: (1.0f + 1.0f) keeps mul.s (x * 2.0f becomes add.s)
            arg0->unk384->unk8 = arg0->unk384->unk8 * (1.0f + 1.0f); // FAKE: (1.0f + 1.0f) keeps mul.s (x * 2.0f becomes add.s)
        }
        sp30 = arg0->unk344;
        if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp30) != 0) {
            arg0->unk384->unkC = sp30;
        } else {
            arg0->unk384->unkC = 0.0f;
        }
    }
    if (arg0->unk34E >= 9) {
        arg0->unk384->unk0 = (f32) ((f64) arg0->unk384->unk0 + -0.63);
        arg0->unk384->unk4 = (f32) ((f64) arg0->unk384->unk4 * 0.9);
        arg0->unk384->unk8 = (f32) ((f64) arg0->unk384->unk8 * 0.9);
    }
    if (arg0->unk34E >= ((arg0->unk35C >> 24) & 0xFF)) {
        if (arg0->unk36D >= 0x3C) {
            arg0->unk36D -= 0x3C;
        } else {
            arg0->unk36D = 0;
        }
    }
    arg0->unk340 += arg0->unk384->unk4;
    arg0->unk348 += arg0->unk384->unk8;
    arg0->unk344 += arg0->unk384->unk0;
    if (arg0->unk344 < arg0->unk384->unkC) {
        *arg1 = 1;
    }
}
