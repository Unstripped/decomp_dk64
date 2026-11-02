// func_80613AF8 (src/global/17B90.c): func_80613AF8 (src/global/17B90.c): stage 6; frame 0x18 matches; all 49 lines 1:1 shape; score 3 (down from 7): two-statement index mask (sum = sum & 0xFFFF; arg1 = D_807FBB58[sum] + flag;) fixes the t7/t8 ring (index evaluated before the table base); remaining 3 lines: sum in v0 vs a0 (addu/addiu/andi). Tried: u16/u32 sum, flag/index type grid, s32 flag (index gets t0), noindex (flag->a0), tmp locals, dead-test/no-code-def hill-climbs (hc, ~20k evals), phantom v0 locals
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
        sum = sum & 0xFFFF;
        arg1 = D_807FBB58[sum] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = arg1;
    }
    func_80613C48(arg0, arg1, arg2, arg3);
}
