// func_8070DD44 (src/global/112080.c): Stage 3: direct queue unlink/decrement flow compiles, but node stays in a0 and s0 is saved before global setup; delayed head initialization was worse.
extern s32 D_807550C0;

typedef struct N112QueueNode {
    u8 pad0[2];
    u8 unk2;
    u8 pad3[5];
    u8 unk8;
    u8 pad9[3];
    struct N112QueueNode *next;
} N112QueueNode;

typedef struct M112bRecordListHolder M112bRecordListHolder;
void func_8070DD18(M112bRecordListHolder *);

void func_8070DD44(void) {
    u8 value;
    void **head;
    N112QueueNode *node;

    head = (void **)&D_807550C0;
    if (D_807550C0 != 0) {
        node = (N112QueueNode *)D_807550C0;
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
                func_8070DD18((M112bRecordListHolder *)node);
            } else {
                head = (void **)&node->next;
            }
            node = *head;
        } while (node != NULL);
    }
}
