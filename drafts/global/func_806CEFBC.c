// func_806CEFBC (src/global/CEAE0.c): SmallA W6: stage 3 (count 76 vs target 73; stage 5 only by 15 diff lines). Kept the W4FpB body (draft score 15). Traced: target colours the 4 field loads f0/f2/f12/f14 first, then mid0 f16, mid1 f18, mid2 spilled (stored 0x44 but used from ring f4), u/v/w stored at def. Our 3 extra insns = 'swc1 f0,76; lwc1 f4,76' (mid0 var spilled) + 'swc1 f18,72' (mid1 stored) + 'lw a3,60(sp)' for mfc1, all from the two LATE dead tests after the call (sp48 / sp44 live across jal => forbidden all caller-saved => spilled var traffic); without them n=74 but full 29. Natural lerp forms (m-x)*t+x for all three (target uses that form on all 3; W4FpB's x+(m-x)*t / t*(m-x)+x were colouring hacks) cost only +2 (17). New: single-use mid vars are forward-substituted (mids interleave with lerps) unless a dead test sits between a mid def and the lerps; tests on mids AFTER the call keep them live across jal (bad); field dead tests before the calls give the loads lower candidate numbers so they colour first on adjsave ties. Tried: natural base + exhaustive 0-4 dead tests on sp4C/sp48/sp44 at 6 slots (576), tests on all 6 vars (5040 combos), expression-vs-var lerp uses (64), early field-init assignments, anneals (4 x 270 s, pen_n 6-8, floor 33). No variant reached n=73.
typedef struct SmallACbArg {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ Actor *unk8;
} SmallACbArg;

void func_8067A70C(s32, Actor *, f32, f32, f32, u8, u8);

void func_806CEFBC(SmallACbArg *arg0) {
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

    if (arg0->unk8->unk7C > 0.5f) {} // FAKE: dead test steers uopt coloring
    playerGetHoldNodeIndices(&sp34, &sp30);
    if (!arg0->unk8->unk80) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    if (arg0->unk8->unk84) {} // FAKE: dead test steers uopt coloring
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    sp48 = (sp5C + sp58) / 2;
    if (!sp4C) {} // FAKE: dead test steers uopt coloring
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = arg0->unk8->unk80 + (sp48 - arg0->unk8->unk80) * arg0->unk0;
    sp38 = arg0->unk0 * (sp44 - arg0->unk8->unk84) + arg0->unk8->unk84;
    func_8067A70C((s32)arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
    if (sp48 == 0.0f) { if (sp48) {} } // FAKE: dead test steers uopt coloring
    if (!sp44) {} // FAKE: dead test steers uopt coloring
}
