// func_80660070 (src/global/63EC0.c): mesh display list generation with 4x unrolled G_TRI2
typedef Gfx *(*R1C_DLFunc)(void *, R1C_Water *, u8);
extern R1C_DLFunc D_80748A94[];
extern s32 D_807F93EC;

void func_80660070(void *vtx, void *dl, R1C_Water *water) {
    s32 countX, countZ;
    s32 step;
    R1C_SubStruct *sub;
    Gfx *gdl;
    s32 vtxStep;
    s32 rowLen;
    s32 i, j;
    s32 segLen;
    s32 vtx0, vtx1;
    s32 done;
    u8 type;

    D_807F93EC = 0;
    type = water->unk0->unk66;
    sub = water->unk0;
    step = water->unk2C;
    gdl = D_80748A94[type](vtx, water, type);

    countX = ((sub->unk4A - sub->unk46) / step) + 1;
    rowLen = countX + 1;
    vtxStep = rowLen;
    vtx0 = 0;
    done = 0;
    j = 0;

    do {
        segLen = (countX - j) + 1;
        if (segLen >= 17) {
            segLen = 16;
        }

        gSPVertex(gdl++, osVirtualToPhysical((u8 *)vtx + vtx0 * 16), segLen, 0);
        gSPVertex(gdl++, osVirtualToPhysical((u8 *)vtx + vtxStep * 16), segLen, 16);

        for (i = 0; i < segLen - 1; i++) {
            gSP2Triangles(gdl++, i, i + 1, i + 16, 0, i + 1, i + 17, i + 16, 0);
            D_807F93EC += 2;
        }

        j += segLen - 1;
        vtxStep += segLen - 1;
        vtx0 += segLen - 1;
        if (j == countX) {
            j = 0;
            vtx0++;
            vtxStep++;
        }
        if (vtxStep == rowLen * (((sub->unk4C - sub->unk48) / step) + 2)) {
            done = 1;
        }
    } while (!done);

    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, 0, 1, 0);
    gSPEndDisplayList(gdl++);
}
