// func_8071E864 (src/global/11BC10.c): m2c starter; not integrated before handoff
void *func_80610FE8(?, void *);                     /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */

void func_8071E864(void *arg0, s8 *arg1) {
    f32 sp24;
    void *sp1C;
    f32 temp_fa0;
    u8 temp_t5;
    void *temp_v0;
    void *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8, arg0);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 10.0f;
        temp_v0->unk4 = (f32) (arg0->unk35C * 0x154);
        var_v1 = arg0->unk384;
    }
    var_v1->unk0 = (f32) ((f64) var_v1->unk0 - 0.2);
    if ((f64) var_v1->unk0 < 0.8) {
        var_v1->unk0 = 0.8f;
    }
    sp1C = var_v1;
    sp24 = var_v1->unk0 * func_80612794((s16) (s32) var_v1->unk4);
    temp_fa0 = var_v1->unk0 * func_80612790((s16) (s32) var_v1->unk4);
    arg0->unk360 = (f32) ((f64) arg0->unk360 * 1.08);
    arg0->unk364 = (f32) ((f64) arg0->unk364 * 1.08);
    if ((f64) arg0->unk360 > 8.0) {
        temp_t5 = arg0->unk36D - 0x32;
        arg0->unk36D = temp_t5;
        if ((temp_t5 & 0xFF) < 0x33) {
            *arg1 = 1;
        }
    }
    arg0->unk340 = (f32) (arg0->unk340 + sp24);
    arg0->unk348 = (f32) (arg0->unk348 + temp_fa0);
}
