#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern u8 D_80750AB4;
extern s16 D_807FDB34;

void *func_80610FE8(s32);
u32 func_806119A0(void);


typedef struct Ua1ListNode {
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
    struct Ua1ListNode *unk24;
} Ua1ListNode;

typedef struct Ua1Effect {
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
    struct Ua1Effect *previous;
    struct Ua1Effect *next;
} Ua1Effect;


extern Ua1ListNode *D_807FDB00;
extern Ua1Effect *D_807FDB04;
extern Ua1Effect *D_807FDB08;
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

void func_80714A9C(void);

void func_80714670(void) {
    D_807FDB00 = NULL;
    D_807FDB04 = NULL;
    D_807FDB08 = NULL;
    func_80714A9C();
}

s32 func_807146A4(s32 arg0) {
    Ua1ListNode *node = D_807FDB00;

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

void func_807146E0(Ua1ListNode *arg0, u8 *arg1, u8 *arg2) {
    *arg1 = ((u8 *) arg0)[4];
    *arg2 = ((u8 *) arg0)[5];
}

void func_807146F4(Ua1ListNode *arg0, s16 *arg1, s16 *arg2) {
    *arg1 = arg0->unkE;
    *arg2 = arg0->unk10;
}

void func_80714708(Ua1ListNode *arg0, s16 *arg1, s16 *arg2) {
    s16 pad0;
    s16 pad1;
    u8 sp1B;
    u8 sp1A;
    func_807146E0(arg0, &sp1B, &sp1A);
    func_807146F4(arg0, arg1, arg2);
    *arg1 *= sp1B;
    *arg2 *= sp1A;
}

void func_80714778(Ua1ListNode *arg0) {
    Ua1ListNode *last;
    Ua1ListNode *newNode;
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

    newNode = func_80610FE8(0x28);
    newNode->unk24 = NULL;
    newNode->unk0 = arg0;
    newNode->unk4 = (s32) arg0->unk0;
    func_807146E0(arg0, &newNode->unk8, &newNode->unk9);
    ((u8 *) newNode)[0xA] = ((u8 *) arg0)[0x6];
    ((u8 *) newNode)[byteOffset] = ((u8 *) arg0)[0x7];
    ((u8 *) newNode)[0x10] = ((u8 *) arg0)[0x8];
    ((u8 *) newNode)[0x11] = ((u8 *) arg0)[0x9];
    ((u8 *) newNode)[0x12] = ((u8 *) arg0)[0xA];
    ((u8 *) newNode)[0x13] = ((u8 *) arg0)[0xB];
    ((u8 *) newNode)[0x14] = ((u8 *) arg0)[0xC];
    ((u8 *) newNode)[0x15] = ((u8 *) arg0)[0xD];
    func_807146F4(arg0, &newNode->unkC, &newNode->unkE);
    newNode->unk16 = arg0->unk12;
    newNode->unk18 = -1;

    if (D_807FDB00 != NULL) {
        last->unk24 = newNode;
    } else {
        D_807FDB00 = newNode;
    }

    count = newNode->unk8 * newNode->unk9 * newNode->unk16;
    newNode->unk1C = func_80610FE8(count * 8);
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

void func_80714A38(u8 arg0) {
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

void func_80714A9C(void) {
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

void func_806335B0();
void func_80714D08(s32, f32, f32, f32, f32, void *, s32, s32, s32);

void func_80714B84(s32 arg0, f32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    func_806335B0(arg2, 1, arg3, &sp3C, &sp38, &sp34);
    func_80714D08(arg0, arg1, sp3C, sp38, sp34, NULL, arg2, arg3, (s32) arg4);
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
        func_80714A38(0x40);
    }
    func_80714D08(arg0, arg1, sp3C, sp38, sp34, arg2, 0, arg3, (s32) arg4);
}

void func_80714CC0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_80714D08(arg0, arg1, arg2, arg3, arg4, NULL, 0, 0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80714D08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_8071509C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715270.s")

void func_80715908(Ua1Effect *);

void func_8071586C(s32 arg0) {
    Ua1Effect *effect;

    effect = D_807FDB04;
    if (effect != NULL) {
        do {
            if (arg0 == effect->resource) {
                func_80715908(effect);
            }
            effect = effect->next;
        } while (effect != NULL);
    }
}

void func_807158C0(void) {
    Ua1Effect *effect;
    Ua1Effect *next;

    effect = D_807FDB04;
    if (effect != NULL) {
        do {
            next = effect->next;
            func_80715908(effect);
            effect = next;
        } while (next != NULL);
    }
}

void func_80630588(s32, s32, s32, void *);
void func_8062D26C(void *);
void heapFreeDeferred(void *);

void func_80715908(Ua1Effect *effect) {
    u8 sp3F;
    s32 temp_a0;
    s32 i;
    Ua1Effect *previous;
    Ua1Effect *next;
    Ua1Effect *buffer;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            func_80630588(0, (s32)effect, 4, &sp3F - 8);
        } else {
            func_8062D26C(effect);
        }
    } else {
        func_80630588(0, (s32)effect, 3, &sp3F - 8);
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
        buffer = (Ua1Effect *)((u8 *)buffer + 8);
    }
    if (osCicId != 0x17D9) {
        osSetTime((s64)(s32)func_806119A0());
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

typedef struct Ua2bRouteEntry {
    s32 value;
    s32 column;
} Ua2bRouteEntry;

s32 func_8066B0F8(s32, s16, s32, s32);

void func_80715A3C(s16 *arg0, u8 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 *arg5) {
    u8 category;
    s32 i;
    s32 index;
    s32 value;
    s32 *out;
    Ua2bRouteEntry *entry;

    i = 0;
    if (arg3 > 0) {
        out = arg5;
        index = arg3 * arg4;
        entry = (Ua2bRouteEntry *)arg2;
        entry += index;
        do {
            if (entry->column == -1) {
                if (arg1) {
                    category = 0x19;
                } else {
                    category = 7;
                }
                value = func_8066B0F8(category, arg0[index + i], 0, 0);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715B30.s")

f32 func_80715E38(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 x;
    f32 y;
    f32 z;

    x = arg0 - arg3;
    y = arg1 - arg4;
    z = arg2 - arg5;
    return sqrtf((x * x) + (y * y) + (z * z));
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/119370/func_80715E94.s")
