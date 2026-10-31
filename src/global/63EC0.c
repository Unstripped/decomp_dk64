#include "common.h"
#include "actor.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

typedef struct EffectSubNode {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x10];
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0xC];
    union {
        struct {
            u8 pad50[0x14];
            u8 val;
            u8 pad65;
        };
        s16 unk50[11];
    };
    u8 unk66;
    u8 unk67;
} EffectSubNode;

typedef struct EffectNode {
    union {
        EffectSubNode *sub;
        EffectSubNode *target;
        EffectSubNode *unk0;
    };
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    void *dl[2];
    void *vtx[2];
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    u8 pad48[2];
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 pad4D[3];
    struct EffectNode *next;
} EffectNode;

typedef struct EffectTableEntry {
    void (*fn0)();
    void (*fn1)();
    void (*fn2)(EffectNode *);
    void *res0;
    void *res1;
    union {
        u32 flags;
        struct {
            u8 pad14[2];
            u8 unk16;
            u8 pad17;
        };
    };
} EffectTableEntry;

typedef struct TextureCacheEntry {
    void *unk0;
    u8 pad4[0x14];
} TextureCacheEntry;

typedef struct EffectTableFlags {
    u8 unk0;
    u8 pad1[0x17];
} EffectTableFlags;

typedef struct EffectBufferEntry {
    u8 unk0;
    u8 pad1[0x1C7];
} EffectBufferEntry;

void *assetLoad(s32, s32, s32, s32);
void effectNodeApproachTargetPos(EffectNode *);
void screenShakeStep(void);
Gfx *effectWaterSetScissor(Gfx *, EffectNode *);
void effectWaterBuildMeshGdl(void *, void *, EffectNode *);
Gfx *effectBuildMipmapGdl(Gfx *, s32, u8);

extern EffectNode *D_807F93C0;
extern EffectTableEntry D_80748A90[];
extern TextureCacheEntry D_80748A9C[];
extern EffectTableFlags D_80748AA5[];
extern EffectBufferEntry *D_807F6C18;
extern s32 D_807FBB60;
extern u8 D_807444FC;
extern u8 D_807F93C4;
extern f32 D_807F93C8[2];
extern f32 D_807F93D0;
extern f32 D_807F93D4;
extern f32 D_807F93D8;
extern f32 D_807F93DC;
extern f32 D_807F93E0;
extern f32 D_807F93E4;
extern f32 D_807F93E8;

typedef struct WaterTargetData {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x30];
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 pad69[3];
} WaterTargetData;

typedef struct WaterNodeData {
    WaterTargetData *target;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    void *dl[2];
    void *vtx[2];
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[2];
    struct WaterNodeData *next;
} WaterNodeData;

typedef struct WaterTypeEntry {
    void (*func)(u8);
    u8 pad4[0x10];
    u8 unk14;
    u8 pad15[3];
} WaterTypeEntry;

extern s32 D_8076A0A8;

void *heapAlloc(s32);
void effectWaterSetMeshPositionsUV(Vtx *, EffectNode *);
void effectWaterSetMeshHeightsAlpha(Vtx *, EffectNode *);

