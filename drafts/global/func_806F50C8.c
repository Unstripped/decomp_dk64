// func_806F50C8 (src/global/F9450.c): Stage 4: reconstructed node allocation and tail insertion; local stack layout remains unmatched
void *func_80610FE8(?);                             /* extern */
? func_806357F8(s16, f32 *, f32 *, f32 *, ? *, ? *, ? *, ? *, ? *, s32); /* extern */
s8 func_806F4E74(s16);                              /* extern */
s32 func_806F4EBC(f32, f32);                        /* extern */
extern ? D_80753EFC;
extern s32 D_80754244;
extern s16 D_807FD720;
extern void *D_807FD72C;

void func_806F50C8(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    void *sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    ? sp54;
    ? sp50;
    ? sp4C;
    ? sp48;
    ? sp44;
    s32 sp40;
    s32 temp_v0;
    s8 temp_v0_3;
    void **var_v1;
    void *temp_v0_2;
    void *var_v0;

    func_806357F8(arg0, &sp60, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48, &sp44, 1);
    if ((arg5 != 0) || ((temp_v0 = func_806F4EBC(sp60, sp58), sp40 = temp_v0, ((D_807FD720 < temp_v0) == 0)) && (temp_v0 >= 0))) {
        temp_v0_2 = func_80610FE8(0x1C);
        temp_v0_2->unk8 = (s16) (s32) sp60;
        temp_v0_2->unkA = (s16) (s32) sp5C;
        temp_v0_2->unkC = (s16) (s32) sp58;
        temp_v0_2->unk0 = arg0;
        sp64 = temp_v0_2;
        temp_v0_3 = func_806F4E74(arg1);
        sp64->unk4 = (s16) *(&D_80753EFC + (temp_v0_3 * 0x14));
        sp64->unkE = 0;
        var_v1 = &D_807FD72C;
        sp64->unk2 = arg1;
        sp64->unk10 = arg2;
        sp64->unk6 = -1;
        sp64->unk12 = arg3;
        sp64->unk14 = temp_v0_3;
        sp64->unk18 = 0;
        sp64->unk13 = arg4;
        if (arg5 != 0) {
            var_v0 = D_807FD72C;
        } else {
            var_v0 = *(D_80754244 + (sp40 * 4));
            var_v1 = (sp40 * 4) + D_80754244;
        }
        if (var_v0 != NULL) {
            do {
                var_v1 = var_v0 + 0x18;
                var_v0 = var_v0->unk18;
            } while (var_v0 != NULL);
        }
        *var_v1 = sp64;
    }
}
