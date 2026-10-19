#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} Struct80005A90;

void func_80005A90(Struct80005A90 *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6, u8 arg7, s16 arg8, s16 arg9) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = arg3;
    arg0->unkA = arg4;
    arg0->unkC = arg5;
    arg0->unkE = arg6;
    arg0->unkF = arg7;
    arg0->unk10 = arg8;
    arg0->unk12 = arg9;
}
