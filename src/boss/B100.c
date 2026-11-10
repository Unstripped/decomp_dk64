#include "common.h"
#include "actor.h"
#include "proto/boss/3840.h"
#include "proto/boss/B100.h"
#include "proto/global/10E1D0.h"
#include "proto/global/135D30.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/8CA50.h"
#include "proto/global/FCCD0.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} BossE_B100_Sub20;

typedef struct {
    u8 pad0[0x20];
    BossE_B100_Sub20 *unk20;
    u8 pad24[0x38 - 0x24];
    f32 unk38;
} BossE_B100_Sub4;

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} BossE_B100_Sub178;

typedef struct {
    u8 pad0[0x178];
    BossE_B100_Sub178 *unk178;
} BossE_B100_Sub11C;

typedef struct BossE_B100_Actor {
    u8 pad0[0x4];
    BossE_B100_Sub4 *unk4;
    u8 pad8[0x60 - 0x8];
    s32 unk60;
    u8 pad64[0x11C - 0x64];
    void *unk11C;
    u8 pad120[0x132 - 0x120];
    s16 unk132;
    s16 unk134;
    s32 unk138;
    u8 pad13C[0x144 - 0x13C];
    u8 unk144;
    u8 pad145[0x15F - 0x145];
    u8 unk15F;
    u8 pad160[0x17C - 0x160];
    struct BossE_B100_Actor **unk17C;
} BossE_B100_Actor;

extern BossE_B100_Actor *gCurrentActor;
extern BossE_B100_Actor *gSpawnedActor;
extern u8 gBossFightPhase;
extern s32 gFrameCounter;

s32 actorSpawn(s32, s32);
void actorCopyPoseAndScale(void *, void *, f32);
void actorScriptStart(void *, s32);
void func_80724DB0();
void sfxPlayAtFBD6CPosition(void);

f32 mathSinF(s16);

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0x154 - 0xE8];
    u8 unk154;
    u8 unk155;
} BossPlayerActor;


extern BossPlayerActor *gPrimaryPlayerActor;

typedef struct BossPhaseState {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17[1];
    u8 unk18;
} BossPhaseState;

typedef struct BossMainActor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xCC - 0xBC];
    u8 unkCC;
    u8 padCD[0xE6 - 0xCD];
    s16 unkE6;
    u8 padE8[0x11C - 0xE8];
    void *unk11C;
    u8 pad120[0x132 - 0x120];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[1];
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x168 - 0x156];
    s16 unk168;
    u8 pad16A[0x178 - 0x16A];
    BossPhaseState *unk178;
} BossMainActor;


typedef struct BossGlobalC924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BossGlobalC924;


extern u8 *D_80035A90[];
extern BossGlobalC924 *gPlayerSlots;
extern void *gCamActor;

void behaviourFrameBegin(void);
void camSetSecondTarget(struct CamActor *, s16, s16);
void func_80724CA4(s16, s16);
void zoneEntryGetPosition(u8, u8, f32 *, f32 *, f32 *);
u16 camStartPath(void *, s16, u8);
void hudCountdownTimerSaveElapsed(void *);
f32 mathCosF(s16);
void playerWaypointPathStartLineFromActor(Actor *, s16, s16, u8);
void csSendActorMessagePayload(s16, s16);
void playerSetSizeMode(Actor *, u8);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void actorSetTargetSpeed(void *, s32);
s16 mathAngleEaseToward(s16, s16, f32);
void projectileSpawnWithShockwave(s16, f32, u8, u8, u8, u8, f32, f32, f32, f32);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
void scriptSetActorRampTarget(void *, f32, f32);
s32 currentActorTestClearFlag(void);
void behaviourUpdateShadowAlpha(void);
u8 func_8072881C(u8, u32 *);

#define MAIN_ACTOR ((BossMainActor *)gCurrentActor)
#define PLAYER_ACTOR ((BossMainActor *)gPrimaryPlayerActor)
#define SECOND_ACTOR ((BossMainActor *)gSpawnedActor)

