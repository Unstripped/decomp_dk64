// func_80717404 (src/global/11BC10.c): stage 3: recovered branch-specific trajectory and floating-point expressions; frame, delay-slot ordering, and register allocation remain
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Ub1Motion12;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s16 unk35C;
    s16 unk35E;
    u8 pad360[0xF];
    u8 unk36F;
    u8 pad370[0x14];
    Ub1Motion12 *unk384;
} Ub1ActorView;

void *func_80610FE8(s32);
s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80717404(Ub1ActorView *arg0, void *arg1) {
    Ub1Motion12 *temp_v0;
    Ub1Motion12 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        if (arg0->unk35C != 0) {
            temp_v0->unk0 = ((func_80611A44() >> 15) % 200) + arg0->unk35C - 0x64;
        } else {
            temp_v0->unk0 = (func_80611A44() >> 15) % 4095;
        }
        temp_v0->unk4 = (((func_80611A44() >> 15) % 10) + 5) * (arg0->unk36F != 0 ? 4.0 : 1.0);
        temp_v0->unk8 = arg0->unk35E + ((func_80611A44() >> 15) % 6);
        var_v1 = arg0->unk384;
    }
    if (arg0->unk36F != 0) {
        arg0->unk340 = (f32)((f64)arg0->unk340 + (4.0 * (0.01 * (f64)arg0->unk35E * (f64)func_80612794((s16)var_v1->unk0))));
        arg0->unk344 = (f32)((f64)arg0->unk344 + (4.0 * (0.01 * (f64)arg0->unk35E * (f64)func_80612790((s16)var_v1->unk0))));
    } else {
        arg0->unk340 = (f32)((f64)arg0->unk340 + (0.04 * (f64)arg0->unk35E * (f64)func_80612794((s16)var_v1->unk0)));
        arg0->unk348 = (f32)((f64)arg0->unk348 + (0.04 * (f64)arg0->unk35E * (f64)func_80612790((s16)var_v1->unk0)));
        if (arg0->unk35C == 0) {
            arg0->unk344 += var_v1->unk8;
            var_v1->unk8 -= 0.5;
        } else {
            arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)var_v1->unk8 * 0.2));
        }
    }
    arg0->unk35E = arg0->unk35E + var_v1->unk4;
}
