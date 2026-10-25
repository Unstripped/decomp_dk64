// func_80714A9C (src/global/119370.c): Stage 6: size and operation order match; remaining register allocation differs for constants and multiply temporaries.
extern u8 D_8074450C;

void func_80714A9C(void) {
    s32 temp;

    D_807FDB0F = 0;
    D_807FDB10 = 1;
    D_807FDB14 = 0;
    D_807FDB18 = 0;
    D_807FDB1C = 1;
    D_807FDB1A = 0;
    D_807FDB1D = 0;
    D_807FDB28 = 0;
    temp = D_8074450C * 0xA;
    D_807FDB2C = 0;
    D_807FDB30 = 0;
    D_807FDB36 = 0;
    D_807FDB38 = -1;
    D_807FDB3C = temp;
    D_807FDB3E = temp;
    D_807FDB40 = D_8074450C * 0x135;
    D_807FDB42 = D_8074450C * 0xE5;
    D_807FDB3A = 0x258;
}
