// func_8071EDEC (src/global/11BC10.c): stage 4: behavior and instruction sequence match; stack-local offsets are +8 (candidate 0x34/0x38/0x3C, target 0x2C/0x30/0x34) with target 0x40 frame
void actorGetNodePos(s32, s32, f32 *, f32 *, f32 *);
typedef struct {
    u8 unk0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 unk34C[0x10];
    s32 unk35C;
} Ud1dEdecActor;

void func_8071EDEC(Ud1dEdecActor *arg0, s32 arg1) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    actorGetNodePos(arg0->unk35C, 1, &sp34, &sp30, &sp2C);
    temp_fv1 = arg0->unk340;
    temp_fa0 = arg0->unk344;
    temp_fa1 = arg0->unk348;
    arg0->unk340 = (f32) ((f64) temp_fv1 + ((f64) (sp34 - temp_fv1) * 0.1));
    arg0->unk344 = (f32) ((f64) temp_fa0 + ((f64) (sp30 - temp_fa0) * 0.1));
    arg0->unk348 = (f32) ((f64) temp_fa1 + ((f64) (sp2C - temp_fa1) * 0.1));
}
