// func_8071E1C8 (src/global/11BC10.c): stage 4: target frame/save shape matches; closest diff keeps state pointer in v0 through null guard before moving it to s0
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Ub7E110Motion;

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Ub7E1C8Target;

extern s32 actorTableContains(void *);

void func_8071E1C8(Ub2ActorView *arg0, s8 *arg1) {
    f64 pad0;
    f64 pad1;
    f64 pad2;
    f32 sp3C;
    f32 sp2C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fv1;
    Ub7E1C8Target *temp_s2;
    Ub7E110Motion *temp_v0;

    temp_v0 = arg0->unk384;
    if (temp_v0 == NULL) {
        *arg1 = 1;
        return;
    }
    temp_s2 = (Ub7E1C8Target *)(u32)arg0->unk35C;
    if (actorTableContains(temp_s2) == 0) {
        *arg1 = 1;
        return;
    }
    sp2C = func_80612794((s16)(s32)(f32)((s32)(temp_v0->unk10 * ((1.0f - (temp_v0->unk0 * 2.0f)) * 2048.0f)) & 0xFFF)) * temp_v0->unk8;
    temp_v0->unk14 = (f32)((f64)temp_v0->unk14 + (2.0 * (f64)((1.0f - (temp_v0->unk0 * 2.0f)) * 4096.0f) * (f64)temp_v0->unkC));
    temp_v0->unk14 = (f32)((s32)temp_v0->unk14 & 0xFFF);
    sp3C = func_80612794((s16)(s32)temp_v0->unk14) * sp2C;
    temp_fv0 = func_80612790((s16)(s32)temp_v0->unk14);
    temp_fa0 = temp_v0->unk4;
    var_fv1 = temp_v0->unk10 * temp_fa0;
    if (temp_v0->unk0 == 0.0f) {
        var_fv1 = temp_fa0 - var_fv1;
    }
    arg0->unk340 = (f32)(temp_s2->unk7C + sp3C);
    arg0->unk348 = (f32)(temp_s2->unk84 + (temp_fv0 * sp2C));
    arg0->unk344 = (f32)(temp_s2->unk80 + var_fv1);
    temp_v0->unk10 = (f32)(temp_v0->unk10 + temp_v0->unkC);
    if (temp_v0->unk10 >= 1.0f) {
        *arg1 = 1;
    }
}
