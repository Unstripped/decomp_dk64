// func_8060DEC8 (src/global/104F0.c): stage 4: 0x48 frame, callee-saved set (s0-s7, fp, ra) and all loop instructions match; remaining diff is regalloc: s8/s7 swap between outer counter i and entry, s1/s0 swap in loop 2, and s2 caching for base[0x2FC].
extern u8 D_807FC928;
extern u8 D_807FC950[];
extern u8 D_807467C8;

extern u32 func_805FC98C(void);
extern void func_8060C648(s32, u8, u8, u8, s32);
extern u32 func_8060C724(u8);
extern s32 func_8071432C(void);
extern s32 func_80714394(void);
extern void eepromDispatchCommand(s32);

void func_8060DEC8(void) {
    u8 *entry;
    u8 *base;
    u32 total;
    u32 value;
    s32 i;
    s32 j;
    u8 *field;

    if (D_807FC928 == 1) {
        if (func_80714394() != 0 || func_8071432C() != 0) {
            base = D_807FC950;
            entry = base;
            total = func_805FC98C();
            value = func_8060C724(D_807467C8);
            if (total >= 0x400000U) {
                total = -1;
            }
            func_8060C648(0xD, 0, 0, D_807467C8, 1);
            func_8060C648(0xE, 0, 0, D_807467C8, total);
            func_8060C648(0xC, 0, 0, D_807467C8, base[0x2FC]);
            func_8060C648(0xF, 0, 0, D_807467C8, D_807467C8);
            func_8060C648(0x10, 0, 0, D_807467C8, value);
            i = 0;
            do {
                u8 row_idx = i;
                j = 0;
                field = entry;
                do {
                    func_8060C648(j + 4, row_idx, 0, D_807467C8, *field);
                    j++;
                    field++;
                } while (j != 5);
                func_8060C648(9, row_idx, 0, D_807467C8, *(u16 *)(entry + 6));
                func_8060C648(0xA, row_idx, 0, D_807467C8, entry[5] & 0x7F);
                func_8060C648(0xB, row_idx, 0, D_807467C8, ((s32)entry[5] >> 7) & 1);
                j = 0;
                field = entry;
                do {
                    func_8060C648(1, row_idx, (u8)j, D_807467C8, *(u16 *)(field + 0xA));
                    func_8060C648(2, row_idx, (u8)j, D_807467C8, *(u16 *)(field + 0x26));
                    func_8060C648(3, row_idx, (u8)j, D_807467C8, *(u16 *)(field + 0x42));
                    j++;
                    field += 2;
                } while (j != 8);
                i++;
                entry += 0x5E;
            } while (i != 5);
            eepromDispatchCommand(1);
        }
    }
}
