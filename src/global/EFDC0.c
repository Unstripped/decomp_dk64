#include "common.h"
#include "actor.h"


extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern s32 gCurrentMap;
extern u8 gPlayerCharacterId[];
typedef struct EfAQueuedCall {
    u8 pad0[0x29C];
    s16 unk29C;
    Actor *unk2A0;
    s32 unk2A4;
    s32 unk2A8;
    s32 unk2AC;
    s32 unk2B0;
    u8 pad2B4[0x3C];
} EfAQueuedCall;

typedef struct EfAPlayer {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[2];
    s16 unkA;
    u8 padC[0x20];
    f32 unk2C;
    u8 pad30[8];
    f32 unk38;
    s16 unk3C;
    u8 pad3E[0xE];
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    u8 pad52[0x12];
    s32 unk64;
    u8 pad68[0x24];
    u8 unk8C;
    u8 pad90[0x74];
    Actor *unk104;
    u8 pad108[0x9B];
    u8 unk1A3;
    u8 unk1A4;
} EfAPlayer;

typedef struct EfAActor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[8];
    s32 unk60;
    u8 pad64[0x54];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    u8 padC8[0x1E];
    s16 unkE6;
    u8 padE8[0x6C];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x1E];
    void *unk174;
} EfAActor;


typedef struct EfAParameters {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} EfAParameters;

#define EfA_P ((EfAPlayer *)gActivePlayerState)
#define EfA_A40 ((EfAActor *)gCurrentActor)

extern EfAParameters gPlayerStateCallbackParams;
void scriptSetRampValue(Actor *, f32, f32);
void actorScriptStartByIndex(Actor *, s32);
void actorScriptStart(Actor *, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void playerResumeLocomotion(Actor *);
void slotQueueUpdate(s32, s32, s32);

s32 playerStateQueueCallback(s16 priority, void *actor, u8 player) {
    u8 playerByte;
    s32 offset;
    s32 priorityCopy;
    EfAQueuedCall *entry;

    priorityCopy = priority;
    playerByte = player;
    offset = playerByte * 0x2F0;
    entry = (EfAQueuedCall *)((u8 *)gPlayerSlots + offset);
    if (entry->unk29C < priorityCopy) {
        entry->unk29C = priorityCopy;
        ((EfAQueuedCall *)((u8 *)gPlayerSlots + offset))->unk2A0 = actor;
        ((EfAQueuedCall *)((u8 *)gPlayerSlots + offset))->unk2A8 = gPlayerStateCallbackParams.unk0;
        ((EfAQueuedCall *)((u8 *)gPlayerSlots + offset))->unk2AC = gPlayerStateCallbackParams.unk4;
        ((EfAQueuedCall *)((u8 *)gPlayerSlots + offset))->unk2B0 = gPlayerStateCallbackParams.unk8;
        if (actor != NULL) {
            ((EfAQueuedCall *)((u8 *)gPlayerSlots + offset))->unk2A4 = ((EfAActor *)actor)->unk54;
        }
        return 1;
    }
    return 0;
}

void playerStateSetCallbackParameters(s32 unused, s32 param0, s32 param1, s32 param2) {
    gPlayerStateCallbackParams.unk0 = param0;
    gPlayerStateCallbackParams.unk4 = param1;
    gPlayerStateCallbackParams.unk8 = param2;
}

#define EfN9_Q ((EfAQueuedCall *)gPlayerSlots)

extern void (*gPlayerStateCallbacks[])(void);
s32 actorTableContains(Actor *);

void playerStateDispatchQueuedCallback(void) {
    if (EfN9_Q[gCurrentPlayerIndex].unk29C >= 0) {
        if (EfN9_Q[gCurrentPlayerIndex].unk2A0 != NULL) {
            if ((actorTableContains(EfN9_Q[gCurrentPlayerIndex].unk2A0) == 0) ||
                (((EfAActor *)EfN9_Q[gCurrentPlayerIndex].unk2A0)->unk54 != EfN9_Q[gCurrentPlayerIndex].unk2A4)) {
                EfN9_Q[gCurrentPlayerIndex].unk2A0 = NULL;
            }
        }
        gPlayerStateCallbacks[EfN9_Q[gCurrentPlayerIndex].unk29C]();
    }
    EfN9_Q[gCurrentPlayerIndex].unk29C = -1;
}


void playerApproachVelocity(s16, f32, f32);
void playerSetTerminalVelocity5B0(void);

void playerStateInitApproachVelocity(void) {
    playerSetTerminalVelocity5B0();
    gCurrentActor->state = 0x22;
    gCurrentActor->unk155[0] = 0;
    EfA_A40->unkC0 = 100.0f;
    EfA_P->unk50 = 0;
    EfA_P->unk2C = 100.0f;
    if (EfA_P->unk3C == 0) {
        playerApproachVelocity(EfA_P->unkA, EfA_P->unk4, EfA_P->unk38);
    }
    EfA_P->unk2C = 10.0f;
    actorScriptStart(gCurrentActor, 0x17B);
}

void playerStateEnterState3D(void) {
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 6) {
        playerResumeLocomotion(gActivePlayerActor);
        return;
    }
    gCurrentActor->state = 0x3D;
    gCurrentActor->unk155[0] = 0;
    if (EfA_P->unk4E == 0x22) {
        actorScriptStart(gCurrentActor, 0x131);
        return;
    }
    actorScriptStartByIndex(gCurrentActor, 0xD);
}

#define EfA_Q ((EfAQueuedCall *)gPlayerSlots)

typedef struct EfASubActor {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0x11A];
    s32 unk1F0;
} EfASubActor;

s32 playerCanTakeHit(Actor *arg0) {
    s32 pred;
    EfASubActor *sub;

    sub = (EfASubActor *)arg0->customState;
    pred = (sub->unkD4 == 0) || (EfA_Q[gCurrentPlayerIndex].unk29C == 0x3F);
    if ((gPlayerCharacterId[gCurrentPlayerIndex] == 7) || (sub->unk1F0 & 0x8000)) {
        return 0;
    }
    pred |= 0; // FAKE: second def of pred keeps the || copy out of copy propagation
    if ((arg0->state != 0x34) && (arg0->state != 0x36)) {
        if (sub) {} // FAKE: keeps sub live so the state byte takes v1
        pred &= 1;
    } else {
        pred = 0;
    }
    return pred;
}

void playerStateInitState23(void) {
    gCurrentActor->state = 0x23;
    gCurrentActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0x3BC);
}

void playerStateInitState5F(void) {
    gCurrentActor->state = 0x5F;
    gCurrentActor->unk155[0] = 0;
    EfA_P->unk1A3 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x4A);
}

extern s32 slotQueueGetValue(s32, u8);

void playerStateInitState60(void) {
    s32 selector;
    f32 unused;

    selector = 2;
    if (slotQueueGetValue(3, EfA_P->unk1A4) != 0) {
        selector = 3;
    }
    slotQueueUpdate(selector, 0, 0);
    gCurrentActor->state = 0x60;
    gCurrentActor->unk155[0] = 0;
    EfA_P->unk1A3 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x4B);
}

typedef struct EfN2Player {
    u8 pad0[0x64];
    s16 unk64;
    u8 pad66[0x62];
    s16 unkC8;
} EfN2Player;

void playerStateInitLaunchParams(void) {
    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
    case 0:
    case 1:
    case 2:
        EfA_A40->unkC0 = 50.0f;
        EfA_A40->unkC4 = -2.5f;
        break;
    case 3:
        EfA_A40->unkC0 = 140.0f;
        EfA_A40->unkC4 = -20.0f;
        break;
    case 4:
    case 5:
        EfA_A40->unkC0 = 40.0f;
        EfA_A40->unkC4 = -7.0f;
        break;
    }
    EfA_A40->unk154 = 0x2A;
    EfA_A40->unk155 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x43);
    ((EfN2Player *)gActivePlayerState)->unk64 = 0;
    ((EfN2Player *)gActivePlayerState)->unkC8 = 0x32;
}

void playerStateInitTumble(void) {
    EfA_P->unk4C = -1;
    EfA_P->unk38 = 170.0f;
    gCurrentActor->state = 0x3F;
    gCurrentActor->unk155[0] = 0;
    EfA_P->unk4E = 0;
    actorScriptStart(gCurrentActor, 0x14F);
}

typedef struct EfN2SubActor {
    u8 pad0[0xB2];
    s16 unkB2;
    f32 unkB4;
    f32 unkB8;
    s16 unkBC;
    u8 padBE[0x31];
    u8 unkEF;
    u8 unkF0;
    u8 padF1[2];
    s8 unkF3;
} EfN2SubActor;

typedef struct EfN2TargetActor {
    u8 pad0[0xB4];
    f32 unkB4;
} EfN2TargetActor;

void camSaveYaw(void *);
void camSetZoomLevel(void *, s32);
void func_806F0D68(Actor *);
void sfxStopSlotSound(Actor *, u8);

void playerStateTakeDamagePrep(void) {
    Actor *actor;
    s16 speed;
    s32 state;
    s16 state2;
    EfN2SubActor *subactor;
    u8 type;

    actor = EfA_P->unk104;
    subactor = actor->customState;
    if (gPlayerSlots && gPlayerSlots) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    type = subactor->unkEF;
    speed = subactor->unkB8;
    if (type != 0) {
        subactor->unkF0 = type;
        speed = 0x80;
    }
    camSaveYaw(EfA_P->unk104);
    camSetZoomLevel(EfA_P->unk104, 0);
    state = EfA_Q[gCurrentPlayerIndex].unk2A8;
    state2 = state;
    subactor->unkF3 = state2;
    if ((u8)state2 == 3) {
        sfxStopSlotSound(gActivePlayerActor, 0);
        sfxPlayOnFreeSlot(0x26, 0x7FFF, 63.0f, 1.0f, 0, 0);
        if (EfA_Q[gCurrentPlayerIndex].unk2AC != 0) {
            func_806F0D68(gActivePlayerActor);
        }
    }
    subactor->unkBC = 0x80;
    ((EfN2TargetActor *)EfA_P->unk104)->unkB4 = speed;
    subactor->unkB8 = speed;
    subactor->unkB2 = gActivePlayerActor->yaw + 0x800;
    gActivePlayerActor->speedXZ = 0.0f;
    gActivePlayerActor->contactFlags |= 0x2000;
}

void playerStateEnterKnockbackState2(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 2;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->unk155[0] = 0xA;
    if (EfA_P->unk8C != 0) {
        actorScriptStart(gActivePlayerActor, 0x23);
    } else {
        actorScriptStart(gActivePlayerActor, 0x13);
    }
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
}

