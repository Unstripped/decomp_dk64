#include "common.h"

typedef struct BossD_Actor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x144 - 0xF0];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x160 - 0x155];
    f64 unk160;
} BossD_Actor;

typedef struct BossD_Sub178 {
    u8 pad0[0x14];
    u8 unk14;
} BossD_Sub178;

typedef struct BossD_D580 {
    u8 pad0[0x1D8];
    f32 unk1D8;
    u8 pad1DC[0x1F4 - 0x1DC];
    s32 unk1F4;
    u8 pad1F8[0x1FE - 0x1F8];
    s16 unk1FE;
} BossD_D580;

typedef struct BossD_DC90 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0x1A - 0x10];
    u16 unk1A;
} BossD_DC90;

extern BossD_Actor *D_807FBB40;
extern BossD_Actor *D_807FBB4C;
extern BossD_D580 *D_807FD580;
extern BossD_DC90 *D_807FDC90;
extern void *gCamActor;

void func_800290D4(s32);
s32 playerStateQueueCallback(s32, void *, s32);
void zoneEntryGetPosition(s32, s32, void *, void *, void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void actorScriptStart(void *, s32);
s32 camIsCutsceneActive(void);
void camEndPath(void *);
void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806CFF9C(void *);
void camReturnToFollow(void *, void *);
void func_8063DA40(s32, s16);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80030920(s32 arg0) {
    s16 temp_t7;

    D_807FD580->unk1FE = 1;
    func_800290D4(1);
    D_807FBB40->unk144 = 0x24;
    playerStateQueueCallback(0x19, D_807FBB40, 0);
    zoneEntryGetPosition(1, 8, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    D_807FDC90->unkA = D_807FBB40->unk7C;
    D_807FDC90->unkC = D_807FBB40->unk80;
    D_807FDC90->unkE = D_807FBB40->unk84;
    zoneEntryGetPosition(1, 0x20, &D_807FBB4C->unk7C, &D_807FBB4C->unk80, &D_807FBB4C->unk84);
    D_807FBB4C->unkE6 = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk84);
    temp_t7 = D_807FBB4C->unkE6 + 0x800;
    D_807FBB40->unkE6 = temp_t7;
    D_807FBB40->unkEE = temp_t7;
    actorScriptStart(D_807FBB40, 0x3F9);
    if (camIsCutsceneActive() != 0) {
        camEndPath(gCamActor);
    }
    camSetTarget(gCamActor, D_807FBB4C, 4, 0x800, 0x5A, 0, 0x46, 0x64, 0x3A, 0, 0.3f);
}
void func_80030AE0(BossD_Sub178 *arg0) {
    func_800290D4(0);
    D_807FD580->unk1F4 = 0;
    if (D_807FBB4C->unk154 != 0x36) {
        func_806CFF9C(D_807FBB4C);
    }
    camReturnToFollow(gCamActor, D_807FBB4C);
    D_807FD580->unk1D8 = 0.01f;
    func_8063DA40(0xB, (arg0->unk14 <= 0) ? 0 : 4);
    func_8063DA40(0xC, (arg0->unk14 < 2) ? 0 : 4);
    func_8063DA40(0xD, (arg0->unk14 < 3) ? 0 : 4);
    func_8063DA40(0xE, (arg0->unk14 < 4) ? 0 : 4);
    func_8063DA40(0xA, 0xA);
}

void func_80030C30(f32 arg0) {
    D_807FBB40->unk7C = (f32) (((f64) (D_807FBB4C->unk7C - (f32) D_807FDC90->unkA) * D_807FBB40->unk160) + (f64) D_807FDC90->unkA);
    D_807FBB40->unk80 = (f32) (((f64) (D_807FBB4C->unk80 - (f32) D_807FDC90->unkC) * D_807FBB40->unk160) + (f64) D_807FDC90->unkC);
    D_807FBB40->unk84 = (f32) (((f64) (D_807FBB4C->unk84 - (f32) D_807FDC90->unkE) * D_807FBB40->unk160) + (f64) D_807FDC90->unkE);
    D_807FBB40->unk160 += arg0;
    if (D_807FBB40->unk160 > 0.8) {
        D_807FBB40->unk160 = 0.8;
    }
}

void func_80030D50(void) {
    s32 pad[1];
    f32 sp20;
    sp20 = func_80612794((s16) (s32) (D_807FBB40->unk160 * 10240.0));
    D_807FBB40->unk7C += (80.0f * func_80612794(D_807FBB40->unkE6 + 0x400)) * sp20;
    sp20 = func_80612794((s16) (s32) (D_807FBB40->unk160 * 10240.0));
    D_807FBB40->unk84 += (80.0f * func_80612790(D_807FBB40->unkE6 + 0x400)) * sp20;
}

void func_80030E58(void) {
    D_807FDC90->unk1A |= 1;
    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2E2, 0xFF, 0x65, 0, 0, 0.0f, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/func_80030EC4.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/func_80031AA0.s")

#ifdef NON_MATCHING
typedef struct BsB_Sub4_0 {
    char pad0[4];
    f32 unk4;
    char pad8[8];
    s16 unk10;
} BsB_Sub4_0;

typedef struct BsB_Sub4 {
    BsB_Sub4_0 *unk0;
} BsB_Sub4;

typedef struct BsB_Sub174_0_174 {
    char pad0[4];
    f32 unk4;
    char pad8[0xA];
    s8 unk12;
    char pad13[1];
    s8 unk14;
    char pad15[2];
    s8 unk17;
} BsB_Sub174_0_174;

typedef struct BsB_Sub174_0 {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0xCC];
    u8 unk154;
    char pad155[0x1F];
    BsB_Sub174_0_174 *unk174;
} BsB_Sub174_0;

typedef struct BsB_Sub174 {
    BsB_Sub174_0 *unk0;
    s8 unk4;
    s8 unk5;
} BsB_Sub174;

typedef struct BsB_Actor {
    char pad0[4];
    BsB_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5C];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0x40];
    s16 unk12A;
    char pad12C[0x18];
    u8 unk144;
    char pad145[0x25];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[7];
    BsB_Sub174 *unk174;
} BsB_Actor;

