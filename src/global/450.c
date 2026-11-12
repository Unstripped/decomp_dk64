#include "common.h"
#include "actor.h"
#include "render.h"
#include "sched.h"
#include "segment.h"
#include "proto/boot/30E0.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/103AB0.h"
#include "proto/global/109660.h"
#include "proto/global/10D2D0.h"
#include "proto/global/10E1D0.h"
#include "proto/global/112080.h"
#include "proto/global/114270.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/126260.h"
#include "proto/global/127B00.h"
#include "proto/global/1295B0.h"
#include "proto/global/1332B0.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/136820.h"
#include "proto/global/13980.h"
#include "proto/global/14CF0.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/2DE90.h"
#include "proto/global/2F550.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/450.h"
#include "proto/global/5230.h"
#include "proto/global/55B20.h"
#include "proto/global/5650.h"
#include "proto/global/5A50.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/63EC0.h"
#include "proto/global/684C0.h"
#include "proto/global/68AA0.h"
#include "proto/global/68EA0.h"
#include "proto/global/699B0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8D3E0.h"
#include "proto/global/8F050.h"
#include "proto/global/8F4B0.h"
#include "proto/global/90D80.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/global/FE40.h"

void func_80024000(void);
void func_80026FD0(void *);
void func_8002EC08(s32);

extern u8 D_1000020[];
extern u8 D_1000030[];
extern u8 D_1000040[];
extern u8 D_1000068[];
extern u8 D_1000090[];
extern u8 D_2000000[];
extern u8 D_2000180[];
extern u8 D_2000200[];

extern s32 D_8000DDCC;
extern s32 D_8000DDE4;

extern u8 D_8074458B[][4];

extern u8 D_80745BDC[][4];
extern s8 D_807467CC;
extern u8 D_807467E4;
extern s8 D_80746830;
extern s8 gPlayerCharacterId;
extern s32 D_80750AB0;
extern u8 gSplitScreenMode;
extern u8 gActivePlayerCount;
extern s16 D_80750AC4;

extern s32 D_8076A058;
extern s16 gCurrentLevelIndex;
extern u8 D_8076AEE0;

extern OSIoMesg D_807ECE00;
extern s16 *D_807ECDF4;
extern s8 D_807F6008;
extern s32 D_807F6010;
extern u32 gGlobalOverlayFlags;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s32 D_807FF100;

extern s8 D_80744460;
extern u64 D_80761680;
extern OSMesgQueue *D_807655E0;

// .data 0x80744470-0x807445E0
u16 *gFramebuffers[2] = { 0 };
u32 gFrameDelta = 2;
u8 gViewportInsetLeft = 0;
u8 gViewportInsetRight = 0;
u8 gViewportInsetTop = 0;
u8 gViewportInsetBottom = 0;
u8 gViewportInsetActive = 0;
s16 gScreenWidth = 0x140;
s16 gScreenHeight = 0xF0;
s16 gGfxScreenLeft = 0xA;
s16 gGfxScreenTop = 0xA;
s16 gGfxScreenRight = 0x135;
s16 gGfxScreenBottom = 0xE5;
s16 D_807444A8 = 0xA;
s16 D_807444AC = 0x28;
s16 D_807444B0 = 0xC7;
s16 D_807444B4 = 0xE5;
f32 gGfxFovY = 45.0f;
f32 gGfxAspect = 1.0f;
s8 D_807444C0 = 0;
f32 gGfxFarClip = 1500.0f;
f32 gGfxNearClip = 10.0f;
f32 D_807444CC = 1.0f;
f32 D_807444D0 = 1.0f;
f32 D_807444D4 = 1.0f;
f32 D_807444D8 = 1.0f;
f32 D_807444DC = 1.0f;
f32 func_807444E0 = 1.0f;
s32 gInitialMap = 0x28;
s32 gInitialExit = 0;
u8 gGameMode = 0;
u8 D_807444F0 = 0;
u8 D_807444F4 = 0;
u8 gNextGameMode = 0;
u8 gGfxBufferIndex = 0;
s8 D_80744500 = 0;
s8 D_80744504 = 0;
s16 D_80744508 = 0;
u8 gHiResScale = 1;
u8 D_80744510[28] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 };
s8 D_8074452C = 0;
u32 D_80744530[5] = { 0 };
u32 D_80744544 = 0;
u32 D_80744548[8] = { 0x644141, 0x4100005A, 0x41414100, 0x504141, 0x41000046, 0x41414100, 0x3C4141, 0x41000000 };
u32 D_80744568[8] = { 0x644141, 0x4100005A, 0x41414100, 0x504141, 0x41000046, 0x41414100, 0x464141, 0x41000000 };
u32 D_80744588[6] = { 0xF, 0x19, 2, 0xA, 0x1E, 0x26 };
s8 D_807445A0 = 0;
s8 D_807445A4 = 1;
u32 D_807445A8[2] = { 0 };
u64 D_807445B0 = 0;
u64 D_807445B8 = 0;
u64 D_807445C0 = 0;
s8 D_807445C8 = 0;
s32 D_807445CC[5] = { 0, 0x4B0, 0, 0, 0 };

