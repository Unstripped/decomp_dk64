// func_806CF138 (src/global/CEAE0.c): stage 6: asm-differ score 45 (7 lines, was 200): ONLY sp4C (target f2, ours f14) and the sp48 reload (target f14, ours f0) differ; everything else matches. Dead tests that matter: if (sp68) {} between the two actorGetNodePos calls, if (!sp50) {} before sp4C, if (sp34) {} between sp40= and sp44= (reads of later-assigned vars extend live ranges), if (sp4C) {} at end; sp40= before sp44=. Found by random hill-climbing of dead-test positions. Cause (uopt -l 5): post-call 'sp44 = dz' is linked to the pre-call dz candidate so dz interferes with sp4C/sp48reload (bits 19 vs 51/101); target has dz unlinked like dx. Moving sp44= into the sp4C block (both before the test) gets sp4C=f2 but sp44 then colors f16 (test var sp34 takes f18). Address-of / pointer tricks no effect. NOTE: the score-45 form reads uninitialised sp50/sp34 in dead tests (UB); src parks a version without those two tests.
typedef struct G05CbArg2 {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
} G05CbArg2;

s32 func_806CF2EC(s32 *, s32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 sqrtf(f32);
f32 func_80611850(f32);
f32 func_806118FC(f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
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
    if (sp68) {}
    actorGetNodePos(arg0->unk0, sp2C, &sp74, &sp6C, &sp64);
    sp5C = sp6C - sp68;
    sp58 = sqrtf((sp64 - sp60) * (sp64 - sp60) + ((sp74 - sp70) * (sp74 - sp70) + sp5C * sp5C));
    sp54 = func_806118FC(sp5C / sp58) * 57.29577637f;
    sp48 = func_80612794(arg0->unk0->unkE6) * 50.0f;
    if (!sp50) {}
    sp4C = func_80612790(arg0->unk0->unkE6) * 50.0f;
    sp40 = sp74 - sp70;
    if (sp34) {}
    sp44 = sp64 - sp60;
    sp3C = sp44 * sp4C + sp48 * sp40;
    sp38 = sqrtf(sp4C * sp4C + sp48 * sp48);
    sp34 = sqrtf(sp44 * sp44 + sp40 * sp40);
    if (sp4C) {}
    func_8067AA58(arg0->unk0, arg0->unk4, sp54, 90.0 - func_80611850(sp3C / (sp38 * sp34)) * 57.29577637f);
}
