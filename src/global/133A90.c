#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB48;
extern void *D_807FC924;

typedef struct ProxPathSegment {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} ProxPathSegment; // size = 0x1C

typedef struct ProxPath {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 pad32[2];
    /* 0x34 */ ProxPathSegment *unk34;
    /* 0x38 */ struct ProxPath *next;
} ProxPath; // size = 0x3C

extern ProxPath *D_807FDCC0;
void *func_80610FE8(s32);
void heapFree(void *);

void proxPathListClear(void) {
    D_807FDCC0 = NULL;
}

void proxPathSetEnabled(Actor *arg0, u8 arg1, u8 arg2) {
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == arg0 && node->unk5 == arg1) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->unk31 = arg2;
    }
}

void func_8072EE0C(Actor *arg0, u8 arg1, u8 arg2) {
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == arg0 && node->unk5 == arg1) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->unk18 = arg2;
    }
}

void proxPathAdd(Actor *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, u8 argB, f32 argC, f32 argD, u8 argE) {
    ProxPath **tail;
    ProxPath *node;

    tail = &D_807FDCC0;
    node = D_807FDCC0;
    while (node != NULL) {
        tail = &node->next;
        node = node->next;
    }
    node = *tail = func_80610FE8(0x3C);
    node->unk0 = arg0;
    node->unk4 = arg1;
    node->unk5 = arg2;
    node->unk6 = arg3;
    node->unk7 = arg4;
    node->unk8 = arg5;
    node->unkC = arg6;
    node->unk14 = arg7;
    node->unk1C = arg8;
    node->unk20 = arg9;
    node->unk24 = argA;
    node->unk18 = argB;
    node->unk28 = argC;
    node->unk2C = argD;
    node->unk30 = argE;
    node->unk31 = 1;
    node->next = NULL;
    node->unk34 = func_80610FE8(arg4 * 0x1C);
}

void proxPathSetSegment(Actor *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, f32 arg6, f32 arg7, u8 arg8, s16 arg9, s16 argA, s16 argB, s16 argC) {
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == arg0 && node->unk5 == arg1) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->unk34[arg2].unk0 = arg3;
        node->unk34[arg2].unk1 = arg4;
        node->unk34[arg2].unk4 = arg5;
        node->unk34[arg2].unk8 = arg6;
        node->unk34[arg2].unkC = arg7;
        node->unk34[arg2].unk18 = arg8;
        node->unk34[arg2].unk10 = arg9;
        node->unk34[arg2].unk14 = argA;
        node->unk34[arg2].unk12 = argB;
        node->unk34[arg2].unk16 = argC;
    }
}

void proxPathRemoveActor(Actor *arg0) {
    ProxPath **prev;
    ProxPath *node;
    ProxPath *next;

    prev = &D_807FDCC0;
    node = *prev;
    while (node != NULL) {
        if (node->unk0 == arg0) {
            *prev = node->next;
            next = node->next;
            heapFree(node);
            node = next;
        } else {
            prev = &node->next;
            node = node->next;
        }
    }
}

typedef struct PlayerSlot {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} PlayerSlot; // size = 0x2F0

extern u8 D_807FC928;
extern u32 D_807FBB64;
s32 flagGet(s32, s32);
s32 func_807142D8(void);
void proxPathAttachNearestToPlayer(Actor *, u8, u8);

void proxPathUpdateAllPlayers(void) {
    u8 i;

    for (i = 0; i < D_807FC928; i++) {
        if (((PlayerSlot *)D_807FC924)[i].unk0 != 0) {
            proxPathAttachNearestToPlayer(((PlayerSlot *)D_807FC924)[i].unk4, i, flagGet(0x183, 0) || (D_807FBB64 & 0x10000000) || D_807FC928 >= 2 || func_807142D8());
        }
    }
}

typedef struct H1PlayerBlock {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F0 - 0x2C1];
} H1PlayerBlock; // size = 0x2F0

typedef struct H1ActorState {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ Actor *unk130;
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ f32 unk13C;
    /* 0x140 */ f32 unk140;
    /* 0x144 */ f32 unk144;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ u8 pad14C[0x10];
    /* 0x15C */ u8 unk15C[0x40];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ u8 pad1A0[4];
    /* 0x1A4 */ u8 unk1A4;
} H1ActorState;

f32 sqrtf(f32);
u8 proxPathGetActorPosition(Actor *, u8, f32 *, f32 *, f32 *);
s32 proxPathFindNearestSegment(Actor *, ProxPath *, f32 *, u8 *);
f32 proxPathAttachToSegment(Actor *, H1ActorState *, ProxPath *, u8);
void proxPathGetDistanceAt(ProxPath *, u8, f32, f32 *);
void playerStateQueueCallback(s32, void *, s32);

