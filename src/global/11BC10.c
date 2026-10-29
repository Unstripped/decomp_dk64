#include "common.h"
#include "actor.h"

extern u8 D_807444FC;
extern u32 D_8076A064;
extern s32 D_8076A0A8;
extern Actor *D_807FBB4C;

void *func_80610FE8(s32);
u32 func_806119A0(void);
f32 func_806119FC(void);
char randomNonNegative(void); // FAKE: byte-return home steers func_8071CDE0's spill layout (real return is s32)
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 cosApprox(f32);
f32 sinApprox(f32);

typedef struct {
    u8 pad0[0x32C];
    u8 unk32C;
    u8 pad32D[0x13];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[0x1C];
    void *unk384;
} RotatingEffectActorView;

void func_80716F10(RotatingEffectActorView *arg0, void *arg1) {
    f32 sp68[4][4];
    f32 sp28[4][4];

    guScaleF(sp68, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp28, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp68, sp28, sp68);
    guMtxF2L(sp68, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
} RotationState;

void func_80716FB4(RotatingEffectActorView *arg0, void *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];
    RotationState *var_v1;

    var_v1 = (RotationState *)arg0->unk384;
    if (var_v1 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((RotationState *)arg0->unk384)->unk0 = (func_806119A0() % 36000U) / 100U;
        ((RotationState *)arg0->unk384)->unk4 = (func_806119A0() % 400U) / 100U;
        var_v1 = (RotationState *)arg0->unk384;
    }
    var_v1->unk0 += var_v1->unk4;
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, ((RotationState *)arg0->unk384)->unk0, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}

#ifdef NON_MATCHING
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Fx11BAMotion10;

void func_80717100(RotatingEffectActorView *arg0, void *arg1) {
    Fx11BAMotion10 *var_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xA);
        var_v1 = arg0->unk384;
        var_v1->unk0 = (s16) ((randomNonNegative() >> 15) % 0xFFF);
        var_v1->unk2 = arg0->unk35C;
        var_v1->unk4 = arg0->unk35C >> 16;
        var_v1->unk6 = arg0->unk340;
        var_v1->unk8 = arg0->unk348;
    }
    var_v1 = arg0->unk384;
    var_v1->unk0 = var_v1->unk4 + var_v1->unk0;
    arg0->unk340 = func_80612794(var_v1->unk0) * var_v1->unk2 + var_v1->unk6;
    arg0->unk348 = func_80612790(var_v1->unk0) * var_v1->unk2 + var_v1->unk8;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717100.s")
#endif


#ifdef NON_MATCHING
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Fx11BAMotion8;

void lightSetFlags();
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8071720C(RotatingEffectActorView *arg0, void *arg1) {
    Fx11BAMotion8 *var_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        var_v1 = arg0->unk384;
        var_v1->unk0 = (randomNonNegative() >> 15) % 0xFFF;
        var_v1->unk2 = ((randomNonNegative() >> 15) % 10) + 2;
        var_v1->unk4 = 0;
        var_v1->unk6 = -50 - (((randomNonNegative() >> 15) % 10000) % 600);
    }
    var_v1 = arg0->unk384;
    arg0->unk344 = (f32) ((f64) arg0->unk344 - (f64) var_v1->unk6 / 100.0);
    var_v1->unk6 += 0x14;
    arg0->unk340 = (f32) ((f64) arg0->unk340 + 0.04 * (f64) var_v1->unk4 * (f64) func_80612794(var_v1->unk0));
    arg0->unk348 = (f32) ((f64) arg0->unk348 + 0.04 * (f64) var_v1->unk4 * (f64) func_80612790(var_v1->unk0));
    var_v1->unk0 += 0x50;
    var_v1->unk4 += var_v1->unk2;
    if (arg0->unk35C != 0) {
        lightSetFlags(1);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 40.0f, 0, 0xFF,
                 (randomNonNegative() >> 15) % 0xFF, 0xFF);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071720C.s")
#endif


#ifdef NON_MATCHING
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Fx11BAMotion12;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    u8 pad360[0xF];
    u8 unk36F;
    u8 pad370[0x14];
    Fx11BAMotion12 *unk384;
} Fx11BAEffectActor;

void func_80717404(Fx11BAEffectActor *arg0, void *arg1) {
    Fx11BAMotion12 *motion;
    s16 *var_s2;
    f64 scale;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        motion = arg0->unk384;
        var_s2 = (s16 *) &arg0->unk35C;
        if (*var_s2 != 0) {
            motion->unk0 = (f32) (((randomNonNegative() >> 15) % 200) + *var_s2 - 100);
        } else {
            motion->unk0 = (f32) ((randomNonNegative() >> 15) % 0xFFF);
        }
        scale = (arg0->unk36F != 0) ? 4.0 : 1.0;
        motion->unk4 = (f32) ((((randomNonNegative() >> 15) % 10) + 5) * scale);
        motion->unk8 = (f32) (var_s2[1] + ((randomNonNegative() >> 15) % 6));
    }
    motion = arg0->unk384;
    var_s2 = (s16 *) &arg0->unk35C;
    if (arg0->unk36F != 0) {
        arg0->unk340 = (f32) ((f64) arg0->unk340 + 4.0 * ((f64) func_80612794((s16) motion->unk0) * (0.01 * (f64) var_s2[1])));
        arg0->unk344 = (f32) ((f64) arg0->unk344 + 4.0 * ((f64) func_80612790((s16) motion->unk0) * (0.01 * (f64) var_s2[1])));
    } else {
        arg0->unk340 = (f32) ((f64) arg0->unk340 + (f64) func_80612794((s16) motion->unk0) * (0.04 * (f64) var_s2[1]));
        arg0->unk348 = (f32) ((f64) arg0->unk348 + (f64) func_80612790((s16) motion->unk0) * (0.04 * (f64) var_s2[1]));
        if (*var_s2 == 0) {
            arg0->unk344 = arg0->unk344 + motion->unk8;
            motion->unk8 = (f32) ((f64) motion->unk8 - 0.5);
        } else {
            arg0->unk344 = (f32) ((f64) arg0->unk344 + (f64) motion->unk8 * 0.2);
        }
    }
    var_s2[1] = (s16) (var_s2[1] + motion->unk4);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717404.s")
#endif


void func_80714950(s32);
void func_80717404();
void func_8071498C(void *);
void func_807149B8(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
extern s32 D_8074E880[];

void func_80717760(RotatingEffectActorView *arg0, u8 *arg1) {
    s32 temp_v0;

    temp_v0 = arg0->unk35C;
    *((u8 *)arg0 + 0x36D) = 0;
    if (temp_v0 != 0) {
        arg0->unk35C = temp_v0 - 1;
        func_807149B8(1);
        func_8071498C(func_80717404);
        func_80714950(0xA);
        func_80714CC0(D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 0.8f, arg0->unk340, arg0->unk344, arg0->unk348);
        return;
    }
    *arg1 = 1;
}

typedef struct {
    s16 unk0;
    s16 unk2;
} RandomDriftState;

void func_80717814(RotatingEffectActorView *arg0, void *arg1) {
    RotatingEffectActorView *actor;
    RandomDriftState *motion;

    actor = arg0;
    if (actor->unk384 == NULL) {
        actor->unk384 = func_80610FE8(4);
        motion = actor->unk384;
        motion->unk0 = (randomNonNegative() >> 15) % 4095;
        motion->unk2 = ((randomNonNegative() >> 15) % 10) + 2;
    }
    motion = actor->unk384;
    actor->unk340 += 0.2 * actor->unk35C * func_80612794(motion->unk0);
    actor->unk344 += 0.2 * actor->unk35C * func_80612790(motion->unk0);
    motion->unk0 += 0x46;
    actor->unk35C += motion->unk2;
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

typedef struct {
    u8 pad0[0x32C];
    u8 unk32C;
    u8 pad32D[0xB];
    ScaleHolder *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[0x1C];
    OrbitMotionState *unk384;
    u8 pad388[4];
    u16 unk38C;
} OrbitEffectActorView;

void func_80717930(OrbitEffectActorView *arg0, void *arg1) {
    f32 temp_fv0;
    f32 call_result;
    s32 temp_v1;
    OrbitMotionState *temp_s1;
    void *temp_v0;
    ScaleHolder *temp_v0_2;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xA);
        temp_v0 = arg0->unk384;
        ((OrbitMotionState *)temp_v0)->unk0 = (randomNonNegative() >> 0xF) % 4095;
        ((OrbitMotionState *)temp_v0)->unk2 = arg0->unk340;
        ((OrbitMotionState *)temp_v0)->unk4 = arg0->unk348;
        temp_v1 = arg0->unk35C;
        if (temp_v1 & 0x8000) {
            arg0->unk35C = temp_v1 & 0xFFFF7FFF;
            ((OrbitMotionState *)temp_v0)->unk6 = 0xC8;
            ((OrbitMotionState *)temp_v0)->unk8 = 0xA;
        } else {
            ((OrbitMotionState *)temp_v0)->unk6 = 0x46;
            ((OrbitMotionState *)temp_v0)->unk8 = 0xF;
        }
        temp_v0_2 = arg0->unk338;
        if (temp_v0_2 != NULL) {
            temp_fv0 = temp_v0_2->unk4->unk38 / 0.15;
            ((OrbitMotionState *)temp_v0)->unk8 = ((OrbitMotionState *)temp_v0)->unk8 * temp_fv0;
            arg0->unk35C = arg0->unk35C * temp_fv0;
        }
    }
    temp_s1 = arg0->unk384;
    if (arg0->unk38C & 2) {
        arg0->unk340 = func_80612794(temp_s1->unk0) * arg0->unk35C + D_807FBB4C->unk7C;
        arg0->unk348 = func_80612790(temp_s1->unk0) * arg0->unk35C + D_807FBB4C->unk84;
    } else {
        arg0->unk340 = func_80612794(temp_s1->unk0) * arg0->unk35C + temp_s1->unk2;
        arg0->unk348 = func_80612790(temp_s1->unk0) * arg0->unk35C + temp_s1->unk4;
    }
    arg0->unk344 += temp_s1->unk8 * 0.1;
    temp_s1->unk0 += temp_s1->unk6;
}

typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    u8 pad34E[2];
    u8 unk350;
    u8 pad351[0xB];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[5];
    u8 unk36D;
    u8 pad36E[0x16];
    void *unk384;
} TimedEffectActorView;


void func_80714998(s32);
void func_80718380();
extern u8 D_8071FEF4;

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80717B64.s")

void func_80717CE8(arg0, arg1)
TimedEffectActorView *arg0;
s8 *arg1;
{
    if (arg0->unk36D != 0xFF) {
        arg0->unk36D += 0x14;
    }
    if ((s32) arg0->unk36D >= 0xEB) {
        arg0->unk36D = 0xFFU;
    }
    arg0->unk344 = (f32) ((f64) arg0->unk344 - ((f64) arg0->unk35C / 100.0));
}

void func_80717D4C(arg0, arg1)
TimedEffectActorView *arg0;
s8 *arg1;
{
    arg0->unk344 = (f32) ((f64) arg0->unk344 - ((f64) arg0->unk35C / 100.0));
}

void func_80717D84(TimedEffectActorView *arg0, s8 *arg1) {
    s32 temp_v0;
    u8 temp_v1;

    temp_v0 = arg0->unk35C;
    temp_v1 = arg0->unk36D;
    if (temp_v0 < (s32) temp_v1) {
        arg0->unk36D = (u8) (temp_v1 - temp_v0);
        return;
    }
    arg0->unk36D = 0U;
    *arg1 = 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Fx11BADriftState;

void effectDriftXZUpdate(RotatingEffectActorView *arg0, void *arg1) {
    Fx11BADriftState *state;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x10);
        state = arg0->unk384;
        state->unk0 = arg0->unk340;
        state->unk4 = arg0->unk348;
        state->unk8 = 0;
        state->unkA = 0;
        state->unkC = (randomNonNegative() % 10000) % 150 - 75;
        state->unkE = (randomNonNegative() % 10000) % 150 - 75;
    }
    state = arg0->unk384;
    arg0->unk340 = (f32) ((f64) func_80612794(state->unk8) * 6.0 + (f64) state->unk0);
    arg0->unk348 = (f32) ((f64) func_80612794(state->unkA) * 6.0 + (f64) state->unk4);
    state->unk8 += state->unkC;
    state->unkA += state->unkE;
    arg0->unk344 = (f32) ((f64) arg0->unk344 - (f64) arg0->unk35C / 100.0);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} VelocityMotionState;

void effectShrinkOffsetUpdate(arg0, arg1)
TimedEffectActorView *arg0;
s8 *arg1;
{
    VelocityMotionState *state;
    void *parent;

    if (arg0->unk384 == NULL) {
        parent = arg0->unk338;
        arg0->unk384 = func_80610FE8(0x10);
        state = arg0->unk384;
        if (parent != NULL) {
            state->unk0 = (*(f32 *) ((u8 *) parent + 0xB8) * 0.025f) * func_80612794(*(s16 *) ((u8 *) parent + 0xEE));
            state->unk4 = (*(f32 *) ((u8 *) parent + 0xB8) * 0.025f) * func_80612790(*(s16 *) ((u8 *) parent + 0xEE));
        } else {
            state->unk0 = 0.0f;
            state->unk4 = 0.0f;
        }
        state->unk8 = arg0->unk360;
        state->unkC = 0.2f;
    }
    state = arg0->unk384;
    arg0->unk344 = (f32) ((f64) arg0->unk344 - (f64) arg0->unk35C / 100.0);
    arg0->unk340 += state->unk0;
    arg0->unk348 += state->unk4;
    state->unk0 = (f32) ((f64) state->unk0 * 0.93);
    state->unk4 = (f32) ((f64) state->unk4 * 0.93);
}


void func_80718080(TimedEffectActorView *arg0) {
    f32 temp_fv0;
    VelocityMotionState *temp_v0;

    effectShrinkOffsetUpdate();
    temp_v0 = arg0->unk384;
    arg0->unk360 = temp_v0->unkC * temp_v0->unk8;
    arg0->unk364 = arg0->unk360;
    temp_fv0 = temp_v0->unkC;
    if (temp_fv0 < 2.0f) {
        temp_v0->unkC = (f32) ((f64) temp_fv0 + 0.2);
    }
}

void func_807180F4(s32 arg0, s32 arg1) {
    func_80717D4C();
    func_80716FB4((RotatingEffectActorView *)arg0, (void *)arg1);
}

void func_80718124(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_807149B8(1);
    func_80714998(3);
    func_8071498C(&func_80718380);
    func_80714CC0((s32)&D_8071FEF4, arg0, arg1, arg2, arg3);
}

extern s16 D_807502D0;

void effectFallUpdate(TimedEffectActorView *arg0, s8 *arg1) {
    s16 *temp_v0;
    s16 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(2);
        arg0->unk384 = temp_v0;
        *temp_v0 = 0;
        var_v1 = arg0->unk384;
    }
    arg0->unk344 += (f32) *var_v1;
    *var_v1 -= 1;
    var_v1 = arg0->unk384;
    if (*var_v1 < D_807502D0) {
        *var_v1 = D_807502D0;
    }
    if (arg0->unk344 < (f32) arg0->unk35C) {
        *arg1 = 1;
        func_80718124((f32) ((f64) arg0->unk360 * 1.5), arg0->unk340, arg0->unk35C, arg0->unk348);
    }
}

typedef f32 EffectMatrix[4][4];

void func_8071827C(TimedEffectActorView *arg0, s8 *arg1) {
    EffectMatrix sp70;
    EffectMatrix sp30;
    u8 temp_v0;

    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    temp_v0 = arg0->unk36D;
    arg0->unk360 = (f32) ((f64) arg0->unk360 + 0.07);
    arg0->unk364 = (f32) ((f64) arg0->unk364 + 0.07);
    if ((s32) temp_v0 >= 0xA) {
        arg0->unk36D = (u8) (temp_v0 - 0xA);
    } else {
        arg0->unk36D = 0U;
    }
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
}

void func_80718380(TimedEffectActorView *arg0, s8 *arg1) {
    EffectMatrix sp70;
    EffectMatrix sp30;
    u32 temp_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(4);
        temp_v1 = (u32) (func_806119A0() % 36000U) / 100U;
        *(f32 *) arg0->unk384 = (f32) temp_v1;
    }
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guRotateF(sp30, *(f32 *) arg0->unk384, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    if ((s32) arg0->unk36D >= 0xA) {
        arg0->unk36D -= 0xA;
    } else {
        arg0->unk36D = 0U;
    }
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
    if (arg0->unk36D == 0) {
        *arg1 = 1;
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
} Ub3TwoFloats;

typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
} Ub3TargetView;

