// func_8071DC90 (src/global/11BC10.c): stage 3: typed behavioral draft compiled; target frame 0x30 versus current 0x50, and the movement update order diverges after the angle wraps
typedef struct { u8 pad0[0x174]; void *unk174; } Ub7DC90Target;
typedef struct { u8 pad0[0x1F0]; u32 unk1F0; } Ub7DC90Flags;
typedef struct { f32 unk0; f32 unk4; f32 unk8; f32 unkC; f32 unk10; f32 unk14; } Ub7DC90Motion;
typedef struct { u8 pad0[0x7C]; f32 unk7C; f32 unk80; f32 unk84; } Ub7DC90Position;

void func_8071DC90(Ub2ActorView *arg0, s8 *arg1) {
    Ub7DC90Target *sp28;
    f32 sp20;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f64 var_fv1;
    f64 var_fv1_2;
    Ub7DC90Motion *temp_v0;
    Ub7DC90Motion *var_v0;

    sp20 = 0.3f;
    sp28 = (Ub7DC90Target *)(u32)arg0->unk35C;
    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        temp_v0 = func_80610FE8(0x18);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.0f;
        temp_v0->unk4 = func_806119FC() * 4095.0f;
        if ((f64)func_806119FC() > 0.5) { var_fv1 = (f64)func_806119FC(); } else { var_fv1 = 0.5; }
        temp_v0->unk8 = (f32)(var_fv1 * 300.0);
        if ((f64)func_806119FC() > 0.5) { temp_v0->unk8 = -temp_v0->unk8; }
        temp_v0->unkC = func_806119FC() * 4095.0f;
        if ((f64)func_806119FC() > 0.5) { var_fv1_2 = (f64)func_806119FC(); } else { var_fv1_2 = 0.5; }
        temp_v0->unk10 = (f32)(var_fv1_2 * 300.0);
        if ((f64)func_806119FC() > 0.5) { temp_v0->unk10 = -temp_v0->unk10; }
        if ((f64)func_806119FC() > 0.3) { temp_v0->unk14 = (f32)(f64)func_806119FC(); } else { temp_v0->unk14 = 0.3f; }
        sp20 = 1.0f;
        var_v0 = arg0->unk384;
    }
    temp_fv0 = var_v0->unk0;
    if (temp_fv0 < 1.0f) { var_v0->unk0 = temp_fv0 + 0.033333335f; }
    var_v0->unk4 = var_v0->unk4 + var_v0->unk8;
    var_v0->unkC = var_v0->unkC + var_v0->unk10;
    var_v0->unk4 = (f32)((s32)var_v0->unk4 & 0xFFF);
    var_v0->unkC = (f32)((s32)var_v0->unkC & 0xFFF);
    temp_fv1 = arg0->unk340;
    arg0->unk340 = (f32)(((((func_80612794((s16)(s32)var_v0->unk4) * (15.0f * var_v0->unk0)) + ((Ub7DC90Position *)sp28)->unk7C) - temp_fv1) * sp20) + temp_fv1);
    temp_fv1_2 = arg0->unk348;
    arg0->unk348 = (f32)(((((func_80612790((s16)(s32)var_v0->unk4) * (15.0f * var_v0->unk0)) + ((Ub7DC90Position *)sp28)->unk84) - temp_fv1_2) * sp20) + temp_fv1_2);
    temp_fv1_3 = arg0->unk344;
    arg0->unk344 = (f32)(((((((func_80612794((s16)(s32)var_v0->unkC) * (var_v0->unk14 * var_v0->unk0)) + 1.0f) * 15.0f) + ((Ub7DC90Position *)sp28)->unk80) - temp_fv1_3) * sp20) + temp_fv1_3);
    if (!(((Ub7DC90Flags *)sp28->unk174)->unk1F0 & 0x10)) { *arg1 = 1; }
}
