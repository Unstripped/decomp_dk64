#include "common.h"

typedef struct {
    u32 romStart;
    u32 romEnd;
    u32 vramStart;
    u32 vramEnd;
    u32 bssStart;
    u32 bssEnd;
} SegmentTableEntry;

typedef struct {
    u32 v[3];
} ViModeIdx;

extern SegmentTableEntry gSegmentTable[18];
extern s8 sBootResetState;
extern u32 sAudioFreq;
extern ViModeIdx sBootViMode;
extern OSMesgQueue sResetMesgQueue;
extern OSMesg sResetMesgBuf[10];
extern OSThread sResetThread;
extern OSThread sMainThread;
extern u8 D_800138C0[];

extern u8 boot_ROM_START[];
extern u8 boot_ROM_END[];
extern u8 global_ROM_START[];
extern u8 global_ROM_END[];
extern u8 multiplayer_ROM_START[];
extern u8 multiplayer_ROM_END[];
extern u8 minecart_ROM_START[];
extern u8 minecart_ROM_END[];
extern u8 bonus_ROM_START[];
extern u8 bonus_ROM_END[];
extern u8 race_ROM_START[];
extern u8 race_ROM_END[];
extern u8 critter_ROM_START[];
extern u8 critter_ROM_END[];
extern u8 boss_ROM_START[];
extern u8 boss_ROM_END[];
extern u8 arcade_ROM_START[];
extern u8 arcade_ROM_END[];
extern u8 jetpac_ROM_START[];
extern u8 jetpac_ROM_END[];
extern u8 menu_ROM_START[];
extern u8 menu_ROM_END[];
extern u8 seg11_ROM_START[];
extern u8 seg11_ROM_END[];
extern u8 seg12_ROM_START[];
extern u8 seg12_ROM_END[];
extern u8 seg13_ROM_START[];
extern u8 seg13_ROM_END[];
extern u8 seg14_ROM_START[];
extern u8 seg14_ROM_END[];
extern u8 seg15_ROM_START[];
extern u8 seg15_ROM_END[];
extern u8 seg16_ROM_START[];
extern u8 seg16_ROM_END[];
extern u8 seg17_ROM_START[];
extern u8 seg17_ROM_END[];
extern u8 rspboot_ROM_START[];
extern u8 rspboot_ROM_END[];
extern u8 global_LOAD_START[];
extern u8 global_LOAD_END[];
extern u8 seg11_FALLBACK_START[];
extern u8 seg11_FALLBACK_END[];

void gunzip(void *, void *, u32);
void noExpPakScreen(void);
void decompressGlobal(void *, void *);
void bootResetThread(void *);
void bootMainThread(void *);
void bootStartMainThread(void);

void dmaCopy(u32 romStart, u32 romEnd, void *dest) {
    u32 size = romEnd - romStart;

    osInvalDCache(dest, size);
    osPiRawStartDma(OS_READ, romStart, dest, size);
    do {
    } while (osPiGetStatus() & PI_STATUS_DMA_BUSY);
}

void decompressGlobal(void *a, void *b) {
    gunzip(a, b, 0x804FAE00);
    gunzip(a, b, 0x804FAE00);
}

void bootResetThread(void *arg) {
    s32 msg;
    s32 pad;

    osRecvMesg(&sResetMesgQueue, (OSMesg *)&msg, OS_MESG_BLOCK);
    switch (msg) {
    case 0x29D:
        if (sBootResetState != 0) {
            ((void (*)(OSMesgQueue *, s32))0x805FB300)(&sResetMesgQueue, 2);
        } else {
            osViBlack(1);
            for (;;) {}
        }
        break;
    case 0x309:
        osSetThreadPri(NULL, 0x12);
        ((void (*)(OSMesgQueue *, s32))0x805FB300)(&sResetMesgQueue, 1);
        for (;;) {}
        break;
    }
}

#define SEG(i, n) gSegmentTable[i].romStart = (u32)n##_START; gSegmentTable[i].romEnd = (u32)n##_END;

void bootMainThread(void *arg) {
    void *src;
    void *dst;
    u32 pad;
    ViModeIdx viModes = sBootViMode;

    osCreateMesgQueue(&sResetMesgQueue, sResetMesgBuf, 10);
    osSetEventMesg(OS_EVENT_PRENMI, &sResetMesgQueue, (OSMesg)0x29D);
    osCreateThread(&sResetThread, 11, bootResetThread, NULL, &sMainThread, 100);
    osStartThread(&sResetThread);
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[viModes.v[osTvType]]);
    osViBlack(1);
    if (osMemSize < 0x800000 || osTvType == 0) {
        SEG(11, seg11_FALLBACK)
        noExpPakScreen();
    } else {
        dmaCopy((u32)rspboot_ROM_START, (u32)rspboot_ROM_END, (void *)0x805FB000);
        sAudioFreq = osAiSetFrequency(0x5622);
        bzero((void *)0x805FB300, 0x204D00);
        src = (void *)0x80020000;
        dst = (void *)0x805FB300;
        dmaCopy((u32)global_LOAD_START, (u32)global_LOAD_END, src);
        decompressGlobal(&src, &dst);
        osInvalICache((void *)0x805FB300, (u32)dst - 0x805FB300);
        osWritebackDCacheAll();
        SEG(0, boot_ROM)
        SEG(1, global_ROM)
        SEG(2, multiplayer_ROM)
        SEG(3, minecart_ROM)
        SEG(4, bonus_ROM)
        SEG(5, race_ROM)
        SEG(6, critter_ROM)
        SEG(7, boss_ROM)
        SEG(8, arcade_ROM)
        SEG(9, jetpac_ROM)
        SEG(10, menu_ROM)
        SEG(11, seg11_ROM)
        SEG(12, seg12_ROM)
        SEG(13, seg13_ROM)
        SEG(14, seg14_ROM)
        SEG(15, seg15_ROM)
        SEG(16, seg16_ROM)
        SEG(17, seg17_ROM)
        osSetThreadPri(NULL, 0);
        sBootResetState = 1;
        ((void (*)(OSMesgQueue *, s32))0x805FB300)(&sResetMesgQueue, 0);
    }
    for (;;) {}
}

void bootStartMainThread(void) {
    osCreateThread(&sMainThread, 1, bootMainThread, NULL, D_800138C0, 0);
    osStartThread(&sMainThread);
}

void bootMain(void) {
    u32 *p;
    u32 *q;

    osInitialize();
    p = (u32 *)0xA02FE1C0;
    q = (u32 *)0xA02FE1C0;
    if (*p != 0xAD170014) {
        do {
        } while (*q != 0xAD170014);
    }
    *p = 0xF0F0F0F0;
    bootStartMainThread();
}
