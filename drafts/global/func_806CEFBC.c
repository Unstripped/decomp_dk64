// func_806CEFBC (src/global/CEAE0.c): PlrCommon revisit3: stage 5, 19 diff lines (was 20), shape 3. No uninitialised-read tests now (old draft had pre-def 'if (sp48 < 0.0f)/sp40/sp38/sp3C'): only post-def sp4C/sp48/sp44 tests + 'if (arg0->unk8->unk7C)/unk80 {}' after the node-pos calls. Remaining diff: target mid1/mid2 (sp4C/sp48) colored f16/f18 w/o stores, mid3 uncolored (f4 temp, stored 0x44); ours mid1 f0 + store/reload at 0x4C and mid3 f2/f12 stored. Tried: 5-level legit-only dead-test beams (3 depth, ~25k variants, vars + arg0 field exprs), statement order perms (all 90 valid orders), lerp/mid operand spellings (512), decl-order perms (720), pre-def tests removal. Without any test 31-33.
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

    func_806CF2EC(&sp34, &sp30);
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
