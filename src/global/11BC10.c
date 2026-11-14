#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
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
extern s32 gCurrentMap;
extern Actor *gPrimaryPlayerActor;


void effectZRotationMatrixUpdate(EffectNode *effect, void *unused) {
    f32 scaleMtx[4][4];
    f32 rotMtx[4][4];

    guScaleF(scaleMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, (f32)effect->speed, 0.0f, 0.0f, 1.0f);
    guMtxCatF(scaleMtx, rotMtx, scaleMtx);
    guMtxF2L(scaleMtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

typedef struct {
    f32 angle;
    f32 angleStep;
} RotationState;

typedef struct {
    f32 speed;
    f32 heading;
} DriftHeadingState;

void effectZSpinMatrixUpdate(EffectNode *effect, void *unused) {
    f32 scaleMtx[4][4];
    f32 rotMtx[4][4];
    RotationState *state;

    state = effect->allocation;
    if (state == NULL) {
        effect->allocation = heapAlloc(8);
        ((RotationState *)effect->allocation)->angle = (randomLcgNext() % 36000U) / 100U;
        ((RotationState *)effect->allocation)->angleStep = (randomLcgNext() % 400U) / 100U;
        state = effect->allocation;
    }
    state->angle += state->angleStep;
    guScaleF(scaleMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, ((RotationState *)effect->allocation)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(scaleMtx, rotMtx, scaleMtx);
    guMtxF2L(scaleMtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

typedef struct {
    s16 angle;
    s16 radius;
    s16 angleStep;
    s16 centerX;
    s16 centerZ;
} OrbitMotionState10;

void effectOrbitXZUpdate(EffectNode *effect, void *unused) {
    OrbitMotionState10 *state;

    if (!effect->allocation) {
        effect->allocation = heapAlloc(0xA);
        state = effect->allocation;
        state->angle = (s16) ((randomNonNegative() >> 15) % 0xFFF);
        state->radius = effect->speed & 0xFFFF;
        state->angleStep = (effect->speed >> 16) & 0xFFFF;
        state->centerX = effect->x;
        state->centerZ = effect->z;
    }
    state = effect->allocation;
    state->angle = state->angleStep + state->angle;
    effect->x = mathSinF(state->angle) * state->radius + state->centerX;
    effect->z = mathCosF(state->angle) * state->radius + state->centerZ;
}


typedef struct {
    s16 angle;
    s16 radiusStep;
    s16 radius;
    s16 fallVelocity;
} PuffRiseMotionState;


void effectPuffRiseUpdate(EffectNode *effect, void *unused) {
    PuffRiseMotionState *state;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(8);
        state = effect->allocation;
        state->angle = (randomNonNegative() >> 15) % 0xFFF;
        state->radiusStep = ((randomNonNegative() >> 15) % 10) + 2;
        state->radius = 0;
        state->fallVelocity = -50 - (((randomNonNegative() >> 15) % 10000) % 600);
    }
    state = effect->allocation;
    effect->y -= state->fallVelocity / 100.0;
    state->fallVelocity += 0x14;
    effect->x += 0.04 * state->radius * mathSinF(state->angle);
    effect->z += 0.04 * state->radius * mathCosF(state->angle);
    state->angle += 0x50;
    state->radius += state->radiusStep;
    if (effect->speed != 0) {
        lightSetFlags(1);
        lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 40.0f, 0, 0xFF,
                 0xFF, (randomNonNegative() >> 15) % 0xFF);
    }
}


typedef struct {
    f32 angle;
    f32 radiusStep;
    f32 velocityY;
} ConfettiMotionState;

void effectConfettiPhysicsUpdate(EffectNode *effect, void *unused) {
    ConfettiMotionState *motion;
    EffectParamPair *params = &effect->pair;
    f64 scale;
    s32 rem;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xC);
        motion = effect->allocation;
        if (params->hi != 0) {
            motion->angle = (f32) (((randomNonNegative() >> 15) % 200) + params->hi - 100);
        } else {
            motion->angle = (f32) ((randomNonNegative() >> 15) % 0xFFF);
        }
        scale = (effect->mode != 0) ? 4.0 : 1.0;
        motion->radiusStep = (f32) ((((randomNonNegative() >> 15) % 10) + 5) * scale);
        rem = (randomNonNegative() >> 15) % 6;
        motion->velocityY = (f32) (params->lo + rem);
    }
    motion = effect->allocation;
    params = &effect->pair;
    if (effect->mode != 0) {
        effect->x += 4.0 * ((0.01 * (f64) params->lo) * (f64) mathSinF((s16) motion->angle));
        effect->y += 4.0 * ((0.01 * (f64) params->lo) * (f64) mathCosF((s16) motion->angle));
    } else {
        effect->x += (0.04 * (f64) params->lo) * (f64) mathSinF((s16) motion->angle);
        effect->z += (0.04 * (f64) params->lo) * (f64) mathCosF((s16) motion->angle);
        if (params->hi == 0) {
            effect->y += motion->velocityY;
            motion->velocityY = (f32) ((f64) motion->velocityY - 0.5);
        } else {
            effect->y += (f64) motion->velocityY * 0.2;
        }
    }
    params->lo = (s16) (params->lo + motion->radiusStep);
}


extern void *D_8074E880[];

void effectTimerCountdownAlphaUpdate(EffectNode *effect, u8 *isDone) {
    s32 timer;

    timer = effect->speed;
    effect->alpha = 0;
    if (timer != 0) {
        effect->speed = timer - 1;
        effectSetDepth(1);
        effectSetCallback(effectConfettiPhysicsUpdate);
        effectSetSpeed(0xA);
        effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 0.8f, effect->x, effect->y, effect->z);
        return;
    }
    *isDone = 1;
}

typedef struct {
    s16 angle;
    s16 speedStep;
} RandomDriftState;

void effectRandomDriftVelocityUpdate(EffectNode *effect, void *unused) {
    RandomDriftState *motion;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(4);
        motion = effect->allocation;
        motion->angle = (randomNonNegative() >> 15) % 4095;
        motion->speedStep = ((randomNonNegative() >> 15) % 10) + 2;
    }
    motion = effect->allocation;
    effect->x += 0.2 * effect->speed * mathSinF(motion->angle);
    effect->y += 0.2 * effect->speed * mathCosF(motion->angle);
    motion->angle += 0x46;
    effect->speed += motion->speedStep;
}

typedef struct {
    s16 angle;
    s16 centerX;
    s16 centerZ;
    s16 angleStep;
    s16 riseSpeed;
} OrbitMotionState;

void func_80717930(EffectNode *effect, void *unused) {
    f32 scaleFactor;
    s32 flags;
    OrbitMotionState *state;
    OrbitMotionState *allocatedState;
    Actor *owner;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xA);
        allocatedState = effect->allocation;
        allocatedState->angle = (randomNonNegative() >> 0xF) % 4095;
        allocatedState->centerX = effect->x;
        allocatedState->centerZ = effect->z;
        flags = effect->speed;
        if (flags & 0x8000) {
            effect->speed = flags & 0xFFFF7FFF;
            allocatedState->angleStep = 0xC8;
            allocatedState->riseSpeed = 0xA;
        } else {
            allocatedState->angleStep = 0x46;
            allocatedState->riseSpeed = 0xF;
        }
        owner = effect->owner;
        if (owner != NULL) {
            scaleFactor = owner->sub4->scaleY / 0.15;
            allocatedState->riseSpeed = allocatedState->riseSpeed * scaleFactor;
            effect->speed = effect->speed * scaleFactor;
        }
    }
    state = effect->allocation;
    if (effect->flags & 2) {
        effect->x = mathSinF(state->angle) * effect->speed + gPrimaryPlayerActor->x;
        effect->z = mathCosF(state->angle) * effect->speed + gPrimaryPlayerActor->z;
    } else {
        effect->x = mathSinF(state->angle) * effect->speed + state->centerX;
        effect->z = mathCosF(state->angle) * effect->speed + state->centerZ;
    }
    effect->y += state->riseSpeed * 0.1;
    state->angle += state->angleStep;
}


extern u8 sEffectImpactPuffConfig;

typedef struct {
    s16 step;
    s16 stepCount;
    s16 baseAlpha;
} PlayerDistanceFadeState;

extern PlayerStruct *gPlayerSlots;

void effectPlayerDistanceFadeUpdate(effect, isDone)
EffectNode *effect;
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

    scale = (f32) ((s32) (effect->maxDistance * 3) / 4);
    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(6);
        state = effect->allocation;
        state->step = 0;
        state->stepCount = effect->grid->frameCount * effect->frameDelay;
        state->baseAlpha = effect->alpha;
    }
    state = effect->allocation;
    curStep = state->step;
    if (curStep == state->stepCount) {
        *isDone = 1;
    } else {
        state->step = curStep + 1;
    }
    dz = gPlayerSlots->camZ - effect->z;
    dx = gPlayerSlots->camX - effect->x;
    dy = gPlayerSlots->camY - effect->y;
    dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
    if (dist < scale) {
        effect->alpha = state->baseAlpha;
        return;
    }
    value = (s32) ((f32) state->baseAlpha * ((dist - scale) / ((f32) effect->maxDistance - scale)));
    if (state->baseAlpha < value) {
        value = (s32) state->baseAlpha;
    }
    effect->alpha = state->baseAlpha - value;
}

void func_80717CE8(effect, isDone)
EffectNode *effect;
s8 *isDone;
{
    if (effect->alpha != 0xFF) {
        effect->alpha += 0x14;
    }
    if ((s32) effect->alpha >= 0xEB) {
        effect->alpha = 0xFFU;
    }
    effect->y = (f32) ((f64) effect->y - ((f64) effect->speed / 100.0));
}

void func_80717D4C(effect, isDone)
EffectNode *effect;
s8 *isDone;
{
    effect->y = (f32) ((f64) effect->y - ((f64) effect->speed / 100.0));
}

void effectLinearFadeAlphaUpdate(EffectNode *effect, s8 *isDone) {
    s32 alphaStep;
    u8 curAlpha;

    alphaStep = effect->speed;
    curAlpha = effect->alpha;
    if (alphaStep < (s32) curAlpha) {
        effect->alpha = (u8) (curAlpha - alphaStep);
        return;
    }
    effect->alpha = 0U;
    *isDone = 1;
}

typedef struct {
    f32 centerX;
    f32 centerZ;
    s16 phaseX;
    s16 phaseZ;
    s16 phaseStepX;
    s16 phaseStepZ;
} DriftMotionState;

void effectDriftXZUpdate(EffectNode *effect, void *unused) {
    DriftMotionState *state;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0x10);
        state = effect->allocation;
        state->centerX = effect->x;
        state->centerZ = effect->z;
        state->phaseX = 0;
        state->phaseZ = 0;
        state->phaseStepX = (randomNonNegative() % 10000) % 150 - 75;
        state->phaseStepZ = (randomNonNegative() % 10000) % 150 - 75;
    }
    state = effect->allocation;
    effect->x = (f32) ((f64) mathSinF(state->phaseX) * 6.0 + (f64) state->centerX);
    effect->z = (f32) ((f64) mathSinF(state->phaseZ) * 6.0 + (f64) state->centerZ);
    state->phaseX += state->phaseStepX;
    state->phaseZ += state->phaseStepZ;
    effect->y = (f32) ((f64) effect->y - (f64) effect->speed / 100.0);
}