void func_807184F4(TimedEffectActorView *arg0, s8 *arg1) {
    EffectMatrix sp70;
    EffectMatrix sp30;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((Ub3TwoFloats *) arg0->unk384)->unk0 = 0.0f;
        ((Ub3TwoFloats *) arg0->unk384)->unk4 = (f32) ((func_806119A0() % 400U) / 100U);
    }
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, ((Ub3TwoFloats *) arg0->unk384)->unk0, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    if (arg0->unk338 != NULL) {
        arg0->unk344 = ((Ub3TargetView *) arg0->unk338)->unkAC;
    }
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    if (arg0->unk35C != 0) {
        ((Ub3TwoFloats *) arg0->unk384)->unk0 += ((Ub3TwoFloats *) arg0->unk384)->unk4;
        arg0->unk360 = (f32) ((f64) arg0->unk360 - 0.02);
        arg0->unk364 = (f32) ((f64) arg0->unk364 - 0.02);
        if (arg0->unk36D >= 0xA) {
            arg0->unk36D -= 0xA;
        } else {
            arg0->unk36D = 0;
        }
    }
    ((u8 *) arg0)[0x32C] = 3;
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
} M2Interpolation;

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807186C8.s")


typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
} NM2ProjectileSource;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} NM2Projectile;

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807189BC.s")


typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} NM2MotionState;


#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80718BF4.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071910C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807195D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_807197B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719A0C.s")

#ifdef NON_MATCHING
void func_80719A0C(TimedEffectActorView *, s8 *);

void func_80719B88(TimedEffectActorView *arg0, s8 *arg1) {
    u8 temp_t6;
    u8 temp_v0;
    u8 var_v1;

    func_80719A0C(arg0, arg1);
    temp_v0 = arg0->unk36D;
    var_v1 = 0x10;
    arg0->unk344 = (f32)((f64)arg0->unk344 + 0.8);
    if ((s32)temp_v0 < 0x10) {
        var_v1 = temp_v0;
    }
    temp_t6 = temp_v0 - var_v1;
    arg0->unk36D = temp_t6;
    if (!(temp_t6 & 0xFF)) {
        *arg1 = 1;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719B88.s")
#endif



#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_80719C00.s")

void effectSpriteMotionUpdate(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp1C;
    f32 temp_fv1;
    TimedEffectActorView *var_a1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((RotationState *)arg0->unk384)->unk0 = 3.2f;
        ((RotationState *)arg0->unk384)->unk4 = (f32)arg0->unk35C;
    }
    ((RotationState *)arg0->unk384)->unk0 = (f32)((f64)((RotationState *)arg0->unk384)->unk0 - 0.2);
    if ((f64)((RotationState *)arg0->unk384)->unk0 < 0.8) {
        ((RotationState *)arg0->unk384)->unk0 = 0.8f;
    }
    sp1C = sinApprox(((RotationState *)arg0->unk384)->unk4 * 0.017453292f) * ((RotationState *)(var_a1 = arg0)->unk384)->unk0;
    temp_fv1 = cosApprox(((RotationState *)arg0->unk384)->unk4 * 0.017453292f);
    temp_fv1 = temp_fv1 * ((RotationState *)var_a1->unk384)->unk0;
    arg0->unk340 = arg0->unk340 + sp1C;
    var_a1->unk348 = var_a1->unk348 + temp_fv1;
    arg0->unk344 = var_a1->unk344 + 1.0f;
}


void effectSpriteMatrixUpdate(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp78[4][4];
    f32 sp38[4][4];
    f32 sp34;
    f32 Fx11BDpad;
    f32 temp_fv0;
    u8 *temp_v0;
    f32 sp24;

    temp_fv0 = (f32)(*((u8 *)arg0 + 0x351) + (*(s16 *)((u8 *)arg0 + 0x34E) * 2));
    temp_v0 = (u8 *)(s32)arg0->unk35C;
    if (temp_fv0 < 28.0f) {
        sp34 = temp_fv0;
    } else {
        sp34 = 56.0f - temp_fv0;
    }
    if (*temp_v0 != 0) {
        arg0->unk340 -= 12.0f;
        *temp_v0 -= 1;
    }
    if (sinApprox((f32)(((f64)temp_fv0 / 56.0) * 6.2831854820251465)) > 0.0f) {
        sp24 = sinApprox((f32)(((f64)temp_fv0 / 56.0) * 6.2831854820251465));
    } else {
        sp24 = -sinApprox((f32)(((f64)temp_fv0 / 56.0) * 6.2831854820251465));
    }
    guScaleF(sp78, arg0->unk360, arg0->unk364, 0.0f);
    guTranslateF(sp38, (f32)((f64)arg0->unk340 + ((f64)sp34 * 0.5)), arg0->unk344 - (sp24 * 15.0f), arg0->unk348);
    guMtxCatF(sp78, sp38, sp78);
    guMtxF2L(sp78, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 3;
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Fx11BDMotion3;

#ifdef NON_MATCHING
void func_8071A1E4(TimedEffectActorView *arg0, s8 *arg1) {
    s32 Fx11BDt5;
    s32 Fx11BDa;
    s32 Fx11BDb;
    f32 sp8C[4][4];
    f32 sp4C[4][4];
    s8 sp4B;
    s8 sp4A;
    s8 sp49;
    s8 sp48;
    s16 sp46;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (arg0->unk384 == NULL) {
        sp48 = (u32)-(s32)(func_806119A0() / 10000U) % 30U;
        sp46 = (u32)(func_806119A0() / 10000U) % 180U;
        guRotateF(sp8C, (f32)sp48, 0.0f, 1.0f, 0.0f);
        sp4B = arg0->unk35C >> 0x10;
        Fx11BDt5 = arg0->unk35C;
        sp4A = Fx11BDt5 >> 8;
        sp49 = Fx11BDt5;
        arg0->unk384 = func_80610FE8(0xC);
        guAlignF(sp4C, (f32)sp46, (f32)sp4B, (f32)sp4A, (f32)sp49);
        guMtxCatF(sp8C, sp4C, sp8C);
        guMtxXFMF(sp8C, 0.0f, 0.0f, -2.0f, &sp40, &sp3C, &sp38);
        ((Fx11BDMotion3 *)arg0->unk384)->unk0 = (f32)((f64)sp40 * 0.5);
        if (sp3C < 0.0f) {
            ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)-sp3C * 0.5);
        } else {
            ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)sp3C * 0.5);
        }
        ((Fx11BDMotion3 *)arg0->unk384)->unk8 = (f32)((f64)sp38 * 0.5);
    }
    arg0->unk340 += ((Fx11BDMotion3 *)arg0->unk384)->unk0;
    arg0->unk344 += ((Fx11BDMotion3 *)arg0->unk384)->unk4;
    arg0->unk348 += ((Fx11BDMotion3 *)arg0->unk384)->unk8;
    Fx11BDa = *((s32 *)((u8 *)arg0 + 0x354));
    Fx11BDb = *((s32 *)((u8 *)arg0 + 0x358));
    if ((Fx11BDa - Fx11BDb) < 0xA) {
        ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)((Fx11BDMotion3 *)arg0->unk384)->unk4 - 0.1);
        if ((s32)arg0->unk36D >= 0x16) {
            arg0->unk36D = arg0->unk36D - 0x14;
            return;
        }
        arg0->unk36D = 0;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071A1E4.s")
#endif

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} EffectTimer;

typedef struct {
    u8 pad0[0x330];
    EffectTimer *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[2];
    s16 unk34E;
    u8 pad34F[0xC];
    s32 unk35C;
} TimedLightActorView;

void lightSetFlags();
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

typedef struct {
    u8 pad0[0x88];
    s32 unk88;
} LightOwnerView;

extern LightOwnerView *D_807FD580;
extern void *D_80028C30;

void func_8071A440(TimedLightActorView *arg0, s8 *arg1) {
    f32 var_fv0;

    var_fv0 = (f32)(arg0->unk330->unk16 - arg0->unk34E) / (f32)arg0->unk330->unk16;
    if ((f64)var_fv0 > 0.7) {
        var_fv0 = 1.0f;
    }
    if ((D_807FD580->unk88 == arg0->unk35C) && ((void *)arg0 == D_80028C30)) {
        lightSetFlags(1, arg0);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f,
                 (f32)((f64)var_fv0 * 50.0), 0, 0xFF,
                 (u32)((-80.0f * var_fv0) + 255.0f),
                 (u32)((-205.0f * var_fv0) + 255.0f));
    }
}

extern s32 D_8002FBB0[];
extern s32 D_8002FBC0;
void timedLightOrbitUpdate(TimedLightActorView *arg0, s8 *arg1) {
    f32 var_fv0;
    s32 *var_v0;

    var_fv0 = (f32)(arg0->unk330->unk16 - arg0->unk34E) / (f32)arg0->unk330->unk16;
    if ((f64)var_fv0 > 0.7) {
        var_fv0 = 1.0f;
    }
    var_v0 = &D_8002FBB0[0];
    do {
        if ((s32)arg0 == *var_v0) {
            lightSetFlags(1);
            lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f,
                     (f32)((f64)var_fv0 * 50.0), 0, 0xFF,
                     (u32)((-80.0f * var_fv0) + 255.0f),
                     (u32)((-205.0f * var_fv0) + 255.0f));
            return;
        }
        var_v0++;
    } while (var_v0 != &D_8002FBC0);
}


