// func_8060B5C0 (src/global/10130.c): stage 5: 1 instruction schedule diff on last memcpy address formation
void *heapAlloc(s32);

void func_8060B5C0(s32 arg0) {
    s32 temp_s0;

    if (D_807463A8 == NULL) {
        D_807463A8 = heapAlloc(0x1C20);
    }
    D_807ECE98 = D_807463A8;
    if (D_807ECE90 == NULL) {
        D_807ECE90 = heapAlloc(0xE10);
    }
    D_807ECE94 = D_807ECE90;
    memcpy(&D_807463B0, (void *)arg0, 2);
    arg0 += 2;
    temp_s0 = D_807463B0 * 4;
    memcpy(D_807463A8, (void *)arg0, temp_s0);
    arg0 += temp_s0;
    memcpy(&D_807463A0, (void *)arg0, 2);
    arg0 += 2;
    temp_s0 = D_807463A0 * 2;
    memcpy(D_807ECE90, (void *)arg0, temp_s0);
    memcpy(&D_807ECE20, (void *)(arg0 + temp_s0), 0x70);
}
