#include "common.h"

void *func_80610FE8(s32);
void heapClearBlock(void *);
struct RaceUnknownActor;
struct RaceStruct3;
typedef struct Struct806C7C94 {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Struct806C7C94;

typedef struct RacePair {
    struct RaceUnknownActor *unk0;
    struct RaceStruct3 *unk4;
} RacePair;

typedef struct RaceUnknown174 {
    u8 unk0;
    char pad1;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    u16 unk1C;
    u8 unk1E;
    char pad1F[1];
    RacePair *unk20;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    char pad29;
    u8 unk2A;
    char pad2B;
    void *unk2C;
    struct RaceUnknownActor *unk30;
    char pad34[2];
    u8 unk36;
    char pad37[0x11];
    Struct806C7C94 *unk48;
    char pad4C[0x88 - 0x4C];
    struct RaceUnknownActor *unk88;
} RaceUnknown174;

typedef struct Struct_Player {
    char pad0[4];
    struct RaceUnknownActor *unk4;
    char pad8[0x2F0 - 8];
} Struct_Player;
extern Struct_Player *D_807FC924;

typedef struct RaceStruct3 {
    char pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    char pad20[0x26 - 0x20];
    u8 unk26;
    u8 unk27;
    u8 unk28;
    char pad29[0x34 - 0x29];
    u8 unk34;
    u8 unk35;
    u8 unk36;
    s8 unk37;
    char pad38[2];
    u16 unk3A;
    s16 unk3C;
    char pad3E[2];
    f32 unk40;
    char pad44[0x45 - 0x44];
    u8 unk45;
    u8 unk46;
    char pad47[1];
    s32 unk48;
} RaceStruct3;

typedef struct RaceSub4 {
    char pad0[0x4];
    f32 unk4;
    char pad8[0x34 - 0x8];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} RaceSub4;

typedef struct RaceUnknownActor {
    char pad0[0x4];
    RaceSub4 *unk4;
    char pad8[0xF - 0x8];
    u8 unkF;
    u8 unk10;
    char pad11[0x58 - 0x11];
    s32 unk58;
    char pad5C[0x60 - 0x5C];
    u32 unk60;
    char pad64[0x6A - 0x64];
    u16 unk6A;
    u16 unk6C;
    char pad6E[0x7C - 0x6E];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xAC - 0x88];
    f32 unkAC;
    char padB0[0xB8 - 0xB0];
    f32 unkB8;
    char padBC[0xEE - 0xBC];
    s16 unkEE;
    char padF0[0x154 - 0xF0];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    RaceUnknown174 *unk174;
    RaceUnknown174 *unk178;
    s32 *unk17C;
} RaceUnknownActor;
typedef struct RaceUnknownC {
    char pad0[0xC];
    RaceUnknownActor *unkC;
} RaceUnknownC;
typedef struct RaceUnknownDCF0 {
    char pad0[0x1C];
    RaceUnknownActor *unk1C[2];
} RaceUnknownDCF0;
typedef struct Struct_807FD63A {
    u16 unk0;
    char pad2[0x32];
} Struct_807FD63A;
extern Struct_807FD63A D_807FD63A[];




void func_8002BBD0(RaceUnknownActor *arg0, s32 arg1) {
    RaceUnknown174 *sp1C;
    void *temp_v0;

    sp1C = arg0->unk174;
    temp_v0 = func_80610FE8(arg1 * 8);
    sp1C->unk20 = temp_v0;
    heapClearBlock(temp_v0);
    sp1C->unk1E = arg1;
    sp1C->unk1C = 0xFFFF;
    arg0->unk154 = 0;
}

u16 *func_8002E960(u8);
void func_8002F36C(void *, void *);
s32 cameraFindViewportEntry(u8);
#define RaceE3 ((RaceStruct3 *)arg3)

void func_8002BC2C(RaceUnknownActor *arg0, s32 arg1, RaceUnknownActor *arg2, RaceUnknown174 *arg3) {
    RaceUnknown174 *temp_t0;
    RacePair *temp_v1;
    RacePair *temp_v0;
    u16 *temp_a1;

    temp_t0 = arg0->unk174;
    temp_v1 = temp_t0->unk20;
    temp_v0 = (RacePair *)((s32)temp_v1 + (arg1 * 8));
    temp_v0->unk0 = arg2;
    temp_v0->unk4 = RaceE3;
    RaceE3->unk45 = 0;
    RaceE3->unk3A = 0;
    RaceE3->unk37 = 1;
    if (RaceE3->unk27 == 0) {
        temp_a1 = func_8002E960(temp_t0->unk26);
        if (temp_a1 != NULL) {
            RaceE3->unk3C = *temp_a1 - 1;
            func_8002F36C(arg3, temp_a1);
        }
        RaceE3->unk48 = cameraFindViewportEntry(RaceE3->unk28);
    }
}
#undef RaceE3

void func_8002BCB0(RaceUnknownActor *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    RaceUnknown174 *temp_v0;
    RacePair *temp_v1;
    RacePair *temp_t0;

    temp_v0 = arg0->unk174;
    temp_v1 = temp_v0->unk20;
    temp_t0 = (RacePair *)((s32)temp_v1 + (arg1 * 8));
    *arg2 = (s32)temp_t0->unk0;
    *arg3 = (s32)temp_t0->unk4;
}

typedef struct RaceEBounds {
    f32 *start;
    char pad4[8];
    f32 *end;
} RaceEBounds;
extern RaceEBounds *D_807F5FD4;

