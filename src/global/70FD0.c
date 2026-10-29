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

void dynamicBufferPurgeExpired(void);
void func_8066C2D0(s32, s32, f32, f32, f32, f32, f32, f32, f32);
void collisionTransformNode(s32, s32, f32, f32, f32, f32, f32, f32, f32);
void dynamicBufferFree(DynamicBuffer *);
void collisionBufferCacheUpdate(void);
void collisionPurgeExpiredBuffers(void);
s32 collisionIsTriangleDegenerate(CollisionTri *);
s8 func_8066D2F4(s16 *);
s16 func_8066D4DC(s16 *, u8 *, f32 *);
void func_8066DD34(CollisionBox *);
void actorSub140Free(ActorSub140 *);
void actorSetNodeValue(Actor *, s32, u16);
void actorOrNodeFlags(Actor *, s32, u8);
void actorClearNodeFlags(Actor *, s32, u8);
void actorSub140Alloc(f32, f32, f32, f32, f32, f32, s32, s32, s32);
void actorFreeModelNodeList(Actor *);
void actorSetNodeFlag(Actor *, s32);
void actorClearNodeFlag(Actor *, s32);
void actorClearAllNodeFlags(Actor *);
ModelNode *func_8066EAEC(Actor *, s32);
ActorSub140 *func_8066EB40(Actor *, f32);
void actorSub140SetVectors(Actor *, f32, f32, f32, f32);
void actorUpdateModelMatrices(Actor *);
void func_8066EC6C(ActorSub140 *);
s32 collisionBuildBoxFromMatrix(f32 *, CollisionBox *);
void func_8066F06C(ActorSub140 *);
u8 actorSetTargetAngleAndCheck(s32, s16);
void actorClearTargetAngle(void);
u8 actorCheckTargetAngle();

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C2D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C610.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C7F4.s")

