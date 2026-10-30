#include "common.h"
#include "sched.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct80744464;

typedef struct {
    u32 romStart;
    u32 romEnd;
    u32 vramStart;
    u32 vramEnd;
    u32 bssStart;
    u32 bssEnd;
} SegEntry;

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
void func_805FB5C4(OSMesgQueue *, s32);
void func_805FB7E4(void);
void func_805FB944();
void func_805FBC5C(void);
void func_805FBE04(void);
void func_805FBFF4(s32);
void func_805FC2B0(void);
s32 func_805FC668(void);
s32 func_805FC98C(void);
s32 func_805FCA64(void);
void func_805FCA94(void *);
Gfx *func_805FCFD8(Gfx *);
Gfx *func_805FD030(Gfx *);
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
void func_805FF118(void);
void func_805FF670(void);
void func_805FFEF8(s32);
void func_806003EC(s16);
s32 func_8060042C(s16);
void frameTimingReset(s32);
void frameTimingUpdate(void);
void timerQueueInit(void);
void timerQueueAdd(void *, s32, s32, s32, s32);
void timerQueueUpdate(void);
void audioInit(void);
void audioThreadStop(s32);
void sfxPlayCurrent(void);
void func_806025D4(void);
void sfxAllocateChannel(s32, f32);
void func_80603450(void);
void audioResetAll(void);
void func_806057F8(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
void seqSetChannelVolumeScale(s32, f32);
void controllerInit(void);
void controllerStartRead(void);
void controllerWaitRead(void);
void controllerUpdate(void);
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
void func_8060E930(void);
void func_8060FFF0(void);
void func_80610044(void *, s32, s32, u8, s32, s32);
void func_80610268(s32);
void *func_80610FE8(s32);
void func_80611730(void);
void camResetAllPlayers(void);
void camInit(s32);
void screenWipeReset(void);
s32 screenWipeDraw(s32);
f32 func_8062A850(void);
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
void func_80658CCC(void);
void lightInitGlobals(void);
void lightClearCount(void);
void billboardCacheInit(void);
void func_8065D1AC(void);
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
void func_806787CC(void);
void actorGlobalCallbacksReset(void);
void func_806789E4(void);
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
void func_806D0430(f32);
void func_806F3760(s16);
void func_806F4778(void);
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
void func_8070DD44(void);
void func_8070E8C8(void);
void func_8070F570(void);
void func_80712A40(void);
void func_80712B80(void);
void func_80712BD4(void);
s32 func_80714060(s32);
s32 func_80714464(void);
void effectResetLists(void);
void func_80715270(s32);
void commandStateInit(void);
void commandQueueReset(void);
void pathFreeAsset(s32);
void func_80724C78(s32);
void volumeTriggerTableInit(s32);
void proxPathListClear(void);
void func_80731030(void);
s32 flagGet(s32, s32);
void faultSetMessage(s32, s32, s32, s32);
void faultThreadInit(void);
void func_806F6F28(void);

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

extern u8 mainThread_STACK[];

extern s32 D_8000DDCC;
extern s32 D_8000DDE4;
extern u32 gSegmentTable[];

extern u8 D_8074458B[][4];

extern u8 D_80745BDC[][4];
extern s8 D_807467CC;
extern u8 D_807467E4;
extern s8 D_80746830;
extern s8 D_8074E77C;
extern s32 D_80750AB0;
extern u8 D_80750AB8;
extern u8 D_80750AC0;
extern s16 D_80750AC4;
extern f32 D_807565B0;
extern f32 D_807565B4;
extern f32 D_807565B8;
extern f32 D_807565BC;
extern f32 D_807565C0;
extern f32 D_807565C4;
extern f32 D_807565C8;
extern f32 D_807565CC;
extern f64 D_807565D0;
extern f32 D_807565D8;


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
extern PlayerStruct *D_807FC924;
extern u8 D_807FC928;
extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s32 D_807FF100;


// .data 0x80744460-0x807445E0
s8 D_80744460 = 0;
Struct80744464 D_80744464 = { 0xF, 2, 0x1E };
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

// .bss 0x80761050-0x8076A160
OSMesgQueue D_80761050;
OSMesg D_80761068[0xF2];
OSThread D_80761430;
u8 D_807615E0[160];
u64 D_80761680;
u8 D_80761688[16216];
OSMesgQueue *D_807655E0;
u32 D_807655E4;
u64 D_807655E8;
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
s32 D_8076A064;
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
s32 D_8076A0A8;
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
u8 D_8076A158[8];

// as1 schedules by source line: each segment entry stays on one line (matches the target store order)
#define SEG ((SegEntry *)gSegmentTable)

void globalInit(OSMesgQueue *arg0, s32 arg1) {
    if (arg1 != 0) {
        func_805FB5C4(arg0, arg1);
    }
    D_807655E0 = arg0;
    SEG[0].vramStart = (u32)boot_VRAM; SEG[0].vramEnd = (u32)boot_VRAM_END; SEG[0].bssStart = (u32)boot_BSS_START; SEG[0].bssEnd = (u32)boot_BSS_END;
    SEG[1].vramStart = (u32)globalInit; SEG[1].vramEnd = (u32)global_VRAM_END; SEG[1].bssStart = (u32)&D_80761050; SEG[1].bssEnd = (u32)global_BSS_END;
    SEG[2].vramStart = (u32)multiplayer_VRAM; SEG[2].vramEnd = (u32)multiplayer_VRAM_END; SEG[2].bssStart = (u32)multiplayer_BSS_START; SEG[2].bssEnd = (u32)multiplayer_BSS_END;
    SEG[3].vramStart = (u32)minecart_VRAM; SEG[3].vramEnd = (u32)minecart_VRAM_END; SEG[3].bssStart = (u32)minecart_BSS_START; SEG[3].bssEnd = (u32)minecart_BSS_END;
    SEG[4].vramStart = (u32)bonus_VRAM; SEG[4].vramEnd = (u32)bonus_VRAM_END; SEG[4].bssStart = (u32)bonus_BSS_START; SEG[4].bssEnd = (u32)bonus_BSS_END;
    SEG[5].vramStart = (u32)race_VRAM; SEG[5].vramEnd = (u32)race_VRAM_END; SEG[5].bssStart = (u32)race_BSS_START; SEG[5].bssEnd = (u32)race_BSS_END;
    SEG[6].vramStart = (u32)critter_VRAM; SEG[6].vramEnd = (u32)critter_VRAM_END; SEG[6].bssStart = (u32)critter_BSS_START; SEG[6].bssEnd = (u32)critter_BSS_END;
    SEG[7].vramStart = (u32)boss_VRAM; SEG[7].vramEnd = (u32)boss_VRAM_END; SEG[7].bssStart = (u32)boss_BSS_START; SEG[7].bssEnd = (u32)boss_BSS_END;
    SEG[8].vramStart = (u32)arcade_VRAM; SEG[8].vramEnd = (u32)arcade_VRAM_END; SEG[8].bssStart = (u32)arcade_BSS_START; SEG[8].bssEnd = (u32)arcade_BSS_END;
    SEG[9].vramStart = (u32)jetpac_VRAM; SEG[9].vramEnd = (u32)jetpac_VRAM_END; SEG[9].bssStart = (u32)jetpac_BSS_START; SEG[9].bssEnd = (u32)jetpac_BSS_END;
    SEG[10].vramStart = (u32)menu_VRAM; SEG[10].vramEnd = (u32)menu_VRAM_END; SEG[10].bssStart = (u32)menu_BSS_START; SEG[10].bssEnd = (u32)menu_BSS_END;
    osDpSetStatus(4);
    osCreatePiManager(0x96, &D_80761050, D_80761068, 0xF2);
    D_80761680 = 0x12345678;
    osCreateThread(&D_80761430, 3, func_805FBFF4, NULL, &D_807655E0, 0xA);
    osStartThread(&D_80761430);
}


void func_805FB5C4(OSMesgQueue *arg0, s32 arg1) {
    u64 *p;
    u64 *q;
    Struct80744464 sp34;
    s32 pad[4];
    void *sp20;

    sp34 = D_80744464;
    if (arg1 == 2) {
        osViBlack(1);
        audioThreadStop(1);
        D_80744460 = 1;
        while (1) {
        }
    }
    osRecvMesg(arg0, &sp20, 1);
    D_80744460 = 1;
    audioThreadStop(1);
    osStopThread(&D_80761430);
    p = &D_807655E8; // FAKE: keeps the D_807655E8 address web split so IDO does not hoist it into $s0
    osSetThreadPri(NULL, 0xB);
    D_807655E8 = osGetTime();
    while (osGetTime() < *(q = p) + 0x22ADD7) { // FAKE: second pointer copy, see above
    }
    osViBlack(1);
    __osSpSetStatus(0xAAAA82);
    osDpSetStatus(0x1D6);
    func_8060E930();
    while (1) {
    }
}

void seg11DmaRead(s32 arg0, s32 arg1, void *arg2) {
    s32 sp2C;

    sp2C = D_8000DDCC;
    osWritebackDCache(arg2, arg1);
    osPiStartDma(&D_807ECE00, 0, 0, sp2C + arg0, arg2, (u32) arg1, &D_807655F0);
    osRecvMesg(&D_807655F0, NULL, 1);
    osInvalDCache(arg2, arg1);
}

void func_805FB7E4(void) {
    u16 *fb;
    u16 *end;
    void *pad0;
    void *pad1;
    u16 *src;
    u8 *temp_s0;
    void *pad2;
    void *pad3;
    u8 *sp3C;
    u8 *sp38;
    s32 i;
    s32 j;

    fb = (u16 *)D_80744470[0];
    end = (u16 *)((u8 *)fb + 0x25800);
    while (fb < end) {
        *fb++ = 1;
    }
    osWritebackDCacheAll();

    temp_s0 = (u8 *)D_80744470[1] + 0xC800;
    seg11DmaRead(0x38, 0x10, temp_s0);
    seg11DmaRead(*(s32 *)temp_s0 + 0x178, 0x10, temp_s0);
    seg11DmaRead(*(s32 *)temp_s0, *(s32 *)(temp_s0 + 4) - *(s32 *)temp_s0, temp_s0);

    sp3C = temp_s0;
    sp38 = (u8 *)D_80744470[1];
    src = (u16 *)D_80744470[1];
    gunzip(&sp3C, &sp38, (u8 *)D_80744470[1] + 0x15E00);

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

void func_805FB944(arg0)
u8 arg0;
{
    u8 var_a1;
    s32 var_a2;

    var_a1 = 1;
    var_a2 = 0;
    func_806003EC(D_8076A0AA);
    if (D_807445A4 && D_807445A4) {}  // FAKE: deadsweep dead statement (steers uopt; keeps the D_807445A4 address out of a register)
    if (D_8076A0A8 == 0x28) {
        D_8074450C = 2;
    } else {
        D_8074450C = 1;
    }
    switch (D_807444EC) {
    case 3:
        var_a1 = 9;
    case 4:
        if (var_a1 == 1) {
            var_a1 = 10;
        }
        D_80744498 = 0;
        D_8074449C = 0;
        D_807444A0 = D_8074450C * 0x140 - 1;
        D_807444A4 = D_8074450C * 0xF0 - 1;
        break;
    default:
        var_a2 = func_8060042C(D_8076A0A8);
        if (D_807FBB64 & 1) {
            var_a1 = 7;
        } else if (D_807FBB64 & 0x1000) {
            var_a1 = 6;
        } else if (D_807FBB64 & 0x104000) {
            var_a1 = 8;
        } else if (D_807FBB64 & 0x80000) {
            var_a1 = 4;
        } else if (D_807FBB64 & 0x2000) {
            var_a1 = 5;
        } else if (D_807FBB64 & 0x4000000) {
            var_a1 = 3;
        } else if (D_807FBB64 & 0x40000000) {
            var_a1 = 2;
        }
        D_80744498 = D_8074450C * 10;
        D_8074449C = D_8074450C * 10;
        D_807444A0 = D_8074450C * 0x136 - 1;
        D_807444A4 = D_8074450C * 0xE6 - 1;
        break;
    }
    loadOverlay(arg0, var_a1, var_a2);
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
    D_8076A0A8 = D_807444E4;
    func_805FB944(0);
    D_8076A07C = 5;
    func_8060FFF0();
    controllerInit();
    audioInit();
    func_8070B308(0);
    faultThreadInit();
    osWritebackDCacheAll();
    osCreateMesgQueue(&D_8076A110, &D_8076A108, 2);
    osSetTimer(&D_8076A130, 0xD693A4, 0, &D_8076A110, D_8076A128);
    func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
}

void func_805FBE04(void) {
    s32 stackpad1;
    f32 sp28;

    osWritebackDCacheAll();
    osInvalDCache((void *)0x80000000, 0x800000);
    D_8076A080 = &D_807FF100;
    func_8060B140(D_8000DDE4, D_8076A080, &D_8076A084, 0, 0, 0, 0);
    D_8076A0A4 = 0;
    controllerWaitRead();
    D_8076A064 = 0;
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
    func_80731030();
    func_805FF118();
    csTimerQueueClear();
    sp28 = func_8062A850();
    guTranslate(&D_80767E68, 0.0f, 0.0f, 0.0f);
    guTranslate(&D_80769018, 0.0f, 0.0f, 0.0f);
    guPerspective(&D_80767CE8, &D_8076A09C, D_807444B8, D_807444BC * sp28, D_807444C8, D_807444C4, 1.0f);
    guPerspective(&D_80768E98, &D_8076A09C, D_807444B8, D_807444BC * sp28, D_807444C8, D_807444C4, 1.0f);
}

#ifdef NON_MATCHING
extern s16 D_8074682C;
extern u8 D_807F059C;

void func_805FBFF4(s32 arg0) {
    u8 first;
    s32 sp38;

    first = 1;
    if (osTvType == 0) {
        D_807444BC = 1.25f;
    }
    func_805FBC5C();
    osViSetSpecialFeatures(0x42);
    func_805FBE04();
    D_8076A070[0] = D_80767CC0 - 2;
    osRecvMesg(&D_8076A110, (OSMesg *)&sp38, 1);
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
            func_80658CCC();
            func_80700BF4();
        }
        func_80611730();
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FBFF4.s")
#endif

void func_805FC2B0(void) {
    Gfx *sp2C;
    Gfx *sp28;

    controllerStartRead();
    func_80610044(D_8076A050[D_807444FC], D_8076A088, 3, (D_8076A0A4 != 0) ? 0 : 1, 0x4D2, 1);
    if (D_8076A0A4 != 0) {
        func_80610044((u8 *)&D_80767CE8 + D_807444FC * 0x11B0 + 0xDB0, D_8076A08C, 0, 1, 0x929, 1);
    }
    D_807444FC ^= 1;
    D_8076A064++;
    if (!(D_807FBB60 & 2)) {
        D_8076A068++;
    }
    D_8076A048 = (u8 *)&D_80767CE8 + D_807444FC * 0x11B0;
    controllerUpdate();
    if (func_805FC668() != 0) {
        func_8065D1AC();
        func_806789E4();
        func_80715270(1);
        func_80603450();
        func_806057F8();
        func_806025D4();
        func_805FCA94(D_8076A048);
    } else {
        lightClearCount();
        func_806787CC();
        func_805FCA94(D_8076A048);
        func_8065D1AC();
        actorProximityUpdate();
        collisionBufferCacheUpdate();
        modelSlotExpireNextBuffers();
        effectUpdateAndDispatch();
        actorGlobalCallbacksReset();
        triggerZoneUpdate();
        func_80715270(0);
        func_80603450();
        func_806025D4();
        func_806057F8();
        func_806F6F28();
    }
    func_8070DD44();
    D_8076A150 = D_8076A050[D_807444FC];
    if ((D_8076A0B1 & 1) && gScreenFadeProgress == 31.0f) {
        sp2C = D_8076A050[D_807444FC];
        sp28 = D_8076A048 + 0xDB0;
        renderCallbacksReset();
    } else {
        func_805FD088((Struct_8076A048 *)D_8076A048, &sp2C, &sp28);
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
        sp2C = screenFadeUpdate(sp2C, D_8076AEE0);
    }
    if (D_8076A0A4 != 0 && D_807444EC != 6) {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 0);
        func_805FE7B4(sp28, (s32)D_8076A048, &D_8076A08C, 1);
    } else {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 1);
    }
}


