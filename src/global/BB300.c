#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct BB300Quad {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
} BB300Quad;

typedef struct BB300Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ BB300Quad *unk1C;
} BB300Sub4;

typedef struct BB300Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ BB300Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x9C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[8];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 *unk178;
} BB300Actor;

#define BB300A44 ((BB300Actor *)D_807FBB44)
#define BB300A ((BB300Actor *)D_807FBB40)

extern Actor *D_807FBB44;
extern s16 D_807502E0;
extern f32 D_807502E8;

s32 actorSpawn(s32, s32);
void func_80614EBC(void *, s32);
void func_8067B238(void *, void *, f32);
void actorSetTargetSpeed(void *, s32);
void *memcpy(void *, const void *, unsigned int);
void behaviourFrameBegin(void);
void func_80724C2C(s32);
void func_806B6DB0();
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);

void actorUpdatePulseIntensity(u8 arg0) {
    u8 *p = BB300A->unk178;
    s32 pad1;
    BB300Quad *q = BB300A->unk4->unk1C;
    s32 pad2;
    f32 f;
    f32 x;
    u32 a;

    if (!arg0) {
        p[0] = -p[0] * 0.2 + (u32)p[0];
        p[1] = 0;
    } else {
        switch (p[1]) {
            case 0:
                p[1] = 1;
                break;
            case 1:
                p[0] += 0x32;
                if (p[0] >= 0xCE) {
                    p[0] = 0xFF;
                    p[1] = 2;
                }
                break;
            case 2:
                p[0] -= 0x50;
                a = p[0];
                if (p[0] >= 0x64 && (s32)a < 0xB4) {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16C, 0xFF, 0xA0, 6);
                    a = p[0];
                }
                if ((s32)a < 0x50) {
                    p[0] = 0;
                    p[1] = 0;
                }
                break;
        }
    }
    x = (u32)p[0] / 255.0;
    f = 8000.0f * x;
    q->unk2 = (u32)-f;
    q[1].unk1 = 3;
    q++;
    q->unk0 = 0x7F;
    q->unk2 = (u32)f;
    q->unk4 = 0;
    q->unk6 = 0;
}

typedef struct BB300View90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20[0xC];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[7];
    /* 0x35 */ u8 unk35;
} BB300View90;

#define BB300S90 ((BB300View90 *)D_807FDC90)

void effectSpawnRing();
void actorDespawn(Actor *);
void func_806319C4(void *, s32);
s32 actorMoveWithinZone(s32, f32, f32, s32, f32);
void func_8072B7CC();

