#include "common.h"
#include "sched.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Struct806C7C94;

typedef struct {
    Mtx unk0;
    Mtx unk40;
    Mtx unk80;
    Mtx unkC0;
    Mtx unk100;
    Mtx unk140;
    Mtx unk180;
    u8 pad1C0[0xDB0 - 0x1C0];
    Gfx unkDB0[5];
    Gfx unkDD8[1];
} Struct_8076A048;

void func_80024000(void);
void func_80026FD0(s32);
void func_8002EC08(s32);
void func_805FB7E4(void);
void viModeSetup();
void func_805FBC5C(void);
void func_805FBE04(void);
void mainThreadLoop(s32);
void func_805FC2B0(void);
s32 pauseStateUpdate(void);
s32 func_805FC98C(void);
s32 func_805FCA64(void);
void playerViewsBuildMatrices(void *);
Gfx *func_805FCFD8(Gfx *);
Gfx *gfxInit2DDisplayList(Gfx *);
void func_805FD088(Struct_8076A048 *, Gfx **, Gfx **);
Gfx *func_805FE398(Gfx *);
Gfx *func_805FE4D4(Gfx *);
void func_805FE544(u8);
Gfx *func_805FE634(Gfx *, u8);
void func_805FE71C(Gfx *, u8, s32 *, u8);
void func_805FE7B4(Gfx *, s32, s32 *, u8);
void func_805FE7FC(void);
void func_805FEE84(s8, s8, s8, s8);
void func_805FEEB8(s32 *, s32);
void mapSlotArrayInit(void);
void func_805FF670(void);
void mapSlotFree(s32);
void func_806003EC(s16);
s32 func_8060042C(s16);
void frameTimingReset(s32);
void frameTimingUpdate(void);
void timerQueueInit(void);
void timerQueueAdd(void *, s32, s32, s32, s32);
void timerQueueUpdate(void);
void audioInit(void);
void sfxPlayCurrent(void);
void sfxUpdateChannels(void);
void sfxAllocateChannel(s32, f32);
void sfxUpdateLevelAmbient(void);
void audioResetAll(void);
void sfxUpdateSourceGroups(void);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void seqSetChannelVolumeScale(s32, f32);
void controllerInit(void);
void controllerStartRead(void);
void controllerWaitRead(void);
void controllerUpdate(void);
void dmaReadAssetDecompress(s32, void *, void *, s32, s32, s32, s32);
void func_8060FFF0(void);
void schedSubmitGfxTask(void *, s32, s32, u8, s32, s32);
void func_80610268(s32);
void *heapAlloc(s32);
void heapTickDeferredFrees(void);
void camResetAllPlayers(void);
void camInit(s32);
void screenWipeReset(void);
s32 screenWipeDraw(s32);
f32 cameraStepAspectScale(void);
Gfx *gfxPassThrough(s32);
s32 playerViewsRender(Gfx *, Struct_8076A048 *, u32);
s32 func_8062CA0C(s32, s32, s32, s32);
void mapHeaderLoad(s32);
void renderEntryListsReset(void);
void modelSkipListClear(void);
void modelTypeCountsInit(void);
void modelSlotsAllocate(s32, s32);
void displayListFreeQueueReset(void);
void csTimerQueueClear(void);
void mapChunkAllocLists(s32);
void mapLoadNodeAsset(s32);
void mapSearchTableReset(void);
void mapSearchTableUpdateVisibility(void);
void lightInitGlobals(void);
void lightClearCount(void);
void billboardCacheInit(void);
void billboardCacheEvictStale(void);
void effectUpdateAndDispatch(void);
void triggerZoneUpdate(void);
void actorInitTargetEntries(void);
void actorInitEntryPoints(void);
void particleFindPathIndices(s16);
void collisionInitTables(void);
void dmaDrainQueueAndFreeBuffer(void);
s32 assetLoad(s32, s32, s32, s32);
void assetFreeBuffer(s32, s32, s32);
void collisionBstRebalanceAll(void);
void modelSlotExpireNextBuffers(void);
void collisionBufferCacheUpdate(void);
void actorInit(void);
void actorUpdateSpawnsWrapper(void);
void actorGlobalCallbacksReset(void);
void actorUpdateWhilePaused(void);
void actorMapModelsSetup(s32, s32, s32);
void actorListInitOffsets(void);
void actorProximityUpdate(void);
void actorSpawnInitialSet(void);
void texCacheReset(void);
void texCacheUpdate(void);
s32 renderCallbacksExecute(s32, s32);
void renderCallbacksReset(void);
void func_806C7C10(void);
Struct806C7C94 *cameraFindViewportEntry(s32);
void func_806C7D40(s32);
void func_806C95D0(s32);
void func_806C9AE0(void);
void playerSetLargeModeScale(f32);
void playerWaypointPathsLoad(s16);
void gridBuildNodeLists(void);
s32 slotQueueBuildDisplayList(s32);
void textFontInitTables(void);
void textFontAgeSheets(void);
void gfxResourceListReset(void);
s32 lensFlareBuildDisplayList(s32);
void func_80700BF4(void);
void func_80701C90(void);
s32 func_80701CA0(s32);
void *screenFadeUpdate(void *, u8);
Gfx *func_80704960(Gfx *);
void vtxGradientSetColorA(s32, s32, s32);
void vtxGradientSetColorB(s32, s32, s32);
void gfxBackgroundReset(void);
s32 healthHudDrawAll(s32);
void func_807094D0(s32, u32 *);
void transitionRunFrame(s32, s32);
void func_8070B308(s32);
s32 func_8070B318(void);
void resListTick(void);
void func_8070E8C8(void);
void effectSpritePoolReset(void);
void func_80712A40(void);
void func_80712B80(void);
void func_80712BD4(void);
s32 screenStateTickAndDraw(s32);
s32 menuIsTransitionTypeAOrE(void);
void effectResetLists(void);
void effectUpdateAll(s32);
void commandStateInit(void);
void commandQueueReset(void);
void pathFreeAsset(s32);
void func_80724C78(s32);
void volumeTriggerTableInit(s32);
void proxPathListClear(void);
void flagsClearAllBank2(void);
s32 flagGet(s32, s32);
void faultSetMessage(s32, s32, s32, s32);
void faultThreadInit(void);
void gridTickPlayers(void);

