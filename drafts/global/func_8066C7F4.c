// func_8066C7F4 (src/global/70FD0.c): Stage 5: frame 0x80 matches via volatile i + j; remaining: addu a1,t7,a1 (mine s3), lw t9/t0 temp (mine v0/t9) in the i<<2 index
void func_8066C7F4(s32 *arg0, u8 *arg1, f32 (*arg2)[4]) {
    volatile s32 i;
    s32 j;
    Mtx sp38;

    i = 1;
    memcpy(&sp38, arg0[0] + arg1, 0x40);
    j = i;
    if (arg0[1] != -1) {
        do {
            guMtxCatL(&sp38, (Mtx *)(arg0[j] + arg1), &sp38);
        } while (arg0[++j] != -1);
    }
    guMtxL2F(arg2, &sp38);
}
