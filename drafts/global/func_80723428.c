// func_80723428 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
? heapFree(s32, s32);                               /* extern */
extern ? D_807FDBF8;

void func_80723428(s32 arg0) {
    s32 *sp1C;
    s32 *temp_v0;

    if ((arg0 == -1) || (*(&D_807FDBF8 + (arg0 * 4)) != 0)) {
        temp_v0 = (arg0 * 4) + &D_807FDBF8;
        sp1C = temp_v0;
        heapFree(*temp_v0, arg0);
        *temp_v0 = 0;
    }
}
