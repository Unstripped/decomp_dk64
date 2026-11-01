#include "common.h"
#include "actor.h"


typedef struct ActorPhysicsWork {
    char pad0[0x64];
    u32 unk64;
    char pad68[0x86];
    s16 unkEE;
    char padF0[2];
    s16 unkF2;
    s16 unkF4;
    s16 unkF6;
    s16 unkF8;
    s16 unkFA;
    u8 unkFC;
} ActorPhysicsWork;

void func_8067ACB4(void);
void mathAngleClampToArc(s16, s16, s16, s16, void *);
s16 func_80672134(s16, s16, s16, s16);
void func_80665ACC(Actor *);

void actorStepPhysics(arg0, arg1, arg2)
ActorPhysicsWork *arg0;
s16 arg1;
s16 arg2;
{
    func_8067ACB4();
    func_80665ACC((Actor *)arg0);
    if (arg0->unkFC != 0) {
        mathAngleClampToArc(arg0->unkEE, arg1, arg0->unkF4, arg0->unkF6, &arg0->unkF2);
        arg0->unkFA = func_80672134(arg0->unkF4, arg0->unkF6, arg2, arg0->unkF8);
        if ((arg0->unk64 & 0x200) && (arg0->unk64 & 0x100)) {
            arg0->unkFA = 0;
        }
        arg0->unkEE = arg0->unkF2;
    }
}

typedef struct ActorVelocityWork {
    char pad0[0x4];
    ActorSub4 *unk4;
    char pad8[0x54];
    u16 unk5C;
    char pad5E[2];
    u32 unk60;
    char pad64[6];
    u16 unk6A;
    char pad6C[0x10];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    char padC4[0x16];
    s16 unkDA;
    char padDC[0x12];
    s16 unkEE;
    char padF0[0xA];
    s16 unkFA;
    u8 unkFC;
} ActorVelocityWork;

f32 func_80612790(s16);
f32 func_80612794(s16);
extern u32 D_80744478;

void actorApplyVelocity(ActorVelocityWork *arg0) {
    f32 pad;
    f32 sp28;
    f32 fv1;
    f32 var_fs0;

    var_fs0 = arg0->unkB8;
    if (arg0->unkFC != 0) {
        if ((f32)arg0->unkFA < var_fs0) {
            var_fs0 = arg0->unkFA;
        }
    }
    sp28 = (f64)((arg0->unk4 != NULL) ? arg0->unk4->unk38 : 0.15f) * 0.16666666675;
    if ((arg0->unk5C & 4) && (arg0->unk6A & 4)) {
        sp28 = (f64)sp28 * 0.5;
    }
    var_fs0 *= sp28;
    if (arg0->unk6A & 1) {
        if (func_80612794(arg0->unkDA) > 0.0f) {
            fv1 = func_80612794(arg0->unkDA);
        } else {
            fv1 = -func_80612794(arg0->unkDA);
        }
        var_fs0 *= fv1;
    }
    if (arg0->unk60 & 0x400000) {
        var_fs0 = (f64)var_fs0 * ((f64)(u32)D_80744478 * 0.5);
    }
    arg0->unk7C += var_fs0 * func_80612794(arg0->unkEE);
    arg0->unk84 += var_fs0 * func_80612790(arg0->unkEE);
    arg0->unk80 += arg0->unkC0 * sp28;
}

typedef struct ActorVelocityCustomWork {
    char pad0[0x4];
    ActorSub4 *unk4;
    char pad8[0x58];
    u32 unk60;
    char pad64[0x6];
    u16 unk6A;
    char pad6C[0x10];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x52];
    s16 unkDA;
    char padDC[0x12];
    s16 unkEE;
    char padF0[0xA];
    s16 unkFA;
    u8 unkFC;
} ActorVelocityCustomWork;


