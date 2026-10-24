#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FDC94;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[0x12];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ f32 unk30;
} M5State90;

typedef struct {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} M5State98;

typedef struct {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ u8 padC8[0x1C];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ u8 padE6[2];
    /* 0xE8 */ s16 unkE8;
} M5Actor;

#define M5A ((M5Actor *)D_807FBB40)

extern M5State90 *D_807FDC90;
extern M5State98 *D_807FDC98;

void func_80614EBC(void *, s32);
s32 func_8072E0A8(s32, s32);
void func_80729B00(void);
void func_8067ACB4(Actor *);
void func_806319C4(void *, s32);
void effectSpawnSparks(s32, s32);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072A920(s16, s32, f32, f32, f32, s32, f32, f32, s32);
void func_8072A86C(s16, f32, f32, f32, s32);
void func_8072B7CC(s32);
s32 func_8072D13C();
void func_8072D714(s32, s32);
void func_8072DE44(s32, s32);
void func_8072DC7C(s32, s32, f32);
void func_8072AA80(void);
void func_8072C918(s32, s32, s32);
s32 func_80611A44(void);
f32 func_80612794(s16);
s16 func_806CC190(s16, s16, f32);

#ifdef NON_MATCHING
void func_806B2790(void) {
    u8 flag;
    u8 st;

    func_80729B00();
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, 0x2E1);
        D_807FDC98->unk46 |= 8;
    }
    effectSpawnSparks(0x1F, 0);
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x27:
            flag = 0;
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2E0);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    flag = 1;
                    D_807FBB40->unkB8 = 150.0f;
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    flag = 1;
                    break;
                case 4:
                    func_8072DE44(0x2DE, 0x2E0);
                    break;
            }
            st = D_807FBB40->unk154;
            if (flag) {
                func_8072A86C(st, D_807FDC94->unk7C, D_807FDC94->unk84, 100.0f, 0x2240);
            }
            break;
        case 1:
            M5A->unkE4 = M5A->unkE4 + 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((func_80611A44() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, D_807FDC90->unkC, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            M5A->unkE4 = M5A->unkE4 + 800.0f * func_80612794(D_807FDC90->unk18 * 15);
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, ((D_807FBB40->unkAC - D_807FBB40->unk15E) < D_807FDC94->unk80) ? (D_807FBB40->unkAC - D_807FBB40->unk15E) : D_807FDC94->unk80, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    M5A->unkE4 = func_806CC190(M5A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14, 0, 7.0f);
                    break;
                case 2:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2DE);
            break;
    }
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(st, 1);
        default:
            func_8072C918(0x6400, 0x2DE, 0x2DE);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B2790.s")
#endif

void func_806B2D5C(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B2D64.s")

void actorClearNodeFlag(Actor *, s32);
void func_80614D00(void *, f32, f32);

void func_806B3420(void) {
    f32 dx;
    f32 dy;
    f32 dz;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 0x24;
        D_807FBB40->unk60 |= 0x400;
        D_807FDC90->unk2C = 0x5A;
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155[0] = 0;
        func_8067ACB4(D_807FBB40);
        actorClearNodeFlag(D_807FBB40, 1);
    }
    dx = D_807FBB40->unk7C - D_807FDC94->unk7C;
    dy = D_807FBB40->unk80 - D_807FDC94->unk80;
    dz = D_807FBB40->unk84 - D_807FDC94->unk84;
    if (dx * dx + dy * dy + dz * dz > 90000.0f) {
        D_807FBB40->unk60 |= 0x80000000;
    } else {
        D_807FBB40->unk60 &= 0x7FFFFFFF;
    }
    switch (D_807FBB40->unk154) {
        case 0:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                func_80614EBC(D_807FBB40, 0x35D);
                func_80614D00(D_807FBB40, 0.5f, 0.0f);
                D_807FBB40->unk154 = 1;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 1:
            if (D_807FBB40->unk155[0] != 0) {
                D_807FBB40->unk154 = 2;
                D_807FBB40->unk155[0] = 0;
                D_807FDC90->unk2C = 0x5A;
            }
            break;
        case 2:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk132 = 2;
                func_80614D00(D_807FBB40, 0.5f, 0.0f);
                D_807FBB40->unk154 = 3;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] != 0) {
                D_807FBB40->unk132 = 1;
                D_807FBB40->unk154 = 0;
                D_807FBB40->unk155[0] = 0;
                D_807FDC90->unk2C = 0x5A;
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}


