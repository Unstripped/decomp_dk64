#include "common.h"
#include "actor.h"
#define PROTO_SKIP_effectCreateAtActorBone // FAKE: callee prototype steer
#define PROTO_SKIP_effectCreateAtPosition // PROTO: Reference of an expression of void type or an incomplete typ
#define PROTO_SKIP_effectSetColor // FAKE: callee prototype steer
#define PROTO_SKIP_effectSetMode // FAKE: callee prototype steer
#define PROTO_SKIP_mathAngleInArcWithMargin // PROTO: Reference of an expression of void type or an incomplete typ
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

typedef struct ActorRampState {
    u8 pad0[0x48];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
} ActorRampState;

void scriptSetActorRampTarget(Actor *actor, f32 targetVal, f32 rampTime) {
    ActorRampState *ramp;

    ramp = (ActorRampState *)actor->sub4;
    if (rampTime > 0.0f) {
        ramp->unk58 = rampTime;
        ramp->unk50 = targetVal;
        ramp->unk54 = 0.0f;
        ramp->unk4C = ramp->unk48;
        return;
    }
    ramp->unk48 = targetVal;
    ramp->unk58 = 0.0f;
}

typedef struct RampValue {
    u8 pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} RampValue;

typedef struct RampValueHolder {
    RampValue *unk0;
} RampValueHolder;

void scriptSetRampValue(Actor *actor, f32 target, f32 rampTime) {
    RampValue *ramp;

    ramp = ((RampValueHolder *)actor->sub4)->unk0;
    if (rampTime > 0.0f) {
        ramp->unk34 = rampTime;
        ramp->unk2C = target;
        ramp->unk30 = 0.0f;
        ramp->unk28 = ramp->unk24;
        return;
    }
    ramp->unk24 = target;
    ramp->unk34 = 0.0f;
}

extern s32 sScriptContinueRunning;
typedef s32 (*ActorScriptCommand)(Actor *);
extern ActorScriptCommand sScriptOpcodeTable[];

typedef struct ActorScriptState {
    u8 pad0[0x68];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    u8 *unk74;
    s32 unk78;
} ActorScriptState;

