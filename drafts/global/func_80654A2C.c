// func_80654A2C (src/global/55B20.c): stage6: matches except lbu v0/v1 operand reg (2x) and one nop; permuter hint idx temp applied
#include "common.h"
#include "actor.h"

typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
} M55P4Cell;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ s16 unk14[16];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 pad35;
    /* 0x36 */ s16 unk36[16];
    /* 0x56 */ u8 unk56;
} M55P4Trigger;

extern s32 D_807F70AC;
extern s32 D_807F70B0;
extern M55P4Trigger *D_807F70B8[];
extern u8 D_807F7048[];
extern u8 D_807F7058;

void func_80654BC0(s32, u8);

void func_80654A2C(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 j;
    s32 off;
    s32 done;
    s16 *val;
    M55P4Trigger *trig;
    u8 idx;

    done = 0;
    i = 0;
    while (i < D_807F7058) {
        idx = D_807F7048[i];
        if (D_807F70B8[idx] != 0) {
            trig = (M55P4Trigger *)D_807F70B8[idx];
            if (!done) {
                if (trig->unk56 != 0) {
                    done = 1;
                    val = trig->unk36;
                    j = 0;
                    off = 0;
                    while (j < D_807F70AC) {
                        j++;
                        *((u8 *)(D_807F70B0 + off) + 0x18) = 0;
                        off += 0x1C;
                    }
                    for (j = 0; j < trig->unk56; j++) {
                        func_80654BC0(*val, 1);
                        val++;
                    }
                } else {
                    val = trig->unk14;
                    for (j = 0; j < trig->unk34; j++) {
                        func_80654BC0(*val, 0);
                        val++;
                    }
                }
            }
        }
        i++;
    }
}
