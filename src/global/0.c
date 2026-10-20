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
void func_806003EC(s16, u8);
s32 func_8060042C(s16, s32, s32);
void func_80600590(s32);
void func_80600674(void);
void func_80600950(void);
void func_8060098C(void *, s32, s32, s32, s32);
void func_80600B10(void);
void func_80600D50(void);
void func_80601CF0(s32);
void func_806025AC(void);
void func_806025D4(void);
void func_80602A94(s32, f32);
void func_80603450(void);
void func_80605510(void);
void func_806057F8(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_8060A4D0(s32, f32);
void func_8060A900(void);
void func_8060A9BC(void);
void func_8060AA04(void);
void func_8060AC7C(void);
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
void func_8060E930(void);
void func_8060FFF0(void);
void func_80610044(void *, s32, s32, u8, s32, s32);
void func_80610268(s32);
void *func_80610FE8(s32);
void func_80611730(void);
void func_8061EA78(void);
void func_80626264(s32);
void func_80629190(void);
s32 func_80629300(s32);
f32 func_8062A850(void);
Gfx *func_8062A844(s32);
s32 func_8062BF24(Gfx *, Struct_8076A048 *, u32);
s32 func_8062CA0C(s32, s32, s32, s32);
void func_8062F050(s32);
void func_80630300(void);
void func_80631B80(void);
void func_80631C3C(void);
void func_80631FAC(s32, s32);
void func_8063643C(void);
void func_8063DB0C(void);
void func_80650E20(s32);
void func_806588E0(s32);
void func_80658BD0(void);
void func_80658CCC(void);
void func_8065A570(void);
void func_8065A648(void);
void func_8065D170(void);
void func_8065D1AC(void);
void func_80661054(void);
void func_80663A80(void);
void func_80663DA0(void);
void func_806641A0(void);
void func_80664CB0(s16);
void func_8066ADA0(void);
void func_8066AF40(void);
s32 func_8066B0F8(s32, s32, s32, s32);
void func_8066B434(s32, s32, s32);
void func_8066BDE0(void);
void func_8066CCD8(void);
void func_8066CDD0(void);
void func_80677D80(void);
void func_806787CC(void);
void func_80678824(void);
void func_806789E4(void);
void func_806886E0(s32, s32, s32);
void func_80688940(void);
void func_8068A508(void);
void func_8068A7B0(void);
void func_8068C080(void);
void func_8068C0B4(void);
s32 func_8068C20C(s32, s32);
void func_8068C2EC(void);
void func_806C7C10(void);
Struct806C7C94 *func_806C7C94(s32);
void func_806C7D40(s32);
void func_806C95D0(s32);
void func_806C9AE0(void);
void func_806D0430(f32);
void func_806F3760(s16);
void func_806F4778(void);
s32 func_806FAB20(s32);
void func_806FBB58(void);
void func_806FBC34(void);
void func_806FD9A0(void);
s32 func_807007B8(s32);
void func_80700BF4(void);
void func_80701C90(void);
s32 func_80701CA0(s32);
void *func_80704484(void *, u8);
Gfx *func_80704960(Gfx *);
void func_807040E0(s32, s32, s32);
void func_80704108(s32, s32, s32);
void func_80705B30(void);
s32 func_80709344(s32);
void func_807094D0(s32, u32 *);
void func_8070A934(s32, s32);
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
void func_80714670(void);
void func_80715270(s32);
void func_807215EC(void);
void func_80722280(void);
void func_80722E00(s32);
void func_80724C78(s32);
void func_8072E740(s32);
void func_8072ED90(void);
void func_80731030(void);
s32 func_8073110C(s32, s32);
void func_80732354(s32, s32, s32, s32);
void func_8073239C(void);
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

extern u8 D_80744460;
extern Struct80744464 D_80744464;
extern u32 D_80744470[8];
extern u8 D_8074447C;
extern u8 D_80744480;
extern u8 D_80744484;
extern u8 D_80744488;
extern u8 D_8074448C;
extern s16 D_80744490;
extern s16 D_80744494;
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;
extern s16 D_807444A8;
extern s16 D_807444AC;
extern s16 D_807444B0;
extern s16 D_807444B4;
extern f32 D_807444B8;
extern f32 D_807444BC;
extern f32 D_807444C4;
extern f32 D_807444C8;
extern s32 D_807444E4;
extern s32 D_807444E8;
extern u8 D_807444EC;
extern u8 D_807444F8;
extern u8 D_807444FC;
extern s8 D_80744500;
extern s8 D_80744504;
extern s16 D_80744508;
extern u8 D_8074450C;
extern u8 D_8074458B[][4];
extern u64 D_807445B8;
extern u64 D_807445C0;

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

extern OSMesg D_80761050;
extern OSMesgQueue D_80761068;
extern OSThread D_80761430;
extern s32 D_80761680;
extern s32 D_80761684;
extern OSMesgQueue *D_807655E0;
extern u64 D_807655E8;
extern OSMesgQueue D_807655F0;
extern OSMesg D_80765608;
extern OSMesgQueue D_807656D0;
extern OSMesg D_807656E8;
extern OSMesgQueue D_807659E8;
extern OSMesg D_80765A00[];
extern u8 D_80767CD8[];
extern Mtx D_80767CE8;
extern Mtx D_80767E68;
extern Mtx D_80768E98;
extern Mtx D_80769018;

extern u8 *D_8076A048;
extern Gfx *D_8076A050[4];
extern s32 D_8076A054;
extern s32 D_8076A058;
extern u8 *D_8076A060;
extern s32 D_8076A064;
extern s32 D_8076A068;
extern s32 D_8076A06C;
extern s32 D_8076A07C;
extern void *D_8076A080;
extern s32 D_8076A084;
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern s32 D_8076A090;
extern s32 D_8076A094;
extern s32 D_8076A098;
extern u16 D_8076A09C;
extern s32 D_8076A0A0;
extern u8 D_8076A0A4;
extern s32 D_8076A0AC;
extern s32 D_8076A0A8;
extern s16 D_8076A0AA;
extern u8 D_8076A0B1;
extern s8 D_8076A0B2;
extern u8 D_8076A0B3;
extern OSMesg D_8076A108;
extern OSMesgQueue D_8076A110;
extern OSMesg D_8076A128;
extern OSTimer D_8076A130;
extern void *D_8076A150;
extern u8 D_8076AEE0;

extern OSIoMesg D_807ECE00;
extern s16 *D_807ECDF4;
extern s8 D_807F6008;
extern s32 D_807F6010;
extern u32 D_807FBB60;
extern u32 D_807FBB64;
extern PlayerStruct *D_807FC924;
extern u8 D_807FC928;
extern f32 D_807FD888;
extern f32 D_807FD88C;
extern s32 D_807FF100;
extern u8 gScheduler[];


#pragma GLOBAL_ASM("asm/global/nonmatchings/0/globalInit.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FB5C4.s")

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


#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FB944.s")

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
    func_8060A900();
    func_80600D50();
    func_8070B308(0);
    func_8073239C();
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
    func_8060AA04();
    D_8076A064 = 0;
    D_8076A068 = 0;
    D_807467CC = 0;
    D_8076A0AC = 4;
    D_807FBB60 = 0x30030;
    D_8076A0B1 |= 1;
    D_8076A0B2 = 0;
    D_807FD888 = 31.0f;
    D_8076A0B1 |= 4;
    func_80631B80();
    func_806C9AE0();
    func_80731030();
    func_805FF118();
    func_8063DB0C();
    sp28 = func_8062A850();
    guTranslate(&D_80767E68, 0.0f, 0.0f, 0.0f);
    guTranslate(&D_80769018, 0.0f, 0.0f, 0.0f);
    guPerspective(&D_80767CE8, &D_8076A09C, D_807444B8, D_807444BC * sp28, D_807444C8, D_807444C4, 1.0f);
    guPerspective(&D_80768E98, &D_8076A09C, D_807444B8, D_807444BC * sp28, D_807444C8, D_807444C4, 1.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FBFF4.s")

void func_805FC2B0(void) {
    Gfx *sp2C;
    Gfx *sp28;

    func_8060A9BC();
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
    func_8060AC7C();
    if (func_805FC668() != 0) {
        func_8065D1AC();
        func_806789E4();
        func_80715270(1);
        func_80603450();
        func_806057F8();
        func_806025D4();
        func_805FCA94(D_8076A048);
    } else {
        func_8065A648();
        func_806787CC();
        func_805FCA94(D_8076A048);
        func_8065D1AC();
        func_8068A508();
        func_8066CDD0();
        func_8066CCD8();
        func_80661054();
        func_80678824();
        func_80663A80();
        func_80715270(0);
        func_80603450();
        func_806025D4();
        func_806057F8();
        func_806F6F28();
    }
    func_8070DD44();
    D_8076A150 = D_8076A050[D_807444FC];
    if ((D_8076A0B1 & 1) && D_807FD888 == 31.0f) {
        sp2C = D_8076A050[D_807444FC];
        sp28 = D_8076A048 + 0xDB0;
        func_8068C2EC();
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
        sp2C = func_80704484(sp2C, D_8076AEE0);
    }
    if (D_8076A0A4 != 0 && D_807444EC != 6) {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 0);
        func_805FE7B4(sp28, (s32)D_8076A048, &D_8076A08C, 1);
    } else {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 1);
    }
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FC668.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FCA94.s")

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

    glist = (Gfx *)func_80701CA0(func_8062BF24(glist, arg0, 0xFFFD));
    if (D_807FC928 == 1) {
        glist = (Gfx *)func_807007B8((s32)glist);
    }
    glist = func_8062A844(func_80629300(func_8068C20C((s32)glist, 1)));

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
        temp_v0_6 = func_806C7C94(0);
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

    glist = (Gfx *)func_8068C20C(func_8068C20C(func_8062CA0C(func_8068C20C((s32)func_805FD030(glist), 3), D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218), 5), 7);
    if (D_807467E4 != 0) {
        D_807467E4 -= 1;
    }
    glist = (Gfx *)func_80714060(func_806FAB20(func_80709344((s32)glist)));
    func_806FBC34();
    func_8068C0B4();
    func_80722280();
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
        func_80732354(0x12, 0, 0, 0);
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
    func_80605510();
    D_80744508 = 0;
    *D_807ECDF4 = 0;
    func_8068C080();
    D_8076A0B1 &= 0xFFCF;
    func_8070F570();
    if (D_807444EC == 1) {
        D_807444EC = 0;
    }
    D_8076A06C = D_8076A064;
    D_80744500 = 0;
    func_80600950();
    

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
    func_8066ADA0();
    func_806FBB58();
    func_806FD9A0();
    func_807040E0(0xFF, 0xFF, 0xFF);
    func_80704108(0xFF, 0xFF, 0xFF);
    if (D_807444EC == 0) {
        D_8076A0A0 = func_8066B0F8(0x13, 0, 1, 1);
        func_80705B30();
        func_807215EC();
        func_806F3760(D_8076A0AA);
        func_8072ED90();
        func_80658BD0();
        func_80722E00(D_8076A0A8);
        sp2C = func_8066B0F8(1, D_8076A0A8, 1, 1);
        func_80630300();
        func_80650E20(sp2C);
        func_8062F050(sp2C);
        func_806C95D0(D_8076A0A8);
        func_8065D170();
        func_806588E0(D_8076A0A8);
        func_80688940();
        func_80631C3C();
        func_8063643C();
        sp24 = func_8066B0F8(9, D_8076A0A8, 1, 1);
        func_80631FAC(D_8076A0A8, 1);
        func_806886E0(sp24, 0, 0);
        func_80663DA0();
        func_8065A570();
        func_80677D80();
        func_8068A7B0();
        func_8072E740(D_8076A0A8);
        func_80626264(sp28 = func_8066B0F8(8, D_8076A0A8, 1, 1));
        if (sp28 != 0) {
            func_8066B434(sp28, 0x8D0, 2);
        }
        func_80712B80();
        func_806C7D40(D_807444E8);
        func_80714670();
        sp28 = func_8066B0F8(0x10, D_8076A0A8, 1, 1);
        func_80724C78(sp28);
        if (sp28 != 0) {
            func_8066B434(sp28, 0x8DD, 2);
        }
        func_8061EA78();
        func_8068C2EC();
        func_806F4778();
        func_8070E8C8();
        func_8060098C(func_806025AC, 2, 0, 0, 0);
        if (D_807FBB64 & 0x1000) {
            sp28 = func_8066B0F8(0x16, D_8076A0A8, 1, 1);
            func_80026FD0(sp28);
            if (sp28 != 0) {
                func_8066B434(sp28, 0x8ED, 2);
            }
        }
        if (D_807FBB64 & 0x2000) {
            func_8002EC08(D_8076A0A8);
        }
        func_8066BDE0();
        D_807F6008 = 0;
        if ((func_8070B318() == 0) && (D_807444EC != 2)) {
            if ((D_8076A0A8 == 0x11) && (func_8073110C(0x302, 0) != 0)) {
                func_80602A94(0x74, 1.0f);
            } else {
                temp_a0 = D_80745BDC[D_8076A0A8][0];
                var_fv0 = 1.0f;
                if ((temp_a0 == 6) || (temp_a0 == 0x1F)) {
                    var_fv0 = D_807565D8;
                }
                func_80602A94(temp_a0, var_fv0);
            }
        }
        if ((D_8076A0A8 == 0x22) || (D_8076A0A8 == 0xB8)) {
            func_80602A94(0x60, 1.0f);
        }
        func_8060A4D0(0, 1.0f);
        func_8060A4D0(1, 1.0f);
        func_8060A4D0(2, 1.0f);
        func_805FFEF8(D_8076A0A8);
        func_806641A0();
    }
    func_80712BD4();
    func_805FF670();
    D_8076A0B1 ^= 1;
    D_807FD888 = 31.0f;
    D_8076A0B1 |= 4;
    D_807FD88C = -1.0f;
    if ((D_807444F8 != 2) && (D_8076AEE0 == 1)) {
        func_80602A94(0x2B, 1.0f);
    }
    func_80701C90();
    func_80629190();
    func_80664CB0(D_8076A0AA);
    func_80600590(D_8076A0A8);
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

