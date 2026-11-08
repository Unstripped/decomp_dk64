#include "common.h"

typedef struct ModelSub_25F0 {
    u8 pad0[4];
    u16 unk4;
} ModelSub_25F0;

typedef struct Model_25F0 {
    f32 *unk0;
    u8 pad4[0x1C - 4];
    ModelSub_25F0 *unk1C;
    u8 pad20[0x34 - 0x20];
    f32 unk34;
    f32 unk38;
    u8 pad3C[0x64 - 0x3C];
    u16 unk64;
} Model_25F0;

struct MinecartCart;

typedef struct Actor_25F0 {
    u8 pad0[4];
    Model_25F0 *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xA4 - 0x88];
    f32 unkA4;
    u8 padA8[0xB8 - 0xA8];
    f32 unkB8;
    u8 padBC[0xC0 - 0xBC];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xE4 - 0xCC];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0xEC - 0xEA];
    s16 unkEC;
    s16 unkEE;
    s16 unkF0;
    u8 padF2[0x11C - 0xF2];
    struct Actor_25F0 *unk11C;
    u8 pad120[0x128 - 0x120];
    s16 unk128;
    u8 pad12A[0x132 - 0x12A];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x168 - 0x160];
    s16 unk168;
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    u8 pad16D[0x174 - 0x16D];
    void *unk174;
    struct MinecartCart *unk178;
} Actor_25F0;

typedef struct PlayerState_25F0 {
    u8 pad0[0x88];
    Actor_25F0 *unk88;
    u8 pad8C[0x104 - 0x8C];
    void *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} PlayerState_25F0;

typedef struct MinecartCart {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0x30 - 0x12];
    u8 *unk30;
    u8 *unk34;
    u8 pad38[0x3A - 0x38];
    u8 unk3A;
    u8 pad3B;
    s16 unk3C;
    u8 pad3E[0x42 - 0x3E];
    u8 unk42;
} MinecartCart;

typedef struct MinecartTargetState {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0x2C - 0x10];
    s16 unk2C;
} MinecartTargetState;

typedef struct Struct_DC90 {
    u8 pad0[0x26];
    s16 unk26;
    u8 pad28[0x35 - 0x28];
    u8 unk35;
} Struct_DC90;

typedef struct Struct_DC9C {
    u8 pad0[0xA];
    u8 unkA;
    u8 unkB;
    u8 padC;
    u8 unkD;
} Struct_DC9C;

typedef struct StructBB70_Sub {
    u8 pad0[2];
    s16 unk2;
    s16 unk4;
} StructBB70_Sub;

typedef struct StructBB70 {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x200 - 0x16];
    u8 unk200;
    u8 pad201[0x254 - 0x201];
    u8 unk254;
    u8 pad255[0x278 - 0x255];
    StructBB70_Sub *unk278;
} StructBB70;

typedef struct MinecartTrackPoint {
    f32 x;
    f32 y;
    f32 z;
} MinecartTrackPoint;

typedef struct MinecartPlayerPosition {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} MinecartPlayerPosition;

extern Actor_25F0 *D_807FBB40;
extern Actor_25F0 *D_807FBB44;
extern Actor_25F0 *D_807FBB4C;
extern PlayerState_25F0 *gActivePlayerState;
extern Actor_25F0 *D_807FDC94;
extern Struct_DC90 *D_807FDC90;
extern Struct_DC9C *D_807FDC9C;
extern StructBB70 D_807FBB70;
extern MinecartTrackPoint **D_807F5FD4;
extern MinecartPlayerPosition *gPlayerSlots;
extern u8 D_807FBB85;
extern u32 gFrameCounter;
extern s32 gCurrentMap;
extern s32 D_80717D4C;
extern void *D_8074E880[];
extern u8 D_80720120[];
extern s32 D_8072030C;
extern s32 gCamActor;
extern u8 D_80028BD0[];
extern u8 D_80028C34[];
extern u8 D_80028C40[];
extern u8 D_80028C48[];

