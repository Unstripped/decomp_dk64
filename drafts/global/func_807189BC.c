// func_807189BC (src/global/11BC10.c): stage 4: retained 0x28 frame; source-pointer local remains sp+0x24 rather than target sp+0x20 after corrected zero clamp.
typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
} NM2ProjectileSource;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} NM2Projectile;

void func_807189BC(TimedEffectActorView *arg0, s8 *arg1) {
    s32 sp20;
    f64 temp_fv0;
    NM2Projectile *var_v1;

    sp20 = arg0->unk35C;
    if (arg0->unk384 == NULL) {
        var_v1 = func_80610FE8(8);
        arg0->unk384 = var_v1;
        temp_fv0 = (f64)((NM2ProjectileSource *)sp20)->unkB8 * 0.01;
        if (temp_fv0 < 0.0) {
            var_v1->unk0 = (s16)0.0;
        } else {
            var_v1->unk0 = (s16)temp_fv0;
        }
        var_v1->unk2 = ((NM2ProjectileSource *)sp20)->unkE6;
        var_v1->unk4 = (s16)(((s32)(func_80611A44() >> 0xF) % 1000) + 0xC8);
        arg0->unk360 = (f32)((f64)arg0->unk360 + ((f64)((s32)(func_80611A44() >> 0xF) % 100) / 500.0));
        arg0->unk364 = arg0->unk360;
        var_v1->unk6 = (s16)((NM2ProjectileSource *)sp20)->unkAC;
    } else {
        var_v1 = arg0->unk384;
    }
    arg0->unk340 = (f32)(arg0->unk340 - ((f32)var_v1->unk0 * func_80612794(var_v1->unk2)));
    arg0->unk348 = (f32)(arg0->unk348 - ((f32)var_v1->unk0 * func_80612790(var_v1->unk2)));
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)var_v1->unk4 / 500.0));
    if ((f32)var_v1->unk6 <= arg0->unk344) {
        *arg1 = 1;
        func_80718124((f32)((f64)arg0->unk360 * 1.5), arg0->unk340, (f32)var_v1->unk6, arg0->unk348);
    }
    if ((s32)arg0->unk36D >= 0xC) {
        arg0->unk36D -= 0xA;
        return;
    }
    *arg1 = 1;
    arg0->unk36D = 0U;
}
