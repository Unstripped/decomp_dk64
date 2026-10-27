// func_80636EFC (src/global/36880.c): stage 6: all identical except `and t1,v0,s6` (target) vs `and t0,v0,s6`; extra temp register consumed in target; u32 w/tag with 0xFD == tag form needed for lw v0 / bnel t6,s5.
typedef struct R36880eCmd {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} R36880eCmd;

typedef struct R36880eDLObj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x28];
    /* 0x30 */ s32 unk30;
} R36880eDLObj;

typedef struct R36880ePtrSet {
    /* 0x0 */ R36880eDLObj *unk0;
    /* 0x4 */ R36880eDLObj *unk4;
    /* 0x8 */ s32 *unk8;
} R36880ePtrSet;

typedef struct R36880eNode {
    /* 0x00 */ R36880ePtrSet unk0[2];
    /* 0x18 */ R36880ePtrSet unk18[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C[29];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct R36880eNode *unkD4;
} R36880eNode;

s32 func_8066B0F8();

s32 func_80636EFC(R36880eCmd *arg0, R36880eCmd *arg1, R36880eNode *arg2, u8 arg3) {
    u32 w;
    u32 tag;
    s32 result;
    s32 found;
    R36880eNode *node;
    s32 val;

    result = 0;
    if (arg0 != arg1) {
        do {
            w = arg0->unk0;
            found = 0;
            tag = w >> 24;
            if (0xFD == tag) {
                node = arg2;
                if (node != NULL) {
                    do {
                        if (arg0->unk4 == node->unk5C[0]) {
                            found = 1;
                        } else {
                            node = node->unkD4;
                        }
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    val = (s32)func_8066B0F8(0x19, arg0->unk4, (u8)(arg3 == 0), 0);
                    arg0->unk4 = val;
                    if (val & 7) {
                        arg0->unk4 = val & ~0xF;
                        result = 1;
                    }
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
    return result;
}
