#include "common.h"
#include "actor.h"

typedef struct B2CE0Sub4 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8 pad40[0x24];
    /* 0x64 */ u16 unk64;
} B2CE0Sub4;

typedef struct B2CE0Sub178 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
} B2CE0Sub178;

typedef struct B2CE0Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ B2CE0Sub4 *unk4;
    /* 0x008 */ u8 pad8[4];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xC];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[4];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ u8 pad13C[0xA];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0xE];
    /* 0x178 */ B2CE0Sub178 *unk178;
} B2CE0Actor;

typedef struct B2CE0Node {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B2CE0Node;

typedef struct B2CE0ModelHdr {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} B2CE0ModelHdr;

typedef struct B2CE0View90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xD];
    /* 0x35 */ u8 unk35;
} B2CE0View90;

typedef struct B2CE0View9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} B2CE0View9C;

extern B2CE0Actor *D_807FBB40;
extern B2CE0Actor *D_807FBB44;

s32 randomNonNegative(void);
void actorUpdateModelMatrix(B2CE0Actor *, s32);

void matrixMakeRotationX(f32 (*)[4], f32);
void collisionSetQueryMode(s32);
void actorApplyGravity(void);
void func_8067ACB4(B2CE0Actor *);
void actorApplyVelocity(B2CE0Actor *);
void actorUpdateFloorContactAndTilt(B2CE0Actor *, f32);
void billboardSubmit(B2CE0Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void actorDespawn(B2CE0Actor *);
extern u8 D_8071FBC8[];
extern ActorGlobalState D_807FBB70;
void behaviourSetAnimIds(s32, s32, s32);
void func_80724CA4(s32, s32);
void actorScriptStart(B2CE0Actor *, s32);
void func_80724E48(u8);
u32 actorMoveWithinZone(u32, f32, f32, s32, f32);
void actorSetTargetSpeed(B2CE0Actor *, s32);
void func_8072A450();
void actorSetDefaultState();
s32 func_8072E54C();
void patrolPathStep(u32, s32);
void func_8072B7CC();
void behaviourFrameBegin(void);
s32 func_8072DE10(u16);
s16 mathAngleEaseToward(s16, s16, f32);
void func_8072C918(s32, s32, s32);
void func_8072D714(s32, s32);
void func_8072DC7C(s32);
void func_8072DEA8();
void func_8072E1A4(s32, void *);
void sfxSpawnTableNodes(void *);
void actorPatrolFollowerUpdate();
void effectSpawnOctagonRing(f32, f32, f32, f32);
s32 zoneCanReachPoint(B2CE0Actor *, s16, s16, s16, s32);
void projectileGetTargetCoords(B2CE0Actor *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s16, f32, f32, B2CE0Actor *);
void func_8072881C(s32, void *);
s32 actorIsTargetWithinDistance(s32);
extern s32 D_807FDCA0;
extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];

void func_806ADFE0(void) {
    f32 sp88[4][4];
    f32 sp48[4][4];

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkB8 = (randomNonNegative() >> 15) % 50 + 0x46;
        D_807FBB40->unkC0 = D_807FBB40->unkB8 * 2;
        D_807FBB40->unkC4 = -30.0f;
        D_807FBB40->unkC8 = -220.0f;
        D_807FBB40->unk168 = (randomNonNegative() >> 15) % 400 + 200;
    }
    D_807FBB40->unkE6 += D_807FBB40->unk168;
    if (D_807FBB40->unk168 > 0) {
        D_807FBB40->unk168 -= 10;
    }
    collisionSetQueryMode(1);
    actorApplyGravity();
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    actorUpdateFloorContactAndTilt(D_807FBB40, 0);
    billboardSubmit(D_807FBB40, 0x3C8, 0x40, 0x40, 10, 10, 1, 200, 0x80, 0, 1.0f);
    if (D_807FBB40->unk15F != 0) {
        actorUpdateModelMatrix(D_807FBB40, 0);
    } else {
        guTranslateF(sp88, 0, -30.0f, 0);
        matrixMakeRotationX(sp48, 180.0f);
        guMtxCatF(sp88, sp48, sp88);
        guTranslateF(sp48, 0, 30.0f, 0.0f);
        guMtxCatF(sp88, sp48, D_807FBB40->unkC);
        actorUpdateModelMatrix(D_807FBB40, 1);
    }
    if ((D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x56, 0xB4, 0x96, 1, 0x4B, 0.3f, 0);
        D_807FBB40->unkB8 = D_807FBB40->unkB8 * 0.6;
        D_807FBB40->unkC0 = D_807FBB40->unkB8 * 3.0f;
        return;
    }
    if ((D_807FBB40->unk6A & 1) && (D_807FBB40->unk6C & 1)) {
        func_80714CC0(D_8071FBC8, 1.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        actorDespawn(D_807FBB40);
    }
}