void func_8002BCD4(RaceUnknownActor *arg0) {
    RaceUnknown174 *temp_v0;
    f32 *p;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    f32 x;
    f32 z;

    minX = 9999.0f;
    minZ = 9999.0f;
    maxX = -1.0f;
    maxZ = -1.0f;
    temp_v0 = arg0->unk174;
    for (p = D_807F5FD4->start; p < D_807F5FD4->end; p += 3) {
        x = p[0];
        if (x < minX) {
            minX = x;
        }
        z = p[2];
        if (z < minZ) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxZ < z) {
            maxZ = z;
        }
    }
    temp_v0->unkC = ((maxX - minX) * 0.5f + minX) - 10.0f;
    temp_v0->unk10 = ((maxZ - minZ) * 0.5f + minZ) - 20.0f;
    temp_v0->unk4 = 116.48f / (maxX - minX);
    temp_v0->unk8 = 121.6f / (maxZ - minZ);
}

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_8002BDDC(Gfx *arg0, RaceUnknownActor *arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    RaceUnknown174 *temp_v0;

    temp_v0 = arg1->unk174;
    arg2 = temp_v0->unkC - arg2;
    arg3 = temp_v0->unk10 - arg3;
    arg2 *= temp_v0->unk4;
    arg3 *= temp_v0->unk8;
    gDPSetPrimColor(arg0++, 0, 0, arg4, arg5, arg6, 0xC8);
    return func_8068C5A8(arg0, 0x4A, 3, 1, 0x10, 0x10,
        (s32)(((0.5f * arg2) + 50.0f) * 4.0f),
        (s32)(((0.5f * arg3) + 60.0f) * 4.0f),
        1.0f, 1.0f, 0, 0.0f);
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern u8 D_807444FC;
extern s16 D_80744490;
Gfx *func_805FD030(Gfx *);
s32 _sprintf(char *, const char *, ...);
void *heapFreeDeferred(void *);
void *func_8070E750(s32, s32, s32);
s32 func_806FBD5C(s32, void *);
Gfx *func_806FC530(Gfx *, s32, s32, s32, void *, s32);

Gfx *func_8002BEE8(Gfx *arg0, RaceUnknownActor *arg1) {
    u8 sp3F;
    s32 sp38;
    s32 temp_v0;
    RaceUnknown174 *temp_v1;
    s32 var_a2;
    void *var_s1;
    f32 temp_fv0;

    sp3F = 0xFF;
    sp38 = D_80744490 / 2;
    temp_v1 = arg1->unk174;
    if (arg1->unk154 == 2 || arg1->unk154 == 1) {
        if (temp_v1->unk1C < 0x78) {
            if (temp_v1->unk1C < 0x5A) {
                var_a2 = (0x78 - temp_v1->unk1C) / 30;
                if (var_a2 >= 3) {
                    var_a2 = 3;
                }
                var_s1 = func_80610FE8(4);
                heapFreeDeferred(var_s1);
                _sprintf(var_s1, "%d", var_a2);
            } else {
                temp_fv0 = (f32)(0x78 - temp_v1->unk1C) * 0.033333335f;
                sp3F = (u8)(u32)((f32)sp3F * temp_fv0);
                var_s1 = func_8070E750(0x26, 9, 1);
            }
            WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
            WRITE_GFX(arg0++, 0xE7000000, 0);
            WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
            WRITE_GFX(arg0++, 0xFA000000, sp3F & 0xFF);
            WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
            sp38 -= func_806FBD5C(1, var_s1) >> 1;
            arg0 = func_806FC530(arg0, 1, (s16)(sp38 * 4), 0x3C, var_s1, 1);
        }
    }
    return arg0;
}

Gfx *func_8002C14C(Gfx *arg0, RaceUnknown174 *arg1) {
    Struct806C7C94 *temp_v0;
    s32 temp_ft4;
    s32 temp_t0;
    s32 var_s0;
    s32 var_s1;
    f32 temp_fs1;
    s16 temp_s4;
    f32 f_s1;

    temp_v0 = arg1->unk48;
    temp_ft4 = (s32)((f64)(temp_v0->unk4 + 8) + 4.0);
    temp_t0 = temp_v0->unkA - 0x22;
    WRITE_GFX(arg0++, 0xFA000000, 0xFFC800B4);
    var_s0 = 0;
    if (arg1->unk2A > 0) {
        var_s1 = 0;
        temp_fs1 = (f32)temp_ft4 + (f32)temp_ft4;
        temp_s4 = (s16)(s32)(((f32)temp_t0 + (f32)temp_t0) * 4.0f);
        do {
            Gfx *next;
            f_s1 = var_s1;
            next = func_8068C5A8(arg0, 0x4A, 3, 1, 0x10, 0x10,
                (s32)((temp_fs1 + f_s1) * 4.0f),
                temp_s4, 4.0f, 4.0f, 0, 0.0f);
            var_s0++;
            var_s1 += 0x10;
            arg0 = next;
        } while (var_s0 < arg1->unk2A);
    }
    if (arg1->unk2A != 0) {
        WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    }
    return arg0;
}

#ifdef NON_MATCHING
u32 func_806FD894(s32);

Gfx *func_8002C2E8(Gfx *arg0, RaceUnknown174 *arg1) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv0;
    Struct806C7C94 *temp_s0;
    f32 sp70;
    f32 temp_t1;
    f32 temp_t2;
    s16 temp_s3;
    s32 var_s0;
    s32 var_s1;
    void *temp_v0_2;

    temp_s0 = arg1->unk48;
    temp_fv0 = (f32)func_806FD894(1) * 0.5f;
    sp70 = temp_fv0;
    temp_fs0 = (f32)(temp_s0->unk4 + 8);
    temp_fs2 = (f32)(temp_s0->unkA - 0x10);
    temp_fs2 -= 2 * temp_fv0;
    temp_v0_2 = func_8070E750(0x26, 0xA, 1);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFFF);
    arg0 = func_806FC530(arg0, 1, (s16)(s32)(2.0f * (temp_fs0 * 4.0f)), (s16)(s32)(2.0f * (temp_fs2 * 4.0f)), temp_v0_2, 4);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
    WRITE_GFX(arg0++, 0xDA380005, (u32)((u8 *)arg1 + (D_807444FC << 6) + 0x50));
    temp_t1 = 0.5f;
    temp_fs0 = temp_fs0 + ((f32)func_806FBD5C(1, temp_v0_2) * temp_t1);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFF00FF);
    temp_fs0 = (f32)((f64)temp_fs0 + 8.0);
    temp_fs1 = temp_fs0 + temp_fs0;
    temp_fs2 = (f32)((f64)temp_fs2 + (0.4 * (f64)sp70));
    temp_s3 = (s16)(s32)((temp_fs2 + temp_fs2) * 4.0f);
    var_s0 = 0;
    do {
        arg0 = func_8068C5A8(arg0, 0x4B, 3, 1, 0x40, 0x40, (s32)(((f32)var_s0 + temp_fs1) * 4.0f), temp_s3, 1.5f, 1.5f, 0, 0.0f);
        var_s0 += 0x18;
    } while (var_s0 < 0x78);
    WRITE_GFX(arg0++, 0xFA000000, 0xFF0000FF);
    var_s1 = 0;
    if ((5 - *((u8 *)arg1 + 0x44)) > 0) {
        var_s0 = 0;
        do {
            arg0 = func_8068C5A8(arg0, 0x45, 3, 1, 0x40, 0x40, (s32)(((f32)var_s0 + temp_fs1) * 4.0f), temp_s3, 1.5f, 1.5f, 0, 0.0f);
            var_s1 += 1;
            var_s0 += 0x18;
        } while (var_s1 < (5 - *((u8 *)arg1 + 0x44)));
    }
    WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    return arg0;
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/7BD0/func_8002C2E8.s")
#endif


