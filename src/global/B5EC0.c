#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern s32 D_8071FFA0;

s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void effectSpawnScatterRandom(void *, s32, f32, s32, s32, s32, s32, s32, s32);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, Actor *, u8);

typedef struct B5EC0Sub4 {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} B5EC0Sub4;

// File-local view of the current actor (D_807FBB40) for fields Actor lacks or types differently.
typedef struct B5EC0Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ B5EC0Sub4 **unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x54];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[2];
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u8 pad13C[0x18];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
} B5EC0Actor;

typedef struct B5EC0View90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x19];
    /* 0x35 */ u8 unk35;
} B5EC0View90;

typedef struct B5EC0View9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} B5EC0View9C;

typedef struct B5EC0View94 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
} B5EC0View94;

void actorSpawnGroundEffectAtNode(u8 nodeIndex) {
    f32 x;
    f32 y;
    f32 z;

    actorGetNodePos(D_807FBB40, nodeIndex, &x, &y, &z);
    effectSpawnScatterRandom(&D_8071FFA0, 0, 1.0f, 3, 5, 0x28, x, D_807FBB40->unkA4, z);
    actorSpawnEffectChild(x, D_807FBB40->unkA4, z, 0.05f, 0.04f, D_807FBB40, 0);
}

s32 randomNonNegative(void);

void func_806B1290(void) {
    if (((B5EC0View90 *)D_807FDC90)->unk18 >= 0x65
        && (((((B5EC0View90 *)D_807FDC90)->unk1A & 0x80) && (randomNonNegative() >> 15) % 1000 >= 0x3D5)
            || ((randomNonNegative() >> 15) % 1000 >= 0x3DF && (D_807FBB40->unk60 & 0x100)))) {
        ((B5EC0Actor *)D_807FBB40)->unk154 = 0x28;
        ((B5EC0Actor *)D_807FBB40)->unk155 = 0;
    }
}

extern u8 D_807FBD70;

s32 func_8072DE10(s32);

void func_806B1348(void) {
    if (((B5EC0View90 *)D_807FDC90)->unk18 >= 0x65 && D_807FBD70 == 2 && func_8072DE10(0x2710) != 0) {
        ((B5EC0Actor *)D_807FBB40)->unk154 = 0x27;
        ((B5EC0Actor *)D_807FBB40)->unk155 = 0;
    }
}

extern ActorGlobalState D_807FBB70;
extern s32 gCurrentMap;

void behaviourFrameBegin(void);
void behaviourSetAnimIds(s32, s32, s32);
void func_80724CA4(s32, s32);
void func_8072D714(s32, s32);
void func_8072DEA8(s32, s32, s32);
void actorSetDefaultState();
void actorScriptStart(void *, s32);
s32 camIsCutsceneActive(void);
void actorSpawnGroundEffectAtNode(u8);
s16 mathAngleEaseToward(s16, s16, f32);
void func_80724E48();
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(Actor *, s32);
void func_8072A450(void);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxSpawnTableNodes(Actor *);
void actorClearNodeFlag(Actor *, s32);
void func_8072DC7C(s32);
s32 func_8072E54C();
void patrolPathStep(s32, s32);
void enemyAggroStateUpdate(s32, s32, s32);
void actorUpdateModelMatrix(Actor *, s32);
void func_8072B7CC();

