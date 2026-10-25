// func_806FB714 (src/global/100180.c): Stage 1 m2c draft saved; parser helper remains.
s32 func_806FB490(u8, s32, s32, s16, s32, u8 *, s32); /* extern */
s32 func_806FB914(?, u8 *, u8 *);                   /* extern */
? func_806FBB9C(s16);                               /* extern */
extern s32 D_807549FC;
extern s32 D_80754A18;
extern u8 D_80754A35;
extern s32 D_807FD7F0;

void func_806FB714(s32 arg0, s32 arg1, u8 *arg2) {
    u8 sp63;
    u8 sp61;
    s32 temp_s3;
    s32 var_a0;
    s32 var_s0;
    s32 var_s2;
    u8 *var_a2;
    u8 temp_t1;
    u8 temp_t6;
    void *temp_v1;
    void *temp_v1_2;

    sp61 = 0;
    temp_t6 = *arg2;
    var_s2 = arg0;
    var_a2 = arg2 + 1;
    sp63 = temp_t6;
    if (temp_t6 & 0xFF) {
        do {
            if (sp63 != 0x20) {
                var_s0 = 1;
                arg2 = var_a2;
                temp_s3 = func_806FB914(0, &sp63, var_a2) & 0xFF;
                var_a0 = D_80754A35 + 1;
                if (var_a0 >= 2) {
                    do {
                        temp_v1 = D_807549FC + var_s0;
                        if (((s32) sp63 >= (s32) temp_v1->unk-1) && ((s32) sp63 < (s32) temp_v1->unk0)) {
                            func_806FBB9C((s16) (var_s0 - 1));
                            temp_v1_2 = D_80754A18 + (sp63 * 4);
                            var_s2 = func_806FB490(temp_v1_2->unk2, var_s2, (D_807FD7F0 + (var_s0 * 4))->unk-4, temp_v1_2->unk0, temp_s3, &sp61, arg1 & 0xFF);
                            var_a0 = D_80754A35 + 1;
                        }
                        var_s0 += 1;
                    } while (var_s0 < var_a0);
                }
                var_a2 = arg2;
            } else {
                var_s2 += 3;
                sp61 += 6;
            }
            temp_t1 = *var_a2;
            var_a2 += 1;
            sp63 = temp_t1;
        } while (temp_t1 & 0xFF);
    }
}
