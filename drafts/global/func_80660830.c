// func_80660830 (src/global/63EC0.c): regalloc diff only, 51 instructions match
typedef struct R1C_SubStruct {
    u8 pad[0x46];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    u8 pad2[0x61 - 0x4E];
    u8 unk61;
    u8 unk62;
    u8 unk63;
} R1C_SubStruct;

typedef struct R1C_Water {
    R1C_SubStruct *unk0;
    u8 pad[0x2C - 4];
    s16 unk2C;
} R1C_Water;

void func_80660830(Vtx *vtx, R1C_Water *water) {
    s16 minX, minZ, maxX, maxZ;
    s16 step;
    u32 total;
    s32 count;
    R1C_SubStruct *sub;
    u8 r, g, b;

    sub = water->unk0;
    step = water->unk2C;
    minX = sub->unk46;
    maxX = sub->unk4A;
    minZ = sub->unk48;
    maxZ = sub->unk4C;
    total = (((maxX - minX) / step) + 2) * (((maxZ - minZ) / step) + 2);
    r = sub->unk61;
    g = sub->unk62;
    b = sub->unk63;
    count = total - 1;
    if (total != 0) {
        do {
            vtx->v.cn[0] = r;
            vtx->v.cn[1] = g;
            vtx->v.cn[2] = b;
            vtx++;
        } while (count--);
    }
}
