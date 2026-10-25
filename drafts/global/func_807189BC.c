// func_807189BC (src/global/11BC10.c): Stage 3: compiled projectile behavior draft; target requires s1-held projectile and a non-prototyped float-bit third argument to func_80718124.
typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
} Ub3SourceView;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Ub3Projectile;

void func_807189BC(Ub2ActorView *arg0, s8 *arg1) {
    Ub3SourceView *sp20;
    f64 temp_fv0;
    u8 temp_v0_2;
    Ub3Projectile *temp_v0;
    Ub3Projectile *var_v1;

    sp20 = (Ub3SourceView *) arg0->unk35C;
    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_fv0 = (f64) sp20->unkB8 * 0.01;
        if (temp_fv0 < 2.0) {
            temp_v0->unk0 = 2;
        } else {
            temp_v0->unk0 = (s16) temp_fv0;
        }
        temp_v0->unk2 = sp20->unkE6;
        temp_v0->unk4 = (s16) (((s32) (func_80611A44() >> 0xF) % 1000) + 0xC8);
        arg0->unk360 = (f32) ((f64) arg0->unk360 + ((f64) ((s32) (func_80611A44() >> 0xF) % 100) / 500.0));
        arg0->unk364 = arg0->unk360;
        temp_v0->unk6 = (s16) sp20->unkAC;
        var_v1 = arg0->unk384;
    }
    arg0->unk340 = (f32) (arg0->unk340 - ((f32) var_v1->unk0 * func_80612794(var_v1->unk2)));
    arg0->unk348 = (f32) (arg0->unk348 - ((f32) var_v1->unk0 * func_80612790(var_v1->unk2)));
    arg0->unk344 = (f32) ((f64) arg0->unk344 + ((f64) var_v1->unk4 / 500.0));
    if ((f32) var_v1->unk6 <= arg0->unk344) {
        *arg1 = 1;
        func_80718124((f32) ((f64) arg0->unk360 * 1.5), arg0->unk340, (s32) (f32) var_v1->unk6, arg0->unk348);
    }
    temp_v0_2 = arg0->unk36D;
    if ((s32) temp_v0_2 >= 0xC) {
        arg0->unk36D = (u8) (temp_v0_2 - 0xA);
        return;
    }
    *arg1 = 1;
    arg0->unk36D = 0U;
}
