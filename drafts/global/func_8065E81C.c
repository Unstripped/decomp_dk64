// func_8065E81C (src/global/61AA0.c): 136/138 insns matched; only 2 prologue insns diff (sw a0, 0x58(sp) home-slot spill and andi s7, a0, 0xff order); loop body 100% matched
#include <ultra64.h>

void heapFree(void *);
void heapFreeDeferred(void *);
s32 func_8065EA98(s32, s16, u8);

typedef struct R3C_Node {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    struct R3C_Node *hash_next;
    struct R3C_Node *hash_prev;
    struct R3C_Node *list_next;
    struct R3C_Node *list_prev;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
} R3C_Node;

extern R3C_Node *D_807F8EC0[];
extern R3C_Node *D_807F9050;
extern R3C_Node *D_807F9054;
extern s32 D_8076A064;
extern s32 D_807F905C;
extern u16 D_807F9060;
extern s32 D_807F9064;

s32 func_8065E81C(s32 arg0, s16 arg1) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    u8 sp43;
    R3C_Node *node;
    R3C_Node *next;
    R3C_Node **bucket;
    s32 cond;

    cond = arg0 & 0xFF;
    node = D_807F9054;
    sp43 = 0;
    if (cond != 0) {
        arg1 = 1;
    }

    while (1) {
        if (cond != 0) {
            if (!((u32)D_807F9064 < (u32)D_807F905C)) {
                break;
            }
        }
        if (node == NULL) {
            break;
        }
        next = node->list_prev;
        if ((cond == 0 && (u32)D_807F9064 < (u32)D_807F905C) || (u32)arg1 < (u32)(D_8076A064 - node->unkC)) {
            if (node == D_807F9054) {
                D_807F9054 = node->list_prev;
            }
            if (node == D_807F9050) {
                D_807F9050 = node->list_next;
            }
            if (node->list_next != NULL) {
                node->list_next->list_prev = node->list_prev;
            }
            if (node->list_prev != NULL) {
                node->list_prev->list_next = node->list_next;
            }
            D_807F905C -= node->unk10;
            D_807F9060--;
            bucket = &D_807F8EC0[func_8065EA98(node->unk29, node->unk24, node->unk28)];
            if (node == *bucket) {
                *bucket = node->hash_next;
                if (node->hash_next != NULL) {
                    node->hash_next->hash_prev = NULL;
                }
            } else {
                if (node->hash_next != NULL) {
                    node->hash_next->hash_prev = node->hash_prev;
                }
                if (node->hash_prev != NULL) {
                    node->hash_prev->hash_next = node->hash_next;
                }
            }
            if ((u32)(D_8076A064 - node->unkC) >= 2) {
                heapFree(node);
                sp43 = 1;
            } else {
                heapFreeDeferred(node);
            }
        }
        node = next;
    }
    return sp43;
}
