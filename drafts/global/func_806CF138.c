// func_806CF138 (src/global/CEAE0.c): PlrCommon revisit3: stage 6, 6 diff lines (was 7). sp38 = sqrtf(sp48*sp48 + sp4C*sp4C) (swapped commutative operands; no code change but frees nothing) + dead tests sp6C/sp68 after the sp4C/sp40 stmts and sp4C twice. ONLY remaining diff: lerp-ish sp4C mul result in f14 (target f2) and sp48 reload f0 (target f14): cand 51 sp4C var takes f27(f14) because it interferes with 21 dz1 expr. Tried: ~30k variants: beam of dead tests (vars+arg0 exprs, forms if(x)/x==0/!x/x<0/x+1/x&&x), all 6 statement perms of the three sub stmts x sqrt operand spellings x trig order (3456), 12288-grid of commutative operand spellings, sp5C/sp44/sp40 early (-> 11 lines), array/deref forms. Stuck at 6-7.
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

    func_806CF2EC(&sp30, &sp2C);
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
