// func_80613FB0 (src/global/17B90.c): stage 6; frame 0x18 matches; all 25 insns 1:1; score 5 (down from 65: clean C with 7 * arg1; diff only in missing move t6, a1 copy)
typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} CtrlA_Controller;
extern u16 *D_807FBB58;
struct AnimControllerRef;
void func_80614014(struct AnimControllerRef *, u16, f32, u8);

void func_80613FB0(CtrlA_Controller *arg0, s32 arg1, f32 arg2, u8 arg3) {
    u16 idx = (u16)(7 * arg1 + arg0->unk58 - 2);
    func_80614014((struct AnimControllerRef *)arg0, D_807FBB58[idx], arg2, arg3);
}