// .bss 0x807655F0-0x8076A160
OSMesgQueue D_807655F0;
OSMesg D_80765608;
u32 D_8076560C;
u8 D_80765610[192];
OSMesgQueue D_807656D0;
OSMesg D_807656E8;
u32 D_807656EC;
u8 D_807656F0[760];
OSMesgQueue D_807659E8;
OSMesg D_80765A00[0x810];
SchedStruct gScheduler;
SchedClient D_80767CD8;
FrameMatrices D_80767CE8[2];
FrameMatrices *gGfxCurrentFrameBuffer;
u32 D_8076A04C;
Gfx *gGfxTaskBuffers[4];
u8 *gGfxDepthBuffer;
s32 gFrameCounter;
s32 gGameFrameCounter;
s32 D_8076A06C;
s32 D_8076A070[3];
s32 D_8076A07C;
void *D_8076A080;
s32 D_8076A084;
s32 D_8076A088;
s32 D_8076A08C;
s32 D_8076A090;
s32 D_8076A094;
s32 D_8076A098;
u16 D_8076A09C;
u16 D_8076A09E;
s16 *D_8076A0A0;
u8 D_8076A0A4;
u8 D_8076A0A5;
u16 D_8076A0A6;
s32 gCurrentMap;
s32 D_8076A0AC;
u8 D_8076A0B0;
u8 gScreenRenderFlags;
u8 D_8076A0B2;
u8 sHudDisabled;
f32 *D_8076A0B4;
f32 *D_8076A0B8;
f32 *D_8076A0BC;
f32 *D_8076A0C0;
f32 *D_8076A0C4;
f32 *D_8076A0C8;
u32 D_8076A0CC;
u8 D_8076A0D0[48];
u32 D_8076A100;
u8 D_8076A104;
s8 D_8076A105;
u16 D_8076A106;
OSMesg D_8076A108;
u32 D_8076A10C;
OSMesgQueue D_8076A110;
OSMesg D_8076A128;
u32 D_8076A12C;
OSTimer D_8076A130;
void *D_8076A150;
u32 D_8076A154;

void seg11DmaRead(s32 romOffset, s32 size, void *dst) {
    s32 romBase;

    romBase = D_8000DDCC;
    osWritebackDCache(dst, size);
    osPiStartDma(&D_807ECE00, 0, 0, romBase + romOffset, dst, (u32) size, &D_807655F0);
    osRecvMesg(&D_807655F0, NULL, 1);
    osInvalDCache(dst, size);
}

void viModeApplyHighRes(void) {
    u16 *fb;
    u16 *end;
    void *pad0;
    void *pad1;
    u16 *src;
    u8 *compressedBuf;
    void *pad2;
    void *pad3;
    u8 *gzipSrc;
    u8 *gzipDst;
    s32 i;
    s32 j;

    fb = gFramebuffers[0];
    end = (u16 *)((u8 *)fb + 0x25800);
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();

    compressedBuf = (u8 *)gFramebuffers[1] + 0xC800;
    seg11DmaRead(0x38, 0x10, compressedBuf);
    seg11DmaRead(*(s32 *)compressedBuf + 0x178, 0x10, compressedBuf);
    seg11DmaRead(*(s32 *)compressedBuf, *(s32 *)(compressedBuf + 4) - *(s32 *)compressedBuf, compressedBuf);

    gzipSrc = compressedBuf;
    gzipDst = (u8 *)gFramebuffers[1];
    src = gFramebuffers[1];
    gunzip(&gzipSrc, &gzipDst, (u8 *)gFramebuffers[1] + 0x15E00);

    fb = (u16 *)((u8 *)gFramebuffers[0] + 0xF080);
    i = 0;
    do {
        j = 0;
        for (;;) {
            *fb++ = *src++;
            *fb++ = *src++;
            *fb++ = *src++;
            *fb++ = *src++;
            j += 4;
            if (j == 0xC0) {
                break;
            }
        }
        fb = (u16 *)((u8 *)fb + 0x100);
        i++;
    } while (i < 0x30);

    fb = gFramebuffers[1];
    end = (u16 *)((u8 *)fb + 0x25800);
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();
}



void viModeSetup(u8 overlaySlot) {
    u8 overlayId;
    s32 overlayParam;

    overlayId = 1;
    overlayParam = 0;
    func_806003EC(gCurrentLevelIndex);
    if (D_807445A4 && D_807445A4) {}  // FAKE: deadsweep dead statement (steers uopt; keeps the D_807445A4 address out of a register)
    if (gCurrentMap == 0x28) {
        gHiResScale = 2;
    } else {
        gHiResScale = 1;
    }
    switch (gGameMode) {
    case 3:
        overlayId = 9;
    case 4:
        if (overlayId == 1) {
            overlayId = 10;
        }
        gGfxScreenLeft = 0;
        gGfxScreenTop = 0;
        gGfxScreenRight = gHiResScale * 0x140 - 1;
        gGfxScreenBottom = gHiResScale * 0xF0 - 1;
        break;
    default:
        overlayParam = func_8060042C(gCurrentMap);
        if (gGlobalOverlayFlags & 1) {
            overlayId = 7;
        } else if (gGlobalOverlayFlags & 0x1000) {
            overlayId = 6;
        } else if (gGlobalOverlayFlags & 0x104000) {
            overlayId = 8;
        } else if (gGlobalOverlayFlags & 0x80000) {
            overlayId = 4;
        } else if (gGlobalOverlayFlags & 0x2000) {
            overlayId = 5;
        } else if (gGlobalOverlayFlags & 0x4000000) {
            overlayId = 3;
        } else if (gGlobalOverlayFlags & 0x40000000) {
            overlayId = 2;
        }
        gGfxScreenLeft = gHiResScale * 10;
        gGfxScreenTop = gHiResScale * 10;
        gGfxScreenRight = gHiResScale * 0x136 - 1;
        gGfxScreenBottom = gHiResScale * 0xE6 - 1;
        break;
    }
    loadOverlay(overlaySlot, overlayId, overlayParam);
    if (D_807445A4 == 0) {
        osViSetMode(&osViModeTable[D_80744588[osTvType + osTvType + gHiResScale - 1]]);
        if (D_807445A0 == 0) {
            osViBlack(1);
        }
        D_80744510[0] = 0;
        D_807445A0 = 0;
    } else {
        D_80744510[0] = 1;
        D_807445A0 = 1;
        D_807445A4 = 0;
        viModeApplyHighRes();
    }
    osViSetSpecialFeatures(0x42);
    gScreenWidth = gHiResScale * 0x140;
    gScreenHeight = gHiResScale * 0xF0;
    D_807444AC = gGfxScreenTop + gHiResScale * 0x1E;
    D_807444B0 = gGfxScreenBottom - gHiResScale * 0x1E;
    D_807444A8 = gGfxScreenTop;
    D_807444B4 = gGfxScreenBottom;
}

