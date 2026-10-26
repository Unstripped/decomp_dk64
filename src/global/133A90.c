#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB48;
extern void *D_807FC924;

typedef struct H1ProxSub {
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
} H1ProxSub; // size = 0x1C

typedef struct H1ProxNode {
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
    /* 0x34 */ H1ProxSub *unk34;
    /* 0x38 */ struct H1ProxNode *next;
} H1ProxNode; // size = 0x3C

extern H1ProxNode *D_807FDCC0;
void *func_80610FE8(s32);
void heapFree(void *);

void func_8072ED90(void) {
    D_807FDCC0 = NULL;
}

void func_8072ED9C(Actor *arg0, u8 arg1, u8 arg2) {
    H1ProxNode *node;
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
    H1ProxNode *node;
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

void func_8072EE7C(Actor *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, u8 argB, f32 argC, f32 argD, u8 argE) {
    H1ProxNode **tail;
    H1ProxNode *node;

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

void func_8072EF7C(Actor *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, f32 arg6, f32 arg7, u8 arg8, s16 arg9, s16 argA, s16 argB, s16 argC) {
    H1ProxNode *node;
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

void func_8072F09C(Actor *arg0) {
    H1ProxNode **prev;
    H1ProxNode *node;
    H1ProxNode *next;

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

typedef struct H1Player {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} H1Player; // size = 0x2F0

extern u8 D_807FC928;
extern u32 D_807FBB64;
s32 func_8073110C(s32, s32);
s32 func_807142D8(void);
void func_8072F230(Actor *, u8, u8);

void func_8072F120(void) {
    u8 i;

    for (i = 0; i < D_807FC928; i++) {
        if (((H1Player *)D_807FC924)[i].unk0 != 0) {
            func_8072F230(((H1Player *)D_807FC924)[i].unk4, i, func_8073110C(0x183, 0) || (D_807FBB64 & 0x10000000) || D_807FC928 >= 2 || func_807142D8());
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
    /* 0x13C */ u8 pad13C[0x60];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ u8 pad1A0[4];
    /* 0x1A4 */ u8 unk1A4;
} H1ActorState;

f32 sqrtf(f32);
u8 func_8072F4A8(Actor *, u8, f32 *, f32 *, f32 *);
s32 func_8072F59C(Actor *, H1ProxNode *, f32 *, u8 *);
f32 func_8072FA14(Actor *, H1ActorState *, H1ProxNode *, u8);
void func_8072FCC4(H1ProxNode *, u8, f32, f32 *);
void playerStateQueueCallback(s32, void *, s32);

void func_8072F230(Actor *arg0, u8 arg1, u8 arg2) {
    f32 dx;
    f32 x;
    f32 y;
    f32 z;
    H1ProxNode *node;
    H1ProxNode *best;
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
        got = func_8072F4A8(node->unk0, node->unk4, &x, &y, &z);
        dx = arg0->unk7C - x;
        dy = arg0->unk80 - y;
                dz = arg0->unk84 - z;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (dist < node->unk1C && node->unk31 != 0) {
            if (node->unk6 == 1 || (arg2 != 0 && (node->unk0->unk60 & 0x04000000))) {
                if (got == 0 || !(u8)isPlayer) {
                    if (func_8072F59C(arg0, node, &d, &sub)) {
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
        func_8072FCC4(best, bestSub, func_8072FA14(arg0, state, best, bestSub), &out);
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
    /* 0x0C */ u8 padC[0x18];
    /* 0x24 */ u32 *unk24;
    /* 0x28 */ u8 pad28[0x68];
} H1SlotEntry; // size = 0x90

extern H1SlotEntry *D_807F6000;
s32 hashTableLookup();

u8 func_8072F4A8(Actor *arg0, u8 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072F59C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072F8D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072FA14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072FCC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072FDD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_8072FE60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_807300BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_80730408.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_80730AEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_80730D60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/133A90/func_80730E18.s")
