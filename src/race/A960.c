#include "common.h"

typedef struct RaceGEnt {
    u16 count;
    u8 pad2[2];
    u8 *items;
    u16 active;
    u8 padA[2];
} RaceGEnt;
typedef struct RaceGEnt2 { u8 b[40]; } RaceGEnt2;
typedef struct RaceGTbl {
    u8 count;
    u8 pad1[3];
    RaceGEnt *items;
    u16 count2;
    u8 pad2[2];
    RaceGEnt2 *items2;
} RaceGTbl;
extern RaceGTbl *D_8002FCF0;

RaceGEnt *func_8002E960(u8 idx) {
    RaceGEnt *e = &D_8002FCF0->items[idx];

    if (D_8002FCF0 == NULL || idx >= D_8002FCF0->count) {
        return NULL;
    }
    e = &D_8002FCF0->items[idx];
    return e;
}

void *func_8002E9AC(u8 idx) {
    RaceGEnt2 *e = &D_8002FCF0->items2[idx];

    if (D_8002FCF0 == NULL || idx >= D_8002FCF0->count2) {
        return NULL;
    }
    e = &D_8002FCF0->items2[idx];
    return e;
}

void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_8002EDD4(u8 *);

void func_8002E9F8(s32 arg0) {
    u8 *src;
    RaceGEnt *ent;
    RaceGEnt2 *node;
    s32 i;
    s32 j;
    s32 m;
    s32 sz;

    if (arg0 != 0) {
        src = (u8 *)arg0;
        memcpy(D_8002FCF0, src, 1);
        src += 1;
        memcpy(&D_8002FCF0->count2, src, 2);
        src += 2;
        D_8002FCF0->items = func_80610FE8(D_8002FCF0->count * 12);
        heapClearBlock(D_8002FCF0->items);
        ent = D_8002FCF0->items;
        for (i = 0; i < D_8002FCF0->count; i++) {
            memcpy(ent, src, 2);
            src += 2;
            ent->items = func_80610FE8(ent->count * 2);
            sz = ent->count * 2;
            memcpy(ent->items, src, sz);
            src += sz;
            ent++;
        }
        D_8002FCF0->items2 = func_80610FE8(D_8002FCF0->count2 * 40);
        heapClearBlock(D_8002FCF0->items2);
        node = D_8002FCF0->items2;
        for (m = 0; m < D_8002FCF0->count2; m++) {
            memcpy(node, src, 0x1C);
            src += 0x1C;
            func_8002EDD4((u8 *)node);
            node++;
        }
        ent = D_8002FCF0->items;
        for (i = 0; i < D_8002FCF0->count; i++) {
            ent->active = 0;
            for (j = 0; j < ent->count; j++) {
                if (((u8 *)func_8002E9AC(ent->items[j * 2 + 1]))[0x10] != 0) {
                    ent->active++;
                }
            }
            ent++;
        }
    }
}

s32 func_8066B0F8(s32, s32, s32, s32);
void func_80025FDC(void);
void func_80029488(void);
void func_8002D0FC(void);
void func_8002D064(void);
extern s16 D_80750AC4;

void func_8002EC08(s32 arg0) {
    s32 sp1C;

    sp1C = func_8066B0F8(0x18, arg0, 1, 1);
    D_8002FCF0 = func_80610FE8(0x10);
    heapClearBlock(D_8002FCF0);
    func_8002E9F8(sp1C);
    switch (arg0) {
        case 0x1B:
            func_80025FDC();
            break;
        case 0x27:
            func_80029488();
            break;
        case 0xE:
        case 0x52:
            func_8002D0FC();
            break;
        case 0xB9:
            func_8002D064();
            break;
    }
    D_80750AC4 = 0;
}

void raceScaleVelocity(u8 *arg0, f32 arg1) {
    (*(f32 *)(*(u8 **)(arg0 + 4) + 0x34)) *= arg1;
    (*(f32 *)(*(u8 **)(arg0 + 4) + 0x38)) = *(f32 *)(*(u8 **)(arg0 + 4) + 0x34);
    (*(f32 *)(*(u8 **)(arg0 + 4) + 0x3C)) = *(f32 *)(*(u8 **)(arg0 + 4) + 0x38);
}

void actorSpawn(s32, s32);
void actorScriptStart(void *, s32);
extern void *D_807FBB44;

void func_8002ED04(f32 arg0, s32 arg1, u8 arg2) {
    s8 *sp1C;

    switch (arg1) {
        case 1:
            if (arg2 != 0) {
                actorSpawn(0x137, 0xB0);
                actorScriptStart(D_807FBB44, 0x2A9);
            } else {
                actorSpawn(0x137, 0xB1);
                actorScriptStart(D_807FBB44, 0x2AA);
            }
            break;
        case 2:
            actorSpawn(0x137, arg2 != 0 ? 0xD8 : 0xD9);
            break;
    }
    sp1C = *(s8 **)((u8 *)D_807FBB44 + 0x174);
    raceScaleVelocity(D_807FBB44, arg0);
    *sp1C = arg1;
}

