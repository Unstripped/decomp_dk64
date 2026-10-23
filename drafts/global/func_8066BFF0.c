// func_8066BFF0 (src/global/699B0.c): BST flatten pre-order; 0-insn size delta (59/59), 100% loop body logic matched; regalloc $s0/$s1 swapped between index and node across loop
void func_8066BFF0(R2ENode *node, R1EBufferItem *buffer, s32 *index) {
    while (node != NULL) {
        buffer[*index].unk0 = node->unk0;
        buffer[*index].unk4 = node->unk4;
        buffer[*index].unk8 = node->unk8;
        buffer[*index].unkC = node->unkC;
        buffer[*index].unk10 = node->unk10;
        (*index)++;
        func_8066BFF0(node->left, buffer, index);
        node = node->right;
    }
}
