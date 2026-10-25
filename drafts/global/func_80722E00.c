// func_80722E00 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
? assetFreeBuffer(s32, ?, ?);                       /* extern */
s32 func_8066B0F8(?, s32, ?, ?);                    /* extern */
? func_80722E48(s32);                               /* extern */

void func_80722E00(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = func_8066B0F8(0xF, arg0, 1, 1);
    sp1C = temp_v0;
    func_80722E48(temp_v0);
    assetFreeBuffer(sp1C, 0x47, 0x27);
}
