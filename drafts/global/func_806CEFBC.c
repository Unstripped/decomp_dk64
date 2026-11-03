// func_806CEFBC (src/global/CEAE0.c): from .scratch/W3CountB/func_806CEFBC_best.c
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
