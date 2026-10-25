#include "common.h"
#include "actor.h"

typedef struct B6C50Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u8 pad6A[0x12];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[8];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x2A];
    /* 0x11C */ struct B6C50Actor *unk11C;
    /* 0x120 */ u8 pad120[9];
    /* 0x129 */ u8 unk129;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0xC];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ u8 pad13C[8];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} B6C50Actor;

typedef struct B6C50View90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ B6C50Actor *unk4;
} B6C50View90;

extern B6C50Actor *D_807FBB40;
extern B6C50Actor *D_807FBB44;
extern ActorGlobalState D_807FBB70;
extern s32 D_8072030C;
extern u32 D_8076A064;

void actorClearNodeFlag(B6C50Actor *, s32);
void actorDespawn(B6C50Actor *);
void actorSetStateTwo(B6C50Actor *);
s32 actorSpawn(s32, s32);
s32 actorTableContains();
void effectSpawnBoneDefault(B6C50Actor *, s16, f32, f32, f32, f32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_80614EBC(B6C50Actor *, s32);
void func_8061CC40(B6C50Actor *, s32, s32);
s32 func_80629148(void);
void func_806319C4(B6C50Actor *, s32);
void func_80665564(B6C50Actor *, f32);
void func_8067B238(B6C50Actor *, B6C50Actor *, f32);
void func_8067DF44(f32, f32, f32, f32, u8, u8);
void func_806A2A10(s32, s32, u8);
void func_80714998(s32);
void func_807149A8(s16);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714C08(void *, f32, void *, s32, s32);
void effectFreeByResource(B6C50Actor *);
void func_80726EE0(s32);
void func_80729B00(void);
s32 sfxAllocateChannel(s32, f32);
void sfxPlayActorSound(B6C50Actor *, s16, u8, u8, u8, u8, f32, s8);
void sfxPlayFromActorWithAltitudeCheck(B6C50Actor *, s16, u8, s16, u8);
void sfxStopSlotSound(B6C50Actor *, u8);

void func_806B1F50(void) {
    u8 sp37;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0xA0;
        D_807FBB40->unk60 |= 0x400;
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155 = 0;
        actorSpawn(0x73, 0x7D);
        ((B6C50View90 *)D_807FDC90)->unk4 = D_807FBB44;
        func_8067B238(D_807FBB44, D_807FBB40, 0.3f);
        D_807FBB44->unk7C = func_80612794(D_807FBB40->unkE6) * 14.0f + D_807FBB40->unk7C;
        D_807FBB44->unk84 = func_80612790(D_807FBB40->unkE6) * 14.0f + D_807FBB40->unk84;
        actorClearNodeFlag(D_807FBB44, 3);
        actorClearNodeFlag(D_807FBB44, 1);
        func_80665564(D_807FBB44, 14.0f);
        D_807FBB40->unk68 &= 0xFFBF;
        D_807FBB44->unk60 |= 0x1000;
        func_807149B8(1);
        func_807149FC(-1);
        func_807149A8(D_807FBB44->unk12A * 0.75);
        func_80714C08(&D_8072030C, 0.28f, D_807FBB44, 1, 2);
        func_80614EBC(D_807FBB40, 0x300);
        sfxPlayActorSound(D_807FBB40, 0x135, 0x64, 0, 0, 0x78, 1.0f, 0);
    }
    if (D_807FBB70.unk15 != 0 || D_807FBB70.unk200 == 9) {
        D_807FBB40->unk11C->unk154 = 0;
        func_8061CC40(D_807FBB40, 6, 5);
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155 = 0;
    } else if (D_807FBB70.unk200 == 4) {
        D_807FBB40->unk155++;
    }
    switch (D_807FBB40->unk154) {
        case 0x27:
            break;
        case 0:
            if (func_80629148() != 0) {
                func_806A2A10(0xDC, 0x2A, 0x1E);
                actorSetStateTwo(D_807FBB40->unk11C);
                D_807FBB40->unk154 = 7;
                D_807FBB40->unk155 = 0;
            }
            break;
        case 0x37:
            switch (D_807FBB40->unk155) {
                case 0x3C:
                    D_807FBB40->unk60 &= ~4;
                    D_807FBB40->unk68 &= 0xFFBF;
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xED, 0xFF, 0x7F, 0x14);
                    func_8067DF44(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, D_807FBB40->unk4->unk38 * 2 / 0.15, 0, 1);
                    actorDespawn((B6C50Actor *)D_807FDC94);
                    D_807FBB40->unk155++;
                    break;
                case 0x64:
                    actorDespawn(D_807FBB40->unk11C);
                    D_807FBB40->unk154 = 0x40;
                    sfxAllocateChannel(0x2A, 1.0f);
                default:
                    D_807FBB40->unk155++;
                    break;
            }
            break;
        default:
            if (D_807FBB40->unk11C != NULL && D_807FBB40->unk11C->unk154 == 5) {
                D_807FBB40->unk138 &= ~0x8000;
                sfxStopSlotSound(D_807FBB40, 0);
                func_80726EE0(0);
                effectFreeByResource((B6C50Actor *)D_807FDC94);
                actorDespawn(D_807FBB40->unk11C);
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155 = 0;
                func_8061CC40(D_807FBB40, 3, 1);
                func_80614EBC(D_807FBB40, 0x307);
                D_807FBB40->unkE6 += 0x800;
                D_807FBB40->unk84 += 5.0f;
            }
            if (D_807FBB40->unk155 != 0 && actorTableContains(D_807FDC94) != 0 && D_8076A064 % 7 == 0) {
                sp37 = -D_807FBB40->unk155 * 0x1E + 0xB4;
                func_80714998(3);
                func_807149C8(sp37, sp37, sp37 & 0xFF, D_807FBB40->unk129);
                effectSpawnBoneDefault((B6C50Actor *)D_807FDC94, 1, 1.0f, 0.0f, 0.0f, 0.0f, -0x96);
            }
            break;
    }
    func_806319C4((B6C50Actor *)*(s32 *)&D_807FBB40, 0);
}

