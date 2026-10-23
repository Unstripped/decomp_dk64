// func_8066D2F4 (src/global/70FD0.c): near miss: cross-product regalloc; 3-vector layout matches stack frame 0x48 exactly
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
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
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
s8 func_8066D2F4();
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
void func_8066F274();

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

f32 func_80611BB4(f32, f32);

s8 func_8066D2F4(CollisionTri *arg0) {
    f32 v2[3];
    f32 v1[3];
    f32 cross[3];
    f32 len;
    f32 angle;
    f32 temp;
    s32 ret;

    v2[0] = arg0->unkC - arg0->unk0;
    v2[1] = arg0->unkE - arg0->unk2;
    v2[2] = arg0->unk10 - arg0->unk4;
    v1[0] = arg0->unk6 - arg0->unk0;
    v1[1] = arg0->unk8 - arg0->unk2;
    v1[2] = arg0->unkA - arg0->unk4;
    cross[0] = (v2[1] * v1[2]) - (v1[1] * v2[2]);
    cross[1] = (v2[2] * v1[0]) - (v1[2] * v2[0]);
    cross[2] = (v2[0] * v1[1]) - (v1[0] * v2[1]);

    len = sqrtf((cross[2] * cross[2]) + (cross[0] * cross[0]));
    if (((f64)len < 0.01) && ((f64)len > -0.01)) {
        angle = 1.57f;
    } else {
        temp = -cross[1];
        if (0.0f < cross[1]) {
            temp = cross[1];
        }
        angle = func_80611BB4(temp, len);
    }

    if ((f64)(f32)((f64)angle * 57.29577791868205) < 10.0) {
        return 1;
    }
    ret = 0;
    if ((f64)(f32)((f64)angle * 57.29577791868205) < 45.0) {
        ret = 2;
    }
    return ret;
}

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F274.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F400.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066F84C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FC0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FD6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FE08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670C5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670F04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80670FA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806710E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671260.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806713E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671528.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806717FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671880.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671A6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671C0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671D10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671D64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671E00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80671F54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672328.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806725A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806725E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672630.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672680.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806726DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_806728F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672A70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672AFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672B1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672BD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672C70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672CBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_80672E6C.s")
