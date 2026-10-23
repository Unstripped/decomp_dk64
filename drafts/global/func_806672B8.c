// func_806672B8 (src/global/6AD90.c): 362/363 insns, frame 0xF8 matches, all saved regs and callers match, ternary matches, 4-byte stack shift on spA0 (0xA4 vs 0xA0)
#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666090.s")

extern u8 D_807F94B4;

void func_80666280(arg0)
u8 arg0;
{
    D_807F94B4 = arg0;
}

void func_80666428(Actor *, f32, f32, f32, ...);
extern u8 D_807F94B3;
extern u8 D_807F94BC;
extern f32 D_807F948C;

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666290.s")

void func_8066635C(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    u8 sp3F;
    u8 sp3E;
    f32 sp38;
    f32 sp34;

    if (arg0->unk58 == 0xBC) {
        D_807F94B3 = 1;
    } else {
        D_807F94B3 = 0;
    }
    D_807F94BC = 1;
    func_80666428(NULL, arg1, arg2, arg3, &sp3F, &sp38, &sp3E, &sp34, 0);
    *arg4 = D_807F948C;
}

extern u8 D_807F94AE;
extern u8 D_807F94AF;
extern u8 D_807F94B0;
extern u8 D_807F94B7;
extern u8 D_807F951D;

void func_806663F8(void) {
    D_807F94AE = 0;
    D_807F94AF = 0;
    D_807F94B0 = 0;
    D_807F94B7 = 0;
}

