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

void func_80005A90(Struct80005A90 *texDesc, s32 texture, s32 param2, s16 width, s16 height, s16 format, u8 param6, u8 param7, s16 param8, s16 param9) {
    texDesc->unk0 = texture;
    texDesc->unk4 = param2;
    texDesc->unk8 = width;
    texDesc->unkA = height;
    texDesc->unkC = format;
    texDesc->unkE = param6;
    texDesc->unkF = param7;
    texDesc->unk10 = param8;
    texDesc->unk12 = param9;
}