void seg11DmaRead(s32, s32, void *);
void gunzip(void *, void *, void *);
void schedCreate(void *, void *, s32, u8, u8);
void schedAddClient(void *, void *, OSMesgQueue *, s32, s32);
extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
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
extern u32 gSegmentTable[];

extern u8 D_8074458B[][4];

extern u8 D_80745BDC[][4];
extern s8 D_807467CC;
extern u8 D_807467E4;
extern s8 D_80746830;
extern s8 gPlayerCharacterId;
extern s32 D_80750AB0;
extern u8 D_80750AB8;
extern u8 D_80750AC0;
extern s16 D_80750AC4;

extern s32 D_8076A054;
extern s32 D_8076A058;
extern s16 D_8076A0AA;
extern u8 D_8076AEE0;

extern OSIoMesg D_807ECE00;
extern s16 *D_807ECDF4;
extern s8 D_807F6008;
extern s32 D_807F6010;
extern u32 D_807FBB60;
extern u32 D_807FBB64;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s32 D_807FF100;

extern s8 D_80744460;
extern u64 D_80761680;
extern OSMesgQueue *D_807655E0;

// .data 0x80744470-0x807445E0
u32 D_80744470[2] = { 0 };
u32 D_80744478 = 2;
u8 D_8074447C = 0;
u8 D_80744480 = 0;
u8 D_80744484 = 0;
u8 D_80744488 = 0;
u8 D_8074448C = 0;
s16 D_80744490 = 0x140;
s16 D_80744494 = 0xF0;
s16 D_80744498 = 0xA;
s16 D_8074449C = 0xA;
s16 D_807444A0 = 0x135;
s16 D_807444A4 = 0xE5;
s16 D_807444A8 = 0xA;
s16 D_807444AC = 0x28;
s16 D_807444B0 = 0xC7;
s16 D_807444B4 = 0xE5;
f32 D_807444B8 = 45.0f;
f32 D_807444BC = 1.0f;
s8 D_807444C0 = 0;
f32 D_807444C4 = 1500.0f;
f32 D_807444C8 = 10.0f;
f32 D_807444CC = 1.0f;
f32 D_807444D0 = 1.0f;
f32 D_807444D4 = 1.0f;
f32 D_807444D8 = 1.0f;
f32 D_807444DC = 1.0f;
f32 func_807444E0 = 1.0f;
s32 D_807444E4 = 0x28;
s32 D_807444E8 = 0;
u8 D_807444EC = 0;
u8 D_807444F0 = 0;
u8 D_807444F4 = 0;
u8 D_807444F8 = 0;
u8 D_807444FC = 0;
s8 D_80744500 = 0;
s8 D_80744504 = 0;
s16 D_80744508 = 0;
u8 D_8074450C = 1;
u32 D_80744510[7] = { 0, 0, 0, 0, 0x3000000, 0, 0 };
s8 D_8074452C = 0;
u32 D_80744530[5] = { 0 };
u32 D_80744544 = 0;
u32 D_80744548[8] = { 0x644141, 0x4100005A, 0x41414100, 0x504141, 0x41000046, 0x41414100, 0x3C4141, 0x41000000 };
u32 D_80744568[7] = { 0x644141, 0x4100005A, 0x41414100, 0x504141, 0x41000046, 0x41414100, 0x464141 };
u32 D_80744584 = 0x41000000;
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
u8 gScheduler[0x280];
u32 D_80767CC0;
s32 D_80767CC4;
u8 D_80767CC8[16];
u8 D_80767CD8[0x10];
Mtx D_80767CE8;
u8 D_80767D28[320];
Mtx D_80767E68;
u8 D_80767EA8[4080];
Mtx D_80768E98;
u8 D_80768ED8[320];
Mtx D_80769018;
u8 D_80769058[4080];
u8 *D_8076A048;
u32 D_8076A04C;
Gfx *D_8076A050[4];
u8 *D_8076A060;
s32 gFrameCounter;
s32 D_8076A068;
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
s32 D_8076A0A0;
u8 D_8076A0A4;
u8 D_8076A0A5;
u16 D_8076A0A6;
s32 gCurrentMap;
s32 D_8076A0AC;
u8 D_8076A0B0;
u8 D_8076A0B1;
u8 D_8076A0B2;
u8 D_8076A0B3;
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

