#include "common.h"

typedef struct RaceActorVel {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} RaceActorVel;

typedef struct RaceActorState {
    s8 unk0;
    u8 pad1[0x23];
    u8 unk24;
    u8 pad25;
    u8 route;
} RaceActorState;

typedef struct RaceActor {
    u8 pad0[4];
    RaceActorVel *unk4;
    u8 pad8[0x7C - 8];
    f32 x;
    f32 y;
    f32 z;
    f32 prevX;
    f32 prevY;
    f32 prevZ;
    u8 pad94[0xE6 - 0x94];
    s16 angle;
    u8 padE8[0xEC - 0xE8];
    s16 unkEC;
    u8 padEE[0x174 - 0xEE];
    RaceActorState *state;
} RaceActor;

typedef struct RaceWaypoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u16 angle;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 kind;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 mode;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ u16 width;
    /* 0x1C */ RaceActor *actors[2];
    /* 0x24 */ s32 state;
} RaceWaypoint;

typedef struct RaceRoute {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u16 *items;
    /* 0x08 */ u16 active;
    /* 0x0A */ u8 padA[2];
} RaceRoute;

typedef struct RaceRouteTable {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ RaceRoute *items;
    /* 0x08 */ u16 count2;
    /* 0x0A */ u8 pad2[2];
    /* 0x0C */ RaceWaypoint *items2;
} RaceRouteTable;

typedef struct RaceTracker {
    u8 pad0[0x27];
    u8 unk27;
    u8 playerIdx;
    u8 pad29[0x30 - 0x29];
    RaceActor *actor;
    u8 pad34[0x37 - 0x34];
    s8 lap;
    u8 unk38;
    u8 pad39;
    u16 unk3A;
    u16 unk3C;
    f32 unk40;
    u8 unk44;
    u8 unk45;
} RaceTracker;

typedef struct RacePlayerPos {
    u8 pad0[0x210];
    f32 pos[3];
    u8 pad21C[0xC];
    f32 f228;
    f32 f22C;
    f32 f230;
    u8 pad234[0x2F0 - 0x234];
} RacePlayerPos;

extern RaceRouteTable *D_8002FCF0;
extern RaceActor *D_807FBB40;
extern RaceActor *D_807FBB44;
extern RacePlayerPos *D_807FC924;
extern u8 D_807FC928;

RaceRoute *raceGetRoute(u8 idx) {
    RaceRoute *e = &D_8002FCF0->items[idx];

    if (D_8002FCF0 == NULL || idx >= D_8002FCF0->count) {
        return NULL;
    }
    e = &D_8002FCF0->items[idx];
    return e;
}

RaceWaypoint *raceGetWaypoint(u8 idx) {
    RaceWaypoint *e = &D_8002FCF0->items2[idx];

    if (D_8002FCF0 == NULL || idx >= D_8002FCF0->count2) {
        return NULL;
    }
    e = &D_8002FCF0->items2[idx];
    return e;
}

void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_8002EDD4(RaceWaypoint *);

