// func_8073BB10 (src/global/140600.c): stage 3: target 0x40 frame and all stack slots/operation order match; remaining FP temporary-register allocation and own-data relocations
void func_8073BB10(f32 arg0, f32 arg1, f32 arg2, LpfNMBiquad *arg3, LpfNMBiquad *arg4) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    if ((arg0 - 200.0f) <= arg1) {
        arg1 = arg0 - 200.0f;
    }
    sp3C = func_80611BB4(arg1 * 3.141592741f, arg0);
    sp38 = sp3C * sp3C;
    sp34 = (sp3C * 1.414213657f) / arg2;
    arg3->unk0 = sp38 / (1.0f + sp38 + sp34);
    arg3->unk4 = arg3->unk0 * 2.0f;
    arg3->unk8 = arg3->unk0;
    arg4->unk4 = ((sp38 - 1.0f) * 2.0f) / (1.0f + sp38 + sp34);
    arg4->unk8 = ((1.0f + sp38) - sp34) / (1.0f + sp38 + sp34);
}
