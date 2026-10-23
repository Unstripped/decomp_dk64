#include "common.h"
#include "actor.h"

typedef struct DynamicBuffer {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ void *unk18;
    /* 0x1C */ u8 pad1C[4];
} DynamicBuffer; // size = 0x20

typedef struct BufferCacheEntry {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0xC];
} BufferCacheEntry; // size = 0x18

typedef struct CollisionTri {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
} CollisionTri; // size = 0x12

typedef struct CollisionBox {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ s8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 pad52[0x58 - 0x52];
} CollisionBox; // size = 0x58

extern s32 D_8076A064;
extern BufferCacheEntry *D_807FB534;
extern s32 D_807FB538;
extern s32 D_807FB540;
extern s16 D_807FB544;
extern u8 D_807FB546;
extern u8 D_807FB549;
extern u8 D_807FB604;

void *func_80610FE8(s32);
void heapFree(void *);

void func_806687E0(void);
void func_8066C2D0(s32, s32, f32, f32, f32, f32, f32, f32, f32);
void func_8066C8B0(s32, s32, f32, f32, f32, f32, f32, f32, f32);
void func_8066C904(DynamicBuffer *);
void func_8066CDD0(void);
void func_8066CDF8(void);
s32 func_8066D250(CollisionTri *);
s8 func_8066D2F4(s16 *);
s16 func_8066D4DC(s16 *, u8 *, f32 *);
void func_8066DD34(CollisionBox *);
void func_8066E21C(ActorSub140 *);
void func_8066E5CC(Actor *, s32, u16);
void func_8066E5F8(Actor *, s32, u8);
void func_8066E62C(Actor *, s32, u8);
void func_8066E72C(f32, f32, f32, f32, f32, f32, s32, s32, s32);
void func_8066E990(Actor *);
void func_8066EA64(Actor *, s32);
void func_8066EA90(Actor *, s32);
void func_8066EABC(Actor *);
ModelNode *func_8066EAEC(Actor *, s32);
ActorSub140 *func_8066EB40(Actor *, f32);
void func_8066EB50(Actor *, f32, f32, f32, f32);
void func_8066EBF4(Actor *);
void func_8066EC6C(ActorSub140 *);
s32 func_8066EE50(f32 *, CollisionBox *);
void func_8066F06C(ActorSub140 *);
u8 func_8066F1F8(s32, s16);
void func_8066F250(void);
u8 func_8066F274();

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C2D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C610.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C7F4.s")

void func_8066C8B0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_8066C2D0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

