// func_80671A6C (src/global/70FD0.c): regalloc: s5/s6 swapped (-1 vs mtx_base); all other instructions and stack offsets 0x9C,0xA0,0xA4,0x5C match 100%
typedef struct M70E_Node8C {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
    struct M70E_Node8C *next;
} M70E_Node8C;
typedef struct M70E_Node {
    f32 x;
    f32 y;
    f32 z;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u32 unk18;
    struct M70E_Node *next;
} M70E_Node;
typedef struct M70H_SubActor {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xC];
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[0x70 - 0x25];
    void *unk70;
    s32 unk74[2];
    u8 pad7C[0x84 - 0x7C];
    s32 unk84;
    s32 unk88;
    M70E_Node8C *unk8C;
    M70E_Node *unk90;
} M70H_SubActor;

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
