// func_8070DA28 (src/global/112080.c): Stage 3 K&R/do-while candidate; target still needs beqz and bnel delay-slot scheduling.
typedef struct P112bNode {
    u8 flags;
    u8 pad1[0xB];
    void *children;
    u8 pad10[0xC];
    struct P112bNode *next;
} P112bNode;

typedef struct P112bFreeList {
    u8 pad0[0xC];
    P112bNode *first;
    u8 state;
} P112bFreeList;

void func_8070DA28(P112bFreeList *arg0) {
    P112bNode *node;

    node = arg0->first;
    if (node != NULL) {
        do {
            func_8070D9AC(node);
            node = node->next;
        } while (node != NULL);
    }
    arg0->first = NULL;
    arg0->state = 0;
}
