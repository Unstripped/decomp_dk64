// func_80639F1C (src/global/36880.c): from .scratch/NM36B/func_80639F1C_best.c
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

s32 func_80639F1C(R36880eNode *arg0, s32 *arg1, s32 *arg2) {
    s32 result;

    result = 0;
    switch (arg0->unk48) {
        case 1:
            arg0->unk50 += 1;
            if (arg0->unk50 == arg0->unk4C) {
                arg0->unk50 = 0;
                arg0->unk54 += 1;
                if (arg0->unk54 == arg0->unk58) {
                    arg0->unk54 = 0;
                }
                result = 1;
            }
            break;
        case 0:
            if (arg0->unk49 != 0) {
                result = 1;
            }
            break;
        default:
            break;
    }
    *arg1 = arg0->unk54;
    if (arg0->unk58 == arg0->unk54 + 1) {
        *arg2 = 0;
    } else {
        *arg2 = arg0->unk54 + 1;
    }
    return result;
}