void func_8065F1C0(u8 *arg0) {
    u8 pad[0x1C];
    s32 i;
    WaterTargetData *base;
    WaterNodeData **var_fp;
    s32 count;

    for (i = 0; i < 9; i++) {
        ((WaterTypeEntry *)D_80748A90)[i].unk14 = 0;
    }

    var_fp = (WaterNodeData **)&D_807F93C0;
    if (D_8076A0A8 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    D_807F93C0 = NULL;
    count = *(u8 *)(arg0 + *(s32 *)(arg0 + 0x4C) + 3);
    D_807F93C4 = 0;

    if (count == (count * 0)) {  // FAKE: extra use of count steers the v0/v1 pick
        return;
    }

    base = (WaterTargetData *)(arg0 + *(s32 *)(arg0 + 0x4C) + 4);
    for (i = 0; i < count; i++) {
        WaterNodeData *node = heapAlloc(0x54);
        s32 temp_s3;
        s32 temp_s4;
        s32 temp_s1;
        u8 temp_a0;
        WaterTypeEntry *entry2;

        *var_fp = node;
        node->target = &base[i];
        node->unk2C = base[i].unk44;
        node->unk4 = 0.0f;
        node->unkC = 0.0f;
        node->unk8 = 0.0f;
        node->unk30 = 0;
        node->unk34 = 0;
        node->unk38 = 0;
        node->unk3C = 0;
        node->unk4A = 0;
        node->unk4B = 0;
        node->x = base[i].unkC;
        node->y = base[i].unk10;
        node->z = 0.0f;
        node->unk4D = 0;
        var_fp = &node->next;

        if (((D_8076A0A8 == 0x53) || (D_8076A0A8 == 0xC5)) && (i == 0)) {
            node->unk4D = 1;
        }

        temp_s3 = ((s32)(base[i].unk4A - base[i].unk46) / base[i].unk44) + 1;
        temp_s4 = ((s32)(base[i].unk4C - base[i].unk48) / base[i].unk44) + 1;
        node->unk48 = (temp_s3 + 1) * (temp_s4 + 1);

        node->dl[0] = heapAlloc(node->unk48 * 0x10);
        effectWaterSetMeshPositionsUV((Vtx *)node->dl[0], (EffectNode *)node);
        effectWaterSetMeshHeightsAlpha((Vtx *)node->dl[0], (EffectNode *)node);

        node->dl[1] = heapAlloc(node->unk48 * 0x10);
        effectWaterSetMeshPositionsUV((Vtx *)node->dl[1], (EffectNode *)node);
        effectWaterSetMeshHeightsAlpha((Vtx *)node->dl[1], (EffectNode *)node);

        temp_s1 = (temp_s3 * temp_s4) + (((temp_s3 / 16) + 1) * temp_s4 * 2);
        temp_s1 += 0xC8;
        node->vtx[0] = heapAlloc(temp_s1 << 3);
        node->vtx[1] = heapAlloc(temp_s1 * 8);

        temp_a0 = base[i].unk66;
        entry2 = (WaterTypeEntry *)D_80748A90 + temp_a0;
        if (entry2->unk14 == 0) {
            entry2->func(temp_a0);
            entry2->unk14 = 1;
        }
        node->next = NULL;
    }
}

void effectNodeSetTargetPosition(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    EffectNode *node = D_807F93C0;

    if (node != NULL && arg0 != 0) {
        do {
            node = node->next;
            arg0--;
            if (node == NULL) {
                break;
            }
        } while (arg0 != 0);
    }
    if (node != NULL) {
        node->x = arg1;
        node->y = arg2;
        node->z = arg3;
    }
}

void effectNodeApproachTargetPos(EffectNode *arg0) {
    if (arg0->target->unkC < arg0->x) {
        arg0->target->unkC += arg0->z;
        if (arg0->x < arg0->target->unkC) {
            arg0->target->unkC = arg0->x;
        }
    } else {
        arg0->target->unkC -= arg0->z;
        if (arg0->target->unkC < arg0->x) {
            arg0->target->unkC = arg0->x;
        }
    }

    if (arg0->target->unk10 < arg0->y) {
        arg0->target->unk10 += arg0->z;
        if (arg0->y < arg0->target->unk10) {
            arg0->target->unk10 = arg0->y;
        }
    } else {
        arg0->target->unk10 -= arg0->z;
        if (arg0->target->unk10 < arg0->y) {
            arg0->target->unk10 = arg0->y;
        }
    }
}

u8 effectGetTableFlag(EffectNode *arg0) {
    return D_80748AA5[arg0->target->unk66].unk0;
}

void effectUpdateNodes(void) {
    EffectNode *node = D_807F93C0;

    if (node != NULL) {
        do {
            node->unk4C = 0;
            effectNodeApproachTargetPos(node);
            node = node->next;
        } while (node != NULL);
    }
    if (!(D_807FBB60 & 2)) {
        screenShakeStep();
    }
}

typedef struct WaterTargetUpdateView {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x10];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x1A];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[1];
    u8 pad52[0x15];
    u8 unk67;
} WaterTargetUpdateView;

s32 effectCheckTargetActive(EffectSubNode *);
void effectWaterSetMeshColors(Vtx *, EffectNode *);
void effectNodeComputeBounds(EffectNode *, f32, f32, f32, u8, void *, void *);
s32 mapBspBoxInFrustum(s16, s16, s16, s16, s32, s16, f32, f32, f32, f32, void *);
s32 matrix4Invert(f32 (*)[4], f32 (*)[4]);
extern f32 D_807F5FAC;
extern void *D_807FC924;

