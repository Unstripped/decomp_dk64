#include "common.h"

typedef struct KaN5_Node {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[8];
    struct KaN5_Node *next;
} KaN5_Node;

typedef struct KaN5_Sub140 {
    u8 pad0[0x8C];
    KaN5_Node *unk8C;
} KaN5_Sub140;

typedef struct KaN5_Elem {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} KaN5_Elem;

typedef struct KaN5_Callback {
    s32 type;
    u8 pad4[4];
    void *actor;
    s32 count;
    KaN5_Elem *elems;
    struct KaN5_Callback *next;
} KaN5_Callback;

typedef struct KaN5_Actor {
    u8 pad0[0x64];
    u32 unk64;
    u8 pad68[0x14];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x6C];
    s16 unkF4;
    s16 unkF6;
    u8 padF8[4];
    u8 unkFC;
    u8 unkFD;
    u8 padFE[0x3E];
    KaN5_Callback *unk13C;
    KaN5_Sub140 *unk140;
} KaN5_Actor;

extern u8 D_807FB606;
s32 actorTableContains(void *);
void actorUpdateCollisionSpheres(void *, s32);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_80675478();
void func_806755A8();

u8 func_80674B90(KaN5_Actor *arg0, KaN5_Actor *arg1, f32 *arg2, f32 *arg3) {
    KaN5_Callback *cb;
    f32 posX_f;
    f32 posY_f;
    f32 posZ_f;
    s32 posX;
    s32 posY;
    s32 posZ;
    KaN5_Elem *elem;
    KaN5_Node *node;
    KaN5_Sub140 *sub140;
    s32 i;
    s32 j;
    f32 elemX_f;
    s32 pad2[1];
    s8 foundCb;
    u8 matched;

    cb = arg0->unk13C;
    matched = 0;
    foundCb = 0;
    D_807FB606 = 0;
    sub140 = arg0->unk140;
    actorUpdateCollisionSpheres(arg0, 1);
    if (!actorTableContains(arg1)) {
        return 0;
    }

    posX_f = arg1->unk7C;
    posY_f = arg1->unk80;
    posZ_f = arg1->unk84;

    if (cb != NULL) {
        do {
            if (cb->type == 0x8000 && cb->actor == arg1) {
                elem = cb->elems;
                foundCb = 1;
                for (j = 0; j < cb->count; j++, elem++) {
                    elemX_f = elem->unk0;
                    node = sub140->unk8C;
                    for (i = elem->unk14 - 1; i != 0; i--) {
                        node = node->next;
                    }
                    if (func_80674ADC((s32)(posX_f * 8.0f), (s32)(posY_f * 8.0f), (s32)(posZ_f * 8.0f), (s32)(elemX_f * 8.0f),
                                      node->unk10, node->unk14, node->unk18, node->unk1C)) {
                        matched = 1;
                        func_80675478(arg0, elem, arg2, arg3);
                    }
                    func_806755A8((s32)(posX_f * 8.0f), (s32)(posZ_f * 8.0f), node->unk10, node->unk18, (s32)&arg1->unkF4, (s32)&arg1->unkF6);
                    arg1->unkFC = 1;
                    arg1->unkFD = 1;
                }
            }
            cb = cb->next;
        } while (cb != NULL && !(u8)foundCb);  // FAKE: s8 foundCb + (u8) read: keeps `foundCb = 1` off the shared u8 constant-1 web (li t2 ring temp) while the loop test stays lbu
    }

    if (D_807FB606 != 0) {
        arg1->unk64 |= 0x100;
    }
    return matched;
}

typedef struct KaN5_NodeE14 {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[4];
    u16 unk24;
    u8 unk26;
    u8 unk27;
    struct KaN5_NodeE14 *next;
} KaN5_NodeE14;

typedef struct KaN5_Sub140E14 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x7C];
    KaN5_NodeE14 *unk8C;
} KaN5_Sub140E14;

