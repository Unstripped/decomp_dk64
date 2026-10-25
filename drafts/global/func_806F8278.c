// func_806F8278 (src/global/FCCD0.c): m2c behavioural starter; 49-insn table summation requires local view struct.
extern s32 D_80754280;
extern ? D_807FC950;

void func_806F8278(s32 arg0) {
    s16 var_v0;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_a3;
    u16 temp_t6_2;
    u16 temp_t7;
    u16 temp_t8;
    void *temp_t1;
    void *temp_v1;
    void *var_t2;

    temp_t6 = arg0 & 0xFF;
    temp_v1 = (temp_t6 * 0x306) + &D_807FC950;
    var_v0 = 0;
    var_t2 = temp_v1;
    var_a3 = 0;
    do {
        temp_t1 = temp_v1 + (1 * 0x5E) + var_a3;
        temp_t6_2 = temp_t1->unkA0;
        temp_t7 = temp_t1->unkFE;
        temp_v0 = var_v0 + var_t2->unk42 + temp_t1->unk42;
        temp_t8 = temp_t1->unk15C;
        var_a3 += 2;
        var_t2 += 2;
        var_v0 = temp_v0 + temp_t6_2 + temp_t7 + temp_t8;
    } while (var_a3 < 0x1C);
    (D_80754280 + (temp_t6 * 0x2D0))->unk1B4 = var_v0;
}
