// func_80602144 (src/global/6710.c): MATCHED (stage 6, TEXT OK): declared sp44 first with pad[3], removed unused next, D_807452C4++ in osPiStartDma
#include "common.h"
#include "actor.h"

typedef struct Aud6710_DmaNode {
    struct Aud6710_DmaNode *next;
    struct Aud6710_DmaNode *prev;
    u32 unk8;
    u32 unkC;
    void *unk10;
} Aud6710_DmaNode;

typedef struct Aud6710_Struct80770188 {
    u8 unk0;
    u8 pad1[3];
    Aud6710_DmaNode *unk4;
    Aud6710_DmaNode *unk8;
} Aud6710_Struct80770188;

extern Aud6710_Struct80770188 D_80770188;
extern OSIoMesg D_807701A8[];
extern u32 D_807452C0;
extern u32 D_807452C4;
extern OSMesgQueue D_807704A8;

s32 func_80602144(u32 addr, s32 len, void *state) {
    void *sp44;
    s32 pad[3];
    Aud6710_DmaNode *node;
    Aud6710_DmaNode *last;
    s32 head;
    s32 end;

    last = NULL;
    head = (s32)D_80770188.unk4;
    node = (Aud6710_DmaNode *)head;
    if (head != 0) {
        do {
            end = node->unk8 + 0x800;
            if (addr < node->unk8) {
                break;
            }
            if (end >= (s32)addr + len) {
                last = node;
                node->unkC = D_807452C0;
                return osVirtualToPhysical((u8 *)node->unk10 + (addr - node->unk8));
            }
            last = node;
            node = node->next;
        } while (node != NULL);
    }

    node = D_80770188.unk8;
    if (node == NULL) {
        return osVirtualToPhysical((void *)head);
    }

    D_80770188.unk8 = node->next;
    alUnlink((ALLink *)node);
    if (last != NULL) {
        alLink((ALLink *)node, (ALLink *)last);
    } else {
        head = (s32)D_80770188.unk4;
        if (head != 0) {
            D_80770188.unk4 = node;
            node->next = (Aud6710_DmaNode *)head;
            node->prev = NULL;
            ((Aud6710_DmaNode *)head)->prev = node;
        } else {
            D_80770188.unk4 = node;
            node->next = NULL;
            node->prev = NULL;
        }
    }

    head = addr & 1;
    addr -= head;
    node->unk8 = addr;
    node->unkC = D_807452C0;
    sp44 = node->unk10;
    osPiStartDma(&D_807701A8[D_807452C4++], 1, 0, addr, sp44, 0x800, &D_807704A8);
    return osVirtualToPhysical(sp44) + head;
}
