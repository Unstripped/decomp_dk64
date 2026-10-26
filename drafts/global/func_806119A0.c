// func_806119A0 (src/global/166A0.c): stage 2: m2c starter; remaining diff not yet reduced
u64 __ll_mul(?, s32, ?, ?);                         /* extern */
extern s32 D_80746A40;

void func_806119A0(void) {
    s32 sp1C;
    s32 sp18;

    sp18 = 0;
    sp1C = D_80746A40;
    D_80746A40 = ((u32) __ll_mul(0, D_80746A40, 0, 0x01DF5E0D) + 1) & ~0;
}
