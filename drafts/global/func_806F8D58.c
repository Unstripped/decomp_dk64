// func_806F8D58 (src/global/FCCD0.c): m2c behavioural starter; 27-insn list mask update.
? func_806F8CFC();                                  /* extern */
extern s32 D_80754280;
extern void *D_80754284;

void func_806F8D58(s32 arg0) {
    void *var_v0;

    var_v0 = D_80754284;
    (D_80754280 + (arg0 * 0x30))->unk1C = 0;
    if (var_v0 != NULL) {
        do {
            var_v0->unk0 = (s32) (var_v0->unk0 & ~(1 << arg0));
            var_v0 = var_v0->unk4;
        } while (var_v0 != NULL);
    }
    func_806F8CFC();
}
