// func_80616318 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614E78(void *, u16);                       /* extern */
? func_80614F4C(u16 *);                             /* extern */
extern s32 D_807F5AF0;
extern s32 D_807F5AF4;

s32 func_80616318(void *arg0) {
    u16 sp1E;

    D_807F5AF0 += 1;
    func_80614F4C(&sp1E);
    func_80614E78(arg0, sp1E);
    D_807F5AF0 = arg0->unk4->unk6C;
    return D_807F5AF4;
}