void func_8071A8B0(TimedLightActorView *arg0, s8 *arg1) {
    f32 var_fv0;
    f32 var_ft4;
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = arg0->unk330->unk16;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) {
        var_fv0 = 1.0f;
    }
    temp_v0_2 = arg0->unk35C;
    if (((u32)temp_v0_2 >> 16) != 0) {
        var_ft4 = (f32)(temp_v0_2 & 0xFFFF) * var_fv0;
    } else {
        var_ft4 = (f32)(temp_v0_2 & 0xFFFF);
    }
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, var_ft4, 0, 0xFF, (u32)((-80.0f * var_fv0) + 255.0f), (u32)((-205.0f * var_fv0) + 255.0f));
}

void func_8071AADC(TimedLightActorView *arg0, s8 *arg1) {
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = arg0->unk330->unk16;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) {
        var_fv0 = 1.0f;
    }
    temp_v0_2 = arg0->unk35C;
    if (((u32)temp_v0_2 >> 16) != 0) {
        var_fv1 = (f32)(temp_v0_2 & 0xFFFF) * var_fv0;
    } else {
        var_fv1 = (f32)(temp_v0_2 & 0xFFFF);
    }
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, var_fv1, 0, 0xFF, 0xFF, 0xFF);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071ABDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071AF30.s")

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

typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x12];
    s16 unk35E;
    u8 pad360[0x24];
    void *unk384;
} MotionEffectActorView;

void func_8071B1AC(MotionEffectActorView *arg0, s8 *arg1) {
    f32 new_var;
    f32 speed;

    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 - ((f64)speed * 0.5));
    new_var = func_80612794(arg0->unk35E);
    arg0->unk340 = (f32)(arg0->unk340 + (0.35f * new_var));
    new_var = func_80612790(arg0->unk35E);
    arg0->unk348 = (f32)(arg0->unk348 + (0.35f * new_var));
}

void func_8071B24C(MotionEffectActorView *arg0, s8 *arg1) {
    f32 new_var;
    f32 speed;

    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)speed * 0.5));
    new_var = func_80612794(arg0->unk35E);
    arg0->unk340 = (f32)(arg0->unk340 + (0.35f * new_var));
    new_var = func_80612790(arg0->unk35E);
    arg0->unk348 = (f32)(arg0->unk348 + (0.35f * new_var));
}

void func_8071B2EC(MotionEffectActorView *arg0, s8 *arg1) {
    f32 speed;
    f32 call_result;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((MotionState *)arg0->unk384)->unk0 = (f32)((MotionParentView *)arg0->unk338)->unkEE;
        ((MotionState *)arg0->unk384)->unk4 = ((MotionParentView *)arg0->unk338)->unkB8 + 30.0f;
    }
    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)speed * 0.5));
    speed = (f32)((f64)((MotionState *)arg0->unk384)->unk4 * 0.02);
    call_result = func_80612794((s16)(s32)((MotionState *)arg0->unk384)->unk0);
    arg0->unk340 = (f32)(arg0->unk340 + (speed * call_result));
    call_result = func_80612790((s16)(s32)((MotionState *)arg0->unk384)->unk0);
    arg0->unk348 = (f32)(arg0->unk348 + (speed * call_result));
    ((MotionState *)arg0->unk384)->unk4 -= 15.0f;
    if (((MotionState *)arg0->unk384)->unk4 < 0.0f) {
        ((MotionState *)arg0->unk384)->unk4 = 0.0f;
    }
}

void func_8071B44C(MotionEffectActorView *arg0, s8 *arg1) {
    f32 speed;
    f32 call_result;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(4);
        ((MotionState *)arg0->unk384)->unk0 = ((MotionParentView *)arg0->unk338)->unkB8;
    }
    speed = 0.35f;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)speed * 0.5));
    speed = (f32)((f64)((MotionState *)arg0->unk384)->unk0 * 0.02);
    call_result = func_80612794(arg0->unk35E);
    arg0->unk340 = (f32)(arg0->unk340 + (speed * call_result));
    call_result = func_80612790(arg0->unk35E);
    arg0->unk348 = (f32)(arg0->unk348 + (speed * call_result));
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B520.s")


void func_8071B758(TimedEffectActorView *arg0, s8 *arg1) {
    f32 ratio;
    s32 intensity;

    ratio = (f32)(*((s16 *)((u8 *)arg0->unk330 + 0x16)) - *((s16 *)((u8 *)arg0 + 0x34E))) / (f32)*((s16 *)((u8 *)arg0->unk330 + 0x16));
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    intensity = (u32)((-155.0f * ratio) + 255.0f) & 0xFF;
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 50.0f, 0, intensity, intensity, intensity);
}

void func_8071B89C(TimedEffectActorView *arg0, s8 *arg1) {
    f32 temp_fv0;
    f32 divisor;
    s16 var_v0;

    divisor = 4.0f;
    var_v0 = *((s16 *)((u8 *)arg0 + 0x34E));
    if (var_v0 >= 5) {
        var_v0 = 4;
    }
    temp_fv0 = (f32)((f64)((f32)var_v0 / divisor) * 3.0);
    arg0->unk360 = temp_fv0;
    arg0->unk364 = temp_fv0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071B8EC.s")

typedef struct {
    f32 angle;
    f32 speed;
} RandomRotationState;

void func_8071BB14(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(8);
        ((RandomRotationState *)arg0->unk384)->angle = (f32)((func_806119A0() % 36000U) / 100U);
        ((RandomRotationState *)arg0->unk384)->speed = (f32)((f64)(func_806119A0() % 10000U) / 7000.0);
    }
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)((RandomRotationState *)arg0->unk384)->speed + 1.0));
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, ((RandomRotationState *)arg0->unk384)->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} VelocityState;

void func_8071BC80(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    VelocityState *var_v0;

    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        guRotateF(sp90, -(f32)((func_806119A0() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32)((arg0->unk35C * 0x168) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, 10.0f, &sp48, &sp44, &sp40);
        ((VelocityState *)arg0->unk384)->unk0 = sp48;
        ((VelocityState *)arg0->unk384)->unk4 = sp44;
        ((VelocityState *)arg0->unk384)->unk8 = sp40;
        var_v0 = arg0->unk384;
    }
    arg0->unk340 += var_v0->unk0;
    arg0->unk344 += var_v0->unk4;
    arg0->unk348 += var_v0->unk8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071BE04.s")

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} FxInt1Timer16;

typedef struct {
    u8 pad0[0x330];
    FxInt1Timer16 *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[2];
    s16 unk34E;
    u8 pad350;
    u8 unk351;
    u8 pad352[0xA];
    u32 unk35C;
} FxInt1FadeView;

void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void func_807149FC(s32);
void func_8071C24C();
extern u8 D_807201D4;

void func_8071C004(FxInt1FadeView *arg0, s8 *arg1) {
    f64 ratio;
    s32 temp_v0;
    s16 temp_v0_2;
    s16 sp44[3];
    f32 temp_fv0;
    f32 temp_fv1;
    f32 frac;

    if (D_8076A0A8 == 0xAA) {
        sp44[0] = 0xFF; sp44[1] = 0x46;
        sp44[2] = 0;
    } else {
        sp44[0] = 0xFF; sp44[1] = 0xFF; sp44[2] = 0xFF;
    }
    temp_v0 = arg0->unk35C;
    switch (temp_v0) {
        case 0:
            temp_v0_2 = arg0->unk34E;
            if ((temp_v0_2 == 0xA) && (arg0->unk351 == 0)) {
                func_806086CC(arg0->unk340, arg0->unk344, arg0->unk348, 0xE4, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
                func_807149FC(-1);
                func_807149B8(1);
                func_8071498C(func_8071C24C);
                func_80714CC0((s32)&D_807201D4, 0.8f, arg0->unk340, arg0->unk344, arg0->unk348);
                return;
            }
            temp_fv0 = (f32)(arg0->unk330->unk16 * 2);
            temp_fv1 = (f32)((temp_v0_2 * 2) + arg0->unk351);
            ratio = (f64)((temp_fv0 - temp_fv1) / temp_fv0);
            frac = (f32)(1.0 - ratio);
            lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f * frac, 0, 0xFF, sp44[1], sp44[2]);
            return;
        case 1:
            temp_fv0 = (f32)(arg0->unk330->unk16 * 2);
            temp_fv1 = (f32)((arg0->unk34E * 2) + arg0->unk351);
            frac = (temp_fv0 - temp_fv1) / temp_fv0;
            lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f * frac, 0, 0xFF, sp44[1], sp44[2]);
            return;
    }
}