#include "actor.h"

extern Actor *D_807FBB44;
s32 func_80714360(void);
s32 func_8071432C(void);
s32 func_8071441C(void);
s32 func_807143E8(void);
Actor *actorFindByType(u16);
void actorDespawn(void *);
s32 actorSpawn(s32, s32);
void sfxStopChannel(s32, s32);
void slotQueuePopActiveMask(void);
void slotQueueReset(void);

s32 func_805FC668(void) {
    Actor *actor;

    if ((D_8076A0A8 == 0x50) || (func_80714360() == 0 && func_8071432C() == 0 && func_8071441C() == 0 && func_807143E8() == 0)) {
        D_807FBB60 &= ~1;
    }
    if (D_807FBB60 & 2) {
        if ((D_807FBB60 & 0x40) && (func_8071432C() != 0 || func_8071441C() != 0)) {
            sfxStopChannel(0x22, 0);
            D_807FBB60 &= 0xFFEBFFBD;
            actor = actorFindByType((D_807FC928 < 2 && func_8071441C() == 0) ? 0x5F : 0x157);
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
                    if ((func_8071432C() != 0 || func_8071441C() != 0) && !(D_807FBB60 & 0x40000)) {
                        sfxAllocateChannel(0x22, 1.0f);
                        sfxAllocateChannel(0x29, 1.0f);
                        if (D_807FC928 < 2 && func_8071441C() == 0) {
                            actorSpawn(0x5F, 0);
                            D_807FBB60 |= 0x100000;
                        } else {
                            actorSpawn(0x157, 0);
                        }
                        D_807FBB44->unk64 |= 2;
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
    s32 var_v1;

    var_v1 = (D_8076A0B1 & 0x10) == 0;
    if (var_v1 != 0) {
        var_v1 = D_8076A0B3 == 0;
    }
    return var_v1 & 0xFF;
}

#ifdef NON_MATCHING
extern u8 D_80750AB4;
f32 func_806276AC(void);
void func_8062754C(f32);
f32 sinApprox(f32);

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0xFA - 0x94];
    u8 unkFA;
} Sched0Held;

typedef struct {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} Sched0PlayerData;

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
} Sched0View;

