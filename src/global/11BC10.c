#include "common.h"
#include "actor.h"
#define PROTO_SKIP_effectSetColor // FAKE: callee prototype steer
#define PROTO_SKIP_lightAdd // FAKE: callee prototype steer
#define PROTO_SKIP_lightSetFlags // PROTO: The number of arguments doesn't agree with the number in the
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/3C10.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"


extern u8 gGfxBufferIndex;
extern u32 gFrameCounter;
extern s32 gCurrentMap;
extern Actor *gPrimaryPlayerActor;

f32 mathCosF(s16);
f32 mathSinF(s16);
f32 cosApprox(f32);
f32 sinApprox(f32);

typedef struct RotatingEffectActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 mtxState;
    u8 pad32D[0x13];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x10];
    s32 param;
    f32 scaleX;
    f32 scaleY;
    u8 pad368[5];
    u8 alpha;
    u8 pad36E[0x16];
    void *motion;
} RotatingEffectActorView;

void effectZRotationMatrixUpdate(RotatingEffectActorView *effect, void *unused) {
    f32 scaleMtx[4][4];
    f32 rotMtx[4][4];

    guScaleF(scaleMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, (f32)effect->param, 0.0f, 0.0f, 1.0f);
    guMtxCatF(scaleMtx, rotMtx, scaleMtx);
    guMtxF2L(scaleMtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
} RotationState;

void effectZSpinMatrixUpdate(RotatingEffectActorView *effect, void *unused) {
    f32 scaleMtx[4][4];
    f32 rotMtx[4][4];
    RotationState *state;

    state = (RotationState *)effect->motion;
    if (state == NULL) {
        effect->motion = heapAlloc(8);
        ((RotationState *)effect->motion)->unk0 = (randomLcgNext() % 36000U) / 100U;
        ((RotationState *)effect->motion)->unk4 = (randomLcgNext() % 400U) / 100U;
        state = (RotationState *)effect->motion;
    }
    state->unk0 += state->unk4;
    guScaleF(scaleMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, ((RotationState *)effect->motion)->unk0, 0.0f, 0.0f, 1.0f);
    guMtxCatF(scaleMtx, rotMtx, scaleMtx);
    guMtxF2L(scaleMtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} OrbitMotionState10;

void effectOrbitXZUpdate(RotatingEffectActorView *effect, void *unused) {
    OrbitMotionState10 *state;

    if (!effect->motion) {
        effect->motion = heapAlloc(0xA);
        state = effect->motion;
        state->unk0 = (s16) ((randomNonNegative() >> 15) % 0xFFF);
        state->unk2 = effect->param & 0xFFFF;
        state->unk4 = (effect->param >> 16) & 0xFFFF;
        state->unk6 = effect->x;
        state->unk8 = effect->z;
    }
    state = effect->motion;
    state->unk0 = state->unk4 + state->unk0;
    effect->x = mathSinF(state->unk0) * state->unk2 + state->unk6;
    effect->z = mathCosF(state->unk0) * state->unk2 + state->unk8;
}


typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} PuffRiseMotionState;

void lightSetFlags();
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);  // FAKE: callee prototype steer

void effectPuffRiseUpdate(RotatingEffectActorView *effect, void *unused) {
    PuffRiseMotionState *state;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(8);
        state = effect->motion;
        state->unk0 = (randomNonNegative() >> 15) % 0xFFF;
        state->unk2 = ((randomNonNegative() >> 15) % 10) + 2;
        state->unk4 = 0;
        state->unk6 = -50 - (((randomNonNegative() >> 15) % 10000) % 600);
    }
    state = effect->motion;
    effect->y = (f32) ((f64) effect->y - (f64) state->unk6 / 100.0);
    state->unk6 += 0x14;
    effect->x += (0.04 * (f64) state->unk4) * (f64) mathSinF(state->unk0);
    effect->z += (0.04 * (f64) state->unk4) * (f64) mathCosF(state->unk0);
    state->unk0 += 0x50;
    state->unk4 += state->unk2;
    if (effect->param != 0) {
        lightSetFlags(1);
        lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 40.0f, 0, 0xFF,
                 0xFF, (randomNonNegative() >> 15) % 0xFF);
    }
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} ConfettiMotionState;

typedef struct {
    s16 unk0;
    s16 unk2;
} ConfettiParams;

typedef struct ConfettiActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x198];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x10];
    ConfettiParams param;
    u8 pad360[0xF];
    u8 mode;
    u8 pad370[0x14];
    ConfettiMotionState *motion;
} ConfettiActorView;

void effectConfettiPhysicsUpdate(ConfettiActorView *effect, void *unused) {
    ConfettiMotionState *motion;
    ConfettiParams *params = &effect->param;
    f64 scale;
    s32 rem;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xC);
        motion = effect->motion;
        if (params->unk0 != 0) {
            motion->unk0 = (f32) (((randomNonNegative() >> 15) % 200) + params->unk0 - 100);
        } else {
            motion->unk0 = (f32) ((randomNonNegative() >> 15) % 0xFFF);
        }
        scale = (effect->mode != 0) ? 4.0 : 1.0;
        motion->unk4 = (f32) ((((randomNonNegative() >> 15) % 10) + 5) * scale);
        rem = (randomNonNegative() >> 15) % 6;
        motion->unk8 = (f32) (params->unk2 + rem);
    }
    motion = effect->motion;
    params = &effect->param;
    if (effect->mode != 0) {
        effect->x += 4.0 * ((0.01 * (f64) params->unk2) * (f64) mathSinF((s16) motion->unk0));
        effect->y += 4.0 * ((0.01 * (f64) params->unk2) * (f64) mathCosF((s16) motion->unk0));
    } else {
        effect->x += (0.04 * (f64) params->unk2) * (f64) mathSinF((s16) motion->unk0);
        effect->z += (0.04 * (f64) params->unk2) * (f64) mathCosF((s16) motion->unk0);
        if (params->unk0 == 0) {
            effect->y += motion->unk8;
            motion->unk8 = (f32) ((f64) motion->unk8 - 0.5);
        } else {
            effect->y += (f64) motion->unk8 * 0.2;
        }
    }
    params->unk2 = (s16) (params->unk2 + motion->unk4);
}


extern s32 D_8074E880[];

void effectTimerCountdownAlphaUpdate(RotatingEffectActorView *effect, u8 *isDone) {
    s32 timer;

    timer = effect->param;
    effect->alpha = 0;
    if (timer != 0) {
        effect->param = timer - 1;
        effectSetDepth(1);
        effectSetCallback(effectConfettiPhysicsUpdate);
        effectSetSpeed(0xA);
        effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 0.8f, effect->x, effect->y, effect->z);
        return;
    }
    *isDone = 1;
}

typedef struct {
    s16 unk0;
    s16 unk2;
} RandomDriftState;

void effectRandomDriftVelocityUpdate(RotatingEffectActorView *effect, void *unused) {
    RotatingEffectActorView *actor;
    RandomDriftState *motion;

    actor = effect;
    if (actor->motion == NULL) {
        actor->motion = heapAlloc(4);
        motion = actor->motion;
        motion->unk0 = (randomNonNegative() >> 15) % 4095;
        motion->unk2 = ((randomNonNegative() >> 15) % 10) + 2;
    }
    motion = actor->motion;
    actor->x += 0.2 * actor->param * mathSinF(motion->unk0);
    actor->y += 0.2 * actor->param * mathCosF(motion->unk0);
    motion->unk0 += 0x46;
    actor->param += motion->unk2;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} OrbitMotionState;

typedef struct {
    u8 pad0[4];
    ActorSub4 *unk4;
} ScaleHolder;

typedef struct OrbitEffectActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 mtxState;
    u8 pad32D[0xB];
    ScaleHolder *parent;
    u8 pad33C[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x10];
    s32 param;
    f32 scaleX;
    f32 scaleY;
    u8 pad368[0x1C];
    OrbitMotionState *motion;
    u8 pad388[4];
    u16 flags;
} OrbitEffectActorView;

void func_80717930(OrbitEffectActorView *effect, void *unused) {
    f32 scaleFactor;
    f32 call_result;
    s32 flags;
    OrbitMotionState *state;
    void *allocatedState;
    ScaleHolder *scaleHolder;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xA);
        allocatedState = effect->motion;
        ((OrbitMotionState *)allocatedState)->unk0 = (randomNonNegative() >> 0xF) % 4095;
        ((OrbitMotionState *)allocatedState)->unk2 = effect->x;
        ((OrbitMotionState *)allocatedState)->unk4 = effect->z;
        flags = effect->param;
        if (flags & 0x8000) {
            effect->param = flags & 0xFFFF7FFF;
            ((OrbitMotionState *)allocatedState)->unk6 = 0xC8;
            ((OrbitMotionState *)allocatedState)->unk8 = 0xA;
        } else {
            ((OrbitMotionState *)allocatedState)->unk6 = 0x46;
            ((OrbitMotionState *)allocatedState)->unk8 = 0xF;
        }
        scaleHolder = effect->parent;
        if (scaleHolder != NULL) {
            scaleFactor = scaleHolder->unk4->scaleY / 0.15;
            ((OrbitMotionState *)allocatedState)->unk8 = ((OrbitMotionState *)allocatedState)->unk8 * scaleFactor;
            effect->param = effect->param * scaleFactor;
        }
    }
    state = effect->motion;
    if (effect->flags & 2) {
        effect->x = mathSinF(state->unk0) * effect->param + gPrimaryPlayerActor->x;
        effect->z = mathCosF(state->unk0) * effect->param + gPrimaryPlayerActor->z;
    } else {
        effect->x = mathSinF(state->unk0) * effect->param + state->unk2;
        effect->z = mathCosF(state->unk0) * effect->param + state->unk4;
    }
    effect->y += state->unk8 * 0.1;
    state->unk0 += state->unk6;
}

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} EffectTimerConfig;

typedef struct TimedEffectActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 mtxState;
    u8 pad32D[3];
    EffectTimerConfig *timerConfig;
    u8 pad334[4];
    void *parent;
    u8 pad33C[4];
    f32 x;
    f32 y;
    f32 z;
    s16 unk34C;
    s16 timer;
    u8 unk350;
    u8 unk351;
    u8 pad352[2];
    s32 count;
    s32 previousCount;
    s32 param;
    f32 scaleX;
    f32 scaleY;
    u8 pad368[5];
    u8 alpha;
    u8 pad36E[0x16];
    void *motion;
} TimedEffectActorView;


extern u8 sEffectImpactPuffConfig;

typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
} PlayerDistanceView;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} PlayerDistanceFadeState;

extern void *gPlayerSlots;

void effectPlayerDistanceFadeUpdate(effect, isDone)
TimedEffectActorView *effect;
s8 *isDone;
{
    PlayerDistanceFadeState *state;
    f32 dy;
    f32 scale;
    f32 dz;
    f32 dx;
    f32 dist;
    s32 curStep;
    s32 value;

    scale = (f32) ((s32) (effect->unk34C * 3) / 4);
    if (effect->motion == NULL) {
        effect->motion = heapAlloc(6);
        state = effect->motion;
        state->unk0 = 0;
        state->unk2 = effect->timerConfig->unk16 * effect->unk350;
        state->unk4 = effect->alpha;
    }
    state = effect->motion;
    curStep = state->unk0;
    if (curStep == state->unk2) {
        *isDone = 1;
    } else {
        state->unk0 = curStep + 1;
    }
    dz = ((PlayerDistanceView *) gPlayerSlots)->unk218 - effect->z;
    dx = ((PlayerDistanceView *) gPlayerSlots)->unk210 - effect->x;
    dy = ((PlayerDistanceView *) gPlayerSlots)->unk214 - effect->y;
    dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
    if (dist < scale) {
        effect->alpha = state->unk4;
        return;
    }
    value = (s32) ((f32) state->unk4 * ((dist - scale) / ((f32) effect->unk34C - scale)));
    if (state->unk4 < value) {
        value = (s32) state->unk4;
    }
    effect->alpha = state->unk4 - value;
}

void func_80717CE8(effect, isDone)
TimedEffectActorView *effect;
s8 *isDone;
{
    if (effect->alpha != 0xFF) {
        effect->alpha += 0x14;
    }
    if ((s32) effect->alpha >= 0xEB) {
        effect->alpha = 0xFFU;
    }
    effect->y = (f32) ((f64) effect->y - ((f64) effect->param / 100.0));
}

