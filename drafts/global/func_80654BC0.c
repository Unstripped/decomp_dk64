// func_80654BC0 (src/global/55B20.c): stage 5-6 near-miss; see M55P4 report
#include "common.h"
#include "actor.h"



void func_80654BC0(s32, u8);
f32 func_80654CCC(M55P4Tri *, f32, f32);
s32 func_80654E84(M55P4Tri *, f32, f32);
s32 func_80654FEC(M55P4Tri *, f32, f32);
void func_80636164(s32, u8);
void func_80636210(s32, u8);
s32 func_80652E58(s32);
s32 func_8065E81C(s32, s32);
void heapFree(void *);

void func_806547A8(f32 arg0, f32 arg1, f32 arg2) {
    M55P4Zone **p;
    M55P4Zone *zone;
    M55P4Tri *node;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 found;
    u8 *q;
    f32 h;

    D_807F7058 = 0;
    D_807F7070 = 0;
    p = D_807F70B8;
    for (i = 0; i != 0x20; i++) {
        zone = *p;
        if (zone != NULL && (f32)zone->unk10 <= arg1 && arg1 <= (f32)(zone->unk12 + zone->unkE)) {
            node = (M55P4Tri *)zone->unk8;
            for (j = 0; j < zone->unkC; j++, node++) {
                if (func_80654E84(node, arg0, arg2) != 0 && func_80654FEC(node, arg0, arg2) != 0) {
                    h = func_80654CCC(node, arg0, arg2);
                    if (h <= arg1 && arg1 <= (f32)zone->unkE + h) {
                        k = 0;
                        if (D_807F7058 != 0x10) {
                            D_807F7048[D_807F7058] = i;
                            D_807F7058++;
                        }
                        for (; k < zone->unk68; k++) {
                            found = 0;
                            n = 0;
                            q = D_807F7060;
                            while (!found && n < D_807F7070) {
                                if (*q == zone->unk58[k]) {
                                    found = 1;
                                } else {
                                    n++;
                                    q++;
                                }
                            }
                            if (!found && n != 0x10) {
                                D_807F7060[D_807F7070] = zone->unk58[k];
                                D_807F7070++;
                            }
                        }
                    }
                }
            }
        }
        p++;
    }
}