void mainSystemInit(void) {
    D_8076A084 = gSegmentTable[12].romEnd - gSegmentTable[12].romStart;
    osCreateMesgQueue(&D_807655F0, &D_80765608, 0x32);
    osCreateMesgQueue(&D_807656D0, &D_807656E8, 0xC0);
    schedCreate(&gScheduler, &D_80765A00[0x810], 0x19, D_8074458B[osTvType + osTvType][0], 1); // FAKE: osTvType + osTvType gives the two sll-by-2 + addu index into D_8074458B (osTvType * 2 folds to one sll by 3)
    osCreateMesgQueue(&D_807659E8, D_80765A00, 0x10);
    schedAddClient(&gScheduler, &D_80767CD8, &D_807659E8, 1, 1);
    gCurrentMap = gInitialMap;
    viModeSetup(0);
    D_8076A07C = 5;
    func_8060FFF0();
    controllerInit();
    audioInit();
    transitionSetState(0);
    faultThreadInit();
    osWritebackDCacheAll();
    osCreateMesgQueue(&D_8076A110, &D_8076A108, 2);
    osSetTimer(&D_8076A130, 0xD693A4, 0, &D_8076A110, D_8076A128);
    sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
}

void mainResetEngineState(void) {
    s32 pad;
    f32 aspectScale;

    osWritebackDCacheAll();
    osInvalDCache((void *)0x80000000, 0x800000);
    D_8076A080 = &D_807FF100;
    dmaReadAssetDecompress(D_8000DDE4, D_8076A080, &D_8076A084, 0, 0, 0, 0);
    D_8076A0A4 = 0;
    controllerWaitRead();
    gFrameCounter = 0;
    gGameFrameCounter = 0;
    D_807467CC = 0;
    D_8076A0AC = 4;
    gGlobalPauseFlags = 0x30030;
    gScreenRenderFlags |= 1;
    D_8076A0B2 = 0;
    gScreenFadeProgress = 31.0f;
    gScreenRenderFlags |= 4;
    modelSkipListClear();
    playerResetSpawnGlobals();
    flagsClearAllBank2();
    mapSlotArrayInit();
    csTimerQueueClear();
    aspectScale = cameraStepAspectScale();
    guTranslate(&D_80767CE8[0].identity, 0.0f, 0.0f, 0.0f);
    guTranslate(&D_80767CE8[1].identity, 0.0f, 0.0f, 0.0f);
    guPerspective(&D_80767CE8[0].perspective, &D_8076A09C, gGfxFovY, gGfxAspect * aspectScale, gGfxNearClip, gGfxFarClip, 1.0f);
    guPerspective(&D_80767CE8[1].perspective, &D_8076A09C, gGfxFovY, gGfxAspect * aspectScale, gGfxNearClip, gGfxFarClip, 1.0f);
}

extern s16 D_8074682C;
extern u8 D_807F059C;

void mainThreadLoop(s32 unused) {
    u8 first;
    OSMesg receivedMesg;

    first = 1;
    if (osTvType == 0) {
        gGfxAspect = 1.25f;
    }
    mainSystemInit();
    osViSetSpecialFeatures(0x42);
    mainResetEngineState();
    D_8076A070[0] = gScheduler.unk280 - 2;
    osRecvMesg(&D_8076A110, &receivedMesg, 1);
    while (1) {
        D_8074682C = 0xC8;
        while (D_80744460 != 0) {
        }
        if ((gScreenRenderFlags & 1) && D_8076A0B2 == 0) {
            mapLoadLevel();
            if (gNextGameMode == 2) {
                gGlobalPauseFlags |= 0x200;
                D_80744504 = 8;
            }
        }
        switch (gGameMode) {
            case 6:
                transitionRunFrame(gInitialMap, gInitialExit);
                break;
            case 3:
                func_80024000();
                break;
            case 4:
                func_80024000();
                break;
            case 5:
                break;
            default:
                gfxSubmitFrame();
                break;
        }
        timerQueueUpdate();
        dmaDrainQueueAndFreeBuffer();
        func_80610268(0x4D2);
        if (D_807F059C != 0) {
            func_80610268(0x929);
        }
        frameTimingUpdate();
        if (gGameMode == 0 || gGameMode == 1 || gGameMode == 7) {
            mapSearchTableUpdateVisibility();
            func_80700BF4();
        }
        heapTickDeferredFrees();
        if (D_80761680 != 0x12345678) {
            faultSetMessage(2, 0, 0, 0);
        }
        if (first != 0) {
            osSendMesg(D_807655E0, (OSMesg)0x309, 1);
            first = 0;
        }
        if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
            D_8076A0B2--;
        }
        D_807444F0 = gGameMode;
    }
}

