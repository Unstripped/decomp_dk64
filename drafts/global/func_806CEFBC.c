// func_806CEFBC (src/global/CEAE0.c): Player 2026-11-01: stage 5, 18 diff lines (was 19; parked in src copy). Nested dead test 'if (sp48 == 0.0f) { if (sp48) {} }' at end + 'if (!sp44) {}' + sp4C test after sp48 def. Result: sp48 f18 right, mid3 f14/unk84 f16 (target unk84 f14, mids f16/f18), sp4C spilled f0->76(sp). Cause: uopt colours FP cands by adjsave then index: unk84 (idx 57, 3.0) must precede mids (idx 21/31/40, 3.0): need mids adj<3 or unk84>3 without block split. 11k random test-position/form combos (incl nested/else forms) + 29k hill-climb: floor 18.
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
    sp48 = (sp5C + sp58) / 2;
    if (sp4C == 0.0f) {} // FAKE: dead test steers uopt coloring
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C(arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
    if (sp48 == 0.0f) { if (sp48) {} } // FAKE: nested dead test steers uopt coloring (lower priority)
    if (!sp44) {} // FAKE: dead test steers uopt coloring
}