void playerStateEnterKnockbackState4(void) {
    sfxPlayOnFreeSlot(0x1B9, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 4;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->unk155[0] = 0xA;
    actorScriptStart(gActivePlayerActor, 0x13);
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void playerStateEnterKnockbackState3(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 3;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->unk155[0] = 0xA;
    actorScriptStart(gActivePlayerActor, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
}

void playerStateEnterKnockbackState5(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 5;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->unk155[0] = 0xA;
    actorScriptStart(gActivePlayerActor, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void playerStateEnterState4F(void) {
    gCurrentActor->state = 0x4F;
    gCurrentActor->unk155[0] = 2;
    actorScriptStartByIndex(gCurrentActor, 0x34);
    EfA_P->unk50 = 0;
}

void playerStateEnterStunState1(void) {
    extern u32 gGlobalPauseFlags;

    gGlobalPauseFlags |= 0x4000;
    gActivePlayerActor->state = 1;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk4C = -1;
}

void playerStateEnterKnockbackState6(void) {
    gActivePlayerActor->state = 6;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk4C = -1;
    *(s32 *)((u8 *)gActivePlayerActor + 0x60) &= ~4;
}

void playerStateEnterElectrocute(void) {
    gActivePlayerActor->state = 0x6B;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk4C = -1;
    *(s32 *)((u8 *)gActivePlayerActor + 0x60) &= ~4;
}


typedef struct EfBActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x54];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x90];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x22];
    s32 unk178;
} EfBActor;

typedef struct EfBPlayer {
    u8 pad0[0x4C];
    s16 unk4C;
    u8 pad4E[2];
    s16 unk50;
    u8 pad52[0x36];
    EfBActor *unk88;
    u8 pad8C[0x3C];
    s16 unkC8;
    u8 padCA[0x126];
    s32 unk1F0;
    u8 pad1F4[0xA];
    s16 unk1FE;
} EfBPlayer;
typedef struct EfBCamera {
    u8 pad0[0x2A0];
    s32 unk2A0;
    u8 pad2A4[4];
    s32 unk2A8;
    u8 pad2AC[0x44];
} EfBCamera;

#define EFB_C ((EfBCamera *)gPlayerSlots)


#define EFB_P ((EfBPlayer *)gActivePlayerState)

void playerDropHeldActor(Actor *);
void behaviourAddSlotQueueValueB(s32);
void func_80026004();
void playerTransformAnimalStartSfx(Actor *);

void playerStateEnterSquish(void) {
    ((EfBActor *)gActivePlayerActor)->unk154 = 7;
    ((EfBActor *)gActivePlayerActor)->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x7A);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    EFB_P->unk88 = (EfBActor *)EFB_C[gCurrentPlayerIndex].unk2A0;
    gActivePlayerActor->flags &= 0xFFFBFFFF;
    ((EfBActor *)gActivePlayerActor)->unkB8 = 0.0f;
}

void playerStateSetFlag8(void) {
    gActivePlayerState->stateFlags |= 8;
}

void playerStateInitKongAction69(void) {
    ((EfBActor *)gActivePlayerActor)->unk154 = 0x69;
    ((EfBActor *)gActivePlayerActor)->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0.0f, 0.0f);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    gActivePlayerActor->flags &= 0xFEFFFFFF;
    EFB_P->unk88 = (EfBActor *)EFB_C[gCurrentPlayerIndex].unk2A0;
}

void playerStateAdjustUpwardVelocity(void) {
    EfBActor *actor;
    s32 arg;

    actor = EFB_P->unk88;
    arg = actor->unk178;
    if (actor->unk154 < 3) {
        func_80026004(arg, 0x1E, 0x3F800000);
    }
}

void playerStateAdjustUpwardVelocity200(void) {
    EfBActor *actor;

    actor = EFB_P->unk88;
    actor->unkC0 += 200.0f;
    actor = EFB_P->unk88;
    if (actor->unkC0 > 200.0f) {
        actor->unkC0 = 200.0f;
    }
    behaviourAddSlotQueueValueB(3);
}

void playerStateAdjustUpwardVelocity300(void) {
    EfBActor *actor;

    actor = EFB_P->unk88;
    actor->unkC0 += 300.0f;
    behaviourAddSlotQueueValueB(3);
}

void playerStateInitAnimalTransformation(void) {
    playerTransformAnimalStartSfx(gActivePlayerActor);
    EFB_P->unk1FE = EFB_C[gCurrentPlayerIndex].unk2A8;
}

void playerStateInitKongAction78(void) {
    actorScriptStart(gActivePlayerActor, 0x1A);
    ((EfBActor *)gActivePlayerActor)->unk154 = 0x78;
    ((EfBActor *)gActivePlayerActor)->unk155 = 0;
}

void playerStateDropAndResume(void) {
    playerDropHeldActor(gCurrentActor);
    playerResumeLocomotion(gCurrentActor);
}

typedef struct EfN2ModelSlot {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84];
} EfN2ModelSlot;

typedef struct EfN2PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
} EfN2PlayerState;

extern EfN2ModelSlot *gModelSlots;
extern s16 D_807539DC[];
extern s16 D_807539EC[];
void scriptSetActorRampTarget(Actor *, f32, f32);
void func_806F0C18(void *);
void actorClearMovementFlags(void *);
s32 hashTableLookup(s32);
void camStartPath(Actor *, s32, s32);
void controllerAnimSetStateIfChanged(Actor *, s32, f32, f32);
void actorCopyPoseAndScale(Actor *, Actor *, f32);
void controllerAnimSetStateRemap(Actor *, s32, f32, f32);

void playerStateEnterFlattened(void) {
    f32 speed;

    speed = 1.0f;
    func_806F0C18(gCurrentActor);
    gActivePlayerActor->state = 0x6C;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0x3B);
    if (gPlayerCharacterId[0] == 0) {
        speed = 0.5f;
    }
    scriptSetActorRampTarget(gActivePlayerActor, speed, 0.0f);
    actorClearMovementFlags(gActivePlayerActor);
    gActivePlayerActor->x = gModelSlots[hashTableLookup(gActivePlayerActor->cutsceneId)].unk0;
    gActivePlayerActor->y = gModelSlots[hashTableLookup(gActivePlayerActor->cutsceneId)].unk4 + 5.0f;
    gActivePlayerActor->z = gModelSlots[hashTableLookup(gActivePlayerActor->cutsceneId)].unk8;
    *(s16 *)((u8 *)gActivePlayerActor + 0xE4) = 0;
    *(s16 *)((u8 *)gActivePlayerActor + 0xE8) = 0;
    camStartPath(gActivePlayerActor, 0, 1);
    slotQueueUpdate(0, 1, 0);
}

void playerStateEnterSlideSlope(void) {
    s32 animation;

    *(u32 *)((u8 *)EfA_P->unk104->customState + 0xAC) |= 4;
    gActivePlayerActor->state = 0x6D;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    gActivePlayerActor->flags &= ~1;
    if (gCurrentMap == 0x27) {
        gActivePlayerActor->unk144 = 1;
    }
    EFB_P->unk88 = (EfBActor *)EFB_C[gCurrentPlayerIndex].unk2A0;
    if (gActivePlayerActor->actorType == 2) { animation = 0x53; } else { animation = 0x1C7; } controllerAnimSetStateIfChanged(gActivePlayerActor, (s16)animation, 0.0f, 0.0f); // LAYOUT: one source line steers the scheduler (li at,2 after mfc1)
}

void playerStateEnterFrozen(void) {
    Actor *actor;

    gActivePlayerActor->state = 0x75;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    gActivePlayerActor->flags &= ~1;
    EFB_P->unk88 = (EfBActor *)EFB_C[gCurrentPlayerIndex].unk2A0;
    actor = (Actor *)EFB_P->unk88;
    actorCopyPoseAndScale(gActivePlayerActor, actor, actor->sub4->scaleX);
    gActivePlayerActor->unk144 = 1;
    controllerAnimSetStateIfChanged(gActivePlayerActor, 0x22A, 0.0f, 0.0f);
}

void playerStateEnterState3C(void) {
    ((EfN2PlayerState *)gActivePlayerState)->unk12 = D_807539EC[gCurrentCharacterIndex];
    ((EfN2PlayerState *)gActivePlayerState)->unk14 = gCurrentActor->yaw;
    ((EfN2PlayerState *)gActivePlayerState)->unk10 = D_807539DC[gCurrentCharacterIndex];
    gCurrentActor->state = 0x4F;
    gCurrentActor->unk155[0] = 1;
    if (gCurrentActor->speedY > 0.0f) {
        gCurrentActor->speedY = 0.0f;
    }
    actorScriptStartByIndex(gCurrentActor, 0x36);
    controllerAnimSetStateRemap(gCurrentActor, 0x31, 0.0f, 8.0f);
    scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
}

typedef struct EfN3PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0xA];
    f32 unk1C;
    u8 pad20[0xC];
    f32 unk2C;
    f32 unk30;
    u8 pad34[4];
    f32 unk38;
    u8 pad3C[0xC];
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    f32 unk54;
    s32 unk58;
    u8 pad5C[0x94];
    f32 unkF0;
    u8 padF4[0x18];
    s8 unk10C;
    u8 pad10D[0xA3];
    u8 pad1B0[8];
} EfN3PlayerState;

typedef struct EfN3Actor {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x24];
    f32 unk80;
    u8 pad84[0x1C];
    f32 unkA0;
    u8 padA4[8];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x2A];
    s16 unkEE;
    u8 padF0[4];
    s16 arcYawMin;
    u8 padF6[0x5E];
    u8 unk154;
    u8 unk155;
} EfN3Actor;


typedef struct EfN3Camera {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F];
} EfN3Camera;

#define EFN3_P ((EfN3PlayerState *)gActivePlayerState)
#define EFN3_A40 ((EfN3Actor *)gCurrentActor)
#define EFN3_A48 ((EfN3Actor *)gActivePlayerActor)
#define EFN3_C ((EfN3Camera *)gPlayerSlots)

extern f32 D_807531C4[];
extern f32 gKongTurnDecelRates[];
extern f32 D_807534E4[];
extern f32 D_80753500[];
extern s16 D_8075351C[];
extern f32 D_80753908[];
extern f32 D_80753924[];
extern f32 D_80753940[];
extern f32 D_80753D70[];
extern f32 D_80753D8C[];
extern s32 D_80767CC0;
extern f32 gKongCannonInitialPitch[];
extern s16 D_8075388C[];
extern s16 D_807538D8[];
extern s16 D_807538E8[];
extern s16 D_807538F8[];
extern f32 D_80753988[];
extern s16 D_807539FC[];
extern f32 D_80753A5C[];
void playerThrowHeldActor(Actor *);