extern B6C50Actor *D_807FBB4C;
extern s32 D_80720340;

B6C50Actor *actorFindByType(s32);
void func_80613C48(B6C50Actor *, s16, f32, f32);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072B7CC(s32);
f32 sqrtf(f32);

void func_806B24B8(void) {
    B6C50Actor *found;
    f32 dx;
    f32 dz;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        found = actorFindByType(0x110);
        if (found != NULL) {
            ((B6C50View90 *)D_807FDC90)->unk4 = found;
        }
        D_807FDC9C->unk10 = 0x23;
        func_80613C48(D_807FBB40, 0x599, 0.0f, 0.0f);
        D_807FBB40->unk68 &= 0xFFBF;
        sfxPlayActorSound(D_807FBB40, 0x139, 0x78, 0, 1, 0x3C, 0.56f, 0);
        D_807FBB40->unk60 |= 0x400;
    }
    if (D_8076A064 % 10 == 0) {
        func_807149B8(1);
        func_80714C08(&D_80720340, D_807FBB40->unk4->unk38 * 6.66666667 * 0.9, D_807FBB40, 1, 2);
    }
    if (actorTableContains(D_807FDC94) == 0) {
        ((B6C50View90 *)D_807FDC90)->unk4 = D_807FBB4C;
        D_807FDC94 = (Actor *)((B6C50View90 *)D_807FDC90)->unk4;
    }
    if (D_807FBB70.unk15 != 0 || D_807FBB70.unk200 == 9) {
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk154 = 0x40;
        func_8067DF44(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, D_807FBB40->unk4->unk38 / 0.15, 0, 1);
    }
    if (D_807FBB40->unk154 == 0x23) {
        if (D_807FBB40->unkF0 == 0) {
            dx = D_807FBB40->unk7C - D_807FDC94->unk7C;
            dz = D_807FBB40->unk84 - D_807FDC94->unk84;
            if (sqrtf(dx * dx + dz * dz) < 30.0f) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x2CA, 0xFF, 0x7F, 0x14);
                D_807FBB40->unkF0 = 1;
            }
        }
        func_8072AB74(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
    } else {
        func_8072B7CC(0x1F8);
    }
    func_806319C4(D_807FBB40, 0);
}
