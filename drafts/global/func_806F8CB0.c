// func_806F8CB0 (src/global/FCCD0.c): m2c behavioural starter; 19-insn list clear.
extern s32 D_80754280;

void func_806F8CB0(s32 arg0) {
    s32 var_v1;
    void *var_v0;

    if (arg0 == 8) {
        var_v0 = (D_80754280 + (arg0 * 0x30))->unk28;
        var_v1 = 0;
        if (var_v0 != NULL) {
            do {
                var_v0->unkC = var_v1;
                var_v0 = var_v0->unk18;
                var_v1 += 2;
            } while (var_v0 != NULL);
        }
    }
}