void actorApplyVelocityCustom(ActorVelocityCustomWork *arg0, f32 arg1, f32 arg2) {
    f32 sp28;
    f32 scale;

    if (arg0->unkFC != 0) {
        if ((f32)arg0->unkFA < arg1) {
            arg1 = arg0->unkFA;
        }
    }
    if (arg0->unk4 != NULL) {
        scale = arg0->unk4->unk38;
    } else {
        scale = 0.15f;
    }
    sp28 = (f64)scale * 0.16666666675;
    arg1 *= sp28;
    if (arg0->unk6A & 1) {
        arg1 *= (func_80612794(arg0->unkDA) > 0.0f) ? func_80612794(arg0->unkDA) : -func_80612794(arg0->unkDA);
    }
    if (arg0->unk60 & 0x400000) {
        arg1 = (f64)arg1 * ((f64)(u32)D_80744478 * 0.5);
    }
    arg0->unk7C += arg1 * func_80612794(arg0->unkEE);
    arg0->unk84 += arg1 * func_80612790(arg0->unkEE);
    arg0->unk80 += arg2 * sp28;
}

extern u8 D_80748E00;
extern u8 D_80748E04;

void actorSkipFloorSnap(void) {
    D_80748E00 = 1;
}

u8 actorGetFloorSnapped(void) {
    return D_80748E04;
}

typedef struct ActorFloorContactView {
    char pad0[0x4];
    ActorSub4 *unk4;
    char pad8[0x54];
    u16 unk5C;
    char pad5E[2];
    u32 unk60;
    char pad64[0x6];
    u16 unk6A;
    u16 unk6C;
    char pad6E[0x12];
    f32 unk80;
    char pad84[0x8];
    f32 unk8C;
    char pad90[0x14];
    f32 unkA4;
    char padA8[0xC];
    f32 unkB4;
    char padB8[0x8];
    f32 unkC0;
    char padC4[0xD];
    u8 unkD1;
    char padD2[6];
    s16 unkD8;
    s16 unkDA;
    s16 unkDC;
    s16 unkDE;
    f32 unkE0;
} ActorFloorContactView;

typedef struct {
    s16 unk0;
    char pad2[0x24];
    s16 unk26;
} CameraStateView;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 pad4[2];
    u8 unk6;
    u8 pad7[3];
} ActorTiltTableEntry;

extern ActorTiltTableEntry D_80748D40[];
extern ActorTiltTableEntry D_80748DA4;
extern CameraStateView *gActivePlayerState;
extern Actor *D_807FBB40;
extern s32 gCurrentMap;





