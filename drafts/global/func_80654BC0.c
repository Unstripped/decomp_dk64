// func_80654BC0 (src/global/55B20.c): stage5-6 near-miss (M55P4)
#include "common.h"
#include "actor.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
} M55P4Cell;

extern s32 D_807F70AC;
extern s32 D_807F70B0;

void func_80654BC0(s32 arg0, u8 arg1) {
    s32 i;
    s32 off;
    s32 found;

    found = 0;
    i = 0;
    off = i * 0x1C;
    while (!found && i < D_807F70AC) {
        i++;
        if (arg0 == ((M55P4Cell *)(D_807F70B0 + off))->unk2) {
            ((M55P4Cell *)(D_807F70B0 + off))->unk18 = arg1;
            found = 1;
            if (arg1 != 0) {
                ((M55P4Cell *)(D_807F70B0 + off))->unk19 = 1;
            }
        }
        off += 0x1C;
    }
    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        if (arg0 == ((M55P4Cell *)(D_807F70B0 + off))->unk4) {
            func_80654BC0(((M55P4Cell *)(D_807F70B0 + off))->unk2, arg1);
        }
        i++;
        off += 0x1C;
    }
}
