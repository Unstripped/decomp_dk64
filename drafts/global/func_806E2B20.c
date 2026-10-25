// func_806E2B20 (src/global/E4090.c): G23: structure+frame (0x90, dead f32 slots above locals) match; only scheduling differs: target loads z1 (0x6C) after the stack-arg stores/add.s fa0, ours hoists it before; also float temp regs. Tried inline/temp per-coordinate (all perms), operand forms, array locals, permuter 200s. Behaviourally equivalent.
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
        temp3 = ((sp6C - sp68) * var_fs1) + sp68;
        sp63 = func_80671E00(((sp7C - sp78) * var_fs1) + sp78, ((sp74 - sp70) * var_fs1) + sp70, temp3, 10.0f, &sp66,
                             &sp64, 0, 0);
    }
    return sp63;
}
