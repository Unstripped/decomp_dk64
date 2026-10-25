// func_806F39E8 (src/global/F56F0.c): Stage 3: path-pair allocator and sin/cos transform reconstructed. Closest draft needs compact 0x38 frame and point layout preserving delay-slot stores.
void *func_80610FE8(?);                             /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */
? func_806F386C(u8, s32, ?, ?, s32);                /* extern */
? heapClearBlock(void *);                           /* extern */
extern void *D_80753E90;
extern s32 D_807FBB60;
extern s8 D_807FD716;

void func_806F39E8(s32 arg0, void *arg1, u8 arg2) {
    void *sp30;
    s16 *sp2C;
    f32 sp28;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 var_fv1;
    f64 var_ft1;
    f64 var_ft5;
    s16 *temp_v1;
    u8 temp_t6;
    u8 temp_t6_2;
    void *temp_t0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v1 = D_80753E90->unk4 + (D_80753E90->unk0 * 8);
    *temp_v1 = 2;
    sp2C = temp_v1;
    temp_v0 = func_80610FE8(0x24);
    sp2C->unk4 = temp_v0;
    heapClearBlock(temp_v0);
    temp_v0_2 = sp2C->unk4;
    temp_v0_2->unk0 = (s16) arg1->unk0;
    temp_t0 = temp_v0_2 + 0x12;
    temp_v0_2->unk2 = (s16) arg1->unk2;
    temp_v0_2->unk9 = 0x32;
    temp_v0_2->unk4 = (s16) arg1->unk4;
    temp_t6 = arg1->unk6;
    var_ft1 = (f64) temp_t6;
    if ((s32) temp_t6 < 0) {
        var_ft1 += 4294967296.0;
    }
    sp30 = temp_t0;
    temp_fv0 = func_80612794((s16) (s32) ((var_ft1 / 255.0) * 4095.0));
    var_fv1 = (f32) arg2;
    if ((s32) arg2 < 0) {
        var_fv1 += 4294967296.0f;
    }
    temp_v0_2->unk12 = (s16) (s32) ((temp_fv0 * var_fv1) + (f32) arg1->unk0);
    temp_t0->unk2 = (s16) arg1->unk2;
    temp_t6_2 = arg1->unk6;
    var_ft5 = (f64) temp_t6_2;
    if ((s32) temp_t6_2 < 0) {
        var_ft5 += 4294967296.0;
    }
    sp28 = var_fv1;
    temp_ft5 = func_80612790((s16) (s32) ((var_ft5 / 255.0) * 4095.0)) * var_fv1;
    sp30->unk9 = 0x32;
    sp30->unk4 = (s16) (s32) (temp_ft5 + (f32) arg1->unk4);
    func_806F386C(D_80753E90->unk1, arg0, 0, 0, 0);
    D_807FD716 = 0;
    D_807FBB60 |= 0x400;
}
