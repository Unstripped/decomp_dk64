// func_80671528 (src/global/70FD0.c): Plane normal calculation from CollisionBox (points 0,1,2 / 8.0f -> cross product v1 x v2 -> normalize with sqrtf -> write normal to arg1,2,3 -> call func_806744A8). Frame 0xA8 vs expected 0x88 (needs variable merging).
extern CollisionBox *D_807FB5D4;

void func_80671528(arg0, arg1, arg2, arg3, arg4)
M70M_Actor60 *arg0;
f32 *arg1;
f32 *arg2;
f32 *arg3;
u8 arg4;
{
    CollisionBox *box;
    M70M_Sub140 *sub;
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    f32 v1x, v1y, v1z;
    f32 v2x, v2y, v2z;
    f32 nx, ny, nz;
    f32 inv_len;

    sub = arg0->unk140;
    if (arg4 != 0) {
        box = (CollisionBox *)func_806732A8(D_807FB5DC, D_807FB5F6);
    } else {
        box = D_807FB5D4;
    }

    x0 = (f32)box->unk24 / 8.0f;
    y0 = (f32)box->unk28 / 8.0f;
    z0 = (f32)box->unk2C / 8.0f;
    x1 = (f32)box->unk30 / 8.0f;
    y1 = (f32)box->unk34 / 8.0f;
    z1 = (f32)box->unk38 / 8.0f;
    x2 = (f32)box->unk3C / 8.0f;
    y2 = (f32)box->unk40 / 8.0f;
    z2 = (f32)box->unk44 / 8.0f;

    v1y = y2 - y0;
    v1x = x2 - x0;
    v1z = z2 - z0;
    v2x = x1 - x0;
    v2y = y1 - y0;
    v2z = z1 - z0;

    nx = (v1y * v2z) - (v2y * v1z);
    ny = (v1z * v2x) - (v2z * v1x);
    nz = (v1x * v2y) - (v2x * v1y);

    inv_len = 1.0f / sqrtf((nz * nz) + ((nx * nx) + (ny * ny)));
    *arg1 = nx * inv_len;
    *arg2 = ny * inv_len;
    *arg3 = nz * inv_len;

    func_806744A8((M70H_Actor *)box, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
    if (arg4 != 0) {
        if (arg0->unk60 & 0x800) {
            D_807FB5C4 = sub->unkB0;
            D_807FB5CC = sub->unkB4;
        }
        sub->unkB0 = D_807FB5C4;
        sub->unkB4 = D_807FB5CC;
    }
}
