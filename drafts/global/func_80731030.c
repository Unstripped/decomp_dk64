// func_80731030 (src/global/135D30.c): single loop 'for (i=0;i<14;i++) D_807FDD90[i]=0' is the likely original (IDO unroll remainder = 2 stores + 12-byte x4 loop); gives 23 insns vs 22: remainder emits a second 'lui at' instead of sharing; explicit [0],[1] stores + loop hoists base into a reg (any 2 same-base stores hoist).
extern u8 D_807FDD90[14];

void func_80731030(void) {
    u32 i;

    for (i = 0; i < 14; i++) {
        D_807FDD90[i] = 0;
    }
}
