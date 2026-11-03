// func_80613AF8 (src/global/17B90.c): W3IntA wave3 (2026-11-02): stage 6, park score 3 unchanged. NEW basin with the target colours (sum chain in a0, flag v1; 49 insns, score 4, only the index ring temp is t0 vs target t2: 4 lines): body = flag=arg1&0x4000; if(flag==0){} FAKE; index=arg1-flag; arg1=arg1&-1 FAKE; unk4E=index; sum=(index*7+unk58-2)&0xFFFF (single statement); if(arg1&0x4000){} FAKE (extends the arg1&0x4000 CSE web over sum so v0 is taken and sum falls to a0); arg1=D_807FBB58[sum]+flag. Moving 'arg1=arg1&-1' to right after flag= gives score 2 but 50 insns (extra move t0,t7: arg1 redefined before index reads it). Tried this unit: 4.3k-variant grid (sum form x flag spelling x if/arg1-fake/E6-test slots), pair grids of 168 dead-test/no-code snippets on both bases (14k each), 2 simulated-annealing runs from the a0 basin (back to 3.3), store-forwarding kills (v=0 / no-code (1|w)?v:v+1), flag adjsave raisers (flag+(flag*0)). Cause of sum=v0: uopt colours sum (adjsave 6.0, 2.0 single-def) before flag(1.5)/index(1.5); the target needs v0 held by the arg1&0x4000 expression web live across sum.
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
