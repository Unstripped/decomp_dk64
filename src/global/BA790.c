#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

// View of the current actor (D_807FBB40) with the fields func_806B5A90 and func_806B640C need typed.
typedef struct BA790Actor {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0xA];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0xC];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x48];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ u8 pad13C[0x18];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ s16 *unk178;
} BA790Actor;

typedef struct BA790View9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[1];
    /* 0x0D */ u8 unkD;
} BA790View9C;

#define BA790A ((BA790Actor *)D_807FBB40)
#define BA790S9C ((BA790View9C *)D_807FDC9C)

extern u8 D_807FBB85;
extern u8 D_807444EC;
extern s32 D_8076A064;
extern s16 D_80770628[];
extern s16 D_80770710[];
extern s32 gCamActor;
extern BA790Actor *D_807FBD6C;
extern u8 D_80720630;

void func_8072D99C();
void sfxSpawnTableNodes(void *);
void tagBarrelDespawnEffects(void);
void func_80685210(f32, s16, s16);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
u32 actorMoveWithinZone(u32, f32, f32, u16, f32);
void func_8072C918(s32, s32, s32);
void actorUpdateFloorContactAndTilt(Actor *, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void actorScriptStart(void *, s32);
void func_8067E278(s32, s32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8072B7CC(s32);
void actorSetNodeFlag(Actor *, s32);
void actorClearNodeFlag(Actor *, s32);
void camStartShakeFromPoint(s32, s32, s32, f32, f32, f32, f32, f32);
void func_807149FC(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714998(s32);
void func_80714A08(f32, f32);
void func_8071498C(void (*)(void));
void effectSparkSpawnUpdate(void);
void func_80714CC0(void *, f32, f32, f32, f32);
void actorUpdateModelMatrix(Actor *, s32);

s32 func_806B5A90(s32 arg0, s32 arg1) {
    u8 ret;
    s16 diff;
    s32 sel;
    f32 fv;
    s32 x;
    u32 t;
    s16 q;
    s32 r;

    ret = 0;
    if (BA790A->unkEE < BA790A->unkE6) {
        diff = BA790A->unkE6 - BA790A->unkEE;
    } else {
        diff = BA790A->unkEE - BA790A->unkE6;
    }
    if (D_807FBD70 == 9 || D_807FBB85 != 0) {
        if (D_807FBB40->unk154 != 0x37 && D_807FBB40->unk154 != 0x38) {
            switch (D_807FBB40->unk58) {
            case 0xAF:
                if (D_807444EC == 1) {
                    if (D_807FBB40->unk60 & 4) {
                        D_807FBB40->unk154 = 0x38;
                        BA790A->unk155 = 0;
                    } else {
                        func_8072D99C();
                    }
                } else {
                    D_807FBB40->unk154 = 0x37;
                    BA790A->unk155 = 0;
                }
                break;
            case 0xB6:
                sfxSpawnTableNodes(D_807FBB40);
                tagBarrelDespawnEffects();
                func_8072D99C();
                break;
            }
        }
    }
    if (diff >= 0x1F5 && diff < 0xE0C) {
        func_80685210(0.5f, 0x32, (D_8076A064 & 1) + 2);
        BA790A->unkB8 = BA790A->unkB8 / 2;
        if (BA790A->unk6E == -1) {
            sfxPlayActorSound(D_807FBB40, 0x122, 0, 0, 0, 0xFF, 1.0f, 0);
        }
    } else {
        if (BA790A->unk6E != -1 && D_80770710[D_80770628[BA790A->unk6E]] == 0x122) {
            sfxStopSlotSound(D_807FBB40, 0);
        }
    }
    switch (D_807FBB40->unk154) {
    case 0x33:
        if (D_807FBD70 == 2) {
            BA790A->unkC0 = 150.0f;
            BA790A->unkEE = D_807FBD6C->unkEE;
        }
        if (BA790A->unk155) {
            x = 0;
        } else {
            x = 2;
        }
        actorMoveWithinZone(0x33, D_807FDC94->unk7C, D_807FDC94->unk84, x, 6.0f);
        if (D_807FBB40->unk58 == 0xB6) {
            func_8072C918(arg0, 0x24E, 0x24D);
        }
        break;
    case 0:
    case 4:
        sfxStopSlotSound(D_807FBB40, 0);
        if (BA790A->unk155 == 0) {
            actorUpdateFloorContactAndTilt(D_807FBB40, 6.0f);
            BA790A->unk155 = 1;
        }
        if (D_807444EC != 1) {
            if (D_807FBB40->unk58 == 0xB6) {
                x = 0x24D;
            } else {
                x = 0x24C;
            }
            func_8072C918(arg0, 0x24E, x);
        }
        if (D_807FBB40->unk154 == 0x33) {
            ret = 1;
            BA790A->unkB8 = ((BA790View9C *)D_807FDC9C)->unkD;
            q = mathAngleBetweenPoints2D(D_807FDC94->unk7C, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk84);
            BA790A->unkE6 = q;
            BA790A->unkEE = q;
        }
        break;
    case 0x38:
        switch (BA790A->unk155) {
        case 1:
            break;
        case 0:
            actorScriptStart(D_807FBB40, 0x24B);
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 2:
            func_8067E278(0, 1);
            func_8072D99C();
            break;
        }
        break;
    case 0x37:
        sel = BA790A->unk155;
        if (sel >= 2) {
            if (sel - 0x82 < 0) {
                x = 0;
            } else {
                x = sel - 0x82;
            }
            if (sel * 6 >= 0x23) {
                r = 0x22;
            } else {
                r = (sel * 6) & 0xFF;
            }
            q = r;
            t = (u32)((1.0 - (f64)x * 0.03125) * 230.0) & 0xFF;
            if (t != 0) {
                func_8065D254(D_807FBB40, 0x3C3, 0x40, 0x40, q, q, 1, 0x96, t, 0, 1.0f);
            } else {
                func_8072D99C();
            }
            sel = BA790A->unk155;
            if (sel >= 0x17) {
                x = 0x16;
            } else {
                x = sel;
            }
            fv = ((22.0 - (f64)x) / 20.0) * 200.0;
            if (fv > 130.0) {
                fv = 200.0f;
            }
            lightAdd(BA790A->unk7C, BA790A->unk80, BA790A->unk84, 0.0f, 0.0f, 0.0f, fv, 0, 0xFF, 0xFF, 0xFF);
            sel = BA790A->unk155;
        }
        if (sel < 4) {
            actorMoveWithinZone(0x33, D_807FDC94->unk7C, D_807FDC94->unk84, 0x20, 6.0f);
            sel = BA790A->unk155;
        }
        switch (sel) {
        case 0:
            actorScriptStart(D_807FBB40, 0x24B);
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 2:
            sfxSpawnTableNodes(D_807FBB40);
            func_8067E278(1, 1);
            actorSetNodeFlag(D_807FBB40, 3);
            camStartShakeFromPoint(gCamActor, 5, 0x14, BA790A->unk7C, BA790A->unk80, BA790A->unk84, 200.0f, 400.0f);
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 4:
            sfxStopSlotSound(D_807FBB40, 0);
            BA790A->unkEE = BA790A->unkE6;
            sfxPlayActorSound(D_807FBB40, 0x136, 0, 0, 0, 0xFF, 1.0f, 0);
            func_807149FC(5);
            func_807149B8(1);
            func_807149C8(0xFF, 0xFF, 0xFF, 1);
            func_80714998(1);
            func_80714A08(-0.4f, 0.4f);
            func_8071498C(effectSparkSpawnUpdate);
            func_80714CC0(&D_80720630, 0.3f, BA790A->unk7C, BA790A->unkA4 + 7.0f, BA790A->unk84);
            BA790A->unk60 &= ~4;
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 1:
        case 3:
            break;
        case 5:
            BA790A->unk138 = 0;
            actorClearNodeFlag(D_807FBB40, 3);
        default:
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        }
        break;
    default:
        func_8072B7CC(0x24E);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    return ret;
}

s32 func_806B5A90();
void behaviourFrameBegin(void);

void func_806B63E0(void) {
    behaviourFrameBegin();
    func_806B5A90(0x2710, 0);
}

extern u8 D_807444EC;
extern s32 D_8076A0A8;

void actorClearNodeFlag(Actor *, s32);
void actorScriptStart(void *, s32);
void lightUpdateFromActorLighting(void *, void *, void *);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void func_806B640C(void) {
    s16 *p = BA790A->unk178;
    s16 i;
    s32 sel;
    s32 a;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorClearNodeFlag(D_807FBB40, 3);
        *p = -BA790S9C->unkA;
    }
    if (D_807444EC == 1) {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 3) {
                D_807FBB40->unk144 = 0x24;
                actorScriptStart(D_807FBB40, 0x24F);
            }
        }
        lightUpdateFromActorLighting(&D_807FBB40->unk16A, &D_807FBB40->unk16B, &D_807FBB40->unk16C);
    }
    sel = D_807FBB40->unk154;
    if (sel != 0x37 && sel != 0x38) {
        if (*p > 0) {
            (*p)--;
            if (*p == 0xA) {
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x150, 0xFF, 0x7F, 0x1E, 0x32, 0.3f, 0);
            }
            if (*p == 0) {
                D_807FBB70.unk200 = 9;
            }
        }
    }
    if (D_8076A0A8 == 6) {
        a = 0x9C40;
    } else {
        a = 0x2710;
    }
    if (func_806B5A90(a, *p) != 0) {
        *p = -*p;
    }
}