void func_80717D4C(effect, isDone)
TimedEffectActorView *effect;
s8 *isDone;
{
    effect->y = (f32) ((f64) effect->y - ((f64) effect->param / 100.0));
}

void effectLinearFadeAlphaUpdate(TimedEffectActorView *effect, s8 *isDone) {
    s32 alphaStep;
    u8 curAlpha;

    alphaStep = effect->param;
    curAlpha = effect->alpha;
    if (alphaStep < (s32) curAlpha) {
        effect->alpha = (u8) (curAlpha - alphaStep);
        return;
    }
    effect->alpha = 0U;
    *isDone = 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} DriftMotionState;

void effectDriftXZUpdate(RotatingEffectActorView *effect, void *unused) {
    DriftMotionState *state;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0x10);
        state = effect->motion;
        state->unk0 = effect->x;
        state->unk4 = effect->z;
        state->unk8 = 0;
        state->unkA = 0;
        state->unkC = (randomNonNegative() % 10000) % 150 - 75;
        state->unkE = (randomNonNegative() % 10000) % 150 - 75;
    }
    state = effect->motion;
    effect->x = (f32) ((f64) mathSinF(state->unk8) * 6.0 + (f64) state->unk0);
    effect->z = (f32) ((f64) mathSinF(state->unkA) * 6.0 + (f64) state->unk4);
    state->unk8 += state->unkC;
    state->unkA += state->unkE;
    effect->y = (f32) ((f64) effect->y - (f64) effect->param / 100.0);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} VelocityMotionState;

void effectShrinkOffsetUpdate(effect, isDone)
TimedEffectActorView *effect;
s8 *isDone;
{
    VelocityMotionState *state;
    Actor *parent;

    if (effect->motion == NULL) {
        parent = effect->parent;
        effect->motion = heapAlloc(0x10);
        state = effect->motion;
        if (parent != NULL) {
            state->unk0 = (parent->speedXZ * 0.025f) * mathSinF(parent->moveYaw);
            state->unk4 = (parent->speedXZ * 0.025f) * mathCosF(parent->moveYaw);
        } else {
            state->unk0 = 0.0f;
            state->unk4 = 0.0f;
        }
        state->unk8 = effect->scaleX;
        state->unkC = 0.2f;
    }
    state = effect->motion;
    effect->y = (f32) ((f64) effect->y - (f64) effect->param / 100.0);
    effect->x += state->unk0;
    effect->z += state->unk4;
    state->unk0 = (f32) ((f64) state->unk0 * 0.93);
    state->unk4 = (f32) ((f64) state->unk4 * 0.93);
}


void effectShrinkAndVelocityUpdate(TimedEffectActorView *effect) {
    f32 scaleFactor;
    VelocityMotionState *state;

    effectShrinkOffsetUpdate(); // FAKE: K&R call with no arguments forwards the caller's $a1 untouched
    state = effect->motion;
    effect->scaleX = state->unkC * state->unk8;
    effect->scaleY = effect->scaleX;
    scaleFactor = state->unkC;
    if (scaleFactor < 2.0f) {
        state->unkC = (f32) ((f64) scaleFactor + 0.2);
    }
}

void func_807180F4(RotatingEffectActorView *effect, void *unused) {
    func_80717D4C(effect, unused);
    effectZSpinMatrixUpdate(effect, unused);
}

void effectSpawnImpactPuff(f32 scale, f32 x, f32 y, f32 z) {
    effectSetDepth(1);
    effectSetMode(3);
    effectSetCallback(&effectRandomYRotDecalUpdate);
    effectCreateAtPosition((s32)&sEffectImpactPuffConfig, scale, x, y, z);
}

extern s16 D_807502D0;

void effectFallUpdate(TimedEffectActorView *effect, s8 *isDone) {
    s16 *newVel;
    s16 *velocity;

    velocity = effect->motion;
    if (velocity == NULL) {
        newVel = heapAlloc(2);
        effect->motion = newVel;
        *newVel = 0;
        velocity = effect->motion;
    }
    effect->y += (f32) *velocity;
    *velocity -= 1;
    velocity = effect->motion;
    if (*velocity < D_807502D0) {
        *velocity = D_807502D0;
    }
    if (effect->y < (f32) effect->param) {
        *isDone = 1;
        effectSpawnImpactPuff((f32) ((f64) effect->scaleX * 1.5), effect->x, effect->param, effect->z);
    }
}

typedef f32 EffectMatrix[4][4];

void effectFadeOutMatrixUpdate(TimedEffectActorView *effect, s8 *isDone) {
    EffectMatrix modelMtx;
    EffectMatrix tempMtx;
    u8 alpha;

    guScaleF(modelMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tempMtx, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guTranslateF(tempMtx, effect->x, effect->y, effect->z);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    alpha = effect->alpha;
    effect->scaleX = (f32) ((f64) effect->scaleX + 0.07);
    effect->scaleY = (f32) ((f64) effect->scaleY + 0.07);
    if ((s32) alpha >= 0xA) {
        effect->alpha = (u8) (alpha - 0xA);
    } else {
        effect->alpha = 0U;
    }
    guMtxF2L(modelMtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 3;
}

void effectRandomYRotDecalUpdate(TimedEffectActorView *effect, s8 *isDone) {
    EffectMatrix modelMtx;
    EffectMatrix tempMtx;
    u32 rotAngle;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(4);
        rotAngle = (u32) (randomLcgNext() % 36000U) / 100U;
        *(f32 *) effect->motion = (f32) rotAngle;
    }
    guScaleF(modelMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tempMtx, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guRotateF(tempMtx, *(f32 *) effect->motion, 0.0f, 1.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guTranslateF(tempMtx, effect->x, effect->y, effect->z);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    if ((s32) effect->alpha >= 0xA) {
        effect->alpha -= 0xA;
    } else {
        effect->alpha = 0U;
    }
    guMtxF2L(modelMtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 3;
    if (effect->alpha == 0) {
        *isDone = 1;
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
} GroundSpinState;

typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
} GroundSpinTargetView;

void effectGroundDecalSpinUpdate(TimedEffectActorView *effect, s8 *isDone) {
    EffectMatrix modelMtx;
    EffectMatrix tempMtx;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(8);
        ((GroundSpinState *) effect->motion)->unk0 = 0.0f;
        ((GroundSpinState *) effect->motion)->unk4 = (f32) ((randomLcgNext() % 400U) / 100U);
    }
    guScaleF(modelMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tempMtx, ((GroundSpinState *) effect->motion)->unk0, 0.0f, 0.0f, 1.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guRotateF(tempMtx, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    if (effect->parent != NULL) {
        effect->y = ((GroundSpinTargetView *) effect->parent)->unkAC;
    }
    guTranslateF(tempMtx, effect->x, effect->y, effect->z);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guMtxF2L(modelMtx, &effect->mtx[gGfxBufferIndex]);
    if (effect->param != 0) {
        ((GroundSpinState *) effect->motion)->unk0 += ((GroundSpinState *) effect->motion)->unk4;
        effect->scaleX = (f32) ((f64) effect->scaleX - 0.02);
        effect->scaleY = (f32) ((f64) effect->scaleY - 0.02);
        if (effect->alpha >= 0xA) {
            effect->alpha -= 0xA;
        } else {
            effect->alpha = 0;
        }
    }
    effect->mtxState = 3;
}



typedef struct {
    f32 progress;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 increment;
    f32 angle;
    f32 angleIncrement;
} EffectInterpolationState;
extern f32 D_807FDB50;
extern f32 D_807FDB54;
extern f32 D_807FDB58;

void effectInterpolationUpdate(TimedEffectActorView *effect, s8 *isDone) {
    EffectMatrix mtx;
    EffectMatrix rotMtx;
    f32 start[3];
    f32 end[3];
    f32 result[3];
    s32 i;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0x28);
        ((EffectInterpolationState *)effect->motion)->progress = 0.0f;
        ((EffectInterpolationState *)effect->motion)->startX = D_807FDB50;
        ((EffectInterpolationState *)effect->motion)->startY = D_807FDB54;
        ((EffectInterpolationState *)effect->motion)->startZ = D_807FDB58;
        ((EffectInterpolationState *)effect->motion)->endX = effect->x;
        ((EffectInterpolationState *)effect->motion)->endY = effect->y;
        ((EffectInterpolationState *)effect->motion)->endZ = effect->z;
        ((EffectInterpolationState *)effect->motion)->increment = 0.01f;
        ((EffectInterpolationState *)effect->motion)->angle = (f32)((u32)(randomLcgNext() % 36000U) / 100U);
        ((EffectInterpolationState *)effect->motion)->angleIncrement = (f32)((u32)(randomLcgNext() % 400U) / 100U);
    }
    start[0] = ((EffectInterpolationState *)effect->motion)->startX;
    start[1] = ((EffectInterpolationState *)effect->motion)->startY;
    start[2] = ((EffectInterpolationState *)effect->motion)->startZ;
    end[0] = ((EffectInterpolationState *)effect->motion)->endX;
    end[1] = ((EffectInterpolationState *)effect->motion)->endY;
    end[2] = ((EffectInterpolationState *)effect->motion)->endZ;
    for (i = 0; i < 3; i++) {
        result[i] = end[i] + (start[i] - end[i]) * *(f32 *)effect->motion;
    }
    effect->x = result[0];
    effect->y = result[1];
    effect->z = result[2];
    ((EffectInterpolationState *)effect->motion)->progress += ((EffectInterpolationState *)effect->motion)->increment;
    ((EffectInterpolationState *)effect->motion)->increment = (f32)((f64)((EffectInterpolationState *)effect->motion)->increment + 0.001);
    effect->scaleX = (f32)((f64)effect->scaleX * 0.975);
    effect->scaleY = (f32)((f64)effect->scaleY * 0.975);
    ((EffectInterpolationState *)effect->motion)->angle = ((EffectInterpolationState *)effect->motion)->angle + ((EffectInterpolationState *)effect->motion)->angleIncrement;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, ((EffectInterpolationState *)effect->motion)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}


typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
} ProjectileSourceActor;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} ProjectileMotionState;

void effectProjectileDriftUpdate(TimedEffectActorView *effect, s8 *isDone) {
    ProjectileMotionState *proj;
    ProjectileSourceActor *src;
    f64 min;
    f64 temp;

    src = (ProjectileSourceActor *)effect->param;
    if (effect->motion == NULL) {
        proj = heapAlloc(8); effect->motion = proj;
        temp = (f64)src->unkB8 * 0.01;
        min = 2.0;
        if (temp < min) {
            proj->unk0 = min;
        } else {
            proj->unk0 = temp;
        }
        proj->unk2 = src->unkE6;
        proj->unk4 = (s16)(((s32)(randomNonNegative() >> 0xF) % 1000) + 0xC8);
        effect->scaleX += ((f64)((s32)(randomNonNegative() >> 0xF) % 100) / 500.0);
        effect->scaleY = effect->scaleX;
        proj->unk6 = (s16)src->unkAC;
    }
    proj = effect->motion;
    effect->x -= (f32)proj->unk0 * mathSinF(proj->unk2);
    effect->z -= (f32)proj->unk0 * mathCosF(proj->unk2);
    effect->y = (f32)((f64)effect->y + ((f64)proj->unk4 / 500.0));
    if ((f32)proj->unk6 <= effect->y) {
        *isDone = 1;
        effectSpawnImpactPuff((f32)((f64)effect->scaleX * 1.5), effect->x, (f32)proj->unk6, effect->z);
    }
    if ((s32)effect->alpha >= 0xC) {
        effect->alpha -= 0xA;
        return;
    }
    *isDone = 1;
    effect->alpha = 0U;
}


typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} GroundBounceMotionState;


void effectWobbleRiseUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f64 pad;
    f32 swayX;
    f32 swayZ;
    f32 riseSpeed;
    f32 floorY;
    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0x20);
        ((GroundBounceMotionState *)effect->motion)->unk0 = 0;
        ((GroundBounceMotionState *)effect->motion)->unk4 = 0.0f;
        ((GroundBounceMotionState *)effect->motion)->unk8 = effect->x;
        ((GroundBounceMotionState *)effect->motion)->unkC = effect->z;
        ((GroundBounceMotionState *)effect->motion)->unk10 = ((f64)(randomLcgNext() % 10000U) / 10000.0) * 0.19;
        ((GroundBounceMotionState *)effect->motion)->unk14 = ((f64)(randomLcgNext() % 10000U) / 10000.0) * 0.077;
        if ((randomLcgNext() / 10000U) & 1) {
            ((GroundBounceMotionState *)effect->motion)->unk10 = (f32)(0.0 - (f64)((GroundBounceMotionState *)effect->motion)->unk10);
            ((GroundBounceMotionState *)effect->motion)->unk14 = (f32)(0.0 - (f64)((GroundBounceMotionState *)effect->motion)->unk14);
        }
        floorY = effect->y;
        collisionCheckGroundAtPoint(effect->x, effect->z, &floorY);
        if (collisionGetFloorHeight(&((GroundBounceMotionState *)effect->motion)->unk18) == 0) {
            ((GroundBounceMotionState *)effect->motion)->unk18 = 0.0f;
        }
        ((GroundBounceMotionState *)effect->motion)->unk1C = (f32)gFrameCounter;
    }
    swayX = sinApprox(((GroundBounceMotionState *)effect->motion)->unk10 * (f32)((GroundBounceMotionState *)effect->motion)->unk0);
    swayZ = sinApprox(((GroundBounceMotionState *)effect->motion)->unk14 * (f32)((GroundBounceMotionState *)effect->motion)->unk0) * 6.0f;
    effect->x = ((GroundBounceMotionState *)effect->motion)->unk8 + (swayX * 6.0f);
    effect->z = ((GroundBounceMotionState *)effect->motion)->unkC + swayZ;
    ((GroundBounceMotionState *)effect->motion)->unk0 += 1;
    ((GroundBounceMotionState *)effect->motion)->unk4 = (f32)((f64)((GroundBounceMotionState *)effect->motion)->unk4 + 0.02);
    riseSpeed = ((GroundBounceMotionState *)effect->motion)->unk4;
    if ((f64)riseSpeed > 1.0) {
        ((GroundBounceMotionState *)effect->motion)->unk4 = 1.0f;
    }
    riseSpeed = ((GroundBounceMotionState *)effect->motion)->unk4;
    effect->y += riseSpeed;
    switch (effect->param) {
    case 0:
        effect->scaleX = (f32)(((f64)((GroundBounceMotionState *)effect->motion)->unk0 * 0.01) + 0.01);
        if ((f64)effect->scaleX > 0.12) effect->scaleX = 0.12f;
        break;
    case 1:
        effect->scaleX = (f32)(((f64)((GroundBounceMotionState *)effect->motion)->unk0 * 0.005) + 0.05);
        if ((f64)effect->scaleX > 0.07) effect->scaleX = 0.07f;
        break;
    case 2:
        effect->scaleX = (f32)(((f64)((GroundBounceMotionState *)effect->motion)->unk0 * 0.02) + 0.02);
        if ((f64)effect->scaleX > 0.24) effect->scaleX = 0.24f;
        break;
    }
    effect->scaleY = effect->scaleX;
    swayX = sinApprox((f32)((f64)((GroundBounceMotionState *)effect->motion)->unk0 * 0.17));
    swayZ = sinApprox((f32)((f64)((GroundBounceMotionState *)effect->motion)->unk0 * 0.2267));
    effect->scaleX = (f32)((f64)effect->scaleX + ((f64)swayX * 0.03));
    effect->scaleY = (f32)((f64)effect->scaleY + ((f64)swayZ * 0.03));
    if ((((GroundBounceMotionState *)effect->motion)->unk1C + 100.0f) < (f32)gFrameCounter) *isDone = 1;
    if (((GroundBounceMotionState *)effect->motion)->unk18 <= effect->y) {
        *isDone = 1;
        effectSpawnImpactPuff(0.3f, effect->x, effect->y, effect->z);
    }
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
} TumbleBounceState;

extern s32 D_8072073C;
extern s32 D_807212B0;
extern s32 D_807212C8;


void effectTumbleBounceUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 speed;
    f32 yawDeg;
    f32 velX;
    f32 cosYaw;
    f32 groundY;
    s16 sfxId;

    if (((TumbleBounceState *) effect->motion) == NULL) {
        effect->motion = heapAlloc(0x1C);
        ((TumbleBounceState *) effect->motion)->unk0 = (f32) (((f64) (f32) (u32) ((randomLcgNext() / 10000U) % 100U) / 25.0) + 5.0 + (((s32) effect->param >> 8) * 3.0));
        speed = ((f32) (u32) ((randomLcgNext() / 10000U) % 1000U) / 500.0f) + (f32) (effect->param & 0xFF);
        yawDeg = (f32) (u32) ((randomLcgNext() / 10000U) % 360U);
        velX = sinApprox(yawDeg * 0.017453292f) * speed;
        cosYaw = cosApprox(yawDeg * 0.017453292f);
        ((TumbleBounceState *) effect->motion)->unk4 = velX;
        ((TumbleBounceState *) effect->motion)->unk8 = cosYaw * speed;
        ((TumbleBounceState *) effect->motion)->unkC = (f32) (u32) ((randomLcgNext() % 36000U) / 100U);
        groundY = effect->y;
        if (collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) != 0) {
            ((TumbleBounceState *) effect->motion)->unk10 = groundY;
        } else {
            ((TumbleBounceState *) effect->motion)->unk10 = 0.0f;
        }
        ((TumbleBounceState *) effect->motion)->unk14 = 0;
    }
    ((TumbleBounceState *) effect->motion)->unk0 = (f32) ((f64) ((TumbleBounceState *) effect->motion)->unk0 + -0.63);
    effect->x += ((TumbleBounceState *) effect->motion)->unk4;
    effect->z += ((TumbleBounceState *) effect->motion)->unk8;
    effect->y += ((TumbleBounceState *) effect->motion)->unk0;
    if (effect->y < ((TumbleBounceState *) effect->motion)->unk10) {
        sfxId = 0x56;
        if (*(s32 **) effect->timerConfig == &D_8072073C) {
            sfxId = 0x1B1;
        } else if (*(s32 **) effect->timerConfig == &D_807212C8 || *(s32 **) effect->timerConfig == &D_807212B0) {
            sfxId = 7;
        }
        sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, sfxId,
            (u32) ((f64) (u32) effect->alpha * 0.7), 0x96, 1, 0x4B, 0.3f, 0);
        ((TumbleBounceState *) effect->motion)->unk0 = 5.0f;
        if (((TumbleBounceState *) effect->motion)->unk14 != 2) {
            ((TumbleBounceState *) effect->motion)->unk14++;
        }
    }
    if (((TumbleBounceState *) effect->motion)->unk14 == 2) {
        if (effect->alpha >= 0xB) {
            effect->alpha -= 0xA;
        } else {
            effect->alpha = 0;
        }
    }
    ((TumbleBounceState *) effect->motion)->unkC = (f32) ((f64) ((TumbleBounceState *) effect->motion)->unkC + 5.9);
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, ((TumbleBounceState *) effect->motion)->unkC, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}


typedef struct {
    f32 unk0;
    f32 unk4;
} SpiralDriftState;

void effectSpiralDriftMatrixUpdate(TimedEffectActorView *effect, s8 *isDone) {
    SpiralDriftState *newState;
    f32 offsetX;
    f32 offsetZ;
    EffectMatrix mtx;
    EffectMatrix rotMtx;

    if (effect->motion == NULL) {
        newState = heapAlloc(8);
        effect->motion = newState;
        offsetZ = effect->param * 2;
        newState->unk0 = (f32) offsetZ;
        ((SpiralDriftState *) effect->motion)->unk4 = 0.0f;
        effect->alpha = 0U;
    }
    if ((s32) effect->alpha >= 0xDD) {
        effect->alpha = 0xFFU;
    } else {
        effect->alpha += 0x14;
    }
    offsetX = (f32) ((f64) sinApprox(((SpiralDriftState *) effect->motion)->unk0 * 0.017453292f) * 2.5);
    offsetZ = cosApprox(((SpiralDriftState *) effect->motion)->unk0 * 0.017453292f);
    effect->x = (f32) (effect->x + offsetX);
    effect->y = (f32) ((f64) effect->y + 3.5);
    effect->z = (f32) (effect->z + (f32) ((f64) offsetZ * 2.5));
    ((SpiralDriftState *) effect->motion)->unk0 = (f32) ((f64) ((SpiralDriftState *) effect->motion)->unk0 + 8.0);
    ((SpiralDriftState *) effect->motion)->unk4 = (f32) ((f64) ((SpiralDriftState *) effect->motion)->unk4 + 7.3);
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, ((SpiralDriftState *) effect->motion)->unk4, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
} WobbleScaleState;

void effectWobbleScaleUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtxs[2][4][4];
    f32 wobbleX;
    f32 wave;
    f32 driftX;
    WobbleScaleState *state;
    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xC);
        ((WobbleScaleState *) effect->motion)->unk0 = 0;
        ((WobbleScaleState *) effect->motion)->unk4 = effect->scaleX;
        ((WobbleScaleState *) effect->motion)->unk8 = effect->scaleY;
    }
    ((WobbleScaleState *) effect->motion)->unk4 = (f32) ((f64) ((WobbleScaleState *) effect->motion)->unk4 + 0.0015);
    ((WobbleScaleState *) effect->motion)->unk8 = (f32) ((f64) ((WobbleScaleState *) effect->motion)->unk8 + 0.0015);
    driftX = (f32) ((f64) sinApprox((f32) (effect->param * 2)) * 0.2);
    wave = cosApprox((f32) (effect->param * 2));
    effect->x -= driftX;
    effect->y = (f32) ((f64) effect->y + 0.12);
    effect->z -= (f32) ((f64) wave * 0.2);
    effect->scaleX = ((WobbleScaleState *) effect->motion)->unk4;
    effect->scaleY = ((WobbleScaleState *) effect->motion)->unk8;
    wobbleX = sinApprox((f32) ((f64) ((WobbleScaleState *) effect->motion)->unk0 * 0.17));
    wave = sinApprox((f32) ((f64) ((WobbleScaleState *) effect->motion)->unk0 * 0.2267));
    state = (WobbleScaleState *) effect->motion;
    effect->scaleX = (f32) ((f64) effect->scaleX * (1.0 + ((f64) wobbleX * 0.15)));
    effect->scaleY = (f32) ((f64) effect->scaleY * (1.0 + ((f64) wave * 0.15)));
    if (!((WobbleScaleState *) effect->motion)->unk0) { // FAKE: dead re-read of state->unk0 steers the increment schedule
    }
    state->unk0++;
    if ((effect->count - effect->previousCount) < 10) {
        if (effect->alpha >= 0x16) {
            effect->alpha -= 0x14;
        } else {
            effect->alpha = 0;
        }
    }
    guScaleF(mtxs[1], effect->scaleX, effect->scaleY, 0.0f);
    guMtxF2L(mtxs[1], &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

void effectDecelerateDriftUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 stepX;
    f32 stepZ;
    RotationState *newState;
    RotationState *state;

    state = (RotationState *) effect->motion;
    if (state == NULL) {
        newState = heapAlloc(8);
        effect->motion = newState;
        newState->unk0 = ((f64) effect->scaleX / 0.36) * 2.5;
        newState->unk4 = (f32) (u32) ((gFrameCounter * 40) + (effect->param << 9));
        state = (RotationState *) effect->motion;
    }
    state->unk0 = (f32) ((f64) state->unk0 - 0.2);
    newState = state;
    if ((f64) state->unk0 < 0.8) {
        state->unk0 = 0.8f;
    }
    state = newState;
    stepX = mathSinF((s16) (s32) state->unk4);
    stepX = state->unk0 * stepX;
    stepZ = mathCosF((s16) (s32) state->unk4);
    stepZ = state->unk0 * stepZ;
    effect->x += stepX;
    effect->z += stepZ;
}


void timedEffectCountdownTick(TimedEffectActorView *effect, s8 *isDone) {
    u8 newAlpha;
    s32 alpha;
    s32 step;

    effectDecelerateDriftUpdate(effect, isDone);
    alpha = effect->alpha;
    effect->y = (f32)((f64)effect->y + 0.8);
    if (alpha < 0x10) {
        step = alpha;
    } else {
        step = 0x10;
    }
    newAlpha = alpha - step;
    effect->alpha = newAlpha;
    if (effect->alpha == 0) {
        *isDone = 1;
    }
}



typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} SpiralRiseState;

