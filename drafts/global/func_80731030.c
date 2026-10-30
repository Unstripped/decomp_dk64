// func_80731030 (src/global/135D30.c): stage 6: single loop 'for (i=0;i<14;i++) D_807FDD90[i]=0' unrolls to 2 peeled stores + 12-byte x4 loop; 23 insns vs 22 (15 target), remainder store scheduling difference.
extern u8 D_807FDD90[14];

void func_80731030(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        D_807FDD90[i] = 0;
    }
}