typedef struct {
    f32 velocityX;
    f32 velocityZ;
    f32 baseScale;
    f32 scaleFactor;
} VelocityMotionState;

void effectShrinkOffsetUpdate(effect, isDone)
EffectNode *effect;
s8 *isDone;
{
    VelocityMotionState *state;
    Actor *parent;

    if (effect->allocation == NULL) {
        parent = effect->owner;
        effect->allocation = heapAlloc(0x10);
        state = effect->allocation;
        if (parent != NULL) {
            state->velocityX = (parent->speedXZ * 0.025f) * mathSinF(parent->moveYaw);
            state->velocityZ = (parent->speedXZ * 0.025f) * mathCosF(parent->moveYaw);
        } else {
            state->velocityX = 0.0f;
            state->velocityZ = 0.0f;
        }
        state->baseScale = effect->scaleX;
        state->scaleFactor = 0.2f;
    }
    state = effect->allocation;
    effect->y = (f32) ((f64) effect->y - (f64) effect->speed / 100.0);
    effect->x += state->velocityX;
    effect->z += state->velocityZ;
    state->velocityX = (f32) ((f64) state->velocityX * 0.93);
    state->velocityZ = (f32) ((f64) state->velocityZ * 0.93);
}


void effectShrinkAndVelocityUpdate(EffectNode *effect, s8 *isDone) {
    f32 scaleFactor;
    VelocityMotionState *state;

    effectShrinkOffsetUpdate(effect, isDone);
    state = effect->allocation;
    effect->scaleX = state->scaleFactor * state->baseScale;
    effect->scaleY = effect->scaleX;
    scaleFactor = state->scaleFactor;
    if (scaleFactor < 2.0f) {
        state->scaleFactor = scaleFactor + 0.2;
    }
}

void func_807180F4(EffectNode *effect, void *unused) {
    func_80717D4C(effect, unused);
    effectZSpinMatrixUpdate(effect, unused);
}

void effectSpawnImpactPuff(f32 scale, f32 x, f32 y, f32 z) {
    effectSetDepth(1);
    effectSetMode(3);
    effectSetCallback(&effectRandomYRotDecalUpdate);
    effectCreateAtPosition(&sEffectImpactPuffConfig, scale, x, y, z);
}

extern s16 D_807502D0;

void effectFallUpdate(EffectNode *effect, s8 *isDone) {
    s16 *newVel;
    s16 *velocity;

    velocity = effect->allocation;
    if (velocity == NULL) {
        newVel = heapAlloc(2);
        effect->allocation = newVel;
        *newVel = 0;
        velocity = effect->allocation;
    }
    effect->y += (f32) *velocity;
    *velocity -= 1;
    velocity = effect->allocation;
    if (*velocity < D_807502D0) {
        *velocity = D_807502D0;
    }
    if (effect->y < (f32) effect->speed) {
        *isDone = 1;
        effectSpawnImpactPuff((f32) ((f64) effect->scaleX * 1.5), effect->x, effect->speed, effect->z);
    }
}

typedef f32 EffectMatrix[4][4];

void effectFadeOutMatrixUpdate(EffectNode *effect, s8 *isDone) {
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
    guMtxF2L(modelMtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 3;
}

void effectRandomYRotDecalUpdate(EffectNode *effect, s8 *isDone) {
    EffectMatrix modelMtx;
    EffectMatrix tempMtx;
    u32 rotAngle;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(4);
        rotAngle = (u32) (randomLcgNext() % 36000U) / 100U;
        *(f32 *) effect->allocation = (f32) rotAngle;
    }
    guScaleF(modelMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tempMtx, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guRotateF(tempMtx, *(f32 *) effect->allocation, 0.0f, 1.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guTranslateF(tempMtx, effect->x, effect->y, effect->z);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    if ((s32) effect->alpha >= 0xA) {
        effect->alpha -= 0xA;
    } else {
        effect->alpha = 0U;
    }
    guMtxF2L(modelMtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 3;
    if (effect->alpha == 0) {
        *isDone = 1;
    }
}

typedef struct {
    f32 angle;
    f32 angleStep;
} GroundSpinState;

void effectGroundDecalSpinUpdate(EffectNode *effect, s8 *isDone) {
    EffectMatrix modelMtx;
    EffectMatrix tempMtx;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(8);
        ((GroundSpinState *) effect->allocation)->angle = 0.0f;
        ((GroundSpinState *) effect->allocation)->angleStep = (f32) ((randomLcgNext() % 400U) / 100U);
    }
    guScaleF(modelMtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tempMtx, ((GroundSpinState *) effect->allocation)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guRotateF(tempMtx, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    if (effect->owner != NULL) {
        effect->y = effect->owner->waterY;
    }
    guTranslateF(tempMtx, effect->x, effect->y, effect->z);
    guMtxCatF(modelMtx, tempMtx, modelMtx);
    guMtxF2L(modelMtx, &effect->matrices[0][gGfxBufferIndex]);
    if (effect->speed != 0) {
        ((GroundSpinState *) effect->allocation)->angle += ((GroundSpinState *) effect->allocation)->angleStep;
        effect->scaleX = (f32) ((f64) effect->scaleX - 0.02);
        effect->scaleY = (f32) ((f64) effect->scaleY - 0.02);
        if (effect->alpha >= 0xA) {
            effect->alpha -= 0xA;
        } else {
            effect->alpha = 0;
        }
    }
    effect->state = 3;
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

void effectInterpolationUpdate(EffectNode *effect, s8 *isDone) {
    EffectMatrix mtx;
    EffectMatrix rotMtx;
    f32 start[3];
    f32 end[3];
    f32 result[3];
    s32 i;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0x28);
        ((EffectInterpolationState *)effect->allocation)->progress = 0.0f;
        ((EffectInterpolationState *)effect->allocation)->startX = D_807FDB50;
        ((EffectInterpolationState *)effect->allocation)->startY = D_807FDB54;
        ((EffectInterpolationState *)effect->allocation)->startZ = D_807FDB58;
        ((EffectInterpolationState *)effect->allocation)->endX = effect->x;
        ((EffectInterpolationState *)effect->allocation)->endY = effect->y;
        ((EffectInterpolationState *)effect->allocation)->endZ = effect->z;
        ((EffectInterpolationState *)effect->allocation)->increment = 0.01f;
        ((EffectInterpolationState *)effect->allocation)->angle = (f32)((u32)(randomLcgNext() % 36000U) / 100U);
        ((EffectInterpolationState *)effect->allocation)->angleIncrement = (f32)((u32)(randomLcgNext() % 400U) / 100U);
    }
    start[0] = ((EffectInterpolationState *)effect->allocation)->startX;
    start[1] = ((EffectInterpolationState *)effect->allocation)->startY;
    start[2] = ((EffectInterpolationState *)effect->allocation)->startZ;
    end[0] = ((EffectInterpolationState *)effect->allocation)->endX;
    end[1] = ((EffectInterpolationState *)effect->allocation)->endY;
    end[2] = ((EffectInterpolationState *)effect->allocation)->endZ;
    for (i = 0; i < 3; i++) {
        result[i] = end[i] + (start[i] - end[i]) * *(f32 *)effect->allocation; // FAKE: reading progress through *(f32 *) (or (*p).progress) keeps mul.s $f14,$f12 operand order; ->progress swaps it
    }
    effect->x = result[0];
    effect->y = result[1];
    effect->z = result[2];
    ((EffectInterpolationState *)effect->allocation)->progress += ((EffectInterpolationState *)effect->allocation)->increment;
    ((EffectInterpolationState *)effect->allocation)->increment = (f32)((f64)((EffectInterpolationState *)effect->allocation)->increment + 0.001);
    effect->scaleX = (f32)((f64)effect->scaleX * 0.975);
    effect->scaleY = (f32)((f64)effect->scaleY * 0.975);
    ((EffectInterpolationState *)effect->allocation)->angle = ((EffectInterpolationState *)effect->allocation)->angle + ((EffectInterpolationState *)effect->allocation)->angleIncrement;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, ((EffectInterpolationState *)effect->allocation)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}


typedef struct {
    s16 speed;
    s16 yaw;
    s16 riseSpeed;
    s16 floorY;
} ProjectileMotionState;

void effectProjectileDriftUpdate(EffectNode *effect, s8 *isDone) {
    ProjectileMotionState *proj;
    Actor *src;
    f64 min;
    f64 temp;

    src = effect->target;
    if (effect->allocation == NULL) {
        proj = heapAlloc(8); effect->allocation = proj;
        temp = (f64)src->speedXZ * 0.01;
        min = 2.0;
        if (temp < min) {
            proj->speed = min;
        } else {
            proj->speed = temp;
        }
        proj->yaw = src->yaw;
        proj->riseSpeed = (s16)(((s32)(randomNonNegative() >> 0xF) % 1000) + 0xC8);
        effect->scaleX += ((f64)((s32)(randomNonNegative() >> 0xF) % 100) / 500.0);
        effect->scaleY = effect->scaleX;
        proj->floorY = (s16)src->waterY;
    }
    proj = effect->allocation;
    effect->x -= (f32)proj->speed * mathSinF(proj->yaw);
    effect->z -= (f32)proj->speed * mathCosF(proj->yaw);
    effect->y = (f32)((f64)effect->y + ((f64)proj->riseSpeed / 500.0));
    if ((f32)proj->floorY <= effect->y) {
        *isDone = 1;
        effectSpawnImpactPuff((f32)((f64)effect->scaleX * 1.5), effect->x, (f32)proj->floorY, effect->z);
    }
    if ((s32)effect->alpha >= 0xC) {
        effect->alpha -= 0xA;
        return;
    }
    *isDone = 1;
    effect->alpha = 0U;
}


typedef struct {
    s32 frame;
    f32 riseSpeed;
    f32 centerX;
    f32 centerZ;
    f32 swayRateX;
    f32 swayRateZ;
    f32 floorY;
    f32 spawnFrame;
} WobbleRiseState;


void effectWobbleRiseUpdate(EffectNode *effect, s8 *isDone) {
    f64 pad;
    f32 swayX;
    f32 swayZ;
    f32 riseSpeed;
    f32 floorY;
    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0x20);
        ((WobbleRiseState *)effect->allocation)->frame = 0;
        ((WobbleRiseState *)effect->allocation)->riseSpeed = 0.0f;
        ((WobbleRiseState *)effect->allocation)->centerX = effect->x;
        ((WobbleRiseState *)effect->allocation)->centerZ = effect->z;
        ((WobbleRiseState *)effect->allocation)->swayRateX = ((f64)(randomLcgNext() % 10000U) / 10000.0) * 0.19;
        ((WobbleRiseState *)effect->allocation)->swayRateZ = ((f64)(randomLcgNext() % 10000U) / 10000.0) * 0.077;
        if ((randomLcgNext() / 10000U) & 1) {
            ((WobbleRiseState *)effect->allocation)->swayRateX = (f32)(0.0 - (f64)((WobbleRiseState *)effect->allocation)->swayRateX);
            ((WobbleRiseState *)effect->allocation)->swayRateZ = (f32)(0.0 - (f64)((WobbleRiseState *)effect->allocation)->swayRateZ);
        }
        floorY = effect->y;
        collisionCheckGroundAtPoint(effect->x, effect->z, &floorY);
        if (collisionGetFloorHeight(&((WobbleRiseState *)effect->allocation)->floorY) == 0) {
            ((WobbleRiseState *)effect->allocation)->floorY = 0.0f;
        }
        ((WobbleRiseState *)effect->allocation)->spawnFrame = (f32)gFrameCounter;
    }
    swayX = sinApprox(((WobbleRiseState *)effect->allocation)->swayRateX * (f32)((WobbleRiseState *)effect->allocation)->frame);
    swayZ = sinApprox(((WobbleRiseState *)effect->allocation)->swayRateZ * (f32)((WobbleRiseState *)effect->allocation)->frame) * 6.0f;
    effect->x = ((WobbleRiseState *)effect->allocation)->centerX + (swayX * 6.0f);
    effect->z = ((WobbleRiseState *)effect->allocation)->centerZ + swayZ;
    ((WobbleRiseState *)effect->allocation)->frame += 1;
    ((WobbleRiseState *)effect->allocation)->riseSpeed = (f32)((f64)((WobbleRiseState *)effect->allocation)->riseSpeed + 0.02);
    riseSpeed = ((WobbleRiseState *)effect->allocation)->riseSpeed;
    if ((f64)riseSpeed > 1.0) {
        ((WobbleRiseState *)effect->allocation)->riseSpeed = 1.0f;
    }
    riseSpeed = ((WobbleRiseState *)effect->allocation)->riseSpeed;
    effect->y += riseSpeed;
    switch (effect->speed) {
    case 0:
        effect->scaleX = (f32)(((f64)((WobbleRiseState *)effect->allocation)->frame * 0.01) + 0.01);
        if ((f64)effect->scaleX > 0.12) effect->scaleX = 0.12f;
        break;
    case 1:
        effect->scaleX = (f32)(((f64)((WobbleRiseState *)effect->allocation)->frame * 0.005) + 0.05);
        if ((f64)effect->scaleX > 0.07) effect->scaleX = 0.07f;
        break;
    case 2:
        effect->scaleX = (f32)(((f64)((WobbleRiseState *)effect->allocation)->frame * 0.02) + 0.02);
        if ((f64)effect->scaleX > 0.24) effect->scaleX = 0.24f;
        break;
    }
    effect->scaleY = effect->scaleX;
    swayX = sinApprox((f32)((f64)((WobbleRiseState *)effect->allocation)->frame * 0.17));
    swayZ = sinApprox((f32)((f64)((WobbleRiseState *)effect->allocation)->frame * 0.2267));
    effect->scaleX = (f32)((f64)effect->scaleX + ((f64)swayX * 0.03));
    effect->scaleY = (f32)((f64)effect->scaleY + ((f64)swayZ * 0.03));
    if ((((WobbleRiseState *)effect->allocation)->spawnFrame + 100.0f) < (f32)gFrameCounter) *isDone = 1;
    if (((WobbleRiseState *)effect->allocation)->floorY <= effect->y) {
        *isDone = 1;
        effectSpawnImpactPuff(0.3f, effect->x, effect->y, effect->z);
    }
}


typedef struct {
    f32 velocityY;
    f32 velocityX;
    f32 velocityZ;
    f32 rotation;
    f32 groundY;
    s32 bounceCount;
} TumbleBounceState;

extern EffectGridAsset D_8072073C;
extern EffectGridAsset D_807212B0;
extern EffectGridAsset D_807212C8;


void effectTumbleBounceUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 speed;
    f32 yawDeg;
    f32 velX;
    f32 cosYaw;
    f32 groundY;
    s16 sfxId;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0x1C);
        ((TumbleBounceState *) effect->allocation)->velocityY = (f32) (((f64) (f32) (u32) ((randomLcgNext() / 10000U) % 100U) / 25.0) + 5.0 + (((s32) effect->speed >> 8) * 3.0));
        speed = ((f32) (u32) ((randomLcgNext() / 10000U) % 1000U) / 500.0f) + (f32) (effect->speed & 0xFF);
        yawDeg = (f32) (u32) ((randomLcgNext() / 10000U) % 360U);
        velX = sinApprox(yawDeg * 0.017453292f) * speed;
        cosYaw = cosApprox(yawDeg * 0.017453292f);
        ((TumbleBounceState *) effect->allocation)->velocityX = velX;
        ((TumbleBounceState *) effect->allocation)->velocityZ = cosYaw * speed;
        ((TumbleBounceState *) effect->allocation)->rotation = (f32) (u32) ((randomLcgNext() % 36000U) / 100U);
        groundY = effect->y;
        if (collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) != 0) {
            ((TumbleBounceState *) effect->allocation)->groundY = groundY;
        } else {
            ((TumbleBounceState *) effect->allocation)->groundY = 0.0f;
        }
        ((TumbleBounceState *) effect->allocation)->bounceCount = 0;
    }
    ((TumbleBounceState *) effect->allocation)->velocityY = (f32) ((f64) ((TumbleBounceState *) effect->allocation)->velocityY + -0.63);
    effect->x += ((TumbleBounceState *) effect->allocation)->velocityX;
    effect->z += ((TumbleBounceState *) effect->allocation)->velocityZ;
    effect->y += ((TumbleBounceState *) effect->allocation)->velocityY;
    if (effect->y < ((TumbleBounceState *) effect->allocation)->groundY) {
        sfxId = 0x56;
        if (effect->grid->asset == &D_8072073C) {
            sfxId = 0x1B1;
        } else if (effect->grid->asset == &D_807212C8 || effect->grid->asset == &D_807212B0) {
            sfxId = 7;
        }
        sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, sfxId,
            (u32) ((f64) (u32) effect->alpha * 0.7), 0x96, 1, 0x4B, 0.3f, 0);
        ((TumbleBounceState *) effect->allocation)->velocityY = 5.0f;
        if (((TumbleBounceState *) effect->allocation)->bounceCount != 2) {
            ((TumbleBounceState *) effect->allocation)->bounceCount++;
        }
    }
    if (((TumbleBounceState *) effect->allocation)->bounceCount == 2) {
        if (effect->alpha >= 0xB) {
            effect->alpha -= 0xA;
        } else {
            effect->alpha = 0;
        }
    }
    ((TumbleBounceState *) effect->allocation)->rotation = (f32) ((f64) ((TumbleBounceState *) effect->allocation)->rotation + 5.9);
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, ((TumbleBounceState *) effect->allocation)->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}


