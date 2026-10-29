#include "common.h"

typedef struct Actor_3340 {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x154 - 0x88];
    u8 unk154;
    u8 unk155;
    char pad156[0x1A4 - 0x156];
    u8 unk1A4;
} Actor_3340;

extern Actor_3340 *D_807FBB40;
extern Actor_3340 *D_807FBB4C;
extern Actor_3340 *D_807FD580;
extern s32 D_8076A064;

void behaviourFrameBegin(void);
void sfxPlayActorSound(Actor_3340 *, s32, s32, s32, s32, s32, f32, s32);
s32 flagGet(s32, s32);
void actorScriptStart(Actor_3340 *, s32);
s32 flagCountRange(s32, s32, s32);
void flagSet(s32, s32, s32);
void camStartPath(Actor_3340 *, s32, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(Actor_3340 *);
void effectSpawnBurst(s32);
void func_80614E78(Actor_3340 *, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor_3340 *, s32, s32, s32, s32);
void sfxStopSlotSound(Actor_3340 *, s32);
void slotQueueUpdate(s32, s32, s32);
void slotQueueAddValue(s32, u8, s32);
void actorUpdateModelMatrix(Actor_3340 *, s32);

void animSetLoopLimit(void *, s32, s32);
void animSetSpeed(void *, s32, f32);
void animSetFrameAndSubframe(void *, s32, s16, f32);
void animSetFinished(void *, s32, s32);


void critterSetDigitFrames(s32 arg0) {
    s32 var_s0;
    f32 zero = 0.0f;
    s32 n = arg0;

    for (var_s0 = 2; var_s0 >= 0; var_s0--) {
        animSetLoopLimit(D_807FBB40, var_s0, 1);
        animSetSpeed(D_807FBB40, var_s0, zero);
        animSetFrameAndSubframe(D_807FBB40, var_s0, (n % 10) + 1, zero);
        animSetFinished(D_807FBB40, var_s0, 0);
        n /= 10;
    }
}


typedef struct J0b2Sub {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} J0b2Sub;

typedef struct J0b2Actor {
    char pad0[4];
    J0b2Sub *unk4;
    char pad8[0x60 - 0x8];
    s32 unk60;
    s32 unk64;
    char pad68[0x7C - 0x68];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x144 - 0xE8];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x15E - 0x156];
    u8 unk15E;
    char pad15F[0x174 - 0x15F];
    s16 *unk174;
} J0b2Actor;

#define J0B2_A ((J0b2Actor *)D_807FBB40)
#define J0B2_P ((J0b2Actor *)D_807FBB4C)

extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8074E77C;
extern u16 D_807446C0[];
extern s16 D_807446D0[];
extern s8 D_807446E0[];
extern s8 D_807446EE;
extern u16 D_807FC930[];
extern u16 D_807ECD48;
extern u16 D_80029F90[];
extern s8 D_80029F80;
extern s8 D_80029F84;
extern f32 D_8002A1B0;
extern u8 D_8071FE08[];
extern u8 D_80720A7C[];
extern void *gCamActor;