void bossDogadonStep(void) {
    BossPhaseState *phaseState;
    u8 *scriptOpcodes;
    s32 pad[2];
    f32 lineDist;

    phaseState = MAIN_ACTOR->unk178;
    behaviourFrameBegin();
    if (!(MAIN_ACTOR->unk60 & 0x10)) {
        MAIN_ACTOR->unk132 = 8;
        transitionSetState(0);
        camSetSecondTarget(gCamActor, 0, 0);
        MAIN_ACTOR->unk146 = 5;
        MAIN_ACTOR->unkCC = 1;
        func_80724CA4(2, 1);
        MAIN_ACTOR->unk154 = 0x1E;
        MAIN_ACTOR->unk155 = 0;
        if (flagGet(0x54, 2) != 0) {
            phaseState->unk14 = 4;
            MAIN_ACTOR->unk154 = 0x37;
            MAIN_ACTOR->unk155 = 0;
        } else if (flagGet(0x53, 2) != 0) {
            phaseState->unk14 = 3;
        } else if (flagGet(0x52, 2) != 0) {
            phaseState->unk14 = 2;
        } else if (flagGet(0x51, 2) != 0) {
            phaseState->unk14 = 1;
        }
        if (phaseState->unk14 != 0 && MAIN_ACTOR->unk154 != 0x37) {
            MAIN_ACTOR->unk154 = 0x31;
            MAIN_ACTOR->unk155 = 0;
            zoneEntryGetPosition(1, 0, &MAIN_ACTOR->unk7C, &MAIN_ACTOR->unk80, &MAIN_ACTOR->unk84);
        }
    }
    scriptOpcodes = D_80035A90[phaseState->unk14];
    bossRoundFrame(scriptOpcodes);
    switch (MAIN_ACTOR->unk154) {
    case 0x28:
        if (gBossFightPhase == 5 && gPlayerSlots->unk2C0 != 1) {
            MAIN_ACTOR->unk144 = 1;
            PLAYER_ACTOR->unk144 = 1;
            camStartPath(0, 2, 1);
            MAIN_ACTOR->unk154 = 0x29;
            hudCountdownTimerSaveElapsed(MAIN_ACTOR->unk11C);
            screenSetTransitionFadeType(1);
            transitionSetState(1);
            mapRequestTransition(0xD6, 0);
            PLAYER_ACTOR->unk7C = mathSinF(MAIN_ACTOR->unkE6 + 0x320) * 30.0 + MAIN_ACTOR->unk7C;
            PLAYER_ACTOR->unk84 = mathCosF(MAIN_ACTOR->unkE6 + 0x320) * 30.0 + MAIN_ACTOR->unk84;
            lineDist = mathSinF(MAIN_ACTOR->unkE6 + 0x384);
            playerWaypointPathStartLineFromActor(PLAYER_ACTOR, (s32)(lineDist * 15.0f + MAIN_ACTOR->unk7C), (s32)(mathCosF(MAIN_ACTOR->unkE6 + 0x384) * 15.0f + MAIN_ACTOR->unk84), 0x50);
        } else {
            switch (MAIN_ACTOR->unk155) {
            case 0:
                if (phaseState->unk16 != 0) {
                    csSendActorMessagePayload(0, 0);
                }
                actorScriptStart(MAIN_ACTOR, 0x3FF);
                gBehaviourWorkState->timer = scriptOpcodes[phaseState->unk15] * 0x1E;
                phaseState->unk15++;
                MAIN_ACTOR->unk155++;
                break;
            case 1:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else {
                    actorScriptStart(MAIN_ACTOR, 0x400);
                    MAIN_ACTOR->unk155++;
                }
                break;
            case 3:
                if (gPlayerSlots->unk2C0 != 1) {
                    playerSetSizeMode(PLAYER_ACTOR, 1);
                }
                csSendActorMessagePayload(0, 0xFF);
                actorScriptStart(MAIN_ACTOR, 0x3E4);
                MAIN_ACTOR->unk154 = scriptOpcodes[phaseState->unk15];
                phaseState->unk15++;
                MAIN_ACTOR->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
        switch (MAIN_ACTOR->unk155) {
        case 0:
            actorSetTargetSpeed(MAIN_ACTOR, 0);
            phaseState->unk18 = scriptOpcodes[phaseState->unk15];
            phaseState->unk15++;
            MAIN_ACTOR->unk155++;
            /* fallthrough */
        case 1:
            gBehaviourWorkState->timer = 4;
            actorScriptStart(MAIN_ACTOR, 0x3E7);
            MAIN_ACTOR->unk155++;
            break;
        case 2:
            MAIN_ACTOR->unkE6 = mathAngleEaseToward(MAIN_ACTOR->unkE6, mathAngleBetweenPoints2D((f32)D_807FDCA0->entries->x, (f32)D_807FDCA0->entries->z, MAIN_ACTOR->unk7C, MAIN_ACTOR->unk84), 10.0f);
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0 && (u32)gFrameCounter % 5 == 0) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 150, 3, (f32)((f64)(u32)phaseState->unk14 * 0.01 + 1.04), 0.0f, 0.0f, 0.0f);
                if (gBehaviourWorkState->timer-- < 4) {
                    SECOND_ACTOR->unk168 = 0;
                } else {
                    sfxPlayAtPositionPooled(MAIN_ACTOR->unk7C, MAIN_ACTOR->unk80, MAIN_ACTOR->unk84, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                }
                controllerAnimSetStateIfChanged(SECOND_ACTOR, 0x4F9, 0.0f, 0.0f);
                scriptSetActorRampTarget(SECOND_ACTOR, 0.5f, 0.0f);
            } else if (gBehaviourWorkState->timer == 0) {
                gBehaviourWorkState->timer = phaseState->unk18;
                MAIN_ACTOR->unk155++;
            }
            break;
        case 4:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                actorSetTargetSpeed(MAIN_ACTOR, gBehaviourExtraState->targetSpeed);
                actorScriptStart(MAIN_ACTOR, 0x3E4);
                MAIN_ACTOR->unk154 = scriptOpcodes[phaseState->unk15];
                phaseState->unk15++;
                MAIN_ACTOR->unk155 = 0;
            }
            break;
        }
        break;
    case 0x1E:
        phaseState->unk14 = 0;
        phaseState->unk15 = 0;
        MAIN_ACTOR->unk154 = scriptOpcodes[phaseState->unk15];
        phaseState->unk15++;
        MAIN_ACTOR->unk155 = 0;
        MAIN_ACTOR->unkB8 = (f32)(u32)gBehaviourExtraState->targetSpeed;
        break;
    case 0:
        switch (MAIN_ACTOR->unk155) {
        case 0:
            actorScriptStart(MAIN_ACTOR, 0x3EA);
            MAIN_ACTOR->unk155++;
            break;
        case 2:
            MAIN_ACTOR->unk154 = scriptOpcodes[phaseState->unk15];
            phaseState->unk15++;
            MAIN_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x31:
        switch (MAIN_ACTOR->unk155) {
        case 0:
            playerSetSizeMode(PLAYER_ACTOR, 0);
            playerSetSizeMode(PLAYER_ACTOR, 1);
            camStartPath(MAIN_ACTOR, 1, 1);
            actorScriptStart(MAIN_ACTOR, 0x3FB);
            MAIN_ACTOR->unk155++;
            break;
        case 2:
            actorScriptStart(MAIN_ACTOR, 0x3E4);
            MAIN_ACTOR->unk154 = scriptOpcodes[phaseState->unk15];
            phaseState->unk15++;
            MAIN_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (MAIN_ACTOR->unk155) {
        case 0:
            actorScriptStart(MAIN_ACTOR, 0);
            camStartPath(MAIN_ACTOR, 0x15, 1);
            MAIN_ACTOR->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                screenSetTransitionFadeType(0);
                mapRequestTransition(0xCF, 0);
                MAIN_ACTOR->unk155++;
            }
            break;
        }
        break;
    default:
        bossScriptStep(scriptOpcodes, 0x10, 0.0f);
        break;
    }
    behaviourUpdateShadowAlpha();
    if (func_8072881C(0, gBehaviourWorkState->unk28) != 0) {
        func_8072881C(0x81, gBehaviourWorkState->unk28);
    }
    actorUpdateModelMatrix(MAIN_ACTOR, 0);
}


