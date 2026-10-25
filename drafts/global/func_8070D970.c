// func_8070D970 (src/global/112080.c): stage 3: taking arg0’s address obtains the required stack home; with s32 target the remaining mismatch is only target’s andi into t6 before the call versus IDO scheduling it into a0 in the call delay slot.
typedef struct S112aListNode {
    u16 id;
    u8 count;
    u8 pad3[9];
    struct S112aListNode *next;
} S112aListNode;

S112aListNode *func_8070D928(u16);

void func_8070D970(s32 arg0) {
    s32 *arg;
    s32 target;
    S112aListNode *node;

    arg = &arg0;
    target = *arg & 0xFFFF;
    node = func_8070D928(target);
    if (node != NULL) {
        node->count--;
    }
}