void func_8002EDD4(u8 *arg0) {
    f32 mA[4][4];
    f32 mB[4][4];
    f32 pad[5];
    u32 j;
    f32 xoff;
    u8 i;

    if (arg0[0x10] != 0) {
        if (arg0[0x18] == 2) {
            xoff = (f32)*(u16 *)(arg0 + 0x1A) * 0.5f;
            for (i = 0; i < 2; i++) {
                func_8002ED04(*(f32 *)(arg0 + 0x14), arg0[0x10], i ^ 1);
                j = i;
                *(void **)(arg0 + j * 4 + 0x1C) = D_807FBB44;
                *(s16 *)((u8 *)D_807FBB44 + 0xE6) = (*(u16 *)(arg0 + 6) + 0x800) & 0xFFF;
                if (j != 0) {
                    xoff *= -1.0f;
                }
                guRotateF(mA, *(s16 *)((u8 *)D_807FBB44 + 0xE6) * 0.087890625f, 0.0f, 1.0f, 0.0f);
                guTranslateF(mB, *(s16 *)(arg0 + 0), *(s16 *)(arg0 + 2), *(s16 *)(arg0 + 4));
                guMtxCatF(mA, mB, mA);
                guMtxXFMF(mA, xoff, 0.0f, 0.0f, (f32 *)((u8 *)D_807FBB44 + 0x7C), (f32 *)((u8 *)D_807FBB44 + 0x80), (f32 *)((u8 *)D_807FBB44 + 0x84));
            }
        } else {
            func_8002ED04(*(f32 *)(arg0 + 0x14), arg0[0x10], arg0[0x18] == 1);
            *(void **)(arg0 + 0x1C) = D_807FBB44;
            *(s16 *)((u8 *)D_807FBB44 + 0xE6) = (*(u16 *)(arg0 + 6) + 0x800) & 0xFFF;
            *(f32 *)((u8 *)D_807FBB44 + 0x7C) = *(s16 *)(arg0 + 0);
            *(f32 *)((u8 *)D_807FBB44 + 0x80) = *(s16 *)(arg0 + 2);
            *(f32 *)((u8 *)D_807FBB44 + 0x84) = *(s16 *)(arg0 + 4);
        }
    }
}

f32 func_8002F04C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 r = 0.0f;
    f32 a = arg7 * arg2;
    f32 b = arg6 * arg3;

    if (a != b) {
        r = (((arg4 - arg0) * arg3) + (arg2 * (arg1 - arg5))) / (a - b);
    }
    return r;
}

extern void *D_807FBB40;

u8 func_8002F0AC(u8 *arg0) {
    f32 sp44;
    f32 sp40;
    f32 dx;
    f32 dz;
    f32 sp34;
    f32 sp30;
    f32 res;
    u8 sp2B;
    u8 *a;
    u8 *b;

    sp2B = 0;
    if (arg0[0x10] == 0) {
        return 1;
    }
    switch (arg0[0x18]) {
        case 2:
            a = *(u8 **)(arg0 + 0x20);
            b = *(u8 **)(arg0 + 0x1C);
            sp44 = *(f32 *)(a + 0x7C) - *(f32 *)(b + 0x7C);
            sp40 = *(f32 *)(a + 0x84) - *(f32 *)(b + 0x84);
            sp34 = *(f32 *)(b + 0x7C);
            sp30 = *(f32 *)(b + 0x84);
            break;
        case 0:
            sp44 = -*(f32 *)(arg0 + 0xC);
            sp40 = *(f32 *)(arg0 + 8);
            sp34 = *(s16 *)(arg0 + 0);
            sp30 = *(s16 *)(arg0 + 4);
            break;
        case 1:
            sp44 = *(f32 *)(arg0 + 0xC);
            sp40 = -*(f32 *)(arg0 + 8);
            sp34 = *(s16 *)(arg0 + 0);
            sp30 = *(s16 *)(arg0 + 4);
            break;
    }
    dx = *(f32 *)((u8 *)D_807FBB40 + 0x88) - *(f32 *)((u8 *)D_807FBB40 + 0x7C);
    dz = *(f32 *)((u8 *)D_807FBB40 + 0x90) - *(f32 *)((u8 *)D_807FBB40 + 0x84);
    res = func_8002F04C(*(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x84), dx, dz, sp34, sp30, sp44, sp40);
    switch (arg0[0x18]) {
        case 2:
            if (res > 0.0f && res < 1.0f) {
                sp2B = 1;
            }
            break;
        case 0:
        case 1:
            if (res > 0.0f) {
                sp2B = 1;
            }
            break;
    }
    return sp2B;
}

