// func_806F8CFC (src/global/FCCD0.c): m2c behavioural starter; 23-insn slot clear.
? func_806F8D58(?, ?);                              /* extern */
extern s32 D_80754280;

void func_806F8CFC(s32 arg0, ? arg1) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x30;
    (D_80754280 + temp_v0)->unk7 = 0;
    (D_80754280 + temp_v0)->unk6 = 0;
    if (arg0 == 8) {
        func_806F8D58(9, 0);
    }
}
