// func_80616850 (src/global/19A00.c): stage 4: behavior recovered; remaining diff is state-pointer stack slot/register allocation
? func_80614EBC(void *, u16);                       /* extern */
? func_80614F4C(u16 *, s32 *);                      /* extern */
extern s32 D_807F5AF0;
extern s32 D_807F5AF4;

s32 func_80616850(void *arg0) {
    s32 sp24;
    u16 sp22;
    void *sp1C;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    D_807F5AF0 += 1;
    sp1C = temp_v0;
    sp24 = temp_v0->unk88;
    func_80614F4C(&sp22, &D_807F5AF0);
    sp1C->unk5C = (u16) sp1C->unk64;
    sp1C->unk60 = (s32) (D_807F5AF0 - sp1C->unk68);
    func_80614EBC(arg0, sp22);
    D_807F5AF0 = sp1C->unk6C;
    sp1C->unk88 = sp24;
    return D_807F5AF4;
}
