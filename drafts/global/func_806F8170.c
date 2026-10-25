// func_806F8170 (src/global/FCCD0.c): m2c behavioural starter; 66-insn transform wrapper requires local view struct and stage work.
? func_806F8004(f32, ?, f32 *, f32 *, f32 *);       /* extern */
extern s32 D_80754280;

void func_806F8170(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 temp_v0;

    if (arg0 < 0) {
        func_806F8004(16.5f, 0, arg1, arg2, arg3);
        return;
    }
    if (arg0 == 8) {
        func_806F8004((f32) (1.5 - (f64) ((D_80754280 + (arg0 * 0x30))->unk4 * 7)), 0x41D00000, arg1, arg2, arg3);
        return;
    }
    temp_v0 = arg0 * 0x30;
    *arg1 = (D_80754280 + temp_v0)->unk10;
    *arg2 = (D_80754280 + temp_v0)->unk14;
    *arg3 = (D_80754280 + temp_v0)->unk18;
}
