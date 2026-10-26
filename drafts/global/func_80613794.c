// func_80613794 (src/global/17B90.c): stage 1: m2c starter recovered from local asm; requires typed controller/cache views and C compile
? assetFreeBuffer(u32, ?, ?);                       /* extern */
extern ? D_807FB630;
extern ? D_807FB7B0;
extern u16 D_807FBB30;

void func_80613794(void *arg0, s32 arg1) {
    ? *var_s1;
    s32 temp_t6;
    u16 temp_t0;
    u16 temp_t4;
    u32 temp_v0;
    void **temp_s2;
    void *temp_v0_2;
    void *var_s0;
    void *var_s6;

    temp_t6 = arg1 & 0xFF;
    switch (temp_t6) {                              /* irregular */
    default:
        var_s6 = sp3C;
        break;
    case 0:
        var_s6 = arg0->unk0;
        arg0->unk0 = NULL;
        break;
    case 1:
        var_s6 = arg0->unk4C;
        arg0->unk4C = NULL;
        break;
    case 2:
        var_s6 = arg0->unk50;
        arg0->unk50 = NULL;
        break;
    }
    if (var_s6 != NULL) {
        var_s1 = &D_807FB630;
loop_9:
        if (var_s6 != var_s1->unk4) {
            var_s1 += 0xC;
            if (var_s1 != &D_807FB7B0) {
                goto loop_9;
            }
        }
        if (var_s1 != &D_807FB7B0) {
            temp_t0 = var_s1->unk2 - 1;
            var_s1->unk2 = temp_t0;
            if (!(temp_t0 & 0xFFFF)) {
                temp_s2 = var_s6->unk4;
                var_s0 = *temp_s2;
                if (var_s0 != temp_s2) {
                    do {
                        if (((u32) var_s0->unk0 >> 0x18) == 0xFD) {
                            temp_v0 = var_s0->unk4;
                            if ((temp_v0 >= 0x80000000U) && (temp_v0 < 0xA0000000U)) {
                                assetFreeBuffer(temp_v0, 0x270, 0x15);
                            }
                        }
                        var_s0 += 8;
                    } while (var_s0 != temp_s2);
                }
                temp_t4 = D_807FBB30 - 1;
                temp_v0_2 = ((temp_t4 & 0xFFFF) * 0xC) + &D_807FB630;
                D_807FBB30 = temp_t4;
                var_s1->unk0 = (u16) temp_v0_2->unk0;
                var_s1->unk4 = (s32) temp_v0_2->unk4;
                var_s1->unk8 = (u8) temp_v0_2->unk8;
                var_s1->unk2 = (u16) temp_v0_2->unk2;
                temp_v0_2->unk0 = 0U;
                temp_v0_2->unk4 = 0;
                temp_v0_2->unk8 = 0U;
                temp_v0_2->unk2 = 0U;
                assetFreeBuffer((u32) var_s6, 0x281, 0x15);
            }
        }
    }
}
