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
Gfx *func_8065FEB8(Gfx *, EffectNode *);
void func_80660070(void *, void *, EffectNode *);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F1C0.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F678.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_8065F964.s")

s32 effectCheckTargetActive(EffectSubNode *arg0) {
    s32 i;

    for (i = 0; i < arg0->unk67; i++) {
        if (D_807F6C18[arg0->unk50[i]].unk0 == 1) {
            return 1;
        }
    }
    return 0;
}

typedef struct EffATargetFB64 {
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
} EffATargetFB64;

typedef struct EffANodeFB64 {
    EffATargetFB64 *target;
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
    struct EffANodeFB64 *next;
} EffANodeFB64;

typedef struct EffAEntryFB64 {
    u8 unk0;
    u8 pad1[2];
    u8 unk3;
    u8 pad4[0x1C4];
} EffAEntryFB64;

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern u8 D_807F78C0[];
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;

s32 func_8065BAA0(f32, f32, f32, s16, s32, s32, s32, s32, s32, s32, u8 *);
void func_8065C990(s32, s32, s32, void *, s32, s32);

void func_8065FB64(f32 arg0, f32 arg1, f32 arg2) {
    EffANodeFB64 *node;
    EffATargetFB64 *target;
    u8 sp8F;
    s16 s1;
    s32 v0;
    s32 temp_a0;
    u8 flags;

    node = (EffANodeFB64 *)D_807F93C0;
    if (node != NULL) {
        do {
            flags = node->unk4C;
            if ((flags & 1) && !(flags & 2)) {
                target = node->target;
                s1 = target->unk50[0];
                if (target->unk68 != 0) {
                    v0 = func_8065BAA0(arg0, arg1, arg2, target->unk46,
                                           (s32)(((f32)target->unk4E + node->unk4) - (target->unk10 + target->unkC)), target->unk48, target->unk4A,
                                           (s32)(((f32)target->unk4E + node->unk4) + (target->unk10 + target->unkC)), target->unk4C, s1, &sp8F);
                    D_807F7EEC = D_8076A0B4[s1];
                    D_807F7EF0 = D_8076A0B8[s1];
                    D_807F7EF4 = D_8076A0BC[s1];
                    if (D_807FBB60 & 0x10) {
                        temp_a0 = node->unk1C[D_807444FC];
                        func_8065C990(temp_a0, temp_a0 + node->unk48 * 16, 1, &D_807F78C0, v0, ((EffAEntryFB64 *)D_807F6C18)[s1].unk3 == 1);
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
            gdl = func_8065FEB8(gdl, water);
            gSPDisplayList(gdl++, osVirtualToPhysical(water->vtx[D_807444FC]));
            if (!(water->unk4C & 4)) {
                func_80660070(water->vtx[D_807444FC], water->dl[D_807444FC], water);
                water->unk4C |= 4;
            }
        }
        water = water->next;
    }
    return gdl;
}

typedef struct EffAStruct1C8FEB8 {
    u8 pad[0x68];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
} EffAStruct1C8FEB8;

#define EFFA_ENTRY(off) ((EffAStruct1C8FEB8 *)((u32)D_807F6C18 + (off)))

Gfx *func_8065FEB8(Gfx *gdl, EffectNode *water) {
    s32 index;
    s32 offset;

    gDPPipeSync(gdl++);
    if (water->sub->unk67 == 1) {
        index = water->sub->unk50[0];
        offset = index * 0x1C8;
        {
            Gfx *_g = (Gfx *)gdl++;

            _g->words.w0 = ((s32)(EFFA_ENTRY(offset)->unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)(EFFA_ENTRY(offset)->unk68 * 4.0f) & 0xFFF) << 12);
            _g->words.w1 = ((s32)(EFFA_ENTRY(offset)->unk74 * 4.0f) & 0xFFF) | (((s32)(EFFA_ENTRY(offset)->unk70 * 4.0f) & 0xFFF) << 12);
        }
    } else {
        gDPSetScissor(gdl++, G_SC_NON_INTERLACE, water->unk40, water->unk42, water->unk44, water->unk46);
    }
    return gdl;
}
#undef EFFA_ENTRY

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_80660070.s")

typedef struct EffBHeightSub {
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
} EffBHeightSub;

f32 func_806608FC(EffectNode *, s32, s32, u8);

#define EFFB_HSUB ((EffBHeightSub *)water->unk0)
void func_80660520(Vtx *vtx, EffectNode *water) {
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
    minX = EFFB_HSUB->unk46;
    maxX = EFFB_HSUB->unk4A;
    minZ = EFFB_HSUB->unk48;
    maxZ = EFFB_HSUB->unk4C;
    baseHeight = (f32)EFFB_HSUB->unk4E + water->unk4;
    heightScale = EFFB_HSUB->unk10 + EFFB_HSUB->unkC;
    alphaMax = EFFB_HSUB->unk65;
    alphaBase = EFFB_HSUB->unk64;
    flag = D_80748AA5[EFFB_HSUB->unk66].unk0;
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
#undef EFFB_HSUB

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

#ifdef NON_MATCHING
typedef struct EffBHeightSub2 {
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
} EffBHeightSub2;

f32 sqrtf(f32);

f32 func_806608FC(EffectNode *water, s32 arg1, s32 arg2, u8 type) {
    s32 temp1;
    s32 temp;
    EffBHeightSub2 * sub;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 diff;
    f32 h;
    f32 baseH;
    f32 edgeDist;
    s32 d;
    f32 sin1;

    switch (type) {
    case 0:
        {
            temp1 = (s32)(((EffBHeightSub2 *)water->unk0)->unk4 * (f32)arg1);
            temp = (s32)(((EffBHeightSub2 *)water->unk0)->unk8 * (f32)arg2);
            sin1 = func_80612794((s16)((water->unk30 + temp1) % 4095));
        }
        return (func_80612794((s16)((water->unk34 + temp) % 4095)) * ((EffBHeightSub2 *)water->unk0)->unk10) + ((f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4 + (((EffBHeightSub2 *)water->unk0)->unkC * sin1));

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
                baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
                h += baseH;
            } else if ((f64)diff > 150.0) {
                baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
                h = baseH;
            } else {
                baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
                h = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / 100.0))));
            }
        } else {
            baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
            h = baseH;
        }

        if (type == 2) {
            sub = (EffBHeightSub2 *)water->unk0;
            d = arg1 - sub->unk46;
            edgeDist = (f32)(d > 0 ? d : -d);

            d = arg1 - sub->unk4A;
            dx = (f32)(d > 0 ? d : -d);
            if (dx < edgeDist) edgeDist = dx;

            d = arg2 - sub->unk4C;
            dx = (f32)(d > 0 ? d : -d);
            if (dx < edgeDist) edgeDist = dx;
            if (D_807F93E4 && D_807F93E4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)

            d = arg2 - sub->unk48;
            dx = (f32)(d > 0 ? d : -d);
            if (dx < edgeDist) edgeDist = dx;

            if ((f64)edgeDist < 100.0) {
                h = (f32)((f64)baseH + ((f64)(h - baseH) * ((f64)edgeDist / 100.0)));
            }
        }
        return h;

    default:
        return 0.0f;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/63EC0/func_806608FC.s")
