// func_80717DB4 (src/global/11BC10.c): Complete recovered logic; typed local motion state changes compiler register allocation.
typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    u8 pad360[0x24];
    void *unk384;
} Ub2ActorView;

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Ub2OrbitMotion;

void func_80717DB4(arg0, arg1)
Ub2ActorView *arg0;
s8 *arg1;
{
    Ub2OrbitMotion *temp_v0;
    Ub2OrbitMotion *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0x10);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = arg0->unk340;
        temp_v0->unk8 = 0;
        temp_v0->unkA = 0;
        temp_v0->unk4 = arg0->unk348;
        temp_v0->unkC = (s16) (((s32) (func_80611A44() % 10000) % 150) - 0x4B);
        temp_v0->unkE = (s16) (((s32) (func_80611A44() % 10000) % 150) - 0x4B);
        var_v1 = arg0->unk384;
    }
    arg0->unk340 = (f32) (((f64) func_80612794(var_v1->unk8) * 6.0) + (f64) var_v1->unk0);
    arg0->unk348 = (f32) (((f64) func_80612794(var_v1->unkA) * 6.0) + (f64) var_v1->unk4);
    var_v1->unk8 = var_v1->unk8 + var_v1->unkC;
    var_v1->unkA = var_v1->unkA + var_v1->unkE;
    arg0->unk344 = (f32) ((f64) arg0->unk344 - ((f64) arg0->unk35C / 100.0));
}
