#include "common.h"
#include "actor.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/12E800.h"
#include "proto/global/13A7A0.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/936B0.h"
#include "proto/global/D5E10.h"
#include "proto/global/F4C0.h"
#include "proto/global/FCCD0.h"

extern u8 *sScriptPc;
extern PlayerState *gActivePlayerState;
extern Actor *gSpawnedActor;

void scriptSetActorRampTarget(Actor *actor, f32 targetVal, f32 rampTime) {
    ActorSub4 *ramp;

    ramp = actor->sub4;
    if (rampTime > 0.0f) {
        ramp->speedRampDuration = rampTime;
        ramp->speedTo = targetVal;
        ramp->speedRampTime = 0.0f;
        ramp->speedFrom = ramp->unk48;
        return;
    }
    ramp->unk48 = targetVal;
    ramp->speedRampDuration = 0.0f;
}

void scriptSetRampValue(Actor *actor, f32 target, f32 rampTime) {
    AnimSlot *ramp;

    ramp = actor->sub4->model;
    if (rampTime > 0.0f) {
        ramp->speedRampDuration = rampTime;
        ramp->speedTo = target;
        ramp->speedRampTime = 0.0f;
        ramp->speedFrom = ramp->speed;
        return;
    }
    ramp->speed = target;
    ramp->speedRampDuration = 0.0f;
}

extern s32 sScriptContinueRunning;
typedef s32 (*ActorScriptCommand)(Actor *);
extern ActorScriptCommand sScriptOpcodeTable[];

void actorScriptExecute(Actor *actor) {
    ActorSub4 *state;

    state = actor->sub4;
    if (state->scriptStart != NULL) {
        sScriptContinueRunning = 1;
        sScriptPc = state->scriptPc;
        while ((state->scriptWaitFlags == 0) && (sScriptContinueRunning != 0)) {
            sScriptContinueRunning = sScriptOpcodeTable[*sScriptPc](actor);
        }
        state->scriptPc = sScriptPc;
        if (state->scriptCommand != NULL) {
            sScriptPc = state->scriptCommandPc;
            state->scriptCommand(actor);
        }
    }
}


extern u16 *gActorScriptIndexTable;


void actorScriptStartByIndex(Actor *actor, s32 slot) {
    s32 index;

    index = ((slot * 7) + actor->actorType) - 2;
    actorScriptStart(actor, gActorScriptIndexTable[index]);
}

extern u8 *gActorScriptAsset;

void actorScriptStart(Actor *actor, s32 scriptId) {
    ActorSub4 *state;
    u8 *base;

    state = actor->sub4;
    state->scriptCommand = NULL;
    state->scriptWaitFlags = 0;
    state->loopCount = 0;
    state->scriptResult = 0;
    state->waitFrame = 0.0f;
    if (scriptId == 0) {
        state->scriptStart = NULL;
        sScriptPc = NULL;
        sScriptContinueRunning = 0;
        return;
    }
    state->animId = scriptId;
    base = gActorScriptAsset;
    state->scriptStart = base + ((s32 *)base)[scriptId];
    state->scriptPc = state->scriptStart;
    sScriptPc = state->scriptStart;
}

void scriptReadU8(void *dst) {
    *(u8 *)dst = *sScriptPc++;
}

void scriptReadU16(void *dst) {
    dst = (u8 *)dst + 1;
    ((u8 *)dst)[-1] = *sScriptPc++;
    ((u8 *)dst)[0] = *sScriptPc++;
}

void scriptReadU24(void *dst) {
    dst = (u8 *)dst + 2;
    ((u8 *)dst)[-2] = *sScriptPc++;
    ((u8 *)dst)[-1] = *sScriptPc++;
    ((u8 *)dst)[0] = *sScriptPc++;
}

void scriptReadU32(void *dst) {
    dst = (u8 *)dst + 3;
    ((u8 *)dst)[-3] = *sScriptPc++;
    ((u8 *)dst)[-2] = *sScriptPc++;
    ((u8 *)dst)[-1] = *sScriptPc++;
    ((u8 *)dst)[0] = *sScriptPc++;
}

s32 scriptOpNop(Actor *actor) {
    sScriptPc++;
    return 1;
}

s32 scriptOpYield(Actor *actor) {
    sScriptPc++;
    return 0;
}

s32 scriptOpSetRegister(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actor->sub4->scriptResult = imm;
    return 1;
}

s32 scriptOpDecrementRegister(Actor *actor) {
    ActorSub4 *state;
    s32 reg;

    state = actor->sub4;
    reg = state->scriptResult;
    if (reg != 0) {
        state->scriptResult = reg - 1;
    }
    sScriptPc++;
    return 1;
}

s32 scriptOpWaitRegisterCountdown(Actor *actor) {
    ActorSub4 *state;
    s32 reg;

    state = actor->sub4;
    reg = state->scriptResult;
    if (reg != 0) {
        state->scriptResult = reg - 1;
        return 0;
    }
    sScriptPc++;
    return 1;
}

s32 scriptOpCheckSelectorActive(Actor *actor) {
    ActorSub4 *state;
    AnimSlot *value;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        value = state->layer;
    } else {
        value = state->model;
    }
    sScriptPc++;
    if ((value->speed != 0.0f) || ((value->speedTo != 0.0f) && (value->speedRampDuration != 0.0f))) {
        actor->sub4->scriptWaitFlags |= 1;
    }
    return 0;
}

s32 scriptOpSetCountdownFromByte(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    if (imm) {
        actor->sub4->loopCount = imm - 1;
        actor->sub4->scriptWaitFlags |= 2;
        return 0;
    }
    return 1;
}

s32 scriptOpSetRandomByteInRange(Actor *actor) {
    u8 pad;
    u8 min;
    u8 max;
    u8 val;

    sScriptPc++;
    scriptReadU8(&min);
    scriptReadU8(&max);
    val = (((randomNonNegative() >> 15) % 32767) % ((max - min) + 1)) + min;
    if (val != 0) {
        actor->sub4->loopCount = val - 1;
        actor->sub4->scriptWaitFlags |= 2;
        return 0;
    }
    return 1;
}

s32 scriptOpEnableFlag4(Actor *actor) {
    sScriptPc++;
    actor->sub4->scriptWaitFlags |= 4;
    return 0;
}

s32 scriptOpOrFlags(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actor->sub4->scriptWaitFlags |= imm;
    return 0;
}

s32 scriptOpSetRampTarget(Actor *actor) {
    f32 imm;

    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < 0.0f) {
        imm = (f32)actor->sub4->scriptResult;
    }
    actor->sub4->waitFrame = imm;
    actor->sub4->scriptWaitFlags |= 8;
    return 0;
}

