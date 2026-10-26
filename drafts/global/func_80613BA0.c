// func_80613BA0 (src/global/17B90.c): stage 3: semantic indexed transition compiled and fdiff'd; missing target a0 spill / global table base hoist, call delay-slot reload
typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} P17bGlobalView;

typedef struct {
    u8 pad0[4];
    void *unk4;
    u8 pad8[0x50];
    s32 unk58;
} P17bControllerView;

extern u16 D_807FBB58[];
void func_80613CA8(P17bControllerView *, s16, f32, f32);

void func_80613BA0(P17bControllerView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s16 index;
    s32 flag;

    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        ((P17bGlobalView *)D_807FD580)->unk4E = index;
        arg1 = D_807FBB58[((index * 7 + arg0->unk58 - 2) & 0xFFFF)] + flag;
    } else {
        ((P17bGlobalView *)D_807FD580)->unk4E = arg1;
    }
    func_80613CA8(arg0, arg1, arg2, arg3);
}
