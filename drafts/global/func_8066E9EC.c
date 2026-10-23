// func_8066E9EC (src/global/70FD0.c): Loop peeling with bnel delay slot or a2, a1, zero; 6 insns diff on loop condition
f32 func_8066E9EC(M70C_Actor *arg0, s32 arg1, f32 arg2) {
    M70C_Sub140 *sub = arg0->unk140;
    M70C_Node *node;

    arg1--;
    node = sub->unk8C;
    if (arg1 != 0 && node != NULL) {
        while (node != NULL) {
            node = node->next;
            if (--arg1 == 0) {
                break;
            }
        }
    }
    if (node != NULL) {
        if (arg2 != -1.0f) {
            node->unkC = arg2;
        }
        return node->unkC;
    }
    return -1.0f;
}