void effectSpiralRiseUpdate(TimedEffectActorView *effect, s8 *isDone) {
    SpiralRiseState *newState;
    f32 alpha;
    SpiralRiseState *state;
    f32 clampedAlpha;

    state = (SpiralRiseState *)effect->motion;
    if (state == NULL) {
        newState = heapAlloc(0x18);
        effect->motion = newState;
        newState->unk0 = effect->x;
        newState->unk4 = effect->z;
        newState->unk8 = 0.0f;
        newState->unkC = (f32)effect->param * 455.1111f;
        newState->unk10 = ((effect->param % 3) * 0x64) - 0x64;
        newState->unk14 = 375.0f;
        state = (SpiralRiseState *)effect->motion;
    }
    newState = effect->motion;
    effect->y = (f32)((f64)effect->y + 0.3);
    alpha = newState->unk14;
    if (alpha < 15.0f) {
        clampedAlpha = alpha;
    } else {
        clampedAlpha = 15.0f;
    }
    newState->unk14 = alpha - clampedAlpha; clampedAlpha = 255.0f; alpha = newState->unk14; if (alpha > clampedAlpha) { effect->alpha = (u8) ((u32) clampedAlpha); } else { effect->alpha = (u8) ((u32) alpha); } // LAYOUT: one source line keeps the as1 schedule
    state = newState;
    newState->unk8 = (f32)((f64)newState->unk8 + 1.5);
    state->unkC += state->unk10;
    effect->x = (mathSinF((s16)(s32)state->unkC) * newState->unk8) + newState->unk0;
    effect->z = (mathCosF((s16)(s32)state->unkC) * state->unk8) + newState->unk4;
    if (effect->alpha == 0) {
        *isDone = 1;
    }
}

void effectSpriteMotionUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 stepX;
    f32 stepZ;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(8);
        ((RotationState *)effect->motion)->unk0 = 3.2f;
        ((RotationState *)effect->motion)->unk4 = (f32)effect->param;
    }
    ((RotationState *)effect->motion)->unk0 = (f32)((f64)((RotationState *)effect->motion)->unk0 - 0.2);
    if ((f64)((RotationState *)effect->motion)->unk0 < 0.8) {
        ((RotationState *)effect->motion)->unk0 = 0.8f;
    }
    stepX = sinApprox(((RotationState *)effect->motion)->unk4 * 0.017453292f);
    stepX = stepX * ((RotationState *)effect->motion)->unk0;
    stepZ = cosApprox(((RotationState *)effect->motion)->unk4 * 0.017453292f);
    stepZ = stepZ * ((RotationState *)effect->motion)->unk0;
    effect->x = effect->x + stepX;
    effect->z = effect->z + stepZ;
    effect->y = effect->y + 1.0f;
}

void effectSpriteMatrixUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 offset;
    f32 pad;
    f32 phase;
    u8 *counter;
    f32 bob;

    phase = (f32)(effect->unk351 + (*(s16 *)((u8 *)effect + 0x34E) * 2));
    counter = (u8 *)effect->param;
    if (phase < 28.0f) {
        offset = phase;
    } else {
        offset = 56.0f - phase;
    }
    if (*counter != 0) {
        effect->x -= 12.0f;
        *counter -= 1;
    }
    if (sinApprox((f32)(((f64)phase / 56.0) * 6.2831854820251465)) > 0.0f) {
        bob = sinApprox((f32)(((f64)phase / 56.0) * 6.2831854820251465));
    } else {
        bob = -sinApprox((f32)(((f64)phase / 56.0) * 6.2831854820251465));
    }
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guTranslateF(tmpMtx, (f32)((f64)effect->x + ((f64)offset * 0.5)), effect->y - (bob * 15.0f), effect->z);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 3;
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} ParticleArcMotionState;

void effectParticleArcUpdate(TimedEffectActorView *effect, s8 *isDone) {
    void *ptr;
    s32 pad0;
    s32 pad1;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    s8 dirX;
    s8 dirY;
    s8 dirZ;
    s8 yaw;
    s16 tilt;
    f32 velX;
    f32 velY;
    f32 velZ;

    if (effect->motion == NULL) {
        yaw = (u32)-(s32)(randomLcgNext() / 10000U) % 30U;
        tilt = (u32)(randomLcgNext() / 10000U) % 180U;
        guRotateF(mtx, (f32)yaw, 0.0f, 1.0f, 0.0f);
        dirX = effect->param >> 0x10;
        dirY = (effect->param >> 8) & 0xFF;
        dirZ = effect->param & 0xFF;
        ptr = heapAlloc(0xC);
        effect->motion = ptr;
        guAlignF(tmpMtx, (f32)tilt, (f32)dirX, (f32)dirY, (f32)dirZ);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, -2.0f, &velX, &velY, &velZ);
        ((ParticleArcMotionState *)effect->motion)->unk0 = (f32)((f64)velX * 0.5);
        if (velY < 0.0f) {
            ((ParticleArcMotionState *)effect->motion)->unk4 = (f32)((f64)-velY * 0.5);
        } else {
            ((ParticleArcMotionState *)effect->motion)->unk4 = (f32)((f64)velY * 0.5);
        }
        ((ParticleArcMotionState *)effect->motion)->unk8 = (f32)((f64)velZ * 0.5);
    }
    effect->x += ((ParticleArcMotionState *)effect->motion)->unk0;
    effect->y += ((ParticleArcMotionState *)effect->motion)->unk4;
    effect->z += ((ParticleArcMotionState *)effect->motion)->unk8;
    if ((effect->count - effect->previousCount) < 0xA) {
        ((ParticleArcMotionState *)effect->motion)->unk4 = (f32)((f64)((ParticleArcMotionState *)effect->motion)->unk4 - 0.1);
        if ((s32)effect->alpha >= 0x16) {
            effect->alpha = effect->alpha - 0x14;
            return;
        }
        effect->alpha = 0;
    }
}

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} EffectTimer;

typedef struct TimedLightActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x188];
    EffectTimer *timerConfig;
    u8 pad334[0xC];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[2];
    s16 timer;
    u8 pad34F[0xC];
    s32 param;
} TimedLightActorView;

void lightSetFlags();
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);  // FAKE: callee prototype steer

extern PlayerState *gActivePlayerState;
extern void *D_80028C30;

void effectTimedLightIntensityFade(TimedLightActorView *effect, s8 *isDone) {
    f32 ratio;

    ratio = (f32)(effect->timerConfig->unk16 - effect->timer) / (f32)effect->timerConfig->unk16;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    if ((gActivePlayerState->actor == (Actor *)effect->param) && ((void *)effect == D_80028C30)) {
        lightSetFlags(1, effect);
        lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f,
                 (f32)((f64)ratio * 50.0), 0, 0xFF,
                 (u32)((-80.0f * ratio) + 255.0f),
                 (u32)((-205.0f * ratio) + 255.0f));
    }
}

extern s32 D_8002FBB0[];
extern s32 D_8002FBC0;
void timedLightOrbitUpdate(TimedLightActorView *effect, s8 *isDone) {
    f32 ratio;
    s32 *slot;

    ratio = (f32)(effect->timerConfig->unk16 - effect->timer) / (f32)effect->timerConfig->unk16;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    slot = &D_8002FBB0[0];
    do {
        if ((s32)effect == *slot) {
            lightSetFlags(1);
            lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f,
                     (f32)((f64)ratio * 50.0), 0, 0xFF,
                     (u32)((-80.0f * ratio) + 255.0f),
                     (u32)((-205.0f * ratio) + 255.0f));
            return;
        }
        slot++;
    } while (slot != &D_8002FBC0);
}


void effectLightPulseOscillate(TimedLightActorView *effect, s8 *isDone) {
    f32 ratio;
    f32 radius;
    s16 duration;
    s32 params;

    duration = effect->timerConfig->unk16;
    ratio = (f32)(duration - effect->timer) / (f32)duration;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    params = effect->param;
    if (((u32)params >> 16) != 0) {
        radius = (f32)(params & 0xFFFF) * ratio;
    } else {
        radius = (f32)(params & 0xFFFF);
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, (u32)((-80.0f * ratio) + 255.0f), (u32)((-205.0f * ratio) + 255.0f));
}

void effectLightFlickerDecay(TimedLightActorView *effect, s8 *isDone) {
    f32 ratio;
    f32 radius;
    s16 duration;
    s32 params;

    duration = effect->timerConfig->unk16;
    ratio = (f32)(duration - effect->timer) / (f32)duration;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    params = effect->param;
    if (((u32)params >> 16) != 0) {
        radius = (f32)(params & 0xFFFF) * ratio;
    } else {
        radius = (f32)(params & 0xFFFF);
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, 0xFF, 0xFF);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} RadialSprayMotion;

typedef struct RadialSprayActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x198];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[2];
    s16 timer;
    u8 pad350[0xC];
    s32 param;
    u8 pad360[0xD];
    u8 alpha;
    u8 pad36E[0x16];
    RadialSprayMotion *motion;
} RadialSprayActorView;


void effectRadialSprayUpdate(RadialSprayActorView *effect, s8 *isDone) {
    f32 pad80[4][4];
    f32 pad40[4][4];
    f32 pad3C;
    f32 angleDeg;
    f32 offsetZ;
    f32 groundY;
    s16 pad2E;
    s16 mode;
    s32 pad28;
    f32 angleRad;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0x10);
        mode = (s16) ((effect->param >> 16) & 0xFF);
        if (mode == 0) {
            effect->motion->unk0 = (f32) (((f64) (f32) ((randomLcgNext() / 10000U) % 100U) / 20.0) - 2.5);
        } else {
            effect->motion->unk0 = (f32) (((f64) (f32) ((randomLcgNext() / 10000U) % 100U) / 10.0) - 2.5);
        }
        angleDeg = (f32) ((effect->param & 0xFFFF) * 30);
        angleRad = angleDeg * 0.017453292f;
        angleDeg = (f32) ((f64) sinApprox(angleRad) * 2.5);
        offsetZ = (f32) ((f64) cosApprox(angleRad) * 2.5);
        effect->motion->unk4 = angleDeg;
        effect->motion->unk8 = offsetZ;
        if (mode != 1) {
            if (mode == 2) {
                effect->motion->unk4 = effect->motion->unk4 * 4.0f;
                effect->motion->unk8 = effect->motion->unk8 * 4.0f;
            }
        } else {
            effect->motion->unk4 *= 2;
            effect->motion->unk8 *= 2;
        }
        groundY = effect->y;
        if (collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) != 0) {
            effect->motion->unkC = groundY;
        } else {
            effect->motion->unkC = 0.0f;
        }
    }
    if (effect->timer >= 9) {
        effect->motion->unk0 = (f32) ((f64) effect->motion->unk0 + -0.63);
        effect->motion->unk4 = (f32) ((f64) effect->motion->unk4 * 0.9);
        effect->motion->unk8 = (f32) ((f64) effect->motion->unk8 * 0.9);
    }
    if (effect->timer >= ((effect->param >> 24) & 0xFF)) {
        if (effect->alpha >= 0x3C) {
            effect->alpha -= 0x3C;
        } else {
            effect->alpha = 0;
        }
    }
    effect->x += effect->motion->unk4;
    effect->z += effect->motion->unk8;
    effect->y += effect->motion->unk0;
    if (effect->y < effect->motion->unkC) {
        *isDone = 1;
    }
}


typedef struct {
    u8 pad0[0x58];
    s32 mode;
    u8 pad5C[4];
    u32 flags;
    u8 pad64[0x54];
    f32 speed;
    u8 padBC[0x32];
    s16 angle;
} ParentFollowView;

typedef struct FollowParentActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 state;
    u8 pad32D[0x13];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x10];
    ParentFollowView *parent;
    f32 scaleX;
    f32 scaleY;
    u8 pad368[5];
    u8 brightness;
    u8 pad36E[0x16];
    Mtx *matrix;
} FollowParentActorView;

void *memcpy(void *, const void *, size_t);

