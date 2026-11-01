#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern u8 D_80750AB4;
extern s16 D_807FDB34;

void *heapAlloc(s32);
u32 randomLcgNext(void);


typedef struct EffectGridNode {
    void *unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s32 unk18;
    void *unk1C;
    void *unk20;
    struct EffectGridNode *unk24;
} EffectGridNode;

typedef struct EffectNode {
    u8 pad0[0x20];
    u8 itemCount;
    u8 pad21[0x317];
    s32 resource;
    u8 pad33C[0x33];
    u8 mode;
    u8 pad370[0x14];
    void *allocation;
    u8 pad388[4];
    u16 flags;
    u8 pad38E[0xA];
    struct EffectNode *previous;
    struct EffectNode *next;
} EffectNode;


extern EffectGridNode *D_807FDB00;
extern EffectNode *D_807FDB04;
extern EffectNode *D_807FDB08;
extern s8 D_807FDB0C;
extern s8 D_807FDB0D;
extern s8 D_807FDB0E;
extern s8 D_807FDB0F;
extern s32 D_807FDB10;
extern s32 D_807FDB14;
extern s8 D_807FDB18;
extern s16 D_807FDB1A;
extern u8 D_807FDB1C;
extern s8 D_807FDB1D;
extern f32 D_807FDB20;
extern f32 D_807FDB24;
extern s8 D_807FDB28;
extern s32 D_807FDB2C;
extern s32 D_807FDB30;
extern u16 D_807FDB36;
extern s16 D_807FDB38;
extern s16 D_807FDB3A;
extern s16 D_807FDB3C;
extern s16 D_807FDB3E;
extern s16 D_807FDB40;
extern s16 D_807FDB42;

void effectResetState(void);

void effectResetLists(void) {
    D_807FDB00 = NULL;
    D_807FDB04 = NULL;
    D_807FDB08 = NULL;
    effectResetState();
}

s32 func_807146A4(s32 arg0) {
    EffectGridNode *node = D_807FDB00;

    if (node != NULL) {
        do {
            if (arg0 == node->unk4) {
                return (s32) node->unk0;
            }
            node = node->unk24;
        } while (node != NULL);
    }
    return (s32) D_807FDB00->unk0;
}

void effectGridGetByteDimensions(EffectGridNode *arg0, u8 *arg1, u8 *arg2) {
    *arg1 = ((u8 *) arg0)[4];
    *arg2 = ((u8 *) arg0)[5];
}

void effectGridGetCellDimensions(EffectGridNode *arg0, s16 *arg1, s16 *arg2) {
    *arg1 = arg0->unkE;
    *arg2 = arg0->unk10;
}

void effectGridGetScaledDimensions(EffectGridNode *arg0, s16 *arg1, s16 *arg2) {
    s16 pad0;
    s16 pad1;
    u8 sp1B;
    u8 sp1A;
    effectGridGetByteDimensions(arg0, &sp1B, &sp1A);
    effectGridGetCellDimensions(arg0, arg1, arg2);
    *arg1 *= sp1B;
    *arg2 *= sp1A;
}

void effectGridRegister(EffectGridNode *arg0) {
    EffectGridNode *last;
    EffectGridNode *newNode;
    s32 byteOffset;
    s32 count;
    s32 i;

    newNode = D_807FDB00;
    byteOffset = 0xB;
    last = NULL;
    while (newNode != NULL) {
        last = newNode;
        if (arg0 == newNode->unk0) {
            return;
        }
        newNode = newNode->unk24;
    }

    newNode = heapAlloc(0x28);
    newNode->unk24 = NULL;
    newNode->unk0 = arg0;
    newNode->unk4 = (s32) arg0->unk0;
    effectGridGetByteDimensions(arg0, &newNode->unk8, &newNode->unk9);
    ((u8 *) newNode)[0xA] = ((u8 *) arg0)[0x6];
    ((u8 *) newNode)[byteOffset] = ((u8 *) arg0)[0x7];
    ((u8 *) newNode)[0x10] = ((u8 *) arg0)[0x8];
    ((u8 *) newNode)[0x11] = ((u8 *) arg0)[0x9];
    ((u8 *) newNode)[0x12] = ((u8 *) arg0)[0xA];
    ((u8 *) newNode)[0x13] = ((u8 *) arg0)[0xB];
    ((u8 *) newNode)[0x14] = ((u8 *) arg0)[0xC];
    ((u8 *) newNode)[0x15] = ((u8 *) arg0)[0xD];
    effectGridGetCellDimensions(arg0, &newNode->unkC, &newNode->unkE);
    newNode->unk16 = arg0->unk12;
    newNode->unk18 = -1;

    if (D_807FDB00 != NULL) {
        last->unk24 = newNode;
    } else {
        D_807FDB00 = newNode;
    }

    count = newNode->unk8 * newNode->unk9 * newNode->unk16;
    newNode->unk1C = heapAlloc(count * 8);
    for (i = 0; i < count; i++) {
        ((s32 *) ((u8 *) newNode->unk1C + (i * 8)))[1] = -1;
    }
    newNode->unk20 = (u8 *) arg0 + 0x14;
}

