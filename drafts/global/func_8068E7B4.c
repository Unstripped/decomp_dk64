// func_8068E7B4 (src/global/90D80.c): regalloc: sp30 at 0x28 instead of 0x30, with sp2E at 0x2c (all text 98% matched)
int _sprintf(char *, const char *, ...);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
u32 textGetFontHeight(s32);

Gfx *func_8068E7B4(Gfx *arg0, f32 arg1, f32 arg2, s32 arg3) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    char sp3C[16];
    s16 sp2E;
    s32 sp30;

    sp50 = arg2 - ((f32)(u32)textGetFontHeight(0x86) * 0.5f);
    _sprintf(sp3C, ":");
    sp4C = (f32)textGetStringWidth(6, sp3C) * 0.5f;
    sp54 = arg1 - sp4C;
    sp2E = (s16)(s32)(sp50 * 4.0f);
    arg0 = textDrawStringVtx(arg0, 6, (s16)(s32)(sp54 * 4.0f), sp2E, sp3C, 1);
    sp30 = arg3 / 60;
    _sprintf(sp3C, "%2d", sp30);
    arg0 = textDrawStringVtx(arg0, 0x86, (s16)(s32)((sp54 - (f32)textGetStringWidth(0x86, sp3C)) * 4.0f), sp2E, sp3C, 1);
    _sprintf(sp3C, "%02d", arg3 - sp30 * 60);
    return textDrawStringVtx(arg0, 0x86, (s16)(s32)((arg1 + sp4C) * 4.0f), sp2E, sp3C, 1);
}
