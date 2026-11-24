#include "common.h"
#include "proto/boot/30E0_gunzip.h"
#include "proto/global/15050_heap.h"
#include "proto/global/FE40_asset_dma.h"


extern s8 gWaitPointId;
extern OSMesgQueue gPiDmaMesgQueue;
extern OSIoMesg gPiDmaIoMesg;
extern void *sDecompressScratch;
void func_80002790(void *, void *, void *, s32);

void dmaReadAssetDecompress(u32 romAddr, void *dst, u32 *sizePtr, u8 decompressFlag1, u8 decompressFlag2, u8 compressType, void *scratchBuf) {
    s32 count;
    u8 useScratch;
    u8 *dmaBuf;
    u8 *dstStart;
    s32 rem;
    void *allocBuf;
    u8 *ptr;

    dstStart = dst;
    if (decompressFlag1 || decompressFlag2) {
        useScratch = decompressFlag1 & 0x80;
        if (useScratch) {
            dmaBuf = scratchBuf;
            scratchBuf = (u8 *)scratchBuf + 0x3800;
        } else if (scratchBuf != NULL) {
            dmaBuf = (u8 *)0x80024000;
        } else {
            allocBuf = heapAlloc(*sizePtr);
            dmaBuf = allocBuf;
        }
    } else {
        dmaBuf = dst;
    }
    osInvalDCache(dmaBuf, *sizePtr);
    count = 0; ptr = dmaBuf; while (count < (*sizePtr >> 14)) { // LAYOUT: joined onto the loop header line (as1 preheader order)
        osPiStartDma(&gPiDmaIoMesg, 0, 0, romAddr, ptr, 0x4000, &gPiDmaMesgQueue);
        gWaitPointId = 4;
        osRecvMesg(&gPiDmaMesgQueue, NULL, 1);
        gWaitPointId = 0;
        count++;
        romAddr += 0x4000;
        ptr += 0x4000;
    }
    rem = *sizePtr - ((*sizePtr >> 14) << 14);
    if (rem != 0) {
        osPiStartDma(&gPiDmaIoMesg, 0, 0, romAddr, ptr, rem, &gPiDmaMesgQueue);
        gWaitPointId = 5;
        osRecvMesg(&gPiDmaMesgQueue, NULL, 1);
        gWaitPointId = 0;
    }
    sDecompressScratch = scratchBuf;
    if ((scratchBuf == NULL) && ((compressType == 1) || (compressType == 2))) {
        sDecompressScratch = heapAlloc(0x4000);
    }
    switch (compressType) {
    case 1:
        if (decompressFlag1) {
            gunzip(&dmaBuf, &dst, sDecompressScratch);
        }
        if (decompressFlag2) {
            gunzip(&dmaBuf, &dst, sDecompressScratch);
        }
        break;
    case 2:
        if (decompressFlag1) {
            func_80002790(&dmaBuf, &dst, sDecompressScratch, decompressFlag1);
        }
        if (decompressFlag2) {
            func_80002790(&dmaBuf, &dst, sDecompressScratch, decompressFlag2);
        }
        break;
    }
    if ((scratchBuf == NULL) && ((compressType == 1) || (compressType == 2))) {
        heapFree(sDecompressScratch);
    }
    if (decompressFlag1 || decompressFlag2) {
        *sizePtr = (u8 *)dst - dstStart;
        if (scratchBuf == NULL) {
            heapFree(allocBuf);
        }
    }
}
