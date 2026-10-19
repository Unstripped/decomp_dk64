#include "common.h"

void dmaCopy(u32 romStart, u32 romEnd, void *dest) {
    u32 size = romEnd - romStart;

    osInvalDCache(dest, size);
    osPiRawStartDma(OS_READ, romStart, dest, size);
    do {
    } while (osPiGetStatus() & PI_STATUS_DMA_BUSY);
}

#pragma GLOBAL_ASM("asm/nonmatchings/boot/main/func_800004B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/boot/main/func_800004F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/boot/main/func_800005A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/boot/main/func_80000980.s")

#pragma GLOBAL_ASM("asm/nonmatchings/boot/main/func_800009D0.s")
