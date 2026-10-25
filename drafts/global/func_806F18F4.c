// func_806F18F4 (src/global/F56F0.c): stage 5: exact size; only table value register is v1 rather than target v0
extern ? D_80752F38;
extern void *D_807FD580;

void func_806F18F4(s32 arg0, s32 arg1, s32 *arg2) {
    s32 temp_v1;

    temp_v1 = D_807FD580->unk8E - 0x16;
    if ((temp_v1 >= 0) && ((u32) temp_v1 < 4U)) {
        *(arg1 + (*arg2 * 8)) = 0x7F;
        (arg1 + (*arg2 * 8))->unk1 = 1;
        (arg1 + (*arg2 * 8))->unk2 = 0;
        (arg1 + (*arg2 * 8))->unk4 = (u16) *(&D_80752F38 + (temp_v1 * 2));
        (arg1 + (*arg2 * 8))->unk6 = 0;
        *arg2 += 1;
    }
}
