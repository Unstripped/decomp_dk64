#include "common.h"
#include "actor.h"

typedef struct {
    u8 unk0;
    u8 pad[0x1F];
} R1A_Struct8BA0;

extern R1A_Struct8BA0 D_80748BA0[];
extern u8 D_807F9440[];
extern s32 D_807F9448;

void func_80664CB0(arg0)
s16 arg0;
{
    s32 limit;
    u8 *ptr;
    s32 i;

    limit = 13;
    D_807F9448 = 0;
    for (i = 0, ptr = (u8 *)D_80748BA0; i < limit; i++, ptr += 0x20) {
        if (arg0 == *ptr) {
            if (D_807F9448 != 8) {
                D_807F9440[D_807F9448++] = i;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80664D20.s")

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
#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665564.s")

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


#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665FB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666090.s")

extern u8 D_807F94B4;

void func_80666280(arg0)
u8 arg0;
{
    D_807F94B4 = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666290.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066635C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806663F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066641C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666A88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666A94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666AF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666D88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666F04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666FC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80667110.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066715C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80667174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80667180.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806672B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066785C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806679BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80668520.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806685E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806686F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806687E0.s")

typedef struct R1C_Struct_806688B8 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} R1C_Struct_806688B8;

extern R1C_Struct_806688B8 *D_807F9514;
extern ActorEntry D_807FB930[];
extern u16 D_807FBB34;

void func_806688B8(s32 arg0) {
    s32 i;
    u32 min = D_807F9514[arg0].unk0;
    u32 max = D_807F9514[arg0].unk4;

    for (i = 0; i < D_807FBB34; i++) {
        Actor *actor = D_807FB930[i].actor;
        u32 val = actor->unk150;

        if (!(actor->unk60 & 0x2000) && val >= min && max >= val) {
            actor->unk150 = 0;
        }
    }
}

typedef struct R1C_TriangleS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
} R1C_TriangleS;

typedef struct R1C_CrossStack {
    f32 cross;
    f32 v0[3];
    f32 v1[3];
} R1C_CrossStack;

s32 func_8066893C(R1C_TriangleS *arg0) {
    R1C_CrossStack sp;

    sp.v1[0] = arg0->x[2] - arg0->x[0];
    sp.v1[2] = arg0->z[2] - arg0->z[0];
    sp.v0[0] = arg0->x[1] - arg0->x[0];
    sp.v0[2] = arg0->z[1] - arg0->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806689F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80668B28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80668C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80668E9C.s")

typedef struct R1C_TriangleF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} R1C_TriangleF;

typedef struct R1C_Entry_94C0 {
    f32 unk0;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} R1C_Entry_94C0;

extern R1C_Entry_94C0 D_807F94C0[];
extern u8 D_807F9510;
extern s16 D_807F94A8;
s32 func_80669930(R1C_TriangleF *);
void func_80669830(s32, R1C_TriangleF *, s32);

void func_80669588(R1C_TriangleF *arg0, f32 arg1) {
    if (D_807F9510 != 10) {
        D_807F94C0[D_807F9510].unk0 = arg1;
        if (func_80669930(arg0)) {
            D_807F94C0[D_807F9510].unk6 = 1;
        } else {
            D_807F94C0[D_807F9510].unk6 = 2;
        }
        func_80669830(0, arg0, 0);
        D_807F94C0[D_807F9510].unk4 = D_807F94A8;
        D_807F9510++;
    }
}

s32 func_80669650(u8 arg0, u8 *arg1) {
    u8 i = 0;

    do {
        if (arg1[i] != 0xFF && arg1[i] == arg0) {
            return 0;
        }
        i++;
    } while (i < 2);
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806696A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80669830.s")


s32 func_80669930(R1C_TriangleF *arg0) {
    R1C_CrossStack sp;

    sp.v1[0] = arg0->x[2] - arg0->x[0];
    sp.v1[2] = arg0->z[2] - arg0->z[0];
    sp.v0[0] = arg0->x[1] - arg0->x[0];
    sp.v0[2] = arg0->z[1] - arg0->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806699C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80669A6C.s")

typedef struct R1C_BoundingBox {
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
} R1C_BoundingBox;

s32 func_80669BE8(R1C_BoundingBox *arg0, f32 arg1, f32 arg2) {
    if (arg1 < arg0->minX) {
        return 0;
    }
    if (arg2 < arg0->minZ) {
        return 0;
    }
    if (arg0->maxX < arg1) {
        return 0;
    }
    if (arg0->maxZ < arg2) {
        return 0;
    }
    return 1;
}

s32 func_80669C6C(R1C_BoundingBox *arg0, f32 arg1) {
    if (arg1 < arg0->minY) {
        return 0;
    }
    if (arg0->maxY < arg1) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80669CB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80669E04.s")

void *func_80610FE8(s32);
void gunzip(void *, void *, void *);
void heapFree(void *);
void heapFreeDeferred(void *);
extern void *D_80748E14;
void func_8066B5F4(void);
s32 func_8066B4D4(s32, s32, s32 *, s32 *);
s32 func_8066B9F4();
void func_8066BC00();
void func_8066B4AC(s32, s32, s32);
extern s32 D_807F9678;
extern u8 D_807F967C;
extern u8 D_807F967D;
extern s32 *D_807F95A8[];
extern u8 D_80748E18[];
extern s32 *D_807FB1A0[];
s32 func_8066AC10(void *);
void func_8066ACA4(s32, void *, s32, void *);
typedef struct {
    void *unk0;
    void *unk4;
    u8 unk8;
} R1D_StructA8A0;

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A08C.s")

void func_8066A584(void *arg0, f32 arg1) {
    if (D_807F9510 != 0xA) {
        D_807F94C0[D_807F9510].unk0 = arg1;
        if (func_8066AC10(arg0) != 0) {
            D_807F94C0[D_807F9510].unk6 = 1;
        } else {
            D_807F94C0[D_807F9510].unk6 = 2;
        }
        func_8066ACA4(0, arg0, 0, D_807F94C0);
        D_807F94C0[D_807F9510].unk4 = D_807F94A8;
        D_807F9510++;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A64C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A75C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A988.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066AC10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066ACA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066ADA0.s")

void func_8066AEE4(void *arg0, void *arg1) {
    void *sp24;
    void *sp20;

    sp24 = arg0;
    sp20 = arg1;
    if (D_80748E14 == NULL) {
        D_80748E14 = func_80610FE8(0x2400);
    }
    gunzip(&sp24, &sp20, D_80748E14);
    heapFree(arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066AF40.s")

s32 func_8066B020(s32 arg0, s32 arg1) {
    s32 sp1C;
    s32 sp18;

    func_8066B5F4();
    func_8066B4D4(arg0, arg1, &sp1C, &sp18);
    if (sp18 == 0) {
        return 0;
    }
    return sp1C;
}

s32 func_8066B06C(s32 arg0, s32 arg1) {
    s32 sp1C;
    s32 sp18;

    if (D_80748E18[arg0] != 0) {
        sp18 = D_807FB1A0[arg0][arg1];
    } else {
        func_8066B5F4();
        func_8066B4D4(arg0, arg1, &sp1C, &sp18);
    }
    return sp18;
}

void func_8066B0DC(void) {
    D_807F967C = 1;
}

void func_8066B0EC(s32 arg0) {
    D_807F9678 = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B0F8.s")

void func_8066B424(void) {
    D_807F967D = 1;
}

void func_8066B434(void *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    s32 sp18;

    if (func_8066B9F4(arg0) == 0) {
        func_8066BC00(arg0, &sp1C, &sp18);
        func_8066B4AC(sp1C, sp18, 0);
        if (D_807F967D == 0) {
            heapFreeDeferred(arg0);
        } else {
            heapFree(arg0);
        }
    }
    D_807F967D = 0;
}

void func_8066B4AC(s32 arg0, s32 arg1, s32 arg2) {
    if (D_807F95A8[arg0] != NULL) {
        D_807F95A8[arg0][arg1] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B4D4.s")


s32 func_8066B5C8(s32 arg0, s32 arg1) {
    s32 *ptr = D_807F95A8[arg0];
    s32 ret = 0;

    if (ptr != NULL) {
        ret = ptr[arg1];
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B5F4.s")


typedef struct R1ENode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u16 pad8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ struct R1ENode *left;
    /* 0x18 */ struct R1ENode *right;
} R1ENode;

s32 func_8066B75C(R1ENode *node) {
    s32 count;

    if (node == NULL) {
        return 0;
    }
    count = func_8066B75C(node->left);
    return func_8066B75C(node->right) + count + 1;
}

extern void *D_807F9628[];
u32 func_8066C2B4(u32);
void func_8066B7F4(void *, s32, s32, s32);

void func_8066B7AC(s32 arg0, s32 arg1, s32 arg2) {
    func_8066B7F4(D_807F9628[func_8066C2B4(arg0)], arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B7F4.s")

void *func_8066B924(void *, s32, s32, s32);

void func_8066B8C8(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = func_8066C2B4(arg0);

    D_807F9628[index] = func_8066B924(D_807F9628[index], arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B924.s")

s32 func_8066BB44(void *, s32);

s32 func_8066B9F4(s32 arg0) {
    return func_8066BB44(D_807F9628[func_8066C2B4(arg0)], arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BA2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BAB8.s")
#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BB44.s")

void *func_8066BC5C(void *, s32, s32, s32);

void func_8066BC00(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = func_8066C2B4(arg0);

    D_807F9628[index] = func_8066BC5C(D_807F9628[index], arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BC5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BD54.s")

void func_8066BE20(s32);

void func_8066BDE0(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        func_8066BE20(i);
    }
}

typedef struct R1EBufferItem {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
} R1EBufferItem;

void func_8066BFF0(R1ENode *, R1EBufferItem *, s32 *);
void func_8066C0DC(void *, s32, s32);
R1ENode *func_8066BF0C(R1EBufferItem *, s32, s32);
void func_8066BECC(R1ENode *);

void func_8066BE20(s32 arg0) {
    s32 count;
    void *buffer;
    R1ENode *new_root;
    s32 index;

    index = 0;
    count = func_8066B75C(D_807F9628[arg0]);
    if (count != 0) {
        buffer = func_80610FE8(count * 20);
        func_8066BFF0(D_807F9628[arg0], buffer, &index);
        func_8066C0DC(buffer, 0, count - 1);
        new_root = func_8066BF0C(buffer, 0, count - 1);
        func_8066BECC(D_807F9628[arg0]);
        D_807F9628[arg0] = new_root;
        heapFree(buffer);
    }
}


void func_8066BECC(R1ENode *node) {
    if (node != NULL) {
        func_8066BECC(node->left);
        func_8066BECC(node->right);
        heapFree(node);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BF0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BFF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066C0DC.s")

u32 func_8066C2B4(u32 arg0) {
    return (arg0 >> 12) % 20;
}
