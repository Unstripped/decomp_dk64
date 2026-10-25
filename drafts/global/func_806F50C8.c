// func_806F50C8 (src/global/F9450.c): Stage 4: stack-slot layout remains
extern F9F1_Node **D_80754244;
extern F9F1_Node *D_807FD72C;
extern s16 D_807FD720;
extern s16 D_80753EFC[];
void func_806357F8();
void *func_80610FE8(s32);
s32 func_806F4EBC(f32, f32);
s32 func_806F4E74(s16);

void func_806F50C8(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    F9F1_Node *sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 temp_v0;
    s32 temp_v0_3;
    F9F1_Node **var_v1;
    F9F1_Node *temp_v0_2;
    F9F1_Node *var_v0;

    func_806357F8(arg0, &sp60, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48, &sp44, 1);
    if ((arg5 != 0) || ((temp_v0 = func_806F4EBC(sp60, sp58), sp40 = temp_v0, (D_807FD720 >= temp_v0)) && (temp_v0 >= 0))) {
        temp_v0_2 = func_80610FE8(0x1C);
        temp_v0_2->unk8 = (s16)sp60;
        temp_v0_2->unkA = (s16)sp5C;
        temp_v0_2->unkC = (s16)sp58;
        temp_v0_2->unk0 = arg0;
        sp64 = temp_v0_2;
        temp_v0_3 = func_806F4E74(arg1);
        sp64->unk4 = D_80753EFC[temp_v0_3 * 0xA];
        sp64->unkE = 0;
        var_v1 = &D_807FD72C;
        sp64->unk2 = arg1;
        sp64->unk10 = arg2;
        sp64->unk6 = -1;
        sp64->unk12 = arg3;
        sp64->unk14 = temp_v0_3;
        sp64->next = NULL;
        sp64->unk13 = arg4;
        if (arg5 != 0) {
            var_v0 = D_807FD72C;
        } else {
            var_v0 = D_80754244[sp40];
            var_v1 = &D_80754244[sp40];
        }
        if (var_v0 != NULL) {
            do {
                var_v1 = &var_v0->next;
                var_v0 = var_v0->next;
            } while (var_v0 != NULL);
        }
        *var_v1 = sp64;
    }
}