Gfx *func_8002C63C(Gfx *arg0, RaceUnknown174 *arg1) {
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xE3000A01, 0);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    arg0 = func_805FD030(arg0);
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
    guScale((Mtx *)((u8 *)arg1 + (D_807444FC << 6) + 0x50), 0.5f, 0.5f, 1.0f);
    WRITE_GFX(arg0++, 0xDA380005, (u32)((u8 *)arg1 + (D_807444FC << 6) + 0x50));
    WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
    return arg0;
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/7BD0/func_8002C76C.s")


s32 func_807142D8(void);
Gfx *func_8002C63C(Gfx *, RaceUnknown174 *);
Gfx *func_8002C2E8(Gfx *, RaceUnknown174 *);
Gfx *func_8002C14C(Gfx *, RaceUnknown174 *);
Gfx *func_8002C76C(Gfx *, RaceUnknown174 *);

Gfx *func_8002CAC8(Gfx *arg0, RaceUnknownActor *arg1, RaceUnknown174 *arg2) {
    RaceUnknown174 *sp24;
    RaceUnknownActor *temp_v1;
    RaceUnknown174 *temp_v0;

    sp24 = arg2->unk30->unk174;
    if (arg2 == NULL || func_807142D8() != 0) {
        return arg0;
    }
    temp_v1 = D_807FC924[arg2->unk28].unk4;
    if (temp_v1 == NULL) {
        return arg0;
    }
    temp_v0 = temp_v1->unk174;
    if (arg1 != temp_v0->unk88) {
        return arg0;
    }
    arg0 = func_8002C63C(arg0, arg2);
    if (sp24->unk0 & 8) {
        arg0 = func_8002C2E8(arg0, arg2);
    } else if (sp24->unk0 & 0x10) {
        arg0 = func_8002C14C(arg0, arg2);
    }
    if (sp24->unk0 & 6) {
        arg0 = func_8002C76C(arg0, arg2);
    }
    return arg0;
}

struct RaceECB3;
typedef struct RaceECBPair {
    struct RaceUnknownActor *unk0;
    struct RaceECB3 *unk4;
} RaceECBPair;
typedef struct RaceECBView {
    u8 unk0;
    char pad1[0x13];
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    char pad1C[2];
    u8 unk1E;
    char pad1F;
    RaceECBPair *unk20;
} RaceECBView;
typedef struct RaceECB3 {
    char pad0[0x27];
    u8 unk27;
    char pad28[4];
    struct RaceUnknownActor *unk2C;
} RaceECB3;