void gfxSubmitFrame(void) {
    Gfx *glist;
    Gfx *gfxEnd;

    controllerStartRead();
    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], D_8076A088, 3, (D_8076A0A4 != 0) ? 0 : 1, 0x4D2, 1);
    if (D_8076A0A4 != 0) {
        schedSubmitGfxTask(D_80767CE8[gGfxBufferIndex].subDisplayList, D_8076A08C, 0, 1, 0x929, 1);
    }
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    if (!(gGlobalPauseFlags & 2)) {
        gGameFrameCounter++;
    }
    gGfxCurrentFrameBuffer = &D_80767CE8[gGfxBufferIndex];
    controllerUpdate();
    if (pauseStateUpdate() != 0) {
        billboardCacheEvictStale();
        actorUpdateWhilePaused();
        effectUpdateAll(1);
        sfxUpdateLevelAmbient();
        sfxUpdateSourceGroups();
        sfxUpdateChannels();
        playerViewsBuildMatrices(gGfxCurrentFrameBuffer);
    } else {
        lightClearCount();
        actorUpdateSpawnsWrapper();
        playerViewsBuildMatrices(gGfxCurrentFrameBuffer);
        billboardCacheEvictStale();
        actorProximityUpdate();
        collisionBufferCacheUpdate();
        modelSlotExpireNextBuffers();
        effectUpdateAndDispatch();
        actorGlobalCallbacksReset();
        triggerZoneUpdate();
        effectUpdateAll(0);
        sfxUpdateLevelAmbient();
        sfxUpdateChannels();
        sfxUpdateSourceGroups();
        gridTickPlayers();
    }
    resListTick();
    D_8076A150 = gGfxTaskBuffers[gGfxBufferIndex];
    if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
        glist = gGfxTaskBuffers[gGfxBufferIndex];
        gfxEnd = gGfxCurrentFrameBuffer->subDisplayList;
        renderCallbacksReset();
    } else {
        gfxBuildFrameDisplayLists(gGfxCurrentFrameBuffer, &glist, &gfxEnd);
    }
    if (gGlobalPauseFlags & 0x100) {
        gGlobalPauseFlags &= ~0x100;
        func_807094D0(2, &gGlobalPauseFlags);
    } else if (gGlobalPauseFlags & 0x200) {
        D_80744504--;
        if (D_80744504 == 0) {
            gGlobalPauseFlags &= ~0x200;
            func_807094D0(3, &gGlobalPauseFlags);
        }
    } else {
        glist = screenFadeUpdate(glist, D_8076AEE0);
    }
    if (D_8076A0A4 != 0 && gGameMode != 6) {
        gfxEndDisplayList(glist, gGfxBufferIndex, &D_8076A088, 0);
        gfxEndSubDisplayList(gfxEnd, gGfxCurrentFrameBuffer, &D_8076A08C, 1);
    } else {
        gfxEndDisplayList(glist, gGfxBufferIndex, &D_8076A088, 1);
    }
}


extern Actor *gSpawnedActor;

s32 pauseStateUpdate(void) {
    Actor *actor;

    if ((gCurrentMap == 0x50) || (menuIsTransitionType8() == 0 && menuIsTransitionType6() == 0 && menuIsTransitionTypeC() == 0 && menuIsTransitionTypeD() == 0)) {
        gGlobalPauseFlags &= ~1;
    }
    if (gGlobalPauseFlags & 2) {
        if ((gGlobalPauseFlags & 0x40) && (menuIsTransitionType6() != 0 || menuIsTransitionTypeC() != 0)) {
            sfxStopChannel(0x22, 0);
            gGlobalPauseFlags &= 0xFFEBFFBD;
            actor = actorFindByType((gPlayerCount < 2 && menuIsTransitionTypeC() == 0) ? 0x5F : 0x157);
            if (actor != NULL) {
                actorDespawn(actor);
            }
            D_807445B0 = osGetTime() - D_807445C0;
            slotQueuePopActiveMask();
        }
    } else {
        D_807445B8 += D_807445B0;
        D_807445B0 = 0;
        D_807445C0 = 0;
        if (D_807445C8 > 0) {
            if (!(gGlobalPauseFlags & 1)) {
                D_807445C8 = 0;
            } else {
                D_807445C8 -= 1;
                if (D_807445C8 <= 0) {
                    if ((menuIsTransitionType6() != 0 || menuIsTransitionTypeC() != 0) && !(gGlobalPauseFlags & 0x40000)) {
                        sfxAllocateChannel(0x22, 1.0f);
                        sfxAllocateChannel(0x29, 1.0f);
                        if (gPlayerCount < 2 && menuIsTransitionTypeC() == 0) {
                            actorSpawn(0x5F, 0);
                            gGlobalPauseFlags |= 0x100000;
                        } else {
                            actorSpawn(0x157, 0);
                        }
                        gSpawnedActor->renderFlags |= 2;
                    }
                    D_807445C0 = osGetTime();
                    gGlobalPauseFlags ^= 1;
                    gGlobalPauseFlags |= 2;
                }
            }
        }
        if ((gGlobalPauseFlags & 1) && D_807445C8 <= 0) {
            slotQueueReset();
            D_807445C8 = 2;
        }
    }
    return gGlobalPauseFlags & 2;
}

s32 gfxSetupFrameViewports(void) {
    u64 t;
    u64 x;

    t = osGetTime();
    x = t - D_807445B8;
    if (gGlobalPauseFlags & 2) {
        x = x - t + D_807445C0;
    }
    x = x * 0x40 / 0xBB8 / 0xF4240;
    return (u32) x + D_80750AB0;
}

s32 hudCanRender(void) {
    s32 canRenderHud;

    canRenderHud = (gScreenRenderFlags & 0x10) == 0;
    if (canRenderHud != 0) {
        canRenderHud = sHudDisabled == 0;
    }
    return canRenderHud & 0xFF;
}

