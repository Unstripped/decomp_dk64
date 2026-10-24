// func_806A370C (src/global/A8400.c): stage 1: unedited m2c starter from the base asm (never attempted this round)
s32 func_80611A44();                                /* extern */
f32 func_80612D1C(f32);                             /* extern */
void *func_806FC530(void *, ?, ?, ?, u16 *, s32);   /* extern */
extern u8 D_807444FC;
static u16 D_8075A740 = 0;                          /* const */

void func_806A370C(void **arg0, void *arg1, void *arg2, void *arg3) {
    u16 spE8;                                       /* compiler-managed */
    f32 sp60;
    f32 sp5C;
    f32 sp4C;
    f32 sp38;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv1;
    void *temp_s1;
    void *temp_s3;
    void *temp_t0;
    void *temp_v1;

    temp_s3 = *arg0;
    spE8 = D_8075A740;
    guMtxIdentF((f32 (*)[4]) &spA8[0]);
    temp_s1 = arg3 + 0x10;
    if ((arg3->unk10 != 0) && (arg3->unk2 != 0)) {
        temp_fa0 = (f32) arg3->unk0 * 0.5f * 4.0f;
        sp60 = temp_fa0;
        temp_fa1 = arg2->unk18 * 0.5f * 4.0f;
        sp5C = temp_fa1;
        guTranslateF((f32 (*)[4]) &sp68[0], -temp_fa0, -temp_fa1, 0.0f);
        guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
        temp_s1->unk88 = (f32) ((f64) temp_s1->unk88 + 0.41887903213500977);
        if (arg3->unk10 & 8) {
            temp_fv0 = (f32) ((f64) temp_s1->unk88 * 0.5);
            if (temp_fv0 <= 6.2831855f) {
                guRotateF((f32 (*)[4]) &sp68[0], temp_fv0 * 57.295776f, 0.0f, 0.0f, 1.0f);
                guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
            }
        }
        if (arg3->unk10 & 4) {
            temp_fv0_2 = temp_s1->unk88;
            if (temp_fv0_2 <= 6.2831855f) {
                var_fv1 = (0.25f * (func_80612D1C(temp_fv0_2 - 1.5707964f) + 1.0f)) + 1.0f;
            } else {
                var_fv1 = 1.0f;
            }
            guScaleF((f32 (*)[4]) &sp68[0], var_fv1, var_fv1, 1.0f);
            guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
        }
        if (arg3->unk10 & 2) {
            sp38 = func_80612D1C(temp_s1->unk88);
            sp4C = ((20.0f - (f32) ((s32) (func_80611A44() >> 0xF) % 40)) / 20.0f) * (4.0f * sp38);
            sp38 = func_80612D1C(temp_s1->unk88);
            guTranslateF((f32 (*)[4]) &sp68[0], sp4C, ((20.0f - (f32) ((s32) (func_80611A44() >> 0xF) % 40)) / 20.0f) * (4.0f * sp38), 0.0f);
            guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
        }
        guTranslateF((f32 (*)[4]) &sp68[0], sp60, sp5C, 0.0f);
        guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
    }
    guScaleF((f32 (*)[4]) &sp68[0], 1.0f, 1.0f, 1.0f);
    guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
    guTranslateF((f32 (*)[4]) &sp68[0], (f32) (((f64) arg1->unk44 + (f64) arg3->unk4) * 4.0), (f32) (((f64) arg1->unk48 + (f64) arg3->unk8) * 4.0), 0.0f);
    guMtxCatF((f32 (*)[4]) &spA8[0], (f32 (*)[4]) &sp68[0], (f32 (*)[4]) &spA8[0]);
    guMtxF2L((f32 (*)[4]) &spA8[0], temp_s1 + (D_807444FC << 6) + 8);
    temp_s3->unk0 = 0xDA380003;
    temp_v1 = temp_s3 + 8;
    temp_s3->unk4 = (void *) (temp_s1 + (D_807444FC << 6) + 8);
    temp_v1->unk4 = 0;
    temp_s3->unk8 = 0xE7000000;
    temp_t0 = temp_v1 + 8;
    temp_v1->unk8 = 0xFA000000;
    temp_t0->unk4 = (s32) (arg3->unk3 | 0x2828FF00);
    spE8 = temp_s1->unk2;
    *arg0 = func_806FC530(temp_t0 + 8, 6, 0, 0, &spE8, 0);
}
