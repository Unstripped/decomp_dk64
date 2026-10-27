// func_8063495C (src/global/36880.c): stage 5: same frame/insn count, control flow matches (if (found != 0) else-branch ordering fixed); remaining diff is pure regalloc: target n=a0, arg0=a2 (move a2,a0), tbl=a3, p=t0, found=t1, idx=t2; ours found=a0, tbl=a2, arg0=a3, n=t0, p=t1. Declaration order/types, tbl-less CSE form, found placement, permuter (115->50) did not change it.
typedef struct R36880bNode {
    /* 0x00 */ u32 *unk0[12];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ void *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60[28];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct R36880bNode *unkD4;
} R36880bNode;

typedef struct R36880bObj {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ void *unk24[11];
    /* 0x50 */ R36880bNode *unk50;
    /* 0x54 */ u8 pad54[0x4C];
    /* 0xA0 */ u32 *unkA0;
    /* 0xA4 */ u32 *unkA4;
    /* 0xA8 */ u32 *unkA8;
    /* 0xAC */ u32 *unkAC;
    /* 0xB0 */ u8 padB0[8];
    /* 0xB8 */ R36880bNode *unkB8;
} R36880bObj;

void func_8063495C(u8 *arg0, ModelSlot *arg1) {
    R36880bNode *node;
    u8 *tbl;
    s16 *p;
    s32 n;
    s32 idx;
    s32 found;
    s32 key;

    node = ((R36880bObj *)arg1->unk20)->unk50;
    if (node != NULL) {
        do {
            key = node->unk5C;
            found = 0;
            tbl = arg0 + *(s32 *)(arg0 + 0x70);
            n = *(s32 *)tbl;
            p = (s16 *)(tbl + 4);
            idx = 0;
            if (n != 0) {
                do {
                    if (key == *p) {
                        found = 1;
                    } else {
                        n--;
                        p = (s16 *)((u8 *)p + 0x30);
                        idx++;
                    }
                } while (n != 0 && found == 0);
            }
            if (found != 0) {
                node->unk44 = ((R36880bObj *)arg1->unk20)->unk24[idx];
            } else {
                node->unk44 = NULL;
            }
            node = node->unkD4;
        } while (node != NULL);
    }
}
