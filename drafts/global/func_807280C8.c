// func_807280C8 (src/global/1295B0.c): stage 6 near-miss (15 diff lines): only FP load/mul schedule + a2/a1 regs differ vs target; shape ret=0; if(arg1<sum) ret=1; if(ret==0){ret=(x&0x40)==0; if(ret!=0){...}} with dz,dx,dy statement order; needs C1Node/C1PLAYERS (C1PlayerView f32 unk210/214/218 at 0x210..0x218, size 0x2F0). permuter 600s found nothing.
s32 mapChunkIsVisibleForPlayer(s32, s16);

u8 func_807280C8(C1Node *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    ret = 0;
    if (arg1 < ((dz * dz) + ((dx * dx) + (dy * dy)))) {
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
