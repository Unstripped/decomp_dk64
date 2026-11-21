#include "common.h"
#include "map.h"
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

extern s8 gEepromLoaded;
extern u8 gSaveIconTimer;
extern s8 gWatchdogPaused;
extern s32 gPlayTimeBaseSeconds;
extern u8 gSplitScreenMode;
extern u8 gActivePlayerCount;
extern u16 gMinigameCoinCount;

extern s32 gGfxTaskBufferCap;
extern s16 gCurrentLevelIndex;
extern u8 gTransitionFadeType;

extern OSIoMesg gPiDmaIoMesg;
extern s16 *gPhysicalContPads;
extern s8 gModelSlotAppendBlocked;
extern u8 *gSavedMapModelData;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s32 gSegment1DataBuffer;

extern s8 gMainThreadHalted;
extern u64 gMainThreadStackSentinel;
extern OSMesgQueue *gBootResetQueue;

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
s16 gLetterboxTopBarTop = 0xA;
s16 gLetterboxTopBarBottom = 0x28;
s16 gLetterboxBottomBarTop = 0xC7;
s16 gLetterboxBottomBarBottom = 0xE5;
f32 gGfxFovY = 45.0f;
f32 gGfxAspect = 1.0f;
s8 gWidescreenEnabled = 0;
f32 gGfxFarClip = 1500.0f;
f32 gGfxNearClip = 10.0f;
f32 gHiliteKeyDirX = 1.0f;
f32 gHiliteKeyDirY = 1.0f;
f32 gHiliteKeyDirZ = 1.0f;
f32 gHiliteFillDirX = 1.0f;
f32 gHiliteFillDirY = 1.0f;
f32 gHiliteFillDirZ = 1.0f;
s32 gInitialMap = 0x28;
s32 gInitialExit = 0;
u8 gGameMode = 0;
u8 gGameModeLastFrame = 0;
u8 gPrevGameMode = 0;
u8 gNextGameMode = 0;
u8 gGfxBufferIndex = 0;
s8 D_80744500 = 0;
s8 gMapLoadPauseFrames = 0;
s16 gEnemyDefeatCount = 0;
u8 gHiResScale = 1;
// Formerly the blobs u8 gBootScreenState[28] and u32 gCamAutoRotate[5]: each label below is its own object (IDO pads every
// .data object to 4 bytes); the types are the ones their readers load (lb/lbu/lh).
u8 gBootScreenState = 0; // viModeSetup's 1 is a separate li from sBootScreenShown's s8 1 (0x3e4/0x3f0); 13980 reads it signed
u8 gMenuReturnContext = 0;
s16 gMinigameScore = 0;
s8 gMenuMpModeSel = 0;
s8 gMenuMpLimit = 3;
s16 gMpWinCounts[4] = { 0 }; // per player: multiplayer rounds won (menuInitMultiplayerResults)
s8 gSkipCutscenes = 0;
u8 gCamAutoRotate = 0; // menu/3E10 lbu; 201B0 reads it signed (ORIG there)
s8 gMenuMpSplitScreenSel = 0;
s8 gMenuMpMapSel = 0;
s8 gMenuCheatOptions[5] = { 0 }; // selected option of each cheat menu row (menu/3E10)
s16 gCheatFlags = 0;
MenuHighScoreEntry gRambiHighScores[5] = { { 100, "AAA" }, { 90, "AAA" }, { 80, "AAA" }, { 70, "AAA" }, { 60, "AAA" } };
MenuHighScoreEntry gEnguardeHighScores[5] = { { 100, "AAA" }, { 90, "AAA" }, { 80, "AAA" }, { 70, "AAA" }, { 70, "AAA" } };
u32 gViModeIndexByTvType[6] = { 0xF, 0x19, 2, 0xA, 0x1E, 0x26 };
s8 sBootScreenShown = 0;
s8 sViModeFirstSetup = 1;
u32 D_807445A8[2] = { 0 };
u64 gLastPauseDuration = 0;
u64 gPauseTimeTotal = 0;
u64 gPauseStartTime = 0;
s8 sPauseOpenDelay = 0;
s32 sViewFrameCounter[5] = { 0, 0x4B0, 0, 0, 0 };

