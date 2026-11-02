// func_80613AF8 (src/global/17B90.c): func_80613AF8 (src/global/17B90.c): stage 6; frame 0x18 matches; all 49 lines 1:1; score 7 (down from 17): s16 flag/index + s32 sum two-step (`sum = index*7 + field; sum -= 2;`) with no value local; FAKEs `arg1 = arg1 & -1` + dead `flag == 0`; remaining: sum in v0 vs a0 and ring t7/t8 (target andi before lui); u16 sum without mask reaches 13 only
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
void func_80613C48(struct ControllerStateView *, s16, f32, f32);

void func_80613AF8(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
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
        arg1 = D_807FBB58[(u32)(sum & 0xFFFF)] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = arg1;
    }
    func_80613C48(arg0, arg1, arg2, arg3);
}