s32 scriptOpApproachRampTarget(Actor *actor) {
    f32 imm;
    AnimSlot *value;

    if (actor->sub4->waitOnLayer != 0) {
        value = actor->sub4->layer;
    } else {
        value = actor->sub4->model;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < 0.0f) {
        imm = (f32)actor->sub4->scriptResult;
    }
    if ((actor->sub4->unk48 * value->speed) > 0.0f) {
        if (imm <= value->frame) {
            return 1;
        }
    } else if (value->frame <= imm) {
        return 1;
    }
    actor->sub4->waitFrame = imm;
    actor->sub4->scriptWaitFlags |= 8;
    return 0;
}

s32 scriptOpEnableValueState10(Actor *actor) {
    ActorSub4 *state;

    sScriptPc++;
    state = actor->sub4;
    if (state->blendFrom->clip != NULL) {
        state->scriptWaitFlags |= 0x10;
    }
    return 0;
}

s32 scriptOpStepRampValue(Actor *actor) {
    f32 imm;
    ActorSub4 *state;

    state = actor->sub4;
    sScriptPc++;
    scriptReadU32(&imm);
    if (state->blendFrom->clip != NULL) {
        if (imm < state->blendDuration) {
            state->blendDuration = imm;
            state->blendTime = state->blendDuration - (state->blendWeight * state->blendDuration);
        }
        actor->sub4->scriptWaitFlags |= 0x10;
    }
    return 0;
}

s32 scriptOpWaitRegisterNonZero(Actor *actor) {
    if (actor->sub4->scriptResult != 0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitRegisterZero(Actor *actor) {
    if (actor->sub4->scriptResult == 0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitValueZero(Actor *actor) {
    if (actor->sub4->layer->clip == NULL) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitValueEqual(Actor *actor) {
    ActorSub4 *state;

    state = actor->sub4;
    if (state->layerWeight == state->layerWeightTarget) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpSetActionVelocity(Actor *actor) {
    f32 imm;
    AnimSlot *action;

    if (actor->sub4->waitOnLayer != 0) {
        action = actor->sub4->layer;
    } else {
        action = actor->sub4->model;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < (f32)action->clip->frameCount) {
        action->firstFrame = imm;
    }
    return 1;
}

s32 scriptOpAccelerateAction(Actor *actor) {
    f32 imm;
    AnimSlot *action;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        action = state->layer;
    } else {
        action = state->model;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < action->clip->frameCount) {
        action->lastFrame = imm;
    }
    return 1;
}

s32 scriptOpApproachActionTarget(Actor *actor) {
    f32 imm;
    f32 imm2;
    AnimSlot *action;

    if (actor->sub4->waitOnLayer != 0) {
        action = actor->sub4->layer;
    } else {
        action = actor->sub4->model;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    scriptReadU32(&imm2);
    if (imm < action->clip->frameCount) {
        action->firstFrame = imm;
    }
    if (imm2 < action->clip->frameCount) {
        action->lastFrame = imm2;
    }
    return 1;
}

s32 func_806158E8(Actor *actor) {
    AnimSlot *action;
    ActorSub4 *state;
    AnimClip *resource;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        action = state->layer;
    } else {
        action = state->model;
    }
    resource = action->clip;
    sScriptPc++;
    action->firstFrame = 0.0f;
    action->lastFrame = (f32)(resource->frameCount - 1);
    action->flags = resource->flags;
    return 1;
}




s32 scriptOpAnimSetRemapDefault(Actor *actor) {
    s16 imm;
    sScriptPc++;
    scriptReadU16(&imm);
    controllerAnimSetStateIfChanged(actor, imm, 0.0f, 1.0f);
    return 1;
}

s32 scriptOpAnimSetRemapDirectDefault(Actor *actor) {
    s16 imm;
    sScriptPc++;
    scriptReadU16(&imm);
    controllerAnimSetStateRemapDirect(actor, imm, 0.0f, 1.0f);
    return 1;
}


s32 scriptOpAnimSetStateDefault(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    controllerAnimSetState(actor, imm, 0.0f, 0);
    return 1;
}
s32 scriptOpAnimSetRemapBlend(Actor *actor) {
    s16 imm;
    f32 imm2;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU32(&imm2);
    controllerAnimSetStateIfChanged(actor, imm, 0.0f, imm2);
    return 1;
}

s32 scriptOpAnimScaleInterpolate(Actor *actor) {
    s8 imm;
    sScriptPc++;
    scriptReadU8(&imm);
    controllerAnimScaleInterpolate(actor, imm);
    return 1;
}


s32 scriptOpAnimSetDirect(Actor *actor) {
    u16 imm;
    u8 imm2;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    controllerAnimSetDirect(actor, imm, 0.0f, imm2);
    return 1;
}

s32 scriptOpAnimSetStateRemap(Actor *actor) {
    s16 imm;
    sScriptPc++;
    scriptReadU16(&imm);
    controllerAnimSetStateRemap(actor, imm, 0.0f, 1.0f);
    return 1;
}

s32 scriptOpAnimSetStateRemapBlend(Actor *actor) {
    s16 imm;
    f32 imm2;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU32(&imm2);
    controllerAnimSetStateRemap(actor, imm, 0.0f, imm2);
    return 1;
}

s32 scriptOpAnimSetFromTable(Actor *actor) {
    u16 imm;
    u8 imm2;
    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    controllerAnimSetFromTable(actor, imm, 0.0f, imm2);
    return 1;
}


s32 scriptOpReadRampInterpolation(Actor *actor) {
    u8 imm;
    AnimSlot *value;
    AnimSlot *selected;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        value = state->layer;
    } else {
        value = state->model;
    }
    selected = value;
    sScriptPc++;
    scriptReadU8(&imm);
    if (imm == 0xFF) {
        imm = actor->sub4->scriptResult;
    }
    controllerApplyMotionWindow(actor, selected, (f32)imm);
    return 1;
}

extern u8 sMotionWindowProgress;

s32 func_80615CE4(Actor *actor) {
    u8 imm;
    void *selected;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        selected = state->layer;
    } else {
        selected = state->model;
    }
    sScriptPc++;
    scriptReadU8(&imm);
    controllerApplyMotionWindow(actor, selected, (f32)sMotionWindowProgress);
    if (sMotionWindowProgress != 0) {
        sMotionWindowProgress += imm;
    } else {
        sMotionWindowProgress = 0;
    }
    return 1;
}

s32 scriptOpUpdateMotionDelta(Actor *actor) {
    u8 imm;
    AnimSlot *motion;

    if (actor->sub4->waitOnLayer != 0) {
        motion = actor->sub4->layer;
    } else {
        motion = actor->sub4->model;
    }
    sScriptPc++;
    scriptReadU8(&imm);
    motion->jumpFrom = motion->frameIndex;
    motion->jumpTo = imm;
    motion->flags |= 8;
    if ((f32)motion->frameIndex < motion->frame) {
        motion->frameFrac = motion->frame - (f32)motion->frameIndex;
    } else {
        motion->frameFrac = -(motion->frame - (f32)motion->frameIndex);
    }
    motion->nextFrameIndex = imm;
    actor->sub4->scriptWaitFlags |= 0x20;
    return 1;
}

s32 scriptOpApplyMotionFriction(Actor *actor) {
    u8 imm;
    u8 imm2;
    AnimSlot *motion;
    f32 target;
    f32 currentF;
    s16 current;

    if (actor->sub4->waitOnLayer != 0) {
        motion = actor->sub4->layer;
    } else {
        motion = actor->sub4->model;
    }
    sScriptPc++;
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    current = motion->frameIndex;
    if ((u32)current == imm) {
        currentF = (f32)current;
        target = motion->frame;
        motion->jumpFrom = current;
        motion->jumpTo = imm2;
        motion->flags |= 8;
        if (currentF < target) {
            motion->frameFrac = target - currentF;
        } else {
            motion->frameFrac = -(target - currentF);
        }
        motion->nextFrameIndex = imm2;
        actor->sub4->scriptWaitFlags |= 0x20;
    } else {
        motion->frameIndex = (current + imm2) - imm;
        motion->nextFrameIndex = (motion->nextFrameIndex + imm2) - imm;
        motion->frame += imm2 - imm;
    }
    return 1;
}

s32 scriptOpSetMotionAngleFlags(Actor *actor) {
    s16 imm;
    AnimSlot *motion;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        motion = state->layer;
    } else {
        motion = state->model;
    }
    sScriptPc++;
    scriptReadU16(&imm);
    motion->flags |= imm;
    return 1;
}

s32 scriptOpClearMotionAngleFlags(Actor *actor) {
    s16 imm;
    AnimSlot *motion;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        motion = state->layer;
    } else {
        motion = state->model;
    }
    sScriptPc++;
    scriptReadU16(&imm);
    motion->flags &= ~imm;
    return 1;
}

s32 scriptOpScaleMotionVelocity(Actor *actor) {
    f32 start;
    f32 imm;
    AnimSlot *motion;

    motion = actor->sub4->waitOnLayer != 0
        ? actor->sub4->layer
        : actor->sub4->model;
    sScriptPc++;
    scriptReadU32(&imm);
    if (motion->clip != NULL) {
        start = motion->clip->speed;
    } else {
        start = .0f;
    }
    if (imm > 0.0f) {
        motion->speedRampDuration = imm;
        motion->speedTo = start;
        motion->speedRampTime = 0.0f;
        motion->speedFrom = motion->speed;
    } else {
        motion->speed = start;
        motion->speedRampDuration = 0.0f;
    }
    return 1;
}

s32 scriptOpAccelerateMotionVelocity(Actor *actor) {
    f32 imm;
    f32 imm2;
    AnimSlot *motion;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        motion = state->layer;
    } else {
        motion = state->model;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    scriptReadU32(&imm2);
    if (imm2 > 0.0f) {
        motion->speedRampDuration = imm2;
        motion->speedTo = imm;
        motion->speedFrom = motion->speed;
        motion->speedRampTime = 0.0f;
    } else {
        motion->speed = imm;
        motion->speedRampDuration = 0.0f;
    }
    return 1;
}

s32 scriptOpCapMotionVelocityMax(Actor *actor) {
    f32 speed;
    ActorSub4 *state;
    AnimSlot *motion;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        motion = state->layer;
    } else {
        motion = state->model;
    }
    sScriptPc++;
    speed = motion->speed;
    if (speed < 0.0f) {
        motion->speed = 0.0f - speed;
        if (motion->speedRampDuration != 0) {
            motion->speedTo = 0.0f - motion->speedTo;
            motion->speedFrom = 0.0f - motion->speedFrom;
        }
    }
    return 1;
}

