#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/globalInit.s")

void func_80601CF0(s32);
void func_8060E930(void);
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct80744464;

extern Struct80744464 D_80744464;
extern u8 D_80744460;
extern OSThread D_80761430;

extern u64 D_807655E8;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FB5C4.s")

extern s32 D_8000DDCC;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;

void seg11DmaRead(s32 arg0, s32 arg1, void *arg2) {
    s32 sp2C;

    sp2C = D_8000DDCC;
    osWritebackDCache(arg2, arg1);
    osPiStartDma(&D_807ECE00, 0, 0, sp2C + arg0, arg2, (u32) arg1, &D_807655F0);
    osRecvMesg(&D_807655F0, NULL, 1);
    osInvalDCache(arg2, arg1);
}

extern u32 D_80744470[8];
extern void *D_8076A080;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FB7E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FB944.s")

extern u32 gSegmentTable[];
extern OSMesg D_80765608;
extern OSMesgQueue D_807656D0;
extern OSMesg D_807656E8;
extern u8 D_8074458B[][4];
extern u8 gScheduler[];
extern u8 D_80767CD8[];
extern OSMesgQueue D_807659E8;
extern OSMesg D_80765A00[];
extern s32 D_807444E4;
extern s32 D_8076A084;
extern s32 D_8076A0A8;
extern s32 D_8076A07C;
extern OSMesg D_8076A108;
extern OSMesgQueue D_8076A110;
extern OSMesg D_8076A128;
extern OSTimer D_8076A130;
void schedCreate(OSMesgQueue *, void *, s32, u8, u8);
void schedAddClient(void *, void *, OSMesgQueue *, s32, s32);
void func_805FB944(s32);
void func_8060FFF0(void);
void func_8060A900(void);
void func_80600D50(void);
void func_8070B308(s32);
void func_8073239C(void);
void func_80609140(s32, s32, f32, f32, s32, s32);

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

extern s32 D_8000DDE4;
extern f32 D_807444B8;
extern f32 D_807444BC;
extern f32 D_807444C4;
extern f32 D_807444C8;
extern s8 D_807467CC;
extern Mtx D_80767CE8;
extern Mtx D_80767E68;
extern Mtx D_80768E98;
extern Mtx D_80769018;
extern s32 D_8076A064;
extern s32 D_8076A068;
extern u16 D_8076A09C;
extern s8 D_8076A0A4;
extern s32 D_8076A0AC;
extern u8 D_8076A0B1;
extern s8 D_8076A0B2;
extern f32 D_807FD888;
extern u32 D_807FBB60;
extern s32 D_807FF100;
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
void func_8060AA04(void);
void func_80631B80(void);
void func_806C9AE0(void);
void func_80731030(void);
void func_805FF118(void);
void func_8063DB0C(void);
f32 func_8062A850(void);

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FC2B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FC668.s")

extern u64 __ll_mul(u64, u64);
extern u64 __ull_div(u64, u64);
extern u64 D_807445B8;
extern u64 D_807445C0;
extern s32 D_80750AB0;
extern u32 D_807FBB60;

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

extern s16 D_80744490;
extern s16 D_80744494;
extern s8 D_8074447C;
extern s8 D_80744480;
extern s8 D_80744484;
extern s8 D_80744488;
extern u8 D_807444FC;
extern u8 D_807444EC;
extern u8 D_8074450C;
extern s32 D_8076A064;
extern s32 D_8076A068;
extern s32 D_8076A084;
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 D_8076A0B1;
extern u8 D_8076A0B3;
extern u32 D_807FBB60;
extern u32 D_807FBB64;

s32 func_805FCA64(void) {
    s32 var_v1;

    var_v1 = (D_8076A0B1 & 0x10) == 0;
    if (var_v1 != 0) {
        var_v1 = D_8076A0B3 == 0;
    }
    return var_v1 & 0xFF;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FCA94.s")

extern u8 D_8074450C;
extern u8 D_1000040[];
extern u8 D_1000068[];

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FCFD8.s")

extern u8 D_1000020[];
extern u8 D_1000030[];

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FD030.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FD088.s")

extern s16 D_80744490;
extern s16 D_80744494;
extern u8 *D_8076A060;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE398.s")

extern s16 D_80744490;
extern u8 D_807444FC;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE4D4.s")

void *func_80610FE8(s32);
void *func_805FE634(void *, s32);
void func_805FE71C(void *, s32, s32 *, s32);
extern u8 *D_8076A050[4];
extern s32 D_8076A054;
extern s32 D_8076A058;
extern s32 D_8076A088;
extern u32 D_807FBB64;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE544.s")

extern s16 D_80744490;
extern s16 D_80744494;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE634.s")

void func_80732354(s32, s32, s32, s32);
extern u8 *D_8076A050[4];
extern s32 D_8076A058;

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE71C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE7B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FE7FC.s")

extern s8 D_8074447C;
extern s8 D_80744480;
extern s8 D_80744484;
extern s8 D_80744488;

void func_805FEE84(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_8074447C = arg0;
    D_80744480 = arg1;
    D_80744484 = arg2;
    D_80744488 = arg3;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/0/func_805FEEB8.s")
