// func_80717100 (src/global/11BC10.c): stage 4: recovered allocation and arithmetic; target frame and callee saves are reproduced, but pointer live-range register allocation differs
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Ub1Motion10;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    u8 pad344[0x14];
    s32 unk35C;
    u8 pad360[0x24];
    Ub1Motion10 *unk384;
} Ub1ActorView;

void *func_80610FE8(s32);
s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80717100(Ub1ActorView *arg0, void *arg1) {
    Ub1Motion10 *temp_v0;
    Ub1Motion10 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xA);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (func_80611A44() >> 15) % 4095;
        temp_v0->unk2 = arg0->unk35C;
        temp_v0->unk4 = arg0->unk35C >> 16;
        temp_v0->unk6 = arg0->unk340;
        temp_v0->unk8 = arg0->unk348;
        var_v1 = arg0->unk384;
    }
    var_v1->unk0 += var_v1->unk4;
    arg0->unk340 = func_80612794(var_v1->unk0) * var_v1->unk2 + var_v1->unk6;
    arg0->unk348 = func_80612790(var_v1->unk0) * var_v1->unk2 + var_v1->unk8;
}