void collisionTransformNode(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_8066C2D0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

void dynamicBufferFree(DynamicBuffer *arg0) {
    if (arg0->unk18 != NULL && (arg0->unk15 & 1)) {
        heapFree(arg0->unk18);
    }
    arg0->unk15 &= ~1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066C958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CB88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066CCD8.s")

void collisionBufferCacheUpdate(void) {
    collisionPurgeExpiredBuffers();
    dynamicBufferPurgeExpired();
}

void collisionPurgeExpiredBuffers(void) {
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

s32 collisionIsTriangleDegenerate(CollisionTri *arg0) {
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

void actorSub140Free(ActorSub140 *arg0) {
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

void actorSetNodeValue(Actor *arg0, s32 arg1, u16 arg2) {
    ModelNode *temp_v0;

    temp_v0 = func_8066EAEC(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk24 = arg2;
    }
}

void actorOrNodeFlags(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *temp_v0;

    temp_v0 = func_8066EAEC(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk27 |= arg2;
    }
}

void actorClearNodeFlags(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *temp_v0;

    temp_v0 = func_8066EAEC(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk27 &= ~arg2;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E664.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066E6C8.s")

void actorSub140Alloc(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8) {
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

typedef struct ActorModelSubNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct ActorModelSubNode *next;
} ActorModelSubNode;

typedef struct ActorModelNode {
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
    /* 0x28 */ struct ActorModelNode *next;
} ActorModelNode;

void actorAppendModelSubNode(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 pad[3];
    ActorSub140 *sub;
    ActorModelSubNode *node;
    ActorModelSubNode **head;
    ActorModelSubNode *curr;

    sub = arg0->unk140;
    node = (ActorModelSubNode *)func_80610FE8(sizeof(ActorModelSubNode));
    node->next = NULL;
    head = (ActorModelSubNode **)&sub->unk90;
    node->unk0 = arg1;
    node->unk4 = arg2;
    node->unk8 = arg3;
    node->unk18 = arg4;
    node->unkC = 0;
    node->unk10 = 0;
    node->unk14 = 0;
    curr = (ActorModelSubNode *)sub->unk90;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}

void actorAppendModelNode(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 pad[3];
    ActorSub140 *sub;
    ActorModelNode *node;
    ActorModelNode **head;
    ActorModelNode *curr;

    sub = arg0->unk140;
    node = (ActorModelNode *)func_80610FE8(sizeof(ActorModelNode));
    node->next = NULL;
    head = (ActorModelNode **)&sub->unk8C;
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
    curr = (ActorModelNode *)sub->unk8C;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}

void actorFreeModelNodeList(Actor *arg0) {
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

f32 actorGetOrSetNodeScale(Actor *arg0, s32 arg1, f32 arg2) {
    ActorSub140 *sub = arg0->unk140;
    ModelNode *node;

    arg1--;
    node = sub->unk8C;
    while (arg1-- && node != NULL) {
        node = node->next;
    }
    if (node != NULL) {
        if (arg2 != -1.0f) {
            node->unkC = arg2;
        }
        return node->unkC;
    }
    return -1.0f;
}

void actorSetNodeFlag(Actor *arg0, s32 arg1) {
    ModelNode *node = func_8066EAEC(arg0, arg1);

    if (node != NULL) {
        node->unk26 = 1;
    }
}

void actorClearNodeFlag(Actor *arg0, s32 arg1) {
    ModelNode *node = func_8066EAEC(arg0, arg1);

    if (node != NULL) {
        node->unk26 = 0;
    }
}

void actorClearAllNodeFlags(Actor *arg0) {
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

void actorSub140SetVectors(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
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

void actorUpdateModelMatrices(Actor *arg0) {
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

s32 collisionBuildBoxFromMatrix(f32 *arg0, CollisionBox *arg1) {
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

    if (collisionIsTriangleDegenerate((CollisionTri *)sp20) != 0) {
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

u8 actorSetTargetAngleAndCheck(s32 arg0, s16 arg1) {
    s16 sp1E;
    s16 sp1C;
    s8 sp1B;

    D_807FB544 = arg1;
    D_807FB540 = arg0;
    D_807FB546 = 1;
    D_807FB604 = 1;
    actorCheckTargetAngle(arg0, &sp1E, &sp1C, &sp1B);
    return D_807FB546;
}

void actorClearTargetAngle(void) {
    D_807FB604 = 0;
    actorCheckTargetAngle();
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ActorSub140State;

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
} ActorSub174State;

typedef struct {
    s64 unk0;
    s64 unk8;
    s64 unk10;
    s64 unk18;
    u8 pad20[0x48 - 0x20];
    s16 unk48;
} CollisionPlane;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} CollisionVec3i;

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
    ActorSub140State *unk140;
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    ActorSub174State *unk174;
} CollisionActor;

typedef struct {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} KongPlayerData;
extern KongPlayerData *D_807FC924;
extern u8 D_807FB547;
extern u8 D_807FB602;
extern u8 D_807FB605;
extern u8 D_807FB606;

void func_80672E90(s32, s32, s32);
void actorSetCameraBoundaryMode(s32);
void func_80674E14(CollisionActor *);
s32 actorCheckTargetAngleBounds();
u8 func_8066F4AC(CollisionActor *, s16 *, s16 *);
s8 func_80676ED0(CollisionActor *, s16 *, s16 *);
void actorQueueCollisionCallbacks(CollisionActor *);
void actorQueueDelayedCallback();

u8 actorCheckTargetAngle(CollisionActor *arg0, s16 *arg1, s16 *arg2, s8 *arg3) {
    s32 pad;
    u8 sp23;
    u8 sp22;
    ActorSub140State *temp_v0;

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
    actorSetCameraBoundaryMode(arg0->unk58);
    D_807FB602 = 0;
    D_807FB547 = 0;
    D_807FB605 = 0;
    D_807FB606 = 0;
    if (arg0->unk144 & 0x20) {
        func_80674E14(arg0);
    }
    if (arg0->unk144 & 8) {
        sp23 = actorCheckTargetAngleBounds(arg0, arg1, arg2);
        sp22 = func_8066F4AC(arg0, arg1, arg2);
        *arg3 = func_80676ED0(arg0, arg1, arg2);
    } else {
        *arg3 = 0;
    }
    actorQueueCollisionCallbacks(arg0);
    arg0->unkFD = D_807FB547;
    if (D_807FB606 != 0) {
        arg0->unk64 |= 0x100;
    } else {
        arg0->unk64 &= ~0x100;
    }
    return (sp23 != 0) || (sp22 != 0);
}

void actorQueueCollisionCallbacks(CollisionActor *arg0) {
    if (D_807FB602) {
        if (arg0->unk5C & 1) {
            ActorSub174State *sub = arg0->unk174;
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

typedef struct Col7DHitInfo {
    u8 pad0[0x9B];
    u8 unk9B;
} Col7DHitInfo;

typedef struct Col7DSlot {
    u8 pad0[0x7C];
    Col7DHitInfo *unk7C;
    u8 pad80[8];
    s16 unk88;
    u8 pad8A[0x90 - 0x8A];
} Col7DSlot;

typedef struct Col7DHitSub {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x26 - 0x10];
    s16 unk26;
    f32 unk28[3];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    s16 unk58;
    s8 unk5A;
    s32 unk5C;
    u8 pad60[4];
    s16 unk64;
    s16 unk66;
    u8 pad68[4];
    u8 unk6C;
} Col7DHitSub;

typedef struct Col7DHitActor {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x140 - 0x88];
    Col7DHitSub *unk140;
} Col7DHitActor;

extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern CollisionBox *D_807FB5D8;
extern Col7DSlot *D_807F6000;
s32 matrix4Invert(f32 (*)[4], f32 (*)[4]); // FAKE: non-void return flips the $v0/$v1 pick in func_8066F84C
void func_8066C610(s16, s8, f32 [4][4]);
void func_8066FE08();
struct ActorFacingWork;
s32 func_806744A8(struct ActorFacingWork *, s32, s32, s32, s32);
void actorReflectCollisionAngle(CollisionActor *, CollisionPlane *, CollisionVec3i *);
s32 actorGetCollisionThreshold(CollisionActor *);

void func_8066F84C(arg0, arg1, arg2)
s32 arg0;
Col7DHitActor *arg1;
CollisionBox *arg2;
{
    Col7DHitSub *sub;
    f32 pad[7];
    f32 mtx[4][4];
    f32 mtxC[4][4];
    f32 inv[4][4];
    s32 off;
    s32 hit;
    u8 ok;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 px;
    f32 py;
    f32 pz;
    s32 i;

    sub = arg1->unk140;
    hit = 0;
    ok = func_806744A8((struct ActorFacingWork *)D_807FB5D8, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
    func_8066FE08(arg0);
    if (ok != 0) {
        sub->unk5A = D_807FB5D8->unk4E;
        sub->unk58 = D_807FB5D8 - arg2;
        func_8066C610(arg0, D_807FB5D8->unk4E, mtx);
        matrix4Invert(inv, mtx);
        off = arg0 * 0x90;
        if (D_807F6000[arg0].unk7C != NULL && (D_807F6000[arg0].unk7C->unk9B & 0x24)) {
            hit = 1;
        }
        if (hit != 0) {
            px = arg1->unk7C;
            py = arg1->unk80;
            pz = arg1->unk84;
        } else {
            px = (f32)D_807FB5C4 / 8;
            py = (f32)D_807FB5C8 / 8;
            pz = (f32)D_807FB5CC / 8;
        }
        if (!(arg1->unk60 & 0x800)) {
            guMtxXFMF(inv, px, py, pz, &sub->unk4C, &sub->unk50, &sub->unk54);
        }
        x[0] = (f32)D_807FB5D8->unk24 / 8;
        y[0] = (f32)D_807FB5D8->unk28 / 8;
        z[0] = (f32)D_807FB5D8->unk2C / 8;
        x[1] = (f32)D_807FB5D8->unk30 / 8;
        y[1] = (f32)D_807FB5D8->unk34 / 8;
        z[1] = (f32)D_807FB5D8->unk38 / 8;
        x[2] = (f32)D_807FB5D8->unk3C / 8;
        y[2] = (f32)D_807FB5D8->unk40 / 8;
        z[2] = (f32)D_807FB5D8->unk44 / 8;
        for (i = 0; i < 3; i++) {
            guMtxXFMF(inv, x[i], y[i], z[i], &sub->unk28[i], &sub->unk34[i], &sub->unk40[i]);
        }
        sub->unk26 = *(s16 *)((u8 *)D_807F6000 + off + 0x88);
        sub->unk5C = D_807FB5D0;
        if (sub->unk5C < 0x14) {
            sub->unk5C = 0x14;
        }
        sub->unk64 = actorGetCollisionThreshold((CollisionActor *)arg1);
        sub->unk66 = D_807FB5D8->unk48;
        if (D_807FB5D8->unk4C != 0) {
            sub->unk66 -= 0x800;
        }
        if (sub->unk66 < 0) {
            sub->unk66 += 0x1000;
        }
        sub->unk6C = 1;
        if (arg1->unk5C & 1) {
            actorReflectCollisionAngle((CollisionActor *)arg1, (CollisionPlane *)D_807FB5D8, (CollisionVec3i *)sub);
        }
    }
}

void actorReflectCollisionAngle(CollisionActor *arg0, CollisionPlane *arg1, CollisionVec3i *arg2) {
    ActorSub174State *sub = arg0->unk174;
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

s32 actorGetCollisionThreshold(CollisionActor *arg0) {
    switch (arg0->unk58) {
    case 5: {
        ActorSub174State *sub = arg0->unk174;
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

typedef struct Col7DPlane {
    u8 pad0[0x28];
    f32 unk28[3];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    u8 pad58[2];
    s8 unk5A;
} Col7DPlane;

typedef struct Col7DSub174 {
    u8 pad0[0xE0];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
} Col7DSub174;

typedef struct Col7DWork {
    u8 pad0[0x174];
    Col7DSub174 *unk174;
} Col7DWork;

extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern u8 D_807FC929;
extern s16 D_807FD584;

void func_80670C5C(Col7DWork *arg0, s16 arg1, Col7DPlane *arg2) {
    f32 mtx[4][4];
    f32 spCC;
    f32 spC8;
    f32 spC4;
    s32 i;
    f32 spB4[3];
    f32 spA8[3];
    f32 sp9C[3];
    f32 normal[3];
    f32 v1[3];
    f32 v2[3];
    f32 inv_len;
    f32 norm[3];
    f32 out[3];
    Col7DSub174 *sub;
    f32 sp54;
    f32 scale;

    sub = arg0->unk174;
    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        sp54 = D_80753D50[D_807FD584];
    } else {
        sp54 = D_80753D60[D_807FD584];
    }

    func_8066C610(arg1, arg2->unk5A, mtx);
    guMtxXFMF(mtx, arg2->unk4C, arg2->unk50, arg2->unk54, &spCC, &spC8, &spC4);

    for (i = 0; i < 3; i++) {
        guMtxXFMF(mtx, arg2->unk28[i], arg2->unk34[i], arg2->unk40[i], &spB4[i], &spA8[i], &sp9C[i]);
    }

    v1[0] = spB4[2] - spB4[0];
    v1[1] = spA8[2] - spA8[0];
    v1[2] = sp9C[2] - sp9C[0];

    v2[0] = spB4[1] - spB4[0];
    v2[1] = spA8[1] - spA8[0];
    v2[2] = sp9C[1] - sp9C[0];

    normal[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    normal[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    normal[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    inv_len = 1.0f / sqrtf((normal[0] * normal[0]) + (normal[1] * normal[1]) + (normal[2] * normal[2]));
    norm[0] = normal[0] * inv_len;
    norm[1] = normal[1] * inv_len;
    norm[2] = normal[2] * inv_len;

    scale = sp54 / 8;
    out[0] = norm[0] * scale;
    out[1] = norm[1] * scale;
    out[2] = norm[2] * scale;

    sub->unkE0 = spCC - out[0];
    sub->unkE4 = spC4 - out[2];
    sub->unkE8 = 1;
}

typedef struct {
    u8 pad0[0x48];
    s16 unk48;
} ActorTargetBounds;

extern s16 D_807FB5EC;
extern s16 D_807FB5EE;
extern s16 D_807FB5F0;
extern s16 D_807FB5F2;

void actorSetTargetAngleBounds(ActorTargetBounds *arg0) {
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

typedef struct ActorTargetSub174 {
    u8 pad[0x1A4];
    u8 unk1A4;
} ActorTargetSub174;

typedef struct ActorTargetNode8C {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
    struct ActorTargetNode8C *next;
} ActorTargetNode8C;

typedef struct ActorTargetNode {
    f32 x;
    f32 y;
    f32 z;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u32 unk18;
    struct ActorTargetNode *next;
} ActorTargetNode;

typedef struct ActorTargetSub140 {
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
    ActorTargetNode8C *unk8C;
    ActorTargetNode *unk90;
} ActorTargetSub140;

typedef struct ActorTargetWork {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x64 - 0x5C];
    u32 unk64;
    u8 pad68[0x140 - 0x68];
    ActorTargetSub140 *unk140;
    u8 pad144[0x174 - 0x144];
    ActorTargetSub174 *unk174;
} ActorTargetWork;

extern u8 D_807FB548;
extern u8 D_807FB61C;

s32 func_806730A4(s32, s32, s32, s32);
void func_80671880();
s32 func_806734E4();
void actorUpdateCollisionExtents(ActorTargetWork *);
s32 actorGetPlayerThreshold(ActorTargetWork *);
s32 actorCheckTargetAngleBounds(ActorTargetWork *arg0, s32 arg1, s32 arg2) {
    s32 pad0;
    s32 pad1;
    ActorTargetSub140 *sub = arg0->unk140;
    ActorTargetNode8C *node;
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
            actorUpdateCollisionExtents(arg0);
        }
        D_807FB605 = 0;
    }
    return ret;
}

typedef struct PlayerContext {
    u8 pad0[0xEA];
    s16 unkEA;
} PlayerContext;

typedef struct ActorFacingSub174 {
    u8 pad0[0xE0];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
    u8 padE9[0x1A4 - 0xE9];
    u8 unk1A4;
} ActorFacingSub174;

typedef struct ActorFacingWork {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[0x58 - 0x4A];
    s32 unk58;
    u16 unk5C;
    u8 pad5E[0x64 - 0x5E];
    u32 unk64;
    u8 pad68[0x140 - 0x68];
    ActorTargetSub140 *unk140;
    u8 pad144[0x174 - 0x144];
    ActorFacingSub174 *unk174;
} ActorFacingWork;

extern PlayerContext *D_807FD580;
extern s32 D_807FB5DC;
extern s16 D_807FB5F6;

s32 mathAngleDistance(s16, s16);
s32 func_806744A8(ActorFacingWork *, s32, s32, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_806732A8(s32, s16);
void actorUpdateSubActorOffsets(ActorTargetWork *, u8);
void func_80671528(ActorTargetWork *, f32 *, f32 *, f32 *, s32);

void actorUpdateFacingAndOffset(ActorFacingWork *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp36;
    s32 sp30;
    s32 pad2C;
    s32 sp28;
    s32 temp;
    ActorTargetSub140 *sub;
    f32 temp_f0;
    s32 temp_v1;

    sp36 = mathAngleDistance(arg0->unk48, D_807FB544);
    temp = mathAngleDistance((s16)((arg0->unk48 + 0x800) & 0xFFF), D_807FB544);
    if ((sp36 < 0x321) || (temp < 0x321)) {
        mathAngleDistance(arg0->unk48, D_807FD580->unkEA);
        mathAngleDistance((s16)((arg0->unk48 + 0x800) & 0xFFF), D_807FD580->unkEA);
        sub = ((ActorFacingWork *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
        sp28 = D_807FB5D0;
        sp30 = (s32)(func_80612794(D_807FB544) * 20.0f);
        temp_f0 = func_80612790(D_807FB544);
        sub = ((ActorFacingWork *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0 + sp30, sub->unk4, sub->unk8 + (s32)(temp_f0 * 20.0f), sub->unkC);
        temp_v1 = D_807FB5D0;
        if (sp28 - 2 < temp_v1) {
            D_807FB546 = 0;
        }
    }
}

void actorUpdateCollisionExtents(ActorTargetWork *arg0) {
    s32 pad4C;
    ActorFacingSub174 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        sp44 = D_80753D50[D_807FD584];
    } else {
        sp44 = D_80753D60[D_807FD584];
    }
    if (((ActorFacingWork *)arg0)->unk5C & 1) {
        f32 scale;
        f32 temp_c4;
        f32 temp_cc;

        sp48 = ((ActorFacingWork *)arg0)->unk174;
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
        actorReflectCollisionAngle((CollisionActor *)arg0, (CollisionPlane *)func_806732A8(D_807FB5DC, D_807FB5F6), (CollisionVec3i *)arg0->unk140);
    }
    actorUpdateSubActorOffsets(arg0, 1);
}

void actorUpdateSubActorOffsets(ActorTargetWork *arg0, u8 arg1) {
    if (D_807FB5D0 < actorGetPlayerThreshold(arg0)) {
        ActorTargetSub140 *sub = arg0->unk140;
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
            scale = (f32)actorGetPlayerThreshold(arg0) / (f32)8;
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

#ifdef NON_MATCHING
typedef struct Col7DPlaneActor {
    u8 pad0[0x60];
    u32 unk60;
} Col7DPlaneActor;

typedef struct Col7DPlaneSub {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xB0 - 0x10];
    s32 unkB0;
    s32 unkB4;
} Col7DPlaneSub;

extern CollisionBox *D_807FB5D4;

void func_80671528(arg0, arg1, arg2, arg3, arg4)
ActorTargetWork *arg0;
f32 *arg1;
f32 *arg2;
f32 *arg3;
volatile u8 arg4; // FAKE: reload arg4 from its stack home after the calls
{
    CollisionBox *box;
    f32 padA;
    Col7DPlaneSub *sub;
    f32 v1[3];
    f32 v2[3];
    f32 n[3];
    f32 padB;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 inv_len;

    sub = (Col7DPlaneSub *)arg0->unk140;
    if (arg4 != 0) {
        box = (CollisionBox *)func_806732A8(D_807FB5DC, D_807FB5F6);
    } else {
        box = D_807FB5D4;
    }
    x[0] = (f32)box->unk24 / 8;
    y[0] = (f32)box->unk28 / 8;
    z[0] = (f32)box->unk2C / 8;
    x[1] = (f32)box->unk30 / 8;
    y[1] = (f32)box->unk34 / 8;
    z[1] = (f32)box->unk38 / 8;
    x[2] = (f32)box->unk3C / 8;
    y[2] = (f32)box->unk40 / 8;
    z[2] = (f32)box->unk44 / 8;

    v1[0] = x[2] - x[0];
    v1[1] = y[2] - y[0];
    v1[2] = z[2] - z[0];

    v2[0] = x[1] - x[0];
    v2[1] = y[1] - y[0];
    v2[2] = z[1] - z[0];

    n[0] = (v1[1] * v2[2]) - (v2[1] * v1[2]);
    n[1] = (v1[2] * v2[0]) - (v2[2] * v1[0]);
    n[2] = (v1[0] * v2[1]) - (v2[0] * v1[1]);

    inv_len = 1.0f / sqrtf((n[2] * n[2]) + ((n[0] * n[0]) + (n[1] * n[1])));
    *arg1 = n[0] * inv_len;
    *arg2 = n[1] * inv_len;
    *arg3 = n[2] * inv_len;

    func_806744A8((ActorFacingWork *)box, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
    if (arg4 != 0) {
        if (((Col7DPlaneActor *)arg0)->unk60 & 0x800) {
            D_807FB5C4 = sub->unkB0;
            D_807FB5CC = sub->unkB4;
        }
        sub->unkB0 = D_807FB5C4;
        sub->unkB4 = D_807FB5CC;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671528.s")
#endif

s32 actorGetPlayerThreshold(ActorTargetWork *arg0) {
    ActorTargetSub174 *sub;

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

s32 actorGetNodePos(ActorTargetWork *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    ActorTargetSub140 *sub;
    ActorTargetNode *node;
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
void actorGetSubNodePos(ActorTargetWork *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 count = arg1 - 1;
    ActorTargetNode *node = arg0->unk140->unk90;

    while (node != NULL && count != 0) {
        count--;
        node = node->next;
    }
    *arg2 = node->x;
    *arg3 = node->y;
    *arg4 = node->z;
}

extern u8 D_807444FC;
s32 actorStepSubNodeList(ActorTargetWork *arg0, s32 arg1) {
    ActorTargetSub140 *sub = arg0->unk140;
    u8 val;
    s32 base;
    ActorTargetNode *node;

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

s16 func_80672A70();

s16 func_80672134(arg0, arg1, arg2, arg3)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s16 var_a3;
    f32 var_fv1;
    s16 bisect;
    s16 diff1;
    s16 diff2;

    if (arg1 >= arg0) {
        if (arg2 >= arg0 && arg1 >= arg2) {
            return 0x270F;
        }
    } else if (arg2 >= arg0 || arg1 >= arg2) {
        return 0x270F;
    }

    var_a3 = arg2 + 0x800;
    if (var_a3 >= 0x1000) {
        var_a3 -= 0x1000;
    }

    bisect = func_80672A70(arg0, arg1);
    if ((arg0 - bisect) > 0) {
        diff1 = arg0 - bisect;
    } else {
        diff1 = -(arg0 - bisect);
    }
    if (diff1 >= 0x800) {
        diff1 = 0xFFF - diff1;
    }
    if ((var_a3 - bisect) > 0) {
        diff2 = var_a3 - bisect;
    } else {
        diff2 = -(var_a3 - bisect);
    }
    if (diff2 >= 0x800) {
        diff2 = 0xFFF - diff2;
    }

    if (diff1 != 0) {
        var_fv1 = (f32)diff2 / (f32)diff1;
    } else {
        var_fv1 = 0.0f;
    }

    if (var_fv1 > 1.0) {
        var_fv1 = 1.0f;
    }
    if (var_fv1 < 0.2) {
        var_fv1 = 0.0f;
    }
    return (s16)(s32)((f32)arg3 * var_fv1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672328.s")

typedef struct ActorMotionSub140 {
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
} ActorMotionSub140;

typedef struct ActorMotionSub174 {
    u8 pad0[0x1A3];
    u8 unk1A3;
    u8 pad1A4[0x1C];
    f32 unk1C0;
    u8 pad1C4[8];
    f32 unk1CC;
} ActorMotionSub174;

typedef struct ActorMotionWork {
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
    ActorMotionSub140 *unk140;
    u8 unk144;
    u8 pad145[0x2F];
    ActorMotionSub174 *unk174;
} ActorMotionWork;

void func_80672680();

void func_806725A0(arg0, arg1)
ActorMotionWork *arg0;
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
ActorMotionWork *arg0;
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



void actorTouchSub140Timestamp(ActorMotionWork *arg0) {
    ActorMotionSub140 *temp_v0 = arg0->unk140;
    if (temp_v0 != NULL) {
        temp_v0->unk88 = D_8076A064;
    }
}

s32 func_80670548(void);
s32 func_80672328(ActorMotionWork *, f32, f32);

void actorUpdateMovementFlags(ActorMotionWork *arg0) {
    ActorMotionSub140 *temp_v0;

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

u8 actorHasActiveMovementFlags(ActorMotionWork *arg0) {
    return arg0->unk110 != 0
        || arg0->unk140->unk6C != 0
        || arg0->unk140->unk24 != 0
        || (arg0->unk6A & 8) != 0
        || (arg0->unk6A & 0x400) != 0;
}

void actorClearMovementFlags(ActorMotionWork *arg0) {
    ActorMotionSub140 *temp_v0;

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

void actorSetCameraBoundaryMode(s32 arg0) {
    D_807FB53C = arg0;
    if (arg0 != 0 && arg0 != 0xBC) {
        D_807FB5F8 = 2;
        D_807FB5FA = 10;
    } else {
        D_807FB5F8 = 100;
        D_807FB5FA = 100;
    }
}

extern ActorMotionWork *D_807FBB4C;

s32 actorCheckCameraBoundaryCondition(s8 arg0) {
    ActorMotionSub174 *temp_v0;

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

static void actorBoundaryStub(void) {
}
s32 func_806119A0(void);

s32 actorRng(void) {
    return func_806119A0();
}
