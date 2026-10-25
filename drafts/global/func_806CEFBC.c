// func_806CEFBC (src/global/CEAE0.c): stage 5: analysis: target keeps sp44/sp40/sp3C/sp38 as UNCOLORED vars (stores kept, loads of arg0->unk8 not hoisted above the first store) with mid1/mid2 in pool temps f16/f18; ours forwards the mids in-block (copy-prop) so the stores vanish and loads hoist. Dead 'if (var) {}' tests split blocks and store ALL mids (v9A), not just mid3. Arrays/structs/array elements, assignments in call args, in-place lerp, address-of tricks, hill-climbed dead tests (best 29 vs 32 base) all fail; no source form found that stores only mid3.
s32 func_806CF2EC(s32 *, s32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
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
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    sp48 = (sp5C + sp58) / 2;
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C(arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
}