void playerStateCheckLandingAir(void) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_fs0;
    f32 var_ft5;
    f32 var_ft5b;

    playerThrowHeldActor(gActivePlayerActor);
    temp_fv0 = D_80753A5C[gCurrentCharacterIndex];
    if (temp_fv0 > 0.0f) {
        var_fs0 = temp_fv0;
    } else {
        var_fs0 = -temp_fv0;
    }
    temp_ft4 = EFN3_A48->unkAC;
    temp_fv0_2 = D_807538D8[gCurrentCharacterIndex];
    var_ft5 = EFN3_A48->unkA0 - temp_ft4;
    if (temp_fv0_2 < var_ft5) {
        var_ft5 = temp_fv0_2;
    }
    temp_fa0 = D_807538E8[gCurrentCharacterIndex] + ((D_807538F8[gCurrentCharacterIndex] - D_807538E8[gCurrentCharacterIndex]) * (var_ft5 / temp_fv0_2));
    temp_fa0 -= (temp_ft4 - D_8075388C[gCurrentCharacterIndex]) - EFN3_A48->unk80;
    temp_fa0 *= 40.0f;
    var_ft5 *= 40.0f;
    temp_fv0_2 *= 40.0f;
    if (temp_fa0 > 0.0f) {
        var_fa1 = EFN3_A48->unkC0;
        var_fa1 = (f32)((f64)var_fa1 * (0.5 + (f64)(var_ft5 / (2 * temp_fv0_2))));
        var_ft5b = (var_fa1 * var_fa1) / (2 * temp_fa0);
        if (var_ft5b < var_fs0) {
            var_ft5b = var_fs0;
        }
    } else {
        var_fa1 = 0.0f;
        var_ft5b = var_fs0;
    }
    EFN3_A48->unkC0 = var_fa1;
    EFN3_P->unk1C = var_ft5b;
    EFN3_P->unk10 = 0;
    EFN3_P->unk30 = gKongCannonInitialPitch[gCurrentCharacterIndex];
    temp_fv0_3 = EFN3_A40->unkB8;
    temp_fv1 = D_80753988[gCurrentCharacterIndex];
    if (temp_fv0_3 < temp_fv1) {
        EFN3_A40->unkB8 = temp_fv0_3;
    } else {
        EFN3_A40->unkB8 = temp_fv1;
    }
    EFN3_A48->unk154 = 0x4E;
    EFN3_A48->unk155 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x35);
    EFN3_P->unk48 = D_807539FC[gCurrentCharacterIndex];
}


void playerStateEnterKnockbackRecovery(void) {
    EFN3_A48->unk154 = 0x51;
    EFN3_A48->unk155 = 0;
    EFN3_P->unk54 = D_80753908[gCurrentCharacterIndex];
    EFN3_P->unk50 = 0;
    EFN3_P->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex];
    EFN3_P->unk2C = D_80753924[gCurrentCharacterIndex];
    EFN3_P->unk30 = D_80753940[gCurrentCharacterIndex];
    actorScriptStartByIndex(gActivePlayerActor, 0x3E);
    scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
    EFN3_P->unk58 = D_80767CC0 - 0x1E;
}

void playerStateEnterDamageKnockback(void) {
    f32 current;
    f32 limit;

    EFN3_A48->unk154 = 0x50;
    EFN3_A48->unk155 = 0;
    EFN3_A40->unkC0 = -10.0f;
    EFN3_P->unk50 = 0;
    current = EFN3_A40->unkB8;
    limit = D_807531C4[gCurrentCharacterIndex];
    if (current < limit) {
        EFN3_A40->unkB8 = current;
    } else {
        EFN3_A40->unkB8 = limit;
    }
    EFN3_P->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex];
    actorScriptStartByIndex(gActivePlayerActor, 0x3C);
}

typedef struct EfN3bTarget {
    u8 pad0[0x54];
    s32 unk54;
    s32 unk58;
} EfN3bTarget;

typedef struct EfN3bPlayerState {
    u8 pad0[0x1B0];
    EfN3bTarget *unk1B0;
    s32 unk1B4;
} EfN3bPlayerState;

#define EFN3B_P ((EfN3bPlayerState *)gActivePlayerState)

extern Actor *D_807FBB90;

void playerStateEnterAirDamageReaction(void) {
    EFN3B_P->unk1B0 = (EfN3bTarget *)D_807FBB90;
    EFN3B_P->unk1B4 = EFN3B_P->unk1B0->unk54;
    switch ((u32)EFN3B_P->unk1B0->unk58) {
    case 0x3D:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x55:
    case 0x82:
        actorScriptStart(gActivePlayerActor, 0x1C8);
        break;
    default:
        actorScriptStartByIndex(gActivePlayerActor, 0x2B);
        break;
    }
    EFN3_A48->unk154 = 0x47;
    EFN3_A48->unk155 = 0;
}

void playerStateEnterGroundImpact(void) {
    actorScriptStartByIndex(gActivePlayerActor, 8);
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    controllerAnimSetStateRemap(gActivePlayerActor, 0x2E, 0.0f, 6.0f);
    EFN3_A48->unk154 = 0x46;
    EFN3_A48->unk155 = 0;
    EFN3_P->unk38 = D_807534E4[gCurrentCharacterIndex];
    EFN3_P->unk2C = D_80753500[gCurrentCharacterIndex];
    EFN3_P->unk48 = D_8075351C[gCurrentCharacterIndex];
    EFN3_P->unk4C = -1;
}

void playerStateEnterAction24(void) {
    ((EfBActor *)gCurrentActor)->unk154 = 0x24;
    ((EfBActor *)gCurrentActor)->unk155 = 0;
    actorScriptStart(gCurrentActor, 0x1B2);
    EFB_P->unkC8 = 0x32;
}

void actorScriptExecute(Actor *);

void playerStateEnterHoldThrow(void) {
    f32 value;

    if (EFN3_C[gCurrentPlayerIndex].unk2C0 == 1) {
        value = D_80753D70[gCurrentCharacterIndex];
    } else {
        value = D_80753D8C[gCurrentCharacterIndex];
    }
    EFN3_A48->unk154 = 0x5B;
    EFN3_A48->unk155 = 0;
    EFN3_P->unk10C = (s8)value;
    EFN3_A48->unk80 = EFN3_P->unkF0 - EFN3_P->unk10C;
    EFN3_A48->unkEE = EFN3_A48->arcYawMin + 0x14;
    EFN3_A48->unkC0 = 0.0f;
    actorScriptStartByIndex(gActivePlayerActor, 0x75);
    actorScriptExecute(gActivePlayerActor);
}


void playerStateEnterState57(void) {
    gActivePlayerActor->contactFlags |= 0x40;
    gActivePlayerActor->renderFlags &= ~0x2000;
    gActivePlayerActor->state = 0x57;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x69);
    actorScriptExecute(gActivePlayerActor);
}

typedef struct EfN4PlayerState {
    u8 pad0[0x3C];
    s16 unk3C;
    u8 pad3E[0xA];
    s16 unk48;
    u8 pad4A[6];
    s16 unk50;
    u8 pad52[2];
    f32 unk54;
    u8 pad58[0xC];
    s16 unk64;
    u8 pad66[2];
    f32 unk68;
    u8 pad6C[0x20];
    u8 unk8C;
    u8 pad8D[0x2F];
    s16 unkBC;
    s16 unkBE;
    u8 padC0[0x44];
    Actor *unk104;
    u8 pad108[0x1C];
    f32 unk124;
} EfN4PlayerState;

typedef struct EfN4Cam {
    u8 pad0[0x2A0];
    Actor *unk2A0;
    u8 pad2A4[0x1C];
    u8 unk2C0;
    u8 pad2C1[0x2F];
} EfN4Cam;

#define EfN4PS ((EfN4PlayerState *)gActivePlayerState)
#define EfN4CamBlocks ((EfN4Cam *)gPlayerSlots)

typedef struct EfN4ActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfN4ActorC0;

extern s32 gGlobalCutsceneFlags;
extern f32 D_807535CC[];
extern s16 D_8075380C[];
void camStartBlendRamp(void *, s32);
s16 actorListFindIdByActor(Actor *);
void playerSetBaseGravity(void);
void playerClearCarriedItemState(void);



void playerStateEnterState59(void) {
    void *callback;

    callback = EfN4PS->unk104->customState;
    gActivePlayerActor->contactFlags |= 0x40;
    gActivePlayerActor->renderFlags &= ~0x2000;
    gActivePlayerActor->state = 0x59;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x70);
    actorScriptExecute(gActivePlayerActor);
    camStartBlendRamp(callback, 0x14);
}

void playerStateEnterState17(void) {
    void *callback;

    callback = EfN4PS->unk104->customState;
    gCurrentActor->state = 0x17;
    gCurrentActor->unk155[0] = 0;
    if (gGlobalCutsceneFlags & 2) {
        EfN4PS->unk54 = D_807535CC[gCurrentCharacterIndex] * 1.3;
    } else {
        EfN4PS->unk54 = D_807535CC[gCurrentCharacterIndex];
    }
    gActivePlayerActor->speedXZ = EfN4PS->unk124;
    EfN4PS->unk50 = 0;
    EfN4PS->unk3C = 0xA;
    actorScriptStartByIndex(gCurrentActor, 0x10);
    camStartBlendRamp(callback, 0x14);
}


s32 playerCanTakeHit(Actor *);
void playerTakeDamage(s16);

void playerStateTakeHitAndDamage(void) {
    s32 value;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        value = 1;
        if (gGlobalCutsceneFlags & 2) {
            value = 0;
        } else {
            value = 1;
        }
        playerTakeDamage((s16)value);
    }
}

void playerStateEnterState10(void) {
    if ((gPlayerCount >= 2) || (gActivePlayerActor->actorType != 6) || (EfN4CamBlocks[gCurrentPlayerIndex].unk2C0 == 1)) {
        ((EfN4ActorC0 *)gActivePlayerActor)->unkC0 = 260.0f;
        playerSetBaseGravity();
        EfN4PS->unk50 = 0;
        EfN4PS->unk48 = 0x64;
        actorScriptStartByIndex(gActivePlayerActor, 0x1F);
        scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
        gActivePlayerActor->state = 0x30;
        gActivePlayerActor->unk155[0] = 0;
        playerDropHeldActor(gActivePlayerActor);
    }
}


typedef struct EfCActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfCActorC0;

typedef struct EfCPlayer48 {
    u8 pad0[0x50];
    s16 unk50;
} EfCPlayer48;


