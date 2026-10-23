// func_80660070 (src/global/63EC0.c): from .scratch/R4A63EC0/func_80660070_best.c
typedef struct R4A_SubStruct0070 {
    u8 pad0[0x46];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    u8 pad4E[0x66 - 0x4E];
    u8 unk66;
} R4A_SubStruct0070;

typedef Gfx *(*R4A_DLFunc)(void *, EffectNode *, u8);
extern R4A_DLFunc D_80748A94[];
extern s32 D_807F93EC;

void func_80660070(void *vtx, void *dl, EffectNode *water) {
    s32 countX, countZ;
    s32 step;
    R4A_SubStruct0070 *sub;
    Gfx *gdl;
    s32 vtxStep;
    s32 rowLen;
    s32 i, j;
    s32 segLen;
    s32 vtx0;
    u8 done;
    u8 type;
    s32 total;
    s32 rem;
    s32 idx0, idx1, idx2, idx3;

    D_807F93EC = 0;
    type = ((R4A_SubStruct0070 *)water->unk0)->unk66;
    sub = (R4A_SubStruct0070 *)water->unk0;
    step = water->unk2C;
    gdl = D_80748A94[type](vtx, water, type);

    countX = ((sub->unk4A - sub->unk46) / step) + 1;
    countZ = ((sub->unk4C - sub->unk48) / step) + 1;
    rowLen = countX + 1;
    total = rowLen * (countZ + 1);
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

        idx0 = 0;
        idx1 = idx0 + 1;
        idx2 = idx0 + 16;
        idx3 = idx0 + 17;
        rem = (segLen - 1) & 3;
        for (i = 0; i < rem; i++) {
            gSP2Triangles(gdl++, idx0, idx1, idx2, 0, idx1, idx3, idx2, 0);
            D_807F93EC += 2;
            idx0++;
            idx1++;
            idx2++;
            idx3++;
        }

        idx0 = i;
        idx1 = idx0 + 1;
        idx2 = idx0 + 16;
        idx3 = idx0 + 17;
        for (; i < segLen - 1; i += 4) {
            gSP2Triangles(gdl++, idx0, idx1, idx2, 0, idx1, idx3, idx2, 0);
            D_807F93EC += 2;
            idx0++; idx1++; idx2++; idx3++;
            gSP2Triangles(gdl++, idx0, idx1, idx2, 0, idx1, idx3, idx2, 0);
            D_807F93EC += 2;
            idx0++; idx1++; idx2++; idx3++;
            gSP2Triangles(gdl++, idx0, idx1, idx2, 0, idx1, idx3, idx2, 0);
            D_807F93EC += 2;
            idx0++; idx1++; idx2++; idx3++;
            gSP2Triangles(gdl++, idx0, idx1, idx2, 0, idx1, idx3, idx2, 0);
            D_807F93EC += 2;
            idx0++; idx1++; idx2++; idx3++;
        }

        j += segLen - 1;
        vtxStep += segLen - 1;
        vtx0 += segLen - 1;
        if (j == countX) {
            j = 0;
            vtx0++;
            vtxStep++;
        }
        if (vtxStep == total) {
            done = 1;
        }
    } while (!done);

    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, 16, 1, 0);
    gSPEndDisplayList(gdl++);
}