void func_805FB7E4(void) {
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

    fb = (u16 *)D_80744470[0];
    end = (u16 *)((u8 *)fb + 0x25800);
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();

    compressedBuf = (u8 *)D_80744470[1] + 0xC800;
    seg11DmaRead(0x38, 0x10, compressedBuf);
    seg11DmaRead(*(s32 *)compressedBuf + 0x178, 0x10, compressedBuf);
    seg11DmaRead(*(s32 *)compressedBuf, *(s32 *)(compressedBuf + 4) - *(s32 *)compressedBuf, compressedBuf);

    gzipSrc = compressedBuf;
    gzipDst = (u8 *)D_80744470[1];
    src = (u16 *)D_80744470[1];
    gunzip(&gzipSrc, &gzipDst, (u8 *)D_80744470[1] + 0x15E00);

    fb = (u16 *)((u8 *)D_80744470[0] + 0xF080);
    i = 0;
    do {
        j = 0;
loop_5:
        *fb++ = *src++;
        *fb++ = *src++;
        *fb++ = *src++;
        *fb++ = *src++;
        j += 4;
        if (j != 0xC0) goto loop_5;
        fb = (u16 *)((u8 *)fb + 0x100);
        i++;
    } while (i < 0x30);

    fb = (u16 *)D_80744470[1];
    end = (u16 *)((u8 *)fb + 0x25800);
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();
}


void loadOverlay(u8, u8, s32);

void viModeSetup(overlaySlot)
u8 overlaySlot;
{
    u8 overlayId;
    s32 overlayParam;

    overlayId = 1;
    overlayParam = 0;
    func_806003EC(D_8076A0AA);
    if (D_807445A4 && D_807445A4) {}  // FAKE: deadsweep dead statement (steers uopt; keeps the D_807445A4 address out of a register)
    if (gCurrentMap == 0x28) {
        D_8074450C = 2;
    } else {
        D_8074450C = 1;
    }
    switch (D_807444EC) {
    case 3:
        overlayId = 9;
    case 4:
        if (overlayId == 1) {
            overlayId = 10;
        }
        D_80744498 = 0;
        D_8074449C = 0;
        D_807444A0 = D_8074450C * 0x140 - 1;
        D_807444A4 = D_8074450C * 0xF0 - 1;
        break;
    default:
        overlayParam = func_8060042C(gCurrentMap);
        if (D_807FBB64 & 1) {
            overlayId = 7;
        } else if (D_807FBB64 & 0x1000) {
            overlayId = 6;
        } else if (D_807FBB64 & 0x104000) {
            overlayId = 8;
        } else if (D_807FBB64 & 0x80000) {
            overlayId = 4;
        } else if (D_807FBB64 & 0x2000) {
            overlayId = 5;
        } else if (D_807FBB64 & 0x4000000) {
            overlayId = 3;
        } else if (D_807FBB64 & 0x40000000) {
            overlayId = 2;
        }
        D_80744498 = D_8074450C * 10;
        D_8074449C = D_8074450C * 10;
        D_807444A0 = D_8074450C * 0x136 - 1;
        D_807444A4 = D_8074450C * 0xE6 - 1;
        break;
    }
    loadOverlay(overlaySlot, overlayId, overlayParam);
    if (D_807445A4 == 0) {
        osViSetMode(&osViModeTable[(&D_80744584)[osTvType + osTvType + D_8074450C]]);
        if (D_807445A0 == 0) {
            osViBlack(1);
        }
        *(u8 *)D_80744510 = 0;
        D_807445A0 = 0;
    } else {
        *(u8 *)D_80744510 = 1;
        D_807445A0 = 1;
        D_807445A4 = 0;
        func_805FB7E4();
    }
    osViSetSpecialFeatures(0x42);
    D_80744490 = D_8074450C * 0x140;
    D_80744494 = D_8074450C * 0xF0;
    D_807444AC = D_8074449C + D_8074450C * 0x1E;
    D_807444B0 = D_807444A4 - D_8074450C * 0x1E;
    D_807444A8 = D_8074449C;
    D_807444B4 = D_807444A4;
}

void func_805FBC5C(void) {
    D_8076A084 = gSegmentTable[0x49] - gSegmentTable[0x48];
    osCreateMesgQueue(&D_807655F0, &D_80765608, 0x32);
    osCreateMesgQueue(&D_807656D0, &D_807656E8, 0xC0);
    schedCreate(&gScheduler, &D_80765A00[0x810], 0x19, D_8074458B[osTvType + osTvType][0], 1);
    osCreateMesgQueue(&D_807659E8, &D_80765A00, 0x10);
    schedAddClient(&gScheduler, &D_80767CD8, &D_807659E8, 1, 1);
    gCurrentMap = D_807444E4;
    viModeSetup(0);
    D_8076A07C = 5;
    func_8060FFF0();
    controllerInit();
    audioInit();
    func_8070B308(0);
    faultThreadInit();
    osWritebackDCacheAll();
    osCreateMesgQueue(&D_8076A110, &D_8076A108, 2);
    osSetTimer(&D_8076A130, 0xD693A4, 0, &D_8076A110, D_8076A128);
    sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
}