void func_80714944(s32);
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
extern u8 D_8071FB54;

void func_8071C24C(TimedEffectActorView *arg0, u8 *arg1) {
    f32 *temp_v0_2;
    f32 sp50;
    s16 sp48[3];
    f32 *temp_v0;

    if (*(s32 *)&arg0->unk384 == 0) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        *temp_v0 = 6.0f;
    }
    if (D_8076A0A8 == 0xAA) {
        sp48[0] = 0xFF; sp48[1] = 0x46;
        sp48[2] = 0;
    } else {
        sp48[0] = 0xFF; sp48[1] = 0xFF; sp48[2] = 0xFF;
    }
    temp_v0_2 = arg0->unk384;
    arg0->unk340 = arg0->unk340 + 1.0f;
    arg0->unk344 += *temp_v0_2;
    *temp_v0_2 = (f64)*temp_v0_2 - 0.15;
    sp50 = arg0->unk344;
    if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp50) == 0) {
        *arg1 = 1;
    } else if ((arg0->unk344 < sp50) && ((f64)*(f32 *)arg0->unk384 < 0.0)) {
        *arg1 = 1;
    }
    if (*arg1 != 0) {
        func_806086CC(arg0->unk340, arg0->unk344, arg0->unk348, 0xEA, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
        func_80714998(2);
        func_807149B8(1);
        func_80714950(1);
        func_8071498C(func_8071C004);
        func_80714944(7);
        func_80714CC0((s32)&D_8071FB54, 0.667f, arg0->unk340, sp50 + 10.0f, arg0->unk348);
    }
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f, 0, sp48[0], sp48[1], sp48[2]);
}

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} LightTimer;

typedef struct {
    u8 pad0[0x330];
    LightTimer *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    s16 unk34E;
    u8 pad350;
    u8 unk351;
    u8 pad352[0xA];
    u32 unk35C;
} TimedLightEffectActorView;


void func_8071C48C(TimedLightEffectActorView *arg0, s8 *arg1) {
    f32 sp3C;
    f32 sp38;
    s16 temp_v0;
    u32 temp_v0_2;

    temp_v0 = arg0->unk330->unk16;
    sp3C = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)sp3C > 0.7) {
        sp3C = 1.0f;
    }
    temp_v0_2 = arg0->unk35C;
    if ((temp_v0_2 >> 0x10) != 0) {
        sp38 = (f32)(s32)(temp_v0_2 & 0xFFFF) * sp3C;
    } else {
        sp38 = (f32)(s32)(temp_v0_2 & 0xFFFF);
    }
    lightSetFlags(1, arg0);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, sp38, 0, 0,
             (u32)((-80.0f * sp3C) + 255.0f), 0xFF);
}

void func_8071C620(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    VelocityState *var_v0;

    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        guRotateF(sp90, (f32)((func_806119A0() % 36000U) / 100U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32)((func_806119A0() % 36000U) / 100U), 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp90, sp50, sp90);
        guRotateF(sp90, (f32)((func_806119A0() % 36000U) / 100U), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, 0.5f, &sp4C, &sp48, &sp44);
        ((VelocityState *)arg0->unk384)->unk0 = sp4C;
        ((VelocityState *)arg0->unk384)->unk4 = sp48;
        ((VelocityState *)arg0->unk384)->unk8 = sp44;
        var_v0 = arg0->unk384;
    }
    arg0->unk340 += var_v0->unk0;
    arg0->unk344 += var_v0->unk4;
    arg0->unk348 += var_v0->unk8;
}

void func_8071C818(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];

    arg0->unk360 = (f32)((f64)arg0->unk360 - 0.05);
    arg0->unk364 = (f32)((f64)arg0->unk364 - 0.05);
    if (arg0->unk360 <= 0.0f) {
        *arg1 = 1;
    }
    arg0->unk35C = arg0->unk35C + 5;
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}

