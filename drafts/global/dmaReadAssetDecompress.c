// dmaReadAssetDecompress (src/global/FE40.c): UNPARKED 2026-11-02: park was 186 insns vs target 188 (count-inexact parks stay drafts); dmaReadAssetDecompress (src/global/FE40.c): stage 4, text=38 (unchanged by W4Frame), frame 0x68 + saves s0-s4/ra, exact length. Root cause of the remaining diff: the entry test (arg3 != 0) loads ucvt(arg3), which DOMINATES every later arg3 use (& 0x80, if (arg3), the func_80002790 arg, final test), so uopt makes ONE candidate whose def is the entry lbu: uncoloured -> 'sw t7,68(sp)' + lw reloads; target reloads 'lbu 0x77(sp)' at every use (arg4, whose first use is inside the || arm, already does). Tried, no gain: 13 spellings of the entry/final test x 8 of '& 0x80' x 6 of the call arg (anneal over 6 sites); volatile on arg3 (per-use lbu appears, 68(sp) spill vanishes, 41 lines, but as1 delay-slot hoists lost) and arg3/4/5 (worse); dead '&arg3' forms (if (&arg3) {}, ptr local, global store) drop the spill but keep arg3 as a v0 candidate (84 lines); rem = size - (((u32)size >> 14) << 14) / size % 0x4000 / (u32)size % 0x4000U (target's srl a0 / sll t3,a0,14 / subu CSE of a chunk count): 45-96 lines. Untried: making the entry compare a raw non-ucvt node so it does not dominate.
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