void playerStateEnterState11(void) {
    ((EfCActorC0 *)gActivePlayerActor)->unkC0 = 260.0f;
    playerSetBaseGravity();
    ((EfCPlayer48 *)gActivePlayerState)->unk50 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x20);
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    gActivePlayerActor->state = 0x30;
    gActivePlayerActor->unk155[0] = 0;
    playerDropHeldActor(gActivePlayerActor);
}

typedef struct EfCPlayer68 {
    u8 pad0[0x50];
    s16 unk50;
    u8 pad52[0x16];
    f32 unk68;
} EfCPlayer68;

extern s16 D_807537FC[];
extern s16 D_8075383C[];
extern s16 D_8075384C[];

void playerStateEnterState12(void) {
    ((EfCPlayer68 *)gActivePlayerState)->unk50 = D_807537FC[gCurrentCharacterIndex];
    ((EfCPlayer68 *)gActivePlayerState)->unk68 += D_8075383C[gCurrentCharacterIndex];
    if (D_8075384C[gCurrentCharacterIndex] < ((EfCPlayer68 *)gActivePlayerState)->unk68) {
        ((EfCPlayer68 *)gActivePlayerState)->unk68 = D_8075384C[gCurrentCharacterIndex];
    }
    ((EfCActorC0 *)gActivePlayerActor)->unkC0 = 0.0f;
    ((EfCPlayer68 *)gActivePlayerState)->unk50 = 0;
}

void playerStateEnterState29(void) {
    if ((gCurrentActor->state != 2) && (gPlayerCharacterId[gCurrentPlayerIndex] == 6)) {
        gCurrentActor->state = 0x29;
        gCurrentActor->unk155[0] = 0;
        actorScriptStartByIndex(gCurrentActor, 0x3F);
        EfN4PS->unk64 = 0;
        EfN4PS->unk68 = D_8075380C[gCurrentCharacterIndex];
    }
}


void playerStateEnterState15ThrowHeldActor(void) {
    Actor *target;

    playerClearCarriedItemState();
    playerThrowHeldActor(gActivePlayerActor);
    EfN4PS->unk8C = 0;
    func_806F0C18(gCurrentActor);
    sfxStopSlotSound(gCurrentActor, 0);
    sfxStopSlotSound(gCurrentActor, 1);
    actorScriptStartByIndex(gActivePlayerActor, 0x21);
    target = EfN4CamBlocks[gCurrentPlayerIndex].unk2A0;
    if (target != NULL) {
        EfN4PS->unkBC = target->actorType;
        EfN4PS->unkBE = actorListFindIdByActor(EfN4CamBlocks[gCurrentPlayerIndex].unk2A0);
    } else {
        EfN4PS->unkBC = 0;
        EfN4PS->unkBE = -1;
    }
    if (gCurrentActor->contactFlags & 4) {
        gActivePlayerActor->state = 0x43;
        gActivePlayerActor->unk155[0] = 0;
        return;
    }
    gActivePlayerActor->state = 0x42;
    gActivePlayerActor->unk155[0] = 0;
}

typedef struct EfN8PlayerD4 {
    u8 pad0[0xD4];
    s16 unkD4;
} EfN8PlayerD4;
extern s16 D_807530B0[];
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);

typedef struct EfdAPlayer {
    u8 pad0[0x88];
    Actor *unk88;
} EfdAPlayer;

void playerStateDamageTargetCheck(void) {
    Actor *camTarget;
    Actor *target;
    f32 zero;
    f32 v;

    target = ((EfdAPlayer *)gActivePlayerState)->unk88;
    zero = 0.0f;
    if (target->speedXZ >= zero) {
        behaviourAddSlotQueueValueB(3);
        target = ((EfdAPlayer *)gActivePlayerState)->unk88;
    }
    camTarget = ((EfAQueuedCall *)gPlayerSlots)[gCurrentPlayerIndex].unk2A0;
    if (camTarget != NULL) {
        if (camTarget->speedXZ != zero) {
            v = camTarget->speedXZ > zero ? camTarget->speedXZ : -camTarget->speedXZ;
            target->speedXZ = (f32)(2.0 * (f64)v);
        } else {
            v = target->speedXZ > zero ? target->speedXZ : -target->speedXZ;
            target->speedXZ = v < 50.0f ? -50.0f : -(target->speedXZ > zero ? target->speedXZ : -target->speedXZ);
        }
    } else {
        v = target->speedXZ > zero ? target->speedXZ : -target->speedXZ;
        target->speedXZ = v < 50.0f ? -50.0f : -(target->speedXZ > zero ? target->speedXZ : -target->speedXZ);
    }
    actorScriptStart(((EfdAPlayer *)gActivePlayerState)->unk88, 0x292);
    if (gActivePlayerState && gActivePlayerState) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (gActivePlayerActor->state != 9) {
        actorScriptStartByIndex(gActivePlayerActor, 0x83);
    }
}


void playerStateDamageCheck4(void) {
    f32 divisor;
    u8 character;

    if (((EfN8PlayerD4 *)gActivePlayerState)->unkD4 == 0) {
        playerClearCarriedItemState();
        behaviourAddSlotQueueValueB(3);
        character = gPlayerCharacterId[gCurrentPlayerIndex];
        divisor = 2.0f;
        if (character != 2) {
            if (character == 3) {
                sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xB9, 0xFF, 0x7F, 0x14);
            }
        } else {
            sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xD2, 0xFF, 0x7F, 0x14);
        }
        ((EfN8PlayerD4 *)gActivePlayerState)->unkD4 = D_807530B0[gCurrentCharacterIndex];
        gActivePlayerActor->speedXZ = gActivePlayerActor->speedXZ / divisor;
    }
}

s32 flagGet(s16, s32);
void flagSet(s16, s32, s32);

void playerStatePlayAnimationByDamageType(u16 arg0) {
    u16 ev;
    s16 anim;

    switch (arg0) {
    case 0x12:
        ev = 0x16D;
        anim = 0x23;
        break;
    case 0x81:
        ev = 0x16E;
        anim = 0x24;
        break;
    }
    if (flagGet(ev, 0) == 0) {
        if (arg0 == 0x81) {
            gActivePlayerActor->speedXZ = 0.0f;
        }
        camStartPath(NULL, anim, 5);
        flagSet(ev, 1, 0);
    }
}

void playerStateApplyAttackerDamage(Actor *arg0) {
    s16 id;
    u16 state;
    s32 ev;

    state = arg0->actorType;
    id = actorListFindIdByActor(arg0);
    switch (gCurrentMap) {
    case 26:
        if (id == 0x11) {
            return;
        }
        break;
    case 48:
        if (id == 0x17) {
            return;
        }
        break;
    }
    switch (state) {
    case 0x19:
        ev = 0x169;
        break;
    case 0x28:
        ev = 0x168;
        break;
    case 0x39:
        ev = 0x16B;
        break;
    case 0x38:
        ev = 0x16A;
        break;
    default:
        return;
    }
    if (flagGet(ev, 0) == 0) {
        camStartPath(NULL, 0x16, 5);
        flagSet(ev, 1, 0);
    }
}

typedef struct EfL1PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x22];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x1A];
    f32 unk6C;
    s16 unk70;
    u8 pad72[2];
    f32 unk74;
    u8 pad78[0x14];
    u8 unk8C;
    u8 pad8D[0x161];
    s16 unk1EE;
    s32 unk1F0;
    s32 unk1F4;
} EfL1PlayerState;

typedef struct EfL1Actor {
    u8 pad0[0x58];
    u32 unk58;
    u8 pad5C[4];
    s32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u8 pad6C[0x14];
    f32 unk80;
    u8 pad84[0x28];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0x22];
    s16 unkE6;
    u8 padE8[6];
    s16 unkEE;
    u8 padF0[0x38];
    s16 unk128;
    u8 pad12A[0x2A];
    u8 unk154;
    u8 unk155;
} EfL1Actor;

typedef struct EfL1CamBlock {
    u8 pad0[0x2A0];
    EfL1Actor *unk2A0;
    u8 pad2A4[0x4C];
} EfL1CamBlock;

typedef struct EfL1Global568 {
    u8 pad0[2];
    u8 unk2;
} EfL1Global568;

#define EfL1PS ((EfL1PlayerState *)gActivePlayerState)
#define EfL1Cam ((EfL1CamBlock *)gPlayerSlots)
#define EfL1G568 ((EfL1Global568 *)D_807FD568)
#define EfL1A40 ((EfL1Actor *)gCurrentActor)
#define EfL1A48 ((EfL1Actor *)gActivePlayerActor)

extern void *D_807FD568;
Actor *actorFindByType(s32);
void actorSpawnChildActor(Actor *);
void effectSpawnActorOrbitParticles(Actor *);
void actorSetInteractionTimer(Actor *);
s32 playerGetResolvedKongId(s32);
void playerSetKongByActorType(s16);
void playerEnterFall(Actor *);
void playerSetSizeMode(Actor *, s32);
void playerStatePlayAnimationByDamageType(u16);
void playerStateApplyAttackerDamage(Actor *);