void func_8071C914(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp70[4][4];
    f32 sp30[4][4];
    f32 scale;

    arg0->unk360 = (f32)((f64)arg0->unk360 * 1.07);
    arg0->unk35C = arg0->unk35C + 0xA;
    scale = arg0->unk360;
    arg0->unk364 = scale;
    guScaleF(sp70, scale, scale, 0.0f);
    guRotateF(sp30, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
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

extern s16 D_80755650[];
s16 func_806CC190(s16, s16, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
extern s32 D_8071FB08;

void func_8071C9E8(TimedEffectActorView *arg0, s8 *arg1) {
    f32 spA0[4][4];
    f32 sp60[4][4];
    FxInt1C9State *state;
    u8 sp5B;
    s16 sp58;
    s16 *sp4C;

    if (arg0->unk384 == NULL) {
        sp5B = (randomNonNegative() >> 0xF) % 1000 % 6;
        arg0->unk384 = func_80610FE8(0xE);
        state = arg0->unk384;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        sp4C = &D_80755650[sp5B * 3];
        state->x = sp4C[0];
        state->z = sp4C[1];
        state->target_y = sp4C[2];
        state->rotation = 0;
        state->y = (s16)arg0->unk344;
    }
    state = arg0->unk384;
    if (*(f32 *)((u8 *)D_807FBB4C + 0x84) < 340.0f) {
        state->x = 0x12C;
        state->z = 0x96;
        state->target_y = 0x64;
    }
    sp58 = mathAngleBetweenPoints2D((f32)state->x, (f32)state->target_y, arg0->unk340, arg0->unk348);
    state->angle = func_806CC190(state->angle, sp58, (f32)(((randomNonNegative() >> 0xF) % 10) + 5));
    state->y = (s16)((f64)(state->z - state->y) * 0.1 + (f64)state->y);
    arg0->unk340 += state->speed * func_80612794(state->angle);
    arg0->unk348 += state->speed * func_80612790(state->angle);
    arg0->unk344 = (f32)((((f64)func_80612794((state->speed + 0x32) * D_8076A064)) * 40.0) + (state->y + 0x28));
    if (((randomNonNegative() >> 0xF) % 1000) >= 991) {
        sp5B = ((randomNonNegative() >> 0xF) % 1000) % 6;
        state->x = D_80755650[sp5B * 3];
        state->z = D_80755650[(sp5B * 3) + 1];
        state->target_y = D_80755650[(sp5B * 3) + 2];
    }
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(D_8076A064 & 3)) {
        func_807149B8(1);
        func_8071498C(func_8071C818);
        func_80714CC0((s32)&D_8071FB08, 1.6f, arg0->unk340, arg0->unk344, arg0->unk348);
    }
    state->rotation += state->speed;
    guScaleF(spA0, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp60, (f32)state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(spA0, sp60, spA0);
    guMtxF2L(spA0, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}


typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 rotation;
} FxInt1Cde0State;

typedef struct {
    u8 pad0[0x7C];
    f32 x;
    f32 y;
    f32 z;
    u8 pad88[0xD6];
    u8 height;
} FxInt1Cde0Actor;

void func_8071CDE0(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    FxInt1Cde0State *state;
    FxInt1Cde0Actor *actor;

    if (arg0->unk384 == NULL) {
        randomNonNegative();
        state = func_80610FE8(8);
        arg0->unk384 = state;
        state->angle = 0;
        state->y = (s16)arg0->unk344;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        state->rotation = 0;
    }
    state = arg0->unk384;
    actor = (FxInt1Cde0Actor *)(u32)arg0->unk35C;
    state->angle = func_806CC190(state->angle,
            mathAngleBetweenPoints2D(actor->x, actor->z, arg0->unk340, arg0->unk348),
            (f32)(((randomNonNegative() >> 0xF) % 10) + 5));
    state->y = (s16)((((f64)((actor->y + ((f32)((u32)actor->height))) - ((f32)state->y))) * 0.1) + ((f64)state->y));
    arg0->unk340 += state->speed * func_80612794(state->angle);
    arg0->unk348 += state->speed * func_80612790(state->angle);
    arg0->unk344 = (f32)((((f64)func_80612794((state->speed + 0x32) * D_8076A064)) * 40.0) + (state->y + 0x28));
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(D_8076A064 & 3)) {
        func_807149B8(1);
        func_8071498C(func_8071C818);
        func_80714CC0((s32)&D_8071FB08, 1.6f, arg0->unk340, arg0->unk344, arg0->unk348);
    }
    state->rotation += state->speed;
    guScaleF(sp98, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp58, (f32)state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp98, sp58, sp98);
    guMtxF2L(sp98, (Mtx *)((((u8 *)arg0) + (D_807444FC << 6)) + 0x128));
    arg0->pad0[0x32C] = 2;
}

#ifdef NON_MATCHING
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} FxInt1Motion16;

void actorGetNodePos(s32, s32, f32 *, f32 *, f32 *);
u8 func_805FF030(u8, u8);
extern u8 D_8076A0AB;
extern u16 D_807FC930[];

void func_8071D0F0(TimedEffectActorView *arg0, s8 *arg1) {
    FxInt1Motion16 *motion;
    LightOwnerView **lightNodePtr;
    s32 node;
    f32 factor;

    node = arg0->unk35C;
    motion = arg0->unk384;
    if (motion == NULL) {
        motion = func_80610FE8(0x10);
        arg0->unk384 = motion;
        motion->unk0 = 30.0f;
        motion = arg0->unk384;
    }
    actorGetNodePos(node, 1, &motion->unk4, &motion->unk8, &motion->unkC);
    factor = (f32)((f64)motion->unk0 / 30.0);
    arg0->unk340 = (D_807FBB4C->unk7C - motion->unk4) * factor + motion->unk4;
    lightNodePtr = &D_807FD580;
    arg0->unk344 = (D_807FBB4C->unk80 - motion->unk8) * factor + motion->unk8;
    arg0->unk348 = (D_807FBB4C->unk84 - motion->unkC) * factor + motion->unkC;
    motion->unk0 -= 1.0f;
    if (motion->unk0 == 0.0f) {
        if (D_807FBB4C && D_807FBB4C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        *(s32 *)((u8 *)(*lightNodePtr) + 0x1F0) |= 0x20000;
        D_807FC930[func_805FF030(D_8076A0AB, 0)]++;
        *arg1 = 1;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071D0F0.s")
#endif

void func_8071D260(TimedEffectActorView *arg0, s8 *arg1) {
    u16 difference;
    s32 amount;
    u8 remaining;
    s32 completed;

    amount = arg0->unk35C;
    difference = arg0->unk36D - amount;
    completed = 1;
    remaining = difference;
    arg0->unk36D = remaining;
    if (amount >= remaining) {
        *arg1 = completed;
    }
}

void playerStateQueueCallback();

typedef struct {
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
} Fx11BGSource;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Fx11BGOrbitState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Fx11BGVelocityState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Fx11BGFallState;

void func_8071D94C(Fx11BGSource *, TimedEffectActorView *, s8 *);

void func_80714A28(s16);

void func_8071D28C(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BGOrbitState *var_v1;
    Fx11BGOrbitState *temp_v0;
    Fx11BGSource *source;

    source = arg0->unk338;
    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(0x20);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = sqrtf(((source->unk7C - arg0->unk340) * (source->unk7C - arg0->unk340)) + ((source->unk84 - arg0->unk348) * (source->unk84 - arg0->unk348)));
        temp_v0->unk4 = (func_806119FC() * 20.0f) + 10.0f;
        temp_v0->unk8 = func_806119FC() * 4095.0f;
        temp_v0->unkC = (func_806119FC() * 90.0f) + 10.0f;
        temp_v0->unk10 = (f32) source->unkE6;
        temp_v0->unk14 = func_806119FC() * 30.0f;
        temp_v0->unk18 = 0.0f;
        temp_v0->unk1C = (f32) (((randomNonNegative() >> 0xF) % 0xFF) % 2) * 2 - 1.0f;
    }
    var_v1 = arg0->unk384;
    var_v1->unk0 = (f32) (((f64) (var_v1->unk4 - var_v1->unk0) * 0.15) + (f64) var_v1->unk0);
    var_v1->unk14 = (f32) (((f64) (120.0f - var_v1->unk14) * 0.01) + (f64) var_v1->unk14);
    var_v1->unk10 = var_v1->unk10 + (var_v1->unk1C * var_v1->unk14);
    var_v1->unk8 = var_v1->unk8 + var_v1->unkC;
    arg0->unk340 = (func_80612794((s16) var_v1->unk10) * var_v1->unk0) + source->unk7C;
    arg0->unk348 = (func_80612790((s16) var_v1->unk10) * var_v1->unk0) + source->unk84;
    arg0->unk344 += 0.6 * func_80612794((s16) var_v1->unk8);
    var_v1->unk18 = var_v1->unk18 + 1.0f;
    if (45.0f < var_v1->unk18) {
        *arg1 = 1;
    }
    if ((D_8076A064 % arg0->unk35C) == 0) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(0x2A);
        func_8071498C(&func_8071D260);
        func_80714A28(0x20);
        func_80714CC0(*(s32 *) arg0->unk330, arg0->unk360, arg0->unk340, arg0->unk344, arg0->unk348);
    }
}

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xD6];
    u8 unk15E;
} Fx11BGPlayerView;

void func_8071D5BC(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp80[4][4];
    f32 sp40[4][4];
    Fx11BGPlayerView *player;
    s32 radius;

    radius = (s32) (arg0->unk360 * 20.0f);
    player = (Fx11BGPlayerView *) D_807FBB4C;
    if ((player->unk80 <= arg0->unk344) && (arg0->unk344 < player->unk80 + (f32) player->unk15E)) {
        if ((((player->unk7C - arg0->unk340) * (player->unk7C - arg0->unk340)) + ((player->unk84 - arg0->unk348) * (player->unk84 - arg0->unk348))) < (f32) (radius * radius)) {
            playerStateQueueCallback(0x2E, 0, 0);
        }
    }
    guScaleF(sp80, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp40, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp80, sp40, sp80);
    guTranslateF(sp40, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp80, sp40, sp80);
    if ((s32) arg0->unk36D >= 9) {
        arg0->unk36D -= 9;
    } else {
        *arg1 = 1;
    }
    arg0->unk360 = (f32) ((f64) arg0->unk360 * 1.08);
    arg0->unk364 = arg0->unk360;
    guMtxF2L(sp80, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
}

extern f32 D_80755674;
extern f32 D_80755678;

void func_8071D784(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    s32 pad;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        guRotateF(sp90, -(f32) ((func_806119A0() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32) ((arg0->unk35C * 360) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, D_80755678, &sp48, &sp44, &sp40);
        ((Fx11BGVelocityState *) arg0->unk384)->unk0 = sp48;
        ((Fx11BGVelocityState *) arg0->unk384)->unk4 = sp44;
        ((Fx11BGVelocityState *) arg0->unk384)->unk8 = sp40;
    }
    arg0->unk340 = arg0->unk340 + ((Fx11BGVelocityState *) arg0->unk384)->unk0;
    arg0->unk344 = arg0->unk344 + ((Fx11BGVelocityState *) arg0->unk384)->unk4;
    ((Fx11BGVelocityState *) arg0->unk384)->unk4 = ((Fx11BGVelocityState *) arg0->unk384)->unk4 + D_80755674;
    arg0->unk348 = arg0->unk348 + ((Fx11BGVelocityState *) arg0->unk384)->unk8;
    if (arg0->unk344 <= ((Fx11BGPlayerView *) D_807FBB4C)->unk80) {
        *arg1 = 1;
    }
}

void func_8071D94C(Fx11BGSource *arg0, TimedEffectActorView *arg1, s8 *arg2) {
    s16 sp38;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    Fx11BGFallState *sp24;
    Fx11BGFallState *temp_v0;
    f32 var_fv0;
    u32 r;

    temp_v0 = func_80610FE8(0x10);
    arg1->unk384 = temp_v0;
    sp24 = temp_v0;
    var_fv0 = func_806119FC();
    arg1->unk340 = arg1->unk340 + ((var_fv0 - 0.5f) * 2.0f);
    var_fv0 = func_806119FC();
    arg1->unk344 = arg1->unk344 + ((var_fv0 - 0.5f) * 2.0f);
    var_fv0 = func_806119FC();
    arg1->unk348 = arg1->unk348 + ((var_fv0 - 0.5f) * 2.0f);
    if (arg0 != NULL) {
        r = func_806119A0();
        sp34 = ((arg0->unkE6 + (s16) (r & 0x1FF)) + 0x700) & 0xFFF; // FAKE: (s16) cast shifts the ugen temp ring
        sp2C = arg0->unkB8 * 0.016666668f;
        if (!(sp2C < 1.0f)) {
            sp2C = 1.0f;
        }
        if (sp2C < 0.3) {
            *arg2 = 1;
        }
        sp28 = sp2C * 1.5f * 1.8f;
        arg1->unk338 = arg0;
    } else {
        sp2C = 0.8f;
        sp34 = (s16) (func_806119A0() % 4095U);
        sp28 = (func_806119FC() + 1.0f) * 3.0f;
    }
    arg1->unk360 *= 0.5 * (1 + func_806119FC());
    arg1->unk36D = 0x82;
    arg1->unk364 = arg1->unk360;
    sp30 = func_806119FC() * sp2C;
    sp24->unk0 = func_80612794(sp34) * sp30;
    sp24->unk4 = func_80612790(sp34) * sp30;
    sp24->unk8 = sp28;
    collisionGetFloorHeight(&sp24->unkC);
}

void func_8071DB74(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BGFallState *var_v1;
    Fx11BGSource *floor;
    s32 state;

    if (arg0->unk384 == NULL) {
        func_8071D94C(0, arg0, arg1);
    }
    var_v1 = arg0->unk384;
    var_v1->unk8 = var_v1->unk8 + -0.5f;
    arg0->unk340 = arg0->unk340 + var_v1->unk0;
    arg0->unk344 = arg0->unk344 + var_v1->unk8;
    arg0->unk348 = arg0->unk348 + var_v1->unk4;
    state = *(u8 *) arg1;
    if (state == 0) {
        floor = arg0->unk338;
        if (floor != NULL) {
            if (arg0->unk344 <= floor->unkAC) {
                state = *(u8 *) arg1 = 1;
            }
        } else {
            if (arg0->unk344 <= var_v1->unkC) {
                state = *(u8 *) arg1 = 1;
            }
        }
        if (state != 0) {
            func_80718124(arg0->unk360 * 5.0f, arg0->unk340, arg0->unk344, arg0->unk348);
        }
    }
}

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xEC];
    void *unk174;
} Fx11BHDTarget;

