// func_80612AD8 (src/global/17540.c): stage 4: direct field stores match through delay-slot store; remaining diff is two target trailing nops before func_80612B00. Tried direct fields, aggregate initializer (unsupported by IDO), and local aggregate copy.
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

void func_80612AD8(Vec3f *arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}