extern Actor *D_807FBB4C;
extern s32 D_8076A0A8;
extern u8 D_8072073C[];

void func_8072E1A4(s32, void *);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_807248B0(void *, f32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_8071ABDC();
void func_80714998(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8067E278(s32, s32);
void actorGetOrSetNodeScale(void *, s32, f32);
void func_8066EB40(void *, f32);

#ifdef NON_MATCHING
void func_806B3680(void) {
    f32 dx;
    f32 var;
    f32 sp54;
    f32 dy;
    f32 dz;
    u8 st;
    s16 i;

    var = D_807FBB40->unk4->unk38 * 800.0f;
    sp54 = 1.1f;
    if (D_8076A0A8 == 0xC7) {
        if (!(D_807FBB4C->unk6A & 4)) {
            var = 0.0f;
            sp54 = 0.4f;
        } else {
            var = var * 0.75;
            sp54 = 0.7f;
        }
    }
    var = var * var;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 4;
        func_8067ACB4(D_807FBB40);
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x27)) {
        D_807FBB40->unk154 = 0x27;
        D_807FBB40->unk155[0] = 0;
    } else if (D_807FBB40->unk154 != 0x27) {
        dx = D_807FDC94->unk7C - D_807FBB40->unk7C;
        dy = D_807FDC94->unk80 - D_807FBB40->unk80;
        dz = D_807FDC94->unk84 - D_807FBB40->unk84;
        if (dx * dx + dy * dy + dz * dz < var) {
            D_807FBB40->unk154 = 0x27;
            D_807FBB40->unk155[0] = 0;
        }
    }
    effectSpawnSparks(0x1F, 0);
    st = D_807FBB40->unk154;
    switch (st) {
        case 4:
            func_8072AB74(0, 0.0f, 0.0f, 2, 0.0f);
            if (D_807FBB40->unk80 < D_807FBB40->unkAC) {
                D_807FBB40->unk80 = D_807FBB40->unkAC;
                M5A->unkC0 = M5A->unkC4;
            }
        case 0:
            func_8072E1A4(0xA, D_807FDC94);
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C2, 0xFF, 0x7F, 0);
                    D_807FDC90->unk30 = 2.0 * D_807FBB40->unk4->unk38;
                    D_807FBB40->unk155[0]++;
                case 1:
                    dx = D_807FBB40->unk4->unk38;
                    i = 0;
                    if (dx < D_807FDC90->unk30) {
                        func_807248B0(D_807FBB40, dx * 1.01);
                    } else {
                        do {
                            func_807149B8(1);
                            func_807149FC(2);
                            func_80714950(i + 0x0B020000);
                            func_8071498C(func_8071ABDC);
                            func_80714998(1);
                            func_80714CC0(D_8072073C, 2.0 * D_807FBB40->unk4->unk38, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                            i++;
                        } while (i < 0xC);
                        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x3D, 0xFF, 0x7F, 0);
                        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x35C, 0xFF, 0x7F, 0, 0x32, 0.3f, 0);
                        func_8067E278(0, 1);
                        actorGetOrSetNodeScale(D_807FBB40, 1, D_807FBB40->unk140->unkC * sp54);
                        func_8066EB40(D_807FBB40, D_807FBB40->unk140->unkC * sp54);
                        D_807FBB40->unk60 &= ~4;
                        D_807FBB40->unk155[0]++;
                    }
                    break;
                case 5:
                    D_807FBB40->unk154 = 0x40;
                    break;
                default:
                    D_807FBB40->unk155[0]++;
                    break;
            }
            break;
        case 2:
        case 3:
            dx = D_807FDC90->unkC;
            dy = D_807FBB40->unkAC - D_807FBB40->unk15E;
            dz = (dx < dy) ? dx : dy;
            func_8072A920((s16)st, 0, D_807FDC90->unkA, dz, D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        default:
            func_8072B7CC(0x32E);
            break;
    }
    if (D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 3) {
        func_8072D13C(st, 1);
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B3680.s")
#endif

void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);