#define S0V ((Sched0View *)D_807FC924)
#define S0DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void func_805FCA94(void *arg0) {
    Sched0View *v;
    Sched0PlayerData *pl;
    Sched0Held *held;
    s32 i;
    f32 fov;
    f32 aspect;
    f32 offs;

    if (D_807445CC[0] && D_807445CC[0]) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    aspect = func_8062A850();
    if (D_807FC928 >= 2 && D_80750AB8 == 1) {
        func_8062754C(func_806276AC());
    }
    for (i = 0; i < D_80750AB4; i++) {
        v = &S0V[i];
        if (v->unk0 != 0) {
            if (S0DIFF(v->unk210, v->unk228) < 0.5 && S0DIFF(v->unk218, v->unk230) < 0.5) {
                offs = 1.0f;
            } else {
                offs = 0.0f;
            }
            guLookAtHilite(&v->unk8[D_807444FC], &v->unk190[D_807444FC], &v->unk1D0[D_807444FC],
                           v->unk210 + offs, v->unk214, v->unk218 + offs,
                           v->unk228, v->unk22C, v->unk230,
                           v->unk240, v->unk244, v->unk248,
                           D_807444CC, D_807444D0, D_807444D4,
                           D_807444D8, D_807444DC, func_807444E0,
                           0x20, 0x20);
            v = &S0V[i];
            if (D_807445CC[0] && D_807445CC[0]) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            fov = v->unk280;
            pl = (Sched0PlayerData *)v->unk4->unk174;
            held = (Sched0Held *)pl->unk104->unk174;
            if (pl->unk1F0 & 0x100) {
                if (D_807444FC && D_807444FC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                fov = fov + 0.5 * sinApprox(D_807445CC[0] * 0.1);
                v = &S0V[i];
            } else if (pl->unk1F0 & 0x2000000) {
                fov = fov + 0.05 * sinApprox(D_807445CC[0] * 0.4);
                v = &S0V[i];
            } else if (held->unkFA != 0 && v->unk220 < held->unk90 + 3.0f) {
                fov = fov + 0.04 * sinApprox(D_807445CC[0] * 0.1);
                v = &S0V[i];
                if (D_807444FC == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            guPerspective(&v->unk88[D_807444FC], &S0V[i].unk188, v->unk27C, fov * aspect, v->unk284, v->unk288, 1.0f);
        }
    }
    if (S0DIFF(S0V->unk210, S0V->unk228) < 0.5 && S0DIFF(S0V->unk218, S0V->unk230) < 0.5) {
        offs = 1.0f;
    } else {
        offs = 0.0f;
    }
    guPerspective((Mtx *)arg0, &D_8076A09C, S0V->unk27C, fov * aspect, S0V->unk284, S0V->unk288, 1.0f);
    guLookAt((Mtx *)((u8 *)arg0 + 0x200), S0V->unk210 + offs, S0V->unk214, S0V->unk218 + offs,
             S0V->unk228, S0V->unk22C, S0V->unk230,
             S0V->unk240, S0V->unk244, S0V->unk248);
    D_807445CC[0]++;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FCA94.s")
#endif

Gfx *func_805FCFD8(Gfx *glistp) {
    if (D_8074450C == 2) {
        gSPDisplayList(glistp++, D_1000068);
    } else {
        gSPDisplayList(glistp++, D_1000040);
    }
    return glistp;
}


Gfx *func_805FD030(Gfx *glistp) {
    if (D_8074450C == 2) {
        gSPDisplayList(glistp++, D_1000030);
    } else {
        gSPDisplayList(glistp++, D_1000020);
    }
    return glistp;
}


void func_805FD088(Struct_8076A048 *arg0, Gfx **arg1, Gfx **arg2) {
    Gfx *glist;
    Gfx *glist2;

    glist = D_8076A050[D_807444FC];
    gSPPerspNormalize(&arg0->unkDB0[0], D_8076A09C);
    glist2 = &arg0->unkDB0[1];
    gSPClipRatio(glist2++, FRUSTRATIO_3);

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(arg0));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));

    gSPSegment(glist2++, 0, 0);
    gSPSegment(glist2++, 2, osVirtualToPhysical(arg0));
    gSPSegment(glist2++, 1, osVirtualToPhysical(D_8076A080));

    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist2++, &D_1000090);

    glist = func_805FCFD8(glist);
    glist2 = func_805FCFD8(glist2);

    gDPSetScissor(glist++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);
    gDPSetScissor(glist2++, G_SC_NON_INTERLACE, 0, 0, D_80744490, D_80744494);

    guTranslate(&arg0->unk180, 0.0f, 0.0f, 0.0f);
    guOrtho(&arg0->unk80, 0.0f, (f32)((f64)(f32)D_80744490 - 1.0), (f32)((f64)(f32)D_80744494 - 1.0), 0.0f, D_807565B0, D_807565B4, 1.0f);
    guOrtho(&arg0->unkC0, 0.0f, (f32)(((f64)(f32)D_80744490 * 4.0) - 1.0), (f32)(((f64)(f32)D_80744494 * 4.0) - 1.0), 0.0f, D_807565B8, D_807565BC, 1.0f);
    guOrtho(&arg0->unk140, 0.0f, (f32)((2.0 * (f64)(f32)D_80744490) - 1.0), (f32)((2.0 * (f64)(f32)D_80744494) - 1.0), 0.0f, D_807565C0, D_807565C4, 1.0f);
    guOrtho(&arg0->unk100, (f32)((f64)(f32)D_807FC924->rect[0] * 4.0), (f32)(((f64)(f32)D_807FC924->rect[2] * 4.0) - 1.0), (f32)(((f64)(f32)D_807FC924->rect[3] * 4.0) - 1.0), (f32)((f64)(f32)D_807FC924->rect[1] * 4.0), D_807565C8, D_807565CC, 1.0f);
    guPerspective(&arg0->unk0, &D_8076A09C, D_807444B8, func_8062A850() * D_807444BC, D_807444C8, D_807444C4, 1.0f);

    gSPMatrix(glist2++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glist2++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    glist2 = func_805FD030(glist2);

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

    glist = (Gfx *)func_80701CA0(playerViewsRender(glist, arg0, 0xFFFD));
    if (D_807FC928 == 1) {
        glist = (Gfx *)lensFlareBuildDisplayList((s32)glist);
    }
    glist = gfxPassThrough(screenWipeDraw(renderCallbacksExecute((s32)glist, 1)));

    if ((D_8076A0A8 == 0x4C) || (D_8076A0A8 == 0x50) || ((func_80714464() != 0) && (D_8076A0A8 != 0xD0))) {
        D_8076A0B1 &= ~0x10;
        D_8076A0B3 = 0;
    }

    if (((D_8076A0B1 & 0x10) || (D_8076A0B3 != 0)) && ((D_807FC928 == 1) || (D_80750AB8 == 1))) {
        f32 temp_fv0;
        f32 var_fv1;
        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
        gSPClearGeometryMode(glist++, 1);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_80744498, D_8074449C, D_807444A0, D_807444A4);

        if (D_8076A0B3 != 0) {
            D_8076A0B3 -= 15;
            var_fv1 = (f32)(1.0 - ((f64)(u32)D_8076A0B3 / D_807565D0));
            temp_fv0 = (f32)(D_807444AC - D_807444A8) * var_fv1;
            gDPFillRectangle(glist++, 0,
                (temp_fv0 < (f32)D_807444A8) ? (f32)D_807444A8 - temp_fv0 : 0.0f,
                (D_80744490 > 0) ? D_80744490 : 0,
                (temp_fv0 < (f32)D_807444AC) ? (f32)D_807444AC - temp_fv0 : 0.0f);
            gDPFillRectangle(glist++, 0, D_807444B0 + temp_fv0, D_80744490, D_807444B4 + temp_fv0);
            D_807FC924->rect[1] = (s16)(s32)((f32)D_807444AC - temp_fv0);
            D_807FC924->rect[3] = (s16)(s32)((f32)D_807444B0 + temp_fv0);
        } else {
            gDPFillRectangle(glist++, 0, D_807444A8, D_80744490, D_807444AC);
            gDPFillRectangle(glist++, 0, D_807444B0, D_80744490, D_807444B4);
            D_807FC924->rect[1] = (s16)D_807444AC;
            D_807FC924->rect[3] = (s16)D_807444B0;
        }
        D_807FC924->unk27A = (s16)(D_807FC924->rect[3] - D_807FC924->rect[1]);
        D_807FC924->unk280 = (f32)((f32)D_807FC924->unk278 / (f32)D_807FC924->unk27A);
        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    }

    if ((D_8074447C != 0) || (D_80744480 != 0) || (D_80744484 != 0) || (D_80744488 != 0) || (D_8074448C != 0)) {
        Struct806C7C94 *temp_v0_6;
        s16 dx, dy;
        temp_v0_6 = cameraFindViewportEntry(0);
        D_807FC924->rect[0] = (s16)(temp_v0_6->unk4 + D_8074447C);
        D_807FC924->rect[2] = (s16)(temp_v0_6->unk8 - D_80744480);
        D_807FC924->rect[1] = (s16)(temp_v0_6->unk6 + D_80744484);
        D_807FC924->rect[3] = (s16)(temp_v0_6->unkA - D_80744488);

        gDPPipeSync(glist++);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
        gSPClearGeometryMode(glist++, 1);
        gDPSetFillColor(glist++, 0x00010001);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_80744498, D_8074449C, D_807444A0, D_807444A4);

        if (D_8074447C != 0) {
            gDPFillRectangle(glist++, temp_v0_6->unk4, temp_v0_6->unk6, D_807FC924->rect[0], temp_v0_6->unkA);
        }
        if (D_80744480 != 0) {
            gDPFillRectangle(glist++, D_807FC924->rect[2], temp_v0_6->unk6, temp_v0_6->unk8, temp_v0_6->unkA);
        }
        if (D_80744484 != 0) {
            gDPFillRectangle(glist++, D_807FC924->rect[0], temp_v0_6->unk6, D_807FC924->rect[2], D_807FC924->rect[1]);
        }
        if (D_80744488 != 0) {
            gDPFillRectangle(glist++, D_807FC924->rect[0], D_807FC924->rect[3], D_807FC924->rect[2], temp_v0_6->unkA);
        }

        gDPPipeSync(glist++);
        D_807FC924->unk278 = (s16)(D_807FC924->rect[2] - D_807FC924->rect[0]);
        D_807FC924->unk27A = (s16)(D_807FC924->rect[3] - D_807FC924->rect[1]);
        if ((D_8074447C == 0) && (D_80744480 == 0) && (D_80744484 == 0) && (D_80744488 == 0)) {
            D_8074448C = 0;
        } else {
            D_8074448C = 1;
        }
        D_8074447C = 0;
        D_80744480 = 0;
        D_80744484 = 0;
        D_80744488 = 0;
        dx = temp_v0_6->unk8 - temp_v0_6->unk4; dy = temp_v0_6->unkA - temp_v0_6->unk6; D_807FC924->unk280 = (f32)dx / (f32)dy;
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    }

    glist = (Gfx *)renderCallbacksExecute(renderCallbacksExecute(func_8062CA0C(renderCallbacksExecute((s32)func_805FD030(glist), 3), D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218), 5), 7);
    if (D_807467E4 != 0) {
        D_807467E4 -= 1;
    }
    glist = (Gfx *)func_80714060(slotQueueBuildDisplayList(healthHudDrawAll((s32)glist)));
    textFontAgeSheets();
    texCacheUpdate();
    commandQueueReset();
    *arg1 = glist;
    *arg2 = glist2;
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


