// func_8070D970 (src/global/112080.c): stage 2: correct decrement control flow; caller temporary still differs from target.
typedef struct M112aLookupNode {
    u16 id;
    u8 count;
    u8 pad3[9];
    struct M112aLookupNode *next;
} M112aLookupNode;

M112aLookupNode *func_8070D928(s32);

void func_8070D970(s32 arg0) {
    s32 target;
    M112aLookupNode *node;

    target = arg0 & 0xFFFF;
    node = func_8070D928(target);
    if (node != NULL) {
        node->count--;
    }
}