void func_80613C48(void *, s16, f32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80614644(void *, void *, f32);
void actorDespawn(void *);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
void actorUpdateModelMatrix(void *, s32);
extern s16 D_80035B00[];
extern s16 D_80035B08[];
extern s16 D_80035B10[];
extern s16 D_80035B18[];
extern s16 D_80035B20[];
extern s8 D_80035B28;
extern s16 D_80035B2C;
extern f32 D_80035B3C;
extern s16 D_80035B74;
extern f32 D_80036DC4;

#define ACTOR ((BsB_Actor *)D_807FBB40)

void func_80032B08(void) {
    BsB_Sub174 *sub174 = ACTOR->unk174;
    BsB_Sub174_0_174 *sp30 = sub174->unk0->unk174;
    BsB_Sub4_0 *sub4_0 = ACTOR->unk4->unk0;

    if (sub174->unk5 == 0) {
        f32 dx = D_807FBB4C->unk7C - ACTOR->unk7C;
        f32 dz = D_807FBB4C->unk84 - ACTOR->unk84;
        D_80036DC4 = dx * dx + dz * dz;
    }
    if (!(ACTOR->unk60 & 0x10)) {
        func_80613C48(ACTOR, sub174->unk4 + 0x668, 0.0f, 0.0f);
        ACTOR->unk12A = 0xFA0;
    }
    if (D_80035B28 & (1 << sub174->unk4)) {
        ACTOR->unkE8 = (s16)((s32)((f64)sp30->unk4 * 1024.0) - 0x400);
        ACTOR->unkE4 = D_80035B2C;
        if (sub4_0 != NULL) {
            if (D_80035B3C != sub4_0->unk4) {
                func_80614644(ACTOR, sub4_0, D_80035B3C);
            }
        }
    } else {
        ACTOR->unkE8 = 0;
        if (sub4_0 != NULL) {
            s32 v0 = sub174->unk4 + 0x66B;
            if (v0 != sub4_0->unk10) {
                func_80613C48(ACTOR, v0, 0.0f, 0.0f);
                func_80609140(0x38D, 0x7D00, 63.0f, 1.0f, 0, 0);
            } else {
                func_80614644(ACTOR, sub4_0, sub4_0->unk4 + 0.75f);
            }
            if (sub174->unk4 == 1) {
                if (sub4_0->unk4 > 24.0f) {
                    sub4_0->unk4 = 24.0f;
                }
                if (sub4_0->unk4 > 15.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            } else {
                if (sub4_0->unk4 > 37.0f) {
                    sub4_0->unk4 = 37.0f;
                }
                if (sub4_0->unk4 > 26.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            }
            if ((f64)ACTOR->unk80 < 0.0) {
                func_80609140(0x384, 0x7D00, 63.0f, 1.0f, 0, 0);
                actorDespawn(ACTOR);
            }
        }
    }
    if (sub174->unk5 == 0) {
        ACTOR->unk144 = 0xC;
        if (sub174->unk4 == 0) {
            if (sp30->unk17 == 1) {
                s16 temp_v1;
                if (sub174->unk0->unk154 == 0) {
                    D_80035B74 = 0x28;
                }
                temp_v1 = D_80035B74 - 1;
                D_80035B74 = temp_v1;
                if (temp_v1 < 0) {
                    f32 x = ACTOR->unk7C + D_80035B18[sp30->unk14];
                    f32 y = ACTOR->unk80 + 270.0f;
                    f32 z = ACTOR->unk84 + D_80035B20[sp30->unk14];
                    D_80035B74 = 0xA;
                    projectileSetTargetCoords(x, y, z);
                    projectileAimAndSpawn(0x2C, 1, 0.25f, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84, 2400.0f, ACTOR);
                }
            } else {
                D_80035B74 = 0;
            }
        }
        ACTOR->unk7C = D_80035B00[sp30->unk14] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[sp30->unk14] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[sp30->unk14];
    } else {
        s32 var_v0;
        ACTOR->unk144 = 1;
        var_v0 = sp30->unk14 + 2;
        if (var_v0 >= 4) {
            var_v0 -= 4;
        }
        ACTOR->unk7C = D_80035B00[var_v0] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[var_v0] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[var_v0];
        ACTOR->unk60 |= 0x800000;
        ACTOR->unk16A = 0x23;
        ACTOR->unk16B = 0x23;
        ACTOR->unk16C = 0x46;
        if (sp30->unk12 != 1) {
            ACTOR->unk60 &= ~4;
        } else {
            ACTOR->unk60 |= 4;
        }
    }
    actorUpdateModelMatrix(ACTOR, 0);
}
#undef ACTOR
#else

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/func_80032B08.s")
#endif

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036A90.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036AA8.s")