void func_805FE544(u8 arg0) {
    if (D_807FBB64 & 1) {
        D_8076A058 = 0x1770;
    } else {
        D_8076A058 = arg0 * 3000;
    }
    D_8076A050[0] = func_80610FE8(D_8076A058 * sizeof(Gfx));
    D_8076A050[1] = func_80610FE8(D_8076A058 * sizeof(Gfx));
    func_805FE71C(func_805FE634(D_8076A050[0], 0), 0, &D_8076A088, 1);
    func_805FE71C(func_805FE634((void *)D_8076A054, 1), 1, &D_8076A088, 1);
}


Gfx *func_805FE634(Gfx *glistp, u8 arg1) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, 0, 0);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80744490, D_80744470[arg1]);
    gDPSetFillColor(glistp++, 0x10001);
    gDPPipeSync(glistp++);
    gDPFillRectangle(glistp++, 0, 0, D_80744490 - 1, D_80744494 - 1);
    return glistp;
}


void func_805FE71C(Gfx *arg0, u8 arg1, s32 *arg2, u8 arg3) {
    Gfx *glistp = arg0;

    if (arg3) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *arg2 = glistp - (Gfx *)D_8076A050[arg1];
    if (*arg2 >= D_8076A058) {
        faultSetMessage(0x12, 0, 0, 0);
    }
}


