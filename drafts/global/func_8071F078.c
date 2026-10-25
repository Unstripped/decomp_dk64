// func_8071F078 (src/global/11BC10.c): stage 3: m2c behavior recovered; state typing/frame integration remains
void *func_80610FE8(?);                             /* extern */
s32 func_80611A44();                                /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */

void func_8071F078(void *arg0, ? arg1) {
    s32 temp_t6;
    void *temp_v0;
    void *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) (((f64) ((s32) (func_80611A44() >> 0xF) % 100) / 10.0) + 2.0);
        temp_v0->unk4 = (f32) (-8.0 - ((f64) ((s32) (func_80611A44() >> 0xF) % 100) / 70.0));
        temp_t6 = (arg0->unk35C + (s16) ((s32) (func_80611A44() >> 0xF) % 800)) - 0x190;
        arg0->unk35C = temp_t6;
        arg0->unk35C = (s32) (temp_t6 % 4095);
        var_v1 = arg0->unk384;
    }
    arg0->unk340 = (f32) (arg0->unk340 + (var_v1->unk0 * func_80612794(arg0->unk35E)));
    arg0->unk348 = (f32) (arg0->unk348 + (var_v1->unk0 * func_80612790(arg0->unk35E)));
    arg0->unk344 = (f32) (arg0->unk344 + var_v1->unk4);
}