s32 scriptOpCapMotionVelocityMin(Actor *actor) {
    ActorSub4 *state;
    AnimSlot *motion;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        motion = state->layer;
    } else {
        motion = state->model;
    }
    sScriptPc++;
    motion->speed = 0.0f - motion->speed;
    if (motion->speedRampDuration != 0) {
        motion->speedTo = 0.0f - motion->speedTo;
        motion->speedFrom = 0.0f - motion->speedFrom;
    }
    return 1;
}


s32 scriptOpSetActorRampTarget(Actor *actor) {
    f32 imm;
    f32 imm2;

    sScriptPc++;
    scriptReadU32(&imm);
    scriptReadU32(&imm2);
    scriptSetActorRampTarget(actor, imm, imm2);
    return 1;
}

s32 scriptOpCallScriptByIndex(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actorScriptStartByIndex(actor, imm);
    sScriptPc = actor->sub4->scriptPc;
    return sScriptContinueRunning;
}

s32 scriptOpGotoScript(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actorScriptStart(actor, imm);
    sScriptPc = actor->sub4->scriptPc;
    return sScriptContinueRunning;
}

s32 scriptOpEnableFlag8000(Actor *actor) {
    ActorSub4 *state;

    state = actor->sub4;
    state->scriptWaitFlags |= 0x8000;
    return 0;
}

s32 scriptOpResetRampVelocity(Actor *actor) {
    f32 imm;
    AnimSlot *value;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        value = state->layer;
    } else {
        value = state->model;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    actor->sub4->scriptResult = value->frame - imm;
    return 1;
}

s32 scriptOpCompareStateToU16(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actor->sub4->scriptResult = actor->state - imm;
    return 1;
}

s32 scriptOpCompareSubStateToU16(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actor->sub4->scriptResult = actor->unk155 - imm;
    return 1;
}

s32 func_80616518(Actor *actor) {
    u16 imm;
    AnimSlot *command;

    if (actor->sub4->waitOnLayer != 0) {
        command = actor->sub4->layer;
    } else {
        command = actor->sub4->model;
    }
    sScriptPc++;
    scriptReadU16(&imm);
    actor->sub4->scriptResult = command->animId - imm;
    return 1;
}

typedef struct GlobalCountdownView {
    u8 pad0[0x4E];
    s16 unk4E;
} GlobalCountdownView;

s32 scriptOpCompareGlobalCountdown(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actor->sub4->scriptResult =
        ((GlobalCountdownView *)gActivePlayerState)->unk4E - imm;
    return 1;
}

s32 scriptOpJump(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    sScriptPc = actor->sub4->scriptStart + imm;
    return 1;
}