void effectFollowParentUpdate(FollowParentActorView *effect, s8 *isDone) {
    f32 mtx0[4][4];
    f32 mtx1[4][4];
    s32 angle;
    f32 trig;
    ParentFollowView *parent;

    parent = effect->parent;
    if (parent->flags & 4) {
        if (effect->matrix == NULL) {
            effect->matrix = heapAlloc(0x40);
            angle = (u32) (randomLcgNext() % 36000U) / 100U;
            guScaleF(mtx0, effect->scaleX, effect->scaleY, 0.0f);
            guRotateF(mtx1, (f32) angle, 0.0f, 0.0f, 1.0f);
            guMtxCatF(mtx0, mtx1, mtx0);
            guMtxF2L(mtx0, effect->matrix);
            effect->brightness = 0xC8;
        }
        if ((parent->mode == 0xC5) && ((f64) effect->scaleX < 0.5)) {
            trig = mathSinF(parent->angle);
            effect->x = (f32) ((f64) effect->x - ((10.0 * (f64) effect->scaleX) * (f64) trig));
            trig = mathCosF(parent->angle);
            effect->z = (f32) ((f64) effect->z - ((10.0 * (f64) effect->scaleX) * (f64) trig));
        } else {
            trig = mathSinF(parent->angle);
            effect->x = (f32) ((f64) effect->x + (((f64) parent->speed * 0.003) * (f64) trig));
            trig = mathCosF(parent->angle);
            effect->z = (f32) ((f64) effect->z + (((f64) parent->speed * 0.003) * (f64) trig));
            effect->y = (f32) ((f64) effect->y - 0.1);
        }
        if (parent->mode == 0xFE) {
            effect->y = (f32) ((f64) effect->y - 0.6);
        }
        memcpy(&effect->mtx[gGfxBufferIndex], effect->matrix, 0x40);
        effect->state = 2;
        return;
    }
    *isDone = 1;
}

typedef struct {
    u8 pad0[0xB8];
    f32 unkB8;
    u8 padBC[0x32];
    s16 unkEE;
} MotionParentView;

typedef struct {
    f32 unk0;
    f32 unk4;
} MotionState;

typedef struct MotionEffectActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x188];
    void *timerConfig;
    u8 pad334[4];
    void *parent;
    u8 pad33C[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x12];
    s16 unk35E;
    u8 pad360[0x24];
    void *motion;
} MotionEffectActorView;

void effectDownwardDriftUpdate(MotionEffectActorView *effect, s8 *isDone) {
    f32 new_var;
    f32 speed;

    speed = 0.35f;
    effect->y = (f32)((f64)effect->y - ((f64)speed * 0.5));
    new_var = mathSinF(effect->unk35E);
    effect->x = (f32)(effect->x + (0.35f * new_var));
    new_var = mathCosF(effect->unk35E);
    effect->z = (f32)(effect->z + (0.35f * new_var));
}

void effectUpwardDriftUpdate(MotionEffectActorView *effect, s8 *isDone) {
    f32 new_var;
    f32 speed;

    speed = 0.35f;
    effect->y = (f32)((f64)effect->y + ((f64)speed * 0.5));
    new_var = mathSinF(effect->unk35E);
    effect->x = (f32)(effect->x + (0.35f * new_var));
    new_var = mathCosF(effect->unk35E);
    effect->z = (f32)(effect->z + (0.35f * new_var));
}

void effectSineHorizontalDriftUpdate(MotionEffectActorView *effect, s8 *isDone) {
    f32 speed;
    f32 call_result;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(8);
        ((MotionState *)effect->motion)->unk0 = (f32)((MotionParentView *)effect->parent)->unkEE;
        ((MotionState *)effect->motion)->unk4 = ((MotionParentView *)effect->parent)->unkB8 + 30.0f;
    }
    speed = 0.35f;
    effect->y = (f32)((f64)effect->y + ((f64)speed * 0.5));
    speed = (f32)((f64)((MotionState *)effect->motion)->unk4 * 0.02);
    call_result = mathSinF((s16)(s32)((MotionState *)effect->motion)->unk0);
    effect->x = (f32)(effect->x + (speed * call_result));
    call_result = mathCosF((s16)(s32)((MotionState *)effect->motion)->unk0);
    effect->z = (f32)(effect->z + (speed * call_result));
    ((MotionState *)effect->motion)->unk4 -= 15.0f;
    if (((MotionState *)effect->motion)->unk4 < 0.0f) {
        ((MotionState *)effect->motion)->unk4 = 0.0f;
    }
}

void effectSineDriftUpdate(MotionEffectActorView *effect, s8 *isDone) {
    f32 speed;
    f32 call_result;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(4);
        ((MotionState *)effect->motion)->unk0 = ((MotionParentView *)effect->parent)->unkB8;
    }
    speed = 0.35f;
    effect->y = (f32)((f64)effect->y + ((f64)speed * 0.5));
    speed = (f32)((f64)((MotionState *)effect->motion)->unk0 * 0.02);
    call_result = mathSinF(effect->unk35E);
    effect->x = (f32)(effect->x + (speed * call_result));
    call_result = mathCosF(effect->unk35E);
    effect->z = (f32)(effect->z + (speed * call_result));
}

typedef struct GroundBounceActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 state;
    u8 pad32D[0x13];
    f32 x;
    f32 y;
    f32 z;
    s16 unk34C;
    s16 timer;
    u8 unk350;
    u8 unk351;
    u8 pad352[0xA];
    s32 rotation;
    f32 scaleX;
    f32 scaleY;
    u8 pad368[5];
    u8 brightness;
} GroundBounceActorView;


void effectGroundBounceUpdate(GroundBounceActorView *effect, s8 *isDone) {
    f32 mtx0[4][4];
    f32 mtx1[4][4];
    f32 groundY;
    f32 progress;
    f32 pad1;
    f32 pad2;

    groundY = effect->y;
    if ((collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) == 0) ||
        (((effect->y < groundY) ? (groundY - effect->y) : -(groundY - effect->y)) > 10.0)) {
        progress = (f32) effect->timer + ((f32) (u32) effect->unk351 / (f32) (u32) effect->unk350);
        if (effect->timer >= 7) {
            effect->y = (f32) ((f64) effect->y - (0.3 * ((f64) (14 - (s32) (20.0f - progress)) / 14.0)));
        }
    }
    if (effect->timer == 0x10) {
        effect->unk350 = 0xA;
    }
    guScaleF(mtx0, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(mtx1, (f32) ((effect->rotation * 360) / 4096), 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx0, mtx1, mtx0);
    guTranslateF(mtx1, effect->x, effect->y, effect->z);
    guMtxCatF(mtx0, mtx1, mtx0);
    guMtxF2L(mtx0, &effect->mtx[gGfxBufferIndex]);
    if (effect->timer >= 0x13) {
        effect->brightness -= 0x14;
    }
    effect->state = 3;
}

void effectFadeRatioStepUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 ratio;
    s32 intensity;

    ratio = (f32)(effect->timerConfig->unk16 - effect->timer) / (f32)effect->timerConfig->unk16;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    intensity = (u32)((-155.0f * ratio) + 255.0f) & 0xFF;
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 50.0f, 0, intensity, intensity, intensity);
}

void effectPuffExpandFadeUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 scale;
    f32 divisor;
    s16 timer;

    divisor = 4.0f;
    timer = effect->timer;
    if (timer >= 5) {
        timer = 4;
    }
    scale = (f32)((f64)((f32)timer / divisor) * 3.0);
    effect->scaleX = scale;
    effect->scaleY = scale;
}

typedef struct SparkSpawnActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x198];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[2];
    s16 timer;
    u8 pad350[4];
    s32 count;
    s32 previousCount;
    u8 pad35C[0x11];
    u8 brightness;
} SparkSpawnActorView;

void effectSetColor(s32, s32, s32, s32);  // FAKE: callee prototype steer
extern u8 sEffectSparkConfig;

void effectSparkSpawnUpdate(SparkSpawnActorView *effect, s8 *isDone) {
    s32 pad;
    s32 random;

    if (effect->previousCount == 0) {
        if (effect->brightness < 0xE1) {
            effect->brightness += 0x1E;
        } else {
            effect->brightness = 0xFF;
        }
    }
    if ((effect->timer == 3) || (effect->timer == 0x11) || (effect->timer == 0x15)) {
        sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, 0x14F, 0xFF, 0x7F, 0x1E, 0x4B, 0.3f, 0);
    }
    if ((effect->count - effect->previousCount) < 3) {
        if (effect->brightness >= 0xB) {
            effect->brightness -= 0xA;
        } else {
            *isDone = 1;
        }
        return;
    }
    if (((randomNonNegative() >> 15) % 100) >= 91) {
        effectSetMode(3);
        effectSetCallback(func_80717D4C);
        effectSetSpeed(-0xA);
        effectSetDepth(1);
        effectSetColor(0x9B, 0x9B, 0x9B, 0x96);
        random = randomNonNegative();
        effectCreateAtPosition((s32)&sEffectSparkConfig, 0.8f,
            (f32)(((random >> 15) % 65535) & 7) + effect->x,
            effect->y + 10.0f,
            (f32)(((randomNonNegative() >> 15) % 65535) & 7) + effect->z);
    }
}

typedef struct {
    f32 angle;
    f32 speed;
} RandomRotationState;

void effectSpinBillboardingUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(8);
        ((RandomRotationState *)effect->motion)->angle = (f32)((randomLcgNext() % 36000U) / 100U);
        ((RandomRotationState *)effect->motion)->speed = (f32)((f64)(randomLcgNext() % 10000U) / 7000.0);
    }
    effect->y = (f32)((f64)effect->y + ((f64)((RandomRotationState *)effect->motion)->speed + 1.0));
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, ((RandomRotationState *)effect->motion)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} VelocityState;

void func_8071BC80(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 pad;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    VelocityState *state;

    state = effect->motion;
    if (state == NULL) {
        effect->motion = heapAlloc(0xC);
        guRotateF(mtx, -(f32)((randomLcgNext() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(tmpMtx, (f32)((effect->param * 0x168) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, 10.0f, &dirX, &dirY, &dirZ);
        ((VelocityState *)effect->motion)->unk0 = dirX;
        ((VelocityState *)effect->motion)->unk4 = dirY;
        ((VelocityState *)effect->motion)->unk8 = dirZ;
        state = effect->motion;
    }
    effect->x += state->unk0;
    effect->y += state->unk4;
    effect->z += state->unk8;
}

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    u8 unk4;
} WaveMotionData;

typedef struct {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    u8 padC[4];
    s16 unk10;
    u8 pad12[2];
    WaveMotionData *unk14;
} WaveMotionState;

typedef struct WaveMotionActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 mtxState;
    u8 pad32D[0x13];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x10];
    WaveMotionState *param;
    f32 scaleX;
    f32 scaleY;
    u8 pad368[5];
    s8 alpha;
} WaveMotionActorView;

void effectWaveMotionUpdate(WaveMotionActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 scale;
    WaveMotionState *wave2;
    WaveMotionData *data;
    f32 wave;

    wave2 = effect->param;
    data = wave2->unk14;
    wave = mathSinF(wave2->unk10);
    effect->alpha = (u32) ((f32) (u32) data->unk0 * wave);
    wave = 1.0f - wave;
    scale = effect->scaleY;
    if (data->unk4 != 0) {
        scale = (f32) ((((f64) mathSinF(data->unk2) * 0.15) + 0.85) * (f64) effect->scaleY);
        data->unk2 += 0xAA;
        data->unk2 &= 0xFFF;
    }
    guScaleF(mtx, effect->scaleX, scale, 0.0f);
    guTranslateF(tmpMtx, effect->x + (wave2->unk4 * wave), effect->y + (wave2->unk8 * wave), effect->z);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 3;
}

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} PulseTimer;

typedef struct PulseFadeActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x188];
    PulseTimer *timerConfig;
    u8 pad334[0xC];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[2];
    s16 timer;
    u8 pad350;
    u8 unk351;
    u8 pad352[0xA];
    u32 param;
} PulseFadeActorView;

extern u8 D_807201D4;

void timedLightPulse(PulseFadeActorView *effect, s8 *isDone) {
    f64 ratio;
    s32 phase;
    s16 timer;
    s16 color[3];
    f32 total;
    f32 elapsed;
    f32 frac;

    if (gCurrentMap == 0xAA) {
        color[0] = 0xFF; color[1] = 0x46;
        color[2] = 0;
    } else {
        color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
    }
    phase = effect->param;
    switch (phase) {
        case 0:
            timer = effect->timer;
            if ((timer == 0xA) && (effect->unk351 == 0)) {
                sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, 0xE4, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
                effectSetDuration(-1);
                effectSetDepth(1);
                effectSetCallback(effectFallingSparkUpdate);
                effectCreateAtPosition((s32)&D_807201D4, 0.8f, effect->x, effect->y, effect->z);
                return;
            }
            total = (f32)(effect->timerConfig->unk16 * 2);
            elapsed = (f32)((timer * 2) + effect->unk351);
            ratio = (f64)((total - elapsed) / total);
            frac = (f32)(1.0 - ratio);
            lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 200.0f * frac, 0, 0xFF, color[1], color[2]);
            return;
        case 1:
            total = (f32)(effect->timerConfig->unk16 * 2);
            elapsed = (f32)((effect->timer * 2) + effect->unk351);
            frac = (total - elapsed) / total;
            lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 200.0f * frac, 0, 0xFF, color[1], color[2]);
            return;
    }
}

