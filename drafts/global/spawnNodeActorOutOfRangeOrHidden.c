// func_807280C8 (src/global/1295B0.c): stage 6; score 55. Instruction schedule matches target 100% (split dx and dead unk210 read steer cvt.s.w and add.s); remaining diff is 3 temporary float registers (/, /, /).
u8 func_807280C8(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dxy;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210;
    dx -= arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    if (C1PLAYERS[0].unk210 && C1PLAYERS[0].unk210) {} // FAKE: steer cvt.s.w schedule
    ret = 0;
    dxy = (dx * dx) + (dy * dy);
    dz = (dz * dz) + dxy;
    if (arg1 < dz) {
        ret = 1;
    }
    if (ret == 0) {
        ret = (arg0->unk18->unk5C & 0x40) == 0;
        if (ret != 0) {
            ret = (arg0->unk46 & 0x20) == 0;
            if (ret != 0) {
                ret = mapChunkIsVisibleForPlayer(0, arg0->unk40) == 0;
            }
        }
    }
    return ret;
}
