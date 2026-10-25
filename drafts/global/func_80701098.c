// func_80701098 (src/global/103AB0.c): Stage 2 m2c reconstruction; transform helper prototypes and vector local types need resolution before frame matching.
? func_80612840(? *, s32, s32, s32, ?32, s32, s32); /* extern */
? func_806128A8(?32 *, s32, s32, s32, s32, s32, s32); /* extern */
? func_80612910(? *, ?32, ? *, s32, f32, s32, f32); /* extern */
? func_80612970(? *, s32, s32, s32);                /* extern */
f32 func_80612A14(s32, ? *, s32, s32, ? *, s32);    /* extern */
? func_80612AD8(?32 *, s32, s32, s32);              /* extern */
? func_80626F8C(?32, ?32, s32, f32 *, f32 *, s32, f32, s32); /* extern */
void *func_8068C5A8(s32, s32, ?, ?, s32, s32, s32, s32, f32, f32, s32, f32); /* extern */
void *func_80703374(void *, u8, u8, u8, u32);       /* extern */
extern ? D_80754AF0;
extern void *D_807FC924;

void *func_80701098(void *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5) {
    ?32 sp1B4;
    ? sp1A8;
    ? sp19C;
    ? sp190;
    ?32 sp184;
    ?32 sp178;
    ?32 sp16C;
    ?32 sp160;
    f32 sp108;
    f32 spF4;
    f32 spF0;
    ? spD0;
    ? spC4;
    f64 sp90;
    f64 sp88;
    f64 sp80;
    f32 temp_fv0_2;
    f32 var_fs0;
    f32 var_fs2;
    f32 var_fs3;
    f64 temp_fa0;
    f64 temp_fa0_2;
    f64 temp_fa0_3;
    f64 temp_fs1;
    f64 temp_fv0;
    f64 var_ft0;
    f64 var_ft1;
    f64 var_ft1_2;
    f64 var_ft1_3;
    f64 var_ft1_4;
    f64 var_ft4;
    f64 var_ft5;
    f64 var_fv0;
    f64 var_fv0_2;
    f64 var_fv0_3;
    s16 var_s1;
    u8 temp_t3;
    u8 temp_t6;
    u8 temp_t9;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s0;
    void *var_s2;

    var_s2 = arg0;
    var_ft1 = (f64) arg5;
    if ((s32) arg5 < 0) {
        var_ft1 += 4294967296.0;
    }
    spF0 = (f32) (var_ft1 / 5.0);
    func_80612AD8(&sp160, arg1, arg2, arg3);
    func_80612AD8(&sp178, D_807FC924->unk21C, D_807FC924->unk220, D_807FC924->unk224);
    func_80612AD8(&sp16C, D_807FC924->unk234, D_807FC924->unk238, D_807FC924->unk23C);
    func_80612840(&spD0, subroutine_arg1, sp16C.unk4, subroutine_arg3, sp178.unk0, sp178.unk4, sp178.unk8);
    func_80612970(&sp19C, subroutine_arg1, spD0.unk4, spD0.unk8);
    func_80612910(&spD0, subroutine_arg1, sp19C.unk4, sp19C.unk8, 5000.0f);
    func_806128A8(&sp1B4, subroutine_arg1, sp178.unk4, subroutine_arg3, spD0.unk0, spD0.unk4, spD0.unk8);
    func_80612840(&spD0, subroutine_arg1, sp160.unk4, subroutine_arg3, sp178.unk0, sp178.unk4, sp178.unk8);
    func_80612970(&sp190, subroutine_arg1, spD0.unk4, spD0.unk8);
    if ((f64) func_80612A14(subroutine_arg0, sp190.unk4, subroutine_arg2, subroutine_arg3, sp19C.unk4, sp19C.unk8) < 1e-05) {
        var_fs0 = (f32) 1e-05;
    } else {
        var_fs0 = (f32) (f64) func_80612A14(subroutine_arg0, sp190.unk4, subroutine_arg2, subroutine_arg3, sp19C.unk4, sp19C.unk8);
    }
    func_80612910(&spC4, subroutine_arg1, sp190.unk4, sp190.unk8, 5000.0f);
    func_80612910(&spD0, subroutine_arg1, spC4.unk4, subroutine_arg3, 1.0f / var_fs0);
    func_806128A8(&sp160, subroutine_arg1, sp178.unk4, subroutine_arg3, spD0.unk0, spD0.unk4, spD0.unk8);
    func_80612840(&sp1A8, subroutine_arg1, sp160.unk4, subroutine_arg3, sp1B4.unk0, sp1B4.unk4, sp1B4.unk8);
    if (var_fs0 < 0.0f) {

    } else {
        var_s1 = 0;
        temp_fs1 = (f64) var_fs0;
        var_ft0 = (f64) arg4;
        if ((s32) arg4 < 0) {
            var_ft0 += 4294967296.0;
        }
        var_ft5 = (f64) arg4;
        sp90 = var_ft0 / 255.0;
        if ((s32) arg4 < 0) {
            var_ft5 += 4294967296.0;
        }
        var_ft4 = (f64) (u8) (s16) arg4;
        sp88 = var_ft5 / 255.0;
        if ((s32) (u8) (s16) arg4 < 0) {
            var_ft4 += 4294967296.0;
        }
        sp80 = var_ft4 / 255.0;
        do {
            if (temp_fs1 < 0.75) {
                var_fv0 = 0.0;
            } else {
                var_fv0 = temp_fs1 - 0.75;
            }
            var_fs3 = (f32) (var_fv0 * 4.0);
            temp_fa0 = (f64) var_fs3;
            if (temp_fa0 < 0.85) {
                var_fs2 = (f32) 0.85;
            } else {
                var_fs2 = (f32) temp_fa0;
            }
            switch (var_s1) {                       /* irregular */
            case 11:
                sp108 = 640.0f;
                spF4 = 480.0f;
                if (temp_fs1 < 0.9) {
                    var_fv0_2 = 0.0;
                } else {
                    var_fv0_2 = temp_fs1 - 0.9;
                }
                var_fs3 = (f32) (var_fv0_2 * 10.0);
                temp_fa0_2 = (f64) var_fs3;
                if (temp_fa0_2 < 0.85) {
                    var_fs2 = (f32) 0.85;
                } else {
                    var_fs2 = (f32) temp_fa0_2;
                }
                var_s0 = (var_s1 * 0x10) + &D_80754AF0;
                break;
            case 0:
            case 12:
                if (temp_fs1 < 0.25) {
                    var_fv0_3 = 0.0;
                } else {
                    var_fv0_3 = temp_fs1 - 0.25;
                }
                var_fs3 = (f32) (var_fv0_3 * 1.333);
                temp_fa0_3 = (f64) var_fs3;
                if (temp_fa0_3 < 0.85) {
                    var_fs2 = (f32) 0.85;
                } else {
                    var_fs2 = (f32) temp_fa0_3;
                }
                func_80626F8C(sp160, sp164, sp168, &sp108, &spF4, 0, 4.0f, 0);
                var_s0 = (var_s1 * 0x10) + &D_80754AF0;
                break;
            default:
                var_s0 = (var_s1 * 0x10) + &D_80754AF0;
                func_80612910((bitwise ? *) temp_fa0, sp164, &spD0, subroutine_arg1, sp1A8.unk4, sp1A8.unk8, var_s0->unk4);
                func_806128A8(&sp184, subroutine_arg1, sp1B4.unk4, subroutine_arg3, spD0.unk0, spD0.unk4, spD0.unk8);
                func_80626F8C(sp184, sp188, sp18C, &sp108, &spF4, 0, 4.0f, 0);
                break;
            }
            temp_s2 = var_s2 + 8;
            var_s2->unk0 = 0xE7000000;
            var_s2->unk4 = 0;
            var_s2->unk8 = 0xFA000000;
            temp_fv0 = (f64) var_fs2;
            temp_t9 = var_s0->unk8;
            var_ft1_2 = (f64) temp_t9;
            if ((s32) temp_t9 < 0) {
                var_ft1_2 += 4294967296.0;
            }
            temp_t6 = var_s0->unk9;
            var_ft1_3 = (f64) temp_t6;
            if ((s32) temp_t6 < 0) {
                var_ft1_3 += 4294967296.0;
            }
            temp_t3 = var_s0->unkA;
            var_ft1_4 = (f64) temp_t3;
            if ((s32) temp_t3 < 0) {
                var_ft1_4 += 4294967296.0;
            }
            temp_s2->unk4 = (s32) (((u32) ((f32) var_s0->unkB * var_fs3 * spF0) & 0xFF) | ((u32) (sp90 * var_ft1_2 * temp_fv0) << 0x18) | (((u32) (sp88 * var_ft1_3 * temp_fv0) & 0xFF) << 0x10) | (((u32) (sp80 * var_ft1_4 * temp_fv0) & 0xFF) << 8));
            temp_fv0_2 = var_s0->unk0 * 4.0f * spF0;
            temp_v0 = func_8068C5A8(temp_s2 + 8, (var_s0->unkC + 0x4D) & 0xFFFF, 3, 1, 0x40, 0x40, (s32) sp108, (s32) spF4, temp_fv0_2, temp_fv0_2, 0, 0.0f);
            var_s1 += 1;
            var_s2 = temp_v0;
        } while (var_s1 < 0xC);
        temp_v0->unk0 = 0xE7000000;
        temp_v0->unk4 = 0;
        var_s2 = temp_v0 + 8;
        if (temp_fs1 > 0.97) {
            temp_v0_2 = func_80703374(var_s2, arg4, arg4, (u8) (s16) arg4, (u32) ((temp_fs1 - 0.97) * 33.0 * 128.0));
            temp_v0_2->unk0 = 0xD7000002;
            temp_v0_2->unk4 = 0x80008000;
            temp_v0_2->unk8 = 0xFC119623;
            temp_v0_2->unkC = 0xFF2FFFFF;
            var_s2 = temp_v0_2 + 0x10;
        }
    }
    return var_s2;
}
