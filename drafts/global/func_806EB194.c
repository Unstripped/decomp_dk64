// func_806EB194 (src/global/EFDC0.c): m2c starter; callback queue dispatch
s32 actorTableContains(s32, u8 *, ?);               /* extern */
extern ? D_80752C70;
extern s32 D_807FC924;
extern u8 D_807FC929;

void func_806EB194(void) {
    s32 temp_a0;
    void *var_v0;

    var_v0 = D_807FC924 + (D_807FC929 * 0x2F0);
    if (var_v0->unk29C >= 0) {
        temp_a0 = var_v0->unk2A0;
        if ((temp_a0 != 0) && ((actorTableContains(temp_a0, &D_807FC929, 0x2F0) == 0) || (var_v0 = D_807FC924 + (D_807FC929 * 0x2F0), (var_v0->unk2A0->unk54 != var_v0->unk2A4)))) {
            (D_807FC924 + (D_807FC929 * 0x2F0))->unk2A0 = 0;
            var_v0 = D_807FC924 + (D_807FC929 * 0x2F0);
        }
        *(&D_80752C70 + (var_v0->unk29C * 4))();
        var_v0 = D_807FC924 + (D_807FC929 * 0x2F0);
    }
    var_v0->unk29C = -1;
}
