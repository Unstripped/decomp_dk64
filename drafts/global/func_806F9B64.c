// func_806F9B64 (src/global/FCCD0.c): Stage 1 m2c reconstruction; needs typed slot records and callback signatures.
? func_806F966C(s32);                               /* extern */
? func_806F96CC(void *, ?);                         /* extern */
? func_80714950(s32);                               /* extern */
? func_8071495C();                                  /* extern */
? func_8071498C(? *);                               /* extern */
? func_807149FC(?);                                 /* extern */
? func_80714CC0(s32, ?, ?, ?, f32);                 /* extern */
extern s32 D_80750518;
extern s32 D_80754280;
extern f32 D_807FD7A0;
extern ? func_806F9AF0;

void func_806F9B64(s32 arg0) {
    s32 sp64;
    f32 *var_s1;
    s32 *var_s2;
    s32 temp_v1;
    s32 var_s0;
    void *temp_s4;
    void *temp_v0;

    temp_v1 = arg0 * 0x30;
    temp_s4 = temp_v1 + D_80754280;
    sp64 = temp_v1;
    func_806F966C(temp_s4 + 0x28);
    func_806F96CC(temp_s4->unk28, 0);
    temp_s4->unk28->unk10 = 0;
    temp_v0 = temp_s4->unk28->unk14;
    temp_v0->unk0 = (s32) ((D_80754280 + temp_v1)->unk8 + 0x14);
    var_s2 = &D_80750518;
    var_s1 = &D_807FD7A0;
    var_s0 = 0;
    temp_v0->unk4 = (s32) ((D_80754280 + temp_v1)->unkC - 0x14);
    do {
        func_8071495C();
        func_807149FC(-1);
        func_8071498C(&func_806F9AF0);
        func_80714950(var_s0);
        *var_s1 = -100.0f;
        func_80714CC0(*var_s2, 0x3F800000, 0xC3480000, 0, -10.0f);
        var_s0 += 1;
        var_s1 += 4;
        var_s2 += 4;
    } while (var_s0 != 5);
}
