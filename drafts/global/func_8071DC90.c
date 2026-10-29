// func_8071DC90 (src/global/11BC10.c): stage 5: struct+schedule match (frame 0x30, homes sp28@0x28/sp20@0x20 via pad24); remaining = ugen int-temp ring offset in the unk4/unkC wrap section (target t0,t1,t5,t6,t8 vs mine t8,t9,t1,t2,t4) + %lo addends; tried m2c shape, ternary mins, field-test alloc pattern, wrap reorder [add4,wrap4,addC,wrapC]
typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xEC];
    void *unk174;
} Fx11BHDTarget;

typedef struct {
    u8 pad0[0x1F0];
    u32 unk1F0;
} Fx11BHDFlags;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Fx11BHDState;

void func_8071DC90(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BHDState *temp_v0;
    Fx11BHDTarget *sp28;
    f32 pad24;
    f32 sp20;

    sp20 = 0.3f;
    sp28 = (Fx11BHDTarget *)(u32)arg0->unk35C;
    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(0x18);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.0f;
        temp_v0->unk4 = (f32)(func_806119FC() * 4095.0f);
        temp_v0->unk8 = (f32)((func_806119FC() > 0.5 ? (f64)func_806119FC() : 0.5) * 300.0);
        if ((f64)func_806119FC() > 0.5) {
            temp_v0->unk8 = (f32)-temp_v0->unk8;
        }
        temp_v0->unkC = (f32)(func_806119FC() * 4095.0f);
        temp_v0->unk10 = (f32)((func_806119FC() > 0.5 ? (f64)func_806119FC() : 0.5) * 300.0);
        if ((f64)func_806119FC() > 0.5) {
            temp_v0->unk10 = (f32)-temp_v0->unk10;
        }
        temp_v0->unk14 = (f32)(func_806119FC() > 0.3 ? (f64)func_806119FC() : 0.3);
        sp20 = 1.0f;
    }
    temp_v0 = arg0->unk384;
    if (temp_v0->unk0 < 1.0f) {
        temp_v0->unk0 = temp_v0->unk0 + 0.033333335f;
    }
    temp_v0->unk4 = (f32)(temp_v0->unk4 + temp_v0->unk8);
    temp_v0->unk4 = (f32)((s32)temp_v0->unk4 & 0xFFF);
    temp_v0->unkC = (f32)(temp_v0->unkC + temp_v0->unk10);
    temp_v0->unkC = (f32)((s32)temp_v0->unkC & 0xFFF);
    arg0->unk340 = (f32) (((((func_80612794((s16) (s32) temp_v0->unk4) * (15.0f * temp_v0->unk0)) + sp28->unk7C) - arg0->unk340) * sp20) + arg0->unk340);
    arg0->unk348 = (f32) (((((func_80612790((s16) (s32) temp_v0->unk4) * (15.0f * temp_v0->unk0)) + sp28->unk84) - arg0->unk348) * sp20) + arg0->unk348);
    arg0->unk344 = (f32) (((((((func_80612794((s16) (s32) temp_v0->unkC) * (temp_v0->unk14 * temp_v0->unk0)) + 1.0f) * 15.0f) + sp28->unk80) - arg0->unk344) * sp20) + arg0->unk344);
    if (!(((Fx11BHDFlags *)sp28->unk174)->unk1F0 & 0x10)) {
        *arg1 = 1;
    }
}
