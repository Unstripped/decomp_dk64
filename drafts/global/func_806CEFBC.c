// func_806CEFBC (src/global/CEAE0.c): stage 5, full diff 20 lines (was 25 by deadsweep score; 509 by asm-differ): target = loads t,7C,80,84 colored f0,f2,f12,f14, mid1/mid2 VARIABLES sp4C/sp48 colored f16/f18 with no stores, mid3 uncolored (stored 0x44, value in f4 temp), lerps stored. Ours: mid1 EXPRESSION candidate (f0) stored 0x4C + reloaded, mid3 expression candidate colored f2 + stored. Cause (uopt -l 6): only 6 FP colors f0,f2,f12,f14,f16,f18; target has 6 higher-priority candidates (4 loads + sp4C var + sp48 var) so mid3 gets none; ours has mid1/mid3 as expression candidates outranking the loads. A pre-def dead test 'if (spXX < 0.0f)' blocks copy-prop and turns the var into the candidate (sp48 works that way; sp4C only gets there with the post-def test removed, then mid3 expr still takes a color and sp4C var is the 7th). Hill-climb/SA (130k iters, 3 basins) stalls at 20-21; adding a sp44 pre-def test makes arg0 lose s0 (-ve save).
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

    if (sp48 < 0.0f) {} // FAKE: dead test steers uopt coloring
    if (sp40 + 1.0f) {} // FAKE: dead test steers uopt coloring
    if (sp38 < 0.0f) {} // FAKE: dead test steers uopt coloring
    func_806CF2EC(&sp34, &sp30);
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    if (sp38 == 0.0f) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    if (sp4C == 0.0f) {} // FAKE: dead test steers uopt coloring
    sp48 = (sp5C + sp58) / 2;
    if (sp3C == 0) {} // FAKE: dead test steers uopt coloring
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C(arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
    if (sp44) {} // FAKE: dead test steers uopt coloring
}