void func_8002FB7C(scaleFactor)
u8 scaleFactor;
{
    BossE_B100_Sub20 *sub;
    f32 sin_val;

    sub = gCurrentActor->unk4->unk20;
    sub->unk0 = 2;
    sub->unk1 = 4;
    sub->unk4 = 1.0f;
    sin_val = mathSinF((s16)(gFrameCounter << 7));
    sub->unk4 += (f64)scaleFactor * (0.04 + 0.04 * (f64)sin_val);
    sub->unk8 = sub->unk4;
    sub->unkC = 1.0f;
}
void func_8002FC48(actorObj, frame)
s32 actorObj;
u8 frame;
{
    animSetLoopLimit(actorObj, 0, 1);
    animSetFinished(actorObj, 0, 1);
    animSetFrameAndSubframe(actorObj, 0, frame, 0.0f);
}

void scriptSetActorRampTarget(void *, f32, f32);

void bossActorGroupCommand(groupLeader, mask, command, param)
BossE_B100_Actor *groupLeader;
u8 mask;
s32 command;
u8 param;
{
    BossE_B100_Actor **actor_list;
    BossE_B100_Actor *actor;
    s16 i;

    actor_list = groupLeader->unk17C;
    for (i = 0; i < 4; i++) {
        if (mask & (1 << i)) {
            actor = i != 0 ? actor_list[i - 1] : groupLeader;
            switch (command) {
            case 1:
            case 2:
                actor->unk132 = command;
                break;
            case -1:
            case 0:
                actor->unk138 = command;
                break;
            default:
                actorScriptStart(actor, command);
                if (param) {
                    scriptSetActorRampTarget(actor, (f64)param * 0.01, 0.0f);
                }
                break;
            }
        }
    }
}


