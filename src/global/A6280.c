#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;

void actorUpdateModelMatrix(Actor *, s32);

typedef struct ActorView {
    u8 pad0[0x130];
    u8 unk130;
    u8 unk131;
    u8 pad132[0x178 - 0x132];
    void *unk178;
} ActorView;

typedef struct ActorSubView {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0x15F - 0xEE];
    u8 unk15F;
} ActorSubView;

typedef struct PlayerState {
    u8 unk0;
    u8 pad1[0x20F];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} PlayerState;

extern Actor *D_807FBB4C;
extern PlayerState *D_807FC924;
extern u8 D_807506C0[];
extern u8 D_807FBD70;

s16 actorListFindIdByActor(Actor *);
void *spawnNodeActivate(s32, s32);
void animSetStartFrame(Actor *, s32, s32);
s32 animIsPlaying(Actor *, s32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void actorAppendCallback(void *, s32, s32, u8, s32, void *);
void sfxAllocateChannel(s32, f32);

void actorSeekTargetUpdate(void) {
    s16 sp36;
    ActorSubView *sp30;
    f32 sp2C;
    f32 dx;
    f32 dz;

    sp36 = actorListFindIdByActor(D_807FBB40);
    sp30 = spawnNodeActivate(2, 0);
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((ActorView *)D_807FBB40)->unk130 = 0x46;
        ((ActorView *)D_807FBB40)->unk131 = 0x32;
        D_807FBB40->unk6A &= ~1;
        D_807FBB40->unk144 = 2;
        D_807FBB40->unk60 |= 0x80000000;
        D_807FBB40->unk64 |= 0x28;
        animSetStartFrame(D_807FBB40, 0, 1);
    }
    dx = D_807FBB4C->unk7C - D_807FBB40->unk7C;
    dz = D_807FBB4C->unk84 - D_807FBB40->unk84;
    if (dx * dx + dz * dz < 50000.0f) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    if (sp30 != NULL) {
        if (sp36 == D_807506C0[sp30->unk15F]) {
            dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
            dz = D_807FBB40->unk84 - D_807FBB4C->unk84;
            if (dx * dx + dz * dz > 900.0f) {
                sp2C = mathAngleBetweenPointsDeg((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk84, (s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84);
                sp30->unkEC = (s16)(sp2C - mathAngleBetweenPointsDeg((s32)D_807FC924->unk228, (s32)D_807FC924->unk230, (s32)D_807FC924->unk210, (s32)D_807FC924->unk218));
            }
            if (animIsPlaying(D_807FBB40, 0) == 0) {
                animSetSpeed(D_807FBB40, 0, 1.0f);
                animSetLoopLimit(D_807FBB40, 0, -1);
            }
        } else if (animIsPlaying(D_807FBB40, 0) != 0) {
            animSetFinished(D_807FBB40, 0, 1);
            animSetFrameAndSubframe(D_807FBB40, 0, 0, 0);
        }
        if (D_807FBD70 == 4) {
            if (D_807FBB40->unk132 == 4) {
                D_807FBB40->unk132 = 8;
                sfxAllocateChannel(0x43, 1.0f);
                actorAppendCallback(sp30, (s32)D_807FBB40, 0x02000000, (u8)sp36, 0, NULL);
            } else {
                D_807FBB40->unk132 *= 2;
            }
        }
        if ((D_807FBB4C->unk6A & 1) && D_807FBB4C->unk110 == 0) {
            D_807FBB40->unk132 = 1;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/A6280/func_806A18A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A6280/func_806A1AC4.s")

void actorFinishInRange(void) {
    D_807FBB40->unk60 |= 0x400;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 camIsCutsceneActive(void);
void func_80613C48(Actor *, s16, f32, f32);

void actorPlaySoundVariantAndFinish(void) {
    if (camIsCutsceneActive() != 0) {
        func_80613C48(D_807FBB40, 0x640, 0, 8.0f);
    } else {
        func_80613C48(D_807FBB40, 0x63F, 0, 8.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

static void stub_806A1FD0(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A6280/func_806A1FD8.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/A6280/func_806A2328.s")

void mathAngleBetweenPoints3D(s16 *, s16 *, f32, f32, f32, f32, f32, f32);

void actorPlaceModelAtCamera(void) {
    s16 spBE;
    s16 spBC;
    f32 mtx1[4][4];
    f32 mtx2[4][4];

    mathAngleBetweenPoints3D(&spBE, &spBC, D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218, D_807FC924->unk228, D_807FC924->unk22C, D_807FC924->unk230);
    D_807FBB40->unkE6 = spBC;
    D_807FBB40->unkE8 = spBE;
    guRotateF(mtx1, spBE / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
    guRotateF(mtx2, spBC / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    guTranslateF(mtx2, D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218);
    guMtxCatF(mtx1, mtx2, mtx1);
    guMtxXFMF(mtx1, 0.0f, 0.0f, -11.0f, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), 0.0f, -20.0f, 0.0f);
    actorUpdateModelMatrix(D_807FBB40, 1);
}
