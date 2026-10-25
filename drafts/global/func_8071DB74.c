// func_8071DB74 (src/global/11BC10.c): stage 5: state pointer stays v0 rather than target v1; the target move v0,v1 after the guard remains absent.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} NM1FallingState;

typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
} NM1FloorSource;

void func_8071D94C(void *, Ub2ActorView *, s8 *);

void func_8071DB74(Ub2ActorView *arg0, s8 *arg1) {
    NM1FallingState *motion;
    NM1FallingState *motion_for_floor;
    NM1FloorSource *floor;
    u8 state;

    motion = arg0->unk384;
    if (motion == NULL) {
        func_8071D94C(NULL, arg0, arg1);
        motion = arg0->unk384;
    }
    motion_for_floor = motion;
    motion->unk8 = (f32)(motion->unk8 + -0.5f);
    arg0->unk340 += motion->unk0;
    arg0->unk344 += motion->unk8;
    arg0->unk348 += motion->unk4;
    state = *arg1;
    if (state == 0) {
        floor = arg0->unk338;
        if (floor != NULL) {
            if (arg0->unk344 <= floor->unkAC) {
                state = (u8)(*arg1 = 1);
            }
        } else if (arg0->unk344 <= motion_for_floor->unkC) {
            state = (u8)(*arg1 = 1);
        }
        if (state != 0) {
            func_80718124(arg0->unk360 * 5.0f, arg0->unk340, arg0->unk344, arg0->unk348);
        }
    }
}