void collisionQueryActorFloor(Actor *, u8 *, f32 *, u8 *, void *, s32);
void func_806D09E8(Actor *);
s32 mathAngleSignedDistance(s16, s16);
void actorUpdateFloorContactAndTilt(ActorFloorContactView *arg0, f32 arg1) {
    f32 sp5C;
    u8 sp5B;
    f32 sp54;
    u8 sp53;
    f32 temp_fv0;
    f32 var_fv1;
    s32 tmpd;
    s16 var_t0;
    s16 var_a1;
    s16 var_a2;
    s16 diff;
    ActorTiltTableEntry *var_t1;
    f32 var_fv0;

    collisionQueryActorFloor((Actor *)arg0, &sp5B, &sp5C, &sp53, &sp54, 0);
    if (arg0->unk5C & 1) {
        func_806D09E8((Actor *)arg0);
    }
    temp_fv0 = arg0->unk80 - arg0->unkA4;
    arg0->unk6A &= ~1;
    arg0->unkB4 = temp_fv0 - arg1;
    if ((temp_fv0 <= arg1) || ((arg0->unk6C & 1) && (arg0->unkC0 < 0.0f))) {
        if ((D_807FBB40->unk6A & 0x200) || ((u32)gCurrentMap == 0x27) || ((u32)gCurrentMap == 0x6F) || ((u32)gCurrentMap == 0xB9)) {
            if ((f64)arg0->unkB4 < 0.5) {
                if (arg0->unk4 != NULL) {
                    var_fv1 = arg0->unk4->unk38;
                } else {
                    var_fv1 = 0.15f;
                }
                arg0->unk80 = arg0->unkA4 + arg1;
                arg0->unkB4 = 0.0f;
                arg0->unk6A |= 1;
                arg0->unkC0 = (arg0->unkA4 + arg1 - arg0->unk8C) * (f32)(40.0 / ((f64)var_fv1 * 6.66666667));
            }
        } else if (arg0->unkB4 < 5.0f) {
            arg0->unkB4 = 0.0f;
            arg0->unk80 = arg0->unkA4 + arg1;
            arg0->unk6A |= 1;
            if (arg0->unkC0 < -10.0f) {
                arg0->unkC0 = -10.0f;
            }
        }
    }
    D_80748E04 = 0;
    if (sp5B && !(arg0->unk6A & 1) && (D_80748E00 == 0)) {
        if (arg0->unkC0 > 0.0f) {
            arg0->unkC0 = 0.0f;
        }
        arg0->unk80 = (f64)sp5C + (f64)arg0->unkC0 * 0.025;
        D_80748E04 = 1;
    }
    D_80748E00 = 0;
    var_fv0 = (arg0->unk60 & 0x40000) ? 0.2 : 1.0;
    var_t0 = (arg0->unk6A & 1) ? arg0->unkDA : 0x400;
    var_a1 = arg0->unkD8;
    var_t1 = &D_80748D40[arg0->unkD1];
    switch ((u32)gCurrentMap) {
    case 0x52:
        gActivePlayerState->unk26 = 0x14;
        /* fallthrough */
    case 0xE:
        if (arg0->unk6A & 0x200) {
            var_t1 = &D_80748DA4;
        }
        break;
    }
    if (arg0->unkDE >= 0x3F4) {
        arg0->unkDC = var_a1;
    }
    if (var_t0 >= 0x3F4) {
        var_a1 = arg0->unkDC;
    }
    var_a2 = (s16)((var_t1->unk6 << 12) / 360);
    if (var_a2 < var_t0) {
        var_a2 = var_t0;
    }
    diff = tmpd = mathAngleSignedDistance(arg0->unkDC, var_a1);
    if (((tmpd > 0) ? tmpd : -tmpd) >= 0x6AB) {
        if (arg0->unkDE >= 0x3C8) {
            arg0->unkDE = 0x400;
            arg0->unkDC = var_a1;
        } else {
            diff = (f32)mathAngleSignedDistance(arg0->unkDE, 0x400) * var_fv0;  // FAKE: s16 diff as the float-to-s16 temp (steers t-register order)
            arg0->unkDE += diff;
            arg0->unkDE &= 0xFFF;
        }
    } else {
        diff = (f32)diff * var_fv0;  // FAKE: s16 diff as the float-to-s16 temp (steers t-register order)
        arg0->unkDC += diff;
        arg0->unkDC &= 0xFFF;
        diff = (f32)mathAngleSignedDistance(arg0->unkDE, var_a2) * var_fv0;  // FAKE: s16 diff as the float-to-s16 temp (steers t-register order)
        arg0->unkDE += diff;
        arg0->unkDE &= 0xFFF;
    }
    if (!(arg0->unk6A & 0x20)) {
        var_a2 = var_t1->unk3;
    } else {
        var_a2 = var_t1->unk2;
    }
    var_a2 = (s16)((var_a2 << 12) / 360);
    if (var_a2 < var_t0) {
        arg0->unkE0 = 0.0f;
    } else {
        arg0->unkE0 = (f32)((0x400 - var_t0) / var_t1->unk0);
    }
}

extern u8 D_80748D48[][10];

u8 func_80665AAC(Actor *arg0) {
    return D_80748D48[arg0->unkC8[8]][0];
}

void func_80665ACC(Actor *arg0) {
    arg0->unk60 |= 2;
    arg0->unk60 |= 0x20;
}

f32 func_80611BB4(f32, f32);

f32 mathAngleBetweenPointsDeg(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 sp1C;

    if (arg2 >= arg0 && arg3 >= arg1) {
        sp1C = func_80611BB4(arg3 - arg1, arg2 - arg0) + 1.570796371f;
    } else if (arg2 >= arg0 && arg3 < arg1) {
        sp1C = 1.570796371f - func_80611BB4(arg1 - arg3, arg2 - arg0);
    } else if (arg2 < arg0 && arg3 < arg1) {
        sp1C = (f64)func_80611BB4(arg1 - arg3, arg0 - arg2) + 4.71238911151885986;
    } else if (arg2 < arg0 && arg3 >= arg1) {
        sp1C = 4.71238911151885986 - (f64)func_80611BB4(arg3 - arg1, arg0 - arg2);
    }
    return sp1C * 57.29577637f;
}

s32 func_80611E60(s32);