void func_806B13B4(u8 arg0) {
    s32 v;
    s32 sel;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (gCurrentMap == 0x43) {
            ((B5EC0View9C *)D_807FDC9C)->unkD = 0x82;
            D_807FDC98->unk46 |= 0x40;
        }
        behaviourSetAnimIds(0x205, 0x203, 0x204);
        func_80724CA4(2, 1);
    }
    sel = D_807FBB40->state;
    if (sel == 0x27) {
        ((B5EC0Actor *)D_807FBB40)->unk132 = 2;
        sel = D_807FBB40->state;
    } else if (sel != 0x32) {
        ((B5EC0Actor *)D_807FBB40)->unk132 = 1;
        sel = D_807FBB40->state;
    }
    if (sel != 0x32 || D_807FBB70.unk15 != 0) {
        if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && sel != 0x37) {
            if (((B5EC0Actor *)D_807FBB40)->unk134 < -1) {
                func_8072D714(D_807FBB70.unk1FC, 0x20C);
                ((B5EC0Actor *)D_807FBB40)->unkC0 = 250.0f;
            } else {
                func_8072D714(D_807FBB70.unk1FC, 0x20B);
                ((B5EC0Actor *)D_807FBB40)->unkC0 = 200.0f;
            }
            ((B5EC0View90 *)D_807FDC90)->unk35 = 2;
            D_807FBB40->unk138 &= 0xFFFF7FFF;
            sel = D_807FBB40->state;
        } else if (D_807FBB70.unk200 == 4) {
            func_8072DEA8(0x209, 0x31, D_807FBB70.unk1FC);
            sel = D_807FBB40->state;
        } else if (D_807FBB70.unk200 == 5) {
            func_8072DEA8(0x20A, 0x32, D_807FBB70.unk1FC);
            ((B5EC0Actor *)D_807FBB40)->unkC0 = 220.0f;
            D_807FBB40->unk132 = 8;
            sel = D_807FBB40->state;
        }
    }
    sel = D_807FBB40->state;
    switch (sel) {
    case 0x31:
        if (((B5EC0Actor *)D_807FBB40)->unk155 != 0 || (*((B5EC0Actor *)D_807FBB40)->unk4)->unk24 == 0.0f) {
            actorSetDefaultState(0x203, sel);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        ((B5EC0Actor *)D_807FBB40)->unkE6 = mathAngleEaseToward(((B5EC0Actor *)D_807FBB40)->unkE6, ((B5EC0Actor *)D_807FBB40)->unkEE, 7.0f);
        switch (((B5EC0Actor *)D_807FBB40)->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            ((B5EC0Actor *)D_807FBB40)->unk132 = 1;
            actorSetDefaultState(0x203);
            break;
        }
        break;
    case 0x28:
        switch (((B5EC0Actor *)D_807FBB40)->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x20D);
            ((B5EC0Actor *)D_807FBB40)->unk155 = 1;
            break;
        case 2:
            actorSpawnGroundEffectAtNode(1);
            actorSpawnGroundEffectAtNode(2);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1D5, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x25A, 0xFF, 0x7F, 1);
            ((B5EC0Actor *)D_807FBB40)->unk155 = 3;
            break;
        case 4:
            actorSetDefaultState(0x203, sel);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (((B5EC0Actor *)D_807FBB40)->unk155) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            actorScriptStart(D_807FBB40, 0x205);
            ((B5EC0Actor *)D_807FBB40)->unk155 += 1;
        case 1:
            actorMoveWithinZone(D_807FBB40->state, ((B5EC0View94 *)D_807FDC94)->unk7C, ((B5EC0View94 *)D_807FDC94)->unk84, 0x200, 0.0f);
            if (((B5EC0Actor *)D_807FBB40)->unkB8 < 1.0f) {
                ((B5EC0Actor *)D_807FBB40)->unk155 += 1;
            }
            break;
        case 2:
            func_8072A450();
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x203);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(D_807FBB40->state, ((B5EC0View94 *)D_807FDC94)->unk7C, ((B5EC0View94 *)D_807FDC94)->unk84, 0x200, 0.0f);
        switch (((B5EC0Actor *)D_807FBB40)->unk155) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            if ((randomNonNegative() >> 15) % 1000 >= 0x259) {
                actorScriptStart(D_807FBB40, 0x208);
                ((B5EC0Actor *)D_807FBB40)->unk155 = 5;
            } else {
                actorScriptStart(D_807FBB40, 0x206);
                ((B5EC0Actor *)D_807FBB40)->unk155 = 1;
            }
            break;
        case 1:
            if (((B5EC0View90 *)D_807FDC90)->unk1A & 0x100) {
                actorClearNodeFlag(D_807FBB40, 2);
                actorClearNodeFlag(D_807FBB40, 3);
            }
            break;
        case 2:
            if (((B5EC0View90 *)D_807FDC90)->unk1A & 0x100) {
                ((B5EC0View90 *)D_807FDC90)->unk1A &= 0xFEFF;
                actorScriptStart(D_807FBB40, 0x207);
                ((B5EC0Actor *)D_807FBB40)->unk155 = 3;
            } else {
                actorSetDefaultState(0x203);
            }
            break;
        case 3:
            if (((B5EC0View90 *)D_807FDC90)->unk1A & 0x100) {
                ((B5EC0View90 *)D_807FDC90)->unk1A &= 0xFEFF;
                actorScriptStart(D_807FBB40, 0x208);
                ((B5EC0Actor *)D_807FBB40)->unk155 = 5;
            }
            break;
        case 4:
            actorSetDefaultState(0x203);
            break;
        case 5:
            ((B5EC0Actor *)D_807FBB40)->unk132 = 4;
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->state = 0x11;
            ((B5EC0Actor *)D_807FBB40)->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        if (camIsCutsceneActive() == 0) {
            func_806B1290();
            func_806B1348();
        }
        func_80724E48((u8)(D_807FBB40->state == 1 ? 2 : 0));
        actorMoveWithinZone(D_807FBB40->state, ((B5EC0View94 *)D_807FDC94)->unk7C, ((B5EC0View94 *)D_807FDC94)->unk84, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((u8)(sel == 0x35 ? 2 : 3), sel);
        actorMoveWithinZone(D_807FBB40->state, ((B5EC0View90 *)D_807FDC90)->unkA, ((B5EC0View90 *)D_807FDC90)->unkE, 0, 0.0f);
        break;
    case 0x37:
        ((B5EC0Actor *)D_807FBB40)->unkE6 = mathAngleEaseToward(((B5EC0Actor *)D_807FBB40)->unkE6, ((B5EC0Actor *)D_807FBB40)->unkEE, 7.0f);
        switch (((B5EC0Actor *)D_807FBB40)->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if (arg0 != 0) {
                sfxSpawnTableNodes(D_807FBB40);
            }
            ((B5EC0Actor *)D_807FBB40)->unk155 += 1;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            ((B5EC0Actor *)D_807FBB40)->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x203);
        break;
    }
    sel = D_807FBB40->state;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(D_807FBB40->state, 1);
    default:
        enemyAggroStateUpdate(0x6400, 0x203, 0x204);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, u8, f32);

