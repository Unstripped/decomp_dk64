// func_806FAFE4 (src/global/FCCD0.c): stage 2: semantic allocation and bitmask construction compiled; allocation-record aliasing and bit-test branch shapes differ
s32 *func_80610FE8(?, s32 **);                      /* extern */
? heapClearBlock(s32 *);                            /* extern */
extern void *D_80754280;
extern s32 *D_80754284;

void func_806FAFE4(void) {
    s32 **sp18;
    s32 **var_a2;
    s32 *temp_v0;
    s32 *temp_v0_11;
    s32 *temp_v0_13;
    s32 *temp_v0_15;
    s32 *temp_v0_3;
    s32 *temp_v0_5;
    s32 *temp_v0_7;
    s32 *temp_v0_9;
    s32 *var_v0;
    s32 temp_v0_10;
    s32 temp_v0_12;
    s32 temp_v0_14;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 var_a0;
    s32 var_a1;
    void *var_v1;

    var_a2 = &D_80754284;
    if (D_80754284 != NULL) {
        var_v0 = D_80754284;
        do {
            var_a2 = (s32 **) (var_v0 + 4);
            var_v0 = *var_a2;
        } while (var_v0 != NULL);
    }
    sp18 = var_a2;
    temp_v0 = func_80610FE8(8, var_a2);
    *var_a2 = temp_v0;
    heapClearBlock(temp_v0);
    temp_v0_2 = D_80754280->unk20;
    var_a0 = 3;
    var_a1 = 0x90;
    if (((temp_v0_2 == 1) || (temp_v0_2 == 2)) && (D_80754280->unk6 != 0)) {
        temp_v0_3 = *var_a2;
        *temp_v0_3 |= 1;
    }
    temp_v0_4 = D_80754280->unk50;
    if (((temp_v0_4 == 1) || (temp_v0_4 == 2)) && (D_80754280->unk36 != 0)) {
        temp_v0_5 = *var_a2;
        *temp_v0_5 |= 2;
    }
    temp_v0_6 = D_80754280->unk80;
    if (((temp_v0_6 == 1) || (temp_v0_6 == 2)) && (D_80754280->unk66 != 0)) {
        temp_v0_7 = *var_a2;
        *temp_v0_7 |= 4;
    }
    do {
        var_v1 = D_80754280 + var_a1;
        temp_v0_8 = var_v1->unk20;
        if (((temp_v0_8 == 1) || (temp_v0_8 == 2)) && (var_v1->unk6 != 0)) {
            temp_v0_9 = *var_a2;
            *temp_v0_9 |= 1 << var_a0;
            var_v1 = D_80754280 + var_a1;
        }
        temp_v0_10 = var_v1->unk50;
        if (((temp_v0_10 == 1) || (temp_v0_10 == 2)) && (var_v1->unk36 != 0)) {
            temp_v0_11 = *var_a2;
            *temp_v0_11 |= 1 << (var_a0 + 1);
            var_v1 = D_80754280 + var_a1;
        }
        temp_v0_12 = var_v1->unk80;
        if (((temp_v0_12 == 1) || (temp_v0_12 == 2)) && (var_v1->unk66 != 0)) {
            temp_v0_13 = *var_a2;
            *temp_v0_13 |= 1 << (var_a0 + 2);
            var_v1 = D_80754280 + var_a1;
        }
        temp_v0_14 = var_v1->unkB0;
        if (((temp_v0_14 == 1) || (temp_v0_14 == 2)) && (var_v1->unk96 != 0)) {
            temp_v0_15 = *var_a2;
            *temp_v0_15 |= 1 << (var_a0 + 3);
        }
        var_a0 += 4;
        var_a1 += 0xC0;
    } while (var_a0 != 0xF);
}
