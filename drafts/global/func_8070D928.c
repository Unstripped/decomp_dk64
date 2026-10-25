// func_8070D928 (src/global/112080.c): stage 3: structurally correct lookup; target preserves arg stack home and temp register allocation.
typedef struct M112aLookupNode {
    u16 id;
    u8 count;
    u8 pad3[9];
    struct M112aLookupNode *next;
} M112aLookupNode;

extern M112aLookupNode *D_807550C0;

M112aLookupNode *func_8070D928(s32 arg0) {
    s32 target;
    M112aLookupNode *node;

    node = D_807550C0;
    target = arg0 & 0xFFFF;
    if ((node != NULL) && (target != node->id)) {
loop:
        node = node->next;
        if ((node != NULL) && (target != node->id)) {
            goto loop;
        }
    }
    return node;
}
