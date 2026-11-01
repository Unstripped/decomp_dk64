// func_806CEFBC (src/global/CEAE0.c): W2FP: stage 5, 19 diff lines (unchanged best). Analysis: target = unk0 f0, 124/128/132 loads f2/f12/f14 coloured BEFORE mid1/mid2 (f16/f18); mid3 + sp40/3C/38 uncoloured (stores kept), one straight-line block after call 2. Colour order = priority then candidate id: load ids come from first appearance, dead tests at the top make 7C/80 ids low but a third test for unk84 before calls costs +8 frame (3 loads spilled across 2 calls), after call 2 it splits the block and its priority drops 3.0->2.0. Plain (no tests) = 43/shape 28 (mids -ve save, sp40/sp3C coloured instead); 29 with one deadsweep test; hill-climb from plain 28k compiles -> 28; 1500-variant grid of unk7C/80/84 test placements x tails x mid tests best 19 (= current). Tried also: local pointer pp=arg0->unk8 (57+), register decls, pre/post tests on every sp var.
typedef struct G05CbArg {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ Actor *unk8;
} G05CbArg;

void func_8067A70C(Actor *, Actor *, f32, f32, f32, s32, s32);

void func_806CEFBC(G05CbArg *arg0) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp34;
    s32 sp30;

    playerGetHoldNodeIndices(&sp34, &sp30);
    if (arg0->unk8->unk7C) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    if (arg0->unk8->unk80) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    if (sp4C == 0.0f) {} // FAKE: dead test steers uopt coloring
    sp48 = (sp5C + sp58) / 2;
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C(arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
    if (sp48) {} // FAKE: dead test steers uopt coloring
    if (sp44) {} // FAKE: dead test steers uopt coloring
}