s32 func_805FF030(u8, s32);
s32 camIsCutsceneActive(void);
s32 camIsPathPaused(void);
void camStartShake(void *, s32, s32);
s32 func_806FB418(void);
void func_8070E8DC(s32);
void func_8070D8C0(void *, s32, s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
f32 func_806119FC(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
f32 sqrtf(f32);
void critterSetDigitFrames(s32);

void func_80027448(void) {
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s16 *sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    s8 sp47;
    s8 sp46;

    sp60 = J0B2_A->unk174;
    sp46 = 0;
    sp47 = 0;
    sp6C = func_805FF030(D_8076A0AB, 0);
    if (sp6C >= 8) {
        sp6C = 7;
    }
    if (D_8076A0A8 == 0x2A) {
        sp64 = D_807446C0[sp6C];
    } else {
        sp64 = D_807446D0[sp6C];
    }
    if (!(J0B2_A->unk60 & 0x10)) {
        J0B2_A->unk64 |= 0x20;
        if (D_8076A0A8 == 0x2A) {
            actorScriptStart(D_807FBB40, 0x39F);
            J0B2_A->unk155 = 4;
            if (D_807FC930[sp6C] < sp64) {
                slotQueueUpdate(0, 1, 0);
            }
        } else {
            slotQueueUpdate(9, 1, 0);
            if (flagGet((s16)(sp6C + 0x1CD), 0) != 0) {
                J0B2_A->unk155 = 4;
            }
            actorScriptStart(D_807FBB40, 0x39E);
            critterSetDigitFrames(sp64);
        }
        *sp60 = 0;
        D_8002A1B0 = 0.0f;
        D_80029F84 = 0;
        D_80029F80 = 0;
    } else if (D_80029F84 != 0) {
        s8 *pair = &D_807446E0[sp6C + sp6C];

        if (D_8074E77C == pair[1]) {
            if (func_806FB418() < sp64 && sp6C != 7) {
                sp64 = pair[0];
                sp47 = 1;
            }
            if (sp6C == 7) {
                if (D_80029F84 == 1) {
                    sp46 = 1;
                } else {
                    sp64 = D_807446EE;
                    sp47 = 1;
                }
            }
        }
    }
    J0B2_A->unk15E = 0x23;
    if (D_8076A0A8 != 0x2A) {
        sp5C = J0B2_P->unk7C - J0B2_A->unk7C;
        sp58 = (f32)(2.0 * (f64)(J0B2_P->unk80 - J0B2_A->unk80));
        sp54 = J0B2_P->unk84 - J0B2_A->unk84;
        sp50 = sqrtf(sp5C * sp5C + sp58 * sp58 + sp54 * sp54);
        if ((f64)sp50 < 300.0 && flagGet(0x17E, 0) == 0) {
            func_8070E8DC(1);
            func_8070D8C0(D_807FBB40, 0x1D, 0);
            camStartPath(D_807FBB40, 1, 1);
            flagSet(0x17E, 1, 0);
        } else if (sp46 != 0 && (f64)sp50 < 200.0 && camIsCutsceneActive() == 0 && J0B2_P->unk154 == 0x24 && J0B2_P->unk155 == 2 && (f64)sp54 > -35.0) {
            if ((f64)sp5C > -27.0 && (f64)sp5C < 27.0 && (J0B2_P->unkE6 < 0x200 || J0B2_P->unkE6 >= 0xE01)) {
                D_80029F84 = 2;
                func_80609140(0x145, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                camStartShake(gCamActor, 0xA, 0xA);
                J0B2_A->unk155 = 0xA;
                *sp60 = 0;
                actorScriptStart(D_807FBB40, 0x3A1);
            }
        }
        switch (J0B2_A->unk155) {
        case 10:
            *sp60 += 1;
            if (*sp60 == 0xA) {
                critterSetDigitFrames(sp64);
                func_80609140(0xE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
            }
            if (*sp60 >= 0x2E) {
                J0B2_A->unk155 = 0;
                if (func_806FB418() < sp64) {
                }
            }
            break;
        case 0:
            if (D_8076A0A8 == 0xAA && D_8074E77C != 4) {
                D_8002A1B0 = 0.0f;
            }
            if ((f64)sp50 < 70.0 && (f64)D_8002A1B0 >= 70.0) {
                s16 var;

                func_8070E8DC(1);
                camStartPath(D_807FBB40, 0x1B, 5);
                if (func_806FB418() < sp64) {
                    func_8070D8C0(D_807FBB40, 0x1D, 1);
                    actorScriptStart(D_807FBB40, 0x3A1);
                    J0B2_A->unk155 = 1;
                } else {
                    flagSet((s16)(sp6C + 0x1CD), 1, 0);
                    var = sp47 != 0 ? sp6C + 2 : 2;
                    func_8070D8C0(D_807FBB40, 0x1D, (u8)var);
                    actorScriptStart(D_807FBB40, 0x3A0);
                    J0B2_A->unk155 = 2;
                    *sp60 = 0;
                }
            }
            break;
        case 1:
            if ((f64)sp50 > 110.0) {
                J0B2_A->unk155 = 0;
            }
            break;
        case 2:
            if (camIsPathPaused() == 0 && *sp60 >= 0x14) {
                if (*sp60 == 0x32) {
                    actorScriptStart(D_807FBB40, 0x3A2);
                }
                if (*sp60 >= 0x3D) {
                    func_807149B8(0);
                    func_807149FC(1);
                    func_80714CC0(D_80720A7C, 0.5f, (f32)(((f64)func_806119FC() * 35.0 + (f64)J0B2_A->unk7C) - 15.0), (f32)((f64)func_806119FC() * 35.0 + (f64)J0B2_A->unk80), (f32)(((f64)func_806119FC() * 35.0 + (f64)J0B2_A->unk84) - 15.0));
                }
                if (*sp60 >= 0x51) {
                    J0B2_A->unk4->unk34 = (f32)((f64)J0B2_A->unk4->unk34 * 0.9);
                    J0B2_A->unk4->unk38 = J0B2_A->unk4->unk34;
                    J0B2_A->unk4->unk3C = J0B2_A->unk4->unk34;
                }
                *sp60 += 1;
            } else {
                if (*sp60 < 0x14) {
                    *sp60 += 1;
                }
            }
            break;
        case 3:
            J0B2_A->unk4->unk34 = 0.0f;
            J0B2_A->unk4->unk38 = 0.0f;
            J0B2_A->unk4->unk3C = 0.0f;
            sfxStopSlotSound(D_807FBB40, 0);
            J0B2_A->unk155 = 4;
            func_807149B8(0);
            func_807149FC(1);
            func_80714CC0(D_8071FE08, 0.5f, J0B2_A->unk7C, J0B2_A->unk80 + 7.0f, J0B2_A->unk84);
            break;
        case 4:
            J0B2_A->unk4->unk34 = 0.0f;
            J0B2_A->unk4->unk38 = 0.0f;
            J0B2_A->unk4->unk3C = 0.0f;
            break;
        }
        D_8002A1B0 = sp50;
        if (D_807ECD48 != 0) {
            if (D_80029F90[D_80029F80] & D_807ECD48) {
                D_80029F80 += 1;
                if (D_80029F80 == 4) {
                    D_80029F80 = 0;
                    func_80609140(0x1EE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                    D_80029F84 = 1;
                }
            } else {
                D_80029F80 = 0;
            }
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (J0B2_A->unk155 != 4) {
        J0B2_A->unk60 |= 4;
    } else {
        J0B2_A->unk60 &= ~4;
        J0B2_A->unk144 = 1;
    }
}


void func_80027DC0(void) {
    f32 dx;
    f32 dz;
    Actor_3340 *volatile sp34;
    s32 var_t5;
    s32 var_t6;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        sfxPlayActorSound(D_807FBB40, 0x10F, 0x46, 1, 0, 0x1E, 1.0f, 0);
        D_807FBB40->unk154 = 0;
        if (flagGet(0x179, 0) == 0) {
            D_807FBB40->unk154 = 1;
        } else if (flagGet(0x189, 0) != 0) {
            actorScriptStart(D_807FBB40, 0x2B5);
        } else if (flagCountRange(0x24D, 0x14, 0) == 0x14) {
            actorScriptStart(D_807FBB40, 0x2B5);
            D_807FBB40->unk154 = 3;
        }
    }
    dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
    dz = D_807FBB40->unk84 - D_807FBB4C->unk84;
    switch (D_807FBB40->unk154) {
    case 1:
        var_t5 = ((dx * dx + dz * dz) < 10000.0f) != 0;
        if (var_t5) {
            flagSet(0x179, 1, 0);
            camStartPath(D_807FBB4C, 0, 1);
            currentActorClearFlag();
            D_807FBB40->unk154 = 2;
        }
        break;
    case 2:
        sp34 = D_807FBB40;
        if (D_807FBB40->unk155 != 0) {
            D_807FBB40->unk155++;
            if (D_807FBB40->unk155 < 0x4B) {
                D_807FBB40 = D_807FBB4C;
                if (!(D_8076A064 & 3)) {
                    effectSpawnBurst(0);
                }
                D_807FBB40 = sp34;
            } else {
                D_807FBB40 = D_807FBB4C;
                D_807FBB4C->unk154 = 0x2D;
                D_807FBB4C->unk155 = 0;
                func_80614E78(D_807FBB4C, 0x42);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB4C, 0xF2, 0xFF, 0x7F, 0);
                D_807FBB40 = sp34;
                D_807FBB40->unk155 = 0;
                sfxStopSlotSound(D_807FBB4C, 1);
            }
        } else if (currentActorTestClearFlag(D_807FBB40) != 0) {
            D_807FBB40->unk155 = 1;
            sfxPlayActorSound(D_807FBB4C, 0x104, 0x3C, 1, 1, 0xFF, 1.0f, 0);
            slotQueueUpdate(6, 0, 0);
            slotQueueAddValue(6, D_807FD580->unk1A4, 0x3E7);
        }
        break;
    case 3:
        var_t6 = ((dx * dx + dz * dz) < 10000.0f) != 0;
        if (var_t6) {
            camStartPath(D_807FBB40, 1, 1);
            currentActorClearFlag();
            D_807FBB40->unk154 = 4;
        }
        break;
    case 4:
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}



#ifdef NON_MATCHING
typedef struct J1b2Data {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} J1b2Data;

typedef struct J1b2Sub {
    char pad0[4];
    f32 unk4;
} J1b2Sub;

typedef struct J1b2Actor {
    char pad0[4];
    J1b2Sub **unk4;
    char pad8[0x60 - 8];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x154 - 0xE8];
    u8 unk154;
    char pad155[0x15E - 0x155];
    u8 unk15E;
    char pad15F[0x160 - 0x15F];
    u32 unk160;
    char pad164[0x174 - 0x164];
    J1b2Data *unk174;
} J1b2Actor;

#define J1b2A ((J1b2Actor *)D_807FBB40)

extern u8 D_807FBD70;
f32 func_80612790(s16);
f32 func_80612794(s16);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_806CC10C(s16, s16);
void func_8065D254(Actor_3340 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_80665564(Actor_3340 *, f32);
u8 func_8072881C(u8, u32 *);

void func_80028120(void) {
    f32 dx;
    f32 dz;
    f32 k;
    f32 v;
    f32 t;
    f32 w;
    s32 near;
    s32 angleTmp;
    J1b2Data *d;
    J1b2Sub *sub;

    d = J1b2A->unk174;
    sub = *J1b2A->unk4;
    if (!(J1b2A->unk60 & 0x10)) {
        J1b2A->unk154 = 0x78;
        if (flagGet(0x189, 0) != 0) {
            if (flagGet(0x23, 1) == 0) {
                J1b2A->unk154 = 1;
            } else if (flagGet(0x18A, 0) == 0) {
                if (flagGet(0x24, 1) != 0) {
                    J1b2A->unk154 = 0xA;
                } else {
                    J1b2A->unk154 = 0x64;
                }
            }
            actorScriptStart(D_807FBB40, 0x43B);
        } else {
            J1b2A->unk154 = 0;
        }
        d->unk20 = J1b2A->unk7C;
        d->unk24 = J1b2A->unk80;
        d->unk28 = J1b2A->unk84;
        d->unk4 = 0.028571429f;
        d->unk0 = 2.0f;
        d->unk14 = d->unk20;
        d->unk1C = d->unk28;
    }
    dx = J1b2A->unk7C - ((J1b2Actor *)D_807FBB4C)->unk7C;
    dz = J1b2A->unk84 - ((J1b2Actor *)D_807FBB4C)->unk84;
    if (J1b2A->unk154 != 1) {
        J1b2A->unkE6 = J1b2A->unkE6 - (func_806CC10C(mathAngleBetweenPoints2D(((J1b2Actor *)D_807FBB4C)->unk7C, ((J1b2Actor *)D_807FBB4C)->unk84, J1b2A->unk7C, J1b2A->unk84), J1b2A->unkE6) >> 3);
    }
    J1b2A->unk15E = 0xF;
    switch (J1b2A->unk154) {
    case 0:
        if (flagGet(0x189, 0) != 0) {
            actorScriptStart(D_807FBB40, 0x43B);
            J1b2A->unk154 = 1;
        }
        break;
    case 0x64:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0 && (D_807ECD48 & 0x8000)) {
            camStartPath(D_807FBB40, 4, 1);
            currentActorClearFlag();
            J1b2A->unk154 = 0x65;
        }
        if (flagGet(0x24, 1) != 0) {
            J1b2A->unk154 = 0xA;
        }
        break;
    case 0x65:
        if (camIsCutsceneActive() == 0) {
            J1b2A->unk154 = 0x64;
        }
        break;
    case 1: {
        t = sub->unk4 / 19.0;
        if (t < d->unk0) {
            d->unk8 = J1b2A->unk7C;
            d->unkC = d->unk24;
            d->unk10 = J1b2A->unk84;
            angleTmp = (s32)(func_806119FC() * 4096.0);
            k = func_806119FC() * 65.0;
            d->unk14 = (func_80612790((s16)angleTmp) * k) + d->unk20;
            d->unk18 = d->unk24;
            d->unk1C = (func_80612794((s16)angleTmp) * k) + d->unk28;
            if (!k) {
            }
            if (!k) {
            }
        }
        d->unk0 = t;
        t = (t - 0.5) * 2.5;
        if (t > 1.0) {
            t = 1.0f;
        }
        if (t < 0.0) {
            t = 0.0f;
        }
        J1b2A->unk7C = d->unk8 + (t * (d->unk14 - d->unk8));
        J1b2A->unk84 = d->unk10 + (t * (d->unk1C - d->unk10));
        if (D_807FBD70 == 4) {
            actorScriptStart(D_807FBB40, 0x43C);
            J1b2A->unk154 = 2;
            d->unk0 = 0.0f;
        }
        break;
    }
    case 2:
        d->unk0 = d->unk0 + 1.0;
        if (d->unk0 > 49.0) {
            camStartPath(D_807FBB40, 2, 1);
            currentActorClearFlag();
            d->unk0 = 0.0f;
            J1b2A->unk154 = 0x64;
        } else if (d->unk0 < 20.0) {
            f64 dist;

            dist = sqrtf((dx * dx) + (dz * dz));
            if (dist > 1.0) {
                k = 3.0 / dist;
                if (!k) {
                }
                J1b2A->unk7C = J1b2A->unk7C + (dx * k);
                J1b2A->unk84 = J1b2A->unk84 + (dz * k);
            }
        }
        break;
    case 0xA:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0) {
            J1b2A->unk154 = 0xB;
            camStartPath(D_807FBB40, 3, 1);
        }
        break;
    case 0xB:
        break;
    }
    func_8072881C(0, &J1b2A->unk160);
    if (J1b2A->unk154 == 0) {
        J1b2A->unk60 = J1b2A->unk60 & ~4;
    } else {
        J1b2A->unk60 = J1b2A->unk60 | 4;
        func_80665564(D_807FBB40, 0);
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x23, 0xF, 1, 0x4B, 0x78, J1b2A->unkE6, 1.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/critter/nonmatchings/3340/func_80028120.s")
#endif
