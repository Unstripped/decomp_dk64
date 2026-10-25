// func_8071EA24 (src/global/11BC10.c): m2c starter; not integrated before handoff
void *func_80610FE8(?);                             /* extern */
f32 func_806119FC();                                /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */

void func_8071EA24(void *arg0, ? arg1) {
    f64 temp_ft2;
    void *temp_v0;
    void *var_v0;

    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) (func_806119FC() * 4095.0f);
        temp_ft2 = (((f64) func_806119FC() * 0.5) + 1.0) * 5.0;
        temp_v0->unk8 = 15.0f;
        temp_v0->unk4 = (f32) temp_ft2;
        var_v0 = arg0->unk384;
    }
    var_v0->unk4 = (f32) (var_v0->unk4 - 1.0f);
    var_v0->unk8 = (f32) ((f64) var_v0->unk8 * 0.95);
    arg0->unk340 = (f32) (arg0->unk340 + (var_v0->unk8 * func_80612794((s16) (s32) var_v0->unk0)));
    arg0->unk348 = (f32) (arg0->unk348 + (var_v0->unk8 * func_80612790((s16) (s32) var_v0->unk0)));
    arg0->unk344 = (f32) (arg0->unk344 + var_v0->unk4);
}