void func_8066C904(DynamicBuffer *arg0) {
    if (arg0->unk18 != NULL && (arg0->unk15 & 1)) {
        heapFree(arg0->unk18);
    }
    arg0->unk15 &= ~1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CB88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CCD8.s")

void func_8066CDD0(void) {
    func_8066CDF8();
    func_806687E0();
}

void func_8066CDF8(void) {
    s32 i;

    for (i = 0; i < D_807FB538; i++) {
        if (D_807FB534[i].unk0 != NULL && (u32)(D_8076A064 - D_807FB534[i].unk8) >= 0x15) {
            if (D_807FB549 == 0) {
                heapFree(D_807FB534[i].unk4);
                D_807FB534[i].unk4 = NULL;
            }
            heapFree(D_807FB534[i].unk0);
            D_807FB534[i].unk0 = NULL;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CEE4.s")

s32 func_8066D250(CollisionTri *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = arg0->unk6;
    temp_v1 = arg0->unk0;
    if ((temp_v0 == temp_v1) && (arg0->unk2 == arg0->unk8) && (arg0->unk4 == arg0->unkA)) {
        return 1;
    }
    temp_a1 = arg0->unkC;
    if ((temp_v0 == temp_a1) && (arg0->unkE == arg0->unk8) && (arg0->unk10 == arg0->unkA)) {
        return 1;
    }
    if ((temp_a1 == temp_v1) && (arg0->unk2 == arg0->unkE) && (arg0->unk4 == arg0->unk10)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066D2F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066D4DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066DB40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066DD34.s")

void func_8066E21C(ActorSub140 *arg0) {
    void *temp;
    ModelNode *curr8C;
    ModelNode *next8C;
    ModelSubNode *curr90;
    ModelSubNode *next90;

    if (arg0 != NULL) {
        curr8C = arg0->unk8C;
        if (curr8C != NULL) {
            do {
                next8C = curr8C->next;
                heapFree(curr8C);
                curr8C = next8C;
            } while (next8C != NULL);
        }
        curr90 = arg0->unk90;
        if (curr90 != NULL) {
            do {
                next90 = curr90->next;
                heapFree(curr90);
                curr90 = next90;
            } while (next90 != NULL);
        }
        temp = arg0->unkA0;
        if (temp != NULL) {
            heapFree(temp);
        }
        temp = arg0->unk98;
        if (temp != NULL) {
            heapFree(temp);
        }
        heapFree(arg0);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E2C0.s")

void func_8066E5CC(Actor *arg0, s32 arg1, u16 arg2) {
    ModelNode *temp_v0;

    temp_v0 = func_8066EAEC(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk24 = arg2;
    }
}

void func_8066E5F8(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *temp_v0;

    temp_v0 = func_8066EAEC(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk27 |= arg2;
    }
}

void func_8066E62C(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *temp_v0;

    temp_v0 = func_8066EAEC(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk27 &= ~arg2;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E664.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E6C8.s")

void func_8066E72C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    ActorSub140 *temp_v0;

    temp_v0 = (ActorSub140 *)func_80610FE8(sizeof(ActorSub140));
    temp_v0->unk0 = (s32) (arg0 * 8.0f);
    temp_v0->unk4 = (s32) (arg1 * 8.0f);
    temp_v0->unk8 = (s32) (arg2 * 8.0f);
    temp_v0->unk14 = arg4;
    temp_v0->unk18 = arg5;
    temp_v0->unkC = (s32) (arg4 * arg3 * 8.0f);
    temp_v0->unk10 = (s32) (arg5 * arg3 * 8.0f);
    temp_v0->unk70 = arg6;
    temp_v0->unk74 = arg7;
    temp_v0->unk78 = arg8;
    temp_v0->unk7C = -1;
    temp_v0->unk80 = -2;
    temp_v0->unk84 = -1;
    temp_v0->unk88 = -1;
    temp_v0->unk60 = 0;
    temp_v0->unk6C = 0;
    temp_v0->unk24 = 0;
    temp_v0->unk8C = NULL;
    temp_v0->unk90 = NULL;
    temp_v0->unk94 = 0;
    temp_v0->unk98 = NULL;
    temp_v0->unk9C = 0;
    temp_v0->unkA0 = NULL;
    temp_v0->unkA4 = 0;
    temp_v0->unkA8 = 0;
    temp_v0->unkAC = 0;
}

typedef struct M70G_ModelSubNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct M70G_ModelSubNode *next;
} M70G_ModelSubNode;

typedef struct M70G_ModelNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct M70G_ModelNode *next;
} M70G_ModelNode;

void func_8066E854(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 pad[3];
    ActorSub140 *sub;
    M70G_ModelSubNode *node;
    M70G_ModelSubNode **head;
    M70G_ModelSubNode *curr;

    sub = arg0->unk140;
    node = (M70G_ModelSubNode *)func_80610FE8(sizeof(M70G_ModelSubNode));
    node->next = NULL;
    head = (M70G_ModelSubNode **)&sub->unk90;
    node->unk0 = arg1;
    node->unk4 = arg2;
    node->unk8 = arg3;
    node->unk18 = arg4;
    node->unkC = 0;
    node->unk10 = 0;
    node->unk14 = 0;
    curr = (M70G_ModelSubNode *)sub->unk90;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}

void func_8066E8E4(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 pad[3];
    ActorSub140 *sub;
    M70G_ModelNode *node;
    M70G_ModelNode **head;
    M70G_ModelNode *curr;

    sub = arg0->unk140;
    node = (M70G_ModelNode *)func_80610FE8(sizeof(M70G_ModelNode));
    node->next = NULL;
    head = (M70G_ModelNode **)&sub->unk8C;
    node->unk0 = arg1;
    node->unk4 = arg2;
    node->unk8 = arg3;
    node->unkC = arg4;
    node->unk20 = arg5;
    node->unk10 = 0;
    node->unk14 = 0;
    node->unk18 = 0;
    node->unk1C = 0;
    node->unk26 = 1;
    node->unk24 = 0;
    node->unk27 = 0;
    curr = (M70G_ModelNode *)sub->unk8C;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}

void func_8066E990(Actor *arg0) {
    ActorSub140 *sub;
    ModelNode *node;
    ModelNode *next;

    sub = arg0->unk140;
    if (sub != NULL) {
        node = sub->unk8C;
        if (node != NULL) {
            do {
                next = node->next;
                heapFree(node);
                node = next;
            } while (node != NULL);
        }
        sub->unk8C = NULL;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E9EC.s")

void func_8066EA64(Actor *arg0, s32 arg1) {
    ModelNode *node = func_8066EAEC(arg0, arg1);

    if (node != NULL) {
        node->unk26 = 1;
    }
}

void func_8066EA90(Actor *arg0, s32 arg1) {
    ModelNode *node = func_8066EAEC(arg0, arg1);

    if (node != NULL) {
        node->unk26 = 0;
    }
}

void func_8066EABC(Actor *arg0) {
    ActorSub140 *sub = arg0->unk140;
    ModelNode *node;

    if (sub != NULL) {
        node = sub->unk8C;
        if (node != NULL) {
            do {
                node->unk26 = 0;
                node = node->next;
            } while (node != NULL);
        }
    }
}

ModelNode *func_8066EAEC(Actor *arg0, s32 arg1) {
    ActorSub140 *sub;
    ModelNode *node;

    sub = arg0->unk140;
    arg1--;
    if (sub != NULL) {
        node = sub->unk8C;
        while (arg1 != 0 && node != NULL) {
            arg1--;
            node = node->next;
        }
        if (node != NULL) {
            return node;
        }
        return NULL;
    }
    return NULL;
}

ActorSub140 *func_8066EB40(Actor *arg0, f32 arg1) {
    ActorSub140 *sub = arg0->unk140;
    sub->unk14 = arg1;
    return sub;
}

void func_8066EB50(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    ActorSub140 *sub = arg0->unk140;

    if (arg0->unk64 & 0x800) {
        arg4 = *(f32 *)arg0->unk120;
    }
    sub->unk0 = (s32)(arg1 * 8.0f);
    sub->unk4 = (s32)(arg2 * 8.0f);
    sub->unk8 = (s32)(arg3 * 8.0f);
    sub->unkC = (s32)(sub->unk14 * arg4 * 8.0f);
    sub->unk10 = (s32)(sub->unk18 * arg4 * 8.0f);
}

void func_8066EBF4(Actor *arg0) {
    ActorSub140 *sub;
    s32 temp_v0;

    sub = arg0->unk140;
    if (sub != NULL) {
        temp_v0 = arg0->unk60;
        if (!(temp_v0 & 0x80000000) || !(temp_v0 & 0x10)) {
            func_8066EC6C(sub);
        }
        if (!(arg0->unk64 & 8) || !(arg0->unk60 & 0x10)) {
            func_8066F06C(arg0->unk140);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066EC6C.s")

s32 func_8066EE50(f32 *arg0, CollisionBox *arg1) {
    u8 sp34[4];
    s16 sp32;
    s16 sp20[9];

    sp20[0] = arg0[0];
    sp20[1] = arg0[3];
    sp20[2] = arg0[6];
    sp20[3] = arg0[1];
    sp20[4] = arg0[4];
    sp20[5] = arg0[7];
    sp20[6] = arg0[2];
    sp20[7] = arg0[5];
    sp20[8] = arg0[8];

    if (func_8066D250((CollisionTri *)sp20) != 0) {
        return 0;
    }

    arg1->unk24 = (s32)(arg0[0] * 8.0f);
    arg1->unk28 = (s32)(arg0[3] * 8.0f);
    arg1->unk2C = (s32)(arg0[6] * 8.0f);
    arg1->unk30 = (s32)(arg0[1] * 8.0f);
    arg1->unk34 = (s32)(arg0[4] * 8.0f);
    arg1->unk38 = (s32)(arg0[7] * 8.0f);
    arg1->unk3C = (s32)(arg0[2] * 8.0f);
    arg1->unk40 = (s32)(arg0[5] * 8.0f);
    arg1->unk44 = (s32)(arg0[8] * 8.0f);

    sp32 = func_8066D4DC(sp20, sp34, arg0);
    arg1->unk4B = func_8066D2F4(sp20);
    arg1->unk4D = 0;
    arg1->unk4F = 0;
    arg1->unk51 = 0;
    arg1->unk50 = 0xFF;
    arg1->unk48 = sp32;
    arg1->unk4C = sp34[0];
    func_8066DD34(arg1);
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F06C.s")

u8 func_8066F1F8(s32 arg0, s16 arg1) {
    s16 sp1E;
    s16 sp1C;
    s8 sp1B;

    D_807FB544 = arg1;
    D_807FB540 = arg0;
    D_807FB546 = 1;
    D_807FB604 = 1;
    func_8066F274(arg0, &sp1E, &sp1C, &sp1B);
    return D_807FB546;
}

void func_8066F250(void) {
    D_807FB604 = 0;
    func_8066F274();
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} M70D_ActorSub140;

typedef struct {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0xE0 - 0xD6];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
    u8 padE9[1];
    s16 unkEA;
    u8 padEC[0x1A4 - 0xEC];
    u8 unk1A4;
} M70D_ActorSub174;

typedef struct {
    s64 unk0;
    s64 unk8;
    s64 unk10;
    s64 unk18;
    u8 pad20[0x48 - 0x20];
    s16 unk48;
} M70D_PlaneFC0C;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} M70D_Vec3i;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u8 pad68[0xFD - 0x68];
    u8 unkFD;
    u8 padFE[0x140 - 0xFE];
    M70D_ActorSub140 *unk140;
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    M70D_ActorSub174 *unk174;
} M70D_Actor;

typedef struct {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} M70D_PlayerData;
extern M70D_PlayerData *D_807FC924;
extern u8 D_807FB547;
extern u8 D_807FB602;
extern u8 D_807FB605;
extern u8 D_807FB606;

void func_80672E90(s32, s32, s32);
void func_80672C70(s32);
void func_80674E14(M70D_Actor *);
s32 func_80670FA4();
u8 func_8066F4AC(M70D_Actor *, s16 *, s16 *);
s8 func_80676ED0(M70D_Actor *, s16 *, s16 *);
void func_8066F400(M70D_Actor *);
void actorQueueDelayedCallback();

u8 func_8066F274(M70D_Actor *arg0, s16 *arg1, s16 *arg2, s8 *arg3) {
    s32 pad;
    u8 sp23;
    u8 sp22;
    M70D_ActorSub140 *temp_v0;

    sp23 = 0;
    sp22 = 0;
    temp_v0 = arg0->unk140;
    if (arg0->unk60 & 0x10000) {
        *arg1 = 0;
        *arg2 = 0xFFF;
    }
    if ((temp_v0 == NULL) || !(arg0->unk60 & 0x10)) {
        *arg3 = 0;
        return 0;
    }
    func_80672E90(temp_v0->unk0, temp_v0->unk4, temp_v0->unk8);
    func_80672C70(arg0->unk58);
    D_807FB602 = 0;
    D_807FB547 = 0;
    D_807FB605 = 0;
    D_807FB606 = 0;
    if (arg0->unk144 & 0x20) {
        func_80674E14(arg0);
    }
    if (arg0->unk144 & 8) {
        sp23 = func_80670FA4(arg0, arg1, arg2);
        sp22 = func_8066F4AC(arg0, arg1, arg2);
        *arg3 = func_80676ED0(arg0, arg1, arg2);
    } else {
        *arg3 = 0;
    }
    func_8066F400(arg0);
    arg0->unkFD = D_807FB547;
    if (D_807FB606 != 0) {
        arg0->unk64 |= 0x100;
    } else {
        arg0->unk64 &= ~0x100;
    }
    return (sp23 != 0) || (sp22 != 0);
}

void func_8066F400(M70D_Actor *arg0) {
    if (D_807FB602) {
        if (arg0->unk5C & 1) {
            M70D_ActorSub174 *sub = arg0->unk174;
            if (sub->unkD4 == 0) {
                if (D_807FB602 & 1) {
                    actorQueueDelayedCallback(arg0, 0, 8, 0, 0, 0, 1);
                }
                if (D_807FB602 & 2) {
                    actorQueueDelayedCallback(arg0, 0, 8, 0, 0, 0, 1);
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F84C.s")

void func_8066FC0C(M70D_Actor *arg0, M70D_PlaneFC0C *arg1, M70D_Vec3i *arg2) {
    M70D_ActorSub174 *sub = arg0->unk174;
    s64 total;
    s64 x_prod;
    s64 y_prod;
    sub->unkEA = arg1->unk48;
    y_prod = arg1->unk8 * arg2->y;
    x_prod = arg1->unk0 * arg2->x;
    total = (arg1->unk10 * arg2->z) + x_prod + y_prod + arg1->unk18;
    if (arg1->unk18 > 0) {
        if (total <= 0) {
            sub->unkEA += 0x800;
        }
    } else if (total >= 0) {
        sub->unkEA += 0x800;
    }
    sub->unkEA &= 0xFFF;
}

s32 func_8066FD6C(M70D_Actor *arg0) {
    switch (arg0->unk58) {
    case 5: {
        M70D_ActorSub174 *sub = arg0->unk174;
        if (D_807FC924[sub->unk1A4].unk2C0 == 1) {
            return 0x32;
        }
        return 0x14;
    }
    case 3:
        return 0x32;
    case 2:
        return 0x32;
    case 4:
        return 0x32;
    case 21:
        return 0x12C;
    default:
        return 0x32;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FE08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670C5C.s")

typedef struct {
    u8 pad0[0x48];
    s16 unk48;
} M70D_Target48;

extern s16 D_807FB5EC;
extern s16 D_807FB5EE;
extern s16 D_807FB5F0;
extern s16 D_807FB5F2;

void func_80670F04(M70D_Target48 *arg0) {
    s16 temp_v0;

    temp_v0 = arg0->unk48;
    D_807FB5EC = temp_v0 - 0x32;
    if (D_807FB5EC < 0) {
        D_807FB5EC += 0xFFF;
    }
    D_807FB5EE = temp_v0 + 0x32;
    if (D_807FB5EC >= 0x1000) {
        D_807FB5EE -= 0xFFF;
    }
    D_807FB5F0 = D_807FB5EC + 0x800;
    if (D_807FB5F0 >= 0x1000) {
        D_807FB5F0 -= 0xFFF;
    }
    D_807FB5F2 = D_807FB5EE + 0x800;
    if (D_807FB5F2 >= 0x1000) {
        D_807FB5F2 -= 0xFFF;
    }
}

typedef struct M70E_Sub174 {
    u8 pad[0x1A4];
    u8 unk1A4;
} M70E_Sub174;

typedef struct M70E_Node8C {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
    struct M70E_Node8C *next;
} M70E_Node8C;

typedef struct M70E_Node {
    f32 x;
    f32 y;
    f32 z;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u32 unk18;
    struct M70E_Node *next;
} M70E_Node;

typedef struct M70E_SubActor {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xC];
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[0x74 - 0x25];
    s32 unk74[2];
    u8 pad7C[0xC];
    s32 unk88;
    M70E_Node8C *unk8C;
    M70E_Node *unk90;
} M70E_SubActor;

typedef struct M70E_Actor {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x64 - 0x5C];
    u32 unk64;
    u8 pad68[0x140 - 0x68];
    M70E_SubActor *unk140;
    u8 pad144[0x174 - 0x144];
    M70E_Sub174 *unk174;
} M70E_Actor;

extern u8 D_807FB548;
extern u8 D_807FB61C;

s32 func_806730A4(s32, s32, s32, s32);
void func_80671880(M70E_Actor *, s32);
s32 func_806734E4();
void func_80671260(M70E_Actor *);
s32 func_806717FC(M70E_Actor *);
s32 func_80670FA4(M70E_Actor *arg0, s32 arg1, s32 arg2) {
    s32 pad0;
    s32 pad1;
    M70E_SubActor *sub = arg0->unk140;
    M70E_Node8C *node;
    u8 ret = 0;

    sub->unk24 = 0;
    D_807FB548 = 0;

    if (func_806730A4(sub->unk0, sub->unk4, sub->unk8, sub->unkC) != 0) {
        if (arg0->unk64 & 0x80) {
            D_807FB605 = 1;
        }
        func_80671880(arg0, 0);
        node = sub->unk8C;
        while (node != NULL) {
            if (node->unk26 != 0 && node->unk1C != 0 && !(node->unk27 & 1)) {
                ret |= func_806734E4(node->unk10, node->unk14, node->unk18, node->unk1C, arg1, arg2);
            }
            node = node->next;
        }
        if ((ret != 0 || D_807FB605 != 0) && D_807FB61C != 0) {
            func_80671260(arg0);
        }
        D_807FB605 = 0;
    }
    return ret;
}

typedef struct M70H_D580 {
    u8 pad0[0xEA];
    s16 unkEA;
} M70H_D580;

typedef struct M70H_Sub174 {
    u8 pad0[0xE0];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
    u8 padE9[0x1A4 - 0xE9];
    u8 unk1A4;
} M70H_Sub174;

typedef struct M70H_Actor {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[0x58 - 0x4A];
    s32 unk58;
    u16 unk5C;
    u8 pad5E[0x64 - 0x5E];
    u32 unk64;
    u8 pad68[0x140 - 0x68];
    M70E_SubActor *unk140;
    u8 pad144[0x174 - 0x144];
    M70H_Sub174 *unk174;
} M70H_Actor;

extern M70H_D580 *D_807FD580;
extern s32 D_807FB5D0;
extern s32 D_807FB5C4;
extern s32 D_807FB5CC;
extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern s16 D_807FD584;
extern u8 D_807FC929;
extern s32 D_807FB5DC;
extern s16 D_807FB5F6;

s32 func_806CC14C(s16, s16);
s32 func_806744A8(M70H_Actor *, s32, s32, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_806732A8(s32, s16);
void func_806713E4(M70E_Actor *, u8);
void func_80671528(M70E_Actor *, f32 *, f32 *, f32 *, s32);

void func_806710E0(M70H_Actor *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp36;
    s32 sp30;
    s32 pad2C;
    s32 sp28;
    s32 temp;
    M70E_SubActor *sub;
    f32 temp_f0;
    s32 temp_v1;

    sp36 = func_806CC14C(arg0->unk48, D_807FB544);
    temp = func_806CC14C((s16)((arg0->unk48 + 0x800) & 0xFFF), D_807FB544);
    if ((sp36 < 0x321) || (temp < 0x321)) {
        func_806CC14C(arg0->unk48, D_807FD580->unkEA);
        func_806CC14C((s16)((arg0->unk48 + 0x800) & 0xFFF), D_807FD580->unkEA);
        sub = ((M70H_Actor *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
        sp28 = D_807FB5D0;
        sp30 = (s32)(func_80612794(D_807FB544) * 20.0f);
        temp_f0 = func_80612790(D_807FB544);
        sub = ((M70H_Actor *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0 + sp30, sub->unk4, sub->unk8 + (s32)(temp_f0 * 20.0f), sub->unkC);
        temp_v1 = D_807FB5D0;
        if (sp28 - 2 < temp_v1) {
            D_807FB546 = 0;
        }
    }
}

void func_80671260(M70E_Actor *arg0) {
    s32 pad4C;
    M70H_Sub174 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        sp44 = D_80753D50[D_807FD584];
    } else {
        sp44 = D_80753D60[D_807FD584];
    }
    if (((M70H_Actor *)arg0)->unk5C & 1) {
        f32 scale;
        f32 temp_c4;
        f32 temp_cc;

        sp48 = ((M70H_Actor *)arg0)->unk174;
        func_80671528(arg0, &sp38, &sp3C, &sp40, 1);
        scale = sp44 / 8;
        temp_c4 = (f32)D_807FB5C4 / 8;
        temp_cc = (f32)D_807FB5CC / 8;
        sp38 *= scale;
        sp3C *= scale;
        sp40 *= scale;
        sp48->unkE0 = temp_c4 - sp38;
        sp48->unkE4 = temp_cc - sp40;
        sp48->unkE8 = 1;
        func_8066FC0C((M70D_Actor *)arg0, (M70D_PlaneFC0C *)func_806732A8(D_807FB5DC, D_807FB5F6), (M70D_Vec3i *)arg0->unk140);
    }
    func_806713E4(arg0, 1);
}

void func_806713E4(M70E_Actor *arg0, u8 arg1) {
    if (D_807FB5D0 < func_806717FC(arg0)) {
        M70E_SubActor *sub = arg0->unk140;
        f32 temp_fa0;
        f32 scale;
        f32 temp_fa1;
        f32 sp2C;
        f32 sp28;
        f32 sp24;

        func_80671528(arg0, &sp24, &sp28, &sp2C, arg1);
        temp_fa0 = (f32)D_807FB5C4 / (f32)8;
        temp_fa1 = (f32)D_807FB5CC / (f32)8;
        if (D_807FB548 != 0) {
            scale = (f32)func_806717FC(arg0) / (f32)8;
            sp24 *= scale;
            sp2C *= scale;
        } else {
            scale = (f32)(D_807FB5D0 + 6) / (f32)8;
            sp24 *= scale;
            sp2C *= scale;
        }
        sub->unk1C = temp_fa0 - sp24;
        sub->unk20 = temp_fa1 - sp2C;
        sub->unk24 = 1;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671528.s")

s32 func_806717FC(M70E_Actor *arg0) {
    M70E_Sub174 *sub;

    if (arg0->unk58 == 2) {
        goto ret_32_2;
    }
    if (arg0->unk58 == 3) {
        goto ret_32_1;
    }
    if (arg0->unk58 != 5) {
        goto ret_32_3;
    }
    sub = arg0->unk174;
    if (D_807FC924[sub->unk1A4].unk2C0 != 1) {
        return 0x14;
    }
    return 0x32;
ret_32_1:
    return 0x32;
ret_32_2:
    return 0x32;
ret_32_3:
    return 0x32;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671880.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671A6C.s")

s32 func_80671C0C(M70E_Actor *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    M70E_SubActor *sub;
    M70E_Node *node;
    s32 count;

    sub = arg0->unk140;
    if (sub != NULL) {
        func_80671A6C(sub, 1);
        node = arg0->unk140->unk90;
        count = arg1 - 1;
        while (node != NULL && count != 0) {
            count--;
            node = node->next;
        }
        if (node == NULL) {
            *arg4 = 0.0f;
            *arg3 = 0.0f;
            *arg2 = 0.0f;
            return 0;
        }
        *arg2 = (f32)node->unkC / (f32)8;
        *arg3 = (f32)node->unk10 / (f32)8;
        *arg4 = (f32)node->unk14 / (f32)8;
        return 1;
    }
    return 0;
}
void func_80671D10(M70E_Actor *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 count = arg1 - 1;
    M70E_Node *node = arg0->unk140->unk90;

    while (node != NULL && count != 0) {
        count--;
        node = node->next;
    }
    *arg2 = node->x;
    *arg3 = node->y;
    *arg4 = node->z;
}

extern u8 D_807444FC;
s32 func_80671D64(M70E_Actor *arg0, s32 arg1) {
    M70E_SubActor *sub = arg0->unk140;
    u8 val;
    s32 base;
    M70E_Node *node;

    if (D_8076A064 == sub->unk88) {
        val = D_807444FC;
    } else {
        val = D_807444FC ^ 1;
    }
    base = sub->unk74[val];

    node = sub->unk90;
    arg1--;
    while (arg1 != 0) {
        arg1--;
        node = node->next;
    }

    return (((u32)node->unk18 >> 6) << 6) + base;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671E00.s")
#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671F54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672328.s")

typedef struct M70F_ActorSub140 {
    u8 pad0[0x1C];
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[0x3B];
    s32 unk60;
    u8 pad64[8];
    u8 unk6C;
    u8 pad6D[0x1B];
    s32 unk88;
} M70F_ActorSub140;

typedef struct M70F_Actor174 {
    u8 pad0[0x1A3];
    u8 unk1A3;
    u8 pad1A4[0x1C];
    f32 unk1C0;
    u8 pad1C4[8];
    f32 unk1CC;
} M70F_Actor174;

typedef struct M70F_Actor {
    u8 pad0[0x60];
    u32 unk60;
    u32 unk64;
    u16 unk68;
    u16 unk6A;
    u8 pad6C[0x10];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
    u8 pad88[0x6C];
    s16 unkF4;
    s16 unkF6;
    u8 padF8[4];
    u8 unkFC;
    u8 padFD[0x13];
    u8 unk110;
    u8 pad111[0x2F];
    M70F_ActorSub140 *unk140;
    u8 unk144;
    u8 pad145[0x2F];
    M70F_Actor174 *unk174;
} M70F_Actor;

void func_80672680();

void func_806725A0(arg0, arg1)
M70F_Actor *arg0;
s16 arg1;
{
    s16 sp24[2];

    func_80672680(sp24[0], arg1, arg0->unkF4, arg0->unkF6, &sp24[1]);
}

s32 func_806726DC();

void func_806725E4(arg0, arg1, arg2, arg3)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s16 sp24[2];

    func_806726DC(sp24[0], arg2, arg0, arg1, &sp24[1], arg3);
}

void func_80672630(arg0, arg1, arg2)
M70F_Actor *arg0;
s16 arg1;
s16 arg2;
{
    s16 sp24[2];

    func_806726DC(sp24[0], arg1, arg0->unkF4, arg0->unkF6, &sp24[1], arg2);
}

void func_80672680(arg0, arg1, arg2, arg3, arg4)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 *arg4;
{
    func_806726DC(arg0, arg1, arg2, arg3, arg4, 10);
}

s16 func_806728F0(s16, s16, s16);

s32 func_806726DC(arg0, arg1, arg2, arg3, arg4, arg5)
s32 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 *arg4;
s16 arg5;
{
    s16 temp_t0;
    s16 temp_t1;
    s16 var_t2;
    s16 var_t3;
    u8 var_a0;

    temp_t0 = arg2 + arg5;
    temp_t1 = arg3 - arg5;
    var_t2 = temp_t0;
    var_t3 = temp_t1;
    if (arg3 >= arg2) {
        if (temp_t0 < temp_t1 && arg1 >= temp_t0 && temp_t1 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = func_806728F0(arg2, arg3, arg1);
        goto ret_0;
    }

    var_a0 = 0;
    if (temp_t0 >= 0x1000) {
        var_t2 = temp_t0 - 0x1000;
        var_a0 = 1;
    }
    if (temp_t1 < 0) {
        var_t3 = temp_t1 + 0x1000;
        var_a0 += 2;
    }

    switch (var_a0) {
    default:
        return 0;
    case 0:
        if (arg1 >= var_t2 || var_t3 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = func_806728F0(arg2, arg3, arg1);
        break;
    case 1:
    case 2:
        if (var_t2 < var_t3 && arg1 >= var_t2 && var_t3 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = func_806728F0(arg2, arg3, arg1);
        break;
    case 3:
        *arg4 = func_806728F0(arg2, arg3, arg1);
        break;
    }

ret_0:
    return 0;
}

s16 func_80672A70();

s16 func_806728F0(arg0, arg1, arg2)
s16 arg0;
s16 arg1;
s16 arg2;
{
    s32 temp_v0;
    s32 temp_v1;
    s16 var_a0;
    s16 var_a3;
    s16 var_t0;
    s16 var_v0;
    s16 var_v1;

    var_a3 = arg0 + 10;
    var_t0 = arg1 - 10;
    temp_v0 = arg0 - arg2;
    if (temp_v0 > 0) {
        var_a0 = temp_v0;
    } else {
        var_a0 = -temp_v0;
    }
    temp_v1 = arg1 - arg2;
    if (var_a0 >= 0x801) {
        var_a0 = 0xFFF - var_a0;
    }
    if (temp_v1 > 0) {
        var_v0 = temp_v1;
    } else {
        var_v0 = -temp_v1;
    }
    if (var_v0 >= 0x801) {
        var_v0 = 0xFFF - var_v0;
    }
    if (var_v0 >= var_a0) {
        if (var_a3 >= 0x1000) {
            var_a3 -= 0xFFF;
        }
        var_v1 = var_a3;
    } else {
        if (var_t0 < 0) {
            var_t0 += 0xFFF;
        }
        var_v1 = var_t0;
    }
    if (arg1 >= arg0) {
        if ((var_v1 < arg0) || (arg1 < var_v1)) {
            var_v1 = func_80672A70(arg0, arg1);
        }
    } else if ((var_v1 < arg0) && (arg1 < var_v1)) {
        var_v1 = func_80672A70(arg0, arg1);
    }
    return var_v1;
}

s16 func_80672A70(arg0, arg1)
s16 arg0;
s16 arg1;
{
    s16 temp_v0;
    s16 var_v1;

    if (arg1 >= arg0) {
        return (arg0 + arg1) >> 1;
    }
    temp_v0 = ((arg1 - arg0 + 0xFFF) / 2) + arg0;
    var_v1 = temp_v0;
    if (temp_v0 >= 0x1000) {
        var_v1 = temp_v0 - 0xFFF;
    }
    return var_v1;
}



void func_80672AFC(M70F_Actor *arg0) {
    M70F_ActorSub140 *temp_v0 = arg0->unk140;
    if (temp_v0 != NULL) {
        temp_v0->unk88 = D_8076A064;
    }
}

s32 func_80670548(void);
s32 func_80672328(M70F_Actor *, f32, f32);

void func_80672B1C(M70F_Actor *arg0) {
    M70F_ActorSub140 *temp_v0;

    if (arg0->unk144 & 8) {
        temp_v0 = arg0->unk140;
        if (temp_v0->unk6C != 0) {
            arg0->unkFC |= func_80670548();
        } else {
            temp_v0->unk60 = 0;
        }
        if (arg0->unk60 & 0x20) {
            temp_v0 = arg0->unk140;
            if (temp_v0->unk24 != 0 && func_80672328(arg0, temp_v0->unk1C, temp_v0->unk20) != 0) {
                temp_v0 = arg0->unk140;
                arg0->unk7C = temp_v0->unk1C;
                arg0->unk84 = temp_v0->unk20;
            }
        }
    } else {
        temp_v0 = arg0->unk140;
        if (temp_v0 != NULL) {
            temp_v0->unk6C = 0;
        }
    }
}

u8 func_80672BD4(M70F_Actor *arg0) {
    return arg0->unk110 != 0
        || arg0->unk140->unk6C != 0
        || arg0->unk140->unk24 != 0
        || (arg0->unk6A & 8) != 0
        || (arg0->unk6A & 0x400) != 0;
}

void func_80672C30(M70F_Actor *arg0) {
    M70F_ActorSub140 *temp_v0;

    temp_v0 = arg0->unk140;
    arg0->unk110 = 0;
    if (temp_v0 != NULL) {
        temp_v0->unk6C = 0;
        arg0->unk140->unk24 = 0;
    }
    arg0->unk6A &= ~8;
    *(u16*)((u8*)arg0 + 0x6A) &= ~0x400;
    arg0->unk64 |= 0x2000;
}

extern s32 D_807FB53C;
extern s16 D_807FB5F8;
extern s16 D_807FB5FA;

void func_80672C70(s32 arg0) {
    D_807FB53C = arg0;
    if (arg0 != 0 && arg0 != 0xBC) {
        D_807FB5F8 = 2;
        D_807FB5FA = 10;
    } else {
        D_807FB5F8 = 100;
        D_807FB5FA = 100;
    }
}

extern M70F_Actor *D_807FBB4C;

s32 func_80672CBC(s8 arg0) {
    M70F_Actor174 *temp_v0;

    switch (arg0) {
    case 0:
        if (D_807FB53C == 0xBC) {
            return 1;
        }
        goto ret_0;
    case 1:
        if (D_807FB53C != 0xBC) {
            return 1;
        }
        goto ret_0;
    case 2:
        if (D_807FB53C != 5 || D_807FC924->unk2C0 == 1) {
            return 1;
        }
        goto ret_0;
    case 3:
        if (D_807FB53C == 5 && D_807FC924->unk2C0 != 1) {
            return 1;
        }
        goto ret_0;
    case 4:
        if (D_807FB53C == 8) {
            return 1;
        }
        goto ret_0;
    case 5:
        D_807FB548 = 1;
        return 1;
    case 6:
        temp_v0 = D_807FBB4C->unk174;
        if (D_807FB53C == 3 && temp_v0->unk1A3 != 0) {
            return 1;
        }
        goto ret_0;
    case 7:
        temp_v0 = D_807FBB4C->unk174;
        if (D_807FB53C == 6 && (D_807FC924->unk2C0 != 1 || temp_v0->unk1CC != temp_v0->unk1C0)) {
            return 1;
        }
        goto ret_0;
    case 8:
        if (D_807FB53C == 9) {
            return 1;
        }
        goto ret_0;
    }
ret_0:
    return 0;
}

static void func_80672E64(void) {
}
s32 func_806119A0(void);

s32 func_80672E6C(void) {
    return func_806119A0();
}