// .bss 0x807655F0-0x8076A160
OSMesgQueue gPiDmaMesgQueue;
OSMesg gPiDmaMesgs[0x32];
OSMesgQueue gAssetDmaDoneQueue;
OSMesg gAssetDmaDoneMesgs[0xC0];
OSMesgQueue gGfxDoneQueue;
OSMesg gGfxDoneMesgs[0x10];
u64 gSchedThreadStack[0x400];
SchedStruct gScheduler;
SchedClient gGfxSchedClient;
FrameMatrices gFrameMatrices[2];
FrameMatrices *gGfxCurrentFrameBuffer;
u32 D_8076A04C;
Gfx *gGfxTaskBuffers[4];
u8 *gGfxDepthBuffer;
u32 gFrameCounter;
u32 gGameFrameCounter;
s32 gMapLoadFrame;
s32 D_8076A070[3];
s32 D_8076A07C;
void *gSegment1Data;
u32 gSegment1DataSize;
s32 gGfxListCommandCount;
s32 gGfxSubListCommandCount;
s32 gMapActiveFrameCount;
s32 gMapWarpCount;
s32 gMapPauseCount;
u16 gPerspNorm;
u16 D_8076A09E;
s16 *gZbufferDistanceTable;
u8 gGfxSubListEnabled;
u8 D_8076A0A5;
u16 D_8076A0A6;
s32 gCurrentMap;
s32 gHubReturnExit;
u8 D_8076A0B0;
u8 gScreenRenderFlags;
u8 gMapLoadCountdown;
u8 gLetterboxRetractTimer;
f32 *gChunkLightR;
f32 *gChunkLightG;
f32 *gChunkLightB;
f32 *gChunkLightTargetR;
f32 *gChunkLightTargetG;
f32 *gChunkLightTargetB;
u32 D_8076A0CC;
s8 gMenuScreenSelection[20]; // saved selection per menu screen (menu init clears 13)
s8 gMenuPlayerCharacterSel[4];
s8 gMenuCharacterVariantOwner[6][4];
u32 gMenuPlayerCharacterVariant;
u8 gMenuMpMatchTypeSel;
s8 gMpWinnerIndex;
u16 D_8076A106;
OSMesg gBootDelayMesgs[2];
OSMesgQueue gBootDelayMesgQueue;
OSMesg gBootDelayMesg;
u32 D_8076A12C;
OSTimer gBootDelayTimer;
void *gGfxFrameTaskBuffer;
u32 D_8076A154;

void seg11DmaRead(s32 romOffset, s32 size, void *dst) {
    s32 romBase;

    romBase = gSegmentTable[11].romStart;
    osWritebackDCache(dst, size);
    osPiStartDma(&gPiDmaIoMesg, OS_MESG_PRI_NORMAL, OS_READ, romBase + romOffset, dst, size, &gPiDmaMesgQueue);
    osRecvMesg(&gPiDmaMesgQueue, NULL, OS_MESG_BLOCK);
    osInvalDCache(dst, size);
}

void viModeApplyHighRes(void) {
    u16 *fb;
    u16 *end;
    void *pad0;
    void *pad1;
    u16 *src;
    s32 *compressedBuf;
    void *pad2;
    void *pad3;
    u8 *gzipSrc;
    u8 *gzipDst;
    s32 i;
    s32 j;

    fb = gFramebuffers[0];
    end = fb + 320 * 240;
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();

    compressedBuf = (s32 *)(gFramebuffers[1] + 0x6400);
    seg11DmaRead(0x38, 0x10, compressedBuf);
    seg11DmaRead(compressedBuf[0] + 0x178, 0x10, compressedBuf);
    seg11DmaRead(compressedBuf[0], compressedBuf[1] - compressedBuf[0], compressedBuf);

    gzipSrc = (u8 *)compressedBuf;
    gzipDst = (u8 *)gFramebuffers[1];
    src = gFramebuffers[1];
    gunzip(&gzipSrc, &gzipDst, (u8 *)gFramebuffers[1] + 0x15E00);

    fb = gFramebuffers[0] + 96 * 320 + 64;
    for (i = 0; i < 48; i++) {
        for (j = 0; j < 192; j++) {
            *fb++ = *src++;
        }
        fb += 320 - 192;
    }

    fb = gFramebuffers[1];
    end = fb + 320 * 240;
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();
}



