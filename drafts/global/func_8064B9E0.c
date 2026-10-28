// func_8064B9E0 (src/global/478F0.c): stage 4-5: frame/regs identical; remaining diff: target li order x,y,z (t9,t0,t1) but stores z,y,x (x in b delay slot); source order z,y,x gives li z,y,x (first/last li regs swapped). Tried all 36 decl x assign perms, s16 p[3] perms, s32/s16 temps, permuter 240s (no gain). parked NON_MATCHING.
void actorListSetPosById(s16, f32, f32, f32);

void func_8064B9E0(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 x, y, z;
    switch (b) {
        case 0:
            z = 0x16A;
            y = 6;
            x = 0x3A4;
            break;
        case 1:
            z = 0x20A;
            y = 0x7A;
            x = 0x439;
            break;
        case 2:
            z = 0x237;
            y = 0x7A;
            x = 0x35D;
            break;
        case 3:
            z = 0x120;
            y = 0x11;
            x = 0x502;
            break;
        case 4:
            z = 0x172;
            y = 0x12;
            x = 0x28A;
            break;
    }
    actorListSetPosById(5, (f32)x, (f32)y, (f32)z);
}