Gfx *func_8002CBEC(Gfx *arg0, RaceUnknownActor *arg1) {
    RaceECBView *temp_s5;
    RaceECBPair *var_s2;
    RaceECB3 *temp_s0;
    RaceUnknownActor *temp_t0;
    RaceUnknownActor *temp_v1;
    RaceECBPair *temp_s6;
    s32 var_s3;
    int var_v0;
    int var_v1;

    temp_s5 = (RaceECBView *)arg1->unk174;
    if (temp_s5->unk0 & 1) {
        temp_s6 = temp_s5->unk20;
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xD7000000, 0xFFFFFFFF);
        WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
        arg0 = func_805FD030(arg0);
        var_v0 = 0x40;
        WRITE_GFX(arg0++, 0xFA000000, 0x3CA0);
        WRITE_GFX(arg0++, 0xE3000A01, 0);
        WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFDF6FB);
        WRITE_GFX(arg0++, 0xF6148170, 0x00048070);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xFA000000, 0x8000FF64);
        WRITE_GFX(arg0++, 0xF6150070, 0x00040068);
        WRITE_GFX(arg0++, 0xF6150178, 0x00040170);
        WRITE_GFX(arg0++, 0xF6048170, 0x00040070);
        WRITE_GFX(arg0++, 0xF6150170, 0x00148070);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFB4);
        WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
        WRITE_GFX(arg0++, 0xD7000002, 0x80008000);
        arg0 = func_8068C5A8(arg0, temp_s5->unk14, 3, 1, 0x40, 0x40, 0x88, 0x130, 2.0, 2.0, 0, 0.0f);
        arg0 = func_8068C5A8(arg0, temp_s5->unk16, 3, 1, var_v0, 0x40, 0x108, 0x130, 2, 2, 0, 0.0f);
        arg0 = func_8068C5A8(arg0, temp_s5->unk18, 3, 1, 0x40, 0x40, 0x88, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        arg0 = func_8068C5A8(arg0, temp_s5->unk1A, 3, 1, 0x40, 0x40, 0x108, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        var_v1 = temp_s5->unk1E;
        var_s3 = 0;
        var_s2 = temp_s6;
        if (var_v1 > 0) {
            do {
                temp_t0 = var_s2->unk0;
                if (temp_t0 == NULL) {
                } else {
                    temp_s0 = var_s2->unk4;
                    var_v0 = temp_s0->unk27;
                    if (var_v0 == 0) {
                        var_v0 = 0x80;
                        var_v1 = 0x80;
                    } else if ((var_v0 ^ 0) == 1) {
                        var_v0 = 0xFF;
                        var_v1 = 0;
                    } else {
                        goto next;
                    }
                    arg0 = func_8002BDDC(arg0, arg1, temp_t0->unk7C, temp_t0->unk84, var_v0, 0, var_v1);
                    temp_v1 = temp_s0->unk2C;
                    if (temp_v1 != NULL) {
                        arg0 = func_8002BDDC(arg0, arg1, temp_v1->unk7C, temp_v1->unk84, 0xFF, 0xC8, 0);
                    }
                    var_v1 = temp_s5->unk1E;
                }
next:
                var_s3 += 8;
                var_s2++;
            } while (var_s3 < (var_v1 * 8));
        }
    }
    return func_8002BEE8(arg0, arg1);
}


extern RaceUnknownActor *D_807FBB44;
void actorSpawn(s32, s32);
void raceInitParticipants(RaceUnknownActor *);
void func_800292D0(RaceUnknownActor *);
void func_8002E2C8(RaceUnknownActor *);

void func_80025E9C(RaceUnknownActor *);
void func_8002BCD4(RaceUnknownActor *);

void func_8002CFF0(void) {
    RaceUnknown174 *temp_v0;
    RaceUnknownActor *actor;

    actorSpawn(0x132, 0);
    actor = D_807FBB44;
    func_80025E9C(actor);
    func_8002BCD4(actor);
    temp_v0 = actor->unk174;
    temp_v0->unk0 = 0x17;
    temp_v0->unk14 = 0x46;
    temp_v0->unk16 = 0x47;
    temp_v0->unk18 = 0x48;
    temp_v0->unk1A = 0x49;
    temp_v0->unk24 = 2;
}


void func_8002D064(void) {
    RaceUnknown174 *sp1C;

    actorSpawn(0x132, 0);
    sp1C = D_807FBB44->unk174;
    raceInitParticipants(D_807FBB44);
    sp1C->unk0 = 0xE;
    sp1C->unk24 = 2;
}

void func_8002D0B0(void) {
    RaceUnknown174 *sp1C;

    actorSpawn(0x132, 0);
    sp1C = D_807FBB44->unk174;
    func_800292D0(D_807FBB44);
    sp1C->unk0 = 0xE;
    sp1C->unk24 = 2;
}

void func_8002D0FC(void) {
    RaceUnknown174 *sp1C;

    actorSpawn(0x132, 0);
    sp1C = D_807FBB44->unk174;
    func_8002E2C8(D_807FBB44);
    sp1C->unk0 = 2;
    sp1C->unk24 = 1;
}

extern s32 D_8002FCD4[];
s32 func_806FDB8C(s32, void *, s32, f32, f32, f32);

void func_8002D148(RacePair *arg0, u8 arg1) {
    extern RaceUnknownActor *D_807FBB40;
    RaceUnknown174 *t;
    s32 slot;

    if (arg0->unk4->unk34 != arg1) {
        arg0->unk4->unk34 = arg1;
        arg0->unk4->unk35 = 0;
        if (arg1 == 3) {
            t = D_807FBB40->unk174;
            slot = arg0->unk4->unk36;
            if (slot + 1 == (u32)t->unk1E || arg0->unk4->unk45 != 0) {
                slot = 3;
            }
            if (arg0->unk4->unk27 == 0) {
                arg0->unk4->unk46 = func_806FDB8C(1, func_8070E750(0x26, D_8002FCD4[slot], 1), 2, 160.0f, 100.0f, 0.0f);
            }
        }
    }
}

extern RaceUnknownActor *D_807FBB40;
void func_8002D148(RacePair *, u8);

void func_8002D224(u8 arg0) {
    s32 i;
    RaceUnknown174 *temp_s2;
    RacePair *temp_s3;
    u8 temp_s4;

    temp_s2 = D_807FBB40->unk174;
    temp_s4 = arg0;
    i = 0;
    temp_s3 = temp_s2->unk20;
    D_807FBB40->unk154 = temp_s4;
    if (temp_s2->unk1E > 0) {
        do {
            if (temp_s3[i].unk0 != 0) {
                func_8002D148(&temp_s3[i], temp_s4);
            }
            i++;
        } while (i < temp_s2->unk1E);
    }
}

