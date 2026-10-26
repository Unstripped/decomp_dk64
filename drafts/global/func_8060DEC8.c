// func_8060DEC8 (src/global/104F0.c): stage 3: complete serialisation loops compiled and fdiffed; target needs 0x48 frame with s0-s8 while candidate has 0x40 and different loop/local allocation.
extern u32 func_805FC98C(void);
extern void func_8060C648(s32, s32, s32, u8, u32);
extern u32 func_8060C724(u8);
extern s32 func_8071432C(void);
extern s32 func_80714394(void);
extern u8 D_807FC928, D_807FC950[];
void func_8060DEC8(void) {
    s32 i, j; u32 value, total; u8 *entry, *field;
    if ((D_807FC928 == 1) && ((func_80714394() != 0) || (func_8071432C() != 0))) {
        entry = D_807FC950; total = func_805FC98C(); value = func_8060C724(D_807467C8);
        if (total >= 0x400000U) total = -1U;
        func_8060C648(0xD, 0, 0, D_807467C8, 1); func_8060C648(0xE, 0, 0, D_807467C8, total);
        func_8060C648(0xC, 0, 0, D_807467C8, D_807FC950[0x2FC]);
        func_8060C648(0xF, 0, 0, D_807467C8, D_807467C8); func_8060C648(0x10, 0, 0, D_807467C8, value);
        i = 0; do {
            j = 0; field = entry; do { func_8060C648(j + 4, i, 0, D_807467C8, field[0]); j++; field++; } while (j != 5);
            func_8060C648(9, i, 0, D_807467C8, *(u16 *)(entry + 6));
            func_8060C648(0xA, i, 0, D_807467C8, entry[5] & 0x7F);
            func_8060C648(0xB, i, 0, D_807467C8, ((s32)entry[5] >> 7) & 1);
            j = 0; field = entry; do {
                func_8060C648(1, i, j, D_807467C8, *(u16 *)(field + 0xA));
                func_8060C648(2, i, j, D_807467C8, *(u16 *)(field + 0x26));
                func_8060C648(3, i, j, D_807467C8, *(u16 *)(field + 0x42)); j++; field += 2;
            } while (j != 8); i++; entry += 0x5E;
        } while (i != 5); func_8060B8F8(1);
    }
}
