// func_806FB3D0 (src/global/FCCD0.c): no note
u8 func_806FB3D0(u8 arg0, u8 arg1) {
    u8 player;
    s32 playerOffset;
    void* players;

    player = arg0;
    playerOffset = (arg1 << 4) - arg1;
    players = D_80754280;
    if (!player) {
    }
    playerOffset = (playerOffset << 2) - playerOffset;
    return *((u8*) players + (playerOffset << 4) + (arg0 * 0x30) + 0x2C);
}
