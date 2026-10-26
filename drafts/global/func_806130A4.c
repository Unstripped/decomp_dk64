// func_806130A4 (src/global/17B90.c): stage 1: m2c starter; needs concrete Gfx command representation and constant expression matching
void func_806130A4(void *arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v1_2;
    u32 temp_v1;
    void *var_a0;

    var_a0 = arg0;
    if (var_a0 != arg1) {
        do {
            temp_v1 = var_a0->unk0;
            temp_t0 = var_a0->unk4;
            if ((temp_v1 >> 0x18) == 0xD9) {
                temp_v0 = temp_t0 & 0x600;
                if (temp_t0 == 0) {
                    temp_v1_2 = ~temp_v1 & 0xFFFFFF;
                    temp_a3 = temp_v1_2 & 0x600;
                    if (temp_a3 == 0x200) {
                        var_a0->unk0 = (u32) (~((temp_v1_2 | 0x400) & ~0x200) | 0xD9000000);
                    } else if (temp_a3 == 0x400) {
                        var_a0->unk0 = (u32) (~((temp_v1_2 | 0x200) & ~0x400) | 0xD9000000);
                    }
                } else {
                    temp_t7 = temp_t0 | 0x400;
                    if (temp_v0 == 0x200) {
                        var_a0->unk4 = temp_t7;
                        var_a0->unk4 = (s32) (temp_t7 & ~0x200);
                    } else {
                        temp_t6 = temp_t0 | 0x200;
                        if (temp_v0 == 0x400) {
                            var_a0->unk4 = temp_t6;
                            var_a0->unk4 = (s32) (temp_t6 & ~0x400);
                        }
                    }
                }
            }
            var_a0 += 8;
        } while (var_a0 != arg1);
    }
}
