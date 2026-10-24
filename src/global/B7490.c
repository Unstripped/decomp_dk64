#include "common.h"
#include "actor.h"

typedef struct B7490Actor {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0xC];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ u8 padE6[2];
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[0x46];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x42];
    /* 0x178 */ s16 *unk178;
} B7490Actor;

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 x;
    /* 0x0C */ s16 y;
    /* 0x0E */ s16 z;
} B7490Pos;

#define B7490A ((B7490Actor *)D_807FBB40)
#define B7490MAXD(a, b) ((a) < (b) ? (b) : (a))

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;
extern Struct807FD580 *D_807FD580;
extern s32 D_807FDCA0;
extern u32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_8072073C[];
extern s16 D_80750340;

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
void func_8072DE44();
void func_8072DC7C();
void func_8072AA80(void);
void func_8072C918(s32, s32, s32);
s32 func_80611A44(void);
f32 func_80612794(s16);
s16 func_806CC190(s16, s16, f32);
void actorClearNodeFlag(Actor *, s32);
void func_80614D00(void *, f32, f32);
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
void projectileGetTargetCoords(void *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, void *);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
s32 func_80726164(void *, s16, s16, s16, s32);
f32 sqrtf(f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void func_8072881C();
void func_806B4194(void);
void func_806B42A8(void (*)(), u16, u16, s16);
void func_806B49B0(u8, s16, s16);
void actorSpawnNodeEntryAtActor(s32, s32);
void actorAttachChildCallbacks(void);
void sfxAllocateChannel(s32, f32);
void func_8063DA40(s32, s32);
void actorPlaceAttachedChildren(s32);
void func_8072D9D4(void);
void func_8061CC40(void *, s32, s32);
void func_8072B79C(s32, s32, s32);
void actorApplyVelocityCustom(void *, f32, f32);
void func_80665564(void *, f32);

void func_806B2790(void) {
    u8 flag;
    s32 st;

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
                    func_8072DE44(0x2DE);
                    break;
            }
            st = D_807FBB40->unk154;
            if (flag) {
                func_8072A86C(st, D_807FDC94->unk7C, D_807FDC94->unk84, 100.0f, 0x2240);
            }
            break;
        case 1:
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((func_80611A44() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, D_807FDC90->unkC, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 15);
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
            func_8072A920(st, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    B7490A->unkE4 = func_806CC190(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14);
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
            func_8072D13C(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x6400, 0x2DE, 0x2DE);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806B2D5C(void) {
}

typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} L1Sub24;

typedef struct {
    /* 0x00 */ L1Sub24 *unk0;
} L1Sub4;

void func_8072DEA8(s32, s32, s32, void *);
void func_8072881C(s32, void *);

void func_806B2D64(void) {
    s32 st;
    f32 min;
    f32 fa;
    f32 fb;

    func_80729B00();
    effectSpawnSparks(0x1F, 2);
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        D_807FDC98->unk46 |= 8;
        func_8072D714(D_807FBB70.unk1FC, 0x2E7);
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x2E5, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
        D_807FBB40->unkB8 = 0.0f;
    }
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x31:
            effectSpawnSparks(0x1F, 2);
            if ((D_807FBB40->unk155[0] != 0) || (((L1Sub4 *)D_807FBB40->unk4)->unk0->unk24 == 0.0f)) {
                func_8072DE44(0x2E2);
            }
            break;
        case 0x27:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2E6);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    break;
                case 4:
                    func_8072DE44(0x2E2);
                    break;
            }
            break;
        case 0x25:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_80614EBC(D_807FBB40, 0x2E4);
                    D_807FBB40->unk155[0] = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(D_807FBB40, 1);
                    projectileSpawnNodeEntry(0x112, 0, 0.3f, D_807FBB40->unkE6, 300.0f, func_80612794(B7490A->unkE8) * 300.0f, D_807FBB40);
                    effectSpawnSparks(1, 1);
                    break;
                case 3:
                    func_8072DE44(0x2E2);
                    break;
            }
            break;
        case 1:
            func_806B2D5C();
            B7490A->unkE4 += 800.0f * func_80612794(D_807FDC90->unk18 * 10);
            if (((func_80611A44() >> 15) % 1000) >= 0x3D5) {
                func_8072AA80();
            }
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, D_807FDC90->unkC, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            func_806B2D5C();
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC94->unk7C, ((D_807FBB40->unkAC - D_807FBB40->unk15E) < D_807FDC94->unk80) ? (D_807FBB40->unkAC - D_807FBB40->unk15E) : D_807FDC94->unk80, D_807FDC94->unk84, 0x1E, 3.3f, 100.0f, 0x2040);
            if (D_807FBD70 == 2) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 2:
        case 3:
            D_807FBB40->unk132 = 2;
        case 7:
        case 0x35:
            func_806B2D5C();
            func_8072A920(D_807FBB40->unk154, 0, D_807FDC90->unkA, (D_807FDC90->unkC < (D_807FBB40->unkAC - D_807FBB40->unk15E)) ? D_807FDC90->unkC : (D_807FBB40->unkAC - D_807FBB40->unk15E), D_807FDC90->unkE, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    B7490A->unkE4 = func_806CC190(B7490A->unkE4, 0, 7.0f);
                    break;
                case 1:
                    func_8072DC7C(0x14);
                    break;
                case 2:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x2E2);
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
            func_8072D13C(D_807FBB40->unk154, 1);
            break;
        default:
            func_8072C918(0x6400, 0x2E2, 0x2E2);
            break;
    }
    func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
    func_806319C4(D_807FBB40, 0);
}

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
                B7490A->unkC0 = B7490A->unkC4;
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
                    if (D_807FDC90->unk30 > (dx = D_807FBB40->unk4->unk38)) {
                        func_807248B0(D_807FBB40, dx * 1.01);
                    } else {
                        for (i = 0; i < 0xC; i++) {
                            func_807149B8(1);
                            func_807149FC(2);
                            func_80714950(i + 0x0B020000);
                            func_8071498C(func_8071ABDC);
                            func_80714998(1);
                            func_80714CC0(D_8072073C, 2.0 * D_807FBB40->unk4->unk38, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                        }
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
    st = (s32)D_807FBB40->unk154;
    if (D_807FBB40->unk154 == 2 || st == 3) {
        func_8072D13C(D_807FBB40->unk154, 1);
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B3680.s")
#endif

void func_806B3C30(u8 arg0) {
    projectileGetTargetCoords(D_807FBB40, arg0);
    projectileSpawnNodeEntry(0x32, 1, 0.3f, ((s16 *)D_807FBB40)[0xEE / 2], 80.0f, 0.0f, D_807FBB40);
}

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

void func_806B3F90(B7490Pos *arg0, u8 arg1) {
    f32 dz;
    f32 dx;
    f32 dist;
    f32 t;
    f32 dy;

    dz = arg0->z - B7490A->unk84;
    dx = arg0->x - B7490A->unk7C;
    dist = sqrtf(dz * dz + dx * dx);
    t = B7490MAXD(dist / B7490MAXD(B7490A->unkB8, 0.0001), 0.0001);
    B7490A->unkC0 = 0.0f;
    dy = (B7490A->unk80 < arg0->y) ? 0.0f : B7490A->unk80 - arg0->y;
    B7490A->unkC4 = -(dy / t);
    B7490A->unkE8 = func_806CC190(B7490A->unkE8, (s32)((mathCalculatePitchAngle(arg0->x, arg0->y, arg0->z, B7490A->unk7C, B7490A->unk80, B7490A->unk84, 0x46) * 2048.0) / 3.1415927410125732), 3.3f);
    func_8072AB74(arg1, arg0->x, arg0->z, 0x2E0, 0.0f);
}

void func_807149C8(u8, u8, u8, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void func_806B4194(void) {
    u8 col2;
    u8 col;
    f32 f;
    u32 var_v0;

    switch (B7490A->unk134) {
        case 2:
            col = 0xC8;
            var_v0 = 0x20;
            f = 0.5f;
            break;
        case 1:
            var_v0 = 0x18;
            col = 0x64;
            f = 1.0f;
            break;
        case 0:
            var_v0 = 8;
            col = 0x32;
            f = 1.5f;
            break;
        default:
            var_v0 = 0;
    }
    if ((var_v0 != 0) && ((D_8076A064 % var_v0) == 0)) {
        func_80714998(3);
        func_807149C8(col, col, col, *(u8 *) ((u8 *) D_807FBB40 + 0x129));
        effectSpawnBoneDefault(D_807FBB40, 1, f, 0.0f, 0.0f, 0.0f, -0x50);
    }
}

#ifdef NON_MATCHING
s32 func_8061CB50(void *);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void sfxSpawnTableNodes(Actor *);

void func_806B42A8(void (*arg0)(), u16 arg1, u16 arg2, s16 arg3) {
    s16 *var_t2;
    s16 var_t0;
    s16 var_t1;
    s32 st;

    var_t2 = B7490A->unk178;
    if ((arg3 != 0) && (D_807FBB40->unk154 != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, arg3, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        *var_t2 = D_807FDC9C->unkA;
        if (D_807FDC9C->unkB == 0) {
            D_807FDC9C->unkB = 0x28;
        }
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, arg1);
        B7490A->unkC0 = 300.0f;
        *var_t2 = 0;
        D_807FDC90->unk2C = 0x2BC;
    }
    var_t0 = D_807FDC90->unkA;
    var_t1 = D_807FDC90->unkE;
    switch (D_807FBB40->unk154) {
        case 1:
        case 0x10:
        case 0x23:
            var_t0 = (s16) (s32) D_807FDC94->unk7C;
            var_t1 = (s16) (s32) D_807FDC94->unk84;
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (D_807FBB40->unk80 < (f32) (D_807FDC9C->unk6 + *var_t2)) {
                D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (u32) D_807FDC9C->unkB * 0.03125));
            } else {
                if ((func_8061CB50(D_807FDC90) == 0) && (arg0 != NULL)) {
                    arg0();
                }
            }
            func_8072AB74(D_807FBB40->unk154, (f32) var_t0, (f32) var_t1, 0x2C1, 0.0f);
            B7490A->unkE8 = func_806CC190(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    D_807FDC90->unkA = (s16) (s32) D_807FDC94->unk7C;
                    D_807FDC90->unkC = (s16) (s32) D_807FDC94->unk80;
                    D_807FDC90->unkE = (s16) (s32) D_807FDC94->unk84;
                    D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                    D_807FDC90->unk2C = 0x64;
                case 1:
                    /* func_806B3F90 is defined above as void; the target uses its v0 result. */
                    if ((((s32 (*)()) func_806B3F90)(D_807FDC90, 0x23) & 1) || (D_807FBB40->unk80 < (f32) (D_807FDC90->unkC + 0xF))) {
                        D_807FBB40->unk154 = D_807FDC9C->unk10;
                        D_807FBB40->unk155[0] = 0;
                    }
                    break;
            }
            break;
        case 0x37:
            D_807FBB40->unkE6 = D_807FBB40->unkE6 + D_807FDC90->unk2C;
            D_807FDC90->unk2C = ((D_807FDC90->unk2C - 0x11) < 0) ? 0 : (D_807FDC90->unk2C - 0x11);
            if (D_807FDC90->unk2C == 0) {
                sfxStopSlotSound(D_807FBB40, 0);
            }
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_8072AB74(0x37, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    if (D_807FBB40->unk58 == 0x11D) {
                        D_807FBB40->unk155[0] = 3;
                    } else {
                        B7490A->unkC0 = 50.0f;
                        D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
                case 2:
                        func_8072AB74(0x37, 0.0f, 0.0f, 0x222, 0.0f);
                    }
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(arg2);
            break;
    }
    st = D_807FBB40->unk154;
    switch (st) {
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(st, 1);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B42A8.s")
#endif

void func_806B486C(void) {
    func_80729B00();
    func_806B42A8(func_806B3E7C, 0x251, 0x250, 0x10E);
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806B48B8(void) {
    func_80729B00();
    func_806B42A8(func_806B3DA4, 0x251, 0x250, 0x10E);
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806B4904(void) {
    func_80729B00();
    func_806B42A8(func_806B3D18, 0x254, 0x252, 0x108);
    func_806B4194();
    func_8072881C(0, D_807FDC90->unk28);
}

void func_806B4958(void) {
    func_80729B00();
    func_806B42A8(func_806B3E7C, 0x251, 0x250, 0x10E);
    if (D_807FBB40->unk154 != 0x37) {
        func_806B3E08();
    }
}

#ifdef NON_MATCHING
extern f32 D_807502EC;
void func_80724CA4(s32, s32);

void func_806B49B0(u8 arg0, s16 arg1, s16 arg2) {
    s16 *temp_v0;
    s16 sp32;
    u8 var_t0;
    s32 *dead1;
    s32 *dead2;

    temp_v0 = B7490A->unk178;
    dead1 = (s32 *) temp_v0;
    dead2 = (s32 *) temp_v0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(1, 1);
        D_807FDC90->unk30 = D_807FBB40->unk4->unk38;
        D_807FBB40->unkB8 = (f32) (u32) D_807FDC9C->unkC;
        *temp_v0 = D_807FDC9C->unkA;
        B7490A->unkC4 = D_807502EC;
    }
    sp32 = D_807FDC9C->unk6 + *temp_v0;
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (arg0 != 0x37)) {
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
    }
    var_t0 = arg0;
    switch (var_t0) {
        case 2:
        case 3:
            if (D_807FBB40->unk155[0] == 0) {
                func_80614EBC(D_807FBB40, arg1);
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            }
            func_8072AB74(arg0, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0xE1, 0.0f);
            if (D_807FBB40->unk80 < (f32) sp32) {
                if (D_807FBB40->unk155[0] == 2) {
                    D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.03125));
                } else {
                    D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (f32) (u32) D_807FDC9C->unkB * 0.015625));
                }
            }
            B7490A->unkE8 = func_806CC190(B7490A->unkE8, 0, 5.0f);
            break;
        case 0x26:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                case 1:
                case 2:
                    func_80614EBC(D_807FBB40, arg2);
                    D_807FBB40->unk155[0] = 3;
                case 3:
                    func_806B3F90((void *) D_807FDC90, 0x26);
                    break;
            }
            break;
        case 0x37:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                D_807FBB40->unk154 = 0x40;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(arg1);
            break;
    }
    switch (var_t0) {
        case 2:
        case 3:
            func_8072D13C(arg0, 1);
            break;
        case 0x26:
            if (func_8072D13C(arg0, 1) != 0) {
                D_807FBB40->unk154 = D_807FDC9C->unk10;
                D_807FBB40->unk155[0] = 0;
            }
            break;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/B7490/func_806B49B0.s")
#endif

void func_806B4DCC(void) {
    f64 temp_f64;
    s16 *sp3C;
    f32 temp_fv0;
    s32 temp_v0;
    s16 temp_v1;
    u8 temp_v0_2;

    sp3C = ((B7490Actor *) D_807FBB40)->unk178;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 = D_807FBB40->unk60 | 0x400;
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x40;
        D_807FBB40->unk16A = 0xFA;
        D_807FBB40->unk16B = 0xFA;
        D_807FBB40->unk16C = 0xFA;
        actorSpawnNodeEntryAtActor(0x2D, 0x44);
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2C1, 0xFF, 0x7F, 0, 0x14, 0.0f, 0);
    }
    temp_v0 = D_807FDC90->unkC - D_807FDC9C->unk6;
    *sp3C = (temp_v0 < 0) ? 0 : temp_v0;
    if ((D_807FBD70 == 9) && (D_807FBB40->unk154 != 0x37)) {
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
        func_80614EBC(D_807FBB40, 0x248);
        actorAttachChildCallbacks();
        sfxAllocateChannel(0x14, 1.0f);
        func_8063DA40(0x7F, 0xA);
    }
    temp_v0_2 = D_807FBB40->unk154;
    if ((temp_v0_2 != 0x37) && (temp_v0_2 != 0x40)) {
        actorPlaceAttachedChildren(-0x1E);
    }
    temp_f64 = D_807FBB40->unk4->unk34;
    temp_fv0 = D_807FBB40->unk4->unk34;
    func_807248B0(D_807FBB40, (f32) (((f64) (D_807FDC90->unk30 - temp_fv0) * 0.05) + (f64) temp_fv0));
    temp_v1 = D_807FDC90->unk2C;
    if (temp_v1 != 0) {
        D_807FDC90->unk2C = temp_v1 - 1;
        if (D_8076A064 & 4) {
            D_807FBB40->unk60 = D_807FBB40->unk60 | 0x800000;
        } else {
            D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFF7FFFFF;
        }
    } else {
        D_807FBB40->unk132 = 1;
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFF7FFFFF;
        if (D_807FBD70 == 4) {
            D_807FBB40->unk132 = 2;
            D_807FDC90->unk2C = 0x1E;
            D_807FDC90->unk30 = (f32) ((f64) D_807FDC90->unk30 * 0.7);
            func_8072D9D4();
            func_8061CC40(D_807FBB40, 3, 5);
            if (((B7490Actor *) D_807FBB40)->unk134 & 1) {
                func_80614EBC(D_807FBB40, 0x24A);
            } else {
                func_80614EBC(D_807FBB40, 0x249);
            }
        }
    }
    func_806B49B0(D_807FBB40->unk154, 0x247, 0x246);
    func_8072881C(0, D_807FDC90->unk28);
    func_806319C4(D_807FBB40, 0);
}

