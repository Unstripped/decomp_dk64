// func_80613FB0 (src/global/17B90.c): stage 4; permuter best 465; remaining call argument register allocation and scheduling
typedef struct { u8 pad0[0x58]; s32 value; } Perm3Controller;
extern u16 *D_807FBB58;
void func_80614014(Perm3Controller *, u16, f32, u8);

void func_80613FB0(Perm3Controller *arg0, s32 arg1, f32 arg2, s32 arg3) {
    func_80614014(arg0, D_807FBB58[((arg1 * 7 + arg0->value - 2) & 0xFFFF)], arg2, arg3 & 0xFF);
}