extern u8 D_8071FB54;

void effectFallingSparkUpdate(TimedEffectActorView *effect, u8 *isDone) {
    f32 *state;
    f32 groundY;
    s16 color[3];
    f32 *newState;

    if (effect->motion == 0) {
        newState = heapAlloc(0xC);
        effect->motion = newState;
        *newState = 6.0f;
    }
    if (gCurrentMap == 0xAA) {
        color[0] = 0xFF; color[1] = 0x46;
        color[2] = 0;
    } else {
        color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
    }
    state = effect->motion;
    effect->x = effect->x + 1.0f;
    effect->y += *state;
    *state = (f64)*state - 0.15;
    groundY = effect->y;
    if (collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) == 0) {
        *isDone = 1;
    } else if ((effect->y < groundY) && ((f64)*(f32 *)effect->motion < 0.0)) {
        *isDone = 1;
    }
    if (*isDone != 0) {
        sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, 0xEA, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
        effectSetMode(2);
        effectSetDepth(1);
        effectSetSpeed(1);
        effectSetCallback(timedLightPulse);
        effectSetParam(7);
        effectCreateAtPosition((s32)&D_8071FB54, 0.667f, effect->x, groundY + 10.0f, effect->z);
    }
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 200.0f, 0, color[0], color[1], color[2]);
}

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} LightTimer;

typedef struct TimedLightEffectActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x188];
    LightTimer *timerConfig;
    u8 pad334[0xC];
    f32 x;
    f32 y;
    f32 z;
    s16 unk34C;
    s16 timer;
    u8 pad350;
    u8 unk351;
    u8 pad352[0xA];
    u32 param;
} TimedLightEffectActorView;


void func_8071C48C(TimedLightEffectActorView *effect, s8 *isDone) {
    f32 ratio;
    f32 radius;
    s16 duration;
    u32 params;

    duration = effect->timerConfig->unk16;
    ratio = (f32)(duration - effect->timer) / (f32)duration;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    params = effect->param;
    if ((params >> 0x10) != 0) {
        radius = (f32)(s32)(params & 0xFFFF) * ratio;
    } else {
        radius = (f32)(s32)(params & 0xFFFF);
    }
    lightSetFlags(1, effect);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, radius, 0, 0,
             (u32)((-80.0f * ratio) + 255.0f), 0xFF);
}

void func_8071C620(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    VelocityState *state;

    state = effect->motion;
    if (state == NULL) {
        effect->motion = heapAlloc(0xC);
        guRotateF(mtx, (f32)((randomLcgNext() % 36000U) / 100U), 1.0f, 0.0f, 0.0f);
        guRotateF(tmpMtx, (f32)((randomLcgNext() % 36000U) / 100U), 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guRotateF(mtx, (f32)((randomLcgNext() % 36000U) / 100U), 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, 0.5f, &dirX, &dirY, &dirZ);
        ((VelocityState *)effect->motion)->unk0 = dirX;
        ((VelocityState *)effect->motion)->unk4 = dirY;
        ((VelocityState *)effect->motion)->unk8 = dirZ;
        state = effect->motion;
    }
    effect->x += state->unk0;
    effect->y += state->unk4;
    effect->z += state->unk8;
}

void effectShrinkFadeMatrixUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    effect->scaleX = (f32)((f64)effect->scaleX - 0.05);
    effect->scaleY = (f32)((f64)effect->scaleY - 0.05);
    if (effect->scaleX <= 0.0f) {
        *isDone = 1;
    }
    effect->param = effect->param + 5;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, (f32)effect->param, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

void effectGrowExpandMatrixUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 scale;

    effect->scaleX = (f32)((f64)effect->scaleX * 1.07);
    effect->param = effect->param + 0xA;
    scale = effect->scaleX;
    effect->scaleY = scale;
    guScaleF(mtx, scale, scale, 0.0f);
    guRotateF(tmpMtx, (f32)effect->param, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 x;
    s16 z;
    s16 target_y;
    s16 rotation;
} FxInt1C9State;

s16 D_80755650[18] = {
    0x01D4, 0x0078, 0x026D, 0x01EE, 0x0082, 0x02F6, 0x02E5, 0x008C, 0x0254,
    0x02C3, 0x0078, 0x02FA, 0x025A, 0x006E, 0x0312, 0x025E, 0x0096, 0x026A,
};
extern s32 D_8071FB08;

void effectWispWanderUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    FxInt1C9State *state;
    u8 homeIndex;
    s16 targetAngle;
    s16 *home;

    if (effect->motion == NULL) {
        homeIndex = (randomNonNegative() >> 0xF) % 1000 % 6;
        effect->motion = heapAlloc(0xE);
        state = effect->motion;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        home = &D_80755650[homeIndex * 3];
        state->x = home[0];
        state->z = home[1];
        state->target_y = home[2];
        state->rotation = 0;
        state->y = (s16)effect->y;
    }
    state = effect->motion;
    if (gPrimaryPlayerActor->z < 340.0f) {
        state->x = 0x12C;
        state->z = 0x96;
        state->target_y = 0x64;
    }
    targetAngle = mathAngleBetweenPoints2D((f32)state->x, (f32)state->target_y, effect->x, effect->z);
    state->angle = mathAngleEaseToward(state->angle, targetAngle, (f32)(((randomNonNegative() >> 0xF) % 10) + 5));
    state->y = (s16)((f64)(state->z - state->y) * 0.1 + (f64)state->y);
    effect->x += state->speed * mathSinF(state->angle);
    effect->z += state->speed * mathCosF(state->angle);
    effect->y = (f32)((((f64)mathSinF((state->speed + 0x32) * gFrameCounter)) * 40.0) + (state->y + 0x28));
    if (((randomNonNegative() >> 0xF) % 1000) >= 991) {
        homeIndex = ((randomNonNegative() >> 0xF) % 1000) % 6;
        state->x = D_80755650[homeIndex * 3];
        state->z = D_80755650[(homeIndex * 3) + 1];
        state->target_y = D_80755650[(homeIndex * 3) + 2];
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(gFrameCounter & 3)) {
        effectSetDepth(1);
        effectSetCallback(effectShrinkFadeMatrixUpdate);
        effectCreateAtPosition((s32)&D_8071FB08, 1.6f, effect->x, effect->y, effect->z);
    }
    state->rotation += state->speed;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, (f32)state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}


typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 rotation;
} WispHomeMotionState;

typedef struct {
    u8 pad0[0x7C];
    f32 x;
    f32 y;
    f32 z;
    u8 pad88[0xD6];
    u8 height;
} WispHomeTargetActor;

void effectWispHomeUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    WispHomeMotionState *state;
    WispHomeTargetActor *actor;
    s16 currentAngle;
    s16 targetAngle;
    f32 turnRate;

    if (effect->motion == NULL) {
        randomNonNegative();
        state = heapAlloc(8);
        effect->motion = state;
        state->angle = 0;
        state->y = (s16)effect->y;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        state->rotation = 0;
    }
    state = effect->motion;
    actor = (WispHomeTargetActor *)(u32)effect->param;
    targetAngle = mathAngleBetweenPoints2D(actor->x, actor->z, effect->x, effect->z);
    turnRate = ((randomNonNegative() >> 0xF) % 10) + 5;
    currentAngle = state->angle;
    state->angle = mathAngleEaseToward(currentAngle, targetAngle, turnRate);
    state->y = (s16)((((f64)((actor->y + ((f32)((u32)actor->height))) - ((f32)state->y))) * 0.1) + ((f64)state->y));
    effect->x += state->speed * mathSinF(state->angle);
    effect->z += state->speed * mathCosF(state->angle);
    effect->y = (f32)((((f64)mathSinF((state->speed + 0x32) * gFrameCounter)) * 40.0) + (state->y + 0x28));
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(gFrameCounter & 3)) {
        effectSetDepth(1);
        effectSetCallback(effectShrinkFadeMatrixUpdate);
        effectCreateAtPosition((s32)&D_8071FB08, 1.6f, effect->x, effect->y, effect->z);
    }
    state->rotation += state->speed;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, (f32)state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} LightApproachMotionState;

extern u8 gCurrentWorldId;
extern u16 gLevelCollectibleCounts[];

void effectConvergeOnNodeUpdate(TimedEffectActorView *effect, s8 *isDone) {
    LightApproachMotionState *motion;
    f32 factor;
    s32 node;
    f64 pad;

    node = effect->param;
    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0x10);
        ((LightApproachMotionState *)effect->motion)->unk0 = 30.0f;
    }
    motion = effect->motion;
    actorGetNodePos(node, 1, &motion->unk4, &motion->unk8, &motion->unkC);
    factor = (f32)((f64)motion->unk0 / 30.0);
    effect->x = (gPrimaryPlayerActor->x - motion->unk4) * factor + motion->unk4;
    effect->y = (gPrimaryPlayerActor->y - motion->unk8) * factor + motion->unk8;
    effect->z = (gPrimaryPlayerActor->z - motion->unkC) * factor + motion->unkC;
    motion->unk0 -= 1.0f;
    if (motion->unk0 == 0.0f) {
        gActivePlayerState->stateFlags |= 0x20000;
        gLevelCollectibleCounts[mapGetHubWorldIndex(gCurrentWorldId, 0)]++;
        *isDone = 1;
    }
}


void effectLifetimeCountdownUpdate(TimedEffectActorView *effect, s8 *isDone) {
    u16 difference;
    s32 amount;
    u8 remaining;
    s32 completed;

    amount = effect->param;
    difference = effect->alpha - amount;
    completed = 1;
    remaining = difference;
    effect->alpha = remaining;
    if (amount >= remaining) {
        *isDone = completed;
    }
}


typedef struct OrbitSourceActor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x24];
    f32 unkAC;
    u8 padB0[0x8];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
} OrbitSourceActor;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} OrbitSourceState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} BallisticVelocityState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} FallInitState;



void effectOrbitSourceUpdate(TimedEffectActorView *effect, s8 *isDone) {
    OrbitSourceState *state;
    OrbitSourceState *newState;
    OrbitSourceActor *source;

    source = effect->parent;
    if (effect->motion == NULL) {
        newState = heapAlloc(0x20);
        effect->motion = newState;
        newState->unk0 = sqrtf(((source->unk7C - effect->x) * (source->unk7C - effect->x)) + ((source->unk84 - effect->z) * (source->unk84 - effect->z)));
        newState->unk4 = (randomFloat() * 20.0f) + 10.0f;
        newState->unk8 = randomFloat() * 4095.0f;
        newState->unkC = (randomFloat() * 90.0f) + 10.0f;
        newState->unk10 = (f32) source->unkE6;
        newState->unk14 = randomFloat() * 30.0f;
        newState->unk18 = 0.0f;
        newState->unk1C = (f32) (((randomNonNegative() >> 0xF) % 0xFF) % 2) * 2 - 1.0f;
    }
    state = effect->motion;
    state->unk0 = (f32) (((f64) (state->unk4 - state->unk0) * 0.15) + (f64) state->unk0);
    state->unk14 = (f32) (((f64) (120.0f - state->unk14) * 0.01) + (f64) state->unk14);
    state->unk10 = state->unk10 + (state->unk1C * state->unk14);
    state->unk8 = state->unk8 + state->unkC;
    effect->x = (mathSinF((s16) state->unk10) * state->unk0) + source->unk7C;
    effect->z = (mathCosF((s16) state->unk10) * state->unk0) + source->unk84;
    effect->y += 0.6 * mathSinF((s16) state->unk8);
    state->unk18 = state->unk18 + 1.0f;
    if (45.0f < state->unk18) {
        *isDone = 1;
    }
    if ((gFrameCounter % effect->param) == 0) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetSpeed(0x2A);
        effectSetCallback(&effectLifetimeCountdownUpdate);
        effectSetFlags(0x20);
        effectCreateAtPosition(*(s32 *) effect->timerConfig, effect->scaleX, effect->x, effect->y, effect->z);
    }
}

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xD6];
    u8 unk15E;
} ShockwavePlayerView;

void effectShockwaveRingUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    ShockwavePlayerView *player;
    s32 radius;

    radius = (s32) (effect->scaleX * 20.0f);
    player = (ShockwavePlayerView *) gPrimaryPlayerActor;
    if ((player->unk80 <= effect->y) && (effect->y < player->unk80 + (f32) player->unk15E)) {
        if ((((player->unk7C - effect->x) * (player->unk7C - effect->x)) + ((player->unk84 - effect->z) * (player->unk84 - effect->z))) < (f32) (radius * radius)) {
            playerStateQueueCallback(0x2E, 0, 0);
        }
    }
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guTranslateF(tmpMtx, effect->x, effect->y, effect->z);
    guMtxCatF(mtx, tmpMtx, mtx);
    if ((s32) effect->alpha >= 9) {
        effect->alpha -= 9;
    } else {
        *isDone = 1;
    }
    effect->scaleX = (f32) ((f64) effect->scaleX * 1.08);
    effect->scaleY = effect->scaleX;
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 3;
}

f32 D_80755674 = -0.1f;
f32 D_80755678 = 2.0f;

void effectBallisticUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    s32 pad;
    f32 dirX;
    f32 dirY;
    f32 dirZ;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xC);
        guRotateF(mtx, -(f32) ((randomLcgNext() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(tmpMtx, (f32) ((effect->param * 360) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, D_80755678, &dirX, &dirY, &dirZ);
        ((BallisticVelocityState *) effect->motion)->unk0 = dirX;
        ((BallisticVelocityState *) effect->motion)->unk4 = dirY;
        ((BallisticVelocityState *) effect->motion)->unk8 = dirZ;
    }
    effect->x = effect->x + ((BallisticVelocityState *) effect->motion)->unk0;
    effect->y = effect->y + ((BallisticVelocityState *) effect->motion)->unk4;
    ((BallisticVelocityState *) effect->motion)->unk4 = ((BallisticVelocityState *) effect->motion)->unk4 + D_80755674;
    effect->z = effect->z + ((BallisticVelocityState *) effect->motion)->unk8;
    if (effect->y <= ((ShockwavePlayerView *) gPrimaryPlayerActor)->unk80) {
        *isDone = 1;
    }
}

void effectFallStateInit(OrbitSourceActor *effect, TimedEffectActorView *target, s8 *isDone) {
    s16 unusedAngle;
    s16 angle;
    f32 speedXZ;
    f32 sourceSpeed;
    f32 speedY;
    FallInitState *fallState;
    FallInitState *newState;
    f32 jitter;
    s16 angleOffset;

    newState = heapAlloc(0x10);
    target->motion = newState;
    fallState = newState;
    jitter = randomFloat();
    target->x = target->x + ((jitter - 0.5f) * 2.0f);
    jitter = randomFloat();
    target->y = target->y + ((jitter - 0.5f) * 2.0f);
    jitter = randomFloat();
    target->z = target->z + ((jitter - 0.5f) * 2.0f);
    if (effect != NULL) {
        angleOffset = randomLcgNext() & 0x1FF;
        angle = (effect->unkE6 + angleOffset + 0x700) & 0xFFF;
        sourceSpeed = effect->unkB8 * 0.016666668f;
        if (!(sourceSpeed < 1.0f)) {
            sourceSpeed = 1.0f;
        }
        if (sourceSpeed < 0.3) {
            *isDone = 1;
        }
        speedY = sourceSpeed * 1.5f * 1.8f;
        target->parent = effect;
    } else {
        sourceSpeed = 0.8f;
        angle = (s16) (randomLcgNext() % 4095U);
        speedY = (randomFloat() + 1.0f) * 3.0f;
    }
    target->scaleX *= 0.5 * (1 + randomFloat());
    target->alpha = 0x82;
    target->scaleY = target->scaleX;
    speedXZ = randomFloat() * sourceSpeed;
    fallState->unk0 = mathSinF(angle) * speedXZ;
    fallState->unk4 = mathCosF(angle) * speedXZ;
    fallState->unk8 = speedY;
    collisionGetFloorHeight(&fallState->unkC);
}

void effectFloorFallUpdate(TimedEffectActorView *effect, u8 *isDone) {
    FallInitState *state;
    OrbitSourceActor *floor;
    s32 landed;

    if (effect->motion == NULL) {
        effectFallStateInit(0, effect, isDone);
    }
    state = effect->motion;
    state->unk8 = state->unk8 + -0.5f;
    effect->x = effect->x + state->unk0;
    effect->y = effect->y + state->unk8;
    effect->z = effect->z + state->unk4;
    landed = *isDone;
    if (landed == 0) {
        floor = effect->parent;
        if (floor != NULL) {
            if (effect->y <= floor->unkAC) {
                landed = *isDone = 1;
            }
        } else {
            if (effect->y <= state->unkC) {
                landed = *isDone = 1;
            }
        }
        if (landed != 0) {
            effectSpawnImpactPuff(effect->scaleX * 5.0f, effect->x, effect->y, effect->z);
        }
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} ActorOrbitState;

void effectActorOrbitFollowUpdate(TimedEffectActorView *effect, s8 *isDone) {
    ActorOrbitState *state;
    Actor *target;
    PlayerState *targetState;
    f32 blend;

    blend = 0.3f;
    target = (Actor *)effect->param;
    if (effect->motion == NULL) {
        state = heapAlloc(0x18);
        effect->motion = state;
        state->unk0 = 0.0f;
        state->unk4 = (f32)(randomFloat() * 4095.0f);
        state->unk8 = (f32)((randomFloat() > 0.5 ? (f64)randomFloat() : 0.5) * 300.0);
        if ((f64)randomFloat() > 0.5) {
            state->unk8 = (f32)-state->unk8;
        }
        state->unkC = (f32)(randomFloat() * 4095.0f);
        state->unk10 = (f32)((randomFloat() > 0.5 ? (f64)randomFloat() : 0.5) * 300.0);
        if ((f64)randomFloat() > 0.5) {
            state->unk10 = (f32)-state->unk10;
        }
        state->unk14 = (f32)(randomFloat() > 0.3 ? (f64)randomFloat() : 0.3);
        blend = 1.0f;
    }
    state = effect->motion;
    if (state->unk0 < 1.0f) {
        state->unk0 = state->unk0 + 0.033333335f;
    }
    state->unk4 = (f32)(state->unk4 + state->unk8);
    state->unk4 = (f32)((((s32)state->unk4 & 0xFFF) & 0xFFFF) & 0xFFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    state->unkC = (f32)(state->unkC + state->unk10);
    state->unkC = (f32)((((s32)state->unkC & 0xFFF) & 0xFFFF) & 0xFFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    effect->x = (f32) (((((mathSinF((s16) (s32) state->unk4) * (15.0f * state->unk0)) + target->x) - effect->x) * blend) + effect->x);
    effect->z = (f32) (((((mathCosF((s16) (s32) state->unk4) * (15.0f * state->unk0)) + target->z) - effect->z) * blend) + effect->z);
    effect->y = (f32) (((((((mathSinF((s16) (s32) state->unkC) * (state->unk14 * state->unk0)) + 1.0f) * 15.0f) + target->y) - effect->y) * blend) + effect->y);
    targetState = target->customState;
    if (!(targetState->stateFlags & 0x10)) {
        *isDone = 1;
    }
}

void func_8071E028(TimedEffectActorView *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guTranslateF(tmpMtx, 0.0f, effect->scaleY * 20.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, (f32)effect->param, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} TimedMotionState;

void func_8071E110(TimedEffectActorView *actorView, u8 duration, u16 maxVal, f32 startVal, f32 endVal, s32 steps) {
    TimedMotionState *motion;

    motion = heapAlloc(0x18);
    actorView->motion = motion;
    motion->unk0 = (f32)(u32)duration;
    motion->unk4 = endVal;
    motion->unk8 = startVal;
    motion->unkC = 1.0f / (f32)steps;
    motion->unk10 = 0.0f;
    motion->unk14 = (f32)(u32)maxVal;
}

void effectArcAroundActorUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f64 pad0;
    f32 offsetX;
    f32 pad1;
    f64 pad2;
    f32 radius;
    f32 pad3;
    f32 height;
    f32 cosYaw;
    f32 arcAngle;
    f32 offsetY;
    Actor *target;
    TimedMotionState *state;

    if (effect->motion == NULL) {
        *isDone = 1;
        return;
    }
    state = effect->motion;
    target = (Actor *)effect->param;
    if (actorTableContains(target) == 0) {
        *isDone = 1;
        return;
    }
    arcAngle = state->unk10 * ((1.0f - (state->unk0 * 2)) * 2048.0f);
    arcAngle = (f32)((((s32)arcAngle & 0xFFFF) & 0xFFFF) & 0xFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    radius = mathSinF((s16)(s32)arcAngle) * state->unk8;
    state->unk14 = (f32)((f64)state->unk14 + (2.0 * (f64)((1.0f - (state->unk0 * 2)) * 4096.0f) * (f64)state->unkC));
    state->unk14 = (f32)((((s32)state->unk14 & 0xFFF) & 0xFFFF) & 0xFFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    offsetX = mathSinF((s16)(s32)state->unk14) * radius;
    cosYaw = mathCosF((s16)(s32)state->unk14);
    height = state->unk4;
    offsetY = state->unk10 * height;
    if (state->unk0 == 0.0f) {
        offsetY = height - offsetY;
    }
    effect->x = (f32)(target->x + offsetX);
    effect->z = (f32)(target->z + (cosYaw * radius));
    effect->y = (f32)(target->y + offsetY);
    state->unk10 = (f32)(state->unk10 + state->unkC);
    if (state->unk10 >= 1.0f) {
        *isDone = 1;
    }
}


void effectLightGrowShrinkUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f64 size;
    f32 intensity;
    f32 red;
    f32 green;
    f32 blue;
    f32 brightness;
    s32 mode;
    VelocityState *newState;
    VelocityState *state;

    if (effect->motion == NULL) {
        newState = heapAlloc(0xC);
        effect->motion = newState;
        newState->unk0 = 0.0f;
        newState->unk4 = 0.0f;
        newState->unk8 = (f32)mapChunkFindByPosition(effect->x, effect->y, effect->z, 0);
    }
    state = effect->motion;
    if ((f64)state->unk4 == 0.0) {
        state->unk0 = (f32)((f64)state->unk0 + 30.0);
        size = (f64)state->unk0;
        if (size > 300.0) {
            state->unk4 = 1.0f;
            state->unk0 = 300.0f;
        }
    } else {
        state->unk0 = (f32)((f64)state->unk0 - 30.0);
        size = (f64)state->unk0;
        if (size < 30.0) {
            *isDone = 1;
            state->unk0 = 30.0f;
        }
    }
    size = (f64)state->unk0;
    if (size < 300.0) {
        intensity = (f32)(size / 300.0);
    } else {
        intensity = 1.0f;
    }
    lightSetRadius(1000);
    lightSetTargetId((s16)(s32)state->unk8);
    mode = effect->param;
    switch (mode) {
    case 0:
        red = 1.0f;
        green = 1.0f;
        blue = 1.0f;
        lightSetFlags(2);
        lightSetRadius(1000);
        break;
    case 1:
        red = 1.0f;
        green = 0.5f;
        blue = 0.3f;
        lightSetFlags(3);
        lightSetRadius(1000);
        break;
    case 2:
        red = 1.0f;
        green = 0.5f;
        blue = 0.3f;
        lightSetFlags(2);
        lightSetRadius(2000);
        break;
    case 3:
        red = 1.0f;
        green = 1.0f;
        blue = 1.0f;
        lightSetFlags(2);
        lightSetRadius(2000);
        break;
    }
    brightness = 255.0f * intensity;
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, state->unk0, 0, (u32)(brightness * red), (u32)(brightness * green), (u32)(brightness * blue));
}

typedef struct {
    f32 unk0;
    f32 unk4;
} DecelDriftState;

void effectDecelDriftFadeUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 stepX;
    DecelDriftState *newState;
    DecelDriftState *state;
    f32 stepZ;

    if (effect->motion == NULL) {
        newState = heapAlloc(8);
        effect->motion = newState;
        newState->unk0 = 10.0f;
        newState->unk4 = (f32)(effect->param * 0x154);
    }
    state = (DecelDriftState *)effect->motion;
    state->unk0 = (f32)((f64)state->unk0 - 0.2);
    if ((f64)state->unk0 < 0.8) {
        state->unk0 = 0.8f;
    }
    stepX = mathSinF((s16)(s32)state->unk4);
    stepX = state->unk0 * stepX;
    stepZ = mathCosF((s16)(s32)state->unk4);
    stepZ = state->unk0 * stepZ;
    effect->scaleX = (f32)((f64)effect->scaleX * 1.08);
    effect->scaleY = (f32)((f64)effect->scaleY * 1.08);
    if ((f64)effect->scaleX > 8.0) {
        effect->alpha = effect->alpha - 0x32;
        if (effect->alpha < 0x33) {
            *isDone = 1;
        }
    }
    effect->x = (f32)(effect->x + stepX);
    effect->z = (f32)(effect->z + stepZ);
}

void effectBurstParticleUpdate(TimedEffectActorView *effect, s8 *isDone) {
    TimedMotionState *state;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xC);
        state = (TimedMotionState *)effect->motion;
        state->unk0 = randomFloat() * 4095.0f;
        state->unk4 = (f32)(((f64)randomFloat() * 0.5 + 1.0) * 5.0);
        state->unk8 = 15.0f;
    }
    state = (TimedMotionState *)effect->motion;
    state->unk4 = state->unk4 - 1.0f;
    state->unk8 = (f32)((f64)state->unk8 * 0.95);
    effect->x += state->unk8 * mathSinF((s16)state->unk0);
    effect->z += state->unk8 * mathCosF((s16)state->unk0);
    effect->y = effect->y + state->unk4;
}



void effectProximityFadeUpdate(TimedEffectActorView *effect, s8 *isDone) {
    f32 *state;
    PlayerDistanceView *player;
    f32 limit;
    f32 dist;
    f32 dx;
    f32 dy;
    s32 iv;
    f32 dz;

    limit = (f32)((effect->param * 3) / 4);
    if (effect->motion == NULL) {
        effect->motion = heapAlloc(4);
        *(f32 *)effect->motion = (f32)effect->alpha;
    }
    state = (f32 *)effect->motion;
    player = gPlayerSlots;
    dz = player->unk224 - effect->z;
    dx = player->unk21C - effect->x;
    dy = player->unk220 - effect->y;
    dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
    if (dist < limit) {
        effect->alpha = (u32)*state;
        return;
    }
    iv = *state * ((dist - limit) / ((f32)effect->param - limit));
    if (*state < (f32)iv) {
        iv = *state;
    }
    effect->alpha = (u32)(*state - (f32)iv);
}


typedef struct TargetTrackingActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x198];
    f32 x;
    f32 y;
    f32 z;
    u8 pad34C[0x10];
    s32 param;
} TargetTrackingActorView;