void func_80714944(s32 arg0) {
    D_807FDB30 = arg0;
}

void func_80714950(s32 arg0) {
    D_807FDB2C = arg0;
}

void func_8071495C(void) {
    D_807FDB1D = 1;
}

void func_8071496C(s16 arg0) {
    D_807FDB1A = arg0;
}

void func_8071497C(s16 arg0) {
    D_807FDB34 = arg0;
}

void func_8071498C(s32 arg0) {
    D_807FDB14 = arg0;
}

void func_80714998(s8 arg0) {
    D_807FDB1C = arg0;
}

void func_807149A8(s16 arg0) {
    D_807FDB3A = arg0;
}

void func_807149B8(s8 arg0) {
    D_807FDB18 = arg0;
}

void func_807149C8(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_807FDB0C = arg0;
    D_807FDB0D = arg1;
    D_807FDB0E = arg2;
    D_807FDB0F = arg3;
}

void func_807149FC(s32 arg0) {
    D_807FDB10 = arg0;
}

void func_80714A08(f32 arg0, f32 arg1) {
    D_807FDB20 = arg0;
    D_807FDB24 = arg1;
    D_807FDB28 = 1;
}

void func_80714A28(s16 arg0) {
    D_807FDB36 = arg0;
}

void effectFlagsOr(u8 arg0) {
    u16 *temp = &D_807FDB36;

    *temp = *temp | arg0;
}

void func_80714A58(s16 arg0) {
    D_807FDB38 = arg0;
}

void func_80714A68(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_807FDB3C = arg0;
    D_807FDB3E = arg1;
    D_807FDB40 = arg2;
    D_807FDB42 = arg3;
}

extern u8 D_8074450C;

void effectResetState(void) {
    s32 temp;
    u16 new_var;

    D_807FDB0F = 0;
    D_807FDB10 = 1;
    D_807FDB14 = 0;
    D_807FDB18 = 0;
    D_807FDB1C = 1;
    D_807FDB1A = 0;
    D_807FDB1D = 0;
    D_807FDB28 = 0;
    temp = D_8074450C * 0xA;
    new_var = 0;
    D_807FDB2C = new_var;
    D_807FDB30 = new_var;
    D_807FDB36 = 0;
    D_807FDB38 = -1;
    D_807FDB3C = temp;
    D_807FDB3E = temp;
    D_807FDB40 = D_8074450C * 0x135;
    D_807FDB42 = D_8074450C * 0xE5;
    D_807FDB3A = 0x258;
}

void modelSlotGetNodePos();
EffectNode *effectCreate(s32, f32, f32, f32, f32, void *, s32, s32, u8);

void func_80714B84(s32 arg0, f32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    modelSlotGetNodePos(arg2, 1, arg3, &sp3C, &sp38, &sp34);
    effectCreate(arg0, arg1, sp3C, sp38, sp34, NULL, arg2, arg3, (s32) arg4);
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);

void func_80714C08(s32 arg0, f32 arg1, void *arg2, s32 arg3, u8 arg4) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    u16 new_var;

    actorGetNodePos(arg2, arg3, &sp3C, &sp38, &sp34);
    new_var = ((Actor *) arg2)->unk60 & 0x200;
    if ((!new_var && (((Actor *) arg2)->unk4 != NULL)) && (D_807FDB36 & 0x80)) {
        effectFlagsOr(0x40);
    }
    effectCreate(arg0, arg1, sp3C, sp38, sp34, arg2, 0, arg3, (s32) arg4);
}

void func_80714CC0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    effectCreate(arg0, arg1, arg2, arg3, arg4, NULL, 0, 0, 0);
}

extern s32 D_807FBB64;
void effectBuildGridVertices(EffectNode *);
#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))