void actorSetAnimStartFrame(u8 frame) {
    animSetLoopLimit(D_807FBB40, 0, 1);
    animSetFinished(D_807FBB40, 0, 1);
    animSetFrameAndSubframe(D_807FBB40, 0, frame, 0.0f);
}

extern u8 D_8076A0AB;
extern s32 D_80750600[];

s32 func_805FF000(u8);
s32 func_805FF030(u8, s32);
void func_806B13B4(u8);
s32 flagGridSumRows(s32, s32, s32, s32);

void func_806B1DD4(u8 mode) {
    u8 flag;
    s32 temp;

    if (!(D_807FBB40->unk60 & 0x10)) {
        flag = 0;
        temp = func_805FF000(D_8076A0AB);
        if (temp != 9 && temp != 0xA) {
            temp = func_805FF030(D_8076A0AB, 1);
            flag = flagGridSumRows(0x1D5, temp, temp, D_80750600[mode]) == 0;
        }
        actorSetAnimStartFrame(flag != 0 ? mode : 5);
        ((B5EC0Actor *)D_807FBB40)->unk15F = flag;
    }
    func_806B13B4(((B5EC0Actor *)D_807FBB40)->unk15F);
}

void func_806B1EA8(void) {
    func_806B1DD4(4);
}

void func_806B1EC8(void) {
    func_806B1DD4(2);
}

void func_806B1EE8(void) {
    func_806B1DD4(3);
}

void func_806B1F08(void) {
    func_806B1DD4(0);
}

void func_806B1F28(void) {
    func_806B1DD4(1);
}
