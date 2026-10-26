// func_807280C8 (src/global/1295B0.c): stage 6, 5 diff lines: sum assigned back into dz; only cvt.s.w(arg1) schedule differs
s32 mapChunkIsVisibleForPlayer(s32, s16);

u8 func_807280C8(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    ret = 0;
    dz = ((dz * dz) + ((dx * dx) + (dy * dy)));
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
