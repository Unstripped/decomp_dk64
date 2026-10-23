// func_80660D38 (src/global/63EC0.c): logic matches, frame size difference due to local temps
f32 func_80612794(s16);

s16 func_80660D38(Vtx *vtx, R1C_Water *water) {
    s16 minX, minZ, maxX, maxZ, step;
    s32 countX, countZ;
    s16 x, z;
    s32 i, j;
    R1C_SubStruct *sub;
    s16 posX, posZ;
    f32 fx, fz;
    s32 angleX, angleZ;

    step = water->unk2C;
    sub = water->unk0;
    minX = sub->unk46;
    maxX = sub->unk4A;
    minZ = sub->unk48;
    maxZ = sub->unk4C;
    countX = ((maxX - minX) / step) + 1;
    countZ = ((maxZ - minZ) / step) + 1;
    z = minZ;
    for (j = 0; j <= countZ; j++) {
        x = minX;
        for (i = 0; i <= countX; i++) {
            sub = water->unk0;
            if (maxX < x) {
                x = maxX;
            }
            if (maxZ < z) {
                z = maxZ;
            }
            fx = (f32)x;
            fz = (f32)z;
            angleX = water->unk38 + (s32)(sub->unk1C * fx);
            posX = (func_80612794(angleX & 0xFFF) * sub->unk24) + fx;
            angleZ = water->unk3C + (s32)(sub->unk20 * fz);
            posZ = (func_80612794(angleZ & 0xFFF) * sub->unk28) + fz;
            vtx->v.ob[0] = posX * 3;
            vtx->v.ob[2] = posZ * 3;
            vtx->v.tc[0] = (s32)(fx * sub->unk0) % 0x7FFF;
            vtx->v.tc[1] = (s32)(fz * sub->unk0) % 0x7FFF;
            vtx++;
            x += step;
        }
        z += step;
    }
    return posZ;
}