void viModeSetup(u8 overlaySlot) {
    u8 overlayId;
    s32 overlayParam;
    s8 *firstSetupFlag = &sViModeFirstSetup;

    overlayId = 1;
    overlayParam = 0;
    mapApplyLevelFlags(gCurrentLevelIndex);
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
        overlayParam = mapGetOverlayBufferSize(gCurrentMap);
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
    if (*firstSetupFlag == 0) {
        osViSetMode(&osViModeTable[gViModeIndexByTvType[osTvType + osTvType + gHiResScale - 1]]);
        if (sBootScreenShown == 0) {
            osViBlack(1);
        }
        gBootScreenState = 0;
        sBootScreenShown = 0;
    } else {
        gBootScreenState = 1;
        sBootScreenShown = 1;
        *firstSetupFlag = 0;
        viModeApplyHighRes();
    }
    osViSetSpecialFeatures(0x42);
    gScreenWidth = gHiResScale * 0x140;
    gScreenHeight = gHiResScale * 0xF0;
    gLetterboxTopBarBottom = gGfxScreenTop + gHiResScale * 0x1E;
    gLetterboxBottomBarTop = gGfxScreenBottom - gHiResScale * 0x1E;
    gLetterboxTopBarTop = gGfxScreenTop;
    gLetterboxBottomBarBottom = gGfxScreenBottom;
}

void mainSystemInit(void) {
    gSegment1DataSize = gSegmentTable[12].romEnd - gSegmentTable[12].romStart;
    osCreateMesgQueue(&gPiDmaMesgQueue, gPiDmaMesgs, 0x32);
    osCreateMesgQueue(&gAssetDmaDoneQueue, gAssetDmaDoneMesgs, 0xC0);
    schedCreate(&gScheduler, &gSchedThreadStack[0x400], 0x19, gViModeIndexByTvType[osTvType + osTvType], 1);
    osCreateMesgQueue(&gGfxDoneQueue, gGfxDoneMesgs, 0x10);
    schedAddClient(&gScheduler, &gGfxSchedClient, &gGfxDoneQueue, 1, 1);
    gCurrentMap = gInitialMap;
    viModeSetup(0);
    D_8076A07C = 5;
    schedInitGfxUcodes();
    controllerInit();
    audioInit();
    transitionSetState(0);
    faultThreadInit();
    osWritebackDCacheAll();
    osCreateMesgQueue(&gBootDelayMesgQueue, gBootDelayMesgs, 2);
    osSetTimer(&gBootDelayTimer, OS_USEC_TO_CYCLES(300000), 0, &gBootDelayMesgQueue, gBootDelayMesg);
    sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
}

void mainResetEngineState(void) {
    s32 pad;
    f32 aspectScale;

    osWritebackDCacheAll();
    osInvalDCache((void *)K0BASE, 0x800000);
    gSegment1Data = &gSegment1DataBuffer;
    dmaReadAssetDecompress(gSegmentTable[12].romStart, gSegment1Data, &gSegment1DataSize, 0, 0, 0, 0);
    gGfxSubListEnabled = 0;
    controllerWaitRead();
    gFrameCounter = 0;
    gGameFrameCounter = 0;
    gEepromLoaded = 0;
    gHubReturnExit = 4;
    gGlobalPauseFlags = 0x30030;
    gScreenRenderFlags |= 1;
    gMapLoadCountdown = 0;
    gScreenFadeProgress = 31.0f;
    gScreenRenderFlags |= 4;
    modelSkipListClear();
    playerResetSpawnGlobals();
    flagsClearAllBank2();
    mapSlotArrayInit();
    csTimerQueueClear();
    aspectScale = cameraStepAspectScale();
    guTranslate(&gFrameMatrices[0].identity, 0.0f, 0.0f, 0.0f);
    guTranslate(&gFrameMatrices[1].identity, 0.0f, 0.0f, 0.0f);
    guPerspective(&gFrameMatrices[0].perspective, &gPerspNorm, gGfxFovY, gGfxAspect * aspectScale, gGfxNearClip, gGfxFarClip, 1.0f);
    guPerspective(&gFrameMatrices[1].perspective, &gPerspNorm, gGfxFovY, gGfxAspect * aspectScale, gGfxNearClip, gGfxFarClip, 1.0f);
}

