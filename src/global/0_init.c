#include "common.h"
#include "PR/os_internal_rsp.h"
#include "sched.h"
#include "segment.h"
#include "proto/global/0_init.h"
#include "proto/global/131B0_rumble.h"
#include "proto/global/450_main_loop.h"
#include "proto/global/6710_audio_thread.h"

typedef struct {
    s32 palViMode;
    s32 ntscViMode;
    s32 mpalViMode;
} Struct80744464;

extern u8 boot_VRAM[];
extern u8 boot_VRAM_END[];
extern u8 boot_BSS_START[];
extern u8 boot_BSS_END[];

extern u8 global_VRAM[];
extern u8 global_VRAM_END[];
extern u8 global_BSS_START[];
extern u8 global_BSS_END[];

extern u8 multiplayer_BSS_END[];
extern u8 multiplayer_BSS_START[];
extern u8 multiplayer_VRAM_END[];
extern u8 multiplayer_VRAM[];

extern u8 minecart_VRAM_END[];
extern u8 minecart_VRAM[];
extern u8 minecart_BSS_END[];
extern u8 minecart_BSS_START[];

extern u8 bonus_BSS_START[];
extern u8 bonus_BSS_END[];
extern u8 bonus_VRAM_END[];
extern u8 bonus_VRAM[];

extern u8 race_BSS_START[];
extern u8 race_BSS_END[];
extern u8 race_VRAM[];
extern u8 race_VRAM_END[];

extern u8 critter_BSS_START[];
extern u8 critter_BSS_END[];
extern u8 critter_VRAM[];
extern u8 critter_VRAM_END[];

extern u8 boss_BSS_END[];
extern u8 boss_BSS_START[];
extern u8 boss_VRAM_END[];
extern u8 boss_VRAM[];

extern u8 arcade_VRAM_END[];
extern u8 arcade_VRAM[];
extern u8 arcade_BSS_END[];
extern u8 arcade_BSS_START[];

extern u8 jetpac_BSS_START[];
extern u8 jetpac_BSS_END[];
extern u8 jetpac_VRAM_END[];
extern u8 jetpac_VRAM[];

extern u8 menu_BSS_START[];
extern u8 menu_BSS_END[];
extern u8 menu_VRAM[];
extern u8 menu_VRAM_END[];

// .data 0x80744460-0x80744470
s8 gMainThreadHalted = 0;
Struct80744464 gLowResViModeByTvType = { OS_VI_PAL_LPF1, OS_VI_NTSC_LAN1, OS_VI_MPAL_LAN1 }; // low-res VI mode per osTvType (OS_TV_PAL, OS_TV_NTSC, OS_TV_MPAL)

// .bss 0x80761050-0x807655F0
OSMesgQueue gPiMgrCmdQueue;
OSMesg gPiMgrCmdMesgs[0xF2];
OSThread gMainThread;
u8 D_807615E0[160];
u64 gMainThreadStackSentinel;
u8 gMainThreadStack[16216];
OSMesgQueue *gBootResetQueue;
u32 D_807655E4;

