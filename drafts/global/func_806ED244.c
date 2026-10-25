// func_806ED244 (src/global/EFDC0.c): stage 1: m2c reconstruction of velocity update; needs player-state and camera-block views
? func_80614E78(void *, ?);                         /* extern */
? func_80614EBC(f32, void *, ?);                    /* extern */
? func_8072DB68(?, ?);                              /* extern */
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806ED244(void) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 var_ft2;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    f32 var_fv1_5;
    void *temp_v0;
    void *var_v1;

    var_v1 = D_807FD580->unk88;
    if (var_v1->unkB8 >= 0.0f) {
        func_8072DB68(0, 3);
        var_v1 = D_807FD580->unk88;
    }
    temp_v0 = (D_807FC924 + (D_807FC929 * 0x2F0))->unk2A0;
    if (temp_v0 != NULL) {
        temp_fv0 = temp_v0->unkB8;
        if (temp_fv0 != 0.0f) {
            if (temp_fv0 > 0.0f) {
                var_fv1 = temp_fv0;
            } else {
                var_fv1 = -temp_fv0;
            }
            var_ft2 = (f32) (2.0 * (f64) var_fv1);
            goto block_26;
        }
        temp_fv0_2 = var_v1->unkB8;
        if (temp_fv0_2 > 0.0f) {
            var_fv1_2 = temp_fv0_2;
        } else {
            var_fv1_2 = -temp_fv0_2;
        }
        if (var_fv1_2 < 50.0f) {
            var_v1->unkB8 = -50.0f;
        } else {
            if (temp_fv0_2 > 0.0f) {
                var_fv1_3 = temp_fv0_2;
            } else {
                var_fv1_3 = -temp_fv0_2;
            }
            var_v1->unkB8 = (f32) -var_fv1_3;
        }
    } else {
        temp_fv0_3 = var_v1->unkB8;
        if (temp_fv0_3 > 0.0f) {
            var_fv1_4 = temp_fv0_3;
        } else {
            var_fv1_4 = -temp_fv0_3;
        }
        if (var_fv1_4 < 50.0f) {
            var_v1->unkB8 = -50.0f;
        } else {
            if (temp_fv0_3 > 0.0f) {
                var_fv1_5 = temp_fv0_3;
            } else {
                var_fv1_5 = -temp_fv0_3;
            }
            var_ft2 = -var_fv1_5;
block_26:
            var_v1->unkB8 = var_ft2;
        }
    }
    func_80614EBC(0.0f, D_807FD580->unk88, 0x292);
    if (D_807FBB48->unk154 != 9) {
        func_80614E78(D_807FBB48, 0x83);
    }
}
