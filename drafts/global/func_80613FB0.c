// func_80613FB0 (src/global/17B90.c): stage 5; closest permuter score 440; caller home-slot spill a3 vs a1 and jal delay slot lhu
typedef struct { u8 pad0[0x58]; s32 value; } Perm3Controller;
extern u16 *D_807FBB58;
void func_80614014(Perm3Controller *, u16, f32, u8);

void func_80613FB0(Perm3Controller *arg0, s32 arg1, f32 arg2, s32 arg3) {
    int new_var = ((arg0->value + (arg1 * 7)) - 2) & 0xFFFF;
    func_80614014(arg0, D_807FBB58[new_var], arg2, arg3 & 0xFF);
}