void func_805FBE04(void) {
    s32 stackpad1;
    f32 aspectScale;

    osWritebackDCacheAll();
    osInvalDCache((void *)0x80000000, 0x800000);
    D_8076A080 = &D_807FF100;
    dmaReadAssetDecompress(D_8000DDE4, D_8076A080, &D_8076A084, 0, 0, 0, 0);
    D_8076A0A4 = 0;
    controllerWaitRead();
    gFrameCounter = 0;
    D_8076A068 = 0;
    D_807467CC = 0;
    D_8076A0AC = 4;
    D_807FBB60 = 0x30030;
    D_8076A0B1 |= 1;
    D_8076A0B2 = 0;
    gScreenFadeProgress = 31.0f;
    D_8076A0B1 |= 4;
    modelSkipListClear();
    func_806C9AE0();
    flagsClearAllBank2();
    mapSlotArrayInit();
    csTimerQueueClear();
    aspectScale = cameraStepAspectScale();
    guTranslate(&D_80767E68, 0.0f, 0.0f, 0.0f);
    guTranslate(&D_80769018, 0.0f, 0.0f, 0.0f);
    guPerspective(&D_80767CE8, &D_8076A09C, D_807444B8, D_807444BC * aspectScale, D_807444C8, D_807444C4, 1.0f);
    guPerspective(&D_80768E98, &D_8076A09C, D_807444B8, D_807444BC * aspectScale, D_807444C8, D_807444C4, 1.0f);
}

extern s16 D_8074682C;
extern u8 D_807F059C;

