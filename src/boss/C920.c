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

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/func_80032B08.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036A90.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036AA8.s")
