// func_80709464 (src/global/10D2D0.c): Stage 6 exact except multu operand order: target multu v0,t9; C emits multu t9,v0.
void func_80709464(u8 arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = func_8070943C();
    temp_v1 = (arg0 * 0x306) + (s32) D_807FC950;
    *(u8 *) (temp_v1 + 0x2FD) = 0;
    *(s8 *) (temp_v1 + 0x2FB) = (s8) (*(u8 *) (temp_v1 + 0x2FC) * temp_v0);
}