typedef struct {
    u8 pad0[0x1F0];
    u32 unk1F0;
} Fx11BHDFlags;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Fx11BHDState;

void func_8071DC90(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BHDState *temp_v0;
    Fx11BHDTarget *sp28;
    Fx11BHDFlags *temp_v1;
    f32 sp20;

    sp20 = 0.3f;
    sp28 = (Fx11BHDTarget *)(u32)arg0->unk35C;
    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(0x18);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.0f;
        temp_v0->unk4 = (f32)(func_806119FC() * 4095.0f);
        temp_v0->unk8 = (f32)((func_806119FC() > 0.5 ? (f64)func_806119FC() : 0.5) * 300.0);
        if ((f64)func_806119FC() > 0.5) {
            temp_v0->unk8 = (f32)-temp_v0->unk8;
        }
        temp_v0->unkC = (f32)(func_806119FC() * 4095.0f);
        temp_v0->unk10 = (f32)((func_806119FC() > 0.5 ? (f64)func_806119FC() : 0.5) * 300.0);
        if ((f64)func_806119FC() > 0.5) {
            temp_v0->unk10 = (f32)-temp_v0->unk10;
        }
        temp_v0->unk14 = (f32)(func_806119FC() > 0.3 ? (f64)func_806119FC() : 0.3);
        sp20 = 1.0f;
    }
    temp_v0 = arg0->unk384;
    if (temp_v0->unk0 < 1.0f) {
        temp_v0->unk0 = temp_v0->unk0 + 0.033333335f;
    }
    temp_v0->unk4 = (f32)(temp_v0->unk4 + temp_v0->unk8);
    temp_v0->unk4 = (f32)((((s32)temp_v0->unk4 & 0xFFF) & 0xFFFF) & 0xFFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    temp_v0->unkC = (f32)(temp_v0->unkC + temp_v0->unk10);
    temp_v0->unkC = (f32)((((s32)temp_v0->unkC & 0xFFF) & 0xFFFF) & 0xFFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    arg0->unk340 = (f32) (((((func_80612794((s16) (s32) temp_v0->unk4) * (15.0f * temp_v0->unk0)) + sp28->unk7C) - arg0->unk340) * sp20) + arg0->unk340);
    arg0->unk348 = (f32) (((((func_80612790((s16) (s32) temp_v0->unk4) * (15.0f * temp_v0->unk0)) + sp28->unk84) - arg0->unk348) * sp20) + arg0->unk348);
    arg0->unk344 = (f32) (((((((func_80612794((s16) (s32) temp_v0->unkC) * (temp_v0->unk14 * temp_v0->unk0)) + 1.0f) * 15.0f) + sp28->unk80) - arg0->unk344) * sp20) + arg0->unk344);
    temp_v1 = sp28->unk174;
    if (!(temp_v1->unk1F0 & 0x10)) {
        *arg1 = 1;
    }
}

void func_8071E028(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp68[4][4];
    f32 sp28[4][4];

    guScaleF(sp68, arg0->unk360, arg0->unk364, 0.0f);
    guTranslateF(sp28, 0.0f, arg0->unk364 * 20.0f, 0.0f);
    guMtxCatF(sp68, sp28, sp68);
    guRotateF(sp28, (f32)arg0->unk35C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp68, sp28, sp68);
    guMtxF2L(sp68, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} TimedMotionState;

void func_8071E110(TimedEffectActorView *arg0, u8 arg1, u16 arg2, f32 arg3, f32 arg4, s32 arg5) {
    TimedMotionState *temp_v0;

    temp_v0 = func_80610FE8(0x18);
    arg0->unk384 = temp_v0;
    temp_v0->unk0 = (f32)(u32)arg1;
    temp_v0->unk4 = arg4;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = 1.0f / (f32)arg5;
    temp_v0->unk10 = 0.0f;
    temp_v0->unk14 = (f32)(u32)arg2;
}

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Fx11BHE1Target;

extern s32 actorTableContains(void *);

void func_8071E1C8(TimedEffectActorView *arg0, s8 *arg1) {
    f64 pad0;
    f32 sp3C;
    f32 pad1;
    f64 pad2;
    f32 sp2C;
    f32 pad3;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;
    Fx11BHE1Target *temp_s2;
    TimedEffectActorView *var_a0;
    TimedMotionState *temp_v0;

    if (arg0->unk384 == NULL) {
        *arg1 = 1;
        return;
    }
    temp_v0 = arg0->unk384;
    temp_s2 = (Fx11BHE1Target *)(u32)arg0->unk35C;
    sp3C = 2.0f; // FAKE: dead store keeps the 2.0f scale in a register across the actorTableContains call
    if (actorTableContains(temp_s2) == 0) {
        *arg1 = 1;
        return;
    }
    var_fv0 = temp_v0->unk10 * ((1.0f - (temp_v0->unk0 * sp3C)) * 2048.0f);
    var_fv0 = (f32)((((s32)var_fv0 & 0xFFFF) & 0xFFFF) & 0xFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    sp2C = func_80612794((s16)(s32)var_fv0) * temp_v0->unk8;
    temp_v0->unk14 = (f32)((f64)temp_v0->unk14 + (2.0 * (f64)((1.0f - (temp_v0->unk0 * sp3C)) * 4096.0f) * (f64)temp_v0->unkC));
    temp_v0->unk14 = (f32)((((s32)temp_v0->unk14 & 0xFFF) & 0xFFFF) & 0xFFFF); // FAKE: extra 0xFFFF masks steer the ugen int temp ring
    sp3C = func_80612794((s16)(s32)temp_v0->unk14) * sp2C;
    temp_fv0 = func_80612790((s16)(s32)temp_v0->unk14);
    temp_fa0 = temp_v0->unk4;
    var_fv1 = temp_v0->unk10 * temp_fa0;
    if (temp_v0->unk0 == 0.0f) {
        var_fv1 = temp_fa0 - var_fv1;
    }
    arg0->unk340 = (f32)(temp_s2->unk7C + sp3C);
    var_a0 = arg0;
    var_a0->unk348 = (f32)(temp_s2->unk84 + (temp_fv0 * sp2C));
    arg0->unk344 = (f32)(temp_s2->unk80 + var_fv1);
    temp_v0->unk10 = (f32)(temp_v0->unk10 + temp_v0->unkC);
    if (temp_v0->unk10 >= 1.0f) {
        *arg1 = 1;
    }
}

#ifdef NON_MATCHING
s16 func_806531B8(f32, f32, f32, s32);
void lightSetRadius(s32);
void lightSetTargetId(s32);

void func_8071E3EC(TimedEffectActorView *arg0, s8 *arg1) {
    f64 var_fv0;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 temp_fv0;
    s32 temp_v0_2;
    VelocityState *temp_v0;
    VelocityState *var_v1;

    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.0f;
        temp_v0->unk4 = 0.0f;
        temp_v0->unk8 = (f32)func_806531B8(arg0->unk340, arg0->unk344, arg0->unk348, 0);
    }
    var_v1 = arg0->unk384;
    if ((f64)var_v1->unk4 == 0.0) {
        var_v1->unk0 = (f32)((f64)var_v1->unk0 + 30.0);
        if ((f64)var_v1->unk0 > 300.0) {
            var_v1->unk4 = 1.0f;
            var_v1->unk0 = 300.0f;
        }
    } else {
        var_v1->unk0 = (f32)((f64)var_v1->unk0 - 30.0);
        if ((f64)var_v1->unk0 < 30.0) {
            *arg1 = 1;
            var_v1->unk0 = 30.0f;
        }
    }
    var_fv0 = (f64)var_v1->unk0;
    if (var_fv0 < 300.0) {
        sp4C = (f32)(var_fv0 / 300.0);
    } else {
        sp4C = 1.0f;
    }
    lightSetRadius(1000);
    lightSetTargetId((s16)(s32)var_v1->unk8);
    temp_v0_2 = arg0->unk35C;
    switch (temp_v0_2) {
    case 0:
        sp48 = 1.0f;
        sp44 = 1.0f;
        sp40 = 1.0f;
        lightSetFlags(2);
        lightSetRadius(1000);
        break;
    case 1:
        sp48 = 1.0f;
        sp44 = 0.5f;
        sp40 = 0.3f;
        lightSetFlags(3);
        lightSetRadius(1000);
        break;
    case 2:
        sp48 = 1.0f;
        sp44 = 0.5f;
        sp40 = 0.3f;
        lightSetFlags(2);
        lightSetRadius(2000);
        break;
    case 3:
        sp48 = 1.0f;
        sp44 = 1.0f;
        sp40 = 1.0f;
        lightSetFlags(2);
        lightSetRadius(2000);
        break;
    }
    temp_fv0 = 255.0f * sp4C;
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, var_v1->unk0, 0, (u32)(temp_fv0 * sp48), (u32)(temp_fv0 * sp44), (u32)(temp_fv0 * sp40));
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071E3EC.s")
#endif

typedef struct {
    f32 unk0;
    f32 unk4;
} Fx11BHE8State;

void func_8071E864(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp24;
    Fx11BHE8State *temp_v0;
    Fx11BHE8State *sp1C;
    f32 temp_fa0;

    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 10.0f;
        temp_v0->unk4 = (f32)(arg0->unk35C * 0x154);
    }
    sp1C = (Fx11BHE8State *)arg0->unk384;
    sp1C->unk0 = (f32)((f64)sp1C->unk0 - 0.2);
    if ((f64)sp1C->unk0 < 0.8) {
        sp1C->unk0 = 0.8f;
    }
    sp24 = func_80612794((s16)(s32)sp1C->unk4);
    sp24 = sp1C->unk0 * sp24; // FAKE: forces mul.s operand order (load first, call result second)
    temp_fa0 = func_80612790((s16)(s32)sp1C->unk4);
    temp_fa0 = sp1C->unk0 * temp_fa0; // FAKE: forces mul.s operand order (load first, call result second)
    arg0->unk360 = (f32)((f64)arg0->unk360 * 1.08);
    arg0->unk364 = (f32)((f64)arg0->unk364 * 1.08);
    if ((f64)arg0->unk360 > 8.0) {
        arg0->unk36D = arg0->unk36D - 0x32;
        if (arg0->unk36D < 0x33) {
            *arg1 = 1;
        }
    }
    arg0->unk340 = (f32)(arg0->unk340 + sp24);
    arg0->unk348 = (f32)(arg0->unk348 + temp_fa0);
}

void func_8071EA24(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xC);
        var_v1 = (TimedMotionState *)arg0->unk384;
        var_v1->unk0 = func_806119FC() * 4095.0f;
        var_v1->unk4 = (f32)(((f64)func_806119FC() * 0.5 + 1.0) * 5.0);
        var_v1->unk8 = 15.0f;
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    var_v1->unk4 = var_v1->unk4 - 1.0f;
    var_v1->unk8 = (f32)((f64)var_v1->unk8 * 0.95);
    arg0->unk340 += var_v1->unk8 * func_80612794((s16)var_v1->unk0);
    arg0->unk348 += var_v1->unk8 * func_80612790((s16)var_v1->unk0);
    arg0->unk344 = arg0->unk344 + var_v1->unk4;
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EB70.s")

void actorGetNodePos(s32, s32, f32 *, f32 *, f32 *);
typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
} TargetTrackingActorView;

