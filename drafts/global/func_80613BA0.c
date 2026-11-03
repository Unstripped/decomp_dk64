// func_80613BA0 (src/global/17B90.c): W2IntA: clone of func_80613AF8 (callee controllerAnimSetState), stage 6, score 3 unchanged, same remaining diff (sum v0 vs a0). See func_80613AF8 note: sum coloured first (adjsave >= 2.0 > index/flag 1.5), no spelling tried moves the chain off v0.
typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} GlobalPlayerAnimView;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} ControllerStateParamView;

extern u16 *D_807FBB58;
struct ControllerStateView;
void controllerAnimSetState(struct ControllerStateView *, s16, f32, f32);

void func_80613BA0(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s16 flag;
    s16 index;
    s32 sum;
    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        arg1 = arg1 & -1; // FAKE: no-code def, advances ugen ring / raises arg1 refs
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = index;
        if (flag == 0) {} // FAKE: dead test, steers flag into v1
        sum = index * 7 + ((ControllerStateParamView *)arg0)->unk58;
        sum -= 2;
        sum = sum & 0xFFFF;
        arg1 = D_807FBB58[sum] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = arg1;
    }
    controllerAnimSetState(arg0, arg1, arg2, arg3);
}