f32 func_8002D2C0(RaceStruct3 *arg0) {
    f32 temp;

    if (arg0->unk26 >= 11 && arg0->unk26 < 15 && (D_807FD63A[arg0->unk28].unk0 & 0x2000)) {
        temp = arg0->unk26 - 10;
        return temp * 0.2f;
    }
    return 0.0f;
}

void actorDespawn(void *, void *);

void func_8002D338(void *arg0, RaceUnknownC *arg1) {
    RaceUnknownActor *temp_v0;
    RaceUnknown174 *temp_v1;

    temp_v0 = arg1->unkC;
    temp_v1 = temp_v0->unk174;
    temp_v1->unk2C = NULL;
    actorDespawn(arg0, arg1);
}

RaceUnknownActor *func_8002D360(RaceUnknownActor *arg0) {
    RaceUnknownActor *owner;
    f32 best;
    f32 d;
    RaceUnknown174 *own174;
    RaceUnknownActor *ret;
    RaceUnknownActor *o;
    RaceUnknown174 *t;
    RacePair *list;
    s32 i;

    best = 1e9f;
    own174 = arg0->unk174;
    owner = own174->unk30;
    t = owner->unk174;
    ret = NULL;
    list = t->unk20;
    for (i = 0; i < t->unk1E; i++) {
        o = list[i].unk0;
        if (o != NULL && o != arg0) {
            d = (arg0->unk7C - o->unk7C) * (arg0->unk7C - o->unk7C) + (arg0->unk80 - o->unk80) * (arg0->unk80 - o->unk80) + (arg0->unk84 - o->unk84) * (arg0->unk84 - o->unk84);
            if (d < best) {
                ret = o;
                best = d;
            }
        }
    }
    return ret;
}

void sfxAllocateChannel(s32, f32);

void func_8002D40C(void) {
    RaceUnknown174 *temp_v0;
    RacePair *list;
    RaceStruct3 *s;
    s32 i;
    s32 id;

    temp_v0 = D_807FBB40->unk174;
    id = 0;
    list = temp_v0->unk20;
    i = temp_v0->unk1E - 1;
    if (i >= 0) {
        do {
            s = list[i].unk4;
            if (s->unk27 == 1) {
                if (s->unk36 != 0) {
                    id = 0x56;
                } else {
                    id = 0x57;
                }
            }
            i--;
        } while (id == 0 && i >= 0);
    }
    if (id == 0) {
        id = 0x56;
    }
    sfxAllocateChannel(id, 1.0f);
}

extern s32 D_8076A0A8;

void func_8002D4A0(void) {
    s32 soundId;
    f32 vol;

    vol = 1.0f;
    switch (D_8076A0A8) {
    case 0xE:
        soundId = 0x13;
        vol = 0.6f;
        break;
    case 0x27:
        soundId = 0x3D;
        break;
    case 0x52:
        soundId = 0x66;
        break;
    case 0x1B:
    default:
        soundId = 0x1B;
        break;
    }
    sfxAllocateChannel(soundId, vol);
}
void func_8002D40C(void);

#pragma GLOBAL_ASM("asm/race/nonmatchings/7BD0/func_8002D524.s")

void func_8002D72C(RaceUnknownActor *arg0) {
    RaceUnknown174 *temp_v0;

    if (arg0 != NULL && arg0->unk154 == 0) {
        temp_v0 = arg0->unk174;
        temp_v0->unk1C = 2;
    }
}

void func_8002D754(RaceUnknownActor *arg0) {
    RaceUnknown174 *temp_v0;

    if (arg0 != NULL && arg0->unk154 == 0) {
        temp_v0 = arg0->unk174;
        temp_v0->unk1C = 0;
    }
}

#ifdef NON_MATCHING
typedef struct RaceFActorView {
    char pad0[4];
    RaceSub4 *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0xE4 - 0x64];
    s16 unkE4;
    char padE6[2];
    s16 unkE8;
    char padEA[0x128 - 0xEA];
    s16 unk128;
} RaceFActorView;
void func_80609140(s16, s32, f32, f32, s32, s32);
void func_8002F950(RaceUnknown174 *);

void func_8002D524(void);

