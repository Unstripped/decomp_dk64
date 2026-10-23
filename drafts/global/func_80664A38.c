// func_80664A38 (src/global/68EA0.c): Starter draft from m2c (158 insns)
s32 func_80611A44();                                /* extern */
? func_80714998(?);                                 /* extern */
? func_807149B8(?);                                 /* extern */
? func_80714A28(?);                                 /* extern */
? func_80714CC0(?, ? *, ?, f32, f32, f32);          /* extern */
extern ? D_80720A7C;
extern s32 D_807F9430;

void func_80664A38(s16 arg0) {
    f32 sp34;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    f64 temp_fv0;
    s32 temp_t8;
    void *temp_v1;

    if (((s32) (func_80611A44() % 10000) % 10) == 0) {
        temp_t8 = arg0 * 0xC;
        sp24 = temp_t8;
        sp34 = (f32) ((f64) (D_807F9430 + temp_t8)->unk8 / 25.0);
        func_807149B8(1);
        func_80714998(2);
        func_80714A28(4);
        sp28 = func_80611A44();
        sp2C = func_80611A44();
        temp_v1 = D_807F9430 + sp24;
        temp_fv0 = (f64) sp34;
        func_80714CC0(0, &D_80720A7C, 0x3ECCCCCD, (f32) (((((f64) ((s32) (sp28 % 10000) % 300) / 20.0) - 7.5) * temp_fv0) + (f64) temp_v1->unk2), (f32) ((((f64) ((s32) (sp2C % 10000) % 600) / 20.0) * temp_fv0) + (f64) temp_v1->unk4), (f32) (((((f64) ((s32) (func_80611A44() % 10000) % 300) / 20.0) - 7.5) * temp_fv0) + (f64) temp_v1->unk6));
    }
}
