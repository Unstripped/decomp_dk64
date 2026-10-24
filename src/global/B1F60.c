#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
void actorSpawn(s32, s32);
void func_806AD260();
void func_80729B00(void);
void func_80724CA4(s32, s32);
void func_8072B79C(s32, s32, s32);
void func_80724E48(u8);
void func_806319C4(Actor *, s32);

#ifdef NON_MATCHING
typedef struct {
    u8 pad0[0xC0];
    f32 unkC0;
} M2_ActorC0;

typedef struct {
    u8 pad0[0x28];
    s16 unk28;
    s16 unk2A;
} M2_View98;

extern ActorGlobalState D_807FBB70;
void func_8072D714(s32, s32, Actor *);
void func_8072AB74(s32, f32, f32, u16, f32);
void sfxSpawnTableNodes(Actor *);
void func_8072DC7C(s32);
void func_8072B7CC(s32);
void func_8072D13C(s32, s32);
void func_8072C918(s32, s32, s32);

void func_806AD260(arg0, arg1, arg2)
s16 arg0;
u8 arg1;
u16 arg2;
{
    Actor *actor;

    if (arg0 != 0 && (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0)) {
        actor = D_807FBB40;
        if (actor->unk154 != 0x37) {
            ((M2_ActorC0 *)actor)->unkC0 = 200.0f;
            func_8072D714(D_807FBB70.unk1FC, arg0, actor);
        }
    }
    switch (D_807FBB40->unk154) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, (D_807FBB40->unk6A & 1) ? arg2 : (arg2 | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072AB74(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, arg2, 0.0f);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_8072AB74(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    if (arg1 != 0) {
                        D_807FBB40->unk155[0] = 2;
                        break;
                    }
                    ((M2_ActorC0 *)D_807FBB40)->unkC0 = 100.0f;
                    D_807FBB40->unk155[0]++;
                case 2:
                    func_8072AB74(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
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
            func_8072B7CC(((M2_View98 *)D_807FDC98)->unk28);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x4C90, ((M2_View98 *)D_807FDC98)->unk28, ((M2_View98 *)D_807FDC98)->unk2A);
        case 0x37:
        case 0x40:
            break;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B1F60/func_806AD260.s")
#endif

typedef struct {
    u8 pad0[0x1A];
    u16 unk1A;
} M2_View90;

typedef struct {
    u8 pad0[0xD];
    u8 unkD;
} M2_View9C;

extern s32 D_8076A0A8;
Actor *actorFindByType(s32);

void func_806AD54C(void) {
    Actor *found;
    f32 dx;
    f32 dz;
    s32 dir;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        func_8072B79C(0x1F8, 0x1F8, 0x1F9);
        if (D_8076A0A8 == 0x68 || D_8076A0A8 == 0x88 || D_8076A0A8 == 0x89) {
            D_807FBB40->unk132 = 2;
        }
    }
    if (D_807FBB40->unk132 == 2 && D_807FBB40->unk154 != 0x36) {
        found = actorFindByType(0x11A);
        if (found != NULL) {
            if (found->unk154 != 0) {
                if (!(((M2_View90 *)D_807FDC90)->unk1A & 0x8000)) {
                    dx = found->unk7C - D_807FBB40->unk7C;
                    dz = found->unk84 - D_807FBB40->unk84;
                    if ((dx * dx) + (dz * dz) < 1600.0f) {
                        dir = (((found->unkE6 - D_807FBB40->unkE6) & 0xFFF) > 0x800) ? 1 : -1;
                        D_807FBB40->unkB8 = (f64)(u32)((M2_View9C *)D_807FDC9C)->unkD * 1.8;
                        D_807FBB40->unkE6 += dir * 0x190;
                        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = D_807FBB40->unkE6;
                        ((M2_View90 *)D_807FDC90)->unk1A |= 0x8000;
                        D_807FBB40->unk154 = 0x10;
                        D_807FBB40->unk155[0] = 0;
                    }
                }
            } else {
                ((M2_View90 *)D_807FDC90)->unk1A &= 0x7FFF;
            }
        }
    }
    func_806AD260(0x1FA, 0, 0);
    func_80724E48((D_807FBB40->unk154 == 0x23) ? 0 : 2);
    func_806319C4(D_807FBB40, 0);
}

void func_806AD7AC(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        func_8072B79C(0x1F8, 0x1F8, 0x1F9);
    }
    func_806AD260(0x1FA, 0, 0);
    func_80724E48((D_807FBB40->unk154 == 0x23) ? 0 : 2);
    func_806319C4(D_807FBB40, 0);
}

typedef struct {
    u8 pad0[0x6A];
    u16 unk6A;
    u8 pad6C[0xE8 - 0x6C];
    s16 unkE8;
} M2_Linked;

typedef struct {
    u8 pad0[0x2C8];
    s16 unk2C8;
} M2_Global924;

extern M2_Global924 *D_807FC924;
void actorDespawn(Actor *);
void actorGetNodePos(M2_Linked *, s32, f32 *, f32 *, f32 *);

void func_806AD84C(void) {
    M2_Linked *linked;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk4->unk34 = 0.05f;
        D_807FBB40->unk4->unk3C = 0.05f;
        D_807FBB40->unk4->unk38 = 2.0f;
        D_807FBB40->unk60 |= 0x400;
    }
    switch (D_807FBB40->unk154) {
        case 0:
            linked = (M2_Linked *)D_807FBB40->unk11C;
            if (linked == NULL || (linked->unk6A & 1)) {
                D_807FBB40->unk154 = 1;
                D_807FBB40->unk60 &= ~0x8000;
            } else {
                actorGetNodePos(linked, 2, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
                *(s16 *)((u8 *)D_807FBB40 + 0xE8) = ((M2_Linked *)D_807FBB40->unk11C)->unkE8;
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

void func_806AD9AC(void) {
    actorSpawn(0x118, 0xC0);
    D_807FBB44->unk11C = (s32)D_807FBB40;
    D_807FBB44->unk12A = 0x7D0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B1F60/func_806AD9F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B1F60/func_806ADDD8.s")
