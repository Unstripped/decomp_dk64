// func_806119A0 (src/global/166A0.c): stage 3; five fdiff candidates (4-word/K&R/direct u64 helper and stack-home probes); direct helper has correct __ll_mul words and low v1 result, remaining frame 0x18 vs 0x20 plus argument-home scheduling.
extern s32 D_80746A40;
extern u64 __ll_mul(u64, u64);

s32 func_806119A0(void) {
    return D_80746A40 = ((u32) __ll_mul((u64) (u32) D_80746A40, 0x01DF5E0DULL) + 1) & ~0;
}