void mainThreadLoop(s32 unused) {
    u8 first;
    s32 receivedMesg;

    first = 1;
    if (osTvType == 0) {
        D_807444BC = 1.25f;
    }
    func_805FBC5C();
    osViSetSpecialFeatures(0x42);
    func_805FBE04();
    D_8076A070[0] = D_80767CC0 - 2;
    osRecvMesg(&D_8076A110, (OSMesg *)&receivedMesg, 1);
    while (1) {
        D_8074682C = 0xC8;
        while (D_80744460 != 0) {
        }
        if ((D_8076A0B1 & 1) && D_8076A0B2 == 0) {
            func_805FE7FC();
            if (D_807444F8 == 2) {
                D_807FBB60 |= 0x200;
                D_80744504 = 8;
            }
        }
        switch (D_807444EC) {
            case 6:
                transitionRunFrame(D_807444E4, D_807444E8);
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
                func_805FC2B0();
                break;
        }
        timerQueueUpdate();
        dmaDrainQueueAndFreeBuffer();
        func_80610268(0x4D2);
        if (D_807F059C != 0) {
            func_80610268(0x929);
        }
        frameTimingUpdate();
        if (D_807444EC == 0 || D_807444EC == 1 || D_807444EC == 7) {
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
        if ((D_8076A0B1 & 1) && gScreenFadeProgress == 31.0f) {
            D_8076A0B2--;
        }
        D_807444F0 = D_807444EC;
    }
}

void func_805FC2B0(void) {
    Gfx *glist;
    Gfx *gfxEnd;

    controllerStartRead();
    schedSubmitGfxTask(D_8076A050[D_807444FC], D_8076A088, 3, (D_8076A0A4 != 0) ? 0 : 1, 0x4D2, 1);
    if (D_8076A0A4 != 0) {
        schedSubmitGfxTask((u8 *)&D_80767CE8 + D_807444FC * 0x11B0 + 0xDB0, D_8076A08C, 0, 1, 0x929, 1);
    }
    D_807444FC ^= 1;
    gFrameCounter++;
    if (!(D_807FBB60 & 2)) {
        D_8076A068++;
    }
    D_8076A048 = (u8 *)&D_80767CE8 + D_807444FC * 0x11B0;
    controllerUpdate();
    if (pauseStateUpdate() != 0) {
        billboardCacheEvictStale();
        actorUpdateWhilePaused();
        effectUpdateAll(1);
        sfxUpdateLevelAmbient();
        sfxUpdateSourceGroups();
        sfxUpdateChannels();
        playerViewsBuildMatrices(D_8076A048);
    } else {
        lightClearCount();
        actorUpdateSpawnsWrapper();
        playerViewsBuildMatrices(D_8076A048);
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
    D_8076A150 = D_8076A050[D_807444FC];
    if ((D_8076A0B1 & 1) && gScreenFadeProgress == 31.0f) {
        glist = D_8076A050[D_807444FC];
        gfxEnd = D_8076A048 + 0xDB0;
        renderCallbacksReset();
    } else {
        func_805FD088((Struct_8076A048 *)D_8076A048, &glist, &gfxEnd);
    }
    if (D_807FBB60 & 0x100) {
        D_807FBB60 &= ~0x100;
        func_807094D0(2, &D_807FBB60);
    } else if (D_807FBB60 & 0x200) {
        D_80744504--;
        if (D_80744504 == 0) {
            D_807FBB60 &= ~0x200;
            func_807094D0(3, &D_807FBB60);
        }
    } else {
        glist = screenFadeUpdate(glist, D_8076AEE0);
    }
    if (D_8076A0A4 != 0 && D_807444EC != 6) {
        func_805FE71C(glist, D_807444FC, &D_8076A088, 0);
        func_805FE7B4(gfxEnd, (s32)D_8076A048, &D_8076A08C, 1);
    } else {
        func_805FE71C(glist, D_807444FC, &D_8076A088, 1);
    }
}


#include "actor.h"

extern Actor *gSpawnedActor;
s32 menuIsTransitionType8(void);
s32 menuIsTransitionType6(void);
s32 menuIsTransitionTypeC(void);
s32 menuIsTransitionTypeD(void);
Actor *actorFindByType(u16);
void actorDespawn(void *);
s32 actorSpawn(s32, s32);
void sfxStopChannel(s32, s32);
void slotQueuePopActiveMask(void);
void slotQueueReset(void);

s32 pauseStateUpdate(void) {
    Actor *actor;

    if ((gCurrentMap == 0x50) || (menuIsTransitionType8() == 0 && menuIsTransitionType6() == 0 && menuIsTransitionTypeC() == 0 && menuIsTransitionTypeD() == 0)) {
        D_807FBB60 &= ~1;
    }
    if (D_807FBB60 & 2) {
        if ((D_807FBB60 & 0x40) && (menuIsTransitionType6() != 0 || menuIsTransitionTypeC() != 0)) {
            sfxStopChannel(0x22, 0);
            D_807FBB60 &= 0xFFEBFFBD;
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
            if (!(D_807FBB60 & 1)) {
                D_807445C8 = 0;
            } else {
                D_807445C8 -= 1;
                if (D_807445C8 <= 0) {
                    if ((menuIsTransitionType6() != 0 || menuIsTransitionTypeC() != 0) && !(D_807FBB60 & 0x40000)) {
                        sfxAllocateChannel(0x22, 1.0f);
                        sfxAllocateChannel(0x29, 1.0f);
                        if (gPlayerCount < 2 && menuIsTransitionTypeC() == 0) {
                            actorSpawn(0x5F, 0);
                            D_807FBB60 |= 0x100000;
                        } else {
                            actorSpawn(0x157, 0);
                        }
                        gSpawnedActor->renderFlags |= 2;
                    }
                    D_807445C0 = osGetTime();
                    D_807FBB60 ^= 1;
                    D_807FBB60 |= 2;
                }
            }
        }
        if ((D_807FBB60 & 1) && D_807445C8 <= 0) {
            slotQueueReset();
            D_807445C8 = 2;
        }
    }
    return D_807FBB60 & 2;
}

s32 func_805FC98C(void) {
    u64 t;
    u64 x;

    t = osGetTime();
    x = t - D_807445B8;
    if (D_807FBB60 & 2) {
        x = x - t + D_807445C0;
    }
    x = __ll_mul(x, 0x40);
    x = __ull_div(x, 0xBB8);
    x = __ull_div(x, 0xF4240);
    return (u32) x + D_80750AB0;
}

s32 func_805FCA64(void) {
    s32 canRenderHud;

    canRenderHud = (D_8076A0B1 & 0x10) == 0;
    if (canRenderHud != 0) {
        canRenderHud = D_8076A0B3 == 0;
    }
    return canRenderHud & 0xFF;
}

extern u8 D_80750AB4;
f32 func_806276AC(void);
void func_8062754C(f32);
f32 sinApprox(f32);

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0xFA - 0x94];
    u8 unkFA;
} HeldActorData;

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
    HeldActorData *held;
    s32 i;
    f32 fov;
    f32 aspect;
    f32 offs;
    s32 *cc;

    aspect = cameraStepAspectScale();
    if (D_807445CC && D_807445CC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (gPlayerCount >= 2 && D_80750AB8 == 1) {
        func_8062754C(func_806276AC());
    }
    for (i = 0; i < D_80750AB4; i++) {
        if (PLAYER_VIEWS[i].unk0 != 0) {
            if (ABS_DIFF(PLAYER_VIEWS[i].unk210, PLAYER_VIEWS[i].unk228) < 0.5 && ABS_DIFF(PLAYER_VIEWS[i].unk218, PLAYER_VIEWS[i].unk230) < 0.5) {
                offs = 1.0f;
            } else {
                offs = 0.0f;
            }
            guLookAtHilite(&PLAYER_VIEWS[i].unk8[D_807444FC], &PLAYER_VIEWS[i].unk190[D_807444FC], &PLAYER_VIEWS[i].unk1D0[D_807444FC],
                           PLAYER_VIEWS[i].unk210 + offs, PLAYER_VIEWS[i].unk214, PLAYER_VIEWS[i].unk218 + offs,
                           PLAYER_VIEWS[i].unk228, PLAYER_VIEWS[i].unk22C, PLAYER_VIEWS[i].unk230,
                           PLAYER_VIEWS[i].unk240, PLAYER_VIEWS[i].unk244, PLAYER_VIEWS[i].unk248,
                           D_807444CC, D_807444D0, D_807444D4,
                           D_807444D8, D_807444DC, func_807444E0,
                           0x20, 0x20);
            fov = PLAYER_VIEWS[i].unk280;
            cc = D_807445CC;
            pl = (PlayerActorData *)PLAYER_VIEWS[i].unk4->unk174;
            pa = pl->unk104;
            held = (HeldActorData *)pa->unk174;
            if (pl->unk1F0 & 0x100) {
                fov += 0.5 * sinApprox(cc[0] * 0.1);
            } else if (pl->unk1F0 & 0x2000000) {
                fov += 0.05 * sinApprox(cc[0] * 0.4);
            } else if (held->unkFA != 0 && PLAYER_VIEWS[i].unk220 < held->unk90 + 3.0f) {
                fov += 0.04 * sinApprox(cc[0] * 0.1);
            }
            guPerspective(&PLAYER_VIEWS[i].unk88[D_807444FC], (u16 *)(i * 0x2F0 + (s32)gPlayerSlots + 0x188), PLAYER_VIEWS[i].unk27C, fov * aspect, PLAYER_VIEWS[i].unk284, PLAYER_VIEWS[i].unk288, 1.0f);  // FAKE: operand order (i*0x2F0 first) keeps this address from CSE with the PLAYER_VIEWS[i] address
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

Gfx *func_805FCFD8(Gfx *glistp) {
    if (D_8074450C == 2) {
        gSPDisplayList(glistp++, D_1000068);
    } else {
        gSPDisplayList(glistp++, D_1000040);
    }
    return glistp;
}


Gfx *gfxInit2DDisplayList(Gfx *glistp) {
    if (D_8074450C == 2) {
        gSPDisplayList(glistp++, D_1000030);
    } else {
        gSPDisplayList(glistp++, D_1000020);
    }
    return glistp;
}


void func_805FD088(Struct_8076A048 *frameGfx, Gfx **outGlist, Gfx **outGlist2) {
    Gfx *glist;
    Gfx *glist2;

    glist = D_8076A050[D_807444FC];
    gSPPerspNormalize(&frameGfx->unkDB0[0], D_8076A09C);
    glist2 = &frameGfx->unkDB0[1];
    gSPClipRatio(glist2++, FRUSTRATIO_3);

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(frameGfx));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));

    gSPSegment(glist2++, 0, 0);
    gSPSegment(glist2++, 2, osVirtualToPhysical(frameGfx));
    gSPSegment(glist2++, 1, osVirtualToPhysical(D_8076A080));

    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist2++, &D_1000090);

    glist = func_805FCFD8(glist);
    glist2 = func_805FCFD8(glist2);

    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    gDPSetScissor(glist2++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);

    guTranslate(&frameGfx->unk180, 0.0f, 0.0f, 0.0f);
    guOrtho(&frameGfx->unk80, 0.0f, (f32)((f64)(f32)D_80744490 - 1.0), (f32)((f64)(f32)D_80744494 - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->unkC0, 0.0f, (f32)(((f64)(f32)D_80744490 * 4.0) - 1.0), (f32)(((f64)(f32)D_80744494 * 4.0) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->unk140, 0.0f, (f32)((2.0 * (f64)(f32)D_80744490) - 1.0), (f32)((2.0 * (f64)(f32)D_80744494) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&frameGfx->unk100, (f32)((f64)(f32)gPlayerSlots->rect[0] * 4.0), (f32)(((f64)(f32)gPlayerSlots->rect[2] * 4.0) - 1.0), (f32)(((f64)(f32)gPlayerSlots->rect[3] * 4.0) - 1.0), (f32)((f64)(f32)gPlayerSlots->rect[1] * 4.0), -20000.0f, 20000.0f, 1.0f);
    guPerspective(&frameGfx->unk0, &D_8076A09C, D_807444B8, cameraStepAspectScale() * D_807444BC, D_807444C8, D_807444C4, 1.0f);

    gSPMatrix(glist2++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    glist2 = gfxInit2DDisplayList(glist2);

    glist = func_805FE398(glist);
    gDPPipeSync(glist++);
    glist = func_805FE4D4(glist);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 6, 2, 0);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 4, 2, 0);
    glist = func_80704960(glist);

    gSPClipRatio(glist++, FRUSTRATIO_3);
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPClearGeometryMode(glist++, -1);
    gSPSetGeometryMode(glist++, 0x200404);

    glist = (Gfx *)func_80701CA0(playerViewsRender(glist, frameGfx, 0xFFFD));
    if (gPlayerCount == 1) {
        glist = (Gfx *)lensFlareBuildDisplayList((s32)glist);
    }
    glist = gfxPassThrough(screenWipeDraw(renderCallbacksExecute((s32)glist, 1)));

    if ((gCurrentMap == 0x4C) || (gCurrentMap == 0x50) || ((menuIsTransitionTypeAOrE() != 0) && (gCurrentMap != 0xD0))) {
        D_8076A0B1 &= ~0x10;
        D_8076A0B3 = 0;
    }

    if (((D_8076A0B1 & 0x10) || (D_8076A0B3 != 0)) && ((gPlayerCount == 1) || (D_80750AB8 == 1))) {
        f32 fadeAlpha;
        f32 fadeScale;
        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
        gSPClearGeometryMode(glist++, 1);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_80744498, D_8074449C, D_807444A0, D_807444A4);

        if (D_8076A0B3 != 0) {
            D_8076A0B3 -= 15;
            fadeScale = (f32)(1.0 - ((f64)(u32)D_8076A0B3 / 255.0));
            fadeAlpha = (f32)(D_807444AC - D_807444A8) * fadeScale;
            gDPFillRectangle(glist++, 0,
                (fadeAlpha < (f32)D_807444A8) ? (f32)D_807444A8 - fadeAlpha : 0.0f,
                (D_80744490 > 0) ? D_80744490 : 0,
                (fadeAlpha < (f32)D_807444AC) ? (f32)D_807444AC - fadeAlpha : 0.0f);
            gDPFillRectangle(glist++, 0, D_807444B0 + fadeAlpha, D_80744490, D_807444B4 + fadeAlpha);
            gPlayerSlots->rect[1] = (s16)(s32)((f32)D_807444AC - fadeAlpha);
            gPlayerSlots->rect[3] = (s16)(s32)((f32)D_807444B0 + fadeAlpha);
        } else {
            gDPFillRectangle(glist++, 0, D_807444A8, D_80744490, D_807444AC);
            gDPFillRectangle(glist++, 0, D_807444B0, D_80744490, D_807444B4);
            gPlayerSlots->rect[1] = (s16)D_807444AC;
            gPlayerSlots->rect[3] = (s16)D_807444B0;
        }
        gPlayerSlots->unk27A = (s16)(gPlayerSlots->rect[3] - gPlayerSlots->rect[1]);
        gPlayerSlots->unk280 = (f32)((f32)gPlayerSlots->unk278 / (f32)gPlayerSlots->unk27A);
        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    }

    if ((D_8074447C != 0) || (D_80744480 != 0) || (D_80744484 != 0) || (D_80744488 != 0) || (D_8074448C != 0)) {
        Struct806C7C94 *vpEntry;
        s16 dx, dy;
        vpEntry = cameraFindViewportEntry(0);
        gPlayerSlots->rect[0] = (s16)(vpEntry->unk4 + D_8074447C);
        gPlayerSlots->rect[2] = (s16)(vpEntry->unk8 - D_80744480);
        gPlayerSlots->rect[1] = (s16)(vpEntry->unk6 + D_80744484);
        gPlayerSlots->rect[3] = (s16)(vpEntry->unkA - D_80744488);

        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
        gSPClearGeometryMode(glist++, 1);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_80744498, D_8074449C, D_807444A0, D_807444A4);

        if (D_8074447C != 0) {
            gDPFillRectangle(glist++, vpEntry->unk4, vpEntry->unk6, gPlayerSlots->rect[0], vpEntry->unkA);
        }
        if (D_80744480 != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[2], vpEntry->unk6, vpEntry->unk8, vpEntry->unkA);
        }
        if (D_80744484 != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[0], vpEntry->unk6, gPlayerSlots->rect[2], gPlayerSlots->rect[1]);
        }
        if (D_80744488 != 0) {
            gDPFillRectangle(glist++, gPlayerSlots->rect[0], gPlayerSlots->rect[3], gPlayerSlots->rect[2], vpEntry->unkA);
        }

        gDPPipeSync(glist++);
        gPlayerSlots->unk278 = (s16)(gPlayerSlots->rect[2] - gPlayerSlots->rect[0]);
        gPlayerSlots->unk27A = (s16)(gPlayerSlots->rect[3] - gPlayerSlots->rect[1]);
        if ((D_8074447C == 0) && (D_80744480 == 0) && (D_80744484 == 0) && (D_80744488 == 0)) {
            D_8074448C = 0;
        } else {
            D_8074448C = 1;
        }
        D_8074447C = 0;
        D_80744480 = 0;
        D_80744484 = 0;
        D_80744488 = 0;
        dx = vpEntry->unk8 - vpEntry->unk4; dy = vpEntry->unkA - vpEntry->unk6; gPlayerSlots->unk280 = (f32)dx / (f32)dy;
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    }

    glist = (Gfx *)renderCallbacksExecute(renderCallbacksExecute(func_8062CA0C(renderCallbacksExecute((s32)gfxInit2DDisplayList(glist), 3), gPlayerSlots->unk210, gPlayerSlots->unk214, gPlayerSlots->unk218), 5), 7);
    if (D_807467E4 != 0) {
        D_807467E4 -= 1;
    }
    glist = (Gfx *)screenStateTickAndDraw(slotQueueBuildDisplayList(healthHudDrawAll((s32)glist)));
    textFontAgeSheets();
    texCacheUpdate();
    commandQueueReset();
    *outGlist = glist;
    *outGlist2 = glist2;
}


