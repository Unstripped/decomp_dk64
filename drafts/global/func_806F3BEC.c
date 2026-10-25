// func_806F3BEC (src/global/F56F0.c): Stage 3: actor-coordinate path-pair allocator reconstructed. Closest draft needs compact 0x40 frame and target temporary ordering.
void *func_80610FE8(?, s16 *);                      /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */
? func_806F386C(u8, void *, ?, ?, s32);             /* extern */
? heapClearBlock(void *);                           /* extern */
s16 mathAngleBetweenPoints2D(f32, f32, s16, f32, f32); /* extern */
extern void *D_80753E90;
extern s32 D_807FBB60;
extern s8 D_807FD716;

void func_806F3BEC(void *arg0, s16 arg1, s16 arg2, u8 arg3) {
    s16 sp3A;
    void *sp34;
    s16 *sp30;
    f32 sp2C;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 var_fv1;
    s16 *temp_a1;
    void *temp_t0;
    void *temp_v0;
    void *temp_v0_2;

    sp3A = mathAngleBetweenPoints2D((f32) arg1, (f32) arg2, arg1, arg0->unk7C, arg0->unk84);
    temp_a1 = D_80753E90->unk4 + (D_80753E90->unk0 * 8);
    if (arg0->unk154 != 0x44) {
        *temp_a1 = 2;
        sp30 = temp_a1;
        temp_v0 = func_80610FE8(0x24, temp_a1);
        sp30->unk4 = temp_v0;
        heapClearBlock(temp_v0);
        temp_v0_2 = sp30->unk4;
        temp_t0 = temp_v0_2 + 0x12;
        temp_v0_2->unk0 = (s16) (s32) arg0->unk7C;
        temp_v0_2->unk2 = (s16) (s32) arg0->unk80;
        temp_v0_2->unk9 = 0x28;
        temp_v0_2->unk4 = (s16) (s32) arg0->unk84;
        sp34 = temp_t0;
        temp_fv0 = func_80612794(sp3A);
        var_fv1 = (f32) arg3;
        if ((s32) arg3 < 0) {
            var_fv1 += 4294967296.0f;
        }
        temp_v0_2->unk12 = (s16) (s32) ((temp_fv0 * var_fv1) + arg0->unk7C);
        temp_t0->unk2 = (s16) (s32) arg0->unk80;
        sp2C = var_fv1;
        temp_ft4 = func_80612790(sp3A) * var_fv1;
        sp34->unk9 = 0x28;
        sp34->unk4 = (s16) (s32) (temp_ft4 + arg0->unk84);
        func_806F386C(D_80753E90->unk1, arg0, 0, 0, 0);
        D_807FD716 = 0;
        D_807FBB60 |= 0x400;
    }
}