EffectNode *effectCreate(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, void *arg5, s32 arg6, s32 arg7, u8 arg8) {
    EffectNode *effect;
    EffectGridNode *node;
    s32 found;
    s32 i;

    effectGridRegister((EffectGridNode *)arg0);
    node = D_807FDB00;
    found = 0;
    if (node != NULL) {
        do {
            if (node->unk0 == (void *)arg0) {
                found = 1;
            } else {
                node = node->unk24;
            }
        } while ((found == 0) && (node != NULL));
    }
    if (found == 0) {
        effectResetState();
        return NULL;
    }
    effect = heapAlloc(0x3A0);
    if (D_807FDB04 != NULL) {
        D_807FDB08->next = effect;
        effect->previous = D_807FDB08;
    } else {
        D_807FDB04 = effect;
        effect->previous = NULL;
    }
    D_807FDB08 = effect;
    if ((u8) D_807FDB1D != 0) {
        arg2 *= 4.0f;
        arg3 *= 4.0f;
        arg4 *= 4.0f;
        arg1 *= 4.0f;
        D_807FDB20 *= 4.0f;
        D_807FDB24 *= 4.0f;
    }
    UA1_D08_FIELD(f32, effect, 0x340) = arg2;
    UA1_D08_FIELD(f32, effect, 0x344) = arg3;
    UA1_D08_FIELD(f32, effect, 0x348) = arg4;
    if ((u8) D_807FDB28 != 0) {
        UA1_D08_FIELD(f32, effect, 0x360) = D_807FDB20;
        UA1_D08_FIELD(f32, effect, 0x364) = D_807FDB24;
    } else {
        UA1_D08_FIELD(f32, effect, 0x360) = arg1;
        UA1_D08_FIELD(f32, effect, 0x364) = arg1;
    }
    if ((u8) D_807FDB0F != 0) {
        UA1_D08_FIELD(u8, effect, 0x36A) = *(u8 *)&D_807FDB0C;
        UA1_D08_FIELD(u8, effect, 0x36B) = *(u8 *)&D_807FDB0D;
        UA1_D08_FIELD(u8, effect, 0x36C) = *(u8 *)&D_807FDB0E;
        UA1_D08_FIELD(u8, effect, 0x36D) = *(u8 *)&D_807FDB0F;
    } else {
        UA1_D08_FIELD(u8, effect, 0x36A) = *((u8 *)node + 0x10);
        UA1_D08_FIELD(u8, effect, 0x36B) = *((u8 *)node + 0x11);
        UA1_D08_FIELD(u8, effect, 0x36C) = *((u8 *)node + 0x12);
        UA1_D08_FIELD(u8, effect, 0x36D) = *((u8 *)node + 0x13);
    }
    UA1_D08_FIELD(u8, effect, 0x36E) = *(u8 *)&D_807FDB18;
    effect->mode = *(u8 *)&D_807FDB1D;
    UA1_D08_FIELD(s16, effect, 0x368) = D_807FDB1A;
    UA1_D08_FIELD(s32, effect, 0x380) = *((u8 *)node + 9) * *((u8 *)node + 8);
    UA1_D08_FIELD(u8, effect, 0x334) = arg8;
    effect->resource = (s32)arg5;
    UA1_D08_FIELD(s16, effect, 0x33C) = arg6;
    UA1_D08_FIELD(s8, effect, 0x33E) = arg7;
    UA1_D08_FIELD(s16, effect, 0x34E) = D_807FDB30;
    UA1_D08_FIELD(u8, effect, 0x350) = D_807FDB1C;
    UA1_D08_FIELD(u8, effect, 0x351) = 0;
    UA1_D08_FIELD(s32, effect, 0x354) = D_807FDB10;
    UA1_D08_FIELD(s32, effect, 0x358) = 0;
    UA1_D08_FIELD(s32, effect, 0x35C) = D_807FDB2C;
    if (D_807FBB64 & 0x100) {
        UA1_D08_FIELD(s16, effect, 0x34C) = 0x7D0;
    } else {
        UA1_D08_FIELD(s16, effect, 0x34C) = D_807FDB3A;
    }
    UA1_D08_FIELD(EffectGridNode *, effect, 0x330) = node;
    effect->next = NULL;
    UA1_D08_FIELD(s32, effect, 0x328) = D_807FDB14;
    effect->allocation = NULL;
    UA1_D08_FIELD(s16, effect, 0x388) = D_807FDB38;
    UA1_D08_FIELD(s8, effect, 0x38A) = -1;
    effect->flags = D_807FDB36;
    UA1_D08_FIELD(s16, effect, 0x38E) = D_807FDB3C;
    UA1_D08_FIELD(s16, effect, 0x390) = D_807FDB3E;
    UA1_D08_FIELD(s16, effect, 0x392) = D_807FDB40;
    UA1_D08_FIELD(s16, effect, 0x394) = D_807FDB42;
    for (i = 0; i < D_80750AB4; i++) {
        ((void **)effect)[i * 2] = heapAlloc(0x200);
        ((void **)effect)[i * 2 + 1] = heapAlloc(0x200);
    }
    *((u8 *)effect + 0x20) = D_80750AB4;
    effectBuildGridVertices(effect);
    effectResetState();
    return effect;
}
#undef UA1_D08_FIELD

