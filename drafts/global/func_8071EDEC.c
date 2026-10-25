// func_8071EDEC (src/global/11BC10.c): stage 3: instruction sequence and local offsets match; only target frame is 0x40 versus candidate 0x38
void actorGetNodePos(s32, s32, f32 *, f32 *, f32 *);
typedef struct {
    u8 unk0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 unk34C[0x10];
    s32 unk35C;
} Ub7bEdecActor;

void func_8071EDEC(Ub7bEdecActor *arg0, s32 arg1) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 pad;

    pad = 0.0f;
    actorGetNodePos(arg0->unk35C, 1, &sp34, &sp30, &sp2C);
    arg0->unk340 = (f32)((f64)arg0->unk340 + ((f64)(sp34 - arg0->unk340) * 0.1));
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)(sp30 - arg0->unk344) * 0.1));
    arg0->unk348 = (f32)((f64)arg0->unk348 + ((f64)(sp2C - arg0->unk348) * 0.1));
}
