// func_8070DA28 (src/global/112080.c): stage 3: correct release loop; IDO branch-likely scheduling remains.
typedef struct M112aFreeNode {
    u8 pad0[0x1C];
    struct M112aFreeNode *next;
} M112aFreeNode;
typedef struct M112aFreeList {
    u8 pad0[0xC];
    M112aFreeNode *first;
    u8 state;
} M112aFreeList;
void func_8070D9AC(M112aFreeNode *);
void func_8070DA28(M112aFreeList *arg0) {
    M112aFreeNode *node;

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
