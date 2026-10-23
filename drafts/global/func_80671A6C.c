// func_80671A6C (src/global/70FD0.c): regalloc: s5/s6 swapped (-1 vs mtx_base); all other instructions and stack offsets 0x9C,0xA0,0xA4,0x5C match 100%
extern u8 D_807444FC;
void *memcpy(void *, const void *, size_t);

void func_80671A6C(M70H_SubActor *arg0, u8 arg1) {
    M70E_Node *node;
    u8 var_v0;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 mtx[4][4];
    s32 mtx_base;

    if (arg1 || (D_8076A064 != arg0->unk84)) {
        if (D_8076A064 == arg0->unk88) {
            var_v0 = D_807444FC;
        } else {
            var_v0 = (D_807444FC ^ 1) & 0xFF;
        }
        node = arg0->unk90;
        if (node != NULL) {
            mtx_base = arg0->unk74[var_v0];
            do {
                if (node->unk18 == -1) {
                    memcpy(&mtx, arg0->unk70, sizeof(mtx));
                    guMtxXFMF(mtx, node->x, node->y, node->z, &spA4, &spA0, &sp9C);
                } else {
                    guMtxXFML((Mtx *)(mtx_base + ((node->unk18 >> 6) << 6)), node->x, node->y, node->z, &spA4, &spA0, &sp9C);
                }
                node->unkC = (s32)(spA4 * 8.0f);
                node->unk10 = (s32)(spA0 * 8.0f);
                node->unk14 = (s32)(sp9C * 8.0f);
                node = node->next;
            } while (node != NULL);
        }
        arg0->unk84 = D_8076A064;
    }
}
