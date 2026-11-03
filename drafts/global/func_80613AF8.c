// func_80613AF8 (src/global/17B90.c): W2IntA: stage 6, score 3 unchanged (sum in v0 vs target a0: addu/addiu/andi). Colouring trace: sum (cand 19, adjsave 6.0/2.0 for any single-def form, min 2.0) is coloured FIRST and takes v0; target needs index(8)/flag(4) (adjsave 1.5 each, no-code defs and dead tests do NOT raise it) coloured before sum, or v0 forbidden. Tried this unit: 3780-variant index no-code-def count x sum spelling x use form grid, 211-form single/pair dead-test sweep, flagless (index = arg1 - (arg1 & 0x4000), end + (arg1 & 0x4000)) 192 variants (22: ring shifted), entry-live dead reads of flag/index/sum (illegal, 9), pre-def+test grid (3), callee return type s32/u8/s16/u32/void*/s8/u16 + 'return f(...)' (no change), sum types s16/u16/u32. No variant puts the chain anywhere but v0.
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
