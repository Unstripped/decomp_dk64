// func_806F9CD0 (src/global/FCCD0.c): Best permuter candidate score 8: comma expression fixes base-plus-index operand order; remaining stack index slot.
extern void *D_80754280;

void func_806F9CD0(s32 arg0) {
    s32 sp2C;
    void *sp30;
    R1FCCD0bAllocRecord **temp_s0;

    sp2C = arg0 * 0x30;
    temp_s0 = (R1FCCD0bAllocRecord **)((u8 *)D_80754280 + (0, sp2C) + 0x28);
    func_806F9608(temp_s0);
    sp30 = *(void **)((u8 *)*temp_s0 + 0x14);
    func_806F96CC((R1FCCD0bEffect *)*temp_s0, arg0);
    func_806F9744(*temp_s0, arg0, (f32)*(s32 *)((u8 *)D_80754280 + sp2C + 8), (f32)*(s32 *)((u8 *)D_80754280 + sp2C + 0xC), 0);
    func_806F8DC4(sp30, 0, arg0);
    *(s16 *)((u8 *)*temp_s0 + 0x10) = 0;
}