f32 func_80611BB4(f32, f32);
s32 mathAngleDistance(s16, s16);

s32 raceIsFacingWaypoint(u8 *arg0) {
    f32 diff_x = *(f32 *)((u8 *)D_807FBB40 + 0x7C) - (f32)*(s16 *)(arg0 + 0);
    f32 diff_z = *(f32 *)((u8 *)D_807FBB40 + 0x84) - (f32)*(s16 *)(arg0 + 4);
    s16 angle = (s32)(func_80611BB4(diff_x, diff_z) * 651.8986206f) & 0xFFF;

    return (mathAngleDistance(angle, *(s16 *)(arg0 + 6)) < 0x400) & 0xFF;
}

f32 func_8002F04C(f32, f32, f32, f32, f32, f32, f32, f32);

f32 func_8002F304(u8 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0 = *(f32 *)(arg0 + 0xC);
    f32 temp_fv1 = *(f32 *)(arg0 + 8);

    return func_8002F04C((f32)*(s16 *)(arg0 + 0), (f32)*(s16 *)(arg0 + 4), -temp_fv0, temp_fv1, arg1, arg2, temp_fv1, temp_fv0);
}

void *func_8002E9AC(u8);
void func_8002DCF0(void *, s32);

void func_8002F36C(u8 *arg0, u8 *arg1) {
    u8 *node;

    if (*(u16 *)(arg1 + 8) != 0) {
        do {
            u16 val;
            *(u16 *)(arg0 + 0x3C) += 1;
            *(u16 *)(arg0 + 0x3C) %= *(u16 *)(arg1 + 0);
            val = *(u16 *)(*(u16 *)(arg0 + 0x3C) * 2 + *(u8 **)(arg1 + 4));
            node = func_8002E9AC(val);
        } while (node[0x10] == 0);
        func_8002DCF0(node, 1);
    }
}

void func_8002F420(u8 *arg0, u8 *arg1) {
    if (*(u16 *)(arg1 + 8) != 0) {
        if (*(u16 *)(arg0 + 0x3A) == *(u16 *)(arg0 + 0x3C)) {
            u16 val = *(u16 *)(*(u16 *)(arg0 + 0x3C) * 2 + *(u8 **)(arg1 + 4));
            func_8002DCF0(func_8002E9AC(val), 0);
            func_8002F36C(arg0, arg1);
        }
    }
}

typedef struct RaceGVec3 {
    f32 x;
    f32 y;
    f32 z;
} RaceGVec3;

typedef struct RaceGPlayerPos {
    u8 pad0[0x210];
    RaceGVec3 pos;
    u8 pad21C[0xC];
    f32 f228;
    f32 f22C;
    f32 f230;
    u8 pad234[0x2F0 - 0x234];
} RaceGPlayerPos;

