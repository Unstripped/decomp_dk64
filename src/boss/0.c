#include "common.h"
#include "actor.h"
#include "proto/boss/0.h"
#include "proto/boss/3840.h"
#include "proto/global/119370.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/63EC0.h"
#include "proto/global/8CA50.h"
#include "proto/global/8F050.h"

typedef struct BossByteTable6 {
    u8 bytes[6];
} BossByteTable6;

typedef struct BossActorPos {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} BossActorPos;

struct BossA_Struct_807FBB40;
extern struct BossA_Struct_807FBB40 *gCurrentActor;
extern BossByteTable6 D_8003598C;
extern u8 effectDecelDriftFadeUpdate;
extern u8 sEffectSparkConfig;

void tagBarrelSpawnNodeSmokePuffs(void *, s32, f32); // FAKE: callee prototype steer

void bossArmydilloSpawnSmoke(void) {
    BossByteTable6 smokeBones;
    s16 i;

    for (i = 0; i < 6; i++) {
        smokeBones = D_8003598C;
        tagBarrelSpawnNodeSmokePuffs(gCurrentActor, smokeBones.bytes[i], 3.0f);
    }

    for (i = 0; i < 12; i++) {
        effectSetCallback((void *)(s32)&effectDecelDriftFadeUpdate);
        effectSetSpeed(i);
        effectSetDepth(1);
        effectSetColor(0x8C, 0x8C, 0x8C, 0xFF);
        effectSetMode(3);
        effectCreateAtPosition(&sEffectSparkConfig, 2.5f, ((BossActorPos *)gCurrentActor)->unk7C, ((BossActorPos *)gCurrentActor)->unk80 + 40.0f, ((BossActorPos *)gCurrentActor)->unk84);
    }
}

typedef struct BossA_Struct_8002413C_Template {
    s8 x;
    s8 y;
    s8 z;
    u8 pad3;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
} BossA_Struct_8002413C_Template;

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[4];
    ActorSub4 *sub;
    u8 pad8[0xE6 - 8];
    s16 unkE6;
    u8 padE8[0x146 - 0xE8];
    s16 unk146;
} BossA_Struct_807FBB40;

extern s32 gCurrentMap;
extern BossA_Struct_807FBB40 *gCurrentActor;
extern u8 D_800358D8[5];
extern BossA_Struct_8002413C_Template D_800358E0[][5];
extern u8 D_80035994[8];

void func_80724D28(s16, s16);
void func_80724DB0(s16, s16);
void func_80724CA4(s16, s16);

void bossArmydilloInitArena(void) {
    s32 pad[4];
    u8 mode;
    s16 i;
    ActorSub4 *sub;
    BoneVector *v0;
    BoneVector *a0;
    BoneRotation *a1;
    BossA_Struct_8002413C_Template *t;

    if (gCurrentMap == 8) {
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        if (flagGet(0x68, 2) != 0) {
            mode = 1;
            gCurrentActor->unk146 = 3;
        }
    }
    func_80724D28(1, 0xD);
    func_80724DB0(1, 5);
    func_80724CA4(1, 5);

    sub = gCurrentActor->sub;
    t = D_800358E0[mode];
    v0 = sub->boneOffsets;
    a0 = sub->boneScales;
    a1 = sub->boneRotations;

    for (i = 0; i < 5; i++) {
        v0->bone = D_800358D8[i];
        v0->lastBone = 0xFF;
        v0->x = t[i].x;
        v0->y = t[i].y;
        v0->z = t[i].z;

        a0->bone = D_800358D8[i];
        a0->lastBone = 0xFF;
        a0->x = t[i].rotX;
        a0->y = t[i].rotY;
        a0->z = t[i].rotZ;

        a1->weight = -0x80;
        a1->bone = D_800358D8[i];
        a1->rotX = 0;
        a1->rotY = 0;
        a1->rotZ = 0;

        v0++;
        a0++;
        a1++;
    }

    for (i = 0; i < 8; i++) {
        v0->bone = D_80035994[i];
        v0->lastBone = 0xFF;
        v0->x = 0.0f;
        v0->y = 0.0f;
        v0->z = 0.0f;
        v0++;
    }
}