typedef struct Fx119AEffectVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Fx119AEffectVertex;

void effectBuildGridVertices(EffectNode *effect) {
    EffectGridNode *node;
    Fx119AEffectVertex *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 startX;
    s32 x;
    s32 y;
    node = *(EffectGridNode **)((u8 *)effect + 0x330);
    vertexIndex = 0;
    if (node->unk8 == 0) {} // FAKE: gives unk8 the first candidate index (a1)
    if (node->unk9 == 0) {} // FAKE: gives unk9 the second candidate index (a2)
    node = *(EffectGridNode **)((u8 *)effect + 0x330); // FAKE: kill splits the unk8/unk9 webs so they reload in the arms
    x = -(node->unk8 * node->unkC) / 2;
    startX = x;
    if (effect->mode == 0) {
        y = -(node->unk9 * node->unkE) / 2;
    } else {
        y = (node->unk9 * node->unkE) / 2;
    }
    for (row = 0; row < node->unk9; row++) {
        x = startX;
        column = 0;
        if (node->unk8 > 0) {
            vertex = (Fx119AEffectVertex *)((u8 *)effect + 0x28) + vertexIndex;
            do {
                    vertex[0].x = x;
                    vertex[0].y = y;
                    vertex[0].z = 0;
                    vertex[0].s = 0;
                    vertex[0].t = 0;
                    vertex[1].x = node->unkC + x;
                    vertex[1].y = y;
                    vertex[1].z = 0;
                    vertex[1].s = node->unkC << 5;
                    vertex[1].t = 0;
                    vertex[2].x = x;
                    vertexIndex += 2;
                    vertex += 2;
                    if (effect->mode == 0) {
                        vertex[0].y = node->unkE + y;
                    } else {
                        vertex[0].y = y - node->unkE;
                    }
                    vertex[0].z = 0;
                    vertex[0].s = 0;
                    vertexIndex += 1;
                    vertex += 1;
                    vertex[-1].t = node->unkE << 5;
                    vertex[0].x = node->unkC + x;
                    if (effect->mode == 0) {
                        vertex[0].y = node->unkE + y;
                    } else {
                        vertex[0].y = y - node->unkE;
                    }
                    vertex[0].z = 0;
                    vertex[0].s = node->unkC << 5;
                    vertexIndex += 1;
                    vertex += 1;
                    vertex[-1].t = node->unkE << 5;
                    x += node->unkC;
                    column++;
                } while (column < node->unk8);
            }
            if (effect->mode == 0) {
                y += node->unkE;
            } else {
                y -= node->unkE;
            }
    }
}

#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))
extern u32 gFrameCounter;
extern s32 gPlayerSlots;
void assetFreeBuffer(s32, s32, s32);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
s32 renderEntryAddOrUpdate(s32, u8, void *, f32, f32, f32, s32, s32, s32, s32, s32);
void func_80715A3C(s16 *, u8, u8 *, s32, s32, s32 *);
void effectFreeAndUnlink(EffectNode *);
void effectComputeTransformMatrix(Mtx *, u8, f32, f32, f32, f32, f32, f32, f32, f32, u8);

