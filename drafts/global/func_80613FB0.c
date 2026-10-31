// func_80613FB0 (src/global/17B90.c): stage 6; frame 0x18 matches; all 25 insns 1:1; score 65 (t7/t9 regalloc)
typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} RvT1_Controller;
extern u16 *D_807FBB58;
struct AnimControllerRef;
void func_80614014(struct AnimControllerRef *, u16, f32, u8);

void func_80613FB0(RvT1_Controller *arg0, s32 arg1, f32 arg2, u8 arg3) {
    s32 temp = (arg1 ^ (arg0->unk58 * 0)) & 0xFFFF;
    s32 new_var = (((temp * 7) + arg0->unk58) - 2) & 0xFFFF;
    func_80614014((struct AnimControllerRef *)arg0, D_807FBB58[new_var], arg2, arg3);
}