typedef struct {
    f32 angle;
    f32 rotation;
} SpiralDriftState;

void effectSpiralDriftMatrixUpdate(EffectNode *effect, s8 *isDone) {
    SpiralDriftState *newState;
    f32 offsetX;
    f32 offsetZ;
    EffectMatrix mtx;
    EffectMatrix rotMtx;

    if (effect->allocation == NULL) {
        newState = heapAlloc(8);
        effect->allocation = newState;
        offsetZ = effect->speed * 2;
        newState->angle = (f32) offsetZ;
        ((SpiralDriftState *) effect->allocation)->rotation = 0.0f;
        effect->alpha = 0U;
    }
    if ((s32) effect->alpha >= 0xDD) {
        effect->alpha = 0xFFU;
    } else {
        effect->alpha += 0x14;
    }
    offsetX = (f32) ((f64) sinApprox(((SpiralDriftState *) effect->allocation)->angle * 0.017453292f) * 2.5);
    offsetZ = cosApprox(((SpiralDriftState *) effect->allocation)->angle * 0.017453292f);
    effect->x = (f32) (effect->x + offsetX);
    effect->y = (f32) ((f64) effect->y + 3.5);
    effect->z = (f32) (effect->z + (f32) ((f64) offsetZ * 2.5));
    ((SpiralDriftState *) effect->allocation)->angle = (f32) ((f64) ((SpiralDriftState *) effect->allocation)->angle + 8.0);
    ((SpiralDriftState *) effect->allocation)->rotation = (f32) ((f64) ((SpiralDriftState *) effect->allocation)->rotation + 7.3);
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(rotMtx, ((SpiralDriftState *) effect->allocation)->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

typedef struct {
    s32 frame;
    f32 baseScaleX;
    f32 baseScaleY;
} WobbleScaleState;

void effectWobbleScaleUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtxs[2][4][4];
    f32 wobbleX;
    f32 wave;
    f32 driftX;
    s32 pad;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xC);
        ((WobbleScaleState *) effect->allocation)->frame = 0;
        ((WobbleScaleState *) effect->allocation)->baseScaleX = effect->scaleX;
        ((WobbleScaleState *) effect->allocation)->baseScaleY = effect->scaleY;
    }
    ((WobbleScaleState *) effect->allocation)->baseScaleX = (f32) ((f64) ((WobbleScaleState *) effect->allocation)->baseScaleX + 0.0015);
    ((WobbleScaleState *) effect->allocation)->baseScaleY = (f32) ((f64) ((WobbleScaleState *) effect->allocation)->baseScaleY + 0.0015);
    driftX = (f32) ((f64) sinApprox((f32) (effect->speed * 2)) * 0.2);
    wave = cosApprox((f32) (effect->speed * 2));
    effect->x -= driftX;
    effect->y = (f32) ((f64) effect->y + 0.12);
    effect->z -= (f32) ((f64) wave * 0.2);
    effect->scaleX = ((WobbleScaleState *) effect->allocation)->baseScaleX;
    effect->scaleY = ((WobbleScaleState *) effect->allocation)->baseScaleY;
    wobbleX = sinApprox((f32) ((f64) ((WobbleScaleState *) effect->allocation)->frame * 0.17));
    wave = sinApprox((f32) ((f64) ((WobbleScaleState *) effect->allocation)->frame * 0.2267));
    effect->scaleX = (f32) ((f64) effect->scaleX * (1.0 + ((f64) wobbleX * 0.15)));
    effect->scaleY = (f32) ((f64) effect->scaleY * (1.0 + ((f64) wave * 0.15)));
    ((WobbleScaleState *) effect->allocation)->frame++;
    if ((effect->duration - effect->durationTimer) < 10) {
        if (effect->alpha >= 0x16) {
            effect->alpha -= 0x14;
        } else {
            effect->alpha = 0;
        }
    }
    guScaleF(mtxs[1], effect->scaleX, effect->scaleY, 0.0f);
    guMtxF2L(mtxs[1], &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

void effectDecelerateDriftUpdate(EffectNode *effect, s8 *isDone) {
    f32 stepX;
    f32 stepZ;
    DriftHeadingState *newState;
    DriftHeadingState *state;

    state = effect->allocation;
    if (state == NULL) {
        newState = heapAlloc(8);
        effect->allocation = newState;
        newState->speed = ((f64) effect->scaleX / 0.36) * 2.5;
        newState->heading = (f32) (u32) ((gFrameCounter * 40) + (effect->speed << 9));
        state = effect->allocation;
    }
    state->speed = (f32) ((f64) state->speed - 0.2);
    newState = state;
    if ((f64) state->speed < 0.8) {
        state->speed = 0.8f;
    }
    state = newState;
    stepX = mathSinF((s16) (s32) state->heading);
    stepX = state->speed * stepX;
    stepZ = mathCosF((s16) (s32) state->heading);
    stepZ = state->speed * stepZ;
    effect->x += stepX;
    effect->z += stepZ;
}


void timedEffectCountdownTick(EffectNode *effect, s8 *isDone) {
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
    f32 centerX;
    f32 centerZ;
    f32 radius;
    f32 angle;
    f32 angleStep;
    f32 alphaLevel;
} SpiralRiseState;

void effectSpiralRiseUpdate(EffectNode *effect, s8 *isDone) {
    SpiralRiseState *newState;
    f32 alpha;
    SpiralRiseState *state;
    f32 clampedAlpha;

    state = effect->allocation;
    if (state == NULL) {
        newState = heapAlloc(0x18);
        effect->allocation = newState;
        newState->centerX = effect->x;
        newState->centerZ = effect->z;
        newState->radius = 0.0f;
        newState->angle = (f32)effect->speed * 455.1111f;
        newState->angleStep = ((effect->speed % 3) * 0x64) - 0x64;
        newState->alphaLevel = 375.0f;
        state = effect->allocation;
    }
    newState = effect->allocation;
    effect->y = (f32)((f64)effect->y + 0.3);
    alpha = newState->alphaLevel;
    if (alpha < 15.0f) {
        clampedAlpha = alpha;
    } else {
        clampedAlpha = 15.0f;
    }
    newState->alphaLevel = alpha - clampedAlpha; clampedAlpha = 255.0f; alpha = newState->alphaLevel; if (alpha > clampedAlpha) { effect->alpha = (u8) ((u32) clampedAlpha); } else { effect->alpha = (u8) ((u32) alpha); } // LAYOUT: one source line keeps the as1 schedule
    state = newState;
    newState->radius = (f32)((f64)newState->radius + 1.5);
    state->angle += state->angleStep;
    effect->x = (mathSinF((s16)(s32)state->angle) * newState->radius) + newState->centerX;
    effect->z = (mathCosF((s16)(s32)state->angle) * state->radius) + newState->centerZ;
    if (effect->alpha == 0) {
        *isDone = 1;
    }
}

void effectSpriteMotionUpdate(EffectNode *effect, s8 *isDone) {
    f32 stepX;
    f32 stepZ;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(8);
        ((DriftHeadingState *)effect->allocation)->speed = 3.2f;
        ((DriftHeadingState *)effect->allocation)->heading = (f32)effect->speed;
    }
    ((DriftHeadingState *)effect->allocation)->speed = (f32)((f64)((DriftHeadingState *)effect->allocation)->speed - 0.2);
    if ((f64)((DriftHeadingState *)effect->allocation)->speed < 0.8) {
        ((DriftHeadingState *)effect->allocation)->speed = 0.8f;
    }
    stepX = sinApprox(((DriftHeadingState *)effect->allocation)->heading * 0.017453292f);
    stepX = stepX * ((DriftHeadingState *)effect->allocation)->speed;
    stepZ = cosApprox(((DriftHeadingState *)effect->allocation)->heading * 0.017453292f);
    stepZ = stepZ * ((DriftHeadingState *)effect->allocation)->speed;
    effect->x = effect->x + stepX;
    effect->z = effect->z + stepZ;
    effect->y = effect->y + 1.0f;
}

void effectSpriteMatrixUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 offset;
    f32 pad;
    f32 phase;
    u8 *counter;
    f32 bob;

    phase = effect->param * 2 + effect->frameTimer;
    counter = effect->data;
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
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 3;
}


typedef struct {
    f32 velocityX;
    f32 velocityY;
    f32 velocityZ;
} ParticleArcMotionState;

void effectParticleArcUpdate(EffectNode *effect, s8 *isDone) {
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

    if (effect->allocation == NULL) {
        yaw = (u32)-(s32)(randomLcgNext() / 10000U) % 30U;
        tilt = (u32)(randomLcgNext() / 10000U) % 180U;
        guRotateF(mtx, (f32)yaw, 0.0f, 1.0f, 0.0f);
        dirX = effect->speed >> 0x10;
        dirY = (effect->speed >> 8) & 0xFF;
        dirZ = effect->speed & 0xFF;
        ptr = heapAlloc(0xC);
        effect->allocation = ptr;
        guAlignF(tmpMtx, (f32)tilt, (f32)dirX, (f32)dirY, (f32)dirZ);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, -2.0f, &velX, &velY, &velZ);
        ((ParticleArcMotionState *)effect->allocation)->velocityX = (f32)((f64)velX * 0.5);
        if (velY < 0.0f) {
            ((ParticleArcMotionState *)effect->allocation)->velocityY = (f32)((f64)-velY * 0.5);
        } else {
            ((ParticleArcMotionState *)effect->allocation)->velocityY = (f32)((f64)velY * 0.5);
        }
        ((ParticleArcMotionState *)effect->allocation)->velocityZ = (f32)((f64)velZ * 0.5);
    }
    effect->x += ((ParticleArcMotionState *)effect->allocation)->velocityX;
    effect->y += ((ParticleArcMotionState *)effect->allocation)->velocityY;
    effect->z += ((ParticleArcMotionState *)effect->allocation)->velocityZ;
    if ((effect->duration - effect->durationTimer) < 0xA) {
        ((ParticleArcMotionState *)effect->allocation)->velocityY = (f32)((f64)((ParticleArcMotionState *)effect->allocation)->velocityY - 0.1);
        if ((s32)effect->alpha >= 0x16) {
            effect->alpha = effect->alpha - 0x14;
            return;
        }
        effect->alpha = 0;
    }
}

extern PlayerState *gActivePlayerState;
extern void *D_80028C30;

void effectTimedLightIntensityFade(EffectNode *effect, s8 *isDone) {
    f32 ratio;

    ratio = (f32)(effect->grid->frameCount - effect->param) / (f32)effect->grid->frameCount;
    if (ratio > 0.7) {
        ratio = 1.0f;
    }
    if ((gActivePlayerState->actor == effect->target) && ((void *)effect == D_80028C30)) {
        lightSetFlags(1);
        lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f,
                 ratio * 50.0, 0, 0xFF,
                 (-80.0f * ratio) + 255.0f,
                 (-205.0f * ratio) + 255.0f);
    }
}

extern void *D_8002FBB0[];
extern void *gLightSlotsEnd;
void timedLightOrbitUpdate(EffectNode *effect, s8 *isDone) {
    f32 ratio;
    void **slot;

    ratio = (f32)(effect->grid->frameCount - effect->param) / (f32)effect->grid->frameCount;
    if (ratio > 0.7) {
        ratio = 1.0f;
    }
    slot = D_8002FBB0;
    do {
        if (effect == *slot) {
            lightSetFlags(1);
            lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f,
                     ratio * 50.0, 0, 0xFF,
                     (-80.0f * ratio) + 255.0f,
                     (-205.0f * ratio) + 255.0f);
            return;
        }
        slot++;
    } while (slot != &gLightSlotsEnd);
}


void effectLightPulseOscillate(EffectNode *effect, s8 *isDone) {
    f32 ratio;
    f32 radius;
    s16 duration;
    s32 params;

    duration = effect->grid->frameCount;
    ratio = (f32)(duration - effect->param) / (f32)duration;
    if (ratio > 0.7) {
        ratio = 1.0f;
    }
    params = effect->speed;
    if (((u32)params >> 16) != 0) {
        radius = (params & 0xFFFF) * ratio;
    } else {
        radius = params & 0xFFFF;
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, (-80.0f * ratio) + 255.0f, (-205.0f * ratio) + 255.0f);
}

void effectLightFlickerDecay(EffectNode *effect, s8 *isDone) {
    f32 ratio;
    f32 radius;
    s16 duration;
    s32 params;

    duration = effect->grid->frameCount;
    ratio = (f32)(duration - effect->param) / (f32)duration;
    if (ratio > 0.7) {
        ratio = 1.0f;
    }
    params = effect->speed;
    if (((u32)params >> 16) != 0) {
        radius = (params & 0xFFFF) * ratio;
    } else {
        radius = params & 0xFFFF;
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, 0xFF, 0xFF);
}

typedef struct RadialSprayMotion {
    f32 velocityY;
    f32 velocityX;
    f32 velocityZ;
    f32 groundY;
} RadialSprayMotion;


void effectRadialSprayUpdate(EffectNode *effect, s8 *isDone) {
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

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0x10);
        mode = (s16) ((effect->speed >> 16) & 0xFF);
        if (mode == 0) {
            effect->sprayMotion->velocityY = (f32) (((f64) (f32) ((randomLcgNext() / 10000U) % 100U) / 20.0) - 2.5);
        } else {
            effect->sprayMotion->velocityY = (f32) (((f64) (f32) ((randomLcgNext() / 10000U) % 100U) / 10.0) - 2.5);
        }
        angleDeg = (f32) ((effect->speed & 0xFFFF) * 30);
        angleRad = angleDeg * 0.017453292f;
        angleDeg = (f32) ((f64) sinApprox(angleRad) * 2.5);
        offsetZ = (f32) ((f64) cosApprox(angleRad) * 2.5);
        effect->sprayMotion->velocityX = angleDeg;
        effect->sprayMotion->velocityZ = offsetZ;
        if (mode != 1) {
            if (mode == 2) {
                effect->sprayMotion->velocityX = effect->sprayMotion->velocityX * 4.0f;
                effect->sprayMotion->velocityZ = effect->sprayMotion->velocityZ * 4.0f;
            }
        } else {
            effect->sprayMotion->velocityX *= 2;
            effect->sprayMotion->velocityZ *= 2;
        }
        groundY = effect->y;
        if (collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) != 0) {
            effect->sprayMotion->groundY = groundY;
        } else {
            effect->sprayMotion->groundY = 0.0f;
        }
    }
    if (effect->param >= 9) {
        effect->sprayMotion->velocityY = (f32) ((f64) effect->sprayMotion->velocityY + -0.63);
        effect->sprayMotion->velocityX = (f32) ((f64) effect->sprayMotion->velocityX * 0.9);
        effect->sprayMotion->velocityZ = (f32) ((f64) effect->sprayMotion->velocityZ * 0.9);
    }
    if (effect->param >= ((effect->speed >> 24) & 0xFF)) {
        if (effect->alpha >= 0x3C) {
            effect->alpha -= 0x3C;
        } else {
            effect->alpha = 0;
        }
    }
    effect->x += effect->sprayMotion->velocityX;
    effect->z += effect->sprayMotion->velocityZ;
    effect->y += effect->sprayMotion->velocityY;
    if (effect->y < effect->sprayMotion->groundY) {
        *isDone = 1;
    }
}



void effectFollowParentUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx0[4][4];
    f32 mtx1[4][4];
    s32 angle;
    f32 trig;
    Actor *parent;

    parent = effect->target;
    if (parent->flags & 4) {
        if (effect->allocation == NULL) {
            effect->allocation = heapAlloc(0x40);
            angle = (u32) (randomLcgNext() % 36000U) / 100U;
            guScaleF(mtx0, effect->scaleX, effect->scaleY, 0.0f);
            guRotateF(mtx1, (f32) angle, 0.0f, 0.0f, 1.0f);
            guMtxCatF(mtx0, mtx1, mtx0);
            guMtxF2L(mtx0, effect->allocation);
            effect->alpha = 0xC8;
        }
        if ((parent->actorType == 0xC5) && ((f64) effect->scaleX < 0.5)) {
            trig = mathSinF(parent->moveYaw);
            effect->x = (f32) ((f64) effect->x - ((10.0 * (f64) effect->scaleX) * (f64) trig));
            trig = mathCosF(parent->moveYaw);
            effect->z = (f32) ((f64) effect->z - ((10.0 * (f64) effect->scaleX) * (f64) trig));
        } else {
            trig = mathSinF(parent->moveYaw);
            effect->x = (f32) ((f64) effect->x + (((f64) parent->speedXZ * 0.003) * (f64) trig));
            trig = mathCosF(parent->moveYaw);
            effect->z = (f32) ((f64) effect->z + (((f64) parent->speedXZ * 0.003) * (f64) trig));
            effect->y = (f32) ((f64) effect->y - 0.1);
        }
        if (parent->actorType == 0xFE) {
            effect->y = (f32) ((f64) effect->y - 0.6);
        }
        memcpy(&effect->matrices[0][gGfxBufferIndex], effect->allocation, 0x40);
        effect->state = 2;
        return;
    }
    *isDone = 1;
}

typedef struct {
    f32 heading;
    f32 speed;
} MotionState;

typedef struct {
    f32 speed;
} SineDriftState;

void effectDownwardDriftUpdate(EffectNode *effect, s8 *isDone) {
    f32 trig;
    f32 speed;

    speed = 0.35f; // FAKE: holding 0.35f in a local keeps its cvt.d.s and mul.d by 0.5 at run time; a literal folds
    effect->y = (f32)((f64)effect->y - ((f64)speed * 0.5));
    trig = mathSinF(effect->pair.lo);
    effect->x = (f32)(effect->x + (0.35f * trig));
    trig = mathCosF(effect->pair.lo);
    effect->z = (f32)(effect->z + (0.35f * trig));
}

void effectUpwardDriftUpdate(EffectNode *effect, s8 *isDone) {
    f32 trig;
    f32 speed;

    speed = 0.35f; // FAKE: holding 0.35f in a local keeps its cvt.d.s and mul.d by 0.5 at run time; a literal folds
    effect->y = (f32)((f64)effect->y + ((f64)speed * 0.5));
    trig = mathSinF(effect->pair.lo);
    effect->x = (f32)(effect->x + (0.35f * trig));
    trig = mathCosF(effect->pair.lo);
    effect->z = (f32)(effect->z + (0.35f * trig));
}

void effectSineHorizontalDriftUpdate(EffectNode *effect, s8 *isDone) {
    f32 speed;
    f32 trig;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(8);
        ((MotionState *)effect->allocation)->heading = (f32)effect->owner->moveYaw;
        ((MotionState *)effect->allocation)->speed = effect->owner->speedXZ + 30.0f;
    }
    speed = 0.35f; // FAKE: holding 0.35f in a local keeps its cvt.d.s and mul.d by 0.5 at run time; a literal folds
    effect->y = (f32)((f64)effect->y + ((f64)speed * 0.5));
    speed = (f32)((f64)((MotionState *)effect->allocation)->speed * 0.02);
    trig = mathSinF((s16)(s32)((MotionState *)effect->allocation)->heading);
    effect->x = (f32)(effect->x + (speed * trig));
    trig = mathCosF((s16)(s32)((MotionState *)effect->allocation)->heading);
    effect->z = (f32)(effect->z + (speed * trig));
    ((MotionState *)effect->allocation)->speed -= 15.0f;
    if (((MotionState *)effect->allocation)->speed < 0.0f) {
        ((MotionState *)effect->allocation)->speed = 0.0f;
    }
}

void effectSineDriftUpdate(EffectNode *effect, s8 *isDone) {
    f32 speed;
    f32 trig;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(4);
        ((SineDriftState *)effect->allocation)->speed = effect->owner->speedXZ;
    }
    speed = 0.35f; // FAKE: holding 0.35f in a local keeps its cvt.d.s and mul.d by 0.5 at run time; a literal folds
    effect->y = (f32)((f64)effect->y + ((f64)speed * 0.5));
    speed = (f32)((f64)((SineDriftState *)effect->allocation)->speed * 0.02);
    trig = mathSinF(effect->pair.lo);
    effect->x = (f32)(effect->x + (speed * trig));
    trig = mathCosF(effect->pair.lo);
    effect->z = (f32)(effect->z + (speed * trig));
}


void effectGroundBounceUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx0[4][4];
    f32 mtx1[4][4];
    f32 groundY;
    f32 progress;
    f32 pad1;
    f32 pad2;

    groundY = effect->y;
    if ((collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) == 0) ||
        (((effect->y < groundY) ? (groundY - effect->y) : -(groundY - effect->y)) > 10.0)) {
        progress = (f32) effect->param + ((f32) (u32) effect->frameTimer / (f32) (u32) effect->frameDelay);
        if (effect->param >= 7) {
            effect->y = (f32) ((f64) effect->y - (0.3 * ((f64) (14 - (s32) (20.0f - progress)) / 14.0)));
        }
    }
    if (effect->param == 0x10) {
        effect->frameDelay = 0xA;
    }
    guScaleF(mtx0, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(mtx1, (f32) ((effect->speed * 360) / 4096), 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx0, mtx1, mtx0);
    guTranslateF(mtx1, effect->x, effect->y, effect->z);
    guMtxCatF(mtx0, mtx1, mtx0);
    guMtxF2L(mtx0, &effect->matrices[0][gGfxBufferIndex]);
    if (effect->param >= 0x13) {
        effect->alpha -= 0x14;
    }
    effect->state = 3;
}

void effectFadeRatioStepUpdate(EffectNode *effect, s8 *isDone) {
    f32 ratio;
    u8 intensity;

    ratio = (f32)(effect->grid->frameCount - effect->param) / (f32)effect->grid->frameCount;
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    intensity = (u32)((-155.0f * ratio) + 255.0f);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 50.0f, 0, intensity, intensity, intensity);
}

void effectPuffExpandFadeUpdate(EffectNode *effect, s8 *isDone) {
    f32 scale;
    f32 divisor;
    s16 timer;

    divisor = 4.0f;
    timer = effect->param;
    if (timer >= 5) {
        timer = 4;
    }
    scale = (f32)((f64)((f32)timer / divisor) * 3.0);
    effect->scaleX = scale;
    effect->scaleY = scale;
}

extern u8 sEffectSparkConfig;

void effectSparkSpawnUpdate(EffectNode *effect, s8 *isDone) {
    s32 pad;
    s32 random;

    if (effect->durationTimer == 0) {
        if (effect->alpha < 0xE1) {
            effect->alpha += 0x1E;
        } else {
            effect->alpha = 0xFF;
        }
    }
    if ((effect->param == 3) || (effect->param == 0x11) || (effect->param == 0x15)) {
        sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, 0x14F, 0xFF, 0x7F, 0x1E, 0x4B, 0.3f, 0);
    }
    if ((effect->duration - effect->durationTimer) < 3) {
        if (effect->alpha >= 0xB) {
            effect->alpha -= 0xA;
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
        effectCreateAtPosition(&sEffectSparkConfig, 0.8f,
            ((random >> 15) % 65535 & 7) + effect->x,
            effect->y + 10.0f,
            ((randomNonNegative() >> 15) % 65535 & 7) + effect->z);
    }
}

typedef struct {
    f32 angle;
    f32 speed;
} RandomRotationState;

void effectSpinBillboardingUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(8);
        ((RandomRotationState *)effect->allocation)->angle = (f32)((randomLcgNext() % 36000U) / 100U);
        ((RandomRotationState *)effect->allocation)->speed = (f32)((f64)(randomLcgNext() % 10000U) / 7000.0);
    }
    effect->y = (f32)((f64)effect->y + ((f64)((RandomRotationState *)effect->allocation)->speed + 1.0));
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, ((RandomRotationState *)effect->allocation)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

typedef struct {
    f32 velocityX;
    f32 velocityY;
    f32 velocityZ;
} VelocityState;

typedef struct {
    f32 size;
    f32 shrinking;
    f32 chunk;
} LightGrowShrinkState;