void func_806B50F4(void) {
    func_80729B00();
    func_806B49B0(D_807FBB40->unk154, 0x23D, 0x23E);
    func_806319C4(D_807FBB40, 0);
}

void func_806B513C(void) {
    s32 temp_t3;
    s16 temp_a1;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_8072B79C(0x30C, 0x30B, 0x30D);
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
    }
    if (D_8076A0A8 == 0xA6) {
        temp_t3 = D_807FD580->unk1F0 & 0x40;
        if ((temp_t3 != 0) && (D_807FBB40->unk128 == 0)) {
            D_807FDC90->unk2C = 0xA;
            D_807FBB40->unk144 = 0x24;
        } else if ((temp_t3 == 0) && (D_807FBB40->unk128 == 0xFF)) {
            D_807FDC90->unk2C = -0xA;
            D_807FBB40->unk144 = 1;
        }
        temp_a1 = D_807FDC90->unk2C;
        if (temp_a1 != 0) {
            D_807FBB40->unk128 = D_807FBB40->unk128 + temp_a1;
            if (D_807FBB40->unk128 >= 0x100) {
                D_807FBB40->unk128 = 0xFF;
                D_807FDC90->unk2C = 0;
            } else if (D_807FBB40->unk128 < 0) {
                D_807FBB40->unk128 = 0;
                D_807FDC90->unk2C = 0;
            }
        }
    }
    func_806B42A8((D_8076A064 & 1) ? func_806B3E7C : func_806B3F3C, 0x30E, 0x30B, 0);
}

