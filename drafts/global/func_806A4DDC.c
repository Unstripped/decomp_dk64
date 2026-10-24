// func_806A4DDC (src/global/A8400.c): stage 1: unedited m2c starter from the base asm (never attempted this round)
? func_806A3DA0(void *, void *, f32, f32, void *);  /* extern */
? func_806A4B84(f32, void *, void *, void *, s32, u8 *); /* extern */
? func_8070D9AC(f32, void *, u8, void *, void *);   /* extern */
? func_8070E808(void *, s32);                       /* extern */
extern void *D_807FC924;

void func_806A4DDC(void *arg0) {
    u8 sp103;
    f32 sp50;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_ft4;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 temp_fv1_5;
    f32 var_fs1;
    f32 var_fv0;
    f64 temp_fv0;
    f64 temp_fv0_5;
    f64 temp_fv1;
    s32 var_s0;
    u8 temp_v1;
    u8 var_v0;
    void *temp_a0;
    void *temp_a3;
    void *temp_s2;
    void *var_s1;

    temp_s2 = arg0->unk174;
    var_s1 = temp_s2->unkC;
    sp103 = 0;
    temp_fs0 = temp_s2->unk20;
    var_fv0 = (f32) ((f64) (1.0f - temp_fs0) * 1.4705882352941178);
    if (var_fv0 > 1.0f) {
        var_fv0 = 1.0f;
    }
    temp_s2->unk40 = var_fv0;
    func_806A3DA0(arg0 + 0x7C, arg0 + 0x80, temp_fs0, var_fv0, temp_s2);
    temp_fs0_2 = temp_s2->unk20;
    temp_fv0 = (f64) (temp_fs0_2 * 136.8f) * 0.5;
    temp_s2->unk44 = (f32) ((f64) arg0->unk7C - temp_fv0);
    temp_ft4 = temp_s2->unk44;
    temp_fv1 = (f64) (temp_fs0_2 * 79.799995f) * 0.5;
    temp_s2->unk48 = (f32) ((f64) arg0->unk80 - temp_fv1);
    temp_s2->unk4C = (f32) ((f64) arg0->unk7C + temp_fv0);
    temp_s2->unk50 = (f32) ((f64) arg0->unk80 + temp_fv1);
    temp_fa1 = (f32) D_807FC924->unk270;
    if (temp_fa1 < temp_ft4) {
        temp_s2->unk44 = temp_ft4;
    } else {
        temp_s2->unk44 = temp_fa1;
    }
    temp_fv1_2 = temp_s2->unk48;
    temp_fv0_2 = (f32) D_807FC924->unk272;
    if (temp_fv0_2 < temp_fv1_2) {
        temp_s2->unk48 = temp_fv1_2;
    } else {
        temp_s2->unk48 = temp_fv0_2;
    }
    temp_fv0_3 = temp_s2->unk4C;
    temp_fv1_3 = (f32) D_807FC924->unk274;
    if (temp_fv0_3 < temp_fv1_3) {
        temp_s2->unk4C = temp_fv0_3;
    } else {
        temp_s2->unk4C = temp_fv1_3;
    }
    temp_fv0_4 = temp_s2->unk50;
    temp_fv1_4 = (f32) D_807FC924->unk276;
    if (temp_fv0_4 < temp_fv1_4) {
        temp_s2->unk50 = temp_fv0_4;
    } else {
        temp_s2->unk50 = temp_fv1_4;
    }
    var_fs1 = temp_s2->unk14;
    var_s0 = 0;
    if (((s32) temp_s2->unk10 >= 0) && (var_s1 != NULL) && (sp103 == 0)) {
loop_18:
        temp_fa0 = var_s1->unk18;
        temp_fv1_5 = var_fs1 + temp_fa0;
        temp_fv0_5 = (f64) temp_fv1_5;
        if ((temp_fv0_5 > 73.79999542236328) && (arg0->unk154 == 1)) {
            arg0->unk154 = 2U;
            temp_s2->unk18 = (f32) (temp_fv0_5 - 73.79999542236328);
            sp103 = 1;
        } else {
            temp_a3 = var_s1;
            if ((temp_fv1_5 < 0.0f) && (arg0->unk154 == 2)) {
                temp_a0 = var_s1;
                var_s0 -= 1;
                var_fs1 = temp_fv1_5;
                temp_s2->unk14 = (f32) (temp_s2->unk14 + temp_fa0);
                temp_s2->unk10 = (u8) (temp_s2->unk10 - 1);
                temp_s2->unkC = (void *) var_s1->unk1C;
                var_s1 = var_s1->unk1C;
                func_8070D9AC(temp_fa0, temp_a0, temp_s2->unk10, temp_s2, temp_a3);
            } else {
                sp50 = temp_fv1_5;
                func_806A4B84(var_fs1, arg0, temp_s2, temp_a3, (var_s0 == temp_s2->unk10) & 0xFF, &sp103);
                if (sp103 == 0) {
                    var_s1 = var_s1->unk1C;
                    var_fs1 = sp50;
                }
            }
        }
        var_s0 += 1;
        if (((s32) temp_s2->unk10 >= var_s0) && (var_s1 != NULL) && (sp103 == 0)) {
            goto loop_18;
        }
    }
    var_v0 = arg0->unk154;
    if (var_v0 == 3) {
        temp_v1 = temp_s2->unk12;
        var_v0 = 1 & 0xFF;
        if (temp_v1 != 0) {
            temp_s2->unk12 = (u8) (temp_v1 - 1);
            var_v0 = arg0->unk154;
        } else {
            arg0->unk154 = 1U;
        }
    }
    if ((var_v0 == 1) && (var_s1 == NULL)) {
        func_8070E808(arg0, temp_s2->unk4);
    }
}
