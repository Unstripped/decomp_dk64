// func_806CF138 (src/global/CEAE0.c): W2Int 2026-11-03: stage 6 score 6 unchanged. Subset scan of the 5 FAKEs: only 2 are needed for score 6 (`if (sp6C) {}` + the second `if (sp68) {}`, mask 0b110; count 125 instead of 126: swc1 sp4C store missing), all 5 give count-exact 6. Diagnosis (-l5/-l6): target sp4C=f2 / sp48 piece=f14 vs ours f14/f0; cand 47 (sp4C) interferes with cand 21 (sp64-sp60, live bb5 AND bb13: loads of address-taken sp64/sp60 are isvar M candidates that survive the calls, so the later `sp44 = sp64 - sp60` re-uses cand 21's piece) -> f2 forbidden for sp4C. The target needs no such cross-call CSE (sp4C f2 shares f2 with the early dz): i.e. loads of sp64/sp60 are killed by a call in the original. Tried new: three 2-element array locals f32 X[2],Y[2],Z[2] (&X[1] = sp74 layout, 12 declaration orders/FAKEs on/off: 61-73, code shape changes: load order and +1..2 insns, so not the original), 240s dead-test annealer (FAKE insert/delete/move/retarget over all sp locals): no gain, permuter setup does not compile (K&R decls in the file head). Untried: a spelling that makes uopt treat sp60/sp64 loads as killed by the intervening calls without changing code.
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