extern s16 gMainLoopWatchdog;
extern u8 gGfxTaskPending[];

void mainThreadLoop(void *arg) {
    u8 first;
    OSMesg receivedMesg;

    first = 1;
    if (osTvType == 0) {
        gGfxAspect = 1.25f;
    }
    mainSystemInit();
    osViSetSpecialFeatures(0x42);
    mainResetEngineState();
    D_8076A070[0] = gScheduler.tickCount - 2;
    osRecvMesg(&gBootDelayMesgQueue, &receivedMesg, OS_MESG_BLOCK);
    while (1) {
        gMainLoopWatchdog = 0xC8;
        while (gMainThreadHalted != 0) {
        }
        if ((gScreenRenderFlags & 1) && gMapLoadCountdown == 0) {
            mapLoadLevel();
            if (gNextGameMode == 2) {
                gGlobalPauseFlags |= 0x200;
                gMapLoadPauseFrames = 8;
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
        schedWaitGfxTask(0x4D2);
        if (gGfxTaskPending[0] != 0) {
            schedWaitGfxTask(0x929);
        }
        frameTimingUpdate();
        if (gGameMode == 0 || gGameMode == 1 || gGameMode == 7) {
            mapSearchTableUpdateVisibility();
            playerViewUpdateDepthProbes();
        }
        heapTickDeferredFrees();
        if (gMainThreadStackSentinel != 0x12345678) {
            faultSetMessage(2, 0, 0, 0);
        }
        if (first != 0) {
            osSendMesg(gBootResetQueue, (OSMesg)0x309, OS_MESG_BLOCK);
            first = 0;
        }
        if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
            gMapLoadCountdown--;
        }
        gGameModeLastFrame = gGameMode;
    }
}

void gfxSubmitFrame(void) {
    Gfx *glist;
    Gfx *gfxEnd;

    controllerStartRead();
    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], gGfxListCommandCount, 3, (gGfxSubListEnabled != 0) ? 0 : 1, 0x4D2, 1);
    if (gGfxSubListEnabled != 0) {
        schedSubmitGfxTask(gFrameMatrices[gGfxBufferIndex].subDisplayList, gGfxSubListCommandCount, 0, 1, 0x929, 1);
    }
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    if (!(gGlobalPauseFlags & 2)) {
        gGameFrameCounter++;
    }
    gGfxCurrentFrameBuffer = &gFrameMatrices[gGfxBufferIndex];
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
    gGfxFrameTaskBuffer = gGfxTaskBuffers[gGfxBufferIndex];
    if ((gScreenRenderFlags & 1) && gScreenFadeProgress == 31.0f) {
        glist = gGfxTaskBuffers[gGfxBufferIndex];
        gfxEnd = gGfxCurrentFrameBuffer->subDisplayList;
        renderCallbacksReset();
    } else {
        gfxBuildFrameDisplayLists(gGfxCurrentFrameBuffer, &glist, &gfxEnd);
    }
    if (gGlobalPauseFlags & 0x100) {
        gGlobalPauseFlags &= ~0x100;
        transitionStart(2, &gGlobalPauseFlags);
    } else if (gGlobalPauseFlags & 0x200) {
        gMapLoadPauseFrames--;
        if (gMapLoadPauseFrames == 0) {
            gGlobalPauseFlags &= ~0x200;
            transitionStart(3, &gGlobalPauseFlags);
        }
    } else {
        glist = screenFadeUpdate(glist, gTransitionFadeType);
    }
    if (gGfxSubListEnabled != 0 && gGameMode != 6) {
        gfxEndDisplayList(glist, gGfxBufferIndex, &gGfxListCommandCount, 0);
        gfxEndSubDisplayList(gfxEnd, gGfxCurrentFrameBuffer, &gGfxSubListCommandCount, 1);
    } else {
        gfxEndDisplayList(glist, gGfxBufferIndex, &gGfxListCommandCount, 1);
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
            gLastPauseDuration = osGetTime() - gPauseStartTime;
            slotQueuePopActiveMask();
        }
    } else {
        gPauseTimeTotal += gLastPauseDuration;
        gLastPauseDuration = 0;
        gPauseStartTime = 0;
        if (sPauseOpenDelay > 0) {
            if (!(gGlobalPauseFlags & 1)) {
                sPauseOpenDelay = 0;
            } else {
                sPauseOpenDelay -= 1;
                if (sPauseOpenDelay <= 0) {
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
                    gPauseStartTime = osGetTime();
                    gGlobalPauseFlags ^= 1;
                    gGlobalPauseFlags |= 2;
                }
            }
        }
        if ((gGlobalPauseFlags & 1) && sPauseOpenDelay <= 0) {
            slotQueueReset();
            sPauseOpenDelay = 2;
        }
    }
    return gGlobalPauseFlags & 2;
}

