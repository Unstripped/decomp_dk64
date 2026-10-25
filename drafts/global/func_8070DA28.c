// func_8070DA28 (src/global/112080.c): Stage 3: ANSI and K&R loop forms, do/while, while, for, early return, and explicit current-node staging all miss the target branch-likely scheduling.
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
