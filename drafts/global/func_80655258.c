// func_80655258 (src/global/55B20.c): stage5-6 near-miss (M55P4)
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

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
} M55P4Hit;

typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[0x87];
} M55P4Effect;

extern s32 D_807F70AC;
extern s32 D_807F70B0;
extern s32 D_807F70B4;
extern M55P4Effect *D_807F6C18;
extern f32 D_807F5FAC;

s32 func_8062DBDC(s16, s16, s16, s16, s32, s32, f32, f32, f32, f32, void *);

void func_80655258(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;
    s32 off;

    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        if (arg3 == ((M55P4Cell *)(D_807F70B0 + off))->unk4) {
            if (D_807F6C18[((M55P4Cell *)(D_807F70B0 + off))->unk0].unk0 == 1) {
                if (func_8062DBDC(((M55P4Hit *)D_807F70B4)[((M55P4Cell *)(D_807F70B0 + off))->unk2].unk0,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)(D_807F70B0 + off))->unk2].unk2,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)(D_807F70B0 + off))->unk2].unk4,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)(D_807F70B0 + off))->unk2].unk6,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)(D_807F70B0 + off))->unk2].unk8,
                                  ((M55P4Hit *)D_807F70B4)[((M55P4Cell *)(D_807F70B0 + off))->unk2].unkA,
                                  arg0, arg1, arg2, D_807F5FAC,
                                  (u8 *)&D_807F6C18[((M55P4Cell *)(D_807F70B0 + off))->unk0] + 0x88) != 0) {
                    ((M55P4Cell *)(D_807F70B0 + off))->unk18 = 1;
                    ((M55P4Cell *)(D_807F70B0 + off))->unk19 = 1;
                }
                if (((M55P4Cell *)(D_807F70B0 + off))->unk18 != 0) {
                    func_80655258(arg0, arg1, arg2, ((M55P4Cell *)(D_807F70B0 + off))->unk2);
                }
            }
        }
        i++;
        off += 0x1C;
    }
}