s32 playTimeGetSeconds(void) {
    u64 now;
    u64 elapsed;

    now = osGetTime();
    elapsed = now - gPauseTimeTotal;
    if (gGlobalPauseFlags & 2) {
        elapsed -= now - gPauseStartTime;
    }
    elapsed = OS_CYCLES_TO_USEC(elapsed) / 1000000;
    return (u32) elapsed + gPlayTimeBaseSeconds;
}

u8 hudCanRender(void) {
    return !(gScreenRenderFlags & 0x10) && gLetterboxRetractTimer == 0;
}

extern u8 gViewportCount;

#define ABS_DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void playerViewsBuildMatrices(FrameMatrices *frame) {
    Actor *camActor;
    PlayerState *playerState;
    CamState *camState;
    s32 i;
    f32 viewAspect;
    f32 aspectScale;
    f32 eyeOffset;
    s32 *frameCount = sViewFrameCounter;

    aspectScale = cameraStepAspectScale();
    if (gPlayerCount >= 2 && gSplitScreenMode == 1) {
        camSetSharedViewEye(camSetSharedViewFocus());
    }
    for (i = 0; i < gViewportCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            if (ABS_DIFF(gPlayerSlots[i].camX, gPlayerSlots[i].focusX) < 0.5 && ABS_DIFF(gPlayerSlots[i].camZ, gPlayerSlots[i].focusZ) < 0.5) {
                eyeOffset = 1.0f;
            } else {
                eyeOffset = 0.0f;
            }
            guLookAtHilite(&gPlayerSlots[i].viewMtx[gGfxBufferIndex], &gPlayerSlots[i].lookAt[gGfxBufferIndex], &gPlayerSlots[i].hilite[gGfxBufferIndex],
                           gPlayerSlots[i].camX + eyeOffset, gPlayerSlots[i].camY, gPlayerSlots[i].camZ + eyeOffset,
                           gPlayerSlots[i].focusX, gPlayerSlots[i].focusY, gPlayerSlots[i].focusZ,
                           gPlayerSlots[i].upX, gPlayerSlots[i].upY, gPlayerSlots[i].upZ,
                           gHiliteKeyDirX, gHiliteKeyDirY, gHiliteKeyDirZ,
                           gHiliteFillDirX, gHiliteFillDirY, gHiliteFillDirZ,
                           0x20, 0x20);
            viewAspect = gPlayerSlots[i].aspect;
            playerState = gPlayerSlots[i].actor->customState;
            camActor = playerState->camActor;
            camState = camActor->customState;
            if (playerState->stateFlags & 0x100) {
                viewAspect += 0.5 * sinApprox(frameCount[0] * 0.1);
            } else if (playerState->stateFlags & 0x2000000) {
                viewAspect += 0.05 * sinApprox(frameCount[0] * 0.4);
            } else if (camState->hasWater != 0 && gPlayerSlots[i].eyeY < camState->waterY + 3.0f) {
                viewAspect += 0.04 * sinApprox(frameCount[0] * 0.1);
            }
            guPerspective(&gPlayerSlots[i].projMtx[gGfxBufferIndex], &gPlayerSlots[i].perspNorm, gPlayerSlots[i].fov, viewAspect * aspectScale, gPlayerSlots[i].nearClip, gPlayerSlots[i].farClip, 1.0f);
        }
    }
    if (ABS_DIFF(gPlayerSlots->camX, gPlayerSlots->focusX) < 0.5 && ABS_DIFF(gPlayerSlots->camZ, gPlayerSlots->focusZ) < 0.5) {
        eyeOffset = 1.0f;
    } else {
        eyeOffset = 0.0f;
    }
    guPerspective(&frame->perspective, &gPerspNorm, gPlayerSlots->fov, viewAspect * aspectScale, gPlayerSlots->nearClip, gPlayerSlots->farClip, 1.0f);
    guLookAt(&frame->lookAt, gPlayerSlots->camX + eyeOffset, gPlayerSlots->camY, gPlayerSlots->camZ + eyeOffset,
             gPlayerSlots->focusX, gPlayerSlots->focusY, gPlayerSlots->focusZ,
             gPlayerSlots->upX, gPlayerSlots->upY, gPlayerSlots->upZ);
    frameCount[0]++;
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
    gSPPerspNormalize(&frameGfx->subDisplayList[0], gPerspNorm);
    glist2 = &frameGfx->subDisplayList[1];
    gSPClipRatio(glist2++, FRUSTRATIO_3);

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(frameGfx));
    gSPSegment(glist++, 1, osVirtualToPhysical(gSegment1Data));

    gSPSegment(glist2++, 0, 0);
    gSPSegment(glist2++, 2, osVirtualToPhysical(frameGfx));
    gSPSegment(glist2++, 1, osVirtualToPhysical(gSegment1Data));

    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist2++, &D_1000090);

    glist = gfxSetViewportDisplayList(glist);
    glist2 = gfxSetViewportDisplayList(glist2);

    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);
    gDPSetScissor(glist2++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth, gScreenHeight);

    guTranslate(&frameGfx->identity, 0.0f, 0.0f, 0.0f);
    guOrtho(&frameGfx->ortho, 0.0f, (f32)gScreenWidth - 1.0, (f32)gScreenHeight - 1.0, 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->orthoQuad, 0.0f, (f32)gScreenWidth * 4.0 - 1.0, (f32)gScreenHeight * 4.0 - 1.0, 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->orthoDouble, 0.0f, 2.0 * (f32)gScreenWidth - 1.0, 2.0 * (f32)gScreenHeight - 1.0, 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->orthoViewport, (f32)gPlayerSlots->rect[0] * 4.0, (f32)gPlayerSlots->rect[2] * 4.0 - 1.0, (f32)gPlayerSlots->rect[3] * 4.0 - 1.0, (f32)gPlayerSlots->rect[1] * 4.0, -20000.0f, 20000.0f, 1.0f);
    guPerspective(&frameGfx->perspective, &gPerspNorm, gGfxFovY, cameraStepAspectScale() * gGfxAspect, gGfxNearClip, gGfxFarClip, 1.0f);

    gSPMatrix(glist2++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    glist2 = gfxInit2DDisplayList(glist2);

    glist = gfxClearZBuffer(glist);
    gDPPipeSync(glist++);
    glist = gfxSetFrameBufferColorImage(glist);
    gDPSetColorDither(glist++, G_CD_MAGICSQ);
    gDPSetAlphaDither(glist++, G_AD_PATTERN);
    glist = gfxDrawSplitScreenDividers(glist);

    gSPClipRatio(glist++, FRUSTRATIO_3);
    gDPPipeSync(glist++);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glist++, -1);
    gSPSetGeometryMode(glist++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);

    glist = underwaterTintBuildDisplayList(playerViewsRender(glist, frameGfx));
    if (gPlayerCount == 1) {
        glist = lensFlareBuildDisplayList(glist);
    }
    glist = gfxPassThrough(screenWipeDraw(renderCallbacksExecute(glist, 1)));

    if ((gCurrentMap == 0x4C) || (gCurrentMap == 0x50) || ((menuIsTransitionTypeAOrE() != 0) && (gCurrentMap != 0xD0))) {
        gScreenRenderFlags &= ~0x10;
        gLetterboxRetractTimer = 0;
    }

    if (((gScreenRenderFlags & 0x10) || (gLetterboxRetractTimer != 0)) && ((gPlayerCount == 1) || (gSplitScreenMode == 1))) {
        f32 barOffset;
        f32 barProgress;
        gDPPipeSync(glist++);
        gDPSetCycleType(glist++, G_CYC_FILL);
        gDPSetRenderMode(glist++, 0, 0);
        gSPClearGeometryMode(glist++, G_ZBUFFER);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);

        if (gLetterboxRetractTimer != 0) {
            gLetterboxRetractTimer -= 15;
            barProgress = 1.0 - gLetterboxRetractTimer / 255.0;
            barOffset = (gLetterboxTopBarBottom - gLetterboxTopBarTop) * barProgress;
            gDPFillRectangle(glist++, 0,
                (barOffset < gLetterboxTopBarTop) ? gLetterboxTopBarTop - barOffset : 0.0f,
                (gScreenWidth > 0) ? gScreenWidth : 0,
                (barOffset < gLetterboxTopBarBottom) ? gLetterboxTopBarBottom - barOffset : 0.0f);
            gDPFillRectangle(glist++, 0, gLetterboxBottomBarTop + barOffset, gScreenWidth, gLetterboxBottomBarBottom + barOffset);
            gPlayerSlots->rect[1] = gLetterboxTopBarBottom - barOffset;
            gPlayerSlots->rect[3] = gLetterboxBottomBarTop + barOffset;
        } else {
            gDPFillRectangle(glist++, 0, gLetterboxTopBarTop, gScreenWidth, gLetterboxTopBarBottom);
            gDPFillRectangle(glist++, 0, gLetterboxBottomBarTop, gScreenWidth, gLetterboxBottomBarBottom);
            gPlayerSlots->rect[1] = gLetterboxTopBarBottom;
            gPlayerSlots->rect[3] = gLetterboxBottomBarTop;
        }
        gPlayerSlots->rectHeight = gPlayerSlots->rect[3] - gPlayerSlots->rect[1];
        gPlayerSlots->aspect = (f32)gPlayerSlots->rectWidth / gPlayerSlots->rectHeight;
        gDPPipeSync(glist++);
        gDPSetRenderMode(glist++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    }

    if ((gViewportInsetLeft != 0) || (gViewportInsetRight != 0) || (gViewportInsetTop != 0) || (gViewportInsetBottom != 0) || (gViewportInsetActive != 0)) {
        G00Entry *vpEntry;
        s16 width, height;
        vpEntry = cameraFindViewportEntry(0);
        gPlayerSlots->rect[0] = vpEntry->left + gViewportInsetLeft;
        gPlayerSlots->rect[2] = vpEntry->right - gViewportInsetRight;
        gPlayerSlots->rect[1] = vpEntry->top + gViewportInsetTop;
        gPlayerSlots->rect[3] = vpEntry->bottom - gViewportInsetBottom;

        gDPPipeSync(glist++);
        gDPSetCycleType(glist++, G_CYC_FILL);
        gDPSetRenderMode(glist++, 0, 0);
        gSPClearGeometryMode(glist++, G_ZBUFFER);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);

        if (gViewportInsetLeft != 0) {
            gDPFillRectangle(glist++, vpEntry->left, vpEntry->top, gPlayerSlots->rect[0], vpEntry->bottom);
        }
        if (gViewportInsetRight != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[2], vpEntry->top, vpEntry->right, vpEntry->bottom);
        }
        if (gViewportInsetTop != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[0], vpEntry->top, gPlayerSlots->rect[2], gPlayerSlots->rect[1]);
        }
        if (gViewportInsetBottom != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[0], gPlayerSlots->rect[3], gPlayerSlots->rect[2], vpEntry->bottom);
        }

        gDPPipeSync(glist++);
        gPlayerSlots->rectWidth = gPlayerSlots->rect[2] - gPlayerSlots->rect[0];
        gPlayerSlots->rectHeight = gPlayerSlots->rect[3] - gPlayerSlots->rect[1];
        if ((gViewportInsetLeft == 0) && (gViewportInsetRight == 0) && (gViewportInsetTop == 0) && (gViewportInsetBottom == 0)) {
            gViewportInsetActive = 0;
        } else {
            gViewportInsetActive = 1;
        }
        gViewportInsetLeft = 0;
        gViewportInsetRight = 0;
        gViewportInsetTop = 0;
        gViewportInsetBottom = 0;
        width = vpEntry->right - vpEntry->left;
        height = vpEntry->bottom - vpEntry->top;
        gPlayerSlots->aspect = (f32)width / height;
        gDPSetRenderMode(glist++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    }

    glist = renderCallbacksExecute(renderCallbacksExecute(renderScreenSpaceEffects(renderCallbacksExecute(gfxInit2DDisplayList(glist), 3), gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ), 5), 7);
    if (gSaveIconTimer != 0) {
        gSaveIconTimer -= 1;
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
        gGfxTaskBufferCap = 0x1770;
    } else {
        gGfxTaskBufferCap = numScreens * 3000;
    }
    gGfxTaskBuffers[0] = heapAlloc(gGfxTaskBufferCap * sizeof(Gfx));
    gGfxTaskBuffers[1] = heapAlloc(gGfxTaskBufferCap * sizeof(Gfx));
    gfxEndDisplayList(gfxClearFramebuffer(gGfxTaskBuffers[0], 0), 0, &gGfxListCommandCount, 1);
    gfxEndDisplayList(gfxClearFramebuffer(gGfxTaskBuffers[1], 1), 1, &gGfxListCommandCount, 1);
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
    *outSize = glistp - gGfxTaskBuffers[bufIdx];
    if (*outSize >= gGfxTaskBufferCap) {
        faultSetMessage(0x12, 0, 0, 0);
    }
}