void playerStateSetLaunchVelocity(void) {
    u8 flag;
    s32 selector;
    s32 value;

    flag = 0;
    EfL1A48->unkB8 = EfL1PS->unk6C;
    EfL1A48->unkEE = EfL1PS->unk70;
    EfL1A48->unkE6 = EfL1PS->unk70;
    EfL1A48->unkC0 = EfL1PS->unk74;
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    if (EfL1Cam[gCurrentPlayerIndex].unk2A0 == NULL) {
        EfL1A48->unk154 = 0x44;
        EfL1A48->unk155 = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x22);
        EfL1PS->unk50 = 0x14;
        playerSetBaseGravity();
    } else {
        switch (EfL1Cam[gCurrentPlayerIndex].unk2A0->unk58) {
        case 0x17:
        case 0xA7:
            EfL1A48->unk154 = 0x45;
            EfL1A48->unk155 = 0;
            actorScriptStartByIndex(gActivePlayerActor, 0x22);
            EfL1PS->unk50 = 0x14;
            playerSetBaseGravity();
            break;
        case 0x11:
            EfL1A48->unk154 = 0x44;
            EfL1A48->unk155 = 0;
            actorScriptStartByIndex(gActivePlayerActor, 0x22);
            EfL1PS->unk50 = 0x14;
            playerSetBaseGravity();
            break;
        case 0x1C:
        case 0x6B:
        case 0x86:
            if (actorFindByType(0x25) != NULL) {
                EfL1A48->unk154 = 0x63;
                EfL1A48->unk155 = 0;
                actorScriptStart(gActivePlayerActor, 0x7D);
                EfL1A48->unkB8 = 0.0f;
                EfL1PS->unk38 = 300.0f;
                flag = 1;
                slotQueueUpdate(5, 1, 0);
                break;
            }
        case 0x62:
        case 0x88:
        case 0x89:
            actorSetInteractionTimer(gActivePlayerActor);
            playerEnterFall(gCurrentActor);
            playerSetBaseGravity();
            break;
        case 0x19:
        case 0x28:
        case 0x60:
            if (EfL1Cam[gCurrentPlayerIndex].unk2A0->unk58 == 0x28) {
                selector = 0;
            } else {
                selector = 2;
            }
            playerSetSizeMode(gActivePlayerActor, selector & 0xFF);
            if (EfL1A48->unk58 == 6) {
                EfL1A48->unk60 &= 0xFFFF7FFF;
            } else {
                EfL1A48->unk60 |= 0x8000;
            }
            playerResumeLocomotion(gActivePlayerActor);
            break;
        case 0x39:
            EfL1PS->unk1F0 |= 0x10;
            EfL1A48->unk60 &= 0xFFFF7FFF;
            EfL1A48->unk128 = 0x7F;
            effectSpawnActorOrbitParticles(gActivePlayerActor);
            playerEnterFall(gCurrentActor);
            playerSetBaseGravity();
            break;
        case 0x38:
            EfL1PS->unk1F0 |= 0x20;
            EfL1A48->unk154 = 0x41;
            EfL1A48->unk155 = 0;
            actorScriptStart(gActivePlayerActor, 0x156);
            EfL1A48->unkB8 = 0.0f;
            EfL1PS->unk50 = 4;
            playerSetTerminalVelocity5B0();
            break;
        case 0x31:
            EfL1A48->unk154 = 0x63;
            EfL1A48->unk155 = 0;
            actorScriptStart(gActivePlayerActor, 0x7D);
            EfL1A48->unkB8 = 0.0f;
            EfL1PS->unk38 = 300.0f;
            break;
        case 0x12:
        case 0x81:
            EfL1PS->unk1EE = EfL1A48->unk58;
            if (EfL1Cam[gCurrentPlayerIndex].unk2A0->unk58 == 0x12) {
                playerSetKongByActorType(8);
                EfL1A48->unk154 = 0xC;
                EfL1A48->unk155 = 0;
                actorScriptStartByIndex(gActivePlayerActor, 9);
                EfL1A48->unkB8 = 0.0f;
            } else {
                playerSetKongByActorType(9);
                if (EfL1A48->unkAC < EfL1A48->unk80) {
                    EfL1A48->unk154 = 0x82;
                    EfL1A48->unk155 = 0;
                } else {
                    EfL1A48->unk154 = 0x7F;
                    EfL1A48->unk155 = 0;
                }
                actorScriptStart(gActivePlayerActor, 0x317);
                EfL1A48->unkB8 = 100.0f;
            }
            EfL1PS->unk50 = 4;
            playerSetTerminalVelocity5B0();
            playerStatePlayAnimationByDamageType(*(u16 *)((u8 *)EfL1Cam[gCurrentPlayerIndex].unk2A0 + 0x5A));
            break;
        case 0x84:
            value = playerGetResolvedKongId(gCurrentPlayerIndex);
            if (value != gPlayerCharacterId[gCurrentPlayerIndex]) {
                playerSetKongByActorType((s16)(value + 2));
            }
            actorSpawnChildActor(gActivePlayerActor);
            break;
        }
    }
    if (((EfL1Cam[gCurrentPlayerIndex].unk2A0 != NULL) && (EfL1Cam[gCurrentPlayerIndex].unk2A0->unk58 == 0x31)) || (flag != 0)) {
        if (EfL1G568->unk2 & 1) {
            if (EfL1PS->unk8C != 0) {
                EfL1PS->unk1F4 |= 4;
            } else {
                EfL1PS->unk1F4 &= ~4;
            }
            EfL1PS->unk8C = 1;
            func_806F0D68(gActivePlayerActor);
        }
    } else {
        func_806F0C18(gCurrentActor);
    }
    if (EfL1Cam[gCurrentPlayerIndex].unk2A0 != NULL) {
        playerStateApplyAttackerDamage((Actor *)EfL1Cam[gCurrentPlayerIndex].unk2A0);
    }
    if ((EfL1A48->unk6A & 4) && (EfL1Cam[gCurrentPlayerIndex].unk2A0->unk58 != 0x81)) {
        EfL1PS->unk12 = D_807539EC[gCurrentCharacterIndex];
        EfL1PS->unk14 = EfL1A40->unkE6;
        EfL1PS->unk10 = (s16)((f64)D_807539DC[gCurrentCharacterIndex] * 0.5);
        EfL1A40->unk154 = 0x4F;
        EfL1A40->unk155 = 1;
        if (EfL1A40->unkC0 > 0.0f) {
            EfL1A40->unkC0 = 0.0f;
        }
        actorScriptStartByIndex(gCurrentActor, 0x36);
        controllerAnimSetStateRemap(gCurrentActor, 0x31, 0.0f, 8.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
    }
}


typedef struct EfCPlayerState {
    u8 pad0[0x1EE];
    s16 unk1EE;
} EfCPlayerState;

void playerSetKongByActorType(s16);

void playerRevertToSavedKong(void) {
    playerSetKongByActorType(((EfCPlayerState *)gActivePlayerState)->unk1EE);
    playerResumeLocomotion(gActivePlayerActor);
}


void playerStateThrowHeldActorAndResume(void) {
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x55;
    gActivePlayerActor->unk155[0] = 0;
}

typedef struct EfCPlayerState06 {
    u8 pad0[0x38];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x36];
    Actor *unk88;
} EfCPlayerState06;

typedef struct EfCCamBlock {
    u8 pad0[0x2A0];
    Actor *unk2A0;
    u8 pad2A4[0x4C];
} EfCCamBlock;

#define EfCCam ((EfCCamBlock *)gPlayerSlots)

void playerStateThrowHeldActorWithScript(void) {
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x56;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x87);
    ((EfCPlayerState06 *)gActivePlayerState)->unk50 = 0;
    ((EfCPlayerState06 *)gActivePlayerState)->unk38 = 0.0f;
    ((EfCPlayerState06 *)gActivePlayerState)->unk88 = EfCCam[gCurrentPlayerIndex].unk2A0;
}

typedef struct EfCPlayerD4 {
    u8 pad0[0xD4];
    s16 unkD4;
} EfCPlayerD4;

s32 func_806C9974(u8, s8);

void playerStateEnterDamageTake(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        playerClearCarriedItemState();
        if (func_806C9974(gCurrentPlayerIndex, -1) != 0) {
            if (gActivePlayerActor->contactFlags & 4) {
                actorScriptStartByIndex(gActivePlayerActor, 0x29);
            } else {
                actorScriptStartByIndex(gActivePlayerActor, 0x27);
            }
            gActivePlayerActor->state = 0x36;
            gActivePlayerActor->unk155[0] = 0;
        }
        ((EfCPlayerD4 *)gActivePlayerState)->unkD4 = D_807530B0[gCurrentCharacterIndex];
    }
}


typedef struct EfCActorC0S32 {
    u8 pad0[0xC0];
    s32 unkC0;
} EfCActorC0S32;

void actorAppendCallback4000(Actor *, s32, s16, s32, s32);

void playerStateAttachHeldActorToPlayer(void) {
    s32 value = (s32)gActivePlayerState->heldActor;

    if (value != 0) {
        actorAppendCallback4000(gCurrentActor, value, gActivePlayerActor->yaw,
                      ((EfCActorC0S32 *)gCurrentActor)->unkC0, (s32)gCurrentActor->speedXZ);
        gActivePlayerState->heldActor = NULL;
        gActivePlayerState->queuedHeldActor = NULL;
    }
    playerClearCarriedItemState();
    actorScriptStartByIndex(gCurrentActor, 0x1C);
    gActivePlayerActor->state = 0x20;
    gActivePlayerActor->unk155[0] = 0;
}


void playerStateEnterSlideRecover(void) {
    playerClearCarriedItemState();
    actorScriptStartByIndex(gCurrentActor, 0x1C);
    gActivePlayerActor->state = 0x21;
    gActivePlayerActor->unk155[0] = 0;
}



void playerStateDamageSelector(void) {
    s32 value = 1;
    s8 selector;
    Actor *target;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        selector = -1;
        playerClearCarriedItemState();
        target = EfCCam[gCurrentPlayerIndex].unk2A0;
        if ((target != NULL) && (target->actorType == 0x123)) {
            selector = -2;
        }
        if (func_806C9974(gCurrentPlayerIndex, selector) != 0) {
            value = 0;
            if (gActivePlayerActor->contactFlags & 4) {
                actorScriptStartByIndex(gActivePlayerActor, 0x29);
            } else {
                actorScriptStartByIndex(gActivePlayerActor, 0x27);
            }
            gActivePlayerActor->state = 0x36;
            gActivePlayerActor->unk155[0] = 0;
        } else {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
            actorScriptStartByIndex(gCurrentActor, 0x1E);
            gCurrentActor->state = 0x20;
            gCurrentActor->unk155[0] = 1;
        }
    }
    if ((((EfCPlayerD4 *)gActivePlayerState)->unkD4 == 0) && (gPlayerCount < 2)) {
        ((EfCPlayerD4 *)gActivePlayerState)->unkD4 = D_807530B0[gCurrentCharacterIndex];
    }
    if (value != 0) {
        camStartShake(gActivePlayerState->camActor, 0x14, 0x14);
    }
}

void playerTakeFallDamage(void) {
    s32 shouldNotify = 1;

    playerClearCarriedItemState();
    if ((playerCanTakeHit(gActivePlayerActor) != 0) && (func_806C9974(gCurrentPlayerIndex, -1) != 0)) {
        shouldNotify = 0;
        if ((gActivePlayerActor->contactFlags & 4) != 0) {
            actorScriptStartByIndex(gActivePlayerActor, 0x29);
        } else {
            actorScriptStartByIndex(gActivePlayerActor, 0x27);
        }
        gActivePlayerActor->state = 0x36;
        gActivePlayerActor->unk155[0] = 0;
    } else {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
        actorScriptStartByIndex(gCurrentActor, 0x1E);
        gCurrentActor->state = 0x20;
        gCurrentActor->unk155[0] = 1;
    }
    if ((((EfCPlayerD4 *)gActivePlayerState)->unkD4 == 0) && (gPlayerCount < 2)) {
        ((EfCPlayerD4 *)gActivePlayerState)->unkD4 = D_807530B0[gCurrentCharacterIndex];
    }
    if (shouldNotify != 0) {
        camStartShake(gActivePlayerState->camActor, 0x14, 0x14);
    }
}

