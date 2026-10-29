// func_8060DC3C (src/global/104F0.c): stage 3: complete record import logic compiled and fdiffed; remaining frame is 0x40 vs target 0x48 and loop register/layout allocation differs.
extern void collectibleCountsClear(void);
extern void func_8060BA14(void);
extern u8 func_8060C6B8(s32, s32, s32, s32);
extern void func_8060C758(s32, s32);
extern void func_806C9AE0(void);
extern void healthRefill(s32);
extern u8 D_8074E77C, D_80750AC0, D_807FC928, D_807FC950[];
extern s32 D_80750AB0;
extern u8 D_807ECEA8[], D_807ED6A8[];
extern u16 D_807FC930[];
void func_8060DC3C(s32 arg0, s32 arg1) {
    s32 i, j, selector = arg0 & 0xFF; u8 *entry, *field; u16 *sum; s16 value;
    D_80750AC0 = 1; func_806C9AE0(); memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    D_807467C8 = selector; D_8074E77C = 0;
    if (func_8060C6B8(0xD, 0, 0, selector) == 0) func_8060C758(selector, 0);
    if (arg1 != 0) func_8060BA14();
    D_807FC928 = 0; D_807FC950[0x2FC] = func_8060C6B8(0xC, 0, 0, selector);
    healthRefill(0); collectibleCountsClear(); D_80750AB0 = func_8060C6B8(0xE, 0, 0, selector);
    i = 0; do {
        entry = D_807FC950 + (i * 0x5E); j = 0;
        do { entry[j] = func_8060C6B8(j + 4, i, 0, selector); j++; } while (j != 5);
        *(s16 *)(entry + 6) = func_8060C6B8(9, i, 0, selector);
        entry[5] = func_8060C6B8(0xA, i, 0, selector);
        if (func_8060C6B8(0xB, i, 0, selector) != 0) entry[5] |= 0x80;
        sum = D_807FC930; field = entry; j = 0;
        do {
            *(s16 *)(field + 0xA) = func_8060C6B8(1, i, j, selector);
            value = func_8060C6B8(2, i, j, selector); *(s16 *)(field + 0x26) = value; *sum += value;
            j++; field += 2; sum += 2;
            *(s16 *)(field + 0x40) = func_8060C6B8(3, i, j - 1, selector);
        } while (j != 8);
        i++;
    } while (i != 5);
    if (arg1 != 0) func_8060D7A8(); D_8074E77C = 0;
}
