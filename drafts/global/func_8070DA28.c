// func_8070DA28 (src/global/112080.c): stage 3: do/while, while, for, and early-return forms all preserve size but schedule the call argument and loop branch differently; closest do/while delays the next-pointer load after the call instead of filling its delay slot.
typedef struct S112aFreeNode {
    u8 flags;
    u8 pad1[0xB];
    void *children;
    u8 pad10[0xC];
    struct S112aFreeNode *next;
} S112aFreeNode;

typedef struct S112aFreeList {
    u8 pad0[0xC];
    S112aFreeNode *first;
    u8 state;
} S112aFreeList;

void func_8070D9AC(S112aFreeNode *);

void func_8070DA28(S112aFreeList *arg0) {
    S112aFreeNode *node;

    node = arg0->first;
    if (node != NULL) {
        do {
            func_8070D9AC(node);
        } while ((node = node->next) != NULL);
    }
    arg0->first = NULL;
    arg0->state = 0;
}
