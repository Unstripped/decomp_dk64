// func_80723C98 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
extern ? D_807FDBF8;

u8 func_80723C98(s32 arg0) {
    void *temp_v1;

    if ((arg0 == -1) || (temp_v1 = *(&D_807FDBF8 + (arg0 * 4)), (temp_v1 == NULL))) {
        return 0U;
    }
    return temp_v1->unk21;
}
