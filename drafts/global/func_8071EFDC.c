// func_8071EFDC (src/global/11BC10.c): stage 4: text/size identical; only caller-saved register allocation differs (target t6/t7/t8/t9 vs candidate v0/t6/t7), frame and instructions match
typedef struct {
    u8 unk0[0x330];
    void *unk330;
    u8 unk334[4];
    void *unk338;
    u8 unk33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    u8 unk34E[2];
    u8 unk350;
    u8 unk351[0xB];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 unk368[5];
    u8 unk36D;
} Ud1dActorView;

void func_8071EFDC(Ud1dActorView *arg0, s8 *arg1) {
    s32 temp_t7;

    arg0->unk360 = (f32) ((f64) arg0->unk360 * 1.05);
    arg0->unk364 = (f32) ((f64) arg0->unk364 * 1.05);
    temp_t7 = arg0->unk36D - 5;
    arg0->unk36D = temp_t7;
    if ((temp_t7 & 0xFF) < 6) {
        *arg1 = 1;
    }
}
