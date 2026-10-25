// func_8071EDEC (src/global/11BC10.c): stage 7: frame corrected from 0x40 to target 0x38 by placing the f64 pad before the f32 locals; fdiff TEXT OK.
void actorGetNodePos(s32, s32, f32 *, f32 *, f32 *);
typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
} NM2EdecActor;

void func_8071EDEC(NM2EdecActor *arg0, s32 arg1) {
    f64 pad;
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    actorGetNodePos(arg0->unk35C, 1, &sp34, &sp30, &sp2C);
    arg0->unk340 = (f32)((f64)arg0->unk340 + ((f64)(sp34 - arg0->unk340) * 0.1));
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)(sp30 - arg0->unk344) * 0.1));
    arg0->unk348 = (f32)((f64)arg0->unk348 + ((f64)(sp2C - arg0->unk348) * 0.1));
}
