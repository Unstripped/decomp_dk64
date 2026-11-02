// dmaReadAssetDecompress (src/global/FE40.c): stage 4->6: frame 0x68 + saves s0-s4/ra, exact length; full=38 text=38 shape=15 (was 95). Remaining: arg3 (u8 in a3, only reg-passed narrow formal) ucvt cand spilled 'sw t7,68(sp)' + reloads vs target fresh lbu 0x77(sp) each use (shifts t-ring); chunks as a0 CSE (srl a0 / sll t3,a0,14 / subu v0) lost: rem=size&0x3FFF used (chunks local + rem local -> frame 0x70 because of the arg3 spill slot); switch(arg5) matches dispatch shape; count=0 moved after osInvalDCache/ptr gives s0/s1/s2/s3 right; K&R, &arg3 dead address, cond/and spelling grids no help
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
    if ((arg3 != 0) || (arg4 != 0)) {
        if (arg3 & 0x80) {
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
    ptr = sp5C;
    count = 0;
    size = *arg2;
    while (count < ((u32)size >> 14)) {
        osPiStartDma(&D_807ECE00, 0, 0, arg0, ptr, 0x4000, &D_807655F0);
        D_80746834 = 4;
        osRecvMesg(&D_807655F0, NULL, 1);
        D_80746834 = 0;
        count++;
        size = *arg2;
        arg0 += 0x4000;
        ptr = (u8 *)ptr + 0x4000;
    }
    rem = size & 0x3FFF;
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
    if ((arg3 != 0) || (arg4 != 0)) {
        *arg2 = (u8 *)arg1 - (u8 *)sp58;
        if (arg6 == NULL) {
            heapFree(sp50);
        }
    }
}