Gfx *func_805FE398(Gfx *glistp) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, 0, 0);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetDepthImage(glistp++, osVirtualToPhysical(D_8076A060));
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80744490, osVirtualToPhysical(D_8076A060));
    gDPSetFillColor(glistp++, 0xFFFCFFFC);
    gDPFillRectangle(glistp++, 0, 0, D_80744490 - 1, D_80744494 - 1);
    gDPPipeSync(glistp++);
    return glistp;
}


Gfx *func_805FE4D4(Gfx *glistp) {
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80744490, osVirtualToPhysical((void *)D_80744470[D_807444FC]));
    return glistp;
}


void func_805FE544(u8 numScreens) {
    if (D_807FBB64 & 1) {
        D_8076A058 = 0x1770;
    } else {
        D_8076A058 = numScreens * 3000;
    }
    D_8076A050[0] = heapAlloc(D_8076A058 * sizeof(Gfx));
    D_8076A050[1] = heapAlloc(D_8076A058 * sizeof(Gfx));
    func_805FE71C(func_805FE634(D_8076A050[0], 0), 0, &D_8076A088, 1);
    func_805FE71C(func_805FE634((void *)D_8076A054, 1), 1, &D_8076A088, 1);
}


Gfx *func_805FE634(Gfx *glistp, u8 fbIndex) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, 0, 0);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80744490, D_80744470[fbIndex]);
    gDPSetFillColor(glistp++, 0x10001);
    gDPPipeSync(glistp++);
    gDPFillRectangle(glistp++, 0, 0, D_80744490 - 1, D_80744494 - 1);
    return glistp;
}


