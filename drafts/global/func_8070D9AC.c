// func_8070D9AC (src/global/112080.c): stage 3: correct ownership traversal; DA28 caller remains branch-scheduled differently.
typedef struct M112aChildNode {
    u8 pad0[0x14];
    s32 handle;
    u8 pad18[0x88];
    struct M112aChildNode *next;
} M112aChildNode;
typedef struct M112aFreeNode {
    u8 flags;
    u8 pad1[0xB];
    M112aChildNode *children;
} M112aFreeNode;
void func_80715908(s32);
void heapFreeDeferred(void *);
void func_8070D9AC(M112aFreeNode *arg0) {
    s32 temp_a0;
    s32 temp_s2;
    M112aChildNode *temp_s0;
    M112aChildNode *var_s1;

    var_s1 = arg0->children;
    temp_s2 = arg0->flags & 2;
    if (var_s1 != NULL) {
        do {
            temp_s0 = var_s1;
            var_s1 = var_s1->next;
            if (temp_s2 != 0) {
                temp_a0 = temp_s0->handle;
                if (temp_a0 != 0) {
                    func_80715908(temp_a0);
                }
            }
            heapFreeDeferred(temp_s0);
        } while (var_s1 != NULL);
    }
    heapFreeDeferred(arg0);
}
