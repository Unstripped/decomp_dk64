// func_807085D0 (src/global/10D2D0.c): Stage 1 m2c behavioral starter; 380-instruction display-list builder needs local views and float conversion cleanup.
f32 func_80612794(s16);                             /* extern */
void *func_8068C5A8(void *, s32, ?, ?, s32, s32, s32, s32, f32, f32, s32, f32); /* extern */
s32 func_80714464();                                /* extern */
extern ? D_1000118;
extern ? D_20000C0;
extern s32 D_8076A064;
extern s32 D_807FBB60;

void *func_807085D0(void *arg0, void *arg1, ? arg2, void *arg3) {
    f32 spE8;
    f32 spA4;
    f32 spA0;
    f32 sp94;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_ft1_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f64 temp_ft1;
    f64 var_ft1;
    s16 temp_s0_2;
    s16 var_s3;
    s32 temp_ft0;
    s32 temp_ft1_2;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 var_t5;
    s32 var_v1;
    s8 temp_v0_3;
    s8 var_s4;
    u16 temp_t6;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_v0;
    void *var_s2;

    temp_t6 = arg3->unk2E0;
    var_s4 = arg1->unk2FB;
    var_ft1 = (f64) temp_t6;
    if ((s32) temp_t6 < 0) {
        var_ft1 += 4294967296.0;
    }
    temp_s0 = ((arg1->unk2FC * 0x46) - 0x46) & 0xFF;
    temp_fs0 = (f32) (var_ft1 / 65535.0);
    if ((D_807FBB60 & 3) || (func_80714464() != 0)) {
        return arg0;
    }
    temp_s2 = arg0 + 8;
    arg0->unk4 = &D_1000118;
    arg0->unk0 = 0xDE000000;
    temp_s2_2 = temp_s2 + 8;
    arg0->unk8 = 0xFC119623;
    temp_s2->unk4 = 0xFF2FFFFF;
    temp_s2_3 = temp_s2_2 + 8;
    temp_s2->unk8 = 0xE200001C;
    temp_s2_2->unk4 = 0x504240;
    temp_s2_2->unk8 = 0xDA380007;
    temp_s2_3->unk4 = &D_20000C0;
    var_s2 = temp_s2_3 + 8;
    var_s3 = 0;
    if ((s32) arg1->unk2FC > 0) {
        var_ft1_2 = (f32) temp_s0;
        spA4 = temp_fs0 * 511.0f;
        if (temp_s0 < 0) {
            var_ft1_2 += 4294967296.0f;
        }
        spA0 = var_ft1_2;
        sp94 = (f32) (s16) (s32) ((f64) temp_fs0 * 200.0);
        do {
            temp_s0_2 = (var_s3 << 0xA) + (D_8076A064 * 0xC8);
            spE8 = (f32) (((f64) func_80612794(temp_s0_2) * 0.3) + 3.0);
            temp_fs2 = (f32) (((f64) func_80612794((s16) (temp_s0_2 + 0x800)) * 0.3) + 3.0);
            temp_fs0_2 = (f32) ((f64) func_80612794((s16) ((temp_s0_2 >> 1) + 0x200)) * 10.0);
            temp_ft1 = (f64) func_80612794(temp_s0_2) * 0.5;
            temp_s2_4 = var_s2 + 8;
            var_s2->unk0 = 0xE7000000;
            var_s2->unk4 = 0;
            var_s2->unk8 = 0xFA000000;
            if (spA4 > 80.0f) {
                var_fv0 = 80.0f;
            } else {
                var_fv0 = spA4;
            }
            if (M2C_ERROR(/* cfc1 */) & 0x78) {
                if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                    var_t5 = (s32) (var_fv0 - 2.1474836e9f) | 0x80000000;
                } else {
                    goto block_15;
                }
            } else {
                var_t5 = (s32) var_fv0;
                if (var_t5 < 0) {
block_15:
                    var_t5 = -1;
                }
            }
            temp_s2_4->unk4 = (s32) ((var_t5 & 0xFF) | ~0xFF);
            temp_fs1 = -temp_fs2;
            temp_ft0 = (s32) (sp94 + (f32) ((temp_ft1 + 0.5) * 30.0));
            temp_ft1_2 = (s32) (((f32) ((var_s3 * 0x8C) + 0x280) + temp_fs0_2) - spA0);
            temp_v0 = func_8068C5A8(temp_s2_4 + 8, 0x5D, 0, 2, 0x30, 0x2A, (s32) (s16) temp_ft1_2, (s32) (s16) temp_ft0, spE8, temp_fs1, 0, 0.0f);
            temp_v0->unk0 = 0xE7000000;
            temp_v0->unk4 = 0;
            temp_v0->unk8 = 0xFA000000;
            var_s2 = temp_v0 + 0x10;
            var_fv0_2 = spA4;
            if (spA4 > 255.0f) {
                var_fv0_2 = 255.0f;
            }
            temp_v0->unkC = (s32) (((u32) var_fv0_2 & 0xFF) | ~0xFF);
            if (var_s4 > 0) {
                temp_v0_2 = var_s4 - 1;
                var_v1 = 3;
                if (temp_v0_2 < 3) {
                    var_v1 = temp_v0_2;
                }
                var_s2 = func_8068C5A8(var_s2, (var_v1 + 0x5A) & 0xFFFF, 0, 2, 0x30, 0x2A, (s32) (s16) temp_ft1_2, (s32) (s16) temp_ft0, spE8, temp_fs1, 0, 0.0f);
            }
            temp_v0_3 = var_s4 - 4;
            if (temp_v0_3 < 0) {
                var_s4 = 0;
            } else {
                var_s4 = temp_v0_3;
            }
            var_s3 += 1;
        } while (var_s3 < (s32) arg1->unk2FC);
    }
    var_s2->unk0 = 0xE7000000;
    var_s2->unk4 = 0;
    return var_s2 + 8;
}