void func_806B52DC(void) {
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x60;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        D_807FBB40->unkB8 = (f32) (((func_80611A44() >> 15) % 100) + 0x12C);
        D_807FBB40->unk80 += (f32) ((func_80611A44() >> 15) % 30);
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
        D_807FBB40->unk128 = 0;
        ((B7490Actor *) D_807FBB40)->unkEC = ((func_80611A44() >> 15) % 7) + 0xF;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocityCustom(D_807FBB40, D_807FBB40->unkB8, 0.0f);
    func_80665564(D_807FBB40, 0.0f);
    switch (D_807FBB40->unk154) {
    case 6:
        D_807FBB40->unk128 = D_807FBB40->unk128 + ((B7490Actor *) D_807FBB40)->unkEC;
        if (D_807FBB40->unk128 >= 0xFF) {
            D_807FBB40->unk128 = 0xFF;
            D_807FBB40->unk154 = 0x37;
        }
        break;
    case 0x37:
        D_807FBB40->unk128 = D_807FBB40->unk128 - ((B7490Actor *) D_807FBB40)->unkEC;
        if (D_807FBB40->unk128 < 0) {
            D_807FBB40->unk154 = 0x3C;
            D_807FBB40->unk128 = 0;
        }
        break;
    default:
        func_8072B7CC(0x333);
        break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    func_806319C4(D_807FBB40, 0);
}

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} B7490St178;

