#include "common.h"
#include "actor.h"

extern u8 *D_807F5AF0;
extern Struct807FD580 *gActivePlayerState;
extern Actor *D_807FBB44;

typedef struct ActorRampState {
    u8 pad0[0x48];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
} ActorRampState;

void scriptSetActorRampTarget(Actor *arg0, f32 arg1, f32 arg2) {
    ActorRampState *temp_v0;

    temp_v0 = (ActorRampState *)arg0->unk4;
    if (arg2 > 0.0f) {
        temp_v0->unk58 = arg2;
        temp_v0->unk50 = arg1;
        temp_v0->unk54 = 0.0f;
        temp_v0->unk4C = temp_v0->unk48;
        return;
    }
    temp_v0->unk48 = arg1;
    temp_v0->unk58 = 0.0f;
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

void func_80614D48(Actor *arg0, f32 arg1, f32 arg2) {
    RampValue *temp_v0;

    temp_v0 = ((RampValueHolder *)arg0->unk4)->unk0;
    if (arg2 > 0.0f) {
        temp_v0->unk34 = arg2;
        temp_v0->unk2C = arg1;
        temp_v0->unk30 = 0.0f;
        temp_v0->unk28 = temp_v0->unk24;
        return;
    }
    temp_v0->unk24 = arg1;
    temp_v0->unk34 = 0.0f;
}

extern s32 D_807F5AF4;
typedef s32 (*ActorScriptCommand)(Actor *);
extern ActorScriptCommand D_80746BEC[];

typedef struct ActorScriptState {
    u8 pad0[0x68];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    u8 *unk74;
    s32 unk78;
} ActorScriptState;

void actorScriptExecute(Actor *arg0) {
    ActorScriptState *state;

    state = (ActorScriptState *)arg0->unk4;
    if (state->unk68 != NULL) {
        D_807F5AF4 = 1;
        D_807F5AF0 = state->unk6C;
        while ((state->unk78 == 0) && (D_807F5AF4 != 0)) {
            D_807F5AF4 = D_80746BEC[*D_807F5AF0](arg0);
        }
        state->unk6C = D_807F5AF0;
        if (state->unk70 != NULL) {
            D_807F5AF0 = state->unk74;
            state->unk70(arg0);
        }
    }
}


typedef struct ActorTypeView {
    u8 pad0[0x58];
    s32 unk58;
} ActorTypeView;

extern u16 *D_807FBB54;

void actorScriptStart(Actor *arg0, s32 arg1);

void func_80614E78(Actor *arg0, s32 arg1) {
    s32 index;

    index = ((arg1 * 7) + ((ActorTypeView *)arg0)->unk58) - 2;
    actorScriptStart(arg0, *(D_807FBB54 + index));
}

extern u8 *D_807FBB50;

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

void actorScriptStart(Actor *arg0, s32 arg1) {
    ScriptLoadState *state;
    unsigned int base;
    s32 script;

    state = (ScriptLoadState *)arg0->unk4;
    state->unk70 = 0;
    state->unk78 = 0;
    state->unk7C = 0;
    state->unk88 = 0;
    state->unk80 = 0.0f;
    if (arg1 == 0) {
        state->unk68 = NULL;
        D_807F5AF0 = NULL;
        D_807F5AF4 = 0;
        return;
    }
    state->unk64 = arg1;
    base = (s32)D_807FBB50;
    script = (long long)(*(s32 *)(base + (arg1 * 4)) + base);
    state->unk68 = (u8 *)script;
    state->unk6C = (u8 *)script;
    D_807F5AF0 = (u8 *)script;
    if (script && script) {
    }
}

void scriptReadU8(u8 *arg0) {
    *arg0 = *D_807F5AF0++;
}

void scriptReadU16(u8 *arg0) {
    arg0++;
    arg0[-1] = *D_807F5AF0++;
    arg0[0] = *D_807F5AF0++;
}

void scriptReadU24(u8 *arg0) {
    arg0 += 2;
    arg0[-2] = *D_807F5AF0++;
    arg0[-1] = *D_807F5AF0++;
    arg0[0] = *D_807F5AF0++;
}

void scriptReadU32(u8 *arg0) {
    arg0 += 3;
    arg0[-3] = *D_807F5AF0++;
    arg0[-2] = *D_807F5AF0++;
    arg0[-1] = *D_807F5AF0++;
    arg0[0] = *D_807F5AF0++;
}

s32 scriptOpNop(s32 arg0) {
    D_807F5AF0++;
    return 1;
}

s32 scriptOpYield(s32 arg0) {
    D_807F5AF0++;
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

s32 scriptOpSetRegister(Actor *arg0) {
    s16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    ((ScriptState *)arg0->unk4)->unk88 = sp1E;
    return 1;
}

s32 scriptOpDecrementRegister(Actor *arg0) {
    ScriptState *temp_v0;
    s32 temp_v1;

    temp_v0 = (ScriptState *)arg0->unk4;
    temp_v1 = temp_v0->unk88;
    if (temp_v1 != 0) {
        temp_v0->unk88 = temp_v1 - 1;
    }
    D_807F5AF0++;
    return 1;
}

s32 scriptOpWaitRegisterCountdown(Actor *arg0) {
    ScriptState *temp_v1;
    s32 temp_a1;

    temp_v1 = (ScriptState *)arg0->unk4;
    temp_a1 = temp_v1->unk88;
    if (temp_a1 != 0) {
        temp_v1->unk88 = temp_a1 - 1;
        return 0;
    }
    D_807F5AF0++;
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

s32 func_80615134(Actor *arg0) {
    ScriptSelectorState *state;
    ScriptSelectorValue *value;

    state = (ScriptSelectorState *)arg0->unk4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    D_807F5AF0++;
    if ((value->unk24 != 0.0f) || ((value->unk2C != 0.0f) && (value->unk34 != 0.0f))) {
        ((ScriptSelectorState *)arg0->unk4)->unk78 |= 1;
    }
    return 0;
}

s32 func_806151BC(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    if (sp1F) {
        ((ScriptState *)arg0->unk4)->unk7C = sp1F - 1;
        ((ScriptState *)arg0->unk4)->flags |= 2;
        return 0;
    }
    return 1;
}

s32 scriptOpSetRandomByteInRange(Actor *arg0) {
    u8 pad;
    u8 min;
    u8 max;
    u8 val;

    D_807F5AF0++;
    scriptReadU8(&min);
    scriptReadU8(&max);
    val = (((randomNonNegative() >> 15) % 32767) % ((max - min) + 1)) + min;
    if (val != 0) {
        ((ScriptState *)arg0->unk4)->unk7C = val - 1;
        ((ScriptState *)arg0->unk4)->flags |= 2;
        return 0;
    }
    return 1;
}

s32 func_806152FC(Actor *arg0) {
    D_807F5AF0++;
    ((ScriptState *)arg0->unk4)->flags |= 4;
    return 0;
}

s32 scriptOpOrFlags(Actor *arg0) {
    s16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    ((ScriptState *)arg0->unk4)->flags |= sp1E;
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

s32 func_8061537C(Actor *arg0) {
    f32 sp1C;
    Actor *actor;

    actor = arg0;
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp1C);
    if (sp1C < 0.0f) {
        sp1C = (f32)((ScriptRateState *)actor->unk4)->unk88;
    }
    ((ScriptRateState *)actor->unk4)->unk80 = sp1C;
    ((ScriptRateState *)actor->unk4)->unk78 |= 8;
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

s32 func_8061540C(Actor *arg0) {
    f32 sp24;
    ScriptValue *sp20;
    Actor *actor;

    actor = arg0;
    if (((ScriptValueState *)actor->unk4)->unk84 != 0) {
        sp20 = ((ScriptValueState *)actor->unk4)->unk4;
    } else {
        sp20 = ((ScriptValueState *)actor->unk4)->unk0;
    }
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp24);
    if (sp24 < 0.0f) {
        sp24 = (f32)((ScriptValueState *)actor->unk4)->unk88;
    }
    if ((((ScriptValueState *)actor->unk4)->unk48 * sp20->unk24) > 0.0f) {
        if (sp24 <= sp20->unk4) {
            return 1;
        }
    } else if (sp20->unk4 <= sp24) {
        return 1;
    }
    ((ScriptValueState *)actor->unk4)->unk80 = sp24;
    ((ScriptValueState *)actor->unk4)->unk78 |= 8;
    return 0;
}

s32 func_8061551C(Actor *arg0) {
    ScriptValueState *state;

    D_807F5AF0++;
    state = (ScriptValueState *)arg0->unk4;
    if (*state->unk8 != 0) {
        state->unk78 |= 0x10;
    }
    return 0;
}

s32 func_80615558(Actor *arg0) {
    f32 sp1C;
    ScriptValueState *state;

    state = (ScriptValueState *)arg0->unk4;
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp1C);
    if (*state->unk8 != 0) {
        if (sp1C < state->unk44) {
            state->unk44 = sp1C;
            state->unk40 = state->unk44 - (state->unk10 * state->unk44);
        }
        ((ScriptValueState *)arg0->unk4)->unk78 |= 0x10;
    }
    return 0;
}

s32 scriptOpWaitRegisterNonZero(Actor *arg0) {
    if (((ScriptValueState *)arg0->unk4)->unk88 != 0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

s32 scriptOpWaitRegisterZero(Actor *arg0) {
    if (((ScriptValueState *)arg0->unk4)->unk88 == 0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

s32 func_80615664(Actor *arg0) {
    if (((ScriptValueState *)arg0->unk4)->unk4->unk0 == 0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

s32 func_806156A0(Actor *arg0) {
    ScriptValueState *state;

    state = (ScriptValueState *)arg0->unk4;
    if (state->unk28 == state->unk2C) {
        D_807F5AF0++;
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

s32 func_806156DC(Actor *arg0) {
    f32 sp24;
    ScriptActionView *sp20;

    if (((ScriptValueState *)arg0->unk4)->unk84 != 0) {
        sp20 = (ScriptActionView *)((ScriptValueState *)arg0->unk4)->unk4;
    } else {
        sp20 = (ScriptActionView *)((ScriptValueState *)arg0->unk4)->unk0;
    }
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp24);
    if (sp24 < (f32)sp20->unk0->unk12) {
        sp20->unk14 = sp24;
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

s32 func_80615774(Actor *arg0) {
    f32 sp24;
    ScriptActionInfo *action;
    ScriptActionInfoState *state;

    state = (ScriptActionInfoState *)arg0->unk4;
    if (state->unk84 != 0) {
        action = state->unk4;
    } else {
        action = state->unk0;
    }
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp24);
    if (sp24 < action->unk0->unk12) {
        action->unk18 = sp24;
    }
    return 1;
}

s32 func_8061580C(Actor *arg0) {
    f32 sp24;
    f32 sp20;
    ScriptActionInfo *action;

    if (((ScriptActionInfoState *)arg0->unk4)->unk84 != 0) {
        action = ((ScriptActionInfoState *)arg0->unk4)->unk4;
    } else {
        action = ((ScriptActionInfoState *)arg0->unk4)->unk0;
    }
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp24);
    scriptReadU32((u8 *)&sp20);
    if (sp24 < action->unk0->unk12) {
        action->unk14 = sp24;
    }
    if (sp20 < action->unk0->unk12) {
        action->unk18 = sp20;
    }
    return 1;
}

s32 func_806158E8(Actor *arg0) {
    ScriptActionInfo *action;
    ScriptActionInfoState *state;
    ScriptActionResourceInfo *resource;

    state = (ScriptActionInfoState *)arg0->unk4;
    if (state->unk84 != 0) {
        action = state->unk4;
    } else {
        action = state->unk0;
    }
    resource = action->unk0;
    D_807F5AF0++;
    action->unk14 = 0.0f;
    action->unk18 = (f32)(resource->unk12 - 1);
    action->unk1C = resource->unk4;
    return 1;
}


void func_80613C48(s32, s16, f32, f32);
void controllerAnimSetStateRemap(s32, s16, f32, f32);
void controllerAnimSetStateRemapDirect(s32, s16, f32, f32);
void controllerAnimScaleInterpolate(s32, s8);
void controllerAnimSetFromTable(s32, u16, f32, u8);


s32 func_8061594C(s32 arg0) {
    s16 sp1E;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    func_80613C48(arg0, sp1E, 0.0f, 1.0f);
    return 1;
}

s32 func_8061599C(s32 arg0) {
    s16 sp1E;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    controllerAnimSetStateRemapDirect(arg0, sp1E, 0.0f, 1.0f);
    return 1;
}

void controllerAnimSetState(s32, s16, f32, f32);

s32 func_806159EC(s32 arg0) {
    s16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    controllerAnimSetState(arg0, sp1E, 0.0f, 0);
    return 1;
}
s32 func_80615A3C(s32 arg0) {
    s16 sp1E;
    f32 sp18;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    scriptReadU32((u8 *)&sp18);
    func_80613C48(arg0, sp1E, 0.0f, sp18);
    return 1;
}

s32 func_80615A94(s32 arg0) {
    s8 sp1F;
    D_807F5AF0++;
    scriptReadU8((u8 *)&sp1F);
    controllerAnimScaleInterpolate(arg0, sp1F);
    return 1;
}

void controllerAnimSetDirect(s32, u16, f32, u8);

s32 func_80615ADC(s32 arg0) {
    u16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    scriptReadU8(&sp1D);
    controllerAnimSetDirect(arg0, sp1E, 0.0f, sp1D);
    return 1;
}

s32 func_80615B34(s32 arg0) {
    s16 sp1E;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    controllerAnimSetStateRemap(arg0, sp1E, 0.0f, 1.0f);
    return 1;
}

s32 func_80615B84(s32 arg0) {
    s16 sp1E;
    f32 sp18;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    scriptReadU32((u8 *)&sp18);
    controllerAnimSetStateRemap(arg0, sp1E, 0.0f, sp18);
    return 1;
}

s32 func_80615BDC(s32 arg0) {
    u16 sp1E;
    u8 sp1D;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    scriptReadU8(&sp1D);
    controllerAnimSetFromTable(arg0, sp1E, 0.0f, sp1D);
    return 1;
}

void controllerApplyMotionWindow(Actor *, ScriptValue *, f32);

s32 func_80615C34(Actor *arg0) {
    u8 sp27;
    ScriptValue *var_a1;
    ScriptValue *sp20;
    ScriptValueState *temp_v0;

    temp_v0 = (ScriptValueState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_a1 = temp_v0->unk4;
    } else {
        var_a1 = temp_v0->unk0;
    }
    sp20 = var_a1;
    D_807F5AF0++;
    scriptReadU8(&sp27);
    if (sp27 == 0xFF) {
        sp27 = ((ScriptValueState *)arg0->unk4)->unk88;
    }
    controllerApplyMotionWindow(arg0, sp20, (f32)sp27);
    return 1;
}

extern u8 D_80746D5C;

s32 func_80615CE4(Actor *arg0) {
    u8 sp27;
    void *var_a1;
    ScriptValueState *temp_v0;

    temp_v0 = (ScriptValueState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_a1 = temp_v0->unk4;
    } else {
        var_a1 = temp_v0->unk0;
    }
    D_807F5AF0++;
    scriptReadU8(&sp27);
    controllerApplyMotionWindow(arg0, var_a1, (f32)D_80746D5C);
    if (D_80746D5C != 0) {
        D_80746D5C += sp27;
    } else {
        D_80746D5C = 0;
    }
    return 1;
}

typedef struct ScriptMotion {
    void *unk0;
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

s32 scriptOpUpdateMotionDelta(Actor *arg0) {
    u8 sp27;
    ScriptMotion *sp20;

    if (((ScriptMotionState *)arg0->unk4)->unk84 != 0) {
        sp20 = ((ScriptMotionState *)arg0->unk4)->unk4;
    } else {
        sp20 = ((ScriptMotionState *)arg0->unk4)->unk0;
    }
    D_807F5AF0++;
    scriptReadU8(&sp27);
    sp20->unk1E = sp20->unkC;
    sp20->unk20 = sp27;
    sp20->unk1C |= 8;
    if ((f32)sp20->unkC < sp20->unk4) {
        sp20->unk8 = sp20->unk4 - (f32)sp20->unkC;
    } else {
        sp20->unk8 = -(sp20->unk4 - (f32)sp20->unkC);
    }
    sp20->unkE = sp27;
    ((ScriptMotionState *)arg0->unk4)->unk78 |= 0x20;
    return 1;
}

s32 func_80615E74(Actor *arg0) {
    u8 sp2F;
    u8 sp2E;
    ScriptMotion *sp28;
    f32 temp_fv1;
    f32 temp_fv0;
    s16 temp_v1_2;

    if (((ScriptMotionState *)arg0->unk4)->unk84 != 0) {
        sp28 = ((ScriptMotionState *)arg0->unk4)->unk4;
    } else {
        sp28 = ((ScriptMotionState *)arg0->unk4)->unk0;
    }
    D_807F5AF0++;
    scriptReadU8(&sp2F);
    scriptReadU8(&sp2E);
    temp_v1_2 = sp28->unkC;
    if (temp_v1_2 == (sp2F & 0xFFFFFFFFu)) {
        temp_fv0 = (f32)temp_v1_2;
        temp_fv1 = sp28->unk4;
        sp28->unk1E = temp_v1_2;
        sp28->unk20 = sp2E;
        sp28->unk1C |= 8;
        if (temp_fv0 < temp_fv1) {
            sp28->unk8 = temp_fv1 - temp_fv0;
        } else {
            sp28->unk8 = -(temp_fv1 - temp_fv0);
        }
        sp28->unkE = sp2E;
        ((ScriptMotionState *)arg0->unk4)->unk78 |= 0x20;
    } else {
        sp28->unkC = (temp_v1_2 + sp2E) - sp2F;
        sp28->unkE = (sp28->unkE + sp2E) - sp2F;
        sp28->unk4 += sp2E - sp2F;
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

s32 func_80615FA0(Actor *arg0) {
    s16 sp26;
    ScriptMotionFlagsView *var_v1;
    void *sp20;
    ScriptMotionFlagsState *temp_v0;

    temp_v0 = (ScriptMotionFlagsState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp26);
    ((ScriptMotionFlagsView *)sp20)->unk1C |= sp26;
    return 1;
}

s32 func_8061600C(Actor *arg0) {
    s16 sp26;
    ScriptMotionFlagsView *var_v1;
    void *sp20;
    ScriptMotionFlagsState *temp_v0;

    temp_v0 = (ScriptMotionFlagsState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp26);
    ((ScriptMotionFlagsView *)sp20)->unk1C &= ~sp26;
    return 1;
}

s32 func_8061607C(Actor *arg0) {
    f32 var_fv0;
    f32 sp20;
    ScriptMotion *sp1C;

    sp1C = ((ScriptMotionState *)arg0->unk4)->unk84 != 0
        ? ((ScriptMotionState *)arg0->unk4)->unk4
        : ((ScriptMotionState *)arg0->unk4)->unk0;
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp20);
    if (sp1C->unk0 != NULL) {
        var_fv0 = *(f32 *)sp1C->unk0;
    } else {
        var_fv0 = .0f;
    }
    if (sp20 > 0.0f) {
        sp1C->unk34 = sp20;
        sp1C->unk2C = var_fv0;
        sp1C->unk30 = 0.0f;
        sp1C->unk28 = sp1C->unk24;
    } else {
        sp1C->unk24 = var_fv0;
        sp1C->unk34 = 0.0f;
    }
    return 1;
}

s32 func_8061612C(Actor *arg0) {
    f32 sp24;
    f32 sp20;
    ScriptMotion *sp1C;
    ScriptMotionState *temp_v1;

    temp_v1 = (ScriptMotionState *)arg0->unk4;
    if (temp_v1->unk84 != 0) {
        sp1C = temp_v1->unk4;
    } else {
        sp1C = temp_v1->unk0;
    }
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp24);
    scriptReadU32((u8 *)&sp20);
    if (sp20 > 0.0f) {
        sp1C->unk34 = sp20;
        sp1C->unk2C = sp24;
        sp1C->unk28 = sp1C->unk24;
        sp1C->unk30 = 0.0f;
    } else {
        sp1C->unk24 = sp24;
        sp1C->unk34 = 0.0f;
    }
    return 1;
}

s32 func_806161D0(Actor *arg0) {
    f32 temp_fv0;
    ScriptMotionState *temp_v0;
    ScriptMotion *var_v1;

    temp_v0 = (ScriptMotionState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    D_807F5AF0++;
    temp_fv0 = var_v1->unk24;
    if (temp_fv0 < 0.0f) {
        var_v1->unk24 = 0.0f - temp_fv0;
        if (var_v1->unk34 != (0.0f * 1.0f)) {
            var_v1->unk2C = 0.0f - var_v1->unk2C;
            var_v1->unk28 = 0.0f - var_v1->unk28;
        }
    }
    return 1;
}

s32 func_80616254(Actor *arg0) {
    f32 temp_fv0 = 0.0f;
    ScriptMotionState *temp_v0;
    ScriptMotion *var_v1;

    temp_v0 = (ScriptMotionState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    D_807F5AF0++;
    var_v1->unk24 = temp_fv0 - var_v1->unk24;
    if (var_v1->unk34 != (0.0f * 1.0f)) {
        var_v1->unk2C = temp_fv0 - var_v1->unk2C;
        var_v1->unk28 = temp_fv0 - var_v1->unk28;
    }
    return 1;
}

void scriptSetActorRampTarget(Actor *, f32, f32);

s32 func_806162C4(Actor *arg0) {
    f32 sp1C;
    f32 sp18;

    D_807F5AF0++;
    scriptReadU32((u8 *)&sp1C);
    scriptReadU32((u8 *)&sp18);
    scriptSetActorRampTarget(arg0, sp1C, sp18);
    return 1;
}

typedef struct ScriptCursorView {
    u8 pad0[0x6C];
    u8 *unk6C;
} ScriptCursorView;

void func_80614E78(Actor *, s32);
void actorScriptStart(Actor *, s32);

s32 func_80616318(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    func_80614E78(arg0, sp1E);
    D_807F5AF0 = ((ScriptCursorView *)arg0->unk4)->unk6C;
    return D_807F5AF4;
}

s32 scriptOpGotoScript(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    actorScriptStart(arg0, sp1E);
    D_807F5AF0 = ((ScriptCursorView *)arg0->unk4)->unk6C;
    return D_807F5AF4;
}

typedef struct ScriptFlagState {
    u8 pad0[0x78];
    s32 unk78;
} ScriptFlagState;

s32 func_806163D0(Actor *arg0) {
    ScriptFlagState *temp_v1;

    temp_v1 = (ScriptFlagState *)arg0->unk4;
    temp_v1->unk78 |= 0x8000;
    return 0;
}

s32 func_806163E8(Actor *arg0) {
    f32 sp24;
    ScriptValue *var_v1;
    void *sp20;
    ScriptValueState *temp_v0;

    temp_v0 = (ScriptValueState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0++;
    scriptReadU32((u8 *)&sp24);
    ((ScriptValueState *)arg0->unk4)->unk88 = ((ScriptValue *)sp20)->unk4 - sp24;
    return 1;
}

typedef struct ScriptCountdownState {
    u8 pad0[0x88];
    s32 unk88;
} ScriptCountdownState;

s32 func_80616470(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    ((ScriptCountdownState *)arg0->unk4)->unk88 = arg0->unk154 - sp1E;
    return 1;
}

s32 func_806164C4(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    ((ScriptCountdownState *)arg0->unk4)->unk88 = arg0->unk155[0] - sp1E;
    return 1;
}

typedef struct ScriptCommandView {
    u8 pad0[0x10];
    s16 unk10;
} ScriptCommandView;

s32 func_80616518(Actor *arg0) {
    u16 sp26;
    ScriptCommandView *sp20;

    if (((ScriptValueState *)arg0->unk4)->unk84 != 0) {
        sp20 = (ScriptCommandView *)((ScriptValueState *)arg0->unk4)->unk4;
    } else {
        sp20 = (ScriptCommandView *)((ScriptValueState *)arg0->unk4)->unk0;
    }
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp26);
    ((ScriptValueState *)arg0->unk4)->unk88 = sp20->unk10 - sp26;
    return 1;
}

typedef struct GlobalCountdownView {
    u8 pad0[0x4E];
    s16 unk4E;
} GlobalCountdownView;

s32 func_80616594(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    ((ScriptCountdownState *)arg0->unk4)->unk88 =
        ((GlobalCountdownView *)gActivePlayerState)->unk4E - sp1E;
    return 1;
}

typedef struct ScriptBaseCursorState {
    u8 pad0[0x68];
    u8 *unk68;
} ScriptBaseCursorState;

s32 scriptOpJump(Actor *arg0) {
    s16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    D_807F5AF0 = ((ScriptBaseCursorState *)arg0->unk4)->unk68 + sp1E;
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

s32 scriptOpJumpIfRegisterNonZero(Actor *arg0) {
    s16 sp1E;
    ScriptJumpState *temp_v0;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    temp_v0 = (ScriptJumpState *)arg0->unk4;
    if (temp_v0->unk88 != 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterZero(Actor *arg0) {
    s16 sp1E;
    ScriptJumpState *temp_v0;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    temp_v0 = (ScriptJumpState *)arg0->unk4;
    if (temp_v0->unk88 == 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterPositive(Actor *arg0) {
    s16 sp1E;
    ScriptJumpState *temp_v0;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    temp_v0 = (ScriptJumpState *)arg0->unk4;
    if (temp_v0->unk88 > 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 scriptOpJumpIfRegisterNegative(Actor *arg0) {
    s16 sp1E;
    ScriptJumpState *temp_v0;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    temp_v0 = (ScriptJumpState *)arg0->unk4;
    if (temp_v0->unk88 < 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 scriptOpRestart(Actor *arg0) {
    D_807F5AF0 = ((ScriptJumpState *)arg0->unk4)->unk68;
    return 1;
}

s32 scriptOpJumpTable(Actor *arg0) {
    s16 sp1E;

    /* Preserve IDO's evaluation tree for its register allocation. */
    D_807F5AF0 = (0, 1) + (D_807F5AF0 + (((ScriptJumpState *)arg0->unk4)->unk88 * 2));
    scriptReadU16((u8 *)&sp1E);
    D_807F5AF0 = ((ScriptJumpState *)arg0->unk4)->unk68 + sp1E;
    return (sp1E = 1);
}

s32 scriptOpCallSaveReturn(Actor *arg0) {
    s32 sp24;
    u16 sp22;
    ScriptJumpState *sp1C;

    sp24 = ((ScriptJumpState *)arg0->unk4)->unk88;
    sp1C = (ScriptJumpState *)arg0->unk4;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp22);
    sp1C->unk5C = sp1C->unk64;
    sp1C->unk60 = D_807F5AF0 - sp1C->unk68;
    actorScriptStart(arg0, sp22);
    D_807F5AF0 = sp1C->unk6C;
    sp1C->unk88 = sp24;
    return D_807F5AF4;
}

s32 scriptOpCall(Actor *arg0) {
    u16 sp1E;
    ScriptJumpState *sp18;

    sp18 = (ScriptJumpState *)arg0->unk4;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    sp18->unk5C = sp18->unk64;
    sp18->unk60 = D_807F5AF0 - sp18->unk68;
    func_80614E78(arg0, sp1E);
    D_807F5AF0 = sp18->unk6C;
    return D_807F5AF4;
}
s32 scriptOpReturn(Actor *arg0) {
    s32 sp1C;
    ScriptJumpState *sp18;

    sp1C = ((ScriptJumpState *)arg0->unk4)->unk88;
    sp18 = (ScriptJumpState *)arg0->unk4;
    actorScriptStart(arg0, sp18->unk5C);
    D_807F5AF0 = sp18->unk68 + sp18->unk60;
    sp18->unk5C = 0;
    sp18->unk60 = 0;
    sp18->unk88 = sp1C;
    return 1;
}

typedef void (*ScriptCommandFn)();

extern ScriptCommandFn D_80746D64[];

s32 scriptOpRunCommand(Actor *arg0) {
    s16 sp1E;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    D_80746D64[sp1E](arg0);
    return D_807F5AF4;
}

typedef struct ScriptCommandState {
    u8 pad0[0x70];
    ScriptCommandFn unk70;
    u8 *unk74;
} ScriptCommandState;

s32 scriptOpSetCommandHandler(Actor *arg0) {
    s16 sp1E;
    ScriptCommandState *sp18;
    sp18 = (ScriptCommandState *)arg0->unk4;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    sp18->unk70 = D_80746D64[sp1E];
    sp18->unk74 = D_807F5AF0;
    if (sp1E != 0) {
        sp18->unk70(arg0);
    }
    return D_807F5AF4;
}

void sfxPlayOnFreeSlot(s16, s32, f32, f32, s32, s32);

s32 func_80616A9C(s32 arg0) {
    s16 sp26;
    u8 sp25;
    s16 sp22;
    u8 sp21;
    u8 sp20;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp26);
    scriptReadU8(&sp25);
    scriptReadU8(&sp20);
    scriptReadU16((u8 *)&sp22);
    scriptReadU8(&sp21);
    sfxPlayOnFreeSlot(sp26, (s32)(((f64)sp25 * 32767.0) / 255.0), (f32)sp20,
                  (f32)((f64)sp22 / 127.0), (s32)sp21, 0);
    return 1;
}

s32 func_80616BA4(Actor *arg0) {
    u8 sp1F;
    u8 temp;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    arg0->unk154 = (temp = sp1F);
    arg0->unk155[0] = 0;
    return 1;
}

s32 func_80616BF0(Actor *arg0) {
    D_807F5AF0++;
    arg0->unk155[0] = 0;
    arg0->unk154++;
    return 1;
}

s32 func_80616C1C(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    arg0->unk155[0] = sp1F;
    return 1;
}

s32 func_80616C64(Actor *arg0) {
    D_807F5AF0++;
    arg0->unk155[0]++;
    return 1;
}

s32 func_80616C8C(Actor *arg0) {
    Actor *temp_v1;

    D_807F5AF0++;
    temp_v1 = (Actor *)arg0->unk11C;
    temp_v1->unk155[0]++;
    return 1;
}


s32 scriptOpSetRegisterRandom(Actor *arg0) {
    u8 sp1F;
    u8 sp1E;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    scriptReadU8(&sp1E);
    ((ScriptJumpState *)arg0->unk4)->unk88 = (s32)(((s32)((s32)(randomNonNegative() >> 0xF) % 32767) % (s32)((sp1E - sp1F) + 1)) + sp1F);
    return 1;
}

s32 func_80616D5C(Actor *arg0) {
    D_807F5AF0++;
    ((ScriptJumpState *)arg0->unk4)->unk84 = 1;
    return 1;
}

s32 func_80616D84(Actor *arg0) {
    D_807F5AF0++;
    ((ScriptJumpState *)arg0->unk4)->unk84 = 0;
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

s32 scriptOpHalt(s32 arg0) {
    return 0;
}

s32 func_80616DB4(Actor *arg0) {
    ScriptTarget *target;
    u8 flag;

    target = (ScriptTarget *)((ActorTargetView *)arg0)->unk17C;
    D_807F5AF0++;
    scriptReadU8(&flag);
    target->flags |= flag;
    return 1;
}

struct PlayerSoundStruct;
extern struct PlayerSoundStruct *gPlayerSlots;

typedef struct PlayerSoundView {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} PlayerSoundView;

typedef struct GlobalSoundState {
    u8 pad0[0x104];
    s32 unk104;
    u8 pad108[0x9C];
    u8 unk1A4;
} GlobalSoundState;

typedef struct ActorSoundPosView {
    u8 pad0[0x78];
    u8 unk78;
    u8 pad79[3];
    s32 unk7C;
    f32 unk80;
    f32 unk84;
} ActorSoundPosView;

void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void camStartShakeFromPoint(s32, u8, u16, s32, f32, f32, f32, f32);
s16 mapActionLookupEntry(s16, Actor *, u8);


s32 scriptOpPlaySoundAndShake(Actor *arg0) {
    s16 sp4E;
    volatile u8 sp4D; // FAKE: volatile loads are not hoistable, keeps the 0xFF arm's lbu out of the bnez delay slot
    s16 sp4A;
    u8 sp49;
    u8 var_v1;
    u8 pad;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4E);
    scriptReadU8((u8 *)&sp4D);
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp49);
    if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 2) {
        var_v1 = 0xA;
        if (sp4E == 1) {
            sp4D = (u32)((f64)(u32)sp4D * 0.5);
        }
        camStartShakeFromPoint(((GlobalSoundState *)gActivePlayerState)->unk104, 0xA, 8, ((ActorSoundPosView *)arg0)->unk7C, ((ActorSoundPosView *)arg0)->unk80, ((ActorSoundPosView *)arg0)->unk84, 100.0f, 800.0f);
    } else if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 0) {
        var_v1 = 0xFF;
        sp4D = (u32)((f64)(u32)sp4D * 0.5);
    } else {
        switch (arg0->unk58) {
        case 6:
        case 7:
            var_v1 = 0x46;
            break;
        case 8:
            var_v1 = 0x5A;
            break;
        case 2:
        case 4:
            var_v1 = 0x32;
            break;
        default:
            var_v1 = 0x50;
            break;
        }
    }
    if (arg0 && arg0 && arg0) {} // FAKE: empty guard adds a block to as1's XBB window (limit 10), pushing the then-arm's lh/li hoists out
    if (arg0 && arg0 && arg0) {} // FAKE: same (6 guards needed)
    if (arg0 && arg0 && arg0) {} // FAKE: same
    if (arg0 && arg0 && arg0) {} // FAKE: same
    if (arg0 && arg0 && arg0) {} // FAKE: same
    if (arg0 && arg0 && arg0) {} // FAKE: same
    sp4E = mapActionLookupEntry(sp4E, arg0, ((ActorSoundPosView *)arg0)->unk78);
    if ((sp4E == 2) || (sp4E == 8)) {
        sp49 = 0xA;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp4E, (s32)sp4D, (s32)sp4A, (s32)sp49, (s32)var_v1, 0.3f, 0);
    return 1;
}

typedef struct ActorSoundView {
    u8 pad0[0x78];
    u8 unk78;
} ActorSoundView;

extern s32 D_807457C8;

void n_alSndpStop(s32);
void sfxPlayFromActorDirect(Actor *, s16, u8, f32, s32, s32);

s32 func_80617140(Actor *arg0) {
    s16 sp2E;
    s16 temp_v0;
    u8 sp2B;
    u8 sp2A;
    u8 sp29;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp2E);
    scriptReadU8(&sp2B);
    scriptReadU8(&sp2A);
    scriptReadU8(&sp29);
    if (D_807457C8 != 0) {
        n_alSndpStop(D_807457C8);
        D_807457C8 = 0;
    }
    temp_v0 = mapActionLookupEntry(sp2E, arg0, ((ActorSoundView *)arg0)->unk78);
    if (temp_v0 == 8) {
        sp29 = 4;
    }
    sfxPlayFromActorDirect(arg0, temp_v0, sp2B, (f32)((f64)sp2A / 127.0),
                           (s32)sp29, 0x4B);
    return 1;
}

typedef struct PlayerSoundStruct {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} PlayerSoundStruct;
extern PlayerSoundStruct *gPlayerSlots;

typedef struct GlobalStateView7238 {
    u8 pad0[0x1A4];
    u8 unk1A4;
} GlobalStateView7238;

s32 scriptOpPlayPositionalSoundPlayerStateVolume(Actor *arg0) {
    s16 sp3E;
    u8 sp3D;
    u8 pad;
    u8 sp3B;
    s32 var_v0;

    sp3B = 0xFF;
    D_807F5AF0++;
    scriptReadU16((u8 *)&sp3E);
    scriptReadU8(&sp3D);
    if (gPlayerSlots[((GlobalStateView7238 *)gActivePlayerState)->unk1A4].unk2C0 == 2) {
        var_v0 = 0xA;
    } else if (gPlayerSlots[((GlobalStateView7238 *)gActivePlayerState)->unk1A4].unk2C0 == 0) {
        var_v0 = 0xFF;
        sp3B *= 0.5;
    } else {
        switch (arg0->unk58) {
        case 6:
        case 7:
        case 8:
            var_v0 = 0x5A;
            break;
        case 2:
        case 4:
            var_v0 = 0x32;
            break;
        default:
            var_v0 = 0x50;
            break;
        }
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp3E, sp3B, 0x7F, sp3D, var_v0, 0.3f, 0);
    return 1;
}


s32 func_80617400(Actor *arg0) {
    s16 sp36;
    u8 sp35;
    u8 sp34;
    u8 sp33;
    u8 sp32;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp36);
    scriptReadU8(&sp33);
    scriptReadU8(&sp32);
    scriptReadU8(&sp35);
    scriptReadU8(&sp34);
    if (arg0->unk60 & 4) {
        sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp36, sp33, sp32, sp35, sp34, 0.3f, 0);
    }
    return 1;
}

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);

s32 func_806174B4(Actor *arg0) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    s16 sp4A;
    unsigned char sp49;
    Actor *node_actor;
    u8 sp43;
    u8 sp42;
    u8 sp41;
    u8 sp40;
    u8 sp3F;
    f32 sp38;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp40);
    scriptReadU8(&sp3F);
    scriptReadU8(&sp49);
    scriptReadU8(&sp43);
    scriptReadU32((u8 *)&sp38);
    scriptReadU8(&sp42);
    scriptReadU8(&sp41);
    if (arg0->unk60 & 4) {
        if (sp42) {
            node_actor = arg0;
            actorGetNodePos(node_actor, sp42, &sp54, &sp50, &sp4C);
        } else {
            sp54 = arg0->unk7C;
            sp50 = arg0->unk80;
            sp4C = arg0->unk84;
        }
        sfxPlayAtPositionPooled(sp54, sp50, sp4C, sp4A, sp40, sp3F, sp49, sp43, sp38, sp41);
    }
    return 1;
}

typedef struct ActorSoundScaleState {
    u8 pad0[0x34];
    f32 unk34;
} ActorSoundScaleState;


s32 scriptOpPlayDistanceVolumeSound(Actor *arg0) {
    s16 sp46;
    u8 sp45;
    u8 sp44;
    u8 sp43;
    u8 sp42;
    f32 var_fv1;
    f64 val;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp46);
    scriptReadU8(&sp43);
    scriptReadU8(&sp42);
    scriptReadU8(&sp45);
    scriptReadU8(&sp44);
    val = (((((f64)((ActorSoundScaleState *)arg0->unk4)->unk34 / 0.4381361) * 200.0) + 55.0) * (f64)sp43) / 255;
    var_fv1 = (val > 255.0) ? 255.0 : val;
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp46, (u32)var_fv1, sp42, sp45, sp44, 0.3f, 0);
    return 1;
}

typedef struct ScriptSoundState {
    u8 pad0[0xC4];
    s32 unkC4;
    u8 padC8[0xDC];
    u8 unk1A4;
} ScriptSoundState;

extern s16 *D_807FBB5C;
void sfxPlayAtPositionForPlayer(f32, f32, f32, s16, u8, u8, u8, u8, f32);

void sfxPlayScriptActorSoundForPlayer(Actor *arg0, s16 arg1, u8 arg2) {
    u8 pad0, pad1, pad2;
    u8 var_v1;
    s32 pitch;
    s32 temp_v0;
    temp_v0 = (arg1 * 7 + arg0->unk58 - 2) & 0xFFFF;
    arg1 = D_807FBB5C[temp_v0];
    var_v1 = 0xFF;
    if (arg1 == 0) {
        if (((ScriptSoundState *)gActivePlayerState)->unkC4 != 0) {
            n_alSndpStop(((ScriptSoundState *)gActivePlayerState)->unkC4);
        }
    }
    temp_v0 = gPlayerSlots[((ScriptSoundState *)gActivePlayerState)->unk1A4].unk2C0;
    pitch = 0x7F;
    if (temp_v0 == 2U) {
        temp_v0 = 10;
    } else if (temp_v0 == 0) {
        temp_v0 = 80;
        var_v1 = (u8)(u32)((f64)(var_v1 ^ 0) * 0.5);
    } else {
        if (arg0->unk58 == 2 || arg0->unk58 == 4) {
            temp_v0 = 50;
        } else {
            temp_v0 = 60;
        }
    }
    sfxPlayAtPositionForPlayer(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, var_v1, pitch, arg2, temp_v0, 0.3f);
}

void sfxPlayScriptActorSoundForPlayer(Actor *, s16, u8);
void sfxStopSlotSound(Actor *, u8);
void sfxPlayActorSound(Actor *, s16, u8, u8, u8, u8, f32, s8);
void sfxSetVolumeAndPan(u8, f32, f32);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, u8);
void func_8070D8C0(Actor *, u16, u8);
s32 func_80617DFC(Actor *, s16);
extern u8 D_80746D60[];

typedef struct ActorStateSubView {
    u8 pad0[0x10];
    s16 unk10;
} ActorStateSubView;

typedef struct ActorStateInnerView {
    ActorStateSubView *unk0;
} ActorStateInnerView;

typedef struct ActorStateSlotView {
    u8 pad0[0x72];
    s16 unk72;
} ActorStateSlotView;

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

s32 func_8061796C(Actor *arg0) {
    s16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    scriptReadU8(&sp1D);
    sfxPlayScriptActorSoundForPlayer(arg0, sp1E, sp1D);
    return 1;
}

s32 func_806179C0(Actor *arg0) {
    s16 sp2E;
    u8 sp2D;
    u8 sp2C;
    u8 sp2B;
    s8 sp2A;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp2E);
    scriptReadU8(&sp2D);
    scriptReadU8(&sp2B);
    scriptReadU8(&sp2C);
    scriptReadU8((u8 *)&sp2A);
    sfxStopSlotSound(arg0, sp2D);
    sfxPlayActorSound(arg0, sp2E, sp2C, 1, sp2D, sp2B, 1.0f, sp2A);
    return 1;
}

s32 scriptOpSetSoundVolumeAndPan(Actor *arg0) {
    f32 sp1C;
    u8 sp1B;
    u8 sp1A;

    D_807F5AF0++;
    scriptReadU8(&sp1A);
    scriptReadU32((u8 *)&sp1C);
    scriptReadU8(&sp1B);
    sfxSetVolumeAndPan(((u8 *)arg0)[sp1A * 2 + 0x6F], sp1C, (f32)sp1B);
    return 1;
}

s32 scriptOpStopSlotSound(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    sfxStopSlotSound(arg0, sp1F);
    return 1;
}

s32 func_80617B38(Actor *arg0) {
    s16 sp2E;
    u8 sp2D;
    u8 sp2C;
    s8 sp2B;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp2E);
    scriptReadU8(&sp2D);
    scriptReadU8(&sp2C);
    scriptReadU8((u8 *)&sp2B);
    sfxPlayActorSound(arg0, sp2E, sp2C, 1, sp2D, 0xFF, 1.0f, sp2B);
    ((ActorStateSlotView *)arg0)->unk72 = ((ActorStateInnerView *)arg0->unk4)->unk0->unk10;
    return 1;
}

s32 scriptOpAllocateSoundChannel(Actor *arg0) {
    u8 sp1F;
    u8 sp1E;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    scriptReadU8(&sp1E);
    sfxAllocateChannel(D_80746D60[sp1F], (f32)((f64)sp1E / 255.0));
    return 1;
}

s32 scriptOpStopSoundChannel(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    scriptReadU8(&sp1F);
    sfxStopChannel(D_80746D60[sp1F], 0);
    return 1;
}

s32 func_80617CC0(Actor *arg0) {
    u16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp1E);
    scriptReadU8(&sp1D);
    func_8070D8C0(arg0, sp1E, sp1D);
    return 1;
}

s32 func_80617D14(Actor *arg0) {
    return 1;
}

void func_80617D20(Actor *arg0) {
    ScriptActionState *state;
    ScriptActionValue *value;

    state = (ScriptActionState *)arg0->unk4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    func_80617DFC(arg0, (s16)value->value);
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

typedef struct GlobalFlagsView {
    u8 pad0[0x1F0];
    s32 unk1F0;
} GlobalFlagsView;

void func_80617D70(Actor *arg0) {
    func_80617DFC(arg0, ((ScriptTimerSetState *)arg0->unk4)->unk8A);
}

void func_80617D94(Actor *arg0) {
    u8 sp27;

    scriptReadU8(&sp27);
    if (sp27 != 0) {
        do {
            D_807F5AF0 += 4;
            scriptReadU8(&sp27);
        } while (sp27 != 0);
    }
}

typedef struct ScriptBranchState {
    u8 pad0[0x68];
    u8 *unk68;
    u8 pad6C[0x1C];
    s32 unk88;
} ScriptBranchState;

s32 func_80617DFC(Actor *arg0, s16 arg1) {
    u8 sp2F;
    s16 sp2C;
    s16 sp2A;

    D_807F5AF0++;
    while (1) {
        scriptReadU8(&sp2F);
        scriptReadU16((u8 *)&sp2C);
        switch (sp2F) {
        case 0:
            D_807F5AF0 -= 2;
            return 1;
        case 1:
            if (arg1 == sp2C) {
                scriptReadU16((u8 *)&sp2A);
                D_807F5AF0 = ((ScriptBranchState *)arg0->unk4)->unk68 + sp2A;
                return 1;
            }
            break;
        case 2:
            if (arg1 < sp2C) {
                scriptReadU16((u8 *)&sp2A);
                D_807F5AF0 = ((ScriptBranchState *)arg0->unk4)->unk68 + sp2A;
                return 1;
            }
            break;
        case 3:
            if (sp2C < arg1) {
                scriptReadU16((u8 *)&sp2A);
                D_807F5AF0 = ((ScriptBranchState *)arg0->unk4)->unk68 + sp2A;
                return 1;
            }
            break;
        case 4:
            if (arg1 == sp2C) {
                scriptReadU16((u8 *)&sp2A);
                ((ScriptBranchState *)arg0->unk4)->unk88 = sp2A;
                func_80617D94(arg0);
                return 1;
            }
            break;
        case 5:
            if (arg1 < sp2C) {
                scriptReadU16((u8 *)&sp2A);
                ((ScriptBranchState *)arg0->unk4)->unk88 = sp2A;
                func_80617D94(arg0);
                return 1;
            }
            break;
        case 6:
            if (sp2C < arg1) {
                scriptReadU16((u8 *)&sp2A);
                ((ScriptBranchState *)arg0->unk4)->unk88 = sp2A;
                func_80617D94(arg0);
                return 1;
            }
            break;
        case 7:
            scriptReadU16((u8 *)&sp2A);
            ((ScriptBranchState *)arg0->unk4)->unk88 = sp2A;
            func_80617D94(arg0);
            return 1;
        }
        D_807F5AF0 += 2;
    }
}

s32 scriptOpSetTimer(Actor *arg0) {
    f32 sp1C;

    D_807F5AF0++;
    scriptReadU32((u8 *)&sp1C);
    ((ScriptTimerSetState *)arg0->unk4)->unk8C = sp1C;
    return 1;
}

extern u32 D_80744478;

s32 scriptOpWaitTimer(Actor *arg0) {
    f32 var_fv0;
    ScriptTimerState *state;

    state = (ScriptTimerState *)arg0->unk4;
    if (state->unk30 & 1) {
        var_fv0 = (f32)D_80744478 * 0.5f;
    } else {
        var_fv0 = 1.0f;
    }
    state->unk8C -= var_fv0;
    if ((f64)((ScriptTimerState *)arg0->unk4)->unk8C <= 0.0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

void scriptCmdNop(Actor *arg0) {
}

typedef struct { u8 pad0[0x1A4]; u8 unk1A4; } ProjectileNodeState;
typedef struct { u8 pad0[0x210]; f32 unk210; u8 pad214[4]; f32 unk218; u8 pad21C[0xC]; f32 unk228; u8 pad22C[4]; f32 unk230; u8 pad234[0xBC]; } ProjectilePlayerView;
typedef struct { u8 pad0[2]; u8 unk2; } ProjectileDataView;
extern f32 D_80753E48[];
extern s16 D_80753E64[];
extern Actor *D_807FBB48;
extern u8 gCurrentPlayerIndex;
extern ProjectileDataView *D_807FD568;
extern s16 D_807FD584;
void slotQueueUpdate(s32, s32, s32);
s32 slotQueueGetValue(s32, u8);
void slotQueueAddValue(s32, u8, s32);
s32 actorCountOwnedByClass(Actor *, s32, s32);
s32 collisionTestSphere(f32, f32, f32, f32, s16 *, s16 *, s32, s32);
s32 mathAngleInArcWithMargin(s16, s16, s16, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void projectileSetSpawnFlag(void);
void projectileGetTargetCoords(Actor *, s32);
void projectileSpawnNodeEntry(s32, u8, f32, s16, f32, f32, Actor *);

void projectileTrySpawnFromSlot(Actor *arg0) {
    f32 var_fv0;
    f32 sp50;
    f32 temp_fv0;
    f32 temp_fv1;
    ProjectileNodeState *sp44;
    s16 pad;
    s16 sp40;
    s16 sp3E;
    s16 var_a2;
    ProjectilePlayerView *temp_v0;

    sp44 = arg0->unk174;
    slotQueueUpdate(4, 0, 0);
    if ((slotQueueGetValue(4, sp44->unk1A4) != 0) && (actorCountOwnedByClass(arg0, 4, 0) < D_80753E64[D_807FD584])) {
        slotQueueAddValue(4, sp44->unk1A4, -1);
        sp50 = (f32)((f64)arg0->unk4->unk38 * 2.6666667064030967);
        switch (arg0->unk58) {
            case 2:
            case 6:
            case 7: var_fv0 = 30.0f; break;
            case 3:
            case 5: var_fv0 = 20.0f; break;
            default: var_fv0 = 30.0f; break;
        }
        if (collisionTestSphere(arg0->unk7C, (f32)((f64)arg0->unk80 + 30.0), arg0->unk84, var_fv0, &sp40, &sp3E, 1, 0) != 0) {
            if (arg0->unk154 == 2) {
                temp_v0 = &((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex];
                var_a2 = mathAngleBetweenPoints2D(temp_v0->unk228, temp_v0->unk230, temp_v0->unk210, temp_v0->unk218);
            } else {
                var_a2 = arg0->unkE6;
            }
            if (mathAngleInArcWithMargin(sp40, sp3E, var_a2, 0) == 0) projectileSetSpawnFlag();
        }
        if (arg0->unk154 == 2) {
            projectileGetTargetCoords(D_807FBB48, 6);
            temp_fv0 = ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk230 - ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk218;
            temp_fv1 = ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk228 - ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk210;
            sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
            projectileSpawnNodeEntry(0x29, D_807FD568->unk2, sp50, mathAngleBetweenPoints2D(((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk228, ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk230, ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk210, ((ProjectilePlayerView *)gPlayerSlots)[gCurrentPlayerIndex].unk218), D_80753E48[D_807FD584], 0.0f, arg0);
            return;
        }
        projectileGetTargetCoords(arg0, 7);
        projectileSpawnNodeEntry(0x29, D_807FD568->unk2, sp50, arg0->unkE6, D_80753E48[D_807FD584], 0.0f, arg0);
    }
}

void func_80714950(s32);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714C08(void *, f32, Actor *, u8, s32);
void *func_80714CC0(void *, f32, f32, f32, f32);
void effectSpawnBone(Actor *, s32, f32, f32, f32, f32, s32);
void actorGetNodePosOrPosition(Actor *, s32 *, f32 *, f32 *);
extern void func_8071B1AC(void);
extern void func_8071B24C(void);
extern void func_8071B44C(void);
extern u8 D_8071FE08[];
extern u8 D_8071FF18[];
extern void effectOrbitSourceUpdate(void);
extern s32 D_807FBB60;
extern f32 D_807F5AF8;
extern f32 D_807F5AFC;
extern f32 D_807F5B00;
void actorSpawn(s32, s32);
void actorDespawn(void *);
void actorCopyPoseAndScale(Actor *, Actor *, s32);
void func_806D9924(Actor *);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s16);


typedef struct ActorSpawnState {
    u8 pad0[0x34];
    s32 unk34;
} ActorSpawnState;

typedef struct GlobalSpawnView {
    u8 pad0[0x88];
    Actor *unk88;
    u8 pad8C[0x78];
    s32 unk104;
} GlobalSpawnView;

typedef struct ActorEffectView {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x88];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[0x3C];
    s16 unk12C;
    u8 pad12E[0x46];
    u8 *unk174;
} ActorEffectView;

void func_80618430(Actor *arg0) {
    u8 sp27;

    scriptReadU8(&sp27);
    func_8071498C(func_8071B1AC);
    func_80714998(2);
    func_80714950(((ActorEffectView *)arg0)->unkE6);
    func_807149B8(1);
    func_80714C08(D_8071FF18, 0.4f, arg0, sp27, 0);
}

void func_8061849C(Actor *arg0) {
    ((GlobalFlagsView *)gActivePlayerState)->unk1F0 |= 0x40000;
}

void func_806184BC(Actor *arg0) {
    u8 sp2F;

    scriptReadU8(&sp2F);
    if (sp2F == 0xFF) {
        func_807149B8(0);
        func_807149FC(1);
        func_80714CC0(D_8071FE08, 0.7f, arg0->unk7C, arg0->unk80 + 7.0f, arg0->unk84);
    } else {
        func_8071498C(func_8071B24C);
        func_80714998(2);
        func_80714950((((ActorEffectView *)arg0)->unkE6 + 0x800) & 0xFFF);
        func_807149B8(1);
        func_80714A28(0x80);
        func_80714C08(D_8071FF18, 0.4f, arg0, sp2F, 0);
    }
}

void func_8061859C(Actor *arg0) {
    u8 sp27;

    scriptReadU8(&sp27);
    func_8071498C(func_8071B44C);
    func_80714998(2);
    func_80714950(((ActorEffectView *)arg0)->unkEE);
    func_807149B8(1);
    func_80714C08(D_8071FF18, 0.4f, arg0, sp27, 0);
}

extern s32 D_807FBB68;
extern u8 D_8072006C;
extern u8 D_80720B58;
void func_8071A440(void);
void effectFloorFallUpdate(void);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s16, s16, s16, s32);

void func_80618608(Actor *arg0) {
    u8 sp3F;
    s16 var_s0;

    scriptReadU8(&sp3F);
    if (D_807FBB68 & 2) {
        for (var_s0 = 0; var_s0 < 0x14; var_s0++) {
            func_807149B8(1);
            func_807149FC(-1);
            func_8071498C(effectFloorFallUpdate);
            func_80714A28(4);
            func_80714C08(&D_80720B58, 0.1f, arg0, sp3F, 0);
        }
        return;
    }
    sfxPlayFromActorWithAltitudeCheck(arg0, 0x8A, 0x96, 0x7F, 0x32);
    func_80714950((s32)arg0);
    func_8071498C(func_8071A440);
    func_80714C08(&D_8072006C, 0.4f, arg0, sp3F, 2);
}

void func_80618728(Actor *arg0) {
    func_807149A8(0x7D0);
    func_80714998(3);
    effectSpawnBone(arg0, 0x16, 0.8f, 0.0f, 0.0f, 0.0f, -0x78);
    func_807149A8(0x7D0);
    func_80714998(3);
    effectSpawnBone(arg0, 0x17, 0.8f, 0.0f, 0.0f, 0.0f, -0x78);
}

void func_806187BC(Actor *arg0) {
    s16 sp1E;
    s16 sp1C;

    scriptReadU16((u8 *)&sp1E);
    scriptReadU16((u8 *)&sp1C);
}

void func_806187E8(Actor *arg0) {
    s16 sp1E;

    scriptReadU16((u8 *)&sp1E);
    ((ActorFlagsView *)arg0)->unk146 |= sp1E;
}

void func_80618820(Actor *arg0) {
    s16 sp1E;

    scriptReadU16((u8 *)&sp1E);
    ((ActorFlagsView *)arg0)->unk146 &= ~sp1E;
}

void func_8061885C(Actor *arg0) {
    f32 sp1C;

    scriptReadU32((u8 *)&sp1C);
}

typedef struct {
    u8 pad0[4];
    ScriptState *unk4;
    u8 pad8[0x50];
    s32 unk58;
    u8 pad5C[0xE];
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x52];
    f32 unkC0;
    f32 unkC4;
    u8 padC8[0x16];
    s16 unkDE;
    u8 padE0[0x98];
    void *unk178;
} ActorScriptView;

typedef struct {
    u8 pad0[0x64];
    s16 unk64;
} GlobalToggleView;

void func_80618880(Actor *arg0) {
    ActorScriptView *actor;

    actor = (ActorScriptView *)arg0;
    if (((GlobalToggleView *)gActivePlayerState)->unk64 != 0) {
        ((GlobalToggleView *)gActivePlayerState)->unk64 = 0;
        actor->unk4->unk88 = 0;
        return;
    }
    actor->unk4->unk88 = 1;
}

void func_806188B8(Actor *arg0) {
    ActorScriptView *actor;

    actor = (ActorScriptView *)arg0;
    if (actor->unkC0 < 0.0f) {
        actor->unk4->unk88 = 1;
        return;
    }
    actor->unk4->unk88 = 0;
}

void func_806188F4(Actor *arg0) {
    ActorScriptView *actor;

    actor = (ActorScriptView *)arg0;
    if ((actor->unk6A & actor->unk6C & 1) != 0) {
        actor->unk4->unk88 = 1;
        return;
    }
    actor->unk4->unk88 = 0;
}

void func_8061892C(Actor *arg0) {
    s16 value;

    scriptReadU16((u8 *)&value);
    ((ActorScriptView *)arg0)->unkC0 = (f32)value;
}

void func_80618968(Actor *arg0) {
    f32 value;

    scriptReadU32((u8 *)&value);
    ((ActorScriptView *)arg0)->unkC4 = value;
}

extern u8 D_807444EC;

void scriptCmdActorCamShake(Actor *arg0) {
    s32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 sp42;
    s16 sp40;
    u8 sp3F;
    u8 sp3E;
    s32 temp_v0;
    s32 var_v1;

    actorGetNodePosOrPosition(arg0, &sp4C, &sp48, &sp44);
    scriptReadU8(&sp3E);
    scriptReadU8(&sp3F);
    scriptReadU16((u8 *)&sp42);
    scriptReadU16((u8 *)&sp40);
    sp3F = (u32)((f64)sp3F * ((f64)arg0->unk4->unk38 / 0.15));
    temp_v0 = arg0->unk58;
    if ((temp_v0 == 0xCC) || ((arg0->unk6A & 1) && ((arg0->unk60 & 4) || (temp_v0 == 0xE4)) && (D_807444EC != 1))) {
        var_v1 = (sp3F >= 21) ? 20 : sp3F;
        camStartShakeFromPoint(((GlobalSpawnView *)gActivePlayerState)->unk104, sp3E, var_v1, sp4C, sp48, sp44, (f32)sp42, (f32)sp40);
    }
}
void func_80618B6C(Actor *arg0) {
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    u8 sp2F;
    u8 sp2E;

    actorGetNodePosOrPosition(arg0, &sp3C, &sp38, &sp34);
    scriptReadU8(&sp2E);
    scriptReadU8(&sp2F);
    scriptReadU16((u8 *)&sp32);
    scriptReadU16((u8 *)&sp30);
    camStartShakeFromPoint(((GlobalSpawnView *)gActivePlayerState)->unk104, sp2E, sp2F, sp3C, sp38, sp34, (f32)sp32, (f32)sp30);
}

void actorSpawnEffectChild(f32, f32, f32, f32, f32, Actor *, u8);
void actorSetNodeFlag();
void actorClearNodeFlag();

typedef struct GlobalTimerView {
    u8 pad0[0xCA];
    u8 unkCA;
} GlobalTimerView;

void func_80618C00(Actor *arg0, u8 arg1) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 scale;

    scale = 0.04f;
    actorGetNodePos(arg0, arg1, &sp3C, &sp38, &sp34);
    if ((arg0->unk58 == 6) || (arg0->unk58 == 7)) {
        scale = 0.1f;
    }
    actorSpawnEffectChild(sp3C, arg0->unkA4, sp34, 0.03f, scale, arg0, 0);
}

void func_80618C8C(Actor *arg0) {
    u8 node;

    if (arg0->unk58 == 2) {
        node = 2;
    } else {
        node = 8;
    }
    func_80618C00(arg0, node);
    ((GlobalTimerView *)gActivePlayerState)->unkCA = 0x28;
}

void func_80618CD8(Actor *arg0) {
    u8 sp1F;

    scriptReadU8(&sp1F);
    if (sp1F & 0x80) {
        arg0->unk132 = (s16)(sp1F & 0x7F);
        return;
    }
    actorSetNodeFlag(arg0, sp1F);
}

void func_80618D20(Actor *arg0) {
    u8 sp1F;

    scriptReadU8(&sp1F);
    if (sp1F & 0x80) {
        arg0->unk132 = (s16)(sp1F & 0x7F);
        return;
    }
    actorClearNodeFlag(arg0, sp1F);
}

extern void *D_80746B80[];
void func_8071496C(s32);

void scriptCmdSpawnOrbitEffects(Actor *arg0) {
    s32 i;
    u8 sp43;
    u8 sp42;

    scriptReadU8(&sp43);
    scriptReadU8(&sp42);
    for (i = sp43; i < sp42; i++) {
        func_8071498C(effectOrbitSourceUpdate);
        func_807149FC(-1);
        func_807149B8(1);
        func_8071496C(1);
        func_80714950(1);
        func_80714A28(0x20);
        func_80714C08(D_80746B80[i], 0.2f, arg0, 7, 0);
    }
}

void func_80618E4C(Actor *arg0) {
    u8 sp1F;

    scriptReadU8(&sp1F);
    if (sp1F != 0) {
        arg0->unk60 &= 0xBFFFFFFF;
        D_807FBB60 |= 0x10030;
    } else {
        arg0->unk60 |= 0x40000000;
        D_807FBB60 &= 0xFFFEFFCF;
        func_806D9924(arg0);
    }
}

extern s16 D_80746E10[];

void func_80618EE8(Actor *arg0) {
    u8 *script;

    actorSpawn(0x135, D_80746E10[((ActorEffectView *)arg0)->unk58]);
    actorCopyPoseAndScale(D_807FBB44, arg0, ((ActorSpawnState *)arg0->unk4)->unk34);
    ((ActorEffectView *)D_807FBB44)->unkE8 = ((ActorEffectView *)arg0)->unkE8;
    ((ActorEffectView *)D_807FBB44)->unkE4 = ((ActorEffectView *)arg0)->unkE4;
    script = ((ActorEffectView *)D_807FBB44)->unk174;
    scriptReadU8(script + 6);
}

void func_80618F74(Actor *arg0) {
    u8 sp1F;
    ActorEffectView *actor;

    scriptReadU8(&sp1F);
    if (sp1F != 0) {
        actorSpawn(0x136, 0xA8);
        actorCopyPoseAndScale(D_807FBB44, arg0, ((ActorSpawnState *)arg0->unk4)->unk34);
        ((GlobalSpawnView *)gActivePlayerState)->unk88 = D_807FBB44;
    } else {
        actor = (ActorEffectView *)((GlobalSpawnView *)gActivePlayerState)->unk88;
        if ((actor != NULL) && (actor->unk58 == 0x136)) {
            actorDespawn(actor);
            ((GlobalSpawnView *)gActivePlayerState)->unk88 = NULL;
        }
    }
}

void func_80619018(Actor *arg0) {
    u8 sp1F;

    scriptReadU8(&sp1F);
    if (sp1F != 0) {
        if (((ActorEffectView *)arg0)->unk12C != -1) {
            lightGetColor(&D_807F5AF8, &D_807F5AFC, &D_807F5B00, ((ActorEffectView *)arg0)->unk12C);
            lightSetColor(107.0f, 48.0f, 80.0f, ((ActorEffectView *)arg0)->unk12C);
        }
    } else if (((ActorEffectView *)arg0)->unk12C != -1) {
        lightSetColor(((f32 *)&D_807F5AF8)[0], ((f32 *)&D_807F5AF8)[1], ((f32 *)&D_807F5AF8)[2], ((ActorEffectView *)arg0)->unk12C);
    }
}

typedef struct FallingEffectView {
    u8 pad0[0x35C];
    s32 unk35C;
} FallingEffectView;

extern u8 D_80750AD0;
extern void (*D_80746BD4[])(void);
s32 effectFallStateInit(Actor *, void *, u8 *);
void effectFreeAndUnlink(void *);

void scriptCmdSpawnFallingEffect(Actor *arg0) {
    u16 sp4E;
    u16 sp4C;
    u8 sp4B;
    u8 sp4A;
    s8 sp49;
    u8 sp48;
    s16 sp46;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    FallingEffectView *effect;
    u8 sp2F;
    u8 node;

    scriptReadU16((u8 *)&sp4E);
    scriptReadU16((u8 *)&sp4C);
    scriptReadU8(&sp4B);
    scriptReadU8(&sp4A);
    scriptReadU8((u8 *)&sp49);
    scriptReadU8(&sp48);
    scriptReadU16((u8 *)&sp46);
    if (D_80750AD0 == 0) {
        sp40 = (f32)(u32)sp4C * 0.00048828125f;
        func_807149B8(1);
        func_80714998(sp4B);
        func_807149FC(sp46);
        if ((node = sp4A) == 0) {
            sp3C = arg0->unk7C;
            sp38 = arg0->unk80;
            sp34 = arg0->unk84;
        } else {
            actorGetNodePos(arg0, node, &sp3C, &sp38, &sp34);
        }
        sp38 += (f32)sp49 * sp40;
        if (sp48 != 0) {
            func_8071498C(D_80746BD4[sp48]);
        }
        effect = func_80714CC0(D_80746B80[sp4E], sp40, sp3C, sp38, sp34);
        sp2F = 0;
        switch (sp48) {
            case 1:
                effectFallStateInit(arg0, effect, &sp2F);
                break;
            case 2:
                effect->unk35C = 1;
                break;
            case 4:
                effect->unk35C = -50 - ((randomNonNegative() >> 15) % 50);
                break;
        }
        if (sp2F != 0) {
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

typedef struct ChildEffectSub4View {
    u8 pad0[0x64];
    u16 unk64;
} ChildEffectSub4View;

void func_807149C8(s32, s32, s32, s32);

void scriptCmdSpawnEffectChildAndNode(Actor *arg0) {
    u16 sp46;
    u16 sp44;
    u16 sp42;
    u16 sp40;
    f32 var_fs0;
    ChildEffectNodeState *var_v1;

    var_fs0 = (f32)((f64)arg0->unk4->unk38 / 0.15);
    scriptReadU16((u8 *)&sp46);
    scriptReadU16((u8 *)&sp44);
    scriptReadU16((u8 *)&sp42);
    scriptReadU16((u8 *)&sp40);
    actorSpawn(0x139, sp42);
    actorCopyPoseAndScale(D_807FBB44, arg0, ((ActorSpawnState *)arg0->unk4)->unk34);
    D_807FBB44->unkE6 = arg0->unkE6;
    D_807FBB44->unkE8 = arg0->unkE8;
    D_807FBB44->unkE4 = arg0->unkE4;
    var_v1 = (ChildEffectNodeState *)D_807FBB44->unk174;
    var_v1->unk10 = 0.0f;
    if (sp46 != 0xFFFF) {
        func_807149FC(-1);
        func_807149B8(1);
        switch (arg0->unk58) {
            default:
                var_fs0 = (f32)((f64)var_fs0 * 0.2);
                break;
            case 0xBB:
                var_fs0 = (f32)((f64)var_fs0 * 0.4);
                func_807149C8(0, 0xFF, 0, 0xFF);
                break;
            case 4:
            case 5:
                func_80714998(0);
                var_fs0 = (f32)((f64)var_fs0 * 0.18);
                var_v1->unk10 = -1.4f;
                break;
            case 3:
                func_80714998(0);
                var_fs0 = (f32)((f64)var_fs0 * 0.25);
                var_v1->unk10 = -1.4f;
                break;
        }
    }
    D_807FBB44->unk80 -= var_v1->unk10;
    if (sp46 != 0xFFFF) {
        func_80714C08(D_80746B80[sp46], var_fs0, D_807FBB44, 1, 2);
    }
    var_v1->unk0 = sp44;
    var_v1->unk4 = arg0;
    var_v1->unk8 = ((ChildEffectActorView *)arg0)->unk54;
    var_v1->unkC = ((ChildEffectSub4View *)arg0->unk4)->unk64;
    var_v1->unk2 = sp40;
}

void scriptCmdDespawnActor(Actor *arg0) {
    actorDespawn(arg0);
}

void *func_80619520(Actor *arg0) {
    ActorScriptView *actor;
    void *result;

    actor = (ActorScriptView *)arg0;
    result = NULL;
    if (actor->unk58 == 0x134) {
        result = actor->unk178;
    }
    return result;
}

void func_80619540(Actor *arg0) {
    u8 value;
    u8 *result;

    result = func_80619520(arg0);
    scriptReadU8(&value);
    if (result != NULL) {
        result[0x35] = value;
    }
}

void func_80619580(Actor *arg0) {
    u8 *result;

    result = func_80619520(arg0);
    if (result != NULL) {
        result[0x35]++;
    }
}

void func_806195B4(Actor *arg0) {
    ActorScriptView *actor;

    actor = (ActorScriptView *)arg0;
    actor->unk4->unk88 = actor->unkDE >= 0x3DA;
}
