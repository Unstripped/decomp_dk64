// func_806119A0 (src/global/166A0.c): stage 4: five+ fdiff variants (u64 direct, K&R helper/stack homes, seed local, pointer-to-seed, permuter). Best reproduces target prologue, frame, __ll_mul ABI and all stores; only post-call allocation differs (target t1 then and with at into v0, candidate adds directly in v0). Permuter -j2 --seconds 600 best score 230.
extern s32 D_80746A40;
extern u64 __ll_mul(u64, u64);

s32 func_806119A0(void) {
    u64 seed;
    s32 *seed_ptr;

    seed_ptr = &D_80746A40;
    seed = (u64)(u32)*seed_ptr;
    return D_80746A40 = ((u32)__ll_mul(seed, 0x01DF5E0DULL) + 1) & ~0;
}