void func_8065F678(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    EffectNode *node;
    u8 *var_s1;
    s32 var_s5;
    f32 temp_fs1;
    f32 temp_fs0;
    s32 pad1;
    u8 sp120[0x138];
    u32 pad[2];
    f32 spD8[4][4];
    f32 sp98[4][4];

    node = D_807F93C0;
    var_s5 = 0;

    if (node != NULL) {
        do {
            if (effectCheckTargetActive(node->target) != 0 && !(node->unk4C & 1)) {
                temp_fs0 = (f32)((WaterTargetUpdateView *)node->target)->unk4E + node->unk4;
                temp_fs1 = ((WaterTargetUpdateView *)node->target)->unk10 + ((WaterTargetUpdateView *)node->target)->unkC;
                if (((WaterTargetUpdateView *)node->target)->unk67 == 1) {
                    var_s1 = (u8 *)&D_807F6C18[((WaterTargetUpdateView *)node->target)->unk50[0]] + 0x88;
                } else {
                    if (var_s5 == 0) {
                        guMtxL2F(spD8, (Mtx *)((u8 *)D_807FC924 + (arg3 * 0x2F0) + (D_807444FC << 6) + 8));
                        var_s5 = 1;
                        matrix4Invert(sp98, spD8);
                    }
                    var_s1 = sp120;
                    effectNodeComputeBounds(node, arg0, arg1, arg2, arg3, sp98, sp120);
                }
                if (mapBspBoxInFrustum(((WaterTargetUpdateView *)node->target)->unk46, (s16)(temp_fs0 - temp_fs1), ((WaterTargetUpdateView *)node->target)->unk48, ((WaterTargetUpdateView *)node->target)->unk4A,
                                  (s32)(temp_fs0 + temp_fs1), ((WaterTargetUpdateView *)node->target)->unk4C, arg0, arg1, arg2, D_807F5FAC, var_s1) != 0 || node->pad4D[0] != 0) {
                    if ((f64)((WaterTargetUpdateView *)node->target)->unk24 != 0.0 || (f64)((WaterTargetUpdateView *)node->target)->unk28 != 0.0) {
                        effectWaterSetMeshPositionsUV(node->dl[D_807444FC], node);
                    }
                    if ((f64)((WaterTargetUpdateView *)node->target)->unkC != 0.0 || (f64)((WaterTargetUpdateView *)node->target)->unk10 != 0.0) {
                        effectWaterSetMeshHeightsAlpha(node->dl[D_807444FC], node);
                    }
                    effectWaterSetMeshColors((Vtx *)node->dl[D_807444FC], node);
                    node->unk4C |= 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

void mapRectIntersect(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
void mapScreenRectBuildFrustum(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);
void effectNodeComputeBounds(EffectNode *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, void *arg5, void *arg6) {
    s32 s2 = 0;
    s32 s3 = 0;
    s32 s4 = 0;
    s32 s5 = 0;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    s32 i;
    s32 idx;
    u8 sp70[0x30];
    EffectSubNode *target = arg0->target;

    for (i = 0; i < target->unk67; i++) {
        idx = target->unk50[i];
        if (((u8 *)D_807F6C18 + idx * 0x1C8)[0] == 1) {
            mapRectIntersect(s2, s3, s4, s5, *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x68), *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x6C), *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x70), *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x74), &spB4, &spB0, &spAC, &spA8);
            s2 = spB4;
            s3 = spB0;
            s4 = spAC;
            s5 = spA8;
        }
    }
    mapScreenRectBuildFrustum(s2, s3, s4, s5, arg1, arg2, arg3, arg4, arg5, arg6, sp70);
    arg0->unk40 = s2;
    arg0->unk42 = s3;
    arg0->unk44 = s4;
    arg0->unk46 = s5;
}

s32 effectCheckTargetActive(EffectSubNode *arg0) {
    s32 i;

    for (i = 0; i < arg0->unk67; i++) {
        if (D_807F6C18[arg0->unk50[i]].unk0 == 1) {
            return 1;
        }
    }
    return 0;
}

typedef struct WaterTargetRenderView {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x32];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
} WaterTargetRenderView;

typedef struct WaterNodeRenderView {
    WaterTargetRenderView *target;
    f32 unk4;
    u8 pad8[8];
    f32 x;
    f32 y;
    f32 z;
    s32 unk1C[4];
    u8 pad2C[0x14];
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
    u8 pad4D[3];
    struct WaterNodeRenderView *next;
} WaterNodeRenderView;

typedef struct EffectBufferEntryView {
    u8 unk0;
    u8 pad1[2];
    u8 unk3;
    u8 pad4[0x1C4];
} EffectBufferEntryView;

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern u8 D_807F78C0[];
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;

s32 lightCollectVolumesInBounds(f32, f32, f32, s16, s32, s32, s32, s32, s32, s32, u8 *);
void func_8065C990(s32, s32, s32, void *, s32, s32);

void func_8065FB64(f32 arg0, f32 arg1, f32 arg2) {
    WaterNodeRenderView *node;
    WaterTargetRenderView *target;
    u8 sp8F;
    s16 s1;
    s32 v0;
    s32 temp_a0;
    u8 flags;

    node = (WaterNodeRenderView *)D_807F93C0;
    if (node != NULL) {
        do {
            flags = node->unk4C;
            if ((flags & 1) && !(flags & 2)) {
                target = node->target;
                s1 = target->unk50[0];
                if (target->unk68 != 0) {
                    v0 = lightCollectVolumesInBounds(arg0, arg1, arg2, target->unk46,
                                           (s32)(((f32)target->unk4E + node->unk4) - (target->unk10 + target->unkC)), target->unk48, target->unk4A,
                                           (s32)(((f32)target->unk4E + node->unk4) + (target->unk10 + target->unkC)), target->unk4C, s1, &sp8F);
                    D_807F7EEC = D_8076A0B4[s1];
                    D_807F7EF0 = D_8076A0B8[s1];
                    D_807F7EF4 = D_8076A0BC[s1];
                    if (D_807FBB60 & 0x10) {
                        temp_a0 = node->unk1C[D_807444FC];
                        func_8065C990(temp_a0, temp_a0 + node->unk48 * 16, 1, &D_807F78C0, v0, ((EffectBufferEntryView *)D_807F6C18)[s1].unk3 == 1);
                    }
                    node->unk4C |= 2;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

Gfx *effectWaterRenderSurfaces(Gfx *gdl, u8 arg1, u8 arg2) {
    EffectNode *water;

    water = D_807F93C0;
    while (water != NULL) {
        if ((water->unk4C & 1) && (arg2 == D_80748A90[water->unk0->unk66].unk16)) {
            gdl = effectWaterSetScissor(gdl, water);
            gSPDisplayList(gdl++, osVirtualToPhysical(water->vtx[D_807444FC]));
            if (!(water->unk4C & 4)) {
                effectWaterBuildMeshGdl(water->vtx[D_807444FC], water->dl[D_807444FC], water);
                water->unk4C |= 4;
            }
        }
        water = water->next;
    }
    return gdl;
}

typedef struct EffectBufferEntryRect {
    u8 pad[0x68];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
} EffectBufferEntryRect;

#define EFFECT_BUFFER_RECT(off) ((EffectBufferEntryRect *)((u32)D_807F6C18 + (off)))

Gfx *effectWaterSetScissor(Gfx *gdl, EffectNode *water) {
    s32 index;
    s32 offset;

    gDPPipeSync(gdl++);
    if (water->sub->unk67 == 1) {
        index = water->sub->unk50[0];
        offset = index * 0x1C8;
        {
            Gfx *_g = (Gfx *)gdl++;

            _g->words.w0 = ((s32)(EFFECT_BUFFER_RECT(offset)->unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)(EFFECT_BUFFER_RECT(offset)->unk68 * 4.0f) & 0xFFF) << 12);
            _g->words.w1 = ((s32)(EFFECT_BUFFER_RECT(offset)->unk74 * 4.0f) & 0xFFF) | (((s32)(EFFECT_BUFFER_RECT(offset)->unk70 * 4.0f) & 0xFFF) << 12);
        }
    } else {
        gDPSetScissor(gdl++, G_SC_NON_INTERLACE, water->unk40, water->unk42, water->unk44, water->unk46);
    }
    return gdl;
}
#undef EFFECT_BUFFER_RECT

typedef struct Eff63MeshBuilder {
    Gfx *(*fn)(void *, EffectNode *, u8);
    u8 pad4[0x14];
} Eff63MeshBuilder;

typedef struct Eff63MeshSub {
    u8 pad0[0x46];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    u8 pad4E[0x66 - 0x4E];
    u8 unk66;
} Eff63MeshSub;

extern Eff63MeshBuilder D_80748A94[];
extern s32 D_807F93EC;

void effectWaterBuildMeshGdl(void *arg0, void *arg1, EffectNode *water) {
    s32 vtxStart;
    s32 vtxNext;
    s32 countX;
    Gfx *gdl;
    s32 x;
    s32 countZ;
    s32 segLen;
    s32 i;
    s32 k;
    u8 done;
    s32 total;

    D_807F93EC = 0;
    gdl = D_80748A94[((Eff63MeshSub *)water->unk0)->unk66].fn(arg0, water, ((Eff63MeshSub *)water->unk0)->unk66);
    countX = ((((Eff63MeshSub *)water->unk0)->unk4A - ((Eff63MeshSub *)water->unk0)->unk46) / water->unk2C) + 1;
    countZ = ((((Eff63MeshSub *)water->unk0)->unk4C - ((Eff63MeshSub *)water->unk0)->unk48) / water->unk2C) + 1;
    total = (countX + 1) * (countZ + 1);
    vtxNext = countX + 1;
    vtxStart = 0;
    x = 0;
    done = 0;
    do {
        segLen = (countX - x + 1) >= 17 ? 16 : (countX - x + 1);
        gSPVertex(gdl++, osVirtualToPhysical(vtxStart * 16 + (u8 *)arg1), segLen, 0);
        gSPVertex(gdl++, osVirtualToPhysical(vtxNext * 16 + (u8 *)arg1), segLen, 16);
        k = 0;
        for (i = 0; i < segLen - 1; i++) {
            gSP2Triangles(gdl++, k + 1, k, k + 16, 0, k + 16, k + 17, k + 1, 0);
            D_807F93EC += 2;
            k++;
        }
        x += segLen - 1;
        vtxStart += segLen - 1; vtxNext += segLen - 1; // LAYOUT: same source line steers as1 scheduling of the two addu
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

typedef struct WaterHeightView {
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
} WaterHeightView;

f32 func_806608FC(EffectNode *, s32, s32, u8);

#define WATER_HEIGHT ((WaterHeightView *)water->unk0)
void effectWaterSetMeshHeightsAlpha(Vtx *vtx, EffectNode *water) {
    s32 countX;
    s32 countZ;
    s16 maxX;
    s16 maxZ;
    s16 step;
    s16 minX;
    s16 minZ;
    s16 x;
    s16 z;
    s32 j;
    s32 i;
    f32 baseHeight;
    f32 heightScale;
    f32 h;
    u8 alphaMax;
    u8 alphaBase;
    u8 flag;

    step = water->unk2C;
    minX = WATER_HEIGHT->unk46;
    maxX = WATER_HEIGHT->unk4A;
    minZ = WATER_HEIGHT->unk48;
    maxZ = WATER_HEIGHT->unk4C;
    baseHeight = (f32)WATER_HEIGHT->unk4E + water->unk4;
    heightScale = WATER_HEIGHT->unk10 + WATER_HEIGHT->unkC;
    alphaMax = WATER_HEIGHT->unk65;
    alphaBase = WATER_HEIGHT->unk64;
    flag = D_80748AA5[WATER_HEIGHT->unk66].unk0;
    countX = ((maxX - minX) / step) + 1;
    countZ = ((maxZ - minZ) / step) + 1;
    z = minZ;
    for (j = 0; j <= countZ; j++) {
        x = minX;
        for (i = 0; i <= countX; i++) {
            if (maxX < x) {
                x = maxX;
            }
            if (maxZ < z) {
                z = maxZ;
            }
            h = func_806608FC(water, x, z, flag);
            vtx->v.ob[1] = h * 3.0f;
            vtx->v.cn[3] = (u32)(((h - baseHeight) / heightScale) * (f32)alphaMax + (f32)alphaBase);
            vtx++;
            x += step;
        }
        z += step;
    }
}
#undef WATER_HEIGHT

typedef struct WaterEffectSubNode {
    u8 pad[0x46];
    s16 minX;
    s16 minZ;
    s16 maxX;
    s16 maxZ;
    u8 pad2[0x61 - 0x4E];
    u8 r;
    u8 g;
    u8 b;
} WaterEffectSubNode;

void effectWaterSetMeshColors(Vtx *vtx, EffectNode *water) {
    u8 r;
    WaterEffectSubNode *sub;
    u8 g;
    u8 b;
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    s32 step;
    u32 total;
    s32 count;

    r = ((WaterEffectSubNode *)water->sub)->r;
    sub = (WaterEffectSubNode *)water->sub;
    g = sub->g;
    b = sub->b;
    minX = sub->minX;
    minZ = sub->minZ;
    maxX = sub->maxX;
    maxZ = sub->maxZ;
    step = water->unk2C;
    total = (((maxX - minX) / step) + 2) * (((maxZ - minZ) / step) + 2);
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

f32 func_80612794(s16);

typedef struct WaterHeightView2 {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x46 - 0x14];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
} WaterHeightView2;

#define WATER_SUB ((WaterHeightView2 *)water->unk0)
#define WATER_ABS(x) ((x) > 0 ? (x) : -(x))

f32 sqrtf(f32);

f32 func_806608FC(EffectNode *water, s32 arg1, s32 arg2, u8 type) {
    s32 temp1;
    s32 temp;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 diff;
    f32 h;
    f32 r;
    f32 baseH;
    f32 edgeDist;

    switch (type) {
    case 0:
        temp1 = (s32)(WATER_SUB->unk4 * (f32)arg1);
        temp = (s32)(WATER_SUB->unk8 * (f32)arg2);
        return ((f32)WATER_SUB->unk4E + water->unk4 + (WATER_SUB->unkC * func_80612794((s16)((water->unk30 + temp1) % 4095)))) + (func_80612794((s16)((water->unk34 + temp) % 4095)) * WATER_SUB->unk10);

    case 1:
    case 2:
        if (D_807F93C4 != 0) {
            dz = (f32)arg2 - D_807F93C8[1];
            dx = (f32)arg1 - D_807F93C8[0];
            dist = sqrtf((dz * dz) + (dx * dx));
            if (dist < D_807F93DC) {
                diff = D_807F93DC - dist;
            } else {
                diff = -(D_807F93DC - dist);
            }
            if (D_807F93DC < D_807F93E8) {
                h = D_807F93D4;
            } else if (D_807F93E4 < D_807F93DC) {
                h = 0.0f;
            } else {
                h = (f32)((f64)D_807F93D4 + ((0.0 - (f64)D_807F93D4) * (f64)((D_807F93DC - D_807F93E8) / (D_807F93E4 - D_807F93E8))));
            }
            if ((f64)diff < 50.0) {
                baseH = (f32)WATER_SUB->unk4E + water->unk4;
                r = baseH + h;
            } else if ((f64)diff > 150.0) {
                baseH = (f32)WATER_SUB->unk4E + water->unk4;
                r = baseH;
            } else {
                baseH = (f32)WATER_SUB->unk4E + water->unk4;
                r = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / (100.0 * 1.0)))));  // FAKE: folds to 100.0 but keeps the constant out of the sibling-branch CSE (steers f-reg pick)
            }
        } else {
            baseH = (f32)WATER_SUB->unk4E + water->unk4;
            r = baseH;
        }

        if (type == 2) {
            edgeDist = (f32)WATER_ABS(arg1 - WATER_SUB->unk46);

            dz = (f32)WATER_ABS(arg1 - WATER_SUB->unk4A);
            if (dz < edgeDist) edgeDist = dz;

            dz = (f32)WATER_ABS(arg2 - WATER_SUB->unk4C);
            if (dz < edgeDist) edgeDist = dz;

            dz = (f32)WATER_ABS(arg2 - WATER_SUB->unk48);
            if (dz < edgeDist) edgeDist = dz;

            if ((f64)edgeDist < 100.0) {
                r = (f32)((f64)baseH + ((f64)(r - baseH) * ((f64)edgeDist / 100.0)));
            }
        }
        return r;

    default:
        return 0.0f;
    }
}
#undef WATER_SUB
#undef WATER_ABS

typedef struct WaterWaveView {
    f32 unk0;
    u8 pad4[0x18];
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x46 - 0x2C];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
} WaterWaveView;

#define WATER_WAVE ((WaterWaveView *)water->unk0)
void effectWaterSetMeshPositionsUV(Vtx *vtx, EffectNode *water) {
    s32 countX;
    s32 countZ;
    s16 maxX;
    s16 maxZ;
    s16 step;
    s16 minX;
    s16 minZ;
    s16 x;
    s16 z;
    s32 j;
    s32 i;
    s16 posX;
    s16 posZ;
    s32 offX;
    s32 offZ;
    s32 tcX;
    s32 tcZ;

    step = water->unk2C;
    minX = WATER_WAVE->unk46;
    maxX = WATER_WAVE->unk4A;
    minZ = WATER_WAVE->unk48;
    maxZ = WATER_WAVE->unk4C;
    countX = ((maxX - minX) / step) + 1;
    countZ = ((maxZ - minZ) / step) + 1;
    z = minZ;
    for (j = 0; j <= countZ; j++) {
        x = minX;
        for (i = 0; i <= countX; i++) {
            if (maxX < x) {
                x = maxX;
            }
            if (maxZ < z) {
                z = maxZ;
            }
            offX = (s32)(WATER_WAVE->unk1C * (f32)x);
            offZ = (s32)(WATER_WAVE->unk20 * (f32)z);
            posX = (func_80612794((water->unk38 + offX) & 0xFFF) * WATER_WAVE->unk24) + (f32)x;
            posZ = (func_80612794((water->unk3C + offZ) & 0xFFF) * WATER_WAVE->unk28) + (f32)z;
            vtx->v.ob[0] = posX * 3;
            vtx->v.ob[2] = posZ * 3;
            tcX = (s32)((f32)x * WATER_WAVE->unk0);
            tcZ = (s32)((f32)z * WATER_WAVE->unk0);
            vtx->v.tc[0] = tcX % 0x7FFF;
            vtx->v.tc[1] = tcZ % 0x7FFF;
            vtx++;
            x += step;
        }
        z += step;
    }
}
#undef WATER_WAVE

s32 mathBitwiseNot(s32 arg0) {
    return ~arg0;
}

s32 randomLcgNext(void);
extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;

void effectUpdateAndDispatch(void) {
    u32 sp60[6];
    u32 pad[4];
    u32 *s1;
    EffectNode *s0;
    u32 s2;

    s1 = sp60;
    s0 = D_807F93C0;
    if ((u32)s1 & 7) {
        s1++;
    }
    s2 = mathBitwiseNot(-0xF81);
    osWritebackDCache(s1, 0x10);
    osPiStartDma(&D_807ECE00, 0, 0, s2, s1, 0x10, &D_807655F0);
    D_80746834 = 6;
    osRecvMesg(&D_807655F0, NULL, 1);
    D_80746834 = 0;
    osInvalDCache(s1, 0x10);
    s1[0] -= 0x3E0EF0F0;
    s1[1] -= 0x3E0EF0F0;
    if (s1[0] != 0x3050A14A || s1[1] != 0xBCFCF506) {
        s1 = (u32 *)randomLcgNext();
        s2 = randomLcgNext();
        osPiStartDma(&D_807ECE00, 0, 0, (u32)s1 & 0xFFFF, (void *)((s2 & 0xFFFFE) + 0x80500000), (randomLcgNext() & 0xFF) + 0x100, &D_807655F0);
    }
    if (s0 != NULL) {
        do {
            f32 target = s0->unk8;
            if (target != s0->unk4) {
                if (s0->unk4 < target) {
                    s0->unk4 += s0->unkC;
                    if (target < s0->unk4) {
                        s0->unk4 = target;
                    }
                } else {
                    s0->unk4 -= s0->unkC;
                    if (s0->unk4 < target) {
                        s0->unk4 = target;
                    }
                }
            }
            D_80748A90[s0->sub->unk66].fn2(s0);
            s0 = s0->next;
        } while (s0 != NULL);
    }
}

void effectNodeSetSubVal(s32 arg0, u8 arg1) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->sub->val = arg1;
    }
}

