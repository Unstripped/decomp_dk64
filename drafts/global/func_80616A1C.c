// func_80616A1C (src/global/19A00.c): stage 3: callback table type and local frame layout remain unresolved
? func_80614F4C(s16 *);                             /* extern */
extern ? D_80746D64;
extern s32 D_807F5AF0;
extern s32 D_807F5AF4;

s32 func_80616A1C(void *arg0) {
    s16 sp1E;
    void *sp18;
    ? (*temp_t1)(void *);

    D_807F5AF0 += 1;
    sp18 = arg0->unk4;
    func_80614F4C(&sp1E);
    temp_t1 = *(&D_80746D64 + (sp1E * 4));
    sp18->unk70 = temp_t1;
    sp18->unk74 = (s32) D_807F5AF0;
    if (sp1E != 0) {
        temp_t1(arg0);
    }
    return D_807F5AF4;
}
