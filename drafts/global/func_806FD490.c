// func_806FD490 (src/global/100180.c): Stage 1 m2c draft saved; text renderer remains.
? func_806FB914(s16, u8 *);                         /* extern */
void *func_806FBEF0(void *, s32, ?);                /* extern */
extern ? D_2000000;
extern ? D_2000080;
extern ? D_2000180;
extern ? D_80754A18;
extern ? D_80754A34;

void *func_806FD490(void *arg0, s32 arg1, s16 arg2, s16 arg3, u8 *arg4) {
    u8 sp7F;
    s16 var_s0;
    s16 var_s6;
    s32 *temp_s1;
    s32 var_s7;
    u8 *var_s5;
    u8 temp_t5;
    u8 temp_t7;
    void *temp_a0;
    void *temp_a1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s3;
    void *temp_v1;
    void *var_s2;

    var_s6 = arg1 & 0xFF;
    var_s0 = arg2;
    var_s7 = 0;
    if (var_s6 & 0x80) {
        var_s7 = 1;
        var_s6 = (var_s6 ^ 0x80) & 0xFF;
    }
    temp_v1 = arg0 + 8;
    arg0->unk0 = 0xE7000000;
    arg0->unk4 = 0;
    temp_a0 = temp_v1 + 8;
    arg0->unk8 = 0xE3001201;
    temp_v1->unk4 = 0;
    temp_a1 = temp_a0 + 8;
    temp_v1->unk8 = 0xDA380007;
    temp_a0->unk4 = &D_2000080;
    temp_s2_2 = temp_a1 + 8;
    temp_a0->unk8 = 0xDA380003;
    temp_a1->unk4 = &D_2000180;
    temp_a1->unk8 = 0xE3000C00;
    temp_s2_2->unk4 = 0;
    var_s2 = func_806FBEF0(temp_s2_2 + 8, var_s6 & 0xFF, 1);
    temp_t7 = *arg4;
    var_s5 = arg4 + 1;
    sp7F = temp_t7;
    if (temp_t7 & 0xFF) {
        temp_s3 = (var_s6 * 6) + &D_80754A34;
        do {
            if (sp7F != 0x20) {
                temp_s1 = (var_s6 * 4) + &D_80754A18;
                func_806FB914(var_s6, &sp7F);
                temp_s2_3 = var_s2 + 8;
                var_s2->unk0 = (s32) ((((temp_s3->unk2 + arg3) * 4) & 0xFFF) | 0xE4000000 | ((((var_s0 + (*temp_s1 + (sp7F * 4))->unk2) * 4) & 0xFFF) << 0xC));
                var_s2->unk4 = (s32) ((((var_s0 * 4) & 0xFFF) << 0xC) | ((arg3 * 4) & 0xFFF));
                var_s2->unk8 = 0xE1000000;
                temp_s2_4 = temp_s2_3 + 8;
                temp_s2_3->unk4 = (s32) (*(*temp_s1 + (sp7F * 4)) << 0x15);
                temp_s2_3->unk8 = 0xF1000000;
                temp_s2_4->unk4 = 0x04000400;
                var_s2 = temp_s2_4 + 8;
                if (var_s7 != 0) {
                    var_s0 += temp_s3->unk5;
                } else {
                    var_s0 = var_s0 + (*temp_s1 + (sp7F * 4))->unk2 + temp_s3->unk4;
                }
            } else if (var_s7 != 0) {
                var_s0 += temp_s3->unk5;
            } else {
                var_s0 += temp_s3->unk3;
            }
            temp_t5 = *var_s5;
            var_s5 += 1;
            sp7F = temp_t5;
        } while (temp_t5 & 0xFF);
    }
    temp_s2_5 = var_s2 + 8;
    var_s2->unk0 = 0xE7000000;
    var_s2->unk4 = 0;
    temp_s2 = temp_s2_5 + 8;
    var_s2->unk8 = 0xDA380007;
    temp_s2_5->unk4 = &D_2000000;
    temp_s2->unk4 = 0x80000;
    temp_s2_5->unk8 = 0xE3000C00;
    return temp_s2 + 8;
}
