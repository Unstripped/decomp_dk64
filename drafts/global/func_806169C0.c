// func_806169C0 (src/global/19A00.c): stage 3: compiled typed callback-table candidate; callback table declaration and frame allocation remain.
? func_80614F4C(s16 *);                             /* extern */
extern ? D_80746D64;
extern s32 D_807F5AF0;
extern s32 D_807F5AF4;

s32 func_806169C0(s32 arg0) {
    s16 sp1E;

    D_807F5AF0 += 1;
    func_80614F4C(&sp1E);
    *(&D_80746D64 + (sp1E * 4))(arg0);
    return D_807F5AF4;
}
