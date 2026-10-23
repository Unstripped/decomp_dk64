// func_8066ACA4 (src/global/699B0.c): 3D triangle normal cross product and call to func_80666AF8
typedef struct {
    u8 pad0[0x24];
    f32 x0, x1, x2;
    f32 y0, y1, y2;
    f32 z0, z1, z2;
} R1D_Triangle;
void func_80666AF8(s32, f32, f32, f32, s32, s32, s32);

void func_8066ACA4(s32 arg0, R1D_Triangle *arg1, u8 arg2) {
    f32 v1[3];
    f32 v2[3];
    f32 cross[3];

    v1[0] = arg1->x2 - arg1->x0;
    v1[1] = arg1->y2 - arg1->y0;
    v1[2] = arg1->z2 - arg1->z0;

    v2[0] = arg1->x1 - arg1->x0;
    v2[1] = arg1->y1 - arg1->y0;
    v2[2] = arg1->z1 - arg1->z0;

    cross[0] = (v1[1] * v2[2]) - (v2[1] * v1[2]);
    cross[1] = (v1[2] * v2[0]) - (v2[2] * v1[0]);
    cross[2] = (v1[0] * v2[1]) - (v2[0] * v1[1]);

    func_80666AF8(arg0, cross[0], cross[1], cross[2], 1, arg2, 2);
}
