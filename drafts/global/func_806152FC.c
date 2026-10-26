// func_806152FC (src/global/19A00.c): stage 2: m2c behavioral starter; remaining state view
// Stage 2: m2c behavioral starter; remaining diff: state view.
extern u8 *D_807F5AF0;

s32 func_806152FC(void *arg0) {
    void *temp_v1;

    D_807F5AF0 += 1;
    temp_v1 = arg0->unk4;
    temp_v1->unk78 = (s32)(temp_v1->unk78 | 4);
    return 0;
}