void effectNodeSetUnk4A(s32 arg0, u8 arg1) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk4A = arg1;
    }
}

u8 effectNodeGetUnk4B(s32 arg0) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        return node->unk4B;
    }
    return 0;
}

void effectNodeSetUnk4B(s32 arg0, u8 arg1) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk4B = arg1;
    }
}

void effectNodeSetTargetAndStep(s32 arg0, f32 arg1, f32 arg2) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk8 = arg1;
        node->unkC = arg2;
    }
}

void effectNodeAddTargetAndStep(s32 arg0, f32 arg1, f32 arg2) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        node->unk8 += arg1;
        node->unkC = arg2;
    }
}

void effectNodeCopyValues(f32 *arg0) {
    EffectNode *node = D_807F93C0;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        arg0[i] = node->unk8;
        node = node->next;
    }
}

void effectNodeSetValues(f32 *arg0) {
    EffectNode *node = D_807F93C0;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        node->unk8 = arg0[i];
        node->unk4 = node->unk8;
        node = node->next;
    }
}

f32 effectNodeGetValue(s32 arg0) {
    EffectNode *node = D_807F93C0;
    while (node != NULL && arg0 != 0) {
        node = node->next;
        arg0--;
    }
    if (node != NULL) {
        return node->unk4;
    }
    return 0.0f;
}

