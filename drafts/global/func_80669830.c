// func_80669830 (src/global/6AD90.c): STAGE 3 (blocked by func_80666AF8 signature, same as func_806689F0): arg0 passthrough impossible with AF8 prototyped as u8 arg0; remaining diff: +4 bytes (sw a0 / andi) and f4/f18 alternation in the cross terms.
typedef struct Col6A2PlaneTriF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
    u8 unk24;
} Col6A2PlaneTriF;

typedef struct Col6A2Cross3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} Col6A2Cross3D;

void func_80669830(arg0, arg1, arg2)
s32 arg0;
Col6A2PlaneTriF *arg1;
u8 arg2;
{
    Col6A2Cross3D sp;

    sp.v1[0] = arg1->x[2] - arg1->x[0];
    sp.v1[1] = arg1->y[2] - arg1->y[0];
    sp.v1[2] = arg1->z[2] - arg1->z[0];
    sp.v0[0] = arg1->x[1] - arg1->x[0];
    sp.v0[1] = arg1->y[1] - arg1->y[0];
    sp.v0[2] = arg1->z[1] - arg1->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v0[1] * sp.v1[2]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v0[2] * sp.v1[0]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v0[0] * sp.v1[1]);
    func_80666AF8(arg0, sp.cross[0], sp.cross[1], sp.cross[2], arg1->unk24, arg2, 1);
}
