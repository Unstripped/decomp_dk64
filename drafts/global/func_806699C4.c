// func_806699C4 (src/global/699B0.c): regalloc off by 1 on t-registers (t8-t3 vs t9-t4), frame 0x118 and all stack offsets match
#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80664CB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80664D20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665160.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806651FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_806653C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665558.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665564.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665AAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665ACC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665AE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665C18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665DE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665E48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665E94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665F24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80665FB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666090.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80666280.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_80669588.s")

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

typedef struct R1C_TriangleF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} R1C_TriangleF;

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

typedef struct R1C_D_807F6000 {
    u8 pad[0x88];
    s16 unk88;
    u8 pad8A[6];
} R1C_D_807F6000;

extern R1C_D_807F6000 *D_807F6000;
void func_8066C610(s16, s8, float [4][4]);
void func_8062FF10(float [4][4], float [4][4]);

typedef struct R1C_Actor_99C4 {
    u8 pad[0x100];
    f32 unk100;
    f32 unk104;
    f32 unk108;
    s16 unk10C;
    s8 unk10E;
    s8 unk10F;
} R1C_Actor_99C4;

void func_806699C4(R1C_Actor_99C4 *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 pad2[10];
    float spB0[4][4];
    float pad[4][4];
    float sp30[4][4];

    R1C_D_807F6000 *p = D_807F6000;
    arg0->unk10C = p[arg1].unk88;
    arg0->unk10E = arg3;
    arg0->unk10F = arg2;
    func_8066C610(arg1, arg2, spB0);
    func_8062FF10(sp30, spB0);
    guMtxXFMF(sp30, arg4, arg5, arg6, &arg0->unk100, &arg0->unk104, &arg0->unk108);
}

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A08C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A584.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A64C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A75C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066A988.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066AC10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066ACA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066ADA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066AEE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066AF40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B06C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B0DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B0EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B0F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B424.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B434.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B4D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B5C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B5F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B75C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B7AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B7F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B8C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B924.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066B9F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BA2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BAB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BB44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BC00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BC5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BD54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BDE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BE20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BECC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BF0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066BFF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066C0DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/699B0/func_8066C2B4.s")