extern u8 gViewportCount;
f32 sinApprox(f32);

typedef struct {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} PlayerActorData;

typedef struct {
    u8 unk0;
    u8 pad1[3];
    Actor *unk4;
    Mtx unk8[2];
    Mtx unk88[2];
    u8 pad108[0x188 - 0x108];
    u16 unk188;
    u8 pad18A[6];
    LookAt unk190[2];
    Hilite unk1D0[2];
    u8 pad1F0[0x210 - 0x1F0];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[4];
    f32 unk220;
    u8 pad224[4];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    u8 pad234[0xC];
    f32 unk240;
    f32 unk244;
    f32 unk248;
    u8 pad24C[0x27C - 0x24C];
    f32 unk27C;
    f32 unk280;
    f32 unk284;
    f32 unk288;
    u8 pad28C[0x2F0 - 0x28C];
} PlayerViewData;

#define PLAYER_VIEWS ((PlayerViewData *)gPlayerSlots)
#define ABS_DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void playerViewsBuildMatrices(void *outMtx) {
    Actor *pa;
    PlayerActorData *pl;
    CamState *camState;
    s32 i;
    f32 fov;
    f32 aspect;
    f32 offs;
    s32 *cc;

    aspect = cameraStepAspectScale();
    if (D_807445CC && D_807445CC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (gPlayerCount >= 2 && gSplitScreenMode == 1) {
        func_8062754C(func_806276AC());
    }
    for (i = 0; i < gViewportCount; i++) {
        if (PLAYER_VIEWS[i].unk0 != 0) {
            if (ABS_DIFF(PLAYER_VIEWS[i].unk210, PLAYER_VIEWS[i].unk228) < 0.5 && ABS_DIFF(PLAYER_VIEWS[i].unk218, PLAYER_VIEWS[i].unk230) < 0.5) {
                offs = 1.0f;
            } else {
                offs = 0.0f;
            }
            guLookAtHilite(&PLAYER_VIEWS[i].unk8[gGfxBufferIndex], &PLAYER_VIEWS[i].unk190[gGfxBufferIndex], &PLAYER_VIEWS[i].unk1D0[gGfxBufferIndex],
                           PLAYER_VIEWS[i].unk210 + offs, PLAYER_VIEWS[i].unk214, PLAYER_VIEWS[i].unk218 + offs,
                           PLAYER_VIEWS[i].unk228, PLAYER_VIEWS[i].unk22C, PLAYER_VIEWS[i].unk230,
                           PLAYER_VIEWS[i].unk240, PLAYER_VIEWS[i].unk244, PLAYER_VIEWS[i].unk248,
                           D_807444CC, D_807444D0, D_807444D4,
                           D_807444D8, D_807444DC, func_807444E0,
                           0x20, 0x20);
            fov = PLAYER_VIEWS[i].unk280;
            cc = D_807445CC;
            pl = (PlayerActorData *)PLAYER_VIEWS[i].unk4->customState;
            pa = pl->unk104;
            camState = pa->customState;
            if (pl->unk1F0 & 0x100) {
                fov += 0.5 * sinApprox(cc[0] * 0.1);
            } else if (pl->unk1F0 & 0x2000000) {
                fov += 0.05 * sinApprox(cc[0] * 0.4);
            } else if (camState->unkFA != 0 && PLAYER_VIEWS[i].unk220 < camState->unk90 + 3.0f) {
                fov += 0.04 * sinApprox(cc[0] * 0.1);
            }
            guPerspective(&PLAYER_VIEWS[i].unk88[gGfxBufferIndex], &(i + PLAYER_VIEWS)->unk188, PLAYER_VIEWS[i].unk27C, fov * aspect, PLAYER_VIEWS[i].unk284, PLAYER_VIEWS[i].unk288, 1.0f);  // FAKE: i + base operand order avoids CSE with PLAYER_VIEWS[i]
        }
    }
    if (ABS_DIFF(PLAYER_VIEWS->unk210, PLAYER_VIEWS->unk228) < 0.5 && ABS_DIFF(PLAYER_VIEWS->unk218, PLAYER_VIEWS->unk230) < 0.5) {
        offs = 1.0f;
    } else {
        offs = 0.0f;
    }
    guPerspective((Mtx *)outMtx, &D_8076A09C, PLAYER_VIEWS->unk27C, fov * aspect, PLAYER_VIEWS->unk284, PLAYER_VIEWS->unk288, 1.0f);
    guLookAt((Mtx *)((u8 *)outMtx + 0x200), PLAYER_VIEWS->unk210 + offs, PLAYER_VIEWS->unk214, PLAYER_VIEWS->unk218 + offs,
             PLAYER_VIEWS->unk228, PLAYER_VIEWS->unk22C, PLAYER_VIEWS->unk230,
             PLAYER_VIEWS->unk240, PLAYER_VIEWS->unk244, PLAYER_VIEWS->unk248);
    D_807445CC[0]++;
}

Gfx *gfxSetViewportDisplayList(Gfx *glistp) {
    if (gHiResScale == 2) {
        gSPDisplayList(glistp++, D_1000068);
    } else {
        gSPDisplayList(glistp++, D_1000040);
    }
    return glistp;
}


Gfx *gfxInit2DDisplayList(Gfx *glistp) {
    if (gHiResScale == 2) {
        gSPDisplayList(glistp++, D_1000030);
    } else {
        gSPDisplayList(glistp++, D_1000020);
    }
    return glistp;
}