void proxPathAttachNearestToPlayer(Actor *arg0, u8 arg1, u8 arg2) {
    f32 dx;
    f32 x;
    f32 y;
    f32 z;
    ProxPath *node;
    ProxPath *best;
    f32 d;
    f32 bestDist;
    s32 isPlayer;
    u8 bestSub;
    u8 sub;
    u8 got;
    f32 out;
    f32 dy;
    H1ActorState *state;
    f32 dz;
    f32 dist;

    state = arg0->unk174;
    isPlayer = arg0->unk58 == 6;
    node = D_807FDCC0;
    bestDist = 9999.0f;
    best = NULL;
    if (isPlayer) {
        isPlayer = ((H1PlayerBlock *)D_807FC924)[state->unk1A4].unk2C0 == 2;
    }
    while (node != NULL) {
        got = proxPathGetActorPosition(node->unk0, node->unk4, &x, &y, &z);
        dx = arg0->unk7C - x;
        dy = arg0->unk80 - y;
                dz = arg0->unk84 - z;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (dist < node->unk1C && node->unk31 != 0) {
            if (node->unk6 == 1 || (arg2 != 0 && (node->unk0->unk60 & 0x04000000))) {
                if (got == 0 || !(u8)isPlayer) {
                    if (proxPathFindNearestSegment(arg0, node, &d, &sub)) {
                        if (d < bestDist) {
                            bestDist = d;
                            best = node;
                            bestSub = sub;
                        }
                    }
                }
            }
        }
        node = node->next;
    }
    if (best != NULL) {
        proxPathGetDistanceAt(best, bestSub, proxPathAttachToSegment(arg0, state, best, bestSub), &out);
        state->unk138 = out;
        state->unk130 = best->unk0;
        state->unk134 = best->unk5;
        state->unk19C = 0;
        state->unk19E = 0xFFF;
        arg0->unkB8 = 0.0f;
        isPlayer = best->unk6;
        switch (isPlayer) {
        case 0:
            playerStateQueueCallback(0xC, NULL, arg1);
            break;
        case 1:
            playerStateQueueCallback(0xB, NULL, arg1);
            break;
        }
    }
}

typedef struct H1SlotEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u32 *unk24;
    /* 0x28 */ u8 pad28[0x5C];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[0xA];
} H1SlotEntry; // size = 0x90

extern H1SlotEntry *D_807F6000;
s32 hashTableLookup();

u8 proxPathGetActorPosition(Actor *arg0, u8 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s16 slot;
    u8 ret;

    ret = 0;
    switch (arg1) {
    case 0:
        *arg2 = arg0->unk7C;
        *arg3 = arg0->unk80;
        *arg4 = arg0->unk84;
        break;
    case 1:
    case 2:
        slot = hashTableLookup(arg0);
        *arg2 = D_807F6000[slot].unk0;
        *arg3 = D_807F6000[slot].unk4;
        *arg4 = D_807F6000[slot].unk8;
        if (*D_807F6000[slot].unk24 & 1) {
            ret = 1;
        }
        break;
    }
    return ret;
}

void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void modelSlotGetNodePos(void *, s32, s32, f32 *, f32 *, f32 *);
extern s16 D_807FD584;
extern s16 D_80753B74[];
s32 mathAngleDistance(s16, s16);
f32 func_80611BB4(f32, f32);
s32 func_8072F8D4(ProxPath *, s32, s16);