void behaviourFrameBegin(void);
void actorScriptStart(Actor_25F0 *, s32);
void actorSpawn(s32, s32);
void actorCopyPoseAndScale(void *, void *, f32);
s16 controllerLookupStateByHash(void *);
void controllerAnimLoadStateAsset1(void *, s16);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 func_80724A20(void);
s16 mathAngleEaseToward(s16, s16, f32);
f32 func_80612794(s16);
f32 func_80612790(s16);
void actorUpdateModelMatrix(Actor_25F0 *, s32);
void actorGetOrSetNodeScale(Actor_25F0 *, s32, f32);
void func_807149FC(s32);
void func_80714C08(void *, f32, Actor_25F0 *, s32, s32);
void minecartApplyJunction(MinecartCart *, void *, s32, s32);
s32 randomNonNegative(void);
void func_80714950(s32);
void func_8071498C(s32 *);
void func_807149B8(s32);
void func_80714A28(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80724CA4(s32, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor_25F0 *, s16, u8, s16, u8);
void camStartShake(s32, s32, s32);
void func_8067E278(s32, s32);
void func_80724E48(s32);
s32 func_8072DE10(s32);
void minecartStartScriptNearPlayer(void);
void actorSpawnNodeEffectFacingCamera(s32, s32);
void actorApproachTargetSpeed(s32);
void minecartFollowTrack(MinecartCart *, s32, s32);
void actorGetNodePos(Actor_25F0 *, s32, f32 *, f32 *, f32 *);
void commandQueuePush(Actor_25F0 *, s16, s16, s16, s32, s32, s32, s32, s32);
void minecartPlayPassBySfx(MinecartCart *cart);
void minecartChooseBranchSide(MinecartCart *cart);
u8 *heapAlloc(s32);
f32 sqrtf(f32);
u32 randomLcgNext(void);
void camSetTarget(void *, void *, s32, s16, s32, s32, s32, s32, s32, s32, f32);
void camSetTargetScaled(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void actorDespawn(void *);
void func_80613C48(void *, s32, f32, f32);
void animSetSpeed(void *, s32, f32);
void animSetLoopMode(void *, s32, s32);
void animSetLoopLimit(void *, s32, s32);
void actorApplyGravity(void);
void actorApplyVelocity(void *);
void actorUpdateFloorContactAndTilt(void *, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleDistance(s16, s16);
s32 playerStateQueueCallback(s32, void *, s32);

void minecartFollowerBehaviour(void) {
    u8 followDist = 0x96;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x310);
        actorSpawn(0x11C, 0x4C);
        actorCopyPoseAndScale(D_807FBB44, D_807FBB40, 1.5 * D_807FBB40->unk4->unk38);
        D_807FBB44->unk11C = D_807FBB40;
        D_807FBB44->unk168 = -1;
        D_807FBB44->unk4->unk34 *= -1.0f;
        D_807FBB44->unkEC = 0x2BC;
        controllerAnimLoadStateAsset1(D_807FBB44, controllerLookupStateByHash(D_807FBB44));
        actorSpawn(0x11C, 0x4C);
        actorCopyPoseAndScale(D_807FBB44, D_807FBB40, 1.5 * D_807FBB40->unk4->unk38);
        D_807FBB44->unk11C = D_807FBB40;
        D_807FBB44->unk168 = 1;
        D_807FBB44->unkEC = 0x2BC;
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
        D_807FBB40->unk154 = 1;
        D_807FBB40->unkE8 = 0x12C;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x96;
    }
    if (func_80724A20()) {
        if (gActivePlayerState->unk88->unk154 == 5) {
            if (D_807FBB40->unk154 == 6) {
                D_807FBB40->unk154 = 5;
            } else if (D_807FBB40->unk154 == 5) {
                D_807FBB40->unk154 = 6;
            }
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        D_807FBB40->unk80 += 5.0f;
        if (D_807FBB40->unk155++ >= 0x10) {
            D_807FBB40->unk154 = 0x3B;
        }
        break;
    case 6:
        followDist = 0xFA;
        if ((gFrameCounter % D_807FDC9C->unkA) == 0) {
            sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x182, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            actorSpawn(0x11F, 0x50);
            D_807FBB44->unk11C = D_807FBB40;
            actorCopyPoseAndScale(D_807FBB44, D_807FBB40, 0.06f);
            D_807FBB40->unk15F++;
        }
        /* fallthrough */
    case 2:
    case 3:
    case 4:
    case 5:
        if (D_807FBB40->unk155 == 0xFF) {
            actorScriptStart(D_807FBB40, 0x311);
            D_807FBB40->unk154 = 1;
        }
        /* fallthrough */
    case 1:
        D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, (D_807FBB4C->unkE6 + 0x800) & 0xFFF, 8.0f);
        D_807FBB40->unk7C = (func_80612794(D_807FBB4C->unkE6) * followDist + D_807FBB4C->unk7C - D_807FBB40->unk7C) * 0.3 + D_807FBB40->unk7C;
        D_807FBB40->unk84 = (func_80612790(D_807FBB4C->unkE6) * followDist + D_807FBB4C->unk84 - D_807FBB40->unk84) * 0.3 + D_807FBB40->unk84;
        D_807FBB40->unk7C += 4.0f * func_80612794(gFrameCounter * 0x35);
        D_807FBB40->unk84 += 4.0f * func_80612790(gFrameCounter * 0x3E);
        D_807FBB40->unk80 = (func_80612794(gFrameCounter * 0x32) * 10.0f) + (gActivePlayerState->unk88->unkA4 + 30.0f);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 minecartSetTargetAheadOfPlayer(MinecartTargetState *targetState, f32 distanceFactor) {
    targetState->unkA = ((func_80612794(D_807FBB4C->unkE6) * (gActivePlayerState->unk88->unkB8 * distanceFactor)) + D_807FBB4C->unk7C);
    targetState->unkC = gActivePlayerState->unk88->unkA4;
    targetState->unkE = ((func_80612790(D_807FBB4C->unkE6) * (gActivePlayerState->unk88->unkB8 * distanceFactor)) + D_807FBB4C->unk84);
}

void minecartSpawnRandomParticle(void) {
    func_80714950(((randomNonNegative() >> 15) % 100) + 300);
    func_8071498C(&D_80717D4C);
    func_807149B8(1);
    func_80714A28(4);
    func_80714CC0(
        D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
        0.5f,
        ((randomNonNegative() >> 15) % 20) + (D_807FBB40->unk7C - 10.0f),
        D_807FBB40->unk80,
        ((randomNonNegative() >> 15) % 20) + (D_807FBB40->unk84 - 10.0f)
    );
}

void minecartFollowerChildBehaviour(void) {
    s32 padA;
    MinecartTargetState *targetState;
    s16 angleOffset;
    s32 padB;
    s32 padC;
    f32 interpT;
    f32 sinT;
    f32 lateralOffset;
    f32 vertOffset;
    Actor_25F0 *s2;
    s16 *p;
    f64 d;
    f32 var;
    f32 x;
    s16 v;

    s2 = D_807FBB40->unk11C;
    targetState = s2->unk174;
    angleOffset = D_807FBB40->unk168 * D_807FBB40->unkEC;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x59C, 0.0f, 0.0f);
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x96;
    }
    D_807FBB40->unkE6 = s2->unkE6;
    D_807FBB40->unk7C = (func_80612794(s2->unkE6 + angleOffset) * 47.0f + s2->unk7C - D_807FBB40->unk7C) * 0.3 + D_807FBB40->unk7C;
    D_807FBB40->unk84 = (func_80612790(s2->unkE6 + angleOffset) * 47.0f + s2->unk84 - D_807FBB40->unk84) * 0.3 + D_807FBB40->unk84;
    D_807FBB40->unk80 += (s2->unk80 - 10.0f - D_807FBB40->unk80) * 0.3;
    switch (s2->unk154) {
    case 2:
    case 3:
        if ((D_807FBB40->unk168 == 1 && s2->unk154 == 2) || (D_807FBB40->unk168 == -1 && s2->unk154 == 3)) {
            p = gActivePlayerState->unk88->unk174;
            minecartSpawnRandomParticle();
            switch (s2->unk155) {
            case 0:
                if (*p == 0) {
                    D_807FBB40->unk155 = 0;
                    actorScriptStart(D_807FBB40, 0x312);
                    s2->unk155 = 1;
                    minecartSetTargetAheadOfPlayer(targetState, 2.2f);
                }
                break;
            case 1:
                d = D_807FBB40->unk4->unk0[1] / 17.0;
                var = MIN(1.0, d);
                x = func_80612790(var * 2048.0f + 2048.0f) * 0.5 + 0.5;
                D_807FBB40->unk7C = (targetState->unkA - D_807FBB40->unk7C) * x + D_807FBB40->unk7C;
                D_807FBB40->unk80 = (D_807FBB40->unk80 + 10.0f) + ((gActivePlayerState->unk88->unkA4 - (D_807FBB40->unk80 + 10.0f)) * x);
                D_807FBB40->unk84 = (targetState->unkE - D_807FBB40->unk84) * x + D_807FBB40->unk84;
                if (D_807FBB4C->unk4->unk64 == 0x294 || (D_807FBB40->unk4->unk0[1] > 16.0f && D_807FBB40->unk4->unk0[1] < 18.0f)) {
                    D_807FBB40->unk132 = 1;
                } else {
                    D_807FBB40->unk132 = 0;
                }
                if (D_807FBB40->unk155 != 0) {
                    s2->unk155 = 0xFF;
                }
                break;
            }
        }
        break;
    case 4:
    case 5:
        if ((D_807FBB40->unk168 == 1 && s2->unk154 == 4) || (D_807FBB40->unk168 == -1 && s2->unk154 == 5)) {
            minecartSpawnRandomParticle();
            switch (s2->unk155) {
            case 0:
                targetState->unk2C = 0x46;
                s2->unk155 = 1;
                D_807FBB40->unk132 = 1;
                sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            case 1:
                minecartSetTargetAheadOfPlayer(targetState, 0.3f);
                v = targetState->unk2C;
                targetState->unk2C = v - 1;
                if (v != 0) {
                    interpT = func_80612790(targetState->unk2C / 70.0 * 2048.0 + 2048.0) * 0.5 + 0.5;
                    sinT = func_80612794(2048.0f * interpT);
                    lateralOffset = func_80612794(interpT * 1536.0f + 1024.0f) * (D_807FBB40->unk168 * -110);
                    vertOffset = (func_80612790(interpT * 4096.0f) * 0.5 + 0.5) * 50.0 + -30.0;
                    D_807FBB40->unk7C = ((func_80612794(D_807FBB4C->unkE6 - 0x400) * lateralOffset + targetState->unkA) - D_807FBB40->unk7C) * sinT + D_807FBB40->unk7C;
                    D_807FBB40->unk80 += (gActivePlayerState->unk88->unkA4 + vertOffset - D_807FBB40->unk80) * sinT;
                    D_807FBB40->unk84 = ((func_80612790(D_807FBB4C->unkE6 - 0x400) * lateralOffset + targetState->unkE) - D_807FBB40->unk84) * sinT + D_807FBB40->unk84;
                    if (targetState->unk2C < 0x10) {
                        D_807FBB40->unk132 = 0;
                    }
                } else {
                    s2->unk155 = 0xFF;
                }
                break;
            }
            if (D_807FBB40->unk168 == 1) {
                D_807FBB40->unkE4 = mathAngleEaseToward(D_807FBB40->unkE4, 0xC00, 7.0f);
            } else {
                D_807FBB40->unkE4 = mathAngleEaseToward(D_807FBB40->unkE4, 0x400, 7.0f);
            }
        }
        break;
    case 6:
        if (s2->unk155 == 0) {
            targetState->unk2C = D_807FDC9C->unkB;
            s2->unk155 = 1;
        }
        if (D_807FBB40->unk168 == 1) {
            D_807FBB40->unkE4 = mathAngleEaseToward(D_807FBB40->unkE4, 0xC00, 16.0f);
        } else {
            D_807FBB40->unkE4 = mathAngleEaseToward(D_807FBB40->unkE4, 0x400, 16.0f);
        }
        v = targetState->unk2C;
        if (v != 0) {
            targetState->unk2C = v - 1;
        } else {
            s2->unk155 = 0xFF;
        }
        if (D_807FBB40->unk155 == 0 && s2->unk15F == 4) {
            gActivePlayerState->unk1F0 |= 0x10000000;
            D_807FBB40->unk15F = 0xB4;
            D_807FBB40->unk155++;
        }
        D_807FBB40->unkEC = mathAngleEaseToward(D_807FBB40->unkEC, 0x64, 10.0f);
        break;
    case 0x3B:
        actorDespawn(D_807FBB40);
        break;
    case 1:
        break;
    }
    if (s2->unk154 == 6) {
        if (D_807FBB40->unk15F != 0) {
            D_807FBB40->unk15F -= 0xC;
            camSetTarget(gActivePlayerState->unk104, gActivePlayerState->unk88, 4, (D_807FBB40->unk15F << 12) / 360, 0x64, 0, 5, 0x23, 0x14, 0, 0.2f);
        }
    }
    if (s2->unk154 != 6) {
        if (D_807FBB40->unkE4 != 0) {
            D_807FBB40->unkE4 = mathAngleEaseToward(D_807FBB40->unkE4, 0, 8.0f);
            D_807FBB40->unkEC = mathAngleEaseToward(D_807FBB40->unkEC, 0x2BC, 10.0f);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void minecartUpdateFollower(void) {
    f32 d;
    f32 dist;
    MinecartCart *playerCart;
    s32 a;
    s16 pointX;
    s16 pointZ;

    playerCart = gActivePlayerState->unk88->unk174;
    pointX = D_807F5FD4[D_807FBB40->unk15F][D_807FBB40->unk168].x;
    pointZ = D_807F5FD4[D_807FBB40->unk15F][D_807FBB40->unk168].z;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x5FF, 0.0f, 0.0f);
        animSetSpeed(D_807FBB40, 0, 1.0f);
        animSetLoopMode(D_807FBB40, 0, 0);
        animSetLoopLimit(D_807FBB40, 0, -1);
        D_807FBB40->unk144 = 0x24;
        if (D_807FBB40->unk11C->unk15F == 1) {
            D_807FBB40->unk15F = *playerCart->unk34 & ~0xC0;
        } else {
            switch (*playerCart->unk34 & ~0xC0) {
            case 1:
            case 2:
                D_807FBB40->unk15F = (D_807FBB40->unk11C->unk15F ^ 1) + 1;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                D_807FBB40->unk15F = (D_807FBB40->unk11C->unk15F % 4) + 3;
                break;
            case 7:
            case 8:
                D_807FBB40->unk15F = (D_807FBB40->unk11C->unk15F ^ 1) + 7;
                break;
            }
        }
        a = playerCart->unk10 - 2;
        D_807FBB40->unk168 = MAX(0, a);
        D_807FBB40->unkB8 = 1100.0f;
        D_807FBB40->unkC0 = 400.0f;
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        D_807FBB40->unkC4 = -10.0f;
        D_807FBB40->unkC8 = -200.0f;
        D_807FBB40->unkF0 = 0xB4;
        D_807FBB40->unkEC = 0;
    }
    if (gFrameCounter % 3 == 0) {
        func_807149B8(1);
        func_80714CC0(D_80720120, 1.0f, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84);
    }
    D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, mathAngleBetweenPoints2D(pointX, pointZ, D_807FBB40->unk7C, D_807FBB40->unk84), 6.0f);
    D_807FBB40->unkEE = D_807FBB40->unkE6;
    actorApplyGravity();
    actorApplyVelocity(D_807FBB40);
    actorUpdateFloorContactAndTilt(D_807FBB40, 2.0 * func_80612794(gFrameCounter * 0x64) + 10.0);
    if ((pointX - D_807FBB40->unk7C) * (pointX - D_807FBB40->unk7C) + (pointZ - D_807FBB40->unk84) * (pointZ - D_807FBB40->unk84) < 1600.0f) {
        D_807FBB40->unk168++;
    }
    if (D_807FBB85 != 0 || --D_807FBB40->unkF0 == 0) {
        if (D_807FBB40->unk11C != NULL) {
            D_807FBB40->unk11C->unk15F--;
        }
        if (D_807FBB40->unk11C == NULL || D_807FBB40->unk11C->unk15F == 0) {
            if (gActivePlayerState->unk1F0 & 0x10000000) {
                gActivePlayerState->unk1F0 &= ~0x10000000;
                camSetTargetScaled(gActivePlayerState->unk104, gActivePlayerState->unk88, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
            }
        }
        func_8067E278(0, 1);
        actorDespawn(D_807FBB40);
    }
    dist = D_807FBB40->unk7C - gPlayerSlots->unk210;
    dist = dist * dist;
    d = D_807FBB40->unk80 - gPlayerSlots->unk214;
    dist = d * d + dist;
    d = D_807FBB40->unk84 - gPlayerSlots->unk218;
    dist = d * d + dist;
    switch (D_807FBB40->unkEC) {
    case 0:
    case 2:
        if (dist < 6400.0f) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x128, 0xFF, 0x7F, 0);
            D_807FBB40->unkEC++;
        }
        break;
    case 1:
        if (dist > 10000.0f) {
            D_807FBB40->unkEC++;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void minecartStartScriptNearPlayer(void) {
    if (D_807FBB40->unk155 != 0) {
        return;
    }
    if (func_8072DE10(10000) != 0 ||
        (D_807FDC94->unk7C - D_807FBB40->unk7C) * (D_807FDC94->unk7C - D_807FBB40->unk7C) +
        (D_807FDC94->unk80 - D_807FBB40->unk80) * (D_807FDC94->unk80 - D_807FBB40->unk80) +
        (D_807FDC94->unk84 - D_807FBB40->unk84) * (D_807FDC94->unk84 - D_807FBB40->unk84) < 2500.0f) {
        actorScriptStart(D_807FBB40, 0x280);
    }
}

void minecartChooseBranchSide(MinecartCart *cart) {
    PlayerState_25F0 *c = D_807FDC94->unk174;
    MinecartCart *d = c->unk88->unk174;
    u8 b = *d->unk34 - 0x10;

    if (b < *cart->unk34) {
        cart->unk42 = 1;
    } else if (*cart->unk34 < b) {
        cart->unk42 = 2;
    } else {
        cart->unk42 = 0;
    }
}

void minecartAdjustTargetSpeed(void) {
    u16 targetAngle;
    PlayerState_25F0 *comp = D_807FDC94->unk174;

    targetAngle = D_807FBB40->unk4->unk1C->unk4;
    if (targetAngle >= 0x47D1 && targetAngle < 0xB830) {
        D_807FDC90->unk26 = MAX(9, D_807FDC90->unk26 - 5);
    } else if (targetAngle < 0x3830 || targetAngle >= 0xC7D1) {
        D_807FDC90->unk26 = MIN(D_807FDC9C->unkD, D_807FDC90->unk26 + 5);
    } else {
        D_807FDC90->unk26 = comp->unk88->unkB8;
    }
}

void minecartPlayPassBySfx(MinecartCart *cart) {
    f32 d;
    f32 dist = D_807FBB40->unk7C - D_807FDC94->unk7C;
    dist = dist * dist;
    d = D_807FBB40->unk80 - D_807FDC94->unk80;
    dist = d * d + dist;
    d = D_807FBB40->unk84 - D_807FDC94->unk84;
    dist = sqrtf(dist + d * d);
    if (dist < 200.0f) {
        if (++cart->unk3A >= 9) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1F, 0xFF, (127.0f - (dist - cart->unk3C)), 0);
            cart->unk3A = randomLcgNext() / 4294967295.0 * 3.0;
        }
    }
    cart->unk3C = dist;
}

void minecartUpdateObstacleType1(void) {
    MinecartCart *cart;
    StructBB70_Sub *sub;
    f32 nodePosZ;
    f32 nodePosY;
    f32 nodePosX;
    u8 *alloc;
    cart = D_807FBB40->unk178;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        D_807FDC90->unk35 = 6;
    }
    if (D_807FBB70.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
        camStartShake(gCamActor, 0xA, 0x14);
        D_807FBB40->unk154 = 0x40;
        func_8067E278(0, 1);
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0) {
            sub = D_807FBB70.unk278;
            alloc = heapAlloc(2);
            alloc[0] = sub->unk2;
            alloc[1] = 0xFF;
            cart->unk34 = alloc;
            cart->unk10 = sub->unk4;
            D_807FDC90->unk26 = 0x46;
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154++;
        } else {
            func_80724E48(1);
            minecartStartScriptNearPlayer();
            actorUpdateModelMatrix(D_807FBB40, 0);
            return;
        }
    case 1:
        func_80724E48(1);
        minecartStartScriptNearPlayer();
        minecartAdjustTargetSpeed();
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        actorApproachTargetSpeed(0x200);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        actorGetNodePos(D_807FBB40, 5, &nodePosX, &nodePosY, &nodePosZ);
        commandQueuePush(D_807FBB40, nodePosX, nodePosY, nodePosZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        minecartPlayPassBySfx(cart);
        return;
    case 2:
        D_807FBB40->unk154 = 0x40;
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    default:
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    }
}