#endif

typedef struct EffBWaterSub {
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
} EffBWaterSub;

#define EFFB_SUB ((EffBWaterSub *)water->unk0)
void func_80660D38(Vtx *vtx, EffectNode *water) {
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
    minX = EFFB_SUB->unk46;
    maxX = EFFB_SUB->unk4A;
    minZ = EFFB_SUB->unk48;
    maxZ = EFFB_SUB->unk4C;
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
            offX = (s32)(EFFB_SUB->unk1C * (f32)x);
            offZ = (s32)(EFFB_SUB->unk20 * (f32)z);
            posX = (func_80612794((water->unk38 + offX) & 0xFFF) * EFFB_SUB->unk24) + (f32)x;
            posZ = (func_80612794((water->unk3C + offZ) & 0xFFF) * EFFB_SUB->unk28) + (f32)z;
            vtx->v.ob[0] = posX * 3;
            vtx->v.ob[2] = posZ * 3;
            tcX = (s32)((f32)x * EFFB_SUB->unk0);
            tcZ = (s32)((f32)z * EFFB_SUB->unk0);
            vtx->v.tc[0] = tcX % 0x7FFF;
            vtx->v.tc[1] = tcZ % 0x7FFF;
            vtx++;
            x += step;
        }
        z += step;
    }
}
#undef EFFB_SUB

s32 mathBitwiseNot(s32 arg0) {
    return ~arg0;
}

s32 func_806119A0(void);
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
        s1 = (u32 *)func_806119A0();
        s2 = func_806119A0();
        osPiStartDma(&D_807ECE00, 0, 0, (u32)s1 & 0xFFFF, (void *)((s2 & 0xFFFFE) + 0x80500000), (func_806119A0() & 0xFF) + 0x100, &D_807655F0);
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