void func_806B3C30(u8 arg0) {
    projectileGetTargetCoords(D_807FBB40, arg0);
    projectileSpawnNodeEntry(0x32, 1, 0.3f, ((s16 *)D_807FBB40)[0xEE / 2], 80.0f, 0.0f, D_807FBB40);
}

void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);

void func_806B3C94(void) {
    projectileSetTargetCoords(D_807FBB40->unk7C, D_807FBB40->unk80 - 5.0f, D_807FBB40->unk84);
    projectileAimAndSpawn(0x51, 1, 0.3f, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, 80.0f, D_807FBB40);
}


void func_806B3D18(void) {
    switch (D_807FBB40->unk155[0]) {
        case 0:
            if (func_8072E0A8(0x96, 0x96)) {
                func_80614EBC(D_807FBB40, 0x253);
                D_807FBB40->unk155[0] = 1;
            }
            break;
        case 2:
            func_806B3C30(2);
            D_807FBB40->unk155[0] = 3;
            break;
    }
}

extern s16 D_80750340;

void func_806B3DA4(void) {
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
        return;
    }
    if (func_8072E0A8(0x96, 0x96)) {
        func_806B3C30(1);
        D_807FDC90->unk2C = D_80750340;
    }
}

extern s32 D_8076A064;

void func_806B3E08(void) {
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
        if (D_8076A064 & 1) {
            func_806B3C94();
        }
    } else if (func_8072E0A8(0x96, 0x96)) {
        D_807FDC90->unk2C = 0x14;
    }
}

extern s32 D_807FDCA0;
s32 func_80726164(void *, s16, s16, s16, s32);

void func_806B3E7C(void) {
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
        return;
    }
    if (func_80726164(D_807FBB40, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, D_807FDCA0) && func_8072E0A8(0x96, 0x96)) {
        D_807FBB40->unk154 = 0x26;
        D_807FBB40->unk155[0] = 0;
    }
}


void func_806B3F3C(void) {
    if (((func_80611A44() >> 15) % 1000) >= 0x3E4) {
        D_807FBB40->unk154 = 0x1C;
        D_807FBB40->unk155[0] = 0;
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 x;
    /* 0x0C */ s16 y;
    /* 0x0E */ s16 z;
} M5Pos;

#define M5A ((M5Actor *)D_807FBB40)
#define M5MAXD(a, b) ((a) < (b) ? (b) : (a))

f32 sqrtf(f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);

void func_806B3F90(M5Pos *arg0, u8 arg1) {
    f32 dz;
    f32 dx;
    f32 dist;
    f32 t;
    f32 dy;

    dz = arg0->z - M5A->unk84;
    dx = arg0->x - M5A->unk7C;
    dist = sqrtf(dz * dz + dx * dx);
    t = M5MAXD(dist / M5MAXD(M5A->unkB8, 0.0001), 0.0001);
    M5A->unkC0 = 0.0f;
    dy = (M5A->unk80 < arg0->y) ? 0.0f : M5A->unk80 - arg0->y;
    M5A->unkC4 = -(dy / t);
    M5A->unkE8 = func_806CC190(M5A->unkE8, (s32)((mathCalculatePitchAngle(arg0->x, arg0->y, arg0->z, M5A->unk7C, M5A->unk80, M5A->unk84, 0x46) * 2048.0) / 3.1415927410125732), 3.3f);
    func_8072AB74(arg1, arg0->x, arg0->z, 0x2E0, 0.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B4194.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B42A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B486C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B48B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B4904.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B4958.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B49B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B4DCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B50F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B513C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B52DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B54BC.s")
