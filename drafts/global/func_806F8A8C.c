// func_806F8A8C (src/global/FCCD0.c): 18-insn setter; body understood, parameter storage and delay-slot ordering remain.
s32 func_806F7FD0(s32);                             /* extern */

void func_806F8A8C(u8 arg0, s32 arg1, s32 arg2) {
    (func_806F7FD0(arg1 & 0xFF) + (arg0 * 0x30))->unk4 = (s16) arg2;
}