void minecartUpdateObstacleType2(void) {
    MinecartCart *cart;
    StructBB70_Sub *sub;
    f32 node2Z;
    f32 node2Y;
    f32 node2X;
    f32 node1Z;
    f32 node1Y;
    f32 node1X;
    u8 *alloc;
    s32 pad0, pad1, pad2;

    cart = D_807FBB40->unk178;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if ((gCurrentMap == 0x4D) || (gCurrentMap == 0x81) || (gCurrentMap == 0x82)) {
            actorGetOrSetNodeScale(D_807FBB40, 1, 50.0f);
        }
        func_807149B8(1);
        func_807149FC(-1);
        func_80714C08(&D_8072030C, 0.14f, D_807FBB40, 0xB, 2);
        D_807FBB40->unk154 = 0;
    }
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) {
        func_8067E278(0, 1);
        D_807FBB40->unk154 = 0x40;
        camStartShake(gCamActor, 0xA, 0x14);
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0) {
            sub = D_807FBB70.unk278;
            alloc = heapAlloc(4);
            alloc[0] = sub->unk2;
            alloc[1] = 0xFF;
            cart->unk30 = alloc;
            cart->unk34 = alloc;
            cart->unk10 = 1;
            D_807FDC90->unk26 = sub->unk4;
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154++;
        } else {
            actorUpdateModelMatrix(D_807FBB40, 0);
            return;
        }
    case 1:
        if ((gCurrentMap == 0x4D) || (gCurrentMap == 0x81) || (gCurrentMap == 0x82)) {
            minecartChooseBranchSide(cart);
            minecartApplyJunction(cart, D_80028BD0, 0, 3);
            actorGetNodePos(D_807FBB40, 1, &node1X, &node1Y, &node1Z);
            actorGetNodePos(D_807FBB40, 2, &node2X, &node2Y, &node2Z);
        }
        actorApproachTargetSpeed(0x200);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        if ((D_807FBB40->unk154 == 2) && ((gCurrentMap == 0x4D) || (gCurrentMap == 0x81) || (gCurrentMap == 0x82))) {
            D_807FBB40->unk154 = 1;
            cart->unk34--;
        }
        actorGetNodePos(D_807FBB40, 5, &node1X, &node1Y, &node1Z);
        commandQueuePush(D_807FBB40, node1X, node1Y, node1Z, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        minecartPlayPassBySfx(cart);
        return;
    case 2:
        D_807FBB40->unk154 = 0x40;
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    default:
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    }
}