typedef struct Boss2A_Struct_807FBB40_4300 {
    u8 pad0[4];
    ActorSub4 *sub;
    u8 pad8[0x7C - 8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss2A_Struct_807FBB40_4300;

s32 sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32); // FAKE: callee prototype steer
f32 mathSinF(s16);
f32 mathCosF(s16);

void bossArmydilloDebrisUpdate(void) {
    s16 i;
    BoneVector *debris;
    s32 soundId;
    s32 soundVol;
    s16 angle;

    debris = gCurrentActor->sub->boneOffsets;
    soundId = 0;
    soundVol = 0xFF;
    switch (gBehaviourWorkState->timer) {
    case 19:
        soundId = 0x22;
        break;
    case 17:
        soundId = 0xF6;
        break;
    case 15:
        soundId = 0x17;
        break;
    case 13:
        soundId = 0xED;
        break;
    case 11:
        soundId = 0x18;
        break;
    case 9:
        soundId = 0x22;
        soundVol = 0xC8;
        break;
    case 7:
        soundId = 0xED;
        soundVol = 0x82;
        break;
    case 5:
        soundId = 0x18;
        soundVol = 0x46;
        break;
    case 3:
        soundId = 0x3C;
        break;
    }

    if (soundId != 0) {
        sfxPlayAtPositionPooled(((Boss2A_Struct_807FBB40_4300 *)gCurrentActor)->unk7C,
                      ((Boss2A_Struct_807FBB40_4300 *)gCurrentActor)->unk80,
                      ((Boss2A_Struct_807FBB40_4300 *)gCurrentActor)->unk84,
                      soundId, soundVol, 0x7F, 1, 0x1E, 0.3f, 0);
    }

    i = 0;
    gCurrentActor->sub->boneOffsets[5].x = 99999.0f;
    do {
        if (debris->y >= 1800.0f) {
            debris->x = 99999.0f;
            debris->y = 99999.0f;
            debris->z = 99999.0f;
            debris++;
        } else {
            angle = i * 400;
            debris->x += 200.0f * mathSinF(angle);
            debris->z += 200.0f * mathCosF(angle);
            debris->y += 100.0f;
            debris++;
        }
        i++;
    } while (i < 13);
}

void bossPieceSetState(u8 *pieceData, u8 index, u8 state) {
    pieceData[index + 6] = state;
}

void bossPieceSetAngle(u8 index, s16 angle) {
    BoneRotation *entry = &gCurrentActor->sub->boneRotations[index];
    if (index == 3) {
        entry->bone = 0x2F;
    }
    entry->rotX = angle;
}


typedef struct BossPieceAnim {
    u8 pad0;
    u8 cnt[5];
    u8 state[5];
    u8 pad0B;
    s16 ang[5];
    u8 pad16[2];
    f32 f1[5];
    f32 f2[5];
} BossPieceAnim;

void sfxPlayActorSound(Actor *, s16, u8, u8, u8, u8, f32, s8);
void sfxStopSlotSound();
void actorScriptStart(void *, s32);

typedef struct BossActorState {
    u8 pad0[0x154];
    u8 unk154;
} BossActorState;

#define A154 (((BossActorState *)gCurrentActor)->unk154)
#define BB ((Boss2A_Struct_807FBB40_4300 *)gCurrentActor)
#define OBJ ((BossPieceAnim *)animData)

u8 bossPieceStep(u8 *animData, u8 pieceIdx, f32 maxTimer, f32 scriptTimer, f32 endTimer) {
    u8 ret;
    BoneVector *p1;
    BoneVector *p2;
    BossA_Struct_807FBB40 *boss;

    boss = gCurrentActor;
    ret = 0;
    p1 = &boss->sub->boneOffsets[pieceIdx];
    p2 = &boss->sub->boneScales[pieceIdx];
    switch (OBJ->state[pieceIdx]) {
    case 5:
        OBJ->f1[pieceIdx] = 30.0f;
        OBJ->ang[pieceIdx] = pieceIdx * 0x800 + 0x400;
        OBJ->f2[pieceIdx] = 100.0f;
        OBJ->state[pieceIdx] = 6;
    case 6:
        p1->x += OBJ->f1[pieceIdx] * mathSinF(OBJ->ang[pieceIdx]);
        p1->z += OBJ->f1[pieceIdx] * mathCosF(OBJ->ang[pieceIdx]);
        p1->y += OBJ->f2[pieceIdx];
        OBJ->f2[pieceIdx] -= 10.0f;
        if (OBJ->f2[pieceIdx] < -200.0f) {
            OBJ->f2[pieceIdx] = -200.0f;
        }
        if (p1->y < -300.0f) {
            p1->y = -300.0f;
            if (-50.0f < OBJ->f2[pieceIdx]) {
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, (u8)(pieceIdx + 1), 1.5f);
                func_8068A784(gCurrentActor, pieceIdx);
                OBJ->state[pieceIdx] = 0;
                ret = 1;
                break;
            }
            if (!pieceIdx) {
                sfxPlayAtPositionPooled(BB->unk7C, BB->unk80, BB->unk84, 0x36, (u32)(120.0f - OBJ->f2[pieceIdx] > 255.0f ? 255.0f : 120.0f - OBJ->f2[pieceIdx]), 0x7F, 0x28, 0, 0.3f, 0);
            }
            OBJ->f2[pieceIdx] *= -0.5;
        }
        break;
    case 1:
        switch (pieceIdx) {
        case 0:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.0f, 0);
            break;
        case 2:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.1f, 0);
            break;
        case 4:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.3f, 0);
            break;
        }
        func_8068A764(gCurrentActor, pieceIdx);
        OBJ->state[pieceIdx] = 2;
        OBJ->cnt[pieceIdx] = 0;
    case 2:
        if ((f32)++OBJ->cnt[pieceIdx] < maxTimer) {
            f32 t = (f32)OBJ->cnt[pieceIdx] / maxTimer;
            p1->x = D_800358E0[0][pieceIdx].x + (-D_800358E0[0][pieceIdx].x) * t;
            p1->y = D_800358E0[0][pieceIdx].y + (-D_800358E0[0][pieceIdx].y) * t;
            p1->z = D_800358E0[0][pieceIdx].z + (-D_800358E0[0][pieceIdx].z) * t;
        } else if (maxTimer == (f32)OBJ->cnt[pieceIdx]) {
            switch (pieceIdx) {
            case 0:
            case 2:
            case 4:
                sfxStopSlotSound(gCurrentActor, 1);
                break;
            }
        } else if (scriptTimer == (f32)OBJ->cnt[pieceIdx]) {
            switch (A154) {
            case 0x27:
                actorScriptStart(gCurrentActor, 0x264);
                break;
            case 0x2E:
                actorScriptStart(gCurrentActor, 0x265);
                break;
            default:
                actorScriptStart(gCurrentActor, 0x266);
                break;
            }
        } else if (scriptTimer + 1.0f == (f32)OBJ->cnt[pieceIdx]) {
            p2->x = 1.0f;
            p2->y = 1.0f;
            p2->z = 1.0f;
        } else if (endTimer < (f32)OBJ->cnt[pieceIdx]) {
            ret = 1;
            OBJ->state[pieceIdx] = 0;
        }
        break;
    case 3:
        switch (pieceIdx) {
        case 0:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.0f, 0);
            break;
        case 2:
            sfxPlayActorSound(gCurrentActor, 0x127, 0, 1, 1, 0xFF, 1.1f, 0);
            break;
        }
        OBJ->state[pieceIdx] = 4;
        OBJ->cnt[pieceIdx] = endTimer;
    case 4:
        if (maxTimer < (f32)--OBJ->cnt[pieceIdx]) {
            p2->x = p2->x + (D_800358E0[0][pieceIdx].rotX - p2->x) * 0.08;
            p2->y = p2->y + (D_800358E0[0][pieceIdx].rotY - p2->y) * 0.08;
            p2->z = p2->z + (D_800358E0[0][pieceIdx].rotZ - p2->z) * 0.09;
        } else if (OBJ->cnt[pieceIdx] > 0) {
            f32 t = (f32)OBJ->cnt[pieceIdx] / maxTimer;
            p1->x = D_800358E0[0][pieceIdx].x + (-D_800358E0[0][pieceIdx].x) * t;
            p1->y = D_800358E0[0][pieceIdx].y + (-D_800358E0[0][pieceIdx].y) * t;
            p1->z = D_800358E0[0][pieceIdx].z + (-D_800358E0[0][pieceIdx].z) * t;
        } else {
            func_8068A784(gCurrentActor, pieceIdx);
            OBJ->state[pieceIdx] = 0;
            if (pieceIdx == 0 || pieceIdx == 2) {
                sfxStopSlotSound(gCurrentActor, 1);
            }
            ret = 1;
        }
        break;
    }
    return ret;
}





