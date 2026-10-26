// func_80615328 (src/global/19A00.c): stage 2: m2c behavioral starter; remaining state view
// Stage 2: m2c behavioral starter; remaining diff: state view.
void func_80614F4C(s16 *arg0);
extern u8 *D_807F5AF0;

s32 func_80615328(void *arg0) {
    s16 sp1E;
    void *temp_v1;

    D_807F5AF0 += 1;
    func_80614F4C(&sp1E);
    temp_v1 = arg0->unk4;
    temp_v1->unk78 = (s32)(temp_v1->unk78 | sp1E);
    return 0;
}
