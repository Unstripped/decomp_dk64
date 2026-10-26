// func_8072818C (src/global/1295B0.c): stage 6 (10 diff lines): FP register/schedule only (mul.s order, multu a0,a0 placement). Reusing f32 r for dy (permuter hint) fixed stack/regs; statement order z,x,y. needs SpawnNode/C1PLAYERS; sqrtf(arg1) then (s32)(r*1.5).
u8 func_8072818C(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dz;
    f32 r;
    s32 t;
    s32 ret;

    r = sqrtf(arg1);
    ret = (arg0->unk18->unk5C & 2) != 0;
    if (ret) {
        ret = (arg0->unk46 & 0x20) == 0;
        if (ret) {
            ret = arg0->unk12 == 2;
            if (ret) {
                t = (s32)(r * 1.5);
                dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
                dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
                r = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
                ret = 0;
                if ((f32)(t * t) < ((dz * dz) + ((dx * dx) + (r * r)))) {
                    ret = 1;
                }
            }
        }
    }
    return ret;
}