void raceLoadRouteData(s32 arg0) {
    u8 *src;
    RaceRoute *ent;
    RaceWaypoint *node;
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
            func_8002EDD4(node);
            node++;
        }
        ent = D_8002FCF0->items;
        for (i = 0; i < D_8002FCF0->count; i++) {
            ent->active = 0;
            for (j = 0; j < ent->count; j++) {
                if (raceGetWaypoint(ent->items[j])->kind != 0) {
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
    raceLoadRouteData(sp1C);
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

void raceScaleVelocity(RaceActor *arg0, f32 arg1) {
    arg0->unk4->unk34 *= arg1;
    arg0->unk4->unk38 = arg0->unk4->unk34;
    arg0->unk4->unk3C = arg0->unk4->unk38;
}

void actorSpawn(s32, s32);
void actorScriptStart(void *, s32);

void func_8002ED04(f32 arg0, s32 arg1, u8 arg2) {
    RaceActorState *sp1C;

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
    sp1C = D_807FBB44->state;
    raceScaleVelocity(D_807FBB44, arg0);
    sp1C->unk0 = arg1;
}

void func_8002EDD4(RaceWaypoint *arg0) {
    f32 mA[4][4];
    f32 mB[4][4];
    f32 pad[5];
    u32 j;
    f32 xoff;
    u8 i;

    if (arg0->kind != 0) {
        if (arg0->mode == 2) {
            xoff = (f32)arg0->width * 0.5f;
            for (i = 0; i < 2; i++) {
                func_8002ED04(arg0->unk14, arg0->kind, i ^ 1);
                j = i;
                arg0->actors[j] = D_807FBB44;
                D_807FBB44->angle = (arg0->angle + 0x800) & 0xFFF;
                if (j != 0) {
                    xoff *= -1.0f;
                }
                guRotateF(mA, D_807FBB44->angle * 0.087890625f, 0.0f, 1.0f, 0.0f);
                guTranslateF(mB, arg0->x, arg0->y, arg0->z);
                guMtxCatF(mA, mB, mA);
                guMtxXFMF(mA, xoff, 0.0f, 0.0f, &D_807FBB44->x, &D_807FBB44->y, &D_807FBB44->z);
            }
        } else {
            func_8002ED04(arg0->unk14, arg0->kind, arg0->mode == 1);
            arg0->actors[0] = D_807FBB44;
            D_807FBB44->angle = (arg0->angle + 0x800) & 0xFFF;
            D_807FBB44->x = arg0->x;
            D_807FBB44->y = arg0->y;
            D_807FBB44->z = arg0->z;
        }
    }
}

f32 raceLineIntersectParam(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 r = 0.0f;
    f32 a = arg7 * arg2;
    f32 b = arg6 * arg3;

    if (a != b) {
        r = (((arg4 - arg0) * arg3) + (arg2 * (arg1 - arg5))) / (a - b);
    }
    return r;
}

u8 func_8002F0AC(RaceWaypoint *arg0) {
    f32 sp44;
    f32 sp40;
    f32 dx;
    f32 dz;
    f32 sp34;
    f32 sp30;
    f32 res;
    u8 sp2B;
    RaceActor *a;
    RaceActor *b;

    sp2B = 0;
    if (arg0->kind == 0) {
        return 1;
    }
    switch (arg0->mode) {
        case 2:
            a = arg0->actors[1];
            b = arg0->actors[0];
            sp44 = a->x - b->x;
            sp40 = a->z - b->z;
            sp34 = b->x;
            sp30 = b->z;
            break;
        case 0:
            sp44 = -arg0->unkC;
            sp40 = arg0->unk8;
            sp34 = arg0->x;
            sp30 = arg0->z;
            break;
        case 1:
            sp44 = arg0->unkC;
            sp40 = -arg0->unk8;
            sp34 = arg0->x;
            sp30 = arg0->z;
            break;
    }
    dx = D_807FBB40->prevX - D_807FBB40->x;
    dz = D_807FBB40->prevZ - D_807FBB40->z;
    res = raceLineIntersectParam(D_807FBB40->x, D_807FBB40->z, dx, dz, sp34, sp30, sp44, sp40);
    switch (arg0->mode) {
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

s32 raceIsFacingWaypoint(RaceWaypoint *arg0) {
    f32 diff_x = D_807FBB40->x - (f32)arg0->x;
    f32 diff_z = D_807FBB40->z - (f32)arg0->z;
    s16 angle = (s32)(func_80611BB4(diff_x, diff_z) * 651.8986206f) & 0xFFF;

    return (mathAngleDistance(angle, arg0->angle) < 0x400) & 0xFF;
}

f32 func_8002F304(RaceWaypoint *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0 = arg0->unkC;
    f32 temp_fv1 = arg0->unk8;

    return raceLineIntersectParam((f32)arg0->x, (f32)arg0->z, -temp_fv0, temp_fv1, arg1, arg2, temp_fv1, temp_fv0);
}

void func_8002DCF0(RaceWaypoint *, s32);

void func_8002F36C(RaceTracker *arg0, RaceRoute *arg1) {
    RaceWaypoint *node;

    if (arg1->active != 0) {
        do {
            u16 val;
            arg0->unk3C += 1;
            arg0->unk3C %= arg1->count;
            val = arg1->items[arg0->unk3C];
            node = raceGetWaypoint(val);
        } while (node->kind == 0);
        func_8002DCF0(node, 1);
    }
}

void func_8002F420(RaceTracker *arg0, RaceRoute *arg1) {
    if (arg1->active != 0) {
        if (arg0->unk3C == arg0->unk3A) {
            u16 val = arg1->items[arg0->unk3C];
            func_8002DCF0(raceGetWaypoint(val), 0);
            func_8002F36C(arg0, arg1);
        }
    }
}

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void func_8002F490(RaceTracker *arg0) {
    RaceActor *actor;
    RaceActorState *state;
    RaceRoute *list;
    RaceWaypoint *node;
    RacePlayerPos *pl;
    f32 sp38;
    RacePlayerPos *p;
    u8 pidx;
    u16 val;

    actor = arg0->actor;
    state = actor->state;
    list = raceGetRoute(state->route);
    if (list != NULL) {
        val = list->items[arg0->unk3A];
        node = raceGetWaypoint(val);
        if (node != NULL) {
            if (((f32)node->x - D_807FBB40->x) * ((f32)node->x - D_807FBB40->x) + ((f32)node->z - D_807FBB40->z) * ((f32)node->z - D_807FBB40->z) > 900.0f) {
                sp38 = mathAngleBetweenPointsDeg(node->x, node->z, (s32)D_807FBB40->x, (s32)D_807FBB40->z);
                pl = D_807FC924;
                pidx = arg0->playerIdx;
                p = pl;
                p += pidx;
                D_807FBB40->unkEC = (s32)(sp38 - mathAngleBetweenPointsDeg((s32)p->f228, (s32)p->f230, (s32)p->pos[pidx], (s32)pl->pos[2]));
            }
            if (arg0->unk38 != 0) {
                arg0->unk38 = raceIsFacingWaypoint(node);
            } else if (raceIsFacingWaypoint(node) != 0) {
                if (arg0->unk27 == 0) {
                    if (node->kind != 0) {
                        if (func_8002F0AC(node) == 0) {
                            func_806086CC(node->x, node->y, node->z, 0x98, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                            if (arg0->unk44 != 0) {
                                arg0->unk44--;
                            } else {
                                arg0->unk45 = 1;
                            }
                        } else {
                            sfxAllocateChannel(0x43, 1.0f);
                        }
                    }
                    func_8002F420(arg0, list);
                }
                arg0->unk3A += 1;
                arg0->unk3A %= list->count;
                if (arg0->unk3A == 0) {
                    arg0->lap++;
                }
                val = list->items[arg0->unk3A];
                node = raceGetWaypoint(val);
                arg0->unk38 = raceIsFacingWaypoint(node);
            }
            arg0->unk40 = func_8002F304(node, D_807FBB40->x, D_807FBB40->z);
        }
    }
}

f32 func_8002F784(RaceRoute *arg0, RaceTracker *arg1, RaceTracker *arg2) {
    s32 diff;
    f32 acc;
    f32 prevX;
    f32 prevZ;
    s32 first;
    s32 cur;
    s32 end;
    RaceWaypoint *node;
    s32 idx;
    u16 val;

    cur = arg1->lap * arg0->count + arg1->unk3A;
    end = arg2->lap * arg0->count + arg2->unk3A;
    diff = end - cur;
    acc = arg1->unk40 - arg2->unk40;
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
                idx = cur % arg0->count;
                val = arg0->items[idx];
                node = raceGetWaypoint(val);
                if (!first) {
                    acc += func_8002F304(node, prevX, prevZ);
                }
                first = 0;
                cur++;
                prevX = node->x;
                prevZ = node->z;
            } while (cur <= end);
        }
    }
    acc *= diff >= 0 ? 1 : -1;
    return acc;
}

f32 raceGetProgressPercent(RaceRoute *arg0, RaceTracker *arg1, RaceActorState *arg2) {
    u16 temp_v0 = arg0->count;
    f32 num = (arg1->lap - 1) * temp_v0 + arg1->unk3A;
    f32 den = arg2->unk24 * temp_v0;

    return num / den;
}

void actorRegisterActive(void *);
void actorDeregisterActive(void *);

void raceUpdateWaypointActivation(RaceActorState *arg0) {
    RaceRoute *list;
    RaceWaypoint *node;
    s32 i;
    s32 j;
    s32 k;
    s32 near;
    f32 dist;

    list = raceGetRoute(arg0->route);
    if (list != NULL) {
        for (i = 0; i < list->count; i++) {
            node = raceGetWaypoint(list->items[i]);
            if (node->kind != 0) {
                near = 0;
                for (j = 0; j < D_807FC928; j++) {
                    f32 *p = D_807FC924[j].pos;
                    f32 dz = p[2] - node->z;
                    f32 dx = p[0] - node->x;
                    f32 dy = p[1] - node->y;

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