typedef struct KaN5_ActorE14 {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[4];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x8C];
    void *unk114;
    u8 pad118[0x28];
    KaN5_Sub140E14 *unk140;
    u8 unk144;
} KaN5_ActorE14;

typedef struct KaN5_ActorEntryE14 {
    KaN5_ActorE14 *actor;
    s32 unk4;
} KaN5_ActorEntryE14;

extern u16 gActiveActorCount;
extern KaN5_ActorEntryE14 gActiveActors[];
struct Beh798_Node;
struct Beh7982_80675180_0;
struct Beh7982_80675180_4;
extern struct Beh798_Node *D_807FB620;
extern struct Beh798_Node *D_807FB624;
extern s32 D_807FB628;

s32 func_80679010(void *, void *);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
void actorUpdateCollisionSpheres(void *, s32);
f32 func_80675234(s32, s32, s32, s32, s32, s32, s32);
void func_80675180(struct Beh7982_80675180_0 *, f32, f32, f32, struct Beh7982_80675180_4 *, f32 *, f32 *, f32 *);
void func_806752D4(s32, f32, f32, f32, f32, s32, s32);
void func_80675380(s32, void *);

void func_80674E14(KaN5_ActorE14 *arg0) {
    s32 i;
    KaN5_ActorE14 *actor;
    KaN5_Sub140E14 *actor_sub140;
    s32 sub_unk0;
    s32 sub_unk4;
    s32 sub_unk8;
    s32 sub_unkC;
    KaN5_NodeE14 *node1;
    KaN5_NodeE14 *node2;
    s32 var_s4;
    s32 var_s2;
    KaN5_Sub140E14 *sub140;
    f32 dist;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s32 s0;
    u16 mask1;
    u16 mask2;
    KaN5_ActorEntryE14 *entry;

    sub140 = arg0->unk140;
    sub_unk0 = 0;
    if (sub_unk0) {} // FAKE: raises sub_unk0's colouring priority so it gets s7 while unk4 is loaded first
    sub_unk4 = sub140->unk4;
    sub_unk0 = sub140->unk0;
    sub_unk8 = sub140->unk8;
    sub_unkC = sub140->unkC;
    i = 0;
    if (gActiveActorCount > 0) {
        entry = gActiveActors;
        do {
            D_807FB620 = NULL;
            D_807FB624 = NULL;
            D_807FB628 = 0;
            actor = entry->actor;
            s0 = 0;
            actor_sub140 = actor->unk140;
            if (actor->unk114 != NULL && (actor->unk60 & 0x40) && func_80679010(actor, arg0)) {
                s0 = 1;
            }
            if ((arg0->unk60 & 0x80) && func_80679010(arg0, actor)) {
                s0 = 1;
            }
            if ((actor->unk60 & 0x2000) == 0 &&
                sub140 != actor_sub140 &&
                actor->unk144 != 1 &&
                (actor->unk60 & 0x10) &&
                s0 == 0 &&
                func_80674ADC(sub_unk0, sub_unk4, sub_unk8, sub_unkC,
                              actor_sub140->unk0, actor_sub140->unk4, actor_sub140->unk8, actor_sub140->unkC)) {
                actorUpdateCollisionSpheres(arg0, 0);
                var_s4 = 1;
                actorUpdateCollisionSpheres(actor, 0);
                for (node1 = sub140->unk8C; node1 != NULL; node1 = node1->next, var_s4++) {
                    if (node1->unk26 != 0 && (node1->unk27 & 8) == 0) {
                        var_s2 = 1;
                        for (node2 = actor_sub140->unk8C; node2 != NULL; node2 = node2->next, var_s2++) {
                            if (node2->unk26 != 0 && (node2->unk27 & 8) == 0) {
                                if (func_80674ADC(node1->unk10, node1->unk14, node1->unk18, node1->unk1C,
                                                  node2->unk10, node2->unk14, node2->unk18, node2->unk1C)) {
                                    mask1 = ~node1->unk24;
                                    mask2 = ~node2->unk24;
                                    if ((mask1 & actor->unk5C) && (mask2 & arg0->unk5C)) {
                                        dist = func_80675234(sub_unk0, sub_unk4, sub_unk8,
                                                             node2->unk10, node2->unk14, node2->unk18, node2->unk1C);
                                        func_80675180((struct Beh7982_80675180_0 *)actor_sub140, arg0->unk7C, arg0->unk80, arg0->unk84, (struct Beh7982_80675180_4 *)node2,
                                                      &sp70, &sp6C, &sp68);
                                        func_806752D4(arg0->unk54, dist, sp70, sp6C, sp68, var_s4, var_s2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (D_807FB620 != NULL) {
                func_80675380((s32)arg0, actor);
            }
            i++; entry++; // FAKE: one line keeps the entry/i spill-store order
        } while (i < gActiveActorCount);
    }
}

typedef struct Beh7982_80675180_0 {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
} Beh7982_80675180_0;

typedef struct Beh7982_80675180_4 {
    u8 pad0[0x20];
    s32 unk20;
} Beh7982_80675180_4;

extern u8 D_807444FC;
void matrix4Invert(float [4][4], float [4][4]);

void func_80675180(Beh7982_80675180_0 *arg0, f32 arg1, f32 arg2, f32 arg3, Beh7982_80675180_4 *arg4, f32 *arg5, f32 *arg6, f32 *arg7) {
    float sp70[4][4];
    float sp30[4][4];
    u32 temp_v0;
    Mtx *mtx;

    mtx = arg0->unk74[D_807444FC];
    temp_v0 = arg4->unk20;
    if (temp_v0 == -1) {
        memcpy(sp70, arg0->unk70, sizeof(sp70));
    } else {
        guMtxL2F(sp70, (Mtx *)(((temp_v0 >> 6) << 6) + (u8 *)mtx));
    }
    matrix4Invert(sp30, sp70);
    guMtxXFMF(sp30, arg1, arg2, arg3, arg5, arg6, arg7);
}

f32 func_80675234(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;

    temp_fv0 = (f32) (arg0 - arg3);
    temp_fv1 = (f32) (arg1 - arg4);
    temp_fa1 = (f32) (arg2 - arg5);
    temp_fv1_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)) - (f32) arg6;
    var_fa0 = temp_fv1_2;
    if ((f64) temp_fv1_2 < 0.0) {
        var_fa0 = 0.0f;
    }
    return var_fa0 / (f32)8;
}

typedef struct Beh798_Node {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    struct Beh798_Node *next;
} Beh798_Node;

void *heapAlloc(s32);
extern Beh798_Node *D_807FB620;
extern Beh798_Node *D_807FB624;
extern s32 D_807FB628;

void func_806752D4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    Beh798_Node *temp_v0;

    temp_v0 = heapAlloc(sizeof(Beh798_Node));
    temp_v0->unk0 = arg1;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = arg4;
    temp_v0->unk10 = arg5;
    temp_v0->unk14 = arg6;
    temp_v0->unk18 = arg0;
    temp_v0->next = NULL;
    if (D_807FB620 != NULL) {
        D_807FB624->next = temp_v0;
    } else {
        D_807FB620 = temp_v0;
    }
    D_807FB624 = temp_v0;
    D_807FB628 += 1;
}

typedef struct Beh7982_Elem {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Beh7982_Elem;

void heapFree(void *);
void actorAppendCallback(void *, s32, s32, u8, s32, void *);

void func_80675380(s32 arg0, void *arg1) {
    Beh7982_Elem *arr;
    s32 i;
    Beh798_Node *node;
    Beh798_Node *next;

    arr = heapAlloc(D_807FB628 * sizeof(Beh7982_Elem));
    node = D_807FB620;
    for (i = 0; i < D_807FB628; i++) {
        arr[i].unk0 = node->unk0;
        arr[i].unk4 = node->unk4;
        arr[i].unk8 = node->unk8;
        arr[i].unkC = node->unkC;
        arr[i].unk10 = node->unk10;
        arr[i].unk14 = node->unk14;
        arr[i].unk18 = node->unk18;
        next = node->next;
        heapFree(node);
        node = next;
    }
    actorAppendCallback(arg1, arg0, 0x8000, 0, D_807FB628, arr);
}

typedef struct Beh7982_Node28 {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x4];
    struct Beh7982_Node28 *next;
} Beh7982_Node28;

typedef struct Beh7982_Sub140 {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
    u8 pad7C[0x10];
    Beh7982_Node28 *unk8C;
} Beh7982_Sub140;

typedef struct Beh7982_Arg0_5478 {
    u8 pad0[0x140];
    Beh7982_Sub140 *unk140;
} Beh7982_Arg0_5478;

typedef struct Beh7982_Arg1_5478 {
    u8 pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x4];
    s32 unk14;
} Beh7982_Arg1_5478;

void func_80675478(Beh7982_Arg0_5478 *arg0, Beh7982_Arg1_5478 *arg1, f32 *arg2, f32 *arg3) {
    s32 i;
    Beh7982_Node28 *node;
    Mtx *mtx;
    float sp4C[4][4];
    u32 temp_v1;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    node = arg0->unk140->unk8C;
    for (i = arg1->unk14 - 1; i != 0; i--) {
        node = node->next;
    }
    mtx = arg0->unk140->unk74[D_807444FC ^ 1];
    temp_v1 = node->unk20;
    if (temp_v1 == -1) {
        memcpy(sp4C, arg0->unk140->unk70, sizeof(sp4C));
        guMtxXFMF(sp4C, arg1->unk4, arg1->unk8, arg1->unkC, &sp44, &sp40, &sp3C);
    } else {
        guMtxXFML((Mtx *)(((temp_v1 >> 6) << 6) + (u8 *)mtx), arg1->unk4, arg1->unk8, arg1->unkC, &sp44, &sp40, &sp3C);
    }
    *arg2 = sp44;
    *arg3 = sp3C;
}

s32 func_80611E60(s32);
void func_806742C0(s16, s16, s32, s32);

void func_806755A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad1;
    s32 pad2;
    f32 dist;
    s16 angle;
    s32 dx;
    s32 dy;
    s32 abs_val;

    dx = arg2 - arg0;
    if (dx > 0) {
        abs_val = dx;
    } else {
        abs_val = -dx;
    }
    if (abs_val < 0x2711) {
        dy = arg3 - arg1;
        if (dy > 0) {
            abs_val = dy;
        } else {
            abs_val = -dy;
        }
        if (abs_val < 0x2711) {
            dist = sqrtf((f32)((dx * dx) + (dy * dy)));
            if ((f64)dist != 0.0) {
                if (dx >= 0 && dy >= 0) {
                    angle = (s16)(func_80611E60((s32)(((f64)dx * 65535.9) / (f64)dist)) >> 4);
                }
                if (dx >= 0 && dy < 0) {
                    angle = (s16)((func_80611E60((s32)(((f64)(arg1 - arg3) * 65535.9) / (f64)dist)) >> 4) + 0x400);
                }
                if (dx < 0 && dy < 0) {
                    angle = (s16)((func_80611E60((s32)(((f64)(arg0 - arg2) * 65535.9) / (f64)dist)) >> 4) + 0x800);
                }
                if (dx < 0 && dy >= 0) {
                    angle = (s16)((func_80611E60((s32)(((f64)dy * 65535.9) / (f64)dist)) >> 4) + 0xC00);
                }
                func_806742C0(angle + 0x400, angle - 0x400, arg4, arg5);
            }
        }
    }
}
