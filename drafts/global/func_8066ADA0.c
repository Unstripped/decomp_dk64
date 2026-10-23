// func_8066ADA0 (src/global/6AD90.c): 81 insns: logic fully recovered, frame size 0x48 vs 0x58 (sp40 at 0x40 vs 0x54)
#include "common.h"

extern s32 D_8000DDCC;
extern u8 D_80748E18[];
extern s32 D_807F9520;
extern s32 *D_807F9528[];
extern s32 *D_807F95A8[];
extern void *D_807F9628[];
extern s32 D_807F9678;
extern u8 D_807F967C;
extern u8 D_807F967D;
extern s32 D_807F9680;
extern s32 *D_807FB1A0[];
extern u8 D_807FB220;
extern u8 D_807FB221;

void *func_80610FE8(s32);
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
void *func_8066B0F8(s32, s32, s32, s32);

void func_8066ADA0(void) {
    s32 sp40;
    s32 *var_v0;
    s32 *var_v1;
    s32 i;
    u8 *var_s2;
    s32 **var_s1;

    sp40 = 0x80;
    D_807F9520 = (s32)func_80610FE8(0x80);
    func_8060B140(D_8000DDCC, (void *)D_807F9520, &sp40, 0, 0, 0, 0);

    var_v1 = (s32 *)D_807F9528;
    var_v0 = (s32 *)D_807F95A8;
    do {
        *var_v1++ = 0;
        *var_v0++ = 0;
    } while ((u32)var_v0 < (u32)D_807F9628);

    var_v0 = (s32 *)D_807F9628;
    do {
        *var_v0++ = 0;
    } while ((u32)var_v0 < (u32)&D_807F9678);

    D_807F9680 = 0;
    D_807F967C = 0;
    D_807F9678 = 0;
    D_807F967D = 0;

    var_s2 = D_80748E18;
    var_s1 = D_807FB1A0;
    for (i = 0; i < 0x20; i++) {
        if (*var_s2 != 0) {
            *var_s1 = func_8066B0F8(0x1A, i, 1, 1);
        } else {
            *var_s1 = NULL;
        }
        var_s2++;
        var_s1++;
    }

    D_807FB220 = 0;
    D_807FB221 = 0;
}
