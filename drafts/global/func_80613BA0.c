// func_80613BA0 (src/global/17B90.c): stage 6; clone of func_80613AF8 (jal func_80613CA8 instead of func_80613C48); table lookup and if/else regalloc
typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} RvE2_GlobalView;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} RvE2_ControllerStateView;

extern Struct807FD580 *D_807FD580;
extern u16 *D_807FBB58;
struct ControllerStateView;
void func_80613CA8(struct ControllerStateView *, s16, f32, f32);

void func_80613BA0(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s32 flag;
    s16 index;
    u16 *table;
    s32 value;

    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        ((RvE2_GlobalView *)D_807FD580)->unk4E = index;
        value = ((RvE2_ControllerStateView *)arg0)->unk58;
        table = D_807FBB58;
        arg1 = table[(u32)(((index * 7 + value) - 2) & 0xFFFF)] + flag;
    } else {
        ((RvE2_GlobalView *)D_807FD580)->unk4E = arg1;
    }
    func_80613CA8(arg0, arg1, arg2, arg3);
}