void func_8002FDF8(s32 actorObj, u8 scaleVal) {
    s32 finalScale;
    s32 animFrame;

    if (gCurrentActor->unk15F == 2) {
        finalScale = 4;
    } else {
        finalScale = scaleVal;
    }
    func_8002FB7C(finalScale & 0xFF);
    if (gBossFightPhase == 4) {
        bossActorGroupCommand(actorObj, 0xF, 0, 0);
        animFrame = (0xA - gCurrentActor->unk134) & 0xFF;
        func_8002FC48(gCurrentActor, animFrame);
        actorScriptStart(gCurrentActor, 0x415);
    }
    if (gBossFightPhase == 5 || gBossFightPhase == 4) {
        sfxPlayAtFBD6CPosition();
    }
}

void func_8002FEC0(actorList, slotIndex, modelId)
BossE_B100_Actor **actorList;
u8 slotIndex;
s32 modelId;
{
    actorSpawn(0xE5, modelId);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->unk4->unk38);
    gSpawnedActor->unk60 |= 0x1400;
    gSpawnedActor->unk11C = gCurrentActor;
    gSpawnedActor->unk144 = gCurrentActor->unk144;
    gSpawnedActor->unk60 = gCurrentActor->unk60;
    actorList[slotIndex] = gSpawnedActor;
}

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
    u8 padA[0x12 - 0xA];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    u8 unk18;
    u8 unk19;
} BossScriptState;