typedef struct {
    u8 pad0[0x2A8];
    s32 unk2A8;
    u8 pad2AC[0x44];
} EfDE5Player;

extern void playerClearCarriedItemState(void);
extern void actorScriptStartByIndex(Actor *, s32);
extern void sfxStopChannel(s32, s32);

void playerStateStopSfxAndClearCarried(void) {
    playerClearCarriedItemState();
    sfxStopChannel(0x6B, 0);
    gCurrentActor->yawSpeed = ((EfDE5Player *)gPlayerSlots)[gCurrentPlayerIndex].unk2A8;
    actorScriptStartByIndex(gCurrentActor, 0x1D);
    gActivePlayerActor->state = 0x6F;
    gActivePlayerActor->unk155[0] = 0;
}

extern void playerSetBaseGravity(void);
extern void playerEnterFall(Actor *);

void playerStateEnterFallAndSetGravity(void) {
    playerSetBaseGravity();
    playerEnterFall(gCurrentActor);
}

extern void playerThrowHeldActor(Actor *);
extern void playerResumeLocomotion(Actor *);

void playerStateSwimTreadWithScript(void) {
    playerThrowHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x32);
    gActivePlayerActor->state = 0x52;
    gActivePlayerActor->unk155[0] = 0;
}

void func_806EE6B0(void) {
    playerThrowHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x86);
    gActivePlayerActor->state = 0x53;
    gActivePlayerActor->unk155[0] = 0;
}

void playerResumeLocomotionAndThrow(void) {
    playerThrowHeldActor(gActivePlayerActor);
    playerResumeLocomotion(gActivePlayerActor);
    gActivePlayerActor->state = 0x54;
    gActivePlayerActor->unk155[0] = 0;
}

extern s32 playerCanTakeHit(Actor *);
extern s16 D_807FD6F2;
extern void playerTakeDamage(s16);

typedef struct EfN7TransitionState {
    u8 pad0[0x88];
    Actor *unk88;
} EfN7TransitionState;
void playerStateDamageCheck(void) {
    void *new_var;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if ((gCurrentMap != 0x52) && (gCurrentMap != 0xE)) {
            playerTakeDamage(0x40);
            return;
        }
        new_var = ((EfN7TransitionState *)gActivePlayerState)->unk88->customState;
        ((u8 *)new_var)[0x45] = 1;
    }
}

void playerTakeQueuedDamage(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        playerTakeDamage(D_807FD6F2);
        playerSetBaseGravity();
    }
}

extern void func_806F1048(Actor *);
extern s32 camIsCutsceneActive(void);

void playerStateCutsceneDamageCheck(void) {
    if ((gGlobalCutsceneFlags & 2) != 0) {
        func_806F1048(gActivePlayerActor);
        sfxStopChannel(0xC, 0);
    }
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if (((gGlobalCutsceneFlags & 2) != 0) && (camIsCutsceneActive() != 0)) {
            return;
        }
        playerTakeDamage(1);
        playerSetBaseGravity();
    }
}

typedef struct {
    u8 pad0[0xDC];
    s32 unkDC;
} EfDPlayerStateDc;

typedef struct {
    u8 pad0[0x2A0];
    s32 unk2A0;
    u8 pad2A4[0x4C];
} EfDPlayerBlock;

#define EfDStateDc ((EfDPlayerStateDc *)gActivePlayerState)
#define EfDPlayer ((EfDPlayerBlock *)gPlayerSlots)
extern void actorSpawnAttachment(Actor *, f32);
extern void actorAppendActiveCallback8(void);

void playerStateDamageCheck5(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        EfDStateDc->unkDC = EfDPlayer[gCurrentPlayerIndex].unk2A0;
        if (EfDPlayer[gCurrentPlayerIndex].unk2A0 == 0) {
            actorSpawnAttachment(gActivePlayerActor, 3.2f);
        }
        playerTakeDamage(1);
        playerSetBaseGravity();
        actorAppendActiveCallback8();
    }
}


void playerStateTakeDamageAndDrop(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        EfDStateDc->unkDC = EfDPlayer[gCurrentPlayerIndex].unk2A0;
        playerTakeDamage(1);
        playerSetBaseGravity();
    }
}

extern void actorScriptStart(Actor *, s32);
extern void scriptSetActorRampTarget(Actor *, f32, f32);

void playerStateDamageCheck2(void) {
    if (playerCanTakeHit(gCurrentActor) != 0) {
        EfDStateDc->unkDC = EfDPlayer[gCurrentPlayerIndex].unk2A0;
        gCurrentActor->unk144 = 1;
        gCurrentActor->state = 0x34;
        gCurrentActor->unk155[0] = 0;
        actorScriptStart(gCurrentActor, 0);
        func_806C9974(gCurrentPlayerIndex, -0x40);
        playerSetBaseGravity();
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
    }
}

typedef struct EfN7ActionObject {
    u8 pad0[0x58];
    s32 unk58;
} EfN7ActionObject;

typedef struct EfN7ActionState {
    u8 pad0[0xDC];
    EfN7ActionObject *unkDC;
} EfN7ActionState;

void playerStateDamageCheck3(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        s32 action = 1;

        ((EfN7ActionState *)gActivePlayerState)->unkDC = (EfN7ActionObject *)EfDPlayer[gCurrentPlayerIndex].unk2A0;
        if ((((EfN7ActionState *)gActivePlayerState)->unkDC != NULL) &&
            (((EfN7ActionState *)gActivePlayerState)->unkDC->unk58 == 0x123)) {
            action = 2;
        }
        playerTakeDamage((s16)action);
    }
}

typedef struct EfL2PlayerState {
    u8 pad0[0x38];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x36];
    Actor *unk88;
    u8 pad8C[0x36];
    s16 unkC2;
    u8 padC4[0x10];
    s16 unkD4;
    u8 padD6[0x17A];
    s32 unk250;
} EfL2PlayerState;

typedef struct EfL2PlayerBlock {
    u8 pad0[0x29C];
    s16 unk29C;
    Actor *unk2A0;
    u8 pad2A4[0x1C];
    u8 unk2C0;
    u8 pad2C1[0x2F];
} EfL2PlayerBlock;

#define EfL2PS ((EfL2PlayerState *)gActivePlayerState)
#define EfL2Player ((EfL2PlayerBlock *)gPlayerSlots)

extern f32 gKongSwimStrokeSpeeds[], D_80753040[], gKongSwimTurnSpeeds[], D_80753078[];
extern s16 D_807530B0[], D_807530D0[], D_807530E0[], D_80753160[], D_8075386C[];
extern f32 gKongSwimPaddleSpeeds[], D_8075310C[], D_80753128[], gKongSwimSpeeds[], gKongTurnDecelRates[], D_8075389C[];
extern s32 gFrameCounter;
extern s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void slotQueueCancel(s32, s32);
extern void sfxPlayScriptActorSoundForPlayer(Actor *, s16, u8);
extern s8 func_806C9830(s8, Actor *);
extern Actor *actorResolveKillCreditOwner(Actor *);
extern void playerSetRecentAttacker(Actor *, PlayerState *);
extern void playerRecordHitSource(Actor *, Actor *, s32);
extern s32 playerHitSourceIsStale(s32);
extern s32 func_807142D8(void);
extern s32 func_80714608(s32);

