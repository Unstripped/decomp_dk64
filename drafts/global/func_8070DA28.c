// func_8070DA28 (src/global/112080.c): Stage 3: K&R do/while preserves size and flow, but target's beqz/bnel delay scheduling remains unmatched; goto loop and hoisted forms also failed.
typedef struct S112aFreeNode {
    u8 flags;
    u8 pad1[0xB];
    void *children;
    u8 pad10[0xC];
    struct S112aFreeNode *next;
} S112aFreeNode;

typedef struct N112FreeList {
    u8 pad0[0xC];
    S112aFreeNode *first;
    u8 state;
} N112FreeList;

void func_8070D9AC(S112aFreeNode *);

void func_8070DA28(arg0)
N112FreeList *arg0;
{
    S112aFreeNode *node;

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