void func_8071EDEC(TargetTrackingActorView *effect, s32 unused) {
    f64 pad;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    actorGetNodePos(effect->param, 1, &nodeX, &nodeY, &nodeZ);
    effect->x = (f32)((f64)effect->x + ((f64)(nodeX - effect->x) * 0.1));
    effect->y = (f32)((f64)effect->y + ((f64)(nodeY - effect->y) * 0.1));
    effect->z = (f32)((f64)effect->z + ((f64)(nodeZ - effect->z) * 0.1));
}

void func_8071EEA4(TimedEffectActorView *effect, s32 unused) {
    effect->scaleY = (f32) (((f64) effect->param / 100.0) + 1.0);
}


void effectScaleSpinUpdate(TimedEffectActorView *effect, s8 *isDone) {
    TimedMotionState *state;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xC);
        state = (TimedMotionState *)effect->motion;
        state->unk0 = 0.01f;
        state->unk4 = effect->scaleX;
        state->unk8 = 0.0f;
    }
    state = (TimedMotionState *)effect->motion;
    state->unk0 = (f32)(((f64)(state->unk4 - state->unk0) * 0.1) + (f64)state->unk0);
    state->unk8 += 5.0f;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    matrixMakeRotationZ(tmpMtx, state->unk8);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}


void func_8071EFDC(TimedEffectActorView *effect, s8 *isDone) {
    s32 alpha;

    effect->scaleX = (f32)((f64)effect->scaleX * 1.05);
    effect->scaleY = (f32)(((f64)effect->scaleY * 1.05) * 1.0);
    alpha = (effect->alpha = (effect->alpha & 0xFFu) - 5);
    if ((alpha & 0xFF) < 6) {
        *isDone = 1;
    }
}

typedef struct {
    u8 unk0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} PositionSource;

void func_8071F034(TimedEffectActorView *effect, s32 unused) {
    if (effect->timer == 0) {
        effect->x = ((PositionSource *) gPrimaryPlayerActor)->unk7C;
        effect->y = ((PositionSource *) gPrimaryPlayerActor)->unk80;
        effect->z = ((PositionSource *) gPrimaryPlayerActor)->unk84;
    }
}

void effectScatterFallUpdate(TimedEffectActorView *effect, s8 *isDone) {
    TimedMotionState *state;

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(8);
        state = (TimedMotionState *)effect->motion;
        state->unk0 = (f32)(((f64)((randomNonNegative() >> 0xF) % 100) / 10.0) + 2.0);
        state->unk4 = (f32)(-8.0 - ((f64)((randomNonNegative() >> 0xF) % 100) / 70.0));
        effect->param += (s16)((randomNonNegative() >> 0xF) % 800) - 0x190;
        effect->param = effect->param % 4095;
    }
    state = (TimedMotionState *)effect->motion;
    effect->x += state->unk0 * mathSinF(*(s16 *)((u8 *)effect + 0x35E));
    effect->z += state->unk0 * mathCosF(*(s16 *)((u8 *)effect + 0x35E));
    effect->y += state->unk4;
}




void effectCircleRiseFadeUpdate(TimedEffectActorView *effect, s8 *isDone) {
    static s8 sd = 1; // D_8075567C: a function-local static so uopt treats it as non-aliased
    TimedMotionState *state;
    TimedMotionState *temp;

    if (effect->motion == NULL) {
        temp = heapAlloc(0xC);
        effect->motion = temp;
        temp->unk0 = effect->x;
        temp->unk4 = effect->z;
        temp->unk8 = (f32)sd;
        sd = -sd;
    }
    state = (TimedMotionState *)effect->motion;
    effect->x = (mathSinF(*(s16 *)((u8 *)effect + 0x35E)) * 14.0f) + state->unk0;
    effect->z = (mathCosF(*(s16 *)((u8 *)effect + 0x35E)) * 14.0f) + state->unk4;
    effect->y = effect->y + 0.5f;
    if (effect->alpha >= 5) {
        effect->alpha = effect->alpha - 4;
    } else {
        *isDone = 1;
    }
    effect->param = effect->param + (s32)((f64)state->unk8 * 200.0);
}



typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} FallingMotionState;
typedef struct {
    u8 unk0[4];
    f32 *unk4;
} ScaleRoot;

typedef struct {
    u8 unk0[0x38];
    f32 unk38;
} ScaleSource;

typedef struct FallingEffectActorView {
    u8 unk0[0x338];
    ScaleRoot *parent;
    u8 unk33C[4];
    f32 x;
    f32 y;
    f32 z;
    u8 unk34C[2];
    s16 timer;
    u8 unk350;
    u8 unk351[3];
    s32 count;
    s32 previousCount;
    s32 param;
    f32 scaleX;
    f32 scaleY;
    u8 unk368[0x1C];
    FallingMotionState *motion;
} FallingEffectActorView;

void func_8071F2F8(FallingEffectActorView *effect, s32 unused) {
    f32 height;
    FallingMotionState *newState;
    FallingMotionState *state;

    state = effect->motion;
    if (state == NULL) {
        newState = heapAlloc(8);
        effect->motion = newState;
        newState->unk0 = (f32) (effect->param & 0xFFFF);
        newState->unk4 = (f32) ((s32) effect->param >> 0x10);
        state = effect->motion;
    }
    effect->y = effect->y + state->unk0;
    height = state->unk0;
    if (height > -20.0f) {
        state->unk0 = (f32) ((f64) height - ((f64) state->unk4 * 0.01));
    }
}

void func_8071F3C0(FallingEffectActorView *effect, s32 unused) {
    FallingMotionState *newState;
    FallingMotionState *state;

    state = effect->motion;
    if (state == NULL) {
        newState = heapAlloc(4);
        effect->motion = newState;
        newState->unk0 = (f32) ((f64) effect->scaleY * 6.666666666666667);
        state = effect->motion;
    }
    effect->scaleX = ((ScaleSource *) effect->parent->unk4)->unk38 * state->unk0;
    effect->scaleY = effect->scaleX;
}

void effectSwayRiseUpdate(TimedEffectActorView *effect, s8 *isDone) {
    TimedMotionState *state;

    if (effect->motion == NULL) {
        if (gFrameCounter & 1) {
            effect->scaleX = effect->scaleX * -1.0f;
        }
        effect->motion = heapAlloc(8);
        state = (TimedMotionState *)effect->motion;
        state->unk0 = (f32)(((randomNonNegative() >> 0xF) % 20) + 5);
        state->unk4 = 0.0f;
        state->unk8 = (f32)(((randomNonNegative() >> 0xF) % 100) + 0xA);
        state->unkC = 0.0f;
    }
    state = (TimedMotionState *)effect->motion;
    {
        f32 t = mathSinF((s16)state->unk4);
        effect->y = (f32)((f64)effect->y + ((1.0 + (f64)t) * (f64)(f32)(1.0 + ((f64)state->unk0 * 0.4))));
    }
    effect->x += mathSinF((s16)state->unkC) * (f32)((f64)state->unk8 * 0.5);
    if (effect->unk350 == 0) {
        effect->timer = (s16)(s32)(((f64)mathSinF((s16)state->unkC) * 2.5) + 2.5);
    }
    state->unk4 = state->unk4 + 100.0f;
    state->unkC = state->unkC + 50.0f;
    if (effect->y > 960.0f) {
        *isDone = 1;
    }
}


typedef struct SineScaleActorView {
    u8 pad0[0x128];
    Mtx mtx[2];
    u8 pad1A8[0x184];
    u8 mtxState;
    u8 pad32D[0xB];
    u8 pad338[0x1C];
    s32 count;
    s32 previousCount;
    u8 pad35C[4];
    f32 scaleX;
    f32 scaleY;
} SineScaleActorView;


void func_8071F660(SineScaleActorView *effect, void *unused) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 progress;

    progress = (f32) effect->previousCount / (f32) (effect->count - 1);
    effect->scaleX = (f32) ((f64) mathSinF((s16) (s32) (progress * 2048.0f)) * 3.0);
    effect->scaleY = effect->scaleX;
    guScaleF(mtx, effect->scaleX, effect->scaleX, 0.0f);
    matrixMakeRotationZ(tmpMtx, progress * 180.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}

void effectPulseSpinUpdate(TimedEffectActorView *effect, s8 *isDone) {
    TimedMotionState *state;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    if (effect->motion == NULL) {
        effect->motion = heapAlloc(0xC);
        state = (TimedMotionState *)effect->motion;
        state->unk0 = 0.01f;
        state->unk4 = effect->scaleX;
        state->unk8 = 0.0f;
    }
    state = (TimedMotionState *)effect->motion;
    state->unk0 = (f32)(((f64)(state->unk4 - state->unk0) * 0.1) + (f64)state->unk0);
    state->unk8 += 5.0f;
    effect->scaleX = (f32)(((f64)mathSinF((s16)(gFrameCounter * 50)) * 0.1) + (f64)state->unk0);
    effect->scaleY = (f32)(((f64)mathCosF((s16)(gFrameCounter * 25)) * 0.1) + (f64)state->unk0);
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    matrixMakeRotationZ(tmpMtx, state->unk8);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
    effect->mtxState = 2;
}


typedef struct {
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
} LerpPathMotionState;



void effectLerpPathUpdate(TimedEffectActorView *effect, u8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    LerpPathMotionState *state;

    if (effect->motion != NULL) {
        state = effect->motion;
        state->unk20 = state->unk20 + state->unk24;
        if ((f64)state->unk20 >= 1.0) {
            *isDone = 0xFF;
            state->unk20 = 1.0f;
        }
        effect->x = (state->unk14 * state->unk20) + state->unk8;
        effect->y = (state->unk18 * state->unk20) + state->unkC;
        effect->z = (state->unk1C * state->unk20) + state->unk10;
        if (!(gFrameCounter & 3)) {
            effectSetDepth(1);
            effectSetCallback(effectShrinkFadeMatrixUpdate);
            effectCreateAtPosition((s32)&D_8071FB08, 1.6f, effect->x, effect->y, effect->z);
        }
        state->unk4 = state->unk4 + state->unk0;
        guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
        guRotateF(tmpMtx, state->unk4, 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxF2L(mtx, &effect->mtx[gGfxBufferIndex]);
        effect->mtxState = 2;
    }
}

