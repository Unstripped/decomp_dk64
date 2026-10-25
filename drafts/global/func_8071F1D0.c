// func_8071F1D0 (src/global/11BC10.c): stage 3: m2c behavior recovered; typed attempt had 0x38 frame versus target 0x28
f32 *func_80610FE8(?);                              /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */
extern s8 D_8075567C;

void func_8071F1D0(void *arg0, s8 *arg1) {
    f32 *sp24;
    f32 *temp_v0;
    f32 *var_v1;
    f32 temp_ft5;
    u8 temp_v0_2;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = arg0->unk340;
        temp_v0->unk4 = (f32) arg0->unk348;
        temp_v0->unk8 = (f32) D_8075567C;
        var_v1 = arg0->unk384;
        D_8075567C = -D_8075567C;
    }
    sp24 = var_v1;
    arg0->unk340 = (f32) ((func_80612794(arg0->unk35E) * 14.0f) + *sp24);
    temp_v0_2 = arg0->unk36D;
    temp_ft5 = (func_80612790(arg0->unk35E) * 14.0f) + var_v1->unk4;
    arg0->unk344 = (f32) (arg0->unk344 + 0.5f);
    arg0->unk348 = temp_ft5;
    if ((s32) temp_v0_2 >= 5) {
        arg0->unk36D = (u8) (temp_v0_2 - 4);
    } else {
        *arg1 = 1;
    }
    arg0->unk35C = (s32) (arg0->unk35C + (s32) ((f64) var_v1->unk8 * 200.0));
}
