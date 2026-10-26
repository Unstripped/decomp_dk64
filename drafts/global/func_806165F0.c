// func_806165F0 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614F4C(s16 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_806165F0(void *arg0) {
    s16 sp1E;

    D_807F5AF0 += 1;
    func_80614F4C(&sp1E);
    D_807F5AF0 = arg0->unk4->unk68 + sp1E;
    return 1;
}
