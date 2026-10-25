// func_8070DD44 (src/global/112080.c): Stage 3 direct queue-unlink candidate; node remains in a0 and s0 save occurs too early versus target.
typedef struct P112bQueueNode {
    u8 pad0[2];
    u8 unk2;
    u8 pad3[5];
    u8 unk8;
    u8 pad9[3];
    struct P112bQueueNode *next;
} P112bQueueNode;

extern s32 D_807550C0;

void func_8070DD44(void) {
    u8 value;
    void **head;
    P112bQueueNode *node;

    head = (void **)&D_807550C0;
    if (D_807550C0 != 0) {
        node = (P112bQueueNode *)D_807550C0;
        do {
            if (node->unk8 == 1) {
                value = node->unk2;
                if (value != 0) {
                    node->unk2 = value - 1;
                    node = *head;
                }
            }
            if (node->unk2 == 0) {
                *head = node->next;
                func_8070DD18(node);
            } else {
                head = (void **)&node->next;
            }
            node = *head;
        } while (node != NULL);
    }
}
