// func_806F7FD0 (src/global/FCCD0.c): Correct instruction count and argument home-store; register allocation is shifted t6/t7/t8 to t7/t8/t9.
extern s32 D_80754280;

s32 func_806F7FD0(u8 arg0) {
    s32 index = arg0 & 0xFF;

    return (index * 0x2D0) + D_80754280;
}
