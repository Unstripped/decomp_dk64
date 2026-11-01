// func_806CF138 (src/global/CEAE0.c): Player 2026-11-01: stage 6, 6 diff lines (unchanged). Root cause (trace): dz expr cand 21 (sp64-sp60) is ONE candidate for first-part (bb5) and second-part sp44 (bb13) pieces; its bb13 piece interferes with sp4C var (47) so 47 gets f14 instead of f2 and sp48 piece (101) f0 instead of f14. Tried: pointer-aliased second-part dz/dx reads (*(&sp60+1) etc, 25 combos, no change), 57k-iter hill-climb (hc3) with nested/else dead forms from park, permuter unusable (cpp fails on whole-TU base).
typedef struct G05CbArg2 {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
} G05CbArg2;

f32 acosApprox(f32);
f32 asinApprox(f32);
void func_8067AA58(Actor *, Actor *, f32, f32);

void func_806CF138(G05CbArg2 *arg0) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
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
    f32 sp34;
    s32 sp30;
    s32 sp2C;

    playerGetHoldNodeIndices(&sp30, &sp2C);
    actorGetNodePos(arg0->unk0, sp30, &sp70, &sp68, &sp60);
    if (sp68) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk0, sp2C, &sp74, &sp6C, &sp64);
    sp5C = sp6C - sp68;
    sp58 = sqrtf((sp64 - sp60) * (sp64 - sp60) + ((sp74 - sp70) * (sp74 - sp70) + sp5C * sp5C));
    sp54 = asinApprox(sp5C / sp58) * 57.29577637f;
    sp48 = func_80612794(arg0->unk0->unkE6) * 50.0f;
    sp4C = func_80612790(arg0->unk0->unkE6) * 50.0f;
    if (sp6C) {} // FAKE: dead test steers uopt coloring
    sp40 = sp74 - sp70;
    if (sp68) {} // FAKE: dead test steers uopt coloring
    sp44 = sp64 - sp60;
    sp3C = sp44 * sp4C + sp48 * sp40;
    sp38 = sqrtf(sp48 * sp48 + sp4C * sp4C);
    sp34 = sqrtf(sp44 * sp44 + sp40 * sp40);
    if (sp4C) {} // FAKE: dead test steers uopt coloring
    if (sp4C) {} // FAKE: dead test steers uopt coloring
    func_8067AA58(arg0->unk0, arg0->unk4, sp54, 90.0 - acosApprox(sp3C / (sp38 * sp34)) * 57.29577637f);
}