void playerTakeDamage(s16 arg0) {
    s16 var_a0;
    f32 temp_fv1;
    f32 var_fv0;
    u8 sp33;
    s32 sp2C;
    s8 temp_v0;

    sp33 = 0;
    if (gActivePlayerActor->contactFlags & 4) {
        temp_fv1 = gCurrentActor->waterY - gCurrentActor->floorY;
        if (EfL2Player[gCurrentPlayerIndex].unk2C0 == 1) {
            var_fv0 = D_8075386C[gCurrentCharacterIndex];
        } else {
            var_fv0 = D_8075389C[gCurrentCharacterIndex];
        }
        sp33 = var_fv0 < temp_fv1;
    }
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        sfxStopChannel(0x6B, 0);
        gActivePlayerActor->flags |= 4;
        EfL2PS->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex];
        gActivePlayerActor->contactFlags &= 0xFFBF;
        slotQueueCancel(6, 1);
        if (EfL2PS->unkD4 == 0) {
            playerClearCarriedItemState();
            playerDropHeldActor(gActivePlayerActor);
            if ((EfL2PS->unk88 != NULL) &&
                ((EfL2PS->unk88->actorType == 0x1D) || (EfL2PS->unk88->actorType == 0x57) ||
                 (EfL2PS->unk88->actorType == 0x50) || (EfL2PS->unk88->actorType == 0x3E))) {
                EfL2PS->unkD4 = D_807530E0[gCurrentCharacterIndex];
                actorScriptStart(EfL2PS->unk88, 0x292);
                sfxPlayScriptActorSoundForPlayer(gActivePlayerActor, 0x11, 0);
                if (EfL2PS->unk88->actorType != 0x57) {
                    behaviourAddSlotQueueValueB(3);
                }
            } else {
                sp2C = 0;
                if (gPlayerCount >= 2) {
                    if (playerHitSourceIsStale(EfL2Player[gCurrentPlayerIndex].unk29C) == 0) {
                        return;
                    }
                    playerRecordHitSource(gActivePlayerActor, EfL2Player[gCurrentPlayerIndex].unk2A0,
                                  EfL2Player[gCurrentPlayerIndex].unk29C);
                    if ((func_80714608(0) != 0) && (gActivePlayerActor->state == 0x3C) &&
                        (EfL2Player[gCurrentPlayerIndex].unk29C != 0xE)) {
                        EfL2PS->unk250 -= arg0 * 0xA;
                        if (EfL2PS->unk250 < 0) {
                            EfL2PS->unk250 = 0;
                        }
                        if (EfL2PS->unk250 != 0) {
                            return;
                        }
                    }
                }
                if (((gPlayerCount != 1) || (EfL2Player[gCurrentPlayerIndex].unk29C != 0x2B)) &&
                    (func_807142D8() == 0)) {
                    temp_v0 = func_806C9830((s8)-arg0, gActivePlayerActor);
                    if (temp_v0 < 0) {
                        sp2C = func_806C9974(gCurrentPlayerIndex, temp_v0);
                    }
                }
                if (sp2C != 0) {
                    if (gActivePlayerActor->contactFlags & 4) {
                        actorScriptStartByIndex(gActivePlayerActor, 0x29);
                    } else {
                        actorScriptStartByIndex(gActivePlayerActor, 0x27);
                    }
                    gActivePlayerActor->state = 0x36;
                    gActivePlayerActor->unk155[0] = 0;
                    if (func_80714608(0) != 0) {
                        gActivePlayerActor->speedY = D_80753128[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex] * 5.0f;
                        EfL2PS->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    }
                } else {
                    switch (EfL2Player[gCurrentPlayerIndex].unk29C) {
                    case 0xE:
                        gActivePlayerActor->state = 0x66;
                        gActivePlayerActor->unk155[0] = 0;
                        actorScriptStartByIndex(gActivePlayerActor, 0x26);
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                        break;
                    case 0x31:
                        if (sp33 != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->unk155[0] = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x34;
                            gActivePlayerActor->unk155[0] = 0;
                            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
                            actorScriptStartByIndex(gCurrentActor, 0x1E);
                        }
                        break;
                    case 0x2B:
                        if (sp33 != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->unk155[0] = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x32;
                            gActivePlayerActor->unk155[0] = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x25);
                        }
                        break;
                    case 0x32:
                        if (sp33 != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->unk155[0] = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x35;
                            gActivePlayerActor->unk155[0] = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x26);
                        }
                        break;
                    case 0x37:
                        gActivePlayerActor->state = 0x33;
                        gActivePlayerActor->unk155[0] = 0;
                        actorScriptStart(gActivePlayerActor, 4);
                        break;
                    case 0x2E:
                    case 0x2F:
                        if (sp33 != 0) {
                            if (gCurrentMap == 0x6F) {
                                gActivePlayerActor->state = 0x38;
                                gActivePlayerActor->unk155[0] = 0;
                                actorScriptStart(gActivePlayerActor, 0x3B5);
                                actorScriptStart(EfL2PS->unk88, 0x3BB);
                                EfL2PS->unkC2 = (gFrameCounter & 1) ? -0xFA : 0xFA;
                            } else {
                                gActivePlayerActor->state = 0x37;
                                gActivePlayerActor->unk155[0] = 0;
                                actorScriptStartByIndex(gActivePlayerActor, 0x28);
                            }
                        } else if (gActivePlayerActor->state != 0x63) {
                            gActivePlayerActor->state = 0x31;
                            gActivePlayerActor->unk155[0] = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x24);
                        } else {
                            actorScriptStart(gActivePlayerActor, 0x81);
                        }
                        break;
                    }
                }
                if (EfL2Player[gCurrentPlayerIndex].unk2A0 != NULL) {
                    var_a0 = mathAngleBetweenPoints2D(gActivePlayerActor->x, gActivePlayerActor->z,
                                                      EfL2Player[gCurrentPlayerIndex].unk2A0->x,
                                                      EfL2Player[gCurrentPlayerIndex].unk2A0->z);
                } else {
                    var_a0 = (gActivePlayerActor->moveYaw + 0x800) & 0xFFF;
                }
                gActivePlayerActor->moveYaw = var_a0;
                switch (EfL2Player[gCurrentPlayerIndex].unk29C) {
                case 0x2E:
                case 0x2F:
                    if (gActivePlayerActor->contactFlags & 4) {
                        gActivePlayerActor->speedXZ = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
                        EfL2PS->unkD4 = D_807530B0[gCurrentCharacterIndex];
                    } else {
                        if (gPlayerCount >= 2) {
                            playerSetRecentAttacker(actorResolveKillCreditOwner(EfL2Player[gCurrentPlayerIndex].unk2A0),
                                          gActivePlayerState);
                        }
                        gActivePlayerActor->speedY = D_80753040[gCurrentCharacterIndex];
                        gActivePlayerActor->speedXZ = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
                        EfL2PS->unkD4 = D_807530B0[gCurrentCharacterIndex];
                        gActivePlayerActor->accelY = gKongSwimStrokeSpeeds[gCurrentCharacterIndex];
                    }
                    break;
                case 0x32:
                    if (gPlayerCount >= 2) {
                        playerSetRecentAttacker(actorResolveKillCreditOwner(EfL2Player[gCurrentPlayerIndex].unk2A0),
                                      gActivePlayerState);
                    }
                    EfL2PS->unkD4 = D_807530D0[gCurrentCharacterIndex];
                    gActivePlayerActor->speedXZ = gKongSwimPaddleSpeeds[gCurrentCharacterIndex];
                    gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    break;
                case 0xE:
                    if (gPlayerCount >= 2) {
                        playerSetRecentAttacker(actorResolveKillCreditOwner(EfL2Player[gCurrentPlayerIndex].unk2A0),
                                      gActivePlayerState);
                    }
                    if (func_80714608(0) != 0) {
                        gActivePlayerActor->speedY = D_80753128[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex] * 10.0f;
                        EfL2PS->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex] * 10.0f;
                        EfL2PS->unkD4 = 0xA;
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    } else {
                        gActivePlayerActor->speedY = D_80753128[gCurrentCharacterIndex];
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex];
                        if (arg0 != 0) {
                            EfL2PS->unkD4 = D_80753160[gCurrentCharacterIndex];
                        }
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    }
                    break;
                case 0x37:
                    EfL2PS->unkD4 = D_807530B0[gCurrentCharacterIndex];
                    break;
                case 0x2B: // FAKE: extends the jump table down to 0x2B
                    break;
                }
                if ((gPlayerCount >= 2) && (sp2C == 0)) {
                    EfL2PS->unkD4 = 0x3C;
                }
                if (gActivePlayerActor->state == 0x36) {
                    if (gActivePlayerActor->contactFlags & 4) {
                        gActivePlayerActor->speedY = D_80753078[gCurrentCharacterIndex] / 4;
                    } else {
                        gActivePlayerActor->speedY = D_80753078[gCurrentCharacterIndex];
                    }
                }
                EfL2PS->unk50 = 0;
            }
        }
    }
}

void playerStateEnterDamageReaction(void) {
    void *new_var;
    if ((gActivePlayerActor->state == 0x36) || (gActivePlayerActor->state == 0x39) ||
        (gActivePlayerActor->state == 0x3A) || (gActivePlayerActor->state == 0x71) ||
        (gActivePlayerActor->state == 0x73) || (gActivePlayerActor->state == 0x74)) {
        return;
    }
    playerClearCarriedItemState();
    gActivePlayerActor->flags &= 0xFFFF7FFF;
    actorScriptStartByIndex(gActivePlayerActor, 0x27);
    gActivePlayerActor->state = 0x39;
    gActivePlayerActor->unk155[0] = 0;
    ((u8 *)gActivePlayerState)[0x11C] = 0x19;
    func_8061B610(((void **)gActivePlayerState)[0x41]);
    if ((gCurrentMap != 0x52) && (gCurrentMap != 0xE)) {
        func_806C9974(gCurrentPlayerIndex, -0x40);
    } else {
        new_var = ((EfN7TransitionState *)gActivePlayerState)->unk88->customState;
        ((u8 *)new_var)[0x45] = 1;
    }
}

extern void playerDropHeldActor(Actor *);
extern void camStartPath(Actor *, s32, s32);

void playerStateEnterDamageReaction2(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if (gActivePlayerActor->state != 0x3B) {
            if (camIsCutsceneActive() == 0) {
                playerClearCarriedItemState();
                playerDropHeldActor(gActivePlayerActor);
                gActivePlayerActor->unk144 = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x2A);
                gActivePlayerActor->state = 0x3B;
                gActivePlayerActor->unk155[0] = 0;
                func_806C9974(gCurrentPlayerIndex, -0x40);
                camStartPath(gActivePlayerActor, 0xB, 0x85);
                gActivePlayerActor->speedXZ = 0.0f;
            }
        }
    }
}

void playerStateSetCartDamage(void) {
    ((u8 *)gActivePlayerState)[0x1FC] = 1;
}

void playerStateEnterBarrelBlast(void) {
    gCurrentActor->state = 0x6A;
    gCurrentActor->unk155[0] = 0;
}

typedef struct EfN7SpawnParams {
    u16 values[5];
} EfN7SpawnParams;

extern EfN7SpawnParams D_8075D380;
extern void actorSpawn(s32, s32);

void playerStateSpawnParticles(void) {
    EfN7SpawnParams spawnParams;
    s32 pad;
    f32 height;

    spawnParams = D_8075D380;
    height = gActivePlayerActor->sub4->scaleX;
    actorSpawn(0x140, 0xB9);
    if (gActivePlayerActor->actorType == 2) {
        height *= 1.25;
    }
    actorCopyPoseAndScale(gSpawnedActor, gActivePlayerActor, height);
    actorScriptStart(gSpawnedActor, ((u16 *)&spawnParams)[gPlayerCharacterId[((u8 *)gActivePlayerState)[0x1A4]]]);
    gSpawnedActor->flags |= 0x40000000;
    actorScriptStartByIndex(gActivePlayerActor, 0x88);
    gCurrentActor->state = 0x79;
    gCurrentActor->unk155[0] = 0;
}


typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
    u8 pad21C[0xD4];
} EfDNavigationPlayer;

extern void playerCheckAndResetCarriedActor(Actor *);
extern s16 mathAngleArcMidpoint(s16, s16);
extern s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
extern void camStartPathNearWall(Actor *, s32, s32, s32);

void playerStateStopChannelAndClearCarried(void) {
    sfxStopChannel(0x6B, 0);
    playerClearCarriedItemState();
    playerCheckAndResetCarriedActor(gActivePlayerActor);
    playerDropHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x5B);
    gActivePlayerActor->state = 0x70;
    gActivePlayerActor->unk155[0] = 0;
    if (gActivePlayerActor->hasArcBounds != 0) {
        gActivePlayerActor->yaw = mathAngleArcMidpoint(gActivePlayerActor->arcYawMin, gActivePlayerActor->arcYawMax);
    } else {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(
            ((EfDNavigationPlayer *)gPlayerSlots)[gCurrentPlayerIndex].unk210,
            ((EfDNavigationPlayer *)gPlayerSlots)[gCurrentPlayerIndex].unk218,
            gActivePlayerActor->x,
            gActivePlayerActor->z);
    }
    camStartPathNearWall(gActivePlayerActor, 0x15, 0x1F, 5);
}