u8 func_8066641C(void) {
    return D_807F951D;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666428.s")

extern u8 D_807F946E;
extern u8 D_807F94B1;
extern u8 D_807F94AA;
extern s16 D_807F94A2;
extern s16 D_807F94A4;

u8 func_80666A88(void) {
    return D_807F946E;
}

u8 func_80666A94(void) {
    return D_807F94AE;
}

u8 func_80666AA0(void) {
    return D_807F94AF;
}

u8 func_80666AAC(void) {
    return D_807F94B0;
}

u8 func_80666AB8(void) {
    return D_807F94B7;
}

void func_80666AC4(s16 *arg0, s16 *arg1) {
    *arg0 = D_807F94A2;
    *arg1 = D_807F94A4;
}

u8 func_80666AE0(void) {
    return D_807F94B1;
}

u8 func_80666AEC(void) {
    return D_807F94AA;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666AF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666D88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666F04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666FC8.s")

extern u8 D_807F9484;
extern f32 D_807F9488;
extern s16 D_807F9490;
extern s16 D_807F9498;
extern u8 D_807F94B5;
extern u8 D_807F9510;
u8 func_80667180(f32, f32, f32 *, s32);

s32 func_80667110(f32 arg0, f32 arg1, void *arg2) {
    s32 ret;

    D_807F9484 = 0;
    D_807F9510 = 0;
    ret = func_80667180(arg0, arg1, arg2, 0);
    D_807F94A4 = D_807F9498;
    D_807F94A2 = D_807F9490;
    return ret;
}

u8 func_8066715C(f32 *arg0) {
    *arg0 = D_807F9488;
    return D_807F9484;
}

u8 func_80667174(void) {
    return D_807F94B5;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80667180.s")

typedef struct R4L_SubNode {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[0x60 - 0x4E];
    /* 0x60 */ u8 unk60;
} R4L_SubNode;

typedef struct R4L_Node {
    /* 0x00 */ R4L_SubNode *unk0;
    /* 0x04 */ u8 pad4[0x2C - 0x04];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[0x4A - 0x2E];
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B[0x50 - 0x4B];
    /* 0x50 */ struct R4L_Node *next;
} R4L_Node;

extern R4L_Node *D_807F93C0;
s32 func_8065F5F0(R4L_Node *);
f32 func_806608FC(R4L_Node *, s32, s32, s32);
s32 func_80668C30(s16 *, f32, f32);
f32 func_8066785C(s16 *, f32, f32);
s32 func_80666FC8(f32, f32, f32, s32);

u8 func_806672B8(f32 arg0, f32 arg1, f32 *arg2, Actor *arg3) {
    f32 pad[4];
    f32 x[4];
    f32 y[4];
    f32 z[4];
    s16 spA0[10];
    u8 sp9F;
    f32 var_fs5;
    R4L_Node *var_s3;
    f32 var_fs0;
    f32 sp8C;
    f32 temp_fs1;
    s32 temp_s0;
    s32 cell_x;
    s32 cell_z;

    sp9F = 0;
    var_fs5 = 999999.0f;
    var_s3 = D_807F93C0;
    sp8C = (f32)((f64)*arg2 + 4.0);
    if (var_s3 != NULL) {
        do {
            if (var_s3->unk0->unk46 <= arg0 && var_s3->unk0->unk48 <= arg1 && arg0 <= var_s3->unk0->unk4A && arg1 <= var_s3->unk0->unk4C) {
                var_fs0 = arg0 * 6.0f;
                temp_fs1 = arg1 * 6.0f;
                temp_s0 = func_8065F5F0(var_s3) & 0xFF;
                cell_x = (arg0 - var_s3->unk0->unk46) / (f32)var_s3->unk2C;
                cell_z = (arg1 - var_s3->unk0->unk48) / (f32)var_s3->unk2C;

                x[0] = var_s3->unk2C * cell_x + var_s3->unk0->unk46;
                z[0] = var_s3->unk2C * cell_z + var_s3->unk0->unk48;
                y[0] = func_806608FC(var_s3, x[0], z[0], temp_s0);

                x[1] = (cell_x + 1) * var_s3->unk2C + var_s3->unk0->unk46;
                z[1] = z[0];
                y[1] = func_806608FC(var_s3, x[1], z[1], temp_s0);
                x[2] = x[0];
                z[2] = (cell_z + 1) * var_s3->unk2C + var_s3->unk0->unk48;
                y[2] = func_806608FC(var_s3, x[2], z[2], temp_s0);

                x[3] = x[1];
                z[3] = z[2];
                y[3] = func_806608FC(var_s3, x[3], z[3], temp_s0);

                spA0[0] = x[0] * 6.0f;
                spA0[3] = y[0] * 6.0f;
                spA0[6] = z[0] * 6.0f;

                spA0[1] = x[1] * 6.0f;
                spA0[4] = y[1] * 6.0f;
                spA0[7] = z[1] * 6.0f;

                spA0[2] = x[3] * 6.0f;
                spA0[5] = y[3] * 6.0f;
                spA0[8] = z[3] * 6.0f;

                if (func_80668C30(spA0, var_fs0, temp_fs1) != 0) {
                    var_fs0 = func_8066785C(spA0, var_fs0, temp_fs1) / 6.0f;
                } else {
                    spA0[1] = x[2] * 6.0f;
                    spA0[4] = y[2] * 6.0f;
                    spA0[7] = z[2] * 6.0f;
                    var_fs0 = func_8066785C(spA0, var_fs0, temp_fs1) / 6.0f;
                }

                switch (var_s3->unk0->unk60) {
                case 0:
                case 2:
                case 3:
                    sp9F = 1;
                    if (var_s3->unk0->unk60 == 2 || var_s3->unk0->unk60 == 3) {
                        if ((var_fs0 < *arg2 ? *arg2 - var_fs0 : -(*arg2 - var_fs0)) < 6.0f) {
                            switch (var_s3->unk0->unk60) {
                            case 2:
                                D_807F94AF = 2;
                                break;
                            case 3:
                                D_807F94AF = 1;
                                break;
                            }
                        }
                    }
                    if (func_80666FC8(var_fs5, var_fs0, sp8C, 0) != 0) {
                        var_fs5 = var_fs0;
                    }
                    break;
                case 1:
                    if (arg3 != NULL) {
                        if (arg3->unk80 < var_fs0) {
                            arg3->unkB0[0] = -1;
                            arg3->unk6A |= 4;
                            if (var_s3->unk4A & 1) {
                                D_807F94B0 = 1;
                            }
                        }
                        arg3->unkAC = var_fs0;
                        arg3->unk6A |= 2;
                    }
                    D_807F9484 = 1;
                    D_807F9488 = var_fs0;
                    break;
                }
            }
            var_s3 = var_s3->next;
        } while (var_s3 != NULL);
    }
    if (sp9F != 0) {
        *arg2 = var_fs5;
    }
    return sp9F;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066785C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806679BC.s")

s32 func_80666FC8(f32, f32, f32, s32);

s32 func_80668520(f32 *arg0, f32 arg1, f32 arg2, f32 *arg3) {
    f32 diff;
    f64 val;

    val = (f64)(arg2 * 6.0f);
    if (val > 1614.0) {
        diff = val - 1614.0;
    } else {
        diff = -(val - 1614.0);
    }
    if (diff < 40.0f) {
        D_807F94AE = 1;
    }
    if (func_80666FC8(*arg0, 684.0f, arg1, 1)) {
        *arg3 = 114.0f;
        return 1;
    }
    return 0;
}

typedef struct R2C_TriangleS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
    s16 unk12;
} R2C_TriangleS;

typedef struct R1C_Entry_94C0 {
    f32 unk0;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} R1C_Entry_94C0;

extern R1C_Entry_94C0 D_807F94C0[];
extern s16 D_807F94A8;
s32 func_8066893C();
void func_806689F0(s32, R2C_TriangleS *, s32);

void func_806685E0(R2C_TriangleS *arg0, f32 arg1) {
    if (D_807F9510 != 10) {
        D_807F94C0[D_807F9510].unk0 = arg1 / 6.0f;
        if (func_8066893C(arg0)) {
            D_807F94C0[D_807F9510].unk6 = 1;
        } else {
            D_807F94C0[D_807F9510].unk6 = 2;
        }
        if (arg0->unk12 & 1) {
            D_807F94C0[D_807F9510].unk6 |= 4;
        }
        if (arg0->unk12 & 0x400) {
            D_807F94C0[D_807F9510].unk6 |= 8;
        }
        func_806689F0(0, arg0, 0);
        D_807F94C0[D_807F9510].unk4 = D_807F94A8;
        D_807F9510++;
    }
}

typedef struct R1C_Struct_806688B8 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} R1C_Struct_806688B8;

extern R1C_Struct_806688B8 *D_807F9514;
extern s32 D_8076A064;
extern s32 D_807F9518;
extern u8 D_807F951C;
void func_806688B8(s32);
void heapFree(void *);
void *func_80610FE8(s32);
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);

void func_806686F4(s32 arg0) {
    u32 sp34;

    if (D_807F9514[arg0].unk0 == 0) {
        sp34 = D_807F9514[arg0].unk10;
        if (sp34 != 0) {
            D_807F9514[arg0].unk0 = (u32)func_80610FE8(sp34);
            D_807F9514[arg0].unk4 = D_807F9514[arg0].unk0 + (sp34 / 24) * 24;
            func_8060B140(D_807F9514[arg0].unkC, (void *)D_807F9514[arg0].unk0, &sp34, 0, 0, 0, 0);
        }
    }
    D_807F9514[arg0].unk8 = D_8076A064;
}

void func_806687E0(void) {
    s32 i;

    if (!D_807F951C) {
        for (i = 0; i < D_807F9518; i++) {
            if (D_807F9514[i].unk0 != 0 && (u32)(D_8076A064 - D_807F9514[i].unk8) >= 21) {
                func_806688B8(i);
                heapFree((void *)D_807F9514[i].unk0);
                D_807F9514[i].unk0 = 0;
                D_807F9514[i].unk4 = 0;
            }
        }
    }
}
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806689F0.s")

s32 func_80668B28(R1C_TriangleS *arg0, s32 arg1, s32 arg2) {
    s32 p0, p1, p2;
    s32 val;

    p0 = arg0->x[0];
    p1 = arg0->x[1];
    p2 = arg0->x[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (arg1 < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < arg1) {
        return 0;
    }

    p0 = arg0->z[0];
    p1 = arg0->z[1];
    p2 = arg0->z[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (arg2 < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < arg2) {
        return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80668C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80668E9C.s")

typedef struct R1C_TriangleF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} R1C_TriangleF;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806696A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80669830.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806699C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80669A6C.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80669CB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80669E04.s")

void gunzip(void *, void *, void *);
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
s32 func_8066AC10();
void func_8066ACA4(s32, void *, s32, void *);
typedef struct {
    void *unk0;
    void *unk4;
    u8 unk8;
} R1D_StructA8A0;

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A08C.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A64C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A75C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A988.s")

typedef struct R2D_TriangleAC10 {
    u8 pad0[0x24];
    R1C_TriangleF tri;
} R2D_TriangleAC10;

s32 func_8066AC10(R2D_TriangleAC10 *arg0) {
    R1C_CrossStack sp;

    sp.v1[0] = arg0->tri.x[2] - arg0->tri.x[0];
    sp.v1[2] = arg0->tri.z[2] - arg0->tri.z[0];
    sp.v0[0] = arg0->tri.x[1] - arg0->tri.x[0];
    sp.v0[2] = arg0->tri.z[1] - arg0->tri.z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066ACA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066ADA0.s")

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

extern R1D_StructA8A0 D_807FA8A0[];
extern s8 D_80746834;
extern OSMesgQueue D_807656D0;
extern s32 D_807F9680;

void func_8066AF40(void) {
    s32 i;

    i = 0;
    if (D_807F9680 > 0) {
        do {
            D_80746834 = 7;
            osRecvMesg(&D_807656D0, NULL, 1);
            D_80746834 = 0;
            if (D_807FA8A0[i].unk8 != 0) {
                func_8066AEE4(D_807FA8A0[i].unk0, D_807FA8A0[i].unk4);
            }
        } while (++i < D_807F9680);
    }
    if (D_80748E14 != NULL) {
        heapFree(D_80748E14);
        D_80748E14 = NULL;
    }
    D_807F9680 = 0;
}

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066B0F8.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066B4D4.s")

s32 func_8066B5C8(s32 arg0, s32 arg1) {
    s32 *ptr = D_807F95A8[arg0];
    s32 ret = 0;

    if (ptr != NULL) {
        ret = ptr[arg1];
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066B5F4.s")


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
void func_8066B7F4();

void func_8066B7AC(s32 arg0, s32 arg1, s32 arg2) {
    func_8066B7F4(D_807F9628[func_8066C2B4(arg0)], arg0, arg1, arg2);
}

typedef struct R2ENode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x14 */ struct R2ENode *left;
    /* 0x18 */ struct R2ENode *right;
} R2ENode;

void func_80732354(s32, s32, s32, s32);
void func_8066BA2C(s32, u8 *, u16 *, s32 *);
void func_8066B7F4(R2ENode *arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    u8 sp2F;
    u16 sp2C;
    s32 sp28;

    if (arg0 == NULL) {
        sp2F = 0;
        sp2C = 0;
        sp28 = 0;
        func_8066BA2C(arg1, &sp2F, &sp2C, &sp28);
        func_80732354(7, sp2F, sp2C, D_8076A064 - sp28);
    }
    if (arg1 == arg0->unk0) {
        *arg2 = arg0->unk4;
        *arg3 = arg0->unk8;
    } else if (arg0->unk0 < arg1) {
        func_8066B7F4(arg0->right, arg1, arg2, arg3);
    } else {
        func_8066B7F4(arg0->left, arg1, arg2, arg3);
    }
}

R2ENode *func_8066B924();

void func_8066B8C8(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = func_8066C2B4(arg0);

    D_807F9628[index] = func_8066B924(D_807F9628[index], arg0, arg1, arg2);
}

R2ENode *func_8066B924(R2ENode *node, u32 arg1, s32 arg2, s32 arg3) {
    if (node == NULL) {
        node = (R2ENode *)func_80610FE8(sizeof(R2ENode));
        node->unkC = 1;
        node->unk0 = arg1;
        node->unk4 = arg2;
        node->unk8 = arg3;
        node->unk10 = D_807F967C;
        node->right = NULL;
        node->left = NULL;
    } else if (arg1 == node->unk0) {
        node->unkC++;
        if (D_807F967C) {
            node->unk10 = 1;
        }
    } else if (node->unk0 < arg1) {
        node->right = func_8066B924(node->right, arg1, arg2, arg3);
    } else {
        node->left = func_8066B924(node->left, arg1, arg2, arg3);
    }
    return node;
}

s32 func_8066BB44();

s32 func_8066B9F4(s32 arg0) {
    return func_8066BB44(D_807F9628[func_8066C2B4(arg0)], arg0);
}

typedef struct R2EQueueItem {
    s32 unk0;
    s32 unk4;
    u16 unk8;
    u8 unkA;
} R2EQueueItem;

extern u8 D_807FB220;
extern u8 D_807FB221;
extern R2EQueueItem D_807FB228[];

void func_8066BA2C(s32 arg0, u8 *arg1, u16 *arg2, s32 *arg3) {
    s32 i;

    if ((i = D_807FB221 - 1) < 0) {
        i = 0x3F;
    }
    while (i != D_807FB220) {
        if (arg0 == D_807FB228[i].unk4) {
            *arg1 = D_807FB228[i].unkA;
            *arg2 = D_807FB228[i].unk8;
            *arg3 = D_807FB228[i].unk0;
            break;
        }
        if (--i < 0) {
            i = 0x3F;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066BAB8.s")

void func_8066BAB8();

s32 func_8066BB44(R1ENode *node, u32 arg1) {
    u8 sp2F;
    u16 sp2C;
    s32 sp28;

    if (node == NULL) {
        sp2F = 0;
        sp2C = 0;
        sp28 = 0;
        func_8066BA2C(arg1, &sp2F, &sp2C, &sp28);
        return 0;
    }
    if (arg1 == node->unk0) {
        if (node->unk10 == 0) {
            node->unkC--;
        }
        func_8066BAB8(arg1, node->unk7, node->unkA);
        return node->unkC;
    }
    if (node->unk0 < arg1) {
        return func_8066BB44(node->right, arg1);
    }
    return func_8066BB44(node->left, arg1);
}

R2ENode *func_8066BC5C();

void func_8066BC00(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = func_8066C2B4(arg0);

    D_807F9628[index] = func_8066BC5C(D_807F9628[index], arg0, arg1, arg2);
}

R2ENode *func_8066BD54();

R2ENode *func_8066BC5C(R2ENode *node, u32 key, s32 *out_val1, s32 *out_val2) {
    R2ENode *old;

    if (node != NULL) {
        if (key == node->unk0) {
            *out_val1 = node->unk4;
            *out_val2 = node->unk8;
            if (node->left == NULL && node->right == NULL) {
                heapFree(node);
                node = NULL;
            } else if (node->left == NULL) {
                old = node;
                node = node->right;
                heapFree(old);
            } else if (node->right == NULL) {
                old = node;
                node = node->left;
                heapFree(old);
            } else {
                node->right = func_8066BD54(node->right, &node->unk0, &node->unk4, &node->unk8, &node->unkC, &node->unk10);
            }
        } else if (node->unk0 < key) {
            node->right = func_8066BC5C(node->right, key, out_val1, out_val2);
        } else {
            node->left = func_8066BC5C(node->left, key, out_val1, out_val2);
        }
    }
    return node;
}

R2ENode *func_8066BD54(R2ENode *node, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, u8 *arg5) {
    void *pad;
    R2ENode *left = node->left;

    if (left == NULL) {
        R2ENode *old;

        *arg1 = node->unk0;
        *arg2 = node->unk4;
        *arg3 = node->unk8;
        *arg4 = node->unkC;
        *arg5 = node->unk10;
        old = node;
        node = node->right;
        heapFree(old);
    } else {
        node->left = func_8066BD54(left, arg1, arg2, arg3, arg4, arg5);
    }
    return node;
}

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

R1ENode *func_8066BF0C(R1EBufferItem *buffer, s32 start, s32 end) {
    R2ENode *node;
    s32 mid;

    node = (R2ENode *)func_80610FE8(sizeof(R2ENode));
    mid = (start + end) / 2;

    node->unk0 = buffer[mid].unk0;
    node->unk4 = buffer[mid].unk4;
    node->unk8 = buffer[mid].unk8;
    node->unkC = buffer[mid].unkC;
    node->unk10 = buffer[mid].unk10;

    if (start != mid) {
        node->left = (R2ENode *)func_8066BF0C(buffer, start, mid - 1);
    } else {
        node->left = NULL;
    }

    if (end != mid) {
        node->right = (R2ENode *)func_8066BF0C(buffer, mid + 1, end);
    } else {
        node->right = NULL;
    }

    return (R1ENode *)node;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066BFF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066C0DC.s")

u32 func_8066C2B4(u32 arg0) {
    return (arg0 >> 12) % 20;
}
