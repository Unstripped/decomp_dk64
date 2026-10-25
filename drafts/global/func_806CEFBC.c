// func_806CEFBC (src/global/CEAE0.c): stage 5: asm-differ ~509 (was 3139): dead tests 'if (sp44) {} if (sp48) {}' AFTER the final call keep sp44 as candidate and the store at 0x44 (loads no longer hoist above it) but sp48 is stored too, sp4C is sunk to its use (mids computed order sp48,sp44,sp4C) and the colors differ. Target: mid1/mid2 colored f16/f18 with no stores, mid3 stored (uncolored), 4 loads f0/f2/f12/f14, lerps stored. Permuter (900s, best 170) reuses an address-taken var (sp64 = mid3, store kept) -> store kept without the extra tests, wrong slot; making sp44 address-taken via 'p = &sp44' also keeps its store but sinks mids and adds 8 frame bytes.
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
    if (sp44) {}
    if (sp48) {}
}
