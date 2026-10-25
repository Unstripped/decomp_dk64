// func_806FB3D0 (src/global/FCCD0.c): stage 6: target arithmetic/control flow; permuter improved 115 to 100 but no zero, remaining register allocation
u8 func_806FB3D0(u8 arg0, u8 arg1) {
    s32 playerOffset;

    playerOffset = (arg1 << 4) - arg1;
    playerOffset = ((playerOffset << 1) << 1) - playerOffset;
    return *((u8 *)D_80754280 + (playerOffset << 4) + (arg0 * 0x30) + 0x2C);
}
