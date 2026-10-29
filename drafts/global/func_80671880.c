// func_80671880 (src/global/70FD0.c): text-identical, reloc only: 0.15f literal reloc is .rodata+0xfc vs expected D_8075914C (rodata section bytes identical). K&R def, locals order scale,sub,sp_b4,sp_b0,sp_ac,mtx,node,base,idx; 'if (base) {}' FAKE swaps s5/s6; unk7C != unk80 compare order. Orchestrator: verify against ROM hash and paste.
typedef struct Col7DNode {
    f32 x;
    f32 y;
    f32 z;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u32 unk20;
    u8 pad24[4];
    struct Col7DNode *unk28;
} Col7DNode;

typedef struct Col7DSub140 {
    u8 pad0[0x70];
    void *unk70;
    s32 unk74[2];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    Col7DNode *unk8C;
} Col7DSub140;

typedef struct Col7DActor {
    u8 pad0[4];
    f32 *unk4;
    u8 pad8[0x64 - 8];
    u32 unk64;
    u8 pad68[0x120 - 0x68];
    f32 unk120;
    u8 pad124[0x140 - 0x124];
    Col7DSub140 *unk140;
} Col7DActor;

void *memcpy(void *, void *, s32);
extern u8 D_807444FC;

void func_80671880(arg0, arg1)
Col7DActor *arg0;
u8 arg1;
{
    f32 scale = 0.15f;
    Col7DSub140 *sub = arg0->unk140;
    f32 sp_b4;
    f32 sp_b0;
    f32 sp_ac;
    f32 mtx[4][4];
    Col7DNode *node;
    s32 base;
    u8 idx;

    if (arg1 != 0 || sub->unk7C != sub->unk80) {
        if (base) {} // FAKE: raises base coloring priority (swaps s5/s6)
        if (arg0->unk4 != NULL) {
            scale = arg0->unk4[0xE];
        }
        if (arg0->unk64 & 0x800) {
            scale = arg0->unk120;
        }
        if (D_8076A064 == sub->unk88) {
            idx = D_807444FC;
        } else {
            idx = D_807444FC ^ 1;
        }
        node = sub->unk8C;
        base = sub->unk74[idx];
        while (node != NULL) {
            if (node->unk20 == -1) {
                memcpy(mtx, sub->unk70, 0x40);
                guMtxXFMF(mtx, node->x, node->y, node->z, &sp_b4, &sp_b0, &sp_ac);
            } else {
                guMtxXFML((Mtx *)(((node->unk20 >> 6) << 6) + base), node->x, node->y, node->z, &sp_b4, &sp_b0, &sp_ac);
            }
            node->unk10 = sp_b4 * 8.0f;
            node->unk14 = sp_b0 * 8.0f;
            node->unk18 = sp_ac * 8.0f;
            node->unk1C = node->unkC * scale * 8.0f;
            node = node->unk28;
        }
        sub->unk7C = sub->unk80;
    }
}
