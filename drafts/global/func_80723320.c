// func_80723320 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
extern ? D_807FDBF8;

void func_80723320(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg0 != -1) {
        temp_v0 = *(&D_807FDBF8 + (arg0 * 4));
        if (temp_v0 != NULL) {
            temp_v0->unk18 = arg1;
        }
    }
}
