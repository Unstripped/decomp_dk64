// func_8071F8E4 (src/global/11BC10.c): Stage 1 m2c starter; callback and matrix local declarations unresolved.
? func_8071498C(? *);                               /* extern */
? func_807149B8(?);                                 /* extern */
? func_80714CC0(? *, ?, f32, f32, f32);             /* extern */
extern ? D_8071FB08;
extern u8 D_807444FC;
extern s32 D_8076A064;
extern ? func_8071C818;

void func_8071F8E4(void *arg0, s8 *arg1) {
    void *temp_v0;

    temp_v0 = arg0->unk384;
    if (temp_v0 != NULL) {
        temp_v0->unk20 = (f32) (temp_v0->unk20 + temp_v0->unk24);
        if ((f64) temp_v0->unk20 >= 1.0) {
            *arg1 = 0xFF;
            temp_v0->unk20 = 1.0f;
        }
        arg0->unk340 = (f32) ((temp_v0->unk14 * temp_v0->unk20) + temp_v0->unk8);
        arg0->unk344 = (f32) ((temp_v0->unk18 * temp_v0->unk20) + temp_v0->unkC);
        arg0->unk348 = (f32) ((temp_v0->unk1C * temp_v0->unk20) + temp_v0->unk10);
        if (!(D_8076A064 & 3)) {
            func_807149B8(1);
            func_8071498C(&func_8071C818);
            func_80714CC0(&D_8071FB08, 0x3FCCCCCD, arg0->unk340, arg0->unk344, arg0->unk348);
        }
        temp_v0->unk4 = (f32) (temp_v0->unk4 + temp_v0->unk0);
        guScaleF((f32 (*)[4]) &sp78[0], arg0->unk360, arg0->unk364, 0.0f);
        guRotateF((f32 (*)[4]) &sp38[0], temp_v0->unk4, 0.0f, 0.0f, 1.0f);
        guMtxCatF((f32 (*)[4]) &sp78[0], (f32 (*)[4]) &sp38[0], (f32 (*)[4]) &sp78[0]);
        guMtxF2L((f32 (*)[4]) &sp78[0], arg0 + (D_807444FC << 6) + 0x128);
        arg0->unk32C = 2;
    }
}
