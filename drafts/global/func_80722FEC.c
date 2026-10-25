// func_80722FEC (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
extern ? D_807FDB90;

s32 func_80722FEC(s32 arg0) {
    if (*(&D_807FDB90 + ((arg0 & 0xFF) * 4)) != 0) {
        return 1;
    }
    return 0;
}
