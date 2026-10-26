// func_806168E4 (src/global/19A00.c): stage 4: behavior recovered; remaining diff is state-pointer/register allocation
? func_80614E78(void *, u16);                       /* extern */
? func_80614F4C(u16 *);                             /* extern */
extern s32 D_807F5AF0;
extern s32 D_807F5AF4;

s32 func_806168E4(void *arg0) {
    u16 sp1E;
    void *sp18;

    D_807F5AF0 += 1;
    sp18 = arg0->unk4;
    func_80614F4C(&sp1E);
    sp18->unk5C = (u16) sp18->unk64;
    sp18->unk60 = (s32) (D_807F5AF0 - sp18->unk68);
    func_80614E78(arg0, sp1E);
    D_807F5AF0 = sp18->unk6C;
    return D_807F5AF4;
}