s32 scriptOpJumpIfRegisterNonZero(Actor *actor) {
    s16 imm;
    ActorSub4 *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = actor->sub4;
    if (state->scriptResult != 0) {
        sScriptPc = state->scriptStart + imm;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterZero(Actor *actor) {
    s16 imm;
    ActorSub4 *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = actor->sub4;
    if (state->scriptResult == 0) {
        sScriptPc = state->scriptStart + imm;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterPositive(Actor *actor) {
    s16 imm;
    ActorSub4 *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = actor->sub4;
    if (state->scriptResult > 0) {
        sScriptPc = state->scriptStart + imm;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterNegative(Actor *actor) {
    s16 imm;
    ActorSub4 *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = actor->sub4;
    if (state->scriptResult < 0) {
        sScriptPc = state->scriptStart + imm;
    }
    return 1;
}

s32 scriptOpRestart(Actor *actor) {
    sScriptPc = actor->sub4->scriptStart;
    return 1;
}

s32 scriptOpJumpTable(Actor *actor) {
    s16 imm;

    sScriptPc += 1 + actor->sub4->scriptResult * 2;
    scriptReadU16(&imm);
    sScriptPc = actor->sub4->scriptStart + imm;
    return 1;
}

s32 scriptOpCallSaveReturn(Actor *actor) {
    s32 savedReg;
    u16 imm;
    ActorSub4 *state;

    savedReg = actor->sub4->scriptResult;
    state = actor->sub4;
    sScriptPc++;
    scriptReadU16(&imm);
    state->returnScriptId = state->animId;
    state->returnOffset = sScriptPc - state->scriptStart;
    actorScriptStart(actor, imm);
    sScriptPc = state->scriptPc;
    state->scriptResult = savedReg;
    return sScriptContinueRunning;
}

s32 scriptOpCall(Actor *actor) {
    u16 imm;
    ActorSub4 *state;

    state = actor->sub4;
    sScriptPc++;
    scriptReadU16(&imm);
    state->returnScriptId = state->animId;
    state->returnOffset = sScriptPc - state->scriptStart;
    actorScriptStartByIndex(actor, imm);
    sScriptPc = state->scriptPc;
    return sScriptContinueRunning;
}
s32 scriptOpReturn(Actor *actor) {
    s32 savedReg;
    ActorSub4 *state;

    savedReg = actor->sub4->scriptResult;
    state = actor->sub4;
    actorScriptStart(actor, state->returnScriptId);
    sScriptPc = state->scriptStart + state->returnOffset;
    state->returnScriptId = 0;
    state->returnOffset = 0;
    state->scriptResult = savedReg;
    return 1;
}

typedef void (*ScriptCommandFn)();

extern ScriptCommandFn sScriptCommandTable[];

s32 scriptOpRunCommand(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    sScriptCommandTable[imm](actor);
    return sScriptContinueRunning;
}

s32 scriptOpSetCommandHandler(Actor *actor) {
    s16 imm;
    ActorSub4 *state;
    state = actor->sub4;
    sScriptPc++;
    scriptReadU16(&imm);
    state->scriptCommand = sScriptCommandTable[imm];
    state->scriptCommandPc = sScriptPc;
    if (imm != 0) {
        state->scriptCommand(actor);
    }
    return sScriptContinueRunning;
}


s32 scriptOpPlaySoundOnFreeSlot(Actor *actor) {
    s16 imm;
    u8 imm2;
    s16 imm4;
    u8 imm5;
    u8 imm3;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU16(&imm4);
    scriptReadU8(&imm5);
    sfxPlayOnFreeSlot(imm, (s32)(((f64)imm2 * 32767.0) / 255.0), (f32)imm3,
                  (f32)((f64)imm4 / 127.0), (s32)imm5, 0);
    return 1;
}

s32 scriptOpSetActorState(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    actor->state = imm;
    actor->unk155 = 0;
    return 1;
}

s32 scriptOpIncrementActorState(Actor *actor) {
    sScriptPc++;
    actor->unk155 = 0;
    actor->state++;
    return 1;
}

s32 scriptOpSetActorSubState(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    actor->unk155 = imm;
    return 1;
}

s32 scriptOpIncrementActorSubState(Actor *actor) {
    sScriptPc++;
    actor->unk155++;
    return 1;
}

s32 scriptOpIncrementChildActorSubState(Actor *actor) {
    Actor *parent;

    sScriptPc++;
    parent = actor->parentActor;
    parent->unk155++;
    return 1;
}


s32 scriptOpSetRegisterRandom(Actor *actor) {
    u8 imm;
    u8 imm2;

    sScriptPc++;
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    actor->sub4->scriptResult = ((randomNonNegative() >> 15) % 32767) % ((imm2 - imm) + 1) + imm;
    return 1;
}

s32 scriptOpEnableFlag84(Actor *actor) {
    sScriptPc++;
    actor->sub4->waitOnLayer = 1;
    return 1;
}

s32 scriptOpDisableFlag84(Actor *actor) {
    sScriptPc++;
    actor->sub4->waitOnLayer = 0;
    return 1;
}

typedef struct ActorTargetView {
    u8 pad0[0x17C];
    void *unk17C;
} ActorTargetView;

typedef struct ScriptTarget {
    u8 pad0[0xD];
    u8 flags;
} ScriptTarget;

s32 scriptOpHalt(Actor *actor) {
    return 0;
}

s32 func_80616DB4(Actor *actor) {
    ScriptTarget *target;
    u8 flag;

    target = (ScriptTarget *)((ActorTargetView *)actor)->unk17C;
    sScriptPc++;
    scriptReadU8(&flag);
    target->flags |= flag;
    return 1;
}

typedef struct PlayerSlot {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    u8 pad22C[4];
    f32 unk230;
    u8 pad234[0x8C];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} PlayerSlot;

extern PlayerSlot *gPlayerSlots;



s32 scriptOpPlaySoundAndShake(Actor *actor) {
    s16 imm;
    volatile u8 imm2; // FAKE: volatile loads are not hoistable, keeps the 0xFF arm's lbu out of the bnez delay slot
    s16 imm3;
    u8 imm4;
    u8 priority;
    u8 pad;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU16(&imm3);
    scriptReadU8(&imm4);
    if (gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2) {
        priority = 0xA;
        if (imm == 1) {
            imm2 = (u32)((f64)(u32)imm2 * 0.5);
        }
        camStartShakeFromPoint(gActivePlayerState->camActor, 0xA, 8, actor->x, actor->y, actor->z, 100.0f, 800.0f);
    } else if (gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 0) {
        priority = 0xFF;
        imm2 = (u32)((f64)(u32)imm2 * 0.5);
    } else {
        switch (actor->actorType) {
        case 6:
        case 7:
            priority = 0x46;
            break;
        case 8:
            priority = 0x5A;
            break;
        case 2:
        case 4:
            priority = 0x32;
            break;
        default:
            priority = 0x50;
            break;
        }
    }
    if (actor && actor && actor) {} // FAKE: empty guard adds a block to as1's XBB window (limit 10), pushing the then-arm's lh/li hoists out
    if (actor && actor && actor) {} // FAKE: same (6 guards needed)
    if (actor && actor && actor) {} // FAKE: same
    if (actor && actor && actor) {} // FAKE: same
    if (actor && actor && actor) {} // FAKE: same
    if (actor && actor && actor) {} // FAKE: same
    imm = mapActionLookupEntry(imm, actor, actor->unk78[0]);
    if ((imm == 2) || (imm == 8)) {
        imm4 = 0xA;
    }
    sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, imm, (s32)imm2, (s32)imm3, (s32)imm4, (s32)priority, 0.3f, 0);
    return 1;
}

extern struct GfSndState *D_807457C8;


s32 func_80617140(Actor *actor) {
    s16 imm;
    s16 sound;
    u8 imm2;
    u8 imm3;
    u8 imm4;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    if (D_807457C8 != 0) {
        n_alSndpStop(D_807457C8);
        D_807457C8 = 0;
    }
    sound = mapActionLookupEntry(imm, actor, actor->unk78[0]);
    if (sound == 8) {
        imm4 = 4;
    }
    sfxPlayFromActorDirect(actor, sound, imm2, (f32)((f64)imm3 / 127.0),
                           (s32)imm4, 0x4B);
    return 1;
}

s32 scriptOpPlayPositionalSoundPlayerStateVolume(Actor *actor) {
    s16 imm;
    u8 imm2;
    u8 pad;
    u8 volume;
    s32 priority;

    volume = 0xFF;
    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    if (gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2) {
        priority = 0xA;
    } else if (gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 0) {
        priority = 0xFF;
        volume *= 0.5;
    } else {
        switch (actor->actorType) {
        case 6:
        case 7:
        case 8:
            priority = 0x5A;
            break;
        case 2:
        case 4:
            priority = 0x32;
            break;
        default:
            priority = 0x50;
            break;
        }
    }
    sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, imm, volume, 0x7F, imm2, priority, 0.3f, 0);
    return 1;
}


s32 func_80617400(Actor *actor) {
    s16 imm;
    u8 imm4;
    u8 imm5;
    u8 imm2;
    u8 imm3;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    scriptReadU8(&imm5);
    if (actor->flags & 4) {
        sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, imm, imm2, imm3, imm4, imm5, 0.3f, 0);
    }
    return 1;
}


s32 func_806174B4(Actor *actor) {
    f32 x;
    f32 y;
    f32 z;
    s16 imm;
    u8 imm4;
    s32 pad;
    u8 imm5;
    u8 imm7;
    u8 imm8;
    u8 imm2;
    u8 imm3;
    f32 imm6;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    scriptReadU8(&imm5);
    scriptReadU32(&imm6);
    scriptReadU8(&imm7);
    scriptReadU8(&imm8);
    if (actor->flags & 4) {
        if (imm7) {
            actorGetNodePos(actor, imm7, &x, &y, &z);
        } else {
            x = actor->x;
            y = actor->y;
            z = actor->z;
        }
        sfxPlayAtPositionPooled(x, y, z, imm, imm2, imm3, imm4, imm5, imm6, imm8);
    }
    return 1;
}


s32 scriptOpPlayDistanceVolumeSound(Actor *actor) {
    s16 imm;
    u8 imm4;
    u8 imm5;
    u8 imm2;
    u8 imm3;
    f32 volume;
    f64 val;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    scriptReadU8(&imm5);
    val = (((((f64)actor->sub4->scaleX / 0.4381361) * 200.0) + 55.0) * (f64)imm2) / 255;
    volume = (val > 255.0) ? 255.0 : val;
    sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, imm, (u32)volume, imm3, imm4, imm5, 0.3f, 0);
    return 1;
}

extern s16 *gActorScriptSoundTable;

void sfxPlayScriptActorSoundForPlayer(Actor *actor, s16 sound, u8 slot) {
    u8 pad0, pad1, pad2;
    u8 volume;
    s32 pitch;
    s32 priority;
    s32 index;
    index = (sound * 7 + actor->actorType - 2) & 0xFFFF;
    sound = gActorScriptSoundTable[index];
    volume = 0xFF;
    if (sound == 0) {
        if (gActivePlayerState->sfxHandle != 0) {
            n_alSndpStop(gActivePlayerState->sfxHandle);
        }
    }
    priority = gPlayerSlots[gActivePlayerState->playerIndex].unk2C0;
    pitch = 0x7F;
    if (priority == 2) {
        priority = 10;
    } else if (priority == 0) {
        priority = 80;
        volume *= 0.5;
    } else {
        if (actor->actorType == 2 || actor->actorType == 4) {
            priority = 50;
        } else {
            priority = 60;
        }
    }
    sfxPlayAtPositionForPlayer(actor->x, actor->y, actor->z, sound, volume, pitch, slot, priority, 0.3f);
}

extern u8 sScriptChannelIndexTable[];

s32 func_8061796C(Actor *actor) {
    s16 imm;
    u8 imm2;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    sfxPlayScriptActorSoundForPlayer(actor, imm, imm2);
    return 1;
}

s32 func_806179C0(Actor *actor) {
    s16 imm;
    u8 imm2;
    u8 imm4;
    u8 imm3;
    s8 imm5;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    scriptReadU8(&imm5);
    sfxStopSlotSound(actor, imm2);
    sfxPlayActorSound(actor, imm, imm4, 1, imm2, imm3, 1.0f, imm5);
    return 1;
}

s32 scriptOpSetSoundVolumeAndPan(Actor *actor) {
    f32 imm2;
    u8 imm3;
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    scriptReadU32(&imm2);
    scriptReadU8(&imm3);
    sfxSetVolumeAndPan(actor->soundSlots[imm], imm2, (f32)imm3);
    return 1;
}

s32 scriptOpStopSlotSound(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    sfxStopSlotSound(actor, imm);
    return 1;
}

s32 func_80617B38(Actor *actor) {
    s16 imm;
    u8 imm2;
    u8 imm3;
    s8 imm4;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    sfxPlayActorSound(actor, imm, imm3, 1, imm2, 0xFF, 1.0f, imm4);
    actor->unk72 = actor->sub4->model->animId;
    return 1;
}

s32 scriptOpAllocateSoundChannel(Actor *actor) {
    u8 imm;
    u8 imm2;

    sScriptPc++;
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    sfxAllocateChannel(sScriptChannelIndexTable[imm], (f32)((f64)imm2 / 255.0));
    return 1;
}

s32 scriptOpStopSoundChannel(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    sfxStopChannel(sScriptChannelIndexTable[imm], 0);
    return 1;
}

s32 scriptOpSetActorTextState(Actor *actor) {
    u16 imm;
    u8 imm2;

    sScriptPc++;
    scriptReadU16(&imm);
    scriptReadU8(&imm2);
    resQueueAttachActor(actor, imm, imm2);
    return 1;
}

s32 scriptOpNoopReturn1(Actor *actor) {
    return 1;
}

void func_80617D20(Actor *actor) {
    ActorSub4 *state;
    AnimSlot *value;

    state = actor->sub4;
    if (state->waitOnLayer != 0) {
        value = state->layer;
    } else {
        value = state->model;
    }
    scriptOpBranchOnCondition(actor, (s16)value->frame);
}

typedef struct ActorFlagsView {
    u8 pad0[0x146];
    s16 unk146;
} ActorFlagsView;

void scriptOpBranchByTimer8A(Actor *actor) {
    scriptOpBranchOnCondition(actor, actor->sub4->scriptResult);
}

void func_80617D94(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    while (imm != 0) {
        sScriptPc += 4;
        scriptReadU8(&imm);
    }
}

s32 scriptOpBranchOnCondition(Actor *actor, s16 value) {
    u8 imm;
    s16 imm2;
    s16 imm3;

    sScriptPc++;
    while (1) {
        scriptReadU8(&imm);
        scriptReadU16(&imm2);
        switch (imm) {
        case 0:
            sScriptPc -= 2;
            return 1;
        case 1:
            if (value == imm2) {
                scriptReadU16(&imm3);
                sScriptPc = actor->sub4->scriptStart + imm3;
                return 1;
            }
            break;
        case 2:
            if (value < imm2) {
                scriptReadU16(&imm3);
                sScriptPc = actor->sub4->scriptStart + imm3;
                return 1;
            }
            break;
        case 3:
            if (imm2 < value) {
                scriptReadU16(&imm3);
                sScriptPc = actor->sub4->scriptStart + imm3;
                return 1;
            }
            break;
        case 4:
            if (value == imm2) {
                scriptReadU16(&imm3);
                actor->sub4->scriptResult = imm3;
                func_80617D94(actor);
                return 1;
            }
            break;
        case 5:
            if (value < imm2) {
                scriptReadU16(&imm3);
                actor->sub4->scriptResult = imm3;
                func_80617D94(actor);
                return 1;
            }
            break;
        case 6:
            if (imm2 < value) {
                scriptReadU16(&imm3);
                actor->sub4->scriptResult = imm3;
                func_80617D94(actor);
                return 1;
            }
            break;
        case 7:
            scriptReadU16(&imm3);
            actor->sub4->scriptResult = imm3;
            func_80617D94(actor);
            return 1;
        }
        sScriptPc += 2;
    }
}

s32 scriptOpSetTimer(Actor *actor) {
    f32 imm;

    sScriptPc++;
    scriptReadU32(&imm);
    actor->sub4->scriptTimer = imm;
    return 1;
}

extern u32 gFrameDelta;

s32 scriptOpWaitTimer(Actor *actor) {
    f32 step;
    ActorSub4 *state;

    state = actor->sub4;
    if (state->motionFlags & 1) {
        step = (f32)gFrameDelta * 0.5f;
    } else {
        step = 1.0f;
    }
    state->scriptTimer -= step;
    if ((f64)actor->sub4->scriptTimer <= 0.0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

void scriptCmdNop(Actor *actor) {
}

typedef struct { u8 pad0[2]; u8 unk2; } ProjectileDataView;
extern f32 D_80753E48[];
extern s16 D_80753E64[];
extern Actor *gActivePlayerActor;
extern u8 gCurrentPlayerIndex;
extern ProjectileDataView *D_807FD568;
extern s16 gCurrentCharacterIndex;

void projectileTrySpawnFromSlot(Actor *actor) {
    f32 radius;
    f32 speed;
    f32 dz;
    f32 dx;
    PlayerState *playerState;
    s16 pad;
    s16 hitYaw;
    s16 hitPitch;
    s16 aimYaw;
    PlayerSlot *slot;

    playerState = actor->customState;
    slotQueueUpdate(4, 0, 0);
    if ((slotQueueGetValue(4, playerState->playerIndex) != 0) && (actorCountOwnedByClass(actor, 4, 0) < D_80753E64[gCurrentCharacterIndex])) {
        slotQueueAddValue(4, playerState->playerIndex, -1);
        speed = actor->sub4->scaleY * 2.6666667064030967;
        switch (actor->actorType) {
            case 2:
            case 6:
            case 7: radius = 30.0f; break;
            case 3:
            case 5: radius = 20.0f; break;
            default: radius = 30.0f; break;
        }
        if (collisionTestSphere(actor->x, actor->y + 30.0, actor->z, radius, &hitYaw, &hitPitch, 1, 0) != 0) {
            if (actor->state == 2) {
                slot = &((PlayerSlot *)gPlayerSlots)[gCurrentPlayerIndex]; // FAKE: no-op cast puts the base first in the addu (Q0323)
                aimYaw = mathAngleBetweenPoints2D(slot->unk228, slot->unk230, slot->unk210, slot->unk218);
            } else {
                aimYaw = actor->yaw;
            }
            if (mathAngleInArcWithMargin(hitYaw, hitPitch, aimYaw, 0) == 0) projectileSetSpawnFlag();
        }
        if (actor->state == 2) {
            projectileGetTargetCoords(gActivePlayerActor, 6);
            dz = gPlayerSlots[gCurrentPlayerIndex].unk230 - gPlayerSlots[gCurrentPlayerIndex].unk218;
            dx = gPlayerSlots[gCurrentPlayerIndex].unk228 - gPlayerSlots[gCurrentPlayerIndex].unk210;
            sqrtf((dz * dz) + (dx * dx));
            projectileSpawnNodeEntry(0x29, D_807FD568->unk2, speed, mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].unk228, gPlayerSlots[gCurrentPlayerIndex].unk230, gPlayerSlots[gCurrentPlayerIndex].unk210, gPlayerSlots[gCurrentPlayerIndex].unk218), D_80753E48[gCurrentCharacterIndex], 0.0f, actor);
            return;
        }
        projectileGetTargetCoords(actor, 7);
        projectileSpawnNodeEntry(0x29, D_807FD568->unk2, speed, actor->yaw, D_80753E48[gCurrentCharacterIndex], 0.0f, actor);
    }
}

extern u8 D_8071FE08[];
extern u8 D_8071FF18[];
extern s32 gGlobalPauseFlags;
extern f32 sSavedLightColorR;
extern f32 sSavedLightColorG;
extern f32 sSavedLightColorB;


void scriptCmdAttachToParentNode(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    effectSetCallback(effectDownwardDriftUpdate);
    effectSetMode(2);
    effectSetSpeed(actor->yaw);
    effectSetDepth(1);
    effectCreateAtActorBone(D_8071FF18, 0.4f, actor, imm, 0);
}

void scriptCmdEnablePlayerFlag40000(Actor *actor) {
    gActivePlayerState->stateFlags |= 0x40000;
}

void scriptCmdDetachFromParent(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    if (imm == 0xFF) {
        effectSetDepth(0);
        effectSetDuration(1);
        effectCreateAtPosition(D_8071FE08, 0.7f, actor->x, actor->y + 7.0f, actor->z);
    } else {
        effectSetCallback(effectUpwardDriftUpdate);
        effectSetMode(2);
        effectSetSpeed((actor->yaw + 0x800) & 0xFFF);
        effectSetDepth(1);
        effectSetFlags(0x80);
        effectCreateAtActorBone(D_8071FF18, 0.4f, actor, imm, 0);
    }
}

void scriptCmdSetActorInteractionTimer(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    effectSetCallback(effectSineDriftUpdate);
    effectSetMode(2);
    effectSetSpeed(actor->moveYaw);
    effectSetDepth(1);
    effectCreateAtActorBone(D_8071FF18, 0.4f, actor, imm, 0);
}

extern s32 gGlobalCutsceneFlags;
extern u8 D_8072006C;
extern u8 D_80720B58;

void scriptCmdSpawnAttachedActor(Actor *actor) {
    u8 imm;
    s16 i;

    scriptReadU8(&imm);
    if (gGlobalCutsceneFlags & 2) {
        for (i = 0; i < 0x14; i++) {
            effectSetDepth(1);
            effectSetDuration(-1);
            effectSetCallback(effectFloorFallUpdate);
            effectSetFlags(4);
            effectCreateAtActorBone(&D_80720B58, 0.1f, actor, imm, 0);
        }
        return;
    }
    sfxPlayFromActorWithAltitudeCheck(actor, 0x8A, 0x96, 0x7F, 0x32);
    effectSetSpeed((s32)actor);
    effectSetCallback(effectTimedLightIntensityFade);
    effectCreateAtActorBone(&D_8072006C, 0.4f, actor, imm, 2);
}

void scriptCmdSpawnBoneEffects(Actor *actor) {
    effectSetMaxDistance(0x7D0);
    effectSetMode(3);
    effectSpawnBone(actor, 0x16, 0.8f, 0.0f, 0.0f, 0.0f, -0x78);
    effectSetMaxDistance(0x7D0);
    effectSetMode(3);
    effectSpawnBone(actor, 0x17, 0.8f, 0.0f, 0.0f, 0.0f, -0x78);
}

void scriptCmdSetActorShadowScale(Actor *actor) {
    s16 imm;
    s16 imm2;

    scriptReadU16(&imm);
    scriptReadU16(&imm2);
}

void scriptCmdSetActorFlag146(Actor *actor) {
    s16 imm;

    scriptReadU16(&imm);
    ((ActorFlagsView *)actor)->unk146 |= imm;
}

void scriptCmdClearActorFlag146(Actor *actor) {
    s16 imm;

    scriptReadU16(&imm);
    ((ActorFlagsView *)actor)->unk146 &= ~imm;
}

void scriptCmdPlayActorSound(Actor *actor) {
    f32 imm;

    scriptReadU32(&imm);
}

typedef struct ActorScriptView {
    u8 pad0[0x178];
    void *unk178;
} ActorScriptView;

typedef struct {
    u8 pad0[0x64];
    s16 unk64;
} GlobalToggleView;

void scriptCmdCheckGlobalToggle(Actor *actor) {
    if (((GlobalToggleView *)gActivePlayerState)->unk64 != 0) {
        ((GlobalToggleView *)gActivePlayerState)->unk64 = 0;
        actor->sub4->scriptResult = 0;
        return;
    }
    actor->sub4->scriptResult = 1;
}

void scriptCmdCheckFalling(Actor *actor) {
    if (actor->speedY < 0.0f) {
        actor->sub4->scriptResult = 1;
        return;
    }
    actor->sub4->scriptResult = 0;
}

void scriptCmdResetActorScale(Actor *actor) {
    if ((actor->contactFlags & actor->prevContactFlags & 1) != 0) {
        actor->sub4->scriptResult = 1;
        return;
    }
    actor->sub4->scriptResult = 0;
}

void scriptCmdSetActorSpeedY(Actor *actor) {
    s16 value;

    scriptReadU16(&value);
    actor->speedY = (f32)value;
}

void scriptCmdSetActorAccelY(Actor *actor) {
    f32 value;

    scriptReadU32(&value);
    actor->accelY = value;
}

extern u8 gGameMode;

void scriptCmdActorCamShake(Actor *actor) {
    f32 x;
    f32 y;
    f32 z;
    s16 imm3;
    s16 imm4;
    u8 imm2;
    u8 imm;
    s32 type;
    s32 duration;

    actorGetNodePosOrPosition(actor, &x, &y, &z);
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    scriptReadU16(&imm3);
    scriptReadU16(&imm4);
    imm2 = (u32)((f64)imm2 * ((f64)actor->sub4->scaleY / 0.15));
    type = actor->actorType;
    if ((type == 0xCC) || ((actor->contactFlags & 1) && ((actor->flags & 4) || (type == 0xE4)) && (gGameMode != 1))) {
        duration = (imm2 >= 21) ? 20 : imm2;
        camStartShakeFromPoint(gActivePlayerState->camActor, imm, duration, x, y, z, (f32)imm3, (f32)imm4);
    }
}
void scriptCmdSetActorAlpha(Actor *actor) {
    f32 x;
    f32 y;
    f32 z;
    s16 imm3;
    s16 imm4;
    u8 imm2;
    u8 imm;

    actorGetNodePosOrPosition(actor, &x, &y, &z);
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    scriptReadU16(&imm3);
    scriptReadU16(&imm4);
    camStartShakeFromPoint(gActivePlayerState->camActor, imm, imm2, x, y, z, (f32)imm3, (f32)imm4);
}


typedef struct GlobalTimerView {
    u8 pad0[0xCA];
    u8 unkCA;
} GlobalTimerView;

void func_80618C00(Actor *actor, u8 node) {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;

    scale = 0.04f;
    actorGetNodePos(actor, node, &x, &y, &z);
    if ((actor->actorType == 6) || (actor->actorType == 7)) {
        scale = 0.1f;
    }
    actorSpawnEffectChild(x, actor->floorY, z, 0.03f, scale, actor, 0);
}

void scriptCmdSpawnActorParticleBurst(Actor *actor) {
    u8 node;

    if (actor->actorType == 2) {
        node = 2;
    } else {
        node = 8;
    }
    func_80618C00(actor, node);
    ((GlobalTimerView *)gActivePlayerState)->unkCA = 0x28;
}

void scriptCmdSetActorNodeFlag(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    if (imm & 0x80) {
        actor->interactionType = (s16)(imm & 0x7F);
        return;
    }
    actorSetNodeFlag(actor, imm);
}

void scriptCmdClearActorNodeFlag(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    if (imm & 0x80) {
        actor->interactionType = (s16)(imm & 0x7F);
        return;
    }
    actorClearNodeFlag(actor, imm);
}

extern void *sScriptEffectSprites[];

void scriptCmdSpawnOrbitEffects(Actor *actor) {
    s32 i;
    u8 imm;
    u8 imm2;

    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    for (i = imm; i < imm2; i++) {
        effectSetCallback(effectOrbitSourceUpdate);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetAngle(1);
        effectSetSpeed(1);
        effectSetFlags(0x20);
        effectCreateAtActorBone(sScriptEffectSprites[i], 0.2f, actor, 7, 0);
    }
}

void scriptCmdToggleActorVisibility(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    if (imm != 0) {
        actor->flags &= 0xBFFFFFFF;
        gGlobalPauseFlags |= 0x10030;
    } else {
        actor->flags |= 0x40000000;
        gGlobalPauseFlags &= 0xFFFEFFCF;
        playerClearPitchRollFlags(actor);
    }
}

extern s16 sCharacterBehaviorMap[];

void scriptCmdSpawnCharacterCompanion(Actor *actor) {
    u8 *script;

    actorSpawn(0x135, sCharacterBehaviorMap[actor->actorType]);
    actorCopyPoseAndScale(gSpawnedActor, actor, actor->sub4->scaleX);
    gSpawnedActor->roll = actor->roll;
    gSpawnedActor->pitch = actor->pitch;
    script = gSpawnedActor->customState;
    scriptReadU8(script + 6);
}

void scriptCmdSpawnSmokeRing(Actor *actor) {
    u8 imm;
    Actor *ring;

    scriptReadU8(&imm);
    if (imm != 0) {
        actorSpawn(0x136, 0xA8);
        actorCopyPoseAndScale(gSpawnedActor, actor, actor->sub4->scaleX);
        gActivePlayerState->actor = gSpawnedActor;
    } else {
        ring = gActivePlayerState->actor;
        if ((ring != NULL) && (ring->actorType == 0x136)) {
            actorDespawn(ring);
            gActivePlayerState->actor = NULL;
        }
    }
}

void scriptCmdSpawnSplashPuff(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    if (imm != 0) {
        if (actor->chunkIndex != -1) {
            lightGetColor(&sSavedLightColorR, &sSavedLightColorG, &sSavedLightColorB, actor->chunkIndex);
            lightSetColor(107.0f, 48.0f, 80.0f, actor->chunkIndex);
        }
    } else if (actor->chunkIndex != -1) {
        lightSetColor(((f32 *)&sSavedLightColorR)[0], ((f32 *)&sSavedLightColorR)[1], ((f32 *)&sSavedLightColorR)[2], actor->chunkIndex);
    }
}

typedef struct FallingEffectView {
    u8 pad0[0x35C];
    s32 unk35C;
} FallingEffectView;

extern u8 D_80750AD0;
extern void (*sScriptEffectCallbacks[])(void);

void scriptCmdSpawnFallingEffect(Actor *actor) {
    u16 imm;
    u16 imm2;
    u8 imm3;
    u8 imm4;
    s8 imm5;
    u8 imm6;
    s16 imm7;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    FallingEffectView *effect;
    u8 freed;
    u8 node;

    scriptReadU16(&imm);
    scriptReadU16(&imm2);
    scriptReadU8(&imm3);
    scriptReadU8(&imm4);
    scriptReadU8(&imm5);
    scriptReadU8(&imm6);
    scriptReadU16(&imm7);
    if (D_80750AD0 == 0) {
        scale = imm2 * 0.00048828125f;
        effectSetDepth(1);
        effectSetMode(imm3);
        effectSetDuration(imm7);
        node = imm4;
        if (node == 0) {
            x = actor->x;
            y = actor->y;
            z = actor->z;
        } else {
            actorGetNodePos(actor, node, &x, &y, &z);
        }
        y += (f32)imm5 * scale;
        if (imm6 != 0) {
            effectSetCallback(sScriptEffectCallbacks[imm6]);
        }
        effect = effectCreateAtPosition(sScriptEffectSprites[imm], scale, x, y, z);
        freed = 0;
        switch (imm6) {
            case 1:
                effectFallStateInit(actor, effect, &freed);
                break;
            case 2:
                effect->unk35C = 1;
                break;
            case 4:
                effect->unk35C = -50 - ((randomNonNegative() >> 15) % 50);
                break;
        }
        if (freed != 0) {
            effectFreeAndUnlink(effect);
        }
    }
}

typedef struct ChildEffectNodeState {
    s16 unk0;
    s16 unk2;
    Actor *parent;
    s32 parentInstanceId;
    s16 parentAnimId;
    u8 padE[2];
    f32 yOffset;
} ChildEffectNodeState;

void scriptCmdSpawnEffectChildAndNode(Actor *actor) {
    u16 imm;
    u16 imm2;
    u16 imm3;
    u16 imm4;
    f32 scale;
    ChildEffectNodeState *node;

    scale = actor->sub4->scaleY / 0.15;
    scriptReadU16(&imm);
    scriptReadU16(&imm2);
    scriptReadU16(&imm3);
    scriptReadU16(&imm4);
    actorSpawn(0x139, imm3);
    actorCopyPoseAndScale(gSpawnedActor, actor, actor->sub4->scaleX);
    gSpawnedActor->yaw = actor->yaw;
    gSpawnedActor->roll = actor->roll;
    gSpawnedActor->pitch = actor->pitch;
    node = (ChildEffectNodeState *)gSpawnedActor->customState;
    node->yOffset = 0.0f;
    if (imm != 0xFFFF) {
        effectSetDuration(-1);
        effectSetDepth(1);
        switch (actor->actorType) {
            default:
                scale *= 0.2;
                break;
            case 0xBB:
                scale *= 0.4;
                effectSetColor(0, 0xFF, 0, 0xFF);
                break;
            case 4:
            case 5:
                effectSetMode(0);
                scale *= 0.18;
                node->yOffset = -1.4f;
                break;
            case 3:
                effectSetMode(0);
                scale *= 0.25;
                node->yOffset = -1.4f;
                break;
        }
    }
    gSpawnedActor->y -= node->yOffset;
    if (imm != 0xFFFF) {
        effectCreateAtActorBone(sScriptEffectSprites[imm], scale, gSpawnedActor, 1, 2);
    }
    node->unk0 = imm2;
    node->parent = actor;
    node->parentInstanceId = actor->instanceId;
    node->parentAnimId = actor->sub4->animId;
    node->unk2 = imm4;
}

void scriptCmdDespawnActor(Actor *actor) {
    actorDespawn(actor);
}

void *func_80619520(Actor *actor) {
    void *result;

    result = NULL;
    if (actor->actorType == 0x134) {
        result = ((ActorScriptView *)actor)->unk178;
    }
    return result;
}

void scriptCmdSetActorResultByte35(Actor *actor) {
    u8 value;
    u8 *result;

    result = func_80619520(actor);
    scriptReadU8(&value);
    if (result != NULL) {
        result[0x35] = value;
    }
}

void scriptCmdIncrementActorResultByte35(Actor *actor) {
    u8 *result;

    result = func_80619520(actor);
    if (result != NULL) {
        result[0x35]++;
    }
}

void scriptCmdCheckSlopePitch(Actor *actor) {
    actor->sub4->scriptResult = actor->floorSlopePitch >= 0x3DA;
}