void minecartUpdateObstacleType3(void) {
    MinecartCart *cart;
    s32 pad;
    f32 nodePosZ;
    f32 nodePosY;
    f32 nodePosX;
    PlayerState_25F0 *playerState;
    f64 t1;
    f64 t2;

    cart = D_807FBB40->unk178;
    behaviourFrameBegin();
    playerState = D_807FDC94->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk144 = 0x3C;
        D_807FDC90->unk35 = 2;
        func_807149B8(1);
        func_807149FC(-1);
        func_80714C08(&D_8072030C, 0.14f, D_807FBB40, 0xB, 2);
    }
    if (D_807FBB70.unk200 == 4) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
        camStartShake(gCamActor, 0xA, 0x14);
        t1 = D_807FBB40->unkB8 * 1.2;
        D_807FBB40->unkB8 = -(t1 > 0.0 ? t1 : -t1);
        playerStateQueueCallback(0x34, D_807FBB40, 0);
    }
    func_80724A20();
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0) {
            switch (gCurrentMap) {
            case 0x37:
                cart->unk34 = D_80028C40;
                break;
            case 0x6A:
                cart->unk34 = D_80028C48;
                break;
            default:
                cart->unk34 = D_80028C34;
            }
            cart->unk10 = 1;
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154++;
            goto case_1;
        } else {
            actorUpdateModelMatrix(D_807FBB40, 0);
            return;
        }
