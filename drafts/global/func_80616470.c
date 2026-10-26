// func_80616470 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614F4C(u16 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_80616470(void *arg0) {
    u16 sp1E;

    D_807F5AF0 += 1;
    func_80614F4C(&sp1E);
    arg0->unk4->unk88 = (s32) (arg0->unk154 - sp1E);
    return 1;
}