s16 mathAngleDiscrete(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s16 sp36;

    if ((f64)arg4 < 1.0) {
        arg4 = 1.0f;
    }
    if (arg2 <= arg0 && arg3 <= arg1) {
        sp36 = func_80611E60((s32)(((f64)(arg0 - arg2) * 65535.9) / (f64)arg4)) >> 4;
    } else if (arg2 <= arg0 && arg1 < arg3) {
        sp36 = (func_80611E60((s32)(((f64)(arg3 - arg1) * 65535.9) / (f64)arg4)) >> 4) + 0x400;
    } else if (arg0 < arg2 && arg1 < arg3) {
        sp36 = (func_80611E60((s32)(((f64)(arg2 - arg0) * 65535.9) / (f64)arg4)) >> 4) + 0x800;
    } else if (arg0 < arg2 && arg3 <= arg1) {
        sp36 = (func_80611E60((s32)(((f64)(arg1 - arg3) * 65535.9) / (f64)arg4)) >> 4) + 0xC00;
    }
    return sp36;
}

s32 mathAngleBetweenPoints2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 dx = arg0 - arg2;
    f32 dy = arg1 - arg3;

    return mathAngleDiscrete(arg0, arg1, arg2, arg3, sqrtf((dx * dx) + (dy * dy)));
}

f32 mathAngleBetweenPointsRad(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return (f64)(mathAngleBetweenPoints2D(arg0, arg1, arg2, arg3) * 3.141592741f) * 0.00048828125;
}


void mathCalculatePitchAngle(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
    f32 dx = arg0 - arg3;
    f32 dz = arg2 - arg5;
    f32 dist = sqrtf((dx * dx) + (dz * dz));
    f32 f_arg6 = arg6;
    f32 max_dist;

    if (dist < f_arg6) {
        max_dist = f_arg6;
    } else {
        max_dist = dist;
    }
    func_80611BB4(arg4 - arg1, max_dist);
}

typedef struct ActorSubNodeData {
    f32 unk0;
    f32 unk4;
    u8 unk8[1];
} ActorSubNodeData;

typedef struct ActorSubNodeWrapper {
    char pad[0xC];
    ActorSubNodeData *unkC;
} ActorSubNodeWrapper;

typedef struct ActorScaleConfig {
    char pad[0x14];
    s32 unk14;
    s32 unk18;
    char pad2[0x1C];
    f32 unk38;
} ActorScaleConfig;

typedef struct ActorTransformWork {
    ActorSubNodeWrapper *unk0;
    ActorScaleConfig *unk4;
    char pad[4];
    u8 unkC[1];
} ActorTransformWork;

void actorSub140CreateFromData(f32, f32, f32, f32, f32, f32, void *, s32, s32, void *);

void actorSub140CreateFromModel(ActorTransformWork *arg0) {
    f32 fv0;
    f32 fv1;
    f32 ft4;
    void *v1;
    s32 a1;
    s32 t0;

    fv0 = 0.0f;
    fv1 = 0.0f;
    ft4 = 1.0f;
    v1 = NULL;
    a1 = 0;
    t0 = 0;
    if (arg0->unk0 != NULL) {
        fv0 = arg0->unk0->unkC->unk0;
        fv1 = arg0->unk0->unkC->unk4;
        v1 = &arg0->unk0->unkC->unk8;
    }
    if (arg0->unk4 != NULL) {
        ft4 = arg0->unk4->unk38;
        a1 = arg0->unk4->unk14;
        t0 = arg0->unk4->unk18;
    }
    actorSub140CreateFromData(0.0f, 0.0f, 0.0f, ft4, fv0, fv1, &arg0->unkC, a1, t0, v1);
}


void renderEntryAddOrUpdate(s32, s32, Actor *, f32, f32, f32, s32, s32, s32, s32, s32);
void actorSub140SetVectors(Actor *, f32, f32, f32, f32);
extern s32 gFrameCounter;

void actorUpdatePositionAndSub140(Actor *arg0) {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;

    x = arg0->unk7C;
    y = arg0->unk80;
    z = arg0->unk84;
    if (arg0->unk4 != NULL) {
        renderEntryAddOrUpdate(0, 0, arg0, x, y, z, arg0->unk12A, 0, 1, -1, 1);
    }
    if (arg0->unk140 != NULL) {
        if (arg0->unk4 != NULL) {
            scale = arg0->unk4->unk38;
        } else {
            scale = 0.15f;
        }
        actorSub140SetVectors(arg0, x, y, z, scale);
        arg0->unk140->unk80 = gFrameCounter;
    }
}
