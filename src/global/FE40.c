#include "common.h"
#include "proto/boot/30E0.h"
#include "proto/global/15050.h"
#include "proto/global/FE40.h"


extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;
extern void *D_807ECE18;
void func_80002790(void *, void *, void *, s32);

void dmaReadAssetDecompress(u32 romAddr, void *dst, s32 *sizePtr, u8 decompressFlag1, u8 decompressFlag2, u8 compressType, void *scratchBuf) {
    s32 count;
    s32 size;
    void *dmaBuf;
    void *dstStart;
    s32 rem;
    void *allocBuf;
    void *ptr;

    dstStart = dst;
    if (decompressFlag1 || decompressFlag2) {
        if ((decompressFlag1 & 0xFF) & 0x80) { // FAKE: redundant andi burns one ugen ring temp (as1 deletes it)
            dmaBuf = scratchBuf;
            scratchBuf = (u8 *)scratchBuf + 0x3800;
        } else if (scratchBuf != NULL) {
            dmaBuf = (void *)0x80024000;
        } else {
            allocBuf = heapAlloc(*sizePtr);
            dmaBuf = allocBuf;
        }
    } else {
        dmaBuf = dst;
    }
    osInvalDCache(dmaBuf, *sizePtr);
    size = *sizePtr;
    count = 0; ptr = dmaBuf; while (count < ((u32)size >> 14)) { // LAYOUT: joined onto the loop header line (as1 preheader order)
        osPiStartDma(&D_807ECE00, 0, 0, romAddr, ptr, 0x4000, &D_807655F0);
        D_80746834 = 4;
        osRecvMesg(&D_807655F0, NULL, 1);
        D_80746834 = 0;
        count++;
        size = *sizePtr;
        romAddr += 0x4000;
        ptr = (u8 *)ptr + 0x4000;
    }
    rem = size - (((u32)size >> 14) << 14);
    if (rem != 0) {
        osPiStartDma(&D_807ECE00, 0, 0, romAddr, ptr, rem, &D_807655F0);
        D_80746834 = 5;
        osRecvMesg(&D_807655F0, NULL, 1);
        D_80746834 = 0;
    }
    D_807ECE18 = scratchBuf;
    if ((scratchBuf == NULL) && ((compressType == 1) || (compressType == 2))) {
        D_807ECE18 = heapAlloc(0x4000);
    }
    switch (compressType) {
    case 1:
        if (decompressFlag1) {
            gunzip(&dmaBuf, &dst, D_807ECE18);
        }
        if (decompressFlag2) {
            gunzip(&dmaBuf, &dst, D_807ECE18);
        }
        break;
    case 2:
        if (decompressFlag1) {
            func_80002790(&dmaBuf, &dst, D_807ECE18, decompressFlag1);
        }
        if (decompressFlag2) {
            func_80002790(&dmaBuf, &dst, D_807ECE18, decompressFlag2);
        }
        break;
    }
    if ((scratchBuf == NULL) && ((compressType == 1) || (compressType == 2))) {
        heapFree(D_807ECE18);
    }
    if (decompressFlag1 || decompressFlag2) {
        *sizePtr = (u8 *)dst - (u8 *)dstStart;
        if (scratchBuf == NULL) {
            heapFree(allocBuf);
        }
    }
}
