// func_806CF138 (src/global/CEAE0.c): stage 6, 7 diff lines (full=7): ONLY sp4C (target f2, ours f14) and sp48 reload (target f14, ours f0) differ. Callee asinApprox (name from CEAE0.c). uopt -l 6 this unit: candidates 15 sp5C expr f0, 21 dz1 expr f2, 27 dx1 expr f14, 51 sp4C var -> takes f14 because it interferes with 21 (post-call sp40/sp44 occurrences of the same (sp64-sp60)/(sp74-sp70) expressions are linked to the pre-call ones). Tried without effect: deadsweep sweep with all spXX extras (660 variants), 2 random SA/hill-climbs 40k-120k iters with forms if(X)/!X/X&&X/X==0/X>0.0f/X<0.0f/1/X+1.0f/X*2.0f, *(&sp64) forms for either occurrence, first-part dz/dx as named locals (9), (f32)/*1.0f/+(-x) on the second-part subs.
typedef struct G05CbArg2 {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
} G05CbArg2;

f32 func_80611850(f32);
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

    func_806CF2EC(&sp30, &sp2C);
    actorGetNodePos(arg0->unk0, sp30, &sp70, &sp68, &sp60);
    if (sp68) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk0, sp2C, &sp74, &sp6C, &sp64);
    sp5C = sp6C - sp68;
    sp58 = sqrtf((sp64 - sp60) * (sp64 - sp60) + ((sp74 - sp70) * (sp74 - sp70) + sp5C * sp5C));
    sp54 = asinApprox(sp5C / sp58) * 57.29577637f;
    sp48 = func_80612794(arg0->unk0->unkE6) * 50.0f;
    if (!sp50) {} // FAKE: dead test steers uopt coloring
    sp4C = func_80612790(arg0->unk0->unkE6) * 50.0f;
    sp40 = sp74 - sp70;
    if (sp34) {} // FAKE: dead test steers uopt coloring
    sp44 = sp64 - sp60;
    sp3C = sp44 * sp4C + sp48 * sp40;
    sp38 = sqrtf(sp4C * sp4C + sp48 * sp48);
    sp34 = sqrtf(sp44 * sp44 + sp40 * sp40);
    if (sp4C) {} // FAKE: dead test steers uopt coloring
    func_8067AA58(arg0->unk0, arg0->unk4, sp54, 90.0 - func_80611850(sp3C / (sp38 * sp34)) * 57.29577637f);
}
