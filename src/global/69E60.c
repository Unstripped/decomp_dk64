#include "common.h"
#include "actor.h"

typedef struct R1A_Actor5160 {
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
} R1A_Actor5160;

void func_8067ACB4(void);
void func_80672680(s16, s16, s16, s16, void *);
s16 func_80672134(s16, s16, s16, s16);
void func_80665ACC(Actor *);

void func_80665160(arg0, arg1, arg2)
R1A_Actor5160 *arg0;
s16 arg1;
s16 arg2;
{
    func_8067ACB4();
    func_80665ACC((Actor *)arg0);
    if (arg0->unkFC != 0) {
        func_80672680(arg0->unkEE, arg1, arg0->unkF4, arg0->unkF6, &arg0->unkF2);
        arg0->unkFA = func_80672134(arg0->unkF4, arg0->unkF6, arg2, arg0->unkF8);
        if ((arg0->unk64 & 0x200) && (arg0->unk64 & 0x100)) {
            arg0->unkFA = 0;
        }
        arg0->unkEE = arg0->unkF2;
    }
}

typedef struct R1A_Actor51FC {
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
} R1A_Actor51FC;

f32 func_80612790(s16);
f32 func_80612794(s16);
extern u32 D_80744478;

void func_806651FC(R1A_Actor51FC *arg0) {
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

typedef struct R1A_Actor53C0 {
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
} R1A_Actor53C0;


void func_806653C0(R1A_Actor53C0 *arg0, f32 arg1, f32 arg2) {
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

void func_80665548(void) {
    D_80748E00 = 1;
}

u8 func_80665558(void) {
    return D_80748E04;
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/69E60/func_80665564.s")

extern u8 D_80748D48[][10];

u8 func_80665AAC(Actor *arg0) {
    return D_80748D48[arg0->unkC0[0x10]][0];
}

void func_80665ACC(Actor *arg0) {
    arg0->unk60 |= 2;
    arg0->unk60 |= 0x20;
}

f32 func_80611BB4(f32, f32);

f32 func_80665AE4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

s16 func_80665C18(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
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

s32 func_80665DE0(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 dx = arg0 - arg2;
    f32 dy = arg1 - arg3;

    return func_80665C18(arg0, arg1, arg2, arg3, sqrtf((dx * dx) + (dy * dy)));
}

f32 func_80665E48(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return (f64)(func_80665DE0(arg0, arg1, arg2, arg3) * 3.141592741f) * 0.00048828125;
}


void func_80665E94(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
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

typedef struct R1A_Sub0SubC {
    f32 unk0;
    f32 unk4;
    u8 unk8[1];
} R1A_Sub0SubC;

typedef struct R1A_Sub0 {
    char pad[0xC];
    R1A_Sub0SubC *unkC;
} R1A_Sub0;

typedef struct R1A_Sub4 {
    char pad[0x14];
    s32 unk14;
    s32 unk18;
    char pad2[0x1C];
    f32 unk38;
} R1A_Sub4;

typedef struct R1A_Arg0 {
    R1A_Sub0 *unk0;
    R1A_Sub4 *unk4;
    char pad[4];
    u8 unkC[1];
} R1A_Arg0;

void func_8066E2C0(f32, f32, f32, f32, f32, f32, void *, s32, s32, void *);

void func_80665F24(R1A_Arg0 *arg0) {
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
    func_8066E2C0(0.0f, 0.0f, 0.0f, ft4, fv0, fv1, &arg0->unkC, a1, t0, v1);
}


void func_806303C4(s32, s32, Actor *, f32, f32, f32, s32, s32, s32, s32, s32);
void actorSub140SetVectors(Actor *, f32, f32, f32, f32);
extern s32 D_8076A064;

void func_80665FB4(Actor *arg0) {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;

    x = arg0->unk7C;
    y = arg0->unk80;
    z = arg0->unk84;
    if (arg0->unk4 != NULL) {
        func_806303C4(0, 0, arg0, x, y, z, arg0->unk12A, 0, 1, -1, 1);
    }
    if (arg0->unk140 != NULL) {
        if (arg0->unk4 != NULL) {
            scale = arg0->unk4->unk38;
        } else {
            scale = 0.15f;
        }
        actorSub140SetVectors(arg0, x, y, z, scale);
        arg0->unk140->unk80 = D_8076A064;
    }
}
