#include "common.h"


extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;
extern void *D_807ECE18;
void *heapAlloc(s32);
void heapFree(void *);
void gunzip(void *, void *, void *);
void func_80002790(void *, void *, void *, s32);

void dmaReadAssetDecompress(u32 arg0, void *arg1, s32 *arg2, u8 arg3, u8 arg4, u8 arg5, void *arg6) {
    s32 count;
    s32 size;
    void *sp5C;
    void *sp58;
    s32 rem;
    void *sp50;
    void *ptr;

    sp58 = arg1;
    if (arg3 || arg4) {
        if ((arg3 & 0xFF) & 0x80) { // FAKE: redundant andi burns one ugen ring temp (as1 deletes it)
            sp5C = arg6;
            arg6 = (u8 *)arg6 + 0x3800;
        } else if (arg6 != NULL) {
            sp5C = (void *)0x80024000;
        } else {
            sp50 = heapAlloc(*arg2);
            sp5C = sp50;
        }
    } else {
        sp5C = arg1;
    }
    osInvalDCache(sp5C, *arg2);
    size = *arg2;
    count = 0; ptr = sp5C; while (count < ((u32)size >> 14)) { // LAYOUT: joined onto the loop header line (as1 preheader order)
        osPiStartDma(&D_807ECE00, 0, 0, arg0, ptr, 0x4000, &D_807655F0);
        D_80746834 = 4;
        osRecvMesg(&D_807655F0, NULL, 1);
        D_80746834 = 0;
        count++;
        size = *arg2;
        arg0 += 0x4000;
        ptr = (u8 *)ptr + 0x4000;
    }
    rem = size - (((u32)size >> 14) << 14);
    if (rem != 0) {
        osPiStartDma(&D_807ECE00, 0, 0, arg0, ptr, rem, &D_807655F0);
        D_80746834 = 5;
        osRecvMesg(&D_807655F0, NULL, 1);
        D_80746834 = 0;
    }
    D_807ECE18 = arg6;
    if ((arg6 == NULL) && ((arg5 == 1) || (arg5 == 2))) {
        D_807ECE18 = heapAlloc(0x4000);
    }
    switch (arg5) {
    case 1:
        if (arg3) {
            gunzip(&sp5C, &arg1, D_807ECE18);
        }
        if (arg4) {
            gunzip(&sp5C, &arg1, D_807ECE18);
        }
        break;
    case 2:
        if (arg3) {
            func_80002790(&sp5C, &arg1, D_807ECE18, arg3);
        }
        if (arg4) {
            func_80002790(&sp5C, &arg1, D_807ECE18, arg4);
        }
        break;
    }
    if ((arg6 == NULL) && ((arg5 == 1) || (arg5 == 2))) {
        heapFree(D_807ECE18);
    }
    if (arg3 || arg4) {
        *arg2 = (u8 *)arg1 - (u8 *)sp58;
        if (arg6 == NULL) {
            heapFree(sp50);
        }
    }
}
