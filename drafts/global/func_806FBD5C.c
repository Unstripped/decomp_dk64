// func_806FBD5C (src/global/100180.c): Stage 2 m2c draft: text-width loop; needs typed views and regalloc matching.
s32 func_806FB914(s16, u8 *);
s32 strlen(u8 *);
extern u8 *D_80754A18[];
extern u8 D_80754A34[];
extern u8 D_80754A39[];

s32 func_806FBD5C(s16 arg0, u8 *arg1) {
    u8 sp4B;
    s32 var_s0;
    s32 var_s0_2;
    u8 *var_s1;
    u8 temp_t3;
    u8 temp_t7;
    u8 *temp_s2;

    var_s0 = 0;
    if (arg0 & 0x80) {
        return D_80754A39[(s16)(arg0 ^ 0x80) * 6] * strlen(arg1);
    }
    temp_t3 = *arg1;
    var_s1 = arg1 + 1;
    sp4B = temp_t3;
    if (temp_t3 & 0xFF) {
        temp_s2 = &D_80754A34[arg0 * 6];
        do {
            if (sp4B == 0x20) {
                var_s0_2 = var_s0 + temp_s2[3];
            } else {
                func_806FB914(arg0, &sp4B);
                var_s0_2 = var_s0 + D_80754A18[arg0][sp4B * 4 + 2];
            }
            temp_t7 = *var_s1;
            var_s0 = var_s0_2 + temp_s2[4];
            var_s1 += 1;
            sp4B = temp_t7;
        } while (temp_t7 & 0xFF);
    }
    return var_s0;
}
