// func_806151BC (src/global/19A00.c): stage 4: typed candidate compiled with target frame; remaining register allocation
// Stage 2: m2c behavioral starter; remaining diff: state view/register allocation.
void func_80614F28(u8 *arg0);
extern u8 *D_807F5AF0;

s32 func_806151BC(void *arg0) {
    u8 sp1F;
    s32 var_v0;
    void *temp_v1;

    D_807F5AF0 += 1;
    func_80614F28(&sp1F);
    var_v0 = 1;
    if (sp1F != 0) {
        var_v0 = 0;
        arg0->unk4->unk7C = (s32)(sp1F - 1);
        temp_v1 = arg0->unk4;
        temp_v1->unk78 = (s32)(temp_v1->unk78 | 2);
    }
    return var_v0;
}