s32 actorSpawn(s32, s32);
u32 actorGetNodePos(B2CE0Actor *, s16, f32 *, f32 *, f32 *);
void actorSetUniformScale(void *, s32);

void actorSpawnChildAtNode(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    if (actorSpawn(0xED, arg0) != 0) {
        actorGetNodePos(D_807FBB40, arg2, &sp2C, &sp28, &sp24);
        D_807FBB44->unkA4 = D_807FBB40->unkA4;
        D_807FBB44->unkE6 = D_807FBB40->unkE6 + arg1;
        D_807FBB44->unkEE = D_807FBB44->unkE6;
        D_807FBB44->unk168 = arg3;
        D_807FBB44->unk7C = sp2C;
        D_807FBB44->unk80 = sp28;
        D_807FBB44->unk84 = sp24;
        actorSetUniformScale(D_807FBB44, *(s32 *)&D_807FBB40->unk4->unk38);
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void lensFlareAddSource(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void playerStateQueueCallback(s32, B2CE0Actor *, s32);

void func_806AE394(f32 arg0, f32 arg1) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 sp4E;

    actorGetNodePos(D_807FBB40, 1, &sp64, &sp60, &sp5C);
    actorGetNodePos(D_807FBB40, 2, &sp58, &sp54, &sp50);
    sp4E = mathAngleBetweenPoints2D(sp58, sp50, sp64, sp5C);
    lensFlareAddSource(sp64, sp60, sp5C, sp58, sp54, sp50, 0.6f, 0xFF, 0xFF, 0xFF);
    sp64 = func_80612794(sp4E) * arg0 + D_807FBB40->unk7C;
    sp5C = func_80612790(sp4E) * arg0 + D_807FBB40->unk84;
    lightAdd(sp64, D_807FBB40->unk80, sp5C, 0.0f, 0.0f, 0.0f, arg1, 0, 0xFF, 0xFF, 0xFF);
    if (D_807FBB40->unk154 != 0) {
        if ((D_807FDC94->unk7C - sp64) * (D_807FDC94->unk7C - sp64) + (D_807FDC94->unk80 - D_807FBB40->unk80) * (D_807FDC94->unk80 - D_807FBB40->unk80) + (D_807FDC94->unk84 - sp5C) * (D_807FDC94->unk84 - sp5C) < arg1 * arg1) {
            D_807FBB40->unkE6 = mathAngleBetweenPoints2D(D_807FDC94->unk7C, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk84);
            playerStateQueueCallback(0x43, D_807FBB40, 0);
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk155 = 0;
        }
    }
}

typedef struct B2CE0ActorView134 {
    /* 0x000 */ u8 pad0[0x134];
    /* 0x134 */ s16 unk134;
} B2CE0ActorView134;

extern s32 gCurrentMap;
void actorClearNodeFlag(B2CE0Actor *, s32);
void csModelStateSetFirstByte(s32, s32);

void func_806AE588(void) {
    s32 sel;
    s32 sw;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        behaviourSetAnimIds(0x1FD, 0x1FB, 0x1FC);
        func_80724CA4(3, 1);
        actorClearNodeFlag(D_807FBB40, 3);
        if (gCurrentMap == 0xA5) {
            D_807FBB40->unk132 = 1;
        }
    }
    func_8072881C(0, D_807FDC90->unk28);
    sel = D_807FBB40->unk154;
    if ((sel != 0x32) || (D_807FBB70.unk15 != 0)) {
        if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (sel != 0x37)) {
            if (((B2CE0ActorView134 *)D_807FBB40)->unk134 < -1) {
                func_8072D714(D_807FBB70.unk1FC, 0x202);
                D_807FBB40->unkC0 = 250.0f;
            } else {
                func_8072D714(D_807FBB70.unk1FC, 0x201);
                D_807FBB40->unkC0 = 200.0f;
            }
            ((B2CE0View90 *)D_807FDC90)->unk35 = 2;
            D_807FBB40->unk138 &= 0xFFFF7FFF;
        } else if (D_807FBB70.unk200 == 4) {
            func_8072DEA8(0x1FF, 0x31, D_807FBB70.unk1FC);
        } else if (D_807FBB70.unk200 == 5) {
            func_8072DEA8(0x200, 0x32, D_807FBB70.unk1FC);
            D_807FBB40->unkC0 = 220.0f;
        }
    }
    sel = D_807FBB40->unk154;
    sw = sel;
    switch (sel) {
    case 0x31:
        if ((D_807FBB40->unk155 != 0) || ((*(B2CE0Node **)D_807FBB40->unk4)->unk24 == 0.0f)) {
            actorSetDefaultState(0x1FB);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            D_807FBB40->unkC0 = 200.0f;
            D_807FBB40->unkB8 = 120.0f;
            D_807FBB40->unk155++;
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 3:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (D_807FBB40->unk155) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            actorScriptStart(D_807FBB40, 0x1FD);
            D_807FBB40->unk155++;
        case 1:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            if (D_807FBB40->unkB8 < 1.0f) {
                D_807FBB40->unk155++;
            }
            break;
        case 2:
            func_8072A450();
            if ((randomNonNegative() >> 0xF) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x1FB);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            actorScriptStart(D_807FBB40, 0x1FE);
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            D_807FBB40->unk132 = 2;
            break;
        case 3:
            D_807FBB40->unk132 = 1;
            break;
        case 4:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155 = 0;
        }
    case 0x23:
        if ((D_807FBB70.unk200 == 2) && (func_8072DE10(0x2710) != 0)) {
            D_807FBB40->unk154 = 0x27;
            D_807FBB40->unk155 = 0;
        }
        sel = D_807FBB40->unk154;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sw == 0x35) ? 2 : 3);
        actorMoveWithinZone(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
        break;
    case 0x37:
        D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if ((gCurrentMap == 0xA5) && (D_807FBB40->unk15F != 0)) {
                csModelStateSetFirstByte(0, 0xA);
            }
            sfxSpawnTableNodes(D_807FBB40);
            D_807FBB40->unk155++;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x1FB, sel);
        break;
    }
    sel = D_807FBB40->unk154;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(D_807FBB40->unk154, 1);
    default:
        func_8072C918(0x6400, 0x1FB, 0x1FC);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806AEE08(void) {
    if ((randomNonNegative() >> 15) % 1000 >= 0x3D5 && func_8072DE10(0xFA0) != 0 && !(((B2CE0View90 *)D_807FDC90)->unk1A & 0x80)) {
        D_807FBB40->unk154 = 0x25;
        D_807FBB40->unk155 = 0;
    }
}

