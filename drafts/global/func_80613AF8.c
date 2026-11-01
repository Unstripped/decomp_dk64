// func_80613AF8 (src/global/17B90.c): stage 6; frame 0x18 matches; all 42 insns 1:1; score 19 (s16 flag, direct table lookup; regalloc v0 vs v1 cascade in if block)
typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} CtrlA_GlobalView;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} CtrlA_ControllerStateView;

extern Struct807FD580 *gActivePlayerState;
extern u16 *D_807FBB58;
struct ControllerStateView;
void func_80613C48(struct ControllerStateView *, s16, f32, f32);

void func_80613AF8(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s16 flag;
    s16 index;
    s32 value;

    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        ((CtrlA_GlobalView *)gActivePlayerState)->unk4E = index;
        value = ((CtrlA_ControllerStateView *)arg0)->unk58;
        arg1 = D_807FBB58[(u32)(((index * 7 + value) - 2) & 0xFFFF)] + flag;
    } else {
        ((CtrlA_GlobalView *)gActivePlayerState)->unk4E = arg1;
    }
    func_80613C48(arg0, arg1, arg2, arg3);
}
