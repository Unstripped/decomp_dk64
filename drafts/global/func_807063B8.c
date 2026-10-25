// func_807063B8 (src/global/109660.c): stage 1 m2c candidate; needs concrete 0x18-byte record types and stack-copy reconstruction
void func_807063B8(void *arg0, u8 *arg1, s32 arg2, f32 arg3) {
    f32 *temp_t4;
    f32 *var_a0;
    f32 *var_a0_2;
    f32 *var_a3;
    f32 temp_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_t2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t9;
    s32 var_v1;
    u8 var_v0;
    void *temp_t0;
    void *temp_t0_2;
    void *temp_t1;
    void *temp_t1_2;
    void *temp_t3;
    void *temp_t3_2;
    void *temp_t7_3;
    void *temp_t9_2;
    void *var_a2;

    temp_s1 = arg2 & 0xFF;
    var_v0 = 0;
    var_v1 = 0;
    if ((s32) *arg1 > 0) {
        var_a0 = &sp48[0];
        var_a2 = arg0;
        do {
            var_v1 += 1;
            var_a0 += 0x18;
            var_a0->unk-18 = (s32) var_a2->unk0;
            temp_t7 = var_a2->unk4;
            var_a2 += 0x18;
            var_a0->unk-14 = temp_t7;
            var_a0->unk-10 = (s32) var_a2->unk-10;
            var_a0->unk-C = (s32) var_a2->unk-C;
            var_a0->unk-8 = (s32) var_a2->unk-8;
            var_a0->unk-4 = (s32) var_a2->unk-4;
        } while (var_v1 < (s32) *arg1);
        var_v1 = 0;
    }
    var_a0_2 = &sp48[0];
    if ((s32) *arg1 > 0) {
        temp_a2 = temp_s1 * 4;
        var_a3 = &var_a0_2[temp_s1];
        do {
            temp_fv0 = var_a3->unk0;
            temp_t0 = arg0 + (var_v0 * 0x18);
            temp_t1 = temp_t0 + temp_a2;
            if ((temp_fv0 < 0.0f) || (arg3 < var_a3->unk8)) {
                temp_t2 = temp_s1 ^ 1;
                temp_t9 = temp_t2 * 4;
                temp_t4 = &var_a0_2[temp_t2];
                if (temp_fv0 < 0.0f) {
                    var_fv1 = temp_fv0 + arg3;
                } else {
                    var_fv1 = temp_fv0;
                }
                temp_t1->unk0 = var_fv1;
                temp_t3 = temp_t0 + temp_t9;
                temp_t3->unk0 = (f32) temp_t4->unk0;
                temp_t1->unk8 = arg3;
                temp_t7_2 = (var_v0 + 1) & 0xFF;
                temp_t3->unk8 = (f32) temp_t4->unk8;
                temp_t1->unk10 = (f32) var_a3->unk10;
                temp_t3->unk10 = (f32) temp_t4->unk10;
                temp_t0_2 = arg0 + (temp_t7_2 * 0x18);
                temp_t1_2 = temp_t0_2 + temp_a2;
                if (var_a3->unk0 < 0.0f) {
                    var_fv1_2 = var_a3->unk8;
                } else {
                    var_fv1_2 = var_a3->unk8 - arg3;
                }
                temp_t1_2->unk0 = 0.0f;
                temp_t3_2 = temp_t0_2 + temp_t9;
                temp_t3_2->unk0 = (f32) temp_t4->unk0;
                temp_t1_2->unk8 = var_fv1_2;
                var_v0 = (temp_t7_2 + 1) & 0xFF;
                temp_t3_2->unk8 = (f32) temp_t4->unk8;
                temp_t1_2->unk10 = (f32) (temp_t1->unk10 + (arg3 - var_fv1));
                temp_t3_2->unk10 = (f32) temp_t4->unk10;
            } else {
                temp_t7_3 = arg0 + (var_v0 * 0x18);
                var_v0 = (var_v0 + 1) & 0xFF;
                temp_t9_2 = &sp48[0] + (var_v1 * 0x18);
                temp_t7_3->unk0 = (s32) temp_t9_2->unk0;
                temp_t7_3->unk4 = (s32) temp_t9_2->unk4;
                temp_t7_3->unk8 = (s32) temp_t9_2->unk8;
                temp_t7_3->unkC = (s32) temp_t9_2->unkC;
                temp_t7_3->unk10 = (s32) temp_t9_2->unk10;
                temp_t7_3->unk14 = (s32) temp_t9_2->unk14;
            }
            var_v1 += 1;
            var_a0_2 += 0x18;
            var_a3 += 0x18;
        } while (var_v1 < (s32) *arg1);
    }
    *arg1 = var_v0;
}
