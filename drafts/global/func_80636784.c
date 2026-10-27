// func_80636784 (src/global/36880.c): stage 4: frame 0x58 vs 0x50; mine promotes u8 arg3 into s5 (andi) and hoists 0xFD into s7 where target reads arg3 via lbu a0,0x5f(sp) per outer iter and keeps only s0-s4 (arg0 cursor, const 1, arg4, arg2, arg1); inner node var matches (v0). tried tag var, sel=arg3 copy, if-chain.
typedef struct R36880eCmd {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} R36880eCmd;

typedef struct R36880eLink {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ u8 pad2C[0xA8];
    /* 0xD4 */ struct R36880eLink *unkD4;
} R36880eLink;

void collisionBstLookupByHash(s32, s32 *, s32 *);

void func_80636784(R36880eCmd *arg0, R36880eCmd *arg1, R36880eLink *arg2, u8 arg3, u8 arg4) {
    u32 w;
    s32 sp40;
    s32 sp3C;
    s32 found;
    R36880eLink *node;
    s32 sel;

    if (arg0 != arg1) {
        do {
            w = arg0->unk0;
            found = 0;
            if ((w >> 24) == 0xFD) {
                node = arg2;
                if (node != NULL) {
                    sel = arg3;
                    do {
                        switch (sel) {
                            case 0:
                                if ((void *)arg0 == node->unk0) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk4) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unkC) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk10) {
                                    found = 1;
                                }
                                break;
                            case 1:
                                if ((void *)arg0 == node->unk18) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk1C) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk24) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk28) {
                                    found = 1;
                                }
                                break;
                        }
                        node = node->unkD4;
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    if (arg4 != 0) {
                        collisionBstLookupByHash((s32)arg0->unk4, &sp40, &sp3C);
                    }
                    assetFreeBuffer((void *)arg0->unk4, 0xB27, 7);
                    if (arg4 != 0) {
                        arg0->unk4 = sp3C;
                    }
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
}
