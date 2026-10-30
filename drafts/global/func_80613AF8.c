// func_80613AF8 (src/global/17B90.c): stage 6; frame 0x18 matches; all 42 insns 1:1; score 85 (table lookup and if/else regalloc)
typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} RvT1_GlobalView;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} RvT1_ControllerStateView;

extern Struct807FD580 *D_807FD580;
extern u16 *D_807FBB58;
struct ControllerStateView;
void func_80613C48(struct ControllerStateView *, s16, f32, f32);

void func_80613AF8(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s32 flag;
    s16 index;
    u16 *table;
    s32 value;

    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        ((RvT1_GlobalView *)D_807FD580)->unk4E = index;
        value = ((RvT1_ControllerStateView *)arg0)->unk58;
        arg1 = (table = D_807FBB58)[(u32)(((index * 7 + value) - 2) & 0xFFFF)] + flag;
    } else {
        ((RvT1_GlobalView *)D_807FD580)->unk4E = arg1;
    }
    func_80613C48(arg0, arg1, arg2, arg3);
}