typedef struct BossActor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x138 - 0x64];
    s32 unk138;
    u8 pad13C[0x154 - 0x13C];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x178 - 0x160];
    BossScriptState *unk178;
    struct BossActor **unk17C;
} BossActor;

typedef struct {
    u8 pad0[0x38];
    f32 unk38;
} BossPlayerData;

#define BOSS_ACTOR ((BossActor *)gCurrentActor)

extern BossPlayerData *gActivePlayerState;
extern u8 *D_80035AA4[];

void actorScriptStartByIndex(void *, s32);
s32 func_80724A20(void);
void behaviourFrameBegin(void);
void camClosestPointOnSegment(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);


void bossKRoolTinyStep(void) {
    BossScriptState *st;
    BossActor **list;
    u8 *tbl;
    f32 dummyY;

    st = BOSS_ACTOR->unk178;
    list = BOSS_ACTOR->unk17C;
    behaviourFrameBegin();
    if (!(BOSS_ACTOR->unk60 & 0x10)) {
        transitionSetState(0);
        slotQueueSetDisplayMode(2, 0, 1);
        gPrimaryPlayerActor->unk154 = 0x5F;
        gPrimaryPlayerActor->unk155 = 0;
        actorScriptStartByIndex(gPrimaryPlayerActor, 0x4B);
        BOSS_ACTOR->unk154 = 0;
        BOSS_ACTOR->unk155 = 0;
        func_80724DB0(2, 1);
        func_8002FEC0(list, 0, 0x6D);
        func_8002FEC0(list, 1, 0x6E);
        func_8002FEC0(list, 2, 0x6F);
        st->unk12 = 0;
        if (flagGet(0x51, 2)) {
            func_8002FC48(gCurrentActor, 4);
            BOSS_ACTOR->unk15F = 2;
            list[0]->unk15F = 1;
            st->unk12 = 1;
        }
        if (flagGet(0x52, 2)) {
            func_8002FC48(list[0], 4);
            list[0]->unk15F = 2;
            list[1]->unk15F = 1;
            st->unk12 = 2;
        }
        if (flagGet(0x53, 2)) {
            func_8002FC48(list[1], 4);
            list[1]->unk15F = 2;
            list[2]->unk15F = 1;
            st->unk12 = 3;
        }
        st->unk14 = 0;
        bossActorGroupCommand(gCurrentActor, 0xF, 0x40E, 0);
    }
    tbl = D_80035AA4[st->unk14];
    if (BOSS_ACTOR->unk154) {
        ZoneEntry *p = D_807FDCA0->entries;
        camClosestPointOnSegment(gPrimaryPlayerActor->unk7C, gPrimaryPlayerActor->unk80, gPrimaryPlayerActor->unk84, p[0].x, p[0].y, p[0].z, p[1].x, p[1].y, p[1].z, &gPrimaryPlayerActor->unk7C, &dummyY, &gPrimaryPlayerActor->unk84);
        gPrimaryPlayerActor->unkE6 = 0xFD2;
        gActivePlayerState->unk38 = 150.0f;
    }
    func_8002FDF8((s32)BOSS_ACTOR, st->unk14);
    bossActorGroupCommand(gCurrentActor, (1 << st->unk12) & 0xFF, 1, 0);
    switch (BOSS_ACTOR->unk154) {
    case 0x1F:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            gBehaviourWorkState->timer = tbl[st->unk15++];
            BOSS_ACTOR->unk155++;
        case 1:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                BOSS_ACTOR->unk154 = tbl[st->unk15++];
                BOSS_ACTOR->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        if (BOSS_ACTOR->unk155 == 0) {
            gPrimaryPlayerActor->unk154 = 0x5F;
            gPrimaryPlayerActor->unk155 = 0;
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x4A);
            screenSetTransitionFadeType(1);
            transitionSetState(1);
            mapRequestTransition(0xCE, 0);
            flagSet(st->unk12 + 0x51, 1, 2);
            BOSS_ACTOR->unk155++;
        }
        break;
    case 0:
        func_80724A20();
        break;
    case 1:
        bossActorGroupCommand(BOSS_ACTOR, 0xF, 0x410, 0);
        BOSS_ACTOR->unk154 = tbl[st->unk15++];
        BOSS_ACTOR->unk155 = 0;
        break;
    case 0x27:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            BOSS_ACTOR->unk155++;
            bossActorGroupCommand(BOSS_ACTOR, 0xF, -1, 0);
            st->unk18 = tbl[st->unk15++];
            st->unk19 = tbl[st->unk15++] + st->unk12 * 10;
            st->unk8 = tbl[st->unk15++];
            if (st->unk18 == 0xFF) {
                st->unk18 = 8 >> (s32)((gPrimaryPlayerActor->unk7C - 117.0f) / 50.0f);
            }
            bossActorGroupCommand(BOSS_ACTOR, st->unk18, 0x413, 0);
            gBehaviourWorkState->timer = 0x14;
            break;
        case 1:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                BOSS_ACTOR->unk155++;
            }
            break;
        case 2:
            BOSS_ACTOR->unk155++;
            bossActorGroupCommand(BOSS_ACTOR, st->unk18, 0x414, (st->unk19 + st->unk12 * 15) & 0xFF);
            gBehaviourWorkState->timer = st->unk8;
        case 3:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                BOSS_ACTOR->unk154 = tbl[st->unk15++];
                BOSS_ACTOR->unk155 = 0;
            }
            break;
        }
        break;
    case 0x28:
        bossActorGroupCommand(BOSS_ACTOR, (1 << st->unk12) & 0xFF, 2, 0);
        if (st->unk14 == st->unk12 && BOSS_ACTOR->unk138 == 0) {
            BOSS_ACTOR->unk154 = 0x37;
            BOSS_ACTOR->unk155 = 0;
            break;
        }
        switch (BOSS_ACTOR->unk155) {
        case 0:
            gBehaviourWorkState->timer = tbl[st->unk15++];
            bossActorGroupCommand(BOSS_ACTOR, (1 << st->unk12) & 0xFF, 0x411, 0);
            BOSS_ACTOR->unk155++;
            break;
        case 1:
        case 2:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                if (BOSS_ACTOR->unk155 == 1 && BOSS_ACTOR->unk138) {
                    bossActorGroupCommand(BOSS_ACTOR, (1 << st->unk12) & 0xFF, 0x412, 0);
                }
                gBehaviourWorkState->timer = 10;
                BOSS_ACTOR->unk155++;
            }
            break;
        case 3:
            if (BOSS_ACTOR->unk138 == 0) {
                st->unk14++;
                st->unk15 = 0;
                tbl = D_80035AA4[st->unk14];
            }
            BOSS_ACTOR->unk154 = tbl[st->unk15++];
            BOSS_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x29:
        switch (BOSS_ACTOR->unk155) {
        case 0:
            break;
        }
        break;
    default:
        bossScriptStep(tbl, 0, 0);
        break;
    }
    actorUpdateModelMatrix(BOSS_ACTOR, 0);
}

void bossKRoolTinyUpdateMinion(void) {
    BossE_B100_Sub11C *sub11C;
    BossE_B100_Sub178 *sub178;
    s32 scaleVal;

    sub11C = gCurrentActor->unk11C;
    sub178 = sub11C->unk178;
    if (!(gCurrentActor->unk60 & 0x10)) {
        func_80724DB0(2, 1, sub11C);
    }
    scaleVal = (gCurrentActor->unk15F == 1) ? sub178->unk14 : 0;
    func_8002FDF8(sub11C, (u8)scaleVal);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368C0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368E4.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368F8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036910.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036950.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036968.s")