void scriptSetActorRampTarget(void *, f32, f32);
s16 mathAngleSignedDistance(s16, s16);
void actorMoveWithinZone(s32, f32, f32, s32, f32); // FAKE: callee prototype steer

void bossArmydilloAimTowardTarget(void) {
    s32 res;
    u16 animState;

    animState = gCurrentActor->sub->animId;
    mathAngleSignedDistance(gBehaviourWorkState->unk8, gCurrentActor->unkE6);
    actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x16, 0.0f);
    res = mathAngleSignedDistance(gBehaviourWorkState->unk8, gCurrentActor->unkE6);
    if (res > 0) {
        if (animState != 0x260) {
            actorScriptStart(gCurrentActor, 0x260);
        }
    } else if (res < 0) {
        if (animState != 0x25F) {
            actorScriptStart(gCurrentActor, 0x25F);
        }
    } else if (animState != 0x25A) {
        actorScriptStart(gCurrentActor, 0x25A);
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
    }
}

typedef struct Boss2A_Struct_807FBB40_4FA8 {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} Boss2A_Struct_807FBB40_4FA8;


void bossArmydilloOpenCannons(void *boss, u8 *pieceData, s32 unused, u8 *pieceList) {
    u8 i;
    u8 res;

    i = 0;
    res = 0;
    switch (((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk155) {
    case 2:
        if (*pieceList != 0xFF) {
            do {
                bossPieceSetState(pieceData, pieceList[i++], 1);
            } while (pieceList[i] != 0xFF);
        }
        ((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk155 = 3;
        break;
    case 3:
        if (*pieceList != 0xFF) {
            do {
                if (((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk154 == 0x27 ||
                    ((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk154 == 0x2E) {
                    res = bossPieceStep(pieceData, pieceList[i++], 50.0f, 70.0f, 90.0f);
                } else {
                    res = bossPieceStep(pieceData, pieceList[i++], 10.0f, 15.0f, 50.0f);
                }
            } while (pieceList[i] != 0xFF);
        }
        if (res != 0) {
            ((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk155 = 4;
            animSetLoopLimit(gCurrentActor, 1, 1);
        }
        break;
    }
}

void bossPieceListStep(void *boss, u8 *pieceData, s32 unused, u8 *pieceList) {
    u8 i;
    u8 res;

    i = 0;
    res = 0;
    switch (((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk155) {
    case 2:
        if (*pieceList != 0xFF) {
            do {
                bossPieceSetState(pieceData, pieceList[i++], 3);
            } while (pieceList[i] != 0xFF);
        }
        ((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk155 = 3;
        break;
    case 3:
        if (*pieceList != 0xFF) {
            do {
                res = bossPieceStep(pieceData, pieceList[i++], 10.0f, 20.0f, 30.0f);
            } while (pieceList[i] != 0xFF);
        }
        if (res != 0) {
            ((Boss2A_Struct_807FBB40_4FA8 *)gCurrentActor)->unk155 = 4;
            animSetLoopLimit(gCurrentActor, 1, 1);
        }
        break;
    }
}

void actorClearNodeFlag(void *, s32);
void actorSetNodeFlag(void *, s32);

void bossArmydilloHideCannons(void) {
    actorClearNodeFlag(gCurrentActor, 3);
    actorClearNodeFlag(gCurrentActor, 4);
    actorClearNodeFlag(gCurrentActor, 5);
}

void bossArmydilloShowCannons(void) {
    actorSetNodeFlag(gCurrentActor, 3);
    actorSetNodeFlag(gCurrentActor, 4);
    actorSetNodeFlag(gCurrentActor, 5);
}

typedef struct BossActorUnkC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} BossActorUnkC0;

extern u8 effectFollowParentUpdate;
extern u8 D_80720120;


void bossArmydilloSpawnExhaustSmoke(void) {
    f32 val;
    s32 p;
    f64 dval;

    dval = (0.0 < (f64)((BossActorUnkC0 *)gCurrentActor)->unkC0) ? (f64)((BossActorUnkC0 *)gCurrentActor)->unkC0 : 0.0;
    val = (f32)((f32)((dval / 150.0) * 0.12) + 0.3) * 4.0f;
    p = (s32)&effectFollowParentUpdate;
    effectSetDepth(1);
    effectSetCallback((void *)p);
    effectSetMaxDistance(1000);
    effectSetSpeed(gCurrentActor);
    effectCreateAtActorBone(&D_80720120, val, gCurrentActor, 3, 0);
    effectSetDepth(1);
    effectSetCallback((void *)p);
    effectSetMaxDistance(1000);
    effectSetSpeed(gCurrentActor);
    effectCreateAtActorBone(&D_80720120, val, gCurrentActor, 4, 0);
}

typedef struct Boss3B_178 {
    u8 pad0[0x12];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    u8 unk18;
    u8 unk19;
} Boss3B_178;
typedef struct Boss3B_Sp78 {
    u8 unk0;
    u8 pad1[0xF];
    s16 unk10;
    s16 unk12;
} Boss3B_Sp78;
typedef struct Boss3B_Actor {
    u8 pad0[4];
    ActorSub4 *unk4;
    u8 pad8[0x60 - 8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[4];
    s16 unk70;
    s16 unk72;
    u8 pad74[8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB4 - 0x88];
    f32 unkB4;
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xE6 - 0xCC];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x12A - 0xF0];
    s16 unk12A;
    u8 pad12C[0x138 - 0x12C];
    s32 unk138;
    u8 pad13C[8];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0xC];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x16A - 0x156];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    u8 pad16D[0x178 - 0x16D];
    Boss3B_178 *unk178;
    Boss3B_Sp78 *unk17C;
} Boss3B_Actor;

extern Boss3B_Actor *gSpawnedActor;
extern Boss3B_Actor *gPrimaryPlayerActor;
extern u8 gActorGlobalState[];

extern u8 *D_800358B0[][5];
extern u8 D_80035980;
extern u8 D_80035984;
extern u8 D_80035988;
extern u8 D_80035CB8;
extern u8 D_80035CC0[];
extern s32 camPathCommandDispatch;
extern u8 gGameMode;
extern s8 D_80750190;
extern s16 D_807502D8;
extern f32 D_807502F4;
extern s32 gFrameCounter;
extern s16 D_80770628[];
extern s16 D_80770710[];
extern s32 gCamActor;

u8 camIsCutsceneActive(void);
u16 camStartPath(void *, s16, u8);
void camStartShake();
void camSetSecondTarget();
s32 currentActorTestClearFlag();
void currentActorClearFlag();
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32); // FAKE: callee prototype steer
void effectSpawnBoneDebris();
void effectSpawnBoneWhite(void *, s16, f32, f32, f32, f32, s32);
void effectSpawnJointBeam();
void projectileSetTargetCoords(f32, f32, f32);
void projectileGetTargetCoords();
void projectileSpawnNodeEntry(s16, s16, f32, s16, f32, f32, Actor *);
void projectileAimAndSpawn(s16, s16, f32, f32, f32, f32, f32, Actor *);
void projectileClampAngleAndSpawn(s16, s16, s16, s16, f32, f32, f32, f32, f32, Actor *);
void projectileSpawnWithShockwave(s16, f32, u8, u8, u8, u8, f32, f32, f32, f32);
void actorSetUniformScale(void *, f32);
u8 func_8072881C(u8, u32 *);
void behaviourFrameBegin();
void behaviourUpdateShadowAlpha();
u8 patrolPathStep(u8, u8);

#define gCurrentActor ((Boss3B_Actor *)gCurrentActor)

void bossArmydilloStep(void) {
    s32 pad_top[1];
    Boss3B_Sp78 *state17C;
    u8 *scriptData;
    f32 pad_mid;
    u8 cannonBone;
    u8 playSfx;
    s32 pad_bot[1];
    Boss3B_178 *state;


    state = gCurrentActor->unk178;
    state17C = gCurrentActor->unk17C;
    scriptData = D_800358B0[(gCurrentMap == 8) ? 0 : 1][state->unk14];
    cannonBone = (state->unk12 & 1) ? 1 : 2;
    playSfx = 0;
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        gBehaviourAnimState->unk38 = 0.002f;
        camSetSecondTarget(gCamActor, 0, 0);
        bossInitScriptData(&D_80035CC0);
        gCurrentActor->unkC4 = (f32) D_807502F4;
        gCurrentActor->unkC8 = (f32) D_807502D8;
        bossArmydilloHideCannons();
        gBehaviourAnimState->unk2C = 0.01f;
        gBehaviourAnimState->unk30 = 3.0f;
        gCurrentActor->unk12A = 0x3E8;
        animSetSpeed(gCurrentActor, 1, 0.2f);
        animSetLoopMode(gCurrentActor, 1, 1);
        gCurrentActor->unk146 = 0;
        bossArmydilloInitArena();
        gCurrentActor->unkB8 = 0.0f;
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        {
            u32 checkPtr = (u32) effectUpdateAndDispatch;
            u32 end = (u32) effectNodeSetSubVal;
            s32 checksum = 0;
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            while (checkPtr < end) {
                checksum += *(s32 *) checkPtr;
                checkPtr += 4;
            }
            if (checksum != 0x3D6E227F) {
                *(s32 *)((u32)&camPathCommandDispatch) = 0x27BDFF38;
            }
        }
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    if ((gActorGlobalState[0x200] == 9) || (gActorGlobalState[0x15] != 0)) {
        tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 0xC, 2.0f);
        gCurrentActor->unk138 = 0;
        gCurrentActor->unk144 = 1;
        currentActorClearFlag();
        actorScriptStart(gCurrentActor, 0x262);
        camStartPath(gCurrentActor, 9, 1);
        gCurrentActor->unk154 = 0x37;
        gCurrentActor->unk155 = 0;
    } else if (gActorGlobalState[0x200] == 4) {
        bossArmydilloHideCannons();
        gCurrentActor->unk154 = 0x4D;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unk138 = 0;
        D_80750190 = 1;
        tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 0xC, 2.0f);
        actorScriptStart(gCurrentActor, 0x262);
        state->unk15 = 0;
        state->unk14++;
        scriptData = D_800358B0[(gCurrentMap == 8) ? 0 : 1][state->unk14];
        camStartPath(gCurrentActor, 4, 1);
    }
    switch (gCurrentActor->unk154) {                     /* switch 1 */
    case 0x1F:                                      /* switch 1 */
        controllerAnimSetStateIfChanged(gCurrentActor, 0x39A, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        gCurrentActor->unk146 = 3;
        gCurrentActor->unk154 = scriptData[state->unk15++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x1E:                                      /* switch 1 */
        if (currentActorTestClearFlag() != 0) {
            gCurrentActor->unk154 = 0x40;
            bossSpawnParticleRing(0x1A, D_807FDCA0->entries[4].x, D_807FDCA0->entries[4].y, D_807FDCA0->entries[4].z, 0x800, 6);
        }
        break;
    case 0x37:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                          /* switch 2 */
        case 1:                                     /* switch 2 */
            effectSpawnJointBeam(0xD, 0x11, 0x12, 0x16);
            break;
        case 2:                                     /* switch 2 */
            if (!(gFrameCounter & 3)) {
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, (((randomNonNegative() >> 15) % 32767 % 10) + 0xD) & 0xFF, 1.0f);
            }
            if (currentActorTestClearFlag() != 0) {
                bossArmydilloSpawnSmoke();
                actorScriptStart(gCurrentActor, 0x263);
                gBehaviourWorkState->timer = 0x14;
                gCurrentActor->unk155 = 3;
                gCurrentActor->unk60 = (s32) (gCurrentActor->unk60 | 0x800000);
                gCurrentActor->unk16A = 0x1E;
                gCurrentActor->unk16B = 0x1E;
                gCurrentActor->unk16C = 0x1E;
            }
            break;
        case 3:                                     /* switch 2 */
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                bossArmydilloDebrisUpdate();
            } else if (currentActorTestClearFlag() != 0) {
                if (gCurrentActor->unk70 == -1) {
                    sfxPlayActorSound(gCurrentActor, 0x131, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
                gCurrentActor->unk72 = 0;
                gCurrentActor->unk155 = 4;
                controllerAnimSetState(gCurrentActor, 0x39A, 0.0f, 30.0f);
                gCurrentActor->unkEE = 0;
            }
            bossArmydilloDebrisFall();
            break;
        case 4:                                     /* switch 2 */
            gCurrentActor->unk72 = (gCurrentActor->unk72 + 1);
            effectSpawnBoneDebris((s16) (((s32) ((s32) (randomNonNegative() >> 0xF) % 32767) % 7) + 0x1D), 1);
            gCurrentActor->unkE6 = (gCurrentActor->unkE6 + gCurrentActor->unkEE);
            if (gCurrentActor->unkEE + 10 > 500) {
                gCurrentActor->unkEE = 500;
            } else {
                gCurrentActor->unkEE += 10;
            }
            actorSetUniformScale(gCurrentActor, (f32) ((f64) gCurrentActor->unk4->scaleX * 0.99));
            gCurrentActor->unk80 = (f32) ((f64) gCurrentActor->unk80 + ((f64) (356.0f - gCurrentActor->unk80) * 0.03));
            if ((f64) gCurrentActor->unk4->scaleY < 0.04) {
                gCurrentActor->unk155 = 5;
            }
            break;
        case 5:                                     /* switch 2 */
            sfxStopSlotSound(gCurrentActor, 1);
            gCurrentActor->unk154 = 0x40;
            bossSpawnParticleRing(0x124, (s16)gCurrentActor->unk7C, (s16)gCurrentActor->unk80, (s16)gCurrentActor->unk84, mathAngleBetweenPoints2D((f32) D_807FDCA0->entries[13].x, (f32) D_807FDCA0->entries[13].z, gCurrentActor->unk7C, gCurrentActor->unk84), 5);
            break;
        }
        break;
    case 0x27:                                      /* switch 1 */
        if (flagGet(0x68, 2) != 0) {
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        case 0x29:                                  /* switch 1 */
        case 0x2D:                                  /* switch 1 */
        case 0x2E:                                  /* switch 1 */
            switch (gCurrentActor->unk155) {                      /* switch 3 */
            case 0:                                 /* switch 3 */
                if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                    animSetLoopLimit(gCurrentActor, 1, 1);
                    state17C->unk0 = 0;
                    gCurrentActor->unk155 = 1;
                    sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                }
                break;
            case 1:                                 /* switch 3 */
                if ((animIsPlaying(gCurrentActor, 1) == 0) && (state17C->unk0 == 0)) {
                    sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x174, 0xC8, 0x7F, 1, 0x1E, 0.3f, 0);
                    state17C->unk0 = 1;
                }
                if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                    gCurrentActor->unk155 = 2;
                }
                break;
            case 2:                                 /* switch 3 */
            case 3:                                 /* switch 3 */
                if (gCurrentActor->unk154 == 0x29) {
                    bossArmydilloOpenCannons(state, state17C, scriptData, &D_80035984);
                } else if (gCurrentActor->unk154 == 0x2E) {
                    bossArmydilloOpenCannons(state, state17C, scriptData, &D_80035988);
                } else {
                    bossArmydilloOpenCannons(state, state17C, scriptData, &D_80035980);
                }
                break;
            case 4:                                 /* switch 3 */
                if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                    gCurrentActor->unk154 = scriptData[state->unk15++];
                    gCurrentActor->unk155 = 0;
                }
                break;
            }
        break;
    case 0x28:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                          /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            currentActorClearFlag();
            controllerAnimSetStateIfChanged(gCurrentActor, 0x3AF, 0.0f, 4.0f);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:                                     /* switch 4 */
            if (!(gFrameCounter & 7)) {
                effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            }
            if (currentActorTestClearFlag() != 0) {
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 6, 1.0f);
                tagBarrelSpawnNodeSmokePuffs(gCurrentActor, 7, 1.0f);
                actorScriptStart(gCurrentActor, 0x26C);
                bossPieceSetState(state17C, 0, 5);
                bossPieceSetState(state17C, 1, 5);
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x22, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x3C, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:                                     /* switch 4 */
            bossPieceStep(state17C, 0, 50.0f, 70.0f, 90.0f);
            if (bossPieceStep(state17C, 1, 50.0f, 70.0f, 90.0f) != 0) {
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x13:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
    case 0x1B:                                      /* switch 1 */
    case 0x2F:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 5 */
        case 0:                                     /* switch 5 */
            if (state17C->unk10 >= -0x3FFF) {
                state17C->unk10 -= 0x190;
                if (gCurrentActor->unk70 == -1) {
                    sfxPlayActorSound(gCurrentActor, 0x1F0, 1, 1, 1, 0xFF, 1.0f, 0);
                }
            } else {
                if (gCurrentActor->unk154 == 0x2F) {
                    actorScriptStart(gCurrentActor, 0x268);
                }
                sfxStopSlotSound(gCurrentActor, 1);
                gCurrentActor->unk155 = 1;
                gBehaviourWorkState->unk2E = 0;
                gCurrentActor->unkB8 = 0.0f;
            }
            {
                s16 val = state17C->unk10;

                state17C->unk12 = state17C->unk10;
                bossPieceSetAngle(2, val);
            }
            bossPieceSetAngle(3, state17C->unk12);
            break;
        case 1:                                     /* switch 5 */
            gBehaviourWorkState->unk2E += (gCurrentActor->unk154 == 0x2F) ? 10 : 4;
            if (gBehaviourWorkState->unk2E >= 0x12D) {
                gBehaviourWorkState->unk2E = 0x12C;
            }
            gCurrentActor->unkC0 = (f32) gBehaviourWorkState->unk2E;
            bossArmydilloSpawnExhaustSmoke();
            playSfx = 1;
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (gCurrentActor->unkB4 > 30.0f) {
                gCurrentActor->unkB8 = 100.0f;
            }
            if (gCurrentActor->unkB4 > 150.0f) {
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:                                     /* switch 5 */
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (gFrameCounter & 8) {
                bossArmydilloSpawnExhaustSmoke();
                playSfx = 1;
                gCurrentActor->unkC0 = 100.0f;
            }
            if ((gGameMode != 1) || (currentActorTestClearFlag() != 0)) {
                if (gCurrentActor->unk154 == 0x2F) {
                    gCurrentActor->unk154 = scriptData[state->unk15++];
                    gCurrentActor->unk155 = 0;
                } else {
                    gCurrentActor->unk155 = 3;
                }
            }
            break;
        case 3:                                     /* switch 5 */
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (gCurrentActor->unk6A & 1) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 0x96, 7, 1.04f, 40.0f, 8.0f, 600.0f);
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x221, 0xC8, 0x7F, 1, 0, 0.3f, 0);
                controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0.0f);
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x24A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                gCurrentActor->unk155 = 4;
                gBehaviourWorkState->timer = 0x3C;
            }
            break;
        case 4:                                     /* switch 5 */
            if ((gBehaviourWorkState->timer == 0x28) || (gBehaviourWorkState->timer == 0x32)) {
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x1C1, 0xB4, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2C:                                      /* switch 1 */
        {
            s32 pad;
            state17C->unk10 = -state17C->unk10 * 0.1 + state17C->unk10;
            state17C->unk12 = -state17C->unk12 * 0.1 + state17C->unk12;
            bossPieceSetAngle(3, state17C->unk12);
            bossPieceSetAngle(2, state17C->unk10);
        }
        /* fallthrough */
    case 0x2B:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 6; irregular */
        case 0:                                     /* switch 6 */
            animSetLoopLimit(gCurrentActor, 1, 1);
            gCurrentActor->unk155 = 2;
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            break;
        case 2:                                     /* switch 6 */
        case 3:                                     /* switch 6 */
            bossPieceListStep(state, state17C, scriptData, (gCurrentActor->unk154 == 0x2B) ? &D_80035980 : &D_80035984);
            break;
        case 4:                                     /* switch 6 */
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x2A:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 7; irregular */
        case 0:                                     /* switch 7 */
            actorScriptStart(gCurrentActor, 0x257);
            gCurrentActor->unk155 = 1;
            break;
        case 2:                                     /* switch 7 */
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x11:                                      /* switch 1 */
    case 0x57:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                          /* switch 8 */
        case 0:                                     /* switch 8 */
            actorScriptStart(gCurrentActor, (gCurrentActor->unk154 == 0x57) ? 0x258 : 0x259);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:                                     /* switch 8 */
            actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, (gCurrentActor->unk154 == 0x57) ? 0x210 : 0x212, 0.0f);
            break;
        case 2:                                     /* switch 8 */
            actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x212, 0.0f);
            break;
        case 3:                                     /* switch 8 */
            if (gCurrentActor->unk154 == 0x11) {
                waterRippleStart(gCurrentActor->unk7C, gCurrentActor->unk84, 20.0f, 2.0f, 8.0f, 400.0f);
            }
            camStartShake(gCamActor, 5, 0x14);
            break;
        case 5:                                     /* switch 8 */
            gCurrentActor->unkB8 = 0.0f;
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
        if (gFrameCounter & 8) {
            bossArmydilloSpawnExhaustSmoke();
            playSfx = 1;
            gCurrentActor->unkC0 = 100.0f;
        }
        switch (gCurrentActor->unk155) {                        /* switch 9 */
        case 0:                                     /* switch 9 */
            state->unk18 = scriptData[state->unk15++];
            state->unk19 = state->unk18;
            gCurrentActor->unk155 = 1;
            actorScriptStart(gCurrentActor, 0x269);
            break;
        case 2:                                     /* switch 9 */
            projectileGetTargetCoords(gCurrentActor, 5);
            projectileSpawnNodeEntry(0x1E, 5, 1.2f, gCurrentActor->unkE6, 600.0f, 300.0f, gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0xF6, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            effectSpawnBoneWhite(gCurrentActor, 5, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            if (state->unk19 != 0) {
                state->unk19--;
                gCurrentActor->unk155 = 1;
            } else {
                actorScriptStart(gCurrentActor, 0);
                controllerAnimSetStateIfChanged(gCurrentActor, 0x3A8, 0.0f, 10.0f);
                gCurrentActor->unk155 = 3;
                gBehaviourWorkState->timer = 0x1E;
            }
            break;
        case 3:                                     /* switch 9 */
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->unk155 = 4;
            }
            break;
        case 4:                                     /* switch 9 */
            projectileSetTargetCoords((f32) (((s32) (randomNonNegative() >> 15) % 20)) + gBehaviourTargetActor->x, gBehaviourTargetActor->y + 400.0f, (f32) (((s32) (randomNonNegative() >> 15) % 20)) + gBehaviourTargetActor->z);
            projectileAimAndSpawn(0x1E, 0xA, 1.2f, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, 600.0f, gCurrentActor);
            gBehaviourWorkState->timer = 0x14;
            gCurrentActor->unk155 = 5;
            /* fallthrough */
        case 5:                                     /* switch 9 */
            if (gBehaviourWorkState->timer == 0xF) {
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0xF4, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                state->unk18--;
                if (state->unk18 != 0) {
                    gCurrentActor->unk155 = 4;
                } else {
                    gCurrentActor->unk154 = scriptData[state->unk15++];
                    gCurrentActor->unk155 = 0;
                }
            }
            break;
        }
        break;
    case 0x46:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 10 */
        case 0:                                     /* switch 10 */
            state->unk12 = (u16) (state->unk12 | 1);
            state->unk18 = (u8) *(state->unk15++ + scriptData);
            state->unk19 = (u8) *(state->unk15++ + scriptData);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:                                     /* switch 10 */
            gBehaviourWorkState->timer = (s16) state->unk19;
            if (!(state->unk12 & 1) && (state->unk14 != 0)) {
                gBehaviourWorkState->timer = 0;
                state->unk18 = (u8) (state->unk18 + 1);
            }
            gCurrentActor->unk155 = 2;
            /* fallthrough */
        case 2:                                     /* switch 10 */
            if (gBehaviourWorkState->timer != 0) {
                bossArmydilloAimTowardTarget();
                gBehaviourWorkState->timer = (s16) (gBehaviourWorkState->timer - 1);
            } else {
                actorScriptStart(gCurrentActor, (cannonBone == 1) ? 0x25D : 0x25E);
                gCurrentActor->unk155 = 3;
            }
            break;
        case 4:                                     /* switch 10 */
            projectileGetTargetCoords(gCurrentActor, cannonBone);
            projectileClampAngleAndSpawn(gCurrentActor->unkE6, 0x320, 0x1E, 1, 0.7f, gBehaviourTargetActor->x, gBehaviourTargetActor->y + 5.0f, gBehaviourTargetActor->z, (f32) ((state->unk14 * 0x50) + 0x1F4), gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x18, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            effectSpawnBoneWhite(gCurrentActor, cannonBone, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            state->unk12 = (u16) (state->unk12 ^ 1);
            gCurrentActor->unk155 = 5;
            break;
        case 6:                                     /* switch 10 */
            if (state->unk18 != 0) {
                state->unk18--;
                gCurrentActor->unk155 = 1;
                break;
            }
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x48:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 11; irregular */
        case 0:                                     /* switch 11 */
            gCurrentActor->unk138 = -1;
            bossArmydilloShowCannons();
            gBehaviourWorkState->timer = (s16) *(state->unk15 + scriptData);
            state->unk15 = state->unk15 + 1;
            if (camIsCutsceneActive() != 0) {
                actorScriptStart(gCurrentActor, 0x267);
            } else {
                actorScriptStart(gCurrentActor, 0x261);
            }
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:                                     /* switch 11 */
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                break;
            }
            bossArmydilloHideCannons();
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x4D:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 12; irregular */
        case 0:                                     /* switch 12 */
            currentActorClearFlag();
            actorMoveWithinZone(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        case 1:                                     /* switch 12 */
            actorMoveWithinZone(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            break;
        case 2:                                     /* switch 12 */
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x263);
                gCurrentActor->unk155 = 3;
            }
            effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            effectSpawnJointBeam(9, 0xB, 0xC, 0xC);
            break;
        case 3:                                     /* switch 12 */
            effectSpawnBoneWhite(gCurrentActor, (s16) (((s32) ((s32) (randomNonNegative() >> 0xF) % 32767) % 20) + 9), 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk138 = -1;
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
                D_80750190 = 0;
            }
            break;
        }
        break;
    case 0x26:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 13; irregular */
        case 0:                                     /* switch 13 */
            bossInitScriptData(&D_80035CB8);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:                                     /* switch 13 */
            actorMoveWithinZone(0x42, (f32) gBehaviourWorkState->targetX, (f32) gBehaviourWorkState->targetZ, 0x290, 0.0f);
            if (gFrameCounter & 8) {
                bossArmydilloSpawnExhaustSmoke();
                playSfx = 1;
                gCurrentActor->unkC0 = 100.0f;
            }
            if (patrolPathStep(gCurrentActor->unk154, 0) != 0) {
                gCurrentActor->unk155 = 2;
            }
            break;
        case 2:                                     /* switch 13 */
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x43:                                      /* switch 1 */
    case 0x44:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 14; irregular */
        case 0:                                     /* switch 14 */
            actorScriptStart(gCurrentActor, (gCurrentActor->unk154 == 0x44) ? 0x25C : 0x25B);
            gCurrentActor->unk155 = 1;
            break;
        case 2:                                     /* switch 14 */
            if (gCurrentActor->unk154 == 0x44) {
                waterRippleStart(gCurrentActor->unk7C, gCurrentActor->unk84, 20.0f, 2.0f, 8.0f, 400.0f);
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x47:                                      /* switch 1 */
        switch (gCurrentActor->unk155) {                        /* switch 15 */
        case 2:                                     /* switch 15 */
        case 4:                                     /* switch 15 */
            break;
        case 0:                                     /* switch 15 */
            actorScriptStart(gCurrentActor, 0x26A);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:                                     /* switch 15 */
            actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x292, 0.0f);
            if (gCurrentActor->unk6A & 1) {
                actorScriptStart(gCurrentActor, 0x26B);
                gCurrentActor->unk155 = 2;
            }
            break;
        case 3:                                     /* switch 15 */
            projectileGetTargetCoords(gCurrentActor, 5);
            projectileAimAndSpawn(0x59, 1, 1.5f, gPrimaryPlayerActor->unk7C, gPrimaryPlayerActor->unk80 + 2.0f, gPrimaryPlayerActor->unk84, 300.0f, gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x128, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x188, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            gCurrentActor->unk155 = 4;
            break;
        default:                                    /* switch 15 */
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x23:                                      /* switch 1 */
    case 0x42:                                      /* switch 1 */
        if (gCurrentActor->unk4->model->animId != 0x39A) {
            actorScriptStart(gCurrentActor, 0x256);
        }
        /* fallthrough */
    default:                                        /* switch 1 */
        bossScriptStep(scriptData, 0x10, 0.0f);
        break;
    }
    if (playSfx != 0) {
        if ((gCurrentActor->unk70 != -1) && (D_80770710[D_80770628[gCurrentActor->unk70]] != 0x114)) {
            sfxStopSlotSound(gCurrentActor, 1);
        }
        if (gCurrentActor->unk70 == -1) {
            sfxPlayActorSound(gCurrentActor, 0x114, 1, 1, 1, 0xFF, 0.5f, 0);
        }
    } else {
        if ((gCurrentActor->unk70 != -1) && (D_80770710[D_80770628[gCurrentActor->unk70]] == 0x114)) {
            sfxStopSlotSound(gCurrentActor, 1);
        }
    }
    behaviourUpdateShadowAlpha();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#undef gCurrentActor

void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void bossArmydilloDebrisFall(void) {
    u8 val;

    if (!(gFrameCounter & 3)) {
        if (!(gFrameCounter & 0xF)) {
            val = 0xC;
        } else {
            val = ((randomNonNegative() >> 15) % 0x7FFF) % 7 + 0x1D;
        }
        effectSetMode(3);
        effectSetColor(0x50, 0x50, 0x50, 0xC8);
        effectSpawnBoneDefault(gCurrentActor, val, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C00.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C14.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C28.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C3C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C44.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C5C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C78.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C94.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035CB8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035CC0.s")
