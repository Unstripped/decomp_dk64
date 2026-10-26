// func_80613BA0 (src/global/17B90.c): stage 4; m2c draft saved; remaining compatible controller view declaration and float argument scheduling
void func_80613BA0(Perm3bController *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s32 flag;
    s16 index;
    Perm3bGlobalView *state;

    flag = arg1 & 0x4000;
    index = arg1 - flag;
    state = (Perm3bGlobalView *)D_807FD580;
    if (arg1 >= 0) {
        arg1 = D_807FBB58[(index * 7 + arg0->value - 2) & 0xFFFF] + flag;
    }
    state->value = arg1;
    func_80613CA8(arg0, arg1, arg2, arg3);
}
