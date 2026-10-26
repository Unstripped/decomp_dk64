#include "common.h"
#include "actor.h"

extern u8 *D_807F5AF0;
extern Struct807FD580 *D_807FD580;
extern Actor *D_807FBB44;

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80614D00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80614D48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80614D90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80614E78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80614EBC.s")

void func_80614F28(u8 *arg0) {
    *arg0 = *D_807F5AF0++;
}

void func_80614F4C(u8 *arg0) {
    arg0++;
    arg0[-1] = *D_807F5AF0++;
    arg0[0] = *D_807F5AF0++;
}

void func_80614F88(u8 *arg0) {
    arg0 += 2;
    arg0[-2] = *D_807F5AF0++;
    arg0[-1] = *D_807F5AF0++;
    arg0[0] = *D_807F5AF0++;
}

void func_80614FD8(u8 *arg0) {
    arg0 += 3;
    arg0[-3] = *D_807F5AF0++;
    arg0[-2] = *D_807F5AF0++;
    arg0[-1] = *D_807F5AF0++;
    arg0[0] = *D_807F5AF0++;
}

s32 func_8061503C(s32 arg0) {
    D_807F5AF0++;
    return 1;
}

s32 func_8061505C(s32 arg0) {
    D_807F5AF0++;
    return 0;
}

typedef struct P19aState {
    u8 pad0[0x78];
    s32 flags;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s32 unk88;
} P19aState;

s32 func_8061507C(Actor *arg0) {
    s16 sp1E;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    ((P19aState *)arg0->unk4)->unk88 = sp1E;
    return 1;
}

s32 func_806150C8(Actor *arg0) {
    P19aState *temp_v0;
    s32 temp_v1;

    temp_v0 = (P19aState *)arg0->unk4;
    temp_v1 = temp_v0->unk88;
    if (temp_v1 != 0) {
        temp_v0->unk88 = temp_v1 - 1;
    }
    D_807F5AF0++;
    return 1;
}

