// func_8060DC3C (src/global/104F0.c): stage 4: 0x48 frame, callee-saved set (s0-s7, fp, ra) and spilled loop counter i at sp+0x40 match; remaining diff is regalloc: s0 vs s5 for arg0/selector, and loop pointer/counter register swaps.
extern void collectibleCountsClear(void);
extern void func_8060BA14(void);
extern s32 func_8060C6B8(s32, u8, u8, u8);
extern void func_8060C758(s32, s32);
extern void func_806C9AE0(void);
extern void healthRefill(s32);
extern void func_8060D7A8(void);
extern u8 D_8074E77C;
extern u8 D_80750AC0;
extern u8 D_807FC928;
extern u8 D_807FC950[];
extern u8 D_807467C8;
extern s32 D_80750AB0;
extern u8 D_807ECEA8[], D_807ED6A8[];
extern u16 D_807FC930[];

void func_8060DC3C(s32 arg0, s32 arg1) {
    s32 i;
    u8 selector;
    u8 *base;
    u8 *entry;
    u8 *field;
    u16 *sum;
    s32 j;
    s32 value;

    base = D_807FC950;
    selector = arg0;
    entry = base;
    D_80750AC0 = 1;
    func_806C9AE0();
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    D_807467C8 = selector;
    D_8074E77C = 0;
    if (func_8060C6B8(0xD, 0, 0, selector) == 0) {
        func_8060C758(selector, 0);
    }
    if (arg1 != 0) {
        func_8060BA14();
    }
    D_807FC928 = 0;
    base[0x2FC] = func_8060C6B8(0xC, 0, 0, selector);
    healthRefill(0);
    collectibleCountsClear();
    D_80750AB0 = func_8060C6B8(0xE, 0, 0, selector);
    i = 0;
    do {
        j = 0;
        field = entry;
        do {
            *field = func_8060C6B8(j + 4, i, 0, selector);
            j++;
            field++;
        } while (j != 5);
        *(s16 *)(entry + 6) = func_8060C6B8(9, i, 0, selector);
        entry[5] = func_8060C6B8(0xA, i, 0, selector);
        if (func_8060C6B8(0xB, i, 0, selector) != 0) {
            entry[5] |= 0x80;
        }
        sum = D_807FC930;
        field = entry;
        j = 0;
        do {
            *(s16 *)(field + 0xA) = func_8060C6B8(1, i, j, selector);
            value = func_8060C6B8(2, i, j, selector);
            *(s16 *)(field + 0x26) = value;
            *sum += value;
            *(s16 *)(field + 0x42) = func_8060C6B8(3, i, j, selector);
            j++;
            field += 2;
            sum++;
        } while (j != 8);
        i++;
        entry += 0x5E;
    } while (i != 5);
    if (arg1 != 0) {
        func_8060D7A8();
    }
    D_8074E77C = 0;
}