void func_8002D778(void) {
    void renderCallbacksRegister(void *, RaceUnknownActor *, s32);
    RaceUnknown174 *t;
    u16 sound;
    u8 i;
    RaceStruct3 *s;
    f32 scale;
    RaceFActorView *pa;
    s32 k;
    u16 cnt;
    RacePair *list;
    RacePair *list0;

    t = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        t->unk1C = 0x1E;
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (t->unk1C != 0) {
            t->unk1C = (u32)t->unk1C - 1;
        } else {
            func_8002D224(1);
        }
        break;
    case 1:
        if (t->unk1C < 0x5B) {
            if (t->unk1C % 30 == 0) {
                sound = 0x75;
                if (t->unk1C == 0x5A) {
                    func_8002D224(2);
                    sound = 0x74;
                    func_8002D4A0();
                }
                func_80609140(sound, 0x7FFF, 64.0f, 1.0, 0, 0x80);
            }
            t->unk1C = (u32)t->unk1C + 1;
        }
        break;
    case 2:
        if (t->unk1C < 0x78) {
            t->unk1C = (u32)t->unk1C + 1;
        }
        func_8002D524();
        break;
    case 3:
        if (D_8076A0A8 == 0xE || D_8076A0A8 == 0x52) {
            func_8002D224(4);
            t->unk1C = 0x32;
        } else {
            cnt = (u64)(t->unk1C + 1);
            t->unk1C = cnt;
            if (cnt >= 0x78) {
                if (t->unk25 == 1) {
                    func_8002D224(4);
                    t->unk1C = 0x32;
                } else {
                    func_8002D224(6);
                }
            }
        }
        break;
    case 4:
        if (t->unk1C != 0) {
            t->unk1C = t->unk1C - 1;
        } else {
            list0 = t->unk20;
            i = 0;
            list = list0;
            if (t->unk1E > 0) {
                do {
                    s = list[i].unk4;
                    if (s->unk27 == 0) {
                        pa = (RaceFActorView *)D_807FC924[s->unk28].unk4;
                        scale = 1.0f;
                        pa->unk128 = 0xFF;
                        pa->unk60 |= 0x8000;
                        if (D_8076A0A8 == 0xB9) {
                            scale = 0.3f;
                        }
                        for (k = 0; k < 3; k++) {
                            (&pa->unk4->unk34)[k] = scale * 0.15;
                        }
                        pa->unkE8 = 0;
                        pa->unkE4 = 0;
                    }
                    i++;
                } while (i < t->unk1E);
            }
            func_8002D224(5);
        }
        break;
    }
    func_8002F950(t);
    if (func_807142D8() == 0) {
        if (D_807FBB40->unk154 > 0 && D_807FBB40->unk154 < 5) {
            renderCallbacksRegister((void *)func_8002CBEC, D_807FBB40, 3);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/7BD0/func_8002D778.s")
#endif

f32 func_80612794(s16);

void func_8002DA68(RaceUnknown174 *arg0) {
    s16 var_v0;
    f32 temp_fv1;

    switch (D_807FBB40->unk154) {
    case 0:
        var_v0 = arg0->unk2;
        if (((s16)(var_v0 % 2048) >= 0x81) && ((0x800 - (s16)(var_v0 % 2048)) >= 0x81)) {
            arg0->unk2 = var_v0 + 0x80;
            var_v0 = arg0->unk2;
        }
        break;
    case 1:
        arg0->unk2 += 0x80;
        var_v0 = arg0->unk2;
        break;
    default:
        var_v0 = arg0->unk2;
        break;
    }
    arg0->unk2 = var_v0 & 0xFFF;
    {
        f32 temp_fa0 = (((func_80612794(arg0->unk2) + 1.0f) * 1.5) + 1.0) * arg0->unk4;
        D_807FBB40->unk4->unk3C = temp_fa0;
    }
    temp_fv1 = D_807FBB40->unk4->unk3C;
    D_807FBB40->unk4->unk38 = temp_fv1;
    D_807FBB40->unk4->unk34 = temp_fv1;
}
void animSetSpeed(RaceUnknownActor *, s32, f32);
void animSetLoopLimit(RaceUnknownActor *, s32, s32);
void animSetFinished(RaceUnknownActor *, s32, s32);
s32 animIsPlaying(RaceUnknownActor *, s32);

void func_8002DB90() {
    if (D_807FBB40->unk154 != 0) {
        if (D_807FBB40->unk154 == 1) {
            if (animIsPlaying(D_807FBB40, 0) == 0) {
                animSetSpeed(D_807FBB40, 0, 1.0f);
                animSetLoopLimit(D_807FBB40, 0, -1);
            }
        }
    } else {
        if (animIsPlaying(D_807FBB40, 0) != 0) {
            animSetFinished(D_807FBB40, 0, 1);
        }
    }
}

void func_80665564(RaceUnknownActor *, f32);
void actorUpdateModelMatrix(RaceUnknownActor *, s32);

void func_8002DC24(void) {
    RaceUnknown174 *temp_a0 = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_a0->unk4 = D_807FBB40->unk4->unk38;
    }
    switch (temp_a0->unk0) {
    case 2:
        func_8002DB90(temp_a0);
        break;
    case 1:
        func_8002DB90(temp_a0);
        func_80665564(D_807FBB40, 0.0f);
        D_807FBB40->unk80 = D_807FBB40->unkAC;
        D_807FBB40->unk6A |= 4;
        D_807FBB40->unk6C |= 4;
        break;
    default:
        func_8002DA68(temp_a0);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct RaceFView8 {
    char pad0[8];
    u8 unk8;
} RaceFView8;

void func_8002DCF0(RaceUnknownDCF0 *arg0, s32 arg1) {
    u8 i;
    RaceUnknownActor *a;
    RaceFView8 *p;

    for (i = 0; i < 2; i++) {
        a = arg0->unk1C[i];
        if (a != NULL) {
            p = (RaceFView8 *)a->unk174;
            if (arg1 == 1) {
                if (p->unk8 == 0) {
                    a->unk154 = arg1;
                }
                p->unk8 = p->unk8 + 1;
            } else {
                if (p->unk8 != 0) {
                    p->unk8 = p->unk8 - 1;
                }
                if (p->unk8 == 0) {
                    a->unk154 = arg1;
                }
            }
        }
    }
}

f32 raceLerp(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    return ((arg4 - arg2) * ((arg0 - arg1) / (arg3 - arg1))) + arg2;
}

typedef struct RaceCurvePoint {
    f32 x;
    f32 y;
} RaceCurvePoint;

typedef struct RaceVec3f {
    f32 x;
    f32 y;
    f32 z;
} RaceVec3f;

f32 func_8002DDA0(f32 arg0, RaceCurvePoint *arg1) {
    s32 pad3C;
    f32 sp38;
    f32 ret;
    u8 i;
    s32 found;

    found = 0;
    i = 1;
    if (arg0 < arg1[0].x) {
        ret = arg1[0].y;
        found = 1;
        sp38 = ret;
    }
    ret = sp38;
    if (found == 0) {
        do {
            f32 x = arg1[i].x;
            if (arg0 < x) {
                ret = raceLerp(arg0, arg1[i - 1].x, arg1[i - 1].y, x, arg1[i].y);
                found = 1;
            }
            i++;
        } while (i < 6 && found == 0);
    }
    if (found == 0) {
        ret = arg1[5].y;
    }
    return ret;
}

void func_8002DE78(RaceUnknownActor *arg0, u8 arg1, RaceCurvePoint *arg2, RaceVec3f *arg3) {
    switch (arg1) {
    case 0:
    case 1:
        arg2[0].y = arg3->x;
        arg2[1].y = arg3->y;
        arg2[2].y = arg3->y;
        arg2[3].y = arg3->y;
        arg2[4].y = arg3->y;
        arg2[5].y = arg3->z;
        break;
    case 2:
    case 3:
        arg2[3].y = arg3->z;
        arg2[4].y = arg3->z;
        arg2[5].y = arg3->z;
        break;
    case 5:
        arg2[0].y = arg3->x;
        arg2[1].y = arg3->z;
        arg2[2].y = arg3->z;
        arg2[3].y = arg3->z;
        arg2[4].y = arg3->z;
        arg2[5].y = arg3->z;
        break;
    }
    D_807FBB40->unk155 = 0;
    arg0->unkF = arg1;
}

s32 func_806119A0(void);

f32 func_8002DF38(RaceUnknownActor *arg0, f32 arg1, RaceCurvePoint *arg2, RaceVec3f *arg3) {
    f32 ret;
    f32 lim;
    RaceSub4 *sub;

    switch (arg0->unkF) {
    case 0:
        ret = func_8002DDA0(arg1, arg2);
        break;
    case 1:
        ret = func_8002DDA0(arg1, arg2);
        if (arg0->unk10 != 0) {
            if (arg2[4].x < arg1) {
                if ((u32)func_806119A0() % 0xFF < 0xA) {
                    func_8002DE78(arg0, 2, arg2, arg3);
                }
            }
        }
        break;
    case 2:
    case 3:
    case 4:
        if (arg0->unkF == 3 || arg0->unkF == 4 || arg0->unk10 != 0) {
            sub = arg0->unk4;
            lim = sub->unk4;
            arg2[0].y = lim < arg3->x ? lim : arg3->x;
            arg2[1].y = lim < arg3->y ? lim : arg3->y;
            if (arg0->unkF == 4) {
                arg2[2].y = lim;
            } else {
                arg2[2].y = arg3->z;
            }
            ret = func_8002DDA0(arg1, arg2);
            if (arg0->unkF == 2) {
                if (arg1 < arg2[3].x) {
                    func_8002DE78(arg0, 3, arg2, arg3);
                }
            }
            if (arg0->unkF == 3) {
                if (arg1 < arg2[2].x) {
                    func_8002DE78(arg0, 4, arg2, arg3);
                }
            }
        } else if (arg0->unkF == 2) {
            ret = arg3->y;
            func_8002DE78(arg0, 1, arg2, arg3);
        }
        break;
    case 5:
        ret = func_8002DDA0(arg1, arg2);
        if (arg1 < arg2[1].x) {
            func_8002DE78(arg0, 1, arg2, arg3);
        }
        break;
    default:
        ret = 0.0f;
        break;
    }
    return ret;
}

f32 func_8002E1C8(RaceUnknownActor *arg0, f32 arg1, RaceCurvePoint *arg2, RaceVec3f *arg3) {
    f32 ret;

    switch (arg0->unkF) {
    case 0:
        ret = func_8002DDA0(arg1, arg2);
        break;
    case 1:
        ret = func_8002DDA0(arg1, arg2);
        if (arg0->unk10 != 0) {
            if (arg2[4].x < arg1) {
                func_8002DE78(arg0, 5, arg2, arg3);
            }
        }
        break;
    case 5:
        ret = func_8002DDA0(arg1, arg2);
        if (arg1 < arg2[1].x) {
            func_8002DE78(arg0, 1, arg2, arg3);
        }
        break;
    default:
        ret = 0.0f;
        break;
    }
    return ret;
}

extern u8 D_807FC928;
RaceUnknownActor *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);
void func_8002BC2C(RaceUnknownActor *, s32, RaceUnknownActor *, RaceUnknown174 *);

void func_8002E2C8(RaceUnknownActor *arg0) {
    RaceUnknown174 *sp5C;
    RaceUnknown174 *sp58;
    RaceUnknownActor *sp54;
    s32 var_s1;
    s32 var_s0;
    s32 var_s4;

    var_s4 = D_807FC928;
    var_s1 = 0;
    sp5C = arg0->unk174;
    if (var_s4 == 1) {
        var_s4++;
    }
    func_8002BBD0(arg0, var_s4);
    if (D_807FC928 == 1) {
        sp54 = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        sp58 = sp54->unk178;
        sp58->unk27 = 1;
        func_8002BC2C(arg0, 0, sp54, sp58);
        var_s1 = 1;
        func_8002BCB0(arg0, 0, sp54->unk17C, sp54->unk17C + 1);
        sp5C->unk25 = 1;
    } else {
        sp5C->unk25 = 0;
    }
    for (var_s0 = 0; var_s0 < D_807FC928; var_s0++) {
        actorSpawn(0x13B, 0);
        sp54 = D_807FBB44;
        sp58 = sp54->unk174;
        sp58->unk27 = 0;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        var_s1++;
        sp58->unk28 = var_s0;
    }
    var_s0 = 0;
    if (var_s4 > 0) {
        do {
            func_8002BCB0(arg0, var_s0, (s32 *)&sp54, (s32 *)&sp58);
            sp58->unk36 = var_s0;
            var_s0++;
            sp58->unk30 = arg0;
        } while (var_s0 != var_s4);
    }
    sp5C->unk26 = 0;
}


void func_8002E464(void *arg0, RaceUnknownActor *arg1) {
    func_8002CAC8(arg0, arg1, arg1->unk174);
}

void playerStateQueueCallback(s32, RaceUnknownActor *, u8, RaceUnknownActor *);
void func_8002F490(RaceStruct3 *);
void renderCallbacksRegister(void *, RaceUnknownActor *, s32);

void func_8002E484(void) {
    RaceUnknownActor *var_a3;
    RaceUnknownActor *temp_a1;
    RaceStruct3 *temp_s0;
    f32 temp_fa0;
    f32 temp_fv0_2;

    temp_a1 = D_807FBB40;
    temp_s0 = (RaceStruct3 *)temp_a1->unk174;
    var_a3 = D_807FC924[temp_s0->unk28].unk4;
    if (!(temp_a1->unk60 & 0x10)) {
        playerStateQueueCallback(0x4E, temp_a1, temp_s0->unk28, var_a3);
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155 = 0;
        temp_a1 = D_807FBB40;
    }
    if ((temp_s0->unk34 == 2) && (temp_a1->unk154 == 0)) {
        playerStateQueueCallback(0x57, NULL, temp_s0->unk28, var_a3);
        temp_a1 = D_807FBB40;
        temp_a1->unk154++;
        temp_a1 = D_807FBB40;
    }
    temp_a1->unk7C = var_a3->unk7C;
    D_807FBB40->unk80 = var_a3->unk80;
    D_807FBB40->unk84 = var_a3->unk84;
    if (temp_s0->unk34 == 2) {
        func_8002F490(temp_s0);
        temp_a1 = D_807FBB40;
    }
    if ((temp_s0->unk34 > 0) && (temp_s0->unk34 < 5)) {
        renderCallbacksRegister((void *)func_8002E464, D_807FBB40, 3);
    }
    temp_s0->unk1C = (temp_s0->unk40 < temp_s0->unk1C) ? temp_s0->unk1C : temp_s0->unk40;
    temp_fa0 = temp_s0->unk18;
    temp_fv0_2 = (f32)(temp_s0->unk3A * 3000) - temp_s0->unk40;
    temp_s0->unk14 = temp_fv0_2;
    if (temp_fv0_2 < temp_fa0) {
        temp_s0->unk18 = temp_fa0;
        return;
    }
    temp_s0->unk18 = temp_s0->unk14;
}

typedef struct RaceFE644Arg {
    RaceUnknownActor *unk0;
    char pad4[0xA];
    u8 unkE;
    u8 unkF;
    char pad10[4];
    f32 unk14;
} RaceFE644Arg;
extern u8 D_807FBD70;
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleDistance(s16, s16);
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void func_8002E644(RaceFE644Arg *arg0) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 fv1;
    s16 sp4A;
    s16 sp48;
    s16 sp46;
    f32 sp40;
    s32 sp3C;
    RaceUnknownActor *s0;
    s32 four;

    s0 = arg0->unk0;
    sp5C = (s0->unk7C - D_807FBB40->unk7C) * (s0->unk7C - D_807FBB40->unk7C) + (s0->unk84 - D_807FBB40->unk84) * (s0->unk84 - D_807FBB40->unk84);
    four = 4;
    if (D_807FBD70 == four && sp5C < arg0->unk14 && (arg0->unkF == 1 || arg0->unkF == 0 || arg0->unkF == 4 || (D_807FBB40->unk58 == 0x143 && arg0->unkF == 5))) {
        sp46 = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, s0->unk7C, s0->unk84);
        sp40 = 1.0f;
        if (mathAngleDistance(s0->unkEE, sp46) < 0x200) {
            sp40 = 4.0f;
        }
        sp48 = (s16)(s0->unkEE - sp46) & 0xFFF;
        sp4A = (s16)(D_807FBB40->unkEE - sp46);
        sp4A = sp4A & 0xFFF;
        sp54 = func_80612794(sp48) * s0->unkB8;
        sp50 = func_80612790(sp48) * s0->unkB8;
        fv1 = func_80612790(sp4A) * D_807FBB40->unkB8;
        sp50 = (fv1 - sp50) * sp40 + fv1;
        s0->unkB8 = sqrtf(sp54 * sp54 + sp50 * sp50);
        s0->unkEE = (s16)(s32)(((f64)func_80611BB4(sp54, sp50) * 4096.0) / 6.2831854820251465);
        s0->unkEE = s0->unkEE + sp46;
        s0->unkEE = s0->unkEE & 0xFFF;
        if (arg0->unkE == 0) {
            switch (D_807FBB40->unk58) {
            case 0x134:
                sp3C = 0x1F9;
                break;
            case 0x143:
                sp3C = 0x18A;
                break;
            }
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (s16)sp3C, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            arg0->unkE = 0x14;
        }
    }
    arg0->unk14 = sp5C;
    if (arg0->unkE > 0) {
        arg0->unkE = arg0->unkE - 1;
    }
}

s32 func_806F8AD4(s32, s32);
s32 func_8002E8EC(RaceStruct3 *arg0, RaceStruct3 *arg1, s32 arg2) {
    s32 ret;

    if (arg1->unk45 != 0) {
        ret = 0;
        goto end;
    }
    if (arg0->unk36 != 0) {
        if (func_806F8AD4(11, 0) >= arg2) {
            ret = 1;
        } else {
            ret = 3;
        }
        goto end;
    }
    ret = 2;
end:
    return ret;
}