void screenShakeStart(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    if (D_807F93C4 == 0) {
        D_807F93C8[0] = arg0;
        D_807F93C8[1] = arg1;
        D_807F93D4 = 0.0f;
        D_807F93D0 = arg2;
        D_807F93D8 = arg3;
        D_807F93DC = 0.0f;
        D_807F93E0 = arg4;
        D_807F93E4 = arg5;
        D_807F93E8 = (arg5 * 2) / 3.0f;
        D_807F93C4 = 1;
    }
}

void screenShakeStep(void) {
    if (D_807F93C4 != 0) {
        D_807F93D4 += D_807F93D8;
        if (D_807F93D0 < D_807F93D4) {
            D_807F93D4 = D_807F93D0;
        }
        D_807F93DC += D_807F93E0;
        if (D_807F93E4 < D_807F93DC) {
            D_807F93C4 = 0;
        }
    }
}

void screenShakeStop(void) {
    D_807F93C4 = 0;
}

void effectInitTextureTableRGBA32(u8 arg0) {
    D_80748A9C[arg0].unk0 = assetLoad(7, 0x3C5, 1, 0);
}

Gfx *effectBuildGdlTexture32x32RGBA(Gfx *dlist, EffectNode *arg1, u8 arg2) {
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock(dlist++, D_80748A9C[arg2].unk0, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    WRITE_GFX(dlist++, 0xFC20FE04, 0xFF13F3FF);
    WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(dlist++, 0xE3000F00, 0);
    WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0x0C184A50);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)arg1->sub->unk3C & 0xFFF), 0x0107C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    WRITE_GFX(dlist++, (((s32)arg1->sub->unk40 & 0xFFF) | 0xF2000000) | (((s32)arg1->sub->unk40 & 0xFFF) << 12), 0x0207C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}

