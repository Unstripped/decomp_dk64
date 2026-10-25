// func_806F6554 (src/global/F9450.c): Stage 1 m2c starter; reviewed 60-instruction target and call sequence.
s32 func_806F4EBC(f32, f32, void *);                /* extern */
? func_806F6204(s32, u8, void *);                   /* extern */
extern s32 D_80754244;
extern ? D_807FCC4B;
extern s16 D_807FD726;
extern s16 D_807FD728;
extern s32 D_807FD72C;

void func_806F6554(u8 arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 temp_v0;

    if (*(&D_807FCC4B + (arg0 * 0x306)) > 0) {
        temp_fv0 = arg1->unkC;
        temp_fa0 = arg1->unk0;
        if (temp_fa0 <= ((f32) D_807FD726 + temp_fv0)) {
            temp_fa1 = arg1->unk8;
            if (temp_fa1 <= ((f32) D_807FD728 + temp_fv0)) {
                temp_v0 = func_806F4EBC(temp_fa0, temp_fa1, arg1);
                if (temp_v0 >= 0) {
                    func_806F6204(*(D_80754244 + (temp_v0 * 4)), arg0, arg1);
                }
            }
        }
        func_806F6204(D_807FD72C, arg0, arg1);
    }
}
