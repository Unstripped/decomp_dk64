// func_807232EC (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
extern ? D_807FDBF8;

void func_807232EC(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg0 != -1) {
        temp_v0 = *(&D_807FDBF8 + (arg0 * 4));
        if (temp_v0 != NULL) {
            temp_v0->unk15 = (s8) (arg1 & 0xFF);
        }
    }
}