Gfx *effectBuildGdlTexture32x32RGBAWithPrim(Gfx *dlist, EffectNode *arg1, u8 arg2) {
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock(dlist++, D_80748A9C[arg2].unk0, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    WRITE_GFX(dlist++, 0xFC20FE04, 0xFF0FF3FF);
    gDPSetPrimColor(dlist++, 0, 0, 0, 0, 0, arg1->sub->val);
    WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00210005);
    WRITE_GFX(dlist++, 0xE3000F00, 0);
    WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0xC8104A50);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)arg1->sub->unk3C & 0xFFF), 0x0107C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    WRITE_GFX(dlist++, (((s32)arg1->sub->unk40 & 0xFFF) | 0xF2000000) | (((s32)arg1->sub->unk40 & 0xFFF) << 12), 0x0207C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}

void effectNodeStepUVAndPos(EffectNode *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->sub->unk40 -= arg0->sub->unk38;
    if (arg0->sub->unk40 < 0.0) {
        arg0->sub->unk40 = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}

void effectInitTextureTableCI4(u8 arg0) {
    D_80748A90[arg0].res0 = assetLoad(0x19, 0x2EE, 1, 0);
    D_80748A90[arg0].res1 = assetLoad(0x19, 0x2EF, 1, 0);
}

Gfx *effectBuildGdlTexture64x64CI4(Gfx *dlist, EffectNode *arg1, u8 arg2) {
    EffectTableEntry *entry = &D_80748A90[arg2];
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock_4b(dlist++, entry->res0, G_IM_FMT_CI, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    WRITE_GFX(dlist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(dlist++, 0xE3000A01, 0);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(dlist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(dlist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0x00552230);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)arg1->sub->unk3C & 0xFFF), 0x000FC0FC);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    gDPLoadTLUT_pal16(dlist++, 0, entry->res1);
    gDPSetTextureLUT(dlist++, G_TT_RGBA16);
    return dlist;
}

void effectNodeUpdateAlphaOffset(EffectNode *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}

void effectInitTextureTable0(u8 arg0) {
    D_80748A9C[arg0].unk0 = assetLoad(0x19, 0xF0, 1, 0);
}

Gfx *effectBuildMipmapGdl(Gfx *glist, s32 arg1, u8 arg2) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[arg2].unk0);
    WRITE_GFX(glist++, 0xF5100000, 0x07000000);
    WRITE_GFX(glist++, 0xE6000000, 0);
    WRITE_GFX(glist++, 0xF3000000, 0x0754F000);
    WRITE_GFX(glist++, 0xF5101000, 0x00014050);
    WRITE_GFX(glist++, 0xF2002002, 0x0007E07E);
    WRITE_GFX(glist++, 0xF5100900, 0x01010441);
    WRITE_GFX(glist++, 0xF2002002, 0x0103E03E);
    WRITE_GFX(glist++, 0xF5100540, 0x0200C832);
    WRITE_GFX(glist++, 0xF2002002, 0x0201E01E);
    WRITE_GFX(glist++, 0xF5100350, 0x03008C23);
    WRITE_GFX(glist++, 0xF2002002, 0x0300E00E);
    WRITE_GFX(glist++, 0xFC26A004, 0x1F1093FF);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7001802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C192230);
    return glist;
}