s32 proxPathFindNearestSegment(Actor *arg0, ProxPath *arg1, f32 *arg2, u8 *arg3) {
    s32 i;
    f32 bz;
    f32 by;
    f32 bx;
    f32 az;
    f32 ay;
    f32 ax;
    s32 ang;
    u8 ret;
    u8 idA;
    u8 idB;
    f32 best;
    f32 r2;
    f32 ox;
    f32 oy;
    f32 oz;

    ret = 0;
    best = 999999.0f;
    if (arg0->unk154 == 0x5A || arg0->unk154 == 0x58) {
        r2 = arg1->unk24 * arg1->unk24;
    } else {
        r2 = arg1->unk20 * arg1->unk20;
    }
    if (arg1->unk6 == 1) {
        r2 += D_80753B74[D_807FD584];
    }
    for (i = 0; i < arg1->unk7; i++) {
        if (arg1->unk34[i].unk18 == 0) {
            idA = arg1->unk34[i].unk0;
            idB = arg1->unk34[i].unk1;
            switch (arg1->unk4) {
            case 0:
                actorGetNodePos(arg1->unk0, idA, &ax, &ay, &az);
                actorGetNodePos(arg1->unk0, idB, &bx, &by, &bz);
                break;
            case 1:
            case 2:
                modelSlotGetNodePos(arg1->unk0, 1, idA, &ax, &ay, &az);
                modelSlotGetNodePos(arg1->unk0, 1, idB, &bx, &by, &bz);
                break;
            }
            func_8061F2B8(arg0->unk7C, arg0->unk80, arg0->unk84, ax, ay, az, bx, by, bz, &ox, &oy, &oz);
            *arg2 = (arg0->unk7C - ox) * (arg0->unk7C - ox) + (arg0->unk80 - oy) * (arg0->unk80 - oy) + (arg0->unk84 - oz) * (arg0->unk84 - oz);
            if (*arg2 < r2 && *arg2 < best) {
                ang = func_80611BB4(ox - arg0->unk7C, oz - arg0->unk84) * 4096.0 / 6.2831855f;
                if (mathAngleDistance(ang, arg0->unkE6) < 0x2BC) {
                    if (func_8072F8D4(arg1, i, arg0->unkE6)) {
                        best = *arg2;
                        ret = 1;
                        *arg3 = i;
                    }
                }
            }
        }
    }
    *arg2 = sqrtf(best);
    return ret;
}

s32 func_806725E4(s16, s16, s16, s32);

s32 func_8072F8D4(ProxPath *arg0, s32 arg1, s16 arg2) {
    s16 slot;
    s32 delta;

    if (arg0->unk4 == 0) {
        return 1;
    }
    slot = hashTableLookup(arg0->unk0);
    if (!(D_807F6000[slot].unk84 == 0xC9 || D_807F6000[slot].unk84 == 0xCA || D_807F6000[slot].unk84 == 0x1CB || D_807F6000[slot].unk84 == 0x1F7 || D_807F6000[slot].unk84 == 0x1F8)) {
        return 1;
    }
    delta = D_807F6000[slot].unk14 * 4096.0f / 360.0f;
    if (func_806725E4((s16)((arg0->unk34[arg1].unk10 + delta) & 0xFFF), (s16)((arg0->unk34[arg1].unk14 + delta) & 0xFFF), arg2, 0)) {
        return 1;
    }
    return 0;
}

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void *memcpy(void *, const void *, unsigned int);

f32 proxPathAttachToSegment(Actor *arg0, H1ActorState *arg1, ProxPath *arg2, u8 arg3) {
    u8 idA;
    u8 idB;
    f32 bz;
    f32 by;
    f32 bx;
    f32 az;
    f32 ay;
    f32 ax;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 t;
    f32 px;
    f32 py;
    f32 pz;

    idA = arg2->unk34[arg3].unk0;
    idB = arg2->unk34[arg3].unk1;
    switch (arg2->unk4) {
    case 0:
        actorGetNodePos(arg2->unk0, idA, &ax, &ay, &az);
        actorGetNodePos(arg2->unk0, idB, &bx, &by, &bz);
        break;
    case 1:
    case 2:
        modelSlotGetNodePos(arg2->unk0, 1, idA, &ax, &ay, &az);
        modelSlotGetNodePos(arg2->unk0, 1, idB, &bx, &by, &bz);
        break;
    }
    actorGetNodePos(arg0, 1, &px, &py, &pz);
    func_8061F2B8(px, py, pz, ax, ay, az, bx, by, bz, &ox, &oy, &oz);
    t = (oy - ay) / (by - ay);
    if (arg2->unk18 == 2 || arg2->unk18 == 3) {
        if (arg3 == 0) {
            if (t < 0.05) {
                t = 0.05f;
            }
        }
    }
    if (arg2->unk18 == 1 || arg2->unk18 == 3) {
        if (arg3 + 1 == arg2->unk7) {
            if (t > 0.95) {
                t = 0.95f;
            }
        }
    }
    arg1->unk13C = arg0->unk7C;
    arg1->unk140 = arg0->unk80;
    arg1->unk144 = arg0->unk84;
    arg1->unk148 = 0.0f;
    memcpy(arg1->unk15C, (u8 *)arg0 + 0xC, 0x40);
    arg0->unkE6 = mathAngleBetweenPointsRad(ox, oz, arg0->unk7C, arg0->unk84) * 57.29577637f / 360.0 * 4095.0;
    return t;
}

void proxPathGetDistanceAt(ProxPath *arg0, u8 arg1, f32 arg2, f32 *arg3) {
    s32 i;

    *arg3 = 0.0f;
    for (i = 0; i < arg1; i++) {
        *arg3 = *arg3 + arg0->unk34[i].unk4;
    }
    *arg3 = *arg3 + arg0->unk34[arg1].unk4 * arg2;
}

