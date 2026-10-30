// effectWaterBuildMeshGdl (src/global/63EC0.c): stage 3 (EffC2): frame 0x98 vs 0x90 only real diff (16 text lines = frame/spill offsets + multu a1,t7 operand order). Wins vs old draft: segLen = (countX - x + 1) >= 17 ? 16 : ... (branch sense bnez), vtxNext += before vtxStart += in the tail update. Facts: expected function-level order high->low is vtxStart(0x8c) vtxNext countX ? x +4 done(0x68) ... total(0x40, lowest); region needs 2 fewer words: removing any 2 of the 3 tail Gfx macros (raw words writes) gives 0x90 but changes code; sibling block-locals overlap (2 sibling '{s32 p;}' cost +8 total). Narrow u8/s16 locals, k/i merge, rowEnd/x merge (permuter find) do not fix it.
typedef struct EffC2MeshBuilder {
    Gfx *(*fn)(void *, EffectNode *, u8);
    u8 pad4[0x14];
} EffC2MeshBuilder;

typedef struct EffC2MeshSub {
    u8 pad0[0x46];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    u8 pad4E[0x66 - 0x4E];
    u8 unk66;
} EffC2MeshSub;

extern EffC2MeshBuilder D_80748A94[];
extern s32 D_807F93EC;

void effectWaterBuildMeshGdl(void *arg0, void *arg1, EffectNode *water) {
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
    gdl = D_80748A94[((EffC2MeshSub *)water->unk0)->unk66].fn(arg0, water, ((EffC2MeshSub *)water->unk0)->unk66);
    step = water->unk2C;
    countX = ((((EffC2MeshSub *)water->unk0)->unk4A - ((EffC2MeshSub *)water->unk0)->unk46) / step) + 1;
    countZ = ((((EffC2MeshSub *)water->unk0)->unk4C - ((EffC2MeshSub *)water->unk0)->unk48) / step) + 1;
    rowEnd = countX + 1;
    total = rowEnd * (countZ + 1);
    vtxNext = rowEnd;
    vtxStart = 0;
    x = 0;
    done = 0;
    do {
        segLen = (countX - x + 1) >= 17 ? 16 : (countX - x + 1);
        gSPVertex(gdl++, osVirtualToPhysical((u8 *)arg1 + vtxStart * 16), segLen, 0);
        gSPVertex(gdl++, osVirtualToPhysical((u8 *)arg1 + vtxNext * 16), segLen, 16);
        k = 0;
        for (i = 0; i < segLen - 1; i++) {
            gSP2Triangles(gdl++, k + 1, k, k + 16, 0, k + 16, k + 17, k + 1, 0);
            D_807F93EC += 2;
            k++;
        }
        x += segLen - 1;
        vtxNext += segLen - 1;
        vtxStart += segLen - 1;
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