void gfxBuildFrameDisplayLists(FrameMatrices *frameGfx, Gfx **outGlist, Gfx **outGlist2) {
    Gfx *glist;
    Gfx *glist2;

    glist = gGfxTaskBuffers[gGfxBufferIndex];
    gSPPerspNormalize(&frameGfx->subDisplayList[0], D_8076A09C);
    glist2 = &frameGfx->subDisplayList[1];
    gSPClipRatio(glist2++, FRUSTRATIO_3);

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(frameGfx));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));

    gSPSegment(glist2++, 0, 0);
    gSPSegment(glist2++, 2, osVirtualToPhysical(frameGfx));
    gSPSegment(glist2++, 1, osVirtualToPhysical(D_8076A080));

    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist2++, &D_1000090);

    glist = gfxSetViewportDisplayList(glist);
    glist2 = gfxSetViewportDisplayList(glist2);

    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);
    gDPSetScissor(glist2++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);

    guTranslate(&frameGfx->identity, 0.0f, 0.0f, 0.0f);
    guOrtho(&frameGfx->ortho, 0.0f, (f32)((f64)(f32)gScreenWidth - 1.0), (f32)((f64)(f32)gScreenHeight - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->orthoQuad, 0.0f, (f32)(((f64)(f32)gScreenWidth * 4.0) - 1.0), (f32)(((f64)(f32)gScreenHeight * 4.0) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->orthoDouble, 0.0f, (f32)((2.0 * (f64)(f32)gScreenWidth) - 1.0), (f32)((2.0 * (f64)(f32)gScreenHeight) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->orthoViewport, (f32)((f64)(f32)gPlayerSlots->rect[0] * 4.0), (f32)(((f64)(f32)gPlayerSlots->rect[2] * 4.0) - 1.0), (f32)(((f64)(f32)gPlayerSlots->rect[3] * 4.0) - 1.0), (f32)((f64)(f32)gPlayerSlots->rect[1] * 4.0), -20000.0f, 20000.0f, 1.0f);
    guPerspective(&frameGfx->perspective, &D_8076A09C, gGfxFovY, cameraStepAspectScale() * gGfxAspect, gGfxNearClip, gGfxFarClip, 1.0f);

    gSPMatrix(glist2++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    glist2 = gfxInit2DDisplayList(glist2);

    glist = gfxClearZBuffer(glist);
    gDPPipeSync(glist++);
    glist = gfxSetFrameBufferColorImage(glist);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 6, 2, 0);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 4, 2, 0);
    glist = gfxDrawSplitScreenDividers(glist);

    gSPClipRatio(glist++, FRUSTRATIO_3);
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPClearGeometryMode(glist++, -1);
    gSPSetGeometryMode(glist++, 0x200404);

    glist = func_80701CA0(playerViewsRender(glist, frameGfx));
    if (gPlayerCount == 1) {
        glist = lensFlareBuildDisplayList(glist);
    }
    glist = gfxPassThrough(screenWipeDraw(renderCallbacksExecute(glist, 1)));

    if ((gCurrentMap == 0x4C) || (gCurrentMap == 0x50) || ((menuIsTransitionTypeAOrE() != 0) && (gCurrentMap != 0xD0))) {
        gScreenRenderFlags &= ~0x10;
        sHudDisabled = 0;
    }

    if (((gScreenRenderFlags & 0x10) || (sHudDisabled != 0)) && ((gPlayerCount == 1) || (gSplitScreenMode == 1))) {
        f32 fadeAlpha;
        f32 fadeScale;
        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
        gSPClearGeometryMode(glist++, 1);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);

        if (sHudDisabled != 0) {
            sHudDisabled -= 15;
            fadeScale = (f32)(1.0 - ((f64)(u32)sHudDisabled / 255.0));
            fadeAlpha = (f32)(D_807444AC - D_807444A8) * fadeScale;
            gDPFillRectangle(glist++, 0,
                (fadeAlpha < (f32)D_807444A8) ? (f32)D_807444A8 - fadeAlpha : 0.0f,
                (gScreenWidth > 0) ? gScreenWidth : 0,
                (fadeAlpha < (f32)D_807444AC) ? (f32)D_807444AC - fadeAlpha : 0.0f);
            gDPFillRectangle(glist++, 0, D_807444B0 + fadeAlpha, gScreenWidth, D_807444B4 + fadeAlpha);
            gPlayerSlots->rect[1] = (s16)((f32)D_807444AC - fadeAlpha);
            gPlayerSlots->rect[3] = (s16)((f32)D_807444B0 + fadeAlpha);
        } else {
            gDPFillRectangle(glist++, 0, D_807444A8, gScreenWidth, D_807444AC);
            gDPFillRectangle(glist++, 0, D_807444B0, gScreenWidth, D_807444B4);
            gPlayerSlots->rect[1] = (s16)D_807444AC;
            gPlayerSlots->rect[3] = (s16)D_807444B0;
        }
        gPlayerSlots->unk27A = (s16)(gPlayerSlots->rect[3] - gPlayerSlots->rect[1]);
        gPlayerSlots->unk280 = (f32)((f32)gPlayerSlots->unk278 / (f32)gPlayerSlots->unk27A);
        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    }

    if ((gViewportInsetLeft != 0) || (gViewportInsetRight != 0) || (gViewportInsetTop != 0) || (gViewportInsetBottom != 0) || (gViewportInsetActive != 0)) {
        G00Entry *vpEntry;
        s16 dx, dy;
        vpEntry = cameraFindViewportEntry(0);
        gPlayerSlots->rect[0] = (s16)(vpEntry->unk4 + gViewportInsetLeft);
        gPlayerSlots->rect[2] = (s16)(vpEntry->unk8 - gViewportInsetRight);
        gPlayerSlots->rect[1] = (s16)(vpEntry->unk6 + gViewportInsetTop);
        gPlayerSlots->rect[3] = (s16)(vpEntry->unkA - gViewportInsetBottom);

        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
        gSPClearGeometryMode(glist++, 1);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);

        if (gViewportInsetLeft != 0) {
            gDPFillRectangle(glist++, vpEntry->unk4, vpEntry->unk6, gPlayerSlots->rect[0], vpEntry->unkA);
        }
        if (gViewportInsetRight != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[2], vpEntry->unk6, vpEntry->unk8, vpEntry->unkA);
        }
        if (gViewportInsetTop != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[0], vpEntry->unk6, gPlayerSlots->rect[2], gPlayerSlots->rect[1]);
        }
        if (gViewportInsetBottom != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[0], gPlayerSlots->rect[3], gPlayerSlots->rect[2], vpEntry->unkA);
        }

        gDPPipeSync(glist++);
        gPlayerSlots->unk278 = (s16)(gPlayerSlots->rect[2] - gPlayerSlots->rect[0]);
        gPlayerSlots->unk27A = (s16)(gPlayerSlots->rect[3] - gPlayerSlots->rect[1]);
        if ((gViewportInsetLeft == 0) && (gViewportInsetRight == 0) && (gViewportInsetTop == 0) && (gViewportInsetBottom == 0)) {
            gViewportInsetActive = 0;
        } else {
            gViewportInsetActive = 1;
        }
        gViewportInsetLeft = 0;
        gViewportInsetRight = 0;
        gViewportInsetTop = 0;
        gViewportInsetBottom = 0;
        dx = vpEntry->unk8 - vpEntry->unk4;
        dy = vpEntry->unkA - vpEntry->unk6;
        gPlayerSlots->unk280 = (f32)dx / (f32)dy;
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    }

    glist = renderCallbacksExecute(renderCallbacksExecute(func_8062CA0C(renderCallbacksExecute(gfxInit2DDisplayList(glist), 3), gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ), 5), 7);
    if (D_807467E4 != 0) {
        D_807467E4 -= 1;
    }
    glist = screenStateTickAndDraw(slotQueueBuildDisplayList(healthHudDrawAll(glist)));
    textFontAgeSheets();
    texCacheUpdate();
    commandQueueReset();
    *outGlist = glist;
    *outGlist2 = glist2;
}