void func_806B6958(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        BB300S90->unk35 = BB300S90->unk35 * 2;
        BB300S90->unk2C = 0xD2;
        BB300S90->unk1F = (u32)BB300S90->unk1F * 1.5;
        BB300S90->unk1E = (u32)BB300S90->unk1E * 1.5;
    }
    if (BB300S90->unk2C != 0) {
        BB300S90->unk2C = BB300S90->unk2C - 1;
    }
    if (BB300S90->unk2C % 30 == 0) {
        BB300S90->unk1F = BB300S90->unk1F - 1;
        BB300S90->unk1E = BB300S90->unk1E - 1;
    }
    if (D_807FBB70.unk200 == 4) {
        func_80724C2C(-0x96);
    }
    if (BB300S90->unk2C == 0 || D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3B2, 0xFF, 0x7F, 0x1E);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3B7, 0xFF, 0x7F, 0x1E);
        effectSpawnRing();
        actorDespawn(D_807FBB40);
    }
    if (D_807FBB40->unk154 == 0x23) {
        actorMoveWithinZone(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
    } else {
        func_8072B7CC(0x237);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806B6C88(s16 arg0, s16 arg1) {
    if (actorSpawn(0xD3, 0x24) != 0) {
        BB300A44->unk154 = 0x23;
        func_80614EBC(D_807FBB44, 0x237);
        BB300A44->unkE6 = arg1;
        BB300A44->unkEE = BB300A44->unkE6;
        func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
        BB300A44->unkA4 = BB300A->unkA4;
        BB300A44->unkC4 = D_807502E8;
        BB300A44->unkC8 = D_807502E0;
        BB300A44->unkB8 = 0.0f;
        actorSetTargetSpeed(D_807FBB40, arg0 * 1.25);
        memcpy(BB300A44->unk174, BB300A->unk174, 0x3C);
    }
}

typedef struct BB300Sub178 {
    /* 0x0 */ s16 pad0;
    /* 0x2 */ s16 unk2;
} BB300Sub178;

// Second view of the current actor (D_807FBB40): same object as BB300Actor, but unk178 is typed as BB300Sub178.
typedef struct BB300ActorAlt {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ BB300Sub178 *unk178;
} BB300ActorAlt;

typedef struct BB300View98 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
} BB300View98;

typedef struct BB300View9C {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[5];
    /* 0x13 */ u8 unk13;
} BB300View9C;

extern s32 D_8076A064;
extern s32 D_8076A0A8;

s32 func_80611A44(void);
void actorUpdatePulseIntensity(u8);
void func_80724CA4(s32, s32);
void func_80724E48();
void func_8072881C(s32, void *);
void actorSetBehaviourState();
void func_8072C918(s32, s32, s32);
void func_8072D13C(s32, s32);
void func_8072D714(s32, s32);
void func_8072DAA4();
void func_8072DC7C(s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void sfxSpawnTableNodes(Actor *);
void sfxStopSlotSound(Actor *, s32);

void func_806B6DB0(s32 arg0) {
    BB300Sub178 *p;
    s16 diff;
    u8 near;
    s32 tgt;
    s32 sel;

    p = ((BB300ActorAlt *)D_807FBB40)->unk178;
    if (((BB300ActorAlt *)D_807FBB40)->unkEE < D_807FBB40->unkE6) {
        diff = D_807FBB40->unkE6 - ((BB300ActorAlt *)D_807FBB40)->unkEE;
    } else {
        diff = ((BB300ActorAlt *)D_807FBB40)->unkEE - D_807FBB40->unkE6;
    }
    near = ((D_807FBB40->unk7C - D_807FDC94->unk7C) * (D_807FBB40->unk7C - D_807FDC94->unk7C) + (D_807FBB40->unk84 - D_807FDC94->unk84) * (D_807FBB40->unk84 - D_807FDC94->unk84)) < 2500.0f;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((BB300View98 *)D_807FDC98)->unk34 = 1.0f;
        func_80724CA4(2, 2);
        D_807FBB40->unkB8 = ((BB300View9C *)D_807FDC9C)->unkC;
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        tgt = D_807FBB70.unk1FC;
        ((BB300ActorAlt *)D_807FBB40)->unkC0 = 200.0f;
        func_8072D714(tgt, 0x236);
        if ((tgt != 0 && ((Actor *)tgt)->unk58 == 0x29) || (D_8076A0A8 == 0x10 && ((BB300View9C *)D_807FDC9C)->unk13 < 0x11)) {
            BB300S90->unk1A |= 1;
        }
    }
    sel = D_807FBB40->unk154;
    if (sel == 0x23 && D_807FBB40->unkB8 > 90.0f && diff >= 0x1F5 && diff < 0xE0C) {
        diff = ((BB300ActorAlt *)D_807FBB40)->unkEE - D_807FBB40->unkE6;
        if (diff < 0 || diff >= 0x801) {
            p->unk2 = 0x8C;
        } else {
            p->unk2 = -0x8C;
        }
        actorSetBehaviourState(0x14, 0xA, 0x235);
        sel = D_807FBB40->unk154;
    }
    switch (sel) {
    case 0x14:
        switch (((BB300ActorAlt *)D_807FBB40)->unk155) {
        case 0:
            BB300S90->unk2C = 0x1E;
            ((BB300ActorAlt *)D_807FBB40)->unk155 += 1;
            break;
        case 1:
            if (BB300S90->unk2C != 0) {
                D_807FBB40->unkE6 += p->unk2;
                p->unk2 += -p->unk2 * 0.01;
                BB300S90->unk2C -= 1;
                if (!(D_8076A064 & 3)) {
                    func_8072DAA4();
                }
            } else {
                ((BB300ActorAlt *)D_807FBB40)->unk155 = 2;
            }
            break;
        case 2:
            sfxStopSlotSound(D_807FBB40, 0);
            actorSetBehaviourState(1, ((BB300View9C *)D_807FDC9C)->unkC, 0x232);
            ((BB300ActorAlt *)D_807FBB40)->unkEE = D_807FBB40->unkE6;
            break;
        }
        func_80724E48(5);
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x300, 0.0f);
        break;
    case 1:
        if ((func_80611A44() >> 15) % 1000 >= 0x3E3) {
            D_807FBB40->unk154 = 0x11;
            ((BB300ActorAlt *)D_807FBB40)->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
        func_80724E48((u8)(D_807FBB40->unk154 == 1 ? 2 : 0));
        actorUpdatePulseIntensity(near);
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x400, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
        func_80724E48((u8)(D_807FBB40->unk154 == 0x35 ? 2 : 3));
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(D_807FBB40->unk154, BB300S90->unkA, BB300S90->unkE, 0x400, 0.0f);
        break;
    case 0x11:
        func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
        actorUpdatePulseIntensity(0);
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 2, 0.0f);
        switch (((BB300ActorAlt *)D_807FBB40)->unk155) {
        case 1:
            break;
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            func_80614EBC(D_807FBB40, 0x234);
            ((BB300ActorAlt *)D_807FBB40)->unk155 += 1;
            break;
        case 2:
            actorSetBehaviourState(1, ((BB300View9C *)D_807FDC9C)->unkC, 0x232);
            break;
        }
        break;
    case 0x37:
        switch (((BB300ActorAlt *)D_807FBB40)->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            ((BB300ActorAlt *)D_807FBB40)->unkC0 = 100.0f;
            ((BB300ActorAlt *)D_807FBB40)->unk155 += 1;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x20, 0.0f);
            break;
        case 3:
            if (BB300S90->unk1A & 1) {
                ((BB300ActorAlt *)D_807FBB40)->unk155 += 1;
            } else {
                func_806B6C88(((BB300View9C *)D_807FDC9C)->unkD, mathAngleBetweenPoints2D(D_807FDC94->unk7C, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk84));
                ((BB300ActorAlt *)D_807FBB40)->unk155 = 5;
            }
            break;
        case 4:
            func_8072DC7C(5);
            break;
        case 5:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x16:
        BB300S90->unk1A |= 1;
    default:
        func_8072B7CC(0x232, sel);
        break;
    }
    sel = D_807FBB40->unk154;
    switch (sel) {
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
    default:
        func_8072C918(arg0, 0x232, 0x233);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806B75F4(void) {
    behaviourFrameBegin();
    func_806B6DB0(0x2710);
}

void func_806B761C(void) {
    behaviourFrameBegin();
    if (D_807FBD70 == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}

void func_806B7660(void) {
    behaviourFrameBegin();
    if (D_807FBD70 == 4) {
        func_80724C2C(-0x64);
    }
    func_806B6DB0(0x2710);
}
