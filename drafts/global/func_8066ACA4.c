// func_8066ACA4 (src/global/6AD90.c): func_8066ACA4 (src/global/6AD90.c): stage 6, only diff 'sw a0,0x60(sp)'+'lbu a0,0x63(sp)': caller narrows arg0 to func_80666AF8's u8 first param; with that callee param s32 the whole function matches (probe). Mul operand order (v1[1]*v0[2])-(v1[2]*v0[1]) fixed the f4/f10 FP permutation. Tried u8/void*/u32 arg0, prototyped def, casts: all still narrow.
typedef struct R6D_TriF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} R6D_TriF;

typedef struct CollisionBoxTriangleWork {
    u8 pad0[0x24];
    R6D_TriF tri;
} CollisionBoxTriangleWork;

typedef struct CrossProductStack3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} CrossProductStack3D;

void func_80666AF8(u8 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6);

void func_8066ACA4(arg0, arg1, arg2)
s32 arg0;
CollisionBoxTriangleWork *arg1;
u8 arg2;
{
    CrossProductStack3D sp;

    sp.v1[0] = arg1->tri.x[2] - arg1->tri.x[0];
    sp.v1[1] = arg1->tri.y[2] - arg1->tri.y[0];
    sp.v1[2] = arg1->tri.z[2] - arg1->tri.z[0];
    sp.v0[0] = arg1->tri.x[1] - arg1->tri.x[0];
    sp.v0[1] = arg1->tri.y[1] - arg1->tri.y[0];
    sp.v0[2] = arg1->tri.z[1] - arg1->tri.z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    func_80666AF8(arg0, sp.cross[0], sp.cross[1], sp.cross[2], 1, arg2, 2);
}
