// func_806162C4 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614D00(s32, s32, s32);                     /* extern */
? func_80614FD8(s32 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_806162C4(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    D_807F5AF0 += 1;
    func_80614FD8(&sp1C);
    func_80614FD8(&sp18);
    func_80614D00(arg0, sp1C, sp18);
    return 1;
}