s32 func_806150F8(Actor *arg0) {
    P19aState *temp_v1;
    s32 temp_a1;

    temp_v1 = (P19aState *)arg0->unk4;
    temp_a1 = temp_v1->unk88;
    if (temp_a1 != 0) {
        temp_v1->unk88 = temp_a1 - 1;
        return 0;
    }
    D_807F5AF0++;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806151BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061522C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806152FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615328.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061537C.s")

typedef struct P19bValue {
    void *unk0;
    f32 unk4;
    u8 pad8[0x1C];
    f32 unk24;
} P19bValue;

typedef struct P19bState {
    P19bValue *unk0;
    P19bValue *unk4;
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
} P19bState;

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061540C.s")

s32 func_8061551C(Actor *arg0) {
    P19bState *state;

    D_807F5AF0++;
    state = (P19bState *)arg0->unk4;
    if (*state->unk8 != 0) {
        state->unk78 |= 0x10;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615558.s")

s32 func_806155F4(Actor *arg0) {
    if (((P19bState *)arg0->unk4)->unk88 != 0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

s32 func_8061562C(Actor *arg0) {
    if (((P19bState *)arg0->unk4)->unk88 == 0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

s32 func_80615664(Actor *arg0) {
    if (((P19bState *)arg0->unk4)->unk4->unk0 == 0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

s32 func_806156A0(Actor *arg0) {
    P19bState *state;

    state = (P19bState *)arg0->unk4;
    if (state->unk28 == state->unk2C) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806156DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615774.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061580C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806158E8.s")


void func_80613C48(s32, s16, f32, f32);
void func_80613AF8(s32, s16, f32, f32);
void func_80613BA0(s32, s16, f32, f32);
void func_80613A50(s32, s8);
void func_80613FB0(s32, u16, f32, u8);


s32 func_8061594C(s32 arg0) {
    s16 sp1E;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80613C48(arg0, sp1E, 0.0f, 1.0f);
    return 1;
}

s32 func_8061599C(s32 arg0) {
    s16 sp1E;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80613BA0(arg0, sp1E, 0.0f, 1.0f);
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806159EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615A3C.s")

s32 func_80615A94(s32 arg0) {
    s8 sp1F;
    D_807F5AF0++;
    func_80614F28((u8 *)&sp1F);
    func_80613A50(arg0, sp1F);
    return 1;
}

void func_80614014(s32, u16, f32, u8);

s32 func_80615ADC(s32 arg0) {
    u16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80614F28(&sp1D);
    func_80614014(arg0, sp1E, 0.0f, sp1D);
    return 1;
}

s32 func_80615B34(s32 arg0) {
    s16 sp1E;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80613AF8(arg0, sp1E, 0.0f, 1.0f);
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615B84.s")

s32 func_80615BDC(s32 arg0) {
    u16 sp1E;
    u8 sp1D;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80614F28(&sp1D);
    func_80613FB0(arg0, sp1E, 0.0f, sp1D);
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615C34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615CE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615DA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615E74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80615FA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061600C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061607C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061612C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806161D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616254.s")

void func_80614D00(Actor *, s32, s32);

s32 func_806162C4(Actor *arg0) {
    s32 sp1C;
    s32 sp18;

    D_807F5AF0++;
    func_80614FD8((u8 *)&sp1C);
    func_80614FD8((u8 *)&sp18);
    func_80614D00(arg0, sp1C, sp18);
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616318.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616374.s")

typedef struct P19cFlagState {
    u8 pad0[0x78];
    s32 unk78;
} P19cFlagState;

s32 func_806163D0(Actor *arg0) {
    P19cFlagState *temp_v1;

    temp_v1 = (P19cFlagState *)arg0->unk4;
    temp_v1->unk78 |= 0x8000;
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806163E8.s")

typedef struct P19cCountdownState {
    u8 pad0[0x88];
    s32 unk88;
} P19cCountdownState;

s32 func_80616470(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    ((P19cCountdownState *)arg0->unk4)->unk88 = arg0->unk154 - sp1E;
    return 1;
}

s32 func_806164C4(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    ((P19cCountdownState *)arg0->unk4)->unk88 = arg0->unk155[0] - sp1E;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616518.s")

typedef struct P19cGlobalCountdown {
    u8 pad0[0x4E];
    s16 unk4E;
} P19cGlobalCountdown;

s32 func_80616594(Actor *arg0) {
    u16 sp1E;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    ((P19cCountdownState *)arg0->unk4)->unk88 =
        ((P19cGlobalCountdown *)D_807FD580)->unk4E - sp1E;
    return 1;
}

typedef struct P19cCursorState {
    u8 pad0[0x68];
    u8 *unk68;
} P19cCursorState;

s32 func_806165F0(Actor *arg0) {
    s16 sp1E;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    D_807F5AF0 = ((P19cCursorState *)arg0->unk4)->unk68 + sp1E;
    return 1;
}

typedef struct P19dState {
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
} P19dState;

s32 func_80616644(Actor *arg0) {
    s16 sp1E;
    P19dState *temp_v0;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    temp_v0 = (P19dState *)arg0->unk4;
    if (temp_v0->unk88 != 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 func_806166A8(Actor *arg0) {
    s16 sp1E;
    P19dState *temp_v0;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    temp_v0 = (P19dState *)arg0->unk4;
    if (temp_v0->unk88 == 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 func_8061670C(Actor *arg0) {
    s16 sp1E;
    P19dState *temp_v0;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    temp_v0 = (P19dState *)arg0->unk4;
    if (temp_v0->unk88 > 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 func_80616770(Actor *arg0) {
    s16 sp1E;
    P19dState *temp_v0;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    temp_v0 = (P19dState *)arg0->unk4;
    if (temp_v0->unk88 < 0) {
        D_807F5AF0 = temp_v0->unk68 + sp1E;
    }
    return 1;
}

s32 func_806167D4(Actor *arg0) {
    D_807F5AF0 = ((P19dState *)arg0->unk4)->unk68;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806167EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616850.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806168E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616964.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806169C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616A1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616A9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616BA4.s")

s32 func_80616BF0(Actor *arg0) {
    D_807F5AF0++;
    arg0->unk155[0] = 0;
    arg0->unk154++;
    return 1;
}

s32 func_80616C1C(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    func_80614F28(&sp1F);
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

s32 func_80611A44();

s32 func_80616CB8(Actor *arg0) {
    u8 sp1F;
    u8 sp1E;

    D_807F5AF0++;
    func_80614F28(&sp1F);
    func_80614F28(&sp1E);
    ((P19dState *)arg0->unk4)->unk88 = (s32)(((s32)((s32)(func_80611A44() >> 0xF) % 32767) % (s32)((sp1E - sp1F) + 1)) + sp1F);
    return 1;
}

s32 func_80616D5C(Actor *arg0) {
    D_807F5AF0++;
    ((P19dState *)arg0->unk4)->unk84 = 1;
    return 1;
}

s32 func_80616D84(Actor *arg0) {
    D_807F5AF0++;
    ((P19dState *)arg0->unk4)->unk84 = 0;
    return 1;
}

typedef struct P19eActorView {
    u8 pad0[0x17C];
    void *unk17C;
} P19eActorView;

typedef struct P19eScriptTarget {
    u8 pad0[0xD];
    u8 flags;
} P19eScriptTarget;

s32 func_80616DA8(s32 arg0) {
    return 0;
}

s32 func_80616DB4(Actor *arg0) {
    P19eScriptTarget *target;
    u8 flag;

    target = (P19eScriptTarget *)((P19eActorView *)arg0)->unk17C;
    D_807F5AF0++;
    func_80614F28(&flag);
    target->flags |= flag;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80616E08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80617140.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80617238.s")

void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_80617400(Actor *arg0) {
    s16 sp36;
    u8 sp35;
    u8 sp34;
    u8 sp33;
    u8 sp32;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp36);
    func_80614F28(&sp33);
    func_80614F28(&sp32);
    func_80614F28(&sp35);
    func_80614F28(&sp34);
    if (arg0->unk60 & 4) {
        func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, sp36, sp33, sp32, sp35, sp34, 0.3f, 0);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806174B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806175C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80617770.s")

void func_80617770(Actor *, s16, u8);
void sfxStopSlotSound(Actor *, u8);
void sfxPlayActorSound(Actor *, s16, u8, u8, u8, u8, f32, s8);
void sfxSetVolumeAndPan(u8, f32, f32);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, u8);
void func_8070D8C0(Actor *, u16, u8);
void func_80617DFC(Actor *, s16);
extern u8 D_80746D60[];

typedef struct P19eActorSub4 {
    u8 pad0[0x10];
    s16 unk10;
} P19eActorSub4;

typedef struct P19eActorInner {
    P19eActorSub4 *unk0;
} P19eActorInner;

typedef struct P19eActorStateView {
    u8 pad0[0x72];
    s16 unk72;
} P19eActorStateView;

typedef struct P19eActionValue {
    u8 pad0[4];
    f32 value;
} P19eActionValue;

typedef struct P19eActionState {
    P19eActionValue *unk0;
    P19eActionValue *unk4;
    u8 pad8[0x7C];
    s32 unk84;
} P19eActionState;

s32 func_8061796C(Actor *arg0) {
    s16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80614F28(&sp1D);
    func_80617770(arg0, sp1E, sp1D);
    return 1;
}

s32 func_806179C0(Actor *arg0) {
    s16 sp2E;
    u8 sp2D;
    u8 sp2C;
    u8 sp2B;
    s8 sp2A;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp2E);
    func_80614F28(&sp2D);
    func_80614F28(&sp2B);
    func_80614F28(&sp2C);
    func_80614F28((u8 *)&sp2A);
    sfxStopSlotSound(arg0, sp2D);
    sfxPlayActorSound(arg0, sp2E, sp2C, 1, sp2D, sp2B, 1.0f, sp2A);
    return 1;
}

s32 func_80617A60(Actor *arg0) {
    f32 sp1C;
    u8 sp1B;
    u8 sp1A;

    D_807F5AF0++;
    func_80614F28(&sp1A);
    func_80614FD8((u8 *)&sp1C);
    func_80614F28(&sp1B);
    sfxSetVolumeAndPan(((u8 *)arg0)[sp1A * 2 + 0x6F], sp1C, (f32)sp1B);
    return 1;
}

s32 func_80617AF0(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    func_80614F28(&sp1F);
    sfxStopSlotSound(arg0, sp1F);
    return 1;
}

s32 func_80617B38(Actor *arg0) {
    s16 sp2E;
    u8 sp2D;
    u8 sp2C;
    s8 sp2B;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp2E);
    func_80614F28(&sp2D);
    func_80614F28(&sp2C);
    func_80614F28((u8 *)&sp2B);
    sfxPlayActorSound(arg0, sp2E, sp2C, 1, sp2D, 0xFF, 1.0f, sp2B);
    ((P19eActorStateView *)arg0)->unk72 = ((P19eActorInner *)arg0->unk4)->unk0->unk10;
    return 1;
}

s32 func_80617BD8(Actor *arg0) {
    u8 sp1F;
    u8 sp1E;

    D_807F5AF0++;
    func_80614F28(&sp1F);
    func_80614F28(&sp1E);
    sfxAllocateChannel(D_80746D60[sp1F], (f32)((f64)sp1E / 255.0));
    return 1;
}

s32 func_80617C6C(Actor *arg0) {
    u8 sp1F;

    D_807F5AF0++;
    func_80614F28(&sp1F);
    sfxStopChannel(D_80746D60[sp1F], 0);
    return 1;
}

s32 func_80617CC0(Actor *arg0) {
    u16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80614F28(&sp1D);
    func_8070D8C0(arg0, sp1E, sp1D);
    return 1;
}

s32 func_80617D14(Actor *arg0) {
    return 1;
}

void func_80617D20(Actor *arg0) {
    P19eActionState *state;
    P19eActionValue *value;

    state = (P19eActionState *)arg0->unk4;
    if (state->unk84 != 0) {
        value = state->unk4;
    } else {
        value = state->unk0;
    }
    func_80617DFC(arg0, (s16)value->value);
}

typedef struct P19e3ActionState {
    u8 pad0[0x8A];
    s16 unk8A;
    f32 unk8C;
} P19e3ActionState;

typedef struct P19e3TimerState {
    u8 pad0[0x30];
    s16 unk30;
    u8 pad32[0x5A];
    f32 unk8C;
} P19e3TimerState;

typedef struct P19e3ActorFlags {
    u8 pad0[0x146];
    s16 unk146;
} P19e3ActorFlags;

typedef struct P19e3GlobalState {
    u8 pad0[0x1F0];
    s32 unk1F0;
} P19e3GlobalState;

void func_80617D70(Actor *arg0) {
    func_80617DFC(arg0, ((P19e3ActionState *)arg0->unk4)->unk8A);
}

void func_80617D94(Actor *arg0) {
    u8 sp27;

    func_80614F28(&sp27);
    if (sp27 != 0) {
        do {
            D_807F5AF0 += 4;
            func_80614F28(&sp27);
        } while (sp27 != 0);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80617DFC.s")

s32 func_80617FFC(Actor *arg0) {
    f32 sp1C;

    D_807F5AF0++;
    func_80614FD8((u8 *)&sp1C);
    ((P19e3ActionState *)arg0->unk4)->unk8C = sp1C;
    return 1;
}

extern u32 D_80744478;

s32 func_80618048(Actor *arg0) {
    f32 var_fv0;
    P19e3TimerState *state;

    state = (P19e3TimerState *)arg0->unk4;
    if (state->unk30 & 1) {
        var_fv0 = (f32)D_80744478 * 0.5f;
    } else {
        var_fv0 = 1.0f;
    }
    state->unk8C -= var_fv0;
    if ((f64)((P19e3TimerState *)arg0->unk4)->unk8C <= 0.0) {
        D_807F5AF0++;
        return 1;
    }
    return 0;
}

void func_806180FC(Actor *arg0) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618104.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618430.s")

void func_8061849C(Actor *arg0) {
    ((P19e3GlobalState *)D_807FD580)->unk1F0 |= 0x40000;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806184BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_8061859C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618608.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618728.s")

void func_806187BC(Actor *arg0) {
    s16 sp1E;
    s16 sp1C;

    func_80614F4C((u8 *)&sp1E);
    func_80614F4C((u8 *)&sp1C);
}

void func_806187E8(Actor *arg0) {
    s16 sp1E;

    func_80614F4C((u8 *)&sp1E);
    ((P19e3ActorFlags *)arg0)->unk146 |= sp1E;
}

void func_80618820(Actor *arg0) {
    s16 sp1E;

    func_80614F4C((u8 *)&sp1E);
    ((P19e3ActorFlags *)arg0)->unk146 &= ~sp1E;
}

void func_8061885C(Actor *arg0) {
    f32 sp1C;

    func_80614FD8((u8 *)&sp1C);
}

typedef struct {
    u8 pad0[4];
    P19aState *unk4;
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
} P17b3ActorView;

typedef struct {
    u8 pad0[0x64];
    s16 unk64;
} P17b3GlobalView;

void func_80618880(Actor *arg0) {
    P17b3ActorView *actor;

    actor = (P17b3ActorView *)arg0;
    if (((P17b3GlobalView *)D_807FD580)->unk64 != 0) {
        ((P17b3GlobalView *)D_807FD580)->unk64 = 0;
        actor->unk4->unk88 = 0;
        return;
    }
    actor->unk4->unk88 = 1;
}

void func_806188B8(Actor *arg0) {
    P17b3ActorView *actor;

    actor = (P17b3ActorView *)arg0;
    if (actor->unkC0 < 0.0f) {
        actor->unk4->unk88 = 1;
        return;
    }
    actor->unk4->unk88 = 0;
}

void func_806188F4(Actor *arg0) {
    P17b3ActorView *actor;

    actor = (P17b3ActorView *)arg0;
    if ((actor->unk6A & actor->unk6C & 1) != 0) {
        actor->unk4->unk88 = 1;
        return;
    }
    actor->unk4->unk88 = 0;
}

void func_8061892C(Actor *arg0) {
    s16 value;

    func_80614F4C((u8 *)&value);
    ((P17b3ActorView *)arg0)->unkC0 = (f32)value;
}

void func_80618968(Actor *arg0) {
    f32 value;

    func_80614FD8((u8 *)&value);
    ((P17b3ActorView *)arg0)->unkC4 = value;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618998.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618B6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618C00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618C8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618CD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618D20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618D68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618E4C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618EE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80618F74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_80619018.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806190C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/19A00/func_806192A4.s")

void actorDespawn(void);

void func_80619500(void) {
    actorDespawn();
}

void *func_80619520(Actor *arg0) {
    P17b3ActorView *actor;
    void *result;

    actor = (P17b3ActorView *)arg0;
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
    func_80614F28(&value);
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
    P17b3ActorView *actor;

    actor = (P17b3ActorView *)arg0;
    actor->unk4->unk88 = actor->unkDE >= 0x3DA;
}
