#include "common.h"
#include "actor.h"

typedef struct B1F60Sub0 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
} B1F60Sub0;

typedef struct B1F60Sub4 {
    /* 0x00 */ B1F60Sub0 *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} B1F60Sub4;

// File-local view of Actor for the fields the shared Actor lacks or types differently.
typedef struct B1F60Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ B1F60Sub4 *unk4;
    /* 0x008 */ u8 pad8[0xB8];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x24];
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x65];
    /* 0x155 */ u8 unk155;
} B1F60Actor;

typedef struct B1F60View90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
} B1F60View90;

typedef struct B1F60View98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} B1F60View98;

typedef struct B1F60View9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} B1F60View9C;

typedef struct B1F60Global924 {
    /* 0x000 */ u8 pad0[0x2C8];
    /* 0x2C8 */ s16 unk2C8;
} B1F60Global924;

#define B1F60A ((B1F60Actor *)D_807FBB40)

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern ActorGlobalState D_807FBB70;
extern s32 D_8076A0A8;
extern B1F60Global924 *D_807FC924;

void actorSpawn(s32, s32);
Actor *actorFindByType(s32);
void actorDespawn(Actor *);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void sfxSpawnTableNodes(Actor *);
s32 func_80611A44(void);
void func_80614EBC(Actor *, s32);
void func_806319C4(Actor *, s32);
void func_80724CA4(s32, s32);
void func_80724E48(u8);
void behaviourFrameBegin(void);
void func_8072881C(s32, void *);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void actorSetTargetSpeed(Actor *, s32);
void behaviourSetAnimIds(s32, s32, s32);
void func_8072B7CC(s32);
void func_8072C918(s32, s32, s32);
void func_8072D13C(s32, s32);
void func_8072D714();
void func_8072DC7C(s32);
void actorSetDefaultState(s32);
void func_8072DEA8(s32, s32, s32);
s32 actorIsTargetWithinDistance(s32);
void func_806AD260();

