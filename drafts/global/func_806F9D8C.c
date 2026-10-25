// func_806F9D8C (src/global/FCCD0.c): Stage 1 m2c reconstruction; display-list builder needs typed command and viewport structures.
? _sprintf(? *, ? *, u16);                          /* extern */
void *cameraFindViewportEntry(?, void *, void *);   /* extern */
f32 func_80612794(s16);                             /* extern */
f32 func_80612E40(f32, ? *, ? *);                   /* extern */
s32 func_806FBD5C(?, ? *);                          /* extern */
void *func_806FC530(void *, ?, s16, s16, ? *, s32); /* extern */
extern ? D_1000118;
extern ? D_2000080;
extern s16 D_80744490;
extern u8 D_807444FC;
extern s32 D_80754280;
extern u8 D_807FD7E4;

void *func_806F9D8C(s32 arg0, void *arg1, void *arg2) {
    void *sp74;
    ? sp6C;
    u8 sp6B;
    s32 sp5C;
    s32 sp30;
    ? *temp_a1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_ft4;
    s32 temp_t5;
    s32 var_a2;
    u16 temp_t8;
    u8 temp_v0_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v1;

    sp74 = arg1->unk14;
    temp_fv0 = func_80612794(arg1->unk10);
    sp6B = (u8) (u32) ((f64) temp_fv0 * 255.0);
    sp5C = 0;
    temp_fv1 = 1.0f - temp_fv0;
    arg2->unk4 = &D_2000080;
    arg2->unk0 = 0xDA380007;
    temp_s0 = arg2 + 8;
    guTranslate(sp74 + (D_807444FC << 6) + 8, arg1->unk4 * temp_fv1, arg1->unk8 * temp_fv1, 0.0f);
    temp_t5 = arg0 * 0x30;
    sp30 = temp_t5;
    temp_v1 = D_80754280 + temp_t5;
    temp_v0_2 = temp_v1->unk2C;
    temp_a1 = "o";
    switch (temp_v0_2) {                            /* irregular */
    case 1:
        _sprintf(&sp6C, temp_a1);
        break;
    case 2:
        _sprintf(&sp6C, "NA");
        break;
    default:
        if (sp30 == 0xF0) {
            temp_t8 = temp_v1->unk4;
            var_ft4 = (f32) temp_t8;
            if ((s32) temp_t8 < 0) {
                var_ft4 += 4294967296.0f;
            }
            var_a2 = (s32) func_80612E40(var_ft4 * 0.006666667f, &sp6C, temp_a1);
        } else {
            var_a2 = (s32) temp_v1->unk4;
        }
        _sprintf(&sp6C, "%d", (u16) var_a2);
        break;
    }
    arg2->unk8 = 0xDA380000;
    temp_s0_2 = temp_s0 + 8;
    temp_s0->unk4 = (void *) (sp74 + (D_807444FC << 6) + 8);
    temp_s0_3 = temp_s0_2 + 8;
    temp_s0->unk8 = 0xE7000000;
    temp_s0_2->unk4 = 0;
    temp_s0_2->unk8 = 0xFA000000;
    temp_s0_4 = temp_s0_3 + 8;
    temp_s0_3->unk4 = (s32) sp6B;
    temp_s0_5 = temp_s0_4 + 8;
    D_807FD7E4 = sp6B;
    temp_s0_3->unk8 = 0xDE000000;
    temp_s0_4->unk4 = &D_1000118;
    temp_s0_5->unk4 = 0xFF2CFE7F;
    temp_s0_4->unk8 = 0xFCFF97FF;
    temp_s0_6 = temp_s0_5 + 8;
    temp_v0_3 = cameraFindViewportEntry(0, temp_s0_4, temp_s0_5);
    temp_s0_5->unk8 = (s32) ((((s32) ((f32) temp_v0_3->unk4 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32) ((f32) temp_v0_3->unk6 * 4.0f) & 0xFFF));
    temp_s0_6->unk4 = (s32) ((((s32) ((f32) temp_v0_3->unk8 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) temp_v0_3->unkA * 4.0f) & 0xFFF));
    if (((f64) D_80744490 * 0.5) < (f64) (D_80754280 + sp30)->unk8) {
        sp5C = func_806FBD5C(0x81, &sp6C);
    }
    temp_v0 = func_806FC530(temp_s0_6 + 8, 0x81, (s16) ((sp74->unk0 - sp5C) * 4), (s16) (sp74->unk4 * 4), &sp6C, 0);
    temp_v0->unk4 = 0x40;
    temp_v0->unk0 = 0xD8380002;
    temp_v0->unk8 = 0xE7000000;
    temp_v0->unkC = 0;
    return temp_v0 + 0x10;
}
