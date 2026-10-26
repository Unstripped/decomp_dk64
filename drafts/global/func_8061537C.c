// func_8061537C (src/global/19A00.c): stage 2: m2c behavioral starter; remaining state view/float compare register allocation
// Stage 2: m2c behavioral starter; remaining diff: state view/float compare register allocation.
void func_80614FD8(f32 *arg0, void *arg1);
extern u8 *D_807F5AF0;

s32 func_8061537C(void *arg0) {
    f32 sp1C;
    void *temp_v1;

    D_807F5AF0 += 1;
    func_80614FD8(&sp1C, arg0);
    if (sp1C < 0.0f) {
        sp1C = (f32)arg0->unk4->unk88;
    }
    arg0->unk4->unk80 = sp1C;
    temp_v1 = arg0->unk4;
    temp_v1->unk78 = (s32)(temp_v1->unk78 | 8);
    return 0;
}