void func_805FE71C(Gfx *inGlist, u8 bufIdx, s32 *outSize, u8 fullSync) {
    Gfx *glistp = inGlist;

    if (fullSync) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *outSize = glistp - (Gfx *)D_8076A050[bufIdx];
    if (*outSize >= D_8076A058) {
        faultSetMessage(0x12, 0, 0, 0);
    }
}


void func_805FE7B4(Gfx *inGlist, s32 basePtr, s32 *outSize, u8 fullSync) {
    Gfx *glistp = inGlist;

    if (fullSync) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *outSize = ((s32)glistp - basePtr - 0xDB0) >> 3;
}


void func_805FE7FC(void) {
    s32 mapChunkAsset;
    s32 loadedAsset;
    s32 modelAsset;
    f32 audioVolume;
    s32 activeMap;

    D_80746830 = 1;
    D_8076A090 = 0;
    D_8076A094 = 0;
    D_8076A098 = 0;
    D_807FBB60 &= 0xFFEB3FFC;
    func_80712A40();
    D_80750AC4 = 0;
    D_8076A0A4 = 0;
    D_807444FC = 0;
    gFrameCounter = 0;
    D_8076A068 = 0;
    audioResetAll();
    D_80744508 = 0;
    *D_807ECDF4 = 0;
    texCacheReset();
    D_8076A0B1 &= 0xFFCF;
    effectSpritePoolReset();
    if (D_807444EC == 1) {
        D_807444EC = 0;
    }
    D_8076A06C = gFrameCounter;
    D_80744500 = 0;
    timerQueueInit();
    

    gCurrentMap = D_807444E4;
    activeMap = gCurrentMap;
    if (gCurrentMap != 0x50) {
        if (gCurrentMap != 0x51) {
            D_807FBB60 |= 0x30030;
        } else {
            D_807FBB60 &= 0xFFFCFFCF;
        }
    } else {
        D_807FBB60 &= 0xFFFEFFCF;
    }
    if (activeMap == 2) {
        D_807444EC = 3;
    } else if (activeMap == 9) {
        D_807444EC = 4;
    } else {
        D_807444EC = 0;
    }
    viModeSetup(1, &gCurrentMap);
    
if (((s32) D_80750AC0 >= 2) && !(D_807FBB64 & 0x04000000)) {
        D_80750AC0 = 1;
    }
    func_806C7C10();
    playerSetLargeModeScale(0.0f);
    func_805FE544(D_80750AC0);
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
    if (D_807444EC == 0) {
        D_8076A0A0 = assetLoad(0x13, 0, 1, 1);
        gfxBackgroundReset();
        commandStateInit();
        playerWaypointPathsLoad(D_8076A0AA);
        proxPathListClear();
        mapSearchTableReset();
        pathFreeAsset(gCurrentMap);
        mapChunkAsset = assetLoad(1, gCurrentMap, 1, 1);
        renderEntryListsReset();
        mapChunkAllocLists(mapChunkAsset);
        mapHeaderLoad(mapChunkAsset);
        func_806C95D0(gCurrentMap);
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
        if (loadedAsset != 0) {
            assetFreeBuffer(loadedAsset, 0x8D0, 2);
        }
        func_80712B80();
        func_806C7D40(D_807444E8);
        effectResetLists();
        loadedAsset = assetLoad(0x10, gCurrentMap, 1, 1);
        func_80724C78(loadedAsset);
        if (loadedAsset != 0) {
            assetFreeBuffer(loadedAsset, 0x8DD, 2);
        }
        camResetAllPlayers();
        renderCallbacksReset();
        gridBuildNodeLists();
        func_8070E8C8();
        timerQueueAdd(sfxPlayCurrent, 2, 0, 0, 0);
        if (D_807FBB64 & 0x1000) {
            loadedAsset = assetLoad(0x16, gCurrentMap, 1, 1);
            func_80026FD0(loadedAsset);
            if (loadedAsset != 0) {
                assetFreeBuffer(loadedAsset, 0x8ED, 2);
            }
        }
        if (D_807FBB64 & 0x2000) {
            func_8002EC08(gCurrentMap);
        }
        collisionBstRebalanceAll();
        D_807F6008 = 0;
        if ((func_8070B318() == 0) && (D_807444EC != 2)) {
            if ((gCurrentMap == 0x11) && (flagGet(0x302, 0) != 0)) {
                sfxAllocateChannel(0x74, 1.0f);
            } else {
                activeMap = D_80745BDC[gCurrentMap][0];
                audioVolume = 1.0f;
                if ((activeMap == 6) || (activeMap == 0x1F)) {
                    audioVolume = 0.5493331552f;
                }
                sfxAllocateChannel(activeMap, audioVolume);
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
    func_80712BD4();
    func_805FF670();
    D_8076A0B1 ^= 1;
    gScreenFadeProgress = 31.0f;
    D_8076A0B1 |= 4;
    gScreenFadeRate = -1.0f;
    if ((D_807444F8 != 2) && (D_8076AEE0 == 1)) {
        sfxAllocateChannel(0x2B, 1.0f);
    }
    func_80701C90();
    screenWipeReset();
    particleFindPathIndices(D_8076A0AA);
    frameTimingReset(gCurrentMap);
    D_80746830 = 0;
}


void func_805FEE84(s8 val0, s8 val1, s8 val2, s8 val3) {
    D_8074447C = val0;
    D_80744480 = val1;
    D_80744484 = val2;
    D_80744488 = val3;
}

void func_805FEEB8(s32 *val, s32 alignment) {
    s32 rem;

    rem = *val % alignment;
    if (rem != 0) {
        *val = *val + alignment - rem;
    }
}