void effectUpdateAll(u8 arg0) {
    EffectNode *effect;
    u8 sp7B;
    EffectGridNode *node2;
    s32 i;
    s32 offset;
    s32 offset2;

    effect = D_807FDB04;
    for (; effect != NULL; effect = effect->next) {
        if (UA1_D08_FIELD(s16, effect, 0x368) == 0) {
            UA1_D08_FIELD(u8, effect, 0x32C) = 0;
            UA1_D08_FIELD(u8, effect, 0x32D) = 0;
            UA1_D08_FIELD(u8, effect, 0x21) = 0;
            UA1_D08_FIELD(s32, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x18) = gFrameCounter;
            effect->flags &= 0xFFEF;
            switch (UA1_D08_FIELD(u8, effect, 0x334)) {
            case 1:
                modelSlotGetNodePos(UA1_D08_FIELD(s16, effect, 0x33C), 1, UA1_D08_FIELD(u8, effect, 0x33E),
                                    (f32 *)((u8 *)effect + 0x340), (f32 *)((u8 *)effect + 0x344),
                                    (f32 *)((u8 *)effect + 0x348));
                break;
            case 2: {
                if ((UA1_D08_FIELD(Actor *, effect, 0x338)->unk60 & 0x200) != 0 || UA1_D08_FIELD(Actor *, effect, 0x338)->unk4 == NULL) {
                    actorGetNodePos(UA1_D08_FIELD(Actor *, effect, 0x338), UA1_D08_FIELD(u8, effect, 0x33E), (f32 *)((u8 *)effect + 0x340),
                                    (f32 *)((u8 *)effect + 0x344), (f32 *)((u8 *)effect + 0x348));
                } else {
                    effect->flags |= 0x10;
                }
                break;
            }
            }
            sp7B = 0;
            if (!arg0 || (effect->flags & 1)) {
                if (UA1_D08_FIELD(void *, effect, 0x328) != NULL) {
                    ((void (*)(void *, u8 *))UA1_D08_FIELD(void *, effect, 0x328))(effect, &sp7B);
                }
            } else if (UA1_D08_FIELD(void *, effect, 0x328) != NULL) {
                if (D_80750AB4 > 0) {
                    i = 0;
                    offset = 0;
                    do {
                        if (((u8 *)gPlayerSlots)[offset] != 0) {
                            memcpy((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128,
                                   (u8 *)effect + i * 0x80 + (D_807444FC ^ 1) * 0x40 + 0x128, 0x40);
                        }
                        i++;
                        offset += 0x2F0;
                    } while (i < D_80750AB4);
                }
                UA1_D08_FIELD(u8, effect, 0x32C) = 3;
            }
            if (UA1_D08_FIELD(s16, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x16) ==
                UA1_D08_FIELD(s16, effect, 0x34E)) {
                UA1_D08_FIELD(s16, effect, 0x34E) = 0;
                UA1_D08_FIELD(s32, effect, 0x358) = UA1_D08_FIELD(s32, effect, 0x358) + 1;
                if (UA1_D08_FIELD(s32, effect, 0x354) == UA1_D08_FIELD(s32, effect, 0x358) &&
                    -1 != UA1_D08_FIELD(s32, effect, 0x354)) {
                    UA1_D08_FIELD(u8, effect, 0x32D) = 1;
                }
            }
            if (sp7B != 0) {
                UA1_D08_FIELD(u8, effect, 0x32D) = 1;
            }
            if (UA1_D08_FIELD(u8, effect, 0x32D) != 0) {
                effectFreeAndUnlink(effect);
            } else {
                if (D_80750AB4 >= 2) {
                    i = 1;
                    offset = 0x2F0;
                    do {
                        if (((u8 *)gPlayerSlots)[offset] != 0) {
                            memcpy((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128,
                                   (u8 *)effect + D_807444FC * 0x40 + 0x128, 0x40);
                        }
                        i++;
                        offset += 0x2F0;
                    } while (i < D_80750AB4);
                }
                if (UA1_D08_FIELD(u8, effect, 0x32C) != 3) {
                    if (D_80750AB4 > 0) {
                        i = 0;
                        offset = 0;
                        do {
                            if (((u8 *)gPlayerSlots)[offset] != 0) {
                                effectComputeTransformMatrix((Mtx *)((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128),
                                              UA1_D08_FIELD(u8, effect, 0x32C),
                                              UA1_D08_FIELD(f32, effect, 0x360),
                                              UA1_D08_FIELD(f32, effect, 0x364),
                                              UA1_D08_FIELD(f32, (u8 *)gPlayerSlots + offset, 0x21C),
                                              UA1_D08_FIELD(f32, (u8 *)gPlayerSlots + offset, 0x220),
                                              UA1_D08_FIELD(f32, (u8 *)gPlayerSlots + offset, 0x224),
                                              UA1_D08_FIELD(f32, effect, 0x340),
                                              UA1_D08_FIELD(f32, effect, 0x344),
                                              UA1_D08_FIELD(f32, effect, 0x348), effect->mode);
                            }
                            i++;
                            offset += 0x2F0;
                        } while (i < D_80750AB4);
                    }
                    UA1_D08_FIELD(u8, effect, 0x32C) = 3;
                }
                if (effect->mode == 0) {
                    s32 renderArg;
                    if (effect->flags & 4) {
                        renderArg = 4;
                        if (!(effect->flags & 8)) {
                            UA1_D08_FIELD(s8, effect, 0x38A) = mapChunkFindByPosition(
                                UA1_D08_FIELD(f32, effect, 0x340), UA1_D08_FIELD(f32, effect, 0x344),
                                UA1_D08_FIELD(f32, effect, 0x348), 0);
                        }
                    } else {
                        renderArg = 1;
                    }
                    renderEntryAddOrUpdate(0, 5, effect, UA1_D08_FIELD(f32, effect, 0x340),
                                           UA1_D08_FIELD(f32, effect, 0x344),
                                           UA1_D08_FIELD(f32, effect, 0x348),
                                           UA1_D08_FIELD(s16, effect, 0x34C), 0, 1, -1, renderArg);
                } else {
                    renderEntryAddOrUpdate(0, 5, effect, UA1_D08_FIELD(f32, effect, 0x340),
                                           UA1_D08_FIELD(f32, effect, 0x344),
                                           UA1_D08_FIELD(f32, effect, 0x348), 0, 0, 1, -1, 3);
                }
                func_80715A3C((s16 *)UA1_D08_FIELD(void *, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x20),
                              UA1_D08_FIELD(u8, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x15),
                              (u8 *)UA1_D08_FIELD(void *, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x1C),
                              UA1_D08_FIELD(s32, effect, 0x380), UA1_D08_FIELD(s16, effect, 0x34E),
                              &UA1_D08_FIELD(s32, effect, 0x370));
                if (!arg0 || (effect->flags & 1)) {
                    UA1_D08_FIELD(u8, effect, 0x351) = UA1_D08_FIELD(u8, effect, 0x351) + 1;
                    if (UA1_D08_FIELD(u8, effect, 0x350) == UA1_D08_FIELD(u8, effect, 0x351)) {
                        UA1_D08_FIELD(s16, effect, 0x34E) = UA1_D08_FIELD(s16, effect, 0x34E) + 1;
                        UA1_D08_FIELD(u8, effect, 0x351) = 0;
                    }
                }
            }
            effect->flags |= 8;
        } else {
            if (!arg0 || (effect->flags & 1)) {
                UA1_D08_FIELD(s16, effect, 0x368) = UA1_D08_FIELD(s16, effect, 0x368) - 1;
            }
        }
    }
    for (node2 = D_807FDB00; node2 != NULL; node2 = node2->unk24) {
        if (gFrameCounter - node2->unk18 >= 0xB) {
            continue;
        }
        if (node2->unk18 == -1) {
            continue;
        }
        if (node2->unk16 * node2->unk8 * node2->unk9 > 0) {
            i = 0;
            offset2 = 0;
            do {
                if (node2 && node2) {} // FAKE: raises node2 priority above offset2 (node2 -> s1, offset2 -> s2)
                if (((s32 *)((u8 *)node2->unk1C + offset2))[1] != -1) {
                    if (gFrameCounter - node2->unk18 == 0xA) {
                        assetFreeBuffer(((s32 *)((u8 *)node2->unk1C + offset2))[0], 0x319, 0x1F);
                        ((s32 *)((u8 *)node2->unk1C + offset2))[1] = -1;
                    }
                }
                i++;
                offset2 += 8;
            } while (i < node2->unk16 * node2->unk8 * node2->unk9);
        }
    }
}
#undef UA1_D08_FIELD

void effectFreeAndUnlink(EffectNode *);

void effectFreeByResource(s32 arg0) {
    EffectNode *effect;

    effect = D_807FDB04;
    if (effect != NULL) {
        do {
            if (arg0 == effect->resource) {
                effectFreeAndUnlink(effect);
            }
            effect = effect->next;
        } while (effect != NULL);
    }
}

void effectFreeAll(void) {
    EffectNode *effect;
    EffectNode *next;

    effect = D_807FDB04;
    if (effect != NULL) {
        do {
            next = effect->next;
            effectFreeAndUnlink(effect);
            effect = next;
        } while (next != NULL);
    }
}

void renderEntryRemove(s32, s32, s32, void *);
void func_8062D26C(void *);
void heapFreeDeferred(void *);

void effectFreeAndUnlink(EffectNode *effect) {
    u8 sp3F;
    s32 temp_a0;
    s32 i;
    EffectNode *previous;
    EffectNode *next;
    EffectNode *buffer;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            renderEntryRemove(0, (s32)effect, 4, &sp3F - 8);
        } else {
            func_8062D26C(effect);
        }
    } else {
        renderEntryRemove(0, (s32)effect, 3, &sp3F - 8);
    }
    temp_a0 = (s32)effect->allocation;
    if (temp_a0 != 0) {
        heapFreeDeferred((void *)temp_a0);
    }
    i = 0;
    buffer = effect;
    while (i < effect->itemCount) {
        heapFreeDeferred(((void **)buffer)[0]);
        heapFreeDeferred(((void **)buffer)[1]);
        i += 1;
        buffer = (EffectNode *)((u8 *)buffer + 8);
    }
    if (osCicId != 0x17D9) {
        osSetTime((s64)(s32)randomLcgNext());
    }
    previous = effect->previous;
    next = effect->next;
    heapFreeDeferred(effect);
    if (previous != NULL) {
        previous->next = next;
    } else {
        D_807FDB04 = next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        D_807FDB08 = previous;
    }
}

typedef struct EffectRouteEntry {
    s32 value;
    s32 column;
} EffectRouteEntry;

s32 assetLoad(s32, s16, s32, s32);

void func_80715A3C(s16 *arg0, u8 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 *arg5) {
    u8 category;
    s32 i;
    s32 index;
    s32 value;
    s32 *out;
    EffectRouteEntry *entry;

    i = 0;
    if (arg3 > 0) {
        out = arg5;
        index = arg3 * arg4;
        entry = (EffectRouteEntry *)arg2;
        entry += index;
        do {
            if (entry->column == -1) {
                if (arg1) {
                    category = 0x19;
                } else {
                    category = 7;
                }
                value = assetLoad(category, arg0[index + i], 0, 0);
                *out = value;
                entry->value = value;
            } else {
                *out = entry->value;
            }
            i += 1;
            out += 1;
            entry += 1;
            (entry + (-1))->column = arg4;
        } while (i != arg3);
    }
}

s32 func_80611E60(s32);
void matrixMakeRotationZ(f32 (*)[4], f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 distance3D(f32, f32, f32, f32, f32, f32);

void effectComputeTransformMatrix(Mtx *arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 arg10) {
    f32 pad[2];
    f32 distance;
    f32 value;
    f32 absValue;
    s32 angle;
    s32 temp;
    f32 scale[4][4];
    f32 transform[4][4];
    Mtx mtx;

    if (arg10 == 0) {
        distance = distance3D(arg4, arg5, arg6, arg7, arg8, arg9);
        value = distance;
        if ((f64)distance < 0.1) {
            value = 1.0f;
        }
        distance = (arg5 - arg8) / value;
        if (distance > 0.0f) {
            absValue = distance;
        } else {
            absValue = -distance;
        }
        temp = func_80611E60((s32)((f64)absValue * 65536.0)) >> 4;
        angle = temp;
        if (distance >= 0.0f) {
            angle = 0xFFF - temp;
        }
        if (arg1 != 2) {
            guScaleF(scale, arg2, arg3, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        guRotateF(transform, (f32)(((f64)angle / 4095.0) * 360.0), 1.0f, 0.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        value = mathAngleBetweenPointsRad(arg4, arg6, arg7, arg9);
        guRotateF(transform, value * 57.295776f, 0.0f, 1.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, arg7, arg8, arg9);
        guMtxCatF(scale, transform, scale);
    } else {
        if (arg1 != 2) {
            guScaleF(scale, arg2, arg3, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        matrixMakeRotationZ(transform, (f32)D_807FDB34);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, arg7, arg8, arg9);
        guMtxCatF(scale, transform, scale);
    }
    if ((arg1 == 1) || (arg1 == 2)) {
        guMtxF2L(scale, &mtx);
        guMtxCatL(arg0, &mtx, arg0);
    } else {
        guMtxF2L(scale, arg0);
    }
}

f32 distance3D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 x;
    f32 y;
    f32 z;

    x = arg0 - arg3;
    y = arg1 - arg4;
    z = arg2 - arg5;
    return sqrtf((x * x) + (y * y) + (z * z));
}

typedef struct EffectTextureNode {
    u8 pad0[0xA];
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    u8 unk14;
} EffectTextureNode;

typedef struct EffectDrawView {
    u8 pad0[0x21];
    u8 unk21;
    u8 pad22[6];
    Vtx unk28[48];
    u8 pad328[8];
    EffectTextureNode *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x1E];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    u8 unk36E;
    u8 unk36F;
    void *unk370[4];
    s32 unk380;
    u8 pad384[4];
    s16 unk388;
    s8 unk38A;
    u8 pad38B;
    u16 unk38C;
    s16 unk38E;
    s16 unk390;
    s16 unk392;
    s16 unk394;
} EffectDrawView;

#define EFFECT_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern u8 gCurrentPlayerIndex;
extern s16 D_80744490;
extern s16 D_80744494;
extern Mtx D_2000000;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern Mtx D_2000200;
Gfx *func_805FD030(Gfx *);
void lightSampleColorAtPosition(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
s32 mapChunkContainsPoint(s16, s16, s16);
s32 mapChunkIsInUse(s16);

Gfx *effectGridBuildDisplayList(EffectDrawView *arg0, Gfx *arg1, s16 arg2) {
    s32 i;
    u8 red;
    u8 green;
    u8 blue;
    f32 colorRed = 1.0f;
    f32 colorGreen = 1.0f;
    f32 colorBlue = 1.0f;
    Gfx *glist;

    if (arg0->unk38C & 0x50) {
        return arg1;
    }
    if ((((D_807FBB4C->unk154 == 0x83) || (D_807FBB4C->unk154 == 0x67)) && !(arg0->unk38C & 0x20)) || (((D_807FBB60 & 0x100002) == 0x100002) && !(arg0->unk38C & 0x100))) {
        return arg1;
    }
    if (arg2 == -1) {
        arg2 = arg0->unk38A;
    }
    if (arg0->unk388 != -1) {
        if (arg0->unk36F != 0) {
            if (mapChunkContainsPoint((s16)((f64)arg0->unk340 * 0.25), (s16)((f64)arg0->unk344 * 0.25), arg0->unk388) == 0) {
                return arg1;
            }
        } else if (arg2 != arg0->unk388) {
            return arg1;
        }
    }
    glist = ((Gfx *(*)[2])arg0)[arg0->unk21][D_807444FC];
    arg0->unk21++;
    EFFECT_WRITE_GFX(arg1++, 0xDE000000, osVirtualToPhysical(glist));
    EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3000A01, 0);
    EFFECT_WRITE_GFX(glist++, 0xD9000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3001801, 0xC0);
    if (arg0->unk36E != 0) {
        EFFECT_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200005);
        EFFECT_WRITE_GFX(glist++, 0xE200001C, 0x504B50);
    } else {
        EFFECT_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200004);
        EFFECT_WRITE_GFX(glist++, 0xE200001C, 0x504240);
    }
    EFFECT_WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    EFFECT_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (arg0->unk330->unk14 == 0 && mapChunkIsInUse(arg2)) {
        lightSampleColorAtPosition(arg0->unk340, arg0->unk344, arg0->unk348, 0, &red, &green, &blue, arg2);
        colorRed = (f32)((f64)red / 255.0);
        colorGreen = (f32)((f64)green / 255.0);
        colorBlue = (f32)((f64)blue / 255.0);
    }
    gDPSetPrimColor(glist++, 0, 0, (u32)((f32)arg0->unk36A * colorRed), (u32)((f32)arg0->unk36B * colorGreen), (u32)((f32)arg0->unk36C * colorBlue), arg0->unk36D);
    if (arg0->unk36F != 0) {
        EFFECT_WRITE_GFX(glist++, 0xDA380007, &D_20000C0);
        EFFECT_WRITE_GFX(glist++, 0xDA380003, &D_2000180);
        glist = func_805FD030(glist);
        if (arg0->unk388 == -1) {
            EFFECT_WRITE_GFX(glist++, 0xED000000 | (((s32)((f32)arg0->unk38E * 4.0f) & 0xFFF) << 12) | ((s32)((f32)arg0->unk390 * 4.0f) & 0xFFF), (((s32)((f32)arg0->unk392 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)arg0->unk394 * 4.0f) & 0xFFF));
        }
    }
    EFFECT_WRITE_GFX(glist++, 0xDA380000, osVirtualToPhysical((u8 *)arg0 + (gCurrentPlayerIndex << 7) + (D_807444FC << 6) + 0x128));

    for (i = 0; i < arg0->unk380; i++) {
        if (D_807F6009 != 5 || D_807F600C != (s32)arg0->unk370[i]) {
            EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
            switch (arg0->unk330->unkB) {
                case 0:
                    gDPLoadTextureBlock_4b(glist++, arg0->unk370[i], arg0->unk330->unkA, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 1:
                    gDPLoadTextureBlock(glist++, arg0->unk370[i], arg0->unk330->unkA, G_IM_SIZ_8b, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 2:
                    gDPLoadTextureBlock(glist++, arg0->unk370[i], arg0->unk330->unkA, G_IM_SIZ_16b, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(glist++, arg0->unk370[i], arg0->unk330->unkA, G_IM_SIZ_32b, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
            }
            D_807F600C = (s32)arg0->unk370[i];
        }
        EFFECT_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(arg0->unk28 + (i << 2)));
        EFFECT_WRITE_GFX(glist++, 0x06000206, 0x406);
    }
    EFFECT_WRITE_GFX(glist++, 0xD8380002, 0x40);
    EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3001801, 0);
    if (arg0->unk36F != 0) {
        EFFECT_WRITE_GFX(glist++, 0xDA380007, &D_2000000);
        EFFECT_WRITE_GFX(glist++, 0xDA380005, &D_2000200);
        if (arg0->unk388 == -1) {
            EFFECT_WRITE_GFX(glist++, 0xED000000, ((((s32)((f32)D_80744490 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)D_80744494 * 4.0f) & 0xFFF)));
        }
    }
    EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xDF000000, 0);
    D_807F6009 = 5;
    return arg1;
}
