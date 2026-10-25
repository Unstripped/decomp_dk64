// func_806E2B20 (src/global/E4090.c): stage 5, 8 diff lines: only the z-result float reg (target add.s f0 + mfc1 a2,f0; ours f8, then add.d f8 vs f10). Fixes found: do { temp3 = sp68; } while (0); copy in loop body (z uses temp3 as additive term) fixes the late z1 load schedule and y0/z0 f-regs; bare assignment does not. Permuter 500s from here no better.
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 func_80671E00(f32, f32, f32, f32, void *, void *, s32, s32);

u8 func_806E2B20(void *arg0) {
    f32 temp3;
    f32 temp2;
    f32 temp1;
    f32 var_fs1;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s16 sp66;
    s16 sp64;
    u8 sp63;

    sp63 = 0;
    var_fs1 = 0.0f;
    actorGetNodePos(arg0, 4, &sp78, &sp70, &sp68);
    actorGetNodePos(arg0, 0xA, &sp7C, &sp74, &sp6C);
    for (; var_fs1 <= 1.0 && sp63 == 0; var_fs1 += 0.2) {
        do {
            temp3 = sp68;
        } while (0);
        sp63 = func_80671E00(((sp7C - sp78) * var_fs1) + sp78, ((sp74 - sp70) * var_fs1) + sp70, ((sp6C - sp68) * var_fs1) + temp3, 10.0f, &sp66, &sp64, 0, 0);
    }
    return sp63;
}