Gfx *gfxClearZBuffer(Gfx *glistp) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, 0, 0);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetDepthImage(glistp++, osVirtualToPhysical(gGfxDepthBuffer));
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth, osVirtualToPhysical(gGfxDepthBuffer));
    gDPSetFillColor(glistp++, 0xFFFCFFFC);
    gDPFillRectangle(glistp++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    gDPPipeSync(glistp++);
    return glistp;
}


Gfx *gfxSetFrameBufferColorImage(Gfx *glistp) {
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth, osVirtualToPhysical(gFramebuffers[gGfxBufferIndex]));
    return glistp;
}


void gfxAllocateBuffers(u8 numScreens) {
    if (gGlobalOverlayFlags & 1) {
        D_8076A058 = 0x1770;
    } else {
        D_8076A058 = numScreens * 3000;
    }
    gGfxTaskBuffers[0] = heapAlloc(D_8076A058 * sizeof(Gfx));
    gGfxTaskBuffers[1] = heapAlloc(D_8076A058 * sizeof(Gfx));
    gfxEndDisplayList(gfxClearFramebuffer(gGfxTaskBuffers[0], 0), 0, &D_8076A088, 1);
    gfxEndDisplayList(gfxClearFramebuffer(gGfxTaskBuffers[1], 1), 1, &D_8076A088, 1);
}


Gfx *gfxClearFramebuffer(Gfx *glistp, u8 fbIndex) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, 0, 0);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth, gFramebuffers[fbIndex]);
    gDPSetFillColor(glistp++, 0x10001);
    gDPPipeSync(glistp++);
    gDPFillRectangle(glistp++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    return glistp;
}


void gfxEndDisplayList(Gfx *inGlist, u8 bufIdx, s32 *outSize, u8 fullSync) {
    Gfx *glistp = inGlist;

    if (fullSync) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *outSize = glistp - (Gfx *)gGfxTaskBuffers[bufIdx];
    if (*outSize >= D_8076A058) {
        faultSetMessage(0x12, 0, 0, 0);
    }
}


void gfxEndSubDisplayList(Gfx *inGlist, void *basePtr, s32 *outSize, u8 fullSync) {
    Gfx *glistp = inGlist;

    if (fullSync) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *outSize = ((s32)glistp - (s32)basePtr - 0xDB0) >> 3;
}


