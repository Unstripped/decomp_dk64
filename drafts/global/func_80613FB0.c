// func_80613FB0 (src/global/17B90.c): stage 5; frame 0x18 matches; caller home stores match; permuter closest score 440 (lhu vs andi in delay slot)
typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} RvE2_Controller;
extern u16 *D_807FBB58;
void func_80614014(void *, u16, f32, u8);

void func_80613FB0(RvE2_Controller *arg0, s32 arg1, f32 arg2, s32 arg3) {
    s32 new_var = ((arg0->unk58 + (arg1 * 7)) - 2) & 0xFFFF;
    func_80614014(arg0, D_807FBB58[new_var], arg2, arg3 & 0xFF);
}
