// func_8066AC10 (src/global/699B0.c): triangle winding 2D normal cross product; needs exact local layout to force stack stores
typedef struct R1D_StructAC10 {
    u8 pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 pad30[0xC];
    f32 unk3C;
    f32 unk40;
    f32 unk44;
} R1D_StructAC10;

typedef struct {
    f32 x, y, z;
} R1D_Vec3f;

s32 func_8066AC10(R1D_StructAC10 *arg0) {
    R1D_Vec3f v1;
    R1D_Vec3f v2;
    f32 normal[2];
    s32 var_v0;

    var_v0 = 0;
    v1.x = arg0->unk2C - arg0->unk24;
    v1.z = arg0->unk44 - arg0->unk3C;
    v2.x = arg0->unk28 - arg0->unk24;
    v2.z = arg0->unk40 - arg0->unk3C;
    normal[1] = (v1.z * v2.x) - (v2.z * v1.x);
    if ((f64) normal[1] <= 0.0) {
        var_v0 = 1;
    }
    return var_v0;
}