void func_805FE7B4(Gfx *arg0, s32 arg1, s32 *arg2, u8 arg3) {
    Gfx *glistp = arg0;

    if (arg3) {
        gDPFullSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
    *arg2 = ((s32)glistp - arg1 - 0xDB0) >> 3;
}


void func_805FE7FC(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    f32 var_fv0;
    s32 temp_a0;

    D_80746830 = 1;
    D_8076A090 = 0;
    D_8076A094 = 0;
    D_8076A098 = 0;
    D_807FBB60 &= 0xFFEB3FFC;
    func_80712A40();
    D_80750AC4 = 0;
    D_8076A0A4 = 0;
    D_807444FC = 0;
    D_8076A064 = 0;
    D_8076A068 = 0;
    audioResetAll();
    D_80744508 = 0;
    *D_807ECDF4 = 0;
    texCacheReset();
    D_8076A0B1 &= 0xFFCF;
    func_8070F570();
    if (D_807444EC == 1) {
        D_807444EC = 0;
    }
    D_8076A06C = D_8076A064;
    D_80744500 = 0;
    timerQueueInit();
    

    D_8076A0A8 = D_807444E4;
    temp_a0 = D_8076A0A8;
    if (D_8076A0A8 != 0x50) {
        if (D_8076A0A8 != 0x51) {
            D_807FBB60 |= 0x30030;
        } else {
            D_807FBB60 &= 0xFFFCFFCF;
        }
    } else {
        D_807FBB60 &= 0xFFFEFFCF;
    }
    if (temp_a0 == 2) {
        D_807444EC = 3;
    } else if (temp_a0 == 9) {
        D_807444EC = 4;
    } else {
        D_807444EC = 0;
    }
    func_805FB944(1, &D_8076A0A8);
    
if (((s32) D_80750AC0 >= 2) && !(D_807FBB64 & 0x04000000)) {
        D_80750AC0 = 1;
    }
    func_806C7C10();
    func_806D0430(0.0f);
    func_805FE544(D_80750AC0);
    if (D_8076A0A8 != 0xB8) {
        if (D_8076A0A8 == 0xBF) {
            D_8074E77C = 6;
        }
    } else {
        D_8074E77C = 7;
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
        func_806F3760(D_8076A0AA);
        proxPathListClear();
        mapSearchTableReset();
        pathFreeAsset(D_8076A0A8);
        sp2C = assetLoad(1, D_8076A0A8, 1, 1);
        renderEntryListsReset();
        mapChunkAllocLists(sp2C);
        mapHeaderLoad(sp2C);
        func_806C95D0(D_8076A0A8);
        billboardCacheInit();
        mapLoadNodeAsset(D_8076A0A8);
        actorListInitOffsets();
        modelTypeCountsInit();
        displayListFreeQueueReset();
        sp24 = assetLoad(9, D_8076A0A8, 1, 1);
        modelSlotsAllocate(D_8076A0A8, 1);
        actorMapModelsSetup(sp24, 0, 0);
        actorInitTargetEntries();
        lightInitGlobals();
        actorInit();
        actorSpawnInitialSet();
        volumeTriggerTableInit(D_8076A0A8);
        camInit(sp28 = assetLoad(8, D_8076A0A8, 1, 1));
        if (sp28 != 0) {
            assetFreeBuffer(sp28, 0x8D0, 2);
        }
        func_80712B80();
        func_806C7D40(D_807444E8);
        effectResetLists();
        sp28 = assetLoad(0x10, D_8076A0A8, 1, 1);
        func_80724C78(sp28);
        if (sp28 != 0) {
            assetFreeBuffer(sp28, 0x8DD, 2);
        }
        camResetAllPlayers();
        renderCallbacksReset();
        func_806F4778();
        func_8070E8C8();
        timerQueueAdd(sfxPlayCurrent, 2, 0, 0, 0);
        if (D_807FBB64 & 0x1000) {
            sp28 = assetLoad(0x16, D_8076A0A8, 1, 1);
            func_80026FD0(sp28);
            if (sp28 != 0) {
                assetFreeBuffer(sp28, 0x8ED, 2);
            }
        }
        if (D_807FBB64 & 0x2000) {
            func_8002EC08(D_8076A0A8);
        }
        collisionBstRebalanceAll();
        D_807F6008 = 0;
        if ((func_8070B318() == 0) && (D_807444EC != 2)) {
            if ((D_8076A0A8 == 0x11) && (flagGet(0x302, 0) != 0)) {
                sfxAllocateChannel(0x74, 1.0f);
            } else {
                temp_a0 = D_80745BDC[D_8076A0A8][0];
                var_fv0 = 1.0f;
                if ((temp_a0 == 6) || (temp_a0 == 0x1F)) {
                    var_fv0 = D_807565D8;
                }
                sfxAllocateChannel(temp_a0, var_fv0);
            }
        }
        if ((D_8076A0A8 == 0x22) || (D_8076A0A8 == 0xB8)) {
            sfxAllocateChannel(0x60, 1.0f);
        }
        seqSetChannelVolumeScale(0, 1.0f);
        seqSetChannelVolumeScale(1, 1.0f);
        seqSetChannelVolumeScale(2, 1.0f);
        func_805FFEF8(D_8076A0A8);
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
    frameTimingReset(D_8076A0A8);
    D_80746830 = 0;
}


void func_805FEE84(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_8074447C = arg0;
    D_80744480 = arg1;
    D_80744484 = arg2;
    D_80744488 = arg3;
}

void func_805FEEB8(s32 *arg0, s32 arg1) {
    s32 rem;

    rem = *arg0 % arg1;
    if (rem != 0) {
        *arg0 = *arg0 + arg1 - rem;
    }
}

