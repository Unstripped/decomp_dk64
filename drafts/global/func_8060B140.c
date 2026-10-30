// func_8060B140 (src/global/FE40.c): stage 1: typed m2c recovery saved; not yet compiled in private translation unit
extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;
extern void *D_807ECE18;
void *heapAlloc(s32);
void heapFree(void *);
void func_8060B140(u32 arg0, void *arg1, s32 *arg2, u8 arg3, u8 arg4, u8 arg5, void *arg6) {
    void *sp5C; void *sp58 = arg1; void *sp50; s32 count = 0; s32 size; u32 chunks; void *ptr;
    if ((arg3 != 0) || (arg4 != 0)) {
        if (arg3 & 0x80) { sp5C = arg6; arg6 += 0x3800; }
        else if (arg6 != NULL) sp5C = (void *)0x80024000;
        else { sp50 = heapAlloc(*arg2); sp5C = sp50; }
    } else sp5C = arg1;
    osInvalDCache(sp5C, *arg2);
    size = *arg2; ptr = sp5C; chunks = (u32)size >> 14;
    while (count < chunks) {
        osPiStartDma(&D_807ECE00, 0, 0, arg0, ptr, 0x4000, &D_807655F0);
        D_80746834 = 4; osRecvMesg(&D_807655F0, NULL, 1); D_80746834 = 0;
        count++; size = *arg2; arg0 += 0x4000; ptr += 0x4000; chunks = (u32)size >> 14;
    }
    size -= chunks << 14;
    if (size != 0) { osPiStartDma(&D_807ECE00, 0, 0, arg0, ptr, size, &D_807655F0); D_80746834 = 5; osRecvMesg(&D_807655F0, NULL, 1); D_80746834 = 0; }
    D_807ECE18 = arg6;
    if ((arg6 == NULL) && ((arg5 == 1) || (arg5 == 2))) D_807ECE18 = heapAlloc(0x4000);
    if (arg5 == 1) { if (arg3) gunzip(&sp5C, &arg1, D_807ECE18); if (arg4) gunzip(&sp5C, &arg1, D_807ECE18); }
    else if (arg5 == 2) { if (arg3) func_80002790(&sp5C, &arg1, D_807ECE18, arg3); if (arg4) func_80002790(&sp5C, &arg1, D_807ECE18, arg4); }
    if ((arg6 == NULL) && ((arg5 == 1) || (arg5 == 2))) heapFree(D_807ECE18);
    if ((arg3 != 0) || (arg4 != 0)) { *arg2 = (u8 *)arg1 - (u8 *)sp58; if (arg6 == NULL) heapFree(sp50); }
}
