// func_8071C48C (src/global/11BC10.c): stage 3: compiled starter; frame is 0x48 versus target 0x40 because 16-bit packed low-word conversion is unsigned in the candidate; lightAdd argument shape still needs refinement
typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} Ub6LightData;

typedef struct {
    u8 pad0[0x330];
    Ub6LightData *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    s16 unk34E;
    u8 pad350;
    u8 unk351;
    u8 pad352[0xA];
    u32 unk35C;
    f32 unk360;
    f32 unk364;
} Ub6LightActorView;

void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void lightSetFlags(s32, void *);

void func_8071C48C(Ub6LightActorView *arg0, s8 *arg1) {
    f32 sp3C;
    f32 sp38;
    f32 var_ft4;
    f32 var_fv1;
    s16 temp_v0;
    u32 temp_v0_2;

    temp_v0 = arg0->unk330->unk16;
    var_fv1 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv1 > 0.7) {
        var_fv1 = 1.0f;
    }
    temp_v0_2 = arg0->unk35C;
    if ((temp_v0_2 >> 0x10) != 0) {
        var_ft4 = (f32)(temp_v0_2 & 0xFFFF) * var_fv1;
    } else {
        var_ft4 = (f32)(temp_v0_2 & 0xFFFF);
    }
    sp3C = var_fv1;
    sp38 = var_ft4;
    lightSetFlags(1, arg0);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, sp38, 0, 0,
             (s32)((-80.0f * sp3C) + 255.0f), 0xFF);
}