void func_8071EDEC(TargetTrackingActorView *arg0, s32 arg1) {
    f64 pad;
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    actorGetNodePos(arg0->unk35C, 1, &sp34, &sp30, &sp2C);
    arg0->unk340 = (f32)((f64)arg0->unk340 + ((f64)(sp34 - arg0->unk340) * 0.1));
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)(sp30 - arg0->unk344) * 0.1));
    arg0->unk348 = (f32)((f64)arg0->unk348 + ((f64)(sp2C - arg0->unk348) * 0.1));
}

void func_8071EEA4(TimedEffectActorView *arg0, s32 arg1) {
    arg0->unk364 = (f32) (((f64) arg0->unk35C / 100.0) + 1.0);
}

void matrixMakeRotationZ(f32 (*arg0)[4], f32 arg1);

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071EEE0.s")

void func_8071EFDC(TimedEffectActorView *arg0, s8 *arg1) {
    s32 temp_t7;

    arg0->unk360 = (f32)((f64)arg0->unk360 * 1.05);
    arg0->unk364 = (f32)(((f64)arg0->unk364 * 1.05) * 1.0);
    temp_t7 = (arg0->unk36D = (arg0->unk36D & 0xFFu) - 5);
    if ((temp_t7 & 0xFF) < 6) {
        *arg1 = 1;
    }
}

typedef struct {
    u8 unk0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} PositionSource;

void func_8071F034(TimedEffectActorView *arg0, s32 arg1) {
    if (*(s16 *) ((u8 *) arg0 + 0x34E) == 0) {
        arg0->unk340 = ((PositionSource *) D_807FBB4C)->unk7C;
        arg0->unk344 = ((PositionSource *) D_807FBB4C)->unk80;
        arg0->unk348 = ((PositionSource *) D_807FBB4C)->unk84;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F078.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F1D0.s")

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

typedef struct {
    u8 unk0[0x338];
    ScaleRoot *unk338;
    u8 unk33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 unk34C[2];
    s16 unk34E;
    u8 unk350;
    u8 unk351[3];
    s32 unk354;
    s32 unk358;
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 unk368[0x1C];
    FallingMotionState *unk384;
} FallingEffectActorView;

void func_8071F2F8(FallingEffectActorView *arg0, s32 arg1) {
    f32 temp_fv0;
    FallingMotionState *temp_v0;
    FallingMotionState *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) (arg0->unk35C & 0xFFFF);
        temp_v0->unk4 = (f32) ((s32) arg0->unk35C >> 0x10);
        var_v1 = arg0->unk384;
    }
    arg0->unk344 = arg0->unk344 + var_v1->unk0;
    temp_fv0 = var_v1->unk0;
    if (temp_fv0 > -20.0f) {
        var_v1->unk0 = (f32) ((f64) temp_fv0 - ((f64) var_v1->unk4 * 0.01));
    }
}

void func_8071F3C0(FallingEffectActorView *arg0, s32 arg1) {
    FallingMotionState *temp_v0;
    FallingMotionState *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(4);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) ((f64) arg0->unk364 * 6.666666666666667);
        var_v1 = arg0->unk384;
    }
    arg0->unk360 = ((ScaleSource *) arg0->unk338->unk4)->unk38 * var_v1->unk0;
    arg0->unk364 = arg0->unk360;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F444.s")

typedef struct {
    u8 unk0[0x32C];
    u8 unk32C;
    u8 unk32D[0xB];
    u8 unk338[0x1C];
    s32 unk354;
    s32 unk358;
    u8 unk35C[4];
    f32 unk360;
    f32 unk364;
} SineScaleActorView;


void func_8071F660(SineScaleActorView *arg0, void *arg1) {
    f32 sp68[4][4];
    f32 sp28[4][4];
    f32 sp24;

    sp24 = (f32) arg0->unk358 / (f32) (arg0->unk354 - 1);
    arg0->unk360 = (f32) ((f64) func_80612794((s16) (s32) (sp24 * 2048.0f)) * 3.0);
    arg0->unk364 = arg0->unk360;
    guScaleF(sp68, arg0->unk360, arg0->unk360, 0.0f);
    matrixMakeRotationZ(sp28, sp24 * 180.0f);
    guMtxCatF(sp68, sp28, sp68);
    guMtxF2L(sp68, (Mtx *) ((s32) arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F758.s")

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
} Fx11BIRiseMotionState;


#pragma GLOBAL_ASM("asm/global/nonmatchings/11BC10/func_8071F8E4.s")