void actorScriptExecute(Actor *actor) {
    ActorScriptState *state;

    state = (ActorScriptState *)actor->sub4;
    if (state->unk68 != NULL) {
        sScriptContinueRunning = 1;
        sScriptPc = state->unk6C;
        while ((state->unk78 == 0) && (sScriptContinueRunning != 0)) {
            sScriptContinueRunning = sScriptOpcodeTable[*sScriptPc](actor);
        }
        state->unk6C = sScriptPc;
        if (state->unk70 != NULL) {
            sScriptPc = state->unk74;
            state->unk70(actor);
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

typedef struct ScriptLoadState {
    u8 pad0[0x64];
    s16 unk64;
    u8 pad66[2];
    u8 *unk68;
    u8 *unk6C;
    s32 unk70;
    u8 pad74[4];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    u8 pad84[4];
    s32 unk88;
} ScriptLoadState;

void actorScriptStart(Actor *actor, s32 scriptId) {
    ScriptLoadState *state;
    u8 *base;

    state = (ScriptLoadState *)actor->sub4;
    state->unk70 = 0;
    state->unk78 = 0;
    state->unk7C = 0;
    state->unk88 = 0;
    state->unk80 = 0.0f;
    if (scriptId == 0) {
        state->unk68 = NULL;
        sScriptPc = NULL;
        sScriptContinueRunning = 0;
        return;
    }
    state->unk64 = scriptId;
    base = gActorScriptAsset;
    state->unk68 = base + ((s32 *)base)[scriptId];
    state->unk6C = state->unk68;
    sScriptPc = state->unk68;
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

typedef struct ScriptState {
    u8 pad0[0x78];
    s32 flags;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s32 unk88;
} ScriptState;

s32 scriptOpSetRegister(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    ((ScriptState *)actor->sub4)->unk88 = imm;
    return 1;
}

s32 scriptOpDecrementRegister(Actor *actor) {
    ScriptState *state;
    s32 reg;

    state = (ScriptState *)actor->sub4;
    reg = state->unk88;
    if (reg != 0) {
        state->unk88 = reg - 1;
    }
    sScriptPc++;
    return 1;
}

s32 scriptOpWaitRegisterCountdown(Actor *actor) {
    ScriptState *state;
    s32 reg;

    state = (ScriptState *)actor->sub4;
    reg = state->unk88;
    if (reg != 0) {
        state->unk88 = reg - 1;
        return 0;
    }
    sScriptPc++;
    return 1;
}

typedef struct ScriptSelectorValue {
    u8 pad0[0x24];
    f32 unk24;
    u8 pad28[4];
    f32 unk2C;
    u8 pad30[4];
    f32 unk34;
} ScriptSelectorValue;

typedef struct ScriptSelectorState {
    ScriptSelectorValue *unk0;
    ScriptSelectorValue *unk4;
    u8 pad8[0x70];
    s32 unk78;
    u8 pad7C[8];
    s32 unk84;
} ScriptSelectorState;

s32 scriptOpCheckSelectorActive(Actor *actor) {
    ScriptSelectorState *state;
    ScriptSelectorValue *value;

    state = (ScriptSelectorState *)actor->sub4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    sScriptPc++;
    if ((value->unk24 != 0.0f) || ((value->unk2C != 0.0f) && (value->unk34 != 0.0f))) {
        ((ScriptSelectorState *)actor->sub4)->unk78 |= 1;
    }
    return 0;
}

s32 scriptOpSetCountdownFromByte(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    if (imm) {
        ((ScriptState *)actor->sub4)->unk7C = imm - 1;
        ((ScriptState *)actor->sub4)->flags |= 2;
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
        ((ScriptState *)actor->sub4)->unk7C = val - 1;
        ((ScriptState *)actor->sub4)->flags |= 2;
        return 0;
    }
    return 1;
}

s32 scriptOpEnableFlag4(Actor *actor) {
    sScriptPc++;
    ((ScriptState *)actor->sub4)->flags |= 4;
    return 0;
}

s32 scriptOpOrFlags(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    ((ScriptState *)actor->sub4)->flags |= imm;
    return 0;
}

typedef struct ScriptRateState {
    u8 pad0[0x78];
    s32 unk78;
    u8 pad7C[4];
    f32 unk80;
    s32 unk84;
    s32 unk88;
} ScriptRateState;

s32 scriptOpSetRampTarget(Actor *actor) {
    f32 imm;

    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < 0.0f) {
        imm = (f32)((ScriptRateState *)actor->sub4)->unk88;
    }
    ((ScriptRateState *)actor->sub4)->unk80 = imm;
    ((ScriptRateState *)actor->sub4)->unk78 |= 8;
    return 0;
}

typedef struct ScriptValue {
    void *unk0;
    f32 unk4;
    u8 pad8[0x1C];
    f32 unk24;
} ScriptValue;

typedef struct ScriptValueState {
    ScriptValue *unk0;
    ScriptValue *unk4;
    s32 *unk8;
    u8 padC[4];
    f32 unk10;
    u8 pad14[0x10];
    f32 unk24;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    u8 pad2E[0x12];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0x2C];
    s32 unk78;
    u8 pad7C[4];
    f32 unk80;
    s32 unk84;
    s32 unk88;
} ScriptValueState;

s32 scriptOpApproachRampTarget(Actor *actor) {
    f32 imm;
    ScriptValue *value;

    if (((ScriptValueState *)actor->sub4)->unk84 != 0) {
        value = ((ScriptValueState *)actor->sub4)->unk4;
    } else {
        value = ((ScriptValueState *)actor->sub4)->unk0;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < 0.0f) {
        imm = (f32)((ScriptValueState *)actor->sub4)->unk88;
    }
    if ((((ScriptValueState *)actor->sub4)->unk48 * value->unk24) > 0.0f) {
        if (imm <= value->unk4) {
            return 1;
        }
    } else if (value->unk4 <= imm) {
        return 1;
    }
    ((ScriptValueState *)actor->sub4)->unk80 = imm;
    ((ScriptValueState *)actor->sub4)->unk78 |= 8;
    return 0;
}

s32 scriptOpEnableValueState10(Actor *actor) {
    ScriptValueState *state;

    sScriptPc++;
    state = (ScriptValueState *)actor->sub4;
    if (*state->unk8 != 0) {
        state->unk78 |= 0x10;
    }
    return 0;
}

s32 scriptOpStepRampValue(Actor *actor) {
    f32 imm;
    ScriptValueState *state;

    state = (ScriptValueState *)actor->sub4;
    sScriptPc++;
    scriptReadU32(&imm);
    if (*state->unk8 != 0) {
        if (imm < state->unk44) {
            state->unk44 = imm;
            state->unk40 = state->unk44 - (state->unk10 * state->unk44);
        }
        ((ScriptValueState *)actor->sub4)->unk78 |= 0x10;
    }
    return 0;
}

s32 scriptOpWaitRegisterNonZero(Actor *actor) {
    if (((ScriptValueState *)actor->sub4)->unk88 != 0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitRegisterZero(Actor *actor) {
    if (((ScriptValueState *)actor->sub4)->unk88 == 0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitValueZero(Actor *actor) {
    if (((ScriptValueState *)actor->sub4)->unk4->unk0 == 0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitValueEqual(Actor *actor) {
    ScriptValueState *state;

    state = (ScriptValueState *)actor->sub4;
    if (state->unk28 == state->unk2C) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

typedef struct ScriptActionResource {
    u8 pad0[0x12];
    u8 unk12;
} ScriptActionResource;

typedef struct ScriptActionView {
    ScriptActionResource *unk0;
    u8 pad4[0x10];
    f32 unk14;
} ScriptActionView;

s32 scriptOpSetActionVelocity(Actor *actor) {
    f32 imm;
    ScriptActionView *action;

    if (((ScriptValueState *)actor->sub4)->unk84 != 0) {
        action = (ScriptActionView *)((ScriptValueState *)actor->sub4)->unk4;
    } else {
        action = (ScriptActionView *)((ScriptValueState *)actor->sub4)->unk0;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < (f32)action->unk0->unk12) {
        action->unk14 = imm;
    }
    return 1;
}

typedef struct ScriptActionResourceInfo {
    u8 pad0[4];
    u16 unk4;
    u8 pad6[0xC];
    u8 unk12;
} ScriptActionResourceInfo;

typedef struct ScriptActionInfo {
    ScriptActionResourceInfo *unk0;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} ScriptActionInfo;

typedef struct ScriptActionInfoState {
    ScriptActionInfo *unk0;
    ScriptActionInfo *unk4;
    u8 pad8[0x7C];
    s32 unk84;
} ScriptActionInfoState;

s32 scriptOpAccelerateAction(Actor *actor) {
    f32 imm;
    ScriptActionInfo *action;
    ScriptActionInfoState *state;

    state = (ScriptActionInfoState *)actor->sub4;
    if (state->unk84 != 0) {
        action = state->unk4;
    } else {
        action = state->unk0;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    if (imm < action->unk0->unk12) {
        action->unk18 = imm;
    }
    return 1;
}

s32 scriptOpApproachActionTarget(Actor *actor) {
    f32 imm;
    f32 imm2;
    ScriptActionInfo *action;

    if (((ScriptActionInfoState *)actor->sub4)->unk84 != 0) {
        action = ((ScriptActionInfoState *)actor->sub4)->unk4;
    } else {
        action = ((ScriptActionInfoState *)actor->sub4)->unk0;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    scriptReadU32(&imm2);
    if (imm < action->unk0->unk12) {
        action->unk14 = imm;
    }
    if (imm2 < action->unk0->unk12) {
        action->unk18 = imm2;
    }
    return 1;
}

s32 func_806158E8(Actor *actor) {
    ScriptActionInfo *action;
    ScriptActionInfoState *state;
    ScriptActionResourceInfo *resource;

    state = (ScriptActionInfoState *)actor->sub4;
    if (state->unk84 != 0) {
        action = state->unk4;
    } else {
        action = state->unk0;
    }
    resource = action->unk0;
    sScriptPc++;
    action->unk14 = 0.0f;
    action->unk18 = (f32)(resource->unk12 - 1);
    action->unk1C = resource->unk4;
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
    ScriptValue *value;
    ScriptValue *selected;
    ScriptValueState *state;

    state = (ScriptValueState *)actor->sub4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    selected = value;
    sScriptPc++;
    scriptReadU8(&imm);
    if (imm == 0xFF) {
        imm = ((ScriptValueState *)actor->sub4)->unk88;
    }
    controllerApplyMotionWindow(actor, selected, (f32)imm);
    return 1;
}

extern u8 sMotionWindowProgress;

s32 func_80615CE4(Actor *actor) {
    u8 imm;
    void *selected;
    ScriptValueState *state;

    state = (ScriptValueState *)actor->sub4;
    if (state->unk84 != 0) {
        selected = state->unk4;
    } else {
        selected = state->unk0;
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

typedef struct ScriptMotion {
    f32 *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    u8 pad10[0xC];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 pad22[2];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} ScriptMotion;

typedef struct ScriptMotionState {
    ScriptMotion *unk0;
    ScriptMotion *unk4;
    u8 pad8[0x70];
    s32 unk78;
    u8 pad7C[8];
    s32 unk84;
} ScriptMotionState;

s32 scriptOpUpdateMotionDelta(Actor *actor) {
    u8 imm;
    ScriptMotion *motion;

    if (((ScriptMotionState *)actor->sub4)->unk84 != 0) {
        motion = ((ScriptMotionState *)actor->sub4)->unk4;
    } else {
        motion = ((ScriptMotionState *)actor->sub4)->unk0;
    }
    sScriptPc++;
    scriptReadU8(&imm);
    motion->unk1E = motion->unkC;
    motion->unk20 = imm;
    motion->unk1C |= 8;
    if ((f32)motion->unkC < motion->unk4) {
        motion->unk8 = motion->unk4 - (f32)motion->unkC;
    } else {
        motion->unk8 = -(motion->unk4 - (f32)motion->unkC);
    }
    motion->unkE = imm;
    ((ScriptMotionState *)actor->sub4)->unk78 |= 0x20;
    return 1;
}

s32 scriptOpApplyMotionFriction(Actor *actor) {
    u8 imm;
    u8 imm2;
    ScriptMotion *motion;
    f32 target;
    f32 currentF;
    s16 current;

    if (((ScriptMotionState *)actor->sub4)->unk84 != 0) {
        motion = ((ScriptMotionState *)actor->sub4)->unk4;
    } else {
        motion = ((ScriptMotionState *)actor->sub4)->unk0;
    }
    sScriptPc++;
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    current = motion->unkC;
    if ((u32)current == imm) {
        currentF = (f32)current;
        target = motion->unk4;
        motion->unk1E = current;
        motion->unk20 = imm2;
        motion->unk1C |= 8;
        if (currentF < target) {
            motion->unk8 = target - currentF;
        } else {
            motion->unk8 = -(target - currentF);
        }
        motion->unkE = imm2;
        ((ScriptMotionState *)actor->sub4)->unk78 |= 0x20;
    } else {
        motion->unkC = (current + imm2) - imm;
        motion->unkE = (motion->unkE + imm2) - imm;
        motion->unk4 += imm2 - imm;
    }
    return 1;
}

typedef struct ScriptMotionFlagsView {
    u8 pad0[0x1C];
    s16 unk1C;
} ScriptMotionFlagsView;

typedef struct ScriptMotionFlagsState {
    ScriptMotionFlagsView *unk0;
    ScriptMotionFlagsView *unk4;
    u8 pad8[0x7C];
    s32 unk84;
} ScriptMotionFlagsState;

s32 scriptOpSetMotionAngleFlags(Actor *actor) {
    s16 imm;
    ScriptMotionFlagsView *motion;
    ScriptMotionFlagsState *state;

    state = (ScriptMotionFlagsState *)actor->sub4;
    if (state->unk84 != 0) {
        motion = state->unk4;
    } else {
        motion = state->unk0;
    }
    sScriptPc++;
    scriptReadU16(&imm);
    motion->unk1C |= imm;
    return 1;
}

s32 scriptOpClearMotionAngleFlags(Actor *actor) {
    s16 imm;
    ScriptMotionFlagsView *motion;
    ScriptMotionFlagsState *state;

    state = (ScriptMotionFlagsState *)actor->sub4;
    if (state->unk84 != 0) {
        motion = state->unk4;
    } else {
        motion = state->unk0;
    }
    sScriptPc++;
    scriptReadU16(&imm);
    motion->unk1C &= ~imm;
    return 1;
}

s32 scriptOpScaleMotionVelocity(Actor *actor) {
    f32 start;
    f32 imm;
    ScriptMotion *motion;

    motion = ((ScriptMotionState *)actor->sub4)->unk84 != 0
        ? ((ScriptMotionState *)actor->sub4)->unk4
        : ((ScriptMotionState *)actor->sub4)->unk0;
    sScriptPc++;
    scriptReadU32(&imm);
    if (motion->unk0 != NULL) {
        start = *motion->unk0;
    } else {
        start = .0f;
    }
    if (imm > 0.0f) {
        motion->unk34 = imm;
        motion->unk2C = start;
        motion->unk30 = 0.0f;
        motion->unk28 = motion->unk24;
    } else {
        motion->unk24 = start;
        motion->unk34 = 0.0f;
    }
    return 1;
}

s32 scriptOpAccelerateMotionVelocity(Actor *actor) {
    f32 imm;
    f32 imm2;
    ScriptMotion *motion;
    ScriptMotionState *state;

    state = (ScriptMotionState *)actor->sub4;
    if (state->unk84 != 0) {
        motion = state->unk4;
    } else {
        motion = state->unk0;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    scriptReadU32(&imm2);
    if (imm2 > 0.0f) {
        motion->unk34 = imm2;
        motion->unk2C = imm;
        motion->unk28 = motion->unk24;
        motion->unk30 = 0.0f;
    } else {
        motion->unk24 = imm;
        motion->unk34 = 0.0f;
    }
    return 1;
}

s32 scriptOpCapMotionVelocityMax(Actor *actor) {
    f32 speed;
    ScriptMotionState *state;
    ScriptMotion *motion;

    state = (ScriptMotionState *)actor->sub4;
    if (state->unk84 != 0) {
        motion = state->unk4;
    } else {
        motion = state->unk0;
    }
    sScriptPc++;
    speed = motion->unk24;
    if (speed < 0.0f) {
        motion->unk24 = 0.0f - speed;
        if (motion->unk34 != 0) {
            motion->unk2C = 0.0f - motion->unk2C;
            motion->unk28 = 0.0f - motion->unk28;
        }
    }
    return 1;
}

s32 scriptOpCapMotionVelocityMin(Actor *actor) {
    ScriptMotionState *state;
    ScriptMotion *motion;

    state = (ScriptMotionState *)actor->sub4;
    if (state->unk84 != 0) {
        motion = state->unk4;
    } else {
        motion = state->unk0;
    }
    sScriptPc++;
    motion->unk24 = 0.0f - motion->unk24;
    if (motion->unk34 != 0) {
        motion->unk2C = 0.0f - motion->unk2C;
        motion->unk28 = 0.0f - motion->unk28;
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

typedef struct ScriptCursorView {
    u8 pad0[0x6C];
    u8 *unk6C;
} ScriptCursorView;


s32 scriptOpCallScriptByIndex(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actorScriptStartByIndex(actor, imm);
    sScriptPc = ((ScriptCursorView *)actor->sub4)->unk6C;
    return sScriptContinueRunning;
}

s32 scriptOpGotoScript(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    actorScriptStart(actor, imm);
    sScriptPc = ((ScriptCursorView *)actor->sub4)->unk6C;
    return sScriptContinueRunning;
}

typedef struct ScriptFlagState {
    u8 pad0[0x78];
    s32 unk78;
} ScriptFlagState;

s32 scriptOpEnableFlag8000(Actor *actor) {
    ScriptFlagState *state;

    state = (ScriptFlagState *)actor->sub4;
    state->unk78 |= 0x8000;
    return 0;
}

s32 scriptOpResetRampVelocity(Actor *actor) {
    f32 imm;
    ScriptValue *value;
    ScriptValueState *state;

    state = (ScriptValueState *)actor->sub4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    sScriptPc++;
    scriptReadU32(&imm);
    ((ScriptValueState *)actor->sub4)->unk88 = value->unk4 - imm;
    return 1;
}

typedef struct ScriptCountdownState {
    u8 pad0[0x88];
    s32 unk88;
} ScriptCountdownState;

s32 scriptOpCompareStateToU16(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    ((ScriptCountdownState *)actor->sub4)->unk88 = actor->state - imm;
    return 1;
}

s32 scriptOpCompareSubStateToU16(Actor *actor) {
    u16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    ((ScriptCountdownState *)actor->sub4)->unk88 = actor->unk155[0] - imm;
    return 1;
}

typedef struct ScriptCommandView {
    u8 pad0[0x10];
    s16 unk10;
} ScriptCommandView;

s32 func_80616518(Actor *actor) {
    u16 imm;
    ScriptCommandView *command;

    if (((ScriptValueState *)actor->sub4)->unk84 != 0) {
        command = (ScriptCommandView *)((ScriptValueState *)actor->sub4)->unk4;
    } else {
        command = (ScriptCommandView *)((ScriptValueState *)actor->sub4)->unk0;
    }
    sScriptPc++;
    scriptReadU16(&imm);
    ((ScriptValueState *)actor->sub4)->unk88 = command->unk10 - imm;
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
    ((ScriptCountdownState *)actor->sub4)->unk88 =
        ((GlobalCountdownView *)gActivePlayerState)->unk4E - imm;
    return 1;
}

typedef struct ScriptBaseCursorState {
    u8 pad0[0x68];
    u8 *unk68;
} ScriptBaseCursorState;

s32 scriptOpJump(Actor *actor) {
    s16 imm;

    sScriptPc++;
    scriptReadU16(&imm);
    sScriptPc = ((ScriptBaseCursorState *)actor->sub4)->unk68 + imm;
    return 1;
}

typedef struct ScriptJumpState {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[2];
    s32 unk60;
    u16 unk64;
    u8 pad66[2];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s32 unk88;
} ScriptJumpState;

s32 scriptOpJumpIfRegisterNonZero(Actor *actor) {
    s16 imm;
    ScriptJumpState *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = (ScriptJumpState *)actor->sub4;
    if (state->unk88 != 0) {
        sScriptPc = state->unk68 + imm;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterZero(Actor *actor) {
    s16 imm;
    ScriptJumpState *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = (ScriptJumpState *)actor->sub4;
    if (state->unk88 == 0) {
        sScriptPc = state->unk68 + imm;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterPositive(Actor *actor) {
    s16 imm;
    ScriptJumpState *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = (ScriptJumpState *)actor->sub4;
    if (state->unk88 > 0) {
        sScriptPc = state->unk68 + imm;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterNegative(Actor *actor) {
    s16 imm;
    ScriptJumpState *state;

    sScriptPc++;
    scriptReadU16(&imm);
    state = (ScriptJumpState *)actor->sub4;
    if (state->unk88 < 0) {
        sScriptPc = state->unk68 + imm;
    }
    return 1;
}

s32 scriptOpRestart(Actor *actor) {
    sScriptPc = ((ScriptJumpState *)actor->sub4)->unk68;
    return 1;
}

s32 scriptOpJumpTable(Actor *actor) {
    s16 imm;

    sScriptPc += 1 + ((ScriptJumpState *)actor->sub4)->unk88 * 2;
    scriptReadU16(&imm);
    sScriptPc = ((ScriptJumpState *)actor->sub4)->unk68 + imm;
    return 1;
}

s32 scriptOpCallSaveReturn(Actor *actor) {
    s32 savedReg;
    u16 imm;
    ScriptJumpState *state;

    savedReg = ((ScriptJumpState *)actor->sub4)->unk88;
    state = (ScriptJumpState *)actor->sub4;
    sScriptPc++;
    scriptReadU16(&imm);
    state->unk5C = state->unk64;
    state->unk60 = sScriptPc - state->unk68;
    actorScriptStart(actor, imm);
    sScriptPc = state->unk6C;
    state->unk88 = savedReg;
    return sScriptContinueRunning;
}

s32 scriptOpCall(Actor *actor) {
    u16 imm;
    ScriptJumpState *state;

    state = (ScriptJumpState *)actor->sub4;
    sScriptPc++;
    scriptReadU16(&imm);
    state->unk5C = state->unk64;
    state->unk60 = sScriptPc - state->unk68;
    actorScriptStartByIndex(actor, imm);
    sScriptPc = state->unk6C;
    return sScriptContinueRunning;
}
s32 scriptOpReturn(Actor *actor) {
    s32 savedReg;
    ScriptJumpState *state;

    savedReg = ((ScriptJumpState *)actor->sub4)->unk88;
    state = (ScriptJumpState *)actor->sub4;
    actorScriptStart(actor, state->unk5C);
    sScriptPc = state->unk68 + state->unk60;
    state->unk5C = 0;
    state->unk60 = 0;
    state->unk88 = savedReg;
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

typedef struct ScriptCommandState {
    u8 pad0[0x70];
    ScriptCommandFn unk70;
    u8 *unk74;
} ScriptCommandState;

s32 scriptOpSetCommandHandler(Actor *actor) {
    s16 imm;
    ScriptCommandState *state;
    state = (ScriptCommandState *)actor->sub4;
    sScriptPc++;
    scriptReadU16(&imm);
    state->unk70 = sScriptCommandTable[imm];
    state->unk74 = sScriptPc;
    if (imm != 0) {
        state->unk70(actor);
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
    actor->unk155[0] = 0;
    return 1;
}

s32 scriptOpIncrementActorState(Actor *actor) {
    sScriptPc++;
    actor->unk155[0] = 0;
    actor->state++;
    return 1;
}

s32 scriptOpSetActorSubState(Actor *actor) {
    u8 imm;

    sScriptPc++;
    scriptReadU8(&imm);
    actor->unk155[0] = imm;
    return 1;
}

s32 scriptOpIncrementActorSubState(Actor *actor) {
    sScriptPc++;
    actor->unk155[0]++;
    return 1;
}

s32 scriptOpIncrementChildActorSubState(Actor *actor) {
    Actor *parent;

    sScriptPc++;
    parent = actor->parentActor;
    parent->unk155[0]++;
    return 1;
}


s32 scriptOpSetRegisterRandom(Actor *actor) {
    u8 imm;
    u8 imm2;

    sScriptPc++;
    scriptReadU8(&imm);
    scriptReadU8(&imm2);
    ((ScriptJumpState *)actor->sub4)->unk88 = ((randomNonNegative() >> 15) % 32767) % ((imm2 - imm) + 1) + imm;
    return 1;
}

s32 scriptOpEnableFlag84(Actor *actor) {
    sScriptPc++;
    ((ScriptJumpState *)actor->sub4)->unk84 = 1;
    return 1;
}

s32 scriptOpDisableFlag84(Actor *actor) {
    sScriptPc++;
    ((ScriptJumpState *)actor->sub4)->unk84 = 0;
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
    priority = (sound * 7 + actor->actorType - 2) & 0xFFFF;
    sound = gActorScriptSoundTable[priority];
    volume = 0xFF;
    if (sound == 0) {
        if (gActivePlayerState->sfxHandle != 0) {
            n_alSndpStop(gActivePlayerState->sfxHandle);
        }
    }
    priority = gPlayerSlots[gActivePlayerState->playerIndex].unk2C0;
    pitch = 0x7F;
    if (priority == 2U) {
        priority = 10;
    } else if (priority == 0) {
        priority = 80;
        volume = (u8)(u32)((f64)(volume) * 0.5);
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

typedef struct ActorStateSubView {
    u8 pad0[0x10];
    s16 unk10;
} ActorStateSubView;

typedef struct ActorStateInnerView {
    ActorStateSubView *unk0;
} ActorStateInnerView;

typedef struct ScriptActionValue {
    u8 pad0[4];
    f32 value;
} ScriptActionValue;

typedef struct ScriptActionState {
    ScriptActionValue *unk0;
    ScriptActionValue *unk4;
    u8 pad8[0x7C];
    s32 unk84;
} ScriptActionState;

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
    actor->unk72 = ((ActorStateInnerView *)actor->sub4)->unk0->unk10;
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
    ScriptActionState *state;
    ScriptActionValue *value;

    state = (ScriptActionState *)actor->sub4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    scriptOpBranchOnCondition(actor, (s16)value->value);
}

typedef struct ScriptTimerSetState {
    u8 pad0[0x8A];
    s16 unk8A;
    f32 unk8C;
} ScriptTimerSetState;

typedef struct ScriptTimerState {
    u8 pad0[0x30];
    s16 unk30;
    u8 pad32[0x5A];
    f32 unk8C;
} ScriptTimerState;

typedef struct ActorFlagsView {
    u8 pad0[0x146];
    s16 unk146;
} ActorFlagsView;

void scriptOpBranchByTimer8A(Actor *actor) {
    scriptOpBranchOnCondition(actor, ((ScriptTimerSetState *)actor->sub4)->unk8A);
}

void func_80617D94(Actor *actor) {
    u8 imm;

    scriptReadU8(&imm);
    while (imm != 0) {
        sScriptPc += 4;
        scriptReadU8(&imm);
    }
}

typedef struct ScriptBranchState {
    u8 pad0[0x68];
    u8 *unk68;
    u8 pad6C[0x1C];
    s32 unk88;
} ScriptBranchState;

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
                sScriptPc = ((ScriptBranchState *)actor->sub4)->unk68 + imm3;
                return 1;
            }
            break;
        case 2:
            if (value < imm2) {
                scriptReadU16(&imm3);
                sScriptPc = ((ScriptBranchState *)actor->sub4)->unk68 + imm3;
                return 1;
            }
            break;
        case 3:
            if (imm2 < value) {
                scriptReadU16(&imm3);
                sScriptPc = ((ScriptBranchState *)actor->sub4)->unk68 + imm3;
                return 1;
            }
            break;
        case 4:
            if (value == imm2) {
                scriptReadU16(&imm3);
                ((ScriptBranchState *)actor->sub4)->unk88 = imm3;
                func_80617D94(actor);
                return 1;
            }
            break;
        case 5:
            if (value < imm2) {
                scriptReadU16(&imm3);
                ((ScriptBranchState *)actor->sub4)->unk88 = imm3;
                func_80617D94(actor);
                return 1;
            }
            break;
        case 6:
            if (imm2 < value) {
                scriptReadU16(&imm3);
                ((ScriptBranchState *)actor->sub4)->unk88 = imm3;
                func_80617D94(actor);
                return 1;
            }
            break;
        case 7:
            scriptReadU16(&imm3);
            ((ScriptBranchState *)actor->sub4)->unk88 = imm3;
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
    ((ScriptTimerSetState *)actor->sub4)->unk8C = imm;
    return 1;
}

extern u32 gFrameDelta;

s32 scriptOpWaitTimer(Actor *actor) {
    f32 step;
    ScriptTimerState *state;

    state = (ScriptTimerState *)actor->sub4;
    if (state->unk30 & 1) {
        step = (f32)gFrameDelta * 0.5f;
    } else {
        step = 1.0f;
    }
    state->unk8C -= step;
    if ((f64)((ScriptTimerState *)actor->sub4)->unk8C <= 0.0) {
        sScriptPc++;
        return 1;
    }
    return 0;
}

void scriptCmdNop(Actor *actor) {
}

typedef struct { u8 pad0[0x1A4]; u8 unk1A4; } ProjectileNodeState;
typedef struct { u8 pad0[2]; u8 unk2; } ProjectileDataView;
extern f32 D_80753E48[];
extern s16 D_80753E64[];
extern Actor *gActivePlayerActor;
extern u8 gCurrentPlayerIndex;
extern ProjectileDataView *D_807FD568;
extern s16 gCurrentCharacterIndex;
s32 mathAngleInArcWithMargin(s16, s16, s16, s32);

void projectileTrySpawnFromSlot(Actor *actor) {
    f32 radius;
    f32 speed;
    f32 dz;
    f32 dx;
    ProjectileNodeState *node;
    s16 pad;
    s16 hitYaw;
    s16 hitPitch;
    s16 aimYaw;
    PlayerSlot *slot;

    node = actor->customState;
    slotQueueUpdate(4, 0, 0);
    if ((slotQueueGetValue(4, node->unk1A4) != 0) && (actorCountOwnedByClass(actor, 4, 0) < D_80753E64[gCurrentCharacterIndex])) {
        slotQueueAddValue(4, node->unk1A4, -1);
        speed = (f32)((f64)actor->sub4->scaleY * 2.6666667064030967);
        switch (actor->actorType) {
            case 2:
            case 6:
            case 7: radius = 30.0f; break;
            case 3:
            case 5: radius = 20.0f; break;
            default: radius = 30.0f; break;
        }
        if (collisionTestSphere(actor->x, (f32)((f64)actor->y + 30.0), actor->z, radius, &hitYaw, &hitPitch, 1, 0) != 0) {
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

void effectSetMode(u8); // FAKE: callee prototype steer (shared header has s8; u8 keeps lbu, not lb)
void effectCreateAtActorBone(void *, f32, void *, s32, u8); // FAKE: callee prototype steer (shared header has s32 asset; pointer asset avoids the int conversion, Q0508)
void *effectCreateAtPosition(void *, f32, f32, f32, f32);
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
        ((ScriptState *)actor->sub4)->unk88 = 0;
        return;
    }
    ((ScriptState *)actor->sub4)->unk88 = 1;
}

void scriptCmdCheckNegativeUnkC0(Actor *actor) {
    if (actor->speedY < 0.0f) {
        ((ScriptState *)actor->sub4)->unk88 = 1;
        return;
    }
    ((ScriptState *)actor->sub4)->unk88 = 0;
}

void scriptCmdResetActorScale(Actor *actor) {
    if ((actor->contactFlags & actor->prevContactFlags & 1) != 0) {
        ((ScriptState *)actor->sub4)->unk88 = 1;
        return;
    }
    ((ScriptState *)actor->sub4)->unk88 = 0;
}

void scriptCmdSetActorUnkC0(Actor *actor) {
    s16 value;

    scriptReadU16(&value);
    actor->speedY = (f32)value;
}

void scriptCmdSetActorUnkC4(Actor *actor) {
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
        scale = (f32)(u32)imm2 * 0.00048828125f;
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
    Actor *unk4;
    s32 unk8;
    s16 unkC;
    u8 padE[2];
    f32 unk10;
} ChildEffectNodeState;

typedef struct ChildEffectActorView {
    u8 pad0[0x54];
    s32 unk54;
} ChildEffectActorView;

void effectSetColor(u8, u8, u8, u8); // FAKE: callee prototype steer (shared header has s8; u8 keeps li 255)

void scriptCmdSpawnEffectChildAndNode(Actor *actor) {
    u16 imm;
    u16 imm2;
    u16 imm3;
    u16 imm4;
    f32 scale;
    ChildEffectNodeState *node;

    scale = (f32)((f64)actor->sub4->scaleY / 0.15);
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
    node->unk10 = 0.0f;
    if (imm != 0xFFFF) {
        effectSetDuration(-1);
        effectSetDepth(1);
        switch (actor->actorType) {
            default:
                scale = (f32)((f64)scale * 0.2);
                break;
            case 0xBB:
                scale = (f32)((f64)scale * 0.4);
                effectSetColor(0, 0xFF, 0, 0xFF);
                break;
            case 4:
            case 5:
                effectSetMode(0);
                scale = (f32)((f64)scale * 0.18);
                node->unk10 = -1.4f;
                break;
            case 3:
                effectSetMode(0);
                scale = (f32)((f64)scale * 0.25);
                node->unk10 = -1.4f;
                break;
        }
    }
    gSpawnedActor->y -= node->unk10;
    if (imm != 0xFFFF) {
        effectCreateAtActorBone(sScriptEffectSprites[imm], scale, gSpawnedActor, 1, 2);
    }
    node->unk0 = imm2;
    node->unk4 = actor;
    node->unk8 = ((ChildEffectActorView *)actor)->unk54;
    node->unkC = actor->sub4->animId;
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

void scriptCmdCheckActorUnkDEGe3DA(Actor *actor) {
    ((ScriptState *)actor->sub4)->unk88 = actor->floorSlopePitch >= 0x3DA;
}
