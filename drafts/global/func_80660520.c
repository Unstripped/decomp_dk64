// func_80660520 (src/global/63EC0.c): from .scratch/R4A63EC0/func_80660520_best.c
typedef struct R4A_SubStruct520 {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x46 - 0x14];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    u8 pad50[0x64 - 0x50];
    u8 unk64;
    u8 unk65;
    u8 unk66;
} R4A_SubStruct520;

f32 func_806608FC(EffectNode *, s32, s32, u8);

void func_80660520(Vtx *vtx, EffectNode *water) {
    R4A_SubStruct520 *sub;
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
    sub = (R4A_SubStruct520 *)water->unk0;
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
    flag = D_80748AA5[sub->unk66].unk0;
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