void func_806AEE84(void) {
    B2CE0Sub178 *sp34;
    f32 sp30;

    sp34 = D_807FBB40->unk178;
    sp30 = D_807FBB40->unk4->unk38 / 0.15;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp34->unk0 = 0x2710;
        sp34->unk2 = 0x20;
        behaviourSetAnimIds(0x2AD, 0x2AB, 0x2AC);
        func_80724CA4(2, 1);
    }
    if (D_807FBB40->unk154 != 0x32 || D_807FBB70.unk15 != 0) {
        if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
            func_8072D714(D_807FBB70.unk1FC, 0x2AE);
            D_807FDC90->unk2C = 0x1C2;
        } else if (D_807FBB70.unk200 == 4) {
            func_8072DEA8(0x2B2, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
            D_807FBB40->unkB8 = 0.0f;
        } else if (D_807FBB70.unk200 == 5) {
            func_8072DEA8(0x2B1, 0x31, D_807FBB70.unk1FC, &D_807FBB70);
            D_807FBB40->unkB8 = 0.0f;
        }
    }
    switch (D_807FBB40->unk154) {
        case 0x31:
            if (D_807FBB40->unk155 != 0 || (*(B2CE0ModelHdr **)D_807FBB40->unk4)->unk24 == 0.0f) {
                actorSetDefaultState(0x2AB);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x11:
            func_80724E48(5);
            switch (D_807FBB40->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, 0);
                    actorScriptStart(D_807FBB40, 0x2B0);
                    D_807FBB40->unk155 = 1;
                case 1:
                    actorMoveWithinZone(0x11, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                    if (D_807FBB40->unkB8 < 1.0f) {
                        D_807FBB40->unk155++;
                    }
                    break;
                case 2:
                    func_806AEE08();
                    func_8072A450();
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3DF && (*(B2CE0ModelHdr **)D_807FBB40->unk4)->unk10 != 0x4C4) {
                        actorSetDefaultState(0x2AB);
                    }
            }
            break;
        case 0x27:
            switch (D_807FBB40->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, 0);
                    D_807FBB40->unkB8 = 0.0f;
                    actorScriptStart(D_807FBB40, 0x2B4);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            break;
        case 0x25:
            func_80724E48(0);
            switch (D_807FBB40->unk155) {
                case 0:
                    actorScriptStart(D_807FBB40, 0x2B3);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(D_807FBB40, 2);
                    projectileSpawnNodeEntry(0x32, 0x63, sp30 * 0.4, D_807FBB40->unkE6, 300.0f, 280.0f, D_807FBB40);
                    D_807FBB40->unk155 = 3;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            break;
        case 1:
            if (func_8072E54C() != 0) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
        case 0x23:
            if (D_807FBB70.unk200 == 2 && func_8072DE10(0x1388) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155 = 0;
            }
        case 0x10:
            func_806AEE08();
            func_80724E48(D_807FBB40->unk154 == 1 ? 2 : 0);
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(D_807FBB40->unk154 == 0x35 ? 2 : 3);
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC90->unkA, D_807FDC90->unkE, 0, 0.0f);
            break;
        case 0x37:
            switch (D_807FBB40->unk155) {
                case 0:
                    D_807FBB40->unkE6 += D_807FDC90->unk2C;
                    D_807FDC90->unk2C = D_807FDC90->unk2C * 0.95;
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    D_807FBB40->unk155++;
                case 2:
                    func_8072DC7C(5);
                    break;
                case 3:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            func_8072B7CC(0x2AB);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 0x24:
        case 0x25:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x6400, 0x2AB, 0x2AC);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806AF688(void) {
    s32 var;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        behaviourSetAnimIds(0x2C0, 0x2C1, 0x2C1);
        func_80724CA4(0xE, 1);
        ((B2CE0View90 *)D_807FDC90)->unk1A |= 0x800;
        D_807FBB40->unk60 |= 0x400;
    }
    func_806AE394(40.0f, 70.0f);
    if (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) {
        D_807FBB40->unk154 = 0x3A;
        D_807FBB40->unk155 = 0;
    }
    switch (D_807FBB40->unk154) {
        case 0x11:
            func_80724E48(2);
            switch (D_807FBB40->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, 0);
                    actorScriptStart(D_807FBB40, 0x2C0);
                    D_807FBB40->unk155++;
                case 1:
                    actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                    if (D_807FBB40->unkB8 < 1.0f) {
                        D_807FBB40->unk155++;
                    }
                    break;
                case 2:
                    func_8072A450();
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                        actorSetDefaultState(0x1FB);
                    }
                    break;
            }
            break;
        case 1:
            if (func_8072E54C() != 0) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
            func_80724E48(D_807FBB40->unk154 == 1 ? 2 : 0);
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(D_807FBB40->unk154 == 0x35 ? 2 : 3);
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC90->unkA, D_807FDC90->unkE, 0, 0.0f);
            break;
        case 0x37:
            D_807FBB40->unk154 = 0x40;
            break;
        default:
            func_8072B7CC(0x2C0);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->unk154, 1);
            break;
        case 0x31:
        case 0x37:
        case 0x40:
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_807149B8(s32);
void func_807149FC(s32);
void func_8071498C(void (*)());
void func_80714998(s32);
void func_80714950(s32);
void func_80714C08(void *, f32, B2CE0Actor *, s32, s32);
void effectTumbleBounceUpdate();
extern u8 D_8072073C;