extern u16 D_80744508;
s32 func_806119A0(void);
f32 func_806119FC(void);
f32 func_80612790(s16);
s32 func_806CC10C(s16, s16);
void func_80724B5C(s32, s32, f32 *, f32 *, f32 *);
s32 func_8073110C(s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);

void func_806B54BC(void) {
    f32 dead;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    s16 D_807FBB40_3;
    B7490St178 *temp_s1;

    temp_s1 = (B7490St178 *) B7490A->unk178;
    func_80729B00();
    dead = temp_s1->unk0; // dead store: reserves the extra frame slot above sp68
    if ((D_807FBB40->unk154 != 0x40) && (D_807FBB40->unk154 != 0x37) && ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0))) {
        sfxStopSlotSound(D_807FBB40, 0);
        func_80614EBC(D_807FBB40, 0x331);
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB4C, 0x16, 0xFF, 0x7F, 0x1E);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x20;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        D_807FBB40->unkB8 = 40.0f;
        D_807FBB40->unk154 = 0x23;
        D_807FBB40->unk155[0] = 0;
        B7490A->unkEC = ((func_80611A44() >> 15) % 7) + 0xF;
        temp_s1->unk0 = D_807FBB40->unk7C;
        temp_s1->unk4 = D_807FBB40->unk80;
        temp_s1->unk8 = D_807FBB40->unk84;
        temp_s1->unk10 = 1;
        temp_s1->unkC = D_807FBB40->unk80;
        temp_s1->unk12 = (func_806119A0() & 0xFF) + 0x78;
    }
    if ((D_807FBB40->unk154 != 0x37) && (B7490A->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, 0x10E, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    switch (D_807FBB40->unk154) {
        case 0x26:
            temp_s1->unk0 = D_807FBB4C->unk7C;
            temp_s1->unk4 = D_807FBB4C->unk80;
            temp_s1->unk8 = D_807FBB4C->unk84;
            temp_s1->unk12 = (func_806119A0() & 0xFF) + 0x78;
        case 0x23:
            D_807FBB40->unkE6 = D_807FBB40->unkE6 - (func_806CC10C(mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, temp_s1->unk0, temp_s1->unk8) + 0x800, D_807FBB40->unkE6) >> 4);
            temp_s1->unk10 = temp_s1->unk10 - 1;
            if (temp_s1->unk10 <= 0) {
                func_80724B5C(1, 0, &sp68, &sp64, &sp60);
                temp_s1->unk10 = (func_806119A0() & 0x3F) + 0xF;
                D_807FBB40_3 = mathAngleBetweenPoints2D(sp68, sp60, temp_s1->unk0, temp_s1->unk8);
                D_807FBB40_3 += ((func_806119A0() & 7) << 8) + 0x400;
                sp5C = (f32) ((f64) func_806119FC() * 180.0);
                temp_s1->unk0 = (func_80612794(D_807FBB40_3) * sp5C) + sp68;
                temp_s1->unk4 = temp_s1->unkC;
                temp_s1->unk8 = (func_80612790(D_807FBB40_3) * sp5C) + sp60;
                D_807FBB40->unk154 = 0x23;
            }
            if (D_807FBB40->unk154 == 0x23) {
                temp_s1->unk12 = temp_s1->unk12 - 1;
                if (temp_s1->unk12 <= 0) {
                    temp_s1->unk10 = 0x3C;
                    D_807FBB40->unk154 = 0x26;
                }
            }
            sp64 = (f32) ((f64) (temp_s1->unk4 - D_807FBB40->unk80) * 0.0625);
            if ((f64) sp64 > 8.0) {
                sp64 = 8.0f;
            }
            if ((f64) sp64 < -8.0) {
                sp64 = -8.0f;
            }
            D_807FBB40->unk7C += func_80612794(D_807FBB40->unkE6) * 8.0;
            D_807FBB40->unk80 = D_807FBB40->unk80 + sp64;
            D_807FBB40->unk84 += func_80612790(D_807FBB40->unkE6) * 8.0;
            break;
        case 0x37:
            D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
            D_807FBB40->unk128 = D_807FBB40->unk128 - 8;
            D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 - 10.0);
            if (D_807FBB40->unk128 < 0) {
                D_807FBB40->unk128 = 0;
                D_807FBB40->unk154 = 0x40;
                D_807FBB40->unk155[0] = 0;
                D_807FBB40->unk144 = 1;
                if (D_8076A0A8 == 0xA7) {
                    D_80744508 = D_80744508 + 1;
                    if ((D_80744508 == 5) && (func_8073110C(0x15F, 0) == 0)) {
                        func_8063DA40(4, 0xA);
                    }
                }
            }
            break;
        default:
            func_8072B7CC(0x32F);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}
