// func_806689F0 (src/global/6AD90.c): STAGE 3 (blocked by func_80666AF8 signature): passes arg0 straight to func_80666AF8 (a0 untouched in expected, no sw a0). AF8 is now prototyped (u8 arg0,...,u8 arg6) so any s32/u8 arg0 gets narrowed (sw a0,0x60 + lbu a0 / andi+move) => +4 bytes. Needs AF8's first param to be word-sized while AF8 itself still emits sw a0,0x18(sp) (s32 arg0 drops that store; u16 keeps it but callers would andi). K&R def with s32 arg0 and the body below otherwise matches the frame 0x60 and offsets.
typedef struct Col6A2PlaneTriS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
    s16 unk12;
    u8 unk14;
} Col6A2PlaneTriS;

typedef struct Col6A2Cross3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} Col6A2Cross3D;

void func_806689F0(arg0, arg1, arg2)
s32 arg0;
Col6A2PlaneTriS *arg1;
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
    func_80666AF8(arg0, sp.cross[0], sp.cross[1], sp.cross[2], arg1->unk14, arg2, 0);
}
