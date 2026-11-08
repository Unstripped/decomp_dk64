#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct BD820Actor {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x66];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[4];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
} BD820Actor;

typedef struct BD820View9C {
    /* 0x00 */ u8 pad0[0xF];
    /* 0x0F */ u8 unkF;
} BD820View9C;

#define BD820A ((BD820Actor *)D_807FBB40)
#define BD820S9C ((BD820View9C *)D_807FDC9C)

extern void *D_8074E880[];
extern u8 D_8071FFA0[];
extern void effectWispWanderUpdate(void);
extern void func_80717D4C(void);

s32 randomNonNegative(void);
void behaviourFrameBegin(void);
void actorUpdateModelMatrix(Actor *, s32);
void func_8071496C(s16);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714950(s32);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80613C48(Actor *, s32, f32, f32);
u8 func_805FF0C8(void);
void modelSlotOrFlags(s32, s32);
void func_806B8C78(void);

void effectSpawnRandomParticleAtPoint(s16 x, s16 y, s16 z, s16 lifetime) {
    func_8071498C(effectWispWanderUpdate);
    func_807149FC(-1);
    func_807149B8(1);
    func_8071496C(lifetime);
    func_80714CC0(D_8074E880[(randomNonNegative() >> 15) % 1000 % 3], 1.8f, x, y, z);
}

void func_806B8BDC(s16 x, s16 y, s16 z) {
    func_80714998(2);
    func_8071498C(func_80717D4C);
    func_80714950(-0x28);
    func_807149B8(1);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    func_80714CC0(D_8071FFA0, 2.0f, x, y, z);
}

extern s16 gCsModelIds[];

void actorScriptStart(Actor *, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void sfxAllocateChannel(s32, f32);
void actorSetTargetSlotByte(s32, u8);
void lightSetColor(f32, f32, f32, s16);
void modelSlotClearFlags(s32, s32);

void func_806B8C78(void) {
    f64 t;

    switch (D_807FBB40->unk154) {
        case 1:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    BD820A->unkC0 = 0.0f;
                    actorScriptStart(D_807FBB40, 0x290);
                    D_807FBB40->unk155[0]++;
                    break;
                case 2:
                    if (D_807FBB40->unk80 > -20.0f) {
                        D_807FBB40->unk80 = D_807FBB40->unk80 - BD820A->unkC0;
                    }
                    t = BD820A->unkC0 + 0.5;
                    BD820A->unkC0 = (t < 8.0) ? t : 8.0;
                    break;
            }
            break;
        case 2:
            effectSpawnRandomParticleAtPoint(0x258, 0x64, 0x1E5, 0x64);
            effectSpawnRandomParticleAtPoint(0x258, 0x96, 0x1E5, 0x64);
            effectSpawnRandomParticleAtPoint(0x258, 0xC8, 0x1E5, 0x67);
            effectSpawnRandomParticleAtPoint(0x258, 0xFA, 0x1E5, 0x68);
            effectSpawnRandomParticleAtPoint(0x258, 0x12C, 0x1E5, 0x6C);
            effectSpawnRandomParticleAtPoint(0x258, 0x15E, 0x1E5, 0x6E);
            effectSpawnRandomParticleAtPoint(0x258, 0x190, 0x1E5, 0x73);
            effectSpawnRandomParticleAtPoint(0x258, 0x1C2, 0x1E5, 0x74);
            D_807FBB40->unk154++;
            D_807FDC90->unk2C = 0x46;
            break;
        case 3:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk154 = 0x40;
            }
            if (D_807FDC90->unk2C < 0x28) {
                modelSlotOrFlags(4, 0x10);
                modelSlotOrFlags(6, 0x10);
                modelSlotClearFlags(5, 0x10);
                modelSlotClearFlags(7, 0x10);
                if ((D_807FDC90->unk2C < 0x15 && (randomNonNegative() >> 15) % 1000 < 0x12C) || D_807FBB40->unk154 == 0x40) {
                    if (D_807FBB40->unk154 == 0x40) {
                        modelSlotOrFlags(5, 0x10);
                        modelSlotOrFlags(7, 0x10);
                        sfxPlayOnFreeSlot(0x1D0, 0x58EF, 63.0f, 1.0f, 0, 0);
                        sfxAllocateChannel(0x3A, 1.0f);
                        func_806B8BDC(0xBD, 0xAA, 0x2FB);
                        func_806B8BDC(0x19A, 0xA6, 0x2F8);
                    }
                    actorSetTargetSlotByte(gCsModelIds[4], 0);
                    actorSetTargetSlotByte(gCsModelIds[6], 0);
                    lightSetColor(0.15f, 0.15f, 0.15f, 0);
                } else if (D_807FDC90->unk2C >= 0x15) {
                    actorSetTargetSlotByte(gCsModelIds[4], 9);
                    actorSetTargetSlotByte(gCsModelIds[6], 9);
                    lightSetColor(0.2f, 0.2f, 0.2f, 0);
                } else {
                    actorSetTargetSlotByte(gCsModelIds[4], 8);
                    actorSetTargetSlotByte(gCsModelIds[6], 8);
                    lightSetColor(0.3f, 0.3f, 0.3f, 0);
                }
            }
            break;
    }
}

void func_806B904C(void) {
    s16 i;
    f32 v;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        v = ((f64)BD820S9C->unkF / 255.0) * 0.75;
        D_807FBB40->unk4->unk34 = v;
        D_807FBB40->unk4->unk38 = v;
        D_807FBB40->unk4->unk3C = v;
        if (func_805FF0C8() != 0) {
            D_807FBB40->unk154 = 0x40;
        } else {
            BD820A->unk12A = 0x3E8;
            BD820A->unk130 = 0x3C;
            BD820A->unk131 = 0x3C;
            func_80613C48(D_807FBB40, 0x482, 0.0f, 0.0f);
        }
        modelSlotOrFlags(5, 0x10);
        modelSlotOrFlags(7, 0x10);
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 3) {
            D_807FBB40->unk154 = D_807FBB70.unk278[i][1];
            D_807FBB40->unk155[0] = 0;
        }
    }
    func_806B8C78();
    actorUpdateModelMatrix(D_807FBB40, 0);
}
