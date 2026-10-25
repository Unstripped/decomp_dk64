// func_806FB370 (src/global/FCCD0.c): stage 6: target arithmetic/control flow; only register allocation remains
void func_806FB370(u8 arg0, u8 arg1, u8 arg2) {
    s32 playerOffset;
    u8 *slot;

    playerOffset = (arg1 << 4) - arg1;
    playerOffset = (playerOffset << 2) - playerOffset;
    slot = (u8 *)D_80754280 + (playerOffset << 4) + (arg0 * 0x30);
    if (slot[0x2D] == 0) {
        slot[0x2C] = arg2;
    }
}