void mapLoadLevel(void) {
    void *mapChunkAsset;
    void *loadedAsset;
    s32 modelAsset;
    f32 audioVolume;
    s32 activeMap;
    s32 songId;

    D_80746830 = 1;
    D_8076A090 = 0;
    D_8076A094 = 0;
    D_8076A098 = 0;
    gGlobalPauseFlags &= 0xFFEB3FFC;
    menuSeedRandom();
    D_80750AC4 = 0;
    D_8076A0A4 = 0;
    gGfxBufferIndex = 0;
    gFrameCounter = 0;
    gGameFrameCounter = 0;
    audioResetAll();
    D_80744508 = 0;
    *D_807ECDF4 = 0;
    texCacheReset();
    gScreenRenderFlags &= 0xFFCF;
    effectSpritePoolReset();
    if (gGameMode == 1) {
        gGameMode = 0;
    }
    D_8076A06C = gFrameCounter;
    D_80744500 = 0;
    timerQueueInit();

    gCurrentMap = gInitialMap;
    activeMap = gCurrentMap;
    if (gCurrentMap != 0x50) {
        if (gCurrentMap != 0x51) {
            gGlobalPauseFlags |= 0x30030;
        } else {
            gGlobalPauseFlags &= 0xFFFCFFCF;
        }
    } else {
        gGlobalPauseFlags &= 0xFFFEFFCF;
    }
    if (activeMap == 2) {
        gGameMode = 3;
    } else if (activeMap == 9) {
        gGameMode = 4;
    } else {
        gGameMode = 0;
    }
    viModeSetup(1);
    if ((gActivePlayerCount >= 2) && !(gGlobalOverlayFlags & 0x04000000)) {
        gActivePlayerCount = 1;
    }
    playerSetupViewports();
    playerSetLargeModeScale(0.0f);
    gfxAllocateBuffers(gActivePlayerCount);
    if (gCurrentMap != 0xB8) {
        if (gCurrentMap == 0xBF) {
            gPlayerCharacterId = 6;
        }
    } else {
        gPlayerCharacterId = 7;
    }
    D_807F6010 = 0;
    collisionInitTables();
    textFontInitTables();
    gfxResourceListReset();
    vtxGradientSetColorA(0xFF, 0xFF, 0xFF);
    vtxGradientSetColorB(0xFF, 0xFF, 0xFF);
    if (gGameMode == 0) {
        D_8076A0A0 = assetLoad(0x13, 0, 1, 1);
        gfxBackgroundReset();
        commandStateInit();
        playerWaypointPathsLoad(gCurrentLevelIndex);
        proxPathListClear();
        mapSearchTableReset();
        pathFreeAsset(gCurrentMap);
        mapChunkAsset = assetLoad(1, gCurrentMap, 1, 1);
        renderEntryListsReset();
        mapChunkAllocLists(mapChunkAsset);
        mapHeaderLoad(mapChunkAsset);
        playerLoadSpawnerAsset(gCurrentMap);
        billboardCacheInit();
        mapLoadNodeAsset(gCurrentMap);
        actorListInitOffsets();
        modelTypeCountsInit();
        displayListFreeQueueReset();
        modelAsset = assetLoad(9, gCurrentMap, 1, 1);
        modelSlotsAllocate(gCurrentMap, 1);
        actorMapModelsSetup(modelAsset, 0, 0);
        actorInitTargetEntries();
        lightInitGlobals();
        actorInit();
        actorSpawnInitialSet();
        volumeTriggerTableInit(gCurrentMap);
        camInit(loadedAsset = assetLoad(8, gCurrentMap, 1, 1));
        if (loadedAsset != NULL) {
            assetFreeBuffer(loadedAsset, 0x8D0, 2);
        }
        menuSetupBonusCharacter();
        playerAllocSlots(gInitialExit);
        effectResetLists();
        loadedAsset = assetLoad(0x10, gCurrentMap, 1, 1);
        func_80724C78(loadedAsset);
        if (loadedAsset != NULL) {
            assetFreeBuffer(loadedAsset, 0x8DD, 2);
        }
        camResetAllPlayers();
        renderCallbacksReset();
        gridBuildNodeLists();
        resListReset();
        timerQueueAdd(sfxPlayCurrent, 2, 0, 0, 0);
        if (gGlobalOverlayFlags & 0x1000) {
            loadedAsset = assetLoad(0x16, gCurrentMap, 1, 1);
            func_80026FD0(loadedAsset);
            if (loadedAsset != NULL) {
                assetFreeBuffer(loadedAsset, 0x8ED, 2);
            }
        }
        if (gGlobalOverlayFlags & 0x2000) {
            func_8002EC08(gCurrentMap);
        }
        collisionBstRebalanceAll();
        D_807F6008 = 0;
        if ((transitionGetState() == 0) && (gGameMode != 2)) {
            if ((gCurrentMap == 0x11) && (flagGet(0x302, 0) != 0)) {
                sfxAllocateChannel(0x74, 1.0f);
            } else {
                songId = D_80745BDC[gCurrentMap][0];
                audioVolume = 1.0f;
                if ((songId == 6) || (songId == 0x1F)) {
                    audioVolume = 0.5493331552f;
                }
                sfxAllocateChannel(songId, audioVolume);
            }
        }
        if ((gCurrentMap == 0x22) || (gCurrentMap == 0xB8)) {
            sfxAllocateChannel(0x60, 1.0f);
        }
        seqSetChannelVolumeScale(0, 1.0f);
        seqSetChannelVolumeScale(1, 1.0f);
        seqSetChannelVolumeScale(2, 1.0f);
        mapSlotFree(gCurrentMap);
        actorInitEntryPoints();
    }
    menuCheckMapTransitionOnLoad();
    func_805FF670();
    gScreenRenderFlags ^= 1;
    gScreenFadeProgress = 31.0f;
    gScreenRenderFlags |= 4;
    gScreenFadeRate = -1.0f;
    if ((gNextGameMode != 2) && (D_8076AEE0 == 1)) {
        sfxAllocateChannel(0x2B, 1.0f);
    }
    func_80701C90();
    screenWipeReset();
    particleFindPathIndices(gCurrentLevelIndex);
    frameTimingReset(gCurrentMap);
    D_80746830 = 0;
}


void viewportSetMargins(u8 val0, u8 val1, u8 val2, u8 val3) {
    gViewportInsetLeft = val0;
    gViewportInsetRight = val1;
    gViewportInsetTop = val2;
    gViewportInsetBottom = val3;
}

void alignInt(s32 *val, s32 alignment) {
    s32 rem;

    rem = *val % alignment;
    if (rem != 0) {
        *val = *val + alignment - rem;
    }
}