case_1:
    case 1:
        if (mathAngleDistance(mathAngleBetweenPoints2D(D_807FBB4C->unk7C, D_807FBB4C->unk84, D_807FBB40->unk7C, D_807FBB40->unk84), D_807FBB40->unkE6) >= 0x201 &&
            (D_807FBB40->unk7C - D_807FBB4C->unk7C) * (D_807FBB40->unk7C - D_807FBB4C->unk7C) + (D_807FBB40->unk84 - D_807FBB4C->unk84) * (D_807FBB40->unk84 - D_807FBB4C->unk84) < 22500.0f) {
            D_807FDC90->unk26 = 0;
        } else {
            t2 = playerState->unk88->unkB8 * 1.4;
            D_807FDC90->unk26 = MIN(MAX(t2, 45.0), 90.0);
        }
        actorApproachTargetSpeed(0x200);
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        actorGetNodePos(D_807FBB40, 5, &nodePosX, &nodePosY, &nodePosZ);
        commandQueuePush(D_807FBB40, nodePosX, nodePosY, nodePosZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        if (D_807FBB4C->unk154 == 0x70 || cart->unk10 == 0x90) {
            D_807FBB40->unk154++;
        }
        return;
    case 2:
        func_8067E278(0, 1);
        D_807FBB40->unk154 = 0x40;
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    default:
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    }
}
