// func_806167EC (src/global/19A00.c): stage 6: behavior recovered; remaining diff is temporary register allocation around script cursor arithmetic
? func_80614F4C(s16 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_806167EC(void *arg0) {
    s16 sp1E;

    D_807F5AF0 = D_807F5AF0 + (arg0->unk4->unk88 * 2) + 1;
    func_80614F4C(&sp1E);
    D_807F5AF0 = arg0->unk4->unk68 + sp1E;
    return 1;
}