void effectSpawnActorParticleBurst(u8 arg0) {
    s16 i;
    f32 temp;

    for (i = 0; i < 7; i++) {
        temp = D_807FBB40->unk4->unk38 / 0.15;
        func_807149B8(1);
        func_807149FC(10);
        func_8071498C(effectTumbleBounceUpdate);
        func_80714998(2);
        func_80714950(0);
        func_80714C08(&D_8072073C, temp * 0.15, D_807FBB40, arg0, 0);
    }
}

void func_806AFB58(void) {
    s32 sel;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk146 = -1;
        behaviourSetAnimIds(0x2D9, 0x2D7, 0x2D8);
        func_80724CA4(2, 1);
        D_807FBB40->unkEC = 0x1770;
    }
    if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (D_807FBB40->unk154 != 0x37)) {
        func_8072D714(D_807FBB70.unk1FC, 0x2DD);
        ((B2CE0View90 *)D_807FDC90)->unk35 = 2;
        D_807FBB40->unk138 &= 0xFFFF7FFF;
    } else if ((D_807FBB70.unk200 == 4) || (D_807FBB70.unk200 == 5)) {
        if (D_807FBB40->unk146 & 1) {
            ((B2CE0View90 *)D_807FDC90)->unk1E = 0xF;
            ((B2CE0View90 *)D_807FDC90)->unk1F = 0xF;
            D_807FBB40->unkEC = -1;
            actorSpawnChildAtNode(0xC2, 0x800, 1, 0x190);
            D_807FBB44->unk15F = 1;
            effectSpawnActorParticleBurst(1);
        } else if (D_807FBB40->unk146 & 2) {
            effectSpawnActorParticleBurst(2);
        }
        D_807FBB40->unk146 = D_807FBB40->unk146 * 2;
        func_8072DEA8(0x2DC, 0x31, D_807FBB70.unk1FC);
        ((B2CE0View90 *)D_807FDC90)->unk26 = 0;
        D_807FBB40->unkB8 = 0.0f;
    }
    sel = D_807FBB40->unk154;
    switch (D_807FBB40->unk154) {
    case 0x31:
        if ((D_807FBB40->unk155 != 0) || ((*(B2CE0Node **)D_807FBB40->unk4)->unk24 == 0.0f)) {
            actorSetDefaultState(0x2D7, sel);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
        break;
    case 0x11:
        func_80724E48(5);
        switch (D_807FBB40->unk155) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            actorScriptStart(D_807FBB40, 0x2D9);
            D_807FBB40->unk155++;
        case 1:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            if (D_807FBB40->unkB8 < 1.0f) {
                D_807FBB40->unk155++;
            }
            break;
        case 2:
            func_8072A450();
            if ((randomNonNegative() >> 0xF) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x2D7);
            }
            break;
        }
        break;
    case 0x27:
        if (D_807FBB40->unkEC < 0xFFFF) {
            func_8072E1A4(0xA, D_807FDC94);
        }
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            if (((f64)D_807FBB40->unk4->unk38 > 0.18) && ((randomNonNegative() >> 0xF) % 1000 >= 0x1F5)) {
                actorScriptStart(D_807FBB40, 0x2DB);
            } else {
                actorScriptStart(D_807FBB40, 0x2DA);
            }
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            D_807FBB40->unk132 = 2;
            break;
        case 3:
            D_807FBB40->unk132 = 1;
            break;
        case 4:
            actorSetDefaultState(0x2D7);
            break;
        }
        break;
    case 1:
        if (func_8072E54C((u32)D_807FBB40->unk154, sel) != 0) {
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155 = 0;
        }
    case 0x23:
        if ((D_807FBB70.unk200 == 2) && (func_8072DE10(D_807FBB40->unkEC) != 0)) {
            D_807FBB40->unk154 = 0x27;
            D_807FBB40->unk155 = 0;
        }
        sel = D_807FBB40->unk154;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sel == 0x35) ? 2 : 3);
        actorMoveWithinZone(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
        break;
    case 0x37:
        D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            D_807FBB40->unk155++;
        case 2:
            func_8072DC7C(8);
            break;
        case 3:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x2D7, sel);
        break;
    }
    sel = D_807FBB40->unk154;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(D_807FBB40->unk154, 1);
    default:
        func_8072C918(0x6400, 0x2D7, 0x2D8);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806B02EC(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        behaviourSetAnimIds(0, 0x31E, 0x31F);
    }
    actorPatrolFollowerUpdate(0x320, 0, 0);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806B0354(void) {
    behaviourFrameBegin();
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        func_8072D714(D_807FBB70.unk1FC, 0x37A);
        D_807FBB40->unk138 &= ~0x8000;
    }
    switch (D_807FBB40->unk154) {
        case 4:
            if (D_807FBB40->unk4->unk64 == 0x378) {
                D_807FBB40->unk154 = 0x23;
                D_807FBB40->unk155 = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0
                       && zoneCanReachPoint(D_807FBB40, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, D_807FDCA0) != 0) {
                actorScriptStart(D_807FBB40, 0x37B);
                D_807FBB40->unk154 = 0x23;
                D_807FBB40->unk155 = 0;
                effectSpawnOctagonRing(0.7f, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84);
            }
            break;
        case 0x23:
            switch (D_807FBB40->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, ((B2CE0View9C *)D_807FDC9C)->unkD);
                    D_807FBB40->unk155++;
                case 1:
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                        D_807FBB40->unk155++;
                        actorScriptStart(D_807FBB40, 0x379);
                        actorSetTargetSpeed(D_807FBB40, 0);
                    } else {
                        if (D_807FBB40->unk4->unk64 == 0x378) {
                            actorMoveWithinZone(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
                        } else {
                            func_8072E1A4(0xA, D_807FDC94);
                        }
                        if (actorIsTargetWithinDistance(0xC8) == 0
                            || zoneCanReachPoint(D_807FBB40, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, D_807FDCA0) == 0) {
                            actorScriptStart(D_807FBB40, 0x37C);
                            D_807FBB40->unk154 = 4;
                            D_807FBB40->unk155 = 0;
                            actorSetTargetSpeed(D_807FBB40, 0);
                        }
                    }
                    break;
                case 2:
                    actorMoveWithinZone(0, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                    break;
            }
            break;
        case 0x37:
            switch (D_807FBB40->unk155) {
                case 0:
                    actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    D_807FBB40->unk155++;
                case 2:
                    func_8072DC7C(0xA);
                    break;
                case 3:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(0x378);
            break;
    }
    func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 func_806B0770(void) {
    s32 found;
    s16 i;
    Actor *other;
    f32 dx;
    f32 dy;
    f32 dz;

    found = 0;
    for (i = 0; !found && i < gActiveActorCount; i++) {
        other = gActiveActors[i].actor;
        if (other->unk58 == 0x29) {
            dx = other->unk7C - D_807FBB40->unk7C;
            dy = other->unk80 - D_807FBB40->unk80;
            dz = other->unk84 - D_807FBB40->unk84;
            if (dx * dx + dy * dy + dz * dz < 10000.0f) {
                D_807FBB40->unk154 = 0x28;
                found = 1;
                D_807FBB40->unk155 = 0;
            }
        }
    }
    return found;
}

typedef struct B2CE0ActorTail {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[6];
    /* 0x138 */ s32 unk138;
} B2CE0ActorTail;

typedef struct B2CE0NodeHdr {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B2CE0NodeHdr;

typedef struct B2CE0Sub4Ptr {
    /* 0x0 */ B2CE0NodeHdr *unk0;
} B2CE0Sub4Ptr;

typedef struct B2CE0Sub64 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} B2CE0Sub64;

typedef struct B2CE0View90Ptr {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ s32 unk4;
} B2CE0View90Ptr;

s32 func_806B0770();
void func_8072DEA8(s32, s32, s32);
extern s32 gFrameCounter;
extern s32 D_807FBB4C;

void func_806B0848(void) {
    s32 sel;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        f64 d;
        f64 m = 255.0;

        d = (f64)D_807FBB40->unk4->unk38 / 0.15 * 100.0;
        if (d > m) ((B2CE0ActorTail *)D_807FBB40)->unk130 = m; else ((B2CE0ActorTail *)D_807FBB40)->unk130 = d;
        d = (f64)D_807FBB40->unk4->unk38 / 0.15 * 100.0;
        if (d > m) ((B2CE0ActorTail *)D_807FBB40)->unk131 = m; else ((B2CE0ActorTail *)D_807FBB40)->unk131 = d;
        behaviourSetAnimIds(0x35E, 0x35F, 0x360);
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        func_8072D714(D_807FBB70.unk1FC, 0x367);
        ((B2CE0ActorTail *)D_807FBB40)->unk138 &= 0xFFFF7FFF;
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x365, 0x31, D_807FBB70.unk1FC);
    } else if (D_807FBB70.unk200 == 5) {
        func_8072DEA8(0x366, 0x31, D_807FBB70.unk1FC);
    }
    sel = D_807FBB40->unk154;
    if (sel == 4) {
        D_807FBB40->unk154 = 1;
        sel = D_807FBB40->unk154;
    }
    switch (sel) {
        case 0x37:
            D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, D_807FBB40->unkEE, 7.0f);
            switch (D_807FBB40->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    D_807FBB40->unk155 = D_807FBB40->unk155 + 1;
                case 2:
                    func_8072DC7C(8);
                    break;
                case 3:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 0x31:
            if (D_807FBB40->unk155 != 0 || ((B2CE0Sub4Ptr *)D_807FBB40->unk4)->unk0->unk24 == 0.0f) {
                actorSetDefaultState(0x35F);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x27:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            switch (D_807FBB40->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, 0);
                    actorScriptStart(D_807FBB40, (gFrameCounter & 1) ? 0x362 : 0x361);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    D_807FBB40->unk132 = ((B2CE0Sub64 *)D_807FBB40->unk4)->unk64 == 0x362 ? 4 : 2;
                    break;
                case 3:
                    D_807FBB40->unk132 = ((B2CE0Sub64 *)D_807FBB40->unk4)->unk64 == 0x362 ? 8 : 1;
                    break;
                case 4:
                    D_807FBB40->unk132 = 1;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x28:
            func_8072E1A4(0xA, D_807FDC94);
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            switch (D_807FBB40->unk155) {
                case 0:
                    actorSetTargetSpeed(D_807FBB40, 0);
                    actorScriptStart(D_807FBB40, 0x363);
                    D_807FBB40->unk155 = 1;
                    break;
                case 2:
                    D_807FBB40->unk155++;
                    break;
                case 4:
                    ((B2CE0View90Ptr *)D_807FDC90)->unk4 = D_807FBB4C;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x11:
            if (func_806B0770() == 0) {
                switch (D_807FBB40->unk155) {
                    case 0:
                        actorSetTargetSpeed(D_807FBB40, 0);
                        actorScriptStart(D_807FBB40, 0x35E);
                        D_807FBB40->unk155 = D_807FBB40->unk155 + 1;
                    case 1:
                        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
                        if (D_807FBB40->unkB8 < 1.0f) {
                            D_807FBB40->unk155 = D_807FBB40->unk155 + 1;
                        }
                        break;
                    case 2:
                        func_8072A450();
                        if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                            actorSetDefaultState(0x35F);
                        }
                        break;
                }
            }
            break;
        case 1:
            if (func_8072E54C() != 0) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
        case 0x23:
            if (actorIsTargetWithinDistance(0x50) != 0 && func_8072DE10(0x1770) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155 = 0;
            }
        case 0x10:
            func_806B0770();
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC90->unkA, D_807FDC90->unkE, 0, 0.0f);
            break;
        default:
            func_8072B7CC(0x2D7);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x6400, 0x35F, 0x360);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
