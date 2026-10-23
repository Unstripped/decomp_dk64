// func_80653804 (src/global/55B20.c): stage 2: structure from m2c, frame 0x120 vs 0xC8 (extra spilled f64 locals); body/switch order recoverable
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
} M55P3Box;

s32 func_80653804(void *arg0, f32 arg1, f32 arg2) {
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f64 pad[9];
    f64 sp38;
    f64 temp_fa0;
    f64 temp_fs1;
    f64 temp_fs2;
    f64 temp_fs3;
    f64 temp_fs4;
    f64 temp_fs5;
    f64 var_fa0;
    f64 var_fa1;
    f64 var_fs0;
    f64 var_ft4;
    f64 var_ft5;
    f64 var_fv0;
    f64 var_fv1;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_v0;
    s32 var_a0;
    s32 var_t2;
    s32 var_t3;
    s32 var_v1;
    M55P3Box *box;

    box = arg0;
    temp_a1 = box->unk2;
    temp_v0 = box->unk4;
    temp_a2 = box->unk10;
    temp_a3 = box->unkE;
    temp_t0 = box->unk0;
    temp_t1 = box->unkC;
    temp_fs3 = (f64) arg1;
    var_v1 = 0;
    var_fa1 = sp98;
    var_ft5 = sp88;
    var_t2 = 0;
    temp_fs5 = (f64) temp_t0;
    temp_fa0 = (f64) temp_t1;
    sp38 = temp_fa0;
    temp_fs1 = (temp_fs5 + ((f64) (temp_v0 + temp_a1) * 0.5)) * 0.5;
    var_fa0 = spA0;
    temp_fs4 = (f64) arg2;
    temp_fs2 = (temp_fa0 + ((f64) (temp_a2 + temp_a3) * 0.5)) * 0.5;
    var_ft4 = sp90;
    do {
        switch (var_t2) {
        default:
            var_fv0 = (temp_fs3 - var_ft4) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - var_ft4) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        case 0:
            var_ft5 = sp38;
            var_ft4 = temp_fs5;
            var_fa1 = (f64) (temp_a3 - temp_t1);
            var_fa0 = (f64) (temp_a1 - temp_t0);
            var_fv0 = (temp_fs3 - temp_fs5) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - temp_fs5) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        case 1:
            var_ft5 = sp38;
            var_ft4 = temp_fs5;
            var_fa1 = (f64) (temp_a2 - temp_t1);
            var_fa0 = (f64) (temp_v0 - temp_t0);
            var_fv0 = (temp_fs3 - temp_fs5) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - temp_fs5) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        case 2:
            var_ft4 = (f64) temp_a1;
            var_ft5 = (f64) temp_a3;
            var_fa0 = (f64) (temp_v0 - temp_a1);
            var_fa1 = (f64) (temp_a2 - temp_a3);
            var_fv0 = (temp_fs3 - var_ft4) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - var_ft4) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        }
        var_t2 += 1;
        var_t3 = -1;
        if (var_fv1 <= var_fv0) {
            var_t3 = 1;
        }
        var_a0 = -1;
        if (var_fs0 >= 0.0) {
            var_a0 = 1;
        }
        if (var_a0 != var_t3) {
            var_v1 = 1;
        }
    } while (var_t2 != 3);
    sp88 = var_ft5;
    sp90 = var_ft4;
    sp98 = var_fa1;
    spA0 = var_fa0;
    return (var_v1 == 0) & 0xFF;
}