#ifdef NON_MATCHING
void func_8072FDD4(ProxPath *arg0, f32 arg1, u8 *arg2, f32 *arg3) {
    u8 i;
    f32 rem;
    f32 prev;

    rem = arg1;
    i = 0;
    do {
        prev = rem;
        rem -= arg0->unk34[i++].unk4;
    } while (rem > 0.0 && i < arg0->unk7);
    i--;
    *arg2 = i;
    *arg3 = prev / arg0->unk34[i].unk4;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072FDD4.s")
#endif

typedef struct H1CamState {
    /* 0x000 */ u8 pad0[0x124];
    /* 0x124 */ f32 unk124;
    /* 0x128 */ f32 unk128;
    /* 0x12C */ u8 unk12C;
    /* 0x12D */ u8 pad12D[3];
    /* 0x130 */ Actor *unk130;
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ u8 pad13C[0x68];
    /* 0x1A4 */ u8 unk1A4;
} H1CamState;

typedef struct H1ActorView {
    /* 0x00 */ u8 pad0[0x6A];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x7A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
} H1ActorView;

#define H1BB48 ((H1ActorView *)D_807FBB48)

extern H1CamState *D_807FD580;
extern u32 D_80744478;
void func_806CFF9C(Actor *);

void proxPathAdvance(f32 arg0) {
    f32 step;
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == D_807FD580->unk130 && node->unk5 == D_807FD580->unk134) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || node->unk31 == 0) {
        H1BB48->unk6A &= ~0x40;
        return;
    }
    D_807FD580->unk124 = node->unk28;
    D_807FD580->unk128 = node->unk2C;
    D_807FD580->unk12C = node->unk30;
    step = D_80744478 * 0.5;
    D_807FD580->unk138 = D_807FD580->unk138 + node->unk14 * step * arg0;
    H1BB48->unk6A &= ~0x80;
    if (node->unkC < D_807FD580->unk138) {
        if (node->unk18 == 1 || node->unk18 == 3) {
            H1BB48->unkEE = H1BB48->unkE6;
            playerStateQueueCallback(0xD, NULL, D_807FD580->unk1A4);
        }
        D_807FD580->unk138 = node->unkC;
    }
    if (D_807FD580->unk138 < node->unk8) {
        if (node->unk18 == 2 || node->unk18 == 3) {
            H1BB48->unkEE = H1BB48->unkE6;
            func_806CFF9C(D_807FBB48);
        }
        D_807FD580->unk138 = node->unk8;
    }
    if (node->unkC <= D_807FD580->unk138 || D_807FD580->unk138 <= node->unk8) {
        H1BB48->unk6A |= 0x80;
    }
}

#ifdef NON_MATCHING
typedef struct H1ActorB {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xC];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[8];
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x8A];
    /* 0x174 */ H1ActorState *unk174;
} H1ActorB;

void func_8072FDD4(ProxPath *, f32, u8 *, f32 *);
void proxPathGetSegmentMatrices(Actor *, u8, u8, u8, void **, void **);
void mtxLerpL(Mtx *, Mtx *, f32, Mtx *);
void func_80730408(H1ActorB *, H1ActorState *, ProxPath *, u8, f32);