#ifdef NON_MATCHING
void func_806AD260(arg0, arg1, arg2)
s16 arg0;
u8 arg1;
u16 arg2;
{
    Actor *actor;

    if (arg0 != 0 && (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0)) {
        actor = D_807FBB40;
        if (actor->unk154 != 0x37) {
            ((B1F60Actor *)actor)->unkC0 = 200.0f;
            func_8072D714(D_807FBB70.unk1FC, arg0, actor);
        }
    }
    actor = D_807FBB40;
    switch (actor->unk154) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            actorMoveWithinZone(actor->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, (actor->unk6A & 1) ? arg2 : (arg2 | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(actor->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, arg2, 0.0f);
            break;
        case 0x37:
            switch (((B1F60Actor *)actor)->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(actor);
                    if (arg1 != 0) {
                        B1F60A->unk155 = 2;
                        break;
                    }
                    B1F60A->unkC0 = 100.0f;
                    B1F60A->unk155++;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(((B1F60View98 *)D_807FDC98)->unk28);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x4C90, ((B1F60View98 *)D_807FDC98)->unk28, ((B1F60View98 *)D_807FDC98)->unk2A);
        case 0x37:
        case 0x40:
            break;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B1F60/func_806AD260.s")
#endif

void func_806AD54C(void) {
    Actor *found;
    f32 dx;
    f32 dz;
    s32 dir;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        behaviourSetAnimIds(0x1F8, 0x1F8, 0x1F9);
        if (D_8076A0A8 == 0x68 || D_8076A0A8 == 0x88 || D_8076A0A8 == 0x89) {
            D_807FBB40->unk132 = 2;
        }
    }
    if (D_807FBB40->unk132 == 2 && D_807FBB40->unk154 != 0x36) {
        found = actorFindByType(0x11A);
        if (found != NULL) {
            if (found->unk154 != 0) {
                if (!(((B1F60View90 *)D_807FDC90)->unk1A & 0x8000)) {
                    dx = found->unk7C - D_807FBB40->unk7C;
                    dz = found->unk84 - D_807FBB40->unk84;
                    if ((dx * dx) + (dz * dz) < 1600.0f) {
                        dir = (((found->unkE6 - D_807FBB40->unkE6) & 0xFFF) > 0x800) ? 1 : -1;
                        D_807FBB40->unkB8 = (f64)(u32)((B1F60View9C *)D_807FDC9C)->unkD * 1.8;
                        D_807FBB40->unkE6 += dir * 0x190;
                        B1F60A->unkEE = D_807FBB40->unkE6;
                        ((B1F60View90 *)D_807FDC90)->unk1A |= 0x8000;
                        D_807FBB40->unk154 = 0x10;
                        B1F60A->unk155 = 0;
                    }
                }
            } else {
                ((B1F60View90 *)D_807FDC90)->unk1A &= 0x7FFF;
            }
        }
    }
    func_806AD260(0x1FA, 0, 0);
    func_80724E48((D_807FBB40->unk154 == 0x23) ? 0 : 2);
    func_806319C4(D_807FBB40, 0);
}

void func_806AD7AC(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        behaviourSetAnimIds(0x1F8, 0x1F8, 0x1F9);
    }
    func_806AD260(0x1FA, 0, 0);
    func_80724E48((D_807FBB40->unk154 == 0x23) ? 0 : 2);
    func_806319C4(D_807FBB40, 0);
}

void actorFollowLinkedNodeFadeUpdate(void) {
    Actor *linked;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk4->unk34 = 0.05f;
        D_807FBB40->unk4->unk3C = 0.05f;
        D_807FBB40->unk4->unk38 = 2.0f;
        D_807FBB40->unk60 |= 0x400;
    }
    switch (D_807FBB40->unk154) {
        case 0:
            linked = (Actor *)D_807FBB40->unk11C;
            if (linked == NULL || (linked->unk6A & 1)) {
                D_807FBB40->unk154 = 1;
                D_807FBB40->unk60 &= ~0x8000;
            } else {
                actorGetNodePos(linked, 2, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
                B1F60A->unkE8 = ((B1F60Actor *)D_807FBB40->unk11C)->unkE8;
            }
            break;
        case 1:
            if (D_807FBB40->unk128 >= 0xB) {
                D_807FBB40->unk128 -= 0xA;
            } else {
                actorDespawn(D_807FBB40);
            }
            break;
    }
    D_807FBB40->unkE6 = D_807FC924->unk2C8 & 0xFFF;
    func_806319C4(D_807FBB40, 0);
}

void actorSpawnLinkedFollower(void) {
    actorSpawn(0x118, 0xC0);
    D_807FBB44->unk11C = (s32)D_807FBB40;
    D_807FBB44->unk12A = 0x7D0;
}

void func_806AD9F4(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x200;
        behaviourSetAnimIds(0x2F4, 0x2F4, 0x2F4);
        if (D_807FBB40->unk80 != D_807FBB40->unkA4) {
            D_807FBB40->unk154 = 0x1E;
            func_80614EBC(D_807FBB40, 0x2F8);
            actorSpawnLinkedFollower();
        }
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        func_8072D714(D_807FBB70.unk1FC, 0x2F7);
        actorSetTargetSpeed(D_807FBB40, 0);
        D_807FBB40->unkB8 = -200.0f;
    } else if (D_807FBB70.unk200 == 4) {
        D_807FBB40->unk132 = 2;
        func_8072DEA8(0x2F6, 0x27, D_807FBB70.unk1FC);
        D_807FBB40->unkB8 = D_807FBB40->unkB8 * 2;
        D_807FDC90->unk2C = 0x1F4;
    }
    switch (D_807FBB40->unk154) {
        case 0x1E:
            actorMoveWithinZone(0, D_807FDC94->unk7C, D_807FDC94->unk84, 0x4202, 0.0f);
            if (B1F60A->unk155 != 0) {
                actorSetDefaultState(0x2F4);
            }
            break;
        case 0x27:
            actorMoveWithinZone(0, D_807FDC94->unk7C, D_807FDC94->unk84, 0x4300, 0.0f);
            D_807FBB40->unkE6 += D_807FDC90->unk2C;
            if (D_807FDC90->unk2C >= 0x15) {
                D_807FDC90->unk2C -= 0x14;
            } else {
                D_807FDC90->unk2C = 0;
                B1F60A->unkEE = D_807FBB40->unkE6;
            }
            if (B1F60A->unk155 != 0 && D_807FDC90->unk2C == 0) {
                D_807FBB40->unk132 = 1;
                actorSetDefaultState(0x2F4);
            }
            break;
        case 0x28:
            switch (B1F60A->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, 0);
                    func_80614EBC(D_807FBB40, 0x2F5);
                    B1F60A->unk155++;
                case 1:
                    actorMoveWithinZone(0, D_807FDC94->unk7C, D_807FDC94->unk84, 0x4200, 0.0f);
                    if (D_807FBB40->unkB8 < 1.0f) {
                        B1F60A->unk155++;
                    }
                    break;
                case 3:
                    actorSetDefaultState(0x2F4);
                    break;
            }
            break;
        case 1:
            if ((func_80611A44() >> 15) % 1000 >= 0x3E4) {
                if (D_807FBB40->unk6A & 1) {
                    D_807FBB40->unk154 = 0x28;
                    B1F60A->unk155 = 0;
                }
            }
        default:
            func_806AD260(0, 1, 0);
            break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    func_806319C4(D_807FBB40, 0);
}

void func_806ADDD8(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x40;
        ((B1F60View98 *)D_807FDC98)->unk28 = 0x31A;
    }
    switch (D_807FBB40->unk154) {
        case 0:
        case 1:
            if (actorIsTargetWithinDistance(0x12C) != 0) {
                func_80614EBC(D_807FBB40, 0x31A);
                D_807FBB40->unk154 = 0x23;
                B1F60A->unk155 = 0;
            }
            break;
        case 4:
            if (B1F60A->unk4->unk64 != 0x319) {
                D_807FBB40->unk154 = 0x23;
                B1F60A->unk155 = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0) {
                func_80614EBC(D_807FBB40, 0x31B);
                D_807FBB40->unk154 = 0x1E;
                B1F60A->unk155 = 0;
            }
            break;
        case 0x1E:
            if (B1F60A->unk4->unk64 == 0x31A) {
                D_807FBB40->unk154 = 0x23;
                B1F60A->unk155 = 0;
            }
            break;
        case 0x23:
            if (B1F60A->unk4->unk64 == 0x31A && B1F60A->unk4->unk0->unk4 > 4.0f) {
                actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            }
            if (actorIsTargetWithinDistance(0x12C) == 0) {
                func_80614EBC(D_807FBB40, 0x31C);
                D_807FBB40->unk154 = 0;
                B1F60A->unk155 = 0;
            }
            break;
        default:
            func_8072B7CC(0x31A);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}