void playerStateDropHeldActor(void) {
    playerClearCarriedItemState();
    playerDropHeldActor(gActivePlayerActor);
    playerCheckAndResetCarriedActor(gActivePlayerActor);
    if (gActivePlayerActor->state != 0x6D) {
        actorScriptStartByIndex(gActivePlayerActor, 0x5B);
        gActivePlayerActor->state = 0x71;
        gActivePlayerActor->unk155[0] = 0;
    }
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(
        ((EfDNavigationPlayer *)gPlayerSlots)[gCurrentPlayerIndex].unk210,
        ((EfDNavigationPlayer *)gPlayerSlots)[gCurrentPlayerIndex].unk218,
        gActivePlayerActor->x,
        gActivePlayerActor->z);
    if (gCurrentMap == 8) {
        camStartPath(gActivePlayerActor, 2, 1);
        gActivePlayerActor->unk155[0] = 0xFF;
        ((u16 *)gActivePlayerState)[0x11E] = 0xFFFF;
    } else {
        camStartPath(gActivePlayerActor, 5, 5);
        ((s16 *)gActivePlayerState)[0x11E] = 100;
    }
}

typedef struct EfEPlayerState {
    /* 0x000 */ u8 pad0[0x30];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0x10];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ u8 pad4E[2];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u8 pad58[0x30];
    /* 0x088 */ void *unk88;
    /* 0x08C */ u8 pad8C[0x162];
    /* 0x1EE */ s16 unk1EE;
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[0x34];
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
    /* 0x238 */ u8 pad238[4];
    /* 0x23C */ s16 unk23C;
} EfEPlayerState;

#define EfEPS ((EfEPlayerState *)gActivePlayerState)
typedef struct EfECamBlock {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x84];
    /* 0x2A0 */ void *unk2A0;
    /* 0x2A4 */ u8 pad2A4[0x1C];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C4 */ u8 pad2C4[0x2C];
} EfECamBlock;

#define EfECam ((EfECamBlock *)gPlayerSlots)
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void playerStateDropHeldActorAndScript(void) {
    playerClearCarriedItemState();
    playerDropHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x5B);
    gActivePlayerActor->state = 0x72;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(EfECam[gCurrentPlayerIndex].unk210, EfECam[gCurrentPlayerIndex].unk218,
                                                  gActivePlayerActor->x, gActivePlayerActor->z);
    camStartPath(gActivePlayerActor, 0x15, 5);
}

typedef struct EfEActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfEActorC0;

void playerStateDropHeldActorSetKong(void) {
    playerSetKongByActorType(EfEPS->unk1EE);
    playerDropHeldActor(gActivePlayerActor);
    playerClearCarriedItemState();
    gActivePlayerActor->unk144 = 1;
    if (gActivePlayerActor->state != 0x7D) {
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x34);
        } else if (!(gActivePlayerActor->contactFlags & 2)) {
            actorScriptStartByIndex(gActivePlayerActor, 0x5D);
        }
    }
    gActivePlayerActor->state = 0x73;
    gActivePlayerActor->unk155[0] = 0;
    if ((EfEPS->unk88 == NULL) || (((Actor *)EfEPS->unk88)->actorType != 0x57)) {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(EfECam[gCurrentPlayerIndex].unk210, EfECam[gCurrentPlayerIndex].unk218,
                                                      gActivePlayerActor->x, gActivePlayerActor->z);
    }
    ((EfEActorC0 *)gActivePlayerActor)->unkC0 = 0.0f;
    EfEPS->unk23C = 0x5A;
    playerSetBaseGravity();
}

void playerStateDropHeldActorSetKong2(void) {
    playerSetKongByActorType(EfEPS->unk1EE);
    playerDropHeldActor(gActivePlayerActor);
    playerClearCarriedItemState();
    gActivePlayerActor->unk144 = 1;
    if (gActivePlayerActor->state != 0x7D) {
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x34);
        } else if (!(gActivePlayerActor->contactFlags & 2)) {
            actorScriptStartByIndex(gActivePlayerActor, 0x5C);
        }
    }
    gActivePlayerActor->state = 0x74;
    gActivePlayerActor->unk155[0] = 0;
    if ((EfEPS->unk88 == NULL) || (((Actor *)EfEPS->unk88)->actorType != 0x57)) {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(EfECam[gCurrentPlayerIndex].unk210, EfECam[gCurrentPlayerIndex].unk218,
                                                      gActivePlayerActor->x, gActivePlayerActor->z);
    }
    ((EfEActorC0 *)gActivePlayerActor)->unkC0 = 0.0f;
    EfEPS->unk23C = 0x5A;
    playerSetBaseGravity();
}

void playerStateNoop1(void) {
}

void playerStateNoop2(void) {
}


void func_806F007C(void) {
    gCurrentActor->state = 0x84;
    gCurrentActor->unk155[0] = 0;
    actorScriptStart(gCurrentActor, 0);
}


void playerStateClearCarriedSetFlags(void) {
    playerClearCarriedItemState();
    EfEPS->unk1F0 &= ~0x20;
    gActivePlayerActor->interactionType = 2;
    EfEPS->unk4C = -1;
    EfEPS->unk30 = gKongCannonInitialPitch[gCurrentCharacterIndex];
    gActivePlayerActor->state = 0x7A;
    gActivePlayerActor->unk155[0] = 0;
}



void func_806F014C(void) {
    EfEPS->unk1F4 |= 8;
    playerResumeLocomotion(gActivePlayerActor);
}


void func_806F0184(void) {
    playerClearCarriedItemState();
    EfEPS->unk1F0 &= ~0x20;
    gActivePlayerActor->state = 0x7B;
    gActivePlayerActor->unk155[0] = 0;
}


void playerStateClearCarriedAndCallF00BC(void) {
    playerClearCarriedItemState();
    playerStateClearCarriedSetFlags();
    EfEPS->unk88 = EfECam[gCurrentPlayerIndex].unk2A0;
}


void playerStateEnterClimbTree(void) {
    actorScriptStartByIndex(gActivePlayerActor, 9);
    gActivePlayerActor->state = 0xC;
    gActivePlayerActor->unk155[0] = 0;
}

void actorSpawn(s32, s32);
void actorSetInteractionTimer(Actor *);

void playerStateEnterKnockbackState(void) {
    EfEPS->unk4C = -1;
    EfEPS->unk30 = gKongCannonInitialPitch[gCurrentCharacterIndex];
    playerSetBaseGravity();
    if (gActivePlayerActor->state != 0x7C) {
        playerClearCarriedItemState();
        gActivePlayerActor->state = 0x7C;
        gActivePlayerActor->unk155[0] = 0;
        actorScriptStart(gActivePlayerActor, 0x13);
        actorSpawn(0x117, 0xC5);
        gSpawnedActor->parentActor = (s32)gActivePlayerActor;
        actorSetInteractionTimer(gActivePlayerActor);
    }
}


void func_806F0344(void) {
    playerSetBaseGravity();
    gActivePlayerActor->state = 0x7D;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->flags &= ~4;
    actorSpawn(0x11A, 0x21);
    actorScriptStart(gSpawnedActor, 0x232);
    gSpawnedActor->parentActor = (s32)gActivePlayerActor;
}

void playerStateSetFlagsByActorType(void) {
    s32 ev;

    switch (gActivePlayerActor->actorType) {
    case 2:
        ev = 7;
        break;
    case 3:
        ev = 0;
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        ev = 4;
        break;
    case 5:
        if (EfECam[gCurrentPlayerIndex].unk2C0 == 1) {
            ev = 8;
        } else {
            ev = 0x1F;
        }
        break;
    case 6:
        ev = 9;
        break;
    default:
        break;
    }
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(EfECam[gCurrentPlayerIndex].unk210, EfECam[gCurrentPlayerIndex].unk218,
                                                  gActivePlayerActor->x, gActivePlayerActor->z);
    if (gGlobalCutsceneFlags & 2) {
        EfEPS->unk1F0 &= ~0x100;
        actorScriptStart(gActivePlayerActor, 0x165);
    } else {
        if (gActivePlayerActor->state != 0x56) {
            camStartPath(gActivePlayerActor, (s16)ev, 5);
        }
        actorScriptStartByIndex(gActivePlayerActor, 0x5A);
    }
    gActivePlayerActor->state = 0x67;
    gActivePlayerActor->unk155[0] = 0;
}

void func_806E9964(EfEPlayerState *);

void func_806F0624(void) {
    EfEPS->unk1F4 |= 0x10;
    func_806E9964(EfEPS);
    gActivePlayerActor->state = 0x83;
    gActivePlayerActor->unk155[0] = 0;
    gActivePlayerActor->flags |= 0x40000004;
    gActivePlayerActor->flags &= ~1;
}

void func_806F06A4(void) {
    gActivePlayerActor->state = 0x87;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    EfEPS->unk50 = 0;
    EfEPS->unk4C = -1;
}

typedef struct EfEActorE4 {
    /* 0x000 */ u8 pad0[0xE4];
    /* 0x0E4 */ s16 unkE4;
} EfEActorE4;

void func_806F0700(void) {
    gActivePlayerActor->state = 0x88;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerActor->x = EfEPS->unk22C;
    gActivePlayerActor->y = EfEPS->unk230;
    gActivePlayerActor->z = EfEPS->unk234;
    ((EfEActorE4 *)gActivePlayerActor)->unkE4 = -0x3E6;
    gActivePlayerActor->sub4->scaleX = 0.01f;
    gActivePlayerActor->sub4->scaleY = 0.01f;
    gActivePlayerActor->sub4->scaleZ = 0.01f;
    EfEPS->unk50 = 0;
    EfEPS->unk4C = -1;
}


void playerStateEnterDoubleJumpWithSfx(void) {
    sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xF3, 0xFF, 0x7F, 0x19);
    gActivePlayerActor->state = 0x19;
    gActivePlayerActor->unk155[0] = 0;
    EfEPS->unk54 = D_807535CC[gCurrentCharacterIndex] * 2.6;
    EfEPS->unk50 = 0xC;
    actorScriptStartByIndex(gActivePlayerActor, 0x10);
}

typedef struct EfEActor78 {
    /* 0x000 */ u8 pad0[0x78];
    /* 0x078 */ u8 unk78;
} EfEActor78;

#define EfEActor ((EfEActor78 *)gActivePlayerActor)


void func_806F0878(void) {
    if (EfEActor->unk78 == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0x76, 0x64, 0x7F, 0);
    }
    EfEPS->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex];
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x15;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStartByIndex(gActivePlayerActor, 6);
    gActivePlayerActor->contactFlags |= 0x20;
    actorScriptExecute(gActivePlayerActor);
}

void func_806F0930(void) {
    if (EfEActor->unk78 == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0x76, 0xFF, 0x7F, 0);
    }
    EfEPS->unk38 = gKongTurnDecelRates[gCurrentCharacterIndex];
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x16;
    gActivePlayerActor->unk155[0] = 0;
    actorScriptStartByIndex(gActivePlayerActor, 7);
    gActivePlayerActor->contactFlags |= 0x20;
    actorScriptExecute(gActivePlayerActor);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/D_8075D380.s")