void effectNoopCallback1(s32 arg0) {
}

void effectInitTextureTable1(u8 arg0) {
    D_80748A9C[arg0].unk0 = assetLoad(0x19, 0xAF4, 1, 0);
}

void effectBuildMipmapGdlWrapper(Gfx *arg0, s32 arg1, u8 arg2) {
    effectBuildMipmapGdl(arg0, arg1, arg2);
}

void effectNoopCallback2(s32 arg0) {
}

void effectInitTextureTable2(u8 arg0) {
    D_80748A9C[arg0].unk0 = assetLoad(0x19, 0x75C, 1, 0);
}

Gfx *effectBuildMipmapGdlDup(Gfx *glist, s32 arg1, u8 arg2) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[arg2].unk0);
    WRITE_GFX(glist++, 0xF5100000, 0x07000000);
    WRITE_GFX(glist++, 0xE6000000, 0);
    WRITE_GFX(glist++, 0xF3000000, 0x0754F000);
    WRITE_GFX(glist++, 0xF5101000, 0x00014050);
    WRITE_GFX(glist++, 0xF2002002, 0x0007E07E);
    WRITE_GFX(glist++, 0xF5100900, 0x01010441);
    WRITE_GFX(glist++, 0xF2002002, 0x0103E03E);
    WRITE_GFX(glist++, 0xF5100540, 0x0200C832);
    WRITE_GFX(glist++, 0xF2002002, 0x0201E01E);
    WRITE_GFX(glist++, 0xF5100350, 0x03008C23);
    WRITE_GFX(glist++, 0xF2002002, 0x0300E00E);
    WRITE_GFX(glist++, 0xFC26A004, 0x1F1093FF);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7001802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C192230);
    return glist;
}

