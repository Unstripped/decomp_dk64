// func_80714778 (src/global/119370.c): Stage 4: exact blocks and 0x30 frame; 78 instruction differences are v0/v1 allocation and stack slots 0x24/0x28/0x2c.
#include "common.h"
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
extern Ua1ListNode *D_807FDB00;
extern void *func_80610FE8(s32);
void func_807146E0(Ua1ListNode *, u8 *, u8 *);
void func_807146F4(Ua1ListNode *, s16 *, s16 *);

void func_80714778(Ua1ListNode *arg0) {
    Ua1ListNode *node;
    Ua1ListNode *last;
    Ua1ListNode *newNode;
    s32 count;
    s32 i;

    node = D_807FDB00;
    last = NULL;
    while (node != NULL) {
        last = node;
        if (arg0 == node->unk0) {
            return;
        }
        node = node->unk24;
    }

    newNode = func_80610FE8(0x28);
    newNode->unk24 = NULL;
    newNode->unk0 = arg0;
    newNode->unk4 = (s32) arg0->unk0;
    func_807146E0(arg0, &newNode->unk8, &newNode->unk9);
    ((u8 *) newNode)[0xA] = ((u8 *) arg0)[0x6];
    ((u8 *) newNode)[0xB] = ((u8 *) arg0)[0x7];
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
