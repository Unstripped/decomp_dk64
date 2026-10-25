// func_806ED508 (src/global/EFDC0.c): stage 1: m2c reconstruction of map event selection; stack-local source at 0x1A remains unresolved
? func_8061CC40(?, s16, ?);                         /* extern */
s32 func_8073110C(s16, ?);                          /* extern */
? func_8073129C(s16, ?, ?);                         /* extern */
extern void *D_807FBB48;

void func_806ED508(s32 arg0) {
    s16 sp26;
    s16 sp24;
    s32 sp1C;
    s32 sp18;
    s32 temp_t6;

    temp_t6 = arg0 & 0xFFFF;
    switch (temp_t6) {                              /* irregular */
    case 0x12:
        sp26 = 0x16D;
        sp24 = 0x23;
        break;
    case 0x81:
        sp26 = 0x16E;
        sp24 = 0x24;
        break;
    }
    sp1C = temp_t6;
    sp18 = (s32) sp26;
    if (func_8073110C(sp26, 0) == 0) {
        if (temp_t6 == 0x81) {
            D_807FBB48->unkB8 = 0.0f;
        }
        func_8061CC40(0, sp24, 5);
        func_8073129C(unksp1A, 1, 0);
    }
}
