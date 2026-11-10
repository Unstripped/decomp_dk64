#include "common.h"
#include "sched.h"
#include "segment.h"
#include "proto/global/0.h"
#include "proto/global/131B0.h"
#include "proto/global/450.h"
#include "proto/global/6710.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct80744464;

extern u8 boot_VRAM[];
extern u8 boot_VRAM_END[];
extern u8 boot_BSS_START[];
extern u8 boot_BSS_END[];

extern u8 global_VRAM_END[];
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
s8 D_80744460 = 0;
Struct80744464 D_80744464 = { 0xF, 2, 0x1E };

// .bss 0x80761050-0x807655F0
OSMesgQueue D_80761050;
OSMesg D_80761068[0xF2];
OSThread D_80761430;
u8 D_807615E0[160];
u64 D_80761680;
u8 D_80761688[16216];
OSMesgQueue *D_807655E0;
u32 D_807655E4;
u64 D_807655E8;

// as1 schedules by source line: each segment entry stays on one line (matches the target store order)
void globalInit(OSMesgQueue *queue, s32 haltReason) {
    if (haltReason != 0) {
        mainThreadHalt(queue, haltReason);
    }
    D_807655E0 = queue;
    gSegmentTable[0].vramStart = (u32)boot_VRAM; gSegmentTable[0].vramEnd = (u32)boot_VRAM_END; gSegmentTable[0].bssStart = (u32)boot_BSS_START; gSegmentTable[0].bssEnd = (u32)boot_BSS_END;
    gSegmentTable[1].vramStart = (u32)globalInit; gSegmentTable[1].vramEnd = (u32)global_VRAM_END; gSegmentTable[1].bssStart = (u32)&D_80761050; gSegmentTable[1].bssEnd = (u32)global_BSS_END;
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
    osCreatePiManager(0x96, &D_80761050, D_80761068, 0xF2);
    D_80761680 = 0x12345678;
    osCreateThread(&D_80761430, 3, mainThreadLoop, NULL, &D_807655E0, 0xA);
    osStartThread(&D_80761430);
}


void mainThreadHalt(OSMesgQueue *queue, s32 haltCode) {
    u64 *p;
    u64 *q;
    Struct80744464 timeConfig;
    s32 pad[4];
    void *receivedMsg;

    timeConfig = D_80744464;
    if (haltCode == 2) {
        osViBlack(1);
        audioThreadStop(1);
        D_80744460 = 1;
        while (1) {
        }
    }
    osRecvMesg(queue, &receivedMsg, 1);
    D_80744460 = 1;
    audioThreadStop(1);
    osStopThread(&D_80761430);
    p = &D_807655E8;
    osSetThreadPri(NULL, 0xB);
    D_807655E8 = osGetTime();
    while (osGetTime() < *(q = p) + 0x22ADD7) { // FAKE: second pointer copy, see above
    }
    osViBlack(1);
    __osSpSetStatus(0xAAAA82);
    osDpSetStatus(0x1D6);
    rumbleShutdown();
    while (1) {
    }
}
