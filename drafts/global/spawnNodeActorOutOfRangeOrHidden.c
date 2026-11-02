// spawnNodeActorOutOfRangeOrHidden (src/global/1295B0.c): Stage 6 park, score 4 (was 8): float code exact (ring order fixed by 'ret = arg1 < (dz*dz)+((dx*dx)+(dy*dy))' + dx as one expression); remaining 2 insns: ret web v0 (cmp value candidate, ret==0 test store-forwarded to the cmp) vs target v1, and bnez+move vs bnezl. FAKE if (arg0) {}. 'ret = 0; if (cmp) ret = 1;' form gives the target ret shape but float schedule 16 off. Tried ret types, x=x, dead ret tests, 2-var, else forms, 4k dead-test hill-climb.
u8 spawnNodeActorOutOfRangeOrHidden(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    if (arg0) {} // FAKE: steers ret candidate / schedule
    ret = arg1 < (dz * dz) + ((dx * dx) + (dy * dy));
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
