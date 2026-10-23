// func_80660520 (src/global/63EC0.c): logic matches, frame size 0xB0 vs 0xA0 due to extra local temps
extern u8 D_80748AA5[];
f32 func_806608FC(R1C_Water *, s16, s16, u8);

void func_80660520(Vtx *vtx, R1C_Water *water) {
    R1C_SubStruct *sub;
    s16 step;
    s16 minX, maxX, minZ, maxZ;
    s32 countX, countZ;
    s16 x, z;
    s32 i, j;
    f32 baseHeight;
    f32 heightScale;
    u8 alphaMax, alphaBase;
    u8 flag;
    f32 h;
    f32 relH;

    step = water->unk2C;
    sub = water->unk0;
    minX = sub->unk46;
    maxX = sub->unk4A;
    minZ = sub->unk48;
    maxZ = sub->unk4C;
    alphaMax = sub->unk65;
    alphaBase = sub->unk64;
    countX = ((maxX - minX) / step) + 1;
    countZ = ((maxZ - minZ) / step) + 1;
    z = minZ;
    j = 0;
    baseHeight = (f32)sub->unk4E + water->unk4;
    flag = D_80748AA5[sub->unk66 * 0x18];
    heightScale = sub->unk10 + sub->unkC;
    if (countZ >= 0) {
        do {
            x = minX;
            i = 0;
            if (countX >= 0) {
                do {
                    if (maxX < x) {
                        x = maxX;
                    }
                    if (maxZ < z) {
                        z = maxZ;
                    }
                    h = func_806608FC(water, x, z, flag);
                    vtx->v.ob[1] = h * 3.0f;
                    relH = (h - baseHeight) / heightScale;
                    vtx->v.cn[3] = (u32)(relH * (f32)alphaMax + (f32)alphaBase);
                    vtx++;
                    x += step;
                    i++;
                } while (i != countX + 1);
            }
            j++;
            z += step;
        } while (j <= countZ);
    }
}
