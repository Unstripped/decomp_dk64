// func_8071720C (src/global/11BC10.c): stage 4: m2c-equivalent control flow and all field semantics recovered; saved-register and pointer live-range allocation remain
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Ub1Motion8;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    u8 pad360[0x24];
    Ub1Motion8 *unk384;
} Ub1ActorView;

void *func_80610FE8(s32);
s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, s32, f32, f32, f32, s32, s32, s32, s32);

void func_8071720C(Ub1ActorView *arg0, void *arg1) {
    Ub1Motion8 *temp_v0;
    Ub1Motion8 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (func_80611A44() >> 15) % 4095;
        temp_v0->unk2 = ((func_80611A44() >> 15) % 10) + 2;
        temp_v0->unk4 = 0;
        temp_v0->unk6 = -0x32 - ((func_80611A44() >> 15) % 10000) % 600;
        var_v1 = arg0->unk384;
    }
    arg0->unk344 = (f32)((f64)arg0->unk344 - ((f64)var_v1->unk6 / 100.0));
    var_v1->unk6 += 0x14;
    arg0->unk340 = (f32)((f64)arg0->unk340 + (0.04 * (f64)var_v1->unk4 * (f64)func_80612794(var_v1->unk0)));
    arg0->unk348 = (f32)((f64)arg0->unk348 + (0.04 * (f64)var_v1->unk4 * (f64)func_80612790(var_v1->unk0)));
    var_v1->unk0 += 0x50;
    var_v1->unk4 += var_v1->unk2;
    if (arg0->unk35C != 0) {
        lightSetFlags(1);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0, 0.0f, 0.0f, 40.0f, 0, 0xFF, 0xFF,
                 (func_80611A44() >> 15) % 255);
    }
}