extern RaceGPlayerPos *D_807FC924;
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void func_8002F490(u8 *arg0) {
    u8 *actor;
    u8 *state;
    RaceGEnt *list;
    u8 *node;
    RaceGPlayerPos *pl;
    f32 sp38;
    RaceGPlayerPos *p;
    f32 fa0;
    f32 fa1;
    u8 pidx;
    s32 v;
    u16 val;

    actor = *(u8 **)(arg0 + 0x30);
    state = *(u8 **)(actor + 0x174);
    list = func_8002E960(state[0x26]);
    if (list != NULL) {
        val = ((u16 *)list->items)[*(u16 *)(arg0 + 0x3A)];
        node = func_8002E9AC(val);
        if (node != NULL) {
            fa0 = *(f32 *)((u8 *)D_807FBB40 + 0x7C);
            fa1 = *(f32 *)((u8 *)D_807FBB40 + 0x84);
            if (((f32)*(s16 *)(node + 4) - fa1) * ((f32)*(s16 *)(node + 4) - fa1) + ((f32)*(s16 *)(node + 0) - fa0) * ((f32)*(s16 *)(node + 0) - fa0) > 900.0f) {
                sp38 = mathAngleBetweenPointsDeg(*(s16 *)(node + 0), *(s16 *)(node + 4), (s32)fa0, (s32)fa1);
                pl = D_807FC924;
                pidx = arg0[0x28];
                p = pl;
                p += pidx;
                *(s16 *)((u8 *)D_807FBB40 + 0xEC) = (s32)(sp38 - mathAngleBetweenPointsDeg((s32)p->f228, (s32)p->f230, (s32)((f32 *)&p->pos)[pidx], (s32)pl->pos.z));
            }
            if (arg0[0x38] != 0) {
                arg0[0x38] = raceIsFacingWaypoint(node);
            } else if (raceIsFacingWaypoint(node) != 0) {
                if (arg0[0x27] == 0) {
                    if (node[0x10] != 0) {
                        if (func_8002F0AC(node) == 0) {
                            func_806086CC(*(s16 *)(node + 0), *(s16 *)(node + 2), *(s16 *)(node + 4), 0x98, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                            if (arg0[0x44] != 0) {
                                arg0[0x44]--;
                            } else {
                                arg0[0x45] = 1;
                            }
                        } else {
                            sfxAllocateChannel(0x43, 1.0f);
                        }
                    }
                    func_8002F420(arg0, (u8 *)list);
                }
                *(u16 *)(arg0 + 0x3A) += 1;
                *(u16 *)(arg0 + 0x3A) %= list->count;
                if (*(u16 *)(arg0 + 0x3A) == 0) {
                    (*(s8 *)(arg0 + 0x37))++;
                }
                val = ((u16 *)list->items)[*(u16 *)(arg0 + 0x3A)];
                node = func_8002E9AC(val);
                arg0[0x38] = raceIsFacingWaypoint(node);
            }
            *(f32 *)(arg0 + 0x40) = func_8002F304(node, *(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x84));
        }
    }
}

f32 func_8002F784(u16 *arg0, u8 *arg1, u8 *arg2) {
    s32 diff;
    f32 acc;
    f32 prevX;
    f32 prevZ;
    s32 first;
    s32 cur;
    s32 end;
    u8 *node;
    s32 idx;
    u16 val;

    cur = *(u16 *)(arg1 + 0x3A) + arg0[0] * *(s8 *)(arg1 + 0x37);
    end = *(u16 *)(arg2 + 0x3A) + arg0[0] * *(s8 *)(arg2 + 0x37);
    diff = end - cur;
    acc = *(f32 *)(arg1 + 0x40) - *(f32 *)(arg2 + 0x40);
    if (diff < 0) {
        cur ^= end;
        end ^= cur;
        cur ^= end;
        acc = -acc;
    }
    first = 1;
    if (cur != end) {
        if (cur <= end) {
            do {
                idx = cur % arg0[0];
                val = (*(u16 **)((u8 *)arg0 + 4))[idx];
                if (!cur && !cur) {
                }
                node = func_8002E9AC(val);
                if (first != 0) {
                } else {
                    acc += func_8002F304(node, prevX, prevZ);
                }
                first = 0;
                cur++;
                prevX = *(s16 *)(node + 0);
                prevZ = *(s16 *)(node + 4);
            } while (cur <= end);
        }
    }
    acc *= diff >= 0 ? 1 : -1;
    return acc;
}

typedef struct RaceGPA {
    u8 pad0[0x37];
    s8 lap;
    u8 pad38[2];
    u16 progress;
} RaceGPA;

f32 raceGetProgressPercent(u16 *arg0, RaceGPA *arg1, u8 *arg2) {
    u16 temp_v0 = *arg0;
    f32 num = (arg1->lap - 1) * temp_v0 + arg1->progress;
    f32 den = arg2[0x24] * temp_v0;

    return num / den;
}

typedef struct RaceGNode {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0xA];
    u8 active;
    u8 pad11[0xB];
    void *actors[2];
    s32 state;
} RaceGNode;

typedef struct RaceGList {
    u16 count;
    u8 pad2[2];
    u8 *items;
} RaceGList;

extern u8 D_807FC928;
void actorRegisterActive(void *);
void actorDeregisterActive(void *);

void func_8002F950(u8 *arg0) {
    RaceGList *list;
    RaceGNode *node;
    s32 i;
    s32 j;
    s32 k;
    s32 near;
    f32 dist;

    list = (RaceGList *)func_8002E960(arg0[0x26]);
    if (list != NULL) {
        for (i = 0; i < list->count; i++) {
            node = func_8002E9AC(list->items[i * 2 + 1]);
            if (node->active != 0) {
                near = 0;
                for (j = 0; j < D_807FC928; j++) {
                    RaceGVec3 *p = &D_807FC924[j].pos;
                    f32 dz = p->z - node->z;
                    f32 dx = p->x - node->x;
                    f32 dy = p->y - node->y;

                    dist = dz * dz + (dx * dx + dy * dy);
                    dz = 302500.0f;
                    near |= dist > dz;
                }
                if (near != node->state) {
                    for (k = 0; k < 2; k++) {
                        if (node->actors[k] != NULL) {
                            if (near != 0) {
                                actorDeregisterActive(node->actors[k]);
                            } else {
                                actorRegisterActive(node->actors[k]);
                            }
                        }
                    }
                    node->state = near;
                }
            }
        }
    }
}
