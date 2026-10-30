// func_80660070 (src/global/63EC0.c): stage 5 (EffB): structure matches incl. uopt-unrolled tri loop (plain for loop, tris (k+1,k,k+16),(k+16,k+17,k+1)); remaining 21 text lines: frame 0x98 vs 0x90 (spill-slot layout/decl order), multu/slot/sched diffs. arg0=dl buffer passed to callback, arg1=vertex buffer (EffectNode vtx/dl fields look swapped)
typedef struct EffBMeshBuilder {
    Gfx *(*fn)(void *, EffectNode *, u8);
    u8 pad4[0x14];
} EffBMeshBuilder;

typedef struct EffBMeshSub {
    u8 pad0[0x46];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    u8 pad4E[0x66 - 0x4E];
    u8 unk66;
} EffBMeshSub;

extern EffBMeshBuilder D_80748A94[];
extern s32 D_807F93EC;

void func_80660070(void *arg0, void *arg1, EffectNode *water) {
    s32 countX;
    Gfx * gdl;
    s32 countZ;
    s32 vtxNext;
    s32 step;
    s32 total;
    s32 rowEnd;
    s32 segLen;
    s32 i;
    s32 vtxStart;
    s32 k;
    u8 done;
    s32 x;

    D_807F93EC = 0;
    gdl = D_80748A94[((EffBMeshSub *)water->unk0)->unk66].fn(arg0, water, ((EffBMeshSub *)water->unk0)->unk66);
    step = water->unk2C;
    countX = ((((EffBMeshSub *)water->unk0)->unk4A - ((EffBMeshSub *)water->unk0)->unk46) / step) + 1;
    countZ = ((((EffBMeshSub *)water->unk0)->unk4C - ((EffBMeshSub *)water->unk0)->unk48) / step) + 1;
    rowEnd = countX + 1;
    total = (countZ + 1) * rowEnd;
    vtxNext = rowEnd;
    vtxStart = 0;
    x = 0;
    done = 0;
    do {
        segLen = (countX - x + 1) < 17 ? (countX - x + 1) : 16;
        gSPVertex(gdl++, osVirtualToPhysical((u8 *)arg1 + vtxStart * 16), segLen, 0);
        gSPVertex(gdl++, osVirtualToPhysical((u8 *)arg1 + vtxNext * 16), segLen, 16);
        k = 0;
        for (i = 0; i < segLen - 1; i++) {
            gSP2Triangles(gdl++, k + 1, k, k + 16, 0, k + 16, k + 17, k + 1, 0);
            D_807F93EC += 2;
            k++;
        }
        x += segLen - 1;
        vtxStart += segLen - 1;
        vtxNext += segLen - 1;
        if (x == countX) {
            x = 0;
            vtxStart++;
            vtxNext++;
        }
        if (vtxNext == total) {
            done = 1;
        }
    } while (!done);
    gDPPipeSync(gdl++);
    gDPSetTextureLUT(gdl++, G_TT_NONE);
    gSPEndDisplayList(gdl++);
}