// LAYOUT: as1 schedules by source line: each segment entry stays on one line (one statement per line reorders the target's stores)
void globalInit(OSMesgQueue *queue, s32 haltReason) {
    if (haltReason != 0) {
        mainThreadHalt(queue, haltReason);
    }
    gBootResetQueue = queue;
    gSegmentTable[0].vramStart = (u32)boot_VRAM; gSegmentTable[0].vramEnd = (u32)boot_VRAM_END; gSegmentTable[0].bssStart = (u32)boot_BSS_START; gSegmentTable[0].bssEnd = (u32)boot_BSS_END;
    gSegmentTable[1].vramStart = (u32)global_VRAM; gSegmentTable[1].vramEnd = (u32)global_VRAM_END; gSegmentTable[1].bssStart = (u32)global_BSS_START; gSegmentTable[1].bssEnd = (u32)global_BSS_END;
    gSegmentTable[2].vramStart = (u32)multiplayer_VRAM; gSegmentTable[2].vramEnd = (u32)multiplayer_VRAM_END; gSegmentTable[2].bssStart = (u32)multiplayer_BSS_START; gSegmentTable[2].bssEnd = (u32)multiplayer_BSS_END;
    gSegmentTable[3].vramStart = (u32)minecart_VRAM; gSegmentTable[3].vramEnd = (u32)minecart_VRAM_END; gSegmentTable[3].bssStart = (u32)minecart_BSS_START; gSegmentTable[3].bssEnd = (u32)minecart_BSS_END;
    gSegmentTable[4].vramStart = (u32)bonus_VRAM; gSegmentTable[4].vramEnd = (u32)bonus_VRAM_END; gSegmentTable[4].bssStart = (u32)bonus_BSS_START; gSegmentTable[4].bssEnd = (u32)bonus_BSS_END;
    gSegmentTable[5].vramStart = (u32)race_VRAM; gSegmentTable[5].vramEnd = (u32)race_VRAM_END; gSegmentTable[5].bssStart = (u32)race_BSS_START; gSegmentTable[5].bssEnd = (u32)race_BSS_END;
    gSegmentTable[6].vramStart = (u32)critter_VRAM; gSegmentTable[6].vramEnd = (u32)critter_VRAM_END; gSegmentTable[6].bssStart = (u32)critter_BSS_START; gSegmentTable[6].bssEnd = (u32)critter_BSS_END;
    gSegmentTable[7].vramStart = (u32)boss_VRAM; gSegmentTable[7].vramEnd = (u32)boss_VRAM_END; gSegmentTable[7].bssStart = (u32)boss_BSS_START; gSegmentTable[7].bssEnd = (u32)boss_BSS_END;
    gSegmentTable[8].vramStart = (u32)arcade_VRAM; gSegmentTable[8].vramEnd = (u32)arcade_VRAM_END; gSegmentTable[8].bssStart = (u32)arcade_BSS_START; gSegmentTable[8].bssEnd = (u32)arcade_BSS_END;
    gSegmentTable[9].vramStart = (u32)jetpac_VRAM; gSegmentTable[9].vramEnd = (u32)jetpac_VRAM_END; gSegmentTable[9].bssStart = (u32)jetpac_BSS_START; gSegmentTable[9].bssEnd = (u32)jetpac_BSS_END;
    gSegmentTable[10].vramStart = (u32)menu_VRAM; gSegmentTable[10].vramEnd = (u32)menu_VRAM_END; gSegmentTable[10].bssStart = (u32)menu_BSS_START; gSegmentTable[10].bssEnd = (u32)menu_BSS_END;
    osDpSetStatus(4);
    osCreatePiManager(OS_PRIORITY_PIMGR, &gPiMgrCmdQueue, gPiMgrCmdMesgs, 0xF2);
    gMainThreadStackSentinel = 0x12345678;
    osCreateThread(&gMainThread, 3, mainThreadLoop, NULL, gMainThreadStack + sizeof(gMainThreadStack), 0xA);
    osStartThread(&gMainThread);
}


void mainThreadHalt(OSMesgQueue *queue, s32 haltReason) {
    static OSTime sHaltStartTime;
    s32 pad[2];
    Struct80744464 unused = gLowResViModeByTvType; // ORIG: the target copies gLowResViModeByTvType into sp+0x34 (lw/sw at 0x2d4-0x2f0) and never reads it
    s32 pad2[4];
    OSMesg msg;
    s32 pad3[2];

    if (haltReason == 2) {
        osViBlack(TRUE);
        audioThreadStop(1);
        gMainThreadHalted = TRUE;
        while (TRUE) {}
    }
    osRecvMesg(queue, &msg, OS_MESG_BLOCK);
    gMainThreadHalted = TRUE;
    audioThreadStop(1);
    osStopThread(&gMainThread);
    osSetThreadPri(NULL, 11);
    sHaltStartTime = osGetTime();
    while (osGetTime() < sHaltStartTime + 0x22ADD7) {}
    osViBlack(TRUE);
    __osSpSetStatus(0xAAAA82);
    osDpSetStatus(0x1D6);
    rumbleShutdown();
    while (TRUE) {}
}
