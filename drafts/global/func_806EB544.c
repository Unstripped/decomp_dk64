// func_806EB544 (src/global/EFDC0.c): near match: stack local expected at 0x1C, produced 0x18
? func_80614E78(void *, ?);                         /* extern */
s32 func_806F8AD4(?, u8, ?);                        /* extern */
? func_806F8BC4(s32, ?, ?, s32);                    /* extern */
extern void *D_807FBB40;
extern void *D_807FD580;

void func_806EB544(void) {
    s32 sp1C;
    s32 var_a3;

    sp1C = 2;
    var_a3 = 2;
    if (func_806F8AD4(3, D_807FD580->unk1A4, 2) != 0) {
        var_a3 = 3;
    }
    func_806F8BC4(var_a3, 0, 0, var_a3);
    D_807FBB40->unk154 = 0x60;
    D_807FBB40->unk155 = 0;
    D_807FD580->unk1A3 = 0;
    func_80614E78(D_807FBB40, 0x4B);
}