void func_8071BC80(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 pad;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    VelocityState *state;

    state = effect->allocation;
    if (state == NULL) {
        effect->allocation = heapAlloc(0xC);
        guRotateF(mtx, -(f32)((randomLcgNext() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(tmpMtx, (f32)((effect->speed * 0x168) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, 10.0f, &dirX, &dirY, &dirZ);
        ((VelocityState *)effect->allocation)->velocityX = dirX;
        ((VelocityState *)effect->allocation)->velocityY = dirY;
        ((VelocityState *)effect->allocation)->velocityZ = dirZ;
        state = effect->allocation;
    }
    effect->x += state->velocityX;
    effect->y += state->velocityY;
    effect->z += state->velocityZ;
}

typedef struct {
    u8 maxAlpha;
    u8 pad1;
    s16 pulsePhase;
    u8 pulse;
} WaveMotionData;

typedef struct {
    u8 pad0[4];
    f32 offsetX;
    f32 offsetY;
    u8 padC[4];
    s16 phase;
    u8 pad12[2];
    WaveMotionData *data;
} WaveMotionState;

void effectWaveMotionUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 scale;
    WaveMotionState *state;
    WaveMotionData *data;
    f32 wave;

    state = effect->data;
    data = state->data;
    wave = mathSinF(state->phase);
    effect->alpha = (u32) ((f32) (u32) data->maxAlpha * wave);
    wave = 1.0f - wave;
    scale = effect->scaleY;
    if (data->pulse != 0) {
        scale = (f32) ((((f64) mathSinF(data->pulsePhase) * 0.15) + 0.85) * (f64) effect->scaleY);
        data->pulsePhase += 0xAA;
        data->pulsePhase &= 0xFFF;
    }
    guScaleF(mtx, effect->scaleX, scale, 0.0f);
    guTranslateF(tmpMtx, effect->x + (state->offsetX * wave), effect->y + (state->offsetY * wave), effect->z);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 3;
}

extern u8 D_807201D4;

void timedLightPulse(EffectNode *effect, s8 *isDone) {
    f64 ratio;
    s32 phase;
    s16 timer;
    s16 color[3];
    f32 total;
    f32 elapsed;
    f32 frac;

    if (gCurrentMap == 0xAA) {
        color[0] = 0xFF; color[1] = 0x46; // LAYOUT: one line lets as1 store color[1] (0x46) before color[0]
        color[2] = 0;
    } else {
        color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF; // LAYOUT: one line keeps the as1 store order color[2], [1], [0]
    }
    phase = effect->speed;
    switch (phase) {
        case 0:
            timer = effect->param;
            if ((timer == 0xA) && (effect->frameTimer == 0)) {
                sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, 0xE4, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
                effectSetDuration(-1);
                effectSetDepth(1);
                effectSetCallback(effectFallingSparkUpdate);
                effectCreateAtPosition(&D_807201D4, 0.8f, effect->x, effect->y, effect->z);
                return;
            }
            total = (f32)(effect->grid->frameCount * 2);
            elapsed = (f32)((timer * 2) + effect->frameTimer);
            ratio = (f64)((total - elapsed) / total);
            frac = (f32)(1.0 - ratio);
            lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 200.0f * frac, 0, 0xFF, color[1], color[2]);
            return;
        case 1:
            total = (f32)(effect->grid->frameCount * 2);
            elapsed = (f32)((effect->param * 2) + effect->frameTimer);
            frac = (total - elapsed) / total;
            lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 200.0f * frac, 0, 0xFF, color[1], color[2]);
            return;
    }
}

extern u8 D_8071FB54;

void effectFallingSparkUpdate(EffectNode *effect, u8 *isDone) {
    s32 pad;
    f32 groundY;
    s16 color[3];
    f32 *newState;

    if (effect->allocation == NULL) {
        newState = heapAlloc(0xC);
        effect->allocation = newState;
        *newState = 6.0f;
    }
    if (gCurrentMap == 0xAA) {
        color[0] = 0xFF; color[1] = 0x46; color[2] = 0; // LAYOUT: one line lets as1 store color[1] before color[0]
    } else {
        color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF; // LAYOUT: one line keeps as1's color[2], [0], [1] store order
    }
    effect->x += 1.0f;
    effect->y += *(f32 *)effect->allocation;
    *(f32 *)effect->allocation -= 0.15;
    groundY = effect->y;
    if (collisionCheckGroundAtPoint(effect->x, effect->z, &groundY) == 0) {
        *isDone = 1;
    } else if ((effect->y < groundY) && (*(f32 *)effect->allocation < 0.0)) {
        *isDone = 1;
    }
    if (*isDone != 0) {
        sfxPlayAtPositionPooled(effect->x, effect->y, effect->z, 0xEA, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
        effectSetMode(2);
        effectSetDepth(1);
        effectSetSpeed(1);
        effectSetCallback(timedLightPulse);
        effectSetParam(7);
        effectCreateAtPosition(&D_8071FB54, 0.667f, effect->x, groundY + 10.0f, effect->z);
    }
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 200.0f, 0, color[0], color[1], color[2]);
}


void func_8071C48C(EffectNode *effect, s8 *isDone) {
    f32 ratio;
    f32 radius;
    s16 duration;
    u32 params;

    duration = effect->grid->frameCount;
    ratio = (f32)(duration - effect->param) / (f32)duration;
    if (ratio > 0.7) {
        ratio = 1.0f;
    }
    params = effect->speed;
    if ((params >> 0x10) != 0) {
        radius = (s32)(params & 0xFFFF) * ratio;
    } else {
        radius = (s32)(params & 0xFFFF);
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, radius, 0, 0,
             (-80.0f * ratio) + 255.0f, 0xFF);
}

void func_8071C620(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    VelocityState *state;

    state = effect->allocation;
    if (state == NULL) {
        effect->allocation = heapAlloc(0xC);
        guRotateF(mtx, (f32)((randomLcgNext() % 36000U) / 100U), 1.0f, 0.0f, 0.0f);
        guRotateF(tmpMtx, (f32)((randomLcgNext() % 36000U) / 100U), 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guRotateF(mtx, (f32)((randomLcgNext() % 36000U) / 100U), 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, 0.5f, &dirX, &dirY, &dirZ);
        ((VelocityState *)effect->allocation)->velocityX = dirX;
        ((VelocityState *)effect->allocation)->velocityY = dirY;
        ((VelocityState *)effect->allocation)->velocityZ = dirZ;
        state = effect->allocation;
    }
    effect->x += state->velocityX;
    effect->y += state->velocityY;
    effect->z += state->velocityZ;
}

void effectShrinkFadeMatrixUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    effect->scaleX = (f32)((f64)effect->scaleX - 0.05);
    effect->scaleY = (f32)((f64)effect->scaleY - 0.05);
    if (effect->scaleX <= 0.0f) {
        *isDone = 1;
    }
    effect->speed = effect->speed + 5;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, (f32)effect->speed, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

void effectGrowExpandMatrixUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 scale;

    effect->scaleX = (f32)((f64)effect->scaleX * 1.07);
    effect->speed = effect->speed + 0xA;
    scale = effect->scaleX;
    effect->scaleY = scale;
    guScaleF(mtx, scale, scale, 0.0f);
    guRotateF(tmpMtx, (f32)effect->speed, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 homeX;
    s16 homeY;
    s16 homeZ;
    s16 rotation;
} WispWanderState;

s16 D_80755650[18] = {
    0x01D4, 0x0078, 0x026D, 0x01EE, 0x0082, 0x02F6, 0x02E5, 0x008C, 0x0254,
    0x02C3, 0x0078, 0x02FA, 0x025A, 0x006E, 0x0312, 0x025E, 0x0096, 0x026A,
};
extern s32 D_8071FB08;

void effectWispWanderUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    WispWanderState *state;
    u8 homeIndex;
    s16 targetAngle;
    s16 *home;

    if (effect->allocation == NULL) {
        homeIndex = (randomNonNegative() >> 0xF) % 1000 % 6;
        effect->allocation = heapAlloc(0xE);
        state = effect->allocation;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        home = &D_80755650[homeIndex * 3];
        state->homeX = home[0];
        state->homeY = home[1];
        state->homeZ = home[2];
        state->rotation = 0;
        state->y = effect->y;
    }
    state = effect->allocation;
    if (gPrimaryPlayerActor->z < 340.0f) {
        state->homeX = 0x12C;
        state->homeY = 0x96;
        state->homeZ = 0x64;
    }
    targetAngle = mathAngleBetweenPoints2D(state->homeX, state->homeZ, effect->x, effect->z);
    state->angle = mathAngleEaseToward(state->angle, targetAngle, (randomNonNegative() >> 0xF) % 10 + 5);
    state->y = (state->homeY - state->y) * 0.1 + state->y;
    effect->x += state->speed * mathSinF(state->angle);
    effect->z += state->speed * mathCosF(state->angle);
    effect->y = mathSinF((state->speed + 0x32) * gFrameCounter) * 40.0 + (state->y + 0x28);
    if (((randomNonNegative() >> 0xF) % 1000) >= 991) {
        homeIndex = ((randomNonNegative() >> 0xF) % 1000) % 6;
        state->homeX = D_80755650[homeIndex * 3];
        state->homeY = D_80755650[(homeIndex * 3) + 1];
        state->homeZ = D_80755650[(homeIndex * 3) + 2];
    }
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(gFrameCounter & 3)) {
        effectSetDepth(1);
        effectSetCallback(effectShrinkFadeMatrixUpdate);
        effectCreateAtPosition(&D_8071FB08, 1.6f, effect->x, effect->y, effect->z);
    }
    state->rotation += state->speed;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}


typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 rotation;
} WispHomeMotionState;

void effectWispHomeUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    WispHomeMotionState *state;
    Actor *actor;
    s16 pad;
    s16 targetAngle;
    f32 turnRate;

    if (effect->allocation == NULL) {
        randomNonNegative();
        state = heapAlloc(8);
        effect->allocation = state;
        state->angle = 0;
        state->y = effect->y;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        state->rotation = 0;
    }
    state = effect->allocation;
    actor = effect->target;
    targetAngle = mathAngleBetweenPoints2D(actor->x, actor->z, effect->x, effect->z);
    turnRate = ((randomNonNegative() >> 0xF) % 10) + 5;
    state->angle = mathAngleEaseToward(state->angle, targetAngle, turnRate);
    state->y = (actor->y + actor->eyeHeight - state->y) * 0.1 + state->y;
    effect->x += state->speed * mathSinF(state->angle);
    effect->z += state->speed * mathCosF(state->angle);
    effect->y = mathSinF((state->speed + 0x32) * gFrameCounter) * 40.0 + (state->y + 0x28);
    lightSetFlags(1);
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(gFrameCounter & 3)) {
        effectSetDepth(1);
        effectSetCallback(effectShrinkFadeMatrixUpdate);
        effectCreateAtPosition(&D_8071FB08, 1.6f, effect->x, effect->y, effect->z);
    }
    state->rotation += state->speed;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guRotateF(tmpMtx, state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}


typedef struct {
    f32 framesLeft;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
} LightApproachMotionState;

extern u8 gCurrentWorldId;
extern u16 gLevelCollectibleCounts[];

void effectConvergeOnNodeUpdate(EffectNode *effect, s8 *isDone) {
    LightApproachMotionState *motion;
    f32 factor;
    Actor *node;
    f64 pad;

    node = effect->target;
    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0x10);
        ((LightApproachMotionState *)effect->allocation)->framesLeft = 30.0f;
    }
    motion = effect->allocation;
    actorGetNodePos(node, 1, &motion->nodeX, &motion->nodeY, &motion->nodeZ);
    factor = (f32)((f64)motion->framesLeft / 30.0);
    effect->x = (gPrimaryPlayerActor->x - motion->nodeX) * factor + motion->nodeX;
    effect->y = (gPrimaryPlayerActor->y - motion->nodeY) * factor + motion->nodeY;
    effect->z = (gPrimaryPlayerActor->z - motion->nodeZ) * factor + motion->nodeZ;
    motion->framesLeft -= 1.0f;
    if (motion->framesLeft == 0.0f) {
        gActivePlayerState->stateFlags |= 0x20000;
        gLevelCollectibleCounts[mapGetHubWorldIndex(gCurrentWorldId, 0)]++;
        *isDone = 1;
    }
}


void effectLifetimeCountdownUpdate(EffectNode *effect, s8 *isDone) {
    u16 difference;
    s32 amount;
    u8 remaining;
    s32 completed;

    amount = effect->speed;
    difference = effect->alpha - amount;
    completed = 1;
    remaining = difference;
    effect->alpha = remaining;
    if (amount >= remaining) {
        *isDone = completed;
    }
}


typedef struct {
    f32 radius;
    f32 targetRadius;
    f32 bobAngle;
    f32 bobSpeed;
    f32 orbitAngle;
    f32 orbitSpeed;
    f32 age;
    f32 direction;
} OrbitSourceState;

typedef struct {
    f32 velocityX;
    f32 velocityY;
    f32 velocityZ;
} BallisticVelocityState;

typedef struct {
    f32 velX;
    f32 velZ;
    f32 velY;
    f32 floorY;
} FallInitState;



void effectOrbitSourceUpdate(EffectNode *effect, s8 *isDone) {
    OrbitSourceState *state;
    OrbitSourceState *newState;
    Actor *source;

    source = effect->owner;
    if (effect->allocation == NULL) {
        newState = heapAlloc(0x20);
        effect->allocation = newState;
        newState->radius = sqrtf(((source->x - effect->x) * (source->x - effect->x)) + ((source->z - effect->z) * (source->z - effect->z)));
        newState->targetRadius = (randomFloat() * 20.0f) + 10.0f;
        newState->bobAngle = randomFloat() * 4095.0f;
        newState->bobSpeed = (randomFloat() * 90.0f) + 10.0f;
        newState->orbitAngle = source->yaw;
        newState->orbitSpeed = randomFloat() * 30.0f;
        newState->age = 0.0f;
        newState->direction = (f32) (((randomNonNegative() >> 0xF) % 0xFF) % 2) * 2 - 1.0f;
    }
    state = effect->allocation;
    state->radius = (state->targetRadius - state->radius) * 0.15 + state->radius;
    state->orbitSpeed = (120.0f - state->orbitSpeed) * 0.01 + state->orbitSpeed;
    state->orbitAngle += state->direction * state->orbitSpeed;
    state->bobAngle += state->bobSpeed;
    effect->x = (mathSinF((s16) state->orbitAngle) * state->radius) + source->x;
    effect->z = (mathCosF((s16) state->orbitAngle) * state->radius) + source->z;
    effect->y += 0.6 * mathSinF((s16) state->bobAngle);
    state->age += 1.0f;
    if (state->age > 45.0f) {
        *isDone = 1;
    }
    if ((gFrameCounter % effect->speed) == 0) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetSpeed(0x2A);
        effectSetCallback(&effectLifetimeCountdownUpdate);
        effectSetFlags(0x20);
        effectCreateAtPosition(effect->grid->asset, effect->scaleX, effect->x, effect->y, effect->z);
    }
}

void effectShockwaveRingUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    Actor *player;
    s32 radius;

    radius = (s32) (effect->scaleX * 20.0f);
    player = gPrimaryPlayerActor;
    if ((player->y <= effect->y) && (effect->y < player->y + (f32) player->eyeHeight)) {
        if ((((player->x - effect->x) * (player->x - effect->x)) + ((player->z - effect->z) * (player->z - effect->z))) < (f32) (radius * radius)) {
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
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 3;
}

f32 D_80755674 = -0.1f;
f32 D_80755678 = 2.0f;

void effectBallisticUpdate(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    s32 pad;
    f32 dirX;
    f32 dirY;
    f32 dirZ;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xC);
        guRotateF(mtx, -(f32) ((randomLcgNext() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(tmpMtx, (f32) ((effect->speed * 360) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxXFMF(mtx, 0.0f, 0.0f, D_80755678, &dirX, &dirY, &dirZ);
        ((BallisticVelocityState *) effect->allocation)->velocityX = dirX;
        ((BallisticVelocityState *) effect->allocation)->velocityY = dirY;
        ((BallisticVelocityState *) effect->allocation)->velocityZ = dirZ;
    }
    effect->x = effect->x + ((BallisticVelocityState *) effect->allocation)->velocityX;
    effect->y = effect->y + ((BallisticVelocityState *) effect->allocation)->velocityY;
    ((BallisticVelocityState *) effect->allocation)->velocityY = ((BallisticVelocityState *) effect->allocation)->velocityY + D_80755674;
    effect->z = effect->z + ((BallisticVelocityState *) effect->allocation)->velocityZ;
    if (effect->y <= gPrimaryPlayerActor->y) {
        *isDone = 1;
    }
}

void effectFallStateInit(Actor *source, EffectNode *effect, u8 *isDone) {
    s16 pad;
    s16 angle;
    f32 speedXZ;
    f32 sourceSpeed;
    f32 speedY;
    FallInitState *fallState;
    s16 angleOffset;

    fallState = effect->allocation = heapAlloc(0x10);
    effect->x += (randomFloat() - 0.5f) * 2.0f;
    effect->y += (randomFloat() - 0.5f) * 2.0f;
    effect->z += (randomFloat() - 0.5f) * 2.0f;
    if (source != NULL) {
        angleOffset = randomLcgNext() & 0x1FF;
        angle = (source->yaw + angleOffset + 0x700) & 0xFFF;
        sourceSpeed = source->speedXZ * 0.016666668f;
        sourceSpeed = MIN(sourceSpeed, 1.0f);
        if (sourceSpeed < 0.3) {
            *isDone = 1;
        }
        speedY = sourceSpeed * 1.5f * 1.8f;
        effect->owner = source;
    } else {
        sourceSpeed = 0.8f;
        angle = randomLcgNext() % 4095U;
        speedY = (randomFloat() + 1.0f) * 3.0f;
    }
    effect->scaleX *= 0.5 * (1 + randomFloat());
    effect->alpha = 0x82;
    effect->scaleY = effect->scaleX;
    speedXZ = randomFloat() * sourceSpeed;
    fallState->velX = mathSinF(angle) * speedXZ;
    fallState->velZ = mathCosF(angle) * speedXZ;
    fallState->velY = speedY;
    collisionGetFloorHeight(&fallState->floorY);
}

void effectFloorFallUpdate(EffectNode *effect, u8 *isDone) {
    FallInitState *state;
    Actor *owner;
    s32 landed;

    if (effect->allocation == NULL) {
        effectFallStateInit(NULL, effect, isDone);
    }
    state = effect->allocation;
    state->velY += -0.5f;
    effect->x += state->velX;
    effect->y += state->velY;
    effect->z += state->velZ;
    landed = *isDone;
    if (landed == 0) {
        owner = effect->owner;
        if (owner != NULL) {
            if (effect->y <= owner->waterY) {
                landed = *isDone = 1;
            }
        } else {
            if (effect->y <= state->floorY) {
                landed = *isDone = 1;
            }
        }
        if (landed != 0) {
            effectSpawnImpactPuff(effect->scaleX * 5.0f, effect->x, effect->y, effect->z);
        }
    }
}

typedef struct {
    f32 growth;
    f32 yawAngle;
    f32 yawSpeed;
    f32 bobAngle;
    f32 bobSpeed;
    f32 bobHeight;
} ActorOrbitState;

void effectActorOrbitFollowUpdate(EffectNode *effect, s8 *isDone) {
    ActorOrbitState *state;
    Actor *target;
    PlayerState *targetState;
    f32 blend;

    blend = 0.3f;
    target = effect->target;
    if (effect->allocation == NULL) {
        state = heapAlloc(0x18);
        effect->allocation = state;
        state->growth = 0.0f;
        state->yawAngle = (f32)(randomFloat() * 4095.0f);
        state->yawSpeed = (f32)((randomFloat() > 0.5 ? (f64)randomFloat() : 0.5) * 300.0);
        if ((f64)randomFloat() > 0.5) {
            state->yawSpeed = (f32)-state->yawSpeed;
        }
        state->bobAngle = (f32)(randomFloat() * 4095.0f);
        state->bobSpeed = (f32)((randomFloat() > 0.5 ? (f64)randomFloat() : 0.5) * 300.0);
        if ((f64)randomFloat() > 0.5) {
            state->bobSpeed = (f32)-state->bobSpeed;
        }
        state->bobHeight = (f32)(randomFloat() > 0.3 ? (f64)randomFloat() : 0.3);
        blend = 1.0f;
    }
    state = effect->allocation;
    if (state->growth < 1.0f) {
        state->growth = state->growth + 0.033333335f;
    }
    state->yawAngle = (f32)(state->yawAngle + state->yawSpeed);
    state->yawAngle = (f32)((s16)(s32)state->yawAngle & 0xFFF);
    state->bobAngle = (f32)(state->bobAngle + state->bobSpeed);
    state->bobAngle = (f32)((s16)(s32)state->bobAngle & 0xFFF);
    effect->x = (f32) (((((mathSinF((s16) (s32) state->yawAngle) * (15.0f * state->growth)) + target->x) - effect->x) * blend) + effect->x);
    effect->z = (f32) (((((mathCosF((s16) (s32) state->yawAngle) * (15.0f * state->growth)) + target->z) - effect->z) * blend) + effect->z);
    effect->y = (f32) (((((((mathSinF((s16) (s32) state->bobAngle) * (state->bobHeight * state->growth)) + 1.0f) * 15.0f) + target->y) - effect->y) * blend) + effect->y);
    targetState = target->customState;
    if (!(targetState->stateFlags & 0x10)) {
        *isDone = 1;
    }
}

void func_8071E028(EffectNode *effect, s8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    guTranslateF(tmpMtx, 0.0f, effect->scaleY * 20.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, (f32)effect->speed, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

typedef struct {
    f32 reverse;
    f32 height;
    f32 radius;
    f32 step;
    f32 progress;
    f32 angle;
} ArcMotionState;

typedef struct {
    f32 riseRate;
    f32 risePhase;
    f32 swayAmplitude;
    f32 swayPhase;
    f32 unk10;
    f32 unk14;
} SwayRiseState;

typedef struct {
    f32 centerX;
    f32 centerZ;
    f32 spinDirection;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} CircleRiseState;

typedef struct {
    f32 speed;
    f32 velocityY;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} ScatterFallState;

typedef struct {
    f32 scale;
    f32 targetScale;
    f32 rotation;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} ScaleSpinState;

typedef struct {
    f32 heading;
    f32 velocityY;
    f32 speed;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} BurstParticleState;

void func_8071E110(EffectNode *effect, u8 reverse, u16 startAngle, f32 radius, f32 height, s32 steps) {
    ArcMotionState *motion;

    motion = heapAlloc(0x18);
    effect->allocation = motion;
    motion->reverse = (f32)(u32)reverse;
    motion->height = height;
    motion->radius = radius;
    motion->step = 1.0f / (f32)steps;
    motion->progress = 0.0f;
    motion->angle = (f32)(u32)startAngle;
}

void effectArcAroundActorUpdate(EffectNode *effect, s8 *isDone) {
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
    ArcMotionState *state;

    if (effect->allocation == NULL) {
        *isDone = 1;
        return;
    }
    state = effect->allocation;
    target = effect->target;
    if (actorTableContains(target) == 0) {
        *isDone = 1;
        return;
    }
    arcAngle = state->progress * ((1.0f - (state->reverse * 2)) * 2048.0f);
    arcAngle = (f32)((s16)(s32)arcAngle & 0xFFF);
    radius = mathSinF((s16)(s32)arcAngle) * state->radius;
    state->angle = (f32)((f64)state->angle + (2.0 * (f64)((1.0f - (state->reverse * 2)) * 4096.0f) * (f64)state->step));
    state->angle = (f32)((s16)(s32)state->angle & 0xFFF);
    offsetX = mathSinF((s16)(s32)state->angle) * radius;
    cosYaw = mathCosF((s16)(s32)state->angle);
    height = state->height;
    offsetY = state->progress * height;
    if (state->reverse == 0.0f) {
        offsetY = height - offsetY;
    }
    effect->x = (f32)(target->x + offsetX);
    effect->z = (f32)(target->z + (cosYaw * radius));
    effect->y = (f32)(target->y + offsetY);
    state->progress = (f32)(state->progress + state->step);
    if (state->progress >= 1.0f) {
        *isDone = 1;
    }
}


void effectLightGrowShrinkUpdate(EffectNode *effect, s8 *isDone) {
    f64 size;
    f32 intensity;
    f32 red;
    f32 green;
    f32 blue;
    f32 brightness;
    s32 mode;
    LightGrowShrinkState *newState;
    LightGrowShrinkState *state;

    if (effect->allocation == NULL) {
        newState = heapAlloc(0xC);
        effect->allocation = newState;
        newState->size = 0.0f;
        newState->shrinking = 0.0f;
        newState->chunk = mapChunkFindByPosition(effect->x, effect->y, effect->z, 0);
    }
    state = effect->allocation;
    if (state->shrinking == 0.0) {
        state->size += 30.0;
        size = state->size;
        if (size > 300.0) {
            state->shrinking = 1.0f;
            state->size = 300.0f;
        }
    } else {
        state->size -= 30.0;
        size = state->size;
        if (size < 30.0) {
            *isDone = 1;
            state->size = 30.0f;
        }
    }
    size = state->size;
    if (size < 300.0) {
        intensity = size / 300.0;
    } else {
        intensity = 1.0f;
    }
    lightSetRadius(1000);
    lightSetTargetId(state->chunk);
    mode = effect->speed;
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
    lightAdd(effect->x, effect->y, effect->z, 0.0f, 0.0f, 0.0f, state->size, 0, brightness * red, brightness * green, brightness * blue);
}

typedef struct {
    f32 speed;
    f32 heading;
} DecelDriftState;

void effectDecelDriftFadeUpdate(EffectNode *effect, s8 *isDone) {
    f32 stepX;
    DecelDriftState *newState;
    DecelDriftState *state;
    f32 stepZ;

    if (effect->allocation == NULL) {
        newState = heapAlloc(8);
        effect->allocation = newState;
        newState->speed = 10.0f;
        newState->heading = (f32)(effect->speed * 0x154);
    }
    state = effect->allocation;
    state->speed = (f32)((f64)state->speed - 0.2);
    if ((f64)state->speed < 0.8) {
        state->speed = 0.8f;
    }
    stepX = mathSinF((s16)(s32)state->heading);
    stepX = state->speed * stepX;
    stepZ = mathCosF((s16)(s32)state->heading);
    stepZ = state->speed * stepZ;
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

void effectBurstParticleUpdate(EffectNode *effect, s8 *isDone) {
    BurstParticleState *state;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xC);
        state = effect->allocation;
        state->heading = randomFloat() * 4095.0f;
        state->velocityY = (f32)(((f64)randomFloat() * 0.5 + 1.0) * 5.0);
        state->speed = 15.0f;
    }
    state = effect->allocation;
    state->velocityY = state->velocityY - 1.0f;
    state->speed = (f32)((f64)state->speed * 0.95);
    effect->x += state->speed * mathSinF((s16)state->heading);
    effect->z += state->speed * mathCosF((s16)state->heading);
    effect->y = effect->y + state->velocityY;
}



void effectProximityFadeUpdate(EffectNode *effect, s8 *isDone) {
    f32 *state;
    PlayerStruct *player;
    f32 limit;
    f32 dist;
    f32 dx;
    f32 dy;
    s32 iv;
    f32 dz;

    limit = (f32)((effect->speed * 3) / 4);
    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(4);
        *(f32 *)effect->allocation = (f32)effect->alpha;
    }
    state = effect->allocation;
    player = gPlayerSlots;
    dz = player->eyeZ - effect->z;
    dx = player->eyeX - effect->x;
    dy = player->eyeY - effect->y;
    dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
    if (dist < limit) {
        effect->alpha = (u32)*state;
        return;
    }
    iv = *state * ((dist - limit) / ((f32)effect->speed - limit));
    if (*state < (f32)iv) {
        iv = *state;
    }
    effect->alpha = (u32)(*state - (f32)iv);
}


void func_8071EDEC(EffectNode *effect, s32 unused) {
    f64 pad;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    actorGetNodePos(effect->target, 1, &nodeX, &nodeY, &nodeZ);
    effect->x = (f32)((f64)effect->x + ((f64)(nodeX - effect->x) * 0.1));
    effect->y = (f32)((f64)effect->y + ((f64)(nodeY - effect->y) * 0.1));
    effect->z = (f32)((f64)effect->z + ((f64)(nodeZ - effect->z) * 0.1));
}

void func_8071EEA4(EffectNode *effect, s32 unused) {
    effect->scaleY = (f32) (((f64) effect->speed / 100.0) + 1.0);
}


void effectScaleSpinUpdate(EffectNode *effect, s8 *isDone) {
    ScaleSpinState *state;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xC);
        state = effect->allocation;
        state->scale = 0.01f;
        state->targetScale = effect->scaleX;
        state->rotation = 0.0f;
    }
    state = effect->allocation;
    state->scale = (f32)(((f64)(state->targetScale - state->scale) * 0.1) + (f64)state->scale);
    state->rotation += 5.0f;
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    matrixMakeRotationZ(tmpMtx, state->rotation);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}


void func_8071EFDC(EffectNode *effect, s8 *isDone) {
    s32 alpha;

    effect->scaleX = (f32)((f64)effect->scaleX * 1.05);
    effect->scaleY = (f32)(((f64)effect->scaleY * 1.05) * 1.0);
    alpha = (effect->alpha = (effect->alpha & 0xFFu) - 5);
    if ((alpha & 0xFF) < 6) {
        *isDone = 1;
    }
}

void func_8071F034(EffectNode *effect, s32 unused) {
    if (effect->param == 0) {
        effect->x = gPrimaryPlayerActor->x;
        effect->y = gPrimaryPlayerActor->y;
        effect->z = gPrimaryPlayerActor->z;
    }
}

void effectScatterFallUpdate(EffectNode *effect, s8 *isDone) {
    ScatterFallState *state;

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(8);
        state = effect->allocation;
        state->speed = (f32)(((f64)((randomNonNegative() >> 0xF) % 100) / 10.0) + 2.0);
        state->velocityY = (f32)(-8.0 - ((f64)((randomNonNegative() >> 0xF) % 100) / 70.0));
        effect->speed += (s16)((randomNonNegative() >> 0xF) % 800) - 0x190;
        effect->speed = effect->speed % 4095;
    }
    state = effect->allocation;
    effect->x += state->speed * mathSinF(effect->pair.lo);
    effect->z += state->speed * mathCosF(effect->pair.lo);
    effect->y += state->velocityY;
}




void effectCircleRiseFadeUpdate(EffectNode *effect, s8 *isDone) {
    static s8 sd = 1; // D_8075567C: a function-local static so uopt treats it as non-aliased
    CircleRiseState *state;
    CircleRiseState *temp;

    if (effect->allocation == NULL) {
        temp = heapAlloc(0xC);
        effect->allocation = temp;
        temp->centerX = effect->x;
        temp->centerZ = effect->z;
        temp->spinDirection = (f32)sd;
        sd = -sd;
    }
    state = effect->allocation;
    effect->x = (mathSinF(effect->pair.lo) * 14.0f) + state->centerX;
    effect->z = (mathCosF(effect->pair.lo) * 14.0f) + state->centerZ;
    effect->y = effect->y + 0.5f;
    if (effect->alpha >= 5) {
        effect->alpha = effect->alpha - 4;
    } else {
        *isDone = 1;
    }
    effect->speed = effect->speed + (s32)((f64)state->spinDirection * 200.0);
}



typedef struct {
    f32 velocityY;
    f32 gravity;
} FallingMotionState;

typedef struct {
    f32 scale;
} ScaleFollowState;

void func_8071F2F8(EffectNode *effect, s32 unused) {
    f32 height;
    FallingMotionState *newState;
    FallingMotionState *state;

    state = effect->allocation;
    if (state == NULL) {
        newState = heapAlloc(8);
        effect->allocation = newState;
        newState->velocityY = (f32) (effect->speed & 0xFFFF);
        newState->gravity = (f32) ((s32) effect->speed >> 0x10);
        state = effect->allocation;
    }
    effect->y = effect->y + state->velocityY;
    height = state->velocityY;
    if (height > -20.0f) {
        state->velocityY = (f32) ((f64) height - ((f64) state->gravity * 0.01));
    }
}

void func_8071F3C0(EffectNode *effect, s32 unused) {
    ScaleFollowState *newState;
    ScaleFollowState *state;

    state = effect->allocation;
    if (state == NULL) {
        newState = heapAlloc(4);
        effect->allocation = newState;
        newState->scale = (f32) ((f64) effect->scaleY * 6.666666666666667);
        state = effect->allocation;
    }
    effect->scaleX = effect->owner->sub4->scaleY * state->scale;
    effect->scaleY = effect->scaleX;
}

void effectSwayRiseUpdate(EffectNode *effect, s8 *isDone) {
    SwayRiseState *state;

    if (effect->allocation == NULL) {
        if (gFrameCounter & 1) {
            effect->scaleX = effect->scaleX * -1.0f;
        }
        effect->allocation = heapAlloc(8);
        state = effect->allocation;
        state->riseRate = (f32)(((randomNonNegative() >> 0xF) % 20) + 5);
        state->risePhase = 0.0f;
        state->swayAmplitude = (f32)(((randomNonNegative() >> 0xF) % 100) + 0xA);
        state->swayPhase = 0.0f;
    }
    state = effect->allocation;
    {
        f32 t = mathSinF((s16)state->risePhase);
        effect->y = (f32)((f64)effect->y + ((1.0 + (f64)t) * (f64)(f32)(1.0 + ((f64)state->riseRate * 0.4))));
    }
    effect->x += mathSinF((s16)state->swayPhase) * (f32)((f64)state->swayAmplitude * 0.5);
    if (effect->frameDelay == 0) {
        effect->param = (s16)(s32)(((f64)mathSinF((s16)state->swayPhase) * 2.5) + 2.5);
    }
    state->risePhase = state->risePhase + 100.0f;
    state->swayPhase = state->swayPhase + 50.0f;
    if (effect->y > 960.0f) {
        *isDone = 1;
    }
}



void func_8071F660(EffectNode *effect, void *unused) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 progress;

    progress = (f32) effect->durationTimer / (f32) (effect->duration - 1);
    effect->scaleX = (f32) ((f64) mathSinF((s16) (s32) (progress * 2048.0f)) * 3.0);
    effect->scaleY = effect->scaleX;
    guScaleF(mtx, effect->scaleX, effect->scaleX, 0.0f);
    matrixMakeRotationZ(tmpMtx, progress * 180.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}

void effectPulseSpinUpdate(EffectNode *effect, s8 *isDone) {
    ScaleSpinState *state;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];

    if (effect->allocation == NULL) {
        effect->allocation = heapAlloc(0xC);
        state = effect->allocation;
        state->scale = 0.01f;
        state->targetScale = effect->scaleX;
        state->rotation = 0.0f;
    }
    state = effect->allocation;
    state->scale = (f32)(((f64)(state->targetScale - state->scale) * 0.1) + (f64)state->scale);
    state->rotation += 5.0f;
    effect->scaleX = (f32)(((f64)mathSinF((s16)(gFrameCounter * 50)) * 0.1) + (f64)state->scale);
    effect->scaleY = (f32)(((f64)mathCosF((s16)(gFrameCounter * 25)) * 0.1) + (f64)state->scale);
    guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
    matrixMakeRotationZ(tmpMtx, state->rotation);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
    effect->state = 2;
}


typedef struct {
    f32 spinSpeed;
    f32 rotation;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 progress;
    f32 progressStep;
} LerpPathMotionState;



void effectLerpPathUpdate(EffectNode *effect, u8 *isDone) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    LerpPathMotionState *state;

    if (effect->allocation != NULL) {
        state = effect->allocation;
        state->progress = state->progress + state->progressStep;
        if ((f64)state->progress >= 1.0) {
            *isDone = 0xFF;
            state->progress = 1.0f;
        }
        effect->x = (state->deltaX * state->progress) + state->startX;
        effect->y = (state->deltaY * state->progress) + state->startY;
        effect->z = (state->deltaZ * state->progress) + state->startZ;
        if (!(gFrameCounter & 3)) {
            effectSetDepth(1);
            effectSetCallback(effectShrinkFadeMatrixUpdate);
            effectCreateAtPosition(&D_8071FB08, 1.6f, effect->x, effect->y, effect->z);
        }
        state->rotation = state->rotation + state->spinSpeed;
        guScaleF(mtx, effect->scaleX, effect->scaleY, 0.0f);
        guRotateF(tmpMtx, state->rotation, 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
        guMtxF2L(mtx, &effect->matrices[0][gGfxBufferIndex]);
        effect->state = 2;
    }
}

