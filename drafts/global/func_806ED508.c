// func_806ED508 (src/global/EFDC0.c): Stage 3: selected-event s32 low-half attempt; frame and spill placement remain.
s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);

void func_806ED508(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    s16 sp26;
    s16 sp24;
    s32 temp_t6;

    temp_t6 = arg0 & 0xFFFF;
    switch (temp_t6) {
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
    sp18 = sp26;
    if (func_8073110C(sp26, 0) == 0) {
        if (sp1C == 0x81) {
            D_807FBB48->unkB8 = 0.0f;
        }
        func_8061CC40(NULL, sp24, 5);
        func_8073129C(*(s16 *)((u8 *)&sp18 + 2), 1, 0);
    }
}