void func_807300BC(H1ActorB **arg0) {
    H1ActorB *actor;
    H1ActorState *state;
    u8 idx;
    f32 t;
    ProxPath *node;
    void *p128;
    void *p124;
    s32 found;
    Mtx mtx;
    f32 mA[4][4];
    f32 m6[4][4];
    u8 idA;
    u8 idB;
    s32 nodeId;
    f32 dx;
    f32 x;
    f32 y;
    f32 z;
    f32 dz;
    f32 dy;
    f32 dist;
    f32 ang;

    actor = *arg0;
    node = D_807FDCC0;
    state = actor->unk174;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == state->unk130 && node->unk5 == state->unk134) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || (actor->unk64 & 0x2000)) {
        actor->unk6A &= ~0x40;
        return;
    }
    func_8072FDD4(node, state->unk138, &idx, &t);
    idA = node->unk34[idx].unk0;
    idB = node->unk34[idx].unk1;
    switch (node->unk6) {
    case 0:
        proxPathGetSegmentMatrices(node->unk0, node->unk4, idA, idB, &p128, &p124);
        mtxLerpL(p128, p124, 1.0 - t, &mtx);
        guRotateF(m6, (s16)(0, (actor->unkE6 - state->unk130->unkE6) & 0xFFF) / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
        guTranslateF(mA, 0.0f, state->unk138 + -80.0, 0.0f);
        guMtxCatF(m6, mA, mA);
        guMtxL2F(actor->unkC, &mtx);
        guMtxCatF(mA, actor->unkC, actor->unkC);
        actorGetNodePos(actor, 8, &actor->unk7C, &actor->unk80, &actor->unk84);
        state->unk19C = 0;
        state->unk19E = 0xFFF;
        if (D_807FBB40->unk6A & 0x40) {
            if (actor->unk58 != 2 && actor->unk58 != 5) {
                nodeId = 0xD;
            } else {
                nodeId = 0xF;
            }
            actorGetNodePos(actor, nodeId, &x, &y, &z);
            dy = y - actor->unk80;
            dx = x - actor->unk7C;
            dz = z - actor->unk84;
            dist = sqrtf(dx * dx + dz * dz);
            ang = func_80611BB4(dist, dy);
            actor->unkE8 = 0.0 - ang * 2048.0 / 3.1415927f;
        } else {
            actor->unkE8 = 0;
        }
        break;
    case 1:
        func_80730408(actor, state, node, idx, t);
        actorGetNodePos(actor, 1, &actor->unk7C, &actor->unk80, &actor->unk84);
        break;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_807300BC.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_80730408.s")

f32 splineEvalCubic(f64, f32, f32, f32, f32);

void proxPathInterpolatePosition(u8 arg0, f32 arg1, ProxPath *arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    u8 ids[4];
    f32 p[4][3];

    ids[0] = arg2->unk34[arg0 - 1 > 0 ? arg0 - 1 : 0].unk0;
    ids[1] = arg2->unk34[arg0].unk0;
    ids[2] = arg2->unk34[arg0].unk1;
    ids[3] = arg2->unk34[arg0 + 1 < arg2->unk7 - 1 ? arg0 + 1 : arg2->unk7 - 1].unk1;
    switch (arg2->unk4) {
    case 1:
    case 2:
        modelSlotGetNodePos(arg2->unk0, 1, ids[0], &p[0][0], &p[0][1], &p[0][2]);
        modelSlotGetNodePos(arg2->unk0, 1, ids[1], &p[1][0], &p[1][1], &p[1][2]);
        modelSlotGetNodePos(arg2->unk0, 1, ids[2], &p[2][0], &p[2][1], &p[2][2]);
        modelSlotGetNodePos(arg2->unk0, 1, ids[3], &p[3][0], &p[3][1], &p[3][2]);
        break;
    case 0:
        actorGetNodePos(arg2->unk0, ids[0], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(arg2->unk0, ids[1], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(arg2->unk0, ids[1], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(arg2->unk0, ids[2], &p[0][0], &p[0][1], &p[0][2]);
        break;
    }
    *arg3 = splineEvalCubic(arg1, p[0][0], p[1][0], p[2][0], p[3][0]);
    *arg4 = splineEvalCubic(arg1, p[0][1], p[1][1], p[2][1], p[3][1]);
    *arg5 = splineEvalCubic(arg1, p[0][2], p[1][2], p[2][2], p[3][2]);
}

s32 actorStepSubNodeList(void *, s32);
void *modelSlotGetNodeMatrix(Actor *, s32, s32);
void heapFreeDeferred(void *);

void proxPathGetSegmentMatrices(Actor *arg0, u8 arg1, u8 arg2, u8 arg3, void **arg4, void **arg5) {
    void *tmp;

    switch (arg1) {
    case 0:
        *arg4 = (void *)actorStepSubNodeList(arg0, arg2);
        *arg5 = (void *)actorStepSubNodeList(arg0, arg3);
        break;
    case 1:
    case 2:
        tmp = modelSlotGetNodeMatrix(arg0, 1, arg2);
        *arg4 = tmp;
        heapFreeDeferred(tmp);
        tmp = modelSlotGetNodeMatrix(arg0, 1, arg3);
        *arg5 = tmp;
        heapFreeDeferred(tmp);
        break;
    }
}

void mtxLerpL(Mtx *arg0, Mtx *arg1, f32 arg2, Mtx *arg3) {
    f32 m1[4][4];
    f32 m2[4][4];
    s32 i;
    s32 j;

    guMtxL2F(m1, arg0);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m1[i][j] = m1[i][j] * arg2;
        }
    }
    guMtxL2F(m2, arg1);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m2[i][j] = m2[i][j] * (1.0 - arg2);
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m1[i][j] += m2[i][j];
        }
    }
    guMtxF2L(m1, arg3);
}
