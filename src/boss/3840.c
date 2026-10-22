#include "common.h"

typedef struct {
    char pad[0x20];
    u8 *unk20;
} BossB_Struct_DC98;

typedef struct {
    char pad[0x11];
    u8 unk11;
} BossB_Struct_DC9C;

extern BossB_Struct_DC98 *D_807FDC98;
extern BossB_Struct_DC9C *D_807FDC9C;

void heapFree(void *);
void *func_80610FE8(s32);

void func_80027840(u8 *arg0) {
    s16 i;
    u8 *dst;

    if (D_807FDC98->unk20 != NULL) {
        heapFree(D_807FDC98->unk20);
    }
    D_807FDC9C->unk11 = *arg0;
    D_807FDC98->unk20 = func_80610FE8(*arg0 * 2);
    dst = D_807FDC98->unk20;
    for (i = 0; i < *arg0; i++) {
        dst[0] = arg0[i + 1];
        dst[1] = 0;
        dst += 2;
    }
}

typedef struct {
    char pad0[8];
    f32 unk8;
    f32 unkC;
} BossB_Struct_800278F4;

void bossLerpCoords(BossB_Struct_800278F4 *arg0, f32 arg1, s16 arg2, s16 arg3) {
    arg0->unkC += ((f32)arg2 - arg0->unkC) * arg1;
    arg0->unk8 += ((f32)arg3 - arg0->unk8) * arg1;
}

typedef struct {
    char pad0[0x15];
    u8 unk15;
} BossB_Struct_80027950;

typedef struct {
    char pad0[0x25];
    u8 unk25;
} BossB_Struct_DC90;

extern BossB_Struct_DC90 *D_807FDC90;

s32 func_80611A44(void);

void func_80027950(BossB_Struct_80027950 *arg0, u8 *arg1) {
    u8 prev = D_807FDC90->unk25;
    do {
        s32 rand = func_80611A44() >> 15;
        u8 offset = arg0->unk15;
        D_807FDC90->unk25 = arg1[offset] + ((rand % 65536) % (arg1[offset + 1] - arg1[offset] + 1));
    } while (D_807FDC90->unk25 == prev);
    arg0->unk15 += 2;
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80027A30.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80027BA8.s")

void func_805FF8F8(void);

void func_80028458(void) {
    func_805FF8F8();
}

typedef struct {
    char pad[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x15E - 0x88];
    u8 unk15E;
} Boss3C_Struct_8478;

void func_80602A94(s32, f32);
void func_806A5DF0(s32, f32, f32, f32, s32, s32, s32, s32);
void func_80714950(void *);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
s32 func_8073110C(s16, s32);
void D_8071CDE0(void);

extern s32 D_8074E880[];
extern Boss3C_Struct_8478 *D_807FDC94;

void bossSpawnParticleRing(arg0, arg1, arg2, arg3, arg4, arg5)
u16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 arg4;
u8 arg5;
{
    s16 sp4C;
    s16 s0;

    func_80602A94(0x36, 1.0f);
    sp4C = (s16)arg0;
    if (func_8073110C((s16)arg0, 0) != 0) {
        func_80028458();
        return;
    }
    for (s0 = 0; s0 < 6; s0++) {
        func_8071498C(D_8071CDE0);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714950(D_807FDC94);
        func_80714CC0(D_8074E880[((func_80611A44() >> 15) % 1000) % 3], 1.8f, D_807FDC94->unk7C, D_807FDC94->unk80 + (f32)D_807FDC94->unk15E, D_807FDC94->unk84);
    }
    func_806A5DF0(0x48, (f32)arg1, (f32)arg2, (f32)arg3, (s32)arg4, (s32)arg5, sp4C, 0);
}

typedef struct {
    char pad0[0x11C];
    s32 unk11C;
} BossB_Struct_807FBB40;

extern BossB_Struct_807FBB40 *D_807FBB40;

void func_806A2A10(s32, s32, s32);
void func_806A2B08(s32);

void func_80028680(void) {
    func_806A2A10(-0x7F83, 0xD2, 0xB4);
    func_806A2B08(D_807FBB40->unk11C);
}

#define Boss2C_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

typedef float Boss2C_MtxF[4][4];

typedef struct {
    char pad0[0x276];
    s16 unk276;
} Boss2C_Struct_807FC924;

extern Boss2C_Struct_807FC924 *D_807FC924;
extern u8 D_80750AD4;
extern Gfx D_1000118;

void heapFreeDeferred(void *);
void *func_8070068C(Gfx *);
void func_806FC530(void *, s32, s32, s32, char *, s32);

void bossDrawRoundText(Gfx *arg0, s32 arg1) {
    Boss2C_MtxF sp90;
    Boss2C_MtxF sp50;
    Mtx *sp4C;
    char sp3C[16];

    sp4C = func_80610FE8(sizeof(Mtx));
    heapFreeDeferred(sp4C);
    guScaleF(sp90, 0.6f, 0.6f, 1.0f);
    guTranslateF(sp50, 100.0f, (f32)(D_807FC924->unk276 * 4 - 0x3C), 0.0f);
    guMtxCatF(sp90, sp50, sp90);
    guMtxF2L(sp90, sp4C);
    Boss2C_WRITE_GFX(arg0++, 0xDA380003, (u32)sp4C);
    _sprintf(sp3C, "ROUND %d", D_80750AD4);
    Boss2C_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Boss2C_WRITE_GFX(arg0++, 0xE7000000, 0);
    Boss2C_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    Boss2C_WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFFF);
    arg0 = func_8070068C(arg0);
    func_806FC530(arg0, 1, 0, 0, sp3C, 0);
}

static void func_80028818(void) {}

void func_8073129C(s32, s32, s32);

void bossResetAudioChannels(void) {
    func_8073129C(0x51, 0, 2);
    func_8073129C(0x52, 0, 2);
    func_8073129C(0x53, 0, 2);
    func_8073129C(0x54, 0, 2);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80028878.s")

void func_8066EA64(void *, s32);
void func_8066EA90(void *, s32);

void func_800290D4(arg0)
u8 arg0;
{
    if (arg0) {
        func_8066EA64(D_807FBB40, 2);
        func_8066EA64(D_807FBB40, 3);
    } else {
        func_8066EA90(D_807FBB40, 2);
        func_8066EA90(D_807FBB40, 3);
    }
}

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} BossB_Struct_800359D0;

extern BossB_Struct_800359D0 D_800359D0[];
extern s32 D_8076A0A8;

s32 func_8073110C(s16, s32);

void bossUpdateStageState(s16 *arg0) {
    s16 i = 0;
    while (D_800359D0[i].unk0 != 0 && D_8076A0A8 != D_800359D0[i].unk0) {
        i++;
    }
    if (D_800359D0[i].unk0 != 0 && D_800359D0[i].unk4 == *arg0) {
        if (func_8073110C(D_800359D0[i].unk2, 2) != 0) {
            *arg0 = D_800359D0[i].unk5;
        }
    }
}

void bossPlayStageMusic(void) {
    s16 i = 0;
    while (D_800359D0[i].unk0 != 0 && D_8076A0A8 != D_800359D0[i].unk0) {
        i++;
    }
    if (D_800359D0[i].unk0 != 0) {
        func_8073129C(D_800359D0[i].unk2, 1, 2);
    }
}
