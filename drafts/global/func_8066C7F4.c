// func_8066C7F4 (src/global/70FD0.c): Stage 5 (frame 0x80, saved s0-s4, stack slots and all instructions match; 4 register-name diffs): target 'addu a1,t7,a1' (arg1 still in a1 before memcpy, s3 only afterwards) vs mine 'addu a1,t7,s3'; target 'lw t9,0x7c(sp); sll t0,t9,2; addu s0,a3,t0' vs mine v0/t9. Needs volatile i (FAKE) + j copy to get i memory-resident and arg0 split to a3; p-pointer form gives arg0 in s1 instead. Tried i*1, base copy, dead if on args, struct assign, guard-first reorder
void func_8066C7F4(s32 *arg0, u8 *arg1, f32 (*arg2)[4]) {
    volatile s32 i; // FAKE: volatile reproduces the memory-resident i (stack slot 0x7C, reloaded after memcpy)
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