void effectNoopCallback3(s32 arg0) {
}

void effectInitTextureTable3(u8 arg0) {
    D_80748A9C[arg0].unk0 = assetLoad(7, 0x3B9, 1, 0);
}

Gfx *effectBuildSingleTextureGdl(Gfx *glist, EffectSubNode **arg1, u8 arg2) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[arg2].unk0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*arg1)->unk3C & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void effectInitTextureTable4(u8 arg0) {
    D_80748A9C[arg0].unk0 = assetLoad(7, 0x3D2, 1, 0);
}

Gfx *effectBuildSingleTextureGdlDup(Gfx *glist, EffectSubNode **arg1, u8 arg2) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[arg2].unk0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*arg1)->unk3C & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void effectInitTextureTableDual(u8 arg0) {
    D_80748A90[arg0].res0 = assetLoad(7, 0x3BA, 1, 0);
    D_80748A90[arg0].res1 = assetLoad(7, 0x3DB, 1, 0);
}

extern s32 D_80748B68;

Gfx *effectBuildMultiBlockTextureGdl(Gfx *glist, EffectNode *arg1, u8 arg2) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A90[arg2].res0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    gDPLoadMultiBlock(glist++, D_80748A90[arg2].res1, 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, D_80748B68, D_80748B68);

    gDPSetPrimColor(glist++, 0, arg1->unk4B, 255, 255, 255, 100);
    WRITE_GFX(glist++, 0xFC272C03, 0x1FFC93FB);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0);
    WRITE_GFX(glist++, 0xD7000802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C184A50);

    return glist;
}

void effectNodeUpdateDualAlphaOffset(EffectNode *arg0) {
    arg0->sub->unk3C -= arg0->sub->unk34;
    if (arg0->sub->unk3C < 0.0) {
        arg0->sub->unk3C = 255.0f;
    }
    arg0->sub->unk40 -= arg0->sub->unk38;
    if (arg0->sub->unk40 < 0.0) {
        arg0->sub->unk40 = 255.0f;
    }
    arg0->unk30 += arg0->sub->unk14;
    arg0->unk34 += arg0->sub->unk18;
    arg0->unk38 += arg0->sub->unk2C;
    arg0->unk3C += arg0->sub->unk30;
}
