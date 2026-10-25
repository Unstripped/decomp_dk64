// func_8071DB74 (src/global/11BC10.c): Stage 5: compiled same 0x20 frame and s0 set; remaining v1/v0 state allocation and two flag-materialization delay-slot differences.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Ub3bFallingState;

typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
} Ub3bFloorSource;

void func_8071D94C(void *, Ub2ActorView *, s8 *);

void func_8071DB74(Ub2ActorView *arg0, s8 *arg1) {
    void *var_v1;
    Ub3bFloorSource *temp_v1;
    u8 var_a0;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        func_8071D94C(NULL, arg0, arg1);
        var_v1 = arg0->unk384;
    }
    ((Ub3bFallingState *) var_v1)->unk8 = (f32) (((Ub3bFallingState *) var_v1)->unk8 + -0.5f);
    arg0->unk340 += ((Ub3bFallingState *) var_v1)->unk0;
    arg0->unk344 += ((Ub3bFallingState *) var_v1)->unk8;
    arg0->unk348 += ((Ub3bFallingState *) var_v1)->unk4;
    var_a0 = *arg1;
    if (var_a0 == 0) {
        temp_v1 = arg0->unk338;
        if (temp_v1 != NULL) {
            if (arg0->unk344 <= temp_v1->unkAC) {
                *arg1 = 1;
                var_a0 = 1 & 0xFF;
            }
        } else if (arg0->unk344 <= ((Ub3bFallingState *) var_v1)->unkC) {
            *arg1 = 1;
            var_a0 = 1 & 0xFF;
        }
        if (var_a0 != 0) {
            func_80718124(arg0->unk360 * 5.0f, arg0->unk340, arg0->unk344, arg0->unk348);
        }
    }
}
