// func_806ECDD4 (src/global/EFDC0.c): Stage 4 branch scheduling mismatch; uopt traced and permuter setup attempted.
void func_806ECDD4(void) {
    s32 value;

    if (func_806EB400(D_807FBB48) != 0) {
        value = 1;
        if (D_807FBB68 & 2) {
            value = 0;
        } else {
            value = value;
        }
        func_806EEAF8((s16)value);
    }
}