void gfxEndSubDisplayList(Gfx *inGlist, FrameMatrices *frame, s32 *outSize, u8 fullSync) {
    Gfx *glistp = inGlist;

    if (fullSync) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *outSize = glistp - frame->subDisplayList;
}


void mapLoadLevel(void) {
    void *mapChunkAsset;
    void *loadedAsset;
    u8 *modelAsset;
    f32 audioVolume;
    s32 activeMap;
    s32 songId;

    gWatchdogPaused = 1;
    gMapActiveFrameCount = 0;
    gMapWarpCount = 0;
    gMapPauseCount = 0;
    gGlobalPauseFlags &= ~0x14C003;
    menuSeedRandom();
    gMinigameCoinCount = 0;
    gGfxSubListEnabled = 0;
    gGfxBufferIndex = 0;
    gFrameCounter = 0;
    gGameFrameCounter = 0;
    audioResetAll();
    gEnemyDefeatCount = 0;
    *gPhysicalContPads = 0;
    texCacheReset();
    gScreenRenderFlags &= ~0x30;
    effectSpritePoolReset();
    if (gGameMode == 1) {
        gGameMode = 0;
    }
    gMapLoadFrame = gFrameCounter;
    D_80744500 = 0;
    timerQueueInit();

    gCurrentMap = gInitialMap;
    activeMap = gCurrentMap;
    if (gCurrentMap != 0x50) {
        if (gCurrentMap != 0x51) {
            gGlobalPauseFlags |= 0x30030;
        } else {
            gGlobalPauseFlags &= ~0x30030;
        }
    } else {
        gGlobalPauseFlags &= ~0x10030;
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
            gPlayerCharacterId[0] = 6;
        }
    } else {
        gPlayerCharacterId[0] = 7;
    }
    gSavedMapModelData = NULL;
    collisionInitTables();
    textFontInitTables();
    gfxResourceListReset();
    vtxGradientSetColorA(0xFF, 0xFF, 0xFF);
    vtxGradientSetColorB(0xFF, 0xFF, 0xFF);
    if (gGameMode == 0) {
        gZbufferDistanceTable = assetLoad(0x13, 0, 1, 1);
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
        menuSetupDemoPlayback();
        playerAllocSlots(gInitialExit);
        effectResetLists();
        loadedAsset = assetLoad(0x10, gCurrentMap, 1, 1);
        spawnNodesInitForMap(loadedAsset);
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
        gModelSlotAppendBlocked = 0;
        if ((transitionGetState() == 0) && (gGameMode != 2)) {
            if ((gCurrentMap == 0x11) && (flagGet(0x302, 0) != 0)) {
                sfxAllocateChannel(0x74, 1.0f);
            } else {
                songId = gMapAudioTable[gCurrentMap].songId;
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
        modelEmittersInit();
    }
    menuCheckMapTransitionOnLoad();
    mapSpawnPendingPickups();
    gScreenRenderFlags ^= 1;
    gScreenFadeProgress = 31.0f;
    gScreenRenderFlags |= 4;
    gScreenFadeRate = -1.0f;
    if ((gNextGameMode != 2) && (gTransitionFadeType == 1)) {
        sfxAllocateChannel(0x2B, 1.0f);
    }
    underwaterTintReset();
    screenWipeReset();
    particleFindPathIndices(gCurrentLevelIndex);
    frameTimingReset(gCurrentMap);
    gWatchdogPaused = 0;
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

